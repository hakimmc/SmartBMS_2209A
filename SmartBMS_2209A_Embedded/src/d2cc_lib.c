/*
 *  d2cc_lib.c
 *
 *  Created on: 5.01.2025 
 *  Author: hakimmc
 *
 *  https://www.linkedin.com/in/abdulhakim-calgin/
 *
 */

#include "d2cc_lib.h"


void D2cc_Lib_Init(DbcStruct *dbc){
	dbc->Battery_Messages.ID	=	0x101;
	dbc->Battery_Messages.DLC	=	8;
	dbc->Battery_Temperatures.ID	=	0x103;
	dbc->Battery_Temperatures.DLC	=	8;
	dbc->Battery_Voltages.ID	=	0x102;
	dbc->Battery_Voltages.DLC	=	8;
	dbc->Can_Main.ID	=	0x100;
	dbc->Can_Main.DLC	=	8;
	dbc->Can_Main.BatteryBalance_MaxVoltage.Phys_Value.factor	=	10;
	dbc->Can_Main.BatteryBalance_MaxVoltage.Phys_Value.offset	=	2000;
	dbc->Can_Main.BatteryBalance_MinVoltage.Phys_Value.factor	=	10;
	dbc->Can_Main.BatteryBalance_MinVoltage.Phys_Value.offset	=	2000;
	dbc->Can_Main.BatteryBalance_MinTemp.Phys_Value.factor	=	1;
	dbc->Can_Main.BatteryBalance_MinTemp.Phys_Value.offset	=	-100;
}


void ReadParse(uint8_t* rx_data, uint32_t id, DbcStruct *dbc){
    switch (id) {

	case 0x101:
		for(int i=0;i<8;i++){
			dbc->Battery_Messages.Data[i] = rx_data[i];
		}
		break;
	case 0x103:
		for(int i=0;i<8;i++){
			dbc->Battery_Temperatures.Data[i] = rx_data[i];
		}
		break;
	case 0x102:
		for(int i=0;i<8;i++){
			dbc->Battery_Voltages.Data[i] = rx_data[i];
		}
		break;
	case 0x100:
		for(int i=0;i<8;i++){
			dbc->Can_Main.Data[i] = rx_data[i];
		}
		dbc->Can_Main.BatteryBalance_MaxVoltage.Phys_Value.value	=	(dbc->Can_Main.Signal.BatteryBalance_MaxVoltage * 10) + 2000;
		dbc->Can_Main.BatteryBalance_MinVoltage.Phys_Value.value	=	(dbc->Can_Main.Signal.BatteryBalance_MinVoltage * 10) + 2000;
		dbc->Can_Main.BatteryBalance_MinTemp.Phys_Value.value	=	(dbc->Can_Main.Signal.BatteryBalance_MinTemp * 1) + -100;
		break;
	}
}

void CreateTable_Battery_Messages(DbcStruct *dbc)
{

}
void CreateTable_Battery_Temperatures(DbcStruct *dbc)
{

}
void CreateTable_Battery_Voltages(DbcStruct *dbc)
{

}
void CreateTable_Can_Main(DbcStruct *dbc)
{
	dbc->Can_Main.Signal.AliveCounter = 0;
	dbc->Can_Main.Signal.BatteryChemistry = BatteryChemistry_LFP;
	dbc->Can_Main.Signal.BatteryBalance_MaxVoltage = (2700-dbc->Can_Main.BatteryBalance_MaxVoltage.Phys_Value.offset)/dbc->Can_Main.BatteryBalance_MaxVoltage.Phys_Value.factor;
	dbc->Can_Main.Signal.BatteryBalance_MinVoltage = (3500-dbc->Can_Main.BatteryBalance_MaxVoltage.Phys_Value.offset)/dbc->Can_Main.BatteryBalance_MaxVoltage.Phys_Value.factor;
	dbc->Can_Main.Signal.BatteryBalance_MaxTemp = 40;
	dbc->Can_Main.Signal.BatteryBalance_MinTemp = 0-dbc->Can_Main.BatteryBalance_MinTemp.Phys_Value.offset;
	dbc->Can_Main.Signal.SwVersionMajor = 1;
	dbc->Can_Main.Signal.SwVersionMinor = 0;
	dbc->Can_Main.Signal.SwVersionBugfix = 2;
	dbc->Can_Main.Signal.CanBusEnable = CanBusEnable_Enable;
	dbc->Can_Main.Signal.WiFiEnable = WiFiEnable_Enable;
	dbc->Can_Main.Signal.TcpEnable = TcpEnable_Offline;
	dbc->Can_Main.Signal.VpnEnable = VpnEnable_Disable;
	dbc->Can_Main.Signal.WiFi_AP_Status = WiFi_AP_Status_Disable;
	dbc->Can_Main.Signal.TcpClientCount = 0;

}
