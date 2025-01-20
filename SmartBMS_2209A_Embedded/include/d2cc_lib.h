/**
 * @file d2cc_lib.h
 * @brief Header file for the D2CC library.
 * 
 * @date 2025-01-19
 * @author hakimmc
 * @see https://www.linkedin.com/in/abdulhakim-calgin/
 */

#ifndef LIB_
#define LIB_

#include <stdint.h>
#include <stdbool.h>


/** 
 * @def READ_ENABLE
 * @brief If you want to use Readparse function, uncomment it!
 */
//#define READ_ENABLE

/** 
 * @def Battery_Messages_ID
 * @brief CAN ID for Battery_Messages messages.
 */
#define Battery_Messages_ID 	 257

/** 
 * @def Battery_Messages_DLC
 * @brief CAN DLC for Battery_Messages messages.
 */
#define Battery_Messages_DLC 	 8

/** 
 * @def Battery_Temperatures_ID
 * @brief CAN ID for Battery_Temperatures messages.
 */
#define Battery_Temperatures_ID 	 260

/** 
 * @def Battery_Temperatures_DLC
 * @brief CAN DLC for Battery_Temperatures messages.
 */
#define Battery_Temperatures_DLC 	 8

/** 
 * @def Battery_Voltages_1_ID
 * @brief CAN ID for Battery_Voltages_1 messages.
 */
#define Battery_Voltages_1_ID 	 258

/** 
 * @def Battery_Voltages_1_DLC
 * @brief CAN DLC for Battery_Voltages_1 messages.
 */
#define Battery_Voltages_1_DLC 	 8

/** 
 * @def Battery_Voltages_2_ID
 * @brief CAN ID for Battery_Voltages_2 messages.
 */
#define Battery_Voltages_2_ID 	 259

/** 
 * @def Battery_Voltages_2_DLC
 * @brief CAN DLC for Battery_Voltages_2 messages.
 */
#define Battery_Voltages_2_DLC 	 8

/** 
 * @def Can_Main_ID
 * @brief CAN ID for Can_Main messages.
 */
#define Can_Main_ID 	 256

/** 
 * @def Can_Main_DLC
 * @brief CAN DLC for Can_Main messages.
 */
#define Can_Main_DLC 	 8

typedef enum{
/** 
 * @enum BatteryChemistry_enum
 * @brief Enum for representing signal values for the BatteryChemistry signal.
 * 
 * This enum maps each value in the signal's value table to a corresponding identifier.
 * It is used to interpret the raw data received from the CAN bus and provides human-readable names for each value.
 * 
 * @note Ensure the signal values are aligned with the data type and expected range of the signal.
 */
	/** @brief LFP */
	BatteryChemistry_LFP,	/** @brief NMC */
	BatteryChemistry_NMC,	/** @brief NCA */
	BatteryChemistry_NCA,	/** @brief LCO */
	BatteryChemistry_LCO,	/** @brief LMO */
	BatteryChemistry_LMO,	/** @brief LTO */
	BatteryChemistry_LTO,	/** @brief NiMH */
	BatteryChemistry_NiMH,	/** @brief NiCd */
	BatteryChemistry_NiCd,	/** @brief PbA */
	BatteryChemistry_PbA,	/** @brief Zn_Air */
	BatteryChemistry_Zn_Air,	/** @brief Li_S */
	BatteryChemistry_Li_S,	/** @brief Na_ion */
	BatteryChemistry_Na_ion,	/** @brief Zn_MnO2 */
	BatteryChemistry_Zn_MnO2,	/** @brief VRLA */
	BatteryChemistry_VRLA,	/** @brief Ag_Zn */
	BatteryChemistry_Ag_Zn
}BatteryChemistry_enum;


