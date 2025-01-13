/**
 * @file Can.c
 * @brief CAN driver implementation for the ESP32 using the TWAI driver.
 * @date 18 December 2024
 * @author hakimmc
 */

#include "Can.h"
#include "d2cc_lib.h"

extern DbcStruct maindbc_struct;

/**
 * @brief Initializes the CAN (TWAI) driver with the specified configurations.
 * 
 * @param can_gpio_config General configuration for the CAN GPIO pins and mode.
 * @param can_time_config Timing configuration for the CAN bus (e.g., bitrate).
 * @param can_filter_config Filter configuration for message acceptance.
 * @return uint8_t Returns 1 if the driver is successfully initialized.
 */
uint8_t Can_Init(twai_general_config_t can_gpio_config, twai_timing_config_t can_time_config, twai_filter_config_t can_filter_config)
{
    ESP_ERROR_CHECK(twai_driver_install(&can_gpio_config, &can_time_config, &can_filter_config));
    ESP_LOGI(CAN_TAG, "Driver installed");
    ESP_ERROR_CHECK(twai_start());
    ESP_LOGI(CAN_TAG, "Driver started");
    return 1;
}

/**
 * @brief Transmits a CAN message with the specified data.
 * 
 * @param message The CAN message structure to transmit.
 * @param data The data array to be sent with the message.
 * @return uint8_t Returns 1 if the transmission is successful.
 */
uint8_t Can_Transmit(twai_message_t message, uint8_t data[])
{
    for (int i = 0; i < message.data_length_code; i++) {
        message.data[i] = data[i];
    }
    twai_transmit(&message, portMAX_DELAY); 
    return 1;
}

// Predefined CAN message structures
twai_message_t Can_Main = {.extd = 0, .rtr = 0, .ss = 0, .self = 0, .dlc_non_comp = 0, .identifier = Can_Main_ID, .data_length_code = 8, .data = {0},};
twai_message_t Battery_Messages = {.extd = 0, .rtr = 0, .ss = 0, .self = 0, .dlc_non_comp = 0, .identifier = Battery_Messages_ID, .data_length_code = 8, .data = {0},};
twai_message_t Battery_Voltages = {.extd = 0, .rtr = 0, .ss = 0, .self = 0, .dlc_non_comp = 0, .identifier = Can_Battery_Voltages_ID, .data_length_code = 8, .data = {0},};
twai_message_t Battery_Temperatures = {.extd = 0, .rtr = 0, .ss = 0, .self = 0, .dlc_non_comp = 0, .identifier = Can_Battery_Temperatures_ID, .data_length_code = 8, .data = {0},};

// Predefined data arrays for CAN messages
uint8_t Data_Of_Can_Main[8] = {0, 1, 2, 3, 4, 5, 6, 7};
uint8_t Data_Of_Battery_Messages[8] = {8, 9, 10, 11, 12, 13, 14, 15};
uint8_t Data_Of_Battery_Voltages[8] = {16, 17, 22, 32, 42, 52, 62, 72};
uint8_t Data_Of_Battery_Temperatures[8] = {35, 13, 23, 33, 43, 53, 63, 73};

/**
 * @brief Task function to periodically report CAN messages.
 * 
 * This function initializes the CAN driver and repeatedly transmits
 * preconfigured CAN messages, using data from the `DbcStruct`.
 * 
 * @param pvParameter A pointer to any parameters passed to the task (unused).
 */
void CanReporter(void* pvParameter)
{
    twai_timing_config_t tconf = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t fconf = TWAI_FILTER_CONFIG_ACCEPT_ALL();
    twai_general_config_t gconf = TWAI_GENERAL_CONFIG_DEFAULT(5, 4, TWAI_MODE_NORMAL);

    DbcStruct *struct_of_comm = &maindbc_struct;

    Can_Init(gconf, tconf, fconf);
    while (1) {
        Can_Transmit(Can_Main, struct_of_comm->Can_Main.Data);
        Can_Transmit(Battery_Messages, struct_of_comm->Battery_Messages.Data);
        Can_Transmit(Battery_Voltages, struct_of_comm->Battery_Voltages.Data);
        Can_Transmit(Battery_Temperatures, struct_of_comm->Battery_Temperatures.Data);
        
        printf("Data : {");
        for (int i = 0; i < 8; i++) {
            printf("[%d]", struct_of_comm->Battery_Messages.Data[i]);
        }
        printf("}");
        vTaskDelay(pdMS_TO_TICKS(CAN_DELAY));
    }
}
