#*****************************************************************************
#*
# * MODULE:
# *
# * COMPONENT:
# *
# * $AUTHOR: Faisal Bhaiyat$
# *
# * DESCRIPTION:
# *
# * $HeadURL: $
# *
# * $Revision:  $
# *
# * $LastChangedBy:  $
# *
# * $LastChangedDate:  $
# *
# * $Id:  $
# *
# *****************************************************************************
import sys
import time
import serial
import logging
import struct
import threading
import Queue
import sqlite3

# Message types

# /* Common Commands */
E_SL_MSG_STATUS                         =   0x8000
E_SL_MSG_LOG                            =   0x8001

E_SL_MSG_DATA_INDICATION                =   0x8002

E_SL_MSG_NODE_CLUSTER_LIST              =   0x8003
E_SL_MSG_NODE_ATTRIBUTE_LIST            =   0x8004
E_SL_MSG_NODE_COMMAND_ID_LIST           =   0x8005

E_SL_MSG_GET_VERSION                    =   0x0010
E_SL_MSG_VERSION_LIST                   =   0x8010

E_SL_MSG_SET_EXT_PANID                  =   0x0020
E_SL_MSG_SET_CHANNELMASK                =   0x0021
E_SL_MSG_SET_SECURITY                   =   0x0022
E_SL_MSG_SET_DEVICETYPE                 =   0x0023
E_SL_MSG_START_NETWORK                  =   0x0024
E_SL_MSG_START_SCAN                     =   0x0025
E_SL_MSG_NETWORK_JOINED_FORMED          =   0x8024

E_SL_MSG_RESET                          =   0x0011
E_SL_MSG_ERASE_PERSISTENT_DATA          =   0x0012
E_SL_MSG_ZLL_FACTORY_NEW                =   0x0013
E_SL_MSG_BIND                           =   0x0030
E_SL_MSG_UNBIND                         =   0x0031

E_SL_MSG_NETWORK_ADDRESS_REQUEST        =   0x0040
E_SL_MSG_IEEE_ADDRESS_REQUEST           =   0x0041
E_SL_MSG_NODE_DESCRIPTOR_REQUEST        =   0x0042
E_SL_MSG_SIMPLE_DESCRIPTOR_REQUEST      =   0x0043
E_SL_MSG_SIMPLE_DESCRIPTOR_RESPONSE     =   0x8043
E_SL_MSG_POWER_DESCRIPTOR_REQUEST       =   0x0044
E_SL_MSG_ACTIVE_ENDPOINT_REQUEST        =   0x0045
E_SL_MSG_MATCH_DESCRIPTOR_REQUEST       =   0x0046
E_SL_MSG_MATCH_DESCRIPTOR_RESPONSE      =   0x8046
E_SL_MSG_MANAGEMENT_LEAVE_REQUEST       =   0x0047
E_SL_MSG_LEAVE_CONFIRMATION             =   0x8047
E_SL_MSG_LEAVE_INDICATION               =   0x8048
E_SL_MSG_PERMIT_JOINING_REQUEST         =   0x0049
E_SL_MSG_MANAGEMENT_NETWPRK_UPDATE_REQUEST =0x004A
E_SL_MSG_SYSTEM_SERVER_DISCOVERY        =   0x004B
E_SL_MSG_COMPLEX_DESCRIPTOR_REQUEST     =   0x004C
E_SL_MSG_DEVICE_ANNOUNCE                =   0x004D
E_SL_MSG_MANAGEMENT_LQI_REQUEST         =   0x004E
E_SL_MSG_MANAGEMENT_LQI_RESPONSE        =   0x804E
# /* Group Cluster */
E_SL_MSG_ADD_GROUP                      =   0x0060
E_SL_MSG_VIEW_GROUP                     =   0x0061
E_SL_MSG_GET_GROUP_MEMBERSHIP           =   0x0062
E_SL_MSG_GET_GROUP_MEMBERSHIP_RESPONSE  =   0x8062
E_SL_MSG_REMOVE_GROUP                   =   0x0063
E_SL_MSG_REMOVE_ALL_GROUPS              =   0x0064
E_SL_MSG_ADD_GROUP_IF_IDENTIFY          =   0x0065

# /* Identify Cluster */
E_SL_MSG_IDENTIFY_SEND                  =   0x0070
E_SL_MSG_IDENTIFY_QUERY                 =   0x0071

# /* Level Cluster */
E_SL_MSG_MOVE_TO_LEVEL                  =   0x0080
E_SL_MSG_MOVE_TO_LEVEL_ONOFF            =   0x0081
E_SL_MSG_MOVE_STEP                      =   0x0082
E_SL_MSG_MOVE_STOP_MOVE                 =   0x0083
E_SL_MSG_MOVE_STOP_ONOFF                =   0x0084

# /* On/Off Cluster */
E_SL_MSG_ONOFF_NOEFFECTS                =   0x0092
E_SL_MSG_ONOFF_TIMED                    =   0x0093
E_SL_MSG_ONOFF_EFFECTS                  =   0x0094

# /* Scenes Cluster */
E_SL_MSG_VIEW_SCENE                     =   0x00A0
E_SL_MSG_ADD_SCENE                      =   0x00A1
E_SL_MSG_REMOVE_SCENE                   =   0x00A2
E_SL_MSG_REMOVE_ALL_SCENES              =   0x00A3
E_SL_MSG_STORE_SCENE                    =   0x00A4
E_SL_MSG_RECALL_SCENE                   =   0x00A5
E_SL_MSG_SCENE_MEMBERSHIP_REQUEST       =   0x00A6

