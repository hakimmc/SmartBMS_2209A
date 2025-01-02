/*
 * can.c
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */

#include "Can.h"

uint8_t Can_Init(twai_general_config_t can_gpio_config,twai_timing_config_t can_time_config, twai_filter_config_t can_filter_config)
{
    ESP_ERROR_CHECK(twai_driver_install(&can_gpio_config, &can_time_config, &can_filter_config));
    ESP_LOGI(CAN_TAG, "Driver installed");
    ESP_ERROR_CHECK(twai_start());
    ESP_LOGI(CAN_TAG, "Driver started");
    return 1;
}

uint8_t Can_Transmit(twai_message_t message, uint8_t data[])
{
    for(int i = 0; i< message.data_length_code; i++ ){
        message.data[i] = data[i];
    }
    twai_transmit(&message, portMAX_DELAY); 
    return 1;
}

twai_message_t Can_Main = {.extd = 0,.rtr = 0,.ss = 0,.self = 0,.dlc_non_comp = 0,.identifier = Can_Main_ID,.data_length_code = 8,.data = {0},};
twai_message_t Battery_Messages = {.extd = 0,.rtr = 0,.ss = 0,.self = 0,.dlc_non_comp = 0,.identifier = Battery_Messages_ID,.data_length_code = 8,.data = {0},};
twai_message_t Battery_Voltages = {.extd = 0,.rtr = 0,.ss = 0,.self = 0,.dlc_non_comp = 0,.identifier = Can_Battery_Voltages_ID,.data_length_code = 8,.data = {0},};
twai_message_t Battery_Temperatures = {.extd = 0,.rtr = 0,.ss = 0,.self = 0,.dlc_non_comp = 0,.identifier = Can_Battery_Temperatures_ID,.data_length_code = 8,.data = {0},};

uint8_t Data_Of_Can_Main[8] = {0, 1, 2, 3, 4, 5, 6, 7};
uint8_t Data_Of_Battery_Messages[8] = {8, 9, 10, 11, 12, 13, 14, 15};
uint8_t Data_Of_Battery_Voltages[8] = {16, 17, 22, 32, 42, 52, 62, 72};
uint8_t Data_Of_Battery_Temperatures[8] = {35, 13, 23, 33, 43, 53, 63, 73};

void CanReporter(void* pvParameter){
    twai_timing_config_t tconf = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t fconf = TWAI_FILTER_CONFIG_ACCEPT_ALL();
    twai_general_config_t gconf = TWAI_GENERAL_CONFIG_DEFAULT(5, 4, TWAI_MODE_NORMAL);

    Can_Init(gconf,tconf,fconf);
    while(1){
        Can_Transmit(Can_Main, Data_Of_Can_Main);
        Can_Transmit(Battery_Messages, Data_Of_Battery_Messages);
        Can_Transmit(Battery_Voltages, Data_Of_Battery_Voltages);
        Can_Transmit(Battery_Temperatures, Data_Of_Battery_Temperatures);
        vTaskDelay(pdMS_TO_TICKS(CAN_DELAY));
    }
}