using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

/* Unsuported */
namespace ZGWUI
{
    class NetworkRecovery
    {
        // Neighbour Table and Network Key size
        private static int NR_SIZE_NT = 16;
        private static int NR_SIZE_NETWORK_KEY = 16;

        // Buffer address
        private static int NR_START_ADDR_NETWORK_KEY = 0;
        private static int NR_START_ADDR_KEY_SEQ_NUM = NR_START_ADDR_NETWORK_KEY + NR_SIZE_NETWORK_KEY;
        private static int NR_START_ADDR_KEY_TYPE_START_ELEMENT = NR_START_ADDR_KEY_SEQ_NUM + sizeof(byte);
        private static int NR_START_ADDR_PAN_ID = NR_START_ADDR_KEY_TYPE_START_ELEMENT + sizeof(byte);
        private static int NR_START_ADDR_OUT_FRAME_COUNTER = NR_START_ADDR_PAN_ID + sizeof(short);
        private static int NR_START_ADDR_IEEE = NR_START_ADDR_OUT_FRAME_COUNTER + sizeof(int);
        private static int NR_START_ADDR_SHORT_ADDR = NR_START_ADDR_IEEE + (sizeof(long) * NR_SIZE_NT);
        private static int NR_START_ADDR_NUMBER_OF_NETWORK_ENTRIES = NR_START_ADDR_SHORT_ADDR + (sizeof(short) * NR_SIZE_NT);
        private static int NR_START_ADDR_CHANNEL = NR_START_ADDR_NUMBER_OF_NETWORK_ENTRIES + sizeof(short);

        private ulong[] alIeeeAddress = new ulong[NR_SIZE_NT];
        private uint iOutFrameCounter;
        private ushort sPanID;
        private ushort[] asShortAddress = new ushort[NR_SIZE_NT];
        private ushort sNumberOfNTEntries;
        private byte bChannel;
        private byte[] abNetworkKey = new byte[NR_SIZE_NETWORK_KEY];
        private byte bKeySeqNum;
        private byte bKeyType;


        public NetworkRecovery()
        {

        }

        public override string ToString()
        {
            string attributes = "";

            attributes += "  Pan ID: 0x" + sPanID.ToString("X4") + "\n";
            attributes += "  Channel: 0x" + bChannel.ToString("X4") + "\n";
            attributes += "  Out Frame Counter: 0x" + iOutFrameCounter.ToString("X4") + "\n";
            for (int i = 0; i < NR_SIZE_NETWORK_KEY; i++)
            {
                attributes += "  Network Key: 0x" + abNetworkKey[i].ToString("X1");
            }

            attributes += "  Key Sequence Num: 0x" + bKeySeqNum.ToString("X2") + "\n";
            attributes += "  Key Type: 0x" + bKeyType.ToString("X2") + "\n";
            attributes += "  Number of NT Entries: 0x" + sNumberOfNTEntries.ToString("X4") + "\n";
            for (int i = 0; i < NR_SIZE_NT; i++)
            {
                attributes += "  Short Address: 0x" + asShortAddress[i].ToString("X4");
                attributes += "  IEEE Address: 0x" + alIeeeAddress[i].ToString("X16");
                attributes += "\n";
            }

            return attributes;
        }
        public int iGetSize()
        {
            int size = 0;

            size = alIeeeAddress.Length * sizeof(long);
            size += System.Runtime.InteropServices.Marshal.SizeOf(iOutFrameCounter);
            size += System.Runtime.InteropServices.Marshal.SizeOf(sPanID);
            size += asShortAddress.Length * sizeof(short);
            size += System.Runtime.InteropServices.Marshal.SizeOf(bChannel);
            size += System.Runtime.InteropServices.Marshal.SizeOf(sNumberOfNTEntries);
            size += abNetworkKey.Length * sizeof(byte);
            size += System.Runtime.InteropServices.Marshal.SizeOf(bKeySeqNum);
            size += System.Runtime.InteropServices.Marshal.SizeOf(bKeyType);

            return size;
        }