# /* Colour Cluster */
E_SL_MSG_MOVE_TO_HUE                    =   0x00B0
E_SL_MSG_MOVE_HUE                       =   0x00B1
E_SL_MSG_STEP_HUE                       =   0x00B2
E_SL_MSG_MOVE_TO_SATURATION             =   0x00B3
E_SL_MSG_MOVE_SATURATION                =   0x00B4
E_SL_MSG_STEP_SATURATION                =   0x00B5
E_SL_MSG_MOVE_TO_HUE_SATURATION         =   0x00B6
E_SL_MSG_MOVE_TO_COLOUR                 =   0x00B7
E_SL_MSG_MOVE_COLOUR                    =   0x00B8
E_SL_MSG_STEP_COLOUR                    =   0x00B9

# /* ZLL Commands */
# /* Touchlink */
E_SL_MSG_INITIATE_TOUCHLINK             =   0x00D0
E_SL_MSG_TOUCHLINK_STATUS               =   0x00D1
E_SL_MSG_TOUCHLINK_FACTORY_RESET        =   0x00D2
# /* Identify Cluster */
E_SL_MSG_IDENTIFY_TRIGGER_EFFECT        =   0x00E0

# /* Scenes Cluster */
E_SL_MSG_ADD_ENHANCED_SCENE             =   0x00A7
E_SL_MSG_VIEW_ENHANCED_SCENE            =   0x00A8
E_SL_MSG_COPY_SCENE                     =   0x00A9

# /* Colour Cluster */
E_SL_MSG_ENHANCED_MOVE_TO_HUE           =   0x00BA
E_SL_MSG_ENHANCED_MOVE_HUE              =   0x00BB
E_SL_MSG_ENHANCED_STEP_HUE              =   0x00BC
E_SL_MSG_ENHANCED_MOVE_TO_HUE_SATURATION =  0x00BD
E_SL_MSG_COLOUR_LOOP_SET                =   0x00BE
E_SL_MSG_STOP_MOVE_STEP                 =   0x00BF
E_SL_MSG_MOVE_TO_COLOUR_TEMPERATURE     =   0x00C0
E_SL_MSG_MOVE_COLOUR_TEMPERATURE        =   0x00C1
E_SL_MSG_STEP_COLOUR_TEMPERATURE        =   0x00C2

# /* ZHA Commands */
# /* Door Lock Cluster */
E_SL_MSG_LOCK_UNLOCK_DOOR               =   0x00F0
E_SL_MSG_READ_ATTRIBUTE_REQUEST         =   0x0100
E_SL_MSG_READ_ATTRIBUTE_RESPONSE        =   0x8100
E_SL_MSG_SAVE_PDM_RECORD                =   0x0200
E_SL_MSG_SAVE_PDM_RECORD_RESPONSE       =   0x8200
E_SL_MSG_LOAD_PDM_RECORD_REQUEST        =   0x0201
E_SL_MSG_LOAD_PDM_RECORD_RESPONSE       =   0x8201
E_SL_MSG_DELETE_PDM_RECORD              =   0x0202
E_SL_MSG_PDM_HOST_AVAILABLE             =   0x0300
E_SL_MSG_PDM_HOST_AVAILABLE_RESPONSE    =   0x8300

# Global flag to the threads
bRunning = True

