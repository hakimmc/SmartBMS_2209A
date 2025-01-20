/**
 * @file d2cc_lib.c
 * @brief Source file for the D2CC library.
 * 
 * @date 2025-01-19
 * @author hakimmc
 * @see https://www.linkedin.com/in/abdulhakim-calgin/
 */

#include "d2cc_lib.h"


/**
 * @brief Initializes the DbcStruct with values from the parsed DBC file.
 *
 * This function initializes the necessary fields in the DbcStruct based on the provided DBC messages.
 * The signals' physical factors and offsets are set accordingly.
 *
 * @param[in] dbc Pointer to the DbcStruct instance to be initialized.
 */

void D2cc_Lib_Init(DbcStruct *dbc){

	dbc->Battery_Messages.Battery_Count.Phys_Value.factor	=	1;
	dbc->Battery_Messages.Battery_Count.Phys_Value.offset	=	1;
	dbc->Battery_Messages.BatteryBalance_MaxVoltage.Phys_Value.factor	=	10;
	dbc->Battery_Messages.BatteryBalance_MaxVoltage.Phys_Value.offset	=	2000;
	dbc->Battery_Messages.BatteryBalance_MinVoltage.Phys_Value.factor	=	10;
	dbc->Battery_Messages.BatteryBalance_MinVoltage.Phys_Value.offset	=	2000;
	dbc->Battery_Messages.BatteryBalance_MinTemp.Phys_Value.factor	=	1;
	dbc->Battery_Messages.BatteryBalance_MinTemp.Phys_Value.offset	=	-100;


	dbc->Battery_Voltages_1.BatteryVoltage_1.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_1.BatteryVoltage_1.Phys_Value.offset	=	2000;
	dbc->Battery_Voltages_1.BatteryVoltage_2.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_1.BatteryVoltage_2.Phys_Value.offset	=	2000;
	dbc->Battery_Voltages_1.BatteryVoltage_3.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_1.BatteryVoltage_3.Phys_Value.offset	=	2000;
	dbc->Battery_Voltages_1.BatteryVoltage_4.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_1.BatteryVoltage_4.Phys_Value.offset	=	2000;
	dbc->Battery_Voltages_1.BatteryVoltage_5.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_1.BatteryVoltage_5.Phys_Value.offset	=	2000;
	dbc->Battery_Voltages_1.BatteryVoltage_6.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_1.BatteryVoltage_6.Phys_Value.offset	=	2000;
	dbc->Battery_Voltages_1.BatteryVoltage_7.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_1.BatteryVoltage_7.Phys_Value.offset	=	2000;
	dbc->Battery_Voltages_1.BatteryVoltage_8.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_1.BatteryVoltage_8.Phys_Value.offset	=	2000;

	dbc->Battery_Voltages_2.BatteryVoltage_9.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_2.BatteryVoltage_9.Phys_Value.offset	=	2000;
	dbc->Battery_Voltages_2.BatteryVoltage_10.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_2.BatteryVoltage_10.Phys_Value.offset	=	2000;
	dbc->Battery_Voltages_2.BatteryVoltage_11.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_2.BatteryVoltage_11.Phys_Value.offset	=	2000;
	dbc->Battery_Voltages_2.BatteryVoltage_12.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_2.BatteryVoltage_12.Phys_Value.offset	=	2000;
	dbc->Battery_Voltages_2.BatteryVoltage_13.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_2.BatteryVoltage_13.Phys_Value.offset	=	2000;
	dbc->Battery_Voltages_2.BatteryVoltage_14.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_2.BatteryVoltage_14.Phys_Value.offset	=	2000;
	dbc->Battery_Voltages_2.BatteryVoltage_15.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_2.BatteryVoltage_15.Phys_Value.offset	=	2000;
	dbc->Battery_Voltages_2.BatteryVoltage_16.Phys_Value.factor	=	10;
	dbc->Battery_Voltages_2.BatteryVoltage_16.Phys_Value.offset	=	2000;

}


/**
 * @brief Reads and parses CAN data into the DbcStruct.
 *
 * This function is used to read CAN data and store it in the DbcStruct. It parses the data and converts
 * physical values to raw CAN signal values based on the scaling factors and offsets defined in the DbcStruct.
 *
 * @param[in] rx_data Pointer to the received CAN data to be parsed.
 * @param[in] id CAN message ID for identifying which message to parse.
 * @param[in,out] dbc Pointer to the DbcStruct where parsed data will be stored.
 */

