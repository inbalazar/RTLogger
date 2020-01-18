using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
//using Telerik.QuickStart.WinControls;
using Telerik.WinControls;
using Telerik.WinControls.Themes;
using Telerik.WinControls.UI;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Runtime.InteropServices;

namespace WindowsFormsApplication1
{
    enum LoggerRTSeverity
    {
        LoggerRTSeverityCritical,
        LoggerRTSeverityError,
        LoggerRTSeverityWarn,
        LoggerRTSeverityLog,
        LoggerRTSeverityFlow,
        LoggerRTSeverityInfo,
        LoggerRTSeverityDebug
    };

    enum LoggerRTDevice
    {
        LoggerRTCcu,
        //add more
    };

    struct element
    {
        LoggerRTSeverity[] severityMsg;
        string textMsg;
    };

    struct dataSend
    {
        element elementMsg;
        LoggerRTDevice deviceMsg;
    };
    
    public partial class Form1 : Form
    {
        UdpClient Client = new UdpClient(5001); // port number
        string data = "";
        public Form1()
        {
           
            InitializeComponent();


            this.dataGridView1.ShowGroupPanel = true;
            this.dataGridView1.BackColor = Color.Transparent;
            this.dataGridView1.ReadOnly = true;
            Client.BeginReceive(new AsyncCallback(recV), null);
        }



        dataSend ByteArrayToNewStuff(byte[] bytes)
        {
            GCHandle handle = GCHandle.Alloc(bytes, GCHandleType.Pinned);
            try
            {
                dataSend stuff = (dataSend)Marshal.PtrToStructure(handle.AddrOfPinnedObject(), typeof(dataSend));
            }
            finally
            {
                handle.Free();
            }
            return stuff;
        }


        public void recV(IAsyncResult res)
        {
            IPEndPoint RemoteIP = new IPEndPoint(IPAddress.Any, 60240);
            Byte[] receivd = Client.EndReceive(res, ref RemoteIP);

            var index = 0;

            var severityMsg = (LoggerRTSeverity)BitConverter.ToInt32(receivd, index);
            index += 4;
            var endStringIndex = Array.IndexOf(receivd, (byte)0, index); // TODO: make sure > index;
            var textMsg = Encoding.UTF8.GetString(receivd, index, endStringIndex - index);
            index = endStringIndex + 1;
            //dataSend stdataSend = (*dataSend)receivd;


             //var result = fromBytes<Message>(receivd);

            //data = Encoding.UTF8.GetString(receivd);
         //   data = ByteArrayToNewStuff(receivd);
            Console.WriteLine(textMsg);

            //Console.WriteLine(receivd);


            //Console.WriteLine(data);
            // data = BytesToStringConverted(receivd);
            // Console.WriteLine(data);
            // to avoid cross-threading we use Method Invoker
            this.Invoke(new MethodInvoker(delegate {

                //richTextBox1.Text += "\nRecived data: " + data;
                dt.Rows.Add("0000", "Engine", severityMsg, textMsg);
                
                setColor();

            }
            ));
            Client.BeginReceive(new AsyncCallback(recV), null);



        }
        DataTable dt = new DataTable();
        private dataSend stuff;

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
          //  AquaTheme theme = new AquaTheme();
          //  ThemeResolutionService.ApplicationThemeName = "Aqua";
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void DataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void Form1_Load_1(object sender, EventArgs e)
        {

            comboBox1.Text = "CRITICAL";
            comboBox2.Text = "CRITICAL";
            comboBox3.Text = "CRITICAL";
            comboBox4.Text = "CRITICAL";
            comboBox5.Text = "CRITICAL";
            comboBox6.Text = "CRITICAL";
            comboBox7.Text = "CRITICAL";
            comboBox8.Text = "CRITICAL";
            comboBox9.Text = "CRITICAL";
            comboBox10.Text = "CRITICAL";


            dt.Columns.Add("Cycle", typeof(int));
            dt.Columns.Add("Services", typeof(string));
            dt.Columns.Add("Severity", typeof(string));

            dt.Columns.Add("Message", typeof(string));

            //Type columnType = dt.Columns["MSG"].DataType;


            this.dataGridView1.DataSource = dt;
            this.Controls.Add(this.dataGridView1);

            dataGridView1.Columns[0].Width = 80;
            dataGridView1.Columns[1].Width = 80;
            dataGridView1.Columns[2].Width = 80;

            dataGridView1.Columns[0].TextAlignment = ContentAlignment.MiddleLeft;



            reloadTable(dt);

           //dataGridView1.CellFormatting += new DataGridViewCellFormattingEventHandler(dataGridView1_CellFormatting);










        }


