using Newtonsoft.Json;
using SmartBMS_2209A_Monitor.Properties;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace SmartBMS_2209A_Monitor
{
    public partial class monitor_form : Form
    {
        public monitor_form()
        {
            InitializeComponent();
        }

        private void monitor_form_Load(object sender, EventArgs e)
        {
            tabControl1.TabPages[0].Text = "Main Battery Page";
            tabControl1.TabPages[1].Text = "Multiple Battery Page";
            Thread th = new Thread(Read_Tcp);
            th.Start();
        }
        bool exit = false;
        bool feedback = false;
        void Read_Tcp()
        {
            try
            {
                string readString = string.Empty;
                byte[] rx = new byte[2048];
                while (readString.Length == 0 && !exit)
                {
                    feedback = false;
                    bms_class.WriteTcpClient(bms_class.stream, "data");
                    bms_class.stream.Read(rx, 0, rx.Length);
                    readString = Encoding.UTF8.GetString(rx, 0, rx.Length);
                    if (readString.Length < 50) continue;
                    //textBox1.Text = readString;
                    Replace_Datas(readString);
                    Array.Clear(rx, 0, rx.Length);
                    readString = string.Empty;
                    Thread.Sleep(5000);

                }
            }
            catch
            {
                
            }
        }

        private void monitor_form_FormClosing(object sender, FormClosingEventArgs e)
        {
            exit = true;
            string readString = string.Empty;
            byte[] rx = new byte[2];
            while (true)
            {
                bms_class.WriteTcpClient(bms_class.stream, "exit");
                bms_class.stream.Read(rx, 0, rx.Length);
                readString = Encoding.UTF8.GetString(rx, 0, rx.Length);
                MessageBox.Show("BMS Closed Connection!");
                if (readString == "ER")
                {
                    Environment.Exit(0);
                }
            }
        }

        public void Replace_Datas(string json_data)
        {
            // JSON verisini RawData nesnesine dönüştür
            Root root = JsonConvert.DeserializeObject<Root>(json_data);

            soc.Text = $"SoC : % {root.Battery_Messages.BatterySOC}";
            switch (root.Battery_Messages.BatterySOC / 10)
            {
                case 0:
                    batteryimg.Image = Resources._000;
                        break;
                case 1:
                    batteryimg.Image = Resources._001;
                    break;
                case 2:
                    batteryimg.Image = Resources._002;
                    break;
                case 3:
                    batteryimg.Image = Resources._003;
                    break;
                case 4:
                    batteryimg.Image = Resources._004;
                    break;
                case 5:
                    batteryimg.Image = Resources._005;
                    break;
                case 6:
                    batteryimg.Image = Resources._006;
                    break;
                case 7:
                    batteryimg.Image = Resources._007;
                    break;
                case 8:
                    batteryimg.Image = Resources._008;
                    break;
                case 9:
                    batteryimg.Image = Resources._009;
                    break;
                case 10:
                    batteryimg.Image = Resources._010;
                    break;
            }
            int summbat = (root.Battery_Voltages_1.BatteryVoltage_1 * 10) + 2000 +
                    (root.Battery_Voltages_1.BatteryVoltage_2 * 10) + 2000 +
                    (root.Battery_Voltages_1.BatteryVoltage_3 * 10) + 2000 +
                    (root.Battery_Voltages_1.BatteryVoltage_4 * 10) + 2000 +
                    (root.Battery_Voltages_1.BatteryVoltage_5 * 10) + 2000 +
                    (root.Battery_Voltages_1.BatteryVoltage_6 * 10) + 2000 +
                    (root.Battery_Voltages_1.BatteryVoltage_7 * 10) + 2000 +
                    (root.Battery_Voltages_1.BatteryVoltage_8 * 10) + 2000 +
                    (root.Battery_Voltages_2.BatteryVoltage_9 * 10) + 2000 +
                    (root.Battery_Voltages_2.BatteryVoltage_10 * 10) + 2000 +
                    (root.Battery_Voltages_2.BatteryVoltage_11 * 10) + 2000 +
                    (root.Battery_Voltages_2.BatteryVoltage_12 * 10) + 2000 +
                    (root.Battery_Voltages_2.BatteryVoltage_13 * 10) + 2000 +
                    (root.Battery_Voltages_2.BatteryVoltage_14 * 10) + 2000 +
                    (root.Battery_Voltages_2.BatteryVoltage_15 * 10) + 2000 +
                    (root.Battery_Voltages_2.BatteryVoltage_16 * 10) + 2000;
            summvoltage.Text = $"Sum Voltage : {Convert.ToDouble(summbat)/1000} V";
            temperature.Text = $"Temperature : {root.Battery_Temperatures.Battery_Temp_AUX0} °C";
            batchem.Text = $"Battery Chemistry : {GetBatteryChemistryName(root.Battery_Messages.BatteryChemistry)}";
            batcount.Text = $"Battery Count : {root.Battery_Messages.Battery_Count+1}";
            batterymaxv.Text = $"Battery Max V : {Convert.ToDouble(((root.Battery_Messages.BatteryBalance_MaxVoltage*10)+2000))/1000} V";
            batteryminv.Text = $"Battery Min V : {Convert.ToDouble(((root.Battery_Messages.BatteryBalance_MinVoltage * 10) + 2000))/1000} V";
            batterymaxtemp.Text = $"Battery Max Temp : {root.Battery_Messages.BatteryBalance_MaxTemp} °C";
            batterymintemp.Text = $"Battery Max Temp : {((root.Battery_Messages.BatteryBalance_MinTemp * 1) - 100)} °C";
            sw_version.Text = $"Software Version : {root.Can_Main.SwVersionMajor}.{root.Can_Main.SwVersionMinor}.{root.Can_Main.SwVersionBugfix}";
            alivecounter.Text = $"Alive Counter : {root.Can_Main.AliveCounter}";
            b1.Text = $"{((root.Battery_Voltages_1.BatteryVoltage_1 * 10) + 2000)} mV";
            b2.Text = $"{((root.Battery_Voltages_1.BatteryVoltage_2 * 10) + 2000)} mV";
            b3.Text = $"{((root.Battery_Voltages_1.BatteryVoltage_3 * 10) + 2000)} mV";
            b4.Text = $"{((root.Battery_Voltages_1.BatteryVoltage_4 * 10) + 2000)} mV";
            b5.Text = $"{((root.Battery_Voltages_1.BatteryVoltage_5 * 10) + 2000)} mV";
            b6.Text = $"{((root.Battery_Voltages_1.BatteryVoltage_6 * 10) + 2000)} mV";
            b7.Text = $"{((root.Battery_Voltages_1.BatteryVoltage_7 * 10) + 2000)} mV";
            b8.Text = $"{((root.Battery_Voltages_1.BatteryVoltage_8 * 10) + 2000)} mV";
            b9.Text = $"{((root.Battery_Voltages_2.BatteryVoltage_9 * 10) + 2000)} mV";
            b10.Text = $"{((root.Battery_Voltages_2.BatteryVoltage_10 * 10) + 2000)} mV";
            b11.Text = $"{((root.Battery_Voltages_2.BatteryVoltage_11 * 10) + 2000)} mV";
            b12.Text = $"{((root.Battery_Voltages_2.BatteryVoltage_12 * 10) + 2000)} mV";
            b13.Text = $"{((root.Battery_Voltages_2.BatteryVoltage_13 * 10) + 2000)} mV";
            b14.Text = $"{((root.Battery_Voltages_2.BatteryVoltage_14 * 10) + 2000)} mV";
            b15.Text = $"{((root.Battery_Voltages_2.BatteryVoltage_15 * 10) + 2000)} mV";
            b16.Text = $"{((root.Battery_Voltages_2.BatteryVoltage_16 * 10) + 2000)} mV";
            t1.Text = $"{root.Battery_Temperatures.Battery_Temp_AUX0} °C";
            t2.Text = $"{root.Battery_Temperatures.Battery_Temp_AUX1} °C";
            t3.Text = $"{root.Battery_Temperatures.Battery_Temp_AUX2} °C";
            t4.Text = $"{root.Battery_Temperatures.Battery_Temp_AUX3} °C";
            t5.Text = $"{root.Battery_Temperatures.Battery_Temp_AUX4} °C";
            t6.Text = $"{root.Battery_Temperatures.Battery_Temp_AUX5} °C";
            t7.Text = $"{root.Battery_Temperatures.Battery_Temp_AUX6} °C";
            t8.Text = $"{root.Battery_Temperatures.Battery_Temp_AUX7} °C";
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        public static string GetBatteryChemistryName(int batchem)
        {
            switch (batchem)
            {
                case 0:
                    return "LFP";
                case 1:
                    return "NMC";
                case 2:
                    return "NCA";
                case 3:
                    return "LCO";
                case 4:
                    return "LMO";
                case 5:
                    return "LTO";
                case 6:
                    return "NiMH";
                case 7:
                    return "NiCd";
                case 8:
                    return "PbA";
                case 9:
                    return "Zn_Air";
                case 10:
                    return "Li_S";
                case 11:
                    return "Na_ion";
                case 12:
                    return "Zn_MnO2";
                case 13:
                    return "VRLA";
                case 14:
                    return "Ag_Zn";
                default:
                    return "Unknown";
            }
        }

    }
}
