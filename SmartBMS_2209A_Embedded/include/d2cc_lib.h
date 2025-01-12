/*
 *  d2cc_lib.h
 *
 *  Created on: 5.01.2025 
 *  Author: hakimmc
 *
 *  https://www.linkedin.com/in/abdulhakim-calgin/
 *
 */

#ifndef LIB_
#define LIB_

#include <stdint.h>
#include <stdbool.h>


typedef enum{
	BatteryChemistry_LFP,	BatteryChemistry_NMC
}BatteryChemistry_enum;


typedef enum{
	CanBusEnable_Enable,	CanBusEnable_Disable
}CanBusEnable_enum;


typedef enum{
	WiFiEnable_Enable,	WiFiEnable_Disable
}WiFiEnable_enum;


typedef enum{
	TcpEnable_Offline,	TcpEnable_Online,	TcpEnable_Connected
}TcpEnable_enum;


typedef enum{
	VpnEnable_Enable,	VpnEnable_Disable
}VpnEnable_enum;


typedef enum{
	WiFi_AP_Status_Enable,	WiFi_AP_Status_Disable
}WiFi_AP_Status_enum;

typedef struct{
/* Battery_Messages Line Start */
	struct{
		uint32_t ID;
		uint8_t DLC;
		union{
			struct{
			}Signal;
			uint8_t Data[8];
		};
	}Battery_Messages;

/* Battery_Messages Line End */

/* Battery_Temperatures Line Start */
	struct{
		uint32_t ID;
		uint8_t DLC;
		union{
			struct{
			}Signal;
			uint8_t Data[8];
		};
	}Battery_Temperatures;

/* Battery_Temperatures Line End */

/* Battery_Voltages Line Start */
	struct{
		uint32_t ID;
		uint8_t DLC;
		union{
			struct{
			}Signal;
			uint8_t Data[8];
		};
	}Battery_Voltages;

/* Battery_Voltages Line End */

/* Can_Main Line Start */
	struct{
		uint32_t ID;
		uint8_t DLC;
		union{
			struct{
				uint8_t AliveCounter:7; //7 bit
				BatteryChemistry_enum BatteryChemistry:1; //1 bit
				uint8_t BatteryBalance_MaxVoltage:8; //8 bit
				uint8_t BatteryBalance_MinVoltage:8; //8 bit
				uint8_t BatteryBalance_MaxTemp:8; //8 bit
				uint8_t BatteryBalance_MinTemp:8; //8 bit
				uint8_t SwVersionMajor:2; //2 bit
				uint8_t SwVersionMinor:2; //2 bit
				uint8_t SwVersionBugfix:4; //4 bit
				CanBusEnable_enum CanBusEnable:1; //1 bit
				WiFiEnable_enum WiFiEnable:1; //1 bit
				TcpEnable_enum TcpEnable:2; //2 bit
				VpnEnable_enum VpnEnable:1; //1 bit
				WiFi_AP_Status_enum WiFi_AP_Status:2; //2 bit
				uint8_t TcpClientCount:8; //8 bit
			}Signal;
			uint8_t Data[8];
		};
		struct{
			struct{
				float factor;
				int offset;
				float value;
			}Phys_Value;
		}BatteryBalance_MaxVoltage;
		struct{
			struct{
				float factor;
				int offset;
				float value;
			}Phys_Value;
		}BatteryBalance_MinVoltage;
		struct{
			struct{
				float factor;
				int offset;
				float value;
			}Phys_Value;
		}BatteryBalance_MinTemp;
	}Can_Main;

/* Can_Main Line End */

}DbcStruct;
/*     USER CODE FUNCTION BLOCK START       */

void D2cc_Lib_Init(DbcStruct *st); //Init Function (Must Be Run)

void ReadParse(uint8_t* rx_data, uint32_t id, DbcStruct *st); //Can Read & Parse Function

void CreateTable_Battery_Messages(DbcStruct *dbc);

void CreateTable_Battery_Temperatures(DbcStruct *dbc);

void CreateTable_Battery_Voltages(DbcStruct *dbc);

void CreateTable_Can_Main(DbcStruct *dbc);

/*     USER CODE FUNCTION BLOCK STOP        */

#endif
