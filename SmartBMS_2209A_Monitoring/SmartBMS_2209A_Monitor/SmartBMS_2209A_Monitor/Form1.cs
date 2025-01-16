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
        double opacity_max;
        private void Form1_Load(object sender, EventArgs e)
        {
            opacity_max = this.Opacity;
            timer1.Interval = 10;
            this.Opacity = 0;
            timer1.Enabled = true;
            this.Visible = true;

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (this.Opacity < opacity_max)
            {
                this.Opacity += .01;
            }
            else
            {
                timer1.Enabled = false;
                Control.CheckForIllegalCrossThreadCalls = false;
                Thread th = new Thread(auth);
                th.Start();
            }
        }

        void auth()
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
                    bms_class.tcpClient = new TcpClient();
                    bms_class.tcpClient.Connect("192.168.4.1", 5166);
                    bms_class.stream = bms_class.tcpClient.GetStream();
                    if (get_Admin_Role(bms_class.stream))
                    {
                        //MessageBox.Show("INFO : Validation Success, Login with Username & Password!");
                        login login_w_credentials = new login();
                        DialogResult dr = login_w_credentials.ShowDialog();
                        if (dr == DialogResult.OK)
                        {
                            get_monitor();
                        }
                        else
                        {
                            MessageBox.Show("Invalid Username Or Password, Closing Application!");
                            Thread.Sleep(2000);
                            Environment.Exit(0);
                        }
                    }
                    else
                    {
                        MessageBox.Show("Turn on the Bms, Closing Application!");
                        Environment.Exit(0);
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Turn on the Bms, Closing Application!");
                Environment.Exit(0);
            }
        }

        void get_monitor()
        {
            this.Hide();
            monitor_form monitor_Form = new monitor_form();
            monitor_Form.ShowDialog();
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
            // removed with v2 software. added external bat file for addrule

            string ruleName = "OTTOMOTIVE_BMS";
            bool isRuleExists = false;

            // Check if the rule exists
            var checkRuleProc = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = "netsh",
                    Arguments = $"advfirewall firewall show rule name=\"{ruleName}\"",
                    UseShellExecute = false,
                    RedirectStandardOutput = true,
                    CreateNoWindow = true
                }
            };

            checkRuleProc.Start();
            string output = checkRuleProc.StandardOutput.ReadToEnd();
            checkRuleProc.WaitForExit();

            // Check if the rule exists in the output
            isRuleExists = output.Contains(ruleName);

            if (!isRuleExists)
            {
                // Add the rule if it does not exist
                var addRuleProc = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = "add_firewall_rule.bat",
                        UseShellExecute = true,
                        Verb = "runas",
                        RedirectStandardOutput = false,
                        CreateNoWindow = false
                    }
                };

                try
                {
                    addRuleProc.Start();
                    addRuleProc.WaitForExit();
                    Console.WriteLine("Batch file executed successfully.");
                }
                catch (System.ComponentModel.Win32Exception ex)
                {
                    Console.WriteLine($"Error: {ex.Message}");
                }
            }

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
                cnt++;
                st.Read(rx, 0, rx.Length);
                readString = Encoding.UTF8.GetString(rx, 0, rx.Length);
                Array.Clear(rx, 0, rx.Length);
                //WriteTcpClient(st, "HELO");
                Thread.Sleep(250);

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
                    //WriteTcpClient(st, "OBT");
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
