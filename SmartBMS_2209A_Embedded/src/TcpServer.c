/*
 * TcpServer.c
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */


#include "TcpServer.h"
#include "Wifi.h"
 

char*  GUI_USER = "root";
char*  GUI_PASS = "otto";

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

        TaskHandle_t xHandle = NULL;
        xTaskCreate(Handle_Client, "Client_Handler", 4096, (void*)sock, (UBaseType_t)1, &xHandle);
    }

    close(listen_sock);
}

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
            case 0: {
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
                        if(state<3){
                            send(sock, "EHLO", 4, 0);
                            state = 1;
                            timeout_counter = 0;
                        }
                    }
                    else state = 3;
                }
                break;
            }

            case 1: {
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
            }

            case 2: {
                len = receive_data(sock, rx_buffer, sizeof(rx_buffer) - 1, &timeout_counter, max_timeout);
                if (len != -2 || len != -1) {
                    rx_buffer[len] = '\0';
                    if (!memcmp(rx_buffer, "data", 4)) {
                        send(sock, "OK", 2, 0);
                    }
                    else if (!memcmp(rx_buffer, "exit", 4)) {
                        state = 3;
                    }
                    memset(rx_buffer, 0, sizeof(rx_buffer));
                }
                break;
            }

            case 3: {
                send(sock, "ER", 2, 0);
                close(sock);
                vTaskDelete(NULL);
                break;
            }

            case 4: {
                send(sock, "TO", 2, 0);
                close(sock);
                vTaskDelete(NULL);
                break;
            }
        }
    }

    close(sock);
    vTaskDelete(NULL);
}


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

void Tcp_Init()
{
    wifi_init_ap_sta(); 

    xTaskCreate(Create_Server, "tcp_server", 4096, NULL, (UBaseType_t)5, NULL);
}
