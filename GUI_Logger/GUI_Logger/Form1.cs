using System;
using System.Text;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Linq;
using System.Threading;
using Timer = System.Threading.Timer;

namespace GUI_Logger
{
    public partial class Form1 : Form
    {
        string[] LOGGER_RT_SEVERITY_STR = { "CRITICAL", "ERROR", "WARN", "LOG", "FLOW", "INFO", "DEBUG" };
        string[] LOGGER_RT_SERVICE_STR = { "Gas", "ClimateControl", "TirePressure" };

        public const int MaxRowsForLogFile = 50;
        int numOfRows = 0;

        UdpClient Client = new UdpClient(5001); // port number

        public Form1()
        {
            
            InitializeComponent();

            this.dataGridView1.ShowGroupPanel = true;
            this.dataGridView1.BackColor = Color.Transparent;
            this.dataGridView1.ReadOnly = true;
            
            Client.BeginReceive(new AsyncCallback(recV), null);
            
            }

        public void recV(IAsyncResult res)
        {
            Thread.Sleep(100);

            IPEndPoint RemoteIP = new IPEndPoint(IPAddress.Any, 60240);
            Byte[] receivd = Client.EndReceive(res, ref RemoteIP);

            var index = 0;

            uint cycleMsg = BitConverter.ToUInt32(receivd, index);
            index += 4;
            LOGGER_RT_SEVERITY severityMsg = (LOGGER_RT_SEVERITY)BitConverter.ToInt32(receivd, index);
            index += 4;
            LOGGER_RT_SERVICE serviceMsg = (LOGGER_RT_SERVICE)BitConverter.ToInt32(receivd, index);
            index += 4;
            var endStringIndex = Array.IndexOf(receivd, (byte)0, index);
            string textMsg = Encoding.UTF8.GetString(receivd, index, endStringIndex - index);
            index = endStringIndex + 1;
            
            Console.WriteLine(cycleMsg);
            Console.WriteLine(textMsg);

            this.Invoke(new MethodInvoker(delegate {

                dt.Rows.Add(cycleMsg, LOGGER_RT_SERVICE_STR[(int)serviceMsg], LOGGER_RT_SEVERITY_STR[(int)severityMsg], textMsg);
                numOfRows++;
                reloadTable(dt);

                if (numOfRows % MaxRowsForLogFile == 0)
                {
                    AutoExportDgvToXML();
                }
            }
            ));
            Client.BeginReceive(new AsyncCallback(recV), null);

        }
        DataTable dt = new DataTable();

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
      
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


            this.dataGridView1.DataSource = dt;
            this.Controls.Add(this.dataGridView1);

            dataGridView1.Columns[0].Width = 80;
            dataGridView1.Columns[1].Width = 80;
            dataGridView1.Columns[2].Width = 80;

            dataGridView1.Columns[0].TextAlignment = ContentAlignment.MiddleLeft;

            reloadTable(dt);
        }