typedef enum{
/** 
 * @enum WiFi_AP_Status_enum
 * @brief Enum for representing signal values for the WiFi_AP_Status signal.
 * 
 * This enum maps each value in the signal's value table to a corresponding identifier.
 * It is used to interpret the raw data received from the CAN bus and provides human-readable names for each value.
 * 
 * @note Ensure the signal values are aligned with the data type and expected range of the signal.
 */
	/** @brief WiFi_Ap_Disconnected */
	WiFi_AP_Status_WiFi_Ap_Disconnected,	/** @brief WiFi_Ap_Connected */
	WiFi_AP_Status_WiFi_Ap_Connected
}WiFi_AP_Status_enum;


typedef enum{
/** 
 * @enum CanBusEnable_enum
 * @brief Enum for representing signal values for the CanBusEnable signal.
 * 
 * This enum maps each value in the signal's value table to a corresponding identifier.
 * It is used to interpret the raw data received from the CAN bus and provides human-readable names for each value.
 * 
 * @note Ensure the signal values are aligned with the data type and expected range of the signal.
 */
	/** @brief CAN_Driver_Disabled */
	CanBusEnable_CAN_Driver_Disabled,	/** @brief CAN_Driver_Enabled */
	CanBusEnable_CAN_Driver_Enabled
}CanBusEnable_enum;


typedef enum{
/** 
 * @enum TcpEnable_enum
 * @brief Enum for representing signal values for the TcpEnable signal.
 * 
 * This enum maps each value in the signal's value table to a corresponding identifier.
 * It is used to interpret the raw data received from the CAN bus and provides human-readable names for each value.
 * 
 * @note Ensure the signal values are aligned with the data type and expected range of the signal.
 */
	/** @brief TCP_Offline */
	TcpEnable_TCP_Offline,	/** @brief TCP_Online */
	TcpEnable_TCP_Online,	/** @brief TCP_Connected */
	TcpEnable_TCP_Connected,	/** @brief TCP_Error */
	TcpEnable_TCP_Error
}TcpEnable_enum;


typedef enum{
/** 
 * @enum VpnEnable_enum
 * @brief Enum for representing signal values for the VpnEnable signal.
 * 
 * This enum maps each value in the signal's value table to a corresponding identifier.
 * It is used to interpret the raw data received from the CAN bus and provides human-readable names for each value.
 * 
 * @note Ensure the signal values are aligned with the data type and expected range of the signal.
 */
	/** @brief VPN_Offline */
	VpnEnable_VPN_Offline,	/** @brief VPN_Online */
	VpnEnable_VPN_Online,	/** @brief VPN_Connected */
	VpnEnable_VPN_Connected,	/** @brief VPN_Error */
	VpnEnable_VPN_Error
}VpnEnable_enum;


typedef enum{
/** 
 * @enum WiFi_ST_Status_enum
 * @brief Enum for representing signal values for the WiFi_ST_Status signal.
 * 
 * This enum maps each value in the signal's value table to a corresponding identifier.
 * It is used to interpret the raw data received from the CAN bus and provides human-readable names for each value.
 * 
 * @note Ensure the signal values are aligned with the data type and expected range of the signal.
 */
	/** @brief WiFi_Ap_Disconnected */
	WiFi_ST_Status_WiFi_Ap_Disconnected,	/** @brief WiFi_Ap_Connected */
	WiFi_ST_Status_WiFi_Ap_Connected
}WiFi_ST_Status_enum;

/** 
 * @brief factor, offset and value variable structer for CAN messages structure for message.
 * 
 * This structure including factor, offset and value variables.
 */
typedef struct {
    float factor;
    int offset;
    float value;
} Phys_Value_t;

