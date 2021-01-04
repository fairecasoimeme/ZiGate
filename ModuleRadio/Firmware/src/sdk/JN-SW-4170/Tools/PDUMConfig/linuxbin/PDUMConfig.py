#!/usr/bin/python2

import datetime
import os
import re
import sys
from optparse import OptionParser

from amara import bindery

if os.name == 'nt':
    import win32api
    import win32con


parser = OptionParser()
parser.add_option('-z', '--zigbee', dest='zigbeeNodeName', default='', help='Output configuration for Zigbee Protocol Stack for the specified node.')
parser.add_option('-o', '--output', dest='outputDir', default=os.path.curdir, help='Path to output the configuration into.')
parser.add_option('-f', '--config-file', dest='configFilename', help='Configuration file')
parser.add_option('-e', '--endian', dest='endian', type='string', default='BIG_ENDIAN', help='Endian of the processor BIG_ENDIAN or LITTLE_ENDIAN')
(options, args) = parser.parse_args(sys.argv[1:])


def checkForDuplicateNames(nodes, n1):
    if not hasattr(n1, 'Name'):
        return False
    for n2 in nodes:
        if n2 != n1 and hasattr(n2, 'Name') and n1.Name == n2.Name:
            return True

    return False


def validateConfiguration(configNode):
    nodeName = configNode.Name
    nameCheck = re.compile('[a-zA-Z_][a-zA-Z_0-9]*')
    if hasattr(configNode, 'PDUConfiguration'):
        if not hasattr(configNode.PDUConfiguration, 'NumNPDUs'):
            print("ERROR: The PDU Manager for node '%s' must have a NumNPDUs attribute.\n" % nodeName)
            return False
        elif int(configNode.PDUConfiguration.NumNPDUs, 0) < 8:
            print("ERROR: The PDU Manager for node '%s' must have at least 8 NPDUs configured" % nodeName)
            return False
        if not hasattr(configNode.PDUConfiguration, 'APDUs'):
            print("ERROR: The PDU Manager for node '%s' does not have any APDUs.\n" % nodeName)
            return False
        else:
            for apdu in configNode.PDUConfiguration.APDUs:
                if not hasattr(apdu, 'Name'):
                    print("ERROR: An APDU for node '%s' does not have a Name specified.\n" % nodeName)
                    return False
                else:
                    result = nameCheck.match(apdu.Name)
                    if result.group(0) != apdu.Name:
                        print("ERROR: The APDU '%s' for node '%s' is not a valid C identifier.\n" % (apdu.Name, nodeName))
                        return False
                if not hasattr(apdu, 'Id'):
                    print("ERROR: The APDU '%s' for node '%s' does not have an Id specified.\n" % (apdu.Name, nodeName))
                    return False
                if not hasattr(apdu, 'Size'):
                    print("ERROR: The APDU '%s' for node '%s' does not have a Size specified.\n" % (apdu.Name, nodeName))
                    return False
                elif int(apdu.Size, 0) < 1:
                    print("ERROR: The APDU '%s' for node '%s' must have a Size of at least 1.\n" % (apdu.Name, nodeName))
                    return False
                if not hasattr(apdu, 'Instances'):
                    print("ERROR: The APDU '%s' for node '%s' does not have a number of Instances specified.\n" % (apdu.Name, nodeName))
                    return False
                elif int(apdu.Instances, 0) < 1:
                    print("ERROR: The APDU '%s' for node '%s' must have a number of Instances of at least 1.\n" % (apdu.Name, nodeName))
                    return False
                if checkForDuplicateNames(configNode.PDUConfiguration.APDUs, apdu):
                    print("ERROR: There are one or more APDUs with the name '%s' for node '%s'. APDUs must have unique names.\n" % (apdu.Name, nodeName))
                    return False

    else:
        print("ERROR: The node '%s' must have a PDU Manager element.\n" % nodeName)
        return False
    return True