#ifdef READ_ENABLE
void ReadParse(uint8_t* rx_data, uint32_t id, DbcStruct *dbc){
    switch (id) {

	case 0x101:
		for(int i=0;i<8;i++){
			dbc->Battery_Messages.Data[i] = rx_data[i];
		}
		dbc->Battery_Messages.Battery_Count.Phys_Value.value	=	(dbc->Battery_Messages.Signal.Battery_Count * 1) + 1;
		dbc->Battery_Messages.BatteryBalance_MaxVoltage.Phys_Value.value	=	(dbc->Battery_Messages.Signal.BatteryBalance_MaxVoltage * 10) + 2000;
		dbc->Battery_Messages.BatteryBalance_MinVoltage.Phys_Value.value	=	(dbc->Battery_Messages.Signal.BatteryBalance_MinVoltage * 10) + 2000;
		dbc->Battery_Messages.BatteryBalance_MinTemp.Phys_Value.value	=	(dbc->Battery_Messages.Signal.BatteryBalance_MinTemp * 1) + -100;
		break;
	case 0x104:
		for(int i=0;i<8;i++){
			dbc->Battery_Temperatures.Data[i] = rx_data[i];
		}
		break;
	case 0x102:
		for(int i=0;i<8;i++){
			dbc->Battery_Voltages_1.Data[i] = rx_data[i];
		}
		dbc->Battery_Voltages_1.BatteryVoltage_1.Phys_Value.value	=	(dbc->Battery_Voltages_1.Signal.BatteryVoltage_1 * 10) + 2000;
		dbc->Battery_Voltages_1.BatteryVoltage_2.Phys_Value.value	=	(dbc->Battery_Voltages_1.Signal.BatteryVoltage_2 * 10) + 2000;
		dbc->Battery_Voltages_1.BatteryVoltage_3.Phys_Value.value	=	(dbc->Battery_Voltages_1.Signal.BatteryVoltage_3 * 10) + 2000;
		dbc->Battery_Voltages_1.BatteryVoltage_4.Phys_Value.value	=	(dbc->Battery_Voltages_1.Signal.BatteryVoltage_4 * 10) + 2000;
		dbc->Battery_Voltages_1.BatteryVoltage_5.Phys_Value.value	=	(dbc->Battery_Voltages_1.Signal.BatteryVoltage_5 * 10) + 2000;
		dbc->Battery_Voltages_1.BatteryVoltage_6.Phys_Value.value	=	(dbc->Battery_Voltages_1.Signal.BatteryVoltage_6 * 10) + 2000;
		dbc->Battery_Voltages_1.BatteryVoltage_7.Phys_Value.value	=	(dbc->Battery_Voltages_1.Signal.BatteryVoltage_7 * 10) + 2000;
		dbc->Battery_Voltages_1.BatteryVoltage_8.Phys_Value.value	=	(dbc->Battery_Voltages_1.Signal.BatteryVoltage_8 * 10) + 2000;
		break;
	case 0x103:
		for(int i=0;i<8;i++){
			dbc->Battery_Voltages_2.Data[i] = rx_data[i];
		}
		dbc->Battery_Voltages_2.BatteryVoltage_9.Phys_Value.value	=	(dbc->Battery_Voltages_2.Signal.BatteryVoltage_9 * 10) + 2000;
		dbc->Battery_Voltages_2.BatteryVoltage_10.Phys_Value.value	=	(dbc->Battery_Voltages_2.Signal.BatteryVoltage_10 * 10) + 2000;
		dbc->Battery_Voltages_2.BatteryVoltage_11.Phys_Value.value	=	(dbc->Battery_Voltages_2.Signal.BatteryVoltage_11 * 10) + 2000;
		dbc->Battery_Voltages_2.BatteryVoltage_12.Phys_Value.value	=	(dbc->Battery_Voltages_2.Signal.BatteryVoltage_12 * 10) + 2000;
		dbc->Battery_Voltages_2.BatteryVoltage_13.Phys_Value.value	=	(dbc->Battery_Voltages_2.Signal.BatteryVoltage_13 * 10) + 2000;
		dbc->Battery_Voltages_2.BatteryVoltage_14.Phys_Value.value	=	(dbc->Battery_Voltages_2.Signal.BatteryVoltage_14 * 10) + 2000;
		dbc->Battery_Voltages_2.BatteryVoltage_15.Phys_Value.value	=	(dbc->Battery_Voltages_2.Signal.BatteryVoltage_15 * 10) + 2000;
		dbc->Battery_Voltages_2.BatteryVoltage_16.Phys_Value.value	=	(dbc->Battery_Voltages_2.Signal.BatteryVoltage_16 * 10) + 2000;
		break;
	case 0x100:
		for(int i=0;i<8;i++){
			dbc->Can_Main.Data[i] = rx_data[i];
		}
		break;
	}
}
#endif
/**
 * @brief Creates the signal table for a specified CAN message in the DbcStruct.
 *
 * This function initializes the signal table for a specific message within the DbcStruct. Each signal is 
 * set to 0 initially, preparing it for further use.
 *
 * @param[in] dbc Pointer to the DbcStruct containing the CAN message and signals.
 */