typedef struct{
/** 
 * @brief CAN message structure for message Battery_Messages.
 * 
 * This structure represents the CAN message, including the signals and their values.
 */
/* Battery_Messages Line Start */
	struct{
		union{
			struct{
				/** @brief Signal BatteryChemistry enum type. */
				BatteryChemistry_enum BatteryChemistry:4; //4 bit
				/** @brief Battery_Count signal with 8-bit length. */
				uint8_t Battery_Count:4; //4 bit
				/** @brief BatteryBalance_MaxVoltage signal with 8-bit length. */
				uint8_t BatteryBalance_MaxVoltage:8; //8 bit
				/** @brief BatteryBalance_MinVoltage signal with 8-bit length. */
				uint8_t BatteryBalance_MinVoltage:8; //8 bit
				/** @brief BatteryBalance_MaxTemp signal with 8-bit length. */
				uint8_t BatteryBalance_MaxTemp:8; //8 bit
				/** @brief BatteryBalance_MinTemp signal with 8-bit length. */
				uint8_t BatteryBalance_MinTemp:8; //8 bit
				/** @brief BatterySOC signal with 8-bit length. */
				uint8_t BatterySOC:8; //8 bit
				/** @brief OCV_Voltages signal with 16-bit length. */
				uint16_t OCV_Voltages:16; //16 bit
			}Signal;
			uint8_t Data[8];
		};
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}Battery_Count;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryBalance_MaxVoltage;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryBalance_MinVoltage;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryBalance_MinTemp;
	}Battery_Messages;

/* Battery_Messages Line End */

/** 
 * @brief CAN message structure for message Battery_Temperatures.
 * 
 * This structure represents the CAN message, including the signals and their values.
 */
/* Battery_Temperatures Line Start */
	struct{
		union{
			struct{
				/** @brief Battery_Temp_AUX0 signal with 8-bit length. */
				uint8_t Battery_Temp_AUX0:8; //8 bit
				/** @brief Battery_Temp_AUX1 signal with 8-bit length. */
				uint8_t Battery_Temp_AUX1:8; //8 bit
				/** @brief Battery_Temp_AUX2 signal with 8-bit length. */
				uint8_t Battery_Temp_AUX2:8; //8 bit
				/** @brief Battery_Temp_AUX3 signal with 8-bit length. */
				uint8_t Battery_Temp_AUX3:8; //8 bit
				/** @brief Battery_Temp_AUX4 signal with 8-bit length. */
				uint8_t Battery_Temp_AUX4:8; //8 bit
				/** @brief Battery_Temp_AUX5 signal with 8-bit length. */
				uint8_t Battery_Temp_AUX5:8; //8 bit
				/** @brief Battery_Temp_AUX6 signal with 8-bit length. */
				uint8_t Battery_Temp_AUX6:8; //8 bit
				/** @brief Battery_Temp_AUX7 signal with 8-bit length. */
				uint8_t Battery_Temp_AUX7:8; //8 bit
			}Signal;
			uint8_t Data[8];
		};
	}Battery_Temperatures;

/* Battery_Temperatures Line End */

/** 
 * @brief CAN message structure for message Battery_Voltages_1.
 * 
 * This structure represents the CAN message, including the signals and their values.
 */
/* Battery_Voltages_1 Line Start */
	struct{
		union{
			struct{
				/** @brief BatteryVoltage_1 signal with 8-bit length. */
				uint8_t BatteryVoltage_1:8; //8 bit
				/** @brief BatteryVoltage_2 signal with 8-bit length. */
				uint8_t BatteryVoltage_2:8; //8 bit
				/** @brief BatteryVoltage_3 signal with 8-bit length. */
				uint8_t BatteryVoltage_3:8; //8 bit
				/** @brief BatteryVoltage_4 signal with 8-bit length. */
				uint8_t BatteryVoltage_4:8; //8 bit
				/** @brief BatteryVoltage_5 signal with 8-bit length. */
				uint8_t BatteryVoltage_5:8; //8 bit
				/** @brief BatteryVoltage_6 signal with 8-bit length. */
				uint8_t BatteryVoltage_6:8; //8 bit
				/** @brief BatteryVoltage_7 signal with 8-bit length. */
				uint8_t BatteryVoltage_7:8; //8 bit
				/** @brief BatteryVoltage_8 signal with 8-bit length. */
				uint8_t BatteryVoltage_8:8; //8 bit
			}Signal;
			uint8_t Data[8];
		};
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_1;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_2;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_3;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_4;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_5;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_6;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_7;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_8;
	}Battery_Voltages_1;

/* Battery_Voltages_1 Line End */