        public void txtSearch_KeyPress(object sender, KeyPressEventArgs e)
        {
            
                DataView dv = dt.DefaultView;
                //Console.WriteLine(textBox1.Text);
                //Filter datagridview using textbox
                //Console.WriteLine(textBox1.Text);
                dv.RowFilter = string.Format("Message like '%{0}%'", textBox1.Text);
                dataGridView1.DataSource = dv.ToTable();
                setColor();


        }

        void reloadTable(DataTable dt)
        {

            dataGridView1.DataSource = dt;
            setColor();


        }

        void setColor()
        {
            this.dataGridView1.ShowGroupPanel = true;
         

            for (int y = 0; y < this.dataGridView1.RowCount; y++) 
            {
                for (int x = 0; x < this.dataGridView1.ColumnCount; x++) 
                {
                    if (Convert.ToString(this.dataGridView1.Rows[y].Cells["Severity"].Value) == "CRITICAL")
                    {
           
                        this.dataGridView1.Rows[y].Cells[2].Style.ForeColor = Color.Red;
                    }
                    if (Convert.ToString(this.dataGridView1.Rows[y].Cells["Severity"].Value) == "ERROR")
                    {

                        this.dataGridView1.Rows[y].Cells[2].Style.ForeColor = Color.Blue;
                    }
                    if (Convert.ToString(this.dataGridView1.Rows[y].Cells["Severity"].Value) == "WARN")
                    {

                        this.dataGridView1.Rows[y].Cells[2].Style.ForeColor = Color.DarkOrange;
                    }
                    if (Convert.ToString(this.dataGridView1.Rows[y].Cells["Severity"].Value) == "INFO")
                    {

                        this.dataGridView1.Rows[y].Cells[2].Style.ForeColor = Color.Green;
                    }

                    if (Convert.ToString(this.dataGridView1.Rows[y].Cells["Severity"].Value) == "DEBUG")
                    {

                        this.dataGridView1.Rows[y].Cells[2].Style.ForeColor = Color.YellowGreen;
                    }


                }
            }


            /*
            // Crirtiacl;
            foreach (DataGridViewRow row in dataGridView1.Rows)
            {
                if (Convert.ToString(row.Cells["Severity"].Value) == "CRITICAL")
                {
                    row.DefaultCellStyle.BackColor = Color.Red;
                }

                if (Convert.ToString(row.Cells["Severity"].Value) == "ERROR")
                {
                    row.DefaultCellStyle.BackColor = Color.Red;
                }

                if (Convert.ToString(row.Cells["Severity"].Value) == "WARN")
                {
                    row.DefaultCellStyle.BackColor = Color.Yellow;
                }

                if (Convert.ToString(row.Cells["Severity"].Value) == "INFO")
                {
                    row.DefaultCellStyle.BackColor = Color.Blue;
                }

                if (Convert.ToString(row.Cells["Severity"].Value) == "DEBUG")
                {
                    row.DefaultCellStyle.BackColor = Color.Green;
                }

            }
            *
            *
            */
            //     dataGridView1.Rows[0].DefaultCellStyle.BackColor = Color.Red;
            //dataGridView1.Rows[1].DefaultCellStyle.BackColor = Color.Green;

        }

