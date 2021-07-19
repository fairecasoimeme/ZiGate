using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Globalization;
using DevInfo;

namespace ListManagement
{
    public partial class ListManager : Form
    {
        public ListManager()
        {
            InitializeComponent();

        }

        public int getListCount()
        {
            return listBoxItems.Items.Count;
        }

        public string getListAsString()
        {
            String stringList = "";

            foreach (String item in listBoxItems.Items)
            {
                stringList += item.Substring(2);
            }
            return stringList;
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            string itemToAdd = textBoxItemToBeAdded.Text;
            UInt16 u16ShortAddr = 0;

            if (UInt16.TryParse(itemToAdd, NumberStyles.HexNumber, CultureInfo.CurrentCulture, out u16ShortAddr) == true)
            {

                if (-1 == listBoxItems.FindString("0x" + u16ShortAddr.ToString("X4"), 0))
                {
                    listBoxItems.Items.Add("0x" + u16ShortAddr.ToString("X4"));
                    textBoxItemToBeAdded.Text = "";
                }
                else
                {
                    // Show error message
                    MessageBox.Show("0x" + u16ShortAddr.ToString("X4") + " Already Exists");
                }
            }
            else
            {
                // Show error message
                MessageBox.Show("Invalid Parameter");
            }

        }

        private void listBoxItems_DoubleClick(object sender, EventArgs e)
        {
            listBoxItems.Items.Remove(listBoxItems.SelectedItem);
        }
    }
}
