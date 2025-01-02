/*
 * Wifi.c
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */

#include "Wifi.h"

static void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
	int retry_count = 0;
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (retry_count < MAX_RETRY) {
            esp_wifi_connect();
            retry_count++;
            ESP_LOGI("WIFI_DUAL_MODE", "Retrying to connect to the Wi-Fi network...");
        } else {
            ESP_LOGI("WIFI_DUAL_MODE", "Failed to connect to the Wi-Fi network.");
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
        ESP_LOGI("WIFI_DUAL_MODE", "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
        retry_count = 0;
    }
}

void wifi_init_ap_sta(void) 
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
	#ifdef WIFI_CONNECT
    	esp_netif_create_default_wifi_sta();
	#endif

    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));
	#ifdef WIFI_CONNECT
		wifi_config_t wifi_config = {
			.sta = {
				.ssid = WIFI_SSID,
				.password = WIFI_PASS,
				.threshold.authmode = WIFI_AUTH_WPA2_PSK,
			},
		};
	#endif
    wifi_config_t wifi_ap_config = 
	{
		.ap = 
		{
            .ssid = AP_SSID,                
			.password = AP_PASS,             
            .ssid_len = strlen(AP_SSID),
			.channel = ESP32_AP_CHANNEL,           
            .max_connection = ESP32_MAX_CONN,              
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

	#ifdef WIFI_CONNECT
    	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    	ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
	#else
		ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
	#endif
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_ap_config));

    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI("WIFI_DUAL_MODE", "Wi-Fi initialization completed.");
}