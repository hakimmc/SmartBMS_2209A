/*
 * Wifi.h
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */

#ifndef WIFI_AP_STA_H
#define WIFI_AP_STA_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "freertos/task.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "string.h"
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include <sys/time.h>
#include <esp_system.h>
#include <lwip/netdb.h>
#include <ping/ping_sock.h>

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

/* if you need to use wifi connect just uncomment or comment WIFI_CONNECT definition */

#define WIFI_CONNECT

#define AP_SSID         "OttomotiveBMS"
#define AP_PASS         "Ottomotive22*"
#define MAX_STA_CONN   5
#define MAX_RETRY      5

#ifdef WIFI_CONNECT
    #define WIFI_SSID   "adm"
    #define WIFI_PASS   "12345678"
    #define WIFI_TIMEOUT_MS 10000
    #define ESP32_AP_CHANNEL        3             
    #define ESP32_MAX_CONN          3
#endif



static void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
void wifi_init_ap_sta(void);

#endif
