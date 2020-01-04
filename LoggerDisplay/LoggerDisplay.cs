using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace LoggerDisplay
{
    public partial class LoggerDisplay : Form
    {
        UdpClient Client = new UdpClient(5001); // port number
        string data = "";
        public LoggerDisplay()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                Client.BeginReceive(new AsyncCallback(recV), null);
            }
            catch (Exception ex)
            {
                richTextBox1.Text += ex.Message.ToString();

            }
        }

        public void recV(IAsyncResult res)
        {
            IPEndPoint RemoteIP = new IPEndPoint(IPAddress.Any, 60240);
            Byte[] receivd = Client.EndReceive(res, ref RemoteIP);
            data = Encoding.UTF8.GetString(receivd);

            // to avoid cross-threading we use Method Invoker
            this.Invoke(new MethodInvoker(delegate {
                richTextBox1.Text += "\nRecived data: " + data;

            }
            ));
            Client.BeginReceive(new AsyncCallback(recV), null);



        }

        private void RichTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void LoggerDisplay_Load(object sender, EventArgs e)
        {

        }
    }

}




