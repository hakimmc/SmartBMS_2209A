using Microsoft.VisualBasic.Logging;
using System.Diagnostics;
using System.Net.Sockets;
using System.Text;

namespace SmartBMS_2209A_Monitor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        double opacity_value = 100;
        private void Form1_Load(object sender, EventArgs e)
        {
            timer1.Interval = 1;
            this.Opacity = 0;
            timer1.Enabled = true;
            this.Visible = true;

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (this.Opacity < opacity_value * 100)
            {
                this.Opacity += .010;
            }
            else
            {
                timer1.Enabled = false;
                AUTH();
            }
        }


        public async void AUTH()
        {
            try
            {
                if (!ConnectWifi("connect.bat"))
                {
                    MessageBox.Show("Couldnt Solve WiFi!");
                }
                else
                {
                    AddRule();
                    Thread.Sleep(1000);
                    bms_class.tcpClient = new TcpClient();
                    bms_class.tcpClient.Connect("192.168.4.1", 5166);
                    bms_class.stream = bms_class.tcpClient.GetStream();
                    if (get_Admin_Role(bms_class.stream))
                    {
                        MessageBox.Show("INFO : Validation Success, Login with Username & Password!");
                    }
                    else
                    {
                        MessageBox.Show("INFO : Validation Not Success, Closing App!");
                        Environment.Exit(0);
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        public bool ConnectWifi(string file_name)
        {
            int trycount = 10;
            var proc = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = "connect.bat",
                    UseShellExecute = false,
                    RedirectStandardOutput = true,
                    CreateNoWindow = true
                }
            };
            proc.Start();
            string output = proc.StandardOutput.ReadToEnd().Split('\n')[1];
            proc.WaitForExit();
            int tout = 0;
            while (!output.Contains("Connection request was completed successfully."))// && tout < trycount)
            {
                proc.Start();
                proc.WaitForExit();
                output = proc.StandardOutput.ReadToEnd().Split('\n')[1];
                tout++;
                Thread.Sleep(50);
            }
            return true;
        }

        public async void WriteTcpClient(Stream st, string _buff)
        {
            byte[] buff = System.Text.Encoding.UTF8.GetBytes(_buff);
            st.Write(buff, 0, buff.Length);
            Array.Clear(buff, 0, buff.Length);
        }

        public void AddRule()
        {
            string ruleName = "ESP32_TCP_Connection";
            string portNumber = "5166";
            string netshCommand = $"netsh advfirewall firewall add rule name=\"{ruleName}\" protocol=TCP dir=in localport={portNumber} action=allow";

            // ProcessStartInfo kullanarak netsh komutunu çalýþtýrýyoruz.
            ProcessStartInfo psi = new ProcessStartInfo("cmd.exe", "/c " + netshCommand)
            {
                RedirectStandardOutput = true,
                UseShellExecute = false,
                CreateNoWindow = true
            };

            Process process = new Process
            {
                StartInfo = psi
            };

            process.Start();

            string output = process.StandardOutput.ReadToEnd();
            process.WaitForExit();
        }

        public bool get_Admin_Role(Stream st)
        {

            WriteTcpClient(st, "HELO");
            Thread.Sleep(250);
            string readString = string.Empty;
            byte[] rx = new byte[5];
            int cnt = 0;
            while (!readString.Contains("ID?") && cnt < 10)
            {
                //MessageBox.Show(readString);
                cnt++;
                st.Read(rx, 0, rx.Length);
                readString = Encoding.UTF8.GetString(rx, 0, rx.Length);
                Array.Clear(rx, 0, rx.Length);


            }
            if (cnt == 10)
            {
                return false;
            }
            else
            {
                cnt = 0;
                WriteTcpClient(st, "OBT");
                Thread.Sleep(1000);

                Array.Clear(rx, 0, rx.Length);
                readString = string.Empty;
                while (!readString.Contains("EHLO") && cnt < 10)
                {
                    st.Read(rx, 0, 5);
                    readString = Encoding.UTF8.GetString(rx, 0, rx.Length);
                    //MessageBox.Show(readString);
                    cnt++;
                    Thread.Sleep(100);


                }
                if (cnt == 10)
                {
                    return false;
                }
                return true;
            }
        }
    }
}