class cPDMFunctionality(threading.Thread):
    """Class implementing the binary serial protrocol to the control bridge node"""
    def __init__(self,port):
        threading.Thread.__init__(self, name="PDM")              
        
        # Message queue used to pass messages between reader thread and WaitMessage()
        self.dMessageQueue = {}
        self.logger = logging.getLogger(str(port))
        # Start reader thread
        self.daemon=True
        self.start()
        
    def run(self):
        """ dedicated thread for PDM
        """        
        while(bRunning):
            try:
                # Get the message from the receiver thread, and delete the queue entry
                sData = oCB.oSL.dMessageQueue[E_SL_MSG_DELETE_PDM_RECORD].get(True, 0.1)
                del oCB.oSL.dMessageQueue[E_SL_MSG_DELETE_PDM_RECORD]
                conn = sqlite3.connect('pdm.db')
                c = conn.cursor()
                conn.text_factory = str
                c.execute('DELETE from PdmData')
                conn.commit()
                conn.close()
            except KeyError:
                try:
                # Get the message from the receiver thread, and delete the queue entry
                    sData = oCB.oSL.dMessageQueue[E_SL_MSG_LOAD_PDM_RECORD_REQUEST].get(True, 0.1)
                    del oCB.oSL.dMessageQueue[E_SL_MSG_LOAD_PDM_RECORD_REQUEST]
                    oCB.vPDMSendFunc(sData)
                except KeyError:                
                    try:
                        # Get the message from the receiver thread, and delete the queue entry
                        sData = oCB.oSL.dMessageQueue[E_SL_MSG_SAVE_PDM_RECORD].get(True, 0.1)
                        del oCB.oSL.dMessageQueue[E_SL_MSG_SAVE_PDM_RECORD]
                        conn = sqlite3.connect('pdm.db')
                        c = conn.cursor()
                        conn.text_factory = str
                        RecordId = (''.join(x.encode('hex') for x in sData[:2]))
                        CurrentCount = (''.join(x.encode('hex') for x in sData[10:14]))
                        u32NumberOfWrites = (''.join(x.encode('hex') for x in sData[6:10]))
                        u32Size = (''.join(x.encode('hex') for x in sData[2:6]))
                        dataReceived = int((''.join(x.encode('hex') for x in sData[14:18])),16)
                        #print RecordId
                        #print CurrentCount
                        #print u32NumberOfWrites
                        #print u32Size
                        #print dataReceived                           
                        sWriteData=(''.join(x.encode('hex') for x in sData[18:(dataReceived+18)]))
                        #print sWriteData
                        c.execute("SELECT * FROM PdmData WHERE PdmRecId = ?", (RecordId,))
                        data=c.fetchone()                        
                        if data is None:
                            c.execute("INSERT INTO  PdmData (PdmRecId,PdmRecSize,PersistedData) VALUES (?,?,?)",(RecordId,u32Size,sWriteData))
                        else:
                            if(int(u32NumberOfWrites)>1 ):
                                sWriteData = data[2]+sWriteData                                
                                c.execute("DELETE from PdmData WHERE PdmRecId = ? ",(RecordId,))
                                c.execute("INSERT INTO  PdmData (PdmRecId,PdmRecSize,PersistedData) VALUES (?,?,?)",(RecordId,u32Size,sWriteData))
                            else:
                                c.execute("DELETE from PdmData WHERE PdmRecId = ? ",(RecordId,))
                                c.execute("INSERT INTO  PdmData (PdmRecId,PdmRecSize,PersistedData) VALUES (?,?,?)",(RecordId,u32Size,sWriteData))
                        #print "data written\n"
                        #print sWriteData
                        #print "length %x\n" %len(sWriteData)
                        oCB.oSL._WriteMessage(E_SL_MSG_SAVE_PDM_RECORD_RESPONSE,"00")
                        conn.commit()
                        conn.close()
                    except KeyError:
                        try:
                            # Get the message from the receiver thread, and delete the queue entry
                            sData = oCB.oSL.dMessageQueue[E_SL_MSG_PDM_HOST_AVAILABLE].get(True, 0.2)
                            del oCB.oSL.dMessageQueue[E_SL_MSG_PDM_HOST_AVAILABLE]
                            oCB.oSL._WriteMessage(E_SL_MSG_PDM_HOST_AVAILABLE_RESPONSE,"00")

                        except KeyError:                      
                            self.logger.debug("nothing to do")
        self.logger.debug("Read thread terminated")

class cSerialLinkError(Exception):
    pass



class cModuleError(cSerialLinkError):
    """ Exception class for errors that the node may send back"""
    def __init__(self, statusCode, statusMessage=""):
        self.statusCode = statusCode
        self.statusMessage = statusMessage
        
        Exception.__init__(self, repr(self))
        
    def __repr__(self):
        if (self.statusCode == 0):
            raise ValueError("Not a failure code")
        elif (self.statusCode == 1):
            r = "Incorrect Parameters"
        elif (self.statusCode == 2):
            r = "Unhandled Command"
        elif (self.statusCode == 3):
            r = "Command Failed"
        elif (self.statusCode == 4):
            r = "Busy"
        elif (self.statusCode == 5):
            r = "Stack already started"
        else:
            r = "Unknown status code %d" % self.statusCode
        
        if len(self.statusMessage):
            r = ": ".join([r, self.statusMessage])
        return r

       
