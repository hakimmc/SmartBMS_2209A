/**
 * @file TcpServer.c
 * @brief TCP server implementation to handle incoming client connections, authenticate, and exchange data.
 * @date 18 December 2024
 * @author hakimmc
 */

#include "TcpServer.h"
#include "Wifi.h"
#include "d2cc_lib.h"
#include "gpio.h"

/** @brief Structure to hold CAN message data. */
extern DbcStruct maindbc_struct;
extern DbcStruct *struct_of_comm;
extern SemaphoreHandle_t DataControlSemaphore;

#define TCP_TAG "TCP_SERVER" /**< Tag for logging */

/** @brief Username for GUI authentication */
char* GUI_USER = "root";
/** @brief Password for GUI authentication */
char* GUI_PASS = "otto";

/** @brief Led status value */
uint32_t led_status  = 1;

/**
 * @brief Creates and starts a TCP server to listen for client connections.
 * 
 * This function sets up a TCP socket, binds it to a specified address and port,
 * and listens for incoming connections. For each connection, a new task is created
 * to handle the client.
 * 
 * @param pvParameter Unused parameter for FreeRTOS task.
 */
void Create_Server(void* pvParameter)
{
    char addr_str[128];
    int addr_family;
    int ip_protocol;

    struct sockaddr_in dest_addr;
    dest_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(SERVER_PORT);
    addr_family = AF_INET;
    ip_protocol = IPPROTO_IP;
    inet_ntoa_r(dest_addr.sin_addr, addr_str, sizeof(addr_str) - 1);

    int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
    if (listen_sock < 0) {
        ESP_LOGE(TCP_TAG, "Unable to create socket: errno %d", errno);
        return;
    }
    ESP_LOGI(TCP_TAG, "Socket created");

    int err = bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err != 0) {
        ESP_LOGE(TCP_TAG, "Socket unable to bind: errno %d", errno);
        close(listen_sock);
        return;
    }
    ESP_LOGI(TCP_TAG, "Socket bound, port %d", SERVER_PORT);

    err = listen(listen_sock, 1);
    if (err != 0) {
        ESP_LOGE(TCP_TAG, "Error occurred during listen: errno %d", errno);
        close(listen_sock);
        return;
    }
    ESP_LOGI(TCP_TAG, "Socket listening");

    while (1) {
        struct sockaddr_in source_addr;
        socklen_t addr_len = sizeof(source_addr);
        int sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);
        if (sock < 0) {
            ESP_LOGE(TCP_TAG, "Unable to accept connection: errno %d", errno);
            break;
        }
        ESP_LOGI(TCP_TAG, "Socket accepted");
        maindbc_struct.Can_Main.Signal.TcpEnable = TcpEnable_TCP_Connected;
        maindbc_struct.Can_Main.Signal.TcpClientCount++;

        TaskHandle_t xHandle = NULL;
        xTaskCreate(Handle_Client, "Client_Handler", 4096, (void*)sock, (UBaseType_t)1, &xHandle);
    }

    close(listen_sock);
}

/**
 * @brief Handles communication with a single client.
 * 
 * This function receives and processes commands from the client, authenticates the user,
 * and manages communication based on different states. It handles login, data requests, and exit commands.
 * 
 * @param args Socket descriptor for the client.
 */
