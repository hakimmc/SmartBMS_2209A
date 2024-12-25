using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;
using System.Net.Sockets;


namespace SmartBMS_2209A_Monitor
{
    public static class bms_class
    {
        public static string execute_Command_Run(string url, string cmd)
        {
            return $"{url}?message=${cmd}";
        }

        public static string last_username;
        public static TcpClient tcpClient;
        public static Stream stream;
        public static async void WriteTcpClient(Stream st, string _buff)
        {
            byte[] buff = System.Text.Encoding.UTF8.GetBytes(_buff);
            st.Write(buff, 0, buff.Length);
            Array.Clear(buff, 0, buff.Length);
        }

        public static async void ReadTcpServer(Stream st, string _buff, int buff_len)
        {
            byte[] buff = new byte[buff_len];
            st.Read(buff, 0, buff.Length);
            _buff = System.Text.Encoding.UTF8.GetString(buff);
        }

        public static string[] batteryAbbreviations = new string[]
        {
            "Li-ion",   // Lithium-Ion
            "Li-Po",    // Lithium-Polymer
            "NiCd",     // Nickel-Cadmium
            "NiMH",     // Nickel-Metal Hydride
            "Pb-Acid",  // Lead-Acid
            "Zn-Air",   // Zinc-Air
            "AgO",      // Silver-Oxide
            "Al-Air",   // Aluminum-Air
            "LiFePO4",  // Lithium Iron Phosphate
            "Li-S",     // Lithium-Sulfur
            "LTO",      // Lithium Titanate
            "NaS",      // Sodium-Sulfur
            "Na-NiCl2", // Sodium-Nickel Chloride (Zebra)
            "Mg-Air",   // Magnesium-Air
            "Ni-H2",    // Nickel-Hydrogen
            "Li-Air",   // Lithium-Air
            "Ca-Air",   // Calcium-Air
            "F-ion"     // Fluoride-Ion
        };

        public static string[] batteryDescriptions = new string[]
        {
            "Lithium-Ion",
            "Lithium-Polymer",
            "Nickel-Cadmium",
            "Nickel-Metal Hydride",
            "Lead-Acid",
            "Zinc-Air",
            "Silver-Oxide",
            "Aluminum-Air",
            "Lithium Iron Phosphate",
            "Lithium-Sulfur",
            "Lithium Titanate",
            "Sodium-Sulfur",
            "Sodium-Nickel Chloride (Zebra)",
            "Magnesium-Air",
            "Nickel-Hydrogen",
            "Lithium-Air",
            "Calcium-Air",
            "Fluoride-Ion"
        };

        public static float[] batteryMinVoltages = new float[]
        {
            2.5f,  // Li-ion
            3.0f,  // Li-Po
            0.9f,  // NiCd
            1.0f,  // NiMH
            1.75f, // Pb-Acid
            1.15f, // Zn-Air
            1.55f, // AgO
            1.2f,  // Al-Air
            2.0f,  // LiFePO4
            1.5f,  // Li-S
            1.8f,  // LTO
            1.78f, // NaS
            2.58f, // Na-NiCl2
            1.2f,  // Mg-Air
            1.2f,  // Ni-H2
            2.9f,  // Li-Air
            1.25f, // Ca-Air
            1.0f   // F-ion
        };

        public static float[] batteryMaxVoltages = new float[]
        {
            4.2f,  // Li-ion
            4.2f,  // Li-Po
            1.5f,  // NiCd
            1.4f,  // NiMH
            2.45f, // Pb-Acid
            1.65f, // Zn-Air
            1.65f, // AgO
            2.7f,  // Al-Air
            3.65f, // LiFePO4
            2.6f,  // Li-S
            2.85f, // LTO
            2.08f, // NaS
            2.75f, // Na-NiCl2
            3.1f,  // Mg-Air
            1.55f, // Ni-H2
            4.1f,  // Li-Air
            2.3f,  // Ca-Air
            2.9f   // F-ion
        };

        public static void WriteToJsonFile<T>(string filePath, T data)
        {
            try
            {
                string jsonString = JsonSerializer.Serialize(data, new JsonSerializerOptions
                {
                    WriteIndented = true
                });

                File.WriteAllText(filePath, jsonString);

                MessageBox.Show($"Data successfully written to {filePath}");
            }
            catch (Exception ex)
            {
                MessageBox.Show($"An error occurred while writing to the JSON file: {ex.Message}");
            }
        }

        public class ProjectData
        {
            public string Project_Code { get; set; }
            public int Cell_Count { get; set; }
            public int Chain_Count { get; set; }
            public string Cell_Chemistry { get; set; }
            public float CellVoltageMax_Value { get; set; }
            public float CellVoltageMin_Value { get; set; }
            public double OV_Value { get; set; }
            public double UV_Value { get; set; }
            public bool Chargeable { get; set; }
            public bool Discargeable { get; set;}
            public bool Balanceable { get; set; }
            public double OT_Value { get; set; }
            public double UT_Value { get; set; }

        }
        public static string json_filePath = "batteryData.json";
        public static Size default_size;
    }
}