        private void Button1_Click(object sender, EventArgs e)
        {

            DataView dv = dt.DefaultView;
            //Console.WriteLine(textBox1.Text);
            //Filter datagridview using textbox
            //Console.WriteLine(textBox1.Text);
             dv.RowFilter = string.Format("Severity = '%{0}%'", textBox1.Text);
            dataGridView1.DataSource = dv.ToTable();



        }


        private void TextBox1_TextChanged(object sender, KeyPressEventArgs e)
        {


        }

        private void sortChange(object sender, EventArgs e)
        {
            setColor();
        }

        private void Label1_Click(object sender, EventArgs e)
        {

        }

        private void TableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void Label3_Click(object sender, EventArgs e)
        {

        }

        private void ListBox5_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void Label3_Click_1(object sender, EventArgs e)
        {

        }

        private void Label5_Click(object sender, EventArgs e)
        {

        }

        private void ListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void ComboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            Console.WriteLine(comboBox1.Text);
           /*
            * if (comboBox1.Text == "CRITICAL")
            {
                DataView dv = dt.DefaultView;
                dv.RowFilter = string.Format("");
                dataGridView1.DataSource = dv.ToTable();
                setColor();

            }
            if (comboBox1.Text != "CRITICAL") { 
                DataView dv = dt.DefaultView;
                //Console.WriteLine(textBox1.Text);
                //Filter datagridview using textbox
                //Console.WriteLine(textBox1.Text);
                if (comboBox1.Text == "WARN")
                {
                    dv.RowFilter = string.Format("Devices = 'Engine' and Severity = 'WARN' or Severity = 'INFO' or Severity = 'DEBUG'");
                    dataGridView1.DataSource = dv.ToTable();
                    setColor();

                }

                if (comboBox1.Text == "OFF")
                {
                    dv.RowFilter = string.Format("Devices <> 'Engine'");
                    dataGridView1.DataSource = dv.ToTable();
                    setColor();

                }

            } 
            */


        }

        private void ComboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            Console.WriteLine(comboBox2.Text);
        }

        private void ComboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            Console.WriteLine(comboBox3.Text);
        }

        private void ComboBox4_SelectedIndexChanged(object sender, EventArgs e)
        {
            Console.WriteLine(comboBox4.Text);
        }

        private void ComboBox5_SelectedIndexChanged(object sender, EventArgs e)
        {
            Console.WriteLine(comboBox5.Text);
        }

        private void ComboBox6_SelectedIndexChanged(object sender, EventArgs e)
        {
            Console.WriteLine(comboBox6.Text);
        }

        private void ComboBox7_SelectedIndexChanged(object sender, EventArgs e)
        {
            Console.WriteLine(comboBox7.Text);
        }

        private void ComboBox8_SelectedIndexChanged(object sender, EventArgs e)
        {
            Console.WriteLine(comboBox8.Text);
        }

        private void ComboBox9_SelectedIndexChanged(object sender, EventArgs e)
        {
            Console.WriteLine(comboBox9.Text);
        }
        private void ComboBox10_SelectedIndexChanged(object sender, EventArgs e)
        {
            Console.WriteLine(comboBox10.Text);
        }


        private void XuiGradientPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void Label12_Click(object sender, EventArgs e)
        {

        }

        private void XuiClock1_Click(object sender, EventArgs e)
        {

        }

        private void Label2_Click(object sender, EventArgs e)
        {

        }

        private void JFlatButton2_Click(object sender, EventArgs e)
        {

        }

        private void DataGridView1_Click(object sender, EventArgs e)
        {

        }

        private void Label1_Click_1(object sender, EventArgs e)
        {

        }

        private void dsfdsf(object sender, Telerik.WinControls.UI.Data.PositionChangedEventArgs e)
        {

        }
    }
}