void Handle_Client(void* args)
{
    int sock = (int)args;
    char rx_buffer[32];
    uint8_t timeout_counter = 0;
    uint8_t max_timeout = 200;
    uint8_t state = 0;
    int len;

    struct timeval timeout;
    timeout.tv_sec = 30;
    timeout.tv_usec = 0;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        close(sock);
        vTaskDelete(NULL);
    }

    while (1) {
        switch (state) {
            case 0:
                len = receive_data(sock, rx_buffer, sizeof(rx_buffer) - 1, &timeout_counter, max_timeout);
                if (len == -2) {
                    state = 4;
                } else if (len == -1) {
                    state = 3;
                } else {
                    rx_buffer[len] = 0;
                    if(!memcmp(rx_buffer, "HELO", 4))
                    {
                        while(memcmp(rx_buffer, "OBT", 3))
                        {
                            send(sock, "ID?", 3, 0);
                            len = receive_data(sock, rx_buffer, sizeof(rx_buffer) - 1, &timeout_counter, max_timeout);
                            if (len == -2) {
                                state = 4;
                                break;
                            } else if (len == -1) {
                                state = 3;
                                break;
                            }
                        }
                        if(state < 3){
                            send(sock, "EHLO", 4, 0);
                            state = 1;
                            timeout_counter = 0;
                        }
                    }
                    else state = 3;
                }
                break;

            case 1:
                len = receive_data(sock, rx_buffer, sizeof(rx_buffer) - 1, &timeout_counter, max_timeout);
                if (len == -2) {
                    state = 4;
                } else if (len == -1) {
                    state = 3;
                } else {
                    rx_buffer[len] = '\0';
                    if (!memcmp(rx_buffer, "login_", 6)) {
                        char* credentials[2];
                        char* login_data = rx_buffer + 6;
                        char* token = strtok(login_data, "_");
                        int indx = 0;
                        while (token != NULL && indx < 2) {
                            credentials[indx++] = token;
                            token = strtok(NULL, "_");
                        }
                        if (indx == 2 && strcmp(GUI_USER, credentials[0]) == 0 && strcmp(GUI_PASS, credentials[1]) == 0) {
                            send(sock, "OK", 2, 0);
                            state = 2;
                        } else {
                            state = 3;
                        }
                    }
                    else {
                        state = 3;
                    }
                }
                break;

            case 2:
                len = receive_data(sock, rx_buffer, sizeof(rx_buffer) - 1, &timeout_counter, max_timeout);
                if(len != -2 || len != -1) {
                    rx_buffer[len] = '\0';
                    if (!memcmp(rx_buffer, "data", 4)) {
                        //send(sock, "OK", 2, 0); full data
                        char jsonString[2048];
                        if(xSemaphoreTake(DataControlSemaphore,portMAX_DELAY))
                        {
                            ConvertToJson(struct_of_comm, jsonString);
                            send(sock, jsonString, strlen(jsonString), 0);
                            xSemaphoreGive(DataControlSemaphore);
                            vTaskDelay(10);
                            gpio_set_level(LED_PIN, led_status); /**< Turn the LED to led_status. */
                            led_status = led_status==1?0:1;
                        }
                    }
                    else if (!memcmp(rx_buffer, "exit", 4)) {
                        state = 3;
                    }
                    rx_buffer[0] = 'r';
                    //memset(, 0, sizeof(rx_buffer));
                }
                break;

            case 3:
                send(sock, "ER", 2, 0);
                maindbc_struct.Can_Main.Signal.TcpClientCount--;
                if(maindbc_struct.Can_Main.Signal.TcpClientCount == 0){
                    maindbc_struct.Can_Main.Signal.TcpEnable = TcpEnable_TCP_Online;
                }
                close(sock);
                vTaskDelete(NULL);
                break;

            case 4:
                send(sock, "TO", 2, 0);
                maindbc_struct.Can_Main.Signal.TcpClientCount--;
                if(maindbc_struct.Can_Main.Signal.TcpClientCount == 0){
                    maindbc_struct.Can_Main.Signal.TcpEnable = TcpEnable_TCP_Online;
                }
                close(sock);
                vTaskDelete(NULL);
                break;
        }
    }
    close(sock);
    vTaskDelete(NULL);
}

/**
 * @brief Receives data from the client socket.
 * 
 * This function receives data from the client and handles timeouts. If no data is received
 * within a specified timeout period, it returns a timeout error.
 * 
 * @param sock Socket descriptor for the client.
 * @param buffer Buffer to store received data.
 * @param size Size of the buffer.
 * @param timeout_counter Counter to track consecutive timeouts.
 * @param max_timeout Maximum allowed consecutive timeouts before returning an error.
 * 
 * @return Length of received data, -1 if timeout occurs, or -2 if maximum timeouts reached.
 */
int receive_data(int sock, char* buffer, size_t size, uint8_t* timeout_counter, uint8_t max_timeout)
{
    int len = recv(sock, buffer, size, 0);
    if (len <= 0) {
        (*timeout_counter)++;
        if (*timeout_counter > max_timeout) {
            return -2;
        }
        return -1;
    }
    *timeout_counter = 0;
    return len;
}

/**
 * @brief Convert to JSON function of Dbc Parameters.
 */