def outputC(dir, pdumConfig, sEndian):
    fsp = os.path.join(dir, 'pdum_gen.c')
    if os.path.exists(fsp) and os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_NORMAL)
    Cfile = open(fsp, 'w')
    Cfile.write(
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
    Cfile.write(
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
    Cfile.write('\n/* NPDU Pool */\n')
    npduPoolSize = int(pdumConfig.NumNPDUs)
    Cfile.write('PRIVATE pdum_tsNPdu s_asNPduPool[%d];\n' % npduPoolSize)
    Cfile.write('\n/* APDU Pool */\n')
    a = 0
    for apdu in pdumConfig.APDUs:
        apduSize = int(apdu.Size)
        apduInstances = int(apdu.Instances)
        for i in range(0, apduInstances):
            storageName = 's_au8%sInstance%dStorage' % (apdu.Name, i)
            Cfile.write('PRIVATE uint8 %s[%d];\n'
        '' % (storageName, apduSize))

        Cfile.write('PUBLIC pdum_tsAPduInstance s_as%sInstances[%d] = {\n' % (apdu.Name, apduInstances))
        for i in range(0, apduInstances):
            Cfile.write('    { s_au8%sInstance%dStorage, 0, 0, %d },\n' % (apdu.Name, i, a))

        Cfile.write('};\n')
        a += 1

    Cfile.write(
        '\n'
        '/****************************************************************************/\n'
        '/***        Exported Variables                                            ***/\n'
        '/****************************************************************************/\n'
        '\n')
    numAPdus = len(list(pdumConfig.APDUs))
    Cfile.write('extern pdum_tsAPdu s_asAPduPool[%d];\n' % numAPdus)
    Cfile.write(
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
    Cfile.write('    uint32 i;\n')
    Cfile.write('    for (i =0; i < %d; i++) { \n' % numAPdus)
    Cfile.write('        s_asAPduPool[i].u16FreeListHeadIdx = 0;\n')
    Cfile.write('    }\n')
    Cfile.write('    pdum_vNPduInit(s_asNPduPool, %d);\n' % npduPoolSize)
    if hasattr(pdumConfig, 'PDUMMutexName'):
        Cfile.write('    pdum_vAPduInit(s_asAPduPool, %d);\n' % numAPdus)
    else:
        Cfile.write('    pdum_vAPduInit(s_asAPduPool, %d);\n' % numAPdus)
    Cfile.write(
        '}\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        Local Functions                                               ***/\n'
        '/****************************************************************************/\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        END OF FILE                                                   ***/\n'
        '/****************************************************************************/\n')
    Cfile.close()
    if os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_READONLY)
    fsp = os.path.join(dir, 'pdum_apdu.S')
    if os.path.exists(fsp) and os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_NORMAL)
    Cfile = open(fsp, 'w')
    numAPdus = len(list(pdumConfig.APDUs))
    Cfile.write('    .global s_asAPduPool\n')
    if sEndian != 'BIG_ENDIAN':
        Cfile.write('    .section    .data.s_asAPduPool,"aw",%progbits\n')
    else:
        Cfile.write('    .section    .data.s_asAPduPool,"aw",@progbits\n')
    Cfile.write('    .align 4\n')
    if sEndian != 'BIG_ENDIAN':
        Cfile.write('    .type    s_asAPduPool, %object\n')
    else:
        Cfile.write('    .type    s_asAPduPool, @object\n')
    Cfile.write('    .size    s_asAPduPool, %d\n' % (numAPdus * 12))
    Cfile.write('s_asAPduPool:\n')
    for apdu in pdumConfig.APDUs:
        apduSize = int(apdu.Size)
        apduInstances = int(apdu.Instances)
        Cfile.write('    .global pdum_%s\n' % apdu.Name)
        Cfile.write('pdum_%s:\n' % apdu.Name)
        Cfile.write('    .long    s_as%sInstances\n' % apdu.Name)
        Cfile.write('    .short    0\n')
        Cfile.write('    .short    %d\n' % apduSize)
        Cfile.write('    .short    %d\n' % apduInstances)
        Cfile.write('    .zero     2\n')

    Cfile.close()
    if os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_READONLY)


def outputHeader(dir, pdumConfig):
    fsp = os.path.join(dir, 'pdum_gen.h')
    if os.path.exists(fsp) and os.name == 'nt':
        win32api.SetFileAttributes(fsp, win32con.FILE_ATTRIBUTE_NORMAL)
    Hfile = open(fsp, 'w')
    Hfile.write(
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
    Hfile.write(
        '\n'
        '#ifndef _PDUM_GEN_H\n'
        '#define _PDUM_GEN_H\n'
        '\n'
        '#include <pdum_apl.h>\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        Macro Definitions                                             ***/\n'
        '/****************************************************************************/\n')
    Hfile.write('/* APDUs */\n')
    a = 0
    for apdu in pdumConfig.APDUs:
        aPduSize = int(apdu.Size)
        Hfile.write('#define %s &pdum_%s\n' % (apdu.Name, apdu.Name))
        a += 1

    Hfile.write(
        '\n'
        '/****************************************************************************/\n'
        '/***        Type Definitions                                              ***/\n'
        '/****************************************************************************/\n'
        '\n'
        '/****************************************************************************/\n'
        '/***        External Variables                                            ***/\n'
        '/****************************************************************************/\n'
        '\n')
    Hfile.write('/* APDUs */\n')
    a = 0
    for apdu in pdumConfig.APDUs:
        aPduSize = int(apdu.Size)
        Hfile.write('extern const struct pdum_tsAPdu_tag pdum_%s;\n' % apdu.Name)
        a += 1

    Hfile.write(
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
    Hfile.close()
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
if None == options.configFilename:
    print('ERROR: a configuration file must be specified.\n')
    sys.exit(-1)
if not os.path.exists(options.configFilename):
    print("ERROR: unable to open configuration file '%s'.\n" % options.configFilename)
    sys.exit(-1)
if None != options.outputDir and not os.path.exists(options.outputDir):
    print("ERROR: Output directory '%s' does not exist.\n" % options.outputDir)
    sys.exit(-1)
config = bindery.parse(options.configFilename, validate=False)
if '' == options.zigbeeNodeName:
    print('ERROR: A node must be specified.\n')
    sys.exit(-1)
else:
    configNode = None
    if hasattr(config.ZigbeeWirelessNetwork, 'Coordinator'):
        if options.zigbeeNodeName == config.ZigbeeWirelessNetwork.Coordinator.Name:
            configNode = config.ZigbeeWirelessNetwork.Coordinator
    if None == configNode:
        if hasattr(config.ZigbeeWirelessNetwork, 'ChildNodes'):
            for node in config.ZigbeeWirelessNetwork.ChildNodes:
                if options.zigbeeNodeName == node.Name:
                    configNode = node
                    break

            if None == configNode:
                print("ERROR: Unable to find node '%s' in input configuration file.\n" % options.zigbeeNodeName)
                sys.exit(-1)
        else:
            print("ERROR: Unable to find node '%s' in input configuration file.\n" % options.zigbeeNodeName)
            sys.exit(-1)
if validateConfiguration(configNode):
    outputHeader(options.outputDir, configNode.PDUConfiguration)
    outputC(options.outputDir, configNode.PDUConfiguration, options.endian)
else:
    sys.exit(1)
print('Done.\n')
