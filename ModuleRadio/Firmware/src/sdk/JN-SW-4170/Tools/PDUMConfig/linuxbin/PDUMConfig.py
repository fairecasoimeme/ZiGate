#!/usr/bin/env python3

import datetime
import os
import re
import sys
from optparse import OptionParser

import xmltodict

if os.name == 'nt':
    import win32api
    import win32con


def get_child_nodes(root):
    return [
        item
        for sublist in (
            v if isinstance(v, (list, tuple)) else [v]
            for k, v in root.items()
            if not k.startswith('@')
        )
        for item in sublist
    ]


def as_list(item):
    return item if isinstance(item, list) else [item]


parser = OptionParser()
parser.add_option(
    '-z',
    '--zigbee',
    dest='zigbee_node_name',
    default='',
    help='Output configuration for Zigbee Protocol Stack for the specified node.',
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
    '-e',
    '--endian',
    dest='endian',
    type='string',
    default='BIG_ENDIAN',
    help='Endian of the processor BIG_ENDIAN or LITTLE_ENDIAN',
)
(options, args) = parser.parse_args(sys.argv[1:])


def check_for_duplicate_names(nodes, n1):
    if '@Name' not in n1:
        return False
    for n2 in nodes:
        if n2 != n1 and '@Name' in n2 and n1['@Name'] == n2['@Name']:
            return True

    return False


def validate_configuration(config_node):
    """
    :type config_node: dict
    """
    node_name = config_node['@Name']
    name_check = re.compile(r'[a-zA-Z_][a-zA-Z_0-9]*')
    if 'PDUConfiguration' in config_node:
        if '@NumNPDUs' not in config_node['PDUConfiguration']:
            print("ERROR: The PDU Manager for node '%s' must have a NumNPDUs attribute.\n" % node_name)
            return False
        elif int(config_node['PDUConfiguration']['@NumNPDUs'], 10) < 8:
            print("ERROR: The PDU Manager for node '%s' must have at least 8 NPDUs configured" % node_name)
            return False
        if 'APDUs' not in config_node['PDUConfiguration']:
            print("ERROR: The PDU Manager for node '%s' does not have any APDUs.\n" % node_name)
            return False
        else:
            for apdu in as_list(config_node['PDUConfiguration']['APDUs']):
                if '@Name' not in apdu:
                    print("ERROR: An APDU for node '%s' does not have a Name specified.\n" % node_name)
                    return False
                else:
                    result = name_check.match(apdu['@Name'])
                    if result.group(0) != apdu['@Name']:
                        print(
                            "ERROR: The APDU '%s' for node '%s' is not a valid C identifier.\n" %
                            (apdu['@Name'], node_name))
                        return False
                if '@Id' not in apdu:
                    print(
                        "ERROR: The APDU '%s' for node '%s' does not have an Id specified.\n" %
                        (apdu['@Name'], node_name))
                    return False
                if '@Size' not in apdu:
                    print(
                        "ERROR: The APDU '%s' for node '%s' does not have a Size specified.\n" %
                        (apdu['@Name'], node_name))
                    return False
                elif int(apdu['@Size'], 10) < 1:
                    print(
                        "ERROR: The APDU '%s' for node '%s' must have a Size of at least 1.\n" %
                        (apdu['@Name'], node_name))
                    return False
                if '@Instances' not in apdu:
                    print(
                        "ERROR: The APDU '%s' for node '%s' does not have a number of Instances specified.\n" %
                        (apdu['@Name'], node_name))
                    return False
                elif int(apdu['@Instances'], 10) < 1:
                    print(
                        "ERROR: The APDU '%s' for node '%s' must have a number of Instances of at least 1.\n" %
                        (apdu['@Name'], node_name))
                    return False
                if check_for_duplicate_names(as_list(config_node['PDUConfiguration']['APDUs']), apdu):
                    print(
                        "ERROR: There are one or more APDUs with the name '%s' for node '%s'. "
                        "APDUs must have unique names.\n" % (apdu['@Name'], node_name))
                    return False

    else:
        print("ERROR: The node '%s' must have a PDU Manager element.\n" % node_name)
        return False
    return True