class cSerialLink(threading.Thread):
    """Class implementing the binary serial protrocol to the control bridge node"""
    def __init__(self, port, baudrate=115200):
        threading.Thread.__init__(self, name="SL")
        self.logger = logging.getLogger(str(port))
        self.commslogger = logging.getLogger("Comms("+str(port)+")")
        
        # Turn this up to see traffic between node and host
        self.commslogger.setLevel(logging.WARNING)
        
        self.oPort = serial.Serial(port, baudrate)
        
        # Message queue used to pass messages between reader thread and WaitMessage()
        self.dMessageQueue = {}
        
        # Start reader thread
        self.daemon=True
        self.start()


            
    def _WriteByte(self, oByte, bSpecial=False, bAscii=False):
        """ Internal function
            Send a single byte to the serial port. Takes care of byte stuffing
        """
        if bAscii:
            if not bSpecial and oByte < 0x10:
                self.commslogger.info("Ascii Host->Node: 0x02 ESC")
                oByte = struct.pack("B", oByte ^ 0x10)
                self.oPort.write(struct.pack("B", 0x02))                
            else:
                oByte = struct.pack("B", oByte)
            self.commslogger.info("Ascii Host->Node: 0x%02x", ord(oByte))
            self.oPort.write(oByte)    
        else:
            if not bSpecial and ord(oByte) < 0x10:
                self.commslogger.info("non Ascii Host->Node: 0x02 ESC")
                oByte = struct.pack("B", ord(oByte) ^ 0x10)
                self.oPort.write(struct.pack("B", 0x02))
            self.commslogger.info("non Ascii Host->Node: 0x%02x", ord(oByte))
            self.oPort.write(oByte)    


    def _WriteMessage(self, eMessageType, sData):
        """ Internal function
            Send a complete message to the serial port. Takes care of byte stuffing
            and checksum generation. eMessageType should be a 16bit message number
            sData is a string containing the packed message data 
        """
        self.logger.info("Host->Node: Message Type 0x%04x, length %d %s", eMessageType, (len(sData)),sData)

        u8Checksum = ((eMessageType >> 8) & 0xFF) ^ ((eMessageType >> 0) & 0xFF)
        u8Checksum = u8Checksum ^ (((len(sData)/2) >> 8) & 0xFF) ^ (((len(sData)/2) >> 0) & 0xFF)
        bIn=True
        for byte in sData:
            if bIn:
                u8Byte= int(byte,16)<<4 & 0xFF
                bIn=False
            else:
                u8Byte |= int(byte,16)>>0 & 0xFF          
                u8Checksum = u8Checksum ^ u8Byte
                bIn=True
            
        u16Length = len(sData)/2
        
        self._WriteByte(struct.pack("B", 0x01), True)
        self._WriteByte(struct.pack("B", (eMessageType >> 8) & 0xFF))
        self._WriteByte(struct.pack("B", (eMessageType >> 0) & 0xFF))
        self._WriteByte(struct.pack("B", (u16Length >> 8) & 0xFF))
        self._WriteByte(struct.pack("B", (u16Length >> 0) & 0xFF))
        self._WriteByte(struct.pack("B", (u8Checksum) & 0xFF))
        bIn= True
        
        for byte in sData:
            if bIn:
                u8Byte= int(byte,16)<<4 & 0xFF
                bIn=False
            else:
                u8Byte |= int(byte,16)>>0 & 0xFF                
                self._WriteByte(u8Byte,False,True)
                bIn=True
            
        self._WriteByte(struct.pack("B", 0x03), True)


    def _ReadMessage(self):
        """ Internal function
            Read a complete message from the serial port. Takes care of byte stuffing
            Length and checksum message integrity checks.
            Return tuple of message type and buffer of data.
        """
        bInEsc = False
        
        u8Checksum = 0
        eMessageType = 0
        u16Length = 0
        sData = ""
        state = 0
        while(bRunning):
            byte = self.oPort.read(1)
            #sys.stdout.write(byte)
            if True: #len(byte) > 0:
                self.commslogger.info("Node->Host: 0x%02x", ord(byte))

                if (ord(byte) == 0x01):
                    self.commslogger.debug("Start Message")
                    u8Checksum = 0
                    eMessageType = 0
                    u16Length = 0
                    sData = ""
                    state = 0
                elif (ord(byte) == 0x02):
                    self.commslogger.debug("ESC")
                    bInEsc = True
                elif (ord(byte) == 0x03):
                    self.commslogger.debug("End Message")
                    
                    if not len(sData) == u16Length:
                        self.commslogger.warning("Length mismatch (Expected %d, got %d)", u16Length, len(sData))
                        continue
                    
                    u8MyChecksum = ((eMessageType >> 8) & 0xFF) ^ ((eMessageType >> 0) & 0xFF)
                    u8MyChecksum = u8MyChecksum ^ ((u16Length >> 8) & 0xFF) ^ ((u16Length >> 0) & 0xFF)
                    for byte in sData:
                        u8MyChecksum = (u8MyChecksum ^ ord(byte)) & 0xFF
  
                    if not u8Checksum == u8MyChecksum:
                        self.commslogger.warning("Checkum mismatch (Expected 0x%02x, got 0x%02x)", u8Checksum, u8MyChecksum)
                        continue
                    self.commslogger.debug("Checksum ok")
                    return (eMessageType, sData)
                else:
                    if bInEsc:
                        bInEsc = False
                        byte = struct.pack("B", ord(byte) ^ 0x10)
                    
                    if state == 0:
                        # Type MSB
                        eMessageType = ord(byte) << 8
                        state = state + 1
                    elif state == 1:
                        eMessageType = eMessageType + ord(byte)
                        self.commslogger.debug("Message Type: 0x%04x", eMessageType)
                        state = state + 1
                    elif state == 2:
                        # Type MSB
                        u16Length = ord(byte) << 8
                        state = state + 1
                    elif state == 3:
                        u16Length = u16Length + ord(byte)
                        self.commslogger.debug("Message Length: 0x%04x", u16Length)
                        state = state + 1
                    elif state == 4:
                        u8Checksum = ord(byte)
                        self.commslogger.debug("Message Checksum: 0x%02x", u8Checksum)
                        state = state + 1
                    else:
                        self.commslogger.debug("Message Add Data: 0x%02x", ord(byte))
                        sData = sData + byte
        return (0, "")


    def run(self):
        """ Reader thread function.
            Keep reading messages from the port.
            Log messages are sent straight to the logger.
            Everything else is queued for listers that are waiting for message types via WaitMessage().
        """
        self.logger.debug("Read thread starting")
        try:
            while(bRunning):
                (eMessageType, sData) = self._ReadMessage()
                self.logger.info("Node->Host: Response 0x%04x, length %d", eMessageType, len(sData))
                
                if ((eMessageType == E_SL_MSG_LOG) or
                (eMessageType == E_SL_MSG_NODE_CLUSTER_LIST) or
                (eMessageType == E_SL_MSG_NODE_ATTRIBUTE_LIST) or
                (eMessageType == E_SL_MSG_NODE_COMMAND_ID_LIST) or
                    (eMessageType == E_SL_MSG_NETWORK_JOINED_FORMED) or
                    (eMessageType == E_SL_MSG_MATCH_DESCRIPTOR_RESPONSE) or
                    (eMessageType == E_SL_MSG_DEVICE_ANNOUNCE) or
                    (eMessageType == E_SL_MSG_READ_ATTRIBUTE_RESPONSE)or
                    (eMessageType == E_SL_MSG_GET_GROUP_MEMBERSHIP_RESPONSE) or 
                    (eMessageType == E_SL_MSG_MANAGEMENT_LQI_RESPONSE)):
                    if (eMessageType == E_SL_MSG_LOG):
                        logLevel = struct.unpack("B", sData[0])[0]
                        logLevel = ["EMERG", "ALERT", "CRIT ", "ERROR", "WARN ", "NOT  ", "INFO ", "DEBUG"][logLevel]
                        logMessage = sData[1:]
                        self.logger.info("Module: %s: %s", logLevel, logMessage)
                        self.logger.info("Module: : %s",  logMessage)
                    
                    if(eMessageType == E_SL_MSG_NODE_CLUSTER_LIST):
                        stringme= (':'.join(x.encode('hex') for x in sData))
                        self.logger.info("Node->Host: Cluster List Received %s",stringme)
                    if(eMessageType == E_SL_MSG_NODE_ATTRIBUTE_LIST):
                        self.logger.info("Node->Host: Attribute List ")

                    if(eMessageType == E_SL_MSG_NODE_COMMAND_ID_LIST):
                        self.logger.info("Node->Host: Commands List ")

                    if(eMessageType == E_SL_MSG_NETWORK_JOINED_FORMED):
                        stringme= (':'.join(x.encode('hex') for x in sData))
                        self.logger.info("Network joined/formed event received %s",stringme )

                    if((eMessageType == E_SL_MSG_MATCH_DESCRIPTOR_RESPONSE)):
                        stringme= (':'.join(x.encode('hex') for x in sData))
                        self.logger.info("Match Descriptor response %s", stringme)

                    if((eMessageType == E_SL_MSG_DEVICE_ANNOUNCE)):
                        stringme= (':'.join(x.encode('hex') for x in sData))
                        self.logger.info("Device Announce response %s", stringme)

                    if((eMessageType == E_SL_MSG_READ_ATTRIBUTE_RESPONSE)):
                        stringme= (':'.join(x.encode('hex') for x in sData))
                        self.logger.info("Read Attributes response %s", stringme)

                    if((eMessageType == E_SL_MSG_GET_GROUP_MEMBERSHIP_RESPONSE)):
                        stringme= (':'.join(x.encode('hex') for x in sData))
                        self.logger.info("Get Group response %s", stringme)

                    if((eMessageType == E_SL_MSG_MANAGEMENT_LQI_RESPONSE)):
                        stringme= (':'.join(x.encode('hex') for x in sData))
                        self.logger.info("LQI response %s", stringme)                        

                else:
                    try:
                        
                        # Yield control to other thread to allow it to set up the listener
                        if ((eMessageType == E_SL_MSG_SAVE_PDM_RECORD)or
                            (eMessageType == E_SL_MSG_LOAD_PDM_RECORD_REQUEST) or
                            (eMessageType == E_SL_MSG_DELETE_PDM_RECORD) or
                            (eMessageType == E_SL_MSG_PDM_HOST_AVAILABLE)):                            
                                self.dMessageQueue[eMessageType] = Queue.Queue(30)
                        time.sleep(0)
                        self.dMessageQueue[eMessageType].put(sData)
                    except KeyError:
                            self.logger.warning("Unhandled message 0x%04x", eMessageType)

        finally:
            self.logger.debug("Read thread terminated")


    def SendMessage(self, eMessageType, sData=""):
        """ Send a message to the node amd wait for its synchronous response
            Raise cSerialLinkError or cModuleError on failure
        """
        self.logger.info("Host->Node: Command  0x%04x, length %d", eMessageType, (len(sData)/2))
        self._WriteMessage(eMessageType, sData)
        try:
            status = self.WaitMessage(E_SL_MSG_STATUS, 1)
        except cSerialLinkError:
            raise cSerialLinkError("Module did not acknowledge command 0x%04x" % eMessageType)
        
        status = struct.unpack("B", status[0])[0]
        message = "" if len(sData) == 0 else sData
        
        if status == 0:
            stringme= (':'.join(x.encode('hex') for x in sData))
            self.logger.info("Command success. %s " %message)
        else:
            # Error status code
            raise cModuleError(status, message)


    def WaitMessage(self, eMessageType, fTimeout):
        """ Wait for a message of type eMessageType for fTimeout seconds
            Raise cSerialLinkError on failure
            Many different threads can all block on this function as long
            as they are waiting on different message types.
        """
        sData = None
        try:
            # Get the message from the receiver thread, and delete the queue entry
            sData = self.dMessageQueue[eMessageType].get(True, fTimeout)
            del self.dMessageQueue[eMessageType]
        except KeyError:
            self.dMessageQueue[eMessageType] = Queue.Queue()
            try:
                # Get the message from the receiver thread, and delete the queue entry
                sData = self.dMessageQueue[eMessageType].get(True, fTimeout)
                del self.dMessageQueue[eMessageType]
            except Queue.Empty:
                # Raise exception, no data received
                raise cSerialLinkError("Message 0x%04x not received within %fs" % (eMessageType, fTimeout))
        
        self.logger.debug("Pulled message type 0x%04x from queue", eMessageType)
        return sData



