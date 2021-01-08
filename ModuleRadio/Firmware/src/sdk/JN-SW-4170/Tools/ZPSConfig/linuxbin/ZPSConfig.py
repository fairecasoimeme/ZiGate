#!/usr/bin/env python3

import os
import re
import sys
import subprocess
import struct
import datetime
from optparse import OptionParser

import xmltodict

if os.name == 'nt':
    import win32api, win32con

parser = OptionParser()
parser.add_option(
    '-n',
    '--node-name',
    dest='zigbee_node_name',
    default='',
    help='Name of node to generate configuration for.',
)
parser.add_option(
    '-t',
    '--target',
    dest='target_hardware',
    default='JN5139',
    help='Target hardware platform for node',
)
parser.add_option(
    '-o',
    '--output',
    dest='output_dir',
    default=os.path.curdir,
    help='Path to output the configuration into.',
)
parser.add_option(
    '-f',
    '--config-file',
    dest='config_filename',
    help='Configuration file',
)
parser.add_option(
    '-l',
    '--zigbee-nwk-lib',
    dest='zigbee_nwk_lib_fsp',
    default='libZPSNWK_JN513x.a',
    help='Zigbee target software library.',
)
parser.add_option(
    '-e',
    '--Endian',
    dest='endian',
    type='string',
    default='BIG_ENDIAN',
    help='Endian of the processor.',
)
parser.add_option(
    '-a',
    '--zigbee-apl-lib',
    dest='zigbee_apl_lib_fsp',
    default='libZPSAPL_JN513x.a',
    help='Zigbee target software library.',
)
parser.add_option(
    '-y',
    '--optional_features',
    action='store_true',
    dest='optional_features',
    default=False,
    help='gets the optional features in the diagram',
)
parser.add_option(
    '-c',
    '--compiler-tools',
    dest='tools_dir',
    default='',
    help='specifies a path to the compiler tools',
)
(options, args) = parser.parse_args(sys.argv[1:])


def get_child_nodes(root):
    return [
        (name, item)
        for name, sublist in (
            (k, v) if isinstance(v, (list, tuple)) else (k, [v])
            for k, v in root.items()
            if not k.startswith('@')
        )
        for item in sublist
    ]


def as_list(item):
    return item if isinstance(item, list) else [item]


def from_ns(val):
    return val.split(":")[-1]


def get_lib_obj_size(objdump, lib, s_endian):
    proc = subprocess.Popen(
        [objdump, '-s', '-j.libobjsize', lib],
        stdout=subprocess.PIPE,
    )
    data = proc.communicate()[0]
    if str(data.__class__.__name__) == 'bytes':
        data = data.decode()
    idx = data.find('libobjsize')
    size = int('0x' + data[idx:idx + 100].split()[2], 16)
    if s_endian != 'BIG_ENDIAN':
        a = struct.pack('<I', size)
        size = struct.unpack('>I', a)[0]
    return size


def get_apl_server_context_size(server, objdump, lib, endian):
    try:
        proc = subprocess.Popen(
            [objdump, '-s', '-j.zps_apl_Zdo' + server + 'ContextSize', lib],
            stdout=subprocess.PIPE,
        )
        data = proc.communicate()[0]
        if str(data.__class__.__name__) == 'bytes':
            data = data.decode()
        idx = data.find('zps_apl_Zdo' + server + 'ContextSize')
        size = int('0x' + data[idx:idx + 100].split()[2], 16)
        if endian != 'BIG_ENDIAN':
            a = struct.pack('<I', size)
            size = struct.unpack('>I', a)[0]
        return size
    except Exception:  # noqa
        print("ERROR: Unable to locate '.zps_apl_Zdo%sContextSize' section in library file '%s'\n" % (server, lib))
        sys.exit(10)


def calculate_channel_mask(channel_mask):
    channel_mask_value = 0
    if 'true' == channel_mask['@Channel11'].lower():
        channel_mask_value |= 0x800
    if 'true' == channel_mask['@Channel12'].lower():
        channel_mask_value |= 0x1000
    if 'true' == channel_mask['@Channel13'].lower():
        channel_mask_value |= 0x2000
    if 'true' == channel_mask['@Channel14'].lower():
        channel_mask_value |= 0x4000
    if 'true' == channel_mask['@Channel15'].lower():
        channel_mask_value |= 0x8000
    if 'true' == channel_mask['@Channel16'].lower():
        channel_mask_value |= 0x10000
    if 'true' == channel_mask['@Channel17'].lower():
        channel_mask_value |= 0x20000
    if 'true' == channel_mask['@Channel18'].lower():
        channel_mask_value |= 0x20000
    if 'true' == channel_mask['@Channel19'].lower():
        channel_mask_value |= 0x80000
    if 'true' == channel_mask['@Channel20'].lower():
        channel_mask_value |= 0x100000
    if 'true' == channel_mask['@Channel21'].lower():
        channel_mask_value |= 0x200000
    if 'true' == channel_mask['@Channel22'].lower():
        channel_mask_value |= 0x400000
    if 'true' == channel_mask['@Channel23'].lower():
        channel_mask_value |= 0x800000
    if 'true' == channel_mask['@Channel24'].lower():
        channel_mask_value |= 0x1000000
    if 'true' == channel_mask['@Channel25'].lower():
        channel_mask_value |= 0x2000000
    if 'true' == channel_mask['@Channel26'].lower():
        channel_mask_value |= 0x4000000
    return channel_mask_value


def find_profile(profile_name):
    for profile in as_list(config['ZigbeeWirelessNetwork']['Profiles']):
        if profile['@Name'] == profile_name:
            return profile

    return None


def find_cluster(cluster_name):
    for profile in as_list(config['ZigbeeWirelessNetwork']['Profiles']):
        for cluster in as_list(profile['Clusters']):
            if cluster['@Name'] == cluster_name:
                return cluster

    return None


def find_network_key(id):
    ref = id.split('->', 2)
    _, node = find_node(ref[0])
    key_name = ref[1]
    if 'TrustCenter' in node:
        if 'Keys' in node['TrustCenter']:
            for elem in as_list(node['TrustCenter']['Keys']):
                if key_name == from_ns(elem['@type']):
                    return elem

    return


def network_key_str(key_node):
    key = int(key_node['@Key'], 0)
    key_str = ''
    for i in range(0, 16):
        if 0 != i:
            key_str += ', '
        key_str += '0x%02x' % ((key & 255 << 8 * i) >> 8 * i)

    return key_str


def find_apdu(node, apdu_id):
    if 'PDUConfiguration' in node:
        if 'APDUs' in node['PDUConfiguration']:
            for apdu in as_list(node['PDUConfiguration']['APDUs']):
                if apdu['@Id'] == apdu_id:
                    return apdu

    return


def find_node(node_name):
    if node_name == config['ZigbeeWirelessNetwork']['Coordinator']['@Name']:
        return 'Coordinator', config['ZigbeeWirelessNetwork']['Coordinator']
    for name, child_node in get_child_nodes(config['ZigbeeWirelessNetwork']):
        if node_name == child_node['@Name']:
            return name, child_node

    return None, None


def check_for_duplicate_names(nodes, n1):
    if '@Name' not in n1:
        return False
    for n2 in as_list(nodes):
        if n2 != n1 and '@Name' in n2 and n1['@Name'] == n2['@Name']:
            return True

    return False


def check_for_duplicate_ids(nodes, n1):
    for n2 in as_list(nodes):
        if n2 != n1 and int(n1['@Id'], 0) == int(n2['@Id'], 0):
            return True

    return False