def output_c(output_dir, pdum_config, s_endian):
    """
    :type output_dir: str
    :type pdum_config: dict
    :type s_endian: str
    """
    fsp = os.path.join(output_dir, 'pdum_gen.c')
    if os.path.exists(fsp) and os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_NORMAL)
    c_file = open(fsp, 'w')
    c_file.write(
        '/****************************************************************************\n'
        ' *\n'
        ' *                 THIS IS A GENERATED FILE. DO NOT EDIT!\n'
        ' *\n'
        ' * MODULE:         PDUMCOnfig\n'
        ' *\n'
        ' * COMPONENT:      pdum_gen.c\n'
        ' *\n'
        ' * DATE:           %s\n'
        ' *\n'
        ' * AUTHOR:         NXP PDU Manager Configuration Tool\n'
        ' *\n'
        ' * DESCRIPTION:    PDU definitions\n'
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
        '#include <pdum_nwk.h>\n'
        '#include <pdum_apl.h>\n'
        '\n' % datetime.datetime.ctime(datetime.datetime.now()))
    c_file.write(
        '\n'
        '/****************************************************************************/\n'
        '/***        Macro Definitions                                             ***/\n'
        '/****************************************************************************/\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        Type Definitions                                              ***/\n'
        '/****************************************************************************/\n'
        '\n'
        'struct pdum_tsAPdu_tag {\n'
        '    struct pdum_tsAPduInstance_tag *psAPduInstances;\n'
        '    uint16 u16FreeListHeadIdx;\n'
        '    uint16 u16Size;\n'
        '    uint16 u16NumInstances;\n'
        '};\n'
        '\n'
        'struct pdum_tsAPduInstance_tag {\n'
        '    uint8 *au8Storage;\n'
        '    uint16 u16Size;\n'
        '    uint16 u16NextAPduInstIdx;\n'
        '    uint16 u16APduIdx;\n'
        '};\n'
        '\n'
        'typedef struct pdum_tsAPduInstance_tag pdum_tsAPduInstance;\n'
        'typedef struct pdum_tsAPdu_tag pdum_tsAPdu;\n'
        '\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        Function Prototypes                                           ***/\n'
        '/****************************************************************************/\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        Local Variables                                               ***/\n'
        '/****************************************************************************/\n'
        '\n')
    c_file.write('\n/* NPDU Pool */\n')
    npdu_pool_size = int(pdum_config['@NumNPDUs'], 10)
    c_file.write('PRIVATE pdum_tsNPdu s_asNPduPool[%d];\n' % npdu_pool_size)
    c_file.write('\n/* APDU Pool */\n')
    a = 0
    for apdu in as_list(config_node['PDUConfiguration']['APDUs']):
        apdu_size = int(apdu['@Size'])
        apdu_instances = int(apdu['@Instances'])
        for i in range(0, apdu_instances):
            storage_name = 's_au8%sInstance%dStorage' % (apdu['@Name'], i)
            c_file.write('PRIVATE uint8 %s[%d];\n' % (storage_name, apdu_size))

        c_file.write('PUBLIC pdum_tsAPduInstance s_as%sInstances[%d] = {\n' % (apdu['@Name'], apdu_instances))
        for i in range(0, apdu_instances):
            c_file.write('    { s_au8%sInstance%dStorage, 0, 0, %d },\n' % (apdu['@Name'], i, a))

        c_file.write('};\n')
        a += 1

    c_file.write(
        '\n'
        '/****************************************************************************/\n'
        '/***        Exported Variables                                            ***/\n'
        '/****************************************************************************/\n'
        '\n')
    numAPdus = len(as_list(config_node['PDUConfiguration']['APDUs']))
    c_file.write('extern pdum_tsAPdu s_asAPduPool[%d];\n' % numAPdus)
    c_file.write(
        '\n'
        '/****************************************************************************/\n'
        '/***        Exported Functions                                            ***/\n'
        '/****************************************************************************/\n'
        '\n'
        'extern void pdum_vNPduInit(pdum_tsNPdu *psNPduPool, uint16 u16Size);\n'
        'extern void pdum_vAPduInit(pdum_tsAPdu *asAPduPool, uint16 u16NumAPdus);\n'
        '\n'
        'PUBLIC void PDUM_vInit(void)\n'
        '{\n')
    c_file.write('    uint32 i;\n')
    c_file.write('    for (i =0; i < %d; i++) { \n' % numAPdus)
    c_file.write('        s_asAPduPool[i].u16FreeListHeadIdx = 0;\n')
    c_file.write('    }\n')
    c_file.write('    pdum_vNPduInit(s_asNPduPool, %d);\n' % npdu_pool_size)
    if '@PDUMMutexName' in pdum_config:
        c_file.write('    pdum_vAPduInit(s_asAPduPool, %d);\n' % numAPdus)
    else:
        c_file.write('    pdum_vAPduInit(s_asAPduPool, %d);\n' % numAPdus)
    c_file.write(
        '}\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        Local Functions                                               ***/\n'
        '/****************************************************************************/\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        END OF FILE                                                   ***/\n'
        '/****************************************************************************/\n')
    c_file.close()
    if os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_READONLY)
    fsp = os.path.join(output_dir, 'pdum_apdu.S')
    if os.path.exists(fsp) and os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_NORMAL)
    c_file = open(fsp, 'w')
    c_file.write('    .global s_asAPduPool\n')
    if s_endian != 'BIG_ENDIAN':
        c_file.write('    .section    .data.s_asAPduPool,"aw",%progbits\n')
    else:
        c_file.write('    .section    .data.s_asAPduPool,"aw",@progbits\n')
    c_file.write('    .align 4\n')
    if s_endian != 'BIG_ENDIAN':
        c_file.write('    .type    s_asAPduPool, %object\n')
    else:
        c_file.write('    .type    s_asAPduPool, @object\n')
    c_file.write('    .size    s_asAPduPool, %d\n' % (numAPdus * 12))
    c_file.write('s_asAPduPool:\n')
    for apdu in as_list(config_node['PDUConfiguration']['APDUs']):
        apdu_size = int(apdu['@Size'])
        apdu_instances = int(apdu['@Instances'])
        c_file.write('    .global pdum_%s\n' % apdu['@Name'])
        c_file.write('pdum_%s:\n' % apdu['@Name'])
        c_file.write('    .long    s_as%sInstances\n' % apdu['@Name'])
        c_file.write('    .short    0\n')
        c_file.write('    .short    %d\n' % apdu_size)
        c_file.write('    .short    %d\n' % apdu_instances)
        c_file.write('    .zero     2\n')

    c_file.close()
    if os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_READONLY)


