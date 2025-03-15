namespace SmartBMS_2209A_Monitor
{
    partial class monitor_form
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            batteryimg = new PictureBox();
            summvoltage = new Label();
            tabControl1 = new TabControl();
            tabPage1 = new TabPage();
            panel3 = new Panel();
            b16 = new TextBox();
            b15 = new TextBox();
            b14 = new TextBox();
            b13 = new TextBox();
            b12 = new TextBox();
            b11 = new TextBox();
            b10 = new TextBox();
            b9 = new TextBox();
            label23 = new Label();
            t8 = new TextBox();
            label24 = new Label();
            t7 = new TextBox();
            label25 = new Label();
            t6 = new TextBox();
            label26 = new Label();
            t5 = new TextBox();
            label19 = new Label();
            t4 = new TextBox();
            label20 = new Label();
            t3 = new TextBox();
            label21 = new Label();
            t2 = new TextBox();
            label22 = new Label();
            t1 = new TextBox();
            label11 = new Label();
            label12 = new Label();
            label13 = new Label();
            label14 = new Label();
            label15 = new Label();
            label16 = new Label();
            label17 = new Label();
            label18 = new Label();
            label7 = new Label();
            b8 = new TextBox();
            label8 = new Label();
            b7 = new TextBox();
            label9 = new Label();
            b6 = new TextBox();
            label10 = new Label();
            b5 = new TextBox();
            label5 = new Label();
            b4 = new TextBox();
            label6 = new Label();
            b3 = new TextBox();
            label4 = new Label();
            b2 = new TextBox();
            label3 = new Label();
            b1 = new TextBox();
            panel2 = new Panel();
            alivecounter = new Label();
            sw_version = new Label();
            panel1 = new Panel();
            batterymintemp = new Label();
            batterymaxtemp = new Label();
            batteryminv = new Label();
            batterymaxv = new Label();
            batcount = new Label();
            batchem = new Label();
            temperature = new Label();
            soc = new Label();
            tabPage2 = new TabPage();
            data_pull_timer = new System.Windows.Forms.Timer(components);
            ((System.ComponentModel.ISupportInitialize)batteryimg).BeginInit();
            tabControl1.SuspendLayout();
            tabPage1.SuspendLayout();
            panel3.SuspendLayout();
            panel2.SuspendLayout();
            panel1.SuspendLayout();
            SuspendLayout();
            // 
            // batteryimg
            // 
            batteryimg.Image = Properties.Resources._010;
            batteryimg.Location = new Point(3, 3);
            batteryimg.Name = "batteryimg";
            batteryimg.Size = new Size(174, 92);
            batteryimg.SizeMode = PictureBoxSizeMode.Zoom;
            batteryimg.TabIndex = 1;
            batteryimg.TabStop = false;
            batteryimg.Click += pictureBox1_Click;
            // 
            // summvoltage
            // 
            summvoltage.AutoSize = true;
            summvoltage.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 162);
            summvoltage.Location = new Point(4, 120);
            summvoltage.Name = "summvoltage";
            summvoltage.Size = new Size(130, 21);
            summvoltage.TabIndex = 2;
            summvoltage.Text = "Sum Voltage : V";
            // 
            // tabControl1
            // 
            tabControl1.Controls.Add(tabPage1);
            tabControl1.Controls.Add(tabPage2);
            tabControl1.Location = new Point(0, 0);
            tabControl1.Name = "tabControl1";
            tabControl1.SelectedIndex = 0;
            tabControl1.Size = new Size(708, 383);
            tabControl1.TabIndex = 4;
            // 
            // tabPage1
            // 
            tabPage1.BackColor = SystemColors.Control;
            tabPage1.Controls.Add(panel3);
            tabPage1.Controls.Add(panel2);
            tabPage1.Controls.Add(panel1);
            tabPage1.Location = new Point(4, 24);
            tabPage1.Name = "tabPage1";
            tabPage1.Padding = new Padding(3);
            tabPage1.Size = new Size(700, 355);
            tabPage1.TabIndex = 0;
            tabPage1.Text = "tabPage1";
            // 
            // panel3
            // 
            panel3.Controls.Add(b16);
            panel3.Controls.Add(b15);
            panel3.Controls.Add(b14);
            panel3.Controls.Add(b13);
            panel3.Controls.Add(b12);
            panel3.Controls.Add(b11);
            panel3.Controls.Add(b10);
            panel3.Controls.Add(b9);
            panel3.Controls.Add(label23);
            panel3.Controls.Add(t8);
            panel3.Controls.Add(label24);
            panel3.Controls.Add(t7);
            panel3.Controls.Add(label25);
            panel3.Controls.Add(t6);
            panel3.Controls.Add(label26);
            panel3.Controls.Add(t5);
            panel3.Controls.Add(label19);
            panel3.Controls.Add(t4);
            panel3.Controls.Add(label20);
            panel3.Controls.Add(t3);
            panel3.Controls.Add(label21);
            panel3.Controls.Add(t2);
            panel3.Controls.Add(label22);
            panel3.Controls.Add(t1);
            panel3.Controls.Add(label11);
            panel3.Controls.Add(label12);
            panel3.Controls.Add(label13);
            panel3.Controls.Add(label14);
            panel3.Controls.Add(label15);
            panel3.Controls.Add(label16);
            panel3.Controls.Add(label17);
            panel3.Controls.Add(label18);
            panel3.Controls.Add(label7);
            panel3.Controls.Add(b8);
            panel3.Controls.Add(label8);
            panel3.Controls.Add(b7);
            panel3.Controls.Add(label9);
            panel3.Controls.Add(b6);
            panel3.Controls.Add(label10);
            panel3.Controls.Add(b5);
            panel3.Controls.Add(label5);
            panel3.Controls.Add(b4);
            panel3.Controls.Add(label6);
            panel3.Controls.Add(b3);
            panel3.Controls.Add(label4);
            panel3.Controls.Add(b2);
            panel3.Controls.Add(label3);
            panel3.Controls.Add(b1);
            panel3.Location = new Point(221, 3);
            panel3.Name = "panel3";
            panel3.Size = new Size(476, 298);
            panel3.TabIndex = 8;
            // 
            // b16
            // 
            b16.Location = new Point(366, 158);
            b16.Name = "b16";
            b16.Size = new Size(100, 23);
            b16.TabIndex = 43;
            // 
            // b15
            // 
            b15.Location = new Point(366, 136);
            b15.Name = "b15";
            b15.Size = new Size(100, 23);
            b15.TabIndex = 41;
            // 
            // b14
            // 
            b14.Location = new Point(366, 114);
            b14.Name = "b14";
            b14.Size = new Size(100, 23);
            b14.TabIndex = 39;
            // 
            // b13
            // 
            b13.Location = new Point(366, 92);
            b13.Name = "b13";
            b13.Size = new Size(100, 23);
            b13.TabIndex = 37;
            // 
            // b12
            // 
            b12.Location = new Point(366, 70);
            b12.Name = "b12";
            b12.Size = new Size(100, 23);
            b12.TabIndex = 35;
            // 
            // b11
            // 
            b11.Location = new Point(366, 48);
            b11.Name = "b11";
            b11.Size = new Size(100, 23);
            b11.TabIndex = 33;
            // 
            // b10
            // 
            b10.Location = new Point(366, 26);
            b10.Name = "b10";
            b10.Size = new Size(100, 23);
            b10.TabIndex = 31;
            // 
            // b9
            // 
            b9.Location = new Point(366, 4);
            b9.Name = "b9";
            b9.Size = new Size(100, 23);
            b9.TabIndex = 29;
            // 
            // label23
            // 
            label23.AutoSize = true;
            label23.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label23.Location = new Point(242, 273);
            label23.Name = "label23";
            label23.Size = new Size(124, 17);
            label23.TabIndex = 60;
            label23.Text = "Battery Temp 8     :";
            // 
            // t8
            // 
            t8.Location = new Point(366, 272);
            t8.Name = "t8";
            t8.Size = new Size(100, 23);
            t8.TabIndex = 59;
            // 
            // label24
            // 
            label24.AutoSize = true;
            label24.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label24.Location = new Point(242, 251);
            label24.Name = "label24";
            label24.Size = new Size(124, 17);
            label24.TabIndex = 58;
            label24.Text = "Battery Temp 7     :";
            // 
            // t7
            // 
            t7.Location = new Point(366, 250);
            t7.Name = "t7";
            t7.Size = new Size(100, 23);
            t7.TabIndex = 57;
            // 
            // label25
            // 
            label25.AutoSize = true;
            label25.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label25.Location = new Point(242, 229);
            label25.Name = "label25";
            label25.Size = new Size(124, 17);
            label25.TabIndex = 56;
            label25.Text = "Battery Temp 6     :";
            // 
            // t6
            // 
            t6.Location = new Point(366, 228);
            t6.Name = "t6";
            t6.Size = new Size(100, 23);
            t6.TabIndex = 55;
            // 
            // label26
            // 
            label26.AutoSize = true;
            label26.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label26.Location = new Point(242, 207);
            label26.Name = "label26";
            label26.Size = new Size(124, 17);
            label26.TabIndex = 54;
            label26.Text = "Battery Temp 5     :";
            // 
            // t5
            // 
            t5.Location = new Point(366, 206);
            t5.Name = "t5";
            t5.Size = new Size(100, 23);
            t5.TabIndex = 53;
            // 
            // label19
            // 
            label19.AutoSize = true;
            label19.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label19.Location = new Point(3, 273);
            label19.Name = "label19";
            label19.Size = new Size(124, 17);
            label19.TabIndex = 52;
            label19.Text = "Battery Temp 4     :";
            // 
            // t4
            // 
            t4.Location = new Point(127, 272);
            t4.Name = "t4";
            t4.Size = new Size(100, 23);
            t4.TabIndex = 51;
            // 
            // label20
            // 
            label20.AutoSize = true;
            label20.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label20.Location = new Point(3, 251);
            label20.Name = "label20";
            label20.Size = new Size(124, 17);
            label20.TabIndex = 50;
            label20.Text = "Battery Temp 3     :";
            // 
            // t3
            // 
            t3.Location = new Point(127, 250);
            t3.Name = "t3";
            t3.Size = new Size(100, 23);
            t3.TabIndex = 49;
            // 
            // label21
            // 
            label21.AutoSize = true;
            label21.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label21.Location = new Point(3, 229);
            label21.Name = "label21";
            label21.Size = new Size(124, 17);
            label21.TabIndex = 48;
            label21.Text = "Battery Temp 2     :";
            // 
            // t2
            // 
            t2.Location = new Point(127, 228);
            t2.Name = "t2";
            t2.Size = new Size(100, 23);
            t2.TabIndex = 47;
            // 
            // label22
            // 
            label22.AutoSize = true;
            label22.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label22.Location = new Point(3, 207);
            label22.Name = "label22";
            label22.Size = new Size(122, 17);
            label22.TabIndex = 46;
            label22.Text = "Battery Temp 1     :";
            // 
            // t1
            // 
            t1.Location = new Point(127, 206);
            t1.Name = "t1";
            t1.Size = new Size(100, 23);
            t1.TabIndex = 45;
            // 
            // label11
            // 
            label11.AutoSize = true;
            label11.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label11.Location = new Point(242, 159);
            label11.Name = "label11";
            label11.Size = new Size(125, 17);
            label11.TabIndex = 44;
            label11.Text = "Battery Voltage 16 :";
            // 
            // label12
            // 
            label12.AutoSize = true;
            label12.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label12.Location = new Point(242, 137);
            label12.Name = "label12";
            label12.Size = new Size(125, 17);
            label12.TabIndex = 42;
            label12.Text = "Battery Voltage 15 :";
            // 
            // label13
            // 
            label13.AutoSize = true;
            label13.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label13.Location = new Point(242, 115);
            label13.Name = "label13";
            label13.Size = new Size(125, 17);
            label13.TabIndex = 40;
            label13.Text = "Battery Voltage 14 :";
            // 
            // label14
            // 
            label14.AutoSize = true;
            label14.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label14.Location = new Point(242, 93);
            label14.Name = "label14";
            label14.Size = new Size(125, 17);
            label14.TabIndex = 38;
            label14.Text = "Battery Voltage 13 :";
            // 
            // label15
            // 
            label15.AutoSize = true;
            label15.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label15.Location = new Point(242, 71);
            label15.Name = "label15";
            label15.Size = new Size(125, 17);
            label15.TabIndex = 36;
            label15.Text = "Battery Voltage 12 :";
            // 
            // label16
            // 
            label16.AutoSize = true;
            label16.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label16.Location = new Point(242, 49);
            label16.Name = "label16";
            label16.Size = new Size(123, 17);
            label16.TabIndex = 34;
            label16.Text = "Battery Voltage 11 :";
            // 
            // label17
            // 
            label17.AutoSize = true;
            label17.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label17.Location = new Point(242, 27);
            label17.Name = "label17";
            label17.Size = new Size(125, 17);
            label17.TabIndex = 32;
            label17.Text = "Battery Voltage 10 :";
            // 
            // label18
            // 
            label18.AutoSize = true;
            label18.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label18.Location = new Point(242, 5);
            label18.Name = "label18";
            label18.Size = new Size(124, 17);
            label18.TabIndex = 30;
            label18.Text = "Battery Voltage 9  :";
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label7.Location = new Point(3, 159);
            label7.Name = "label7";
            label7.Size = new Size(124, 17);
            label7.TabIndex = 28;
            label7.Text = "Battery Voltage 8  :";
            // 
            // b8
            // 
            b8.Location = new Point(127, 158);
            b8.Name = "b8";
            b8.Size = new Size(100, 23);
            b8.TabIndex = 27;
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label8.Location = new Point(3, 137);
            label8.Name = "label8";
            label8.Size = new Size(124, 17);
            label8.TabIndex = 26;
            label8.Text = "Battery Voltage 7  :";
            // 
            // b7
            // 
            b7.Location = new Point(127, 136);
            b7.Name = "b7";
            b7.Size = new Size(100, 23);
            b7.TabIndex = 25;
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label9.Location = new Point(3, 115);
            label9.Name = "label9";
            label9.Size = new Size(124, 17);
            label9.TabIndex = 24;
            label9.Text = "Battery Voltage 6  :";
            // 
            // b6
            // 
            b6.Location = new Point(127, 114);
            b6.Name = "b6";
            b6.Size = new Size(100, 23);
            b6.TabIndex = 23;
            // 
            // label10
            // 
            label10.AutoSize = true;
            label10.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label10.Location = new Point(3, 93);
            label10.Name = "label10";
            label10.Size = new Size(124, 17);
            label10.TabIndex = 22;
            label10.Text = "Battery Voltage 5  :";
            // 
            // b5
            // 
            b5.Location = new Point(127, 92);
            b5.Name = "b5";
            b5.Size = new Size(100, 23);
            b5.TabIndex = 21;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label5.Location = new Point(3, 71);
            label5.Name = "label5";
            label5.Size = new Size(124, 17);
            label5.TabIndex = 20;
            label5.Text = "Battery Voltage 4  :";
            // 
            // b4
            // 
            b4.Location = new Point(127, 70);
            b4.Name = "b4";
            b4.Size = new Size(100, 23);
            b4.TabIndex = 19;
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label6.Location = new Point(3, 49);
            label6.Name = "label6";
            label6.Size = new Size(124, 17);
            label6.TabIndex = 18;
            label6.Text = "Battery Voltage 3  :";
            // 
            // b3
            // 
            b3.Location = new Point(127, 48);
            b3.Name = "b3";
            b3.Size = new Size(100, 23);
            b3.TabIndex = 17;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label4.Location = new Point(3, 27);
            label4.Name = "label4";
            label4.Size = new Size(124, 17);
            label4.TabIndex = 16;
            label4.Text = "Battery Voltage 2  :";
            // 
            // b2
            // 
            b2.Location = new Point(127, 26);
            b2.Name = "b2";
            b2.Size = new Size(100, 23);
            b2.TabIndex = 15;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            label3.Location = new Point(3, 5);
            label3.Name = "label3";
            label3.Size = new Size(122, 17);
            label3.TabIndex = 14;
            label3.Text = "Battery Voltage 1  :";
            // 
            // b1
            // 
            b1.Location = new Point(127, 4);
            b1.Name = "b1";
            b1.Size = new Size(100, 23);
            b1.TabIndex = 0;
            // 
            // panel2
            // 
            panel2.Controls.Add(alivecounter);
            panel2.Controls.Add(sw_version);
            panel2.Location = new Point(3, 307);
            panel2.Name = "panel2";
            panel2.Size = new Size(694, 42);
            panel2.TabIndex = 7;
            // 
            // alivecounter
            // 
            alivecounter.AutoSize = true;
            alivecounter.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            alivecounter.Location = new Point(558, 12);
            alivecounter.Name = "alivecounter";
            alivecounter.Size = new Size(101, 17);
            alivecounter.TabIndex = 14;
            alivecounter.Text = "Alive Counter : ";
            // 
            // sw_version
            // 
            sw_version.AutoSize = true;
            sw_version.Font = new Font("Segoe UI Semibold", 9.75F, FontStyle.Bold, GraphicsUnit.Point, 162);
            sw_version.Location = new Point(3, 12);
            sw_version.Name = "sw_version";
            sw_version.Size = new Size(116, 17);
            sw_version.TabIndex = 12;
            sw_version.Text = "Software Version :";
            // 
            // panel1
            // 
            panel1.Controls.Add(batterymintemp);
            panel1.Controls.Add(batterymaxtemp);
            panel1.Controls.Add(batteryminv);
            panel1.Controls.Add(batterymaxv);
            panel1.Controls.Add(batcount);
            panel1.Controls.Add(batchem);
            panel1.Controls.Add(batteryimg);
            panel1.Controls.Add(temperature);
            panel1.Controls.Add(soc);
            panel1.Controls.Add(summvoltage);
            panel1.Location = new Point(3, 3);
            panel1.Name = "panel1";
            panel1.Size = new Size(212, 298);
            panel1.TabIndex = 6;
            // 
            // batterymintemp
            // 
            batterymintemp.AutoSize = true;
            batterymintemp.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 162);
            batterymintemp.Location = new Point(4, 264);
            batterymintemp.Name = "batterymintemp";
            batterymintemp.Size = new Size(174, 21);
            batterymintemp.TabIndex = 11;
            batterymintemp.Text = "Battery Min Temp : °C";
            // 
            // batterymaxtemp
            // 
            batterymaxtemp.AutoSize = true;
            batterymaxtemp.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 162);
            batterymaxtemp.Location = new Point(4, 243);
            batterymaxtemp.Name = "batterymaxtemp";
            batterymaxtemp.Size = new Size(177, 21);
            batterymaxtemp.TabIndex = 10;
            batterymaxtemp.Text = "Battery Max Temp : °C";
            // 
            // batteryminv
            // 
            batteryminv.AutoSize = true;
            batteryminv.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 162);
            batteryminv.Location = new Point(4, 222);
            batteryminv.Name = "batteryminv";
            batteryminv.Size = new Size(138, 21);
            batteryminv.TabIndex = 9;
            batteryminv.Text = "Battery Min V : V";
            // 
            // batterymaxv
            // 
            batterymaxv.AutoSize = true;
            batterymaxv.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 162);
            batterymaxv.Location = new Point(4, 201);
            batterymaxv.Name = "batterymaxv";
            batterymaxv.Size = new Size(141, 21);
            batterymaxv.TabIndex = 8;
            batterymaxv.Text = "Battery Max V : V";
            // 
            // batcount
            // 
            batcount.AutoSize = true;
            batcount.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 162);
            batcount.Location = new Point(4, 180);
            batcount.Name = "batcount";
            batcount.Size = new Size(128, 21);
            batcount.TabIndex = 7;
            batcount.Text = "Battery Count : ";
            // 
            // batchem
            // 
            batchem.AutoSize = true;
            batchem.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 162);
            batchem.Location = new Point(4, 160);
            batchem.Name = "batchem";
            batchem.Size = new Size(160, 21);
            batchem.TabIndex = 6;
            batchem.Text = "Battery Chemistry : ";
            // 
            // temperature
            // 
            temperature.AutoSize = true;
            temperature.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 162);
            temperature.Location = new Point(4, 140);
            temperature.Name = "temperature";
            temperature.Size = new Size(139, 21);
            temperature.TabIndex = 4;
            temperature.Text = "Temperature :  °C";
            // 
            // soc
            // 
            soc.AutoSize = true;
            soc.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point, 162);
            soc.Location = new Point(3, 100);
            soc.Name = "soc";
            soc.Size = new Size(65, 21);
            soc.TabIndex = 5;
            soc.Text = "SoC : %";
            // 
            // tabPage2
            // 
            tabPage2.BackColor = SystemColors.Control;
            tabPage2.Location = new Point(4, 24);
            tabPage2.Name = "tabPage2";
            tabPage2.Padding = new Padding(3);
            tabPage2.Size = new Size(700, 355);
            tabPage2.TabIndex = 1;
            tabPage2.Text = "tabPage2";
            // 
            // data_pull_timer
            // 
            data_pull_timer.Tick += data_pull_timer_Tick;
            // 
            // monitor_form
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(709, 388);
            Controls.Add(tabControl1);
            Name = "monitor_form";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "SMART BMS";
            FormClosed += monitor_form_FormClosed;
            Load += monitor_form_Load;
            ((System.ComponentModel.ISupportInitialize)batteryimg).EndInit();
            tabControl1.ResumeLayout(false);
            tabPage1.ResumeLayout(false);
            panel3.ResumeLayout(false);
            panel3.PerformLayout();
            panel2.ResumeLayout(false);
            panel2.PerformLayout();
            panel1.ResumeLayout(false);
            panel1.PerformLayout();
            ResumeLayout(false);
        }

        #endregion
        private PictureBox batteryimg;
        private Label summvoltage;
        private TabControl tabControl1;
        private TabPage tabPage1;
        private TabPage tabPage2;
        private Panel panel1;
        private Label temperature;
        private Label soc;
        private Label batterymaxtemp;
        private Label batteryminv;
        private Label batterymaxv;
        private Label batcount;
        private Label batchem;
        private Panel panel3;
        private Panel panel2;
        private Label sw_version;
        private Label batterymintemp;
        private Label label23;
        private TextBox t8;
        private Label label24;
        private TextBox t7;
        private Label label25;
        private TextBox t6;
        private Label label26;
        private TextBox t5;
        private Label label19;
        private TextBox t4;
        private Label label20;
        private TextBox t3;
        private Label label21;
        private TextBox t2;
        private Label label22;
        private TextBox t1;
        private Label label11;
        private TextBox b16;
        private Label label12;
        private TextBox b15;
        private Label label13;
        private TextBox b14;
        private Label label14;
        private TextBox b13;
        private Label label15;
        private TextBox b12;
        private Label label16;
        private TextBox b11;
        private Label label17;
        private TextBox b10;
        private Label label18;
        private TextBox b9;
        private Label label7;
        private TextBox b8;
        private Label label8;
        private TextBox b7;
        private Label label9;
        private TextBox b6;
        private Label label10;
        private TextBox b5;
        private Label label5;
        private TextBox b4;
        private Label label6;
        private TextBox b3;
        private Label label4;
        private TextBox b2;
        private Label label3;
        private TextBox b1;
        private Label alivecounter;
        private System.Windows.Forms.Timer data_pull_timer;
    }
}