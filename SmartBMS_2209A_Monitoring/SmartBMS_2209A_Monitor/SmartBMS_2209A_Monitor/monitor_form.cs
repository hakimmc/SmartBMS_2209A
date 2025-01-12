using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

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
            Thread th = new Thread(Read_Tcp);
            th.Start();
        }
        bool exit = false;
        bool feedback = false;
        void Read_Tcp()
        {
            string readString = string.Empty;
            byte[] rx = new byte[1024];
            while (readString.Length == 0 && !exit)
            {
                feedback = false;
                bms_class.WriteTcpClient(bms_class.stream, "data");
                bms_class.stream.Read(rx, 0, rx.Length);
                readString = Encoding.UTF8.GetString(rx, 0, rx.Length);
                textBox1.Text += readString + "\n";
                Array.Clear(rx, 0, rx.Length);
                readString = string.Empty;
                Thread.Sleep(2000);
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
                if(readString == "ER")
                {
                    Environment.Exit(0);
                }
            }
        }
    }
}
