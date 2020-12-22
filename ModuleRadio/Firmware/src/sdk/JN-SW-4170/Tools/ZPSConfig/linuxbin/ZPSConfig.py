#!/usr/bin/python2

import os
import re
import sys
import subprocess
import struct
import datetime
from optparse import OptionParser

from amara import bindery

if os.name == 'nt':
    import win32api, win32con

parser = OptionParser()
parser.add_option('-n', '--node-name', dest='zigbeeNodeName', default='',
                  help='Name of node to generate configuration for.')
parser.add_option('-t', '--target', dest='targetHardware', default='JN5139', help='Target hardware platform for node')
parser.add_option('-o', '--output', dest='outputDir', default=os.path.curdir,
                  help='Path to output the configuration into.')
parser.add_option('-f', '--config-file', dest='configFilename', help='Configuration file')
parser.add_option('-l', '--zigbee-nwk-lib', dest='zigbeeNwkLibFSP', default='libZPSNWK_JN513x.a',
                  help='Zigbee target software library.')
parser.add_option('-e', '--Endian', dest='endian', type='string', default='BIG_ENDIAN', help='Endian of the processor.')
parser.add_option('-a', '--zigbee-apl-lib', dest='zigbeeAplLibFSP', default='libZPSAPL_JN513x.a',
                  help='Zigbee target software library.')
parser.add_option('-y', '--optional_features', action='store_true', dest='OptionalFeatures', default=False,
                  help='gets the optional features in the diagram')
parser.add_option('-c', '--compiler-tools', dest='ToolsDir', default='', help='specifies a path to the compiler tools')
(options, args) = parser.parse_args(sys.argv[1:])


def getLibObjSize(sObjdump, sLib, sEndian):
    print(sObjdump)
    oProc = subprocess.Popen([sObjdump, '-s', '-j.libobjsize', sLib], stdout=subprocess.PIPE)
    sData = oProc.communicate()[0]
    iIdx = sData.find('libobjsize')
    iSize = int('0x' + sData[iIdx:iIdx + 100].split()[2], 16)
    if sEndian != 'BIG_ENDIAN':
        a = struct.pack('<I', iSize)
        iSize = struct.unpack('>I', a)[0]
    return iSize


def getAplServerContextSize(sServer, sObjdump, sLib, sEndian):
    try:
        oProc = subprocess.Popen([sObjdump, '-s', '-j.zps_apl_Zdo' + sServer + 'ContextSize', sLib],
                                 stdout=subprocess.PIPE)
        sData = oProc.communicate()[0]
        iIdx = sData.find('zps_apl_Zdo' + sServer + 'ContextSize')
        iSize = int('0x' + sData[iIdx:iIdx + 100].split()[2], 16)
        if sEndian != 'BIG_ENDIAN':
            a = struct.pack('<I', iSize)
            iSize = struct.unpack('>I', a)[0]
        return iSize
    except:
        print("ERROR: Unable to locate '.zps_apl_Zdo%sContextSize' section in library file '%s'\n" % (sServer, sLib))
        sys.exit(10)


def calculateChannelMask(channelMask):
    channelMaskValue = 0
    if 'true' == channelMask.Channel11.lower():
        channelMaskValue |= 2048
    if 'true' == channelMask.Channel12.lower():
        channelMaskValue |= 4096
    if 'true' == channelMask.Channel13.lower():
        channelMaskValue |= 8192
    if 'true' == channelMask.Channel14.lower():
        channelMaskValue |= 16384
    if 'true' == channelMask.Channel15.lower():
        channelMaskValue |= 32768
    if 'true' == channelMask.Channel16.lower():
        channelMaskValue |= 65536
    if 'true' == channelMask.Channel17.lower():
        channelMaskValue |= 131072
    if 'true' == channelMask.Channel18.lower():
        channelMaskValue |= 262144
    if 'true' == channelMask.Channel19.lower():
        channelMaskValue |= 524288
    if 'true' == channelMask.Channel20.lower():
        channelMaskValue |= 1048576
    if 'true' == channelMask.Channel21.lower():
        channelMaskValue |= 2097152
    if 'true' == channelMask.Channel22.lower():
        channelMaskValue |= 4194304
    if 'true' == channelMask.Channel23.lower():
        channelMaskValue |= 8388608
    if 'true' == channelMask.Channel24.lower():
        channelMaskValue |= 16777216
    if 'true' == channelMask.Channel25.lower():
        channelMaskValue |= 33554432
    if 'true' == channelMask.Channel26.lower():
        channelMaskValue |= 67108864
    return channelMaskValue


def findProfile(profileName):
    for profile in config.ZigbeeWirelessNetwork.Profiles:
        if profile.Name == profileName:
            return profile

    return


def findCluster(clusterName):
    for profile in config.ZigbeeWirelessNetwork.Profiles:
        for cluster in profile.Clusters:
            if cluster.Name == clusterName:
                return cluster

    return


def findNetworkKey(id):
    ref = id.split('->', 2)
    node = findNode(ref[0])
    keyName = 'zpscfg:' + ref[1]
    if hasattr(node, 'TrustCenter'):
        if hasattr(node.TrustCenter, 'Keys'):
            for elem in node.TrustCenter.Keys:
                if keyName == elem.type:
                    return elem

    return


def networkKeyStr(keyNode):
    key = int(keyNode.Key, 0)
    keyStr = ''
    for i in range(0, 16):
        if 0 != i:
            keyStr += ', '
        keyStr += '0x%02x' % ((key & 255 << 8 * i) >> 8 * i)

    return keyStr


def findAPdu(node, apduId):
    if hasattr(node, 'PDUConfiguration'):
        if hasattr(node.PDUConfiguration, 'APDUs'):
            for apdu in node.PDUConfiguration.APDUs:
                if apdu.Id == apduId:
                    return apdu

    return


def findNode(node_name):
    node = None
    if node_name == config.ZigbeeWirelessNetwork.Coordinator.Name:
        node = config.ZigbeeWirelessNetwork.Coordinator
    elif hasattr(config.ZigbeeWirelessNetwork, 'ChildNodes'):
        for childNode in config.ZigbeeWirelessNetwork.ChildNodes:
            if node_name == childNode.Name:
                node = childNode
                break

    return node


def checkForDuplicateNames(nodes, n1):
    if not hasattr(n1, 'Name'):
        return False
    for n2 in nodes:
        if n2 != n1 and hasattr(n2, 'Name') and n1.Name == n2.Name:
            return True

    return False


def checkForDuplicateIds(nodes, n1):
    for n2 in nodes:
        if n2 != n1 and int(n1.Id, 0) == int(n2.Id, 0):
            return True

    return False