def output_header(output_dir, pdumConfig):
    """
    :type output_dir: str
    :type pdumConfig: dict
    """
    fsp = os.path.join(output_dir, 'pdum_gen.h')
    if os.path.exists(fsp) and os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_NORMAL)
    h_file = open(fsp, 'w')
    h_file.write(
        '/****************************************************************************\n'
        ' *\n'
        ' *                 THIS IS A GENERATED FILE. DO NOT EDIT!\n'
        ' *\n'
        ' * MODULE:         PDUMCOnfig\n'
        ' *\n'
        ' * COMPONENT:      pdum_gen.h\n'
        ' *\n'
        ' * DATE:           %s\n'
        ' *\n'
        ' * AUTHOR:         NXP PDU Manager Configuration Tool\n'
        ' *\n'
        ' * DESCRIPTION:    PDU definitions\n'
        ' *\n'
        ' *****************************************************************************\n'
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
        ' ****************************************************************************/\n' %
        datetime.datetime.ctime(datetime.datetime.now()))
    h_file.write(
        '\n'
        '#ifndef _PDUM_GEN_H\n'
        '#define _PDUM_GEN_H\n'
        '\n'
        '#include <pdum_apl.h>\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        Macro Definitions                                             ***/\n'
        '/****************************************************************************/\n')
    h_file.write('/* APDUs */\n')
    a = 0
    for apdu in as_list(pdumConfig['APDUs']):
        apdu_size = int(apdu['@Size'])
        h_file.write('#define %s &pdum_%s\n' % (apdu['@Name'], apdu['@Name']))
        a += 1

    h_file.write(
        '\n'
        '/****************************************************************************/\n'
        '/***        Type Definitions                                              ***/\n'
        '/****************************************************************************/\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        External Variables                                            ***/\n'
        '/****************************************************************************/\n'
        '\n')
    h_file.write('/* APDUs */\n')
    a = 0
    for apdu in as_list(pdumConfig['APDUs']):
        apdu_size = int(apdu['@Size'])
        h_file.write('extern const struct pdum_tsAPdu_tag pdum_%s;\n' % apdu['@Name'])
        a += 1

    h_file.write(
        '\n'
        '/****************************************************************************/\n'
        '/***        Exported Functions                                            ***/\n'
        '/****************************************************************************/\n'
        '\n'
        'PUBLIC void PDUM_vInit(void);\n'
        '\n'
        '/****************************************************************************/\n'
        '/****************************************************************************/\n'
        '/****************************************************************************/\n'
        '\n#endif\n')
    h_file.close()
    if os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_READONLY)