/** 
 * @brief CAN message structure for message Battery_Voltages_2.
 * 
 * This structure represents the CAN message, including the signals and their values.
 */
/* Battery_Voltages_2 Line Start */
	struct{
		union{
			struct{
				/** @brief BatteryVoltage_9 signal with 8-bit length. */
				uint8_t BatteryVoltage_9:8; //8 bit
				/** @brief BatteryVoltage_10 signal with 8-bit length. */
				uint8_t BatteryVoltage_10:8; //8 bit
				/** @brief BatteryVoltage_11 signal with 8-bit length. */
				uint8_t BatteryVoltage_11:8; //8 bit
				/** @brief BatteryVoltage_12 signal with 8-bit length. */
				uint8_t BatteryVoltage_12:8; //8 bit
				/** @brief BatteryVoltage_13 signal with 8-bit length. */
				uint8_t BatteryVoltage_13:8; //8 bit
				/** @brief BatteryVoltage_14 signal with 8-bit length. */
				uint8_t BatteryVoltage_14:8; //8 bit
				/** @brief BatteryVoltage_15 signal with 8-bit length. */
				uint8_t BatteryVoltage_15:8; //8 bit
				/** @brief BatteryVoltage_16 signal with 8-bit length. */
				uint8_t BatteryVoltage_16:8; //8 bit
			}Signal;
			uint8_t Data[8];
		};
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_9;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_10;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_11;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_12;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_13;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_14;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_15;
		/** @brief Factor for scaling the raw signal value. */
		struct{
			Phys_Value_t Phys_Value;
		}BatteryVoltage_16;
	}Battery_Voltages_2;

/* Battery_Voltages_2 Line End */

/** 
 * @brief CAN message structure for message Can_Main.
 * 
 * This structure represents the CAN message, including the signals and their values.
 */
/* Can_Main Line Start */
	struct{
		union{
			struct{
				/** @brief AliveCounter signal with 8-bit length. */
				uint8_t AliveCounter:7; //7 bit
				/** @brief Signal WiFi_AP_Status enum type. */
				WiFi_AP_Status_enum WiFi_AP_Status:1; //1 bit
				/** @brief TcpClientCount signal with 8-bit length. */
				uint8_t TcpClientCount:8; //8 bit
				/** @brief Signal CanBusEnable enum type. */
				CanBusEnable_enum CanBusEnable:1; //1 bit
				/** @brief Signal TcpEnable enum type. */
				TcpEnable_enum TcpEnable:2; //2 bit
				/** @brief Signal VpnEnable enum type. */
				VpnEnable_enum VpnEnable:2; //2 bit
				/** @brief Signal WiFi_ST_Status enum type. */
				WiFi_ST_Status_enum WiFi_ST_Status:2; //2 bit
				/** @brief Reserved_1 signal with 8-bit length. */
				uint8_t Reserved_1:1; //1 bit
				/** @brief WiFi_AP_IP_Adrress signal with 16-bit length. */
				uint16_t WiFi_AP_IP_Adrress:16; //16 bit
				/** @brief WiFi_ST_IP_Address signal with 16-bit length. */
				uint16_t WiFi_ST_IP_Address:16; //16 bit
				/** @brief SwVersionMajor signal with 8-bit length. */
				uint8_t SwVersionMajor:2; //2 bit
				/** @brief SwVersionMinor signal with 8-bit length. */
				uint8_t SwVersionMinor:2; //2 bit
				/** @brief SwVersionBugfix signal with 8-bit length. */
				uint8_t SwVersionBugfix:4; //4 bit
			}Signal;
			uint8_t Data[8];
		};
	}Can_Main;

/* Can_Main Line End */

}DbcStruct;
/*     USER CODE FUNCTION BLOCK START       */

/**
 * @brief Initializes the DbcStruct for CAN message processing.
 *
 * This function should be called before using the DbcStruct to ensure that all
 * message structures are properly initialized. It sets up necessary memory and 
 * configurations.
 *
 * @param[in] st Pointer to the DbcStruct instance that will be initialized.
 */

