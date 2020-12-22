/*
This class is necessary because the SerialPort class included with C# Express has a method
GetPortNames that doesn't work right. The documentation even admits it doesn't work right - which is 
very unusual for Microsoft - the documentation says it reads a register key and if that key ain't right
then the results ain't right (okay, the don't use 'ain't' but gist is the same). In my test case the key had 
an orphan port name in it, so I reverted to the DeviceInfo class that I'd made earlier before the
SerialPort .NET namespace came along. 

The DevInfo class ignores the registry and looks at the ports to see what is there. 

If you are just getting started with C#, you don't want to read this since it uses all sorts of 
hard to follow techniques that violate the spirit of C# specifically and OOP in general. 
However, it does follow the usual Microsoft rule that anything that claims to be object oriented
must have 'sort of' as a prefix. 
 
This code was derived from the DevInfo.cs module in the Code Project Article: 
.NET - Diving into System Programming - Part 3
By Vladimir Afanasyev http://www.codeproject.com/csharp/DivingSysProg3.asp

Joe Pardue added the GetPorts function 7/12/05
Joe Pardue added the parsePorts function 7/14/05
Joe Pardue added the parseFriendlyPorts function 7/21/05
*/

using System;
using System.Text;
using System.Runtime.InteropServices;

namespace DevInfo
{

	class DeviceInfo
	{

		private const int DIGCF_PRESENT    = (0x00000002);
		private const int MAX_DEV_LEN = 1000;
		private const int SPDRP_FRIENDLYNAME = (0x0000000C);  // FriendlyName (R/W)
		private const int SPDRP_DEVICEDESC = (0x00000000);    // DeviceDesc (R/W)

		[StructLayout(LayoutKind.Sequential)]
			private class SP_DEVINFO_DATA
				{
				 public int cbSize;
				 public Guid  ClassGuid;
				 public int DevInst;    // DEVINST handle
				 public ulong Reserved;
				};

		[DllImport("setupapi.dll")]//
		private static extern Boolean
		  SetupDiClassGuidsFromNameA(string ClassN, ref Guid guids, 
			UInt32 ClassNameSize, ref UInt32 ReqSize);

		[DllImport("setupapi.dll")]
		private static extern IntPtr                //result HDEVINFO
		  SetupDiGetClassDevsA(ref Guid ClassGuid, UInt32 Enumerator,
			IntPtr	 hwndParent,  UInt32 Flags);

		[DllImport("setupapi.dll")]
		private static extern Boolean
		  SetupDiEnumDeviceInfo(IntPtr DeviceInfoSet, UInt32 MemberIndex,
			SP_DEVINFO_DATA	 DeviceInfoData);

		[DllImport("setupapi.dll")]
		private static extern Boolean
		  SetupDiDestroyDeviceInfoList(IntPtr DeviceInfoSet);

		[DllImport("setupapi.dll")]
		private static extern Boolean
		  SetupDiGetDeviceRegistryPropertyA(
				IntPtr DeviceInfoSet,
				SP_DEVINFO_DATA	 DeviceInfoData,
				UInt32 Property,
				UInt32   PropertyRegDataType,
				StringBuilder  PropertyBuffer,
				UInt32 PropertyBufferSize,
				IntPtr RequiredSize);


