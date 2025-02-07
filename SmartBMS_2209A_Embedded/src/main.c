/**
 * @file main.c
 * @brief Main application entry point for ESP32, initializing various tasks.
 * @date 18 December 2024
 * @author hakimmc
 */

#include "LedTaskInit.h"
#include "Can.h"
#include "Wifi.h"
#include "TcpServer.h"
#include "d2cc_lib.h"
#include "Bq76pl455.h"

/** @brief Structure to hold CAN message data. */
DbcStruct maindbc_struct;
extern DbcStruct *struct_of_comm;

/**
 * @brief Application entry point.
 * 
 * This function initializes non-volatile storage, sets up the TCP server, and creates tasks
 * for CAN communication, LED toggling, and BQ76PL455 functionality.
 */
void app_main()
{
    printf("\nhelloworld\n"); /**< Print "helloworld" for testing. */
    
    // Initialize CAN messages
    struct_of_comm = &maindbc_struct;

    D2cc_Lib_Init(struct_of_comm);
    CreateTable_Can_Main(struct_of_comm);
    CreateTable_Battery_Messages(struct_of_comm);
    CreateTable_Battery_Voltages_1(struct_of_comm);
    CreateTable_Battery_Voltages_2(struct_of_comm);
    CreateTable_Battery_Temperatures(struct_of_comm);

    // Initialize NVS for persistent storage
    nvs_flash_init();  
    
    // Initialize TCP server
    Tcp_Init();  
    
    // Create CAN communication task
    xTaskCreate(CanReporter, "CanTask", 4096,  NULL, (UBaseType_t)2, NULL);  
    
    // Create LED toggle task
    xTaskCreate(led_init, "ToggleTask", 4096,  NULL, (UBaseType_t)3, NULL);  
    
    // Create BQ76PL455 task to manage battery data
    xTaskCreate(BQ_Start, "BqTask", 4096,  NULL, (UBaseType_t)4, NULL);  
}