        public void NetworkRecoveryParseBuffer(byte[] bNetworkRecoveryBuff)
        {
            for (int i = 0; i < NR_SIZE_NT; i++)
            {
                alIeeeAddress[i] = bNetworkRecoveryBuff[(NR_START_ADDR_IEEE + (sizeof(long) * i))];
                alIeeeAddress[i] <<= 8;
                alIeeeAddress[i] |= bNetworkRecoveryBuff[1 + (NR_START_ADDR_IEEE + (sizeof(long) * i))];
                alIeeeAddress[i] <<= 8;
                alIeeeAddress[i] |= bNetworkRecoveryBuff[2 + (NR_START_ADDR_IEEE + (sizeof(long) * i))];
                alIeeeAddress[i] <<= 8;
                alIeeeAddress[i] |= bNetworkRecoveryBuff[3 + (NR_START_ADDR_IEEE + (sizeof(long) * i))];
                alIeeeAddress[i] <<= 8;
                alIeeeAddress[i] |= bNetworkRecoveryBuff[4 + (NR_START_ADDR_IEEE + (sizeof(long) * i))];
                alIeeeAddress[i] <<= 8;
                alIeeeAddress[i] |= bNetworkRecoveryBuff[5 + (NR_START_ADDR_IEEE + (sizeof(long) * i))];
                alIeeeAddress[i] <<= 8;
                alIeeeAddress[i] |= bNetworkRecoveryBuff[6 + (NR_START_ADDR_IEEE + (sizeof(long) * i))];
                alIeeeAddress[i] <<= 8;
                alIeeeAddress[i] |= bNetworkRecoveryBuff[7 + (NR_START_ADDR_IEEE + (sizeof(long) * i))];
            }

            for (int i = 0; i < NR_SIZE_NT; i++)
            {
                asShortAddress[i] = bNetworkRecoveryBuff[(NR_START_ADDR_SHORT_ADDR + (sizeof(short) * i))];
                asShortAddress[i] <<= 8;
                asShortAddress[i] |= bNetworkRecoveryBuff[1 + (NR_START_ADDR_SHORT_ADDR + (sizeof(short) * i))];
            }

            iOutFrameCounter = bNetworkRecoveryBuff[NR_START_ADDR_OUT_FRAME_COUNTER];
            iOutFrameCounter <<= 8;
            iOutFrameCounter |= bNetworkRecoveryBuff[NR_START_ADDR_OUT_FRAME_COUNTER + 1];
            iOutFrameCounter <<= 8;
            iOutFrameCounter |= bNetworkRecoveryBuff[NR_START_ADDR_OUT_FRAME_COUNTER + 2];
            iOutFrameCounter <<= 8;
            iOutFrameCounter |= bNetworkRecoveryBuff[NR_START_ADDR_OUT_FRAME_COUNTER + 3];

            sPanID = bNetworkRecoveryBuff[NR_START_ADDR_PAN_ID];
            sPanID <<= 8;
            sPanID |= bNetworkRecoveryBuff[NR_START_ADDR_PAN_ID + 1];

            sNumberOfNTEntries = bNetworkRecoveryBuff[NR_START_ADDR_NUMBER_OF_NETWORK_ENTRIES];
            sNumberOfNTEntries <<= 8;
            sNumberOfNTEntries |= bNetworkRecoveryBuff[NR_START_ADDR_NUMBER_OF_NETWORK_ENTRIES + 1];

            bChannel = bNetworkRecoveryBuff[NR_START_ADDR_CHANNEL];

            for (int i = 0; i < NR_SIZE_NETWORK_KEY; i++)
            {
                abNetworkKey[i] = bNetworkRecoveryBuff[NR_START_ADDR_NETWORK_KEY + i];
            }

            bKeySeqNum = bNetworkRecoveryBuff[NR_START_ADDR_KEY_SEQ_NUM];
            bKeyType = bNetworkRecoveryBuff[NR_START_ADDR_KEY_TYPE_START_ELEMENT];
        }