void ConvertToJson(DbcStruct *dbc, char *jsonString) {
    sprintf(jsonString, 
        "{"
            "\"Battery_Messages\": {"
                "\"BatteryChemistry\": %d, "
                "\"Battery_Count\": %d, "
                "\"BatteryBalance_MaxVoltage\": %d, "
                "\"BatteryBalance_MinVoltage\": %d, "
                "\"BatteryBalance_MaxTemp\": %d, "
                "\"BatteryBalance_MinTemp\": %d, "
                "\"BatterySOC\": %d, "
                "\"OCV_Voltages\": %d"
            "}, "
            "\"Battery_Temperatures\": {"
                "\"Battery_Temp_AUX0\": %d, "
                "\"Battery_Temp_AUX1\": %d, "
                "\"Battery_Temp_AUX2\": %d, "
                "\"Battery_Temp_AUX3\": %d, "
                "\"Battery_Temp_AUX4\": %d, "
                "\"Battery_Temp_AUX5\": %d, "
                "\"Battery_Temp_AUX6\": %d, "
                "\"Battery_Temp_AUX7\": %d"
            "}, "
            "\"Battery_Voltages_1\": {"
                "\"BatteryVoltage_1\": %d, "
                "\"BatteryVoltage_2\": %d, "
                "\"BatteryVoltage_3\": %d, "
                "\"BatteryVoltage_4\": %d, "
                "\"BatteryVoltage_5\": %d, "
                "\"BatteryVoltage_6\": %d, "
                "\"BatteryVoltage_7\": %d, "
                "\"BatteryVoltage_8\": %d"
            "}, "
            "\"Battery_Voltages_2\": {"
                "\"BatteryVoltage_9\": %d, "
                "\"BatteryVoltage_10\": %d, "
                "\"BatteryVoltage_11\": %d, "
                "\"BatteryVoltage_12\": %d, "
                "\"BatteryVoltage_13\": %d, "
                "\"BatteryVoltage_14\": %d, "
                "\"BatteryVoltage_15\": %d, "
                "\"BatteryVoltage_16\": %d"
            "}, "
            "\"Can_Main\": {"
                "\"AliveCounter\": %d, "
                "\"WiFi_AP_Status\": %d, "
                "\"TcpClientCount\": %d, "
                "\"CanBusEnable\": %d, "
                "\"TcpEnable\": %d, "
                "\"VpnEnable\": %d, "
                "\"WiFi_ST_Status\": %d, "
                "\"Reserved_1\": %d, "
                "\"WiFi_AP_IP_Adrress\": %d, "
                "\"WiFi_ST_IP_Address\": %d, "
                "\"SwVersionMajor\": %d, "
                "\"SwVersionMinor\": %d, "
                "\"SwVersionBugfix\": %d"
            "}"
        "}", 
        dbc->Battery_Messages.Signal.BatteryChemistry,
        dbc->Battery_Messages.Signal.Battery_Count,
        dbc->Battery_Messages.Signal.BatteryBalance_MaxVoltage,
        dbc->Battery_Messages.Signal.BatteryBalance_MinVoltage,
        dbc->Battery_Messages.Signal.BatteryBalance_MaxTemp,
        dbc->Battery_Messages.Signal.BatteryBalance_MinTemp,
        dbc->Battery_Messages.Signal.BatterySOC,
        dbc->Battery_Messages.Signal.OCV_Voltages,

        dbc->Battery_Temperatures.Signal.Battery_Temp_AUX0,
        dbc->Battery_Temperatures.Signal.Battery_Temp_AUX1,
        dbc->Battery_Temperatures.Signal.Battery_Temp_AUX2,
        dbc->Battery_Temperatures.Signal.Battery_Temp_AUX3,
        dbc->Battery_Temperatures.Signal.Battery_Temp_AUX4,
        dbc->Battery_Temperatures.Signal.Battery_Temp_AUX5,
        dbc->Battery_Temperatures.Signal.Battery_Temp_AUX6,
        dbc->Battery_Temperatures.Signal.Battery_Temp_AUX7,

        dbc->Battery_Voltages_1.Signal.BatteryVoltage_1,
        dbc->Battery_Voltages_1.Signal.BatteryVoltage_2,
        dbc->Battery_Voltages_1.Signal.BatteryVoltage_3,
        dbc->Battery_Voltages_1.Signal.BatteryVoltage_4,
        dbc->Battery_Voltages_1.Signal.BatteryVoltage_5,
        dbc->Battery_Voltages_1.Signal.BatteryVoltage_6,
        dbc->Battery_Voltages_1.Signal.BatteryVoltage_7,
        dbc->Battery_Voltages_1.Signal.BatteryVoltage_8,

        dbc->Battery_Voltages_2.Signal.BatteryVoltage_9,
        dbc->Battery_Voltages_2.Signal.BatteryVoltage_10,
        dbc->Battery_Voltages_2.Signal.BatteryVoltage_11,
        dbc->Battery_Voltages_2.Signal.BatteryVoltage_12,
        dbc->Battery_Voltages_2.Signal.BatteryVoltage_13,
        dbc->Battery_Voltages_2.Signal.BatteryVoltage_14,
        dbc->Battery_Voltages_2.Signal.BatteryVoltage_15,
        dbc->Battery_Voltages_2.Signal.BatteryVoltage_16,

        dbc->Can_Main.Signal.AliveCounter,
        dbc->Can_Main.Signal.WiFi_AP_Status,
        dbc->Can_Main.Signal.TcpClientCount,
        dbc->Can_Main.Signal.CanBusEnable,
        dbc->Can_Main.Signal.TcpEnable,
        dbc->Can_Main.Signal.VpnEnable,
        dbc->Can_Main.Signal.WiFi_ST_Status,
        dbc->Can_Main.Signal.Reserved_1,
        dbc->Can_Main.Signal.WiFi_AP_IP_Adrress,
        dbc->Can_Main.Signal.WiFi_ST_IP_Address,
        dbc->Can_Main.Signal.SwVersionMajor,
        dbc->Can_Main.Signal.SwVersionMinor,
        dbc->Can_Main.Signal.SwVersionBugfix
    );
}


/**
 * @brief Initializes the TCP server and starts listening for client connections.
 */
void Tcp_Init()
{
    wifi_init_ap_sta(); /**< Initialize Wi-Fi in access point and station mode. */
    maindbc_struct.Can_Main.Signal.WiFi_AP_Status = WiFi_AP_Status_WiFi_Ap_Connected;
    maindbc_struct.Can_Main.Signal.WiFi_ST_Status = WiFi_ST_Status_WiFi_Ap_Connected;
    maindbc_struct.Can_Main.Signal.TcpEnable = TcpEnable_TCP_Online;
    xTaskCreate(Create_Server, "tcp_server", 4096, NULL, (UBaseType_t)5, NULL); /**< Start the TCP server task. */
}