void D2cc_Lib_Init(DbcStruct *st); //Init Function (Must Be Run)

#ifdef READ_ENABLE
/**
 * @brief Reads and parses CAN data.
 *
 * This function reads CAN data from the provided `rx_data` and parses it into the 
 * corresponding message and signal structures in the DbcStruct. It uses the CAN 
 * message ID to identify the message to parse.
 *
 * This function is only enabled if `READ_ENABLE` is defined.
 *
 * @param[in] rx_data Pointer to the received CAN data.
 * @param[in] id The CAN message ID that is used to determine which message to parse.
 * @param[in,out] st Pointer to the DbcStruct instance where the parsed data will be stored.
 */

void ReadParse(uint8_t* rx_data, uint32_t id, DbcStruct *st); //Can Read & Parse Function

#endif

/**
 * @brief Creates the signal table for the specified CAN message.
 *
 * This function initializes the signal table for the given CAN message. It 
 * organizes and prepares the signals in the message to be ready for processing 
 * or encoding.
 *
 * @param[in] dbc Pointer to the DbcStruct instance that contains the CAN message.
 */

void CreateTable_Battery_Messages(DbcStruct *dbc);

/**
 * @brief Creates the signal table for the specified CAN message.
 *
 * This function initializes the signal table for the given CAN message. It 
 * organizes and prepares the signals in the message to be ready for processing 
 * or encoding.
 *
 * @param[in] dbc Pointer to the DbcStruct instance that contains the CAN message.
 */

void CreateTable_Battery_Temperatures(DbcStruct *dbc);

/**
 * @brief Creates the signal table for the specified CAN message.
 *
 * This function initializes the signal table for the given CAN message. It 
 * organizes and prepares the signals in the message to be ready for processing 
 * or encoding.
 *
 * @param[in] dbc Pointer to the DbcStruct instance that contains the CAN message.
 */

void CreateTable_Battery_Voltages_1(DbcStruct *dbc);

/**
 * @brief Creates the signal table for the specified CAN message.
 *
 * This function initializes the signal table for the given CAN message. It 
 * organizes and prepares the signals in the message to be ready for processing 
 * or encoding.
 *
 * @param[in] dbc Pointer to the DbcStruct instance that contains the CAN message.
 */

void CreateTable_Battery_Voltages_2(DbcStruct *dbc);

/**
 * @brief Creates the signal table for the specified CAN message.
 *
 * This function initializes the signal table for the given CAN message. It 
 * organizes and prepares the signals in the message to be ready for processing 
 * or encoding.
 *
 * @param[in] dbc Pointer to the DbcStruct instance that contains the CAN message.
 */

void CreateTable_Can_Main(DbcStruct *dbc);

/**
 * @brief Converts a physical value to its corresponding raw CAN value.
 *
 * This function takes a physical value and applies the scaling factor and offset 
 * specified in the `Phys_Value_t` structure to convert it to the raw CAN signal value.
 * The raw value can then be transmitted in a CAN message.
 *
 * @param[in] phys_value The physical value to be converted.
 * @param[in] phys_struct Pointer to the `Phys_Value_t` structure containing scaling and offset information.
 *
 * @return The corresponding raw CAN value.
 */

uint32_t PHYS_TO_RAW(int phys_value, Phys_Value_t *phys_struct);

/**
 * @brief Converts a raw CAN value to its corresponding physical value.
 *
 * This function takes a raw CAN value and applies the scaling factor and offset 
 * specified in the `Phys_Value_t` structure to convert it to the physical signal value.
 * The physical value represents the actual measured or calculated value of the signal.
 *
 * @param[in] raw_value The raw CAN signal value to be converted.
 * @param[in] phys_struct Pointer to the `Phys_Value_t` structure containing scaling and offset information.
 *
 * @return The corresponding physical value.
 */

uint32_t RAW_TO_PHYS(int raw_value, Phys_Value_t *phys_struct);

/*     USER CODE FUNCTION BLOCK STOP        */

#endif