		public static int EnumerateDevices(UInt32 DeviceIndex, string ClassName, StringBuilder DeviceName)
		{
		 UInt32 RequiredSize = 0;
		 Guid guid=Guid.Empty;
		 Guid[] guids=new Guid[1];
		 IntPtr NewDeviceInfoSet;
		 SP_DEVINFO_DATA DeviceInfoData= new SP_DEVINFO_DATA();


		 bool res=SetupDiClassGuidsFromNameA(ClassName,ref guids[0],RequiredSize,ref RequiredSize);
		 if(RequiredSize==0)
			   {
				//incorrect class name:
				DeviceName=new StringBuilder("");
				return -2;
			   }

		 if(!res)
		  {
		   guids=new Guid[RequiredSize];
		   res=SetupDiClassGuidsFromNameA(ClassName,ref guids[0],RequiredSize,ref RequiredSize);

		   if(!res || RequiredSize==0)
			   {
				//incorrect class name:
				DeviceName=new StringBuilder("");
				return -2;
			   }
		  }

		 //get device info set for our device class
		 NewDeviceInfoSet=SetupDiGetClassDevsA(ref guids[0],0,IntPtr.Zero,DIGCF_PRESENT);
		 if( NewDeviceInfoSet.ToInt32() == -1 )
			   {
		  //device information is unavailable:
				DeviceName=new StringBuilder("");
				return -3;
			   }

			DeviceInfoData.cbSize = 28;
			//is devices exist for class
			DeviceInfoData.DevInst=0;
			DeviceInfoData.ClassGuid=System.Guid.Empty;
			DeviceInfoData.Reserved=0;

			res=SetupDiEnumDeviceInfo(NewDeviceInfoSet,
				   DeviceIndex,DeviceInfoData);
			if(!res) {
		 //no such device:
				SetupDiDestroyDeviceInfoList(NewDeviceInfoSet);
				DeviceName=new StringBuilder("");
				return -1;
			}

			DeviceName.Capacity=MAX_DEV_LEN;
			if(!SetupDiGetDeviceRegistryPropertyA(NewDeviceInfoSet,DeviceInfoData,
			SPDRP_FRIENDLYNAME,0,DeviceName,MAX_DEV_LEN,IntPtr.Zero) )
			{
			res = SetupDiGetDeviceRegistryPropertyA(NewDeviceInfoSet,
			DeviceInfoData,SPDRP_DEVICEDESC,0,DeviceName,MAX_DEV_LEN, IntPtr.Zero);
			if(!res){
			//incorrect device name:
					SetupDiDestroyDeviceInfoList(NewDeviceInfoSet);
					DeviceName=new StringBuilder("");
					return -4;
				}
		}
		 return 0;
		}

		// Joe Pardue 7/14/05
		public static string[] ParsePorts()
		{
			string str = GetPorts();

			// Maximum number of possible COM ports is 256
			// create and intialize array
			string[] strArray = new string[256];
			for(int i = 0; i < 256; i++)
			{
				strArray[i] = "";
			}

			char[] cArray = str.ToCharArray();

			int k = 0;
			int j = 0;
			for(int i = 0; i < cArray.Length; i++)
			{
				if(cArray[i] == '(')
				{
					for(j = 0; j < 8; j++)// JWP 12/20/05 changed 6 to 8 to accomodate up to COM255
					{
						if(cArray[i+j] == ')')
						{
							i+=j; 
							k++; 
							break;
						}						
						if(cArray[i+j] != '(') strArray[k] += cArray[i + j];
					}
					if(cArray[i-j+1] == 'L'){strArray[--k] = "";}// dump an Lpt port
				}
			}		
			return strArray;
		}

		// Joe Pardue 7/21/05 - gets the 'Friendly' port name
		public static string[] ParseFriendlyPorts()
		{
			string str = GetPorts();

			// Maximum number of possible COM ports is 256
			// create and intialize array
			string[] strArray = new string[256];
			for(int i = 0; i < 256; i++)
			{
				strArray[i] = "";
			}

			char[] cArray = str.ToCharArray();

			int k = 0;
			for(int i = 0; i < cArray.Length; i++)
			{
					strArray[k] += cArray[i];
					if(cArray[i] == ')') 
					{
						// Hack to get rid of LPT string
						if ( (i > 5) && (cArray[i - 4] != 'L') )
						{
							k++;
						}
						else 
						{
							strArray[k] = "";
							
						}
						i++;// skip the trailing "\n"
					}
			}

			// Debugging
			/*string temp = "";
			for(int i = 0; i < strArray.Length; i++)
			{
					temp += strArray[i];
					if(strArray[i] == ')') 
					{
						temp +=  "\n";
					}
			}
			
			System.Windows.Forms.MessageBox.Show("ParseFriendlyPorts:\n" + temp);
			*/
			return strArray;
		}


		// Joe Pardue 7/12/05
		public static string GetPorts()
		{
			StringBuilder devices=new StringBuilder("");
			UInt32 Index=0;
			int result=0;
			
			string str = "";

			while(true)
			{
				//enumerate devices of selected device class
				result=DevInfo.DeviceInfo.EnumerateDevices(Index++, "Ports", devices);
				if(result != 0) break;
				else str += devices.ToString() + "\n";
			}
			return str;
		}
	}
}