exeFSP = os.path.abspath(sys.executable)
if os.name == 'nt':
    d = win32api.GetFileVersionInfo(exeFSP, '\\')
    version = '%d.%d.%d' % (d['FileVersionMS'] / 65536, d['FileVersionMS'] % 65536, d['FileVersionLS'] / 65536)
else:
    version = 'x.x.x'
print('PDUMConfig - PDU Manager Configuration Tool v%s Build %s\n' % (version, '90693'))
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
        '\n\t(c) Copyright Jennic Ltd 2008. All rights reserved.\n')
    print('For help: %s --help' % sys.argv[0])
    sys.exit(0)
if options.config_filename is None:
    print('ERROR: a configuration file must be specified.\n')
    sys.exit(-1)
if not os.path.exists(options.config_filename):
    print("ERROR: unable to open configuration file '%s'.\n" % options.config_filename)
    sys.exit(-1)
if options.output_dir is not None and not os.path.exists(options.output_dir):
    print("ERROR: Output directory '%s' does not exist.\n" % options.output_dir)
    sys.exit(-1)

namespaces = {
    "http://www.nxp.com/zpscfg": None,
    "http://www.w3.org/2001/XMLSchema-instance": None,
}

with open(options.config_filename, 'rb') as f:
    config = xmltodict.parse(f, process_namespaces=True, namespaces=namespaces)
if not options.zigbee_node_name:
    print('ERROR: A node must be specified.\n')
    sys.exit(-1)
else:
    config_node = None
    root = config['ZigbeeWirelessNetwork']
    if 'Coordinator' in root and root['Coordinator']['@Name'] == options.zigbee_node_name:
        config_node = root['Coordinator']
    if config_node is None:
        children = get_child_nodes(root)
        if children:
            for node in children:
                if options.zigbee_node_name == node.get('@Name'):
                    config_node = node
                    break

            if config_node is None:
                print("ERROR: Unable to find node '%s' in input configuration file.\n" % options.zigbee_node_name)
                sys.exit(-1)
        else:
            print("ERROR: Unable to find node '%s' in input configuration file.\n" % options.zigbee_node_name)
            sys.exit(-1)
if validate_configuration(config_node):
    output_header(options.output_dir, config_node['PDUConfiguration'])
    output_c(options.output_dir, config_node['PDUConfiguration'], options.endian)
else:
    sys.exit(1)
print('Done.\n')
