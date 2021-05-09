using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using DevInfo;

namespace PortSet
{
    public partial class PortSettings : Form
    {
        public PortSettings()
        {
            InitializeComponent();

            // Get a list of the Serial port names
            string[] ports = GetPorts();

            int i = 0;
            foreach (string s in ports)
            {
                if (s != "")
                {
                    listBoxPorts.Items.Insert(i++, s);
                }
            }

            // Initialize baud rates in combobox
            comboBoxBaudRate.Items.AddRange(new object[] { "9600", "19200", "38400", "115200", "250000", "500000", "1000000" });

            // Set available data bits
            comboBoxDataBits.Items.Add("7");
            comboBoxDataBits.Items.Add("8");

            // Set parity types
            foreach (string s in Enum.GetNames(typeof(Parity)))
            {
                comboBoxParity.Items.Add(s);
            }

            // Set stop bits
            comboBoxStopBits.Items.Add("None");
            comboBoxStopBits.Items.Add("1");
            comboBoxStopBits.Items.Add("2");

            // Set flow control
            comboBoxFlowControl.Items.Add("None");
            comboBoxFlowControl.Items.Add("RTS/CTS");
            comboBoxFlowControl.Items.Add("Xon/Xoff");

            // Set default values
            GetCOM(0);
            comboBoxBaudRate.Text = "1000000";
            comboBoxDataBits.Text = "8";
            comboBoxParity.Text = "None";
            comboBoxStopBits.Text = "1";
            comboBoxFlowControl.Text = "None";
        }

        private string SelectedPort = "";
        public string selectedPort
        {
            get
            {
                return SelectedPort;
            }
            set
            {
                SelectedPort = value;
                //labelPort.Text
            }
        }

        private int SelectedBaudRate;
        public int selectedBaudRate
        {
            get
            {
                return SelectedBaudRate;
            }
            set
            {
                SelectedBaudRate = value;
                comboBoxBaudRate.Text = value.ToString();
            }
        }

        private void comboBoxBaudRate_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            selectedBaudRate = Convert.ToInt32(comboBoxBaudRate.Items[comboBoxBaudRate.SelectedIndex]);
        }

        #region Get Port Name
        // We don't use the GetPortNames method of the SerialPort class
        // because it doesn't work right the documentation says it reads
        // a register key and if that key ain't right then the results
        // ain't right. In my test case the key had an orphan port name in it,
        // so I reverted to the DeviceInfo class that I'd made earlier before
        // the SerialPort stuff came along.
        //
        // Oh, and DON'T LOOK AT the DeviceInfo class and after you do look
        // you'll see why I said don't
        private static string[] GetPorts()
        {
            string[] strArray = DeviceInfo.ParseFriendlyPorts();//.parseFriendlyPorts();

            return strArray;
        }

        // Select the port from the list box
        private void listBoxPorts_SelectedIndexChanged(object sender, EventArgs e)
        {
            GetCOM(listBoxPorts.SelectedIndex);
        }

        // Set the selected port and display it in the label
        private void GetCOM(int index)
        {
            string[] strArray = DevInfo.DeviceInfo.ParsePorts();//.parsePorts();

            if (strArray[index] != "")
            {
                SelectedPort = strArray[index];
                //labelPort.Text = "Selected Port = " + SelectedPort;
            }
        }
        #endregion

        private void PortSettings_Load(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
        }
    }
}