void CreateTable_Battery_Messages(DbcStruct *dbc)
{
	dbc->Battery_Messages.Signal.BatteryChemistry = BatteryChemistry_LFP;
	dbc->Battery_Messages.Signal.Battery_Count = PHYS_TO_RAW(16,&dbc->Battery_Messages.Battery_Count.Phys_Value);
	dbc->Battery_Messages.Signal.BatteryBalance_MaxVoltage = PHYS_TO_RAW(3200,&dbc->Battery_Messages.BatteryBalance_MaxVoltage.Phys_Value);
	dbc->Battery_Messages.Signal.BatteryBalance_MinVoltage = PHYS_TO_RAW(2800,&dbc->Battery_Messages.BatteryBalance_MinVoltage.Phys_Value);
	dbc->Battery_Messages.Signal.BatteryBalance_MaxTemp = 100;
	dbc->Battery_Messages.Signal.BatteryBalance_MinTemp = PHYS_TO_RAW(0,&dbc->Battery_Messages.BatteryBalance_MinTemp.Phys_Value);
	dbc->Battery_Messages.Signal.BatterySOC = 50;
	dbc->Battery_Messages.Signal.OCV_Voltages = 0;

}
void CreateTable_Battery_Temperatures(DbcStruct *dbc)
{
	dbc->Battery_Temperatures.Signal.Battery_Temp_AUX0 = 25;
	dbc->Battery_Temperatures.Signal.Battery_Temp_AUX1 = 26;
	dbc->Battery_Temperatures.Signal.Battery_Temp_AUX2 = 25;
	dbc->Battery_Temperatures.Signal.Battery_Temp_AUX3 = 25;
	dbc->Battery_Temperatures.Signal.Battery_Temp_AUX4 = 24;
	dbc->Battery_Temperatures.Signal.Battery_Temp_AUX5 = 25;
	dbc->Battery_Temperatures.Signal.Battery_Temp_AUX6 = 24;
	dbc->Battery_Temperatures.Signal.Battery_Temp_AUX7 = 23;

}
void CreateTable_Battery_Voltages_1(DbcStruct *dbc)
{
	dbc->Battery_Voltages_1.Signal.BatteryVoltage_1 = PHYS_TO_RAW(3200,&dbc->Battery_Voltages_1.BatteryVoltage_1.Phys_Value);
	dbc->Battery_Voltages_1.Signal.BatteryVoltage_2 = PHYS_TO_RAW(3250,&dbc->Battery_Voltages_1.BatteryVoltage_2.Phys_Value);
	dbc->Battery_Voltages_1.Signal.BatteryVoltage_3 = PHYS_TO_RAW(3250,&dbc->Battery_Voltages_1.BatteryVoltage_3.Phys_Value);
	dbc->Battery_Voltages_1.Signal.BatteryVoltage_4 = PHYS_TO_RAW(3230,&dbc->Battery_Voltages_1.BatteryVoltage_4.Phys_Value);
	dbc->Battery_Voltages_1.Signal.BatteryVoltage_5 = PHYS_TO_RAW(3210,&dbc->Battery_Voltages_1.BatteryVoltage_5.Phys_Value);
	dbc->Battery_Voltages_1.Signal.BatteryVoltage_6 = PHYS_TO_RAW(3220,&dbc->Battery_Voltages_1.BatteryVoltage_6.Phys_Value);
	dbc->Battery_Voltages_1.Signal.BatteryVoltage_7 = PHYS_TO_RAW(3220,&dbc->Battery_Voltages_1.BatteryVoltage_7.Phys_Value);
	dbc->Battery_Voltages_1.Signal.BatteryVoltage_8 = PHYS_TO_RAW(3230,&dbc->Battery_Voltages_1.BatteryVoltage_8.Phys_Value);

}
void CreateTable_Battery_Voltages_2(DbcStruct *dbc)
{
	dbc->Battery_Voltages_2.Signal.BatteryVoltage_9 = PHYS_TO_RAW(3200,&dbc->Battery_Voltages_2.BatteryVoltage_9.Phys_Value);
	dbc->Battery_Voltages_2.Signal.BatteryVoltage_10 = PHYS_TO_RAW(3250,&dbc->Battery_Voltages_2.BatteryVoltage_10.Phys_Value);
	dbc->Battery_Voltages_2.Signal.BatteryVoltage_11 = PHYS_TO_RAW(3250,&dbc->Battery_Voltages_2.BatteryVoltage_11.Phys_Value);
	dbc->Battery_Voltages_2.Signal.BatteryVoltage_12 = PHYS_TO_RAW(3250,&dbc->Battery_Voltages_2.BatteryVoltage_12.Phys_Value);
	dbc->Battery_Voltages_2.Signal.BatteryVoltage_13 = PHYS_TO_RAW(3250,&dbc->Battery_Voltages_2.BatteryVoltage_13.Phys_Value);
	dbc->Battery_Voltages_2.Signal.BatteryVoltage_14 = PHYS_TO_RAW(3250,&dbc->Battery_Voltages_2.BatteryVoltage_14.Phys_Value);
	dbc->Battery_Voltages_2.Signal.BatteryVoltage_15 = PHYS_TO_RAW(3250,&dbc->Battery_Voltages_2.BatteryVoltage_15.Phys_Value);
	dbc->Battery_Voltages_2.Signal.BatteryVoltage_16 = PHYS_TO_RAW(3230,&dbc->Battery_Voltages_2.BatteryVoltage_16.Phys_Value);

}
void CreateTable_Can_Main(DbcStruct *dbc)
{
	dbc->Can_Main.Signal.AliveCounter = 0;
	dbc->Can_Main.Signal.WiFi_AP_Status = WiFi_AP_Status_WiFi_Ap_Disconnected;
	dbc->Can_Main.Signal.TcpClientCount = 0;
	dbc->Can_Main.Signal.CanBusEnable = CanBusEnable_CAN_Driver_Disabled;
	dbc->Can_Main.Signal.TcpEnable = TcpEnable_TCP_Offline;
	dbc->Can_Main.Signal.VpnEnable = VpnEnable_VPN_Offline;
	dbc->Can_Main.Signal.WiFi_ST_Status = WiFi_ST_Status_WiFi_Ap_Disconnected;
	dbc->Can_Main.Signal.Reserved_1 = 0; // free
	dbc->Can_Main.Signal.WiFi_AP_IP_Adrress = (4<<8) + 1; // 192.168.x.x
	dbc->Can_Main.Signal.WiFi_ST_IP_Address = 0;
	dbc->Can_Main.Signal.SwVersionMajor = 1;
	dbc->Can_Main.Signal.SwVersionMinor = 1;
	dbc->Can_Main.Signal.SwVersionBugfix = 2;

}
/**
 * @brief Converts a physical value to a raw CAN signal value.
 *
 * This function converts a physical value (e.g., temperature) into a raw CAN signal value based on the 
 * scaling factor and offset stored in the Phys_Value_t structure.
 *
 * @param[in] phys_value The physical value to convert.
 * @param[in] phys_struct Pointer to the Phys_Value_t structure containing scaling factor and offset.
 *
 * @return The corresponding raw CAN signal value.
 */

uint32_t PHYS_TO_RAW(int phys_value, Phys_Value_t *phys_struct) 
{
    return ((phys_value - phys_struct->offset) / phys_struct->factor);
}

/**
 * @brief Converts a raw CAN signal value to a physical value.
 *
 * This function converts a raw CAN signal value to its corresponding physical value based on the 
 * scaling factor and offset stored in the Phys_Value_t structure.
 *
 * @param[in] raw_value The raw CAN signal value to convert.
 * @param[in] phys_struct Pointer to the Phys_Value_t structure containing scaling factor and offset.
 *
 * @return The corresponding physical value.
 */

uint32_t RAW_TO_PHYS(int raw_value, Phys_Value_t *phys_struct) 
{
    return ((raw_value * phys_struct->factor) + phys_struct->offset);
}
