/**
 * @file Wifi.c
 * @brief Functions for initializing and managing Wi-Fi connectivity in AP (Access Point) and STA (Station) modes.
 * @date 18 December 2024
 * @author hakimmc
 */

#include "Wifi.h"

/**
 * @brief Event handler for Wi-Fi and IP events.
 * 
 * This function handles Wi-Fi and IP events, such as Wi-Fi connection status changes and obtaining an IP address.
 * It also manages retry logic for Wi-Fi connection attempts.
 * 
 * @param arg Pointer to additional arguments (unused).
 * @param event_base The event base (WIFI_EVENT or IP_EVENT).
 * @param event_id The event ID (such as WIFI_EVENT_STA_START).
 * @param event_data Event data associated with the event.
 */
void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    int retry_count = 0;

    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect(); /**< Start the Wi-Fi connection process. */
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (retry_count < MAX_RETRY) {
            esp_wifi_connect(); /**< Retry the connection. */
            retry_count++;
            ESP_LOGI("WIFI_DUAL_MODE", "Retrying to connect to the Wi-Fi network...");
        } else {
            ESP_LOGI("WIFI_DUAL_MODE", "Failed to connect to the Wi-Fi network.");
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
        ESP_LOGI("WIFI_DUAL_MODE", "Got IP: " IPSTR, IP2STR(&event->ip_info.ip)); /**< Log obtained IP address. */
        retry_count = 0; /**< Reset retry count. */
    }
}

/**
 * @brief Initializes Wi-Fi in both Access Point (AP) and Station (STA) modes.
 * 
 * This function initializes the Wi-Fi stack, configures the Wi-Fi interfaces, and starts the Wi-Fi service.
 * It also registers event handlers for Wi-Fi and IP events, and connects to a Wi-Fi network in STA mode, if configured.
 * 
 * @note This function configures the ESP32 in dual mode (AP and STA) and connects to a Wi-Fi network if `WIFI_CONNECT` is defined.
 */
void wifi_init_ap_sta(void) 
{
    ESP_ERROR_CHECK(esp_netif_init()); /**< Initialize network interface. */
    ESP_ERROR_CHECK(esp_event_loop_create_default()); /**< Create the default event loop. */

    #ifdef WIFI_CONNECT
        esp_netif_create_default_wifi_sta(); /**< Create the default Wi-Fi STA (Station) interface. */
    #endif

    esp_netif_create_default_wifi_ap(); /**< Create the default Wi-Fi AP (Access Point) interface. */

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); /**< Default Wi-Fi configuration. */
    ESP_ERROR_CHECK(esp_wifi_init(&cfg)); /**< Initialize Wi-Fi driver with the default configuration. */

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id)); /**< Register Wi-Fi event handler. */
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip)); /**< Register IP event handler. */
    
    #ifdef WIFI_CONNECT
        wifi_config_t wifi_config = {
            .sta = {
                .ssid = WIFI_SSID, /**< Wi-Fi SSID. */
                .password = WIFI_PASS, /**< Wi-Fi password. */
                .threshold.authmode = WIFI_AUTH_WPA2_PSK, /**< WPA2 PSK authentication. */
            },
        };
    #endif

    wifi_config_t wifi_ap_config = {
        .ap = {
            .ssid = AP_SSID, /**< AP SSID. */
            .password = AP_PASS, /**< AP password. */
            .ssid_len = strlen(AP_SSID), /**< Length of SSID. */
            .channel = ESP32_AP_CHANNEL, /**< AP channel. */
            .max_connection = ESP32_MAX_CONN, /**< Max connections to the AP. */
            .authmode = WIFI_AUTH_WPA_WPA2_PSK /**< WPA/WPA2 PSK authentication. */
        },
    };

    #ifdef WIFI_CONNECT
        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA)); /**< Set Wi-Fi mode to dual (AP and STA). */
        ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config)); /**< Set STA configuration. */
    #else
        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP)); /**< Set Wi-Fi mode to AP only. */
    #endif

    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_ap_config)); /**< Set AP configuration. */

    ESP_ERROR_CHECK(esp_wifi_start()); /**< Start the Wi-Fi driver. */

    ESP_LOGI("WIFI_DUAL_MODE", "Wi-Fi initialization completed."); /**< Log completion of Wi-Fi initialization. */
}
