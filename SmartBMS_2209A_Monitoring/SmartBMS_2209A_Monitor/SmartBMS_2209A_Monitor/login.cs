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
    public partial class login : Form
    {
        public login()
        {
            InitializeComponent();
        }

        private void login_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                bms_class.WriteTcpClient(bms_class.stream, $"login_{username_textbox.Text}_{password_textbox.Text}");
                string readString = string.Empty;
                byte[] rx = new byte[2];
                int cnt = 0;
                while (readString.Length < 2 && cnt < 10)
                {
                    cnt++;
                    bms_class.stream.Read(rx, 0, rx.Length);
                    readString = Encoding.UTF8.GetString(rx, 0, rx.Length);
                    Array.Clear(rx, 0, rx.Length);
                }
                if (readString.Contains("OK"))
                {
                    this.DialogResult = DialogResult.OK;
                }
                else
                {
                    this.DialogResult = DialogResult.Cancel;
                }
                //MessageBox.Show(readString);
                this.Close();
            }
            catch
            {
                this.DialogResult = DialogResult.Cancel;
                this.Close();
            }

        }
    }
}
