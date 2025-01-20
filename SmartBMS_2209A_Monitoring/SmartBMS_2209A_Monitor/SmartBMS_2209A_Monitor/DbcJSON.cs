using System;

namespace SmartBMS_2209A_Monitor
{
    public class BatteryMessages
    {
        public int BatteryChemistry { get; set; }
        public int Battery_Count { get; set; }
        public int BatteryBalance_MaxVoltage { get; set; }
        public int BatteryBalance_MinVoltage { get; set; }
        public int BatteryBalance_MaxTemp { get; set; }
        public int BatteryBalance_MinTemp { get; set; }
        public int BatterySOC { get; set; }
        public int OCV_Voltages { get; set; }
    }

    public class BatteryTemperatures
    {
        public int Battery_Temp_AUX0 { get; set; }
        public int Battery_Temp_AUX1 { get; set; }
        public int Battery_Temp_AUX2 { get; set; }
        public int Battery_Temp_AUX3 { get; set; }
        public int Battery_Temp_AUX4 { get; set; }
        public int Battery_Temp_AUX5 { get; set; }
        public int Battery_Temp_AUX6 { get; set; }
        public int Battery_Temp_AUX7 { get; set; }
    }

    public class BatteryVoltages1
    {
        public int BatteryVoltage_1 { get; set; }
        public int BatteryVoltage_2 { get; set; }
        public int BatteryVoltage_3 { get; set; }
        public int BatteryVoltage_4 { get; set; }
        public int BatteryVoltage_5 { get; set; }
        public int BatteryVoltage_6 { get; set; }
        public int BatteryVoltage_7 { get; set; }
        public int BatteryVoltage_8 { get; set; }
    }

    public class BatteryVoltages2
    {
        public int BatteryVoltage_9 { get; set; }
        public int BatteryVoltage_10 { get; set; }
        public int BatteryVoltage_11 { get; set; }
        public int BatteryVoltage_12 { get; set; }
        public int BatteryVoltage_13 { get; set; }
        public int BatteryVoltage_14 { get; set; }
        public int BatteryVoltage_15 { get; set; }
        public int BatteryVoltage_16 { get; set; }
    }

    public class CanMain
    {
        public int AliveCounter { get; set; }
        public int WiFi_AP_Status { get; set; }
        public int TcpClientCount { get; set; }
        public int CanBusEnable { get; set; }
        public int TcpEnable { get; set; }
        public int VpnEnable { get; set; }
        public int WiFi_ST_Status { get; set; }
        public int Reserved_1 { get; set; }
        public int WiFi_AP_IP_Adrress { get; set; }
        public int WiFi_ST_IP_Address { get; set; }
        public int SwVersionMajor { get; set; }
        public int SwVersionMinor { get; set; }
        public int SwVersionBugfix { get; set; }
    }

    public class Root
    {
        public BatteryMessages Battery_Messages { get; set; }
        public BatteryTemperatures Battery_Temperatures { get; set; }
        public BatteryVoltages1 Battery_Voltages_1 { get; set; }
        public BatteryVoltages2 Battery_Voltages_2 { get; set; }
        public CanMain Can_Main { get; set; }
    }
}