        public void NetworkRecoveryConstructBuffer(ref byte[] bNetworkRecoveryBuff)
        {
            for (int i = 0; i < NR_SIZE_NT; i++)
            {
                bNetworkRecoveryBuff[(NR_START_ADDR_IEEE + (sizeof(long) * i))] = (byte)(alIeeeAddress[i] >> 56);
                bNetworkRecoveryBuff[1 + (NR_START_ADDR_IEEE + (sizeof(long) * i))] = (byte)(alIeeeAddress[i] >> 48);
                bNetworkRecoveryBuff[2 + (NR_START_ADDR_IEEE + (sizeof(long) * i))] = (byte)(alIeeeAddress[i] >> 40);
                bNetworkRecoveryBuff[3 + (NR_START_ADDR_IEEE + (sizeof(long) * i))] = (byte)(alIeeeAddress[i] >> 32);
                bNetworkRecoveryBuff[4 + (NR_START_ADDR_IEEE + (sizeof(long) * i))] = (byte)(alIeeeAddress[i] >> 24);
                bNetworkRecoveryBuff[5 + (NR_START_ADDR_IEEE + (sizeof(long) * i))] = (byte)(alIeeeAddress[i] >> 16);
                bNetworkRecoveryBuff[6 + (NR_START_ADDR_IEEE + (sizeof(long) * i))] = (byte)(alIeeeAddress[i] >> 8);
                bNetworkRecoveryBuff[7 + (NR_START_ADDR_IEEE + (sizeof(long) * i))] = (byte)(alIeeeAddress[i]);
            }

            for (int i = 0; i < NR_SIZE_NT; i++)
            {
                bNetworkRecoveryBuff[(NR_START_ADDR_SHORT_ADDR + (sizeof(short) * i))] = (byte)(asShortAddress[i] >> 8);
                bNetworkRecoveryBuff[1 + (NR_START_ADDR_SHORT_ADDR + (sizeof(short) * i))] = (byte)asShortAddress[i];
            }

            bNetworkRecoveryBuff[NR_START_ADDR_OUT_FRAME_COUNTER] = (byte)(iOutFrameCounter >> 24);
            bNetworkRecoveryBuff[1 + NR_START_ADDR_OUT_FRAME_COUNTER] = (byte)(iOutFrameCounter >> 16);
            bNetworkRecoveryBuff[2 + NR_START_ADDR_OUT_FRAME_COUNTER] = (byte)(iOutFrameCounter >> 8);
            bNetworkRecoveryBuff[3 + NR_START_ADDR_OUT_FRAME_COUNTER] = (byte)iOutFrameCounter;

            bNetworkRecoveryBuff[NR_START_ADDR_PAN_ID] = (byte)(sPanID >> 8);
            bNetworkRecoveryBuff[1 + NR_START_ADDR_PAN_ID] = (byte)sPanID;

            bNetworkRecoveryBuff[NR_START_ADDR_NUMBER_OF_NETWORK_ENTRIES] = (byte)(sNumberOfNTEntries >> 8);
            bNetworkRecoveryBuff[1 + NR_START_ADDR_NUMBER_OF_NETWORK_ENTRIES] = (byte)sNumberOfNTEntries;

            bNetworkRecoveryBuff[NR_START_ADDR_CHANNEL] = (byte)bChannel;

            for (int i = 0; i < NR_SIZE_NETWORK_KEY; i++)
            {
                bNetworkRecoveryBuff[NR_START_ADDR_NETWORK_KEY + i] = abNetworkKey[i];
            }

            bNetworkRecoveryBuff[NR_START_ADDR_KEY_SEQ_NUM] = (byte)bKeySeqNum;

            bNetworkRecoveryBuff[NR_START_ADDR_KEY_TYPE_START_ELEMENT] = (byte)bKeyType;
        }

        public void NetworkRecoverySetOutFrameCounter(uint iTempOutFrameCounter)
        {
            iOutFrameCounter = iTempOutFrameCounter;
        }

    }
}