        public void txtSearch_KeyPress(object sender, KeyPressEventArgs e)
        {      
                DataView dv = dt.DefaultView;
              
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
                for (int x = 0; x < this.dataGridView1.RowCount; x++) 
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


                    if (Convert.ToString(this.dataGridView1.Rows[y].Cells["Severity"].Value) == "FLOW")
                    {

                        this.dataGridView1.Rows[y].Cells[2].Style.ForeColor = Color.Purple;
                    }

                }
            }
        }

        private void sortChange(object sender, EventArgs e)
        {
            setColor();
        }

        private void Label3_Click_1(object sender, EventArgs e)
        {

        }

        private void Label5_Click(object sender, EventArgs e)
        {

        }

        private void ComboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            Console.WriteLine(comboBox1.Text);

            UdpClient Client2 = new UdpClient(); 
            IPEndPoint target = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 5010);

            int selectedIndex = comboBox1.SelectedIndex;

            int[] myData = { selectedIndex, (int)LOGGER_RT_SERVICE.LOGGER_RT_GAS_SERVICE };
            int width = sizeof(int);

            int nDataIndex = 0;
            byte[] data = new byte[myData.Length * width];

            for (int i = 0; i < myData.Length; ++i)
            {
                byte[] converted = BitConverter.GetBytes(myData[i]);

                for (int j = 0; j < width; ++j)
                {
                    data[nDataIndex + j] = converted[j];
                }
                nDataIndex += width;
            }

            Client2.Send(data, data.Length, target);
        }

        private void ComboBox2_SelectedIndexChanged(object sender, Telerik.WinControls.UI.Data.PositionChangedEventArgs e)
        {
            Console.WriteLine(comboBox2.Text);

            UdpClient Client2 = new UdpClient();
            IPEndPoint target = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 5010);

            int selectedIndex = comboBox2.SelectedIndex;

            int[] myData = { selectedIndex, (int)LOGGER_RT_SERVICE.LOGGER_RT_CLIMATE_CONTROL_SERVICE };
            int width = sizeof(int);

            int nDataIndex = 0;
            byte[] data = new byte[myData.Length * width];

            for (int i = 0; i < myData.Length; ++i)
            {
                byte[] converted = BitConverter.GetBytes(myData[i]);

                for (int j = 0; j < width; ++j)
                {
                    data[nDataIndex + j] = converted[j];
                }
                nDataIndex += width;
            }

            Client2.Send(data, data.Length, target);
        }

        private void ComboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            Console.WriteLine(comboBox3.Text);

            UdpClient Client2 = new UdpClient();
            IPEndPoint target = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 5010);

            int selectedIndex = comboBox3.SelectedIndex;

            int[] myData = { selectedIndex, (int)LOGGER_RT_SERVICE.LOGGER_RT_TIRE_PRESSURE_SERVICE };
            int width = sizeof(int);

            int nDataIndex = 0;
            byte[] data = new byte[myData.Length * width];

            for (int i = 0; i < myData.Length; ++i)
            {
                byte[] converted = BitConverter.GetBytes(myData[i]);

                for (int j = 0; j < width; ++j)
                {
                    data[nDataIndex + j] = converted[j];
                }
                nDataIndex += width;
            }

            Client2.Send(data, data.Length, target);
        }

        private void ComboBox4_SelectedIndexChanged(object sender, EventArgs e)
        {
            
        }

        private void ComboBox5_SelectedIndexChanged(object sender, EventArgs e)
        {
           
        }

        private void ComboBox6_SelectedIndexChanged(object sender, EventArgs e)
        {
            
        }

        private void ComboBox7_SelectedIndexChanged(object sender, EventArgs e)
        {
            
        }

        private void ComboBox8_SelectedIndexChanged(object sender, EventArgs e)
        {
           
        }

        private void ComboBox9_SelectedIndexChanged(object sender, EventArgs e)
        {
           
        }
        private void ComboBox10_SelectedIndexChanged(object sender, EventArgs e)
        {
           
        }

        private void XuiGradientPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void Label12_Click(object sender, EventArgs e)
        {

        }

        private void DataGridView1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void backgroundWorker2_DoWork(object sender, DoWorkEventArgs e)
        {

        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            ExportDgvToXML();
        }

        private void ExportDgvToXML()
        {
            DataSet dataSet = new DataSet();
            DataTable dtCopy = dt.Copy();
            dataSet.Tables.Add(dtCopy);
            DataTable data = dataSet.Tables[0].AsEnumerable().Reverse().Take(MaxRowsForLogFile).OrderBy(row => row["cycle"]).CopyToDataTable();
            dataSet.Tables.Remove(dtCopy);
            dataSet.Tables.Add(data);

            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "XML|*.xml";
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                try
                { 
                    dataSet.WriteXml(sfd.FileName);
                    dataSet.Tables.Remove(dtCopy);
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex);
                }
            }
        }
        private void AutoExportDgvToXML()
        {
            DataSet dataSet = new DataSet();
            dataSet.Tables.Add(dt);
            DataTable data = dataSet.Tables[0].AsEnumerable().Reverse().Take(MaxRowsForLogFile).OrderBy(row => row["cycle"]).CopyToDataTable();
            dataSet.Tables.Remove(dt);
            dataSet.Tables.Add(data);

            string dateValue = DateTime.Now.ToString("ddMMyyyy") + "\\";
            if (!Directory.Exists(dateValue))
            {
                Directory.CreateDirectory(dateValue);
            }
            string dateTimeValue = dateValue + DateTime.Now.ToString("ddMMyyyyTHHmmss") + ".xml";

            try
            {
                dataSet.WriteXml(dateTimeValue);
                dataSet.Tables.Remove(dt);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
            }
        }
    }
}
