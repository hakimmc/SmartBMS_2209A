/*
 * TcpServer.c
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */


#include "TcpServer.h"
#include "Wifi.h"
 

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
        xTaskCreate(Handle_Client, "Client_Handler", 2048, (void*)sock, 5, &xHandle);
    }

    close(listen_sock);
}

void Handle_Client(void* args)
{
    int sock = (int)args;
    char rx_buffer[32];
    uint8_t AUTH = 0;
    while (1) {
        int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
        if (len < 0) {
            ESP_LOGE(TCP_TAG, "recv failed: errno %d", errno);
            break;
        } else if (len == 0) {
            ESP_LOGI(TCP_TAG, "Connection closed");
            break;
        } else {
            rx_buffer[len] = 0;
            ESP_LOGI(TCP_TAG, "Received %d bytes: %s", len, rx_buffer);
            //char dest[4] = {'H','E','L','O'};
            if(!AUTH){
                if(!memcmp(rx_buffer, "HELO", 4))
                {
                    int t_out=0;
                    int max_t_out=10;
                    while(memcmp(rx_buffer, "OBT", 3) && t_out<max_t_out)
                    {
                        send(sock, "ID?", 3, 0);
                        recv(sock, rx_buffer, 4,0);
                        t_out++;
                    }
                    if(t_out==max_t_out){
                        send(sock, "FALSE", 5, 0);
                    }
                    else{
                        send(sock, "EHLO", 4, 0);
                        AUTH=1;
                    }
                }
                else{
                    int err = send(sock, rx_buffer, len, 0);
                    if (err < 0) {
                        ESP_LOGE(TCP_TAG, "Error occurred during sending: errno %d", errno);
                        break;
                    }
                    close(sock);
                }
            }
            else{
                if(!memcmp(rx_buffer, "sa ", 2)){
                    send(sock, "as", 2, 0);
                }
                else if(!memcmp(rx_buffer, "login_", 6)){
                    
                }  
            }   
        }
    }

    close(sock);
    vTaskDelete(NULL);
}

void Tcp_Init()
{
    wifi_init_ap_sta(); 

    xTaskCreate(Create_Server, "tcp_server", 4096, NULL, 5, NULL);
}