def validateConfiguration(xml_qname):
    nameCheck = re.compile('[a-zA-Z_][a-zA-Z_0-9]*')
    if not hasattr(config, 'ZigbeeWirelessNetwork'):
        print("ERROR: The input configuration file does not have a 'ZigbeeWirelessNetwork' element.\n")
        return False
    if hasattr(config.ZigbeeWirelessNetwork, 'Version'):
        if config.ZigbeeWirelessNetwork.Version != '1.1':
            print("ERROR: Unrecognised input file version '%s'\n" % config.ZigbeeWirelessNetwork.Version)
            return False
    else:
        print('ERROR: The input file does not specify a version\n')
        return False
    if not hasattr(config.ZigbeeWirelessNetwork, 'DefaultExtendedPANId'):
        print('WARNING: The input configuration file does contain a Default Extended PAN Id for the ZigBee PRO Wireless Network.\n')
    if not hasattr(config.ZigbeeWirelessNetwork, 'MaxNumberNodes'):
        print('ERROR: The input configuration file does specify a MaxNumberNodes for the ZigBee PRO Wireless Network.\n')
    elif int(config.ZigbeeWirelessNetwork.MaxNumberNodes, 0) < 2:
        print("ERROR: The 'MaxNumberNodes' attribute for a ZigBee PRO Wireless Network must be at least 2 nodes.\n")
        return False
    if not hasattr(config.ZigbeeWirelessNetwork, 'Coordinator'):
        print("WARNING: The input configuration file does not contain a 'Coordinator' node.\n")
    if not hasattr(config.ZigbeeWirelessNetwork, 'Profiles'):
        print('ERROR: The input configuration file does contain any Profile elements.\n')
        return False
    zdpProfileFound = False
    for p in config.ZigbeeWirelessNetwork.Profiles:
        if not hasattr(p, 'Id'):
            if hasattr(p, 'Name'):
                print("ERROR: Profile '%s' does not have an Id attribute." % p.Name)
            else:
                print('ERROR: A Profile element in the input configuration file does not have an Id or Name attribute.')
            return False
        profileId = int(p.Id, 0)
        if not hasattr(p, 'Name'):
            print("ERROR: Profile id '%d' does not have a Name attribute.\n" % profileId)
            return False
        else:
            result = nameCheck.match(p.Name)
            if result.group(0) != p.Name:
                print("ERROR: Profile name '%s' is not a valid C identifier.\n" % p.Name)
                return False
        if profileId == 0:
            zdpProfileFound = True
        elif profileId > 65535 or profileId < 0:
            print("ERROR: The Id of Profile '%s' must be in the range 1-65535" % p.Name)
        if checkForDuplicateNames(config.ZigbeeWirelessNetwork.Profiles, p):
            print("ERROR: There are one or more Profiles with the name '%s'. Profiles must have unique names.\n" % p.Name)
            return False
        if checkForDuplicateIds(config.ZigbeeWirelessNetwork.Profiles, p):
            print("ERROR: There are one or more Profiles with the Id '%s'. Profiles must have unique Ids.\n" % p.Id)
            return False
        if not hasattr(p, 'Clusters'):
            print("ERROR: The Profile '%s' does not contain any Cluster elements.\n" % p.Name)
            return False
        else:
            for cl in p.Clusters:
                if not hasattr(cl, 'Id'):
                    if hasattr(cl, 'Name'):
                        print("ERROR: Cluster '%s' for Profile '%s' does not have an Id attribute." % (cl.Name, p.Name))
                    else:
                        print("ERROR: A Cluster for Profile '%s' does not have an Id or Name attribute." % p.Name)
                    return False
                clusterId = int(cl.Id, 0)
                if not hasattr(cl, 'Name'):
                    print("ERROR: Cluster Id '%d' in Profile id '%s' does not have a Name attribute.\n" % (
                    clusterId, p.Name))
                    return False
                else:
                    result = nameCheck.match(p.Name)
                    if result.group(0) != p.Name:
                        print("ERROR: Profile name '%s' is not a valid C identifier.\n" % p.Name)
                        return False
                if clusterId > 65535 or clusterId < 0:
                    print("ERROR: The Id of Cluster '%s' for Profile '%s' must be in the range 1-65535" % (
                    cl.Name, p.Name))

            if checkForDuplicateNames(p.Clusters, cl):
                print("ERROR: There are one or more Clusters with the name '%s' in Profile '%s'. Clusters must have unique names.\n" % (
                cl.Name, p.Name))
                return False
            if checkForDuplicateIds(p.Clusters, cl):
                print("ERROR: There are one or more Clusters with the Id '%s' in Profile '%s'. Clusters must have unique Ids.\n" % (
                cl.Id, p.Name))
                return False

    if not zdpProfileFound:
        print('ERROR: A ZDP Profile is not present in the input configuration file.')
        return False
    allNodes = []
    if hasattr(config.ZigbeeWirelessNetwork, 'Coordinator'):
        allNodes += config.ZigbeeWirelessNetwork.Coordinator
    if hasattr(config.ZigbeeWirelessNetwork, 'ChildNodes'):
        allNodes += config.ZigbeeWirelessNetwork.ChildNodes
    for node in allNodes:
        if not hasattr(node, 'Name'):
            print('ERROR: A node in the input configuration file does not have a Name attribute.\n')
            return False
        else:
            result = nameCheck.match(node.Name)
            if result.group(0) != node.Name:
                print("ERROR: The node named '%s' in the input configuration file is not a valid C identifier.\n" % node.Name)
                return False
        if checkForDuplicateNames(allNodes, node):
            print("ERROR: There are one or more Nodes with the name '%s'. Nodes must have unique names.\n" % node.Name)
            return False

    foundNode = findNode(xml_qname)
    if None == foundNode:
        print("ERROR: The input configuration file does not contain a node named '%s'.\n" % xml_qname)
        return False
    if not hasattr(foundNode, 'Endpoints'):
        print("ERROR: The input configuration for node '%s' does not contain any 'Endpoint' elements.\n" % xml_qname)
        return False
    zdpEpFound = False
    for ep in foundNode.Endpoints:
        if not hasattr(ep, 'Id'):
            if hasattr(ep, 'Name'):
                print("ERROR: Endpoint '%s' for node '%s' does not have an Id attribute.\n" % (ep.Name, xml_qname))
            else:
                print("ERROR: An Endpoint for node '%s' does not have either an Id or Name attribute.\n" % xml_qname)
            return False
        if not hasattr(ep, 'Name'):
            print("ERROR: Endpoint id '%d' for node '%s' does not have a Name attribute.\n" % (ep.Id, xml_qname))
            return False
        else:
            result = nameCheck.match(ep.Name)
            if result.group(0) != ep.Name:
                print("ERROR: Endpoint name '%s' for node '%s' is not a valid C identifier.\n" % (ep.Name, xml_qname))
                return False
        epId = int(ep.Id, 0)
        if epId == 0:
            zdpEpFound = True
        elif epId > 240:
            if epId != 242:
                print("ERROR: Endpoint '%s' for node '%s' has an invalid id '%d'. Endpoint Ids must be in the range 1-240 or 242.\n" % (
                ep.Name, xml_qname, epId))
                return False
        if checkForDuplicateNames(foundNode.Endpoints, ep):
            print("ERROR: There are one or more Endpoints with the name '%s' for node '%s'. Endpoints must have unique names.\n" % (
            ep.Name, node.Name))
            return False
        if checkForDuplicateIds(foundNode.Endpoints, ep):
            print("ERROR: There are one or more Endpoints with the Id '%s' for node '%s'. Endpoints must have unique Ids.\n" % (
            ep.Id, node.Name))
            return False
        if not hasattr(ep, 'Profile'):
            print("ERROR: Endpoint '%s' on node '%s' does not specify a Profile.\n" % (ep.Name, xml_qname))
            return False
        ioClusterFound = False
        if hasattr(ep, 'InputClusters'):
            ioClusterFound = True
            for cl in ep.InputClusters:
                if not hasattr(cl, 'Cluster'):
                    print("ERROR: An Input Cluster for endpoint '%s' on node '%s' does not specify a Cluster.\n" % (
                    ep.Name, xml_qname))
                    return False
                if not hasattr(cl, 'Discoverable'):
                    print("WARNING: Input cluster '%s' for endpoint '%s' on node '%s' does not have a 'Discoverable' attribute. Defaulting to discoverable.\n" % (
                    cl.Cluster, ep.Name, xml_qname))
                if not hasattr(cl, 'RxAPDU'):
                    print("WARNING: Input cluster '%s' for endpoint '%s' on node '%s' does not specify an RxAPDU. No data can be received for this cluster.\n" % (
                    cl.Cluster, ep.Name, xml_qname))
                elif None == findAPdu(foundNode, cl.RxAPDU):
                    print("ERROR: Unable to find APDU '%s' for input cluster '%s' for endpoint '%s' on node '%s'\n" % (
                    cl.RxAPDU, cl.Cluster, ep.Name, xml_qname))
                    return False

        if hasattr(ep, 'OutputClusters'):
            ioClusterFound = True
            for cl in ep.OutputClusters:
                if not hasattr(cl, 'Cluster'):
                    print("WARNING: An Output Cluster for endpoint '%s' on node '%s' does not specify a Cluster.\n" % (
                    ep.Name, xml_qname))
                    return False
                if not hasattr(cl, 'Discoverable'):
                    print("WARNING: Output cluster '%s' for endpoint '%s' on node '%s' does not have a 'Discoverable' attribute. Defaulting to discoverable.\n" % (
                    cl.Cluster, ep.Name, xml_qname))
                if not hasattr(cl, 'TxAPDUs'):
                    print("WARNING: Output cluster '%s' for endpoint '%s' on node '%s' does not specify any TxAPDUs.\n" % (
                    cl.Cluster, ep.Name, xml_qname))

        if not ioClusterFound:
            print("WARNING: Endpoint '%s' id %d for node '%s' does not contain any input or output clusters.\n" % (
            ep.Name, epId, xml_qname))

    if not zdpEpFound:
        print("ERROR: The input configuration for node '%s' does not contain a ZDP endpoint.\n" % xml_qname)
        return False
    if hasattr(foundNode, 'BindingTable'):
        if hasattr(foundNode.BindingTable, 'Size'):
            if int(foundNode.BindingTable.Size, 0) < 1:
                print("ERROR: The Binding Table for node '%s' must contain at least 1 entry.\n" % xml_qname)
                return False
        else:
            print("ERROR: The Binding Table for node '%s' must specify a table size.\n" % xml_qname)
            return False
    if hasattr(foundNode, 'UserDescriptor'):
        if hasattr(foundNode.UserDescriptor, 'UserDescription'):
            if len(foundNode.UserDescriptor.UserDescription) > 16:
                print("WARNING: The User Descriptor '%s' for node '%s' is longer than 16 characters and will be truncated.\n" % (
                foundNode.UserDescriptor.UserDescription, xml_qname))
            elif len(foundNode.UserDescriptor.UserDescription) <= 0:
                print("ERROR: The User Descriptor for node '%s' does not specify a User Description.\n" % xml_qname)
                return False
        else:
            print("ERROR: The User Descriptor for node '%s' must specify a descriptor.\n" % xml_qname)
            return False
    if hasattr(foundNode, 'PDUConfiguration'):
        if not hasattr(foundNode.PDUConfiguration, 'NumNPDUs'):
            print("ERROR: The PDU Manager for node '%s' must have a NumNPDUs attribute.\n" % xml_qname)
            return False
        elif int(foundNode.PDUConfiguration.NumNPDUs, 0) < 8:
            print("ERROR: The PDU Manager for node '%s' must have at least 8 NPDUs configured" % xml_qname)
            return False
        if not hasattr(foundNode.PDUConfiguration, 'APDUs'):
            print("ERROR: The PDU Manager for node '%s' does not have any APDUs.\n" % xml_qname)
            return False
    else:
        print("ERROR: The node '%s' must have a PDU Manager element.\n" % xml_qname)
        return False
    if hasattr(foundNode, 'GroupTable'):
        if hasattr(foundNode.GroupTable, 'Size'):
            if int(foundNode.GroupTable.Size, 0) < 1:
                print("ERROR: The Group Table for node '%s' must contain at least 1 entry.\n" % xml_qname)
                return False
        else:
            print("ERROR: The Group Table for node '%s' must specify a table size.\n" % xml_qname)
            return False
    if not hasattr(foundNode, 'NodeDescriptor'):
        print("ERROR: A Node Descriptor must be specified for node '%s'.\n" % xml_qname)
        return False
    if not hasattr(foundNode, 'NodePowerDescriptor'):
        print("ERROR: A Node Descriptor must be specified for node '%s'.\n" % xml_qname)
        return False
    elif hasattr(foundNode.NodePowerDescriptor, 'DefaultPowerSource'):
        if foundNode.NodePowerDescriptor.DefaultPowerSource.lower() == 'disposable battery':
            if not hasattr(foundNode.NodePowerDescriptor, 'DisposableBattery') or hasattr(foundNode.NodePowerDescriptor,
                                                                                          'DisposableBattery') and foundNode.NodePowerDescriptor.DisposableBattery.lower() == 'false':
                print("ERROR: Default power source 'Disposable Battery' is not available in the Node Power Descriptor for node '%s'.\n" % xml_qname)
                return False
        if foundNode.NodePowerDescriptor.DefaultPowerSource.lower() == 'rechargeable battery':
            if not hasattr(foundNode.NodePowerDescriptor, 'RechargeableBattery') or hasattr(
                    foundNode.NodePowerDescriptor,
                    'RechargeableBattery') and foundNode.NodePowerDescriptor.RechargeableBattery.lower() == 'false':
                print("ERROR: Default power source 'Rechargeable Battery' is not available in the Node Power Descriptor for node '%s'.\n" % xml_qname)
                return False
        if foundNode.NodePowerDescriptor.DefaultPowerSource.lower() == 'constant power':
            if not hasattr(foundNode.NodePowerDescriptor, 'ConstantPower') or hasattr(foundNode.NodePowerDescriptor,
                                                                                      'ConstantPower') and foundNode.NodePowerDescriptor.ConstantPower.lower() == 'false':
                print("ERROR: Default power source 'Constant Power' is not available in the Node Power Descriptor for node '%s'.\n" % xml_qname)
                return False
    if not hasattr(foundNode, 'ZDOServers'):
        print("ERROR: The node '%s' does not contain a ZDO Configuration.\n" % xml_qname)
        return False
    else:
        if not hasattr(foundNode.ZDOServers, 'ZdoClient'):
            print("ERROR: The ZDO Configuration for node '%s' must contain a ZDO Client.\n" % xml_qname)
            return False
        if not hasattr(foundNode.ZDOServers, 'DeviceAnnceServer'):
            print("ERROR: The ZDO Configuration for node '%s' must contain a Device Annce Server.\n" % xml_qname)
            return False
        if not hasattr(foundNode.ZDOServers, 'ActiveEpServer'):
            print("WARNING: The ZDO Configuration for node '%s' should contain a ActiveEpServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
        if not hasattr(foundNode.ZDOServers, 'NwkAddrServer'):
            print("WARNING: The ZDO Configuration for node '%s' should contain a NwkAddrServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
        if not hasattr(foundNode.ZDOServers, 'IeeeAddrServer'):
            print("WARNING: The ZDO Configuration for node '%s' should contain a IeeeAddrServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
        if not hasattr(foundNode.ZDOServers, 'SystemServerDiscoveryServer'):
            print("WARNING: The ZDO Configuration for node '%s' should contain a SystemServerDiscoveryServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
        if not hasattr(foundNode.ZDOServers, 'NodeDescServer'):
            print("WARNING: The ZDO Configuration for node '%s' should contain a NodeDescServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
        if not hasattr(foundNode.ZDOServers, 'PowerDescServer'):
            print("WARNING: The ZDO Configuration for node '%s' should contain a PowerDescServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
        if not hasattr(foundNode.ZDOServers, 'MatchDescServer'):
            print("WARNING: The ZDO Configuration for node '%s' should contain a MatchDescServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
        if not hasattr(foundNode.ZDOServers, 'SimpleDescServer'):
            print("WARNING: The ZDO Configuration for node '%s' should contain a SimpleDescServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
        if not hasattr(foundNode.ZDOServers, 'MgmtLqiServer'):
            print("WARNING: The ZDO Configuration for node '%s' should contain a MgmtLqiServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
        if not hasattr(foundNode.ZDOServers, 'MgmtLeaveServer') and 'Coordinator' != foundNode.xml_qname:
            print("WARNING: The ZDO Configuration for node '%s' should contain a MgmtLeaveServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
        if not hasattr(foundNode.ZDOServers, 'MgmtNWKUpdateServer'):
            print("WARNING: The ZDO Configuration for node '%s' should contain a MgmtNWKUpdateServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
        print((foundNode.xml_qname))
        if 'Coordinator' == foundNode.xml_qname or 'ChildNodes' == foundNode.xml_qname and 'zpscfg:Router' == foundNode.type:
            if not hasattr(foundNode.ZDOServers, 'PermitJoiningServer'):
                print("WARNING: The ZDO Configuration for node '%s' should contain a PermitJoiningServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
            if not hasattr(foundNode.ZDOServers, 'MgmtRtgServer'):
                print("WARNING: The ZDO Configuration for node '%s' should contain a MgmtRtgServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
        if 'Coordinator' == foundNode.xml_qname:
            if not hasattr(foundNode.ZDOServers, 'EndDeviceBindServer'):
                print("WARNING: The ZDO Configuration for node '%s' should contain a EndDeviceBindServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
        if 'Coordinator' == foundNode.xml_qname:
            if not hasattr(foundNode.ZDOServers, 'MgmtMibIeeeServer'):
                print("WARNING: The ZDO Configuration for node '%s' should contain a MgmtMibIeeeServer to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % xml_qname)
    dns = int(foundNode.MacTableSize, 0)
    if hasattr(foundNode, 'MaxNumSimultaneousApsdeAckReq'):
        if int(foundNode.MaxNumSimultaneousApsdeAckReq, 0) == 0:
            print('WARNING: No Apsde requests with acknowledgements may be made because MaxNumSimultaneousApsdeAckReq is set to 0.\n' % xml_qname)
        if not hasattr(foundNode, 'MaxNumSimultaneousApsdeReq'):
            print('ERROR: No Apsde requests with acknowledgements may be made because MaxNumSimultaneousApsdeAckReq is set to 0.\n' % xml_qname)
            return False
        elif int(foundNode.MaxNumSimultaneousApsdeReq, 0) < 1:
            print("ERROR: MaxNumSimultaneousApsdeReq must be at least 1 or node '%s'.\n" % xml_qname)
            return False
        if not hasattr(foundNode, 'DefaultCallbackName'):
            print("ERROR: DefaultCallbackName is not set for node '%s'\n" % xml_qname)
            return False
        else:
            result = nameCheck.match(foundNode.DefaultCallbackName)
            if result.group(0) != foundNode.DefaultCallbackName:
                print("ERROR: DefaultCallbackName is not a valid C identifier for node '%s'\n" % xml_qname)
                return False
        if 'Coordinator' == foundNode.xml_qname:
            if foundNode.apsDesignatedCoordinator.lower() != 'true':
                print("ERROR: apsDesignatedCoordinator must be set to true for Coordinator node '%s'\n" % xml_qname)
                return False
        if not hasattr(foundNode, 'apsMaxWindowSize'):
            print("ERROR: apsMaxWindowSize is not set for node '%s'\n" % xml_qname)
            return False
        else:
            val = int(foundNode.apsMaxWindowSize, 0)
            if val < 1 or val > 8:
                print("ERROR: apsMaxWindowSize must be in the range 1-8 for node '%s'\n" % xml_qname)
                return False
        if not hasattr(foundNode, 'apsInterframeDelay'):
            print("ERROR: apsInterframeDelay is not set for node '%s'\n" % xml_qname)
            return False
        else:
            val = int(foundNode.apsInterframeDelay, 0)
            if val < 10 or val > 255:
                print("ERROR: apsInterframeDelay must be in the range 10-255 for node '%s'\n" % xml_qname)
                return False
        if not hasattr(foundNode, 'APSDuplicateTableSize'):
            print("ERROR: APSDuplicateTableSize is not set for node '%s'\n" % xml_qname)
            return False
        elif int(foundNode.APSDuplicateTableSize, 0) < 1:
            print("ERROR: APSDuplicateTableSize must be at least 1 for node '%s'\n" % xml_qname)
            return False
        if not hasattr(foundNode, 'apsSecurityTimeoutPeriod'):
            print("ERROR: apsSecurityTimeoutPeriod is not set for node '%s'\n" % xml_qname)
            return False
        elif int(foundNode.apsSecurityTimeoutPeriod, 0) < 1000:
            print("ERROR: apsSecurityTimeoutPeriod must be at least 1000 ms for node '%s'\n" % xml_qname)
            return False
        if not hasattr(foundNode, 'apsUseExtPANId'):
            print("ERROR: apsUseExtPANId is not set for node '%s'\n" % xml_qname)
            return False
        else:
            use_epid = int(foundNode.apsUseExtPANId, 0)
            default_epid = int(config.ZigbeeWirelessNetwork.DefaultExtendedPANId, 0)
            if 0 != use_epid and use_epid != default_epid:
                print("WARNING: apsUseExtPANId for node '%s' does not match the DefaultExtenededPANId setting of the ZigBee Wireless Network.\n" % xml_qname)
        if not hasattr(foundNode, 'apsNonMemberRadius'):
            print("ERROR: apsNonMemberRadius is not set for node '%s'\n" % xml_qname)
            return False
        else:
            nmr = int(foundNode.apsNonMemberRadius, 0)
            if nmr < 0 or nmr > 7:
                print("ERROR: apsNonMemberRadius for node '%s' must be in the range 0-7.\n" % xml_qname)
                return False
        if 'Coordinator' == foundNode.xml_qname or 'ChildNodes' == foundNode.xml_qname and 'zpscfg:Router' == foundNode.type:
            if not hasattr(foundNode, 'PermitJoiningTime'):
                print("ERROR: PermitJoiningTime is not set for node '%s'\n" % xml_qname)
                return False
            else:
                pjt = int(foundNode.PermitJoiningTime, 0)
                if pjt < 0 or pjt > 255:
                    print("ERROR: PermitJoiningTime for node '%s' must be in the range 0-255.\n" % xml_qname)
                    return False
        if not hasattr(foundNode, 'SecurityEnabled'):
            print("ERROR: SecurityEnabled is not set for node '%s'\n" % xml_qname)
            return False
        elif foundNode.SecurityEnabled.lower() != config.ZigbeeWirelessNetwork.DefaultSecurityEnabled.lower():
            print("WARNING: SecurityEnabled for node '%s' does not match the DefaultSecurityEnabled setting for the ZigBeeWirelessNetwork.\n" % xml_qname)
        if not hasattr(foundNode, 'AddressMapTableSize'):
            print("ERROR: AddressMapTableSize is not set for node '%s'\n" % xml_qname)
            return False
        else:
            amts = int(foundNode.AddressMapTableSize, 0)
            if amts > dns:
                print("ERROR: The AddressMapTableSize for node '%s' is greater then the MacTable setting for the ZigBeeWirelessNetwork.\n" % xml_qname)
                return False
        if not hasattr(foundNode, 'ActiveNeighbourTableSize'):
            print("ERROR: ActiveNeighbourTableSize is not set for node '%s'\n" % xml_qname)
            return False
        else:
            ants = int(foundNode.ActiveNeighbourTableSize, 0)
            amts = int(foundNode.AddressMapTableSize, 0)
            if ants > dns:
                print("ERROR: The ActiveNeighbourTableSize for node '%s' is greater then the MacTable setting for the ZigBeeWirelessNetwork.\n" % xml_qname)
                return False
            elif ants < 1:
                print("ERROR: The ActiveNeighbourTableSize for node '%s' must be at least 1.\n" % xml_qname)
                return False
        if not hasattr(foundNode, 'DiscoveryNeighbourTableSize'):
            print("ERROR: DiscoveryNeighbourTableSize is not set for node '%s'\n" % xml_qname)
            return False
        else:
            dnts = int(foundNode.ActiveNeighbourTableSize, 0)
            if dnts < 1:
                print("ERROR: The DiscoveryNeighbourTableSize for node '%s' must be at least 1.\n" % xml_qname)
                return False
        if not hasattr(foundNode, 'RouteDiscoveryTableSize'):
            print("ERROR: RouteDiscoveryTableSize is not set for node '%s'\n" % xml_qname)
            return False
        else:
            rdts = int(foundNode.RouteDiscoveryTableSize, 0)
            if rdts < 1:
                print("ERROR: The RouteDiscoveryTableSize for node '%s' must be at least 1.\n" % xml_qname)
                return False
        if not hasattr(foundNode, 'RoutingTableSize'):
            print("ERROR: RoutingTableSize is not set for node '%s'\n" % xml_qname)
            return False
        else:
            rts = int(foundNode.RoutingTableSize, 0)
            if rts < 1:
                print("ERROR: The RoutingTableSize for node '%s' must be at least 1.\n" % xml_qname)
                return False
        if not hasattr(foundNode, 'BroadcastTransactionTableSize'):
            print("ERROR: BroadcastTransactionTableSize is not set for node '%s'\n" % xml_qname)
            return False
        else:
            btts = int(foundNode.BroadcastTransactionTableSize, 0)
            if btts < 1:
                print("ERROR: The BroadcastTransactionTableSize for node '%s' must be at least 1.\n" % xml_qname)
                return False
        if not hasattr(foundNode, 'RouteRecordTableSize'):
            print("ERROR: RouteRecordTableSize is not set for node '%s'\n" % xml_qname)
            return False
        else:
            btts = int(foundNode.RouteRecordTableSize, 0)
            if btts < 1:
                print("ERROR: The RouteRecordTableSize for node '%s' must be at least 1.\n" % xml_qname)
                return False
        if foundNode.SecurityEnabled.lower() == 'true':
            if not hasattr(foundNode, 'SecurityMaterialSets'):
                print("ERROR: SecurityMaterialSets is not set for node '%s' with SecurityEnabled set to true.\n" % xml_qname)
                return False
            elif int(foundNode.SecurityMaterialSets, 0) < 1:
                print("ERROR: SecurityMaterialSets must be at least 1 for node '%s' with SecurityEnabled set to true.\n" % xml_qname)
                return False
            return True
        if hasattr(foundNode, 'Sleeping'):
            if foundNode.Sleeping.lower() == 'true':
                if not hasattr(foundNode, 'APSPollPeriod'):
                    print("ERROR: APSPollPeriod is not set for node '%s'\n" % xml_qname)
                    return False
                else:
                    ftpp = int(foundNode.APSAckPollPeriod, 0)
                    if ftpp < 25:
                        print("ERROR: The APSPollPeriod for node '%s' must be at least 25ms.\n" % xml_qname)
                        return False
                print(hasattr(foundNode,
                              'NumPollFailuresBeforeRejoin') or "ERROR: NumPollFailuresBeforeRejoin is not set for node '%s'\n" % xml_qname)
                return False
            else:
                npfbr = int(foundNode.NumPollFailuresBeforeRejoin, 0)
                if npfbr == 0:
                    print("WARNING: The NumPollFailuresBeforeRejoin for node '%s' is set to 0. The node will not rejoin if its parent is lost.\n" % xml_qname)
            if hasattr(foundNode, 'ScanDuration'):
                sd = int(foundNode.ScanDuration, 0)
                if sd < 2 or sd > 5:
                    print("ERROR: The ScanDuration for node '%s' must be in the range 2-5\n" % xml_qname)
                    return False
    return


def outputC(dir, configNode, sEndian):
    fsp = os.path.join(dir, 'zps_gen.c')
    if os.path.exists(fsp) and os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_NORMAL)
    Cfile = open(fsp, 'w')
    Cfile.write(
        '/****************************************************************************\n *\n *                 THIS IS A GENERATED FILE. DO NOT EDIT!\n *\n * MODULE:         ZPSConfig\n *\n * COMPONENT:      zps_gen.c\n *\n * DATE:           %s\n *\n * AUTHOR:         Jennic Zigbee Protocol Stack Configuration Tool\n *\n * DESCRIPTION:    ZPS definitions\n *\n ****************************************************************************\n *\n * This software is owned by NXP B.V. and/or its supplier and is protected\n * under applicable copyright laws. All rights are reserved. We grant You,\n * and any third parties, a license to use this software solely and\n * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].\n * You, and any third parties must reproduce the copyright and warranty notice\n * and any other legend of ownership on each copy or partial copy of the\n * software.\n *\n * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"\n * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE\n * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE\n * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR\n * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF\n * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS\n * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN\n * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)\n * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE\n * POSSIBILITY OF SUCH DAMAGE.\n *\n * Copyright NXP B.V. 2016. All rights reserved\n ****************************************************************************/\n\n/****************************************************************************/\n/***        Include files                                                 ***/\n/****************************************************************************/\n\n#include <jendefs.h>\n#include <pdum_gen.h>\n#include "ZQueue.h"\n#include <zps_gen.h>\n\n#include "zps_apl.h"\n#include "zps_apl_aib.h"\n#include "zps_apl_af.h"\n\n' % datetime.datetime.ctime(
            datetime.datetime.now()))
    Cfile.write(
        '\n/****************************************************************************/\n/***        Macro Definitions                                             ***/\n/****************************************************************************/\n\n#define COMPILE_TIME_ASSERT(pred)    switch(0){case 0:case pred:;}\n\n\n#define ZPS_APL_ZDO_VSOUI_LENGTH\t\t3\n/****************************************************************************/\n/***        Type Definitions                                              ***/\n/****************************************************************************/\n\n/*** ZDP Context **************************************************/\n\ntypedef struct {\n    uint8 u8ZdpSeqNum;\n} zps_tsZdpContext;\n\n/*** ZDO Context **************************************************/\n\ntypedef bool (*zps_tprAplZdoServer)(void *pvApl, void *pvServerContext, ZPS_tsAfEvent *psZdoServerEvent);\n\ntypedef struct {\n    zps_tprAplZdoServer prServer;\n    void *pvServerContext;\n} zps_tsAplZdoServer;\n\ntypedef struct\n{\n    uint8               au8Key[ZPS_NWK_KEY_LENGTH];\n    uint8               u8KeySeqNum;\n    uint8               u8KeyType;\n} zps_tsAplZdoInitSecKey;\n\ntypedef struct {\n    uint64 u64InitiatorAddr;\n    uint64 u64ResponderAddr;\n    ZPS_tsTsvTimer sTimer;\n    uint8 au8Key[ZPS_NWK_KEY_LENGTH];\n} zps_tsRequestKeyRequests;\n\n\ntypedef struct {\n    uint8 au8VsOUIBytes[ZPS_APL_ZDO_VSOUI_LENGTH] __attribute__ ((aligned (16)));\n    uint8 eNetworkState; /* ZPS_teZdoNetworkState */\n    uint8 eZdoDeviceType; /* ZPS_teZdoDeviceType */\n    uint8 eNwkKeyState; /* ZPS_teZdoNwkKeyState */\n    uint8 u8PermitJoinTime;\n    uint8 u8StackProfile;\n    uint8 u8ZigbeeVersion;\n    uint8 u8ScanDuration;\n    bool_t bLookupTCAddr;\n    const zps_tsAplZdoServer *psZdoServers;\n    void (*prvZdoServersInit)(void);\n    ZPS_tsTsvTimer sAuthenticationTimer;\n    ZPS_tsTsvTimer sAuthenticationPollTimer;\n    uint8 u8NumPollFailures;\n    uint8 u8MaxNumPollFailures;\n    bool_t bSecurityDisabled;\n    zps_tsAplZdoInitSecKey *psInitSecKey;\n    uint8 u8DevicePermissions;\n    bool_t (*prvZdoReqFilter)(uint16);\n    bool (*pfzps_bAplZdoBindRequestServer)(void *,\n            void *,\n            ZPS_tsAfEvent *);\n    zps_tsRequestKeyRequests *psRequestKeyReqs;\n    uint32 u32ReqKeyTimeout;\n    uint8 u8MaxNumSimulRequestKeyReqs;    \n    \n} zps_tsZdoContext;\n\n/**** Context for the ZDO servers data confirms and acks***********/\n\ntypedef struct {\n    uint8 eState;\n    uint8 u8SeqNum;\n    uint8 u8ConfAck;\n} zps_tsZdoServerConfAckContext;\n\n/*** Trust Center Context *****************************************/\n\ntypedef struct\n{\n    uint16 u16AddrLkup;\n    ZPS_teDevicePermissions eDevPermissions;\n} zps_tsAplTCDeviceTable;\n\ntypedef struct\n{\n    zps_tsAplTCDeviceTable *asTCDeviceTable;\n    uint16  u16SizeOfTCDeviceTable;\n} zps_tsAplTCib;\n\n\ntypedef struct\n{\n    void (*prvTrustCenterInit)(void*);\n    void (*prvTrustCenterUpdateDevice)(void*, uint64, uint64, uint8, uint16);\n    void (*prvTrustCenterRequestKey)(void*, uint64, uint8, uint64);\n    zps_tsAplTCib sTCib;\n    bool_t bTcOverride;\n    bool_t bChangeOverride;\n} zps_tsTrustCenterContext;\n\n/*** AF Context ***************************************************/\n\ntypedef struct zps_tsAplAfDynamicContext zps_tsAplAfDynamicContext;\n\ntypedef struct _zps_tsAplAfSimpleDescCont\n{\n    ZPS_tsAplAfSimpleDescriptor sSimpleDesc;\n    const PDUM_thAPdu *phAPduInClusters;\n    bool_t bEnabled;\n} zps_tsAplAfSimpleDescCont;\n\ntypedef struct {\n    zps_tsAplAfDynamicContext *psDynamicContext;\n    ZPS_tsAplAfNodeDescriptor *psNodeDescriptor;\n    ZPS_tsAplAfNodePowerDescriptor *psNodePowerDescriptor;\n    uint32 u32NumSimpleDescriptors;\n    zps_tsAplAfSimpleDescCont *psSimpleDescConts;\n    ZPS_tsAplAfUserDescriptor *psUserDescriptor;\n    void* hOverrunMsg;   \n    uint8 zcp_u8FragApsAckValue;\n    uint8 zcp_u8FragBlockControl;\n} zps_tsAfContext;\n\n/*** APS Context **************************************************/\n\ntypedef struct\n{\n    uint8 u8Type;\n    uint8 u8ParamLength;\n} ZPS_tsAplApsmeDcfmIndHdr;\n\ntypedef struct\n{\n    uint8 u8Type;\n    uint8 u8ParamLength;\n} ZPS_tsAplApsdeDcfmIndHdr;\n\ntypedef struct {\n    ZPS_tuAddress uDstAddr;\n    PDUM_thAPduInstance hAPduInst;\n    uint8 *pu8SeqCounter;\n    uint16 u16ProfileId;\n    uint16 u16ClusterId;\n    uint8 u8DstEndpoint;\n    uint8 u8SrcEndpoint;\n    uint8 u8Radius;\n    uint8 eDstAddrMode;\n    uint8 eTxOptions;\n} ZPS_tsAplApsdeReqData;\n\ntypedef union\n{\n    ZPS_tsAplApsdeReqData  sReqData;\n} ZPS_tuAplApsdeReqRspParam;\n\ntypedef struct\n{\n    uint8                 u8Type;\n    uint8                 u8ParamLength;\n    uint16                u16Pad;\n    ZPS_tuAplApsdeReqRspParam uParam;\n} ZPS_tsAplApsdeReqRsp;\n\ntypedef struct\n{\n    struct {\n        uint32 u6Reserved       : 6;\n        uint32 u2Fragmentation  : 2;\n        uint32 u24Padding       : 24;\n    } sEFC;\n    uint8 u8BlockNum;\n    uint8 u8Ack;\n} zps_tsExtendedFrameControlField;\n\ntypedef union {\n    struct {\n        uint8   u8DstEndpoint;\n        uint16  u16ClusterId;\n        uint16  u16ProfileId;\n        uint8   u8SrcEndpoint;\n        uint8   u8ApsCounter;\n    } sUnicast;\n\n    struct {\n            uint16  u16GroupAddr;\n            uint16  u16ClusterId;\n            uint16  u16ProfileId;\n            uint8   u8SrcEndpoint;\n            uint8   u8ApsCounter;\n        } sGroup;\n} zps_tuApsAddressingField;\n\ntypedef struct {\n    uint16    *psDuplicateTableSrcAddr;\n    uint32    *psDuplicateTableHash;\n    uint8     *psDuplicateTableApsCnt;\n    uint8     u8TableIndex;\n} zps_tsApsDuplicateTable;\n\ntypedef struct zps_tsMsgRecord_tag {\n    struct zps_tsMsgRecord_tag *psNext;\n    ZPS_tsAplApsdeReqRsp sApsdeReqRsp;\n    ZPS_tsTsvTimer sAckTimer;       /* ack timer */\n    uint8       u8ReTryCnt;\n    uint8       u8ApsCount;\n} zps_tsMsgRecord;\n\ntypedef struct zps_tsDcfmRecord_tag{\n    union {\n        uint16 u16DstAddr;\n        uint64 u64DstAddr;\n    };\n    uint8   u8Handle;\n    uint8   u8SrcEp;\n    uint8   u8DstEp;\n    uint8   u8DstAddrMode;\n    uint8   u8SeqNum;\n} zps_tsDcfmRecord;\n\ntypedef struct zps_tsDcfmRecordPool_tag{\n    zps_tsDcfmRecord *psDcfmRecords;\n    uint8 u8NextHandle;\n    uint8 u8NumRecords;\n} zps_tsDcfmRecordPool;\n\ntypedef struct zps_tsFragmentTransmit_tag {\n    enum {\n        ZPS_FRAG_TX_STATE_IDLE,\n        ZPS_FRAG_TX_STATE_SENDING,\n        ZPS_FRAG_TX_STATE_RESENDING,\n        ZPS_FRAG_TX_STATE_WAIT_FOR_ACK\n    }eState;\n    PDUM_thAPduInstance hAPduInst;\n    uint16  u16DstAddress;\n    uint16  u16ProfileId;\n    uint16  u16ClusterId;\n    uint8   u8DstEndpoint;\n    uint8   u8SrcEndpoint;\n    uint8   u8Radius;\n    uint8   u8SeqNum;\n\n    ZPS_tsTsvTimer sAckTimer;\n    uint8   u8CurrentBlock;\n    uint8   u8SentBlocksInWindow;\n    uint8   u8MinBlockNumber;\n    uint8   u8MaxBlockNumber;\n    uint8   u8TotalBlocksToSend;\n    uint8   u8RetryCount;\n    uint8   u8AckedBlocksInWindow;\n    uint8   u8WindowSize;\n    uint8   u8BlockSize;\n    bool_t  bSecure;\n} zps_tsFragmentTransmit;\n\ntypedef struct zps_tsfragTxPool_tag {\n    zps_tsFragmentTransmit *psFragTxRecords;\n    uint8   u8NumRecords;\n} zps_tsFragTxPool;\n\ntypedef struct zps_tsFragmentReceive_tag {\n    enum {\n        ZPS_FRAG_RX_STATE_IDLE,\n        ZPS_FRAG_RX_STATE_RECEIVING,\n        ZPS_FRAG_RX_STATE_PERSISTING\n    }eState;\n    PDUM_thAPduInstance hAPduInst;\n    uint16  u16SrcAddress;\n    uint16  u16ProfileId;\n    uint16  u16ClusterId;\n    uint8   u8DstEndpoint;\n    uint8   u8SrcEndpoint;\n    uint8   u8SeqNum;\n\n    ZPS_tsTsvTimer  sWindowTimer;\n    PDUM_thNPdu     hNPduPrevious;\n    uint16  u16ReceivedBytes;\n    uint8   u8TotalBlocksToReceive;\n    uint8   u8ReceivedBlocksInWindow;\n    uint8   u8MinBlockNumber;\n    uint8   u8MaxBlockNumber;\n    uint8   u8HighestUnAckedBlock;\n    uint8   u8WindowSize;\n    uint8   u8BlockSize;\n    uint8   u8PreviousBlock;\n} zps_tsFragmentReceive;\n\ntypedef struct zps_tsfragRxPool_tag {\n    zps_tsFragmentReceive *psFragRxRecords;\n    uint8   u8NumRecords;\n    uint8   u8PersistanceTime;\n} zps_tsFragRxPool;\n\ntypedef struct zps_tsApsPollTimer {\n    ZPS_tsTsvTimer sPollTimer;\n    uint16 u16PollInterval;\n    uint8 u8PollActive;\n} zps_tsApsPollTimer;\n\ntypedef struct zps_tsApsmeCmdContainer {\n    struct zps_tsApsmeCmdContainer *psNext; /* must be first element of struct */\n    ZPS_tsNwkNldeReqRsp sNldeReqRsp;\n    ZPS_tsTsvTimer sTimer;\n    PDUM_thNPdu hNPduCopy;\n    uint8 u8Retries;\n} zps_tsApsmeCmdContainer;\n\ntypedef struct {\n    zps_tsApsmeCmdContainer *psFreeList;\n    zps_tsApsmeCmdContainer *psSubmittedList;\n} zps_tsApsmeCmdMgr;\n\ntypedef struct {\n    void* pvParam;\n    ZPS_tsAplApsdeDcfmIndHdr *psApsdeDcfmIndHdr;\n}zps_tsLoopbackDataContext;\n\ntypedef struct {\n    /* APSDE */\n    void *pvParam;\n    ZPS_tsAplApsdeDcfmIndHdr *(*prpsGetApsdeBuf)(void *);\n    void (*prvPostApsdeDcfmInd)(void *, ZPS_tsAplApsdeDcfmIndHdr *);\n    /* APSME */\n    void *pvApsmeParam;\n    ZPS_tsAplApsmeDcfmIndHdr *(*prpsGetApsmeBuf)(void *);\n    void (*prvPostApsmeDcfmInd)(void *, ZPS_tsAplApsmeDcfmIndHdr *);\n\n    zps_tsApsDuplicateTable *psApsDuplicateTable;\n    zps_tsMsgRecord  *psSyncMsgPool;\n    uint8 u8ApsDuplicateTableSize;\n    uint8 u8SeqNum;\n    uint8 u8SyncMsgPoolSize;\n    uint8 u8MaxFragBlockSize;\n    zps_tsDcfmRecordPool sDcfmRecordPool;\n    zps_tsFragRxPool sFragRxPool;\n    zps_tsFragTxPool sFragTxPool;\n    ZPS_teStatus (*preStartFragmentTransmission)(void *, ZPS_tsAplApsdeReqRsp *, uint16, uint8);\n    void (*prvHandleExtendedDataAck)(void *, ZPS_tsNwkNldeDcfmInd *, zps_tuApsAddressingField *, zps_tsExtendedFrameControlField *);\n    void (*prvHandleDataFragmentReceive)(void *, ZPS_tsAplApsdeDcfmIndHdr *);\n    zps_tsApsmeCmdMgr sApsmeCmdMgr;\n    zps_tsApsPollTimer sApsPollTimer;\n    zps_tsLoopbackDataContext sLoopbackContext;\n    ZPS_tsTsvTimer sLoopbackTimer;\n} zps_tsApsContext;\n\n/*** APL Context **************************************************/\n\ntypedef struct {\n    void *pvNwk;\n    const void *pvNwkTableSizes;\n    const void *pvNwkTables;\n    \n    ZPS_tsNwkNib *psNib;\n    ZPS_tsAplAib *psAib;\n    \n    void* hZpsMutex;\n    void* hDefaultStackEventMsg;\n    void* hMcpsDcfmIndMsg;\n    void* hMlmeDcfmIndMsg;\n    void* hTimeEventMsg;\n    void* hMcpsDcfmMsg;\n    /* sub-layer contexts */\n    zps_tsZdpContext sZdpContext;\n    zps_tsZdoContext sZdoContext;\n    zps_tsAfContext  sAfContext;\n    zps_tsApsContext sApsContext;\n\n    /* trust center context if present */\n    zps_tsTrustCenterContext *psTrustCenterContext;\n\n} zps_tsApl;\n\n/*** NIB Defaults **************************************************/\n\ntypedef struct\n{\n    uint32 u32VsOldRouteExpiryTime;\n    uint8  u8MaxRouters;\n    uint8  u8MaxChildren;\n    uint8  u8MaxDepth;\n    uint8  u8PassiveAckTimeout;\n    uint8  u8MaxBroadcastRetries;\n    uint8  u8MaxSourceRoute;\n    uint8  u8NetworkBroadcastDeliveryTime;\n    uint8  u8UniqueAddr;\n    uint8  u8AddrAlloc;\n    uint8  u8UseTreeRouting;\n    uint8  u8SymLink;\n    uint8  u8UseMulticast;\n    uint8  u8LinkStatusPeriod;\n    uint8  u8RouterAgeLimit;\n    uint8  u8RouteDiscoveryRetriesPermitted;\n    uint8  u8VsFormEdThreshold;\n    uint8  u8SecurityLevel;\n    uint8  u8AllFresh;\n    uint8  u8SecureAllFrames;\n    uint8  u8VsTxFailThreshold;\n    uint8  u8VsMaxOutgoingCost;\n    uint8  u8VsLeaveRejoin;\n    uint8  u8ZedTimeout;\n    uint8  u8ZedTimeoutDefault;\n    uint16 u16VerifyLinkCostTransmitRate; \t\t\t\t\t\n\n} zps_tsNwkNibInitialValues;\n\n\n/****************************************************************************/\n/***        External Dependencies                                         ***/\n/****************************************************************************/\n\nPUBLIC ZPS_teStatus zps_eStartFragmentedTransmission(void *, ZPS_tsAplApsdeReqRsp *, uint16 , uint8);\nPUBLIC void zps_vHandleExtendedDataAckFrame(void *, ZPS_tsNwkNldeDcfmInd *, zps_tuApsAddressingField *, zps_tsExtendedFrameControlField * );\nPUBLIC void zps_vHandleApsdeDataFragIndNotSupported(void *pvApl, ZPS_tsAplApsdeDcfmIndHdr *);\nPUBLIC void zps_vHandleApsdeDataFragInd(void *, ZPS_tsAplApsdeDcfmIndHdr *psApsdeDcfmInd);\nbool_t g_pbZpsMutex = FALSE;\nPUBLIC void* zps_vGetZpsMutex(void);\nextern PUBLIC bool_t APP_bMultimaskJoinCallBack(void *);\n')
    myfoundNode = findNode(options.zigbeeNodeName)
    if None == myfoundNode:
        print("ERROR: The input configuration file does not contain a node named '%s'.\n" % myfoundNode.Name)
        return False
    if not hasattr(myfoundNode, 'Endpoints'):
        print("ERROR: The input configuration for node '%s' does not contain any 'Endpoint' elements.\n" % myfoundNode.Name)
        return False
    EpTotal = 0
    for ep in myfoundNode.Endpoints:
        epId = int(ep.Id, 0)
        if epId > 0:
            EpTotal += 1

    MacInterfaceCount = 0
    channelMaskListCount = 0
    ChannelOffset = 0
    if hasattr(configNode, 'ChannelMask'):
        channelMask = calculateChannelMask(configNode.ChannelMask)
        if 0 == channelMask:
            channelMask = 134215680
    else:
        channelMask = 134215680
    SetMaskForIndex0 = 0
    if hasattr(configNode, 'MacInterfaceList'):
        for interface in configNode.MacInterfaceList.MacInterface:
            if interface.RadioType == 'RT2400MHz':
                SetMaskForIndex0 = 1

    if hasattr(configNode, 'MacInterfaceList'):
        for interface in configNode.MacInterfaceList.MacInterface:
            MacInterfaceCount += 1
            channelMaskListCount += int(interface.ChannelListSize)

    if channelMaskListCount > 15:
        print('channelMaskList count in the mac interface should be less than 15')
        return
    if hasattr(configNode, 'MacInterfaceList'):
        for interface in configNode.MacInterfaceList.MacInterface:
            indexTocheck = int(interface.index)
            countIndex = 0
            for interface in configNode.MacInterfaceList.MacInterface:
                if indexTocheck == interface.index:
                    countIndex += 1
                if countIndex > 1:
                    print('ERROR: MAC interfaces should have unique index.\n')

    if MacInterfaceCount > 2:
        print('ERROR: Only two interfaces supported. You have set %d\n' % MacInterfaceCount)
    if MacInterfaceCount > 0:
        Cfile.write('PRIVATE  bool_t    g_bIgnoreBroadcast [ %d ] =  {' % MacInterfaceCount)
        for count in range(0, MacInterfaceCount):
            Cfile.write('TRUE,')

        Cfile.write('};\n')
        Cfile.write('PRIVATE  uint32    g_u32MacTxUcastAvgRetry [ %d ] =  {' % MacInterfaceCount)
        for count in range(0, MacInterfaceCount):
            Cfile.write('1,')

        Cfile.write('};\n')
        Cfile.write('PRIVATE  uint32    g_u32MacTxUcastAccRetry [ %d ]; \n' % MacInterfaceCount)
        Cfile.write('PRIVATE  uint32    g_u32MacTxUcastFail [ %d ]; \n' % MacInterfaceCount)
        Cfile.write('PRIVATE  uint32    g_u32MacTxUcast [ %d ]; \n' % MacInterfaceCount)
        Cfile.write('PRIVATE  uint32    g_u32MacCcaFail [ %d ]; \n' % MacInterfaceCount)
        Cfile.write('PRIVATE  uint32    g_u32ApsRetry   [ %d ]; \n' % MacInterfaceCount)
        Cfile.write('PUBLIC   uint32    g_u32ChannelMaskList [ %d ] = ' % channelMaskListCount)
        Cfile.write('{ ')
        for count in range(0, channelMaskListCount):
            if SetMaskForIndex0 == 1 and count == 0:
                Cfile.write('    0x%08xUL,\n' % channelMask)
            else:
                Cfile.write('0xFFFFFFFF,')

        Cfile.write('}; \n')
        Cfile.write('zps_tsAplAfMMServerContext\ts_sMultiMaskServer =')
        Cfile.write('{')
        Cfile.write('     ZPS_E_MULTIMASK_STATE_IDLE,')
        Cfile.write('     %d,' % channelMaskListCount)
        Cfile.write('     0,')
        Cfile.write('     APP_bMultimaskJoinCallBack')
        Cfile.write('};\n')
        Cfile.write('    /* ... ZPS_MULTIMASK_SUPPORT */\n')
        Cfile.write('    /* The MAC Interface Table (default values) */ \n')
        tempinterface = 0
        Cfile.write('PRIVATE  MAC_tsMacInterface    g_sMacInterface [ %d ]= \n' % MacInterfaceCount)
        Cfile.write('{\n')
        if hasattr(configNode, 'MacInterfaceList'):
            for interface in configNode.MacInterfaceList.MacInterface:
                Radiotype = 'E_MAC_FREQ_NOT_KNOWN'
                macbitmask = 0
                if interface.Enabled == 'true':
                    macbitmask |= 1
                else:
                    macbitmask |= 0
                macbitmask |= int(interface.ChannelListSize) << 2
                if interface.RadioType == 'RT868MHz':
                    Radiotype = 'E_MAC_FREQ_868'
                    tempinterface |= 1
                if interface.RadioType == 'RT2400MHz':
                    Radiotype = 'E_MAC_FREQ_2400'
                    tempinterface |= 2
                if int(interface.index) == 0:
                    if interface.RadioType != 'RT2400MHz':
                        if MacInterfaceCount > 1:
                            print('ERROR: interface index 0 should always be 2.4G in a multimac\n')
                        MacType = 'E_MAC_TYPE_UART1'
                    else:
                        MacType = 'E_MAC_TYPE_SOC'
                if int(interface.index) > 0:
                    MacType = 'E_MAC_TYPE_UART' + str(interface.index)
                if hasattr(interface, 'RouterAllowed'):
                    RouterAllowedFlag = 1
                    macbitmask |= 1 << 1
                else:
                    RouterAllowedFlag = 0
                Cfile.write('        { %d, 0x%x, %s, %s  } , \n' % (0, macbitmask, Radiotype, MacType))

            Cfile.write('};\n')
            Cfile.write('PRIVATE MAC_tsMacInterfaceTable g_asMacInterfaceTable =  \n')
            Cfile.write('{ \n')
            Cfile.write('  &s_sMultiMaskServer,\t\t /* ZPS_MULTIMASK_SUPPORT ...*/ \n')
            Cfile.write('  g_sMacInterface,\n')
            Cfile.write('  &g_u32ChannelMaskList [0],\n')
            Cfile.write('  g_u32MacTxUcastAvgRetry,\n')
            Cfile.write('  g_u32MacTxUcastAccRetry,\n')
            Cfile.write('  g_u32MacTxUcastFail,\n')
            Cfile.write('  g_u32MacTxUcast,\n')
            Cfile.write('  g_u32MacCcaFail,\n')
            Cfile.write('  g_u32ApsRetry,\n')
            Cfile.write('  g_bIgnoreBroadcast,\n')
            Cfile.write('  %d\n' % MacInterfaceCount)
            Cfile.write('};\n')
    Cfile.write('PUBLIC uint8 u8MaxZpsConfigEp = %d ;\n' % EpTotal)
    Cfile.write('PUBLIC uint8 au8EpMapPresent[%d] = {' % EpTotal)
    epLoop = 0
    for ep in myfoundNode.Endpoints:
        epId = int(ep.Id, 0)
        if epId > 0:
            epLoop += 1
            if epLoop < EpTotal:
                Cfile.write('%d ,' % epId)
            else:
                Cfile.write(' %d ' % epId)

    Cfile.write(' }; \n')
    if hasattr(configNode, 'StackProfile'):
        u8ZpsConfigStackProfileId = int(configNode.StackProfile, 0)
        Cfile.write('PUBLIC uint8 u8ZpsConfigStackProfileId = %d;\n' % u8ZpsConfigStackProfileId)
    else:
        Cfile.write('PUBLIC uint8 u8ZpsConfigStackProfileId = 2;\n')
    ApsFcSaveCountBitShift = 10
    if hasattr(configNode, 'ApsFcSaveCountBitShift'):
        ApsFcSaveCountBitShift = int(configNode.ApsFcSaveCountBitShift, 0)
    Cfile.write('PUBLIC const uint32 g_u32ApsFcSaveCountBitShift = %d;\n' % ApsFcSaveCountBitShift)
    NwkFcSaveCountBitShift = 10
    if hasattr(configNode, 'NwkFcSaveCountBitShift'):
        NwkFcSaveCountBitShift = int(configNode.NwkFcSaveCountBitShift, 0)
    Cfile.write('PUBLIC const uint32 g_u32NwkFcSaveCountBitShift = %d;\n' % NwkFcSaveCountBitShift)
    gpSupported = 'NULL'
    if hasattr(configNode, 'GreenPowerSupport'):
        if 'true' == configNode.GreenPowerSupport.lower():
            gpSecTableStruct = 'NULL'
            gpTxQueueStruct = 'NULL'
            gpAgingTimer = 'NULL'
            gpBidirTimer = 'NULL'
            sizeSt = 0
            sizeTxQ = 0
            if hasattr(configNode, 'GreenPowerTxQueue'):
                sizeTxQ = int(configNode.GreenPowerTxQueue.Size, 0)
                Cfile.write('PRIVATE ZPS_tsAfZgpTxGpQueueEntry aZgpTxGpQueue[%d];\n' % sizeTxQ)
                Cfile.write('ZPS_tsTsvTimer sTxAgingTimer;\n')
                Cfile.write('TSV_Timer_s sTxBiDirTimer;\n')
                Cfile.write('ZPS_tsAfZgpTxGpQueue sZgpTxGpQueue = { aZgpTxGpQueue, %d };\n' % sizeTxQ)
                gpAgingTimer = '&sTxAgingTimer'
                gpBidirTimer = '&sTxBiDirTimer'
                gpTxQueueStruct = '&sZgpTxGpQueue'
            if hasattr(configNode, 'GreenPowerSecurityTable'):
                sizeSt = int(configNode.GreenPowerSecurityTable.Size, 0)
                Cfile.write('PRIVATE ZPS_tsAfZgpGpstEntry aZgpGpst[%d];\n' % sizeSt)
                Cfile.write('ZPS_tsAfZgpGpst sZgpGpst = { aZgpGpst, %d };\n' % sizeSt)
                gpSecTableStruct = '&sZgpGpst'
            gpSupported = '&gsGreenPowerContext'
            Cfile.write('ZPS_tsAfZgpGreenPowerContext gsGreenPowerContext = { %s, %s, %s, %s, 100, 0 };\n' % (
            gpSecTableStruct, gpTxQueueStruct, gpAgingTimer, gpBidirTimer))
    Cfile.write('ZPS_tsAfZgpGreenPowerContext *g_psGreenPowerContext = %s;\n' % gpSupported)
    Cfile.write(
        '\n/****************************************************************************/\n/***        Local Function Prototypes                                     ***/\n/****************************************************************************/\n\nPRIVATE void vZdoServersInit(void);\n')
    if hasattr(configNode, 'ZDOServers'):
        for server in configNode.ZDOServers.xml_children:
            if hasattr(server, 'xml_local'):
                if server.xml_qname != 'MgmtNWKEnhanceUpdateServer':
                    Cfile.write('PUBLIC bool zps_bAplZdo%s(void *, void *, ZPS_tsAfEvent *);\n' % server.xml_qname)
                    (outputParams, outputParamTypes) = zdoServers[server.xml_qname]
                    Cfile.write('PUBLIC void zps_vAplZdo%sInit(' % server.xml_qname)
                    outputParamTypes(Cfile)
                    Cfile.write(');\n')

    trustCenterPresent = False
    if hasattr(configNode, 'TrustCenter'):
        Cfile.write('\n/* Trust Center */\n')
        Cfile.write('PUBLIC void zps_vAplTrustCenterInit(void *);')
        Cfile.write('PUBLIC void zps_vAplTrustCenterUpdateDevice(void *, uint64 , uint64 , uint8 , uint16 );')
        Cfile.write('PUBLIC void zps_vAplTrustCenterRequestKey(void *, uint64 , uint8 , uint64 );')
        trustCenterPresent = True
    Cfile.write(
        '\n/****************************************************************************/\n/***        Local Variables                                               ***/\n/****************************************************************************/\n\n')
    bindingTable = 'NULL'
    if hasattr(configNode, 'BindingTable'):
        size = int(configNode.BindingTable.Size, 0)
        if size > 0:
            Cfile.write('PRIVATE ZPS_tsAplApsmeBindingTableStoreEntry s_bindingTableStorage[%d];\n' % size)
            Cfile.write('PRIVATE ZPS_tsAplApsmeBindingTable s_bindingTable = { s_bindingTableStorage, %d };\n' % size)
            bindingTable = '&s_bindingTable'
    bindingCacheCfg = None
    bindingCache = 'NULL'
    if None != bindingCacheCfg:
        tableSize = int(bindingCacheCfg.TableSize, 0)
        numTables = int(bindingCacheCfg.NumTables, 0)
        if numTables > 0:
            for i in range(0, numTables):
                Cfile.write('PRIVATE ZPS_tsAplApsmeBindingTableEntry s_bindingCacheStorage_%d[%d];\n' % (i, tableSize))

            Cfile.write('PRIVATE ZPS_tsAplApsmeBindingTable s_bindingCaches[%d] = {\n' % numTables)
            for i in range(0, numTables):
                Cfile.write('{ 0, &s_bindingCacheStorage_%d, %d },\n' % (i, tableSize))

            Cfile.write('};\n')
            Cfile.write(
                'PRIVATE ZPS_tsAplApsmeBindingTableCache s_bindingCache = { s_bindingCaches, %d, NULL };\n' % numTables)
            bindingCache = '&s_bindingTable'
    bindingTables = 'NULL'
    if 'NULL' != bindingCache or 'NULL' != bindingTable:
        Cfile.write(
            'PRIVATE ZPS_tsAplApsmeBindingTableType s_bindingTables = { %s, %s };\n' % (bindingCache, bindingTable))
        bindingTables = '&s_bindingTables'
    groupTable = 'NULL'
    groupTableSize = 0
    if hasattr(configNode, 'GroupTable'):
        groupTableSize = int(configNode.GroupTable.Size, 0)
        Cfile.write('PRIVATE ZPS_tsAplApsmeGroupTableEntry s_groupTableStorage[%d];\n' % groupTableSize)
        Cfile.write(
            'PRIVATE ZPS_tsAplApsmeAIBGroupTable s_groupTable = { s_groupTableStorage, %d };\n' % groupTableSize)
        Cfile.write('PRIVATE ZPS_tsAPdmGroupTableEntry s_groupTablePdmStorage[%d];\n' % groupTableSize)
        Cfile.write('PUBLIC ZPS_tsPdmGroupTable s_groupPdmTable = { s_groupTablePdmStorage, %d };\n' % groupTableSize)
        groupTable = '&s_groupTable'
    else:
        Cfile.write('PUBLIC ZPS_tsPdmGroupTable s_groupPdmTable = { NULL, %d };\n' % groupTableSize)
    keyPairTable = 'NULL'
    keyPairTableSize = 0
    if hasattr(configNode, 'KeyDescriptorTable'):
        keyPairTableSize = int(configNode.KeyDescriptorTable.Size, 0)
        Cfile.write('PRIVATE ZPS_tsAplApsKeyDescriptorEntry s_keyPairTableStorage[%d] = {\n' % (keyPairTableSize + 3))
        num_pck = 0
        if hasattr(configNode.KeyDescriptorTable, 'PreconfiguredKey'):
            for pck in configNode.KeyDescriptorTable.PreconfiguredKey:
                if num_pck == keyPairTableSize:
                    print('WARNING: There are more PreconfiguredKeys than the KeyDescriptorTable size of %d.\n' % keyPairTableSize)
                    break
                Cfile.write('    { 0x%016lxULL, { ' % int(pck.IEEEAddress, 0))
                key = int(pck.Key, 0)
                for i in range(0, 16):
                    if 0 != i:
                        Cfile.write(', ')
                    Cfile.write('0x%02x' % ((key & 255 << 8 * i) >> 8 * i))

                Cfile.write(' }, 0 , 0 , 0 },\n')
                num_pck += 1

        if num_pck < keyPairTableSize + 3:
            for pck in range(num_pck, keyPairTableSize + 3):
                Cfile.write('    { 0, 0xFFFF, { }  },\n')

        Cfile.write('};\n')
        Cfile.write(
            'ZPS_tsAplApsKeyDescriptorEntry  *psAplDefaultDistributedAPSLinkKey = &s_keyPairTableStorage[%d];\n' % (
                        keyPairTableSize + 1))
        Cfile.write('ZPS_tsAplApsKeyDescriptorEntry  *psAplDefaultGlobalAPSLinkKey = &s_keyPairTableStorage[%d];\n' % (
                    keyPairTableSize + 2))
        Cfile.write('PRIVATE uint32 au32IncomingFrameCounter[%d];\n' % (keyPairTableSize + 3))
        Cfile.write(
            'PRIVATE ZPS_tsAplApsKeyDescriptorTable s_keyPairTable = { s_keyPairTableStorage, %d };\n\n' % keyPairTableSize)
        keyPairTable = '&s_keyPairTable'
    Cfile.write('PRIVATE ZPS_tsAplAib s_sAplAib = {\n')
    Cfile.write('    0,\n')
    extPanId = 0
    if hasattr(configNode, 'apsUseExtPANId'):
        extPanId = int(configNode.apsUseExtPANId, 0)
    Cfile.write('    0x%016lxULL,\n' % extPanId)
    designatedCoordinator = 'FALSE'
    if configNode.xml_qname == 'Coordinator':
        designatedCoordinator = 'TRUE'
    if hasattr(configNode, 'apsDesignatedCoordinator'):
        if 'true' == configNode.apsDesignatedCoordinator.lower():
            designatedCoordinator = 'TRUE'
        else:
            designatedCoordinator = 'FALSE'
    Cfile.write('    %s,\n' % designatedCoordinator)
    useInsecureJoin = 'TRUE'
    if hasattr(configNode, 'apsUseInsecureJoin'):
        if 'true' == configNode.apsUseInsecureJoin.lower():
            useInsecureJoin = 'TRUE'
        else:
            useInsecureJoin = 'FALSE'
    Cfile.write('    %s,\n' % useInsecureJoin)
    Cfile.write('    FALSE,\n')
    Cfile.write('    0,\n')
    nonMemberRadius = 2
    if hasattr(configNode, 'apsNonMemberRadius'):
        nonMemberRadius = int(configNode.apsNonMemberRadius, 0)
    Cfile.write('    0x%02x,\n' % nonMemberRadius)
    interFrameDelay = 0
    if hasattr(configNode, 'apsInterframeDelay'):
        interFrameDelay = int(configNode.apsInterframeDelay, 0)
    Cfile.write('    0x%02x,\n' % interFrameDelay)
    Cfile.write('    0,\n')
    Cfile.write('    0,\n')
    Cfile.write('    0,\n')
    maxWindowSize = 8
    if hasattr(configNode, 'apsMaxWindowSize'):
        maxWindowSize = int(configNode.apsMaxWindowSize, 0)
    Cfile.write('    0x%02x,\n' % maxWindowSize)
    Cfile.write('    %s,\n' % bindingTables)
    Cfile.write('    %s,\n' % groupTable)
    Cfile.write('    %s,\n' % keyPairTable)
    if keyPairTableSize == 0:
        Cfile.write('    NULL,\n')
    else:
        Cfile.write('    &s_keyPairTableStorage[%d],\n' % keyPairTableSize)
    Cfile.write('    FALSE,\n')
    Cfile.write('    FALSE,\n')
    apsSecurityTimeoutPeriod = 3000
    if hasattr(configNode, 'apsSecurityTimeoutPeriod'):
        apsSecurityTimeoutPeriod = int(configNode.apsSecurityTimeoutPeriod, 0)
    Cfile.write('    0x%04x,\n' % apsSecurityTimeoutPeriod)
    if keyPairTableSize == 0:
        Cfile.write('    NULL,\n')
    else:
        Cfile.write('    au32IncomingFrameCounter,\n')
    Cfile.write('    g_u32ChannelMaskList\n')
    Cfile.write('};\n')
    numZDOServers = 0
    if hasattr(configNode, 'ZDOServers'):
        for server in configNode.ZDOServers.xml_children:
            if hasattr(server, 'xml_local'):
                if server.xml_qname != 'MgmtNWKEnhanceUpdateServer':
                    (outputParams, outputParamTypes) = zdoServers[server.xml_qname]
                    contextSize = getAplServerContextSize(server.xml_qname, objdump, options.zigbeeAplLibFSP,
                                                          options.endian)
                    Cfile.write('PRIVATE uint8 s_s%sContext[%d] __attribute__ ((aligned (4)));\n' % (
                    server.xml_qname, contextSize))
                    if server.xml_qname == 'BindRequestServer':
                        if hasattr(server, 'SimultaneousRequests'):
                            SimultaneousRequests = int(server.SimultaneousRequests, 0)
                            Cfile.write('PRIVATE zps_tsZdoServerConfAckContext s_s%sAcksDcfmContext[%d];\n' % (
                            server.xml_qname, SimultaneousRequests))
                    numZDOServers += 1

    if hasattr(configNode, 'ZDOServers'):
        Cfile.write('\n/* ZDO Servers */\n')
        Cfile.write('PRIVATE const zps_tsAplZdoServer s_asAplZdoServers[%d] = {\n' % (numZDOServers + 1))

        def key(item):
            if hasattr(item, 'xml_local'):
                if item.xml_qname == 'DefaultServer':
                    return 1
                if item.xml_qname == 'ZdoClient':
                    return -1
            return 0

        for server in sorted(configNode.ZDOServers.xml_children, key=key):
            if hasattr(server, 'xml_local'):
                if server.xml_qname != 'MgmtNWKEnhanceUpdateServer':
                    Cfile.write('    { zps_bAplZdo%s, s_s%sContext },\n' % (server.xml_qname, server.xml_qname))

        Cfile.write('    { NULL, NULL }\n')
        Cfile.write('};\n')
    Cfile.write('\n/* Simple Descriptors */\n')
    for endpoint in configNode.Endpoints:
        numInputClusters = 0
        numOutputClusters = 0
        endpointId = int(endpoint.Id, 0)
        inDiscFlags = ''
        if hasattr(endpoint, 'InputClusters'):
            numInputClusters = len(list(endpoint.InputClusters))
            inClusterList = ''
            inAPduList = ''
            clusterNum = 0
            clusterDiscMask = 0
            for inCluster in endpoint.InputClusters:
                cluster = findCluster(inCluster.Cluster)
                inClusterList += ' 0x%04x,' % int(cluster.Id, 0)
                if hasattr(inCluster, 'RxAPDU'):
                    apdu = findAPdu(configNode, inCluster.RxAPDU)
                    inAPduList += ' %s,' % apdu.Name
                else:
                    inAPduList += ' NULL,'
                discoverable = 1 << (clusterNum & 7)
                if hasattr(inCluster, 'Discoverable'):
                    if inCluster.Discoverable.lower() == 'false':
                        discoverable = 0
                clusterDiscMask |= discoverable
                if clusterNum & 7 == 7:
                    inDiscFlags += '0x%02x, ' % clusterDiscMask
                    clusterDiscMask = 0
                clusterNum += 1

            if clusterNum & 7 != 0:
                inDiscFlags += '0x%02x' % clusterDiscMask
        outDiscFlags = ''
        if hasattr(endpoint, 'OutputClusters'):
            numOutputClusters = len(list(endpoint.OutputClusters))
            outClusterList = ''
            clusterNum = 0
            clusterDiscMask = 0
            for outCluster in endpoint.OutputClusters:
                cluster = findCluster(outCluster.Cluster)
                outClusterList += ' 0x%04x,' % int(cluster.Id, 0)
                discoverable = 1 << (clusterNum & 7)
                if hasattr(outCluster, 'Discoverable'):
                    if outCluster.Discoverable.lower() == 'false':
                        discoverable = 0
                clusterDiscMask |= discoverable
                if clusterNum & 7 == 7:
                    outDiscFlags += '0x%02x, ' % clusterDiscMask
                    clusterDiscMask = 0
                clusterNum += 1

        if clusterNum & 7 != 0:
            outDiscFlags += '0x%02x' % clusterDiscMask
        if numInputClusters > 0:
            Cfile.write('PRIVATE const uint16 s_au16Endpoint%dInputClusterList[%d] = {%s };\n' % (
            endpointId, numInputClusters, inClusterList))
            Cfile.write('PRIVATE const PDUM_thAPdu s_ahEndpoint%dInputClusterAPdus[%d] = {%s };\n' % (
            endpointId, numInputClusters, inAPduList))
            Cfile.write('PRIVATE uint8 s_au8Endpoint%dInputClusterDiscFlags[%d] = { %s };\n' % (
            endpointId, (numInputClusters + 7) / 8, inDiscFlags))
            Cfile.write('\n')
        if numOutputClusters > 0:
            Cfile.write('PRIVATE const uint16 s_au16Endpoint%dOutputClusterList[%d] = {%s };\n' % (
            endpointId, numOutputClusters, outClusterList))
            Cfile.write('PRIVATE uint8 s_au8Endpoint%dOutputClusterDiscFlags[%d] = { %s };\n' % (
            endpointId, (numOutputClusters + 7) / 8, outDiscFlags))
            Cfile.write('\n')

    if hasattr(configNode, 'DefaultCallbackName'):
        DefaultCallbackName = configNode.DefaultCallbackName
    Cfile.write('PUBLIC void %s(uint8 u8Endpoint, ZPS_tsAfEvent *psStackEvent);\n' % DefaultCallbackName)
    Cfile.write('tszQueue zps_msgMlmeDcfmInd;\n')
    Cfile.write('tszQueue zps_msgMcpsDcfmInd;\n')
    Cfile.write('tszQueue zps_TimeEvents;\n')
    Cfile.write('tszQueue zps_msgMcpsDcfm;\n')
    Cfile.write('PRIVATE zps_tsAplAfSimpleDescCont s_asSimpleDescConts[%d] = {\n' % len(list(configNode.Endpoints)))
    for endpoint in configNode.Endpoints:
        endpointId = int(endpoint.Id, 0)
        numInputClusters = 0
        if hasattr(endpoint, 'InputClusters'):
            numInputClusters = len(endpoint.InputClusters)
        numOutputClusters = 0
        if hasattr(endpoint, 'OutputClusters'):
            numOutputClusters = len(endpoint.OutputClusters)
        profile = findProfile(endpoint.Profile)
        Cfile.write('    {\n')
        Cfile.write('        {\n')
        Cfile.write('            0x%04x,\n' % int(profile.Id, 0))
        Cfile.write('            %s,\n' % endpoint.ApplicationDeviceId)
        Cfile.write('            %s,\n' % endpoint.ApplicationDeviceVersion)
        Cfile.write('            %d,\n' % endpointId)
        Cfile.write('            %d,\n' % numInputClusters)
        Cfile.write('            %d,\n' % numOutputClusters)
        if 0 == numInputClusters:
            Cfile.write('            NULL,\n')
        else:
            Cfile.write('            s_au16Endpoint%dInputClusterList,\n' % endpointId)
        if 0 == numOutputClusters:
            Cfile.write('            NULL,\n')
        else:
            Cfile.write('            s_au16Endpoint%dOutputClusterList,\n' % endpointId)
        if 0 == numInputClusters:
            Cfile.write('            NULL,\n')
        else:
            Cfile.write('            s_au8Endpoint%dInputClusterDiscFlags,\n' % endpointId)
        if 0 == numOutputClusters:
            Cfile.write('            NULL,\n')
        else:
            Cfile.write('            s_au8Endpoint%dOutputClusterDiscFlags,\n' % endpointId)
        Cfile.write('        },\n')
        if 0 == numInputClusters:
            Cfile.write('        NULL,\n')
        else:
            Cfile.write('        s_ahEndpoint%dInputClusterAPdus,\n' % endpointId)
        flags = 0
        if 'true' == endpoint.Enabled.lower():
            flags |= 1
        Cfile.write('        %d\n' % flags)
        Cfile.write('    },\n')

    Cfile.write('};\n')
    Cfile.write('\n/* Node Descriptor */\n')
    Cfile.write('PRIVATE ZPS_tsAplAfNodeDescriptor s_sNodeDescriptor = {\n')
    if 'ZC' == configNode.NodeDescriptor.LogicalType:
        Cfile.write('    0,\n')
    elif 'ZR' == configNode.NodeDescriptor.LogicalType:
        Cfile.write('    1,\n')
    elif 'ZED' == configNode.NodeDescriptor.LogicalType:
        Cfile.write('    2,\n')
    Cfile.write('    %s,\n' % configNode.NodeDescriptor.ComplexDescriptorAvailable.upper())
    Cfile.write('    %s,\n' % configNode.NodeDescriptor.UserDescriptorAvailable.upper())
    Cfile.write('    0,\n')
    localFrequencyBand = 0
    if tempinterface > 0:
        if tempinterface & 1:
            localFrequencyBand |= 16
        if tempinterface & 2:
            localFrequencyBand |= 8
        Cfile.write('    0x%02x,\n' % localFrequencyBand)
    elif '868MHz' == configNode.NodeDescriptor.FrequencyBand:
        Cfile.write('    0,\n')
    elif '915MHz' == configNode.NodeDescriptor.FrequencyBand:
        Cfile.write('    4,\n')
    elif '2.4GHz' == configNode.NodeDescriptor.FrequencyBand:
        Cfile.write('    8,\n')
    Cfile.write('    %d,\n' % int(configNode.NodeDescriptor.APSFlags, 0))
    macFlags = 0
    if 'true' == configNode.NodeDescriptor.AlternatePANCoordinator.lower():
        macFlags |= 1 << 0
    if 'true' == configNode.NodeDescriptor.DeviceType.lower():
        macFlags |= 1 << 1
    if 'true' == configNode.NodeDescriptor.PowerSource.lower():
        macFlags |= 1 << 2
    if 'true' == configNode.NodeDescriptor.RxOnWhenIdle.lower():
        macFlags |= 1 << 3
    if 'true' == configNode.NodeDescriptor.Security.lower():
        macFlags |= 1 << 6
    if 'true' == configNode.NodeDescriptor.AllocateAddress.lower():
        macFlags |= 1 << 7
    Cfile.write('    0x%02x,\n' % macFlags)
    Cfile.write('    0x%04x,\n' % int(configNode.NodeDescriptor.ManufacturerCode, 0))
    Cfile.write('    0x%02x,\n' % int(configNode.NodeDescriptor.MaximumBufferSize, 0))
    Cfile.write('    0x%04x,\n' % int(configNode.NodeDescriptor.MaximumIncomingTransferSize, 0))
    serverMask = 0
    if 'true' == configNode.NodeDescriptor.PrimaryTrustCenter.lower():
        serverMask |= 1 << 0
    if 'true' == configNode.NodeDescriptor.BackupTrustCenter.lower():
        serverMask |= 1 << 1
    if 'true' == configNode.NodeDescriptor.PrimaryBindingTableCache.lower():
        serverMask |= 1 << 2
    if 'true' == configNode.NodeDescriptor.BackupBindingTableCache.lower():
        serverMask |= 1 << 3
    if 'true' == configNode.NodeDescriptor.PrimaryDiscoveryCache.lower():
        serverMask |= 1 << 4
    if 'true' == configNode.NodeDescriptor.BackupDiscoveryCache.lower():
        serverMask |= 1 << 5
    if 'true' == configNode.NodeDescriptor.NetworkManager.lower():
        serverMask |= 1 << 6
    serverMask |= 22 << 9
    Cfile.write('    0x%04x,\n' % serverMask)
    Cfile.write('    0x%04x,\n' % int(configNode.NodeDescriptor.MaximumOutgoingTransferSize, 0))
    descriptorCapabilities = 0
    if 'true' == configNode.NodeDescriptor.ExtendedActiveEndpointListAvailable.lower():
        descriptorCapabilities |= 1 << 0
    if 'true' == configNode.NodeDescriptor.ExtendedSimpleDescriptorListAvailable.lower():
        descriptorCapabilities |= 1 << 1
    Cfile.write('    0x%02x};\n' % descriptorCapabilities)
    if sEndian == 'BIG_ENDIAN':
        Cfile.write('\n/* Node Power Descriptor */\n')
        Cfile.write('PRIVATE ZPS_tsAplAfNodePowerDescriptor s_sNodePowerDescriptor = {\n')
        currentPowerMode = 0
        if 'Synchronised with RxOnWhenIdle' == configNode.NodePowerDescriptor.DefaultPowerMode:
            currentPowerMode = 0
        elif 'Periodic' == configNode.NodePowerDescriptor.DefaultPowerMode:
            currentPowerMode = 1
        elif 'Stimulated' == configNode.NodePowerDescriptor.DefaultPowerMode:
            currentPowerMode = 2
        Cfile.write('    0x%01x,\n' % currentPowerMode)
        availablePowerSources = 0
        if 'true' == configNode.NodePowerDescriptor.ConstantPower.lower():
            availablePowerSources |= 1 << 0
        if 'true' == configNode.NodePowerDescriptor.RechargeableBattery.lower():
            availablePowerSources |= 1 << 1
        if 'true' == configNode.NodePowerDescriptor.DisposableBattery.lower():
            availablePowerSources |= 1 << 2
        Cfile.write('    0x%01x,\n' % availablePowerSources)
        currentPowerSource = 0
        if 'Constant Power' == configNode.NodePowerDescriptor.DefaultPowerSource:
            currentPowerSource = 1
        elif 'Rechargeable Battery' == configNode.NodePowerDescriptor.DefaultPowerSource:
            currentPowerSource = 2
        elif 'Disposable Battery' == configNode.NodePowerDescriptor.DefaultPowerSource:
            currentPowerSource = 4
        Cfile.write('    0x%01x,\n' % currentPowerSource)
        Cfile.write('    0xC};\n')
    else:
        Cfile.write('\n/* Node Power Descriptor */\n')
        Cfile.write('PRIVATE ZPS_tsAplAfNodePowerDescriptor s_sNodePowerDescriptor = {\n')
        Cfile.write('    0xC,   \n')
        currentPowerSource = 0
        if 'Constant Power' == configNode.NodePowerDescriptor.DefaultPowerSource:
            currentPowerSource = 1
        elif 'Rechargeable Battery' == configNode.NodePowerDescriptor.DefaultPowerSource:
            currentPowerSource = 2
        elif 'Disposable Battery' == configNode.NodePowerDescriptor.DefaultPowerSource:
            currentPowerSource = 4
        Cfile.write('    0x%01x,\n' % currentPowerSource)
        availablePowerSources = 0
        if 'true' == configNode.NodePowerDescriptor.ConstantPower.lower():
            availablePowerSources |= 1 << 0
        if 'true' == configNode.NodePowerDescriptor.RechargeableBattery.lower():
            availablePowerSources |= 1 << 1
        if 'true' == configNode.NodePowerDescriptor.DisposableBattery.lower():
            availablePowerSources |= 1 << 2
        Cfile.write('    0x%01x,\n' % availablePowerSources)
        currentPowerMode = 0
        if 'Synchronised with RxOnWhenIdle' == configNode.NodePowerDescriptor.DefaultPowerMode:
            currentPowerMode = 0
        elif 'Periodic' == configNode.NodePowerDescriptor.DefaultPowerMode:
            currentPowerMode = 1
        elif 'Stimulated' == configNode.NodePowerDescriptor.DefaultPowerMode:
            currentPowerMode = 2
        Cfile.write('    0x%01x};\n' % currentPowerMode)
    if hasattr(configNode, 'UserDescriptor'):
        Cfile.write('\n/* User Descriptor */\n')
        Cfile.write('PRIVATE ZPS_tsAplAfUserDescriptor s_sUserDescriptor = { { ')
        for i in range(0, len(configNode.UserDescriptor.UserDescription)):
            if i < 16:
                Cfile.write("'%c', " % configNode.UserDescriptor.UserDescription[i])

        Cfile.write('} };\n')
    Cfile.write('\n/* APSDE duplicate table */\n')
    apsDuplicateTableSize = int(configNode.APSDuplicateTableSize, 0)
    if apsDuplicateTableSize < 1:
        apsDuplicateTableSize = 1
    Cfile.write('PRIVATE uint16 s_au16ApsDuplicateTableAddrs[%d];\n' % apsDuplicateTableSize)
    Cfile.write('PRIVATE uint32 s_au32ApsDuplicateTableHash[%d];\n' % int(configNode.APSDuplicateTableSize, 0))
    Cfile.write('PRIVATE uint8 s_au8ApsDuplicateTableSeqCnts[%d];\n' % int(configNode.APSDuplicateTableSize, 0))
    Cfile.write(
        'PRIVATE zps_tsApsDuplicateTable s_sApsDuplicateTable = { s_au16ApsDuplicateTableAddrs, s_au32ApsDuplicateTableHash, s_au8ApsDuplicateTableSeqCnts, 0 };\n')
    Cfile.write('\n/* APSDE sync msg pool */\n')
    Cfile.write('PRIVATE zps_tsMsgRecord s_asApsSyncMsgPool[%d];\n' % int(configNode.MaxNumSimultaneousApsdeAckReq, 0))
    Cfile.write('\n/* APSDE dcfm record pool */\n')
    Cfile.write('PRIVATE zps_tsDcfmRecord s_asApsDcfmRecordPool[%d];\n' % int(configNode.MaxNumSimultaneousApsdeReq, 0))
    if int(configNode.FragmentationMaxNumSimulRx, 0) > 0:
        Cfile.write('\n/* APSDE fragmentation rx pool */\n')
        Cfile.write(
            'PRIVATE zps_tsFragmentReceive s_asApsFragRxPool[%d];\n' % int(configNode.FragmentationMaxNumSimulRx, 0))
    if int(configNode.FragmentationMaxNumSimulTx, 0) > 0:
        Cfile.write('\n/* APSDE fragmentation tx pool */\n')
        Cfile.write(
            'PRIVATE zps_tsFragmentTransmit s_asApsFragTxPool[%d];\n' % int(configNode.FragmentationMaxNumSimulTx, 0))
    numApsmeCmdContainers = 4
    if hasattr(configNode, 'NumAPSMESimulCommands'):
        if int(configNode.NumAPSMESimulCommands, 0) > 0:
            numApsmeCmdContainers = int(configNode.NumAPSMESimulCommands, 0)
    Cfile.write('\n/* APSME Command Manager Command Containers */\n')
    Cfile.write(
        'PRIVATE zps_tsApsmeCmdContainer s_sApsmeCmdContainer_%d = { NULL, {}, {}, NULL, 0 };\n' % numApsmeCmdContainers)
    for i in range(numApsmeCmdContainers - 1, 0, -1):
        Cfile.write(
            'PRIVATE zps_tsApsmeCmdContainer s_sApsmeCmdContainer_%d = { &s_sApsmeCmdContainer_%d, {}, {}, NULL, 0 };\n' % (
            i, i + 1))

    securityDisabled = False
    securityInitialKey = False
    if not securityDisabled and hasattr(configNode, 'InitialNetworkKey'):
        initKey = findNetworkKey(configNode.InitialNetworkKey)
        if None != initKey:
            if initKey.type == 'zpscfg:PreConfiguredNwkKey' or trustCenterPresent and initKey.type == 'zpscfg:DefaultNwkKey':
                Cfile.write('\n/* Initial Nwk Key */\n')
                Cfile.write('zps_tsAplZdoInitSecKey s_sInitSecKey = { { %s }, 0x%02x, ZPS_NWK_SEC_NETWORK_KEY };\n' % (
                networkKeyStr(initKey), int(initKey.KeySequenceNumber, 0)))
                securityInitialKey = True
    if not securityDisabled and hasattr(configNode, 'TrustCenter'):
        Cfile.write('\n/* Trust Center */\n')
        Cfile.write('PRIVATE zps_tsAplTCDeviceTable s_asTrustCenterDeviceTable[%d] = {\n' % int(
            configNode.TrustCenter.DeviceTableSize, 0))
        for i in range(int(configNode.TrustCenter.DeviceTableSize, 0)):
            Cfile.write('                                                            { 0xFFFF, 0 },\n')

        Cfile.write('                                                                };\n')
        Cfile.write('PRIVATE zps_tsTrustCenterContext s_sTrustCenterContext = {\n')
        Cfile.write('    zps_vAplTrustCenterInit,\n')
        Cfile.write('    zps_vAplTrustCenterUpdateDevice,\n')
        Cfile.write('    zps_vAplTrustCenterRequestKey,\n')
        Cfile.write('    { s_asTrustCenterDeviceTable, %d },\n' % int(configNode.TrustCenter.DeviceTableSize, 0))
        Cfile.write(' FALSE,\n')
        Cfile.write(' FALSE,\n')
        Cfile.write('};\n\n')
    Cfile.write('\n/* Network Layer Context */\n')
    nwkContextSize = getLibObjSize(objdump, options.zigbeeNwkLibFSP, options.endian)
    Cfile.write('PRIVATE uint8                   s_sNwkContext[%d] __attribute__ ((aligned (4)));\n' % nwkContextSize)
    Cfile.write('PRIVATE ZPS_tsNwkDiscNtEntry    s_asNwkNtDisc[%d];\n' % int(configNode.DiscoveryNeighbourTableSize, 0))
    Cfile.write('PRIVATE ZPS_tsNwkActvNtEntry    s_asNwkNtActv[%d];\n' % int(configNode.ActiveNeighbourTableSize, 0))
    Cfile.write('PRIVATE ZPS_tsNwkRtDiscEntry    s_asNwkRtDisc[%d];\n' % int(configNode.RouteDiscoveryTableSize, 0))
    Cfile.write('PRIVATE ZPS_tsNwkRtEntry        s_asNwkRt[%d];\n' % int(configNode.RoutingTableSize, 0))
    Cfile.write('PRIVATE ZPS_tsNwkBtr            s_asNwkBtt[%d];\n' % int(configNode.BroadcastTransactionTableSize, 0))
    Cfile.write('PRIVATE ZPS_tsNwkRctEntry       s_asNwkRct[%d];\n' % int(configNode.RouteRecordTableSize, 0))
    Cfile.write('PRIVATE ZPS_tsNwkSecMaterialSet s_asNwkSecMatSet[%d];\n' % int(configNode.SecurityMaterialSets, 0))
    Cfile.write('PRIVATE uint32                  s_asNwkInFCSet[%d];\n' % int(configNode.ActiveNeighbourTableSize, 0))
    Cfile.write(
        'PRIVATE uint16                  s_au16NwkAddrMapNwk[%d];\n' % (int(configNode.AddressMapTableSize, 0) + 4))
    Cfile.write(
        'PRIVATE uint16                  s_au16NwkAddrMapLookup[%d];\n' % (int(configNode.AddressMapTableSize, 0) + 4))
    Cfile.write('PRIVATE uint64                  s_au64NwkAddrMapExt[%d];\n' % (int(configNode.MacTableSize, 0) + 4))
    Cfile.write('#ifdef ZPS_FRQAG\n')
    Cfile.write(
        'PRIVATE uint32                  s_au32RxPacketCount[%d];\n' % int(configNode.ActiveNeighbourTableSize, 0))
    Cfile.write(
        'PRIVATE uint32                  s_au32TxPacketCount[%d];\n' % int(configNode.ActiveNeighbourTableSize, 0))
    Cfile.write('#endif\n')
    LeaveAllowedDefault = 1
    if configNode.xml_qname == 'ChildNodes' and 'zpscfg:EndDevice' == configNode.type:
        LeaveAllowedDefault = 0
    if hasattr(configNode, 'ChildTableSize'):
        Cfile.write('PRIVATE uint32                  s_au32ZedTimeoutCount[%d];\n' % int(configNode.ChildTableSize, 0))
        Cfile.write('PRIVATE uint8                  s_au8KeepAliveFlags[%d];\n' % int(configNode.ChildTableSize, 0))
    elif configNode.xml_qname == 'ChildNodes' and 'zpscfg:EndDevice' == configNode.type:
        Cfile.write(
            'PRIVATE uint32                  s_au32ZedTimeoutCount[%d];\n' % int(configNode.ActiveNeighbourTableSize,
                                                                                 0))
        Cfile.write(
            'PRIVATE uint8                  s_au8KeepAliveFlags[%d];\n' % int(configNode.ActiveNeighbourTableSize, 0))
    else:
        Cfile.write(
            'PRIVATE uint32                  s_au32ZedTimeoutCount[%d];\n' % int(configNode.ActiveNeighbourTableSize,
                                                                                 0))
        Cfile.write(
            'PRIVATE uint8                  s_au8KeepAliveFlags[%d];\n' % int(configNode.ActiveNeighbourTableSize, 0))
    Cfile.write(
        '\nPRIVATE const zps_tsNwkNibInitialValues s_sNibInitialValues =\n{\n    600,\n    05,\n    7,\n    15,\n    1,\n    2,\n    11,\n    18,\n    0,\n    2,\n    0,\n    1,\n    0,\n    15,\n    3,\n    3,\n    255,\n    5,\n    TRUE,\n    TRUE,\n    5,\n    4,')
    Cfile.write('\n    %d,' % LeaveAllowedDefault)
    Cfile.write('\n    2,\n    8\n    ,0/* u16VerifyLinkCostTransmitRate */\n};\n\n')
    Cfile.write('\nPRIVATE const ZPS_tsNwkNibTblSize     s_sNwkTblSize = {\n')
    Cfile.write('    %d,\n' % int(configNode.ActiveNeighbourTableSize, 0))
    Cfile.write('    %d,\n' % int(configNode.RoutingTableSize, 0))
    Cfile.write('    %d,\n' % int(configNode.RouteRecordTableSize, 0))
    Cfile.write('    %d,\n' % int(configNode.AddressMapTableSize, 0))
    Cfile.write('    %d,\n' % int(configNode.DiscoveryNeighbourTableSize, 0))
    Cfile.write('    %d,\n' % int(configNode.RouteDiscoveryTableSize, 0))
    Cfile.write('    %d,\n' % int(configNode.BroadcastTransactionTableSize, 0))
    Cfile.write('    %d,\n' % int(configNode.SecurityMaterialSets, 0))
    Cfile.write('    sizeof(s_sNibInitialValues),\n')
    if hasattr(configNode, 'ChildTableSize'):
        Cfile.write('    %d,\n' % int(configNode.ChildTableSize, 0))
    elif configNode.xml_qname == 'ChildNodes' and 'zpscfg:EndDevice' == configNode.type:
        Cfile.write('    %d,\n' % int(configNode.ActiveNeighbourTableSize, 0))
    else:
        Cfile.write('    %d,\n' % (int(configNode.ActiveNeighbourTableSize, 0) / 6))
    Cfile.write('    %d\n' % int(configNode.MacTableSize, 0))
    Cfile.write('};\n')
    Cfile.write(
        '\nPRIVATE const ZPS_tsNwkNibTbl s_sNwkTbl = {\n    s_asNwkNtDisc,\n    s_asNwkNtActv,\n    s_asNwkRtDisc,\n    s_asNwkRt,\n    s_asNwkBtt,\n    s_asNwkRct,\n    s_asNwkSecMatSet,\n    (ZPS_tsNwkNibInitialValues*)&s_sNibInitialValues,\n    s_au16NwkAddrMapNwk,\n    s_au16NwkAddrMapLookup,\n    s_asNwkInFCSet,\n#if (defined JENNIC_CHIP_FAMILY_JN516x) || (JENNIC_CHIP_FAMILY_JN517x)\n    0,\n#endif\n    s_au64NwkAddrMapExt,\n    s_au32ZedTimeoutCount,\n    s_au8KeepAliveFlags,\n#ifdef ZPS_FRQAG\n    s_au32RxPacketCount,\n    s_au32TxPacketCount,\n#else\n    NULL,\n    NULL,\n#endif    \n};\n')
    Cfile.write('\n/* Application Layer Context */\n')
    if not securityDisabled and hasattr(configNode, 'TrustCenter'):
        numRequestKeyRequests = 4
    else:
        numRequestKeyRequests = 1
    timeoutRequestKey = 15
    Cfile.write('PRIVATE zps_tsRequestKeyRequests s_asRequestKeyRequests[%d];\n' % numRequestKeyRequests)
    Cfile.write('PRIVATE zps_tsApl s_sApl = {\n')
    Cfile.write('    s_sNwkContext,\n')
    Cfile.write('    &s_sNwkTblSize,\n')
    Cfile.write('    &s_sNwkTbl,\n')
    Cfile.write('    NULL,\n')
    Cfile.write('    &s_sAplAib,\n')
    Cfile.write('    zps_vGetZpsMutex,\n')
    if hasattr(configNode, 'DefaultCallbackName'):
        DefaultCallbackName = configNode.DefaultCallbackName
    else:
        return 1
    Cfile.write('    &%s,\n' % DefaultCallbackName)
    MACMlmeDcfmIndMessage = 'zps_msgMlmeDcfmInd'
    MACMcpsDcfmIndMessage = 'zps_msgMcpsDcfmInd'
    MACTimeEventMessage = 'zps_TimeEvents'
    Cfile.write('    &%s,\n' % MACMcpsDcfmIndMessage)
    Cfile.write('    &%s,\n' % MACMlmeDcfmIndMessage)
    Cfile.write('    &%s,\n' % MACTimeEventMessage)
    MACMcpsDcfmEventMessage = 'zps_msgMcpsDcfm'
    Cfile.write('    &%s,\n' % MACMcpsDcfmEventMessage)
    Cfile.write('    { 0 },\n')
    if 'Coordinator' == configNode.xml_qname:
        nodeType = 'ZPS_ZDO_DEVICE_COORD'
    elif 'ChildNodes' == configNode.xml_qname:
        if 'zpscfg:Router' == configNode.type:
            nodeType = 'ZPS_ZDO_DEVICE_ROUTER'
        elif 'zpscfg:EndDevice' == configNode.type:
            nodeType = 'ZPS_ZDO_DEVICE_ENDDEVICE'
        else:
            nodeType = '<undefined>'
    permitJoiningTime = 0
    if hasattr(configNode, 'PermitJoiningTime'):
        permitJoiningTime = int(configNode.PermitJoiningTime, 0)
    scanDuration = 4
    if hasattr(configNode, 'ScanDuration'):
        scanDuration = int(configNode.ScanDuration, 0)
    Cfile.write('    {\n')
    Cfile.write('         { 0x1B, 0x19, 0x4A },\n')
    Cfile.write('        0,\n')
    Cfile.write('        %s,\n' % nodeType)
    Cfile.write('        ZPS_ZDO_PRECONFIGURED_LINK_KEY,\n')
    Cfile.write('        0x%02x,\n' % permitJoiningTime)
    Cfile.write('        2,\n')
    Cfile.write('        2,\n')
    Cfile.write('        %d,\n' % scanDuration)
    Cfile.write('        FALSE,\n')
    Cfile.write('        s_asAplZdoServers,\n')
    Cfile.write('        vZdoServersInit,\n')
    Cfile.write('        { /* timer struct */},\n')
    Cfile.write('        { /* timer struct */},\n')
    Cfile.write('        0,\n')
    maxNumPollFailures = 3
    if hasattr(configNode, 'NumPollFailuresBeforeRejoin'):
        maxNumPollFailures = int(configNode.NumPollFailuresBeforeRejoin, 0)
    Cfile.write('        %d,\n' % maxNumPollFailures)
    Cfile.write('        %d,\n' % securityDisabled)
    if securityDisabled or not securityInitialKey:
        Cfile.write('        NULL,\n')
    elif securityInitialKey:
        Cfile.write('        &s_sInitSecKey,\n')
    Cfile.write('        0,\n')
    Cfile.write('        NULL,\n')
    Cfile.write('        NULL,\n')
    Cfile.write('        s_asRequestKeyRequests,\n')
    Cfile.write('        %d,\n' % (timeoutRequestKey * 62500))
    Cfile.write('        %d\n' % numRequestKeyRequests)
    Cfile.write('    },\n')
    Cfile.write('    {\n')
    Cfile.write('        NULL,\n')
    Cfile.write('        &s_sNodeDescriptor,\n')
    Cfile.write('        &s_sNodePowerDescriptor,\n')
    Cfile.write('        %d,\n' % len(list(configNode.Endpoints)))
    Cfile.write('        s_asSimpleDescConts,\n')
    if hasattr(configNode, 'UserDescriptor'):
        Cfile.write('        &s_sUserDescriptor,\n')
    else:
        Cfile.write('        NULL,\n')
    Cfile.write('        NULL,\n')
    Cfile.write('        0xff,\n')
    Cfile.write('        0x00\n')
    Cfile.write('    },\n')
    Cfile.write('    {\n')
    Cfile.write('        NULL,\n')
    Cfile.write('        NULL,\n')
    Cfile.write('        NULL,\n')
    Cfile.write('        NULL,\n')
    Cfile.write('        NULL,\n')
    Cfile.write('        NULL,\n')
    Cfile.write('        &s_sApsDuplicateTable,\n')
    Cfile.write('        s_asApsSyncMsgPool,\n')
    apsDuplicateTableSize = 1
    if hasattr(configNode, 'APSDuplicateTableSize'):
        apsDuplicateTableSize = int(configNode.APSDuplicateTableSize, 0)
    Cfile.write('        0x%02x,\n' % apsDuplicateTableSize)
    Cfile.write('        0,\n')
    Cfile.write('        %d,\n' % int(configNode.MaxNumSimultaneousApsdeAckReq, 0))
    Cfile.write('        0,\n')
    Cfile.write('        { s_asApsDcfmRecordPool, 1, %d },\n' % int(configNode.MaxNumSimultaneousApsdeReq, 0))
    fragmentationEnabled = int(configNode.FragmentationMaxNumSimulRx, 0) > 0 or int(
        configNode.FragmentationMaxNumSimulTx, 0) > 0
    APSPersistenceTime = 100
    if hasattr(configNode, 'APSPersistenceTime'):
        if int(configNode.APSPersistenceTime, 0) > 25:
            APSPersistenceTime = int(configNode.APSPersistenceTime, 0)
    if int(configNode.FragmentationMaxNumSimulRx, 0) > 0:
        Cfile.write('        { s_asApsFragRxPool, %d, %d },\n' % (
        int(configNode.FragmentationMaxNumSimulRx, 0), APSPersistenceTime))
    else:
        Cfile.write('        { NULL, 0, 0 },\n')
    if int(configNode.FragmentationMaxNumSimulTx, 0) > 0:
        Cfile.write('        { s_asApsFragTxPool, %d },\n' % int(configNode.FragmentationMaxNumSimulTx, 0))
    else:
        Cfile.write('        { NULL, 0 },\n')
    if int(configNode.FragmentationMaxNumSimulTx, 0) > 0:
        Cfile.write('        zps_eStartFragmentedTransmission,\n')
        Cfile.write('        zps_vHandleExtendedDataAckFrame,\n')
    else:
        Cfile.write('        NULL,\n')
        Cfile.write('        NULL,\n')
    if int(configNode.FragmentationMaxNumSimulRx, 0) > 0:
        Cfile.write('        zps_vHandleApsdeDataFragInd,\n')
    else:
        Cfile.write('        zps_vHandleApsdeDataFragIndNotSupported,\n')
    Cfile.write('        { &s_sApsmeCmdContainer_1, NULL },\n')
    APSPollPeriod = 100
    if hasattr(configNode, 'APSPollPeriod'):
        if int(configNode.APSPollPeriod, 0) > 25:
            APSPollPeriod = int(configNode.APSPollPeriod, 0)
    Cfile.write('        { { /* Timer */}, %d, 0 },\n' % APSPollPeriod)
    Cfile.write('        { NULL, NULL },\n')
    Cfile.write('        { /* Timer */}\n')
    Cfile.write('    },\n')
    if not securityDisabled and hasattr(configNode, 'TrustCenter'):
        Cfile.write('    &s_sTrustCenterContext\n')
    else:
        Cfile.write('    NULL\n')
    Cfile.write('};\n')
    Cfile.write('\nconst void *zps_g_pvApl = &s_sApl;\n')
    Cfile.write(
        '\n'
        '/****************************************************************************/\n'
        '/***        Exported Variables                                            ***/\n'
        '/****************************************************************************/\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        Exported Functions                                            ***/\n'
        '/****************************************************************************/\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        Local Functions                                               ***/\n'
        '/****************************************************************************/\n'
        '\n',
    )
    Cfile.write('\n/****************************************************************************\n')
    Cfile.write(' *\n')
    Cfile.write(' * NAME: ZPS_psMacIFTGetTable\n')
    Cfile.write(' *\n')
    Cfile.write(' * DESCRIPTION:\n')
    Cfile.write(' * Obtain the pointer to the Mac inteface table \n')
    Cfile.write(' *\n')
    Cfile.write(' * PARAMETERS \t\t\tName  \t   \t\tRW  \tUsage \n')
    Cfile.write(' *\n')
    Cfile.write(' * RETURNS:\n')
    Cfile.write(' * Address of Mac interface table if successful, NULL otherwise \n')
    Cfile.write(' *\n')
    Cfile.write(' ****************************************************************************/ \n')
    Cfile.write(' PUBLIC MAC_tsMacInterfaceTable* ZPS_psMacIFTGetTable(void) \n')
    Cfile.write(' {\n')
    Cfile.write('\t return &g_asMacInterfaceTable; \n')
    Cfile.write(' }\n')
    Cfile.write('\n/****************************************************************************\n')
    Cfile.write(' *\n')
    Cfile.write(' * NAME: ZPS_psMacIFTGetInterface \n')
    Cfile.write(' *\n')
    Cfile.write(' * DESCRIPTION:\n')
    Cfile.write(' * Get the Mac interface entry from the MAC interface table for the specified\n')
    Cfile.write(' * Mac ID\n')
    Cfile.write(' *\n')
    Cfile.write(' * PARAMETERS \tName  \t\tRW  \tUsage\n')
    Cfile.write(' *\t\t\t\tu8MacID\t\tR\t\tThe Mac Id for the interface\n')
    Cfile.write(' * RETURNS:\n')
    Cfile.write(' * Address of Mac interface structure if found, NULL otherwise\n')
    Cfile.write(' *\n')
    Cfile.write(' ****************************************************************************/ \n')
    Cfile.write(' PUBLIC MAC_tsMacInterface* ZPS_psMacIFTGetInterface(uint8 u8MacID)\n')
    Cfile.write(' { \n')
    Cfile.write('\t MAC_tsMacInterface *pRet = NULL;\n')
    Cfile.write(' \t if(u8MacID < g_asMacInterfaceTable.u8NumInterfaces) \n')
    Cfile.write(' \t {\n')
    Cfile.write(' \t\t pRet = &g_asMacInterfaceTable.psMacInterfaces[u8MacID];\n')
    Cfile.write(' \t }\n')
    Cfile.write(' \t return pRet;\n')
    Cfile.write(' }\n')
    if hasattr(configNode, 'ZDOServers'):
        Cfile.write('\n/* ZDO Server Initialisation */\n')
        Cfile.write('PRIVATE void vZdoServersInit(void)\n{\n')
        if sEndian == 'BIG_ENDIAN':
            ZPS_APL_Version = 'ZPS_APL_Version_3v0'
            ZPS_NWK_Version = 'ZPS_NWK_Version_3v0'
            Cfile.write('    /* Version compatibility check */\n')
            Cfile.write('    asm(".extern %s" : ) ;\n' % ZPS_APL_Version)
            Cfile.write('    asm("l.addi r0,r0,hi(%s)" : );\n' % ZPS_APL_Version)
            Cfile.write('    asm(".extern %s" : ) ;\n' % ZPS_NWK_Version)
            Cfile.write('    asm("l.addi r0,r0,hi(%s)" : );\n' % ZPS_NWK_Version)
        else:
            ZPS_APL_Version = 'ZPS_APL_Version_3v0'
            ZPS_NWK_Version = 'ZPS_NWK_Version_3v0'
            Cfile.write('    /* Version compatibility check */\n')
            Cfile.write('    asm(".extern %s" : ) ;\n' % ZPS_APL_Version)
            Cfile.write('    asm("LDR R0, =%s" : );\n' % ZPS_APL_Version)
            Cfile.write('    asm(".extern %s" : ) ;\n' % ZPS_NWK_Version)
            Cfile.write('    asm("LDR R0, =%s" : );\n' % ZPS_NWK_Version)
    for server in configNode.ZDOServers.xml_children:
        if hasattr(server, 'xml_local'):
            if server.xml_qname != 'MgmtNWKEnhanceUpdateServer':
                Cfile.write('    zps_vAplZdo%sInit(' % server.xml_qname)
                (outputParams, outputParamTypes) = zdoServers[server.xml_qname]
                outputParams(Cfile, server)
                Cfile.write(');\n')

    if 'Coordinator' == configNode.xml_qname:
        Cfile.write('    zps_vRegisterCallbackForSecondsTick(ZPS_vSecondTimerCallback);\n')
    elif 'zpscfg:Router' == configNode.type:
        Cfile.write('    zps_vRegisterCallbackForSecondsTick(ZPS_vSecondTimerCallback);\n')
    Cfile.write('}\n')
    Cfile.write('\nPUBLIC void* ZPS_vGetGpContext(void)\n{\n')
    Cfile.write('\n    return g_psGreenPowerContext;\n}\n')
    Cfile.write('\nPUBLIC void* zps_vGetZpsMutex(void)\n{\n')
    Cfile.write('\n    return &g_pbZpsMutex;\n}\n')
    Cfile.write('\n\nPUBLIC void ZPS_vGetOptionalFeatures(void)\n{\n')
    if hasattr(configNode, 'InterPAN'):
        if 'true' == configNode.InterPAN.lower():
            Cfile.write('   ZPS_vAfInterPanInit();\n')
    if hasattr(configNode, 'GreenPowerSupport'):
        if 'true' == configNode.GreenPowerSupport.lower():
            Cfile.write('   ZPS_vRegisterGreenPower();\n')
            if hasattr(configNode, 'GreenPowerTxQueue'):
                Cfile.write('   ZPS_vZgpInitGpTxQueue();\n')
            if hasattr(configNode, 'GreenPowerSecurityTable'):
                Cfile.write('   ZPS_vZgpInitGpSecurityTable();\n')
    Cfile.write('}\n')
    Cfile.write(
        '\n/****************************************************************************/\n/***        END OF FILE                                                   ***/\n/****************************************************************************/\n')
    Cfile.close()
    if os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_READONLY)
    return


def outputHeader(dir, configNode):
    fsp = os.path.join(dir, 'zps_gen.h')
    if os.path.exists(fsp) and os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_NORMAL)
    Hfile = open(fsp, 'w')
    Hfile.write(
        '/****************************************************************************\n *\n *                 THIS IS A GENERATED FILE. DO NOT EDIT!\n *\n * MODULE:         ZPSConfig\n *\n * COMPONENT:      zps_gen.h\n *\n * DATE:           %s\n *\n * AUTHOR:         NXP Zigbee Protocol Stack Configuration Tool\n *\n * DESCRIPTION:    ZPS definitions\n *\n ****************************************************************************\n *\n\n * This software is owned by NXP B.V. and/or its supplier and is protected\n * under applicable copyright laws. All rights are reserved. We grant You,\n * and any third parties, a license to use this software solely and\n * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].\n * You, and any third parties must reproduce the copyright and warranty notice\n * and any other legend of ownership on each copy or partial copy of the\n * software.\n *\n * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"\n * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE\n * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE\n * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR\n * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF\n * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS\n * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN\n * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)\n * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE\n * POSSIBILITY OF SUCH DAMAGE.\n *\n * Copyright NXP B.V. 2017. All rights reserved\n ****************************************************************************/\n' % datetime.datetime.ctime(
            datetime.datetime.now()))
    Hfile.write(
        '\n#ifndef _ZPS_GEN_H\n#define _ZPS_GEN_H\n\n/****************************************************************************/\n/***        Macro Definitions                                             ***/\n/****************************************************************************/\n\n')
    Hfile.write('#define ZPS_NWK_OPT_ALL\n')
    if 'Coordinator' == configNode.xml_qname:
        Hfile.write('#define ZPS_COORDINATOR\n')
    elif 'Childnodes' == configNode.xml_qname:
        if 'zpscfg:Router' == configNode.type:
            Hfile.write('#define ZPS_ROUTER\n')
        elif 'zpscfg:EndDevice' == configNode.type:
            Hfile.write('#define ZPS_END_DEVICE\n')
    Hfile.write('#define ZPS_NODE_%s\n' % configNode.Name.upper())
    for profile in config.ZigbeeWirelessNetwork.Profiles:
        Hfile.write("\n/* Profile '%s' */\n" % profile.Name)
        id = int(profile.Id, 0)
        Hfile.write('#define %s_PROFILE_ID    (0x%04x)\n' % (profile.Name.upper(), id))
        for cluster in profile.Clusters:
            id = int(cluster.Id, 0)
            Hfile.write('#define %s_%s_CLUSTER_ID    (0x%04x)\n' % (profile.Name.upper(), cluster.Name.upper(), id))

    node = config.ZigbeeWirelessNetwork.Coordinator
    Hfile.write("\n/* Node '%s' */\n" % node.Name)
    Hfile.write('/* Endpoints */\n')
    for endpoint in node.Endpoints:
        id = int(endpoint.Id, 0)
        Hfile.write('#define %s_%s_ENDPOINT    (%d)\n' % (node.Name.upper(), endpoint.Name.upper(), id))

    if hasattr(config.ZigbeeWirelessNetwork, 'ChildNodes'):
        for node in config.ZigbeeWirelessNetwork.ChildNodes:
            Hfile.write("\n/* Node '%s' */\n" % node.Name)
            Hfile.write('\n/* Endpoints */\n')
            for endpoint in node.Endpoints:
                id = int(endpoint.Id, 0)
                Hfile.write('#define %s_%s_ENDPOINT    (%d)\n' % (node.Name.upper(), endpoint.Name.upper(), id))

    Hfile.write('/* Table Sizes */\n')
    if hasattr(configNode, 'BindingTable'):
        BindTableSize = int(configNode.BindingTable.Size, 0)
    else:
        BindTableSize = 0
    if hasattr(configNode, 'GroupTable'):
        groupTableSize = int(configNode.GroupTable.Size, 0)
    else:
        groupTableSize = 0
    if hasattr(configNode, 'ChildTableSize'):
        childTableSize = int(configNode.ChildTableSize, 0)
    else:
        childTableSize = 0
    channelMaskListCount = 0
    if hasattr(configNode, 'MacInterfaceList'):
        for interface in configNode.MacInterfaceList.MacInterface:
            channelMaskListCount += int(interface.ChannelListSize)

    else:
        channelMaskListCount = 0
    Hfile.write(
        '#define ZPS_NEIGHBOUR_TABLE_SIZE      (%d)\n' %
        int(configNode.ActiveNeighbourTableSize, 0))
    Hfile.write(
        '#define ZPS_ADDRESS_MAP_TABLE_SIZE    (%d)\n' %
        int(configNode.AddressMapTableSize, 0))
    Hfile.write(
        '#define ZPS_ROUTING_TABLE_SIZE        (%d)\n' %
        int(configNode.RoutingTableSize, 0))
    Hfile.write(
        '#define ZPS_MAC_ADDRESS_TABLE_SIZE    (%d)\n' %
        int(configNode.MacTableSize, 0))
    Hfile.write('#define ZPS_BINDING_TABLE_SIZE        (%d)\n' % BindTableSize)
    Hfile.write('#define ZPS_GROUP_TABLE_SIZE          (%d)\n' % groupTableSize)
    Hfile.write('#define ZPS_CHILD_TABLE_SIZE          (%d)\n' % childTableSize)
    Hfile.write(
        '#define ZPS_MAX_CHANNEL_LIST_SIZE     (%d)\n' % channelMaskListCount,
    )
    Hfile.write(
        '\n'
        '/****************************************************************************/\n'
        '/***        Type Definitions                                              ***/\n'
        '/****************************************************************************/\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        External Variables                                            ***/\n'
        '/****************************************************************************/\n'
        '\n'
        'extern void *g_pvApl;\n'
        '\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        Exported Functions                                            ***/\n'
        '/****************************************************************************/\n'
        'PUBLIC void* ZPS_vGetGpContext(void);\n'
        '/****************************************************************************/\n'
        '/****************************************************************************/\n'
        '/****************************************************************************/\n'
        '\n'
        '#endif\n'
    )
    Hfile.close()
    if os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_READONLY)


def outputDefaultServerInitParams(file, node):
    apdu = findAPdu(node.xml_parent.xml_parent, node.OutputAPdu)
    if None != apdu:
        file.write('&s_s%sContext, %s' % (node.xml_qname, apdu.Name))
    else:
        print("WARNING: Server '%s' has no output APDU defined.\n" % node.xml_qname)
    return


def outputDefaultServerInitParamTypes(file):
    file.write('void *, PDUM_thAPdu ')


def outputEndDeviceBindServerInitParams(file, node):
    apdu = findAPdu(node.xml_parent.xml_parent, node.OutputAPdu)
    if None != apdu:
        file.write('&s_s%sContext, %s, %d, %d' % (
        node.xml_qname, apdu.Name, int(node.Timeout, 0) * 62500, int(node.BindNumRetries, 0)))
    else:
        print("WARNING: Server '%s' has no output APDU defined.\n" % node.xml_qname)
    return


def outputEndDeviceBindServerInitParamTypes(file):
    file.write('void *, PDUM_thAPdu , uint32 , uint8 ')


def outputDeviceAnnceServerInitParams(file, node):
    file.write('&s_s%sContext' % node.xml_qname)


def outputDeviceAnnceServerInitParamTypes(file):
    file.write('void *')


def outputMgmtNWKUpdateServerInitParams(file, node):
    apdu = findAPdu(node.xml_parent.xml_parent, node.OutputAPdu)
    if None != apdu:
        file.write('&s_s%sContext, %s, &s_sApl' % (node.xml_qname, apdu.Name))
    else:
        print("WARNING: Server '%s' has no output APDU defined.\n" % node.xml_qname)
    return


def outputMgmtNWKUpdateInitParamTypes(file):
    file.write('void *, PDUM_thAPdu , void *')


def outputBindRequestServerInitParams(file, node):
    TimeInterval = int(node.TimeInterval, 0)
    NumOfSimRequests = int(node.SimultaneousRequests, 0)
    file.write('&s_s%sContext, %d, %d, %s' % (
    node.xml_qname, TimeInterval, NumOfSimRequests, 's_sBindRequestServerAcksDcfmContext'))


def outputBindRequestServerInitParamTypes(file):
    file.write('void *, uint8, uint8, zps_tsZdoServerConfAckContext* ')


zdoServers = {'EndDeviceBindServer': (
    outputEndDeviceBindServerInitParams, outputEndDeviceBindServerInitParamTypes),
    'DefaultServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'DeviceAnnceServer': (
        outputDeviceAnnceServerInitParams, outputDeviceAnnceServerInitParamTypes),
    'ActiveEpServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'NwkAddrServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'IeeeAddrServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'SystemServerDiscoveryServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'PermitJoiningServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'NodeDescServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'PowerDescServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'MatchDescServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'SimpleDescServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'MgmtLqiServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'MgmtRtgServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'MgmtLeaveServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'MgmtNWKUpdateServer': (
        outputMgmtNWKUpdateServerInitParams, outputMgmtNWKUpdateInitParamTypes),
    'MgmtBindServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'BindUnbindServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'ExtendedActiveEpServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'ExtendedSimpleDescServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'ZdoClient': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'BindRequestServer': (
        outputBindRequestServerInitParams, outputBindRequestServerInitParamTypes),
    'ParentAnnceServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'MgmtMibIeeeServer': (
        outputDefaultServerInitParams, outputDefaultServerInitParamTypes),
    'MgmtNWKEnhanceUpdateServer': (
        outputMgmtNWKUpdateServerInitParams, outputMgmtNWKUpdateInitParamTypes)}
patchFunctions = [
    'vHandleEndpointInd',
    'vHandleApsdeDataInd',
    'vHandleApsdeDataDcfm',
    'u32GetScanChannels',
    'eStartNetworkFormation',
    'eStartNetworkDiscovery',
    'eStartRouter',
    'vHandleNetworkFormation',
    'vHandleNetworkDiscovery',
    'vHandleJoin',
    'vHandleJoinInd',
    'vHandleLeaveInd',
    'vHandleLeaveCfm',
    'vHandleNwkStatusInd',
    'vHandleRemoveDeviceIndication',
    'vHandleSwitchKeyIndication',
    'vHandleUpdateDeviceIndication',
    'vHandleTransportKeyIndication']
exeFSP = os.path.abspath(sys.executable)
if os.name == 'nt':
    d = win32api.GetFileVersionInfo(exeFSP, '\\')
    version = '%d.%d.%d' % (
    d['FileVersionMS'] / (256 * 256), d['FileVersionMS'] % (256 * 256), d['FileVersionLS'] / (256 * 256))
else:
    version = 'x.x.x'
if '' == options.zigbeeNodeName:
    print('ERROR: A node must be specified.\n')
    sys.exit(9)
OptionalFeatures = 0
if options.OptionalFeatures:
    config = bindery.parse(options.configFilename, validate=False)
    node = findNode(options.zigbeeNodeName)
    if hasattr(node, 'InterPAN'):
        if 'true' == node.InterPAN.lower():
            OptionalFeatures |= 1
    if hasattr(node, 'GreenPowerSupport'):
        if 'true' == node.GreenPowerSupport.lower():
            OptionalFeatures |= 2
    print(OptionalFeatures)
    sys.exit(0)
print('ZPSConfig - Zigbee Protocol Stack Configuration Tool v%s Build %s\n' % (version, '93315M'))
sys.stdout.flush()
if len(sys.argv) <= 1:
    print('\n\tThis software is owned by Jennic and/or its supplier and is protected\n\tunder applicable copyright laws. All rights are reserved. We grant You,\n\tand any third parties, a license to use this software solely and\n\texclusively on Jennic products. You, and any third parties must reproduce\n\tthe copyright and warranty notice and any other legend of ownership on each\n\tcopy or partial copy of the software.\n\t\n\tTHIS SOFTWARE IS PROVIDED "AS IS". JENNIC MAKES NO WARRANTIES, WHETHER\n\tEXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED\n\tWARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE,\n\tACCURACY OR LACK OF NEGLIGENCE. JENNIC SHALL NOT, IN ANY CIRCUMSTANCES,\n\tBE LIABLE FOR ANY DAMAGES, INCLUDING, BUT NOT LIMITED TO, SPECIAL,\n\tINCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER.\n\n\t(c) Copyright Jennic Ltd 2008. All rights reserved.\n')
    print('For help: %s --help' % sys.argv[0])
    sys.exit(0)
if None == options.configFilename:
    print('ERROR: a configuration file must be specified.\n')
    sys.exit(2)
if not os.path.exists(options.configFilename):
    print("ERROR: unable to open configuration file '%s'.\n" % options.configFilename)
    sys.exit(3)
if not os.path.exists(options.zigbeeNwkLibFSP):
    print("ERROR: unable to locate Zigbee target library file '%s'.\n" % options.zigbeeNwkLibFSP)
    sys.exit(4)
if not os.path.exists(options.zigbeeAplLibFSP):
    print("ERROR: unable to locate Zigbee target library file '%s'.\n" % options.zigbeeAplLibFSP)
    sys.exit(5)
if None != options.outputDir and not os.path.exists(options.outputDir):
    print("ERROR: Output directory '%s' does not exist.\n" % options.outputDir)
    sys.exit(6)
if not os.path.exists(options.ToolsDir):
    print("ERROR: unable to locate Compiler Tools directory '%s'.\n" % options.ToolsDir)
    sys.exit(7)
if options.endian == 'BIG_ENDIAN':
    objdump = os.path.normpath(os.path.join(options.ToolsDir, 'bin', 'ba-elf-objdump'))
elif os.name == 'nt':
    objdump = os.path.normpath(os.path.join(options.ToolsDir, 'bin', 'arm-none-eabi-objdump'))
else:
    objdump = os.path.normpath(os.path.join(options.ToolsDir, 'bin', 'arm-none-eabi-objdump'))
config = bindery.parse(options.configFilename, validate=False)
if '' == options.zigbeeNodeName:
    print('ERROR: A node must be specified.\n')
    sys.exit(9)
if validateConfiguration(options.zigbeeNodeName):
    node = findNode(options.zigbeeNodeName)
    outputHeader(options.outputDir, node)
    outputC(options.outputDir, node, options.endian)
    print('Done.\n')
    sys.exit(0)
else:
    sys.exit(1)