class cControlBridge():
    """Class implementing commands to the control bridge node"""
    def __init__(self, port, baudrate=115200):
        self.oSL = cSerialLink(port, baudrate)
        self.oPdm = cPDMFunctionality(port)
        #self.oSL._WriteMessage(E_SL_MSG_PDM_HOST_AVAILABLE_RESPONSE,"00")

    def parseCommand(self,IncCommand):
        """parse commands"""
        command=str.split(IncCommand,",")          
        if command[0] == 'EXIT':
            return False
        if command[0] == 'EXP':
            self.SetExtendedPANID(command[1])
        if command[0] == 'GTV':            
            print "Node Version: 0x%08x" % self.GetVersion()
        if command[0] == 'RST':
            self.SendSwReset()
        if command[0] == 'LQI':
            self.SendLqiRequest(command[1],command[2])
        if command[0] == 'DEV':
            self.SetDeviceType(command[1])
        if command[0] == 'SIS':
            self.SetInitialSecurity(command[1],command[2],command[3],command[4])
        if command[0] == 'EPD':
            self.ErasePersistentData()
        if command[0] == 'ZFN':
            self.ZLLFactoryNewPersistentData()
        if command[0] == 'TLK':
            if(command[1] == '0'):
                self.InitiateTouchLink()
            else:
                self.InitiateTouchLinkFactoryReset()
        if command[0] == 'START':
            self.StartNetwork()
        if command[0] == 'SCAN':
            self.StartScan()
        if command[0] == 'ONFT':
           self.SendOnOffToggle(command[1],command[2],command[3],command[4],command[5])
        if command[0] == 'M2HS':
            self.SendMoveToHue(command[1],command[2],command[3],command[4],command[5],command[6])
        if command[0] == 'CHL':
            self.SetChannelMask(command[1])
        if command[0] == 'DEFAULTC':
            self.ErasePersistentData()            
            self.SendSwReset()
            time.sleep(5)
            self.SetDeviceType('00')
            time.sleep(1)
            self.SetChannelMask('0000000B') 
            time.sleep(1)
            self.SetExtendedPANID('ABCDEFABCDEFABCD')
            time.sleep(1)
            self.StartNetwork()

        if command[0] == 'DEFAULTRZLL1':
            self.ErasePersistentData()
            self.SendSwReset()
            time.sleep(5)
            self.SetDeviceType('01')
            time.sleep(1)
            self.SetChannelMask('0000000B') 
            time.sleep(1)
            self.SetExtendedPANID('ABCDEFABCDEFABCD')
            time.sleep(1)
            self.StartNetwork()

        if command[0] == 'DEFAULTRZLL2':
            self.ErasePersistentData()
            self.SendSwReset()
            time.sleep(5)
            self.SetDeviceType('01')
            time.sleep(1)
            self.SetInitialSecurity('03','00','01','5A6967426565416C6C69616E63653039')
            time.sleep(1)
            self.SetInitialSecurity('04','00','01','D0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF')
            time.sleep(1)
            self.SetChannelMask('00000014') 
            time.sleep(1)
            self.SetExtendedPANID('ABCDEFABCDEFABCD')
            time.sleep(1)
            self.StartDeviceScan()

        if command[0] == 'DEFAULTRZLLHA':
            self.ErasePersistentData()
            self.SendSwReset()
            time.sleep(5)
            self.SetDeviceType('02')
            time.sleep(1)
            self.SetChannelMask('0000000F') 
            time.sleep(1)
            self.SetExtendedPANID('ABCDEFABCDEFABCD')
            time.sleep(1)
            self.StartNetwork()       

        if command[0] == 'MDR':
            self.SendMatchDescriptor(command[1],command[2],command[3],command[4],command[5],command[6])

        if command[0] == 'LOF':
            self.SendLevelOnff(command[1],command[2],command[3],command[4],command[5],command[6])

        if command[0] == 'SDR':
            self.SendSimpleDescriptor(command[1],command[2])

        if command[0] == 'LQI':
            self.SendLqiRequest(command[1],command[2])            

        if command[0] == 'SPJ':
            self.SetPermitJoiningOnTarget(command[1],command[2],command[3])

        if command[0] == 'RDR':
            self.ReadAttributeRequest(command[1],command[2],command[3],command[4],command[5],command[6],command[7],command[8],command[9],command[10])

        if command[0] == 'GGM':
            self.GetGroupMembership(command[1],command[2],command[3],command[4],command[5])

        if command[0] == 'ADG':
            self.AddGroup(command[1],command[2],command[3],command[4],command[5])


        if command[0] == 'CLOOP':
            self.ColourControlLoop(command[1],command[2],command[3],command[4],command[5],command[6],command[7],command[8],command[9])

        if command[0] == 'MCT':
            self.MoveColourTemperature(command[1],command[2],command[3],command[4],command[5],command[6],command[7],command[8],command[9])

        if command[0] == 'M2CT':
            self.MoveToColourTemperature(command[1],command[2],command[3],command[4],command[5],command[6])

        if command[0] == 'DISREP':
            self.SendMatchDescriptor('FFFD','C05E','01','0006','00','0000')
            self.SendMatchDescriptor('FFFD','0104','01','0006','00','0000')

        if command[0] == 'PDMDUMP':        
            conn = sqlite3.connect('pdm.db')
            c = conn.cursor()
            conn.close()
            
        print ''
        return True
    
    def GetVersion(self):
        """Get the version of the connected node"""
        self.oSL.SendMessage(E_SL_MSG_GET_VERSION)
        version = self.oSL.WaitMessage(E_SL_MSG_VERSION_LIST, 0.5)
        return struct.unpack(">I", version)[0]

    def SetExtendedPANID(self,extPanid):
        """Set Extended PANID"""
        self.oSL.SendMessage(E_SL_MSG_SET_EXT_PANID,str(extPanid))
        

    def SendSwReset(self):
        """Send SW Reset"""
        self.oSL.SendMessage(E_SL_MSG_RESET)
            

    def SetDeviceType(self,device):
        """Set device type"""
        self.oSL.SendMessage(E_SL_MSG_SET_DEVICETYPE,str(device))


    def StartDeviceScan(self):
        """Start scan on the device"""
        self.oSL.SendMessage(E_SL_MSG_START_SCAN)

    def DeviceStartNetwork(self):
        """Start network"""
        self.oSL.SendMessage(E_SL_MSG_START_NETWORK)

    def SetInitialSecurity(self,KeyState,KeySeq,KeyType,sKey):
        """Set Initial Security state and key"""
        self.oSL.SendMessage(E_SL_MSG_SET_SECURITY,(str(KeyState)+str(KeySeq)+str(KeyType)+str(sKey)))

    def ErasePersistentData(self):
        """Erase persistent data"""
        self.oSL._WriteMessage(E_SL_MSG_ERASE_PERSISTENT_DATA,"")

    def ZLLFactoryNewPersistentData(self):
        """Erase persistent data"""
        self.oSL._WriteMessage(E_SL_MSG_ZLL_FACTORY_NEW,"")
        

    def InitiateTouchLink(self):
        """Initiate Touch Link"""
        self.oSL.SendMessage(E_SL_MSG_INITIATE_TOUCHLINK)


    def SetChannelMask(self,channel):
        """Start Network"""
        self.oSL.SendMessage(E_SL_MSG_SET_CHANNELMASK,str(channel))

    def StartNetwork(self):
        """Start Network"""
        self.oSL.SendMessage(E_SL_MSG_START_NETWORK)

    def StartScan(self):
        """Start Network"""
        self.oSL.SendMessage(E_SL_MSG_START_SCAN)

    def SendOnOffToggle(self,addressmode,TargetAddress,srcEp,DstEp,EffectsCommandId):
        """Send on Off or Toggle command"""
        self.oSL.SendMessage(E_SL_MSG_ONOFF_NOEFFECTS,(str(addressmode)+str(TargetAddress)+str(srcEp)+str(DstEp)+str(EffectsCommandId)))

    def SendMoveToHue(self,addressmode,TargetAddress,srcEp,DstEp,Hue,Saturation,TransitionTime):
        """Send move to hue command"""
        self.oSL.SendMessage(E_SL_MSG_MOVE_TO_HUE_SATURATION,(str(addressmode)+str(TargetAddress)+str(srcEp)+str(DstEp)+str(Hue)+str(Saturation)+str(TransitionTime)))
        
    def SendMatchDescriptor(self,TargetAddress,profile,InputClusterCount,InputClusterList,OutputClusterCount,OutputClusterList):
         """Send match descriptor command"""
         self.oSL.SendMessage(E_SL_MSG_MATCH_DESCRIPTOR_REQUEST,(str(TargetAddress)+str(profile)+str(InputClusterCount)+str(InputClusterList)+str(OutputClusterCount)+str(OutputClusterList)))

    def SendLevelOnff(self,TargetAddress,srcEp,DstEp,bOnOff,level,time):
         """Send match descriptor command"""
         self.oSL.SendMessage(E_SL_MSG_MOVE_TO_LEVEL_ONOFF,(str(addressmode)+str(TargetAddress)+str(srcEp)+str(DstEp)+str(bOnOff)+str(level)+str(time)))

    def SendSimpleDescriptor(self,TargetAddress,endpoint):
         """Send match descriptor command"""
         self.oSL.SendMessage(E_SL_MSG_SIMPLE_DESCRIPTOR_REQUEST,(str(TargetAddress)+str(endpoint)))

    def SendLqiRequest(self,TargetAddress,startidx):
         """Send LQI command"""
         self.oSL.SendMessage(E_SL_MSG_MANAGEMENT_LQI_REQUEST,(str(TargetAddress)+str(startidx)))
         
    def InitiateTouchLinkFactoryReset(self):
        """Initiate Touch Link factory reset"""
        self.oSL.SendMessage(E_SL_MSG_TOUCHLINK_FACTORY_RESET)


    def SetPermitJoiningOnTarget(self,targetAddress,pemitDuration,TcOverride):
        """Initiate Touch Link factory reset"""
        self.oSL.SendMessage(E_SL_MSG_PERMIT_JOINING_REQUEST,(str(targetAddress)+str(pemitDuration)+str(TcOverride)))


    def ReadAttributeRequest(self,addressmode,TargetAddress,srcEp,dstEp,clusterid,bServer,bManufactuer,ManId,numberOfAttributes,attributelist):
         """Send Read Attributes Request"""
         self.oSL.SendMessage(E_SL_MSG_READ_ATTRIBUTE_REQUEST,(str(addressmode)+str(TargetAddress)+str(srcEp)+str(dstEp)+str(clusterid)+str(bServer)+str(bManufactuer)+str(ManId)+str(numberOfAttributes)+str(attributelist)))

    def GetGroupMembership(self,addressmode,targetAddress,srcEp,DstEp,GroupCount,GroupList):
        """Get group membership"""
        self.oSL.SendMessage(E_SL_MSG_GET_GROUP_MEMBERSHIP,(str(addressmode)+str(targetAddress)+str(srcEp)+ str(DstEp)+str(GroupCount)+str(GroupList)))

    def AddGroup(self,addressmode,targetAddress,srcEp,DstEp,GroupId):
        """Add Group"""
        self.oSL.SendMessage(E_SL_MSG_ADD_GROUP,(str(addressmode)+str(targetAddress)+str(srcEp)+ str(DstEp)+str(GroupId)))


    def ColourControlLoop(self,addressmode,targetAddress,srcEp,DstEp,updatedFlags,Actions,direction,time,startHue):
        """start colour control loop"""
        self.oSL.SendMessage(E_SL_MSG_COLOUR_LOOP_SET,(str(addressmode)+str(targetAddress)+str(srcEp)+ str(DstEp)+str(updatedFlags)+str(Actions)+str(direction)+str(time)+str(startHue)))

    def MoveColourTemperature(self,addressmode,targetAddress,srcEp,DstEp,mode, rate,minTemp,maxTemp,transitionTime):
        """move temperature"""
        self.oSL.SendMessage(E_SL_MSG_MOVE_COLOUR_TEMPERATURE,(str(addressmode)+str(targetAddress)+str(srcEp)+ str(DstEp)+str(mode)+str(rate)+str(minTemp)+str(maxTemp)+str(transitionTime)))

    def MoveToColourTemperature(self,addressmode,targetAddress,srcEp,DstEp,colourtemp,transitionTime):
        """move to temperature"""
        self.oSL.SendMessage(E_SL_MSG_MOVE_TO_COLOUR_TEMPERATURE,(str(addressmode)+str(targetAddress)+str(srcEp)+ str(DstEp)+str(colourtemp)+str(transitionTime)))

    def vPDMSendFunc(self,sData):
        """ Internal function
        """
        #print "PDMSend"
        conn = sqlite3.connect('pdm.db')
        c = conn.cursor()
        conn.text_factory = str
        RecordId = (''.join(x.encode('hex') for x in sData))
        #print RecordId
        c.execute("SELECT * FROM PdmData WHERE PdmRecId = ?", (RecordId,))
        data=c.fetchone()                        
        status='00'
        if data is None:
            #print "None"
            TotalBlocks = 0
            BlockId = 0
            size =0
            self.oSL.SendMessage(E_SL_MSG_LOAD_PDM_RECORD_RESPONSE, (status+RecordId+str(size).zfill(8)+str(TotalBlocks).zfill(8)+str(BlockId).zfill(8))+str(size).zfill(8))
        else:
            status='02'
            #print "found entry"
            persistedData = data[2]
            size = data[1]
            TotalBlocks = (long(size,16)/128)
            if((long(size,16)%128)>0):
                NumberOfWrites = TotalBlocks + 1
            else:
                NumberOfWrites = TotalBlocks
            #print size
            #print persistedData
            #print TotalBlocks
            #print NumberOfWrites
            #print long(size,16)
            bMoreData=True
            count =0
            lowerbound = 0
            upperbound = 0
            while(bMoreData):
                u32Size = long(size,16) - (count*128)
                if(u32Size>128):
                    u32Size = 256
                else:
                    bMoreData = False
                    u32Size = u32Size*2
                 
                upperbound =upperbound + u32Size
                DataStrip = persistedData[lowerbound:upperbound]
                count = count+1
                self.oSL.SendMessage(E_SL_MSG_LOAD_PDM_RECORD_RESPONSE,(status+RecordId+size+(hex(NumberOfWrites).strip('0x')).strip('L').zfill(8)+(hex(count).strip('0x')).strip('L').zfill(8)+(hex(u32Size/2).strip('0x')).strip('L').zfill(8)+DataStrip))                
                lowerbound = lowerbound+u32Size                
                
        conn.commit()
        conn.close()
        