def validate_configuration(node_name):
    name_check = re.compile(r'[a-zA-Z_][a-zA-Z_0-9]*')
    if 'ZigbeeWirelessNetwork' not in config:
        print("ERROR: The input configuration file does not have a 'ZigbeeWirelessNetwork' element.\n")
        return False
    root = config['ZigbeeWirelessNetwork']
    if '@Version' in root:
        if root['@Version'] != '1.1':
            print("ERROR: Unrecognised input file version '%s'\n" % root['@Version'])
            return False
    else:
        print('ERROR: The input file does not specify a version\n')
        return False
    if '@DefaultExtendedPANId' not in root:
        print(
            'WARNING: The input configuration file does contain a Default Extended '
            'PAN Id for the ZigBee PRO Wireless Network.\n')
    if '@MaxNumberNodes' not in config['ZigbeeWirelessNetwork']:
        print(
            'ERROR: The input configuration file does specify a MaxNumberNodes for the ZigBee PRO Wireless Network.\n')
    elif int(config['ZigbeeWirelessNetwork']['@MaxNumberNodes'], 0) < 2:
        print("ERROR: The 'MaxNumberNodes' attribute for a ZigBee PRO Wireless Network must be at least 2 nodes.\n")
        return False
    if 'Coordinator' not in root:
        print("WARNING: The input configuration file does not contain a 'Coordinator' node.\n")
    if 'Profiles' not in root:
        print('ERROR: The input configuration file does contain any Profile elements.\n')
        return False
    zdp_profile_found = False
    for p in as_list(config['ZigbeeWirelessNetwork']['Profiles']):
        if '@Id' not in p:
            if '@Name' in p:
                print("ERROR: Profile '%s' does not have an Id attribute." % p['@Name'])
            else:
                print('ERROR: A Profile element in the input configuration file does not have an Id or Name attribute.')
            return False
        profile_id = int(p['@Id'], 0)
        if '@Name' not in p:
            print("ERROR: Profile id '%d' does not have a Name attribute.\n" % profile_id)
            return False
        else:
            result = name_check.match(p['@Name'])
            if result.group(0) != p['@Name']:
                print("ERROR: Profile name '%s' is not a valid C identifier.\n" % p['@Name'])
                return False
        if profile_id == 0:
            zdp_profile_found = True
        elif profile_id > 65535 or profile_id < 0:
            print("ERROR: The Id of Profile '%s' must be in the range 1-65535" % p['@Name'])
        if check_for_duplicate_names(config['ZigbeeWirelessNetwork']['Profiles'], p):
            print(
                "ERROR: There are one or more Profiles with the name '%s'. "
                "Profiles must have unique names.\n" % p['@Name'])
            return False
        if check_for_duplicate_ids(config['ZigbeeWirelessNetwork']['Profiles'], p):
            print(
                "ERROR: There are one or more Profiles with the Id '%s'. "
                "Profiles must have unique Ids.\n" % p['@Id'])
            return False
        if 'Clusters' not in p:
            print("ERROR: The Profile '%s' does not contain any Cluster elements.\n" % p['@Name'])
            return False
        else:
            for cl in as_list(p['Clusters']):
                if '@Id' not in cl:
                    if '@Name' in cl:
                        print(
                            "ERROR: Cluster '%s' for Profile '%s' does not have an Id attribute." %
                            (cl['@Name'], p['@Name']))
                    else:
                        print("ERROR: A Cluster for Profile '%s' does not have an Id or Name attribute." % p['@Name'])
                    return False
                cluster_id = int(cl['@Id'], 0)
                if '@Name' not in cl:
                    print(
                        "ERROR: Cluster Id '%d' in Profile id '%s' does not have a Name attribute.\n" %
                        (cluster_id, p['@Name']))
                    return False
                else:
                    result = name_check.match(p['@Name'])
                    if result.group(0) != p['@Name']:
                        print("ERROR: Profile name '%s' is not a valid C identifier.\n" % p['@Name'])
                        return False
                if cluster_id > 65535 or cluster_id < 0:
                    print(
                        "ERROR: The Id of Cluster '%s' for Profile '%s' must be in the range 1-65535" %
                        (cl['@Name'], p['@Name']))

                if check_for_duplicate_names(p['Clusters'], cl):
                    print(
                        "ERROR: There are one or more Clusters with the name '%s' in Profile '%s'. "
                        "Clusters must have unique names.\n" % (cl['@Name'], p['@Name']))
                    return False
                if check_for_duplicate_ids(p['Clusters'], cl):
                    print(
                        "ERROR: There are one or more Clusters with the Id '%s' in Profile '%s'. "
                        "Clusters must have unique Ids.\n" % (cl['@Id'], p['@Name']))
                    return False

    if not zdp_profile_found:
        print('ERROR: A ZDP Profile is not present in the input configuration file.')
        return False
    all_nodes = []
    if 'Coordinator' in config['ZigbeeWirelessNetwork']:
        all_nodes.append(config['ZigbeeWirelessNetwork']['Coordinator'])
    all_nodes.extend([v for k, v in get_child_nodes(config['ZigbeeWirelessNetwork'])])
    for node in all_nodes:
        if '@Name' not in node:
            print('ERROR: A node in the input configuration file does not have a Name attribute.\n')
            return False
        else:
            result = name_check.match(node['@Name'])
            if result.group(0) != node['@Name']:
                print("ERROR: The node named '%s' in the input configuration file is not a valid C identifier.\n" %
                      node['@Name'])
                return False
        if check_for_duplicate_names(all_nodes, node):
            print("ERROR: There are one or more Nodes with the name '%s'. Nodes must have unique names.\n" % node[
                '@Name'])
            return False

    found_node_name, found_node = find_node(node_name)
    if found_node is None:
        print("ERROR: The input configuration file does not contain a node named '%s'.\n" % node_name)
        return False
    if 'Endpoints' not in found_node:
        print("ERROR: The input configuration for node '%s' does not contain any 'Endpoint' elements.\n" % node_name)
        return False
    zdp_ep_found = False
    for ep in as_list(found_node['Endpoints']):
        if '@Id' not in ep:
            if '@Name' in ep:
                print("ERROR: Endpoint '%s' for node '%s' does not have an Id attribute.\n" % (ep['@Name'], node_name))
            else:
                print("ERROR: An Endpoint for node '%s' does not have either an Id or Name attribute.\n" % node_name)
            return False
        if '@Name' not in ep:
            print("ERROR: Endpoint id '%d' for node '%s' does not have a Name attribute.\n" % (ep['@Id'], node_name))
            return False
        else:
            result = name_check.match(ep['@Name'])
            if result.group(0) != ep['@Name']:
                print(
                    "ERROR: Endpoint name '%s' for node '%s' is not a valid C identifier.\n" %
                    (ep['@Name'], node_name))
                return False
        ep_id = int(ep['@Id'], 0)
        if ep_id == 0:
            zdp_ep_found = True
        elif ep_id > 240:
            if ep_id != 242:
                print(
                    "ERROR: Endpoint '%s' for node '%s' has an invalid id '%d'. "
                    "Endpoint Ids must be in the range 1-240 or 242.\n" % (ep['@Name'], node_name, ep_id))
                return False
        if check_for_duplicate_names(found_node['Endpoints'], ep):
            print(
                "ERROR: There are one or more Endpoints with the name '%s' for node '%s'. "
                "Endpoints must have unique names.\n" % (ep['@Name'], found_node['@Name']))
            return False
        if check_for_duplicate_ids(found_node['Endpoints'], ep):
            print(
                "ERROR: There are one or more Endpoints with the Id '%s' for node '%s'. "
                "Endpoints must have unique Ids.\n" % (ep['@Id'], found_node['@Name']))
            return False
        if '@Profile' not in ep:
            print("ERROR: Endpoint '%s' on node '%s' does not specify a Profile.\n" % (ep['@Name'], node_name))
            return False
        io_cluster_found = False
        if 'InputClusters' in ep:
            io_cluster_found = True
            for cl in as_list(ep['InputClusters']):
                if '@Cluster' not in cl:
                    print(
                        "ERROR: An Input Cluster for endpoint '%s' on node '%s' "
                        "does not specify a Cluster.\n" % (ep['@Name'], node_name))
                    return False
                if '@Discoverable' not in cl:
                    print(
                        "WARNING: Input cluster '%s' for endpoint '%s' on node '%s' does not "
                        "have a 'Discoverable' attribute. Defaulting to discoverable.\n" % (
                            cl['@Cluster'],
                            ep['@Name'],
                            node_name,
                        ))
                if '@RxAPDU' not in cl:
                    print(
                        "WARNING: Input cluster '%s' for endpoint '%s' on node '%s' does not "
                        "specify an RxAPDU. No data can be received for this cluster.\n" % (
                            cl['@Cluster'], ep['@Name'], node_name))
                elif not find_apdu(found_node, cl['@RxAPDU']):
                    print(
                        "ERROR: Unable to find APDU '%s' for input cluster '%s'"
                        " for endpoint '%s' on node '%s'\n" %
                        (cl['@RxAPDU'], cl['@Cluster'], ep['@Name'], node_name))
                    return False

        if 'OutputClusters' in ep:
            io_cluster_found = True
            for cl in as_list(ep['OutputClusters']):
                if '@Cluster' not in cl:
                    print(
                        "WARNING: An Output Cluster for endpoint '%s' on node '%s' does not "
                        "specify a Cluster.\n" % (ep['@Name'], node_name))
                    return False
                if '@Discoverable' not in cl:
                    print(
                        "WARNING: Output cluster '%s' for endpoint '%s' on node '%s' does not "
                        "have a 'Discoverable' attribute. Defaulting to discoverable.\n" %
                        (cl['@Cluster'], ep['@Name'], node_name))
                if '@TxAPDUs' not in cl:
                    print(
                        "WARNING: Output cluster '%s' for endpoint '%s' on node '%s' "
                        "does not specify any TxAPDUs.\n" % (cl['@Cluster'], ep['@Name'], node_name))

        if not io_cluster_found:
            print(
                "WARNING: Endpoint '%s' id %d for node '%s' does not contain "
                "any input or output clusters.\n" % (ep['@Name'], ep_id, node_name))

    if not zdp_ep_found:
        print("ERROR: The input configuration for node '%s' does not contain a ZDP endpoint.\n" % node_name)
        return False
    if 'BindingTable' in found_node:
        if '@Size' in found_node['BindingTable']:
            if int(found_node['BindingTable']['@Size'], 0) < 1:
                print("ERROR: The Binding Table for node '%s' must contain at least 1 entry.\n" % node_name)
                return False
        else:
            print("ERROR: The Binding Table for node '%s' must specify a table size.\n" % node_name)
            return False
    if 'UserDescriptor' in found_node:
        if '@UserDescription' in found_node['UserDescriptor']:
            if len(found_node['UserDescriptor']['@UserDescription']) > 16:
                print(
                    "WARNING: The User Descriptor '%s' for node '%s' is longer than 16 "
                    "characters and will be truncated.\n" %
                    (found_node['UserDescriptor']['@UserDescription'], node_name))
            elif len(found_node['UserDescriptor']['@UserDescription']) <= 0:
                print("ERROR: The User Descriptor for node '%s' does not specify a User Description.\n" % node_name)
                return False
        else:
            print("ERROR: The User Descriptor for node '%s' must specify a descriptor.\n" % node_name)
            return False
    if 'PDUConfiguration' in found_node:
        if '@NumNPDUs' not in found_node['PDUConfiguration']:
            print("ERROR: The PDU Manager for node '%s' must have a NumNPDUs attribute.\n" % node_name)
            return False
        elif int(found_node['PDUConfiguration']['@NumNPDUs'], 0) < 8:
            print("ERROR: The PDU Manager for node '%s' must have at least 8 NPDUs configured" % node_name)
            return False
        if 'APDUs' not in found_node['PDUConfiguration']:
            print("ERROR: The PDU Manager for node '%s' does not have any APDUs.\n" % node_name)
            return False
    else:
        print("ERROR: The node '%s' must have a PDU Manager element.\n" % node_name)
        return False
    if 'GroupTable' in found_node:
        if '@Size' in found_node['GroupTable']:
            if int(found_node['GroupTable']['@Size'], 0) < 1:
                print("ERROR: The Group Table for node '%s' must contain at least 1 entry.\n" % node_name)
                return False
        else:
            print("ERROR: The Group Table for node '%s' must specify a table size.\n" % node_name)
            return False
    if 'NodeDescriptor' not in found_node:
        print("ERROR: A Node Descriptor must be specified for node '%s'.\n" % node_name)
        return False
    if 'NodePowerDescriptor' not in found_node:
        print("ERROR: A Node Power Descriptor must be specified for node '%s'.\n" % node_name)
        return False
    elif '@DefaultPowerSource' in found_node['NodePowerDescriptor']:
        if found_node['NodePowerDescriptor']['@DefaultPowerSource'].lower() == 'disposable battery':
            if '@DisposableBattery' not in found_node['NodePowerDescriptor'] or \
                    '@DisposableBattery' in found_node['NodePowerDescriptor'] and \
                    found_node['NodePowerDescriptor']['@DisposableBattery'].lower() == 'false':
                print(
                    "ERROR: Default power source 'Disposable Battery' is not available "
                    "in the Node Power Descriptor for node '%s'.\n" % node_name)
                return False
        if found_node['NodePowerDescriptor']['@DefaultPowerSource'].lower() == 'rechargeable battery':
            if '@RechargeableBattery' not in found_node['NodePowerDescriptor'] or \
                    '@RechargeableBattery' in found_node['NodePowerDescriptor'] and \
                    found_node['NodePowerDescriptor']['@RechargeableBattery'].lower() == 'false':
                print(
                    "ERROR: Default power source 'Rechargeable Battery' is not available "
                    "in the Node Power Descriptor for node '%s'.\n" % node_name)
                return False
        if found_node['NodePowerDescriptor']['@DefaultPowerSource'].lower() == 'constant power':
            if '@ConstantPower' not in found_node['NodePowerDescriptor'] or \
                    '@ConstantPower' in found_node['NodePowerDescriptor'] and \
                    found_node['NodePowerDescriptor']['@ConstantPower'].lower() == 'false':
                print(
                    "ERROR: Default power source 'Constant Power' is not available "
                    "in the Node Power Descriptor for node '%s'.\n" % node_name)
                return False
    if 'ZDOServers' not in found_node:
        print("ERROR: The node '%s' does not contain a ZDO Configuration.\n" % node_name)
        return False
    else:
        if 'ZdoClient' not in found_node['ZDOServers']:
            print("ERROR: The ZDO Configuration for node '%s' must contain a ZDO Client.\n" % node_name)
            return False
        if 'DeviceAnnceServer' not in found_node['ZDOServers']:
            print("ERROR: The ZDO Configuration for node '%s' must contain a Device Annce Server.\n" % node_name)
            return False
        if 'ActiveEpServer' not in found_node['ZDOServers']:
            print(
                "WARNING: The ZDO Configuration for node '%s' should contain a ActiveEpServer "
                "to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % node_name)
        if 'NwkAddrServer' not in found_node['ZDOServers']:
            print(
                "WARNING: The ZDO Configuration for node '%s' should contain a NwkAddrServer "
                "to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % node_name)
        if 'IeeeAddrServer' not in found_node['ZDOServers']:
            print(
                "WARNING: The ZDO Configuration for node '%s' should contain a IeeeAddrServer "
                "to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % node_name)
        if 'SystemServerDiscoveryServer' not in found_node['ZDOServers']:
            print(
                "WARNING: The ZDO Configuration for node '%s' should contain a SystemServerDiscoveryServer "
                "to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % node_name)
        if 'NodeDescServer' not in found_node['ZDOServers']:
            print(
                "WARNING: The ZDO Configuration for node '%s' should contain a NodeDescServer "
                "to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % node_name)
        if 'PowerDescServer' not in found_node['ZDOServers']:
            print(
                "WARNING: The ZDO Configuration for node '%s' should contain a PowerDescServer "
                "to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % node_name)
        if 'MatchDescServer' not in found_node['ZDOServers']:
            print(
                "WARNING: The ZDO Configuration for node '%s' should contain a MatchDescServer "
                "to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % node_name)
        if 'SimpleDescServer' not in found_node['ZDOServers']:
            print(
                "WARNING: The ZDO Configuration for node '%s' should contain a SimpleDescServer "
                "to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % node_name)
        if 'MgmtLqiServer' not in found_node['ZDOServers']:
            print(
                "WARNING: The ZDO Configuration for node '%s' should contain a MgmtLqiServer "
                "to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % node_name)
        if 'MgmtLeaveServer' not in found_node['ZDOServers'] and 'Coordinator' != found_node_name:
            print(
                "WARNING: The ZDO Configuration for node '%s' should contain a MgmtLeaveServer "
                "to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % node_name)
        if 'MgmtNWKUpdateServer' not in found_node['ZDOServers']:
            print(
                    "WARNING: The ZDO Configuration for node '%s' should contain a MgmtNWKUpdateServer "
                    "to meet the requirements for a ZigBee Compliant Platform (ZCP). \n" % node_name)
        if 'Coordinator' == found_node_name or \
                'ChildNodes' == found_node_name and 'Router' == from_ns(found_node['@type']):
            if 'PermitJoiningServer' not in found_node['ZDOServers']:
                print(
                    "WARNING: The ZDO Configuration for node '%s' should contain a "
                    "PermitJoiningServer to meet the requirements for a "
                    "ZigBee Compliant Platform (ZCP). \n" % node_name)
            if 'MgmtRtgServer' not in found_node['ZDOServers']:
                print(
                    "WARNING: The ZDO Configuration for node '%s' should contain a "
                    "MgmtRtgServer to meet the requirements for a "
                    "ZigBee Compliant Platform (ZCP). \n" % node_name)
        if 'Coordinator' == found_node_name:
            if 'EndDeviceBindServer' not in found_node['ZDOServers']:
                print(
                    "WARNING: The ZDO Configuration for node '%s' should contain a "
                    "EndDeviceBindServer to meet the requirements for a "
                    "ZigBee Compliant Platform (ZCP). \n" % node_name)
        if 'Coordinator' == found_node_name:
            if 'MgmtMibIeeeServer' not in found_node['ZDOServers']:
                print(
                    "WARNING: The ZDO Configuration for node '%s' should contain a "
                    "MgmtMibIeeeServer to meet the requirements for a "
                    "ZigBee Compliant Platform (ZCP). \n" % node_name)
    dns = int(found_node['@MacTableSize'], 0)
    if '@MaxNumSimultaneousApsdeAckReq' in found_node:
        if int(found_node['@MaxNumSimultaneousApsdeAckReq'], 0) == 0:
            print(
                'WARNING: No Apsde requests with acknowledgements may be made because '
                'MaxNumSimultaneousApsdeAckReq is set to 0.\n' % node_name)
        if '@MaxNumSimultaneousApsdeReq' not in found_node:
            print(
                'ERROR: No Apsde requests with acknowledgements may be made because '
                'MaxNumSimultaneousApsdeAckReq is set to 0.\n' % node_name)
            return False
        elif int(found_node['@MaxNumSimultaneousApsdeReq'], 0) < 1:
            print("ERROR: MaxNumSimultaneousApsdeReq must be at least 1 or node '%s'.\n" % node_name)
            return False
        if '@DefaultCallbackName' not in found_node:
            print("ERROR: DefaultCallbackName is not set for node '%s'\n" % node_name)
            return False
        else:
            result = name_check.match(found_node['@DefaultCallbackName'])
            if result.group(0) != found_node['@DefaultCallbackName']:
                print("ERROR: DefaultCallbackName is not a valid C identifier for node '%s'\n" % node_name)
                return False
        if 'Coordinator' == found_node_name:
            if found_node['@apsDesignatedCoordinator'].lower() != 'true':
                print("ERROR: apsDesignatedCoordinator must be set to true for Coordinator node '%s'\n" % node_name)
                return False
        if '@apsMaxWindowSize' not in found_node:
            print("ERROR: apsMaxWindowSize is not set for node '%s'\n" % node_name)
            return False
        else:
            val = int(found_node['@apsMaxWindowSize'], 0)
            if val < 1 or val > 8:
                print("ERROR: apsMaxWindowSize must be in the range 1-8 for node '%s'\n" % node_name)
                return False
        if '@apsInterframeDelay' not in found_node:
            print("ERROR: apsInterframeDelay is not set for node '%s'\n" % node_name)
            return False
        else:
            val = int(found_node['@apsInterframeDelay'], 0)
            if val < 10 or val > 255:
                print("ERROR: apsInterframeDelay must be in the range 10-255 for node '%s'\n" % node_name)
                return False
        if '@APSDuplicateTableSize' not in found_node:
            print("ERROR: APSDuplicateTableSize is not set for node '%s'\n" % node_name)
            return False
        elif int(found_node['@APSDuplicateTableSize'], 0) < 1:
            print("ERROR: APSDuplicateTableSize must be at least 1 for node '%s'\n" % node_name)
            return False
        if '@apsSecurityTimeoutPeriod' not in found_node:
            print("ERROR: apsSecurityTimeoutPeriod is not set for node '%s'\n" % node_name)
            return False
        elif int(found_node['@apsSecurityTimeoutPeriod'], 0) < 1000:
            print("ERROR: apsSecurityTimeoutPeriod must be at least 1000 ms for node '%s'\n" % node_name)
            return False
        if '@apsUseExtPANId' not in found_node:
            print("ERROR: apsUseExtPANId is not set for node '%s'\n" % node_name)
            return False
        else:
            use_epid = int(found_node['@apsUseExtPANId'], 0)
            default_epid = int(config['ZigbeeWirelessNetwork']['@DefaultExtendedPANId'], 0)
            if 0 != use_epid and use_epid != default_epid:
                print(
                    "WARNING: apsUseExtPANId for node '%s' does not match the DefaultExtenededPANId "
                    "setting of the ZigBee Wireless Network.\n" % node_name)
        if '@apsNonMemberRadius' not in found_node:
            print("ERROR: apsNonMemberRadius is not set for node '%s'\n" % node_name)
            return False
        else:
            nmr = int(found_node['@apsNonMemberRadius'], 0)
            if nmr < 0 or nmr > 7:
                print("ERROR: apsNonMemberRadius for node '%s' must be in the range 0-7.\n" % node_name)
                return False
        if 'Coordinator' == found_node_name or \
                'ChildNodes' == found_node_name and 'Router' == from_ns(found_node['@type']):
            if '@PermitJoiningTime' not in found_node:
                print("ERROR: PermitJoiningTime is not set for node '%s'\n" % node_name)
                return False
            else:
                pjt = int(found_node['@PermitJoiningTime'], 0)
                if pjt < 0 or pjt > 255:
                    print("ERROR: PermitJoiningTime for node '%s' must be in the range 0-255.\n" % node_name)
                    return False
        if '@SecurityEnabled' not in found_node:
            print("ERROR: SecurityEnabled is not set for node '%s'\n" % node_name)
            return False
        elif found_node['@SecurityEnabled'].lower() != \
                config['ZigbeeWirelessNetwork']['@DefaultSecurityEnabled'].lower():
            print(
                "WARNING: SecurityEnabled for node '%s' does not match the DefaultSecurityEnabled "
                "setting for the ZigBeeWirelessNetwork.\n" % node_name)
        if '@AddressMapTableSize' not in found_node:
            print("ERROR: AddressMapTableSize is not set for node '%s'\n" % node_name)
            return False
        else:
            amts = int(found_node['@AddressMapTableSize'], 0)
            if amts > dns:
                print(
                    "ERROR: The AddressMapTableSize for node '%s' is greater then the MacTable "
                    "setting for the ZigBeeWirelessNetwork.\n" % node_name)
                return False
        if '@ActiveNeighbourTableSize' not in found_node:
            print("ERROR: ActiveNeighbourTableSize is not set for node '%s'\n" % node_name)
            return False
        else:
            ants = int(found_node['@ActiveNeighbourTableSize'], 0)
            amts = int(found_node['@AddressMapTableSize'], 0)
            if ants > dns:
                print(
                    "ERROR: The ActiveNeighbourTableSize for node '%s' is greater then the MacTable "
                    "setting for the ZigBeeWirelessNetwork.\n" % node_name)
                return False
            elif ants < 1:
                print("ERROR: The ActiveNeighbourTableSize for node '%s' must be at least 1.\n" % node_name)
                return False
        if '@DiscoveryNeighbourTableSize' not in found_node:
            print("ERROR: DiscoveryNeighbourTableSize is not set for node '%s'\n" % node_name)
            return False
        else:
            dnts = int(found_node['@DiscoveryNeighbourTableSize'], 0)
            if dnts < 1:
                print("ERROR: The DiscoveryNeighbourTableSize for node '%s' must be at least 1.\n" % node_name)
                return False
        if '@RouteDiscoveryTableSize' not in found_node:
            print("ERROR: RouteDiscoveryTableSize is not set for node '%s'\n" % node_name)
            return False
        else:
            rdts = int(found_node['@RouteDiscoveryTableSize'], 0)
            if rdts < 1:
                print("ERROR: The RouteDiscoveryTableSize for node '%s' must be at least 1.\n" % node_name)
                return False
        if '@RoutingTableSize' not in found_node:
            print("ERROR: RoutingTableSize is not set for node '%s'\n" % node_name)
            return False
        else:
            rts = int(found_node['@RoutingTableSize'], 0)
            if rts < 1:
                print("ERROR: The RoutingTableSize for node '%s' must be at least 1.\n" % node_name)
                return False
        if '@BroadcastTransactionTableSize' not in found_node:
            print("ERROR: BroadcastTransactionTableSize is not set for node '%s'\n" % node_name)
            return False
        else:
            btts = int(found_node['@BroadcastTransactionTableSize'], 0)
            if btts < 1:
                print("ERROR: The BroadcastTransactionTableSize for node '%s' must be at least 1.\n" % node_name)
                return False
        if '@RouteRecordTableSize' not in found_node:
            print("ERROR: RouteRecordTableSize is not set for node '%s'\n" % node_name)
            return False
        else:
            btts = int(found_node['@RouteRecordTableSize'], 0)
            if btts < 1:
                print("ERROR: The RouteRecordTableSize for node '%s' must be at least 1.\n" % node_name)
                return False
        if found_node['@SecurityEnabled'].lower() == 'true':
            if '@SecurityMaterialSets' not in found_node:
                print(
                    "ERROR: SecurityMaterialSets is not set for node '%s' "
                    "with SecurityEnabled set to true.\n" % node_name)
                return False
            elif int(found_node['@SecurityMaterialSets'], 0) < 1:
                print(
                    "ERROR: SecurityMaterialSets must be at least 1 for node '%s' "
                    "with SecurityEnabled set to true.\n" % node_name)
                return False
            return True
        if '@Sleeping' in found_node:
            if found_node['@Sleeping'].lower() == 'true':
                if '@APSPollPeriod' not in found_node:
                    print("ERROR: APSPollPeriod is not set for node '%s'\n" % node_name)
                    return False
                else:
                    ftpp = int(found_node['@APSAckPollPeriod'], 0)
                    if ftpp < 25:
                        print("ERROR: The APSPollPeriod for node '%s' must be at least 25ms.\n" % node_name)
                        return False
                print(
                    'NumPollFailuresBeforeRejoin' in found_node or
                    "ERROR: NumPollFailuresBeforeRejoin is not set for node '%s'\n" % node_name)
                return False
            else:
                npfbr = int(found_node['@NumPollFailuresBeforeRejoin'], 0)
                if npfbr == 0:
                    print(
                        "WARNING: The NumPollFailuresBeforeRejoin for node '%s' is set to 0. "
                        "The node will not rejoin if its parent is lost.\n" % node_name)
            if '@ScanDuration' in found_node:
                sd = int(found_node['@ScanDuration'], 0)
                if sd < 2 or sd > 5:
                    print("ERROR: The ScanDuration for node '%s' must be in the range 2-5\n" % node_name)
                    return False
    return


def output_c(output_dir, config_node_name, config_node, endian):
    """
    :type output_dir: str
    :type config_node_name: str
    :type config_node: dict
    :type endian: str
    """
    fsp = os.path.join(output_dir, 'zps_gen.c')
    if os.path.exists(fsp) and os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_NORMAL)
    c_file = open(fsp, 'w')
    c_file.write(
        '/****************************************************************************\n'
        ' *\n'
        ' *                 THIS IS A GENERATED FILE. DO NOT EDIT!\n'
        ' *\n'
        ' * MODULE:         ZPSConfig\n'
        ' *\n'
        ' * COMPONENT:      zps_gen.c\n'
        ' *\n'
        ' * DATE:           %s\n'
        ' *\n'
        ' * AUTHOR:         Jennic Zigbee Protocol Stack Configuration Tool\n'
        ' *\n'
        ' * DESCRIPTION:    ZPS definitions\n'
        ' *\n'
        ' ****************************************************************************\n'
        ' *\n'
        ' * This software is owned by NXP B.V. and/or its supplier and is protected\n'
        ' * under applicable copyright laws. All rights are reserved. We grant You,\n'
        ' * and any third parties, a license to use this software solely and\n'
        ' * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].\n'
        ' * You, and any third parties must reproduce the copyright and warranty notice\n'
        ' * and any other legend of ownership on each copy or partial copy of the\n'
        ' * software.\n'
        ' *\n'
        ' * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"\n'
        ' * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n'
        ' * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE\n'
        ' * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE\n'
        ' * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR\n'
        ' * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF\n'
        ' * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS\n'
        ' * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN\n'
        ' * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)\n'
        ' * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE\n'
        ' * POSSIBILITY OF SUCH DAMAGE.\n'
        ' *\n'
        ' * Copyright NXP B.V. 2016. All rights reserved\n'
        ' ****************************************************************************/\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        Include files                                                 ***/\n'
        '/****************************************************************************/\n'
        '\n'
        '#include <jendefs.h>\n'
        '#include <pdum_gen.h>\n'
        '#include "ZQueue.h"\n'
        '#include <zps_gen.h>\n'
        '\n'
        '#include "zps_apl.h"\n'
        '#include "zps_apl_aib.h"\n'
        '#include "zps_apl_af.h"\n'
        '\n' % datetime.datetime.ctime(datetime.datetime.now()),
    )
    c_file.write(
        '\n'
        '/****************************************************************************/\n'
        '/***        Macro Definitions                                             ***/\n'
        '/****************************************************************************/\n'
        '\n'
        '#define COMPILE_TIME_ASSERT(pred)    switch(0){case 0:case pred:;}\n'
        '\n'
        '\n'
        '#define ZPS_APL_ZDO_VSOUI_LENGTH\t\t3\n'
        '/****************************************************************************/\n'
        '/***        Type Definitions                                              ***/\n'
        '/****************************************************************************/\n'
        '\n'
        '/*** ZDP Context **************************************************/\n'
        '\n'
        'typedef struct {\n'
        '    uint8 u8ZdpSeqNum;\n'
        '} zps_tsZdpContext;\n'
        '\n'
        '/*** ZDO Context **************************************************/\n'
        '\n'
        'typedef bool (*zps_tprAplZdoServer)(void *pvApl, void *pvServerContext, ZPS_tsAfEvent *psZdoServerEvent);\n'
        '\n'
        'typedef struct {\n'
        '    zps_tprAplZdoServer prServer;\n'
        '    void *pvServerContext;\n'
        '} zps_tsAplZdoServer;\n'
        '\n'
        'typedef struct\n'
        '{\n'
        '    uint8               au8Key[ZPS_NWK_KEY_LENGTH];\n'
        '    uint8               u8KeySeqNum;\n'
        '    uint8               u8KeyType;\n'
        '} zps_tsAplZdoInitSecKey;\n'
        '\n'
        'typedef struct {\n'
        '    uint64 u64InitiatorAddr;\n'
        '    uint64 u64ResponderAddr;\n'
        '    ZPS_tsTsvTimer sTimer;\n'
        '    uint8 au8Key[ZPS_NWK_KEY_LENGTH];\n'
        '} zps_tsRequestKeyRequests;\n'
        '\n'
        '\n'
        'typedef struct {\n'
        '    uint8 au8VsOUIBytes[ZPS_APL_ZDO_VSOUI_LENGTH] __attribute__ ((aligned (16)));\n'
        '    uint8 eNetworkState; /* ZPS_teZdoNetworkState */\n'
        '    uint8 eZdoDeviceType; /* ZPS_teZdoDeviceType */\n'
        '    uint8 eNwkKeyState; /* ZPS_teZdoNwkKeyState */\n'
        '    uint8 u8PermitJoinTime;\n'
        '    uint8 u8StackProfile;\n'
        '    uint8 u8ZigbeeVersion;\n'
        '    uint8 u8ScanDuration;\n'
        '    bool_t bLookupTCAddr;\n'
        '    const zps_tsAplZdoServer *psZdoServers;\n'
        '    void (*prvZdoServersInit)(void);\n'
        '    ZPS_tsTsvTimer sAuthenticationTimer;\n'
        '    ZPS_tsTsvTimer sAuthenticationPollTimer;\n'
        '    uint8 u8NumPollFailures;\n'
        '    uint8 u8MaxNumPollFailures;\n'
        '    bool_t bSecurityDisabled;\n'
        '    zps_tsAplZdoInitSecKey *psInitSecKey;\n'
        '    uint8 u8DevicePermissions;\n'
        '    bool_t (*prvZdoReqFilter)(uint16);\n'
        '    bool (*pfzps_bAplZdoBindRequestServer)(void *,\n'
        '            void *,\n'
        '            ZPS_tsAfEvent *);\n'
        '    zps_tsRequestKeyRequests *psRequestKeyReqs;\n'
        '    uint32 u32ReqKeyTimeout;\n'
        '    uint8 u8MaxNumSimulRequestKeyReqs;    \n'
        '    \n'
        '} zps_tsZdoContext;\n'
        '\n'
        '/**** Context for the ZDO servers data confirms and acks***********/\n'
        '\n'
        'typedef struct {\n'
        '    uint8 eState;\n'
        '    uint8 u8SeqNum;\n'
        '    uint8 u8ConfAck;\n'
        '} zps_tsZdoServerConfAckContext;\n'
        '\n'
        '/*** Trust Center Context *****************************************/\n'
        '\n'
        'typedef struct\n'
        '{\n'
        '    uint16 u16AddrLkup;\n'
        '    ZPS_teDevicePermissions eDevPermissions;\n'
        '} zps_tsAplTCDeviceTable;\n'
        '\n'
        'typedef struct\n'
        '{\n'
        '    zps_tsAplTCDeviceTable *asTCDeviceTable;\n'
        '    uint16  u16SizeOfTCDeviceTable;\n'
        '} zps_tsAplTCib;\n'
        '\n'
        '\n'
        'typedef struct\n'
        '{\n'
        '    void (*prvTrustCenterInit)(void*);\n'
        '    void (*prvTrustCenterUpdateDevice)(void*, uint64, uint64, uint8, uint16);\n'
        '    void (*prvTrustCenterRequestKey)(void*, uint64, uint8, uint64);\n'
        '    zps_tsAplTCib sTCib;\n'
        '    bool_t bTcOverride;\n'
        '    bool_t bChangeOverride;\n'
        '} zps_tsTrustCenterContext;\n'
        '\n'
        '/*** AF Context ***************************************************/\n'
        '\n'
        'typedef struct zps_tsAplAfDynamicContext zps_tsAplAfDynamicContext;\n'
        '\n'
        'typedef struct _zps_tsAplAfSimpleDescCont\n'
        '{\n'
        '    ZPS_tsAplAfSimpleDescriptor sSimpleDesc;\n'
        '    const PDUM_thAPdu *phAPduInClusters;\n'
        '    bool_t bEnabled;\n'
        '} zps_tsAplAfSimpleDescCont;\n'
        '\n'
        'typedef struct {\n'
        '    zps_tsAplAfDynamicContext *psDynamicContext;\n'
        '    ZPS_tsAplAfNodeDescriptor *psNodeDescriptor;\n'
        '    ZPS_tsAplAfNodePowerDescriptor *psNodePowerDescriptor;\n'
        '    uint32 u32NumSimpleDescriptors;\n'
        '    zps_tsAplAfSimpleDescCont *psSimpleDescConts;\n'
        '    ZPS_tsAplAfUserDescriptor *psUserDescriptor;\n'
        '    void* hOverrunMsg;   \n'
        '    uint8 zcp_u8FragApsAckValue;\n'
        '    uint8 zcp_u8FragBlockControl;\n'
        '} zps_tsAfContext;\n'
        '\n'
        '/*** APS Context **************************************************/\n'
        '\n'
        'typedef struct\n'
        '{\n'
        '    uint8 u8Type;\n'
        '    uint8 u8ParamLength;\n'
        '} ZPS_tsAplApsmeDcfmIndHdr;\n'
        '\n'
        'typedef struct\n'
        '{\n'
        '    uint8 u8Type;\n'
        '    uint8 u8ParamLength;\n'
        '} ZPS_tsAplApsdeDcfmIndHdr;\n'
        '\n'
        'typedef struct {\n'
        '    ZPS_tuAddress uDstAddr;\n'
        '    PDUM_thAPduInstance hAPduInst;\n'
        '    uint8 *pu8SeqCounter;\n'
        '    uint16 u16ProfileId;\n'
        '    uint16 u16ClusterId;\n'
        '    uint8 u8DstEndpoint;\n'
        '    uint8 u8SrcEndpoint;\n'
        '    uint8 u8Radius;\n'
        '    uint8 eDstAddrMode;\n'
        '    uint8 eTxOptions;\n'
        '} ZPS_tsAplApsdeReqData;\n'
        '\n'
        'typedef union\n'
        '{\n'
        '    ZPS_tsAplApsdeReqData  sReqData;\n'
        '} ZPS_tuAplApsdeReqRspParam;\n'
        '\n'
        'typedef struct\n'
        '{\n'
        '    uint8                 u8Type;\n'
        '    uint8                 u8ParamLength;\n'
        '    uint16                u16Pad;\n'
        '    ZPS_tuAplApsdeReqRspParam uParam;\n'
        '} ZPS_tsAplApsdeReqRsp;\n'
        '\n'
        'typedef struct\n'
        '{\n'
        '    struct {\n'
        '        uint32 u6Reserved       : 6;\n'
        '        uint32 u2Fragmentation  : 2;\n'
        '        uint32 u24Padding       : 24;\n'
        '    } sEFC;\n'
        '    uint8 u8BlockNum;\n'
        '    uint8 u8Ack;\n'
        '} zps_tsExtendedFrameControlField;\n'
        '\n'
        'typedef union {\n'
        '    struct {\n'
        '        uint8   u8DstEndpoint;\n'
        '        uint16  u16ClusterId;\n'
        '        uint16  u16ProfileId;\n'
        '        uint8   u8SrcEndpoint;\n'
        '        uint8   u8ApsCounter;\n'
        '    } sUnicast;\n'
        '\n'
        '    struct {\n'
        '            uint16  u16GroupAddr;\n'
        '            uint16  u16ClusterId;\n'
        '            uint16  u16ProfileId;\n'
        '            uint8   u8SrcEndpoint;\n'
        '            uint8   u8ApsCounter;\n'
        '        } sGroup;\n'
        '} zps_tuApsAddressingField;\n'
        '\n'
        'typedef struct {\n'
        '    uint16    *psDuplicateTableSrcAddr;\n'
        '    uint32    *psDuplicateTableHash;\n'
        '    uint8     *psDuplicateTableApsCnt;\n'
        '    uint8     u8TableIndex;\n'
        '} zps_tsApsDuplicateTable;\n'
        '\n'
        'typedef struct zps_tsMsgRecord_tag {\n'
        '    struct zps_tsMsgRecord_tag *psNext;\n'
        '    ZPS_tsAplApsdeReqRsp sApsdeReqRsp;\n'
        '    ZPS_tsTsvTimer sAckTimer;       /* ack timer */\n'
        '    uint8       u8ReTryCnt;\n'
        '    uint8       u8ApsCount;\n'
        '} zps_tsMsgRecord;\n'
        '\n'
        'typedef struct zps_tsDcfmRecord_tag{\n'
        '    union {\n'
        '        uint16 u16DstAddr;\n'
        '        uint64 u64DstAddr;\n'
        '    };\n'
        '    uint8   u8Handle;\n'
        '    uint8   u8SrcEp;\n'
        '    uint8   u8DstEp;\n'
        '    uint8   u8DstAddrMode;\n'
        '    uint8   u8SeqNum;\n'
        '} zps_tsDcfmRecord;\n'
        '\n'
        'typedef struct zps_tsDcfmRecordPool_tag{\n'
        '    zps_tsDcfmRecord *psDcfmRecords;\n'
        '    uint8 u8NextHandle;\n'
        '    uint8 u8NumRecords;\n'
        '} zps_tsDcfmRecordPool;\n'
        '\n'
        'typedef struct zps_tsFragmentTransmit_tag {\n'
        '    enum {\n'
        '        ZPS_FRAG_TX_STATE_IDLE,\n'
        '        ZPS_FRAG_TX_STATE_SENDING,\n'
        '        ZPS_FRAG_TX_STATE_RESENDING,\n'
        '        ZPS_FRAG_TX_STATE_WAIT_FOR_ACK\n'
        '    }eState;\n'
        '    PDUM_thAPduInstance hAPduInst;\n'
        '    uint16  u16DstAddress;\n'
        '    uint16  u16ProfileId;\n'
        '    uint16  u16ClusterId;\n'
        '    uint8   u8DstEndpoint;\n'
        '    uint8   u8SrcEndpoint;\n'
        '    uint8   u8Radius;\n'
        '    uint8   u8SeqNum;\n'
        '\n'
        '    ZPS_tsTsvTimer sAckTimer;\n'
        '    uint8   u8CurrentBlock;\n'
        '    uint8   u8SentBlocksInWindow;\n'
        '    uint8   u8MinBlockNumber;\n'
        '    uint8   u8MaxBlockNumber;\n'
        '    uint8   u8TotalBlocksToSend;\n'
        '    uint8   u8RetryCount;\n'
        '    uint8   u8AckedBlocksInWindow;\n'
        '    uint8   u8WindowSize;\n'
        '    uint8   u8BlockSize;\n'
        '    bool_t  bSecure;\n'
        '} zps_tsFragmentTransmit;\n'
        '\n'
        'typedef struct zps_tsfragTxPool_tag {\n'
        '    zps_tsFragmentTransmit *psFragTxRecords;\n'
        '    uint8   u8NumRecords;\n'
        '} zps_tsFragTxPool;\n'
        '\n'
        'typedef struct zps_tsFragmentReceive_tag {\n'
        '    enum {\n'
        '        ZPS_FRAG_RX_STATE_IDLE,\n'
        '        ZPS_FRAG_RX_STATE_RECEIVING,\n'
        '        ZPS_FRAG_RX_STATE_PERSISTING\n'
        '    }eState;\n'
        '    PDUM_thAPduInstance hAPduInst;\n'
        '    uint16  u16SrcAddress;\n'
        '    uint16  u16ProfileId;\n'
        '    uint16  u16ClusterId;\n'
        '    uint8   u8DstEndpoint;\n'
        '    uint8   u8SrcEndpoint;\n'
        '    uint8   u8SeqNum;\n'
        '\n'
        '    ZPS_tsTsvTimer  sWindowTimer;\n'
        '    PDUM_thNPdu     hNPduPrevious;\n'
        '    uint16  u16ReceivedBytes;\n'
        '    uint8   u8TotalBlocksToReceive;\n'
        '    uint8   u8ReceivedBlocksInWindow;\n'
        '    uint8   u8MinBlockNumber;\n'
        '    uint8   u8MaxBlockNumber;\n'
        '    uint8   u8HighestUnAckedBlock;\n'
        '    uint8   u8WindowSize;\n'
        '    uint8   u8BlockSize;\n'
        '    uint8   u8PreviousBlock;\n'
        '} zps_tsFragmentReceive;\n'
        '\n'
        'typedef struct zps_tsfragRxPool_tag {\n'
        '    zps_tsFragmentReceive *psFragRxRecords;\n'
        '    uint8   u8NumRecords;\n'
        '    uint8   u8PersistanceTime;\n'
        '} zps_tsFragRxPool;\n'
        '\n'
        'typedef struct zps_tsApsPollTimer {\n'
        '    ZPS_tsTsvTimer sPollTimer;\n'
        '    uint16 u16PollInterval;\n'
        '    uint8 u8PollActive;\n'
        '} zps_tsApsPollTimer;\n'
        '\n'
        'typedef struct zps_tsApsmeCmdContainer {\n'
        '    struct zps_tsApsmeCmdContainer *psNext; /* must be first element of struct */\n'
        '    ZPS_tsNwkNldeReqRsp sNldeReqRsp;\n'
        '    ZPS_tsTsvTimer sTimer;\n'
        '    PDUM_thNPdu hNPduCopy;\n'
        '    uint8 u8Retries;\n'
        '} zps_tsApsmeCmdContainer;\n'
        '\n'
        'typedef struct {\n'
        '    zps_tsApsmeCmdContainer *psFreeList;\n'
        '    zps_tsApsmeCmdContainer *psSubmittedList;\n'
        '} zps_tsApsmeCmdMgr;\n'
        '\n'
        'typedef struct {\n'
        '    void* pvParam;\n'
        '    ZPS_tsAplApsdeDcfmIndHdr *psApsdeDcfmIndHdr;\n'
        '}zps_tsLoopbackDataContext;\n'
        '\n'
        'typedef struct {\n'
        '    /* APSDE */\n'
        '    void *pvParam;\n'
        '    ZPS_tsAplApsdeDcfmIndHdr *(*prpsGetApsdeBuf)(void *);\n'
        '    void (*prvPostApsdeDcfmInd)(void *, ZPS_tsAplApsdeDcfmIndHdr *);\n'
        '    /* APSME */\n'
        '    void *pvApsmeParam;\n'
        '    ZPS_tsAplApsmeDcfmIndHdr *(*prpsGetApsmeBuf)(void *);\n'
        '    void (*prvPostApsmeDcfmInd)(void *, ZPS_tsAplApsmeDcfmIndHdr *);\n'
        '\n'
        '    zps_tsApsDuplicateTable *psApsDuplicateTable;\n'
        '    zps_tsMsgRecord  *psSyncMsgPool;\n'
        '    uint8 u8ApsDuplicateTableSize;\n'
        '    uint8 u8SeqNum;\n'
        '    uint8 u8SyncMsgPoolSize;\n'
        '    uint8 u8MaxFragBlockSize;\n'
        '    zps_tsDcfmRecordPool sDcfmRecordPool;\n'
        '    zps_tsFragRxPool sFragRxPool;\n'
        '    zps_tsFragTxPool sFragTxPool;\n'
        '    ZPS_teStatus (*preStartFragmentTransmission)(void *, ZPS_tsAplApsdeReqRsp *, uint16, uint8);\n'
        '    void (*prvHandleExtendedDataAck)(void *, ZPS_tsNwkNldeDcfmInd *, zps_tuApsAddressingField *, zps_tsExtendedFrameControlField *);\n'  # noqa
        '    void (*prvHandleDataFragmentReceive)(void *, ZPS_tsAplApsdeDcfmIndHdr *);\n'
        '    zps_tsApsmeCmdMgr sApsmeCmdMgr;\n'
        '    zps_tsApsPollTimer sApsPollTimer;\n'
        '    zps_tsLoopbackDataContext sLoopbackContext;\n'
        '    ZPS_tsTsvTimer sLoopbackTimer;\n'
        '} zps_tsApsContext;\n'
        '\n'
        '/*** APL Context **************************************************/\n'
        '\n'
        'typedef struct {\n'
        '    void *pvNwk;\n'
        '    const void *pvNwkTableSizes;\n'
        '    const void *pvNwkTables;\n'
        '    \n'
        '    ZPS_tsNwkNib *psNib;\n'
        '    ZPS_tsAplAib *psAib;\n'
        '    \n'
        '    void* hZpsMutex;\n'
        '    void* hDefaultStackEventMsg;\n'
        '    void* hMcpsDcfmIndMsg;\n'
        '    void* hMlmeDcfmIndMsg;\n'
        '    void* hTimeEventMsg;\n'
        '    void* hMcpsDcfmMsg;\n'
        '    /* sub-layer contexts */\n'
        '    zps_tsZdpContext sZdpContext;\n'
        '    zps_tsZdoContext sZdoContext;\n'
        '    zps_tsAfContext  sAfContext;\n'
        '    zps_tsApsContext sApsContext;\n'
        '\n'
        '    /* trust center context if present */\n'
        '    zps_tsTrustCenterContext *psTrustCenterContext;\n'
        '\n'
        '} zps_tsApl;\n'
        '\n'
        '/*** NIB Defaults **************************************************/\n'
        '\n'
        'typedef struct\n'
        '{\n'
        '    uint32 u32VsOldRouteExpiryTime;\n'
        '    uint8  u8MaxRouters;\n'
        '    uint8  u8MaxChildren;\n'
        '    uint8  u8MaxDepth;\n'
        '    uint8  u8PassiveAckTimeout;\n'
        '    uint8  u8MaxBroadcastRetries;\n'
        '    uint8  u8MaxSourceRoute;\n'
        '    uint8  u8NetworkBroadcastDeliveryTime;\n'
        '    uint8  u8UniqueAddr;\n'
        '    uint8  u8AddrAlloc;\n'
        '    uint8  u8UseTreeRouting;\n'
        '    uint8  u8SymLink;\n'
        '    uint8  u8UseMulticast;\n'
        '    uint8  u8LinkStatusPeriod;\n'
        '    uint8  u8RouterAgeLimit;\n'
        '    uint8  u8RouteDiscoveryRetriesPermitted;\n'
        '    uint8  u8VsFormEdThreshold;\n'
        '    uint8  u8SecurityLevel;\n'
        '    uint8  u8AllFresh;\n'
        '    uint8  u8SecureAllFrames;\n'
        '    uint8  u8VsTxFailThreshold;\n'
        '    uint8  u8VsMaxOutgoingCost;\n'
        '    uint8  u8VsLeaveRejoin;\n'
        '    uint8  u8ZedTimeout;\n'
        '    uint8  u8ZedTimeoutDefault;\n'
        '    uint16 u16VerifyLinkCostTransmitRate; \t\t\t\t\t\n'
        '\n'
        '} zps_tsNwkNibInitialValues;\n'
        '\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        External Dependencies                                         ***/\n'
        '/****************************************************************************/\n'
        '\n'
        'PUBLIC ZPS_teStatus zps_eStartFragmentedTransmission(void *, ZPS_tsAplApsdeReqRsp *, uint16 , uint8);\n'
        'PUBLIC void zps_vHandleExtendedDataAckFrame(void *, ZPS_tsNwkNldeDcfmInd *, zps_tuApsAddressingField *, zps_tsExtendedFrameControlField * );\n'  # noqa
        'PUBLIC void zps_vHandleApsdeDataFragIndNotSupported(void *pvApl, ZPS_tsAplApsdeDcfmIndHdr *);\n'
        'PUBLIC void zps_vHandleApsdeDataFragInd(void *, ZPS_tsAplApsdeDcfmIndHdr *psApsdeDcfmInd);\n'
        'bool_t g_pbZpsMutex = FALSE;\n'
        'PUBLIC void* zps_vGetZpsMutex(void);\n'
        'extern PUBLIC bool_t APP_bMultimaskJoinCallBack(void *);\n')
    _, my_found_node = find_node(options.zigbee_node_name)
    if my_found_node is None:
        print("ERROR: The input configuration file does not contain a node named '%s'.\n" % options.zigbee_node_name)
        return False
    if 'Endpoints' not in my_found_node:
        print(
            "ERROR: The input configuration for node '%s' does not contain any 'Endpoint' elements.\n" %
            my_found_node['@Name'])
        return False
    ep_total = 0
    for ep in as_list(my_found_node['Endpoints']):
        ep_id = int(ep['@Id'], 0)
        if ep_id > 0:
            ep_total += 1

    mac_interface_count = 0
    channel_mask_list_count = 0
    channel_offset = 0
    if 'ChannelMask' in config_node:
        channelMask = calculate_channel_mask(config_node['ChannelMask'])
        if 0 == channelMask:
            channelMask = 0x7FFF800
    else:
        channelMask = 0x7FFF800
    set_mask_for_index0 = 0
    if 'MacInterfaceList' in config_node:
        for interface in as_list(config_node['MacInterfaceList']['MacInterface']):
            if interface['@RadioType'] == 'RT2400MHz':
                set_mask_for_index0 = 1

    if 'MacInterfaceList' in config_node:
        for interface in as_list(config_node['MacInterfaceList']['MacInterface']):
            mac_interface_count += 1
            channel_mask_list_count += int(interface['@ChannelListSize'])

    if channel_mask_list_count > 15:
        print('channelMaskList count in the mac interface should be less than 15')
        return
    if 'MacInterfaceList' in config_node:
        for interface in as_list(config_node['MacInterfaceList']['MacInterface']):
            index_to_check = int(interface['@index'])
            count_index = 0
            for interface1 in as_list(config_node['MacInterfaceList']['MacInterface']):
                if index_to_check == interface1['@index']:
                    count_index += 1
                if count_index > 1:
                    print('ERROR: MAC interfaces should have unique index.\n')

    if mac_interface_count > 2:
        print('ERROR: Only two interfaces supported. You have set %d\n' % mac_interface_count)
    if mac_interface_count > 0:
        c_file.write('PRIVATE  bool_t    g_bIgnoreBroadcast [ %d ] =  {' % mac_interface_count)
        for count in range(0, mac_interface_count):
            c_file.write('TRUE,')

        c_file.write('};\n')
        c_file.write('PRIVATE  uint32    g_u32MacTxUcastAvgRetry [ %d ] =  {' % mac_interface_count)
        for count in range(0, mac_interface_count):
            c_file.write('1,')

        c_file.write('};\n')
        c_file.write('PRIVATE  uint32    g_u32MacTxUcastAccRetry [ %d ]; \n' % mac_interface_count)
        c_file.write('PRIVATE  uint32    g_u32MacTxUcastFail [ %d ]; \n' % mac_interface_count)
        c_file.write('PRIVATE  uint32    g_u32MacTxUcast [ %d ]; \n' % mac_interface_count)
        c_file.write('PRIVATE  uint32    g_u32MacCcaFail [ %d ]; \n' % mac_interface_count)
        c_file.write('PRIVATE  uint32    g_u32ApsRetry   [ %d ]; \n' % mac_interface_count)
        c_file.write('PUBLIC   uint32    g_u32ChannelMaskList [ %d ] = ' % channel_mask_list_count)
        c_file.write('{ ')
        for count in range(0, channel_mask_list_count):
            if set_mask_for_index0 == 1 and count == 0:
                c_file.write('    0x%08xUL,\n' % channelMask)
            else:
                c_file.write('0xFFFFFFFF,')

        c_file.write('}; \n')
        c_file.write('zps_tsAplAfMMServerContext\ts_sMultiMaskServer =')
        c_file.write('{')
        c_file.write('     ZPS_E_MULTIMASK_STATE_IDLE,')
        c_file.write('     %d,' % channel_mask_list_count)
        c_file.write('     0,')
        c_file.write('     APP_bMultimaskJoinCallBack')
        c_file.write('};\n')
        c_file.write('    /* ... ZPS_MULTIMASK_SUPPORT */\n')
        c_file.write('    /* The MAC Interface Table (default values) */ \n')
        temp_interface = 0
        c_file.write('PRIVATE  MAC_tsMacInterface    g_sMacInterface [ %d ]= \n' % mac_interface_count)
        c_file.write('{\n')
        if 'MacInterfaceList' in config_node:
            for interface in as_list(config_node['MacInterfaceList']['MacInterface']):
                radio_type = 'E_MAC_FREQ_NOT_KNOWN'
                mac_bitmask = 0
                if interface['@Enabled'] == 'true':
                    mac_bitmask |= 1
                else:
                    mac_bitmask |= 0
                mac_bitmask |= int(interface['@ChannelListSize']) << 2
                if interface['@RadioType'] == 'RT868MHz':
                    radio_type = 'E_MAC_FREQ_868'
                    temp_interface |= 1
                if interface['@RadioType'] == 'RT2400MHz':
                    radio_type = 'E_MAC_FREQ_2400'
                    temp_interface |= 2
                if int(interface['@index']) == 0:
                    if interface['@RadioType'] != 'RT2400MHz':
                        if mac_interface_count > 1:
                            print('ERROR: interface index 0 should always be 2.4G in a multimac\n')
                        mac_type = 'E_MAC_TYPE_UART1'
                    else:
                        mac_type = 'E_MAC_TYPE_SOC'
                if int(interface['@index']) > 0:
                    mac_type = 'E_MAC_TYPE_UART' + str(interface['@index'])
                if '@RouterAllowed' in interface:
                    router_allowed_flag = 1
                    mac_bitmask |= 1 << 1
                else:
                    router_allowed_flag = 0
                c_file.write('        { %d, 0x%x, %s, %s  } , \n' % (0, mac_bitmask, radio_type, mac_type))

            c_file.write('};\n')
            c_file.write('PRIVATE MAC_tsMacInterfaceTable g_asMacInterfaceTable =  \n')
            c_file.write('{ \n')
            c_file.write('  &s_sMultiMaskServer,\t\t /* ZPS_MULTIMASK_SUPPORT ...*/ \n')
            c_file.write('  g_sMacInterface,\n')
            c_file.write('  &g_u32ChannelMaskList [0],\n')
            c_file.write('  g_u32MacTxUcastAvgRetry,\n')
            c_file.write('  g_u32MacTxUcastAccRetry,\n')
            c_file.write('  g_u32MacTxUcastFail,\n')
            c_file.write('  g_u32MacTxUcast,\n')
            c_file.write('  g_u32MacCcaFail,\n')
            c_file.write('  g_u32ApsRetry,\n')
            c_file.write('  g_bIgnoreBroadcast,\n')
            c_file.write('  %d\n' % mac_interface_count)
            c_file.write('};\n')
    c_file.write('PUBLIC uint8 u8MaxZpsConfigEp = %d ;\n' % ep_total)
    c_file.write('PUBLIC uint8 au8EpMapPresent[%d] = {' % ep_total)
    ep_loop = 0
    for ep in as_list(my_found_node['Endpoints']):
        ep_id = int(ep['@Id'], 0)
        if ep_id > 0:
            ep_loop += 1
            if ep_loop < ep_total:
                c_file.write('%d ,' % ep_id)
            else:
                c_file.write(' %d ' % ep_id)

    c_file.write(' }; \n')
    if '@StackProfile' in config_node:
        u8ZpsConfigStackProfileId = int(config_node['@StackProfile'], 0)
        c_file.write('PUBLIC uint8 u8ZpsConfigStackProfileId = %d;\n' % u8ZpsConfigStackProfileId)
    else:
        c_file.write('PUBLIC uint8 u8ZpsConfigStackProfileId = 2;\n')
    aps_fc_save_count_bit_shift = 10
    if '@ApsFcSaveCountBitShift' in config_node:
        aps_fc_save_count_bit_shift = int(config_node['@ApsFcSaveCountBitShift'], 0)
    c_file.write('PUBLIC const uint32 g_u32ApsFcSaveCountBitShift = %d;\n' % aps_fc_save_count_bit_shift)
    nwk_fc_save_count_bit_shift = 10
    if '@NwkFcSaveCountBitShift' in config_node:
        nwk_fc_save_count_bit_shift = int(config_node['@NwkFcSaveCountBitShift'], 0)
    c_file.write('PUBLIC const uint32 g_u32NwkFcSaveCountBitShift = %d;\n' % nwk_fc_save_count_bit_shift)
    gp_supported = 'NULL'
    if '@GreenPowerSupport' in config_node:
        if 'true' == config_node['@GreenPowerSupport'].lower():
            gp_sec_table_struct = 'NULL'
            gp_tx_queue_struct = 'NULL'
            gp_aging_timer = 'NULL'
            gp_bidir_timer = 'NULL'
            size_st = 0
            size_tx_q = 0
            if 'GreenPowerTxQueue' in config_node:
                size_tx_q = int(config_node['GreenPowerTxQueue']['@Size'], 0)
                c_file.write('PRIVATE ZPS_tsAfZgpTxGpQueueEntry aZgpTxGpQueue[%d];\n' % size_tx_q)
                c_file.write('ZPS_tsTsvTimer sTxAgingTimer;\n')
                c_file.write('TSV_Timer_s sTxBiDirTimer;\n')
                c_file.write('ZPS_tsAfZgpTxGpQueue sZgpTxGpQueue = { aZgpTxGpQueue, %d };\n' % size_tx_q)
                gp_aging_timer = '&sTxAgingTimer'
                gp_bidir_timer = '&sTxBiDirTimer'
                gp_tx_queue_struct = '&sZgpTxGpQueue'
            if 'GreenPowerSecurityTable' in config_node:
                size_st = int(config_node['GreenPowerSecurityTable']['@Size'], 0)
                c_file.write('PRIVATE ZPS_tsAfZgpGpstEntry aZgpGpst[%d];\n' % size_st)
                c_file.write('ZPS_tsAfZgpGpst sZgpGpst = { aZgpGpst, %d };\n' % size_st)
                gp_sec_table_struct = '&sZgpGpst'
            gp_supported = '&gsGreenPowerContext'
            c_file.write(
                'ZPS_tsAfZgpGreenPowerContext gsGreenPowerContext = { %s, %s, %s, %s, 100, 0 };\n' % (
                    gp_sec_table_struct,
                    gp_tx_queue_struct,
                    gp_aging_timer,
                    gp_bidir_timer,
                ),
            )
    c_file.write('ZPS_tsAfZgpGreenPowerContext *g_psGreenPowerContext = %s;\n' % gp_supported)
    c_file.write(
        '\n'
        '/****************************************************************************/\n'
        '/***        Local Function Prototypes                                     ***/\n'
        '/****************************************************************************/\n'
        '\n'
        'PRIVATE void vZdoServersInit(void);\n')
    if 'ZDOServers' in config_node:
        for server_name, server in get_child_nodes(config_node['ZDOServers']):
            if server_name == 'MgmtNWKEnhanceUpdateServer':
                continue
            c_file.write('PUBLIC bool zps_bAplZdo%s(void *, void *, ZPS_tsAfEvent *);\n' % server_name)
            (output_params, output_param_types) = ZDO_SERVERS[server_name]
            c_file.write('PUBLIC void zps_vAplZdo%sInit(' % server_name)
            output_param_types(c_file)
            c_file.write(');\n')

    trust_center_present = False
    if 'TrustCenter' in config_node:
        c_file.write('\n/* Trust Center */\n')
        c_file.write('PUBLIC void zps_vAplTrustCenterInit(void *);')
        c_file.write('PUBLIC void zps_vAplTrustCenterUpdateDevice(void *, uint64 , uint64 , uint8 , uint16 );')
        c_file.write('PUBLIC void zps_vAplTrustCenterRequestKey(void *, uint64 , uint8 , uint64 );')
        trust_center_present = True
    c_file.write(
        '\n'
        '/****************************************************************************/\n'
        '/***        Local Variables                                               ***/\n'
        '/****************************************************************************/\n'
        '\n')
    binding_table = 'NULL'
    if 'BindingTable' in config_node:
        size = int(config_node['BindingTable']['@Size'], 0)
        if size > 0:
            c_file.write('PRIVATE ZPS_tsAplApsmeBindingTableStoreEntry s_bindingTableStorage[%d];\n' % size)
            c_file.write('PRIVATE ZPS_tsAplApsmeBindingTable s_bindingTable = { s_bindingTableStorage, %d };\n' % size)
            binding_table = '&s_bindingTable'
    binding_cache_cfg = None  # ???
    binding_cache = 'NULL'
    if binding_cache_cfg is not None:
        table_size = int(binding_cache_cfg['@TableSize'], 0)
        num_tables = int(binding_cache_cfg['@NumTables'], 0)
        if num_tables > 0:
            for i in range(0, num_tables):
                c_file.write(
                    'PRIVATE ZPS_tsAplApsmeBindingTableEntry s_bindingCacheStorage_%d[%d];\n' % (i, table_size))

            c_file.write('PRIVATE ZPS_tsAplApsmeBindingTable s_bindingCaches[%d] = {\n' % num_tables)
            for i in range(0, num_tables):
                c_file.write('{ 0, &s_bindingCacheStorage_%d, %d },\n' % (i, table_size))

            c_file.write('};\n')
            c_file.write(
                'PRIVATE ZPS_tsAplApsmeBindingTableCache s_bindingCache = { s_bindingCaches, %d, NULL };\n' %
                num_tables,
            )
            binding_cache = '&s_bindingTable'
    binding_tables = 'NULL'
    if 'NULL' != binding_cache or 'NULL' != binding_table:
        c_file.write(
            'PRIVATE ZPS_tsAplApsmeBindingTableType s_bindingTables = { %s, %s };\n' %
            (binding_cache, binding_table),
        )
        binding_tables = '&s_bindingTables'
    group_table = 'NULL'
    group_table_size = 0
    if 'GroupTable' in config_node:
        group_table_size = int(config_node['GroupTable']['@Size'], 0)
        c_file.write('PRIVATE ZPS_tsAplApsmeGroupTableEntry s_groupTableStorage[%d];\n' % group_table_size)
        c_file.write(
            'PRIVATE ZPS_tsAplApsmeAIBGroupTable s_groupTable = { s_groupTableStorage, %d };\n' % group_table_size)
        c_file.write('PRIVATE ZPS_tsAPdmGroupTableEntry s_groupTablePdmStorage[%d];\n' % group_table_size)
        c_file.write(
            'PUBLIC ZPS_tsPdmGroupTable s_groupPdmTable = { s_groupTablePdmStorage, %d };\n' %
            group_table_size,
        )
        group_table = '&s_groupTable'
    else:
        c_file.write('PUBLIC ZPS_tsPdmGroupTable s_groupPdmTable = { NULL, %d };\n' % group_table_size)
    key_pair_table = 'NULL'
    key_pair_table_size = 0
    if 'KeyDescriptorTable' in config_node:
        key_pair_table_size = int(config_node['KeyDescriptorTable']['@Size'], 0)
        c_file.write(
            'PRIVATE ZPS_tsAplApsKeyDescriptorEntry s_keyPairTableStorage[%d] = {\n' % (key_pair_table_size + 3))
        num_pck = 0
        if 'PreconfiguredKey' in config_node['KeyDescriptorTable']:
            for pck in as_list(config_node['KeyDescriptorTable']['PreconfiguredKey']):
                if num_pck == key_pair_table_size:
                    print(
                        'WARNING: There are more PreconfiguredKeys than the KeyDescriptorTable size of %d.\n' %
                        key_pair_table_size)
                    break
                c_file.write('    { 0x%016lxULL, { ' % int(pck['@IEEEAddress'], 0))
                key = int(pck['@Key'], 0)
                for i in range(0, 16):
                    if 0 != i:
                        c_file.write(', ')
                    c_file.write('0x%02x' % ((key & 255 << 8 * i) >> 8 * i))

                c_file.write(' }, 0 , 0 , 0 },\n')
                num_pck += 1

        if num_pck < key_pair_table_size + 3:
            for pck in range(num_pck, key_pair_table_size + 3):
                c_file.write('    { 0, 0xFFFF, { }  },\n')

        c_file.write('};\n')
        c_file.write(
            'ZPS_tsAplApsKeyDescriptorEntry  *psAplDefaultDistributedAPSLinkKey = &s_keyPairTableStorage[%d];\n' %
            (key_pair_table_size + 1),
        )
        c_file.write(
            'ZPS_tsAplApsKeyDescriptorEntry  *psAplDefaultGlobalAPSLinkKey = &s_keyPairTableStorage[%d];\n' %
            (key_pair_table_size + 2),
        )
        c_file.write('PRIVATE uint32 au32IncomingFrameCounter[%d];\n' % (key_pair_table_size + 3))
        c_file.write(
            'PRIVATE ZPS_tsAplApsKeyDescriptorTable s_keyPairTable = { s_keyPairTableStorage, %d };\n\n' %
            key_pair_table_size,
        )
        key_pair_table = '&s_keyPairTable'
    c_file.write('PRIVATE ZPS_tsAplAib s_sAplAib = {\n')
    c_file.write('    0,\n')
    ext_pan_id = 0
    if '@apsUseExtPANId' in config_node:
        ext_pan_id = int(config_node['@apsUseExtPANId'], 0)
    c_file.write('    0x%016lxULL,\n' % ext_pan_id)
    designated_coordinator = 'FALSE'
    if config_node_name == 'Coordinator':
        designated_coordinator = 'TRUE'
    if '@apsDesignatedCoordinator' in config_node:
        if 'true' == config_node['@apsDesignatedCoordinator'].lower():
            designated_coordinator = 'TRUE'
        else:
            designated_coordinator = 'FALSE'
    c_file.write('    %s,\n' % designated_coordinator)
    use_insecure_join = 'TRUE'
    if '@apsUseInsecureJoin' in config_node:
        if 'true' == config_node['@apsUseInsecureJoin'].lower():
            use_insecure_join = 'TRUE'
        else:
            use_insecure_join = 'FALSE'
    c_file.write('    %s,\n' % use_insecure_join)
    c_file.write('    FALSE,\n')
    c_file.write('    0,\n')
    non_member_radius = 2
    if '@apsNonMemberRadius' in config_node:
        non_member_radius = int(config_node['@apsNonMemberRadius'], 0)
    c_file.write('    0x%02x,\n' % non_member_radius)
    inter_frame_delay = 0
    if '@apsInterframeDelay' in config_node:
        inter_frame_delay = int(config_node['@apsInterframeDelay'], 0)
    c_file.write('    0x%02x,\n' % inter_frame_delay)
    c_file.write('    0,\n')
    c_file.write('    0,\n')
    c_file.write('    0,\n')
    max_window_size = 8
    if '@apsMaxWindowSize' in config_node:
        max_window_size = int(config_node['@apsMaxWindowSize'], 0)
    c_file.write('    0x%02x,\n' % max_window_size)
    c_file.write('    %s,\n' % binding_tables)
    c_file.write('    %s,\n' % group_table)
    c_file.write('    %s,\n' % key_pair_table)
    if key_pair_table_size == 0:
        c_file.write('    NULL,\n')
    else:
        c_file.write('    &s_keyPairTableStorage[%d],\n' % key_pair_table_size)
    c_file.write('    FALSE,\n')
    c_file.write('    FALSE,\n')
    aps_security_timeout_period = 3000
    if '@apsSecurityTimeoutPeriod' in config_node:
        aps_security_timeout_period = int(config_node['@apsSecurityTimeoutPeriod'], 0)
    c_file.write('    0x%04x,\n' % aps_security_timeout_period)
    if key_pair_table_size == 0:
        c_file.write('    NULL,\n')
    else:
        c_file.write('    au32IncomingFrameCounter,\n')
    c_file.write('    g_u32ChannelMaskList\n')
    c_file.write('};\n')
    num_zdo_servers = 0
    if 'ZDOServers' in config_node:
        for server_name, server in get_child_nodes(config_node['ZDOServers']):
            if server_name == 'MgmtNWKEnhanceUpdateServer':
                continue
            (output_params, output_param_types) = ZDO_SERVERS[server_name]
            context_size = get_apl_server_context_size(
                server_name,
                objdump,
                options.zigbee_apl_lib_fsp,
                options.endian,
            )
            c_file.write(
                'PRIVATE uint8 s_s%sContext[%d] __attribute__ ((aligned (4)));\n' %
                (server_name, context_size),
            )
            if server_name == 'BindRequestServer':
                if '@SimultaneousRequests' in server:
                    SimultaneousRequests = int(server['@SimultaneousRequests'], 0)
                    c_file.write(
                        'PRIVATE zps_tsZdoServerConfAckContext s_s%sAcksDcfmContext[%d];\n' %
                        (server_name, SimultaneousRequests),
                    )
            num_zdo_servers += 1

    if 'ZDOServers' in config_node:
        c_file.write('\n/* ZDO Servers */\n')
        c_file.write('PRIVATE const zps_tsAplZdoServer s_asAplZdoServers[%d] = {\n' % (num_zdo_servers + 1))

        def key(key_value):
            if key_value[0] == 'DefaultServer':
                return 1
            if key_value[0] == 'ZdoClient':
                return -1
            return 0

        for server_name, server in sorted(get_child_nodes(config_node['ZDOServers']), key=key):
            if server_name != 'MgmtNWKEnhanceUpdateServer':
                c_file.write('    { zps_bAplZdo%s, s_s%sContext },\n' % (server_name, server_name))

        c_file.write('    { NULL, NULL }\n')
        c_file.write('};\n')
    c_file.write('\n/* Simple Descriptors */\n')
    for endpoint in as_list(config_node['Endpoints']):
        num_input_clusters = 0
        num_output_clusters = 0
        endpoint_id = int(endpoint['@Id'], 0)
        in_disc_flags = ''
        if 'InputClusters' in endpoint:
            num_input_clusters = len(as_list(endpoint['InputClusters']))
            in_cluster_list = ''
            in_apdu_list = ''
            cluster_num = 0
            cluster_disc_mask = 0
            for in_cluster in as_list(endpoint['InputClusters']):
                cluster = find_cluster(in_cluster['@Cluster'])
                in_cluster_list += ' 0x%04x,' % int(cluster['@Id'], 0)
                if '@RxAPDU' in in_cluster:
                    apdu = find_apdu(config_node, in_cluster['@RxAPDU'])
                    in_apdu_list += ' %s,' % apdu['@Name']
                else:
                    in_apdu_list += ' NULL,'
                discoverable = 1 << (cluster_num & 7)
                if '@Discoverable' in in_cluster:
                    if in_cluster['@Discoverable'].lower() == 'false':
                        discoverable = 0
                cluster_disc_mask |= discoverable
                if cluster_num & 7 == 7:
                    in_disc_flags += '0x%02x, ' % cluster_disc_mask
                    cluster_disc_mask = 0
                cluster_num += 1

            if cluster_num & 7 != 0:
                in_disc_flags += '0x%02x' % cluster_disc_mask
        out_disc_flags = ''
        if 'OutputClusters' in endpoint:
            num_output_clusters = len(as_list(endpoint['OutputClusters']))
            out_cluster_list = ''
            cluster_num = 0
            cluster_disc_mask = 0
            for out_cluster in as_list(endpoint['OutputClusters']):
                cluster = find_cluster(out_cluster['@Cluster'])
                out_cluster_list += ' 0x%04x,' % int(cluster['@Id'], 0)
                discoverable = 1 << (cluster_num & 7)
                if '@Discoverable' in out_cluster:
                    if out_cluster['@Discoverable'].lower() == 'false':
                        discoverable = 0
                cluster_disc_mask |= discoverable
                if cluster_num & 7 == 7:
                    out_disc_flags += '0x%02x, ' % cluster_disc_mask
                    cluster_disc_mask = 0
                cluster_num += 1

            if cluster_num & 7 != 0:
                out_disc_flags += '0x%02x' % cluster_disc_mask
        if num_input_clusters > 0:
            c_file.write(
                'PRIVATE const uint16 s_au16Endpoint%dInputClusterList[%d] = {%s };\n' %
                (endpoint_id, num_input_clusters, in_cluster_list),
            )
            c_file.write(
                'PRIVATE const PDUM_thAPdu s_ahEndpoint%dInputClusterAPdus[%d] = {%s };\n' %
                (endpoint_id, num_input_clusters, in_apdu_list),
            )
            c_file.write(
                'PRIVATE uint8 s_au8Endpoint%dInputClusterDiscFlags[%d] = { %s };\n' %
                (endpoint_id, (num_input_clusters + 7) / 8, in_disc_flags),
            )
            c_file.write('\n')
        if num_output_clusters > 0:
            c_file.write(
                'PRIVATE const uint16 s_au16Endpoint%dOutputClusterList[%d] = {%s };\n' %
                (endpoint_id, num_output_clusters, out_cluster_list),
            )
            c_file.write(
                'PRIVATE uint8 s_au8Endpoint%dOutputClusterDiscFlags[%d] = { %s };\n' %
                (endpoint_id, (num_output_clusters + 7) / 8, out_disc_flags),
            )
            c_file.write('\n')

    if '@DefaultCallbackName' in config_node:
        default_callback_name = config_node['@DefaultCallbackName']
        c_file.write('PUBLIC void %s(uint8 u8Endpoint, ZPS_tsAfEvent *psStackEvent);\n' % default_callback_name)
    c_file.write('tszQueue zps_msgMlmeDcfmInd;\n')
    c_file.write('tszQueue zps_msgMcpsDcfmInd;\n')
    c_file.write('tszQueue zps_TimeEvents;\n')
    c_file.write('tszQueue zps_msgMcpsDcfm;\n')
    c_file.write(
        'PRIVATE zps_tsAplAfSimpleDescCont s_asSimpleDescConts[%d] = {\n' %
        len(as_list(config_node['Endpoints'])),
    )
    for endpoint in as_list(config_node['Endpoints']):
        endpoint_id = int(endpoint['@Id'], 0)
        num_input_clusters = 0
        if 'InputClusters' in endpoint:
            num_input_clusters = len(as_list(endpoint['InputClusters']))
        num_output_clusters = 0
        if 'OutputClusters' in endpoint:
            num_output_clusters = len(as_list(endpoint['OutputClusters']))
        profile = find_profile(endpoint['@Profile'])
        c_file.write('    {\n')
        c_file.write('        {\n')
        c_file.write('            0x%04x,\n' % int(profile['@Id'], 0))
        c_file.write('            %s,\n' % endpoint['@ApplicationDeviceId'])
        c_file.write('            %s,\n' % endpoint['@ApplicationDeviceVersion'])
        c_file.write('            %d,\n' % endpoint_id)
        c_file.write('            %d,\n' % num_input_clusters)
        c_file.write('            %d,\n' % num_output_clusters)
        if 0 == num_input_clusters:
            c_file.write('            NULL,\n')
        else:
            c_file.write('            s_au16Endpoint%dInputClusterList,\n' % endpoint_id)
        if 0 == num_output_clusters:
            c_file.write('            NULL,\n')
        else:
            c_file.write('            s_au16Endpoint%dOutputClusterList,\n' % endpoint_id)
        if 0 == num_input_clusters:
            c_file.write('            NULL,\n')
        else:
            c_file.write('            s_au8Endpoint%dInputClusterDiscFlags,\n' % endpoint_id)
        if 0 == num_output_clusters:
            c_file.write('            NULL,\n')
        else:
            c_file.write('            s_au8Endpoint%dOutputClusterDiscFlags,\n' % endpoint_id)
        c_file.write('        },\n')
        if 0 == num_input_clusters:
            c_file.write('        NULL,\n')
        else:
            c_file.write('        s_ahEndpoint%dInputClusterAPdus,\n' % endpoint_id)
        flags = 0
        if 'true' == endpoint['@Enabled'].lower():
            flags |= 1
        c_file.write('        %d\n' % flags)
        c_file.write('    },\n')

    c_file.write('};\n')
    c_file.write('\n/* Node Descriptor */\n')
    c_file.write('PRIVATE ZPS_tsAplAfNodeDescriptor s_sNodeDescriptor = {\n')
    if 'ZC' == config_node['NodeDescriptor']['@LogicalType']:
        c_file.write('    0,\n')
    elif 'ZR' == config_node['NodeDescriptor']['@LogicalType']:
        c_file.write('    1,\n')
    elif 'ZED' == config_node['NodeDescriptor']['@LogicalType']:
        c_file.write('    2,\n')
    c_file.write('    %s,\n' % config_node['NodeDescriptor']['@ComplexDescriptorAvailable'].upper())
    c_file.write('    %s,\n' % config_node['NodeDescriptor']['@UserDescriptorAvailable'].upper())
    c_file.write('    0,\n')
    local_frequency_band = 0
    if temp_interface > 0:
        if temp_interface & 1:
            local_frequency_band |= 16
        if temp_interface & 2:
            local_frequency_band |= 8
        c_file.write('    0x%02x,\n' % local_frequency_band)
    elif '868MHz' == config_node['NodeDescriptor']['@FrequencyBand']:
        c_file.write('    0,\n')
    elif '915MHz' == config_node['NodeDescriptor']['@FrequencyBand']:
        c_file.write('    4,\n')
    elif '2.4GHz' == config_node['NodeDescriptor']['@FrequencyBand']:
        c_file.write('    8,\n')
    c_file.write('    %d,\n' % int(config_node['NodeDescriptor']['@APSFlags'], 0))
    mac_flags = 0
    if 'true' == config_node['NodeDescriptor']['@AlternatePANCoordinator'].lower():
        mac_flags |= 1 << 0
    if 'true' == config_node['NodeDescriptor']['@DeviceType'].lower():
        mac_flags |= 1 << 1
    if 'true' == config_node['NodeDescriptor']['@PowerSource'].lower():
        mac_flags |= 1 << 2
    if 'true' == config_node['NodeDescriptor']['@RxOnWhenIdle'].lower():
        mac_flags |= 1 << 3
    if 'true' == config_node['NodeDescriptor']['@Security'].lower():
        mac_flags |= 1 << 6
    if 'true' == config_node['NodeDescriptor']['@AllocateAddress'].lower():
        mac_flags |= 1 << 7
    c_file.write('    0x%02x,\n' % mac_flags)
    c_file.write('    0x%04x,\n' % int(config_node['NodeDescriptor']['@ManufacturerCode'], 0))
    c_file.write('    0x%02x,\n' % int(config_node['NodeDescriptor']['@MaximumBufferSize'], 0))
    c_file.write('    0x%04x,\n' % int(config_node['NodeDescriptor']['@MaximumIncomingTransferSize'], 0))
    server_mask = 0
    if 'true' == config_node['NodeDescriptor']['@PrimaryTrustCenter'].lower():
        server_mask |= 1 << 0
    if 'true' == config_node['NodeDescriptor']['@BackupTrustCenter'].lower():
        server_mask |= 1 << 1
    if 'true' == config_node['NodeDescriptor']['@PrimaryBindingTableCache'].lower():
        server_mask |= 1 << 2
    if 'true' == config_node['NodeDescriptor']['@BackupBindingTableCache'].lower():
        server_mask |= 1 << 3
    if 'true' == config_node['NodeDescriptor']['@PrimaryDiscoveryCache'].lower():
        server_mask |= 1 << 4
    if 'true' == config_node['NodeDescriptor']['@BackupDiscoveryCache'].lower():
        server_mask |= 1 << 5
    if 'true' == config_node['NodeDescriptor']['@NetworkManager'].lower():
        server_mask |= 1 << 6
    server_mask |= 22 << 9
    c_file.write('    0x%04x,\n' % server_mask)
    c_file.write('    0x%04x,\n' % int(config_node['NodeDescriptor']['@MaximumOutgoingTransferSize'], 0))
    descriptor_capabilities = 0
    if 'true' == config_node['NodeDescriptor']['@ExtendedActiveEndpointListAvailable'].lower():
        descriptor_capabilities |= 1 << 0
    if 'true' == config_node['NodeDescriptor']['@ExtendedSimpleDescriptorListAvailable'].lower():
        descriptor_capabilities |= 1 << 1
    c_file.write('    0x%02x};\n' % descriptor_capabilities)
    if endian == 'BIG_ENDIAN':
        c_file.write('\n/* Node Power Descriptor */\n')
        c_file.write('PRIVATE ZPS_tsAplAfNodePowerDescriptor s_sNodePowerDescriptor = {\n')
        current_power_mode = 0
        if 'Synchronised with RxOnWhenIdle' == config_node['NodePowerDescriptor']['@DefaultPowerMode']:
            current_power_mode = 0
        elif 'Periodic' == config_node['NodePowerDescriptor']['@DefaultPowerMode']:
            current_power_mode = 1
        elif 'Stimulated' == config_node['NodePowerDescriptor']['@DefaultPowerMode']:
            current_power_mode = 2
        c_file.write('    0x%01x,\n' % current_power_mode)
        available_power_sources = 0
        if 'true' == config_node['NodePowerDescriptor']['@ConstantPower'].lower():
            available_power_sources |= 1 << 0
        if 'true' == config_node['NodePowerDescriptor']['@RechargeableBattery'].lower():
            available_power_sources |= 1 << 1
        if 'true' == config_node['NodePowerDescriptor']['@DisposableBattery'].lower():
            available_power_sources |= 1 << 2
        c_file.write('    0x%01x,\n' % available_power_sources)
        current_power_source = 0
        if 'Constant Power' == config_node['NodePowerDescriptor']['@DefaultPowerSource']:
            current_power_source = 1
        elif 'Rechargeable Battery' == config_node['NodePowerDescriptor']['@DefaultPowerSource']:
            current_power_source = 2
        elif 'Disposable Battery' == config_node['NodePowerDescriptor']['@DefaultPowerSource']:
            current_power_source = 4
        c_file.write('    0x%01x,\n' % current_power_source)
        c_file.write('    0xC};\n')
    else:
        c_file.write('\n/* Node Power Descriptor */\n')
        c_file.write('PRIVATE ZPS_tsAplAfNodePowerDescriptor s_sNodePowerDescriptor = {\n')
        c_file.write('    0xC,   \n')
        current_power_source = 0
        if 'Constant Power' == config_node['NodePowerDescriptor']['@DefaultPowerSource']:
            current_power_source = 1
        elif 'Rechargeable Battery' == config_node['NodePowerDescriptor']['@DefaultPowerSource']:
            current_power_source = 2
        elif 'Disposable Battery' == config_node['NodePowerDescriptor']['@DefaultPowerSource']:
            current_power_source = 4
        c_file.write('    0x%01x,\n' % current_power_source)
        available_power_sources = 0
        if 'true' == config_node['NodePowerDescriptor']['@ConstantPower'].lower():
            available_power_sources |= 1 << 0
        if 'true' == config_node['NodePowerDescriptor']['@RechargeableBattery'].lower():
            available_power_sources |= 1 << 1
        if 'true' == config_node['NodePowerDescriptor']['@DisposableBattery'].lower():
            available_power_sources |= 1 << 2
        c_file.write('    0x%01x,\n' % available_power_sources)
        current_power_mode = 0
        if 'Synchronised with RxOnWhenIdle' == config_node['NodePowerDescriptor']['@DefaultPowerMode']:
            current_power_mode = 0
        elif 'Periodic' == config_node['NodePowerDescriptor']['@DefaultPowerMode']:
            current_power_mode = 1
        elif 'Stimulated' == config_node['NodePowerDescriptor']['@DefaultPowerMode']:
            current_power_mode = 2
        c_file.write('    0x%01x};\n' % current_power_mode)
    if 'UserDescriptor' in config_node:
        c_file.write('\n/* User Descriptor */\n')
        c_file.write('PRIVATE ZPS_tsAplAfUserDescriptor s_sUserDescriptor = { { ')
        for i in range(0, len(config_node['UserDescriptor']['@UserDescription'])):
            if i < 16:
                c_file.write("'%c', " % config_node['UserDescriptor']['@UserDescription'][i])

        c_file.write('} };\n')
    c_file.write('\n/* APSDE duplicate table */\n')
    aps_duplicate_table_size = int(config_node['@APSDuplicateTableSize'], 0)
    if aps_duplicate_table_size < 1:
        aps_duplicate_table_size = 1
    c_file.write('PRIVATE uint16 s_au16ApsDuplicateTableAddrs[%d];\n' % aps_duplicate_table_size)
    c_file.write('PRIVATE uint32 s_au32ApsDuplicateTableHash[%d];\n' % int(config_node['@APSDuplicateTableSize'], 0))
    c_file.write('PRIVATE uint8 s_au8ApsDuplicateTableSeqCnts[%d];\n' % int(config_node['@APSDuplicateTableSize'], 0))
    c_file.write(
        'PRIVATE zps_tsApsDuplicateTable s_sApsDuplicateTable = { s_au16ApsDuplicateTableAddrs, s_au32ApsDuplicateTableHash, s_au8ApsDuplicateTableSeqCnts, 0 };\n',  # noqa
    )
    c_file.write('\n/* APSDE sync msg pool */\n')
    c_file.write(
        'PRIVATE zps_tsMsgRecord s_asApsSyncMsgPool[%d];\n' %
        int(config_node['@MaxNumSimultaneousApsdeAckReq'], 0),
    )
    c_file.write('\n/* APSDE dcfm record pool */\n')
    c_file.write(
        'PRIVATE zps_tsDcfmRecord s_asApsDcfmRecordPool[%d];\n' %
        int(config_node['@MaxNumSimultaneousApsdeReq'], 0),
    )
    if int(config_node['@FragmentationMaxNumSimulRx'], 0) > 0:
        c_file.write('\n/* APSDE fragmentation rx pool */\n')
        c_file.write(
            'PRIVATE zps_tsFragmentReceive s_asApsFragRxPool[%d];\n' %
            int(config_node['@FragmentationMaxNumSimulRx'], 0),
        )
    if int(config_node['@FragmentationMaxNumSimulTx'], 0) > 0:
        c_file.write('\n/* APSDE fragmentation tx pool */\n')
        c_file.write(
            'PRIVATE zps_tsFragmentTransmit s_asApsFragTxPool[%d];\n' %
            int(config_node['@FragmentationMaxNumSimulTx'], 0),
        )
    num_apsme_cmd_containers = 4
    if '@NumAPSMESimulCommands' in config_node:
        if int(config_node['@NumAPSMESimulCommands'], 0) > 0:
            num_apsme_cmd_containers = int(config_node['@NumAPSMESimulCommands'], 0)
    c_file.write('\n/* APSME Command Manager Command Containers */\n')
    c_file.write(
        'PRIVATE zps_tsApsmeCmdContainer s_sApsmeCmdContainer_%d = { NULL, {}, {}, NULL, 0 };\n' %
        num_apsme_cmd_containers,
    )
    for i in range(num_apsme_cmd_containers - 1, 0, -1):
        c_file.write(
            'PRIVATE zps_tsApsmeCmdContainer s_sApsmeCmdContainer_%d = { &s_sApsmeCmdContainer_%d, {}, {}, NULL, 0 };\n' %
            (i, i + 1),
        )

    security_disabled = False
    security_initial_key = False
    if not security_disabled and '@InitialNetworkKey' in config_node:
        init_key = find_network_key(config_node['@InitialNetworkKey'])
        if init_key is not None:
            if from_ns(init_key['@type']) == 'PreConfiguredNwkKey' or \
                    trust_center_present and from_ns(init_key['@type']) == 'DefaultNwkKey':
                c_file.write('\n/* Initial Nwk Key */\n')
                c_file.write('zps_tsAplZdoInitSecKey s_sInitSecKey = { { %s }, 0x%02x, ZPS_NWK_SEC_NETWORK_KEY };\n' % (
                    network_key_str(init_key), int(init_key['@KeySequenceNumber'], 0)))
                security_initial_key = True
    if not security_disabled and 'TrustCenter' in config_node:
        c_file.write('\n/* Trust Center */\n')
        c_file.write('PRIVATE zps_tsAplTCDeviceTable s_asTrustCenterDeviceTable[%d] = {\n' % int(
            config_node['TrustCenter']['@DeviceTableSize'], 0))
        for i in range(int(config_node['TrustCenter']['@DeviceTableSize'])):
            c_file.write('                                                            { 0xFFFF, 0 },\n')

        c_file.write('                                                                };\n')
        c_file.write('PRIVATE zps_tsTrustCenterContext s_sTrustCenterContext = {\n')
        c_file.write('    zps_vAplTrustCenterInit,\n')
        c_file.write('    zps_vAplTrustCenterUpdateDevice,\n')
        c_file.write('    zps_vAplTrustCenterRequestKey,\n')
        c_file.write(
            '    { s_asTrustCenterDeviceTable, %d },\n' % int(config_node['TrustCenter']['@DeviceTableSize'], 0))
        c_file.write(' FALSE,\n')
        c_file.write(' FALSE,\n')
        c_file.write('};\n\n')
    c_file.write('\n/* Network Layer Context */\n')
    nwk_context_size = get_lib_obj_size(objdump, options.zigbee_nwk_lib_fsp, options.endian)
    c_file.write(
        'PRIVATE uint8                   s_sNwkContext[%d] __attribute__ ((aligned (4)));\n' % nwk_context_size)
    c_file.write(
        'PRIVATE ZPS_tsNwkDiscNtEntry    s_asNwkNtDisc[%d];\n' % int(config_node['@DiscoveryNeighbourTableSize'], 0))
    c_file.write(
        'PRIVATE ZPS_tsNwkActvNtEntry    s_asNwkNtActv[%d];\n' % int(config_node['@ActiveNeighbourTableSize'], 0))
    c_file.write(
        'PRIVATE ZPS_tsNwkRtDiscEntry    s_asNwkRtDisc[%d];\n' % int(config_node['@RouteDiscoveryTableSize'], 0))
    c_file.write('PRIVATE ZPS_tsNwkRtEntry        s_asNwkRt[%d];\n' % int(config_node['@RoutingTableSize'], 0))
    c_file.write(
        'PRIVATE ZPS_tsNwkBtr            s_asNwkBtt[%d];\n' % int(config_node['@BroadcastTransactionTableSize'], 0))
    c_file.write('PRIVATE ZPS_tsNwkRctEntry       s_asNwkRct[%d];\n' % int(config_node['@RouteRecordTableSize'], 0))
    c_file.write(
        'PRIVATE ZPS_tsNwkSecMaterialSet s_asNwkSecMatSet[%d];\n' % int(config_node['@SecurityMaterialSets'], 0))
    c_file.write(
        'PRIVATE uint32                  s_asNwkInFCSet[%d];\n' % int(config_node['@ActiveNeighbourTableSize'], 0))
    c_file.write(
        'PRIVATE uint16                  s_au16NwkAddrMapNwk[%d];\n' % (
                    int(config_node['@AddressMapTableSize'], 0) + 4))
    c_file.write(
        'PRIVATE uint16                  s_au16NwkAddrMapLookup[%d];\n' % (
                    int(config_node['@AddressMapTableSize'], 0) + 4))
    c_file.write(
        'PRIVATE uint64                  s_au64NwkAddrMapExt[%d];\n' % (int(config_node['@MacTableSize'], 0) + 4))
    c_file.write('#ifdef ZPS_FRQAG\n')
    c_file.write(
        'PRIVATE uint32                  s_au32RxPacketCount[%d];\n' % int(config_node['@ActiveNeighbourTableSize'], 0))
    c_file.write(
        'PRIVATE uint32                  s_au32TxPacketCount[%d];\n' % int(config_node['@ActiveNeighbourTableSize'], 0))
    c_file.write('#endif\n')
    leave_allowed_default = 1
    if config_node_name == 'ChildNodes' and 'EndDevice' == from_ns(config_node['@type']):
        leave_allowed_default = 0
    if '@ChildTableSize' in config_node:
        c_file.write(
            'PRIVATE uint32                  s_au32ZedTimeoutCount[%d];\n' % int(config_node['@ChildTableSize'], 0))
        c_file.write(
            'PRIVATE uint8                  s_au8KeepAliveFlags[%d];\n' % int(config_node['@ChildTableSize'], 0))
    elif config_node_name == 'ChildNodes' and 'EndDevice' == from_ns(config_node['@type']):
        c_file.write(
            'PRIVATE uint32                  s_au32ZedTimeoutCount[%d];\n' %
            int(config_node['@ActiveNeighbourTableSize'], 0),
        )
        c_file.write(
            'PRIVATE uint8                  s_au8KeepAliveFlags[%d];\n' %
            int(config_node['@ActiveNeighbourTableSize'], 0),
        )
    else:
        c_file.write(
            'PRIVATE uint32                  s_au32ZedTimeoutCount[%d];\n' %
            int(config_node['@ActiveNeighbourTableSize'], 0),
        )
        c_file.write(
            'PRIVATE uint8                  s_au8KeepAliveFlags[%d];\n' %
            int(config_node['@ActiveNeighbourTableSize'], 0),
        )
    c_file.write(
        '\n'
        'PRIVATE const zps_tsNwkNibInitialValues s_sNibInitialValues =\n'
        '{\n'
        '    600,\n'
        '    05,\n'
        '    7,\n'
        '    15,\n'
        '    1,\n'
        '    2,\n'
        '    11,\n'
        '    18,\n'
        '    0,\n'
        '    2,\n'
        '    0,\n'
        '    1,\n'
        '    0,\n'
        '    15,\n'
        '    3,\n'
        '    3,\n'
        '    255,\n'
        '    5,\n'
        '    TRUE,\n'
        '    TRUE,\n'
        '    5,\n'
        '    4,')
    c_file.write('\n    %d,' % leave_allowed_default)
    c_file.write('\n    2,\n    8\n    ,0/* u16VerifyLinkCostTransmitRate */\n};\n\n')
    c_file.write('\nPRIVATE const ZPS_tsNwkNibTblSize     s_sNwkTblSize = {\n')
    c_file.write('    %d,\n' % int(config_node['@ActiveNeighbourTableSize'], 0))
    c_file.write('    %d,\n' % int(config_node['@RoutingTableSize'], 0))
    c_file.write('    %d,\n' % int(config_node['@RouteRecordTableSize'], 0))
    c_file.write('    %d,\n' % int(config_node['@AddressMapTableSize'], 0))
    c_file.write('    %d,\n' % int(config_node['@DiscoveryNeighbourTableSize'], 0))
    c_file.write('    %d,\n' % int(config_node['@RouteDiscoveryTableSize'], 0))
    c_file.write('    %d,\n' % int(config_node['@BroadcastTransactionTableSize'], 0))
    c_file.write('    %d,\n' % int(config_node['@SecurityMaterialSets'], 0))
    c_file.write('    sizeof(s_sNibInitialValues),\n')
    if '@ChildTableSize' in config_node:
        c_file.write('    %d,\n' % int(config_node['@ChildTableSize'], 0))
    elif config_node_name == 'ChildNodes' and 'EndDevice' == from_ns(config_node['@type']):
        c_file.write('    %d,\n' % int(config_node['@ActiveNeighbourTableSize'], 0))
    else:
        c_file.write('    %d,\n' % (int(config_node['@ActiveNeighbourTableSize'], 0) / 6))
    c_file.write('    %d\n' % int(config_node['@MacTableSize'], 0))
    c_file.write('};\n')
    c_file.write(
        '\n'
        'PRIVATE const ZPS_tsNwkNibTbl s_sNwkTbl = {\n'
        '    s_asNwkNtDisc,\n'
        '    s_asNwkNtActv,\n'
        '    s_asNwkRtDisc,\n'
        '    s_asNwkRt,\n'
        '    s_asNwkBtt,\n'
        '    s_asNwkRct,\n'
        '    s_asNwkSecMatSet,\n'
        '    (ZPS_tsNwkNibInitialValues*)&s_sNibInitialValues,\n'
        '    s_au16NwkAddrMapNwk,\n'
        '    s_au16NwkAddrMapLookup,\n'
        '    s_asNwkInFCSet,\n'
        '#if (defined JENNIC_CHIP_FAMILY_JN516x) || (JENNIC_CHIP_FAMILY_JN517x)\n'
        '    0,\n'
        '#endif\n'
        '    s_au64NwkAddrMapExt,\n'
        '    s_au32ZedTimeoutCount,\n'
        '    s_au8KeepAliveFlags,\n'
        '#ifdef ZPS_FRQAG\n'
        '    s_au32RxPacketCount,\n'
        '    s_au32TxPacketCount,\n'
        '#else\n'
        '    NULL,\n'
        '    NULL,\n'
        '#endif    \n'
        '};\n')
    c_file.write('\n/* Application Layer Context */\n')
    if not security_disabled and 'TrustCenter' in config_node:
        num_request_key_requests = 4
    else:
        num_request_key_requests = 1
    timeout_request_key = 15
    c_file.write('PRIVATE zps_tsRequestKeyRequests s_asRequestKeyRequests[%d];\n' % num_request_key_requests)
    c_file.write('PRIVATE zps_tsApl s_sApl = {\n')
    c_file.write('    s_sNwkContext,\n')
    c_file.write('    &s_sNwkTblSize,\n')
    c_file.write('    &s_sNwkTbl,\n')
    c_file.write('    NULL,\n')
    c_file.write('    &s_sAplAib,\n')
    c_file.write('    zps_vGetZpsMutex,\n')
    if '@DefaultCallbackName' in config_node:
        default_callback_name = config_node['@DefaultCallbackName']
    else:
        return 1
    c_file.write('    &%s,\n' % default_callback_name)
    mac_mlme_dcfm_ind_message = 'zps_msgMlmeDcfmInd'
    mac_mcps_dcfm_ind_message = 'zps_msgMcpsDcfmInd'
    mac_time_event_message = 'zps_TimeEvents'
    c_file.write('    &%s,\n' % mac_mcps_dcfm_ind_message)
    c_file.write('    &%s,\n' % mac_mlme_dcfm_ind_message)
    c_file.write('    &%s,\n' % mac_time_event_message)
    mac_mcps_dcfm_event_message = 'zps_msgMcpsDcfm'
    c_file.write('    &%s,\n' % mac_mcps_dcfm_event_message)
    c_file.write('    { 0 },\n')

    node_type = '<undefined>'
    if 'Coordinator' == config_node_name:
        node_type = 'ZPS_ZDO_DEVICE_COORD'
    elif 'ChildNodes' == config_node_name:
        if 'Router' == from_ns(config_node['@type']):
            node_type = 'ZPS_ZDO_DEVICE_ROUTER'
        elif 'EndDevice' == from_ns(config_node['@type']):
            node_type = 'ZPS_ZDO_DEVICE_ENDDEVICE'
    permit_joining_time = 0
    if '@PermitJoiningTime' in config_node:
        permit_joining_time = int(config_node['@PermitJoiningTime'], 0)
    scan_duration = 4
    if '@ScanDuration' in config_node:
        scan_duration = int(config_node['@ScanDuration'], 0)
    c_file.write('    {\n')
    c_file.write('         { 0x1B, 0x19, 0x4A },\n')
    c_file.write('        0,\n')
    c_file.write('        %s,\n' % node_type)
    c_file.write('        ZPS_ZDO_PRECONFIGURED_LINK_KEY,\n')
    c_file.write('        0x%02x,\n' % permit_joining_time)
    c_file.write('        2,\n')
    c_file.write('        2,\n')
    c_file.write('        %d,\n' % scan_duration)
    c_file.write('        FALSE,\n')
    c_file.write('        s_asAplZdoServers,\n')
    c_file.write('        vZdoServersInit,\n')
    c_file.write('        { /* timer struct */},\n')
    c_file.write('        { /* timer struct */},\n')
    c_file.write('        0,\n')
    max_num_poll_failures = 3
    if '@NumPollFailuresBeforeRejoin' in config_node:
        max_num_poll_failures = int(config_node['@NumPollFailuresBeforeRejoin'], 0)
    c_file.write('        %d,\n' % max_num_poll_failures)
    c_file.write('        %d,\n' % security_disabled)
    if security_disabled or not security_initial_key:
        c_file.write('        NULL,\n')
    elif security_initial_key:
        c_file.write('        &s_sInitSecKey,\n')
    c_file.write('        0,\n')
    c_file.write('        NULL,\n')
    c_file.write('        NULL,\n')
    c_file.write('        s_asRequestKeyRequests,\n')
    c_file.write('        %d,\n' % (timeout_request_key * 62500))
    c_file.write('        %d\n' % num_request_key_requests)
    c_file.write('    },\n')
    c_file.write('    {\n')
    c_file.write('        NULL,\n')
    c_file.write('        &s_sNodeDescriptor,\n')
    c_file.write('        &s_sNodePowerDescriptor,\n')
    c_file.write('        %d,\n' % len(as_list(config_node['Endpoints'])))
    c_file.write('        s_asSimpleDescConts,\n')
    if '@UserDescriptor' in config_node:
        c_file.write('        &s_sUserDescriptor,\n')
    else:
        c_file.write('        NULL,\n')
    c_file.write('        NULL,\n')
    c_file.write('        0xff,\n')
    c_file.write('        0x00\n')
    c_file.write('    },\n')
    c_file.write('    {\n')
    c_file.write('        NULL,\n')
    c_file.write('        NULL,\n')
    c_file.write('        NULL,\n')
    c_file.write('        NULL,\n')
    c_file.write('        NULL,\n')
    c_file.write('        NULL,\n')
    c_file.write('        &s_sApsDuplicateTable,\n')
    c_file.write('        s_asApsSyncMsgPool,\n')
    aps_duplicate_table_size = 1
    if '@APSDuplicateTableSize' in config_node:
        aps_duplicate_table_size = int(config_node['@APSDuplicateTableSize'], 0)
    c_file.write('        0x%02x,\n' % aps_duplicate_table_size)
    c_file.write('        0,\n')
    c_file.write('        %d,\n' % int(config_node['@MaxNumSimultaneousApsdeAckReq'], 0))
    c_file.write('        0,\n')
    c_file.write('        { s_asApsDcfmRecordPool, 1, %d },\n' % int(config_node['@MaxNumSimultaneousApsdeReq'], 0))
    fragmentation_enabled = int(config_node['@FragmentationMaxNumSimulRx'], 0) > 0 or \
        int(config_node['@FragmentationMaxNumSimulTx'], 0) > 0
    aps_persistence_time = 100
    if '@APSPersistenceTime' in config_node:
        if int(config_node['@APSPersistenceTime'], 0) > 25:
            aps_persistence_time = int(config_node['@APSPersistenceTime'], 0)
    if int(config_node['@FragmentationMaxNumSimulRx'], 0) > 0:
        c_file.write('        { s_asApsFragRxPool, %d, %d },\n' % (
            int(config_node['@FragmentationMaxNumSimulRx'], 0), aps_persistence_time))
    else:
        c_file.write('        { NULL, 0, 0 },\n')
    if int(config_node['@FragmentationMaxNumSimulTx'], 0) > 0:
        c_file.write('        { s_asApsFragTxPool, %d },\n' % int(config_node['@FragmentationMaxNumSimulTx'], 0))
    else:
        c_file.write('        { NULL, 0 },\n')
    if int(config_node['@FragmentationMaxNumSimulTx'], 0) > 0:
        c_file.write('        zps_eStartFragmentedTransmission,\n')
        c_file.write('        zps_vHandleExtendedDataAckFrame,\n')
    else:
        c_file.write('        NULL,\n')
        c_file.write('        NULL,\n')
    if int(config_node['@FragmentationMaxNumSimulRx'], 0) > 0:
        c_file.write('        zps_vHandleApsdeDataFragInd,\n')
    else:
        c_file.write('        zps_vHandleApsdeDataFragIndNotSupported,\n')
    c_file.write('        { &s_sApsmeCmdContainer_1, NULL },\n')
    aps_poll_period = 100
    if '@APSPollPeriod' in config_node:
        if int(config_node['@APSPollPeriod'], 0) > 25:
            aps_poll_period = int(config_node['@APSPollPeriod'], 0)
    c_file.write('        { { /* Timer */}, %d, 0 },\n' % aps_poll_period)
    c_file.write('        { NULL, NULL },\n')
    c_file.write('        { /* Timer */}\n')
    c_file.write('    },\n')
    if not security_disabled and 'TrustCenter' in config_node:
        c_file.write('    &s_sTrustCenterContext\n')
    else:
        c_file.write('    NULL\n')
    c_file.write('};\n')
    c_file.write('\nconst void *zps_g_pvApl = &s_sApl;\n')
    c_file.write(
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
    c_file.write('\n/****************************************************************************\n')
    c_file.write(' *\n')
    c_file.write(' * NAME: ZPS_psMacIFTGetTable\n')
    c_file.write(' *\n')
    c_file.write(' * DESCRIPTION:\n')
    c_file.write(' * Obtain the pointer to the Mac inteface table \n')
    c_file.write(' *\n')
    c_file.write(' * PARAMETERS \t\t\tName  \t   \t\tRW  \tUsage \n')
    c_file.write(' *\n')
    c_file.write(' * RETURNS:\n')
    c_file.write(' * Address of Mac interface table if successful, NULL otherwise \n')
    c_file.write(' *\n')
    c_file.write(' ****************************************************************************/ \n')
    c_file.write(' PUBLIC MAC_tsMacInterfaceTable* ZPS_psMacIFTGetTable(void) \n')
    c_file.write(' {\n')
    c_file.write('\t return &g_asMacInterfaceTable; \n')
    c_file.write(' }\n')
    c_file.write('\n/****************************************************************************\n')
    c_file.write(' *\n')
    c_file.write(' * NAME: ZPS_psMacIFTGetInterface \n')
    c_file.write(' *\n')
    c_file.write(' * DESCRIPTION:\n')
    c_file.write(' * Get the Mac interface entry from the MAC interface table for the specified\n')
    c_file.write(' * Mac ID\n')
    c_file.write(' *\n')
    c_file.write(' * PARAMETERS \tName  \t\tRW  \tUsage\n')
    c_file.write(' *\t\t\t\tu8MacID\t\tR\t\tThe Mac Id for the interface\n')
    c_file.write(' * RETURNS:\n')
    c_file.write(' * Address of Mac interface structure if found, NULL otherwise\n')
    c_file.write(' *\n')
    c_file.write(' ****************************************************************************/ \n')
    c_file.write(' PUBLIC MAC_tsMacInterface* ZPS_psMacIFTGetInterface(uint8 u8MacID)\n')
    c_file.write(' { \n')
    c_file.write('\t MAC_tsMacInterface *pRet = NULL;\n')
    c_file.write(' \t if(u8MacID < g_asMacInterfaceTable.u8NumInterfaces) \n')
    c_file.write(' \t {\n')
    c_file.write(' \t\t pRet = &g_asMacInterfaceTable.psMacInterfaces[u8MacID];\n')
    c_file.write(' \t }\n')
    c_file.write(' \t return pRet;\n')
    c_file.write(' }\n')
    if 'ZDOServers' in config_node:
        c_file.write('\n/* ZDO Server Initialisation */\n')
        c_file.write('PRIVATE void vZdoServersInit(void)\n{\n')
        if endian == 'BIG_ENDIAN':
            zps_apl_version = 'ZPS_APL_Version_3v0'
            zps_nwk_version = 'ZPS_NWK_Version_3v0'
            c_file.write('    /* Version compatibility check */\n')
            c_file.write('    asm(".extern %s" : ) ;\n' % zps_apl_version)
            c_file.write('    asm("l.addi r0,r0,hi(%s)" : );\n' % zps_apl_version)
            c_file.write('    asm(".extern %s" : ) ;\n' % zps_nwk_version)
            c_file.write('    asm("l.addi r0,r0,hi(%s)" : );\n' % zps_nwk_version)
        else:
            zps_apl_version = 'ZPS_APL_Version_3v0'
            zps_nwk_version = 'ZPS_NWK_Version_3v0'
            c_file.write('    /* Version compatibility check */\n')
            c_file.write('    asm(".extern %s" : ) ;\n' % zps_apl_version)
            c_file.write('    asm("LDR R0, =%s" : );\n' % zps_apl_version)
            c_file.write('    asm(".extern %s" : ) ;\n' % zps_nwk_version)
            c_file.write('    asm("LDR R0, =%s" : );\n' % zps_nwk_version)
    for tag_name, server in get_child_nodes(config_node['ZDOServers']):
        if tag_name != 'MgmtNWKEnhanceUpdateServer':
            c_file.write('    zps_vAplZdo%sInit(' % tag_name)
            (output_params, output_param_types) = ZDO_SERVERS[tag_name]
            output_params(c_file, config_node, tag_name, server)
            c_file.write(');\n')

    if 'Coordinator' == config_node_name:
        c_file.write('    zps_vRegisterCallbackForSecondsTick(ZPS_vSecondTimerCallback);\n')
    elif 'Router' == from_ns(config_node['@type']):
        c_file.write('    zps_vRegisterCallbackForSecondsTick(ZPS_vSecondTimerCallback);\n')
    c_file.write('}\n')
    c_file.write('\nPUBLIC void* ZPS_vGetGpContext(void)\n{\n')
    c_file.write('\n    return g_psGreenPowerContext;\n}\n')
    c_file.write('\nPUBLIC void* zps_vGetZpsMutex(void)\n{\n')
    c_file.write('\n    return &g_pbZpsMutex;\n}\n')
    c_file.write('\n\nPUBLIC void ZPS_vGetOptionalFeatures(void)\n{\n')
    if '@InterPAN' in config_node:
        if 'true' == config_node['@InterPAN'].lower():
            c_file.write('   ZPS_vAfInterPanInit();\n')
    if '@GreenPowerSupport' in config_node:
        if 'true' == config_node['@GreenPowerSupport'].lower():
            c_file.write('   ZPS_vRegisterGreenPower();\n')
            if '@GreenPowerTxQueue' in config_node:
                c_file.write('   ZPS_vZgpInitGpTxQueue();\n')
            if 'GreenPowerSecurityTable' in config_node:
                c_file.write('   ZPS_vZgpInitGpSecurityTable();\n')
    c_file.write('}\n')
    c_file.write(
        '\n'
        '/****************************************************************************/\n'
        '/***        END OF FILE                                                   ***/\n'
        '/****************************************************************************/\n')
    c_file.close()
    if os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_READONLY)
    return


def output_header(dir, config_node_name, config_node):
    fsp = os.path.join(dir, 'zps_gen.h')
    if os.path.exists(fsp) and os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_NORMAL)
    h_file = open(fsp, 'w')
    h_file.write(
        '/****************************************************************************\n'
        ' *\n'
        ' *                 THIS IS A GENERATED FILE. DO NOT EDIT!\n'
        ' *\n'
        ' * MODULE:         ZPSConfig\n'
        ' *\n'
        ' * COMPONENT:      zps_gen.h\n'
        ' *\n'
        ' * DATE:           %s\n'
        ' *\n'
        ' * AUTHOR:         NXP Zigbee Protocol Stack Configuration Tool\n'
        ' *\n'
        ' * DESCRIPTION:    ZPS definitions\n'
        ' *\n'
        ' ****************************************************************************\n'
        ' *\n'
        '\n'
        ' * This software is owned by NXP B.V. and/or its supplier and is protected\n'
        ' * under applicable copyright laws. All rights are reserved. We grant You,\n'
        ' * and any third parties, a license to use this software solely and\n'
        ' * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].\n'
        ' * You, and any third parties must reproduce the copyright and warranty notice\n'
        ' * and any other legend of ownership on each copy or partial copy of the\n'
        ' * software.\n'
        ' *\n'
        ' * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"\n'
        ' * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n'
        ' * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE\n'
        ' * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE\n'
        ' * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR\n'
        ' * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF\n'
        ' * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS\n'
        ' * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN\n'
        ' * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)\n'
        ' * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE\n'
        ' * POSSIBILITY OF SUCH DAMAGE.\n'
        ' *\n'
        ' * Copyright NXP B.V. 2017. All rights reserved\n'
        ' ****************************************************************************/\n'
        '' % datetime.datetime.ctime(datetime.datetime.now()))
    h_file.write(
        '\n'
        '#ifndef _ZPS_GEN_H\n'
        '#define _ZPS_GEN_H\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        Macro Definitions                                             ***/\n'
        '/****************************************************************************/\n'
        '\n')
    h_file.write('#define ZPS_NWK_OPT_ALL\n')
    if 'Coordinator' == config_node_name:
        h_file.write('#define ZPS_COORDINATOR\n')
    elif 'Childnodes' == config_node_name:
        if 'Router' == from_ns(config_node['@type']):
            h_file.write('#define ZPS_ROUTER\n')
        elif 'EndDevice' == from_ns(config_node['@type']):
            h_file.write('#define ZPS_END_DEVICE\n')
    h_file.write('#define ZPS_NODE_%s\n' % config_node['@Name'].upper())
    for profile in as_list(config['ZigbeeWirelessNetwork']['Profiles']):
        h_file.write("\n/* Profile '%s' */\n" % profile['@Name'])
        id = int(profile['@Id'], 0)
        h_file.write('#define %s_PROFILE_ID    (0x%04x)\n' % (profile['@Name'].upper(), id))
        for cluster in as_list(profile['Clusters']):
            id = int(cluster['@Id'], 0)
            h_file.write(
                '#define %s_%s_CLUSTER_ID    (0x%04x)\n' %
                (profile['@Name'].upper(), cluster['@Name'].upper(), id),
            )

    node = config['ZigbeeWirelessNetwork']['Coordinator']
    h_file.write("\n/* Node '%s' */\n" % node['@Name'])
    h_file.write('/* Endpoints */\n')
    for endpoint in as_list(node['Endpoints']):
        id = int(endpoint['@Id'], 0)
        h_file.write('#define %s_%s_ENDPOINT    (%d)\n' % (node['@Name'].upper(), endpoint['@Name'].upper(), id))

    if 'ChildNodes' in config['ZigbeeWirelessNetwork']:
        for node in as_list(config['ZigbeeWirelessNetwork']['ChildNodes']):
            h_file.write("\n/* Node '%s' */\n" % node['@Name'])
            h_file.write('\n/* Endpoints */\n')
            for endpoint in as_list(node['Endpoints']):
                id = int(endpoint['@Id'], 0)
                h_file.write(
                    '#define %s_%s_ENDPOINT    (%d)\n' % (node['@Name'].upper(), endpoint['@Name'].upper(), id))

    h_file.write('/* Table Sizes */\n')
    if 'BindingTable' in config_node:
        bind_table_size = int(config_node['BindingTable']['@Size'], 0)
    else:
        bind_table_size = 0
    if 'GroupTable' in config_node:
        group_table_size = int(config_node['GroupTable']['@Size'], 0)
    else:
        group_table_size = 0
    if '@ChildTableSize' in config_node:
        child_table_size = int(config_node['@ChildTableSize'], 0)
    else:
        child_table_size = 0
    channel_mask_list_count = 0
    if 'MacInterfaceList' in config_node:
        for interface in as_list(config_node['MacInterfaceList']['MacInterface']):
            channel_mask_list_count += int(interface['@ChannelListSize'])

    else:
        channel_mask_list_count = 0
    h_file.write(
        '#define ZPS_NEIGHBOUR_TABLE_SIZE      (%d)\n' %
        int(config_node['@ActiveNeighbourTableSize'], 0),
    )
    h_file.write(
        '#define ZPS_ADDRESS_MAP_TABLE_SIZE    (%d)\n' %
        int(config_node['@AddressMapTableSize'], 0),
    )
    h_file.write(
        '#define ZPS_ROUTING_TABLE_SIZE        (%d)\n' %
        int(config_node['@RoutingTableSize'], 0),
    )
    h_file.write(
        '#define ZPS_MAC_ADDRESS_TABLE_SIZE    (%d)\n' %
        int(config_node['@MacTableSize'], 0),
    )
    h_file.write('#define ZPS_BINDING_TABLE_SIZE        (%d)\n' % bind_table_size)
    h_file.write('#define ZPS_GROUP_TABLE_SIZE          (%d)\n' % group_table_size)
    h_file.write('#define ZPS_CHILD_TABLE_SIZE          (%d)\n' % child_table_size)
    h_file.write(
        '#define ZPS_MAX_CHANNEL_LIST_SIZE     (%d)\n' % channel_mask_list_count,
    )
    h_file.write(
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
    h_file.close()
    if os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_READONLY)


def output_default_server_init_params(file, config_node, node_name, node):
    apdu = find_apdu(config_node, node['@OutputAPdu'])
    if apdu is not None:
        file.write('&s_s%sContext, %s' % (node_name, apdu['@Name']))
    else:
        print("WARNING: Server '%s' has no output APDU defined.\n" % node_name)
    return


def output_default_server_init_param_types(file):
    file.write('void *, PDUM_thAPdu ')


def output_end_device_bind_server_init_params(file, config_node, node_name, node):
    apdu = find_apdu(config_node, node['@OutputAPdu'])
    if apdu is not None:
        file.write('&s_s%sContext, %s, %d, %d' % (
            node_name,
            apdu['@Name'],
            int(node['@Timeout'], 0) * 62500,
            int(node['@BindNumRetries'], 0),
        ))
    else:
        print("WARNING: Server '%s' has no output APDU defined.\n" % node_name)
    return


def output_end_device_bind_server_init_param_types(file):
    file.write('void *, PDUM_thAPdu , uint32 , uint8 ')


def output_device_annce_server_init_params(file, config_node, node_name, node):
    file.write('&s_s%sContext' % node_name)


def output_device_annce_server_init_param_types(file):
    file.write('void *')


def output_mgmt_nwk_update_server_init_params(file, config_node, node_name, node):
    apdu = find_apdu(config_node, node['@OutputAPdu'])
    if apdu is not None:
        file.write('&s_s%sContext, %s, &s_sApl' % (node_name, apdu['@Name']))
    else:
        print("WARNING: Server '%s' has no output APDU defined.\n" % node_name)
    return


def output_mgmt_nwk_update_init_param_types(file):
    file.write('void *, PDUM_thAPdu , void *')


def output_bind_request_server_init_params(file, config_node, node_name, node):
    TimeInterval = int(node['@TimeInterval'], 0)
    NumOfSimRequests = int(node['@SimultaneousRequests'], 0)
    file.write(
        '&s_s%sContext, %d, %d, %s' % (
            node_name,
            TimeInterval,
            NumOfSimRequests,
            's_sBindRequestServerAcksDcfmContext',
        ),
    )


def output_bind_request_server_init_param_types(file):
    file.write('void *, uint8, uint8, zps_tsZdoServerConfAckContext* ')


ZDO_SERVERS = {
    'EndDeviceBindServer': (
        output_end_device_bind_server_init_params,
        output_end_device_bind_server_init_param_types,
    ),
    'DefaultServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'DeviceAnnceServer': (
        output_device_annce_server_init_params,
        output_device_annce_server_init_param_types,
    ),
    'ActiveEpServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'NwkAddrServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'IeeeAddrServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'SystemServerDiscoveryServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'PermitJoiningServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'NodeDescServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'PowerDescServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'MatchDescServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'SimpleDescServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'MgmtLqiServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'MgmtRtgServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'MgmtLeaveServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'MgmtNWKUpdateServer': (
        output_mgmt_nwk_update_server_init_params,
        output_mgmt_nwk_update_init_param_types,
    ),
    'MgmtBindServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'BindUnbindServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'ExtendedActiveEpServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'ExtendedSimpleDescServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'ZdoClient': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'BindRequestServer': (
        output_bind_request_server_init_params,
        output_bind_request_server_init_param_types,
    ),
    'ParentAnnceServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'MgmtMibIeeeServer': (
        output_default_server_init_params,
        output_default_server_init_param_types,
    ),
    'MgmtNWKEnhanceUpdateServer': (
        output_mgmt_nwk_update_server_init_params,
        output_mgmt_nwk_update_init_param_types,
    ),
}

PATCH_FUNCTIONS = [
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
exe_fsp = os.path.abspath(sys.executable)
if os.name == 'nt':
    d = win32api.GetFileVersionInfo(exe_fsp, '\\')
    version = '%d.%d.%d' % (
        d['FileVersionMS'] / (256 * 256), d['FileVersionMS'] % (256 * 256), d['FileVersionLS'] / (256 * 256))
else:
    version = 'x.x.x'
if '' == options.zigbee_node_name:
    print('ERROR: A node must be specified.\n')
    sys.exit(9)

namespaces = {
    "http://www.nxp.com/zpscfg": None,
    "http://www.w3.org/2001/XMLSchema-instance": None,
}

optional_features = 0
if options.optional_features:
    with open(options.config_filename, 'rb') as f:
        config = xmltodict.parse(f, process_namespaces=True, namespaces=namespaces)
    _, node = find_node(options.zigbee_node_name)
    if '@InterPAN' in node:
        if 'true' == node['@InterPAN'].lower():
            optional_features |= 1
    if '@GreenPowerSupport' in node:
        if 'true' == node['@GreenPowerSupport'].lower():
            optional_features |= 2
    print(optional_features)
    sys.exit(0)
print('ZPSConfig - Zigbee Protocol Stack Configuration Tool v%s Build %s\n' % (version, '93315M'))
sys.stdout.flush()
if len(sys.argv) <= 1:
    print(
        '\n'
        '\tThis software is owned by Jennic and/or its supplier and is protected\n'
        '\tunder applicable copyright laws. All rights are reserved. We grant You,\n'
        '\tand any third parties, a license to use this software solely and\n'
        '\texclusively on Jennic products. You, and any third parties must reproduce\n'
        '\tthe copyright and warranty notice and any other legend of ownership on each\n'
        '\tcopy or partial copy of the software.\n'
        '\t\n'
        '\tTHIS SOFTWARE IS PROVIDED "AS IS". JENNIC MAKES NO WARRANTIES, WHETHER\n'
        '\tEXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED\n'
        '\tWARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE,\n'
        '\tACCURACY OR LACK OF NEGLIGENCE. JENNIC SHALL NOT, IN ANY CIRCUMSTANCES,\n'
        '\tBE LIABLE FOR ANY DAMAGES, INCLUDING, BUT NOT LIMITED TO, SPECIAL,\n'
        '\tINCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER.\n'
        '\n'
        '\t(c) Copyright Jennic Ltd 2008. All rights reserved.\n')
    print('For help: %s --help' % sys.argv[0])
    sys.exit(0)
if options.config_filename is None:
    print('ERROR: a configuration file must be specified.\n')
    sys.exit(2)
if not os.path.exists(options.config_filename):
    print("ERROR: unable to open configuration file '%s'.\n" % options.config_filename)
    sys.exit(3)
if not os.path.exists(options.zigbee_nwk_lib_fsp):
    print("ERROR: unable to locate Zigbee target library file '%s'.\n" % options.zigbee_nwk_lib_fsp)
    sys.exit(4)
if not os.path.exists(options.zigbee_apl_lib_fsp):
    print("ERROR: unable to locate Zigbee target library file '%s'.\n" % options.zigbee_apl_lib_fsp)
    sys.exit(5)
if options.output_dir is not None and not os.path.exists(options.output_dir):
    print("ERROR: Output directory '%s' does not exist.\n" % options.output_dir)
    sys.exit(6)
if not os.path.exists(options.tools_dir):
    print("ERROR: unable to locate Compiler Tools directory '%s'.\n" % options.tools_dir)
    sys.exit(7)
if options.endian == 'BIG_ENDIAN':
    objdump = os.path.normpath(os.path.join(options.tools_dir, 'bin', 'ba-elf-objdump'))
elif os.name == 'nt':
    objdump = os.path.normpath(os.path.join(options.tools_dir, 'bin', 'arm-none-eabi-objdump'))
else:
    objdump = os.path.normpath(os.path.join(options.tools_dir, 'bin', 'arm-none-eabi-objdump'))
with open(options.config_filename, 'rb') as f:
    config = xmltodict.parse(f, process_namespaces=True, namespaces=namespaces)
if '' == options.zigbee_node_name:
    print('ERROR: A node must be specified.\n')
    sys.exit(9)
if validate_configuration(options.zigbee_node_name):
    node_name, node = find_node(options.zigbee_node_name)
    output_header(options.output_dir, node_name, node)
    output_c(options.output_dir, node_name, node, options.endian)
    print('Done.\n')
    sys.exit(0)
else:
    sys.exit(1)