if __name__ == "__main__":
    from optparse import OptionParser
    parser = OptionParser()
    
    parser.add_option("-p", "--port", dest="port",
                      help="Serial port device name to use", default=None)
                      
    parser.add_option("-b", "--baudrate", dest="baudrate",
                      help="Baudrate", default=1000000)

    (options, args) = parser.parse_args()
    
    logging.basicConfig(format="%(asctime)-15s %(levelname)s:%(name)s:%(message)s")
    logging.getLogger().setLevel(logging.INFO)
                    
    if options.port is None:
        #print "Please specify serial port with --port"
        parser.print_help()
        sys.exit(1)
        
    conn = sqlite3.connect('pdm.db')
    c = conn.cursor()
    conn.text_factory = str
    # Create table
    c.execute("""CREATE TABLE IF NOT EXISTS PdmData
                (PdmRecId text, PdmRecSize text, PersistedData text)""")

    conn.commit()
    conn.close()

    oCB = cControlBridge(options.port, options.baudrate)
    continueToRun = True
    #bRunning = True
    oCB.oSL._WriteMessage(E_SL_MSG_PDM_HOST_AVAILABLE_RESPONSE,"00")
    useString = str(options.port)+ ""
    while continueToRun:                    
        command = raw_input(useString+'$ ')
        if(command == ""):
            continueToRun = True
        else:
            continueToRun = oCB.parseCommand(command.strip())
    print "Terminating current session...."
    sys.exit(1)


    
