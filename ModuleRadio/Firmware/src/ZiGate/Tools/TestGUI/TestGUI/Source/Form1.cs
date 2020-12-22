using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Diagnostics;
using System.Globalization;
using PortSet;
using ListManagement;
using System.IO;
using System.Collections;

namespace ZGWUI
{
    public partial class Form1 : Form
    {
		NetworkRecovery nwkRecovery = new NetworkRecovery();
        ListManager listManager;

        UInt64[] au64ExtAddr = new UInt64[16];

        byte[] au8OTAFile = new byte[524288]; // 512k max file size
        byte u8OtaInProgress = 0;
        byte u8OTAWaitForDataParamsPending = 0;
        UInt16 u16OTAWaitForDataParamsTargetAddr;
        byte u8OTAWaitForDataParamsSrcEndPoint;
        UInt32 u32OTAWaitForDataParamsCurrentTime;
        UInt32 u32OTAWaitForDataParamsRequestTime;
        UInt16 u16OTAWaitForDataParamsBlockDelay;
        UInt32 u32OtaFileIdentifier;
        UInt16 u16OtaFileHeaderVersion;
        UInt16 u16OtaFileHeaderLength;
        UInt16 u16OtaFileHeaderControlField;
        UInt16 u16OtaFileManufacturerCode;
        UInt16 u16OtaFileImageType;
        UInt32 u32OtaFileVersion;
        UInt16 u16OtaFileStackVersion;
        UInt32 u32OtaFileTotalImage;
        byte u8OtaFileSecurityCredVersion;
        UInt64 u64OtaFileUpgradeFileDest;
        UInt16 u16OtaFileMinimumHwVersion;
        UInt16 u16OtaFileMaxHwVersion;

        //UInt16 u16PollControlFastPollExpiry;
        //byte bPollControlStartFastPolling;

        //UInt32 u32CurrentOffset = 0;

        public Form1()
        {
            InitializeComponent();
            GUIinitialize();

            listManager = new ListManager();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            AutoScroll = true;
        }

        #region GUI initialization functions

        private void GUIinitialize()
        {
            comboBoxSetKeyState.Items.Add("NO NETWORK KEY");
            comboBoxSetKeyState.Items.Add("PRECONFIGURED NETWORK KEY");
            comboBoxSetKeyState.Items.Add("DEFAULT NETWORK KEY");
            comboBoxSetKeyState.Items.Add("PRECONFIGURED LINK KEY");
            comboBoxSetKeyState.Items.Add("ZLL LINK KEY");
            comboBoxSetKeyState.SelectedIndex = 3;

            comboBoxSetKeyType.Items.Add("UNIQUE LINK KEY");
            comboBoxSetKeyType.Items.Add("GLOBAL LINK KEY");
            comboBoxSetKeyType.SelectedIndex = 1;

            comboBoxSetType.Items.Add("COORDINATOR");
            comboBoxSetType.Items.Add("ROUTER");
            comboBoxSetType.Items.Add("END DEVICE");
            comboBoxSetType.SelectedIndex = 0;

            comboBoxPermitJoinTCsignificance.Items.Add("NO CHANGE");
            comboBoxPermitJoinTCsignificance.Items.Add("POLICY AS SPEC");
            comboBoxPermitJoinTCsignificance.SelectedIndex = 0;

            comboBoxSecurityKey.Items.Add("5A6967426565416C6C69616E63653039");
            comboBoxSecurityKey.Items.Add("D0D1D2D3D4D5D6D7D8D9DADBDCDDDEDF");
            comboBoxSecurityKey.SelectedIndex = 0;

            textBoxSetEPID.ForeColor = System.Drawing.Color.Gray;
            textBoxSetEPID.Text = "Extended PAN ID (64-bit Hex)";

            textBoxSetCMSK.ForeColor = System.Drawing.Color.Gray;
            textBoxSetCMSK.Text = "Single Channel or Mask (32-bit Hex)";

            textBoxPermitJoinInterval.ForeColor = System.Drawing.Color.Gray;
            textBoxPermitJoinInterval.Text = "Interval (8-bit Hex)";

            textBoxSetSecurityKeySeqNbr.ForeColor = System.Drawing.Color.Gray;
            textBoxSetSecurityKeySeqNbr.Text = "SQN";

            textBoxMatchReqNbrInputClusters.ForeColor = System.Drawing.Color.Gray;
            textBoxMatchReqNbrInputClusters.Text = "Inputs (8-bit Hex)";

            textBoxMatchReqNbrOutputClusters.ForeColor = System.Drawing.Color.Gray;
            textBoxMatchReqNbrOutputClusters.Text = "Outputs (8-bit Hex)";

            textBoxMatchReqInputClusters.ForeColor = System.Drawing.Color.Gray;
            textBoxMatchReqInputClusters.Text = "Clusters (16-bit Hex)";

            textBoxMatchReqOutputClusters.ForeColor = System.Drawing.Color.Gray;
            textBoxMatchReqOutputClusters.Text = "Clusters (16-bit Hex)";

            textBoxUserSetReqDescription.ForeColor = System.Drawing.Color.Gray;
            textBoxUserSetReqDescription.Text = "User Description (String)";

            addrModeComboBoxInit(ref comboBoxBindAddrMode);
            destShortIeeeAddrTextBoxInit(ref textBoxBindDestAddr);
            dstEndPointTextBoxInit(ref textBoxBindDestEP);

            addrModeComboBoxInit(ref comboBoxUnBindAddrMode);
            destShortIeeeAddrTextBoxInit(ref textBoxUnBindDestAddr);
            dstEndPointTextBoxInit(ref textBoxUnBindDestEP);            

            // Management tab text box initialization
            targetExtendedAddrTextBoxInit(ref textBoxBindTargetExtAddr);
            targetEndPointTextBoxInit(ref textBoxBindTargetEP);
            clusterIdTextBoxInit(ref textBoxBindClusterID);

            targetExtendedAddrTextBoxInit(ref textBoxUnBindTargetExtAddr);
            targetEndPointTextBoxInit(ref textBoxUnBindTargetEP);
            clusterIdTextBoxInit(ref textBoxUnBindClusterID);

            shortAddrTextBoxInit(ref textBoxPermitJoinAddr);
            shortAddrTextBoxInit(ref textBoxNodeDescReq);            
            shortAddrTextBoxInit(ref textBoxSimpleReqAddr);            
            shortAddrTextBoxInit(ref textBoxPowerReqAddr);
            shortAddrTextBoxInit(ref textBoxActiveEpAddr);
            shortAddrTextBoxInit(ref textBoxMatchReqAddr);
            shortAddrTextBoxInit(ref textBoxComplexReqAddr);
            shortAddrTextBoxInit(ref textBoxUserReqAddr);
            shortAddrTextBoxInit(ref textBoxUserSetReqAddr);
            shortAddrTextBoxInit(ref textBoxLqiReqTargetAddr);
            profileIdTextBoxInit(ref textBoxMatchReqProfileID);            
            dstEndPointTextBoxInit(ref textBoxSimpleReqEndPoint);   
            targetShortAddrTextBoxInit(ref textBoxIeeeReqTargetAddr);
            shortAddrTextBoxInit(ref textBoxIeeeReqAddr);
            startIndexTextBoxInit(ref textBoxIeeeReqStartIndex);
            startIndexTextBoxInit(ref textBoxLqiReqStartIndex);
            comboBoxIeeeReqType.Items.Add("SINGLE");
            comboBoxIeeeReqType.Items.Add("EXTENDED");
            comboBoxIeeeReqType.SelectedIndex = 0;
            targetShortAddrTextBoxInit(ref textBoxNwkAddrReqTargetAddr);
            extendedAddrTextBoxInit(ref textBoxNwkAddrReqExtAddr);
            startIndexTextBoxInit(ref textBoxNwkAddrReqStartIndex);
            comboBoxNwkAddrReqType.Items.Add("SINGLE");
            comboBoxNwkAddrReqType.Items.Add("EXTENDED");
            comboBoxNwkAddrReqType.SelectedIndex = 0;

            // Restore Network Recovery
            textBoxRestoreNwkFrameCounter.ForeColor = System.Drawing.Color.Gray;
            textBoxRestoreNwkFrameCounter.Text = "Out Frame Counter (32-bit Hex)";

            // Remove Device Request UI
            extendedAddrTextBoxInit(ref textBoxRemoveParentAddr);
            extendedAddrTextBoxInit(ref textBoxRemoveChildAddr);

            // Management Leave Request UI
            extendedAddrTextBoxInit(ref textBoxMgmtLeaveExtAddr);
            targetShortAddrTextBoxInit(ref textBoxMgmtLeaveAddr);
            comboBoxMgmtLeaveReJoin.Items.Add("DO NOT REJOIN");
            comboBoxMgmtLeaveReJoin.Items.Add("REJOIN");
            comboBoxMgmtLeaveReJoin.SelectedIndex = 1;
            comboBoxMgmtLeaveChildren.Items.Add("DO NOT REMOVE CHILDREN");
            comboBoxMgmtLeaveChildren.Items.Add("REMOVE CHILDREN");
            comboBoxMgmtLeaveChildren.SelectedIndex = 1;

            // Leave Request UI
            extendedAddrTextBoxInit(ref textBoxLeaveAddr);
            comboBoxLeaveReJoin.Items.Add("DO NOT REJOIN");
            comboBoxLeaveReJoin.Items.Add("REJOIN");
            comboBoxLeaveReJoin.SelectedIndex = 1;
            comboBoxLeaveChildren.Items.Add("DO NOT REMOVE CHILDREN");
            comboBoxLeaveChildren.Items.Add("REMOVE CHILDREN");
            comboBoxLeaveChildren.SelectedIndex = 1;

            // NCI UI
            comboBoxNciCmd.Items.Add("COMMISSION");
            comboBoxNciCmd.Items.Add("DECOMMISSION");
            comboBoxNciCmd.Items.Add("DISABLE"); 
            comboBoxNciCmd.SelectedIndex = 0;

            // General tab initialization
            addrModeComboBoxInit(ref comboBoxMgmtNwkUpdateAddrMode);
            targetShortAddrTextBoxInit(ref textBoxMgmtNwkUpdateTargetAddr);
            textBoxMgmtNwkUpdateChannelMask.ForeColor = System.Drawing.Color.Gray;
            textBoxMgmtNwkUpdateChannelMask.Text = "ChanMask (32-bit Hex)";
            scanDurationTextBoxInit(ref textBoxMgmtNwkUpdateScanDuration);
            textBoxMgmtNwkUpdateScanCount.ForeColor = System.Drawing.Color.Gray;
            textBoxMgmtNwkUpdateScanCount.Text = "Count (8-bit Hex)";

            textBoxMgmtNwkUpdateNwkManagerAddr.ForeColor = System.Drawing.Color.Gray;
            textBoxMgmtNwkUpdateNwkManagerAddr.Text = "NwkMan Addr (16-bit Hex)";
           
            targetShortAddrTextBoxInit(ref textBoxReadAttribTargetAddr);
            srcEndPointTextBoxInit(ref textBoxReadAttribSrcEP);
            dstEndPointTextBoxInit(ref textBoxReadAttribDstEP);
            clusterIdTextBoxInit(ref textBoxReadAttribClusterID);            
            comboBoxReadAttribDirection.Items.Add("TO SERVER");
            comboBoxReadAttribDirection.Items.Add("TO CLIENT");
            comboBoxReadAttribDirection.SelectedIndex = 0;
            attributeIdTextBoxInit(ref textBoxReadAttribID1);            
            attributeCountTextBoxInit(ref textBoxReadAttribCount);
            manufacturerSpecificComboBoxInit(ref comboBoxReadAttribManuSpecific);
            manufacturerIdTextBoxInit(ref textBoxReadAttribManuID);

            targetShortAddrTextBoxInit(ref textBoxWriteAttribTargetAddr);
            srcEndPointTextBoxInit(ref textBoxWriteAttribSrcEP);
            dstEndPointTextBoxInit(ref textBoxWriteAttribDstEP);
            clusterIdTextBoxInit(ref textBoxWriteAttribClusterID);
            comboBoxWriteAttribDirection.Items.Add("TO SERVER");
            comboBoxWriteAttribDirection.Items.Add("TO CLIENT");
            comboBoxWriteAttribDirection.SelectedIndex = 0;
            attributeIdTextBoxInit(ref textBoxWriteAttribID);
            attributeDataTypeTextBoxInit(ref textBoxWriteAttribDataType);
            attribDataTextBoxInit(ref textBoxWriteAttribData);
            manufacturerSpecificComboBoxInit(ref comboBoxWriteAttribManuSpecific);
            manufacturerIdTextBoxInit(ref textBoxWriteAttribManuID);
            
            targetShortAddrTextBoxInit(ref textBoxConfigReportTargetAddr);
            addrModeComboBoxZCLInit(ref comboBoxConfigReportAddrMode);
            srcEndPointTextBoxInit(ref textBoxConfigReportSrcEP);
            dstEndPointTextBoxInit(ref textBoxConfigReportDstEP);
            clusterIdTextBoxInit(ref textBoxConfigReportClusterID);
            comboBoxConfigReportDirection.Items.Add("TO SERVER");
            comboBoxConfigReportDirection.Items.Add("TO CLIENT");
            comboBoxConfigReportDirection.SelectedIndex = 0;            
            comboBoxConfigReportAttribDirection.Items.Add("TX SERVER");
            comboBoxConfigReportAttribDirection.Items.Add("Rx CLIENT");
            comboBoxConfigReportAttribDirection.SelectedIndex = 0;                      
            attributeTypeTextBoxInit(ref textBoxConfigReportAttribType);
            attributeIdTextBoxInit(ref textBoxConfigReportAttribID);
            minIntervalTextBoxInit(ref textBoxConfigReportMinInterval);
            maxIntervalTextBoxInit(ref textBoxConfigReportMaxInterval);
            timeOutPeriodTextBoxInit(ref textBoxConfigReportTimeOut);
            reportChangeTextBoxInit(ref textBoxConfigReportChange);

            targetShortAddrTextBoxInit(ref textBoxReadAllAttribAddr);
            srcEndPointTextBoxInit(ref textBoxReadAllAttribSrcEP);
            dstEndPointTextBoxInit(ref textBoxReadAllAttribDstEP);
            clusterIdTextBoxInit(ref textBoxReadAllAttribClusterID);
            comboBoxReadAllAttribDirection.Items.Add("TO SERVER");
            comboBoxReadAllAttribDirection.Items.Add("TO CLIENT");
            comboBoxReadAllAttribDirection.SelectedIndex = 0;

            targetShortAddrTextBoxInit(ref textBoxDiscoverAttributesAddr);
            srcEndPointTextBoxInit(ref textBoxDiscoverAttributesSrcEp);
            dstEndPointTextBoxInit(ref textBoxDiscoverAttributesDstEp);
            clusterIdTextBoxInit(ref textBoxDiscoverAttributesClusterID);
            attributeIdTextBoxInit(ref textBoxDiscoverAttributesStartAttrId);
            

            comboBoxDiscoverAttributesDirection.Items.Add("TO SERVER");
            comboBoxDiscoverAttributesDirection.Items.Add("TO CLIENT");
            comboBoxDiscoverAttributesDirection.SelectedIndex = 0;
            maxIDsTextBoxInit(ref textBoxDiscoverAttributesMaxIDs);
            comboBoxDiscoverAttributesExtended.Items.Add("STANDARD");
            comboBoxDiscoverAttributesExtended.Items.Add("EXTENDED");
            comboBoxDiscoverAttributesExtended.SelectedIndex = 0;

            addrModeComboBoxZCLInit(ref comboBoxDiscoverCommandsAddrMode);
            targetShortAddrTextBoxInit(ref textBoxDiscoverCommandsTargetAddr);
            srcEndPointTextBoxInit(ref textBoxDiscoverCommandsSrcEP);
            dstEndPointTextBoxInit(ref textBoxDiscoverCommandsDstEP);
            clusterIdTextBoxInit(ref textBoxDiscoverCommandsClusterID);

            addrModeComboBoxZCLInit(ref comboBoxRawDataCommandsAddrMode);
            targetShortAddrTextBoxInit(ref textBoxRawDataCommandsTargetAddr);
            srcEndPointTextBoxInit(ref textBoxRawDataCommandsSrcEP);
            dstEndPointTextBoxInit(ref textBoxRawDataCommandsDstEP);
            profileIdTextBoxInit(ref textBoxRawDataCommandsProfileID);
            clusterIdTextBoxInit(ref textBoxRawDataCommandsClusterID);

            textBoxRawDataCommandsSecurityMode.ForeColor = System.Drawing.Color.Gray;
            textBoxRawDataCommandsSecurityMode.Text = "Security Mode (8-bit Hex)";

            textBoxRawDataCommandsRadius.ForeColor = System.Drawing.Color.Gray;
            textBoxRawDataCommandsRadius.Text = "Radius (8-bit Hex)";

            textBoxRawDataCommandsData.ForeColor = System.Drawing.Color.Gray;
            textBoxRawDataCommandsData.Text = "Raw Data (Format: Byte:Byte:Byte)";
            textBoxRawDataCommandsData.TextChanged += new EventHandler(textBoxRawDataCommandsData_TextChanged);

            comboBoxDiscoverCommandsDirection.Items.Add("TO SERVER");
            comboBoxDiscoverCommandsDirection.Items.Add("TO CLIENT");
            comboBoxDiscoverCommandsDirection.SelectedIndex = 0;                                                
            commandIDTextBoxInit(ref textBoxDiscoverCommandsCommandID);
            manufacturerSpecificComboBoxInit(ref comboBoxDiscoverCommandsManuSpecific);
            manufacturerIdTextBoxInit(ref textBoxDiscoverCommandsManuID);
            maxCommandsTextBoxInit(ref textBoxDiscoverCommandsMaxCommands);            
            comboBoxDiscoverCommandsRxGen.Items.Add("RECEIVED");
            comboBoxDiscoverCommandsRxGen.Items.Add("GENERATED");
            comboBoxDiscoverCommandsRxGen.SelectedIndex = 0;

            addrModeComboBoxZCLInit(ref comboBoxReadReportConfigAddrMode);
            targetShortAddrTextBoxInit(ref textBoxReadReportConfigTargetAddr);
            srcEndPointTextBoxInit(ref textBoxReadReportConfigSrcEP);
            dstEndPointTextBoxInit(ref textBoxReadReportConfigDstEP);
            clusterIdTextBoxInit(ref textBoxReadReportConfigClusterID);
            comboBoxReadReportConfigDirection.Items.Add("TO SERVER");
            comboBoxReadReportConfigDirection.Items.Add("TO CLIENT");
            comboBoxReadReportConfigDirection.SelectedIndex = 0;           
            attributeIdTextBoxInit(ref textBoxReadReportConfigAttribID);
            comboBoxReadReportConfigDirIsRx.Items.Add("DIR TX");
            comboBoxReadReportConfigDirIsRx.Items.Add("DIR RX");
            comboBoxReadReportConfigDirIsRx.SelectedIndex = 1;

            comboBoxManyToOneRouteRequestCacheRoute.Items.Add("NO CACHE");
            comboBoxManyToOneRouteRequestCacheRoute.Items.Add("CACHE");
            comboBoxManyToOneRouteRequestCacheRoute.SelectedIndex = 1;
            radiusTextBoxInit(ref textBoxManyToOneRouteRequesRadius);

            OOBAddrTextBoxInit(ref textBoxOOBDataAddr);
            OOBKeyTextBoxInit(ref textBoxOOBDataKey);

            // Basic cluster tab initialization
            addrModeComboBoxZCLInit(ref comboBoxBasicResetTargetAddrMode);
            shortAddrTextBoxInit(ref textBoxBasicResetTargetAddr);
            srcEndPointTextBoxInit(ref textBoxBasicResetSrcEP);
            dstEndPointTextBoxInit(ref textBoxBasicResetDstEP);

            // Scenes cluster tab initialization
            addrModeComboBoxZCLInit(ref comboBoxViewSceneAddrMode);
            shortAddrTextBoxInit(ref textBoxViewSceneAddr);
            srcEndPointTextBoxInit(ref textBoxViewSceneSrcEndPoint);
            dstEndPointTextBoxInit(ref textBoxViewSceneDstEndPoint);
            groupIdTextBoxInit(ref textBoxViewSceneGroupId);
            sceneIdTextBoxInit(ref textBoxViewSceneSceneId);

            addrModeComboBoxZCLInit(ref comboBoxAddSceneAddrMode);
            shortAddrTextBoxInit(ref textBoxAddSceneAddr);
            srcEndPointTextBoxInit(ref textBoxAddSceneSrcEndPoint);
            dstEndPointTextBoxInit(ref textBoxAddSceneDstEndPoint);
            groupIdTextBoxInit(ref textBoxAddSceneGroupId);
            sceneIdTextBoxInit(ref textBoxAddSceneSceneId);
            time16bitTextBoxInit(ref textBoxAddSceneTransTime);
            nameStringTextBoxInit(ref textBoxAddSceneName);
            stringLenTextBoxInit(ref textBoxAddSceneNameLen);
            stringMaxLenTextBoxInit(ref textBoxAddSceneMaxNameLen);
            extLenTextBoxInit(ref textBoxAddSceneExtLen);
            sceneDataTextBoxInit(ref textBoxAddSceneData);

            addrModeComboBoxZCLInit(ref comboBoxStoreSceneAddrMode);
            shortAddrTextBoxInit(ref textBoxStoreSceneAddr);
            srcEndPointTextBoxInit(ref textBoxStoreSceneSrcEndPoint);
            dstEndPointTextBoxInit(ref textBoxStoreSceneDstEndPoint);
            groupIdTextBoxInit(ref textBoxStoreSceneGroupId);
            sceneIdTextBoxInit(ref textBoxStoreSceneSceneId);

            addrModeComboBoxZCLInit(ref comboBoxRecallSceneAddrMode);
            shortAddrTextBoxInit(ref textBoxRecallSceneAddr);
            srcEndPointTextBoxInit(ref textBoxRecallSceneSrcEndPoint);
            dstEndPointTextBoxInit(ref textBoxRecallSceneDstEndPoint);
            groupIdTextBoxInit(ref textBoxRecallSceneGroupId);
            sceneIdTextBoxInit(ref textBoxRecallSceneSceneId);

            addrModeComboBoxZCLInit(ref comboBoxGetSceneMembershipAddrMode);
            shortAddrTextBoxInit(ref textBoxGetSceneMembershipAddr);
            srcEndPointTextBoxInit(ref textBoxGetSceneMembershipSrcEndPoint);
            dstEndPointTextBoxInit(ref textBoxGetSceneMembershipDstEndPoint);
            groupIdTextBoxInit(ref textBoxGetSceneMembershipGroupID);

            addrModeComboBoxZCLInit(ref comboBoxRemoveAllScenesAddrMode);
            shortAddrTextBoxInit(ref textBoxRemoveAllScenesAddr);
            srcEndPointTextBoxInit(ref textBoxRemoveAllScenesSrcEndPoint);
            dstEndPointTextBoxInit(ref textBoxRemoveAllScenesDstEndPoint);
            groupIdTextBoxInit(ref textBoxRemoveAllScenesGroupID);

            addrModeComboBoxZCLInit(ref comboBoxRemoveSceneAddrMode);
            shortAddrTextBoxInit(ref textBoxRemoveSceneAddr);
            srcEndPointTextBoxInit(ref textBoxRemoveSceneSrcEndPoint);
            dstEndPointTextBoxInit(ref textBoxRemoveSceneDstEndPoint);
            groupIdTextBoxInit(ref textBoxRemoveSceneGroupID);
            sceneIdTextBoxInit(ref textBoxRemoveSceneSceneID);

            // Group cluster tab initialization
            shortAddrTextBoxInit(ref textBoxAddGroupAddr);
            dstEndPointTextBoxInit(ref textBoxAddGroupDstEp);
            srcEndPointTextBoxInit(ref textBoxAddGroupSrcEp);
            groupIdTextBoxInit(ref textBoxAddGroupGroupAddr);
            groupNameLengthTextBoxInit(ref textBoxGroupNameLength);
            groupNameMaxLengthTextBoxInit(ref textBoxGroupNameMaxLength);
            groupNameTextBoxInit(ref textBoxGroupName);
            shortAddrTextBoxInit(ref textBoxViewGroupAddr);
            dstEndPointTextBoxInit(ref textBoxViewGroupDstEp);
            srcEndPointTextBoxInit(ref textBoxViewGroupSrcEp);
            groupIdTextBoxInit(ref textBoxViewGroupGroupAddr);
            shortAddrTextBoxInit(ref textBoxGetGroupTargetAddr);
            dstEndPointTextBoxInit(ref textBoxGetGroupDstEp);
            srcEndPointTextBoxInit(ref textBoxGetGroupSrcEp);
            groupCountTextBoxInit(ref textBoxGetGroupCount);
            shortAddrTextBoxInit(ref textBoxRemoveGroupTargetAddr);
            srcEndPointTextBoxInit(ref textBoxRemoveGroupSrcEp);
            dstEndPointTextBoxInit(ref textBoxRemoveGroupDstEp);
            groupIdTextBoxInit(ref textBoxRemoveGroupGroupAddr);
            shortAddrTextBoxInit(ref textBoxRemoveAllGroupTargetAddr);
            srcEndPointTextBoxInit(ref textBoxRemoveAllGroupSrcEp);
            dstEndPointTextBoxInit(ref textBoxRemoveAllGroupDstEp);

            shortAddrTextBoxInit(ref textBoxGroupAddIfIndentifyingTargetAddr);
            dstEndPointTextBoxInit(ref textBoxGroupAddIfIdentifyDstEp);
            srcEndPointTextBoxInit(ref textBoxGroupAddIfIdentifySrcEp);
            groupIdTextBoxInit(ref textBoxGroupAddIfIdentifyGroupID);

            // On/off cluster tab initialization
            addrModeComboBoxZCLInit(ref comboBoxOnOffAddrMode);
            shortAddrTextBoxInit(ref textBoxOnOffAddr);
            dstEndPointTextBoxInit(ref textBoxOnOffDstEndPoint);
            srcEndPointTextBoxInit(ref textBoxOnOffSrcEndPoint);
            comboBoxOnOffCommand.Items.Add("Off");
            comboBoxOnOffCommand.Items.Add("On");
            comboBoxOnOffCommand.Items.Add("Toggle");
            comboBoxOnOffCommand.SelectedIndex = 0;

            // Level cluster tab initialization
            addrModeComboBoxZCLInit(ref comboBoxMoveToLevelAddrMode);
            shortAddrTextBoxInit(ref textBoxMoveToLevelAddr);
            srcEndPointTextBoxInit(ref textBoxMoveToLevelSrcEndPoint);
            dstEndPointTextBoxInit(ref textBoxMoveToLevelDstEndPoint);
            withOnOffComboBoxInit(ref comboBoxMoveToLevelOnOff);
            levelTextBoxInit(ref textBoxMoveToLevelLevel);
            time16bitTextBoxInit(ref textBoxMoveToLevelTransTime);

            // Identify cluster initialization
            shortAddrTextBoxInit(ref textBoxSendIdAddr);
            shortAddrTextBoxInit(ref textBoxIdQueryAddr);
            srcEndPointTextBoxInit(ref textBoxSendIdSrcEp);
            srcEndPointTextBoxInit(ref textBoxIdQuerySrcEp);
            dstEndPointTextBoxInit(ref textBoxIdSendDstEp);
            dstEndPointTextBoxInit(ref textBoxIdQueryDstEp);
            time16bitTextBoxInit(ref textBoxIdSendTime);       
            
            // Color cluster initialization
            shortAddrTextBoxInit(ref textBoxMoveToHueAddr);
            srcEndPointTextBoxInit(ref textBoxMoveToHueSrcEp);
            dstEndPointTextBoxInit(ref textBoxMoveToHueDstEp);
            hueTextBoxInit(ref textBoxMoveToHueHue);
            directionTextBoxInit(ref textBoxMoveToHueDir);
            time16bitTextBoxInit(ref textBoxMoveToHueTime);

            shortAddrTextBoxInit(ref textBoxMoveToColorAddr);
            srcEndPointTextBoxInit(ref textBoxMoveToColorSrcEp);
            dstEndPointTextBoxInit(ref textBoxMoveToColorDstEp);
            time16bitTextBoxInit(ref textBoxMoveToColorTime);
            xCoordTextBoxInit(ref textBoxMoveToColorX);
            yCoordTextBoxInit(ref textBoxMoveToColorY);

            shortAddrTextBoxInit(ref textBoxMoveToSatAddr);
            srcEndPointTextBoxInit(ref textBoxMoveToSatSrcEp);
            dstEndPointTextBoxInit(ref textBoxMoveToSatDstEp);
            satTextBoxInit(ref textBoxMoveToSatSat);
            time16bitTextBoxInit(ref textBoxMoveToSatTime);

            shortAddrTextBoxInit(ref textBoxMoveToColorTempAddr);
            srcEndPointTextBoxInit(ref textBoxMoveToColorTempSrcEp);
            dstEndPointTextBoxInit(ref textBoxMoveToColorTempDstEp);
            colorTempTextBoxInit(ref textBoxMoveToColorTempTemp);
            time16bitTextBoxInit(ref textBoxMoveToColorTempRate);

            // Lock cluster initialization
            comboBoxLockUnlock.Items.Add("LOCK");
            comboBoxLockUnlock.Items.Add("UNLOCK");
            comboBoxLockUnlock.SelectedIndex = 0;
            shortAddrTextBoxInit(ref textBoxLockUnlockAddr);
            srcEndPointTextBoxInit(ref textBoxLockUnlockSrcEp);
            dstEndPointTextBoxInit(ref textBoxLockUnlockDstEp);

            // IAS cluster tab initialization
            addrModeComboBoxZCLInit(ref comboBoxEnrollRspAddrMode);
            shortAddrTextBoxInit(ref textBoxEnrollRspAddr);
            dstEndPointTextBoxInit(ref textBoxEnrollRspDstEp);
            srcEndPointTextBoxInit(ref textBoxEnrollRspSrcEp);
            comboBoxEnrollRspCode.Items.Add("SUCCESS");
            comboBoxEnrollRspCode.Items.Add("NOT SUPPORTED");
            comboBoxEnrollRspCode.Items.Add("NO ENROLL PERMIT");
            comboBoxEnrollRspCode.Items.Add("TOO MANY ZONES");
            comboBoxEnrollRspCode.SelectedIndex = 0;
            zoneIdTextBoxInit(ref textBoxEnrollRspZone);

            // ZLL On/Off cluster tab initialization
            shortAddrTextBoxInit(ref textBoxZllOnOffEffectsAddr);
            srcEndPointTextBoxInit(ref textBoxZllOnOffEffectsSrcEp);
            dstEndPointTextBoxInit(ref textBoxZllOnOffEffectsDstEp);             
            gradientTextBoxInit(ref textBoxZllOnOffEffectsGradient);
            comboBoxZllOnOffEffectID.Items.Add("OFF");
            comboBoxZllOnOffEffectID.Items.Add("ON");
            comboBoxZllOnOffEffectID.Items.Add("TOGGLE");
            comboBoxZllOnOffEffectID.SelectedIndex = 0;

            // ZLL color cluster tab initialization
            shortAddrTextBoxInit(ref textBoxZllMoveToHueAddr);
            srcEndPointTextBoxInit(ref textBoxZllMoveToHueSrcEp);
            dstEndPointTextBoxInit(ref textBoxZllMoveToHueDstEp);
            zllhueTextBoxInit(ref textBoxZllMoveToHueHue);
            directionTextBoxInit(ref textBoxZllMoveToHueDirection);
            time16bitTextBoxInit(ref textBoxZllMoveToHueTransTime);

            // OTA cluster tab initialization
            addrModeComboBoxZCLInit(ref comboBoxOTAImageNotifyAddrMode);
            shortAddrTextBoxInit(ref textBoxOTAImageNotifyTargetAddr);
            srcEndPointTextBoxInit(ref textBoxOTAImageNotifySrcEP);
            dstEndPointTextBoxInit(ref textBoxOTAImageNotifyDstEP);
            comboBoxOTAImageNotifyType.Items.Add("JITTER");
            comboBoxOTAImageNotifyType.Items.Add("MDID JITTER");
            comboBoxOTAImageNotifyType.Items.Add("ITYPE MDID JITTER");
            comboBoxOTAImageNotifyType.Items.Add("ITYPE MDID VER JITTER");
            comboBoxOTAImageNotifyType.SelectedIndex = 0;
            fileVersionTextBoxInit(ref textBoxOTAImageNotifyFileVersion);
            imageTypeTextBoxInit(ref textBoxOTAImageNotifyImageType);
            manufacturerIdTextBoxInit(ref textBoxOTAImageNotifyManuID);
            queryJitterTextBoxInit(ref textBoxOTAImageNotifyJitter);

            shortAddrTextBoxInit(ref textBoxOTASetWaitForDataParamsTargetAddr);
            srcEndPointTextBoxInit(ref textBoxOTASetWaitForDataParamsSrcEP);
            currentTme32bitTextBoxInit(ref textBoxOTASetWaitForDataParamsCurrentTime);
            requestTme32bitTextBoxInit(ref textBoxOTASetWaitForDataParamsRequestTime);
            blockDelay16bitTextBoxInit(ref textBoxOTASetWaitForDataParamsRequestBlockDelay);
            time16bitTextBoxInit(ref textBoxIPNConfigPollPeriod);

            DIOMaskInit(ref textBoxDioSetDirectionOutputPinMask);
            DIOMaskInit(ref textBoxDioSetDirectionInputPinMask);

            DIOMaskInit(ref textBoxDioSetOutputOnPinMask);
            DIOMaskInit(ref textBoxDioSetOutputOffPinMask);

            DIOMaskInit(ref textBoxIPNConfigDioRfActiveOutDioMask);
            DIOMaskInit(ref textBoxIPNConfigDioStatusOutDioMask);
            DIOMaskInit(ref textBoxIPNConfigDioTxConfInDioMask);
            comboBoxIPNConfigTimerId.SelectedIndex = 0;
            comboBoxIPNConfigEnable.SelectedIndex = 0;
            comboBoxIPNConfigRegisterCallback.SelectedIndex = 0;

            txPowerTextBoxInit(ref textBoxAHITxPower);

            #region PollControlInit

            PollControlFastPollingExpiryInit(ref textBoxFastPollExpiryTime);

            #endregion
        }

        private void DIOMaskInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "DIO Mask (32-bit Hex)";
        }

        private void txPowerTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Tx Power (6-bit Hex)";
        }

        private void queryJitterTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Query Jitter (8-bit Hex)";
        }

        private void imageTypeTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Image Type (16-bit Hex)";
        }

        private void fileVersionTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Version (32-bit Hex)";
        }

        private void scanDurationTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Duration (8-bit Hex)";
        }

        private void radiusTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Radius (8-bit Hex)";
        }

        private void stringLenTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Len (8-bit Hex)";
        }

        private void extLenTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Ext Len (16-bit Hex)";
        }

        private void sceneDataTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Data (Format: Byte:Byte:Byte)";
            textBox.TextChanged += new EventHandler(textBoxAddSceneData_TextChanged);
        }
        
        private void colorTempTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "TempK (16-bit Dec)";
        }

        private void withOnOffComboBoxInit(ref ComboBox comboBox)
        {
            comboBox.Items.Add("Without OnOff");
            comboBox.Items.Add("With OnOff");
            comboBox.SelectedIndex = 0;
        }

        private void attribDataTypComboBoxInit(ref ComboBox comboBox)
        {            
            comboBox.Items.Add("Bound Addr");
            comboBox.Items.Add("Group Addr");
            comboBox.Items.Add("Short Addr");
            comboBox.Items.Add("IEEE Addr");
            comboBox.SelectedIndex = 0;
        }

        private void manufacturerSpecificComboBoxInit(ref ComboBox comboBox)
        {
            comboBox.Items.Add("STANDARD");
            comboBox.Items.Add("CUSTOM");
            comboBox.SelectedIndex = 0;
        }

        private void attribDataTypeTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Type (8-bit Hex)";
        }

        private void manufacturerIdTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Manu ID (16-bit Hex)";
        }

        private void attribDataTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Data";
        }

        private void reportChangeTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Change (8-bit Hex)";
        }

        private void timeOutPeriodTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "TimeOut (16-bit Hex)";
        }

        private void minIntervalTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Min Intv (16-bit Hex)";
        }

        private void maxIntervalTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Max Intv (16-bit Hex)";
        }

        private void nameStringTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Name (String)";
        }

        private void stringMaxLenTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Max Len (8-bit Hex)";
        }

        private void maxIDsTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Max ID's (8-Bit Hex)";
        }

        private void zoneIdTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Zone ID (8-Bit Hex)";
        }

        private void addrModeComboBoxInit(ref ComboBox comboBox)
        {
            comboBox.Items.Add("Bound");
            comboBox.Items.Add("Group");
            comboBox.Items.Add("Short");
            comboBox.Items.Add("IEEE");
            comboBox.SelectedIndex = 0;
        }

        private void addrModeComboBoxZCLInit(ref ComboBox comboBox)
        {
            comboBox.Items.Add("Bound");
            comboBox.Items.Add("Group");
            comboBox.Items.Add("Short");
            comboBox.Items.Add("IEEE");
            comboBox.Items.Add("Broadcast");
            comboBox.Items.Add("No Transmit");
            comboBox.Items.Add("Bound No Ack");
            comboBox.Items.Add("Short No Ack");
            comboBox.Items.Add("IEEE No Ack");
            comboBox.SelectedIndex = 0;
        }

        private void startIndexTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Start Idx (8-bit Hex)";
        }

        private void effectIdTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Effect ID (8-bit Hex)";
        }

        private void gradientTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Gradient (8-bit Hex)";
        }

        private void directionTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Dir (8-bit Hex)";
        }

        private void hueTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Hue (8-bit Hex)";
        }

        private void zllhueTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Hue (16-bit Hex)";
        }

        private void satTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Saturation (8-bit Hex)";
        }

        private void xCoordTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "X (16-bit Hex)";
        }

        private void yCoordTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Y (16-bit Hex)";
        }

        private void currentTme32bitTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Current Time (32-bit Hex)";
        }

        private void requestTme32bitTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Request Time (32-bit Hex)";
        }

        private void blockDelay16bitTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Block Delay (16-bit Hex)";
        }

        
        private void time8bitTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Time (8-bit Hex)";
        }

        private void time16bitTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Time (16-bit Hex)";
        }

        private void levelTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Level (8-bit Hex)";
        }

        private void profileIdTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Profile (16-bit Hex)";
        }

        private void clusterIdTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Cluster (16-bit Hex)";
        }

        private void attributeIdTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Attrib (16-bit Hex)";
        }

        private void attributeCountTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Attrib Count";
        }

        private void attributeTypeTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Attrib Type";
        }

        private void attributeDataTypeTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Type (8-bit Hex)";
        }

        private void targetShortAddrTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Target (16-bit Hex)";
        }

        private void commandIDTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Cmd ID (8-bit Hex)";
        }

        private void maxCommandsTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Max Cmds (8-bit Hex)";
        }

        private void shortAddrTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Address (16-bit Hex)";
        }

        private void destShortAddrTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Dst Addr (16-bit Hex)";
        }

        private void destShortIeeeAddrTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Dst Addr (16-bit or 64-bit Hex)";
        }

        private void extendedAddrTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Address (64-bit Hex)";
        }

        private void AddrTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Address";
        }

        private void targetExtendedAddrTextBoxInit(ref ComboBox comboBox)
        {
            comboBox.ForeColor = System.Drawing.Color.Gray;
            comboBox.Text = "Target Address (64-bit Hex)";
        }

        private void targetExtendedAddrTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Target Address (64-bit Hex)";
        }

        private void dstEndPointTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Dst EP (8-bit Hex)";
        }

        private void targetEndPointTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Target EP (8-bit Hex)";
        }

        private void srcEndPointTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Src EP (8-bit Hex)";
        }

        private void groupCountTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Group Count";
        }

        private void sceneIdTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Scene ID (8-bit Hex)";
        }

        private void groupIdTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Group ID (16-bit Hex)";
        }

        private void groupNameLengthTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Name Len (8-bit Hex)";
        }

        private void groupNameMaxLengthTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Max Len (8-bit Hex)";
        }

        private void groupNameTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Group Name (String)";
        }

        private void PollControlFastPollingExpiryInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Fast Poll Expiry (16-bit Hex)";
        }

        private void OOBAddrTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Address (64-bit Hex)";
        }

        private void OOBKeyTextBoxInit(ref TextBox textBox)
        {
            textBox.ForeColor = System.Drawing.Color.Gray;
            textBox.Text = "Key (Format: Byte:Byte:Byte)";
            textBox.TextChanged += new EventHandler(textBoxOOBDataKey_TextChanged);
        }

        #endregion
        
        #region ToolTip

        private void showToolTipWindow(string s)
        {
            Point p = this.PointToClient(Cursor.Position);
            toolTipGeneralTooltip.Show(s, this, p.X - 25, p.Y - 5);
        }

        private void hideToolTipWindow()
        {
            toolTipGeneralTooltip.Hide(this);
        }

        #endregion

        #region menu strip functions

        private bool bPortConfigured = false;

        private void settingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                MessageBox.Show("The port must be closed before changing the settings");
                return;
            }
            else
            {
                PortSettings settings = new PortSettings();

                if (settings.ShowDialog() == DialogResult.OK)
                {
                    serialPort1.PortName = settings.selectedPort;
                    serialPort1.BaudRate = settings.selectedBaudRate;
                    serialPort1.DataBits = 8;
                    serialPort1.Parity   = Parity.None;
                    serialPort1.StopBits = StopBits.One;
                    serialPort1.DataReceived += new SerialDataReceivedEventHandler(serialPort1_DataReceivedHandler);                    

                    displayPortSettings();

                    bPortConfigured = true;
                }
            }
        }

        private void openPortToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (bPortConfigured == true)
            {
                try
                {
                    if (serialPort1.IsOpen)
                    {
                        serialPort1.Close();
                        openPortToolStripMenuItem.Text = "Open Port";
                    }
                    else
                    {
                        serialPort1.Open();
                        openPortToolStripMenuItem.Text = "Close Port";
                    }
                    displayPortSettings();
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show("Error - openPortToolStripMenuItem_Click Exception: " + ex);
                }
            }
            else
            {
                MessageBox.Show("Error - No Port Selected");
            }
        }

        private void displayPortSettings()
        {
            toolStripPortSettings.Text = serialPort1.PortName;
            toolStripPortSettings.Text += " ";
            toolStripPortSettings.Text += serialPort1.BaudRate.ToString();
            toolStripPortSettings.Text += "-";
            toolStripPortSettings.Text += serialPort1.DataBits.ToString();
            toolStripPortSettings.Text += "-";
            toolStripPortSettings.Text += (serialPort1.Parity.ToString())[0];
            toolStripPortSettings.Text += "-";

            if (serialPort1.StopBits.ToString() == "One")
            {
                toolStripPortSettings.Text += "1";
            }
            else
            {
                toolStripPortSettings.Text += "2";
            }

            toolStripPortSettings.Text += " ";

            if (serialPort1.IsOpen)
            {
                toolStripPortSettings.Text += "Open";
            }
            else
            {
                toolStripPortSettings.Text += "Closed";
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                string path = Directory.GetCurrentDirectory();
                String version = System.IO.File.ReadAllText(path + "\\..\\..\\VERSION.txt");

                MessageBox.Show("NXP ZigBee Gateway User Interface - Version " + version);
            }
            catch (FileNotFoundException)
            {
                MessageBox.Show("Version File not found\nPlease run ZGWUI in Directory: \n\nJN-AN-1223-ZigBee-IoT-Gateway-Control-Bridge");
            }
        }

        #endregion 

        #region management command button handlers

        private void buttonMgmtLeave_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            UInt64 u64ExtAddr;

            if (bStringToUint16(textBoxMgmtLeaveAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint64(textBoxMgmtLeaveExtAddr.Text, out u64ExtAddr) == true)
                {
                    sendMgmtLeaveRequest(u16ShortAddr, u64ExtAddr, (byte)comboBoxMgmtLeaveReJoin.SelectedIndex, (byte)comboBoxMgmtLeaveChildren.SelectedIndex);
                }
            }            

        }

        private void buttonUnBind_Click(object sender, EventArgs e)
        {            
            UInt64 u64TargetExtAddr;
            UInt16 u16ClusterID;
            UInt64 u64DstAddr;
            byte u8TargetEndPoint;
            byte u8DstEndPoint;

            if (bStringToUint64(textBoxUnBindTargetExtAddr.Text, out u64TargetExtAddr) == true)
            {
                if (bStringToUint8(textBoxUnBindTargetEP.Text, out u8TargetEndPoint) == true)
                {
                    if (bStringToUint16(textBoxUnBindClusterID.Text, out u16ClusterID) == true)
                    {
                        if (bStringToUint64(textBoxUnBindDestAddr.Text, out u64DstAddr) == true)
                        {
                            if (bStringToUint8(textBoxUnBindDestEP.Text, out u8DstEndPoint) == true)
                            {
                                sendUnBindRequest(u64TargetExtAddr, u8TargetEndPoint, u16ClusterID, (byte)comboBoxUnBindAddrMode.SelectedIndex, u64DstAddr, u8DstEndPoint);
                            }
                        }
                    }
                }
            }                     
        }

        private void buttonBind_Click(object sender, EventArgs e)
        {
            UInt64 u64TargetExtAddr;
            UInt16 u16ClusterID;
            UInt64 u64DstAddr;
            byte u8TargetEndPoint;
            byte u8DstEndPoint;

            if (bStringToUint64(textBoxBindTargetExtAddr.Text, out u64TargetExtAddr) == true)
            {
                if (bStringToUint8(textBoxBindTargetEP.Text, out u8TargetEndPoint) == true)
                {
                    if (bStringToUint16(textBoxBindClusterID.Text, out u16ClusterID) == true)
                    {
                        if (bStringToUint64(textBoxBindDestAddr.Text, out u64DstAddr) == true)
                        {
                            if (bStringToUint8(textBoxBindDestEP.Text, out u8DstEndPoint) == true)
                            {
                                sendBindRequest(u64TargetExtAddr, u8TargetEndPoint, u16ClusterID, (byte)comboBoxBindAddrMode.SelectedIndex, u64DstAddr, u8DstEndPoint);
                            }                            
                        }                         
                    }
                }
            }
        }

        private void buttonSetCMSK_Click(object sender, EventArgs e)
        {
            UInt32 u32ChannelMask;

            // First check if user is entering a single channel or a 32-bit mask..
            if (UInt32.TryParse(textBoxSetCMSK.Text, NumberStyles.Integer, CultureInfo.CurrentCulture, out u32ChannelMask) == true)
            {
                if (u32ChannelMask >= 11 && u32ChannelMask <= 26)
                {
                    // User is specifying a single channel, we must create the 32-bit mask from this                                        
                    UInt32 u32ChannelMaskTemp = 1;

                    for (int i = 0; i < u32ChannelMask; i++)
                    {
                        u32ChannelMaskTemp <<= 1;
                    }
                    u32ChannelMask = u32ChannelMaskTemp;
               
                    // Set channel mask
                    setChannelMask(u32ChannelMask);
                }
                else
                {
                    // User has entered a channel bit mask
                    if (bStringToUint32(textBoxSetCMSK.Text, out u32ChannelMask) == true)
                    {
                        // Set channel mask
                        setChannelMask(u32ChannelMask);
                    }
                }
            }
        }

        private void buttonMgmtLqiReq_Click_1(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            byte u8StartIndex;

            if (bStringToUint16(textBoxLqiReqTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint8(textBoxLqiReqStartIndex.Text, out u8StartIndex) == true)
                {
                    sendMgmtLqiRequest(u16TargetAddr, u8StartIndex);
                }
            }
        }

        private void buttonNwkAddrReq_Click(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            UInt64 u64ExtAddr;            
            byte u8StartIndex;

            if (bStringToUint16(textBoxNwkAddrReqTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint64(textBoxNwkAddrReqExtAddr.Text, out u64ExtAddr) == true)
                {
                    if (bStringToUint8(textBoxNwkAddrReqStartIndex.Text, out u8StartIndex) == true)
                    {
                        sendNwkAddrRequest(u16TargetAddr, u64ExtAddr, (byte)comboBoxNwkAddrReqType.SelectedIndex, u8StartIndex);
                    }
                }
            }
        }

        private void buttonIeeeAddrReq_Click(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            UInt16 u16ShortAddr;            
            byte u8StartIndex;

            if (bStringToUint16(textBoxIeeeReqTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint16(textBoxIeeeReqAddr.Text, out u16ShortAddr) == true)
                {
                    if (bStringToUint8(textBoxIeeeReqStartIndex.Text, out u8StartIndex) == true)
                    {
                        sendIeeeAddrRequest(u16TargetAddr, u16ShortAddr, (byte)comboBoxIeeeReqType.SelectedIndex, u8StartIndex);
                    }
                }
            }
        }

        private void buttonComplexReq_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;

            if (bStringToUint16(textBoxComplexReqAddr.Text, out u16ShortAddr) == true)
            {
                complexDescriptorRequest(u16ShortAddr);
            }            
        }

        private void buttonUserReq_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;

            if (bStringToUint16(textBoxUserReqAddr.Text, out u16ShortAddr) == true)
            {
                userDescriptorRequest(u16ShortAddr);
            }  
        }

        private void buttonUserSetReq_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;

            if (bStringToUint16(textBoxUserSetReqAddr.Text, out u16ShortAddr) == true)
            {
                if (textBoxUserSetReqDescription.Text != "")
                {
                    userDescriptorSetRequest(u16ShortAddr, textBoxUserSetReqDescription.Text);
                }
            }  
        }

        private void buttonMatchReq_Click(object sender, EventArgs e)
        {            
            UInt16 u16ShortAddr;
            UInt16 u16ProfileID;
            byte u8NbrInputClusters;
            byte u8NbrOutputClusters;            
            UInt16[] au16InputClusters = new UInt16[8];
            UInt16[] au16OutputClusters = new UInt16[8];           
            
            if (bStringToUint16(textBoxMatchReqAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint16(textBoxMatchReqProfileID.Text, out u16ProfileID) == true)
                {
                    if (bStringToUint8(textBoxMatchReqNbrInputClusters.Text, out u8NbrInputClusters) == true)
                    {
                        if ((u8NbrInputClusters == 0) ||
                            ((u8NbrInputClusters > 0) &&
                             (bStringToUint16Array(textBoxMatchReqInputClusters.Text, out au16InputClusters) == true)))
                        {
                            if (bStringToUint8(textBoxMatchReqNbrOutputClusters.Text, out u8NbrOutputClusters) == true)
                            {
                                if ((u8NbrOutputClusters == 0) ||
                                    ((u8NbrOutputClusters > 0) &&
                                    (bStringToUint16Array(textBoxMatchReqOutputClusters.Text, out au16OutputClusters) == true)))
                                {
                                    matchDescriptorRequest(u16ShortAddr, u16ProfileID, u8NbrInputClusters, au16InputClusters, u8NbrOutputClusters, au16OutputClusters);
                                }
                            }
                        }                        
                    }
                }                
            }
        }

        private void buttonActiveEpReq_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;

            if (bStringToUint16(textBoxActiveEpAddr.Text, out u16ShortAddr) == true)
            {
                activeEndpointDescriptorRequest(u16ShortAddr);
            }            
        }

        private void buttonSimpleDescReq_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr; 
            byte u8EndPoint;

            if (bStringToUint16(textBoxSimpleReqAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxSimpleReqEndPoint.Text, out u8EndPoint) == true)
                {
                    simpleDescriptorRequest(u16ShortAddr, u8EndPoint);
                }
            }
        }

        private void buttonPowerDescReq_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;

            if (bStringToUint16(textBoxPowerReqAddr.Text, out u16ShortAddr) == true)
            {
                powerDescriptorRequest(u16ShortAddr);
            }
        }

        private void buttonPermitJoin_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            byte u8Interval;

            if (bStringToUint16(textBoxPermitJoinAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxPermitJoinInterval.Text, out u8Interval) == true)
                {
                    setPermitJoin((UInt16)u16ShortAddr, u8Interval, (byte)comboBoxPermitJoinTCsignificance.SelectedIndex);
                }
            }
        }
                                        
        private void buttonSetDeviceType_Click(object sender, EventArgs e)
        {
            // Set device type
            setDeviceType((byte)comboBoxSetType.SelectedIndex);
        }

        private void buttonSetEPID_Click(object sender, EventArgs e)
        {
            UInt64 u64ExtendedPanID;

            if (bStringToUint64(textBoxSetEPID.Text, out u64ExtendedPanID) == true)
            {
                // Set channel mask
                setExtendedPanID(u64ExtendedPanID);
            }
        }

        private void buttonGetVersion_Click(object sender, EventArgs e)
        {
            transmitCommand(0x0010, 0, null);
        }

        private void buttonReset_Click(object sender, EventArgs e)
        {
            // Transmit command
            transmitCommand(0x0011, 0, null);
        }

        private void buttonErasePD_Click(object sender, EventArgs e)
        {
            // Transmit command
            transmitCommand(0x0012, 0, null);
        }

        private void buttonStartNWK_Click(object sender, EventArgs e)
        {
            // Transmit command
            transmitCommand(0x0024, 0, null);
        }

        private void buttonStartScan_Click(object sender, EventArgs e)
        {
            transmitCommand(0x0025, 0, null);
        }

        private void buttonDiscoveryOnly_Click(object sender, EventArgs e)
        {
            transmitCommand(0x0015, 0, null);
        }

        private void buttonSetSecurity_Click(object sender, EventArgs e)
        {
            byte u8SeqNbr;
            byte[] au8keyData;

            if (bStringToUint8(textBoxSetSecurityKeySeqNbr.Text, out u8SeqNbr) == true)
            {
                if (bStringToUint128(comboBoxSecurityKey.Text, out au8keyData) == true)
                {
                    // Set key state information
                    setSecurityKeyState((byte)comboBoxSetKeyState.SelectedIndex, u8SeqNbr, (byte)comboBoxSetKeyType.SelectedIndex, au8keyData);
                }
            }            
        }

        private void buttonNodeDescReq_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;

            if (bStringToUint16(textBoxNodeDescReq.Text, out u16ShortAddr) == true)
            {
                nodeDescriptorRequest(u16ShortAddr);
            }
        }

        #endregion        	

        #region general command button handlers

        /* Unsupported*/
		private void buttonRecoverNwk_Click(object sender, EventArgs e)
        {            
            transmitCommand(0x0600, 0, null);
        }

        /* Unsupported */
        private void buttonRestoreNwk_Click(object sender, EventArgs e)
        {
            UInt32 u32OutFrameCounter = 0;
            byte[] baBuff = new byte[nwkRecovery.iGetSize()];

            if (textBoxRestoreNwkFrameCounter.TextLength < 10 && textBoxRestoreNwkFrameCounter.TextLength != 0)
            {
                bStringToUint32(textBoxRestoreNwkFrameCounter.Text, out u32OutFrameCounter);
                nwkRecovery.NetworkRecoverySetOutFrameCounter(u32OutFrameCounter);
            }

            nwkRecovery.NetworkRecoveryConstructBuffer(ref baBuff);
            transmitCommand(0x0601, nwkRecovery.iGetSize(), baBuff);
        }
        private void buttonDiscoverCommands_Click(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            UInt16 u16ClusterID;
            UInt16 u16ManuID;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8CommandId;
            byte u8MaxCommands;

            if (bStringToUint16(textBoxDiscoverCommandsTargetAddr.Text, out u16TargetAddr) == true)
            {                            
                if (bStringToUint8(textBoxDiscoverCommandsSrcEP.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxDiscoverCommandsDstEP.Text, out u8DstEndPoint) == true)
                    {                        
                        if (bStringToUint16(textBoxDiscoverCommandsClusterID.Text, out u16ClusterID) == true)
                        {
                            if (bStringToUint8(textBoxDiscoverCommandsCommandID.Text, out u8CommandId) == true)
                            {
                                if (bStringToUint16(textBoxDiscoverCommandsManuID.Text, out u16ManuID) == true)
                                {                                
                                    if (bStringToUint8(textBoxDiscoverCommandsMaxCommands.Text, out u8MaxCommands) == true)
                                    {
                                        sendDiscoverCommandsRequest((byte)comboBoxDiscoverCommandsAddrMode.SelectedIndex, u16TargetAddr, u8SrcEndPoint, u8DstEndPoint, u16ClusterID, (byte)comboBoxDiscoverCommandsDirection.SelectedIndex, u8CommandId, (byte)comboBoxDiscoverCommandsManuSpecific.SelectedIndex, u16ManuID, u8MaxCommands, (byte)comboBoxDiscoverCommandsRxGen.SelectedIndex);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private void buttonMgmtNwkUpdate_Click(object sender, EventArgs e)
        {
            UInt32 u32ChannelMask;
            UInt16 u16TargetAddr;
            UInt16 u16NwkManangerAddr;
            byte u8ScanDuration;
            byte u8ScanCount;

            if (bStringToUint16(textBoxMgmtNwkUpdateTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint32(textBoxMgmtNwkUpdateChannelMask.Text, out u32ChannelMask) == true)
                {
                    if (bStringToUint8(textBoxMgmtNwkUpdateScanDuration.Text, out u8ScanDuration) == true)
                    {
                        if (bStringToUint8(textBoxMgmtNwkUpdateScanCount.Text, out u8ScanCount) == true)
                        {
                            if (bStringToUint16(textBoxMgmtNwkUpdateNwkManagerAddr.Text, out u16NwkManangerAddr) == true)
                            {
                                sendMgmtNwkUpdateRequest((byte)comboBoxMgmtNwkUpdateAddrMode.SelectedIndex, u16TargetAddr, u32ChannelMask, u8ScanDuration, u8ScanCount, u16NwkManangerAddr);
                            }
                        }
                    }
                }
            }
        }

        private void buttonManyToOneRouteRequest_Click(object sender, EventArgs e)
        {
            byte u8Radius;

            if (bStringToUint8(textBoxManyToOneRouteRequesRadius.Text, out u8Radius) == true)
            {
                sendOneToManyRouteRequest((byte)comboBoxManyToOneRouteRequestCacheRoute.SelectedIndex, u8Radius);
            }
        }

        private void buttonWriteAttrib_Click_1(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            UInt16 u16ClusterID;
            UInt16 u16AttribID;
            UInt16 u16ManuID;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8AttribType;
            byte[] au8Data = new byte[64];
            byte u8DataLen = 0;

            if (bStringToUint16(textBoxWriteAttribTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint8(textBoxWriteAttribSrcEP.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxWriteAttribDstEP.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxWriteAttribClusterID.Text, out u16ClusterID) == true)
                        {
                            if (bStringToUint16(textBoxWriteAttribID.Text, out u16AttribID) == true)
                            {
                                if (bStringToUint16(textBoxWriteAttribManuID.Text, out u16ManuID) == true)
                                {
                                    if (bStringToUint8(textBoxWriteAttribDataType.Text, out u8AttribType) == true)
                                    {
                                        if (u8AttribType == 0x42)
                                        {
                                            // if the data is a character string get the length make make this is the first byte                                         
                                            au8Data[0] = (byte)System.Text.Encoding.ASCII.GetBytes(textBoxWriteAttribData.Text, 0, textBoxWriteAttribData.TextLength, au8Data, 1);
                                            u8DataLen = au8Data[0];
                                            u8DataLen++;
                                        }
                                        else if (u8AttribType == 0x21)
                                        {
                                            UInt16 u16Data;

                                            /* Data is a uint16 */
                                            if (bStringToUint16(textBoxWriteAttribData.Text, out u16Data) == true)
                                            {
                                                u8DataLen = 2;
                                                au8Data[1] = (byte)u16Data;
                                                au8Data[0] = (byte)(u16Data >> 8);
                                            }
                                        }
                                        else
                                        {
                                            for (int i = 0; i < textBoxWriteAttribData.TextLength; i += 2)
                                            {
                                                byte u8Data = 0;
                                                if (bStringToUint8(textBoxWriteAttribData.Text, out u8Data) == true)
                                                {
                                                    au8Data[i] = u8Data;
                                                }
                                                else
                                                {
                                                    return;
                                                }
                                                u8DataLen++;
                                            }
                                        }
                                        sendWriteAttribRequest(u16TargetAddr, u8SrcEndPoint, u8DstEndPoint, u16ClusterID, (byte)comboBoxReadAttribDirection.SelectedIndex, (byte)comboBoxWriteAttribManuSpecific.SelectedIndex, u16ManuID, 1, u16AttribID, u8AttribType, au8Data, u8DataLen);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private void buttonReadAttrib_Click_1(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            UInt16 u16ClusterID;
            UInt16 u16AttribID1;
            UInt16 u16ManuID;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8AttribCount;

            if (bStringToUint16(textBoxReadAttribTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint8(textBoxReadAttribSrcEP.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxReadAttribDstEP.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxReadAttribClusterID.Text, out u16ClusterID) == true)
                        {
                            if (bStringToUint8(textBoxReadAttribCount.Text, out u8AttribCount) == true)
                            {
                                if (bStringToUint16(textBoxReadAttribID1.Text, out u16AttribID1) == true)
                                {
                                    if (bStringToUint16(textBoxReadAttribManuID.Text, out u16ManuID) == true)
                                    {
                                        sendReadAttribRequest(u16TargetAddr, u8SrcEndPoint, u8DstEndPoint, u16ClusterID, (byte)comboBoxReadAttribDirection.SelectedIndex, (byte)comboBoxReadAttribManuSpecific.SelectedIndex, u16ManuID, u8AttribCount, u16AttribID1);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private void buttonReadReportConfig_Click(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint; 
            UInt16 u16ClusterID;
            UInt16 u16AttribID;

            if (bStringToUint16(textBoxReadReportConfigTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint8(textBoxReadReportConfigSrcEP.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxReadReportConfigDstEP.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxReadReportConfigClusterID.Text, out u16ClusterID) == true)
                        {
                            if (bStringToUint16(textBoxReadReportConfigAttribID.Text, out u16AttribID) == true)
                            {
                                sendReadReportConfigRequest((byte)comboBoxReadReportConfigAddrMode.SelectedIndex, u16TargetAddr, u8SrcEndPoint, u8DstEndPoint, u16ClusterID, (byte)comboBoxReadReportConfigDirection.SelectedIndex, 1, 0, 0, (byte)comboBoxReadReportConfigDirIsRx.SelectedIndex, u16AttribID);
                            }
                        }
                    }
                }
            }
        }

        private void buttonConfigReport_Click_1(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            UInt16 u16ClusterID;
            UInt16 u16AttribId;
            UInt16 u16MinInterval;
            UInt16 u16MaxInterval;
            UInt16 u16TimeOut;
            UInt64 u64Change;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;  
            byte u8AttribType;

            if (bStringToUint16(textBoxConfigReportTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint8(textBoxConfigReportSrcEP.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxConfigReportDstEP.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxConfigReportClusterID.Text, out u16ClusterID) == true)
                        {
                            if (bStringToUint8(textBoxConfigReportAttribType.Text, out u8AttribType) == true)
                            {
                                if (bStringToUint16(textBoxConfigReportAttribID.Text, out u16AttribId) == true)
                                {
                                    if (bStringToUint16(textBoxConfigReportMinInterval.Text, out u16MinInterval) == true)
                                    {
                                        if (bStringToUint16(textBoxConfigReportMaxInterval.Text, out u16MaxInterval) == true)
                                        {
                                            if (bStringToUint16(textBoxConfigReportTimeOut.Text, out u16TimeOut) == true)
                                            {
                                                if (bStringToUint64(textBoxConfigReportChange.Text, out u64Change) == true)
                                                {
                                                    sendConfigReportRequest((byte)comboBoxConfigReportAddrMode.SelectedIndex, u16TargetAddr, u8SrcEndPoint, u8DstEndPoint, u16ClusterID, (byte)comboBoxConfigReportDirection.SelectedIndex, (byte)comboBoxConfigReportAttribDirection.SelectedIndex, u8AttribType, u16AttribId, u16MinInterval, u16MaxInterval, u16TimeOut, u64Change);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private void buttonDiscoverAttributes_Click(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            UInt16 u16ClusterID;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8AttribsMax;
            byte u8AttribOffset;

            if (bStringToUint16(textBoxDiscoverAttributesAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint8(textBoxDiscoverAttributesSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxDiscoverAttributesDstEp.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxDiscoverAttributesClusterID.Text, out u16ClusterID) == true)
                        {
                            if (bStringToUint8(textBoxDiscoverAttributesMaxIDs.Text, out u8AttribsMax) == true)
                            {
                                if (bStringToUint8(textBoxDiscoverAttributesStartAttrId.Text, out u8AttribOffset) == true)
                                {
                                    sendDiscoverAttributesRequest(u16TargetAddr, u8SrcEndPoint, u8DstEndPoint, u16ClusterID, u8AttribOffset, (byte)comboBoxDiscoverAttributesDirection.SelectedIndex, 0, 0, u8AttribsMax, (byte)comboBoxDiscoverAttributesExtended.SelectedIndex);
                                }
                            }
                        }
                    }
                }
            }
        }

        /*private void buttonReadAllAttrib_Click(object sender, EventArgs e)
        *{
        *    UInt16 u16DstAddr;
        *    UInt16 u16ClusterID;
        *    byte u8SrcEndPoint;
        *    byte u8DstEndPoint;
        *
        *    if (bStringToUint16(textBoxReadAllAttribAddr.Text, out u16DstAddr) == true)
        *    {
        *        if (bStringToUint8(textBoxReadAllAttribSrcEP.Text, out u8SrcEndPoint) == true)
        *        {
        *            if (bStringToUint8(textBoxReadAllAttribDstEP.Text, out u8DstEndPoint) == true)
        *            {
        *                if (bStringToUint16(textBoxReadAllAttribClusterID.Text, out u16ClusterID) == true)
        *                {
        *                    sendReadAllAttribRequest(u16DstAddr, u8SrcEndPoint, u8DstEndPoint, u16ClusterID, (byte)comboBoxReadAttribDirection.SelectedIndex, 0, 0);
        *                }
        *            }
        *        }
        *    }
        }*/

        private void buttonOOBCommissioningData_Click(object sender, EventArgs e)
        {
            string stringkeydata;
            UInt64 u64AddrData;
                        
            if (bStringToUint64(textBoxOOBDataAddr.Text, out u64AddrData) == true)                        
            {                            
                if (1 == (textBoxOOBDataKey.TextLength % 2))
                {
                    stringkeydata = textBoxOOBDataKey.Text;
                    sendOOBCommissioningData(u64AddrData, stringkeydata);
                }
            }
        }

        private void buttonPermitJoinState_Click(object sender, EventArgs e)
        {
            vSendPermitRejoinStateRequest();
        }

        private void buttonNWKState_Click(object sender, EventArgs e)
        {
            vSendNetworkStateRequest();
        }

        #endregion

        #region basic cluster command button handlers

        private void buttonBasicReset_Click(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;

            if (bStringToUint16(textBoxBasicResetTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint8(textBoxBasicResetSrcEP.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxBasicResetDstEP.Text, out u8DstEndPoint) == true)
                    {
                        sendBasicResetFactoryDefaultCommand((byte)comboBoxBasicResetTargetAddrMode.SelectedIndex, u16TargetAddr, u8SrcEndPoint, u8DstEndPoint);
                    }
                }
            }
        }

        #endregion
        
        #region OTA cluster button handlers


        private void buttonOTASetWaitForDataParams_Click(object sender, EventArgs e)
        {
            if (bStringToUint16(textBoxOTASetWaitForDataParamsTargetAddr.Text, out u16OTAWaitForDataParamsTargetAddr) == true)
            {
                if (bStringToUint8(textBoxOTASetWaitForDataParamsSrcEP.Text, out u8OTAWaitForDataParamsSrcEndPoint) == true)
                {
                    if (bStringToUint32(textBoxOTASetWaitForDataParamsCurrentTime.Text, out u32OTAWaitForDataParamsCurrentTime) == true)
                    {
                        if (bStringToUint32(textBoxOTASetWaitForDataParamsRequestTime.Text, out u32OTAWaitForDataParamsRequestTime) == true)
                        {
                            if (bStringToUint16(textBoxOTASetWaitForDataParamsRequestBlockDelay.Text, out u16OTAWaitForDataParamsBlockDelay) == true)
                            {
                                // Set flag indicating that next time we get a block request we should reply with a wait for data message
                                u8OTAWaitForDataParamsPending = 1;
                            }
                        }
                    }
                }
            }
        }

        private void buttonOTAImageNotify_Click(object sender, EventArgs e)
        {
            UInt32 u32FileVersion;
            UInt16 u16TargetAddr;
            UInt16 u16ImageType;
            UInt16 u16ManuCode;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8Jitter;

            if (bStringToUint16(textBoxOTAImageNotifyTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint8(textBoxOTAImageNotifySrcEP.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxOTAImageNotifyDstEP.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint32(textBoxOTAImageNotifyFileVersion.Text, out u32FileVersion) == true)
                        {
                            if (bStringToUint16(textBoxOTAImageNotifyImageType.Text, out u16ImageType) == true)
                            {
                                if (bStringToUint16(textBoxOTAImageNotifyManuID.Text, out u16ManuCode) == true)
                                {
                                    if (bStringToUint8(textBoxOTAImageNotifyJitter.Text, out u8Jitter) == true)
                                    {
                                        sendOtaImageNotify((byte)comboBoxOTAImageNotifyAddrMode.SelectedIndex, u16TargetAddr, u8SrcEndPoint, u8DstEndPoint, (byte)comboBoxOTAImageNotifyType.SelectedIndex, u32FileVersion, u16ImageType, u16ManuCode, u8Jitter);
                                    }
                                }
                            }
                        }                    
                    }
                }
            }
        }

        private void buttonOTALoadNewImage_Click(object sender, EventArgs e)
        {
            if (openOtaFileDialog.ShowDialog() != DialogResult.Cancel)
            {
                FileStream otaFileStream = null;

                try
                {
                    otaFileStream = File.OpenRead(openOtaFileDialog.FileName);                    
                    otaFileStream.Read(au8OTAFile, 0, Convert.ToInt32(otaFileStream.Length));

                    byte[] au8OtaFileHeaderString = null;
                    au8OtaFileHeaderString = new byte[32];
                    byte i;

                    for (i = 0; i < 32; i++)
                    {
                        au8OtaFileHeaderString[i] = au8OTAFile[20 + i];
                    }

                    u32OtaFileIdentifier = BitConverter.ToUInt32(au8OTAFile, 0);
                    u16OtaFileHeaderVersion = BitConverter.ToUInt16(au8OTAFile, 4);
                    u16OtaFileHeaderLength = BitConverter.ToUInt16(au8OTAFile, 6);
                    u16OtaFileHeaderControlField = BitConverter.ToUInt16(au8OTAFile, 8);
                    u16OtaFileManufacturerCode = BitConverter.ToUInt16(au8OTAFile, 10);
                    u16OtaFileImageType = BitConverter.ToUInt16(au8OTAFile, 12);
                    u32OtaFileVersion = BitConverter.ToUInt32(au8OTAFile, 14);
                    u16OtaFileStackVersion = BitConverter.ToUInt16(au8OTAFile, 18);
                    u32OtaFileTotalImage = BitConverter.ToUInt32(au8OTAFile, 52);
                    u8OtaFileSecurityCredVersion = au8OTAFile[56];
                    u64OtaFileUpgradeFileDest = BitConverter.ToUInt64(au8OTAFile, 57);
                    u16OtaFileMinimumHwVersion = BitConverter.ToUInt16(au8OTAFile, 65);
                    u16OtaFileMaxHwVersion = BitConverter.ToUInt16(au8OTAFile, 67);

                    textBoxOtaFileID.Text = u32OtaFileIdentifier.ToString("X4");
                    textBoxOtaFileHeaderVer.Text = u16OtaFileHeaderVersion.ToString("X2");
                    textBoxOtaFileHeaderLen.Text = u16OtaFileHeaderLength.ToString("X2");
                    textBoxOtaFileHeaderFCTL.Text = u16OtaFileHeaderControlField.ToString("X2");
                    textBoxOtaFileManuCode.Text = u16OtaFileManufacturerCode.ToString("X4");
                    textBoxOtaFileImageType.Text = u16OtaFileImageType.ToString("X4");
                    textBoxOtaFileVersion.Text = u32OtaFileVersion.ToString("X8");
                    textBoxOtaFileStackVer.Text = u16OtaFileStackVersion.ToString("X2");
                    textBoxOtaFileSize.Text = u32OtaFileTotalImage.ToString();
                    textBoxOtaFileHeaderStr.Text = System.Text.Encoding.Default.GetString(au8OtaFileHeaderString);

                    sendOtaLoadNewImage(0x02, 0x0000, u32OtaFileIdentifier, u16OtaFileHeaderVersion, u16OtaFileHeaderLength, u16OtaFileHeaderControlField, u16OtaFileManufacturerCode, u16OtaFileImageType, u32OtaFileVersion, u16OtaFileStackVersion, au8OtaFileHeaderString, u32OtaFileTotalImage, u8OtaFileSecurityCredVersion, u64OtaFileUpgradeFileDest, u16OtaFileMinimumHwVersion, u16OtaFileMaxHwVersion);                                
                }
                finally
                {
                    if (otaFileStream != null)
                    {
                        otaFileStream.Close();
                        otaFileStream.Dispose();
                    }
                }
            }            
        }

        #endregion

        #region group cluster button handlers

        private void buttonGroupAddIfIdentifying_Click(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            UInt16 u16GroupAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;

            if (bStringToUint16(textBoxGroupAddIfIndentifyingTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint8(textBoxGroupAddIfIdentifySrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxGroupAddIfIdentifyDstEp.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxGroupAddIfIdentifyGroupID.Text, out u16GroupAddr) == true)
                        {
                            sendGroupAddIfIdentifying(u16TargetAddr, u8SrcEndPoint, u8DstEndPoint, u16GroupAddr);
                        }
                    }
                }
            }
        }

        private void buttonGroupRemoveAll_Click(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;

            if (bStringToUint16(textBoxRemoveAllGroupTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint8(textBoxRemoveAllGroupSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxRemoveAllGroupDstEp.Text, out u8DstEndPoint) == true)
                    {
                        sendGroupRemoveAll(u16TargetAddr, u8SrcEndPoint, u8DstEndPoint);
                    }
                }
            }
        }

        private void buttonRemoveGroup_Click(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            UInt16 u16GroupAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;

            if (bStringToUint16(textBoxRemoveGroupTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint8(textBoxRemoveGroupSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxRemoveGroupDstEp.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxRemoveGroupGroupAddr.Text, out u16GroupAddr) == true)
                        {
                            sendGroupRemove(u16TargetAddr, u8SrcEndPoint, u8DstEndPoint, u16GroupAddr);
                        }
                    }
                }
            }
        }

        private void buttonGetGroup_Click(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8GroupCount;
            UInt16[] au16GroupList = new UInt16[8];

            if (bStringToUint16(textBoxGetGroupTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint8(textBoxGetGroupSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxGetGroupDstEp.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint8(textBoxGetGroupCount.Text, out u8GroupCount) == true)
                        {
                            if (listManager.getListCount() >= u8GroupCount)
                            {
                                if (bStringToUint16Array(listManager.getListAsString(), out au16GroupList) == true)
                                {
                                    sendGroupGet(u16TargetAddr, u8SrcEndPoint, u8DstEndPoint, u8GroupCount, au16GroupList);
                                }
                            }
                            else
                            {
                                MessageBox.Show("Invalid Parameter");
                            }
                        }
                    }
                }
            }
        }

        private void buttonViewGroup_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            UInt16 u16GroupAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;

            if (bStringToUint16(textBoxViewGroupAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxViewGroupSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxViewGroupDstEp.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxViewGroupGroupAddr.Text, out u16GroupAddr) == true)
                        {
                            sendViewGroup(u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u16GroupAddr);
                        }
                    }
                }
            }
        }

        private void buttonAddGroup_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            UInt16 u16GroupAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8GroupNameLength;
            byte u8GroupNameMaxLength;

            if (bStringToUint16(textBoxAddGroupAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxAddGroupSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxAddGroupDstEp.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxAddGroupGroupAddr.Text, out u16GroupAddr) == true)
                        {
                            if (bStringToUint8(textBoxGroupNameLength.Text, out u8GroupNameLength) == true)
                            {
                                if (bStringToUint8(textBoxGroupNameMaxLength.Text, out u8GroupNameMaxLength) == true)
                                {
                                    sendGroupAdd(u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u16GroupAddr, u8GroupNameLength, u8GroupNameMaxLength, textBoxGroupName.Text);
                                }
                            }
                        }
                    }
                }
            }
        }

        #endregion

        #region on/off cluster button handlers

        private void buttonOnOff_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;            
            byte u8SrcEndPoint;
            byte u8DstEndPoint;

            if (bStringToUint16(textBoxOnOffAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxOnOffSrcEndPoint.Text, out u8SrcEndPoint) == true)
                {                
                    if (bStringToUint8(textBoxOnOffDstEndPoint.Text, out u8DstEndPoint) == true)
                    {
                        sendClusterOnOff((byte)comboBoxOnOffAddrMode.SelectedIndex, u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, (byte)comboBoxOnOffCommand.SelectedIndex);
                    }
                }                
            }            
        }

        private void buttonOnOffTimed_Click(object sender, EventArgs e)
        {

        }
        #endregion

        #region level cluster button handlers

        private void buttonMoveToLevel_Click_1(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            UInt16 u16TransTime;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8Level;

            if (bStringToUint16(textBoxMoveToLevelAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxMoveToLevelSrcEndPoint.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxMoveToLevelDstEndPoint.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint8(textBoxMoveToLevelLevel.Text, out u8Level) == true)
                        {
                            if (bStringToUint16(textBoxMoveToLevelTransTime.Text, out u16TransTime) == true)
                            {
                                sendClusterMoveToLevel((byte)comboBoxMoveToLevelAddrMode.SelectedIndex, u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, (byte)comboBoxMoveToLevelOnOff.SelectedIndex, u8Level, u16TransTime);
                            }
                        }
                    }
                }
            }
        }

        #endregion

        #region identify cluster button handlers

        private void buttonIdSend_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;            
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            UInt16 u16Time;

            if (bStringToUint16(textBoxSendIdAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxSendIdSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxIdSendDstEp.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxIdSendTime.Text, out u16Time) == true)
                        {
                            sendIdentify(u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u16Time);                         
                        }
                    }
                }
            }
        }

        private void buttonIdQuery_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;

            if (bStringToUint16(textBoxIdQueryAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxIdQuerySrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxIdQueryDstEp.Text, out u8DstEndPoint) == true)
                    {
                        sendIdentifyQuery(u16ShortAddr, u8SrcEndPoint, u8DstEndPoint);
                    }
                }
            }
        }

        #endregion

        #region scene cluster button handlers

        private void buttonRemoveScene_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            UInt16 u16GroupId;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8SceneId;

            if (bStringToUint16(textBoxRemoveSceneAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxRemoveSceneSrcEndPoint.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxRemoveSceneDstEndPoint.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxRemoveSceneGroupID.Text, out u16GroupId) == true)
                        {
                            if (bStringToUint8(textBoxRemoveSceneSceneID.Text, out u8SceneId) == true)
                            {
                                sendRemoveScene((byte)comboBoxRemoveSceneAddrMode.SelectedIndex, u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u16GroupId, u8SceneId);
                            }
                        }
                    }
                }
            }
        }

        private void buttonRemoveAllScenes_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            UInt16 u16GroupId;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;

            if (bStringToUint16(textBoxRemoveAllScenesAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxRemoveAllScenesSrcEndPoint.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxRemoveAllScenesDstEndPoint.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxRemoveAllScenesGroupID.Text, out u16GroupId) == true)
                        {
                            sendRemoveAllScenes((byte)comboBoxRemoveAllScenesAddrMode.SelectedIndex, u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u16GroupId);
                        }
                    }
                }
            }
        }

        private void buttonGetSceneMembership_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            UInt16 u16GroupId;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;

            if (bStringToUint16(textBoxGetSceneMembershipAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxGetSceneMembershipSrcEndPoint.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxGetSceneMembershipDstEndPoint.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxGetSceneMembershipGroupID.Text, out u16GroupId) == true)
                        {
                            sendGetSceneMembership((byte)comboBoxGetSceneMembershipAddrMode.SelectedIndex, u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u16GroupId);
                        }
                    }
                }
            }
        }

        private void buttonAddScene_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            UInt16 u16GroupId;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8SceneId;
            UInt16 u16TransTime;
            byte u8NameLen;
            byte u8NameMaxLen;
            UInt16 u16SceneLength;
            string stringSceneData;

            if (bStringToUint16(textBoxAddSceneAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxAddSceneSrcEndPoint.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxAddSceneDstEndPoint.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxAddSceneGroupId.Text, out u16GroupId) == true)
                        {
                            if (bStringToUint8(textBoxAddSceneSceneId.Text, out u8SceneId) == true)
                            {
                                if (checkBoxShowExtension.Checked == true)
                                {
                                    if (bStringToUint16(textBoxAddSceneTransTime.Text, out u16TransTime) == true)
                                    {
                                        if (bStringToUint8(textBoxAddSceneNameLen.Text, out u8NameLen) == true)
                                        {
                                            if (bStringToUint8(textBoxAddSceneMaxNameLen.Text, out u8NameMaxLen) == true)
                                            {
                                                if (bStringToUint16(textBoxAddSceneExtLen.Text, out u16SceneLength) == true)
                                                {
                                                    stringSceneData = textBoxAddSceneData.Text;
                                                    sendAddSceneExtData((byte)comboBoxAddSceneAddrMode.SelectedIndex, u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u16GroupId, u8SceneId, u16TransTime, textBoxAddSceneName.Text, u8NameLen, u8NameMaxLen, u16SceneLength, stringSceneData);
                                                }
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    sendAddScene((byte)comboBoxAddSceneAddrMode.SelectedIndex, u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u16GroupId, u8SceneId);
                                }
                            }
                        }
                    }
                }
            }
        }

        private void buttonViewScene_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            UInt16 u16GroupId;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8SceneId;

            if (bStringToUint16(textBoxViewSceneAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxViewSceneSrcEndPoint.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxViewSceneDstEndPoint.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxViewSceneGroupId.Text, out u16GroupId) == true)
                        {
                            if (bStringToUint8(textBoxViewSceneSceneId.Text, out u8SceneId) == true)
                            {
                                sendViewScene((byte)comboBoxViewSceneAddrMode.SelectedIndex, u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u16GroupId, u8SceneId);
                            }
                        }
                    }
                }
            }
        }

        private void buttonStoreScene_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            UInt16 u16GroupId;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8SceneId;

            if (bStringToUint16(textBoxStoreSceneAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxStoreSceneSrcEndPoint.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxStoreSceneDstEndPoint.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxStoreSceneGroupId.Text, out u16GroupId) == true)
                        {
                            if (bStringToUint8(textBoxStoreSceneSceneId.Text, out u8SceneId) == true)
                            {
                                sendStoreScene((byte)comboBoxStoreSceneAddrMode.SelectedIndex, u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u16GroupId, u8SceneId);
                            }
                        }
                    }
                }
            }
        }

        private void buttonRecallScene_Click_1(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            UInt16 u16GroupId;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8SceneId;

            if (bStringToUint16(textBoxRecallSceneAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxRecallSceneSrcEndPoint.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxRecallSceneDstEndPoint.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxRecallSceneGroupId.Text, out u16GroupId) == true)
                        {
                            if (bStringToUint8(textBoxRecallSceneSceneId.Text, out u8SceneId) == true)
                            {
                                sendRecallScene((byte)comboBoxRecallSceneAddrMode.SelectedIndex, u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u16GroupId, u8SceneId);
                            }
                        }
                    }
                }
            }
        }

        private void buttonDiscoverDevices_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr = 0x0000;
            byte u8StartIndex = 0;

            comboBoxAddressList.Items.Clear();
            sendMgmtLqiRequest(u16ShortAddr, u8StartIndex);
        }

        private void buttonCopyAddr_Click(object sender, EventArgs e)
        {
            textBoxExtAddr.SelectAll();
            textBoxExtAddr.Copy();
        }

        #endregion

        #region color cluster button handlers

        private void buttonMoveToColorTemp_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            UInt16 u16ColorTemp;
            UInt16 u16TransTime;

            if (bStringToUint16(textBoxMoveToColorTempAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxMoveToColorTempSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxMoveToColorTempDstEp.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16Decimal(textBoxMoveToColorTempTemp.Text, out u16ColorTemp) == true)
                        {
                            u16ColorTemp = (UInt16)((UInt32)1000000 / (UInt32)u16ColorTemp);

                            if (bStringToUint16(textBoxMoveToColorTempRate.Text, out u16TransTime) == true)
                            {
                                sendMoveToColorTemp(u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u16ColorTemp, u16TransTime);
                            }
                        }
                    }
                }
            }
        }

        private void buttonMoveToColor_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            UInt16 u16X;
            UInt16 u16Y;
            UInt16 u16Time;

            if (bStringToUint16(textBoxMoveToColorAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxMoveToColorSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxMoveToColorDstEp.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxMoveToColorX.Text, out u16X) == true)
                        {
                            if (bStringToUint16(textBoxMoveToColorY.Text, out u16Y) == true)
                            {
                                if (bStringToUint16(textBoxMoveToColorTime.Text, out u16Time) == true)
                                {
                                    sendMoveToColor(u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u16X, u16Y, u16Time);
                                }
                            }
                        }
                    }
                }
            }            
        }

        private void buttonMoveToHue_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8Hue;
            byte u8Direction;
            UInt16 u16Time;

            if (bStringToUint16(textBoxMoveToHueAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxMoveToHueSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxMoveToHueDstEp.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint8(textBoxMoveToHueHue.Text, out u8Hue) == true)
                        {
                            if (bStringToUint8(textBoxMoveToHueDir.Text, out u8Direction) == true)
                            {
                                if (bStringToUint16(textBoxMoveToHueTime.Text, out u16Time) == true)
                                {
                                    sendMoveToHue(u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u8Hue, u8Direction, u16Time);
                                }
                            }
                        }
                    }
                }
            }
        }

        private void buttonMoveToSat_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8Sat;
            UInt16 u16Time;

            if (bStringToUint16(textBoxMoveToSatAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxMoveToSatSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxMoveToSatDstEp.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint8(textBoxMoveToSatSat.Text, out u8Sat) == true)
                        {
                            if (bStringToUint16(textBoxMoveToSatTime.Text, out u16Time) == true)
                            {
                                sendMoveToSat(u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u8Sat, u16Time);
                            }
                        }
                    }
                }
            }
        }

        #endregion

        #region lock cluster button handlers

        private void buttonLockUnlock_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;

            if (bStringToUint16(textBoxLockUnlockAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxLockUnlockSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxLockUnlockDstEp.Text, out u8DstEndPoint) == true)
                    {
                        sendLockUnlock(u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, (byte)comboBoxLockUnlock.SelectedIndex);                        
                    }
                }
            }
        }

        #endregion

        #region IAS cluster button handlers
  
        private void buttonEnrollResponse_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8ZoneId;

            if (bStringToUint16(textBoxEnrollRspAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxEnrollRspSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxEnrollRspDstEp.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint8(textBoxEnrollRspZone.Text, out u8ZoneId) == true)
                        {
                            sendIASEnrollResponse((byte)comboBoxEnrollRspAddrMode.SelectedIndex, u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, (byte)comboBoxEnrollRspCode.SelectedIndex, u8ZoneId);
                        }
                    }
                }
            }            
        }
        #endregion

        #region touchlink command button handlers

        private void buttonZllTouchlinkFactoryReset_Click(object sender, EventArgs e)
        {
            sendTouchlinkFactoryReset();
        }

        private void buttonZllTouchlinkInitiate_Click(object sender, EventArgs e)
        {
            sendTouchlinkInitiate();
        }

        #endregion

        #region ZLL on/off command button handlers

        private void buttonZllOnOffEffects_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            byte u8EffectGrad;

            if (bStringToUint16(textBoxZllOnOffEffectsAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxZllOnOffEffectsSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxZllOnOffEffectsDstEp.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint8(textBoxZllOnOffEffectsGradient.Text, out u8EffectGrad) == true)
                        {
                            sendZllClusterOnOff(u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, (byte)comboBoxZllOnOffEffectID.SelectedIndex, u8EffectGrad);
                        }
                    }
                }
            }            
        }

        #endregion

        #region ZLL color cluster button handlers

        private void buttonZllMoveToHue_Click(object sender, EventArgs e)
        {
            UInt16 u16ShortAddr;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            UInt16 u16Hue;
            byte u8Direction;
            UInt16 u16Time;

            if (bStringToUint16(textBoxZllMoveToHueAddr.Text, out u16ShortAddr) == true)
            {
                if (bStringToUint8(textBoxZllMoveToHueSrcEp.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxZllMoveToHueDstEp.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxZllMoveToHueHue.Text, out u16Hue) == true)
                        {
                            if (bStringToUint8(textBoxZllMoveToHueDirection.Text, out u8Direction) == true)
                            {
                                if (bStringToUint16(textBoxZllMoveToHueTransTime.Text, out u16Time) == true)
                                {
                                    sendEnhancedMoveToHue(u16ShortAddr, u8SrcEndPoint, u8DstEndPoint, u16Hue, u8Direction, u16Time);
                                }
                            }
                        }
                    }
                }
            }
        }

        #endregion

        #region Poll Control Cluster Button Handlers

        private void buttonSetCheckinRspData_Click(object sender, EventArgs e)
        {
            UInt16 u16PollControlFastPollExpiry = 0;
            if (bStringToUint16(textBoxFastPollExpiryTime.Text, out u16PollControlFastPollExpiry) == true)
            {
                sendPollControlCheckInResponseValues(u16PollControlFastPollExpiry, (byte)comboBoxFastPollEnable.SelectedIndex);
            }
        }

        #endregion

        #region general input handling functions

        private bool bStringToUint8(string inputString, out byte u8Data)
        {
            bool bResult = true;

            if (Byte.TryParse(inputString, NumberStyles.HexNumber, CultureInfo.CurrentCulture, out u8Data) == false)
            {
                // Show error message
                MessageBox.Show("Invalid Parameter");
                bResult = false;
            }
            return bResult;
        }

        private bool bStringToUint16(string inputString, out UInt16 u16Data)
        {
            bool bResult = true;
            
            if (UInt16.TryParse(inputString, NumberStyles.HexNumber, CultureInfo.CurrentCulture, out u16Data) == false)
            {
                // Show error message
                MessageBox.Show("Invalid Parameter");
                bResult = false;
            }
            return bResult;
        }

        private bool bStringToUint16Decimal(string inputString, out UInt16 u16Data)
        {
            bool bResult = true;

            if (UInt16.TryParse(inputString, NumberStyles.Integer, CultureInfo.CurrentCulture, out u16Data) == false)
            {
                // Show error message
                MessageBox.Show("Invalid Parameter");
                bResult = false;
            }
            return bResult;
        }

        private bool bStringToUint32(string inputString, out UInt32 u32Data)
        {
            bool bResult = true;

            if (UInt32.TryParse(inputString, NumberStyles.HexNumber, CultureInfo.CurrentCulture, out u32Data) == false)
            {
                // Show error message
                MessageBox.Show("Invalid Parameter");
                bResult = false;
            }
            return bResult;
        }

        private bool bStringToUint64(string inputString, out UInt64 u64Data)
        {
            bool bResult = true;

            if (UInt64.TryParse(inputString, NumberStyles.HexNumber, CultureInfo.CurrentCulture, out u64Data) == false)
            {
                // Show error message
                MessageBox.Show("Invalid Parameter");
                bResult = false;
            }
            return bResult;
        }

        private bool bStringToUint128(string inputString, out byte[] au8Data)
        {
            bool bResult = true;            
            au8Data = new byte[16];
            
            if (inputString.Length == 32)
            {
                for (int i = 0; i < inputString.Length; i += 2)
                {
                    if (bStringToUint8(inputString.Substring(i, 2), out au8Data[i / 2]) == false)
                    {
                        bResult = false;
                        break;
                    }
                }
            }
            else
            {
                bResult = false;
            }
            return bResult;
        }

        private bool bStringToUint16Array(string inputString, out UInt16[] au16Data)
        {
            bool bResult = true;
            au16Data = new UInt16[8];

            if ((inputString.Length % 4) == 0)
            {
                for (int i = 0; i < inputString.Length; i += 4)
                {
                    if (bStringToUint16(inputString.Substring(i, 4), out au16Data[i / 4]) == false)
                    {
                        bResult = false;
                        break;
                    }
                }
            }
            else
            {
                bResult = false;
            }
            return bResult;
        }

        private void textBoxClearSetTextBlack_MouseClick(object sender, EventArgs e)
        {
            TextBox textBox = sender as TextBox;

            textBox.ForeColor = System.Drawing.Color.Black;
            textBox.Text = "";
        }

        #endregion

        #region command transmit functions

        private void sendBasicResetFactoryDefaultCommand(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint)
        {
            byte[] commandData = null;
            commandData = new byte[32];
            byte u8Len = 0;

            commandData[u8Len++] = u8DstAddrMode; 
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = (byte)u16ShortAddr;
            commandData[u8Len++] = u8SrcEndPoint;
            commandData[u8Len++] = u8DstEndPoint;

            // Transmit command
            transmitCommand(0x0050, u8Len, commandData);
        }

        private void sendMgmtNwkUpdateRequest(byte u8DstAddrMode, UInt16 u16ShortAddr, UInt32 u32ChannelMask, byte u8ScanDuration, byte u8ScanCount, UInt16 u16NwkManangerAddr)
        {
            byte[] commandData = null;
            commandData = new byte[32];
            byte u8Len = 0;

            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = (byte)u16ShortAddr;
            commandData[u8Len++] = (byte)(u32ChannelMask >> 24);
            commandData[u8Len++] = (byte)(u32ChannelMask >> 16);
            commandData[u8Len++] = (byte)(u32ChannelMask >> 8);
            commandData[u8Len++] = (byte)u32ChannelMask;
            commandData[u8Len++] = u8ScanDuration;
            commandData[u8Len++] = u8ScanCount;
            commandData[u8Len++] = (byte)(u16NwkManangerAddr >> 8);
            commandData[u8Len++] = (byte)u16NwkManangerAddr;
         
            // Transmit command
            transmitCommand(0x004A, u8Len, commandData);
        }

        private void sendOneToManyRouteRequest(byte u8CacheRoute, byte u8Radius)
        {
            byte[] commandData = null;
            commandData = new byte[128];
            byte u8Len = 0;

            commandData[u8Len++] = 0; // u8DstAddrMode;
            commandData[u8Len++] = 0; // (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = 0; // (byte)u16ShortAddr;
            commandData[u8Len++] = u8CacheRoute;
            commandData[u8Len++] = u8Radius;

            // Transmit command
            transmitCommand(0x004F, u8Len, commandData);
        }

        private void sendReadReportConfigRequest(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16ClusterID, byte u8DirServerClient, byte u8NbrAttribs, byte u8ManuSpecific, UInt16 u16ManuID, byte u8DirIsRx, UInt16 u16AttribId)
        {
            byte[] commandData = null;
            commandData = new byte[128];
            byte u8Len = 0;

            commandData[u8Len++] = u8DstAddrMode;
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = (byte)u16ShortAddr;
            commandData[u8Len++] = u8SrcEndPoint;
            commandData[u8Len++] = u8DstEndPoint;
            commandData[u8Len++] = (byte)(u16ClusterID >> 8);
            commandData[u8Len++] = (byte)u16ClusterID;
            commandData[u8Len++] = u8DirServerClient;
            commandData[u8Len++] = u8NbrAttribs;
            commandData[u8Len++] = u8ManuSpecific;
            commandData[u8Len++] = (byte)(u16ManuID >> 8);
            commandData[u8Len++] = (byte)u16ManuID;
            commandData[u8Len++] = u8DirIsRx;
            commandData[u8Len++] = (byte)(u16AttribId >> 8);
            commandData[u8Len++] = (byte)u16AttribId;
            
            // Transmit command
            transmitCommand(0x0122, u8Len, commandData);
        }
        
        
        private void sendOtaEndResponse(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, byte u8SeqNbr, UInt32 u32UpgradeTime, UInt32 u32CurrentTime, UInt32 u32FileVersion, UInt16 u16ImageType, UInt16 u16ManuCode)
        {
            byte[] commandData = null;
            commandData = new byte[128];
            byte u8Len = 0;

            // Build command payload   
            commandData[u8Len++] = u8DstAddrMode;
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = (byte)u16ShortAddr;
            commandData[u8Len++] = u8SrcEndPoint;
            commandData[u8Len++] = u8DstEndPoint;
            commandData[u8Len++] = u8SeqNbr;
            commandData[u8Len++] = (byte)(u32UpgradeTime >> 24);
            commandData[u8Len++] = (byte)(u32UpgradeTime >> 16);
            commandData[u8Len++] = (byte)(u32UpgradeTime >> 8);
            commandData[u8Len++] = (byte)u32UpgradeTime;
            commandData[u8Len++] = (byte)(u32CurrentTime >> 24);
            commandData[u8Len++] = (byte)(u32CurrentTime >> 16);
            commandData[u8Len++] = (byte)(u32CurrentTime >> 8);
            commandData[u8Len++] = (byte)u32CurrentTime;
            commandData[u8Len++] = (byte)(u32FileVersion >> 24);
            commandData[u8Len++] = (byte)(u32FileVersion >> 16);
            commandData[u8Len++] = (byte)(u32FileVersion >> 8);
            commandData[u8Len++] = (byte)u32FileVersion;
            commandData[u8Len++] = (byte)(u16ImageType >> 8);
            commandData[u8Len++] = (byte)u16ImageType;
            commandData[u8Len++] = (byte)(u16ManuCode >> 8);
            commandData[u8Len++] = (byte)u16ManuCode;

            // Transmit command
            transmitCommand(0x0504, u8Len, commandData);
        }
        

        private void sendOtaBlock(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, byte u8SeqNbr, byte u8Status, UInt32 u32FileOffset, UInt32 u32FileVersion, UInt16 u16ImageType, UInt16 u16ManuCode, byte u8DataSize, byte[] au8Data)
        {
            byte[] commandData = null;
            commandData = new byte[128];
            byte u8Len = 0;

            // Build command payload   
            commandData[u8Len++] = u8DstAddrMode;
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = (byte)u16ShortAddr;
            commandData[u8Len++] = u8SrcEndPoint;
            commandData[u8Len++] = u8DstEndPoint;
            commandData[u8Len++] = u8SeqNbr;
            commandData[u8Len++] = u8Status;
            commandData[u8Len++] = (byte)(u32FileOffset >> 24);
            commandData[u8Len++] = (byte)(u32FileOffset >> 16);
            commandData[u8Len++] = (byte)(u32FileOffset >> 8);
            commandData[u8Len++] = (byte)u32FileOffset;
            commandData[u8Len++] = (byte)(u32FileVersion >> 24);
            commandData[u8Len++] = (byte)(u32FileVersion >> 16);
            commandData[u8Len++] = (byte)(u32FileVersion >> 8);
            commandData[u8Len++] = (byte)u32FileVersion;
            commandData[u8Len++] = (byte)(u16ImageType >> 8);
            commandData[u8Len++] = (byte)u16ImageType;
            commandData[u8Len++] = (byte)(u16ManuCode >> 8);
            commandData[u8Len++] = (byte)u16ManuCode;
            commandData[u8Len++] = u8DataSize;

            byte i;
            for (i = 0; i < u8DataSize; i++)
            {
                commandData[u8Len++] = au8Data[u32FileOffset + i];
            }

            // Transmit command
            transmitCommand(0x0502, u8Len, commandData);
        }

        private void sendOtaSetWaitForDataParams(byte u8DstAddrMode, UInt16 u16TargetAddr, byte u8SrcEndPoint, byte u8DstEndPoint, byte u8SeqNbr, byte u8Status, UInt32 u32CurrentTime, UInt32 u32RequestTime, UInt16 u16BlockDelay)
        {
            byte[] commandData = null;
            commandData = new byte[32];
            byte u8Len = 0;

            // Build command payload   
            commandData[u8Len++] = u8DstAddrMode;
            commandData[u8Len++] = (byte)(u16TargetAddr >> 8);
            commandData[u8Len++] = (byte)u16TargetAddr;
            commandData[u8Len++] = u8SrcEndPoint;
            commandData[u8Len++] = u8DstEndPoint;
            commandData[u8Len++] = u8SeqNbr;
            commandData[u8Len++] = u8Status;
            commandData[u8Len++] = (byte)(u32CurrentTime >> 24);
            commandData[u8Len++] = (byte)(u32CurrentTime >> 16);
            commandData[u8Len++] = (byte)(u32CurrentTime >> 8);
            commandData[u8Len++] = (byte)u32CurrentTime;
            commandData[u8Len++] = (byte)(u32RequestTime >> 24);
            commandData[u8Len++] = (byte)(u32RequestTime >> 16);
            commandData[u8Len++] = (byte)(u32RequestTime >> 8);
            commandData[u8Len++] = (byte)u32RequestTime;
            commandData[u8Len++] = (byte)(u16BlockDelay >> 8);
            commandData[u8Len++] = (byte)u16BlockDelay;

            // Transmit command
            transmitCommand(0x0506, u8Len, commandData);
        }

        private void sendOtaImageNotify(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, byte u8NotifyType, UInt32 u32FileVersion, UInt16 u16ImageType, UInt16 u16ManuCode, byte u8Jitter)
        {
            byte[] commandData = null;
            commandData = new byte[16];
            byte u8Len = 0;

            // Build command payload   
            commandData[u8Len++] = u8DstAddrMode;
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = (byte)u16ShortAddr;
            commandData[u8Len++] = u8SrcEndPoint;
            commandData[u8Len++] = u8DstEndPoint;
            commandData[u8Len++] = u8NotifyType;
            commandData[u8Len++] = (byte)(u32FileVersion >> 24);
            commandData[u8Len++] = (byte)(u32FileVersion >> 16);
            commandData[u8Len++] = (byte)(u32FileVersion >> 8);
            commandData[u8Len++] = (byte)u32FileVersion;
            commandData[u8Len++] = (byte)(u16ImageType >> 8);
            commandData[u8Len++] = (byte)u16ImageType;
            commandData[u8Len++] = (byte)(u16ManuCode >> 8);
            commandData[u8Len++] = (byte)u16ManuCode;
            commandData[u8Len++] = u8Jitter;
  
            // Transmit command
            transmitCommand(0x0505, u8Len, commandData);
        }

        private void sendOtaLoadNewImage(byte u8DstAddrMode, UInt16 u16ShortAddr, UInt32 u32FileIdentifier, UInt16 u16HeaderVersion, UInt16 u16HeaderLength, UInt16 u16HeaderControlField, UInt16 u16ManufacturerCode, UInt16 u16ImageType, UInt32 u32FileVersion, UInt16 u16StackVersion, byte[] au8HeaderString, UInt32 u32TotalImage, byte u8SecurityCredVersion, UInt64 u64UpgradeFileDest, UInt16 u16MinimumHwVersion, UInt16 u16MaxHwVersion)
        {
            byte[] commandData = null;
            commandData = new byte[72];
            byte u8Len = 0;

            // Build command payload   
            commandData[u8Len++] = u8DstAddrMode;
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = (byte)u16ShortAddr;
            commandData[u8Len++] = (byte)(u32FileIdentifier >> 24);
            commandData[u8Len++] = (byte)(u32FileIdentifier >> 16);
            commandData[u8Len++] = (byte)(u32FileIdentifier >> 8);
            commandData[u8Len++] = (byte)u32FileIdentifier;
            commandData[u8Len++] = (byte)(u16HeaderVersion >> 8);
            commandData[u8Len++] = (byte)u16HeaderVersion;
            commandData[u8Len++] = (byte)(u16HeaderLength >> 8);
            commandData[u8Len++] = (byte)u16HeaderLength;
            commandData[u8Len++] = (byte)(u16HeaderControlField >> 8);
            commandData[u8Len++] = (byte)u16HeaderControlField;
            commandData[u8Len++] = (byte)(u16ManufacturerCode >> 8);
            commandData[u8Len++] = (byte)u16ManufacturerCode;
            commandData[u8Len++] = (byte)(u16ImageType >> 8);
            commandData[u8Len++] = (byte)u16ImageType;
            commandData[u8Len++] = (byte)(u32FileVersion >> 24);
            commandData[u8Len++] = (byte)(u32FileVersion >> 16);
            commandData[u8Len++] = (byte)(u32FileVersion >> 8);
            commandData[u8Len++] = (byte)u32FileVersion;
            commandData[u8Len++] = (byte)(u16StackVersion >> 8);
            commandData[u8Len++] = (byte)u16StackVersion;

            if (au8HeaderString != null)
            {
                byte i;
                for (i = 0; i < 32; i++)
                {
                    commandData[u8Len++] = au8HeaderString[i];
                }
            }

            commandData[u8Len++] = (byte)(u32TotalImage >> 24);
            commandData[u8Len++] = (byte)(u32TotalImage >> 16);
            commandData[u8Len++] = (byte)(u32TotalImage >> 8);
            commandData[u8Len++] = (byte)u32TotalImage;
            commandData[u8Len++] = u8SecurityCredVersion;
            commandData[u8Len++] = (byte)(u64UpgradeFileDest >> 56);
            commandData[u8Len++] = (byte)(u64UpgradeFileDest >> 48);
            commandData[u8Len++] = (byte)(u64UpgradeFileDest >> 40);
            commandData[u8Len++] = (byte)(u64UpgradeFileDest >> 32);
            commandData[u8Len++] = (byte)(u64UpgradeFileDest >> 24);
            commandData[u8Len++] = (byte)(u64UpgradeFileDest >> 16);
            commandData[u8Len++] = (byte)(u64UpgradeFileDest >> 8);
            commandData[u8Len++] = (byte)u64UpgradeFileDest;
            commandData[u8Len++] = (byte)(u16MinimumHwVersion >> 8);
            commandData[u8Len++] = (byte)u16MinimumHwVersion;
            commandData[u8Len++] = (byte)(u16MaxHwVersion >> 8);
            commandData[u8Len++] = (byte)u16MaxHwVersion;
            
            // Transmit command
            transmitCommand(0x0500, u8Len, commandData);
        }

        private void sendIASEnrollResponse(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, byte u8Code, byte u8ZoneId)
        {
            byte[] commandData = null;
            commandData = new byte[7];
            byte u8Len = 7;

            // Build command payload   
            commandData[0] = u8DstAddrMode; 
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = u8Code;
            commandData[6] = u8ZoneId;

            // Transmit command
            transmitCommand(0x0400, u8Len, commandData);
        }

        private void sendMoveToColorTemp(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16ColorTemp, UInt16 u16TransTime)
        {
            byte[] commandData = null;
            commandData = new byte[9];
            byte u8Len = 9;

            // Build command payload   
            commandData[0] = 0x02; // Short address mode
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = (byte)(u16ColorTemp >> 8);
            commandData[6] = (byte)u16ColorTemp;
            commandData[7] = (byte)(u16TransTime >> 8);
            commandData[8] = (byte)u16TransTime;

            // Transmit command
            transmitCommand(0x00C0, u8Len, commandData);
        }

        private void sendWriteAttribRequest(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16ClusterID, byte u8Direction, byte u8ManuSpecific, UInt16 u16ManuID, byte u8AttribCount, UInt16 u16AttribID, byte u8AttribType, byte[] au8Data, byte u8DataLen)
        {
            byte[] commandData = null;
            commandData = new byte[32];
            int u8Len = 0;

            // Build command payload   
            commandData[u8Len++] = 0x02; // Short address mode
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = (byte)u16ShortAddr;
            commandData[u8Len++] = u8SrcEndPoint;
            commandData[u8Len++] = u8DstEndPoint;
            commandData[u8Len++] = (byte)(u16ClusterID >> 8);
            commandData[u8Len++] = (byte)u16ClusterID;
            commandData[u8Len++] = u8Direction;
            commandData[u8Len++] = u8ManuSpecific;
            commandData[u8Len++] = (byte)(u16ManuID >> 8);
            commandData[u8Len++] = (byte)u16ManuID;
            commandData[u8Len++] = u8AttribCount;
            commandData[u8Len++] = (byte)(u16AttribID >> 8);
            commandData[u8Len++] = (byte)u16AttribID;
            commandData[u8Len++] = u8AttribType;

            int i;
            for (i = 0; i < u8DataLen; i++)
            {
                commandData[u8Len] = au8Data[i];
                u8Len++;
            }

            /* Need to re-size the array because if we send more data, 
             * the control bridge will convert it to another write attribute */
            Array.Resize(ref commandData, u8Len); 

            // Transmit command
            transmitCommand(0x0110, u8Len, commandData);
        }

        private void sendRemoveScene(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16GroupId, byte u8SceneId)
        {
            byte[] commandData = null;
            commandData = new byte[32];
            byte u8Len = 0;

            // Build command payload   
            commandData[u8Len++] = u8DstAddrMode;
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = (byte)u16ShortAddr;
            commandData[u8Len++] = u8SrcEndPoint;
            commandData[u8Len++] = u8DstEndPoint;
            commandData[u8Len++] = (byte)(u16GroupId >> 8);
            commandData[u8Len++] = (byte)u16GroupId;
            commandData[u8Len++] = u8SceneId;

            // Transmit command
            transmitCommand(0x00A2, u8Len, commandData);
        }

        private void sendRemoveAllScenes(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16GroupId)
        {
            byte[] commandData = null;
            commandData = new byte[32];
            byte u8Len = 0;

            // Build command payload   
            commandData[u8Len++] = u8DstAddrMode;               // 0 
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);   // 1
            commandData[u8Len++] = (byte)u16ShortAddr;          // 2
            commandData[u8Len++] = u8SrcEndPoint;               // 3
            commandData[u8Len++] = u8DstEndPoint;               // 4
            commandData[u8Len++] = (byte)(u16GroupId >> 8);     // 5
            commandData[u8Len++] = (byte)u16GroupId;            // 6

            // Transmit command
            transmitCommand(0x00A3, u8Len, commandData);
        }

        private void sendGetSceneMembership(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16GroupId)
        {
            byte[] commandData = null;
            commandData = new byte[32];
            byte u8Len = 0;

            // Build command payload   
            commandData[u8Len++] = u8DstAddrMode;               // 0 
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);   // 1
            commandData[u8Len++] = (byte)u16ShortAddr;          // 2
            commandData[u8Len++] = u8SrcEndPoint;               // 3
            commandData[u8Len++] = u8DstEndPoint;               // 4
            commandData[u8Len++] = (byte)(u16GroupId >> 8);     // 5
            commandData[u8Len++] = (byte)u16GroupId;            // 6

            // Transmit command
            transmitCommand(0x00A6, u8Len, commandData);
        }

        private void sendAddSceneExtData(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16GroupId, byte u8SceneId, UInt16 u16TransTime, String sName, byte u8NameLen, byte u8NameMaxLen, UInt16 u16SceneLength, string stringSceneData)
        {
            byte[] commandData = null;
            commandData = new byte[32];
            byte u8Len = 0;
            String stringData = "";

            // Build command payload   
            commandData[u8Len++] = u8DstAddrMode;               // 0 
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);   // 1
            commandData[u8Len++] = (byte)u16ShortAddr;          // 2
            commandData[u8Len++] = u8SrcEndPoint;               // 3
            commandData[u8Len++] = u8DstEndPoint;               // 4
            commandData[u8Len++] = (byte)(u16GroupId >> 8);     // 5
            commandData[u8Len++] = (byte)u16GroupId;            // 6
            commandData[u8Len++] = u8SceneId;                   // 7
            commandData[u8Len++] = (byte)(u16TransTime >> 8);   // 8
            commandData[u8Len++] = (byte)u16TransTime;          // 9
            commandData[u8Len++] = u8NameLen;                   // 10
            commandData[u8Len++] = u8NameMaxLen;                // 11

            char[] u8Array = sName.ToCharArray();

            for (int i = 0; i < sName.ToCharArray().Length; i++)
            {
                commandData[u8Len + i] = (byte)u8Array[i];
            }

            u8Len += u8NameMaxLen;

            commandData[u8Len++] = (byte)(u16SceneLength >> 8); // 12+=u8NameLen
            commandData[u8Len++] = (byte)u16SceneLength;        // 13+=u8NameLen

            stringData = stringSceneData.Replace(" ", "");
            stringData = stringSceneData.Replace(":", "");

            for (int i = 0; i < stringData.Length; i += 2)
            {
                Array.Resize(ref commandData, u8Len + 1);
                commandData[u8Len++] = (byte)Convert.ToInt32(stringData.ToCharArray()[i].ToString() + stringData.ToCharArray()[i + 1].ToString(), 16);
            }

            // Transmit command
            transmitCommand(0x00A1, u8Len, commandData);
        }

        private void sendAddScene(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16GroupId, byte u8SceneId)
        {
            byte[] commandData = null;
            commandData = new byte[32];
            byte u8Len = 0;

            // Build command payload   
            commandData[u8Len++] = u8DstAddrMode;               // 0 
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);   // 1
            commandData[u8Len++] = (byte)u16ShortAddr;          // 2
            commandData[u8Len++] = u8SrcEndPoint;               // 3
            commandData[u8Len++] = u8DstEndPoint;               // 4
            commandData[u8Len++] = (byte)(u16GroupId >> 8);     // 5
            commandData[u8Len++] = (byte)u16GroupId;            // 6
            commandData[u8Len++] = u8SceneId;                   // 7

            // Transmit command
            transmitCommand(0x00A1, u8Len, commandData);
        }

        private void sendViewScene(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16GroupId, byte u8SceneId)
        {
            byte[] commandData = null;
            commandData = new byte[8];
            byte u8Len = 8;
        
            // Build command payload   
            commandData[0] = u8DstAddrMode; 
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = (byte)(u16GroupId >> 8);
            commandData[6] = (byte)u16GroupId;
            commandData[7] = u8SceneId;

            // Transmit command
            transmitCommand(0x00A0, u8Len, commandData);
        }

        private void sendStoreScene(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16GroupId, byte u8SceneId)
        {
            byte[] commandData = null;
            commandData = new byte[8];
            byte u8Len = 8;

            // Build command payload   
            commandData[0] = u8DstAddrMode;
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = (byte)(u16GroupId >> 8);
            commandData[6] = (byte)u16GroupId;
            commandData[7] = u8SceneId;

            // Transmit command
            transmitCommand(0x00A4, u8Len, commandData);
        }

        private void sendRecallScene(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16GroupId, byte u8SceneId)
        {
            byte[] commandData = null;
            commandData = new byte[8];
            byte u8Len = 8;

            // Build command payload   
            commandData[0] = u8DstAddrMode;
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = (byte)(u16GroupId >> 8);
            commandData[6] = (byte)u16GroupId;
            commandData[7] = u8SceneId;

            // Transmit command
            transmitCommand(0x00A5, u8Len, commandData);
        }

        private void sendUnBindRequest(UInt64 u64TargetExtAddr, byte u8TargetEndPoint, UInt16 u16ClusterID, byte u8DstAddrMode, UInt64 u64DstAddr, byte u8DstEndPoint)
        {
            byte[] commandData = null;
            commandData = new byte[32];
            byte u8Len = 0;

            // Build command payload   
            commandData[u8Len++] = (byte)(u64TargetExtAddr >> 56);
            commandData[u8Len++] = (byte)(u64TargetExtAddr >> 48);
            commandData[u8Len++] = (byte)(u64TargetExtAddr >> 40);
            commandData[u8Len++] = (byte)(u64TargetExtAddr >> 32);
            commandData[u8Len++] = (byte)(u64TargetExtAddr >> 24);
            commandData[u8Len++] = (byte)(u64TargetExtAddr >> 16);
            commandData[u8Len++] = (byte)(u64TargetExtAddr >> 8);
            commandData[u8Len++] = (byte)u64TargetExtAddr;
            commandData[u8Len++] = u8TargetEndPoint;
            commandData[u8Len++] = (byte)(u16ClusterID >> 8);
            commandData[u8Len++] = (byte)u16ClusterID;
            commandData[u8Len++] = u8DstAddrMode;

            if (u8DstAddrMode == 3)
            {
                commandData[u8Len++] = (byte)(u64DstAddr >> 56);
                commandData[u8Len++] = (byte)(u64DstAddr >> 48);
                commandData[u8Len++] = (byte)(u64DstAddr >> 40);
                commandData[u8Len++] = (byte)(u64DstAddr >> 32);
                commandData[u8Len++] = (byte)(u64DstAddr >> 24);
                commandData[u8Len++] = (byte)(u64DstAddr >> 16);
                commandData[u8Len++] = (byte)(u64DstAddr >> 8);
                commandData[u8Len++] = (byte)u64DstAddr;
                commandData[u8Len++] = u8DstEndPoint;
            }
            else
            {
                commandData[u8Len++] = (byte)(u64DstAddr >> 8);
                commandData[u8Len++] = (byte)u64DstAddr;
                commandData[u8Len++] = u8DstEndPoint;
            }

            // Transmit command
            transmitCommand(0x0031, u8Len, commandData);
        }

        private void sendBindRequest(UInt64 u64TargetExtAddr, byte u8TargetEndPoint, UInt16 u16ClusterID, byte u8DstAddrMode, UInt64 u64DstAddr, byte u8DstEndPoint)
        {
            byte[] commandData = null;
            commandData = new byte[32];
            byte u8Len = 0;

            // Build command payload   
            commandData[u8Len++] = (byte)(u64TargetExtAddr >> 56);
            commandData[u8Len++] = (byte)(u64TargetExtAddr >> 48);
            commandData[u8Len++] = (byte)(u64TargetExtAddr >> 40);
            commandData[u8Len++] = (byte)(u64TargetExtAddr >> 32);
            commandData[u8Len++] = (byte)(u64TargetExtAddr >> 24);
            commandData[u8Len++] = (byte)(u64TargetExtAddr >> 16);
            commandData[u8Len++] = (byte)(u64TargetExtAddr >> 8);
            commandData[u8Len++] = (byte)u64TargetExtAddr;
            commandData[u8Len++] = u8TargetEndPoint;
            commandData[u8Len++] = (byte)(u16ClusterID >> 8);
            commandData[u8Len++] = (byte)u16ClusterID;
            commandData[u8Len++] = u8DstAddrMode;

            if (u8DstAddrMode == 3)
            {
                commandData[u8Len++] = (byte)(u64DstAddr >> 56);
                commandData[u8Len++] = (byte)(u64DstAddr >> 48);
                commandData[u8Len++] = (byte)(u64DstAddr >> 40);
                commandData[u8Len++] = (byte)(u64DstAddr >> 32);
                commandData[u8Len++] = (byte)(u64DstAddr >> 24);
                commandData[u8Len++] = (byte)(u64DstAddr >> 16);
                commandData[u8Len++] = (byte)(u64DstAddr >> 8);
                commandData[u8Len++] = (byte)u64DstAddr;
                commandData[u8Len++] = u8DstEndPoint;
            }
            else
            {
                commandData[u8Len++] = (byte)(u64DstAddr >> 8);
                commandData[u8Len++] = (byte)u64DstAddr;
            }
            
            // Transmit command
            transmitCommand(0x0030, u8Len, commandData);
        }

        private void sendConfigReportRequest(byte u8DstAddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16ClusterID, byte u8ReportDirection, byte u8AttribDirection, byte u8AttribType, UInt16 u16AttribId, UInt16 u16MinInterval, UInt16 u16MaxInterval, UInt16 u16TimeOut, UInt64 u64Change)        
        {
            byte[] commandData = null;
            commandData = new byte[30];
            byte u8Len = 0;

            // Build command payload   
            commandData[u8Len++] = u8DstAddrMode;
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = (byte)u16ShortAddr;
            commandData[u8Len++] = u8SrcEndPoint;
            commandData[u8Len++] = u8DstEndPoint;
            commandData[u8Len++] = (byte)(u16ClusterID >> 8);
            commandData[u8Len++] = (byte)u16ClusterID;
            commandData[u8Len++] = u8ReportDirection;
            commandData[u8Len++] = 0; // ManuSpecific
            commandData[u8Len++] = 0; // ManuID
            commandData[u8Len++] = 0; // ManuID
            commandData[u8Len++] = 1; // Number of attributes

            commandData[u8Len++] = u8AttribDirection;
            commandData[u8Len++] = u8AttribType;
            commandData[u8Len++] = (byte)(u16AttribId >> 8);
            commandData[u8Len++] = (byte)u16AttribId; ;
            commandData[u8Len++] = (byte)(u16MinInterval >> 8);
            commandData[u8Len++] = (byte)u16MinInterval;
            commandData[u8Len++] = (byte)(u16MaxInterval >> 8);
            commandData[u8Len++] = (byte)u16MaxInterval;
            commandData[u8Len++] = (byte)(u16TimeOut >> 8); ;
            commandData[u8Len++] = (byte)u16TimeOut;

            if (u8AttribType >= 0x20 &&
                u8AttribType <= 0x2f)
            {
                switch (u8AttribType)
                {
                    case 0x20:
                    case 0x28:
                        commandData[u8Len++] = (byte)(u64Change);
                        break;
                    case 0x21:
                    case 0x29:
                        commandData[u8Len++] = (byte)(u64Change >> 8);
                        commandData[u8Len++] = (byte)(u64Change);
                        break;
                    case 0x22:
                    case 0x2a:
                        commandData[u8Len++] = (byte)(u64Change >> 16);
                        commandData[u8Len++] = (byte)(u64Change >> 8);
                        commandData[u8Len++] = (byte)(u64Change);
                        break;
                    case 0x23:
                    case 0x2b:
                        
                        commandData[u8Len++] = (byte)(u64Change >> 24);
                        commandData[u8Len++] = (byte)(u64Change >> 16);                        
                        commandData[u8Len++] = (byte)(u64Change >> 8);
                        commandData[u8Len++] = (byte)(u64Change);
                        break;
                    case 0x24:
                    case 0x2c:                        
                        commandData[u8Len++] = (byte)(u64Change >> 32);
                        commandData[u8Len++] = (byte)(u64Change >> 24);                        
                        commandData[u8Len++] = (byte)(u64Change >> 16);
                        commandData[u8Len++] = (byte)(u64Change >> 8);
                        commandData[u8Len++] = (byte)(u64Change);
                        break;
                    case 0x25:
                    case 0x2d:                        
                        commandData[u8Len++] = (byte)(u64Change >> 40);
                        commandData[u8Len++] = (byte)(u64Change >> 32);
                        commandData[u8Len++] = (byte)(u64Change >> 24);
                        commandData[u8Len++] = (byte)(u64Change >> 16);
                        commandData[u8Len++] = (byte)(u64Change >> 8);
                        commandData[u8Len++] = (byte)(u64Change);                  
                                               
                        break;
                    case 0x26:
                    case 0x2e:
                        
                        commandData[u8Len++] = (byte)(u64Change >> 48);
                        commandData[u8Len++] = (byte)(u64Change >> 40);
                        commandData[u8Len++] = (byte)(u64Change >> 32);
                        commandData[u8Len++] = (byte)(u64Change >> 24);
                        commandData[u8Len++] = (byte)(u64Change >> 16);
                        commandData[u8Len++] = (byte)(u64Change >> 8);
                        commandData[u8Len++] = (byte)(u64Change);
                        break;
                    case 0x27:
                    case 0x2f:
                        commandData[u8Len++] = (byte)(u64Change >> 56);
                        commandData[u8Len++] = (byte)(u64Change >> 48);
                        commandData[u8Len++] = (byte)(u64Change >> 40);
                        commandData[u8Len++] = (byte)(u64Change >> 32);
                        commandData[u8Len++] = (byte)(u64Change >> 24);
                        commandData[u8Len++] = (byte)(u64Change >> 16);
                        commandData[u8Len++] = (byte)(u64Change >> 8);
                        commandData[u8Len++] = (byte)(u64Change);       
                        break;
                    default:
                        break;
                }
                
            }
            else
            {
                /* WARNING : We should not be sent anything from the higher layer as there should be no reportable change field
                 * If we do get something for this record it's an error and the rest of the records will be all wrong.
                 *  */
            }
            // Transmit command
            transmitCommand(0x0120, u8Len, commandData);

            
        }

        private void sendDiscoverCommandsRequest(byte u8AddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16ClusterID, byte u8DirectionIsServerToClient, byte u8CommandId, byte u8ManuSpecific, UInt16 u16ManuID, byte u8MaxCommands, byte u8IsGenerated)
        {
            byte[] commandData = null;
            commandData = new byte[13];
            byte u8Len = 0;

            // Build command payload   
            commandData[u8Len++] = u8AddrMode;
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = (byte)u16ShortAddr;
            commandData[u8Len++] = u8SrcEndPoint;
            commandData[u8Len++] = u8DstEndPoint;
            commandData[u8Len++] = (byte)(u16ClusterID >> 8);
            commandData[u8Len++] = (byte)u16ClusterID;
            commandData[u8Len++] = u8DirectionIsServerToClient;
            commandData[u8Len++] = u8CommandId;
            commandData[u8Len++] = u8ManuSpecific;
            commandData[u8Len++] = (byte)(u16ManuID >> 8);
            commandData[u8Len++] = (byte)u16ManuID;
            commandData[u8Len++] = u8MaxCommands;

            if (u8IsGenerated == 0)
            {
                // Transmit command
                transmitCommand(0x0150, u8Len, commandData);
            }
            else
            {
                // Transmit command
                transmitCommand(0x0160, u8Len, commandData);
            }
        }

        private void sendRawDataCommandsRequest(byte u8AddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16ProfileID, UInt16 u16ClusterID, byte u8SecurityMode, byte u8Radius, String stringRawData)
        {
            byte[] commandData = null;
            commandData = new byte[12];
            byte u8Len = 0;
            String stringData = "";

            // Build command payload   
            commandData[u8Len++] = u8AddrMode;
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = (byte)u16ShortAddr;
            commandData[u8Len++] = u8SrcEndPoint;
            commandData[u8Len++] = u8DstEndPoint;
            commandData[u8Len++] = (byte)(u16ClusterID >> 8);
            commandData[u8Len++] = (byte)u16ClusterID;
            commandData[u8Len++] = (byte)(u16ProfileID >> 8);
            commandData[u8Len++] = (byte)u16ProfileID;
            commandData[u8Len++] = u8SecurityMode;
            commandData[u8Len++] = u8Radius;

            stringData = stringRawData.Replace(" ", "");
            stringData = stringRawData.Replace(":", "");

            commandData[u8Len++] = (byte)(stringData.Length/2);

            for (int i = 0; i < stringData.Length; i += 2)
            {
                Array.Resize(ref commandData, u8Len + 1);
                commandData[u8Len++] = (byte)Convert.ToInt32(stringData.ToCharArray()[i].ToString() + stringData.ToCharArray()[i + 1].ToString(), 16);
            }
            
            // Transmit command
            transmitCommand(0x0530, u8Len, commandData);
            
        }

        private void sendDiscoverAttributesRequest(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16ClusterID, UInt16 u16StartAttrib, byte u8Direction, byte u8ManuSpecific, UInt16 u16ManuID, byte u8AttribsMax, byte u8Extended)
        {
            byte[] commandData = null;
            commandData = new byte[14];
            byte u8Len = 14;

            // Build command payload   
            commandData[0]  = 0x02; // Short address mode
            commandData[1]  = (byte)(u16ShortAddr >> 8);
            commandData[2]  = (byte)u16ShortAddr;
            commandData[3]  = u8SrcEndPoint;
            commandData[4]  = u8DstEndPoint;
            commandData[5]  = (byte)(u16ClusterID >> 8);
            commandData[6]  = (byte)u16ClusterID;
            commandData[7]  = (byte)(u16StartAttrib >> 8);
            commandData[8]  = (byte)u16StartAttrib;
            commandData[9]  = u8Direction;
            commandData[10] = u8ManuSpecific;
            commandData[11] = (byte)(u16ManuID >> 8);
            commandData[12] = (byte)u16ManuID;
            commandData[13] = u8AttribsMax;

            // Transmit command
            if (u8Extended == 0)
            {
                transmitCommand(0x0140, u8Len, commandData);
            }
            else
            {
                transmitCommand(0x0141, u8Len, commandData);
            }
        }

        /*private void sendReadAllAttribRequest(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16ClusterID, byte u8Direction, byte u8ManuSpecific, UInt16 u16ManuID)
        *{
        *    byte[] commandData = null;
        *    commandData = new byte[11];
        *    byte u8Len = 11;
        *
        *    // Build command payload   
        *    commandData[0] = 0x02; // Short address mode
        *    commandData[1] = (byte)(u16ShortAddr >> 8);
        *    commandData[2] = (byte)u16ShortAddr;
        *    commandData[3] = u8SrcEndPoint;
        *    commandData[4] = u8DstEndPoint;
        *    commandData[5] = (byte)(u16ClusterID >> 8);
        *    commandData[6] = (byte)u16ClusterID;
        *    commandData[7] = u8Direction;
        *    commandData[8] = u8ManuSpecific;
        *    commandData[9] = (byte)(u16ManuID >> 8);
        *    commandData[10] = (byte)u16ManuID;
        *
        *    // Transmit command
        *    transmitCommand(0x0130, u8Len, commandData);
        }*/

        private void sendOOBCommissioningData(UInt64 u64AddrData, string stringkeydata)
        {
            byte[] commandData = null;
            commandData = new byte[24];
            byte u8Len = 0;
            String stringData = "";

            // Build command payload
            commandData[u8Len++] = (byte)(u64AddrData >> 56);  //0
            commandData[u8Len++] = (byte)(u64AddrData >> 48);  //1
            commandData[u8Len++] = (byte)(u64AddrData >> 40);   //2
            commandData[u8Len++] = (byte)(u64AddrData >> 32);   //3
            commandData[u8Len++] = (byte)(u64AddrData >> 24);   //4
            commandData[u8Len++] = (byte)(u64AddrData >> 16);   //5
            commandData[u8Len++] = (byte)(u64AddrData >> 8);    //6
            commandData[u8Len++] = (byte)u64AddrData;           //7

            stringData = stringkeydata.Replace(" ", "");
            stringData = stringkeydata.Replace(":", "");

            for (int i = 0; i < stringData.Length; i+=2)
            {
                commandData[u8Len++] = (byte)Convert.ToInt32(stringData.ToCharArray()[i].ToString() + stringData.ToCharArray()[i + 1].ToString(), 16);  //8-23
            }

            // Transmit command
            transmitCommand(0x0029, u8Len, commandData);
            
        }

        private void sendReadAttribRequest(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16ClusterID, byte u8Direction, byte u8ManuSpecific, UInt16 u16ManuID, byte u8AttribCount, UInt16 u16AttribID1)
        {
            byte[] commandData = null;
            commandData = new byte[14];
            byte u8Len = 0;

            // Build command payload   
            commandData[u8Len++]  = 0x02; // Short address mode
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = (byte)u16ShortAddr;
            commandData[u8Len++] = u8SrcEndPoint;
            commandData[u8Len++] = u8DstEndPoint;
            commandData[u8Len++] = (byte)(u16ClusterID >> 8);
            commandData[u8Len++] = (byte)u16ClusterID;
            commandData[u8Len++] = u8Direction;
            commandData[u8Len++] = u8ManuSpecific;
            commandData[u8Len++] = (byte)(u16ManuID >> 8);
            commandData[u8Len++] = (byte)u16ManuID;
            commandData[u8Len++] = u8AttribCount;
            commandData[u8Len++] = (byte)(u16AttribID1 >> 8);
            commandData[u8Len++] = (byte)u16AttribID1;

            // Transmit command
            transmitCommand(0x0100, u8Len, commandData);
        }

        private void sendLockUnlock(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, byte u8LockUnlock)
        {            
            byte[] commandData = null;
            commandData = new byte[6];

            // Build command payload   
            commandData[0] = 0x02; // Short address mode
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = u8LockUnlock;

            // Transmit command
            transmitCommand(0x00F0, 6, commandData);
        }

        private void sendNwkAddrRequest(UInt16 u16TargetAddr, UInt64 u64ExtAddr, byte u8Type, byte u8StartIndex)
        {
            byte[] commandData = null;
            commandData = new byte[12];

            // Build command payload            
            commandData[0] = (byte)(u16TargetAddr >> 8);
            commandData[1] = (byte)u16TargetAddr;
            commandData[2] = (byte)(u64ExtAddr >> 56);
            commandData[3] = (byte)(u64ExtAddr >> 48);
            commandData[4] = (byte)(u64ExtAddr >> 40);
            commandData[5] = (byte)(u64ExtAddr >> 32);
            commandData[6] = (byte)(u64ExtAddr >> 24);
            commandData[7] = (byte)(u64ExtAddr >> 16);
            commandData[8] = (byte)(u64ExtAddr >> 8);
            commandData[9] = (byte)u64ExtAddr;            
            commandData[10] = u8Type;
            commandData[11] = u8StartIndex;

            // Transmit command
            transmitCommand(0x0040, 12, commandData);
        }

        private void sendIeeeAddrRequest(UInt16 u16TargetAddr, UInt16 u16ShortAddr, byte u8Type, byte u8StartIndex)
        {
            byte[] commandData = null;
            commandData = new byte[6];

            // Build command payload            
            commandData[0] = (byte)(u16TargetAddr >> 8);
            commandData[1] = (byte)u16TargetAddr;
            commandData[2] = (byte)(u16ShortAddr >> 8);
            commandData[3] = (byte)u16ShortAddr;
            commandData[4] = u8Type;
            commandData[5] = u8StartIndex;
            
            // Transmit command
            transmitCommand(0x0041, 6, commandData);
        }

        private void sendGroupAdd(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16GroupAddr, byte u8GroupNameLength, byte u8GroupNameMaxLength, string sName)
        {
            byte[] commandData = null;
            commandData = new byte[16];
            byte u8Len = 0;

            // Build command payload
            commandData[u8Len++] = 0x02; // Short address mode    // 0
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);     // 1
            commandData[u8Len++] = (byte)u16ShortAddr;            // 2
            commandData[u8Len++] = u8SrcEndPoint;                 // 3
            commandData[u8Len++] = u8DstEndPoint;                 // 4
            commandData[u8Len++] = (byte)(u16GroupAddr >> 8);     // 5
            commandData[u8Len++] = (byte)u16GroupAddr;            // 6
            commandData[u8Len++] = u8GroupNameLength;             // 7
            commandData[u8Len++] = u8GroupNameMaxLength;          // 8

            char[] u8Array = sName.ToCharArray();

            for (int i = 0; i < sName.ToCharArray().Length; i++)
            {
                commandData[u8Len+i] = (byte)u8Array[i];
            }

            u8Len += u8GroupNameMaxLength;

            // Transmit command
            transmitCommand(0x0060, u8Len, commandData);
        }

        private void sendViewGroup(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16GroupAddr)
        {
            byte[] commandData = null;
            commandData = new byte[7];

            // Build command payload            
            commandData[0] = 0x02; // Short address mode
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = (byte)(u16GroupAddr >> 8);
            commandData[6] = (byte)u16GroupAddr;

            // Transmit command
            transmitCommand(0x0061, 7, commandData);
        }        

        private void sendGroupRemove(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16GroupAddr)
        {
            byte[] commandData = null;
            commandData = new byte[7];

            // Build command payload            
            commandData[0] = 0x02; // Short address mode
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = (byte)(u16GroupAddr >> 8);
            commandData[6] = (byte)u16GroupAddr;
            
            // Transmit command
            transmitCommand(0x0063, 7, commandData);
        }
        
        private void sendGroupRemoveAll(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint)
        {
            byte[] commandData = null;
            commandData = new byte[5];

            // Build command payload            
            commandData[0] = 0x02; // Short address mode
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            
            // Transmit command
            transmitCommand(0x0064, 5, commandData);
        }

        private void sendGroupGet(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, byte u8GroupCount, UInt16[] au16GroupList)
        {
            byte[] commandData = null;
            commandData = new byte[6];
            byte u8Length = 0;

            // Build command payload            
            commandData[u8Length++] = 0x02; // Short address mode
            commandData[u8Length++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Length++] = (byte)u16ShortAddr;
            commandData[u8Length++] = u8SrcEndPoint;
            commandData[u8Length++] = u8DstEndPoint;
            commandData[u8Length++] = u8GroupCount;

            
            for (byte i = 0; i < u8GroupCount; i++)
            {
                Array.Resize(ref commandData, u8Length + 2);
                commandData[u8Length++] = (byte)(au16GroupList[i] >> 8);
                commandData[u8Length++] = (byte)(au16GroupList[i]);
            }

            // Transmit command
            transmitCommand(0x0062, u8Length, commandData);
        }

        private void sendGroupAddIfIdentifying(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16GroupID)
        {
            byte[] commandData = null;
            commandData = new byte[8];

            // Build command payload            
            commandData[0] = 0x02; // Short address mode
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = (byte)(u16GroupID >> 8);
            commandData[6] = (byte)u16GroupID;

            // Transmit command
            transmitCommand(0x0065, 7, commandData);
        }

        private void sendEnhancedMoveToHue(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16Hue, byte u8Direction, UInt16 u16Time)
        {
            byte[] commandData = null;
            commandData = new byte[10];

            // Build command payload            
            commandData[0] = 0x02; // Address mode - short address
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = u8Direction;
            commandData[6] = (byte)(u16Hue >> 8);
            commandData[7] = (byte)u16Hue;
            commandData[8] = (byte)(u16Time >> 8);
            commandData[9] = (byte)u16Time;

            // Transmit command
            transmitCommand(0x00BA, 10, commandData);
        }

        private void sendZllClusterOnOff(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, byte u8EffectID, byte u8EffectGradient)
        {
            byte[] commandData = null;
            commandData = new byte[6];

            // Build command payload
            commandData[0] = (byte)(u16ShortAddr >> 8);
            commandData[1] = (byte)u16ShortAddr;
            commandData[2] = u8SrcEndPoint;
            commandData[3] = u8DstEndPoint;
            commandData[4] = u8EffectID;
            commandData[5] = u8EffectGradient;

            // Transmit command
            transmitCommand(0x0092, 6, commandData);
        }

        private void sendTouchlinkInitiate()
        {
            // Transmit command
            transmitCommand(0x00D0, 0, null);
        }

        private void sendTouchlinkFactoryReset()
        {
            // Transmit command
            transmitCommand(0x00D2, 0, null);
        }

        private void sendMoveToHue(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, byte u8Hue, byte u8Direction, UInt16 u16Time)
        {
            byte[] commandData = null;
            commandData = new byte[9];

            // Build command payload            
            commandData[0] = 0x02; // Address mode - short address
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = u8Hue;
            commandData[6] = u8Direction;
            commandData[7] = (byte)(u16Time >> 8);
            commandData[8] = (byte)u16Time;

            // Transmit command
            transmitCommand(0x00B0, 9, commandData);
        }

        private void sendMoveToColor(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16X, UInt16 u16Y, UInt16 u16Time)
        {
            byte[] commandData = null;
            commandData = new byte[11];

            // Build command payload            
            commandData[0]  = 0x02; // Address mode - short address
            commandData[1]  = (byte)(u16ShortAddr >> 8);
            commandData[2]  = (byte)u16ShortAddr;
            commandData[3]  = u8SrcEndPoint;
            commandData[4]  = u8DstEndPoint;
            commandData[5]  = (byte)(u16X >> 8);
            commandData[6]  = (byte)u16X;
            commandData[7]  = (byte)(u16Y >> 8);
            commandData[8]  = (byte)u16Y;
            commandData[9]  = (byte)(u16Time >> 8);
            commandData[10] = (byte)u16Time;

            // Transmit command
            transmitCommand(0x00B7, 11, commandData);
        }

        private void sendMoveToSat(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, byte u8Sat, UInt16 u16Time)
        {
            byte[] commandData = null;
            commandData = new byte[8];

            // Build command payload            
            commandData[0] = 0x02; // Address mode - short address
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = u8Sat;
            commandData[6] = (byte)(u16Time >> 8);
            commandData[7] = (byte)u16Time;

            // Transmit command
            transmitCommand(0x00B3, 8, commandData);
        }

        private void sendIdentify(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, UInt16 u16Time)
        {
            byte[] commandData = null;
            commandData = new byte[7];

            // Build command payload     
            commandData[0] = 0x02; // Short address mode
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = (byte)(u16Time >> 8);
            commandData[6] = (byte)u16Time;

            // Transmit command
            transmitCommand(0x0070, 7, commandData);
        }

        private void sendIdentifyQuery(UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint)
        {
            byte[] commandData = null;
            commandData = new byte[5];

            // Build command payload            
            commandData[0] = 0x02; // Short address mode
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;

            // Transmit command
            transmitCommand(0x0071, 5, commandData);
        }

        private void sendMgmtLeaveRequest(UInt16 u16ShortAddr, UInt64 u64ExtAddr, byte u8Rejoin, byte u8DoNotRemoveChildren)
        {
            byte[] commandData = null;
            commandData = new byte[12];

            // Build command payload            
            commandData[0] = (byte)(u16ShortAddr >> 8);
            commandData[1] = (byte)u16ShortAddr;
            commandData[2] = (byte)(u64ExtAddr >> 56);
            commandData[3] = (byte)(u64ExtAddr >> 48);
            commandData[4] = (byte)(u64ExtAddr >> 40);
            commandData[5] = (byte)(u64ExtAddr >> 32);
            commandData[6] = (byte)(u64ExtAddr >> 24);
            commandData[7] = (byte)(u64ExtAddr >> 16);
            commandData[8] = (byte)(u64ExtAddr >> 8);
            commandData[9] = (byte)u64ExtAddr;
            commandData[10] = u8Rejoin;
            commandData[11] = u8DoNotRemoveChildren;

            // Transmit command
            transmitCommand(0x0047, 12, commandData);
        }

        private void sendRemoveRequest(UInt64 u64ParentExtAddr, UInt64 u64ChildExtAddr)
        {
            byte[] commandData = null;
            commandData = new byte[16];

            // Build command payload            
            commandData[0] = (byte)(u64ParentExtAddr >> 56);
            commandData[1] = (byte)(u64ParentExtAddr >> 48);
            commandData[2] = (byte)(u64ParentExtAddr >> 40);
            commandData[3] = (byte)(u64ParentExtAddr >> 32);
            commandData[4] = (byte)(u64ParentExtAddr >> 24);
            commandData[5] = (byte)(u64ParentExtAddr >> 16);
            commandData[6] = (byte)(u64ParentExtAddr >> 8);
            commandData[7] = (byte)u64ParentExtAddr;

            commandData[8] = (byte)(u64ChildExtAddr >> 56);
            commandData[9] = (byte)(u64ChildExtAddr >> 48);
            commandData[10] = (byte)(u64ChildExtAddr >> 40);
            commandData[11] = (byte)(u64ChildExtAddr >> 32);
            commandData[12] = (byte)(u64ChildExtAddr >> 24);
            commandData[13] = (byte)(u64ChildExtAddr >> 16);
            commandData[14] = (byte)(u64ChildExtAddr >> 8);
            commandData[15] = (byte)u64ChildExtAddr;

            // Transmit command
            transmitCommand(0x0026, 16, commandData);
        }
        private void sendLeaveRequest(UInt64 u64ExtAddr, byte u8Rejoin, byte u8DoNotRemoveChildren)
        {
            byte[] commandData = null;
            commandData = new byte[10];

            // Build command payload            
            commandData[0] = (byte)(u64ExtAddr >> 56);
            commandData[1] = (byte)(u64ExtAddr >> 48);
            commandData[2] = (byte)(u64ExtAddr >> 40);
            commandData[3] = (byte)(u64ExtAddr >> 32);
            commandData[4] = (byte)(u64ExtAddr >> 24);
            commandData[5] = (byte)(u64ExtAddr >> 16);
            commandData[6] = (byte)(u64ExtAddr >> 8);
            commandData[7] = (byte)u64ExtAddr;

            commandData[8] = u8Rejoin;
            commandData[9] = u8DoNotRemoveChildren;

            // Transmit command
            transmitCommand(0x004C, 10, commandData);
        }

        private void sendClusterMoveToLevel(byte u8AddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, byte u8WithOnOff, byte u8Level, UInt16 u16TransTime)
        {
            byte[] commandData = null;
            commandData = new byte[9];

            // Build command payload            
            commandData[0] = u8AddrMode;
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = u8WithOnOff;
            commandData[6] = u8Level;
            commandData[7] = (byte)(u16TransTime >> 8);
            commandData[8] = (byte)u16TransTime;

            // Transmit command
            transmitCommand(0x0081, 9, commandData);
        }

        private void complexDescriptorRequest(UInt16 u16ShortAddr)
        {
            byte[] commandData = null;
            commandData = new byte[2];

            // Build command payload            
            commandData[0] = (byte)(u16ShortAddr >> 8);
            commandData[1] = (byte)u16ShortAddr;

            // Transmit command
            transmitCommand(0x0531, 2, commandData);
        }

        private void userDescriptorRequest(UInt16 u16ShortAddr)
        {
            byte[] commandData = null;
            commandData = new byte[2];

            // Build command payload            
            commandData[0] = (byte)(u16ShortAddr >> 8);
            commandData[1] = (byte)u16ShortAddr;

            // Transmit command
            transmitCommand(0x0532, 2, commandData);
        }

        private void userDescriptorSetRequest(UInt16 u16ShortAddr, String description)
        {
            byte[] commandData = null;
            char[] au8CharArry;
            byte u8Len = 0;
            commandData = new byte[3];

            au8CharArry = description.ToCharArray();

            // Build command payload            
            commandData[u8Len++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Len++] = (byte)u16ShortAddr;
            commandData[u8Len++] = (byte)(description.Length);

            Array.Resize(ref commandData, (u8Len + description.Length));

            foreach(char u8Byte in au8CharArry)
            {
                commandData[u8Len++] = (byte)u8Byte;
            }
            
            // Transmit command
            transmitCommand(0x0533, u8Len, commandData);
        }        

        private void sendMgmtLqiRequest(UInt16 u16ShortAddr, byte u8StartIndex)
        {
            byte[] commandData = null;
            commandData = new byte[4];

            // Build command payload            
            commandData[0] = (byte)(u16ShortAddr >> 8);
            commandData[1] = (byte)u16ShortAddr;
            commandData[2] = u8StartIndex;

            // Transmit command
            transmitCommand(0x004E, 3, commandData);
        }
        
        private void matchDescriptorRequest(UInt16 u16ShortAddr, UInt16 u16ProfileId, byte u8NbrInputClusters, UInt16[] au16InputClusters, byte u8NbrOutputClusters, UInt16[] au16OutputClusters)
        {
            byte[] commandData = null;
            commandData = new byte[128];
            byte u8Length = 0;

            // Build command payload            
            commandData[u8Length++] = (byte)(u16ShortAddr >> 8);
            commandData[u8Length++] = (byte)u16ShortAddr;
            commandData[u8Length++] = (byte)(u16ProfileId >> 8);
            commandData[u8Length++] = (byte)u16ProfileId;
            
            commandData[u8Length++] = u8NbrInputClusters;
            for (int i = 0; i < u8NbrInputClusters; i++)
            {
                commandData[u8Length++] = (byte)(au16InputClusters[i] >> 8);
                commandData[u8Length++] = (byte)au16InputClusters[i];
            }

            commandData[u8Length++] = u8NbrOutputClusters;
            for (int i = 0; i < u8NbrOutputClusters; i++)
            {
                commandData[u8Length++] = (byte)(au16OutputClusters[i] >> 8);
                commandData[u8Length++] = (byte)au16OutputClusters[i];
            }

            // Transmit command
            transmitCommand(0x0046, u8Length, commandData);
        }

        private void activeEndpointDescriptorRequest(UInt16 u16ShortAddr)
        {
            byte[] commandData = null;
            commandData = new byte[2];

            // Build command payload            
            commandData[0] = (byte)(u16ShortAddr >> 8);
            commandData[1] = (byte)u16ShortAddr;

            // Transmit command
            transmitCommand(0x0045, 2, commandData);
        }

        private void simpleDescriptorRequest(UInt16 u16ShortAddr, byte u8EndPoint)
        {
            byte[] commandData = null;
            commandData = new byte[3];

            // Build command payload
            commandData[0] = (byte)(u16ShortAddr >> 8);
            commandData[1] = (byte)u16ShortAddr;            
            commandData[2] = u8EndPoint;

            // Transmit command
            transmitCommand(0x0043, 3, commandData);
        }

        private void powerDescriptorRequest(UInt16 u16ShortAddr)
        {
            byte[] commandData = null;
            commandData = new byte[2];

            // Build command payload
            commandData[0] = (byte)(u16ShortAddr >> 8);
            commandData[1] = (byte)u16ShortAddr;
            
            // Transmit command
            transmitCommand(0x0044, 2, commandData);
        }

        private void nodeDescriptorRequest(UInt16 u16ShortAddr)
        {
            byte[] commandData = null;
            commandData = new byte[2];

            // Build command payload            
            commandData[0] = (byte)(u16ShortAddr >> 8);
            commandData[1] = (byte)u16ShortAddr;

            // Transmit command
            transmitCommand(0x0042, 2, commandData);
        }

        private void sendClusterOnOff(byte u8AddrMode, UInt16 u16ShortAddr, byte u8SrcEndPoint, byte u8DstEndPoint, byte u8CommandID)
        {
            byte[] commandData = null;
            commandData = new byte[6];

            // Build command payload
            commandData[0] = u8AddrMode;
            commandData[1] = (byte)(u16ShortAddr >> 8);
            commandData[2] = (byte)u16ShortAddr;            
            commandData[3] = u8SrcEndPoint;
            commandData[4] = u8DstEndPoint;
            commandData[5] = u8CommandID;
            
            // Transmit command
            transmitCommand(0x0092, 6, commandData);
        }

        private void setPermitJoin(UInt16 u16ShortAddr, byte u8Interval, byte u8TCsignificance)
        {
            byte[] commandData = null;
            commandData = new byte[4];

            // Build command payload
            commandData[0] = (byte)(u16ShortAddr >> 8);
            commandData[1] = (byte)u16ShortAddr;            
            commandData[2] = u8Interval;
            commandData[3] = u8TCsignificance;

            // Transmit command
            transmitCommand(0x0049, 4, commandData);
        }

        private void setNciCmd(byte u8NciCmdIndex)
        {
            byte[] commandData = null;
            commandData = new byte[1];

            // Build command payload
            commandData[0] = 0; // Default  - disabled
            if (u8NciCmdIndex == 0) commandData[0] = 0xA1; // Commission
            if (u8NciCmdIndex == 1) commandData[0] = 0xA0; // Decommission

            // Transmit command
            transmitCommand(0x002D, 1, commandData);
        }

        private void vSendPermitRejoinStateRequest()
        {
            // Transmit command
            transmitCommand(0x0014, 0, null);
        }

        private void vSendNetworkStateRequest()
        {
            // Transmit command
            transmitCommand(0x0009, 0, null);
        }

        private void setSecurityKeyState(byte keyState, byte keySeqNbr, byte keyType, byte[] keyData)
        {
            byte[] commandData = null;
            commandData = new byte[19];

            // Build command payload
            commandData[0] = keyState;
            commandData[1] = keySeqNbr;
            commandData[2] = keyType;
            for (int i = 0; i < 16; i++)
            {
                commandData[3 + i] = keyData[i];
            }

            // Transmit command
            transmitCommand(0x0022, 19, commandData);
        }

        private void setExtendedPanID(ulong ulExtPanID)
        {
            byte[] commandData = null;
            commandData = new byte[8];

            // Build command payload
            commandData[0] = (byte)(ulExtPanID >> 56);
            commandData[1] = (byte)(ulExtPanID >> 48);
            commandData[2] = (byte)(ulExtPanID >> 40);
            commandData[3] = (byte)(ulExtPanID >> 32);
            commandData[4] = (byte)(ulExtPanID >> 24);
            commandData[5] = (byte)(ulExtPanID >> 16);
            commandData[6] = (byte)(ulExtPanID >> 8);          
            commandData[7] = (byte)ulExtPanID;
            
            // Transmit command
            transmitCommand(0x0020, 8, commandData);
        }

        private void setChannelMask(uint uiMask)
        {
            byte[] commandData = null;
            commandData = new byte[4];

            // Build command payload
            commandData[0] = (byte)(uiMask >> 24);
            commandData[1] = (byte)(uiMask >> 16);
            commandData[2] = (byte)(uiMask >> 8); 
            commandData[3] = (byte)uiMask;
                              
            // Transmit command
            transmitCommand(0x0021, 4, commandData);
        }

        private void setDeviceType(byte deviceType)
        {
            byte[] commandData = null;
            commandData = new byte[1];

            // Build command payload
            commandData[0] = deviceType;

            // Transmit command
            transmitCommand(0x0023, 1, commandData);
        }

        private void sendIPNConfigureCommand(byte bEnabled, UInt32 u32RfActiveOutDioMask, UInt32 u32StatusOutDioMask, UInt32 u32TxConfInDioMask, byte bCallbackEnabled, UInt16 u16PollPeriod, byte u8TimerId)
        {
            byte[] commandData = null;
            commandData = new byte[17];
            byte u8Len = 17;

            // Build command payload   
            commandData[0] = bEnabled; 
            commandData[1] = (byte)(u32RfActiveOutDioMask >> 24);
            commandData[2] = (byte)(u32RfActiveOutDioMask >> 16);
            commandData[3] = (byte)(u32RfActiveOutDioMask >> 8);
            commandData[4] = (byte)u32RfActiveOutDioMask;
            commandData[5] = (byte)(u32StatusOutDioMask >> 24);
            commandData[6] = (byte)(u32StatusOutDioMask >> 16);
            commandData[7] = (byte)(u32StatusOutDioMask >> 8);
            commandData[8] = (byte)u32StatusOutDioMask;
            commandData[9] = (byte)(u32TxConfInDioMask >> 24);
            commandData[10] = (byte)(u32TxConfInDioMask >> 16);
            commandData[11] = (byte)(u32TxConfInDioMask >> 8);
            commandData[12] = (byte)u32TxConfInDioMask;
            commandData[13] = bCallbackEnabled;
            commandData[14] = (byte)(u16PollPeriod >> 8);
            commandData[15] = (byte)u16PollPeriod;
            commandData[16] = u8TimerId;

            // Transmit command
            transmitCommand(0x0800, u8Len, commandData);
        }

        private void sendDioSetDirectionOutputCommand(UInt16 cmdId, UInt32 u32OutputOnDIOMask, UInt32 u32OutputOffDIOMask)
        {
            byte[] commandData = null;
            commandData = new byte[8];
            byte u8Len = 8;

            // Build command payload   
            commandData[0] = (byte)(u32OutputOnDIOMask >> 24);
            commandData[1] = (byte)(u32OutputOnDIOMask >> 16);
            commandData[2] = (byte)(u32OutputOnDIOMask >> 8);
            commandData[3] = (byte)u32OutputOnDIOMask;
            commandData[4] = (byte)(u32OutputOffDIOMask >> 24);
            commandData[5] = (byte)(u32OutputOffDIOMask >> 16);
            commandData[6] = (byte)(u32OutputOffDIOMask >> 8);
            commandData[7] = (byte)u32OutputOffDIOMask;

            // Transmit command
            transmitCommand(cmdId, u8Len, commandData);
        }

        private void sendPollControlCheckInResponseValues(UInt16 u16FastPollExpiryTime, byte bFastPollEnableD)
        {
            byte[] commandData = null;
            commandData = new byte[3];
            byte u8Len = 3;

            // Build command payload   
            commandData[0] = bFastPollEnableD;
            commandData[1] = (byte)(u16FastPollExpiryTime >> 8);
            commandData[2] = (byte)u16FastPollExpiryTime;

            transmitCommand(0x0A00, u8Len, commandData);
        }

        private void sendAHISetTxPowerCommand(byte u8TxPower)
        {
            byte[] commandData = null;
            commandData = new byte[1];
            byte u8Len = 1;

            // Build command payload   
            commandData[0] = u8TxPower;

            transmitCommand(0x0806, u8Len, commandData);
        }

        #endregion

        #region serial transmit functions

        private void transmitCommand(int iCommand, int iLength, byte[] data)
        {
            if (serialPort1.IsOpen)
            {
                int i;
                byte[] specialCharacter = null;
                specialCharacter = new byte[1];
                byte[] message = null;
                message = new byte[256];

                // Build message payload, starting with the type field                
                message[0] = (byte)(iCommand >> 8);
                message[1] = (byte)iCommand;

                // Add message length
                message[2] = (byte)(iLength >> 8);
                message[3] = (byte)iLength;

                // Calculate checksum of header
                byte csum = 0;
                csum ^= message[0];
                csum ^= message[1];
                csum ^= message[2];
                csum ^= message[3];

                // Add message data and update checksum
                if (data != null)
                {
                    for (i = 0; i < iLength; i++)
                    {
                        message[5 + i] = data[i];
                        csum ^= data[i];
                    }
                }

                // Add checksum               
                message[4] = csum;

                // Display data byte in terminal window
                if (iCommand != 0x502)
                {
                    richTextBoxCommandResponse.Text += DateTime.Now.Hour.ToString("D2");
                    richTextBoxCommandResponse.Text += ":";
                    richTextBoxCommandResponse.Text += DateTime.Now.Minute.ToString("D2");
                    richTextBoxCommandResponse.Text += ":";
                    richTextBoxCommandResponse.Text += DateTime.Now.Second.ToString("D2");
                    richTextBoxCommandResponse.Text += ".";
                    richTextBoxCommandResponse.Text += DateTime.Now.Millisecond.ToString("D3");
                    richTextBoxCommandResponse.Text += " -> ";
                }
                
                // Transmit the message, send start character first
                specialCharacter[0] = 1;
                if (iCommand == 0x502)
                {
                    writeByteNoRawDisplay(specialCharacter[0]);                    
                }
                else
                {
                    writeByte(specialCharacter[0]);
                }

                // Transmit message payload with byte stuffing as required                
                for (i = 0; i < iLength + 5; i++)
                {
                    // Check if stuffing is required
                    if (message[i] < 0x10)
                    {
                        // First send escape character then message byte XOR'd with 0x10
                        specialCharacter[0] = 2;
                        if (iCommand == 0x502)
                        {
                            writeByteNoRawDisplay(specialCharacter[0]);
                        }
                        else
                        {
                            writeByte(specialCharacter[0]);
                        }

                        int msg = message[i];
                        msg = msg ^ 0x10;
                        message[i] = (byte)msg;

                        if (iCommand == 0x502)
                        {
                            writeByteNoRawDisplay(message[i]);
                        }
                        else
                        {
                            writeByte(message[i]);
                        }
                    }
                    else
                    {
                        // Send the character with no modification
                        if (iCommand == 0x502)
                        {
                            writeByteNoRawDisplay(message[i]);
                        }
                        else
                        {
                            writeByte(message[i]);
                        }
                    }
                }

                // Send end character
                specialCharacter[0] = 3;
                if (iCommand == 0x502)
                {
                    writeByteNoRawDisplay(specialCharacter[0]);
                }
                else
                {
                    writeByte(specialCharacter[0]);
                }
                richTextBoxCommandResponse.Text += "\n";
            }
        }

        void writeByte(byte data)
        {
            byte[] dataArray = null;
            dataArray = new byte[1];
            dataArray[0] = data;

            // Display data byte in terminal window            
            richTextBoxCommandResponse.Text += Convert.ToByte(dataArray[0]).ToString("X2");
            richTextBoxCommandResponse.Text += " ";

            // Write data byte to serial port
            serialPort1.Write(dataArray, 0, 1);
        }

        void writeByteNoRawDisplay(byte data)
        {
            byte[] dataArray = null;
            dataArray = new byte[1];
            dataArray[0] = data;

            // Write data byte to serial port
            serialPort1.Write(dataArray, 0, 1);
        }

        #endregion

        #region message parser functions

        // define the delegate 
        public delegate void MessageParser();

        // define an instance of the delegate
        MessageParser messageParser;

        // Received message parser
        public void myMessageParser()
        {
            // Display raw message data first 
            displayRawCommandData(rxMessageType, rxMessageLength, rxMessageChecksum, rxMessageData);

            // Display decoded message
            displayDecodedCommand(rxMessageType, rxMessageLength, rxMessageData);
        }

        private void displayDecodedCommand(UInt16 u16Type, UInt16 u16Length, byte[] au8Data)
        {
            if ((checkBoxDebug.Checked == true) || (u16Type != 0x8011 && u16Type != 0x8012))
            {
                richTextBoxMessageView.Text += "Type: 0x";
                richTextBoxMessageView.Text += u16Type.ToString("X4");
                richTextBoxMessageView.Text += "\n";
            }

            switch (u16Type)
            {
                case 0x8000:
                {
                    richTextBoxMessageView.Text += " (Status)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Length: " + u16Length.ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[0].ToString("X2");

                    switch (au8Data[0])
                    {
                        case 0:
                        {
                            richTextBoxMessageView.Text += " (Success)";
                        }
                        break;

                        case 1:
                        {
                            richTextBoxMessageView.Text += " (Incorrect Parameters)";
                        }
                        break;

                        case 2:
                        {
                            richTextBoxMessageView.Text += " (Unhandled Command)";
                        }
                        break;

                        case 3:
                        {
                            richTextBoxMessageView.Text += " (Command Failed)";
                        }
                        break;

                        case 4:
                        {
                            richTextBoxMessageView.Text += " (Busy)";
                        }
                        break;

                        case 5:
                        {
                            richTextBoxMessageView.Text += " (Stack Already Started)";
                        }
                        break;

                        default:
                        {
                            richTextBoxMessageView.Text += " (ZigBee Error Code)";
                        }
                        break;
                    }

                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[1].ToString("X2");

                    if (u16Length > 2)
                    {
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "  Message: ";
                        string errorMessage = System.Text.Encoding.Default.GetString(au8Data);
                        richTextBoxMessageView.Text += errorMessage.Substring(2, (u16Length - 2));
                    }
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8011:
                {
                    if (checkBoxDebug.Checked == true)
                    {
                        UInt16 u16ProfileID = 0;
                        UInt16 u16ClusterID = 0;

                        u16ProfileID = au8Data[4];
                        u16ProfileID <<= 8;
                        u16ProfileID |= au8Data[5];

                        u16ClusterID = au8Data[6];
                        u16ClusterID <<= 8;
                        u16ClusterID |= au8Data[7];

                        richTextBoxMessageView.Text += " (APS Data ACK)";
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "   Status: 0x" + au8Data[0].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "   SQN: 0x" + au8Data[1].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "   Source EndPoint: 0x" + au8Data[2].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "   Destination EndPoint: 0x" + au8Data[3].ToString("X2");
                        richTextBoxMessageView.Text += "\n   ";
                        displayProfileId(u16ProfileID);
                        richTextBoxMessageView.Text += "\n   ";
                        displayClusterId(u16ClusterID);
                        richTextBoxMessageView.Text += "\n";
                    }
                }
                break;

                case 0x8012:
                {
                    if (checkBoxDebug.Checked == true)
                    {
                        richTextBoxMessageView.Text += "  (APS Data Confirm)";
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "   Status: 0x" + au8Data[0].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "   SQN: 0x" + au8Data[1].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "   Source EndPoint: 0x" + au8Data[2].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "   Destination EndPoint: 0x" + au8Data[3].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                    }
                }
                break;

                case 0x8001:
                {                    
                    richTextBoxMessageView.Text += " (Log)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Level: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Message: ";

                    string logMessage = System.Text.Encoding.Default.GetString(au8Data);
                    richTextBoxMessageView.Text += logMessage.Substring(1, (u16Length - 1));
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8002:
                {
                    UInt16 u16ProfileID = 0;
                    UInt16 u16ClusterID = 0;

                    u16ProfileID = au8Data[1];
                    u16ProfileID <<= 8;
                    u16ProfileID |= au8Data[2];

                    u16ClusterID = au8Data[3];
                    u16ClusterID <<= 8;
                    u16ClusterID |= au8Data[4];

                    richTextBoxMessageView.Text += " (Data Indication)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayProfileId(u16ProfileID);
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterID);
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Source EndPoint: 0x" + au8Data[5].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Destination EndPoint: 0x" + au8Data[6].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Source Address Mode: 0x" + au8Data[7].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Source Address: ";

                    byte nextIndex = 0;

                    if (au8Data[9] == 0)
                    {
                        //0x00 = DstAddress and DstEndpoint not present                        
                        richTextBoxMessageView.Text += "Not Present";
                        richTextBoxMessageView.Text += "\n";

                        nextIndex = 10;
                    }
                    else if (au8Data[9] == 1)
                    {
                        UInt16 u16GroupAddr = 0;

                        u16GroupAddr   = au8Data[10];
                        u16GroupAddr <<= 8;
                        u16GroupAddr  |= au8Data[11];

                        //0x01 = 16-bit group address for DstAddress; DstEndpoint not present
                        richTextBoxMessageView.Text += u16GroupAddr.ToString("X4");
                        richTextBoxMessageView.Text += "\n";

                        nextIndex = 12;
                    }
                    else if (au8Data[9] == 2)
                    {
                        UInt16 u16DstAddress = 0;
                        UInt16 u16DstEndPoint1 = 0;

                        u16DstAddress = au8Data[10];
                        u16DstAddress <<= 8;
                        u16DstAddress |= au8Data[11];

                        u16DstEndPoint1 = au8Data[12];
                        u16DstEndPoint1 <<= 8;
                        u16DstEndPoint1 |= au8Data[13];

                        //0x02 = 16-bit address for DstAddress and DstEndpoint present
                        richTextBoxMessageView.Text += u16DstAddress.ToString("X4");
                        richTextBoxMessageView.Text += "  EndPoint: 0x" + u16DstEndPoint1.ToString("X4");
                        richTextBoxMessageView.Text += "\n";

                        nextIndex = 14;
                    }
                    else if (au8Data[9] == 3)
                    {
                        //0x03 = 64-bit extended address for DstAddress and DstEndpoint present
                    }
                    else
                    {
                        //0x04 - 0xff = reserved
                        nextIndex = 10;
                        richTextBoxMessageView.Text += "Not Valid";
                        richTextBoxMessageView.Text += "\n";
                    }

                    richTextBoxMessageView.Text += "  Destination Address Mode: 0x" + au8Data[nextIndex].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8003:
                {
                    UInt16 u16Entries = 0;
                    UInt16 u16ProfileID = 0;

                    u16ProfileID = au8Data[1];
                    u16ProfileID <<= 8;
                    u16ProfileID |= au8Data[2];

                    u16Entries = (UInt16)((u16Length - 3) / 2);
                    
                    richTextBoxMessageView.Text += " (Cluster List - Entries: ";
                    richTextBoxMessageView.Text += u16Entries.ToString();
                    richTextBoxMessageView.Text += ")\n";
                    richTextBoxMessageView.Text += "  Source EndPoint: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayProfileId(u16ProfileID);

                    for (int i = 3; i < u16Length; i+=2)
                    {
                        UInt16 u16ClusterID;

                        u16ClusterID = au8Data[i];
                        u16ClusterID <<= 8;
                        u16ClusterID |= au8Data[i + 1];

                        displayClusterId(u16ClusterID);
                        richTextBoxMessageView.Text += "\n";
                    }
                }
                break;

                case 0x8004:
                {
                    UInt16 u16Entries = 0;
                    UInt16 u16ProfileID = 0;
                    UInt16 u16ClusterID = 0;

                    u16ProfileID = au8Data[1];
                    u16ProfileID <<= 8;
                    u16ProfileID |= au8Data[2];

                    u16ClusterID = au8Data[3];
                    u16ClusterID <<= 8;
                    u16ClusterID |= au8Data[4];

                    u16Entries = (UInt16)((u16Length - 5) / 2);

                    richTextBoxMessageView.Text += " (Cluster Attributes - Entries: ";
                    richTextBoxMessageView.Text += u16Entries.ToString();
                    richTextBoxMessageView.Text += ")\n";
                    richTextBoxMessageView.Text += " Source EndPoint: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayProfileId(u16ProfileID);
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterID);
                    richTextBoxMessageView.Text += "\n";

                    for (int i = 5; i < u16Length; i += 2)
                    {
                        UInt16 u16AttributeID = 0;

                        u16AttributeID = au8Data[i];
                        u16AttributeID <<= 8;
                        u16AttributeID |= au8Data[i + 1];

                        richTextBoxMessageView.Text += " Attribute ID: 0x" + u16AttributeID.ToString("X4");
                        richTextBoxMessageView.Text += "\n";
                    }
                }
                break;

                case 0x8005:
                {
                    UInt16 u16Entries = 0;
                    UInt16 u16ProfileID = 0;
                    UInt16 u16ClusterID = 0;

                    u16ProfileID = au8Data[1];
                    u16ProfileID <<= 8;
                    u16ProfileID |= au8Data[2];

                    u16ClusterID = au8Data[3];
                    u16ClusterID <<= 8;
                    u16ClusterID |= au8Data[4];

                    u16Entries = (UInt16)(u16Length - 5);

                    richTextBoxMessageView.Text += " (Command IDs - Entries: ";
                    richTextBoxMessageView.Text += u16Entries.ToString();
                    richTextBoxMessageView.Text += ")\n";
                    richTextBoxMessageView.Text += " Source EndPoint: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayProfileId(u16ProfileID);
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterID);
                    richTextBoxMessageView.Text += "\n";

                    for (int i = 5; i < u16Length; i++)
                    {
                        richTextBoxMessageView.Text += " Command ID: 0x" + au8Data[i].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                    }
                }
                break;

                case 0x8009:
                {

                    UInt16 u16PanId = 0;
                    UInt16 u16ShortAddr = 0;
                    UInt64 u64ExtendedPANID = 0;
                    UInt64 u64ExtendedAddr = 0;

                    u16ShortAddr = au8Data[0];
                    u16ShortAddr <<= 8;
                    u16ShortAddr |= au8Data[1];

                    for (int i = 0; i < 8; i++)
                    {
                        u64ExtendedAddr <<= 8;
                        u64ExtendedAddr |= au8Data[2 + i];
                    }

                    u16PanId = au8Data[10];
                    u16PanId <<= 8;
                    u16PanId |= au8Data[11];

                    for (int i = 0; i < 8; i++)
                    {
                        u64ExtendedPANID <<= 8;
                        u64ExtendedPANID |= au8Data[12 + i];
                    }

                    richTextBoxMessageView.Text += " (Network State Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Short Address: 0x" + u16ShortAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Extended Address: 0x" + u64ExtendedAddr.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  PAN ID: " + u16PanId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Ext PAN ID: 0x" + u64ExtendedPANID.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Channel: " + au8Data[20].ToString();
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8010:
                {
                    UInt16 u16Major = 0;
                    UInt16 u16Installer = 0;

                    u16Major   = au8Data[0];
                    u16Major <<= 8;
                    u16Major  |= au8Data[1];

                    u16Installer = au8Data[2];
                    u16Installer <<= 8;
                    u16Installer |= au8Data[3];

                    richTextBoxMessageView.Text += " (Version)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Length: " + u16Length.ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Application: " + u16Major.ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SDK: " + u16Installer.ToString();
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8024:
                {
                    UInt16 u16ShortAddr = 0;
                    UInt64 u64ExtAddr = 0;

                    u16ShortAddr   = au8Data[1];
                    u16ShortAddr <<= 8;
                    u16ShortAddr  |= au8Data[2];

                    for(int i = 0; i < 8; i++)
                    {
                        u64ExtAddr <<= 8;
                        u64ExtAddr  |= au8Data[3 + i];
                    }

                    richTextBoxMessageView.Text += " (Network Up)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Short Address: 0x" + u16ShortAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Extended Address: 0x" + u64ExtAddr.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Channel: " + au8Data[11].ToString();
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8014:
                {
                    richTextBoxMessageView.Text += " (Permit Join State)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "Permit Join: " + (au8Data[0] == 1 ? "TRUE" : "FALSE");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8015:
                {
                    UInt16 u16PanId = 0;
                    UInt16 u16ShortAddr = 0;
                    UInt16 u16SuperframeSpec = 0;
                    UInt32 u32TimeStamp = 0;
                    UInt64 u64ExtendedPANID = 0;

                    u16PanId = au8Data[1];
                    u16PanId <<= 8;
                    u16PanId |= au8Data[2];

                    u16ShortAddr = au8Data[3];
                    u16ShortAddr <<= 8;
                    u16ShortAddr |= au8Data[4];

                    u16SuperframeSpec = au8Data[11];
                    u16SuperframeSpec <<= 8;
                    u16SuperframeSpec |= au8Data[12];

                    for (int i = 0; i < 4; i++)
                    {
                        u32TimeStamp <<= 8;
                        u32TimeStamp |= au8Data[13 + i];
                    }

                    for (int i = 0; i < 8; i++)
                    {
                        u64ExtendedPANID <<= 8;
                        u64ExtendedPANID |= au8Data[17 + i];
                    }

                    richTextBoxMessageView.Text += " (Discovery Only Scan Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Address Mode: " + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  PAN ID: " + u16PanId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Short Address: 0x" + u16ShortAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Channel: " + au8Data[5].ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  GTS Permit: " + au8Data[6].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Link Quality: " + au8Data[7];
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Security Use: " + au8Data[8].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  ACL Entry: " + au8Data[9].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Security Failure: " + au8Data[10].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Superframe Specification: " + u16SuperframeSpec.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Time Stamp: " + u32TimeStamp.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Ext PAN ID: 0x" + u64ExtendedPANID.ToString("X8");

                }
                break;

                case 0x8029:
                {
                    UInt64 u64AddrData = 0;
                    UInt64 u64Key = 0;
                    UInt64 u64HostAddrData = 0;
                    UInt64 u64ExtPANID = 0;
                    UInt32 u32Mic = 0;
                    UInt16 u16PANID = 0;
                    UInt16 u16ShortAddr = 0;
                    UInt16 u16DeviceId = 0;

                    for (int i = 0; i < 8; i++)
                    {
                        u64AddrData <<= 8;
                        u64AddrData  |= au8Data[0 + i];
                    }
                    
                    for (int i = 0; i < 16; i++)
                    {
                        u64Key <<= 8;
                        u64Key |= au8Data[8 + i];
                    }
                    
                    for (int i = 0; i < 4; i++)
                    {
                        u32Mic <<= 8;
                        u32Mic |= au8Data[24 + i];
                    }
                    
                    for (int i = 0; i < 8; i++)
                    {
                        u64HostAddrData  <<= 8;
                        u64HostAddrData |= au8Data[28 + i];
                    }

                    u16PANID = au8Data[38];
                    u16PANID <<= 8;
                    u16PANID |= au8Data[39];

                    for (int i = 0; i < 8; i++)
                    {
                        u64ExtPANID <<= 8;
                        u64ExtPANID |= au8Data[40 + i];
                    }

                    u16ShortAddr = au8Data[48];
                    u16ShortAddr <<= 8;
                    u16ShortAddr |= au8Data[49];

                    u16DeviceId = au8Data[50];
                    u16DeviceId <<= 8;
                    u16DeviceId |= au8Data[51];
                    
                    richTextBoxMessageView.Text += " (Encrypted Data)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[52].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Device Extended Address: " + u64AddrData.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Key: " + u64Key.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Mic: " + u32Mic.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Host Extended Address: " + u64HostAddrData.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Active Key Sequence Number: " + au8Data[36].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Channel: " + au8Data[37].ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  PAN ID: " + u16PANID.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Extended PAN ID: " + u64ExtPANID.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Short Address: " + u16ShortAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Device ID: " + u16DeviceId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";

                }
                break;

                // NciCmdNotify
                case 0x802E:
                {
                    UInt16 u16DeviceId = 0;
                    UInt64 u64ExtAddr = 0;

                    u16DeviceId = au8Data[1];
                    u16DeviceId <<= 8;
                    u16DeviceId |= au8Data[2];

                    for (int i = 0; i < 8; i++)
                    {
                        u64ExtAddr <<= 8;
                        u64ExtAddr |= au8Data[3 + i];
                    }

                    richTextBoxMessageView.Text += " (NCI Command Notify)";
                    richTextBoxMessageView.Text += "\n";
                    if (au8Data[0] == 0xA1)
                    {
                        richTextBoxMessageView.Text += "  Command: Commission";
                    }
                    else if (au8Data[0] == 0xA0)
                    {
                        richTextBoxMessageView.Text += "  Command: Decommission";
                    }  
                    else
                    {
                        richTextBoxMessageView.Text += "  Command: Unknown";
                    }
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Device ID: 0x" + u16DeviceId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Extended Address: 0x" + u64ExtAddr.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8030:
                {
                    richTextBoxMessageView.Text += " (Bind Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8031:
                {
                    richTextBoxMessageView.Text += " (UnBind Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8041:
                {
                    UInt64 u64ExtAddr = 0;
                    UInt16 u16ShortAddr = 0;

                    for (int i = 0; i < 8; i++)
                    {
                        u64ExtAddr <<= 8;
                        u64ExtAddr |= au8Data[2 + i];
                    }

                    u16ShortAddr = au8Data[10];
                    u16ShortAddr <<= 8;
                    u16ShortAddr |= au8Data[11];

                    richTextBoxMessageView.Text += " (IEEE Address Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Extended Address: 0x" + u64ExtAddr.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Short Address: 0x" + u16ShortAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";

                    if (u16Length > 14)
                    {
                        richTextBoxMessageView.Text += "  Associated End Devices: " + au8Data[12].ToString();
                        richTextBoxMessageView.Text += "\n";
                    }
                }
                break;

                case 0x8042:
                {
                    UInt16 u16ShortAddr = 0;
                    UInt16 u16ManufacturerCode = 0;
                    UInt16 u16RxSize = 0;
                    UInt16 u16TxSize = 0;
                    UInt16 u16ServerMask = 0;
                    UInt16 u16BitFields = 0;
                    byte u8DescriptorCapability = 0;
                    byte u8MacCapability = 0;
                    byte u8MaxBufferSize = 0;

                    u16ShortAddr   = au8Data[2];
                    u16ShortAddr <<= 8;
                    u16ShortAddr  |= au8Data[3];

                    u16ManufacturerCode   = au8Data[4];
                    u16ManufacturerCode <<= 8;
                    u16ManufacturerCode  |= au8Data[5];

                    u16RxSize = au8Data[6];
                    u16RxSize <<= 8;
                    u16RxSize |= au8Data[7];

                    u16TxSize = au8Data[8];
                    u16TxSize <<= 8;
                    u16TxSize |= au8Data[9];

                    u16ServerMask = au8Data[10];
                    u16ServerMask <<= 8;
                    u16ServerMask |= au8Data[11];

                    u8DescriptorCapability = au8Data[12];
                    u8MacCapability = au8Data[13];
                    u8MaxBufferSize = au8Data[14];

                    u16BitFields = au8Data[15];
                    u16BitFields <<= 8;
                    u16BitFields |= au8Data[16];
                   
                    richTextBoxMessageView.Text += " (Node Descriptor Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Short Address: 0x" + u16ShortAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Manufacturer Code: 0x" + u16ManufacturerCode.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Max Rx Size: " + u16RxSize.ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Max Tx Size: " + u16TxSize.ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Server Mask: 0x" + u16ServerMask.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    displayDescriptorCapability(u8DescriptorCapability);
                    displayMACcapability(u8MacCapability);
                    richTextBoxMessageView.Text += "  Max Buffer Size: " + u8MaxBufferSize.ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Bit Fields: 0x" + u16BitFields.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8043:
                {
                    UInt16 u16ShortAddr = 0;                    
                    byte u8Length = 0;

                    u16ShortAddr = au8Data[2];
                    u16ShortAddr <<= 8;
                    u16ShortAddr |= au8Data[3];
                    u8Length = au8Data[4];

                    richTextBoxMessageView.Text += " (Simple Descriptor Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Short Address: 0x" + u16ShortAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Length: " + u8Length.ToString("");
                    richTextBoxMessageView.Text += "\n";

                    if (u8Length > 0)
                    {
                        byte u8InputClusterCount = 0;
                        UInt16 u16ProfileId = 0;
                        UInt16 u16DeviceId = 0;

                        u16ProfileId = au8Data[6];
                        u16ProfileId <<= 8;
                        u16ProfileId |= au8Data[7];
                        u16DeviceId = au8Data[8];
                        u16DeviceId <<= 8;
                        u16DeviceId |= au8Data[9];
                        u8InputClusterCount = au8Data[11];

                        richTextBoxMessageView.Text += "  EndPoint: 0x" + au8Data[5].ToString("X2");
                        richTextBoxMessageView.Text += "\n";                        
                        displayProfileId(u16ProfileId);
                        richTextBoxMessageView.Text += "\n";
                        displayDeviceId(u16DeviceId);                        
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "  Input Cluster Count: " + u8InputClusterCount.ToString();
                        richTextBoxMessageView.Text += "\n";

                        UInt16 u16Index = 12;
                        for (int i = 0; i < u8InputClusterCount; i++)
                        {
                            UInt16 u16ClusterId = 0;

                            u16ClusterId = au8Data[(i * 2) + 12];
                            u16ClusterId <<= 8;
                            u16ClusterId |= au8Data[(i * 2) + 13];

                            richTextBoxMessageView.Text += "    Cluster " + i.ToString();
                            richTextBoxMessageView.Text += ":";
                            displayClusterId(u16ClusterId);
                            richTextBoxMessageView.Text += "\n";
                            u16Index+=2;
                        }

                        byte u8OutputClusterCount = au8Data[u16Index];
                        u16Index++;

                        richTextBoxMessageView.Text += "  Output Cluster Count: " + u8OutputClusterCount.ToString();
                        richTextBoxMessageView.Text += "\n";

                        for (int i = 0; i < u8OutputClusterCount; i++)
                        {
                            UInt16 u16ClusterId = 0;

                            u16ClusterId = au8Data[u16Index];
                            u16ClusterId <<= 8;
                            u16ClusterId |= au8Data[u16Index + 1];

                            richTextBoxMessageView.Text += "    Cluster " + i.ToString();
                            richTextBoxMessageView.Text += ":";
                            displayClusterId(u16ClusterId);
                            richTextBoxMessageView.Text += "\n";
                            u16Index += 2;
                        }
                    }
                }
                break;
                    /*
                case 0x8044:
                {
                    richTextBoxMessageView.Text += " (Power Descriptor Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                }
                break;
                    */
                case 0x8045:
                {
                    UInt16 u16ShortAddr = 0;

                    u16ShortAddr = au8Data[2];
                    u16ShortAddr <<= 8;
                    u16ShortAddr |= au8Data[3];

                    richTextBoxMessageView.Text += " (Active Endpoints Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Short Address: 0x" + u16ShortAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Endpoint Count: " + au8Data[4].ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Endpoint List: ";
                    richTextBoxMessageView.Text += "\n";

                    for (int i = 0; i < au8Data[4]; i++)
                    {
                        richTextBoxMessageView.Text += "    Endpoint " + i.ToString();
                        richTextBoxMessageView.Text += ": ";
                        richTextBoxMessageView.Text += "0x" + au8Data[i + 5].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                    }
                }
                break;

                case 0x8047:
                {
                    richTextBoxMessageView.Text += " (Leave Confirmation)";
                    richTextBoxMessageView.Text += "\n";
                    
                    if (u16Length == 2)
                    {
                        richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                    }
                    
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";

                    if (u16Length == 9)
                    {
                        UInt64 u64ExtAddr = 0;

                        for (int i = 0; i < 8; i++)
                        {
                            u64ExtAddr <<= 8;
                            u64ExtAddr |= au8Data[1 + i];
                        }

                        richTextBoxMessageView.Text += "  Extended Address: 0x" + u64ExtAddr.ToString("X8");
                        richTextBoxMessageView.Text += "\n";
                    }
                }
                break;

                case 0x8048:
                {
                    UInt64 u64ExtAddr = 0;

                    for (int i = 0; i < 8; i++)
                    {
                        u64ExtAddr <<= 8;
                        u64ExtAddr |= au8Data[i];
                    }

                    richTextBoxMessageView.Text += " (Leave Indication)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Extended Address: 0x" + u64ExtAddr.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Rejoin Status: 0x" + au8Data[8].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x804A:
                {
                    byte u8ScannedChannelsListCount;
                    UInt16 u16TotalTx = 0;
                    UInt16 u16TxFailures = 0;
                    UInt32 u32ScannedChannels = 0;

                    u16TotalTx = au8Data[2];
                    u16TotalTx <<= 8;
                    u16TotalTx |= au8Data[3];
                    
                    u16TxFailures = au8Data[4];
                    u16TxFailures <<= 8;
                    u16TxFailures |= au8Data[5];

                    u32ScannedChannels = au8Data[6];
                    u32ScannedChannels <<= 8;
                    u32ScannedChannels |= au8Data[7];
                    u32ScannedChannels <<= 8; 
                    u32ScannedChannels |= au8Data[8];
                    u32ScannedChannels <<= 8;
                    u32ScannedChannels |= au8Data[9];

                    u8ScannedChannelsListCount = au8Data[10];

                    richTextBoxMessageView.Text += " (Mgmt Nwk Update Notify)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Total Tx: " + u16TotalTx.ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Tx Failures: " + u16TxFailures.ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Scanned Channels: 0x" + u32ScannedChannels.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Scanned Channels List Count: " + u8ScannedChannelsListCount.ToString();
                    richTextBoxMessageView.Text += "\n";

                    for (int x = 0; x < u8ScannedChannelsListCount; x++)
                    {
                        richTextBoxMessageView.Text += "  Value " + x.ToString();
                        richTextBoxMessageView.Text += ":  0x" + au8Data[11 + x].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                    }
                }
                break;

                case 0x804E:
                {
                    byte u8NbTableEntries = 0;
                    byte u8StartIx = 0;
                    byte u8NbTableListCount = 0;

                    UInt16[] au16NwkAddr = new UInt16[16];

                    u8NbTableEntries = au8Data[2];
                    u8NbTableListCount = au8Data[3];                    
                    u8StartIx = au8Data[4];
                    
                    richTextBoxMessageView.Text += " (Mgmt LQI Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Nb Table Entries: " + u8NbTableEntries.ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Start Index: " + u8StartIx.ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Nb Table List Count: " + u8NbTableListCount.ToString();
                    richTextBoxMessageView.Text += "\n";

                    comboBoxAddressList.Items.Clear();

                    if (u8NbTableListCount > 0)
                    {
                        byte i;
                        UInt64 u64PanID = 0;
                        UInt64 u64ExtAddr = 0;
                        UInt16 u16NwkAddr = 0;
                        byte u8Lqi = 0;
                        byte u8Depth = 0;
                        byte u8Flags = 0;
                        byte u8PayloadIndex = 5;

                        for (i = 0; i < u8NbTableListCount; i++)
                        {
                            u16NwkAddr = 0;
                            for (int x = 0; x < 2; x++, u8PayloadIndex++)
                            {
                                u16NwkAddr <<= 8;
                                u16NwkAddr |= au8Data[u8PayloadIndex];
                            }

                            u64PanID = 0;
                            for (int x = 0; x < 8; x++, u8PayloadIndex++)
                            {
                                u64PanID <<= 8;
                                u64PanID |= au8Data[u8PayloadIndex];
                            }

                            u64ExtAddr = 0;
                            for (int x = 0; x < 8; x++, u8PayloadIndex++)
                            {
                                u64ExtAddr <<= 8;
                                u64ExtAddr |= au8Data[u8PayloadIndex];
                            }

                            au16NwkAddr[i] = u16NwkAddr;

                            au64ExtAddr[i] = u64ExtAddr;

                            u8Depth = au8Data[u8PayloadIndex++];
                            u8Lqi = au8Data[u8PayloadIndex++];                            
                            u8Flags = au8Data[u8PayloadIndex++];

                            richTextBoxMessageView.Text += "  Neighbor " + i.ToString();
                            richTextBoxMessageView.Text += ":";
                            richTextBoxMessageView.Text += "\n";
                            richTextBoxMessageView.Text += "    Extended Pan ID: 0x" + u64PanID.ToString("X8");
                            richTextBoxMessageView.Text += "\n";
                            richTextBoxMessageView.Text += "    Extended Address: 0x" + u64ExtAddr.ToString("X8");
                            richTextBoxMessageView.Text += "\n";
                            richTextBoxMessageView.Text += "    Nwk Address: 0x" + u16NwkAddr.ToString("X4");
                            richTextBoxMessageView.Text += "\n";
                            richTextBoxMessageView.Text += "    LQI: " + u8Lqi.ToString();
                            richTextBoxMessageView.Text += "\n";
                            richTextBoxMessageView.Text += "    Depth: " + u8Depth.ToString();
                            richTextBoxMessageView.Text += "\n";
                            richTextBoxMessageView.Text += "    Flags: 0x" + u8Flags.ToString("X2");
                            richTextBoxMessageView.Text += "\n";

                            byte u8DeviceType = (byte)(u8Flags & 0x03);
                            richTextBoxMessageView.Text += "    Device Type: ";

                            if (u8DeviceType == 0)
                            {
                                richTextBoxMessageView.Text += "Coordinator";
                            }
                            else if (u8DeviceType == 1)
                            {
                                richTextBoxMessageView.Text += "Router";
                            }
                            else if (u8DeviceType == 2)
                            {
                                richTextBoxMessageView.Text += "End Device";
                            }
                            else
                            {
                                richTextBoxMessageView.Text += "Unknown";
                            }
                            richTextBoxMessageView.Text += "\n";

                            byte u8PermitJoin = (byte)((u8Flags & 0x0C) >> 2);
                            richTextBoxMessageView.Text += "    Permit Joining: ";

                            if (u8PermitJoin == 0)
                            {
                                richTextBoxMessageView.Text += "Off";
                            }
                            else if (u8PermitJoin == 1)
                            {
                                richTextBoxMessageView.Text += "On";
                            }
                            else
                            {
                                richTextBoxMessageView.Text += "Unknown";
                            }
                            richTextBoxMessageView.Text += "\n";

                            byte u8Relationship = (byte)((u8Flags & 0x30) >> 4);
                            richTextBoxMessageView.Text += "    Relationship: ";

                            if (u8Relationship == 0)
                            {
                                richTextBoxMessageView.Text += "Parent";
                            }
                            else if (u8Relationship == 1)
                            {
                                richTextBoxMessageView.Text += "Child";
                            }
                            else if (u8Relationship == 2)
                            {
                                richTextBoxMessageView.Text += "Sibling";
                            }
                            else if (u8Relationship == 4)
                            {
                                richTextBoxMessageView.Text += "Previous Child";
                            }
                            else
                            {
                                richTextBoxMessageView.Text += "Unknown";
                            }
                            richTextBoxMessageView.Text += "\n";

                            byte u8RxOnWhenIdle = (byte)((u8Flags & 0xC0) >> 6);
                            richTextBoxMessageView.Text += "    RxOnWhenIdle: ";

                            if (u8RxOnWhenIdle == 0)
                            {
                                richTextBoxMessageView.Text += "No";
                            }
                            else if (u8RxOnWhenIdle == 1)
                            {
                                richTextBoxMessageView.Text += "Yes";
                            }
                            else
                            {
                                richTextBoxMessageView.Text += "Unknown";
                            }                            
                            richTextBoxMessageView.Text += "\n";
                        }
                        for (i = 0; i < u8NbTableListCount; i++)
                        {
                            comboBoxAddressList.Items.Add(au16NwkAddr[i].ToString("X4"));
                        }
                    }
                }
                break;

                case 0x8050:
                {
                    UInt16 u16TableSize;
                    UInt16 u16TableEntries;

                    u16TableSize = au8Data[1];
                    u16TableSize <<= 8;
                    u16TableSize |= au8Data[2];

                    u16TableEntries = au8Data[3];
                    u16TableEntries <<= 8;
                    u16TableEntries |= au8Data[4];

                    richTextBoxMessageView.Text += " (Addr Map Table Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Table Size: " + u16TableSize.ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Entries: " + u16TableEntries.ToString();
                    richTextBoxMessageView.Text += "\n";

                    byte i;
                    for (i = 0; i < u16TableEntries; i++)
                    {
                        UInt16 u16Addr;
                        UInt64 u64Addr;

                        u16Addr = au8Data[5 + (i * 8)];
                        u16Addr <<= 8;
                        u16Addr |= au8Data[6 + (i * 8)];

                        u64Addr = au8Data[7 + (i * 8)];
                        u64Addr <<= 8;
                        u64Addr |= au8Data[8 + (i * 8)];
                        u64Addr <<= 8;
                        u64Addr |= au8Data[9 + (i * 8)];
                        u64Addr <<= 8;
                        u64Addr |= au8Data[10 + (i * 8)];
                        u64Addr <<= 8;
                        u64Addr |= au8Data[11 + (i * 8)];
                        u64Addr <<= 8;
                        u64Addr |= au8Data[12 + (i * 8)];
                        u64Addr <<= 8;
                        u64Addr |= au8Data[13 + (i * 8)];
                        u64Addr <<= 8;
                        u64Addr |= au8Data[14 + (i * 8)];

                        richTextBoxMessageView.Text += "  Entry " + i.ToString();
                        richTextBoxMessageView.Text += ": 0x" + u16Addr.ToString("X4");
                        richTextBoxMessageView.Text += " 0x" + u64Addr.ToString("X8");

                        richTextBoxMessageView.Text += "\n";
                    }

                }
                break;

                case 0x8060:
                {
                    UInt16 u16ClusterId = 0;
                    UInt16 u16GroupId = 0;

                    u16ClusterId   = au8Data[2];
                    u16ClusterId <<= 8;
                    u16ClusterId  |= au8Data[3];

                    u16GroupId   = au8Data[5];
                    u16GroupId <<= 8;
                    u16GroupId  |= au8Data[6];

                    richTextBoxMessageView.Text += " (Add Group Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  EndPoint: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterId);
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[4].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Group: 0x" + u16GroupId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8061:
                {
                    UInt16 u16ClusterId = 0;
                    UInt16 u16GroupId = 0;

                    u16ClusterId = au8Data[2];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[3];

                    u16GroupId = au8Data[5];
                    u16GroupId <<= 8;
                    u16GroupId |= au8Data[6];

                    richTextBoxMessageView.Text += " (View Group Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  EndPoint: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterId);
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[4].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Group: 0x" + u16GroupId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8062:
                {
                    UInt16 u16ClusterId = 0;
                    u16ClusterId = au8Data[2];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[3];

                    richTextBoxMessageView.Text += " (Get Group Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  EndPoint: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterId);
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Capacity: " + au8Data[4].ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Count: " + au8Data[5].ToString();
                    richTextBoxMessageView.Text += "\n";

                    byte i;
                    for (i = 0; i < au8Data[5]; i++)
                    {
                        UInt16 u16GroupId;

                        u16GroupId = au8Data[6 + (i * 2)];
                        u16GroupId <<= 8;
                        u16GroupId |= au8Data[7 + (i * 2)];

                        richTextBoxMessageView.Text += "  Group " + i.ToString();
                        richTextBoxMessageView.Text += ": 0x" + u16GroupId.ToString("X4");
                        richTextBoxMessageView.Text += "\n";
                    }
                }
                break;

                case 0x8063:
                {
                    UInt16 u16ClusterId = 0;
                    UInt16 u16GroupId = 0;

                    u16ClusterId = au8Data[2];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[3];

                    u16GroupId = au8Data[5];
                    u16GroupId <<= 8;
                    u16GroupId |= au8Data[6];

                    richTextBoxMessageView.Text += " (Remove Group Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  EndPoint: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterId);
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[4].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Group: 0x" + u16GroupId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x807A:
                {
                    richTextBoxMessageView.Text += " (Identify Local Active)";
                    richTextBoxMessageView.Text += "\n";
                    if (au8Data[0] == 1)
                    {
                        richTextBoxMessageView.Text += "  Status: Start Identifying";
                        richTextBoxMessageView.Text += "\n";
                    }
                    else if (au8Data[0] != 1)
                    {
                        richTextBoxMessageView.Text += "  Status: Stop Identifying";
                        richTextBoxMessageView.Text += "\n";
                    }
                }
                break;

                case 0x8095:
                {
                    UInt16 u16ClusterId = 0;

                    u16ClusterId = au8Data[2];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[3];

                    richTextBoxMessageView.Text += " (On/Off Update)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  EndPoint: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterId);
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Src Addr Mode: 0x" + au8Data[4].ToString("X2");
                    richTextBoxMessageView.Text += "\n";

                    if (au8Data[4] == 0x03)
                    {
                    }
                    else
                    {
                        UInt16 u16Addr = 0;

                        u16Addr = au8Data[5];
                        u16Addr <<= 8;
                        u16Addr |= au8Data[6];

                        richTextBoxMessageView.Text += "  Src Addr Mode: 0x" + u16Addr.ToString("X4");
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "  Status: 0x" + au8Data[7].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                    }
                }
                break;

                case 0x80A0:
                {
                    UInt16 u16ClusterId = 0, u16GroupId = 0, u16TransTime = 0, u16SceneLength = 0;
                    byte u8Status;

                    u16ClusterId = au8Data[2];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[3];

                    u8Status = au8Data[4];

                    u16GroupId = au8Data[5];
                    u16GroupId <<= 8;
                    u16GroupId |= au8Data[6];


                    richTextBoxMessageView.Text += " (View Scene)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  EndPoint: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Cluster ID: 0x" + u16ClusterId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + u8Status.ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Group ID: 0x" + u16GroupId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Scene Id: 0x" + au8Data[7].ToString("X2");

                    if (0 == u8Status)
                    {
                        u16TransTime = au8Data[8];
                        u16TransTime <<= 8;
                        u16TransTime |= au8Data[9];

                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "  Transition Time: 0x" + u16TransTime.ToString("X4");
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "  Scene Name Length: 0x" + au8Data[10].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "  Scene Name Max Length: 0x" + au8Data[11].ToString("X2");
                        richTextBoxMessageView.Text += "\n";

                        richTextBoxMessageView.Text += "  Scene Name: ";

                        byte i = 0;
                        for (i = 0; i < au8Data[10]; i++)
                        {
                            richTextBoxMessageView.Text += Convert.ToChar(au8Data[12 + i]);
                        }
                    
                        u16SceneLength = au8Data[12 + i];
                        u16SceneLength <<= 8;
                        u16SceneLength |= au8Data[13 + i];

                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "  Ext Scene Length: 0x" + u16SceneLength.ToString("X4");
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "  Ext Max Length: 0x" + au8Data[14 + i].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "  Scene Data: ";
                        richTextBoxMessageView.Text += "\n      ";
                    
                        for (byte c = 0; i < u16SceneLength; i++)
                        {
                            richTextBoxMessageView.Text += "0x" + au8Data[15 + i + c].ToString("X2") + " ";
                        }
                    }
                    
                }
                break;

                case 0x80A3:
                {
                    UInt16 u16ClusterId, u16GroupId;

                    u16ClusterId = au8Data[2];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[3];

                    u16GroupId = au8Data[5];
                    u16GroupId <<= 8;
                    u16GroupId |= au8Data[6];

                    richTextBoxMessageView.Text += " (Remove All Scenes)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  EndPoint: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Cluster ID: 0x" + u16ClusterId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[4].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Group ID: 0x" + u16GroupId.ToString("X4");
                }
                break;

                case 0x80A2:
                {
                    UInt16 u16ClusterId, u16GroupId;

                    u16ClusterId = au8Data[2];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[3];

                    u16GroupId = au8Data[5];
                    u16GroupId <<= 8;
                    u16GroupId |= au8Data[6];

                    richTextBoxMessageView.Text += " (Remove Scene)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  EndPoint: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Cluster ID: 0x" + u16ClusterId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[4].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Group ID: 0x" + u16GroupId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Scene ID: 0x" + au8Data[7].ToString("X2");
                }
                break;

                case 0x8100: // Read attribute response
                {
                    UInt16 u16ClusterId = 0;
                    UInt16 u16AttribId = 0;
                    UInt16 u16SrcAddr = 0;
                    UInt16 u16AttributeSize = 0;

                    u16SrcAddr = au8Data[1];
                    u16SrcAddr <<= 8;
                    u16SrcAddr |= au8Data[2];

                    u16ClusterId = au8Data[4];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[5];

                    u16AttribId = au8Data[6];
                    u16AttribId <<= 8;
                    u16AttribId |= au8Data[7];

                    u16AttributeSize = au8Data[10];
                    u16AttributeSize <<= 8;
                    u16AttributeSize |= au8Data[11];

                    richTextBoxMessageView.Text += " (Read Attrib Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Src Addr: 0x" + u16SrcAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";                    
                    richTextBoxMessageView.Text += "  EndPoint: 0x" + au8Data[3].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[8].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterId);                    
                    richTextBoxMessageView.Text += "\n";
                    displayAttribute(u16AttribId, au8Data[9], au8Data, 12, u16AttributeSize);
                }
                break;

                case 0x8101:
                {
                    UInt16 u16ClusterId = 0;
                    UInt16 u16DstAddr = 0;

                    u16ClusterId = au8Data[13];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[14];

                    u16DstAddr = au8Data[1];
                    u16DstAddr <<= 8;
                    u16DstAddr |= au8Data[2];

                    richTextBoxMessageView.Text += " (Default Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Short Address: 0x" + u16DstAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Source EndPoint: 0x" + au8Data[11].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Destination EndPoint: 0x" + au8Data[12].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterId);
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Command: 0x" + au8Data[15].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[16].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8120:
                {
                    UInt16 u16ClusterId = 0;
                    UInt16 u16SrcAddr = 0;

                    u16ClusterId = au8Data[4];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[5];

                    u16SrcAddr = au8Data[1];
                    u16SrcAddr <<= 8;
                    u16SrcAddr |= au8Data[2];

                    richTextBoxMessageView.Text += " (Report Config Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Src Addr: 0x" + u16SrcAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  EndPoint: 0x" + au8Data[3].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterId);
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[6].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8102:
                {
                    UInt16 u16SrcAddr = 0;
                    UInt16 u16ClusterId = 0;
                    UInt16 u16AttribId = 0;
                    UInt16 u16AttributeSize = 0;

                    u16SrcAddr = au8Data[1];
                    u16SrcAddr <<= 8;
                    u16SrcAddr |= au8Data[2];
                    
                    u16ClusterId = au8Data[4];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[5];

                    u16AttribId = au8Data[6];
                    u16AttribId <<= 8;
                    u16AttribId |= au8Data[7];

                    u16AttributeSize = au8Data[10];
                    u16AttributeSize <<= 8;
                    u16AttributeSize |= au8Data[11];

                    richTextBoxMessageView.Text += " (Attribute Report)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Src Addr: 0x" + u16SrcAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Src Ep: 0x" + au8Data[3].ToString("X2");
                    richTextBoxMessageView.Text += "\n";                    
                    displayClusterId(u16ClusterId);
                    richTextBoxMessageView.Text += "\n";
                    displayAttribute(u16AttribId, au8Data[9], au8Data, 12, u16AttributeSize);
                }
                break;

                case 0x8122:
                {
                    UInt16 u16SrcAddr = 0;
                    UInt16 u16ClusterId = 0;
                    UInt16 u16AttribId = 0;
                    UInt16 u16MaxInterval = 0;
                    UInt16 u16MinInterval = 0;

                    u16SrcAddr = au8Data[1];
                    u16SrcAddr <<= 8;
                    u16SrcAddr |= au8Data[2];

                    u16ClusterId = au8Data[4];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[5];

                    u16AttribId = au8Data[8];
                    u16AttribId <<= 8;
                    u16AttribId |= au8Data[9];

                    u16MaxInterval = au8Data[10];
                    u16MaxInterval <<= 8;
                    u16MaxInterval |= au8Data[11];

                    u16MinInterval = au8Data[12];
                    u16MinInterval <<= 8;
                    u16MinInterval |= au8Data[13];

                    richTextBoxMessageView.Text += " (Attribute Config Report)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Src Addr: 0x" + u16SrcAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Src Ep: 0x" + au8Data[3].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterId);
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[6].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayDataType(au8Data[7]);
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Attribute: 0x" + u16AttribId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Min Interval: " + u16MinInterval.ToString();
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Max Interval: " + u16MaxInterval.ToString();
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8103: // Read local attribute response
                {
                    UInt16 u16ClusterId = 0;
                    UInt16 u16AttribId = 0;
                    UInt16 u16SrcAddr = 0;
                    UInt16 u16AttributeSize = 0;

                    u16SrcAddr = au8Data[1];
                    u16SrcAddr <<= 8;
                    u16SrcAddr |= au8Data[2];

                    u16ClusterId = au8Data[4];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[5];

                    u16AttribId = au8Data[6];
                    u16AttribId <<= 8;
                    u16AttribId |= au8Data[7];

                    u16AttributeSize = au8Data[10];
                    u16AttributeSize <<= 8;
                    u16AttributeSize |= au8Data[11];

                    richTextBoxMessageView.Text += " (Read Local Attrib Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    //richTextBoxMessageView.Text += "  Src Addr: 0x" + u16SrcAddr.ToString("X4");
                    //richTextBoxMessageView.Text += "\n";                    
                    richTextBoxMessageView.Text += "  EndPoint: 0x" + au8Data[3].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[8].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterId);                    
                    richTextBoxMessageView.Text += "\n";
                    displayAttribute(u16AttribId, au8Data[9], au8Data, 12, u16AttributeSize);
                }
                break;
                
                case 0x8140: // Discover attribute response
                {
                    UInt16 u16AttribId = 0;

                    u16AttribId = au8Data[2];
                    u16AttribId <<= 8;
                    u16AttribId |= au8Data[3];

                    richTextBoxMessageView.Text += " (Discover Attrib Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Complete: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayDataType(au8Data[1]);
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Attribute: 0x" + u16AttribId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8141: // Discover extended attribute response
                {
                    UInt16 u16AttribId = 0;

                    u16AttribId = au8Data[2];
                    u16AttribId <<= 8;
                    u16AttribId |= au8Data[3];

                    richTextBoxMessageView.Text += " (Discover Attrib Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Complete: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayDataType(au8Data[1]);
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Attribute: 0x" + u16AttribId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Flags: 0x" + au8Data[4].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8150: // Discover command received individual response
                {
                    richTextBoxMessageView.Text += " (Discover Command Received Individual Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Command: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Index: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8151: // Discover command received response
                {
                    richTextBoxMessageView.Text += " (Discover Command Received Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Complete: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Commands: " + au8Data[1].ToString();
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8160: // Discover command generated individual response
                {
                    richTextBoxMessageView.Text += " (Discover Command Generated Individual Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Command: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Index: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8161: // Discover command generated response
                {
                    richTextBoxMessageView.Text += " (Discover Command Generated Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Complete: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Commands: " + au8Data[1].ToString();
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8401:
                {
                    UInt16 u16ClusterId = 0;
                    UInt16 u16ZoneStatus = 0;
                    UInt16 u16Delay = 0;

                    u16ClusterId = au8Data[2];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[3];

                    richTextBoxMessageView.Text += " (IAS Zone Status Change)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  EndPoint: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterId);
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Src Addr Mode: 0x" + au8Data[4].ToString("X2");
                    richTextBoxMessageView.Text += "\n";

                    if (au8Data[4] == 0x03)
                    {
                    }
                    else
                    {
                        UInt16 u16Addr = 0;

                        u16Addr = au8Data[5];
                        u16Addr <<= 8;
                        u16Addr |= au8Data[6];

                        richTextBoxMessageView.Text += "  Src Addr Mode: 0x" + u16Addr.ToString("X4");
                        richTextBoxMessageView.Text += "\n";
                    }

                    u16ZoneStatus   = au8Data[7];
                    u16ZoneStatus <<= 8;
                    u16ZoneStatus  |= au8Data[8];

                    richTextBoxMessageView.Text += "  Zone Status: 0x" + u16ZoneStatus.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Ext Status: 0x" + au8Data[9].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Zone ID: 0x" + au8Data[10].ToString("X2");
                    richTextBoxMessageView.Text += "\n";

                    u16Delay   = au8Data[11];
                    u16Delay <<= 8;
                    u16Delay  |= au8Data[12];

                    richTextBoxMessageView.Text += "  Delay: 0x" + u16Delay.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x004D:
                {
                    UInt16 u16ShortAddr = 0;
                    UInt64 u64ExtAddr = 0;

                    u16ShortAddr = au8Data[0];
                    u16ShortAddr <<= 8;
                    u16ShortAddr |= au8Data[1];

                    for (int i = 0; i < 8; i++)
                    {
                        u64ExtAddr <<= 8;
                        u64ExtAddr |= au8Data[2 + i];
                    }

                    richTextBoxMessageView.Text += " (End Device Announce)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Short Address: 0x" + u16ShortAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Extended Address: 0x" + u64ExtAddr.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    displayMACcapability(au8Data[10]);
                }
                break;

                case 0x8501:
                {
                    byte u8Offset = 0;
                    byte u8SQN;
                    byte u8SrcEndpoint;
                    UInt16 u16ClusterId;
                    UInt16 u16SrcAddr;
                    byte u8SrcAddrMode;
                    UInt64 u64RequestNodeAddress;
                    UInt32 u32FileOffset;
                    UInt32 u32FileVersion;
                    UInt16 u16ImageType;
                    UInt16 u16ManufactureCode;
                    UInt16 u16BlockRequestDelay;
                    byte u8MaxDataSize;
                    byte u8FieldControl;

                    u8SQN = au8Data[u8Offset++];

                    u8SrcEndpoint = au8Data[u8Offset++];

                    u16ClusterId = au8Data[u8Offset++];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[u8Offset++];

                    u8SrcAddrMode = au8Data[u8Offset++];

                    u16SrcAddr = au8Data[u8Offset++];
                    u16SrcAddr <<= 8;
                    u16SrcAddr |= au8Data[u8Offset++];

                    u64RequestNodeAddress = au8Data[u8Offset++];
                    u64RequestNodeAddress <<= 8;
                    u64RequestNodeAddress |= au8Data[u8Offset++];
                    u64RequestNodeAddress <<= 8;
                    u64RequestNodeAddress |= au8Data[u8Offset++];
                    u64RequestNodeAddress <<= 8;
                    u64RequestNodeAddress |= au8Data[u8Offset++];
                    u64RequestNodeAddress <<= 8;
                    u64RequestNodeAddress |= au8Data[u8Offset++];
                    u64RequestNodeAddress <<= 8;
                    u64RequestNodeAddress |= au8Data[u8Offset++];
                    u64RequestNodeAddress <<= 8;
                    u64RequestNodeAddress |= au8Data[u8Offset++];
                    u64RequestNodeAddress <<= 8;
                    u64RequestNodeAddress |= au8Data[u8Offset++];

                    u32FileOffset = au8Data[u8Offset++];
                    u32FileOffset <<= 8;
                    u32FileOffset |= au8Data[u8Offset++];
                    u32FileOffset <<= 8;
                    u32FileOffset |= au8Data[u8Offset++];
                    u32FileOffset <<= 8;
                    u32FileOffset |= au8Data[u8Offset++];

                    u32FileVersion = au8Data[u8Offset++];
                    u32FileVersion <<= 8;
                    u32FileVersion |= au8Data[u8Offset++];
                    u32FileVersion <<= 8;
                    u32FileVersion |= au8Data[u8Offset++];
                    u32FileVersion <<= 8;
                    u32FileVersion |= au8Data[u8Offset++];

                    u16ImageType = au8Data[u8Offset++];
                    u16ImageType <<= 8;
                    u16ImageType |= au8Data[u8Offset++];

                    u16ManufactureCode = au8Data[u8Offset++];
                    u16ManufactureCode <<= 8;
                    u16ManufactureCode |= au8Data[u8Offset++];

                    u16BlockRequestDelay = au8Data[u8Offset++];
                    u16BlockRequestDelay <<= 8;
                    u16BlockRequestDelay |= au8Data[u8Offset++];

                    u8MaxDataSize = au8Data[u8Offset++];

                    u8FieldControl = au8Data[u8Offset++];

                    /*
                    richTextBoxMessageView.Text += " (OTA Block Request)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + u8SQN.ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                     */

                    richTextBoxMessageView.Text = "";
                    richTextBoxCommandResponse.Text = "";


                    /*
                    richTextBoxMessageView.Text += "  Src Addr Mode: 0x" + u8SrcAddrMode.ToString("X2");
                    richTextBoxMessageView.Text += "\n";                    
                    richTextBoxMessageView.Text += "  Src Addr: 0x" + u16SrcAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  EndPoint: 0x" + u8SrcEndpoint.ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterId);
                    richTextBoxMessageView.Text += "\n";

                    if ((u8FieldControl & 0x01) == 0x01)
                    {
                        richTextBoxMessageView.Text += "  Node Addr: 0x" + u64RequestNodeAddress.ToString("X16");
                        richTextBoxMessageView.Text += "\n";
                    }

                    richTextBoxMessageView.Text += "  File Offset: 0x" + u32FileOffset.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  File Version: 0x" + u32FileVersion.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Image Type: 0x" + u16ImageType.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Manu Code: 0x" + u16ManufactureCode.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Block Delay: 0x" + u16BlockRequestDelay.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Max Data Size: 0x" + u8MaxDataSize.ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Field Control: 0x" + u8FieldControl.ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    */
                    // Send response 
                    if (u8OTAWaitForDataParamsPending == 0)
                    {
                        byte u8NbrBytes = 0;

                        if ((u32FileOffset + u8MaxDataSize) > u32OtaFileTotalImage)
                        {
                            u8NbrBytes = (byte)(u32OtaFileTotalImage - u32FileOffset);
                        }
                        else
                        {
                            u8NbrBytes = u8MaxDataSize;
                        }
                        sendOtaBlock(u8SrcAddrMode, u16SrcAddr, 1, u8SrcEndpoint, u8SQN, 0, u32FileOffset, u32FileVersion, u16ImageType, u16ManufactureCode, u8NbrBytes, au8OTAFile);
                    }
                    else
                    {
                        sendOtaSetWaitForDataParams(u8SrcAddrMode, u16SrcAddr, 1, u8SrcEndpoint, u8SQN, 0x97, u32OTAWaitForDataParamsCurrentTime, u32OTAWaitForDataParamsRequestTime, u16OTAWaitForDataParamsBlockDelay);
                        u8OTAWaitForDataParamsPending = 0;
                    }

                    if (u8OtaInProgress == 0)
                    {
                        u8OtaInProgress = 1;
                        textBoxOtaDownloadStatus.Text = "In Progress";
                        progressBarOtaDownloadProgress.Value = 0;
                        textBoxOtaFileOffset.Text = "0";
                    }
                    else
                    {
                        UInt32 u32PercentComplete = (u32FileOffset * 1000) / u32OtaFileTotalImage;
                        progressBarOtaDownloadProgress.Value = (int)u32PercentComplete;
                        textBoxOtaFileOffset.Text = u32FileOffset.ToString();
                    }
                }
                break;
                case 0x8503:
                {
                    
                    byte u8Offset = 0;
                    byte u8SQN;
                    byte u8SrcEndpoint;
                    UInt16 u16ClusterId;
                    UInt16 u16SrcAddr;
                    byte u8SrcAddrMode;
                    UInt32 u32FileVersion;
                    UInt16 u16ImageType;
                    UInt16 u16ManufactureCode;
                    byte u8Status;

                    u8SQN = au8Data[u8Offset++];

                    u8SrcEndpoint = au8Data[u8Offset++];

                    u16ClusterId = au8Data[u8Offset++];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[u8Offset++];

                    u8SrcAddrMode = au8Data[u8Offset++];

                    u16SrcAddr = au8Data[u8Offset++];
                    u16SrcAddr <<= 8;
                    u16SrcAddr |= au8Data[u8Offset++];

                    u32FileVersion = au8Data[u8Offset++];
                    u32FileVersion <<= 8;
                    u32FileVersion |= au8Data[u8Offset++];
                    u32FileVersion <<= 8;
                    u32FileVersion |= au8Data[u8Offset++];
                    u32FileVersion <<= 8;
                    u32FileVersion |= au8Data[u8Offset++];

                    u16ImageType = au8Data[u8Offset++];
                    u16ImageType <<= 8;
                    u16ImageType |= au8Data[u8Offset++];

                    u16ManufactureCode = au8Data[u8Offset++];
                    u16ManufactureCode <<= 8;
                    u16ManufactureCode |= au8Data[u8Offset++];

                    u8Status = au8Data[u8Offset++];

                    richTextBoxMessageView.Text += " (OTA End Request)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + u8SQN.ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Src Addr Mode: 0x" + u8SrcAddrMode.ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Src Addr: 0x" + u16SrcAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  EndPoint: 0x" + u8SrcEndpoint.ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterId);
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  File Version: 0x" + u32FileVersion.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Image Type: 0x" + u16ImageType.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Manu Code: 0x" + u16ManufactureCode.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + u8Status.ToString("X2");
                    richTextBoxMessageView.Text += "\n";

                    //sendOtaEndResponse(u8SrcAddrMode, u16SrcAddr, 1, u8SrcEndpoint, u8SQN, 5, 10, u32FileVersion, u16ImageType, u16ManufactureCode);

                 
                    textBoxOtaDownloadStatus.Text = "Complete";
                    textBoxOtaFileOffset.Text = "";
                    progressBarOtaDownloadProgress.Value = 0;
                    u8OtaInProgress = 0;  
                }
                break;

                case 0x8110:
                {
                    UInt16 u16SrcAddr = 0;
                    UInt16 u16ClusterId = 0;
                    UInt16 u16AttribId = 0;
                    UInt16 u16AttributeSize = 0;

                    u16SrcAddr = au8Data[1];
                    u16SrcAddr <<= 8;
                    u16SrcAddr |= au8Data[2];

                    u16ClusterId = au8Data[4];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[5];

                    u16AttribId = au8Data[6];
                    u16AttribId <<= 8;
                    u16AttribId |= au8Data[7];

                    u16AttributeSize = au8Data[10];
                    u16AttributeSize <<= 8;
                    u16AttributeSize |= au8Data[11];
                                    
                    richTextBoxMessageView.Text += " (Write Attrib Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Src Addr: 0x" + u16SrcAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Src Ep: 0x" + au8Data[3].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    displayClusterId(u16ClusterId);
                    richTextBoxMessageView.Text += "\n";
                    displayAttribute(u16AttribId, au8Data[9], au8Data, 12, u16AttributeSize);
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[8].ToString("X2");
                    richTextBoxMessageView.Text += "\n"; 
                }
                break;
				
				case 0x8600:
                {
                    nwkRecovery.NetworkRecoveryParseBuffer(au8Data);
                    richTextBoxMessageView.Text += " (Retrieve Network Recovery Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += nwkRecovery.ToString();
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8601:
                {
                    richTextBoxMessageView.Text += " (Restore Network Recovery Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Success = " + au8Data[0];
                    richTextBoxMessageView.Text += "\n";
                }
                break;

				case 0x80A4:
				{
				    UInt16 u16GroupId;
                    UInt16 u16ClusterId;

                    u16ClusterId = au8Data[2];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[3];

                    u16GroupId = au8Data[5];
                    u16GroupId <<= 8;
                    u16GroupId |= au8Data[6];

                    richTextBoxMessageView.Text += " (Store Scene Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Tx Num: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Source Endpoint: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Cluster ID: 0x" + u16ClusterId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[4].ToString("X2");
					richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Group ID: 0x" + u16GroupId.ToString("X4");
					richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Scene ID: 0x" + au8Data[7].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
				}
                break;

                case 0x80A1:
                {
                    UInt16 u16GroupId;
                    UInt16 u16ClusterId;

                    u16ClusterId = au8Data[2];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[3];

                    u16GroupId = au8Data[5];
                    u16GroupId <<= 8;
                    u16GroupId |= au8Data[6];

                    richTextBoxMessageView.Text += " (Add Scene Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Tx Num: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Source Endpoint: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Cluster ID: 0x" + u16ClusterId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[4].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Group ID: 0x" + u16GroupId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Scene ID: 0x" + au8Data[7].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x80A6:
                {
                    UInt16 u16GroupId;
                    UInt16 u16ClusterId;

                    u16ClusterId = au8Data[2];
                    u16ClusterId <<= 8;
                    u16ClusterId |= au8Data[3];

                    u16GroupId = au8Data[6];
                    u16GroupId <<= 8;
                    u16GroupId |= au8Data[7];

                    richTextBoxMessageView.Text += " (Get Scene Membership Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Tx Num: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Source Endpoint: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Cluster ID: 0x" + u16ClusterId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[4].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Capacity: 0x" + au8Data[5].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Group ID: 0x" + u16GroupId.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Scene Count: 0x" + au8Data[8].ToString("X2");

                    if (au8Data[8] != 0)
                    {
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "  Scene List: ";
                    }

                    byte i;

                    for (i = 0; i < au8Data[8]; i++)
                    {

                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "    Scene: 0x" + au8Data[i+9].ToString("X2");
                    }
                    richTextBoxMessageView.Text += "\n";
                }
                break;
				case 0x8046:
				{
					UInt16 u16AddrOfInterest;
					
					u16AddrOfInterest = au8Data[2];
					u16AddrOfInterest <<= 8;
					u16AddrOfInterest |= au8Data[3];

                    richTextBoxMessageView.Text += " (Match Descriptor Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
					richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Address Of Interest: 0x" + u16AddrOfInterest.ToString("X4");
					richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Match Length: " + au8Data[4];

                    if (au8Data[4] != 0)
                    {
                        richTextBoxMessageView.Text += "  Matched Endpoints: ";
                    }

					byte i;
					for (i = 0; i < au8Data[4]; i++)
                    {
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "    Endpoint " + au8Data[5 + i].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
					}
				}
                break;
				case 0x8044:
				{
                    richTextBoxMessageView.Text += " (Power Descriptor Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
					richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Power Source Level: " + Convert.ToString(au8Data[2] & 0x7, 2).PadLeft(4, '0');
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Current Power Source: " + Convert.ToString((au8Data[2] >> 4) & 0x7, 2).PadLeft(4, '0');
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Available Power Source: " + Convert.ToString((au8Data[3]) & 0x7, 2).PadLeft(4, '0');
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Current Power Mode: " + Convert.ToString((au8Data[3] >> 4) & 0x7, 2).PadLeft(4, '0');
                    richTextBoxMessageView.Text += "\n";
				}
                break;

                case 0x8701:
                {
                    richTextBoxMessageView.Text += " (Route Discovery Confirm)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Network Status: 0x" + au8Data[2].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                }
                break;
                case 0x8702:
                {
                    UInt16 u16DestAddr;

                    u16DestAddr = au8Data[4];
                    u16DestAddr <<= 8;
                    u16DestAddr |= au8Data[5];

                    richTextBoxMessageView.Text += " (APS Data Confirm Fail)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Source Endpoint: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Destination Endpoint: 0x" + au8Data[2].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Destination Mode: 0x" + au8Data[3].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Destination Address: 0x" + u16DestAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[6].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                }
                break;

                case 0x8531:
                {
                    UInt16 u16AddressOfInterest;

                    u16AddressOfInterest = au8Data[2];
                    u16AddressOfInterest <<= 8;
                    u16AddressOfInterest |= au8Data[3];

                    richTextBoxMessageView.Text += " (Complex Descriptor Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Address of Interest: 0x" + u16AddressOfInterest.ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Length: " + au8Data[4].ToString("X2");
                    richTextBoxMessageView.Text += "\n";

                    if (au8Data[1] == 0)
                    {
                        richTextBoxMessageView.Text += "        XML Tag: " + au8Data[5].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "        Field Count: " + au8Data[6].ToString("X2");
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "        Complex Description: ";
                        for (int i = 0; i < au8Data[6]; i++)
                        {
                            char c = (char)au8Data[6 + i + 1];
                            richTextBoxMessageView.Text += c.ToString();
                        }
                        richTextBoxMessageView.Text += "\n";
                    }                                       
                }
                break;

                case 0x8532:
                {
                    byte u8StrLen;
                    UInt16 u16NwkAddr = 0;

                    u16NwkAddr = au8Data[2];
                    u16NwkAddr <<= 8;
                    u16NwkAddr |= au8Data[3];
                    u8StrLen = au8Data[4];

                    richTextBoxMessageView.Text += " (User Descriptor Request Response)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Nwk Address: 0x" + u16NwkAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";

                    if (au8Data[1] == 0)
                    {
                        richTextBoxMessageView.Text += "  Length: " + u8StrLen.ToString();
                        richTextBoxMessageView.Text += "\n";
                        richTextBoxMessageView.Text += "  Descriptor: ";

                        for (int i = 0; i < u8StrLen; i++)
                        {
                            char c = (char)au8Data[5 + i];
                            richTextBoxMessageView.Text += c.ToString();
                        }
                        richTextBoxMessageView.Text += "\n";
                    }
                }
                break;

                case 0x8533:
                {
                    byte u8StrLen;
                    UInt16 u16NwkAddr = 0;

                    u16NwkAddr = au8Data[2];
                    u16NwkAddr <<= 8;
                    u16NwkAddr |= au8Data[3];
                    u8StrLen = au8Data[4];

                    richTextBoxMessageView.Text += " (User Descriptor Set Confirm)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  SQN: 0x" + au8Data[0].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Status: 0x" + au8Data[1].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Nwk Address: 0x" + u16NwkAddr.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                }
                break;


                default:
                {
                    richTextBoxMessageView.Text += " (Unrecognized)";
                    richTextBoxMessageView.Text += "\n";
                }
                break;
            }
        }

        private void displayAttribute(UInt16 u16AttribId, byte u8AttribType, byte[] au8AttribData, byte u8AttribIndex, UInt16 u16AttrSize)
        {
            richTextBoxMessageView.Text += "  Attribute ID: 0x" + u16AttribId.ToString("X4");
            richTextBoxMessageView.Text += "\n";
            richTextBoxMessageView.Text += "  Attribute Size: 0x" + u16AttrSize.ToString("X4");
            richTextBoxMessageView.Text += "\n";
            richTextBoxMessageView.Text += "  Attribute Type: 0x" + u8AttribType.ToString("X2");
            
            switch (u8AttribType)
            {
                case 0x10:
                    richTextBoxMessageView.Text += " (Boolean)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Attribute Data: 0x" + au8AttribData[u8AttribIndex].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    break;
                case 0x18:
                    richTextBoxMessageView.Text += " (8-bit Bitmap)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Attribute Data: 0x" + au8AttribData[u8AttribIndex].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    break;
                case 0x20:
                    richTextBoxMessageView.Text += " (UINT8)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Attribute Data: 0x" + au8AttribData[u8AttribIndex].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    break;
                case 0x21:
                    UInt16 u16Data;
                    u16Data   = au8AttribData[u8AttribIndex];
                    u16Data <<= 8;
                    u16Data  |= au8AttribData[u8AttribIndex + 1];
                    richTextBoxMessageView.Text += " (UINT16)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Attribute Data: 0x" + u16Data.ToString("X4");
                    richTextBoxMessageView.Text += "\n";
                    break;
                case 0x23:
                    UInt32 u32Data;
                    u32Data = au8AttribData[u8AttribIndex];
                    u32Data <<= 8;
                    u32Data |= au8AttribData[u8AttribIndex + 1];
                    u32Data <<= 8;
                    u32Data |= au8AttribData[u8AttribIndex + 2];
                    u32Data <<= 8;
                    u32Data |= au8AttribData[u8AttribIndex + 3];
                    richTextBoxMessageView.Text += " (UINT32)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Attribute Data: 0x" + u32Data.ToString("X8");
                    richTextBoxMessageView.Text += "\n";
                    break;
                case 0x29: 
                    richTextBoxMessageView.Text += " (INT16)";
                    richTextBoxMessageView.Text += "\n";
                    break;
                case 0x30:
                    richTextBoxMessageView.Text += " (8-bit Enumeration)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Attribute Data: 0x" + au8AttribData[u8AttribIndex].ToString("X2");
                    richTextBoxMessageView.Text += "\n";
                    break;
                case 0x42:
                    richTextBoxMessageView.Text += " (Character String)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Attribute Data (Len - " + u16AttrSize.ToString() + "): ";
                    for (int i = 0; i < u16AttrSize; i++)
                    {
                        char c = (char)au8AttribData[u8AttribIndex + i];
                        richTextBoxMessageView.Text += c.ToString();
                    }                    
                    richTextBoxMessageView.Text += "\n";
                    break;
                case 0xF0:
                    richTextBoxMessageView.Text += " (IEEE Address)";
                    richTextBoxMessageView.Text += "\n";
                    richTextBoxMessageView.Text += "  Attribute Data: " + au8AttribData[u8AttribIndex].ToString("X2");
                    richTextBoxMessageView.Text += ":" + au8AttribData[u8AttribIndex + 1].ToString("X2");
                    richTextBoxMessageView.Text += ":" + au8AttribData[u8AttribIndex + 2].ToString("X2");
                    richTextBoxMessageView.Text += ":" + au8AttribData[u8AttribIndex + 3].ToString("X2");
                    richTextBoxMessageView.Text += ":" + au8AttribData[u8AttribIndex + 4].ToString("X2");
                    richTextBoxMessageView.Text += ":" + au8AttribData[u8AttribIndex + 5].ToString("X2");
                    richTextBoxMessageView.Text += ":" + au8AttribData[u8AttribIndex + 6].ToString("X2");
                    richTextBoxMessageView.Text += ":" + au8AttribData[u8AttribIndex + 7].ToString("X2");                    
                    richTextBoxMessageView.Text += "\n";
                    break;
                default:
                    richTextBoxMessageView.Text += " (Unknown)";
                    richTextBoxMessageView.Text += "\n";
                    break;
            }                        
        }

        private void displayMACcapability(byte u8Capability)
        {
            richTextBoxMessageView.Text += "  MAC Capability: 0x" + u8Capability.ToString("X2");
            richTextBoxMessageView.Text += "\n";
            richTextBoxMessageView.Text += "    Alternate PAN Coordinator: " + (((u8Capability & 0x01) == 0) ? "False" : "True");
            richTextBoxMessageView.Text += "\n";
            richTextBoxMessageView.Text += "    Device Type: " + (((u8Capability & 0x02) == 0) ? "End Device" : "Router");
            richTextBoxMessageView.Text += "\n";
            richTextBoxMessageView.Text += "    Power Source: " + (((u8Capability & 0x04) == 0) ? "Battery" : "AC");
            richTextBoxMessageView.Text += "\n";
            richTextBoxMessageView.Text += "    Receiver On When Idle: " + (((u8Capability & 0x08) == 0) ? "False" : "True");
            richTextBoxMessageView.Text += "\n";
            richTextBoxMessageView.Text += "    Security Capability: " + (((u8Capability & 0x40) == 0) ? "Standard" : "High");
            richTextBoxMessageView.Text += "\n";
            richTextBoxMessageView.Text += "    Allocate Address: " + (((u8Capability & 0x80) == 0) ? "False" : "True");
            richTextBoxMessageView.Text += "\n";        
        }

        private void displayDescriptorCapability(byte u8Capability)
        {
            richTextBoxMessageView.Text += "  Descriptor Capability: 0x" + u8Capability.ToString("X2");
            richTextBoxMessageView.Text += "\n";
            richTextBoxMessageView.Text += "    Ext Active EP List: " + (((u8Capability & 0x01) == 0) ? "No" : "Yes");
            richTextBoxMessageView.Text += "\n";
            richTextBoxMessageView.Text += "    Ext Simple Desc List: " + (((u8Capability & 0x02) == 0) ? "No" : "Yes");
            richTextBoxMessageView.Text += "\n";
        }

        private void displayDeviceId(UInt16 u16DeviceId)
        {
            Dictionary<int, string> deviceList = new Dictionary<int, string>();
            deviceList.Add(0x0000, " (Generic - On/Off Switch)");
            deviceList.Add(0x0001, " (Generic - Level Control Switch)");
            deviceList.Add(0x0002, " (Generic - On/Off Output)");
            deviceList.Add(0x0003, " (Generic - Level Controlable Output)");
            deviceList.Add(0x0004, " (Generic - Scene Selector)");
            deviceList.Add(0x0005, " (Generic - Configuration Tool)");
            deviceList.Add(0x0006, " (Generic - Remote Control)");
            deviceList.Add(0x0007, " (Generic - Combined Interface)");
            deviceList.Add(0x0008, " (Generic - Range Extender)");
            deviceList.Add(0x0009, " (Generic - Mains Power Outlet)");
            deviceList.Add(0x000C, " (Generic - Simple Sensor)");
            deviceList.Add(0x0051, " (Generic - Smart Plug)");
            deviceList.Add(0x0100, " (Lighting - On/Off Light)");
            deviceList.Add(0x0101, " (Lighting - Dimmable Light)");
            deviceList.Add(0x0102, " (Lighting - Color Dimmable Light)");
            deviceList.Add(0x0103, " (Lighting - On/Off Light Switch)");
            deviceList.Add(0x0104, " (Lighting - Dimmer Switch)");
            deviceList.Add(0x0105, " (Lighting - Color Dimmer Switch)");
            deviceList.Add(0x0106, " (Lighting - Light Sensor)");
            deviceList.Add(0x0107, " (Lighting - Occupancy Sensor)");
            deviceList.Add(0x0202, " (HVAC - Fan Control)");
            deviceList.Add(0x0301, " (HVAC - Thermostat)");
            deviceList.Add(0x0500, " (IAS - IAS Zone)");
            deviceList.Add(0x0501, " (IAS - IAS ACE)");
            deviceList.Add(0x0502, " (IAS - IAS WD)");

            
                                    
            richTextBoxMessageView.Text += "  Device ID: 0x" + u16DeviceId.ToString("X4");

            // The indexer throws an exception if the requested key is 
            // not in the dictionary. 
            try
            {
                richTextBoxMessageView.Text += deviceList[u16DeviceId];
            }
            catch (KeyNotFoundException)
            {
                richTextBoxMessageView.Text += " (Unknown)";
            }
        }

        private void displayProfileId(UInt16 u16ProfileId)
        {
            Dictionary<int, string> profileList = new Dictionary<int, string>();
            profileList.Add(0x0104, " (ZigBee HA)");
            profileList.Add(0xC05E, " (ZigBee LL)");

            richTextBoxMessageView.Text += "  Profile ID: 0x" + u16ProfileId.ToString("X4");

            // The indexer throws an exception if the requested key is 
            // not in the dictionary. 
            try
            {
                richTextBoxMessageView.Text += profileList[u16ProfileId];
            }
            catch (KeyNotFoundException)
            {
                richTextBoxMessageView.Text += " (Unknown)";
            }
        }

        private void displayClusterId(UInt16 u16ClusterId)
        {
            Dictionary<int, string> clusterList = new Dictionary<int, string>();
            clusterList.Add(0x0000, " (General: Basic)");
            clusterList.Add(0x0001, " (General: Power Config)");
            clusterList.Add(0x0002, " (General: Temperature Config)");
            clusterList.Add(0x0003, " (General: Identify)");
            clusterList.Add(0x0004, " (General: Groups)");
            clusterList.Add(0x0005, " (General: Scenes)");
            clusterList.Add(0x0006, " (General: On/Off)");
            clusterList.Add(0x0007, " (General: On/Off Config)");
            clusterList.Add(0x0008, " (General: Level Control)");
            clusterList.Add(0x0009, " (General: Alarms)");
            clusterList.Add(0x000A, " (General: Time)");
            clusterList.Add(0x000F, " (General: Binary Input Basic)");
            clusterList.Add(0x0020, " (General: Poll Control)");
            clusterList.Add(0x0019, " (General: OTA)");
            clusterList.Add(0x0101, " (General: Door Lock");
            clusterList.Add(0x0201, " (HVAC: Thermostat)");
            clusterList.Add(0x0202, " (HVAC: Fan Control)");
            clusterList.Add(0x0204, " (HVAC: Thermostat UI Config)");
            clusterList.Add(0x0300, " (Lighting: Color Control)");
            clusterList.Add(0x0400, " (Measurement: Illuminance)");
            clusterList.Add(0x0402, " (Measurement: Temperature)");
            clusterList.Add(0x0406, " (Measurement: Occupancy Sensing)");
            clusterList.Add(0x0500, " (Security & Safety: IAS Zone)");
            clusterList.Add(0x0502, " (Security & Safety: IAS WD)");
            clusterList.Add(0x0702, " (Smart Energy: Metering)");
            clusterList.Add(0x0B05, " (Misc: Diagnostics)");
            clusterList.Add(0x1000, " (ZLL: Commissioning)");

            richTextBoxMessageView.Text += "  Cluster ID: 0x" + u16ClusterId.ToString("X4");
            
            // The indexer throws an exception if the requested key is 
            // not in the dictionary. 
            try
            {
                richTextBoxMessageView.Text += clusterList[u16ClusterId];
            }
            catch (KeyNotFoundException)
            {
                richTextBoxMessageView.Text += " (Unknown)";
            }
        }

        private void displayDataType(byte u8Type)
        {
            Dictionary<byte, string> typeList = new Dictionary<byte, string>();
            typeList.Add(0x00, " (Null: No Data)");
            typeList.Add(0x10, " (Logical: Boolean)");
            typeList.Add(0x20, " (Unisgned Integer: UINT8)");
            typeList.Add(0x21, " (Unisgned Integer: UINT16)");
            typeList.Add(0x25, " (Unisgned Integer: UINT48)");
            typeList.Add(0x30, " (Enumeration: 8-bit)");
            typeList.Add(0x42, " (String: Character String)");

            richTextBoxMessageView.Text += "  Data Type: 0x" + u8Type.ToString("X2");

            // The indexer throws an exception if the requested key is 
            // not in the dictionary. 
            try
            {
                richTextBoxMessageView.Text += typeList[u8Type];
            }
            catch (KeyNotFoundException)
            {
                richTextBoxMessageView.Text += " (Unknown)";
            }
        }

        #endregion 

        #region serial receive functions

        private byte[] rxMessageData   = new byte[1024];
        private byte rxMessageChecksum = 0;
        private UInt16 rxMessageLength = 0;
        private uint rxMessageState    = 0;
        private UInt16 rxMessageType = 0;
        private uint rxMessageCount    = 0;
        private bool rxMessageInEscape = false;
        
        // Serial port event handlder 
        private void serialPort1_DataReceivedHandler(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            while (serialPort1.BytesToRead > 0)
            {
                byte rxByte = (byte)serialPort1.ReadByte();

                if (rxByte == 0x01)
                {
                    // Start character received
                    rxMessageChecksum = 0;
                    rxMessageLength   = 0;
                    rxMessageType     = 0;
                    rxMessageState    = 0;
                    rxMessageCount    = 0;
                    rxMessageInEscape = false;
                }
                else if (rxByte == 0x02)
                {
                    rxMessageInEscape = true;
                }
                else if (rxByte == 0x03)
                {
                    // instantiate the delegate to be invoked by this thread
                    messageParser = new MessageParser(myMessageParser);

                    // invoke the delegate in the MainForm thread
                    this.Invoke(messageParser);
                }
                else
                {
                    if (rxMessageInEscape == true)
                    {
                        rxByte ^= 0x10;
                        rxMessageInEscape = false;
                    }
                    
                    // Parse character
                    switch (rxMessageState)
                    {
                        case 0:
                        {
                            rxMessageType = rxByte;
                            rxMessageType <<= 8;
                            rxMessageState++;
                        }
                        break;

                        case 1:
                        {
                            rxMessageType |= rxByte;
                            rxMessageState++;
                        }
                        break;

                        case 2:
                        {
                            rxMessageLength = rxByte;
                            rxMessageLength <<= 8;
                            rxMessageState++;
                        }
                        break;

                        case 3:
                        {
                            rxMessageLength |= rxByte;
                            rxMessageState++;
                        }
                        break;

                        case 4:
                        {
                            rxMessageChecksum = rxByte;
                            rxMessageState++;
                        }
                        break;

                        default:
                        {
                            rxMessageData[rxMessageCount++] = rxByte;
                        }
                        break;
                    }
                }
            }
        }

        private void displayRawCommandData(UInt16 u16Type, UInt16 u16Length, byte u8Checksum, byte[] au8Data)
        {
            byte tempByte;
            /* Dont display OTA block request/response as it slows down the process!! */
            if ((u8OtaInProgress == 0) || ((u16Type != 0x8000) && (u16Type != 0x8501) && (u16Type != 0x0502)))
            {
                richTextBoxCommandResponse.Text += DateTime.Now.Hour.ToString("D2");
                richTextBoxCommandResponse.Text += ":";
                richTextBoxCommandResponse.Text += DateTime.Now.Minute.ToString("D2");
                richTextBoxCommandResponse.Text += ":";
                richTextBoxCommandResponse.Text += DateTime.Now.Second.ToString("D2");
                richTextBoxCommandResponse.Text += ".";
                richTextBoxCommandResponse.Text += DateTime.Now.Millisecond.ToString("D3");
                richTextBoxCommandResponse.Text += " <- ";
                richTextBoxCommandResponse.Text += "01 ";

                if (u16Type != 0x8501)
                {
                    tempByte = (byte)(u16Type >> 8);
                    richTextBoxCommandResponse.Text += tempByte.ToString("X2");
                    richTextBoxCommandResponse.Text += " ";
                    tempByte = (byte)u16Type;
                    richTextBoxCommandResponse.Text += tempByte.ToString("X2");
                    richTextBoxCommandResponse.Text += " ";

                    tempByte = (byte)(u16Length >> 8);
                    richTextBoxCommandResponse.Text += tempByte.ToString("X2");
                    richTextBoxCommandResponse.Text += " ";
                    tempByte = (byte)u16Length;
                    richTextBoxCommandResponse.Text += tempByte.ToString("X2");
                    richTextBoxCommandResponse.Text += " ";

                    richTextBoxCommandResponse.Text += u8Checksum.ToString("X2");
                    richTextBoxCommandResponse.Text += " ";

                    for (int i = 0; i < u16Length; i++)
                    {
                        richTextBoxCommandResponse.Text += au8Data[i].ToString("X2");
                        richTextBoxCommandResponse.Text += " ";
                    }

                    richTextBoxCommandResponse.Text += "03";
                    richTextBoxCommandResponse.Text += "\n";
                }
            }
        }
        #endregion

        #region message display windows

        private void buttonClearRaw_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Text = "";
        }

        private void buttonMessageViewClear_Click(object sender, EventArgs e)
        {
            richTextBoxMessageView.Text = "";
        }
        #endregion

        private void comboBoxConfigReportAttribDirection_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void textBoxBasicResetTargetAddr_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void buttonLeave_Click(object sender, EventArgs e)
        {
            UInt64 u64ExtAddr = 0;

            if (bStringToUint64(textBoxLeaveAddr.Text, out u64ExtAddr) == true)
            {
                sendLeaveRequest(u64ExtAddr, (byte)comboBoxLeaveReJoin.SelectedIndex, (byte)comboBoxLeaveChildren.SelectedIndex);
            }
        }

        private void buttonRemoveDevice_Click(object sender, EventArgs e)
        {
            UInt64 u64ParentExtAddr = 0;
            UInt64 u64ChildExtAddr = 0;

            if (bStringToUint64(textBoxRemoveParentAddr.Text, out u64ParentExtAddr) == true)
            {
                if (bStringToUint64(textBoxRemoveChildAddr.Text, out u64ChildExtAddr) == true)
                {
                    sendRemoveRequest(u64ParentExtAddr, u64ChildExtAddr);
                }
            }
        }

        private void buttonRawDataSend_Click(object sender, EventArgs e)
        {
            UInt16 u16TargetAddr;
            UInt16 u16ClusterID;
            UInt16 u16ProfileID;
            byte u8SecurityMode, u8Radius;
            byte u8SrcEndPoint;
            byte u8DstEndPoint;
            String stringRawData = "";

            if (bStringToUint16(textBoxRawDataCommandsTargetAddr.Text, out u16TargetAddr) == true)
            {
                if (bStringToUint8(textBoxRawDataCommandsSrcEP.Text, out u8SrcEndPoint) == true)
                {
                    if (bStringToUint8(textBoxRawDataCommandsDstEP.Text, out u8DstEndPoint) == true)
                    {
                        if (bStringToUint16(textBoxRawDataCommandsProfileID.Text, out u16ProfileID) == true)
                        {
                            if (bStringToUint16(textBoxRawDataCommandsClusterID.Text, out u16ClusterID) == true)
                            {
                                if (bStringToUint8(textBoxRawDataCommandsSecurityMode.Text, out u8SecurityMode) == true)
                                {
                                    if (bStringToUint8(textBoxRawDataCommandsRadius.Text, out u8Radius) == true)
                                    {
                                            stringRawData = textBoxRawDataCommandsData.Text;
                                            sendRawDataCommandsRequest((byte)comboBoxRawDataCommandsAddrMode.SelectedIndex, u16TargetAddr, u8SrcEndPoint, u8DstEndPoint, u16ProfileID, u16ClusterID, u8SecurityMode, u8Radius, stringRawData);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        private void buttonInPacketNotification_Click(object sender, EventArgs e)
        {
            UInt32 u32RfActiveOutDioMask;
            UInt32 u32StatusOutDioMask;
            UInt32 u32TxConfInDioMask;
            UInt16 u16PollPeriod;

            if (bStringToUint32(textBoxIPNConfigDioRfActiveOutDioMask.Text, out u32RfActiveOutDioMask) == true)
            {
                if (bStringToUint32(textBoxIPNConfigDioStatusOutDioMask.Text, out u32StatusOutDioMask) == true)
                {
                    if (bStringToUint32(textBoxIPNConfigDioTxConfInDioMask.Text, out u32TxConfInDioMask) == true)
                    {
                        if (bStringToUint16(textBoxIPNConfigPollPeriod.Text, out u16PollPeriod) == true)
                        {
                            sendIPNConfigureCommand((byte)comboBoxIPNConfigEnable.SelectedIndex, u32RfActiveOutDioMask, u32StatusOutDioMask, u32TxConfInDioMask, (byte)comboBoxIPNConfigRegisterCallback.SelectedIndex, u16PollPeriod, (byte)comboBoxIPNConfigTimerId.SelectedIndex);
                        }
                    }
                }
            }
        }

        private void buttonDioSetDirection_Click(object sender, EventArgs e)
        {
            UInt32 u32InputDIOMask;
            UInt32 u32OutputDIOMask;

            if (bStringToUint32(textBoxDioSetDirectionInputPinMask.Text, out u32InputDIOMask) == true)
            {
                if (bStringToUint32(textBoxDioSetDirectionOutputPinMask.Text, out u32OutputDIOMask) == true)
                {
                    sendDioSetDirectionOutputCommand(0x0801, u32InputDIOMask, u32OutputDIOMask);
                }
            }
        }

        private void buttonDioSetOutput_Click(object sender, EventArgs e)
        {
            UInt32 u32OutputOnDIOMask;
            UInt32 u32OutputOffDIOMask;

            if (bStringToUint32(textBoxDioSetOutputOnPinMask.Text, out u32OutputOnDIOMask) == true)
            {
                if (bStringToUint32(textBoxDioSetOutputOffPinMask.Text, out u32OutputOffDIOMask) == true)
                {
                    sendDioSetDirectionOutputCommand(0x0802, u32OutputOnDIOMask, u32OutputOffDIOMask);
                }
            }
        }

        private void buttonAHISetTxPower_Click(object sender, EventArgs e)
        {
            byte u8TxPower;

            if (bStringToUint8(textBoxAHITxPower.Text, out u8TxPower) == true)
            {
                sendAHISetTxPowerCommand(u8TxPower);
            }
        }

        #region Mouse Hover/Leave

        #region ManagementTab

        #region SetEPID

        private void textBoxSetEPID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Extended PAN ID to be used (64-bit Hex)");
        }

        private void textBoxSetEPID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region SetCMSK

        private void textBoxSetCMSK_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Channel value (32-bit). Can be either Hex of Channel Mask or Single Decimal Channel");
        }

        private void textBoxSetCMSK_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region ManagementLeave

        private void textBoxMgmtLeaveAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination address where the command will go (16-bit Hex)");
        }

        private void textBoxMgmtLeaveAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMgmtLeaveExtAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Device which is requested to leave (64-bit Hex)");
        }

        private void textBoxMgmtLeaveExtAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Leave

        private void textBoxLeaveAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Device which is requested to leave (64-bit Hex)");
        }

        private void textBoxLeaveAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region RemoveDevice

        private void textBoxRemoveParentAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Parent address of the device to be removed (64-bit Hex)");
        }

        private void textBoxRemoveParentAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveChildAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address of the device to be removed (64-bit Hex)");
        }

        private void textBoxRemoveChildAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region PermitJoin

        private void textBoxPermitJoinAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address to set permit join value (8 bit-Hex)");
        }

        private void textBoxPermitJoinAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxPermitJoinInterval_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Permit join value (8-bit Hex)");
        }

        private void textBoxPermitJoinInterval_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region MatchDescriptorRequest

        private void textBoxMatchReqAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address for the Match Descriptor Request (16-bit Hex)");
        }

        private void textBoxMatchReqAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMatchReqProfileID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Profile ID (16-bit Hex)");
        }

        private void textBoxMatchReqProfileID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMatchReqNbrInputClusters_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Number of Intput Clusters (8-bit Hex)");
        }

        private void textBoxMatchReqNbrInputClusters_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMatchReqInputClusters_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Input Cluster List (Array 16-bit Hex e.g. 00050010)");
        }

        private void textBoxMatchReqInputClusters_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMatchReqNbrOutputClusters_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Number of Output Clusters (8-bit Hex)");
        }

        private void textBoxMatchReqNbrOutputClusters_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMatchReqOutputClusters_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Output Cluster List (Array 16-bit Hex e.g. 00050010)");
        }

        private void textBoxMatchReqOutputClusters_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region BindRequest

        private void textBoxBindTargetExtAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("The Address the Request is Going to (32-bit Hex)");
        }

        private void textBoxBindTargetExtAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxBindTargetEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Endpoint Number the Request is going to (8-bit Hex)");
        }

        private void textBoxBindTargetEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxBindClusterID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Cluster ID which will be put into the Binding Table (16-bit Hex)");
        }

        private void textBoxBindClusterID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxBindAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode (8-bit Hex)");
        }

        private void comboBoxBindAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxBindDestAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address which will be put into the binding table (32-bit Hex)");
        }

        private void textBoxBindDestAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxBindDestEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Endpoint Number which will be put into the binding table (32-bit Hex)");
        }

        private void textBoxBindDestEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region UnbindRequest

        private void textBoxUnBindTargetExtAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("The Address the Request is Going to (32-bit Hex)");
        }

        private void textBoxUnBindTargetExtAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxUnBindTargetEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Endpoint Number the Request is going to (8-bit Hex)");
        }

        private void textBoxUnBindTargetEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxUnBindClusterID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Cluster ID which will be removed from the Binding Table (16-bit Hex)");
        }

        private void textBoxUnBindClusterID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxUnBindAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode (8-bit Hex)");
        }

        private void comboBoxUnBindAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxUnBindDestAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address which will be removed from the binding table (32-bit Hex)");
        }

        private void textBoxUnBindDestAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxUnBindDestEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Endpoint Number which will be removed from the binding table (32-bit Hex)");
        }

        private void textBoxUnBindDestEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region ActiveEndpointRequest

        private void textBoxActiveEpAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxActiveEpAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region IEEERequest

        private void textBoxIeeeReqTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address request will be sent to (16-bit Hex)");
        }

        private void textBoxIeeeReqTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxIeeeReqAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("The short address associated with the requested IEEE address (16-bit Hex)");
        }

        private void textBoxIeeeReqAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxIeeeReqStartIndex_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Neighbour table index of the first neighbouring node to be included in the response (8-Bit Hex)");
        }

        private void textBoxIeeeReqStartIndex_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region NetworkAddressRequest

        private void textBoxNwkAddrReqTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address the request will be sent to (16-bit Hex)");
        }

        private void textBoxNwkAddrReqTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxNwkAddrReqExtAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address associated with the short address required (32-bit Hex)");
        }

        private void textBoxNwkAddrReqExtAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxNwkAddrReqStartIndex_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Neighbour table index of the first neighbouring node to be included in the response (8-Bit Hex)");
        }

        private void textBoxNwkAddrReqStartIndex_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region NodeDescriptorRequest

        private void textBoxNodeDescReq_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxNodeDescReq_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region PowerDescriptorRequest

        private void textBoxPowerReqAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxPowerReqAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region SimpleDescriptorRequest

        private void textBoxSimpleReqAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxSimpleReqAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxSimpleReqEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Endpoint Number (8-bit Hex)");
        }

        private void textBoxSimpleReqEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region ComplexDescriptorRequest

        private void textBoxComplexReqAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxComplexReqAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxLqiReqTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxLqiReqTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxLqiReqStartIndex_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Starting index in the neighbour table (8-bit Hex)");
        }

        private void textBoxLqiReqStartIndex_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region UserDescriptorRequest

        private void textBoxUserReqAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxUserReqAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region UserDescriptorSetRequest

        private void textBoxUserSetReqAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxUserSetReqAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxUserSetReqDescription_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("User Description (String)");
        }

        private void textBoxUserSetReqDescription_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region NetworkRestoreRequest

        private void textBoxRestoreNwkFrameCounter_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Outgoing frame counter value to start from (16-bit Hex)");
        }

        private void textBoxRestoreNwkFrameCounter_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #endregion

        #region GeneralTab

        #region ReadAttributeRequest

        private void textBoxReadAttribTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxReadAttribTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadAttribSrcEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxReadAttribSrcEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadAttribDstEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxReadAttribDstEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadAttribClusterID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Cluster ID (16-bit Hex)");
        }

        private void textBoxReadAttribClusterID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxReadAttribDirection_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Server or Client Attribute");
        }

        private void comboBoxReadAttribDirection_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadAttribCount_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Number of attributes to read (8-bit Hex)");
        }

        private void textBoxReadAttribCount_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadAttribID1_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Attribute ID to be read (16-bit Hex)");
        }

        private void textBoxReadAttribID1_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxReadAttribManuSpecific_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Standard or Manufacturer Specific");
        }

        private void comboBoxReadAttribManuSpecific_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadAttribManuID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Manufacturer Code (16-bit Hex)");
        }

        private void textBoxReadAttribManuID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region ReadLocalAttributeRequest

        private void textBoxReadLocalSrcEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxReadLocalSrcEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadLocalClusterID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Cluster ID (16-bit Hex)");
        }

        private void textBoxReadLocalClusterID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadLocalAttribID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Attribute ID to be read (16-bit Hex)");
        }

        private void textBoxReadLocalAttribID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadLocalAttribValue_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Attribute Value");
        }

        private void textBoxReadLocalAttribValue_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region WriteAttributeRequest

        private void textBoxWriteAttribTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxWriteAttribTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxWriteAttribSrcEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxWriteAttribSrcEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxWriteAttribDstEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxWriteAttribDstEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxWriteAttribClusterID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Cluster ID (16-bit Hex)");
        }

        private void textBoxWriteAttribClusterID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxWriteAttribDirection_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Server or Client attribute");
        }

        private void comboBoxWriteAttribDirection_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxWriteAttribID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Attribute ID (16-bit Hex)");
        }

        private void textBoxWriteAttribID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxWriteAttribDataType_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Attribute Type (16-bit Hex)");
        }

        private void textBoxWriteAttribDataType_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxWriteAttribData_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Attribute Data");
        }

        private void textBoxWriteAttribData_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxWriteAttribManuSpecific_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Standard or Manufacturer specific attribute");
        }

        private void comboBoxWriteAttribManuSpecific_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxWriteAttribManuID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Manufacturer Code (16-bit Hex)");
        }

        private void textBoxWriteAttribManuID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }
        #endregion

        #region ConfigureReportingRequest

        private void comboBoxConfigReportAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxConfigReportAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxConfigReportTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxConfigReportTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxConfigReportSrcEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxConfigReportSrcEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxConfigReportDstEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (16-bit Hex)");
        }

        private void textBoxConfigReportDstEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxConfigReportClusterID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Cluster ID (16-bit Hex)");
        }

        private void textBoxConfigReportClusterID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxConfigReportDirection_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Server or Client Attribute");
        }

        private void comboBoxConfigReportDirection_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxConfigReportAttribDirection_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Whether it will be sent by the server or recived by the client");
        }

        private void comboBoxConfigReportAttribDirection_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxConfigReportAttribType_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Attribute Type (8-bit Hex)");
        }

        private void textBoxConfigReportAttribType_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxConfigReportAttribID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Attribute ID (16-bit Hex)");
        }

        private void textBoxConfigReportAttribID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxConfigReportMinInterval_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Minimum Interval e.g. On Change Time (16-bit Hex)");
        }

        private void textBoxConfigReportMinInterval_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxConfigReportMaxInterval_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Maximum Interval e.g Periodic Report Time (16-bit Hex)");
        }

        private void textBoxConfigReportMaxInterval_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxConfigReportTimeOut_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("How often a client will expect a report (16-bit Hex)");
        }

        private void textBoxConfigReportTimeOut_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxConfigReportChange_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Minimum change required before a On Change report is generated (8-bit Hex)");
        }

        private void textBoxConfigReportChange_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region ReadReportRequest

        private void comboBoxReadReportConfigAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxReadReportConfigAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadReportConfigTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxReadReportConfigTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadReportConfigSrcEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxReadReportConfigSrcEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadReportConfigDstEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxReadReportConfigDstEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadReportConfigClusterID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Cluster ID (16-bit Hex)");
        }

        private void textBoxReadReportConfigClusterID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxReadReportConfigDirection_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("To Server or Client");
        }

        private void comboBoxReadReportConfigDirection_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadReportConfigAttribID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Attribute ID (16-bit Hex)");
        }

        private void textBoxReadReportConfigAttribID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxReadReportConfigDirIsRx_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Whether it is for a device that is sending report or receiving them");
        }

        private void comboBoxReadReportConfigDirIsRx_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region ReadAllAttributeRequest

        private void textBoxReadAllAttribAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxReadAllAttribAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadAllAttribSrcEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxReadAllAttribSrcEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadAllAttribDstEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxReadAllAttribDstEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxReadAllAttribClusterID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Cluster ID (16-bit Hex)");
        }

        private void textBoxReadAllAttribClusterID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxReadAllAttribDirection_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("To Server or Client");
        }

        private void comboBoxReadAllAttribDirection_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Discover Attribute Request

        private void textBoxDiscoverAttributesAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxDiscoverAttributesAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxDiscoverAttributesSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxDiscoverAttributesSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxDiscoverAttributesDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxDiscoverAttributesDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxDiscoverAttributesStartAttrId_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Start Attr ID (8-bit Hex)");
        }

        private void textBoxDiscoverAttributesStartAttrId_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxDiscoverAttributesClusterID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Cluster ID (16-bit Hex)");
        }

        private void textBoxDiscoverAttributesClusterID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxDiscoverAttributesDirection_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Attribute Direction");
        }

        private void comboBoxDiscoverAttributesDirection_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxDiscoverAttributesMaxIDs_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Number Of Attributes (8-bit Hex)");
        }

        private void textBoxDiscoverAttributesMaxIDs_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxDiscoverAttributesExtended_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Standard or Extended");
        }

        private void comboBoxDiscoverAttributesExtended_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region MTO Rt Req

        private void comboBoxManyToOneRouteRequestCacheRoute_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Cache or No Cache");
        }

        private void comboBoxManyToOneRouteRequestCacheRoute_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxManyToOneRouteRequesRadius_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Radius (8-bit Hex)");
        }

        private void textBoxManyToOneRouteRequesRadius_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Network Update

        private void comboBoxMgmtNwkUpdateAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxMgmtNwkUpdateAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMgmtNwkUpdateTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxMgmtNwkUpdateTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMgmtNwkUpdateChannelMask_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Channel Mask (32-bit Hex)");
        }

        private void textBoxMgmtNwkUpdateChannelMask_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMgmtNwkUpdateScanDuration_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Duration (8-bit Hex)");
        }

        private void textBoxMgmtNwkUpdateScanDuration_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMgmtNwkUpdateScanCount_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Scan Count (8-bit Hex)");
        }

        private void textBoxMgmtNwkUpdateScanCount_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMgmtNwkUpdateNwkManagerAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Network Manager Address (16-bit Hex)");
        }

        private void textBoxMgmtNwkUpdateNwkManagerAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Disc Commands

        private void comboBoxDiscoverCommandsAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxDiscoverCommandsAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxDiscoverCommandsTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxDiscoverCommandsTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxDiscoverCommandsSrcEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxDiscoverCommandsSrcEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxDiscoverCommandsDstEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxDiscoverCommandsDstEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxDiscoverCommandsClusterID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Cluster ID (16-bit Hex)");
        }

        private void textBoxDiscoverCommandsClusterID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxDiscoverCommandsDirection_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("To Server or Client");
        }

        private void comboBoxDiscoverCommandsDirection_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxDiscoverCommandsCommandID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Command ID (8-bit Hex)");
        }

        private void textBoxDiscoverCommandsCommandID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxDiscoverCommandsManuSpecific_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Standard or Manufacturer Specific");
        }

        private void comboBoxDiscoverCommandsManuSpecific_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxDiscoverCommandsManuID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Manufacturer ID (16-bit Hex)");
        }

        private void textBoxDiscoverCommandsManuID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxDiscoverCommandsMaxCommands_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Maximum Commands (8-bit Hex)");
        }

        private void textBoxDiscoverCommandsMaxCommands_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxDiscoverCommandsRxGen_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Received or Generated");
        }

        private void comboBoxDiscoverCommandsRxGen_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Raw Data Send

        private void textBoxRawDataCommandsTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxRawDataCommandsTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRawDataCommandsSrcEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxRawDataCommandsSrcEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRawDataCommandsProfileID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Profile ID (16-bit Hex)");
        }

        private void textBoxRawDataCommandsProfileID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRawDataCommandsDstEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxRawDataCommandsDstEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRawDataCommandsClusterID_MouseHover(object sender, EventArgs e)
        {

            showToolTipWindow("Cluster ID (16-bit Hex)");
        }

        private void textBoxRawDataCommandsClusterID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRawDataCommandsRadius_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Radius/Max Number Of Hops (8-bit Hex)");
        }

        private void textBoxRawDataCommandsRadius_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRawDataCommandsSecurityMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Security Mode (8-bit Hex) - See zps_apl_af.h enum ZPS_teAplAfSecurityMode)");
        }

        private void textBoxRawDataCommandsSecurityMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRawDataCommandsData_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Raw APS data (Array of 8-Bit Hex e.g 00:11:22:33)");
        }

        private void textBoxRawDataCommandsData_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region OOB Commissioning Data

        private void textBoxOOBDataAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Extended Address Data (64-bit Hex)");
        }

        private void textBoxOOBDataAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOOBDataKey_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Key (Format: Byte:Byte:Byte)");
        }

        private void textBoxOOBDataKey_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #endregion

        #region AHITab

        #region IPNConfigure

        private void comboBoxIPNConfigEnable_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Boolean to Enable IPN");
        }

        private void comboBoxIPNConfigEnable_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxIPNConfigDioRfActiveOutDioMask_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Output Pin indicating a Tx/Rx Request (32-Bit Hex)");
        }

        private void textBoxIPNConfigDioRfActiveOutDioMask_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxIPNConfigDioStatusOutDioMask_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("The priority pin (32-Bit Hex)");
        }

        private void textBoxIPNConfigDioStatusOutDioMask_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxIPNConfigDioTxConfInDioMask_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Input pin indicating whether the request is granted or not (32-Bit Hex)");
        }

        private void textBoxIPNConfigDioTxConfInDioMask_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxIPNConfigRegisterCallback_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Enable IPN callback on state change");
        }

        private void comboBoxIPNConfigRegisterCallback_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxIPNConfigPollPeriod_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Poll period, units of 62500Hz clock (16-Bit Hex)");
        }

        private void textBoxIPNConfigPollPeriod_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxIPNConfigTimerId_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("The hardware timer to be used for the 100us request/response delay");
        }

        private void comboBoxIPNConfigTimerId_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAHITxPower_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("A twos compliment 6 bit value indicating the Tx Power.");
        }

        private void textBoxAHITxPower_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region DIOSetDirection

        private void textBoxDioSetDirectionInputPinMask_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("DIO Input Mask (32-Bit Hex)");
        }

        private void textBoxDioSetDirectionInputPinMask_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxDioSetDirectionOutputPinMask_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("DIO Output Mask (32-Bit Hex)");
        }

        private void textBoxDioSetDirectionOutputPinMask_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region DIOSetOutput

        private void textBoxDioSetOutputOnPinMask_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("DIO Input On Mask (32-Bit Hex)");
        }

        private void textBoxDioSetOutputOnPinMask_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxDioSetOutputOffPinMask_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("DIO Output Off Mask (32-Bit Hex)");
        }

        private void textBoxDioSetOutputOffPinMask_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion


        #endregion

        #region BasicClusterTab

        #region Reset to FD

        private void comboBoxBasicResetTargetAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxBasicResetTargetAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxBasicResetTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxBasicResetTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxBasicResetSrcEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxBasicResetSrcEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxBasicResetDstEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxBasicResetDstEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #endregion

        #region PollControlTab

        private void comboBoxFastPollEnable_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Enable or Disable Fast Polling");
        }

        private void comboBoxFastPollEnable_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxFastPollExpiryTime_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Fast polling expiry time (1/4 second increments)");
        }

        private void textBoxFastPollExpiryTime_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region GroupClusterTab

        #region Add Group

        private void textBoxAddGroupAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destionation Address (16-bit Hex)");
        }

        private void textBoxAddGroupAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAddGroupSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxAddGroupSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAddGroupDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxAddGroupDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAddGroupGroupAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group ID (16-bit Hex)");
        }

        private void textBoxAddGroupGroupAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxGroupNameLength_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group Name Length (8-bit Hex)");
        }

        private void textBoxGroupNameLength_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxGroupNameMaxLength_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group Name Maximum Length (8-bit Hex)");
        }

        private void textBoxGroupNameMaxLength_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxGroupName_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group Name (String)");
        }

        private void textBoxGroupName_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region View Group

        private void textBoxViewGroupAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxViewGroupAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxViewGroupSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxViewGroupSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxViewGroupDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxViewGroupDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxViewGroupGroupAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group ID (16-bit Hex)");
        }

        private void textBoxViewGroupGroupAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Get Group

        private void textBoxGetGroupTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxGetGroupTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxGetGroupSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxGetGroupSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxGetGroupDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxGetGroupDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxGetGroupCount_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group Count");
        }

        private void textBoxGetGroupCount_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Remove Group

        private void textBoxRemoveGroupTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxRemoveGroupTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveGroupSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxRemoveGroupSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveGroupDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxRemoveGroupDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveGroupGroupAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group ID (16-bit Hex)");
        }

        private void textBoxRemoveGroupGroupAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Remove All

        private void textBoxRemoveAllGroupTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxRemoveAllGroupTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveAllGroupSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxRemoveAllGroupSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveAllGroupDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxRemoveAllGroupDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Add If Identified

        private void textBoxGroupAddIfIndentifyingTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxGroupAddIfIndentifyingTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxGroupAddIfIdentifySrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxGroupAddIfIdentifySrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxGroupAddIfIdentifyDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxGroupAddIfIdentifyDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxGroupAddIfIdentifyGroupID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group ID (16-bit Hex)");
        }

        private void textBoxGroupAddIfIdentifyGroupID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #endregion

        #region IdentifyClusterTab

        #region ID Send

        private void textBoxSendIdAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxSendIdAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxSendIdSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxSendIdSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxIdSendDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxIdSendDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxIdSendTime_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Time (16-bit Hex)");
        }

        private void textBoxIdSendTime_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region ID Query

        private void textBoxIdQueryAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxIdQueryAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxIdQuerySrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxIdQuerySrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxIdQueryDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxIdQueryDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #endregion

        #region LevelClusterTab

        #region Move To Level

        private void comboBoxMoveToLevelAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxMoveToLevelAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToLevelAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxMoveToLevelAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToLevelSrcEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxMoveToLevelSrcEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToLevelDstEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxMoveToLevelDstEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxMoveToLevelOnOff_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("With or Without OnOff");
        }

        private void comboBoxMoveToLevelOnOff_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToLevelLevel_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Level (8-bit Hex)");
        }

        private void textBoxMoveToLevelLevel_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToLevelTransTime_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Time (8-bit Hex)");
        }

        private void textBoxMoveToLevelTransTime_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #endregion

        #region OnOffClusterTab

        #region OnOff

        private void comboBoxOnOffAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxOnOffAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOnOffAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxOnOffAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOnOffSrcEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxOnOffSrcEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOnOffDstEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxOnOffDstEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxOnOffCommand_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("On/Off/Toggle");
        }

        private void comboBoxOnOffCommand_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #endregion

        #region ScenesClusterTab

        #region View Scene

        private void comboBoxViewSceneAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxViewSceneAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxViewSceneAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxViewSceneAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxViewSceneSrcEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxViewSceneSrcEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxViewSceneDstEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxViewSceneDstEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxViewSceneGroupId_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group ID (16-bit Hex)");
        }

        private void textBoxViewSceneGroupId_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxViewSceneSceneId_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Scene ID (8-bit Hex)");
        }

        private void textBoxViewSceneSceneId_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Add Scene

        private void comboBoxAddSceneAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxAddSceneAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAddSceneAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxAddSceneAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAddSceneSrcEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxAddSceneSrcEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAddSceneDstEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxAddSceneDstEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAddSceneGroupId_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group ID (16-bit Hex)");
        }

        private void textBoxAddSceneGroupId_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAddSceneSceneId_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Scene ID (8-bit Hex)");
        }

        private void textBoxAddSceneSceneId_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAddSceneTransTime_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Transition Time (16-bit Hex)");
        }

        private void textBoxAddSceneTransTime_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAddSceneName_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Scene Name (String)");
        }

        private void textBoxAddSceneName_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAddSceneNameLen_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Scene Name Length (8-bit Hex)");
        }

        private void textBoxAddSceneNameLen_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAddSceneMaxNameLen_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Scene Name Maximum Length (8-bit Hex)");
        }

        private void textBoxAddSceneMaxNameLen_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAddSceneExtLen_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Extension Field Length (16-bit Hex)");
        }

        private void textBoxAddSceneExtLen_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxAddSceneData_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Extension Field Data (8-bit Hex)");
        }

        private void textBoxAddSceneData_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Store Scene

        private void comboBoxStoreSceneAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxStoreSceneAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxStoreSceneAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxStoreSceneAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxStoreSceneSrcEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxStoreSceneSrcEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxStoreSceneDstEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxStoreSceneDstEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxStoreSceneGroupId_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group ID (16-bit Hex)");
        }

        private void textBoxStoreSceneGroupId_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxStoreSceneSceneId_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Scene ID (8-bit Hex)");
        }

        private void textBoxStoreSceneSceneId_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Recall Scene

        private void comboBoxRecallSceneAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxRecallSceneAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRecallSceneAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxRecallSceneAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRecallSceneSrcEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxRecallSceneSrcEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRecallSceneDstEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxRecallSceneDstEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRecallSceneGroupId_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group ID (16-bit Hex)");
        }

        private void textBoxRecallSceneGroupId_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRecallSceneSceneId_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Scene ID (8-bit Hex)");
        }

        private void textBoxRecallSceneSceneId_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Get Member

        private void comboBoxGetSceneMembershipAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxGetSceneMembershipAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxGetSceneMembershipAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxGetSceneMembershipAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxGetSceneMembershipSrcEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxGetSceneMembershipSrcEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxGetSceneMembershipDstEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxGetSceneMembershipDstEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxGetSceneMembershipGroupID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group ID (16-bit Hex)");
        }

        private void textBoxGetSceneMembershipGroupID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Remove All

        private void comboBoxRemoveAllScenesAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxRemoveAllScenesAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveAllScenesAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxRemoveAllScenesAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveAllScenesSrcEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxRemoveAllScenesSrcEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveAllScenesDstEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxRemoveAllScenesDstEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveAllScenesGroupID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group ID (16-bit Hex)");
        }

        private void textBoxRemoveAllScenesGroupID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Remove

        private void comboBoxRemoveSceneAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxRemoveSceneAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveSceneAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxRemoveSceneAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveSceneSrcEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxRemoveSceneSrcEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveSceneDstEndPoint_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxRemoveSceneDstEndPoint_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveSceneGroupID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Group ID (16-bit Hex)");
        }

        private void textBoxRemoveSceneGroupID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxRemoveSceneSceneID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Scene ID (8-bit Hex)");
        }

        private void textBoxRemoveSceneSceneID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #endregion

        #region ColorClusterTab

        #region Move to Hue

        private void textBoxMoveToHueAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxMoveToHueAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToHueSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxMoveToHueSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToHueDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxMoveToHueDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToHueHue_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Hue (8-bit Hex)");
        }

        private void textBoxMoveToHueHue_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToHueDir_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Direction (8-bit Hex)");
        }

        private void textBoxMoveToHueDir_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToHueTime_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Transition Time (16-bit Hex)");
        }

        private void textBoxMoveToHueTime_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Move to Color

        private void textBoxMoveToColorAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxMoveToColorAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToColorSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxMoveToColorSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToColorDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxMoveToColorDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToColorX_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("X Value (16-bit Hex)");
        }

        private void textBoxMoveToColorX_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToColorY_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Y Value (16-bit Hex)");
        }

        private void textBoxMoveToColorY_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToColorTime_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Transition Time (16-bit Hex)");
        }

        private void textBoxMoveToColorTime_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Move to Saturation

        private void textBoxMoveToSatAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxMoveToSatAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToSatSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxMoveToSatSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToSatDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxMoveToSatDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToSatSat_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Saturation (8-bit Hex)");
        }

        private void textBoxMoveToSatSat_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToSatTime_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Transition Time (16-bit Hex)");
        }

        private void textBoxMoveToSatTime_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region Move to Temperature

        private void textBoxMoveToColorTempAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxMoveToColorTempAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToColorTempSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxMoveToColorTempSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToColorTempDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxMoveToColorTempDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToColorTempTemp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Temperature (16-bit Dec)");
        }

        private void textBoxMoveToColorTempTemp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxMoveToColorTempRate_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Transition Time (16-bit Hex)");
        }

        private void textBoxMoveToColorTempRate_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #endregion

        #region DoorLockClusterTab

        #region LockUnlock

        private void textBoxLockUnlockAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxLockUnlockAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxLockUnlockSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxLockUnlockSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxLockUnlockDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxLockUnlockDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxLockUnlock_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Lock or Unlock");
        }

        private void comboBoxLockUnlock_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #endregion

        #region IASClusterTab

        #region Enroll Rsp

        private void comboBoxEnrollRspAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxEnrollRspAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxEnrollRspAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxEnrollRspAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxEnrollRspSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxEnrollRspSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxEnrollRspDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxEnrollRspDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxEnrollRspCode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Response");
        }

        private void comboBoxEnrollRspCode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxEnrollRspZone_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Zone ID (8-bit Hex)");
        }

        private void textBoxEnrollRspZone_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #endregion

        #region ZLLOnOffClusterTab

        #region OnOff Effects

        private void textBoxZllOnOffEffectsAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxZllOnOffEffectsAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxZllOnOffEffectsSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxZllOnOffEffectsSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxZllOnOffEffectsDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void comboBoxZllOnOffEffectID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("On/Off/Toggle");
        }

        private void comboBoxZllOnOffEffectID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxZllOnOffEffectsGradient_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Gradient (8-bit Hex)");
        }

        private void textBoxZllOnOffEffectsGradient_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #endregion

        #region ZLLColorClusterTab

        #region Move to Hue

        private void textBoxZllMoveToHueAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxZllMoveToHueAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxZllMoveToHueSrcEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxZllMoveToHueSrcEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxZllMoveToHueDstEp_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxZllMoveToHueDstEp_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxZllMoveToHueHue_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Hue (16-bit Hex)");
        }

        private void textBoxZllMoveToHueHue_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxZllMoveToHueDirection_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Direction (16-bit Hex)");
        }

        private void textBoxZllMoveToHueDirection_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxZllMoveToHueTransTime_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Transition Time (16-bit Hex)");
        }

        private void textBoxZllMoveToHueTransTime_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #endregion

        #region OTAClusterTab

        #region Image Notify

        private void comboBoxOTAImageNotifyAddrMode_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Address Mode");
        }

        private void comboBoxOTAImageNotifyAddrMode_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOTAImageNotifyTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxOTAImageNotifyTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOTAImageNotifySrcEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxOTAImageNotifySrcEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOTAImageNotifyDstEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Endpoint (8-bit Hex)");
        }

        private void textBoxOTAImageNotifyDstEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void comboBoxOTAImageNotifyType_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Jitter Options");
        }

        private void comboBoxOTAImageNotifyType_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOTAImageNotifyFileVersion_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Version Number (32-bit Hex)");
        }

        private void textBoxOTAImageNotifyFileVersion_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOTAImageNotifyImageType_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Image Type (16-bit Hex)");
        }

        private void textBoxOTAImageNotifyImageType_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOTAImageNotifyManuID_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Manufacturer ID (16-bit Hex)");
        }

        private void textBoxOTAImageNotifyManuID_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOTAImageNotifyJitter_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Query Jitter (8-bit Hex)");
        }

        private void textBoxOTAImageNotifyJitter_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #region WaitParams

        private void textBoxOTASetWaitForDataParamsTargetAddr_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Destination Address (16-bit Hex)");
        }

        private void textBoxOTASetWaitForDataParamsTargetAddr_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOTASetWaitForDataParamsSrcEP_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Source Endpoint (8-bit Hex)");
        }

        private void textBoxOTASetWaitForDataParamsSrcEP_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOTASetWaitForDataParamsCurrentTime_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Current Time (32-bit Hex)");
        }

        private void textBoxOTASetWaitForDataParamsCurrentTime_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOTASetWaitForDataParamsRequestTime_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Request Time (32-bit Hex)");
        }

        private void textBoxOTASetWaitForDataParamsRequestTime_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxOTASetWaitForDataParamsRequestBlockDelay_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Block Delay (16-bit Hex)");
        }

        private void textBoxOTASetWaitForDataParamsRequestBlockDelay_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        #endregion

        #endregion

        #region Text Change

        private void textBoxRawDataCommandsData_TextChanged(object sender, EventArgs e)
        {
            if (textBoxRawDataCommandsData.Text != "Raw Data (Format: Byte:Byte:Byte)")
            {
                String rawData = "";
                int iRawDataSize;

                rawData = textBoxRawDataCommandsData.Text;

                rawData = rawData.Replace(" ", "");
                rawData = rawData.Replace(":", "");

                iRawDataSize = rawData.Length;
                for (int i = iRawDataSize; i > 0; i--)
                {
                    if ((i % 2) == 0)
                    {
                        if (i != iRawDataSize)
                        {
                            rawData = rawData.Insert(i, ":");
                        }
                    }
                }

                textBoxRawDataCommandsData.Text = rawData;
                textBoxRawDataCommandsData.SelectionStart = textBoxRawDataCommandsData.Text.Length;
            }
        }

        private void textBoxOOBDataKey_TextChanged(object sender, EventArgs e)
        {
            if (textBoxOOBDataKey.Text != "Key (Format: Byte:Byte:Byte)")
            {
                String rawData = "";
                int iRawDataSize;

                rawData = textBoxOOBDataKey.Text;

                rawData = rawData.Replace(" ", "");
                rawData = rawData.Replace(":", "");

                iRawDataSize = rawData.Length;
                for (int i = iRawDataSize; i > 0; i--)
                {
                    if ((i % 2) == 0)
                    {
                        if (i != iRawDataSize)
                        {
                            rawData = rawData.Insert(i, ":");
                        }
                    }
                }

                textBoxOOBDataKey.Text = rawData;
                textBoxOOBDataKey.SelectionStart = textBoxOOBDataKey.Text.Length;
            }
        }

        private void textBoxAddSceneData_TextChanged(object sender, EventArgs e)
        {
            if (textBoxAddSceneData.Text != "Data (Format: Byte:Byte:Byte)")
            {
                String rawData = "";
                int iRawDataSize;

                rawData = textBoxAddSceneData.Text;

                rawData = rawData.Replace(" ", "");
                rawData = rawData.Replace(":", "");

                iRawDataSize = rawData.Length;
                for (int i = iRawDataSize; i > 0; i--)
                {
                    if ((i % 2) == 0)
                    {
                        if (i != iRawDataSize)
                        {
                            rawData = rawData.Insert(i, ":");
                        }
                    }
                }

                textBoxAddSceneData.Text = rawData;
                textBoxAddSceneData.SelectionStart = textBoxAddSceneData.Text.Length;
            }
        }

        private void richTextBoxMessageView_TextChanged(object sender, EventArgs e)
        {
            richTextBoxMessageView.SelectionStart = richTextBoxCommandResponse.Text.Length;
            richTextBoxMessageView.ScrollToCaret();
        }

        private void richTextBoxCommandResponse_TextChanged(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.SelectionStart = richTextBoxCommandResponse.Text.Length;
            richTextBoxCommandResponse.ScrollToCaret();
        }

        #endregion

        #region List Management

        private void buttonAddToList_Click(object sender, EventArgs e)
        {
            if (listManager.ShowDialog() == DialogResult.OK)
            {

            }
        }

        #endregion

        #endregion

        #region Clear Grey Text

        #region ManagementTab

        #region Set EPID

        private void textBoxSetEPID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxSetEPID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxSetEPID.ForeColor = System.Drawing.Color.Black;
                textBoxSetEPID.Text = "";
            }
        }

        #endregion

        #region Set CMSK

        private void textBoxSetCMSK_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxSetCMSK.ForeColor != System.Drawing.Color.Black)
            {
                textBoxSetCMSK.ForeColor = System.Drawing.Color.Black;
                textBoxSetCMSK.Text = "";
            }
        }

        #endregion

        #region Set Security Key

        private void textBoxSetSecurityKeySeqNbr_Click(object sender, EventArgs e)
        {
            if (textBoxSetSecurityKeySeqNbr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxSetSecurityKeySeqNbr.ForeColor = System.Drawing.Color.Black;
                textBoxSetSecurityKeySeqNbr.Text = "";
            }
        }

        #endregion

        #region Management Leave

        private void textBoxMgmtLeaveAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMgmtLeaveAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMgmtLeaveAddr.ForeColor = System.Drawing.Color.Black;
                textBoxMgmtLeaveAddr.Text = "";
            }
        }

        private void textBoxMgmtLeaveExtAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMgmtLeaveExtAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMgmtLeaveExtAddr.ForeColor = System.Drawing.Color.Black;
                textBoxMgmtLeaveExtAddr.Text = "";
            }
        }

        #endregion

        #region Leave

        private void textBoxLeaveAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxLeaveAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxLeaveAddr.ForeColor = System.Drawing.Color.Black;
                textBoxLeaveAddr.Text = "";
            }
        }

        #endregion

        #region Remove

        private void textBoxRemoveParentAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveParentAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveParentAddr.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveParentAddr.Text = "";
            }
        }

        private void textBoxRemoveChildAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveChildAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveChildAddr.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveChildAddr.Text = "";
            }
        }

        #endregion

        #region Permit Join

        private void textBoxPermitJoinAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxPermitJoinAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxPermitJoinAddr.ForeColor = System.Drawing.Color.Black;
                textBoxPermitJoinAddr.Text = "";
            }
        }

        private void textBoxPermitJoinInterval_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxPermitJoinInterval.ForeColor != System.Drawing.Color.Black)
            {
                textBoxPermitJoinInterval.ForeColor = System.Drawing.Color.Black;
                textBoxPermitJoinInterval.Text = "";
            }
        }

        #endregion

        #region Match Req

        private void textBoxMatchReqAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMatchReqAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMatchReqAddr.ForeColor = System.Drawing.Color.Black;
                textBoxMatchReqAddr.Text = "";
            }
        }

        private void textBoxMatchReqProfileID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMatchReqProfileID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMatchReqProfileID.ForeColor = System.Drawing.Color.Black;
                textBoxMatchReqProfileID.Text = "";
            }
        }

        private void textBoxMatchReqNbrInputClusters_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMatchReqNbrInputClusters.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMatchReqNbrInputClusters.ForeColor = System.Drawing.Color.Black;
                textBoxMatchReqNbrInputClusters.Text = "";
            }
        }

        private void textBoxMatchReqInputClusters_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMatchReqInputClusters.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMatchReqInputClusters.ForeColor = System.Drawing.Color.Black;
                textBoxMatchReqInputClusters.Text = "";
            }
        }

        private void textBoxMatchReqNbrOutputClusters_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMatchReqNbrOutputClusters.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMatchReqNbrOutputClusters.ForeColor = System.Drawing.Color.Black;
                textBoxMatchReqNbrOutputClusters.Text = "";
            }
        }

        private void textBoxMatchReqOutputClusters_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMatchReqOutputClusters.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMatchReqOutputClusters.ForeColor = System.Drawing.Color.Black;
                textBoxMatchReqOutputClusters.Text = "";
            }
        }

        #endregion

        #region Bind

        private void textBoxBindTargetExtAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxBindTargetExtAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxBindTargetExtAddr.ForeColor = System.Drawing.Color.Black;
                textBoxBindTargetExtAddr.Text = "";
            }
        }

        private void textBoxBindTargetEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxBindTargetEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxBindTargetEP.ForeColor = System.Drawing.Color.Black;
                textBoxBindTargetEP.Text = "";
            }
        }

        private void textBoxBindDestAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxBindDestAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxBindDestAddr.ForeColor = System.Drawing.Color.Black;
                textBoxBindDestAddr.Text = "";
            }
        }

        private void textBoxBindClusterID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxBindClusterID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxBindClusterID.ForeColor = System.Drawing.Color.Black;
                textBoxBindClusterID.Text = "";
            }
        }

        private void textBoxBindDestEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxBindDestEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxBindDestEP.ForeColor = System.Drawing.Color.Black;
                textBoxBindDestEP.Text = "";
            }
        }

        #endregion

        #region Unbind

        private void textBoxUnBindTargetExtAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxUnBindTargetExtAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxUnBindTargetExtAddr.ForeColor = System.Drawing.Color.Black;
                textBoxUnBindTargetExtAddr.Text = "";
            }
        }

        private void textBoxUnBindTargetEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxUnBindTargetEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxUnBindTargetEP.ForeColor = System.Drawing.Color.Black;
                textBoxUnBindTargetEP.Text = "";
            }
        }

        private void textBoxUnBindDestAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxUnBindDestAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxUnBindDestAddr.ForeColor = System.Drawing.Color.Black;
                textBoxUnBindDestAddr.Text = "";
            }
        }

        private void textBoxUnBindClusterID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxUnBindClusterID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxUnBindClusterID.ForeColor = System.Drawing.Color.Black;
                textBoxUnBindClusterID.Text = "";
            }
        }

        private void textBoxUnBindDestEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxUnBindDestEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxUnBindDestEP.ForeColor = System.Drawing.Color.Black;
                textBoxUnBindDestEP.Text = "";
            }
        }

        #endregion

        #region Active Req

        private void textBoxActiveEpAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxActiveEpAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxActiveEpAddr.ForeColor = System.Drawing.Color.Black;
                textBoxActiveEpAddr.Text = "";
            }
        }

        #endregion

        #region IEEE Req

        private void textBoxIeeeReqTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxIeeeReqTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxIeeeReqTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxIeeeReqTargetAddr.Text = "";
            }
        }

        private void textBoxIeeeReqAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxIeeeReqAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxIeeeReqAddr.ForeColor = System.Drawing.Color.Black;
                textBoxIeeeReqAddr.Text = "";
            }
        }

        private void textBoxIeeeReqStartIndex_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxIeeeReqStartIndex.ForeColor != System.Drawing.Color.Black)
            {
                textBoxIeeeReqStartIndex.ForeColor = System.Drawing.Color.Black;
                textBoxIeeeReqStartIndex.Text = "";
            }
        }

        #endregion

        #region NWK Address Req

        private void textBoxNwkAddrReqTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxNwkAddrReqTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxNwkAddrReqTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxNwkAddrReqTargetAddr.Text = "";
            }
        }

        #endregion

        #region Node Req

        private void textBoxNodeDescReq_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxNodeDescReq.ForeColor != System.Drawing.Color.Black)
            {
                textBoxNodeDescReq.ForeColor = System.Drawing.Color.Black;
                textBoxNodeDescReq.Text = "";
            }
        }

        #endregion

        #region Power Req

        private void textBoxPowerReqAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxPowerReqAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxPowerReqAddr.ForeColor = System.Drawing.Color.Black;
                textBoxPowerReqAddr.Text = "";
            }
        }

        #endregion

        #region Simple Req

        private void textBoxSimpleReqAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxSimpleReqAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxSimpleReqAddr.ForeColor = System.Drawing.Color.Black;
                textBoxSimpleReqAddr.Text = "";
            }
        }

        private void textBoxSimpleReqEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxSimpleReqEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxSimpleReqEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxSimpleReqEndPoint.Text = "";
            }
        }

        #endregion

        #region Complex Req

        private void textBoxComplexReqAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxComplexReqAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxComplexReqAddr.ForeColor = System.Drawing.Color.Black;
                textBoxComplexReqAddr.Text = "";
            }
        }

        #endregion

        #region User Req

        private void textBoxUserReqAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxUserReqAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxUserReqAddr.ForeColor = System.Drawing.Color.Black;
                textBoxUserReqAddr.Text = "";
            }
        }

        #endregion

        #region User Set Req

        private void textBoxUserSetReqAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxUserSetReqAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxUserSetReqAddr.ForeColor = System.Drawing.Color.Black;
                textBoxUserSetReqAddr.Text = "";
            }
        }

        private void textBoxUserSetReqDescription_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxUserSetReqDescription.ForeColor != System.Drawing.Color.Black)
            {
                textBoxUserSetReqDescription.ForeColor = System.Drawing.Color.Black;
                textBoxUserSetReqDescription.Text = "";
            }
        }

        #endregion

        #region LQI Req

        private void textBoxLqiReqTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxLqiReqTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxLqiReqTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxLqiReqTargetAddr.Text = "";
            }
        }

        private void textBoxLqiReqStartIndex_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxLqiReqStartIndex.ForeColor != System.Drawing.Color.Black)
            {
                textBoxLqiReqStartIndex.ForeColor = System.Drawing.Color.Black;
                textBoxLqiReqStartIndex.Text = "";
            }
        }

        #endregion

        #region Restore NWK Frame Counter

        private void textBoxRestoreNwkFrameCounter_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRestoreNwkFrameCounter.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRestoreNwkFrameCounter.ForeColor = System.Drawing.Color.Black;
                textBoxRestoreNwkFrameCounter.Text = "";
            }
        }

        #endregion

        #endregion

        #region GeneralTab

        #region Read Attribute

        private void textBoxReadAttribTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadAttribTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadAttribTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxReadAttribTargetAddr.Text = "";
            }
        }

        private void textBoxReadAttribSrcEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadAttribSrcEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadAttribSrcEP.ForeColor = System.Drawing.Color.Black;
                textBoxReadAttribSrcEP.Text = "";
            }
        }

        private void textBoxReadAttribDstEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadAttribDstEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadAttribDstEP.ForeColor = System.Drawing.Color.Black;
                textBoxReadAttribDstEP.Text = "";
            }
        }

        private void textBoxReadAttribClusterID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadAttribClusterID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadAttribClusterID.ForeColor = System.Drawing.Color.Black;
                textBoxReadAttribClusterID.Text = "";
            }
        }

        private void textBoxReadAttribCount_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadAttribCount.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadAttribCount.ForeColor = System.Drawing.Color.Black;
                textBoxReadAttribCount.Text = "";
            }
        }

        private void textBoxReadAttribID1_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadAttribID1.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadAttribID1.ForeColor = System.Drawing.Color.Black;
                textBoxReadAttribID1.Text = "";
            }
        }

        private void textBoxReadAttribManuID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadAttribManuID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadAttribManuID.ForeColor = System.Drawing.Color.Black;
                textBoxReadAttribManuID.Text = "";
            }
        }

        #endregion
        
        #region Write Attribute

        private void textBoxWriteAttribTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxWriteAttribTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxWriteAttribTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxWriteAttribTargetAddr.Text = "";
            }
        }

        private void textBoxWriteAttribSrcEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxWriteAttribSrcEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxWriteAttribSrcEP.ForeColor = System.Drawing.Color.Black;
                textBoxWriteAttribSrcEP.Text = "";
            }
        }

        private void textBoxWriteAttribDstEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxWriteAttribDstEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxWriteAttribDstEP.ForeColor = System.Drawing.Color.Black;
                textBoxWriteAttribDstEP.Text = "";
            }
        }

        private void textBoxWriteAttribClusterID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxWriteAttribClusterID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxWriteAttribClusterID.ForeColor = System.Drawing.Color.Black;
                textBoxWriteAttribClusterID.Text = "";
            }
        }

        private void textBoxWriteAttribID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxWriteAttribID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxWriteAttribID.ForeColor = System.Drawing.Color.Black;
                textBoxWriteAttribID.Text = "";
            }
        }

        private void textBoxWriteAttribDataType_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxWriteAttribDataType.ForeColor != System.Drawing.Color.Black)
            {
                textBoxWriteAttribDataType.ForeColor = System.Drawing.Color.Black;
                textBoxWriteAttribDataType.Text = "";
            }
        }

        private void textBoxWriteAttribData_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxWriteAttribData.ForeColor != System.Drawing.Color.Black)
            {
                textBoxWriteAttribData.ForeColor = System.Drawing.Color.Black;
                textBoxWriteAttribData.Text = "";
            }
        }

        private void textBoxWriteAttribManuID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxWriteAttribManuID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxWriteAttribManuID.ForeColor = System.Drawing.Color.Black;
                textBoxWriteAttribManuID.Text = "";
            }
        }

        #endregion

        #region Config Report

        private void textBoxConfigReportTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxConfigReportTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxConfigReportTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxConfigReportTargetAddr.Text = "";
            }
        }

        private void textBoxConfigReportSrcEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxConfigReportSrcEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxConfigReportSrcEP.ForeColor = System.Drawing.Color.Black;
                textBoxConfigReportSrcEP.Text = "";
            }
        }

        private void textBoxConfigReportDstEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxConfigReportDstEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxConfigReportDstEP.ForeColor = System.Drawing.Color.Black;
                textBoxConfigReportDstEP.Text = "";
            }
        }

        private void textBoxConfigReportClusterID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxConfigReportClusterID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxConfigReportClusterID.ForeColor = System.Drawing.Color.Black;
                textBoxConfigReportClusterID.Text = "";
            }
        }

        private void textBoxConfigReportAttribType_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxConfigReportAttribType.ForeColor != System.Drawing.Color.Black)
            {
                textBoxConfigReportAttribType.ForeColor = System.Drawing.Color.Black;
                textBoxConfigReportAttribType.Text = "";
            }
        }

        private void textBoxConfigReportAttribID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxConfigReportAttribID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxConfigReportAttribID.ForeColor = System.Drawing.Color.Black;
                textBoxConfigReportAttribID.Text = "";
            }
        }

        private void textBoxConfigReportMinInterval_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxConfigReportMinInterval.ForeColor != System.Drawing.Color.Black)
            {
                textBoxConfigReportMinInterval.ForeColor = System.Drawing.Color.Black;
                textBoxConfigReportMinInterval.Text = "";
            }
        }

        private void textBoxConfigReportMaxInterval_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxConfigReportMaxInterval.ForeColor != System.Drawing.Color.Black)
            {
                textBoxConfigReportMaxInterval.ForeColor = System.Drawing.Color.Black;
                textBoxConfigReportMaxInterval.Text = "";
            }
        }

        private void textBoxConfigReportTimeOut_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxConfigReportTimeOut.ForeColor != System.Drawing.Color.Black)
            {
                textBoxConfigReportTimeOut.ForeColor = System.Drawing.Color.Black;
                textBoxConfigReportTimeOut.Text = "";
            }
        }

        private void textBoxConfigReportChange_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxConfigReportChange.ForeColor != System.Drawing.Color.Black)
            {
                textBoxConfigReportChange.ForeColor = System.Drawing.Color.Black;
                textBoxConfigReportChange.Text = "";
            }
        }

        #endregion

        #region Read Report Config

        private void textBoxReadReportConfigTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadReportConfigTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadReportConfigTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxReadReportConfigTargetAddr.Text = "";
            }
        }

        private void textBoxReadReportConfigSrcEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadReportConfigSrcEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadReportConfigSrcEP.ForeColor = System.Drawing.Color.Black;
                textBoxReadReportConfigSrcEP.Text = "";
            }
        }

        private void textBoxReadReportConfigDstEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadReportConfigDstEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadReportConfigDstEP.ForeColor = System.Drawing.Color.Black;
                textBoxReadReportConfigDstEP.Text = "";
            }
        }

        private void textBoxReadReportConfigClusterID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadReportConfigClusterID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadReportConfigClusterID.ForeColor = System.Drawing.Color.Black;
                textBoxReadReportConfigClusterID.Text = "";
            }
        }

        private void textBoxReadReportConfigAttribID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadReportConfigAttribID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadReportConfigAttribID.ForeColor = System.Drawing.Color.Black;
                textBoxReadReportConfigAttribID.Text = "";
            }
        }

        #endregion

        #region Read All Attribute

        private void textBoxReadAllAttribAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadAllAttribAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadAllAttribAddr.ForeColor = System.Drawing.Color.Black;
                textBoxReadAllAttribAddr.Text = "";
            }
        }

        private void textBoxReadAllAttribSrcEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadAllAttribSrcEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadAllAttribSrcEP.ForeColor = System.Drawing.Color.Black;
                textBoxReadAllAttribSrcEP.Text = "";
            }
        }

        private void textBoxReadAllAttribDstEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadAllAttribDstEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadAllAttribDstEP.ForeColor = System.Drawing.Color.Black;
                textBoxReadAllAttribDstEP.Text = "";
            }
        }

        private void textBoxReadAllAttribClusterID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxReadAllAttribClusterID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxReadAllAttribClusterID.ForeColor = System.Drawing.Color.Black;
                textBoxReadAllAttribClusterID.Text = "";
            }
        }

        #endregion

        #region Discover Attributes

        private void textBoxDiscoverAttributesAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDiscoverAttributesAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDiscoverAttributesAddr.ForeColor = System.Drawing.Color.Black;
                textBoxDiscoverAttributesAddr.Text = "";
            }
        }

        private void textBoxDiscoverAttributesSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDiscoverAttributesSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDiscoverAttributesSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxDiscoverAttributesSrcEp.Text = "";
            }
        }

        private void textBoxDiscoverAttributesDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDiscoverAttributesDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDiscoverAttributesDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxDiscoverAttributesDstEp.Text = "";
            }
        }

        private void textBoxDiscoverAttributesClusterID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDiscoverAttributesClusterID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDiscoverAttributesClusterID.ForeColor = System.Drawing.Color.Black;
                textBoxDiscoverAttributesClusterID.Text = "";
            }
        }

        private void textBoxDiscoverAttributesStartAttrId_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDiscoverAttributesStartAttrId.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDiscoverAttributesStartAttrId.ForeColor = System.Drawing.Color.Black;
                textBoxDiscoverAttributesStartAttrId.Text = "";
            }
        }

        private void textBoxDiscoverAttributesMaxIDs_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDiscoverAttributesMaxIDs.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDiscoverAttributesMaxIDs.ForeColor = System.Drawing.Color.Black;
                textBoxDiscoverAttributesMaxIDs.Text = "";
            }
        }

        #endregion

        #region MTO Route Request

        private void textBoxManyToOneRouteRequesRadius_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxManyToOneRouteRequesRadius.ForeColor != System.Drawing.Color.Black)
            {
                textBoxManyToOneRouteRequesRadius.ForeColor = System.Drawing.Color.Black;
                textBoxManyToOneRouteRequesRadius.Text = "";
            }
        }

        #endregion

        #region NWK Update

        private void textBoxMgmtNwkUpdateTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMgmtNwkUpdateTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMgmtNwkUpdateTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxMgmtNwkUpdateTargetAddr.Text = "";
            }
        }

        private void textBoxMgmtNwkUpdateChannelMask_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMgmtNwkUpdateChannelMask.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMgmtNwkUpdateChannelMask.ForeColor = System.Drawing.Color.Black;
                textBoxMgmtNwkUpdateChannelMask.Text = "";
            }
        }

        private void textBoxMgmtNwkUpdateScanDuration_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMgmtNwkUpdateScanDuration.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMgmtNwkUpdateScanDuration.ForeColor = System.Drawing.Color.Black;
                textBoxMgmtNwkUpdateScanDuration.Text = "";
            }
        }

        private void textBoxMgmtNwkUpdateScanCount_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMgmtNwkUpdateScanCount.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMgmtNwkUpdateScanCount.ForeColor = System.Drawing.Color.Black;
                textBoxMgmtNwkUpdateScanCount.Text = "";
            }
        }

        private void textBoxMgmtNwkUpdateNwkManagerAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMgmtNwkUpdateNwkManagerAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMgmtNwkUpdateNwkManagerAddr.ForeColor = System.Drawing.Color.Black;
                textBoxMgmtNwkUpdateNwkManagerAddr.Text = "";
            }
        }

        #endregion

        #region Discover Commands

        private void textBoxDiscoverCommandsTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDiscoverCommandsTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDiscoverCommandsTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxDiscoverCommandsTargetAddr.Text = "";
            }
        }

        private void textBoxDiscoverCommandsSrcEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDiscoverCommandsSrcEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDiscoverCommandsSrcEP.ForeColor = System.Drawing.Color.Black;
                textBoxDiscoverCommandsSrcEP.Text = "";
            }
        }

        private void textBoxDiscoverCommandsDstEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDiscoverCommandsDstEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDiscoverCommandsDstEP.ForeColor = System.Drawing.Color.Black;
                textBoxDiscoverCommandsDstEP.Text = "";
            }
        }

        private void textBoxDiscoverCommandsClusterID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDiscoverCommandsClusterID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDiscoverCommandsClusterID.ForeColor = System.Drawing.Color.Black;
                textBoxDiscoverCommandsClusterID.Text = "";
            }
        }

        private void textBoxDiscoverCommandsCommandID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDiscoverCommandsCommandID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDiscoverCommandsCommandID.ForeColor = System.Drawing.Color.Black;
                textBoxDiscoverCommandsCommandID.Text = "";
            }
        }

        private void textBoxDiscoverCommandsManuID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDiscoverCommandsManuID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDiscoverCommandsManuID.ForeColor = System.Drawing.Color.Black;
                textBoxDiscoverCommandsManuID.Text = "";
            }
        }

        private void textBoxDiscoverCommandsMaxCommands_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDiscoverCommandsMaxCommands.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDiscoverCommandsMaxCommands.ForeColor = System.Drawing.Color.Black;
                textBoxDiscoverCommandsMaxCommands.Text = "";
            }
        }

        #endregion

        #region Raw Data Commands

        private void textBoxRawDataCommandsTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRawDataCommandsTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRawDataCommandsTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxRawDataCommandsTargetAddr.Text = "";
            }
        }

        private void textBoxRawDataCommandsSrcEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRawDataCommandsSrcEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRawDataCommandsSrcEP.ForeColor = System.Drawing.Color.Black;
                textBoxRawDataCommandsSrcEP.Text = "";
            }
        }

        private void textBoxRawDataCommandsDstEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRawDataCommandsDstEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRawDataCommandsDstEP.ForeColor = System.Drawing.Color.Black;
                textBoxRawDataCommandsDstEP.Text = "";
            }
        }

        private void textBoxRawDataCommandsProfileID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRawDataCommandsProfileID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRawDataCommandsProfileID.ForeColor = System.Drawing.Color.Black;
                textBoxRawDataCommandsProfileID.Text = "";
            }
        }

        private void textBoxRawDataCommandsClusterID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRawDataCommandsClusterID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRawDataCommandsClusterID.ForeColor = System.Drawing.Color.Black;
                textBoxRawDataCommandsClusterID.Text = "";
            }
        }

        private void textBoxRawDataCommandsRadius_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRawDataCommandsRadius.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRawDataCommandsRadius.ForeColor = System.Drawing.Color.Black;
                textBoxRawDataCommandsRadius.Text = "";
            }
        }

        private void textBoxRawDataCommandsSecurityMode_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRawDataCommandsSecurityMode.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRawDataCommandsSecurityMode.ForeColor = System.Drawing.Color.Black;
                textBoxRawDataCommandsSecurityMode.Text = "";
            }
        }

        private void textBoxRawDataCommandsData_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRawDataCommandsData.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRawDataCommandsData.ForeColor = System.Drawing.Color.Black;
                textBoxRawDataCommandsData.Text = "";
            }
        }

        #endregion

        #region OOB Data

        private void textBoxOOBDataAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOOBDataAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOOBDataAddr.ForeColor = System.Drawing.Color.Black;
                textBoxOOBDataAddr.Text = "";
            }
        }

        private void textBoxOOBDataKey_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOOBDataKey.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOOBDataKey.ForeColor = System.Drawing.Color.Black;
                textBoxOOBDataKey.Text = "";
            }
        }

        #endregion

        #endregion

        #region AHIControlTab

        #region DIO Set Direction

        private void textBoxDioSetDirectionInputPinMask_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDioSetDirectionInputPinMask.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDioSetDirectionInputPinMask.ForeColor = System.Drawing.Color.Black;
                textBoxDioSetDirectionInputPinMask.Text = "";
            }
        }

        private void textBoxDioSetDirectionOutputPinMask_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDioSetDirectionOutputPinMask.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDioSetDirectionOutputPinMask.ForeColor = System.Drawing.Color.Black;
                textBoxDioSetDirectionOutputPinMask.Text = "";
            }
        }

        #endregion

        #region DIO Set Output

        private void textBoxDioSetOutputOnPinMask_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDioSetOutputOnPinMask.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDioSetOutputOnPinMask.ForeColor = System.Drawing.Color.Black;
                textBoxDioSetOutputOnPinMask.Text = "";
            }
        }

        private void textBoxDioSetOutputOffPinMask_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxDioSetOutputOffPinMask.ForeColor != System.Drawing.Color.Black)
            {
                textBoxDioSetOutputOffPinMask.ForeColor = System.Drawing.Color.Black;
                textBoxDioSetOutputOffPinMask.Text = "";
            }
        }

        #endregion

        #region IPN Config

        private void textBoxIPNConfigDioRfActiveOutDioMask_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxIPNConfigDioRfActiveOutDioMask.ForeColor != System.Drawing.Color.Black)
            {
                textBoxIPNConfigDioRfActiveOutDioMask.ForeColor = System.Drawing.Color.Black;
                textBoxIPNConfigDioRfActiveOutDioMask.Text = "";
            }
        }

        private void textBoxIPNConfigDioStatusOutDioMask_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxIPNConfigDioStatusOutDioMask.ForeColor != System.Drawing.Color.Black)
            {
                textBoxIPNConfigDioStatusOutDioMask.ForeColor = System.Drawing.Color.Black;
                textBoxIPNConfigDioStatusOutDioMask.Text = "";
            }
        }

        private void textBoxIPNConfigDioTxConfInDioMask_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxIPNConfigDioTxConfInDioMask.ForeColor != System.Drawing.Color.Black)
            {
                textBoxIPNConfigDioTxConfInDioMask.ForeColor = System.Drawing.Color.Black;
                textBoxIPNConfigDioTxConfInDioMask.Text = "";
            }
        }

        private void textBoxIPNConfigPollPeriod_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxIPNConfigPollPeriod.ForeColor != System.Drawing.Color.Black)
            {
                textBoxIPNConfigPollPeriod.ForeColor = System.Drawing.Color.Black;
                textBoxIPNConfigPollPeriod.Text = "";
            }
        }

        #endregion

        #region AHI Tx Power

        private void textBoxAHITxPower_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAHITxPower.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAHITxPower.ForeColor = System.Drawing.Color.Black;
                textBoxAHITxPower.Text = "";
            }
        }

        #endregion

        #endregion

        #region BasicClusterTab

        #region Reset to FD

        private void textBoxBasicResetTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxBasicResetTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxBasicResetTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxBasicResetTargetAddr.Text = "";
            }
        }

        private void textBoxBasicResetSrcEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxBasicResetSrcEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxBasicResetSrcEP.ForeColor = System.Drawing.Color.Black;
                textBoxBasicResetSrcEP.Text = "";
            }
        }

        private void textBoxBasicResetDstEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxBasicResetDstEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxBasicResetDstEP.ForeColor = System.Drawing.Color.Black;
                textBoxBasicResetDstEP.Text = "";
            }
        }

        #endregion

        #endregion

        #region GroupClusterTab

        #region Add Group

        private void textBoxAddGroupAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddGroupAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddGroupAddr.ForeColor = System.Drawing.Color.Black;
                textBoxAddGroupAddr.Text = "";
            }
        }

        private void textBoxAddGroupSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddGroupSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddGroupSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxAddGroupSrcEp.Text = "";
            }
        }

        private void textBoxAddGroupDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddGroupDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddGroupDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxAddGroupDstEp.Text = "";
            }
        }

        private void textBoxAddGroupGroupAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddGroupGroupAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddGroupGroupAddr.ForeColor = System.Drawing.Color.Black;
                textBoxAddGroupGroupAddr.Text = "";
            }
        }

        private void textBoxGroupNameLength_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGroupNameLength.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGroupNameLength.ForeColor = System.Drawing.Color.Black;
                textBoxGroupNameLength.Text = "";
            }
        }

        private void textBoxGroupNameMaxLength_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGroupNameMaxLength.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGroupNameMaxLength.ForeColor = System.Drawing.Color.Black;
                textBoxGroupNameMaxLength.Text = "";
            }
        }

        private void textBoxGroupName_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGroupName.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGroupName.ForeColor = System.Drawing.Color.Black;
                textBoxGroupName.Text = "";
            }
        }

        #endregion

        #region View Group

        private void textBoxViewGroupAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxViewGroupAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxViewGroupAddr.ForeColor = System.Drawing.Color.Black;
                textBoxViewGroupAddr.Text = "";
            }
        }

        private void textBoxViewGroupSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxViewGroupSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxViewGroupSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxViewGroupSrcEp.Text = "";
            }
        }

        private void textBoxViewGroupDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxViewGroupDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxViewGroupDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxViewGroupDstEp.Text = "";
            }
        }

        private void textBoxViewGroupGroupAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxViewGroupGroupAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxViewGroupGroupAddr.ForeColor = System.Drawing.Color.Black;
                textBoxViewGroupGroupAddr.Text = "";
            }
        }

        #endregion

        #region Get Group

        private void textBoxGetGroupTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGetGroupTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGetGroupTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxGetGroupTargetAddr.Text = "";
            }
        }

        private void textBoxGetGroupSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGetGroupSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGetGroupSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxGetGroupSrcEp.Text = "";
            }
        }

        private void textBoxGetGroupDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGetGroupDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGetGroupDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxGetGroupDstEp.Text = "";
            }
        }

        private void textBoxGetGroupCount_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGetGroupCount.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGetGroupCount.ForeColor = System.Drawing.Color.Black;
                textBoxGetGroupCount.Text = "";
            }
        }

        #endregion

        #region Remove Group

        private void textBoxRemoveGroupTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveGroupTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveGroupTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveGroupTargetAddr.Text = "";
            }
        }

        private void textBoxRemoveGroupSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveGroupSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveGroupSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveGroupSrcEp.Text = "";
            }
        }

        private void textBoxRemoveGroupDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveGroupDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveGroupDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveGroupDstEp.Text = "";
            }
        }

        private void textBoxRemoveGroupGroupAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveGroupGroupAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveGroupGroupAddr.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveGroupGroupAddr.Text = "";
            }
        }

        #endregion

        #region Remove All

        private void textBoxRemoveAllGroupTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveAllGroupTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveAllGroupTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveAllGroupTargetAddr.Text = "";
            }
        }

        private void textBoxRemoveAllGroupSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveAllGroupSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveAllGroupSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveAllGroupSrcEp.Text = "";
            }
        }

        private void textBoxRemoveAllGroupDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveAllGroupDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveAllGroupDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveAllGroupDstEp.Text = "";
            }
        }

        #region Add If Identifying

        private void textBoxGroupAddIfIndentifyingTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGroupAddIfIndentifyingTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGroupAddIfIndentifyingTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxGroupAddIfIndentifyingTargetAddr.Text = "";
            }
        }

        private void textBoxGroupAddIfIdentifySrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGroupAddIfIdentifySrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGroupAddIfIdentifySrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxGroupAddIfIdentifySrcEp.Text = "";
            }
        }

        private void textBoxGroupAddIfIdentifyDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGroupAddIfIdentifyDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGroupAddIfIdentifyDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxGroupAddIfIdentifyDstEp.Text = "";
            }
        }

        private void textBoxGroupAddIfIdentifyGroupID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGroupAddIfIdentifyGroupID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGroupAddIfIdentifyGroupID.ForeColor = System.Drawing.Color.Black;
                textBoxGroupAddIfIdentifyGroupID.Text = "";
            }
        }

        #endregion

        #endregion

        #endregion

        #region IdentifyClusterTab

        private void textBoxSendIdAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxSendIdAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxSendIdAddr.ForeColor = System.Drawing.Color.Black;
                textBoxSendIdAddr.Text = "";
            }
        }

        private void textBoxSendIdSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxSendIdSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxSendIdSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxSendIdSrcEp.Text = "";
            }
        }

        private void textBoxIdSendDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxIdSendDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxIdSendDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxIdSendDstEp.Text = "";
            }
        }

        private void textBoxIdSendTime_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxIdSendTime.ForeColor != System.Drawing.Color.Black)
            {
                textBoxIdSendTime.ForeColor = System.Drawing.Color.Black;
                textBoxIdSendTime.Text = "";
            }
        }

        private void textBoxIdQueryAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxIdQueryAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxIdQueryAddr.ForeColor = System.Drawing.Color.Black;
                textBoxIdQueryAddr.Text = "";
            }
        }

        private void textBoxIdQuerySrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxIdQuerySrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxIdQuerySrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxIdQuerySrcEp.Text = "";
            }
        }

        private void textBoxIdQueryDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxIdQueryDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxIdQueryDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxIdQueryDstEp.Text = "";
            }
        }

        #endregion

        #region LevelClusterTab

        private void textBoxMoveToLevelAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToLevelAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToLevelAddr.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToLevelAddr.Text = "";
            }
        }

        private void textBoxMoveToLevelSrcEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToLevelSrcEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToLevelSrcEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToLevelSrcEndPoint.Text = "";
            }
        }

        private void textBoxMoveToLevelDstEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToLevelDstEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToLevelDstEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToLevelDstEndPoint.Text = "";
            }
        }

        private void textBoxMoveToLevelLevel_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToLevelLevel.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToLevelLevel.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToLevelLevel.Text = "";
            }
        }

        private void textBoxMoveToLevelTransTime_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToLevelTransTime.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToLevelTransTime.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToLevelTransTime.Text = "";
            }
        }

        #endregion

        #region OnOffClusterTab

        private void textBoxOnOffAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOnOffAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOnOffAddr.ForeColor = System.Drawing.Color.Black;
                textBoxOnOffAddr.Text = "";
            }
        }

        private void textBoxOnOffSrcEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOnOffSrcEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOnOffSrcEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxOnOffSrcEndPoint.Text = "";
            }
        }

        private void textBoxOnOffDstEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOnOffDstEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOnOffDstEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxOnOffDstEndPoint.Text = "";
            }
        }

        #endregion

        #region ScenesClusterTab

        private void textBoxViewSceneAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxViewSceneAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxViewSceneAddr.ForeColor = System.Drawing.Color.Black;
                textBoxViewSceneAddr.Text = "";
            }
        }

        private void textBoxViewSceneSrcEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxViewSceneSrcEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxViewSceneSrcEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxViewSceneSrcEndPoint.Text = "";
            }
        }

        private void textBoxViewSceneDstEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxViewSceneDstEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxViewSceneDstEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxViewSceneDstEndPoint.Text = "";
            }
        }

        private void textBoxViewSceneGroupId_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxViewSceneGroupId.ForeColor != System.Drawing.Color.Black)
            {
                textBoxViewSceneGroupId.ForeColor = System.Drawing.Color.Black;
                textBoxViewSceneGroupId.Text = "";
            }
        }

        private void textBoxViewSceneSceneId_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxViewSceneSceneId.ForeColor != System.Drawing.Color.Black)
            {
                textBoxViewSceneSceneId.ForeColor = System.Drawing.Color.Black;
                textBoxViewSceneSceneId.Text = "";
            }
        }

        private void textBoxAddSceneAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddSceneAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddSceneAddr.ForeColor = System.Drawing.Color.Black;
                textBoxAddSceneAddr.Text = "";
            }
        }

        private void textBoxAddSceneSrcEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddSceneSrcEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddSceneSrcEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxAddSceneSrcEndPoint.Text = "";
            }
        }

        private void textBoxAddSceneDstEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddSceneDstEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddSceneDstEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxAddSceneDstEndPoint.Text = "";
            }
        }

        private void textBoxAddSceneGroupId_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddSceneGroupId.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddSceneGroupId.ForeColor = System.Drawing.Color.Black;
                textBoxAddSceneGroupId.Text = "";
            }
        }

        private void textBoxAddSceneSceneId_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddSceneSceneId.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddSceneSceneId.ForeColor = System.Drawing.Color.Black;
                textBoxAddSceneSceneId.Text = "";
            }
        }

        private void textBoxAddSceneTransTime_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddSceneTransTime.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddSceneTransTime.ForeColor = System.Drawing.Color.Black;
                textBoxAddSceneTransTime.Text = "";
            }
        }

        private void textBoxAddSceneName_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddSceneName.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddSceneName.ForeColor = System.Drawing.Color.Black;
                textBoxAddSceneName.Text = "";
            }
        }

        private void textBoxAddSceneNameLen_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddSceneNameLen.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddSceneNameLen.ForeColor = System.Drawing.Color.Black;
                textBoxAddSceneNameLen.Text = "";
            }
        }

        private void textBoxAddSceneMaxNameLen_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddSceneMaxNameLen.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddSceneMaxNameLen.ForeColor = System.Drawing.Color.Black;
                textBoxAddSceneMaxNameLen.Text = "";
            }
        }

        private void textBoxAddSceneExtLen_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddSceneExtLen.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddSceneExtLen.ForeColor = System.Drawing.Color.Black;
                textBoxAddSceneExtLen.Text = "";
            }
        }

        private void textBoxAddSceneData_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxAddSceneData.ForeColor != System.Drawing.Color.Black)
            {
                textBoxAddSceneData.ForeColor = System.Drawing.Color.Black;
                textBoxAddSceneData.Text = "";
            }
        }

        private void textBoxStoreSceneAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxStoreSceneAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxStoreSceneAddr.ForeColor = System.Drawing.Color.Black;
                textBoxStoreSceneAddr.Text = "";
            }
        }

        private void textBoxStoreSceneSrcEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxStoreSceneSrcEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxStoreSceneSrcEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxStoreSceneSrcEndPoint.Text = "";
            }
        }

        private void textBoxStoreSceneDstEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxStoreSceneDstEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxStoreSceneDstEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxStoreSceneDstEndPoint.Text = "";
            }
        }

        private void textBoxStoreSceneGroupId_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxStoreSceneGroupId.ForeColor != System.Drawing.Color.Black)
            {
                textBoxStoreSceneGroupId.ForeColor = System.Drawing.Color.Black;
                textBoxStoreSceneGroupId.Text = "";
            }
        }

        private void textBoxStoreSceneSceneId_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxStoreSceneSceneId.ForeColor != System.Drawing.Color.Black)
            {
                textBoxStoreSceneSceneId.ForeColor = System.Drawing.Color.Black;
                textBoxStoreSceneSceneId.Text = "";
            }
        }

        private void textBoxRecallSceneAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRecallSceneAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRecallSceneAddr.ForeColor = System.Drawing.Color.Black;
                textBoxRecallSceneAddr.Text = "";
            }
        }

        private void textBoxRecallSceneSrcEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRecallSceneSrcEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRecallSceneSrcEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxRecallSceneSrcEndPoint.Text = "";
            }
        }

        private void textBoxRecallSceneDstEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRecallSceneDstEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRecallSceneDstEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxRecallSceneDstEndPoint.Text = "";
            }
        }

        private void textBoxRecallSceneGroupId_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRecallSceneGroupId.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRecallSceneGroupId.ForeColor = System.Drawing.Color.Black;
                textBoxRecallSceneGroupId.Text = "";
            }
        }

        private void textBoxRecallSceneSceneId_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRecallSceneSceneId.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRecallSceneSceneId.ForeColor = System.Drawing.Color.Black;
                textBoxRecallSceneSceneId.Text = "";
            }
        }

        private void textBoxGetSceneMembershipAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGetSceneMembershipAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGetSceneMembershipAddr.ForeColor = System.Drawing.Color.Black;
                textBoxGetSceneMembershipAddr.Text = "";
            }
        }

        private void textBoxGetSceneMembershipSrcEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGetSceneMembershipSrcEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGetSceneMembershipSrcEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxGetSceneMembershipSrcEndPoint.Text = "";
            }
        }

        private void textBoxGetSceneMembershipDstEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGetSceneMembershipDstEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGetSceneMembershipDstEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxGetSceneMembershipDstEndPoint.Text = "";
            }
        }

        private void textBoxGetSceneMembershipGroupID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxGetSceneMembershipGroupID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxGetSceneMembershipGroupID.ForeColor = System.Drawing.Color.Black;
                textBoxGetSceneMembershipGroupID.Text = "";
            }
        }

        private void textBoxRemoveAllScenesAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveAllScenesAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveAllScenesAddr.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveAllScenesAddr.Text = "";
            }
        }

        private void textBoxRemoveAllScenesSrcEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveAllScenesSrcEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveAllScenesSrcEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveAllScenesSrcEndPoint.Text = "";
            }
        }

        private void textBoxRemoveAllScenesDstEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveAllScenesDstEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveAllScenesDstEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveAllScenesDstEndPoint.Text = "";
            }
        }

        private void textBoxRemoveAllScenesGroupID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveAllScenesGroupID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveAllScenesGroupID.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveAllScenesGroupID.Text = "";
            }
        }

        private void textBoxRemoveSceneAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveSceneAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveSceneAddr.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveSceneAddr.Text = "";
            }
        }

        private void textBoxRemoveSceneSrcEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveSceneSrcEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveSceneSrcEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveSceneSrcEndPoint.Text = "";
            }
        }

        private void textBoxRemoveSceneDstEndPoint_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveSceneDstEndPoint.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveSceneDstEndPoint.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveSceneDstEndPoint.Text = "";
            }
        }

        private void textBoxRemoveSceneGroupID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveSceneGroupID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveSceneGroupID.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveSceneGroupID.Text = "";
            }
        }

        private void textBoxRemoveSceneSceneID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxRemoveSceneSceneID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxRemoveSceneSceneID.ForeColor = System.Drawing.Color.Black;
                textBoxRemoveSceneSceneID.Text = "";
            }
        }

        #endregion

        #region ColorClusterTab

        private void textBoxMoveToHueAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToHueAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToHueAddr.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToHueAddr.Text = "";
            }
        }

        private void textBoxMoveToHueSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToHueSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToHueSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToHueSrcEp.Text = "";
            }
        }

        private void textBoxMoveToHueDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToHueDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToHueDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToHueDstEp.Text = "";
            }
        }

        private void textBoxMoveToHueHue_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToHueHue.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToHueHue.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToHueHue.Text = "";
            }
        }

        private void textBoxMoveToHueDir_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToHueDir.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToHueDir.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToHueDir.Text = "";
            }
        }

        private void textBoxMoveToHueTime_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToHueTime.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToHueTime.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToHueTime.Text = "";
            }
        }

        private void textBoxMoveToColorAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToColorAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToColorAddr.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToColorAddr.Text = "";
            }
        }

        private void textBoxMoveToColorSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToColorSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToColorSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToColorSrcEp.Text = "";
            }
        }

        private void textBoxMoveToColorDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToColorDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToColorDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToColorDstEp.Text = "";
            }
        }

        private void textBoxMoveToColorX_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToColorX.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToColorX.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToColorX.Text = "";
            }
        }

        private void textBoxMoveToColorY_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToColorY.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToColorY.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToColorY.Text = "";
            }
        }

        private void textBoxMoveToColorTime_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToColorTime.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToColorTime.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToColorTime.Text = "";
            }
        }

        private void textBoxMoveToSatAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToSatAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToSatAddr.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToSatAddr.Text = "";
            }
        }

        private void textBoxMoveToSatSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToSatSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToSatSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToSatSrcEp.Text = "";
            }
        }

        private void textBoxMoveToSatDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToSatDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToSatDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToSatDstEp.Text = "";
            }
        }

        private void textBoxMoveToSatSat_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToSatSat.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToSatSat.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToSatSat.Text = "";
            }
        }

        private void textBoxMoveToSatTime_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToSatTime.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToSatTime.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToSatTime.Text = "";
            }
        }

        private void textBoxMoveToColorTempAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToColorTempAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToColorTempAddr.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToColorTempAddr.Text = "";
            }
        }

        private void textBoxMoveToColorTempSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToColorTempSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToColorTempSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToColorTempSrcEp.Text = "";
            }
        }

        private void textBoxMoveToColorTempDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToColorTempDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToColorTempDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToColorTempDstEp.Text = "";
            }
        }

        private void textBoxMoveToColorTempTemp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToColorTempTemp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToColorTempTemp.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToColorTempTemp.Text = "";
            }
        }

        private void textBoxMoveToColorTempRate_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxMoveToColorTempRate.ForeColor != System.Drawing.Color.Black)
            {
                textBoxMoveToColorTempRate.ForeColor = System.Drawing.Color.Black;
                textBoxMoveToColorTempRate.Text = "";
            }
        }

        #endregion

        #region DoorLockClusterTab

        private void textBoxLockUnlockAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxLockUnlockAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxLockUnlockAddr.ForeColor = System.Drawing.Color.Black;
                textBoxLockUnlockAddr.Text = "";
            }
        }

        private void textBoxLockUnlockSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxLockUnlockSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxLockUnlockSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxLockUnlockSrcEp.Text = "";
            }
        }

        private void textBoxLockUnlockDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxLockUnlockDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxLockUnlockDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxLockUnlockDstEp.Text = "";
            }
        }

        #endregion

        #region IASClusterTab

        private void textBoxEnrollRspAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxEnrollRspAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxEnrollRspAddr.ForeColor = System.Drawing.Color.Black;
                textBoxEnrollRspAddr.Text = "";
            }
        }

        private void textBoxEnrollRspSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxEnrollRspSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxEnrollRspSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxEnrollRspSrcEp.Text = "";
            }
        }

        private void textBoxEnrollRspDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxEnrollRspDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxEnrollRspDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxEnrollRspDstEp.Text = "";
            }
        }

        private void textBoxEnrollRspZone_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxEnrollRspZone.ForeColor != System.Drawing.Color.Black)
            {
                textBoxEnrollRspZone.ForeColor = System.Drawing.Color.Black;
                textBoxEnrollRspZone.Text = "";
            }
        }

        #endregion

        #region ZLLOnOffClusterTab

        private void textBoxZllOnOffEffectsAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxZllOnOffEffectsAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxZllOnOffEffectsAddr.ForeColor = System.Drawing.Color.Black;
                textBoxZllOnOffEffectsAddr.Text = "";
            }
        }

        private void textBoxZllOnOffEffectsSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxZllOnOffEffectsSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxZllOnOffEffectsSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxZllOnOffEffectsSrcEp.Text = "";
            }
        }

        private void textBoxZllOnOffEffectsDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxZllOnOffEffectsDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxZllOnOffEffectsDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxZllOnOffEffectsDstEp.Text = "";
            }
        }

        private void textBoxZllOnOffEffectsGradient_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxZllOnOffEffectsGradient.ForeColor != System.Drawing.Color.Black)
            {
                textBoxZllOnOffEffectsGradient.ForeColor = System.Drawing.Color.Black;
                textBoxZllOnOffEffectsGradient.Text = "";
            }
        }

        #endregion

        #region ZLLColorClusterTab

        private void textBoxZllMoveToHueAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxZllMoveToHueAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxZllMoveToHueAddr.ForeColor = System.Drawing.Color.Black;
                textBoxZllMoveToHueAddr.Text = "";
            }
        }

        private void textBoxZllMoveToHueSrcEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxZllMoveToHueSrcEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxZllMoveToHueSrcEp.ForeColor = System.Drawing.Color.Black;
                textBoxZllMoveToHueSrcEp.Text = "";
            }
        }

        private void textBoxZllMoveToHueDstEp_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxZllMoveToHueDstEp.ForeColor != System.Drawing.Color.Black)
            {
                textBoxZllMoveToHueDstEp.ForeColor = System.Drawing.Color.Black;
                textBoxZllMoveToHueDstEp.Text = "";
            }
        }

        private void textBoxZllMoveToHueHue_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxZllMoveToHueHue.ForeColor != System.Drawing.Color.Black)
            {
                textBoxZllMoveToHueHue.ForeColor = System.Drawing.Color.Black;
                textBoxZllMoveToHueHue.Text = "";
            }
        }

        private void textBoxZllMoveToHueDirection_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxZllMoveToHueDirection.ForeColor != System.Drawing.Color.Black)
            {
                textBoxZllMoveToHueDirection.ForeColor = System.Drawing.Color.Black;
                textBoxZllMoveToHueDirection.Text = "";
            }
        }

        private void textBoxZllMoveToHueTransTime_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxZllMoveToHueTransTime.ForeColor != System.Drawing.Color.Black)
            {
                textBoxZllMoveToHueTransTime.ForeColor = System.Drawing.Color.Black;
                textBoxZllMoveToHueTransTime.Text = "";
            }
        }

        #endregion

        #region OTAClusterTab

        private void textBoxOTAImageNotifyTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOTAImageNotifyTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOTAImageNotifyTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxOTAImageNotifyTargetAddr.Text = "";
            }
        }

        private void textBoxOTAImageNotifySrcEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOTAImageNotifySrcEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOTAImageNotifySrcEP.ForeColor = System.Drawing.Color.Black;
                textBoxOTAImageNotifySrcEP.Text = "";
            }
        }

        private void textBoxOTAImageNotifyDstEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOTAImageNotifyDstEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOTAImageNotifyDstEP.ForeColor = System.Drawing.Color.Black;
                textBoxOTAImageNotifyDstEP.Text = "";
            }
        }

        private void textBoxOTAImageNotifyFileVersion_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOTAImageNotifyFileVersion.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOTAImageNotifyFileVersion.ForeColor = System.Drawing.Color.Black;
                textBoxOTAImageNotifyFileVersion.Text = "";
            }
        }

        private void textBoxOTAImageNotifyImageType_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOTAImageNotifyImageType.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOTAImageNotifyImageType.ForeColor = System.Drawing.Color.Black;
                textBoxOTAImageNotifyImageType.Text = "";
            }
        }

        private void textBoxOTAImageNotifyManuID_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOTAImageNotifyManuID.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOTAImageNotifyManuID.ForeColor = System.Drawing.Color.Black;
                textBoxOTAImageNotifyManuID.Text = "";
            }
        }

        private void textBoxOTAImageNotifyJitter_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOTAImageNotifyJitter.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOTAImageNotifyJitter.ForeColor = System.Drawing.Color.Black;
                textBoxOTAImageNotifyJitter.Text = "";
            }
        }

        private void textBoxOTASetWaitForDataParamsTargetAddr_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOTASetWaitForDataParamsTargetAddr.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOTASetWaitForDataParamsTargetAddr.ForeColor = System.Drawing.Color.Black;
                textBoxOTASetWaitForDataParamsTargetAddr.Text = "";
            }
        }

        private void textBoxOTASetWaitForDataParamsSrcEP_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOTASetWaitForDataParamsSrcEP.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOTASetWaitForDataParamsSrcEP.ForeColor = System.Drawing.Color.Black;
                textBoxOTASetWaitForDataParamsSrcEP.Text = "";
            }
        }

        private void textBoxOTASetWaitForDataParamsCurrentTime_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOTASetWaitForDataParamsCurrentTime.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOTASetWaitForDataParamsCurrentTime.ForeColor = System.Drawing.Color.Black;
                textBoxOTASetWaitForDataParamsCurrentTime.Text = "";
            }
        }

        private void textBoxOTASetWaitForDataParamsRequestTime_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOTASetWaitForDataParamsRequestTime.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOTASetWaitForDataParamsRequestTime.ForeColor = System.Drawing.Color.Black;
                textBoxOTASetWaitForDataParamsRequestTime.Text = "";
            }
        }

        private void textBoxOTASetWaitForDataParamsRequestBlockDelay_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxOTASetWaitForDataParamsRequestBlockDelay.ForeColor != System.Drawing.Color.Black)
            {
                textBoxOTASetWaitForDataParamsRequestBlockDelay.ForeColor = System.Drawing.Color.Black;
                textBoxOTASetWaitForDataParamsRequestBlockDelay.Text = "";
            }
        }

        #endregion

        #region PollControlTab

        private void textBoxFastPollExpiryTime_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxFastPollExpiryTime.ForeColor != System.Drawing.Color.Black)
            {
                textBoxFastPollExpiryTime.ForeColor = System.Drawing.Color.Black;
                textBoxFastPollExpiryTime.Text = "";
            }
        }

        #endregion

        #endregion

        #region Restore Grey Text

        #region ManagementTab

        #region Set EPID

        private void textBoxSetEPID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxSetEPID.Text))
            {
                textBoxSetEPID.ForeColor = System.Drawing.Color.Gray;
                textBoxSetEPID.Text = "Extended PAN ID (64-bit Hex)";
            }
        }

        #endregion

        #region Set CMSK

        private void textBoxSetCMSK_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxSetCMSK.Text))
            {
                textBoxSetCMSK.ForeColor = System.Drawing.Color.Gray;
                textBoxSetCMSK.Text = "Single Channel or Mask (32-bit Hex)";
            }
        }

        #endregion

        #region Set Security

        private void textBoxSetSecurityKeySeqNbr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxSetSecurityKeySeqNbr.Text))
            {
                textBoxSetSecurityKeySeqNbr.ForeColor = System.Drawing.Color.Gray;
                textBoxSetSecurityKeySeqNbr.Text = "SQN";
            }
        }

        #endregion

        #region Mgmt Leave

        private void textBoxMgmtLeaveAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMgmtLeaveAddr.Text))
            {
                textBoxMgmtLeaveAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxMgmtLeaveAddr.Text = "Target (16-bit Hex)";
            }
        }

        private void textBoxMgmtLeaveExtAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMgmtLeaveExtAddr.Text))
            {
                textBoxMgmtLeaveExtAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxMgmtLeaveExtAddr.Text = "Address (64-bit Hex)";
            }
        }

        #endregion

        #region Leave

        private void textBoxLeaveAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxLeaveAddr.Text))
            {
                textBoxLeaveAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxLeaveAddr.Text = "Address (64-bit Hex)";
            }
        }

        #endregion

        #region Remove

        private void textBoxRemoveParentAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveParentAddr.Text))
            {
                textBoxRemoveParentAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveParentAddr.Text = "Address (64-bit Hex)";
            }
        }

        private void textBoxRemoveChildAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveChildAddr.Text))
            {
                textBoxRemoveChildAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveChildAddr.Text = "Address (64-bit Hex)";
            }
        }

        #endregion

        #region Permit Join

        private void textBoxPermitJoinAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxPermitJoinAddr.Text))
            {
                textBoxPermitJoinAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxPermitJoinAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxPermitJoinInterval_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxPermitJoinInterval.Text))
            {
                textBoxPermitJoinInterval.ForeColor = System.Drawing.Color.Gray;
                textBoxPermitJoinInterval.Text = "Interval (16-bit Hex)";
            }
        }

        #endregion

        #region Match Req

        private void textBoxMatchReqAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMatchReqAddr.Text))
            {
                textBoxMatchReqAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxMatchReqAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxMatchReqProfileID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMatchReqProfileID.Text))
            {
                textBoxMatchReqProfileID.ForeColor = System.Drawing.Color.Gray;
                textBoxMatchReqProfileID.Text = "Profile (16-bit Hex)";
            }
        }

        private void textBoxMatchReqNbrInputClusters_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMatchReqNbrInputClusters.Text))
            {
                textBoxMatchReqNbrInputClusters.ForeColor = System.Drawing.Color.Gray;
                textBoxMatchReqNbrInputClusters.Text = "Inputs (8-bit Hex)";
            }
        }

        private void textBoxMatchReqInputClusters_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMatchReqInputClusters.Text))
            {
                textBoxMatchReqInputClusters.ForeColor = System.Drawing.Color.Gray;
                textBoxMatchReqInputClusters.Text = "Clusters (16-bit Hex)";
            }
        }

        private void textBoxMatchReqNbrOutputClusters_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMatchReqNbrOutputClusters.Text))
            {
                textBoxMatchReqNbrOutputClusters.ForeColor = System.Drawing.Color.Gray;
                textBoxMatchReqNbrOutputClusters.Text = "Outputs (8-bit Hex)";
            }
        }

        private void textBoxMatchReqOutputClusters_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMatchReqOutputClusters.Text))
            {
                textBoxMatchReqOutputClusters.ForeColor = System.Drawing.Color.Gray;
                textBoxMatchReqOutputClusters.Text = "Clusters (16-bit Hex)";
            }
        }

        #endregion

        #region Bind

        private void textBoxBindTargetExtAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxBindTargetExtAddr.Text))
            {
                textBoxBindTargetExtAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxBindTargetExtAddr.Text = "Target Address (64-bit Hex)";
            }
        }

        private void textBoxBindDestAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxBindDestAddr.Text))
            {
                textBoxBindDestAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxBindDestAddr.Text = "Dst Address (16 or 64-bit Hex)";
            }
        }

        private void textBoxBindTargetEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxBindTargetEP.Text))
            {
                textBoxBindTargetEP.ForeColor = System.Drawing.Color.Gray;
                textBoxBindTargetEP.Text = "Target EP (8-bit Hex)";
            }
        }

        private void textBoxBindClusterID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxBindClusterID.Text))
            {
                textBoxBindClusterID.ForeColor = System.Drawing.Color.Gray;
                textBoxBindClusterID.Text = "Cluster (16-bit Hex)";
            }
        }

        private void textBoxBindDestEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxBindDestEP.Text))
            {
                textBoxBindDestEP.ForeColor = System.Drawing.Color.Gray;
                textBoxBindDestEP.Text = "Dst EP (8-bit Hex)";
            }
        }

        #endregion

        #region UnBind

        private void textBoxUnBindTargetExtAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxUnBindTargetExtAddr.Text))
            {
                textBoxUnBindTargetExtAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxUnBindTargetExtAddr.Text = "Target Address (64-bit Hex)";
            }
        }

        private void textBoxUnBindDestAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxUnBindDestAddr.Text))
            {
                textBoxUnBindDestAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxUnBindDestAddr.Text = "Dst Address (16 or 64-bit Hex)";
            }
        }

        private void textBoxUnBindTargetEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxUnBindTargetEP.Text))
            {
                textBoxUnBindTargetEP.ForeColor = System.Drawing.Color.Gray;
                textBoxUnBindTargetEP.Text = "Target EP (8-bit Hex)";
            }
        }

        private void textBoxUnBindClusterID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxUnBindClusterID.Text))
            {
                textBoxUnBindClusterID.ForeColor = System.Drawing.Color.Gray;
                textBoxUnBindClusterID.Text = "Cluster 16-bit Hex)";
            }
        }

        private void textBoxUnBindDestEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxUnBindDestEP.Text))
            {
                textBoxUnBindDestEP.ForeColor = System.Drawing.Color.Gray;
                textBoxUnBindDestEP.Text = "Dst EP (8-bit Hex)";
            }
        }

        #endregion

        #region Active Req

        private void textBoxActiveEpAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxActiveEpAddr.Text))
            {
                textBoxActiveEpAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxActiveEpAddr.Text = "Address (16-bit Hex)";
            }
        }

        #endregion

        #region IEEE Req

        private void textBoxIeeeReqTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxIeeeReqTargetAddr.Text))
            {
                textBoxIeeeReqTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxIeeeReqTargetAddr.Text = "Target (16-bit Hex)";
            }
        }

        private void textBoxIeeeReqAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxIeeeReqAddr.Text))
            {
                textBoxIeeeReqAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxIeeeReqAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxIeeeReqStartIndex_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxIeeeReqStartIndex.Text))
            {
                textBoxIeeeReqStartIndex.ForeColor = System.Drawing.Color.Gray;
                textBoxIeeeReqStartIndex.Text = "Start Idx (8-bit Hex)";
            }
        }

        #endregion

        #region Addr Req

        private void textBoxNwkAddrReqTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxNwkAddrReqTargetAddr.Text))
            {
                textBoxNwkAddrReqTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxNwkAddrReqTargetAddr.Text = "Target (16-bit Hex)";
            }
        }

        private void textBoxNwkAddrReqExtAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxNwkAddrReqExtAddr.Text))
            {
                textBoxNwkAddrReqExtAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxNwkAddrReqExtAddr.Text = "Address (64-bit Hex)";
            }
        }

        private void textBoxNwkAddrReqStartIndex_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxNwkAddrReqStartIndex.Text))
            {
                textBoxNwkAddrReqStartIndex.ForeColor = System.Drawing.Color.Gray;
                textBoxNwkAddrReqStartIndex.Text = "Start Idx (8-bit Hex)";
            }
        }

        #endregion

        #region Node Req

        private void textBoxNodeDescReq_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxNodeDescReq.Text))
            {
                textBoxNodeDescReq.ForeColor = System.Drawing.Color.Gray;
                textBoxNodeDescReq.Text = "Address (16-bit Hex)";
            }
        }

        #endregion

        #region Power Req

        private void textBoxPowerReqAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxPowerReqAddr.Text))
            {
                textBoxPowerReqAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxPowerReqAddr.Text = "Address (16-bit Hex)";
            }
        }

        #endregion

        #region Simple Req

        private void textBoxSimpleReqAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxSimpleReqAddr.Text))
            {
                textBoxSimpleReqAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxSimpleReqAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxSimpleReqEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxSimpleReqEndPoint.Text))
            {
                textBoxSimpleReqEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxSimpleReqEndPoint.Text = "Dst EP (8-bit Hex)";
            }
        }

        #endregion

        #region ComplexReq

        private void textBoxComplexReqAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxComplexReqAddr.Text))
            {
                textBoxComplexReqAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxComplexReqAddr.Text = "Address (16-bit Hex)";
            }
        }

        #endregion

        #region UserReq

        private void textBoxUserReqAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxUserReqAddr.Text))
            {
                textBoxUserReqAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxUserReqAddr.Text = "Address (16-bit Hex)";
            }
        }

        #endregion

        #region UserSetReq

        private void textBoxUserSetReqAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxUserSetReqAddr.Text))
            {
                textBoxUserSetReqAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxUserSetReqAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxUserSetReqDescription_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxUserSetReqDescription.Text))
            {
                textBoxUserSetReqDescription.ForeColor = System.Drawing.Color.Gray;
                textBoxUserSetReqDescription.Text = "User Description (String)";
            }
        }

        #endregion

        #region Lqi Req

        private void textBoxLqiReqTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxLqiReqTargetAddr.Text))
            {
                textBoxLqiReqTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxLqiReqTargetAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxLqiReqStartIndex_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxLqiReqStartIndex.Text))
            {
                textBoxLqiReqStartIndex.ForeColor = System.Drawing.Color.Gray;
                textBoxLqiReqStartIndex.Text = "Start Idx (8-bit Hex)";
            }
        }

        #endregion

        #endregion

        #region GeneralTab

        #region Read Attribute

        private void textBoxReadAttribTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadAttribTargetAddr.Text))
            {
                textBoxReadAttribTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxReadAttribTargetAddr.Text = "Target (16-bit Hex)";
            }
        }

        private void textBoxReadAttribSrcEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadAttribSrcEP.Text))
            {
                textBoxReadAttribSrcEP.ForeColor = System.Drawing.Color.Gray;
                textBoxReadAttribSrcEP.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxReadAttribDstEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadAttribDstEP.Text))
            {
                textBoxReadAttribDstEP.ForeColor = System.Drawing.Color.Gray;
                textBoxReadAttribDstEP.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxReadAttribClusterID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadAttribClusterID.Text))
            {
                textBoxReadAttribClusterID.ForeColor = System.Drawing.Color.Gray;
                textBoxReadAttribClusterID.Text = "Cluster (16-bit Hex)";
            }
        }

        private void textBoxReadAttribCount_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadAttribCount.Text))
            {
                textBoxReadAttribCount.ForeColor = System.Drawing.Color.Gray;
                textBoxReadAttribCount.Text = "Attrib Count";
            }
        }

        private void textBoxReadAttribID1_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadAttribID1.Text))
            {
                textBoxReadAttribID1.ForeColor = System.Drawing.Color.Gray;
                textBoxReadAttribID1.Text = "Attrib (16-bit Hex)";
            }
        }

        private void textBoxReadAttribManuID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadAttribManuID.Text))
            {
                textBoxReadAttribManuID.ForeColor = System.Drawing.Color.Gray;
                textBoxReadAttribManuID.Text = "Manu ID (16-bit Hex)";
            }
        }

        #endregion

        #region Write Attribute

        private void textBoxWriteAttribTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxWriteAttribTargetAddr.Text))
            {
                textBoxWriteAttribTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxWriteAttribTargetAddr.Text = "Target (16-bit Hex)";
            }
        }

        private void textBoxWriteAttribSrcEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxWriteAttribSrcEP.Text))
            {
                textBoxWriteAttribSrcEP.ForeColor = System.Drawing.Color.Gray;
                textBoxWriteAttribSrcEP.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxWriteAttribDstEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxWriteAttribDstEP.Text))
            {
                textBoxWriteAttribDstEP.ForeColor = System.Drawing.Color.Gray;
                textBoxWriteAttribDstEP.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxWriteAttribClusterID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxWriteAttribClusterID.Text))
            {
                textBoxWriteAttribClusterID.ForeColor = System.Drawing.Color.Gray;
                textBoxWriteAttribClusterID.Text = "Cluster (16-bit Hex)";
            }
        }

        private void textBoxWriteAttribID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxWriteAttribID.Text))
            {
                textBoxWriteAttribID.ForeColor = System.Drawing.Color.Gray;
                textBoxWriteAttribID.Text = "Attrib (16-bit Hex)";
            }
        }

        private void textBoxWriteAttribDataType_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxWriteAttribDataType.Text))
            {
                textBoxWriteAttribDataType.ForeColor = System.Drawing.Color.Gray;
                textBoxWriteAttribDataType.Text = "Type (8-bit Hex)";
            }
        }

        private void textBoxWriteAttribData_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxWriteAttribData.Text))
            {
                textBoxWriteAttribData.ForeColor = System.Drawing.Color.Gray;
                textBoxWriteAttribData.Text = "Data)";
            }
        }

        private void textBoxWriteAttribManuID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxWriteAttribManuID.Text))
            {
                textBoxWriteAttribManuID.ForeColor = System.Drawing.Color.Gray;
                textBoxWriteAttribManuID.Text = "Manu ID (16-bit Hex)";
            }
        }

        #endregion

        #region Config Rprt

        private void textBoxConfigReportTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxConfigReportTargetAddr.Text))
            {
                textBoxConfigReportTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxConfigReportTargetAddr.Text = "Target (16-bit Hex)";
            }
        }

        private void textBoxConfigReportSrcEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxConfigReportSrcEP.Text))
            {
                textBoxConfigReportSrcEP.ForeColor = System.Drawing.Color.Gray;
                textBoxConfigReportSrcEP.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxConfigReportDstEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxConfigReportDstEP.Text))
            {
                textBoxConfigReportDstEP.ForeColor = System.Drawing.Color.Gray;
                textBoxConfigReportDstEP.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxConfigReportClusterID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxConfigReportClusterID.Text))
            {
                textBoxConfigReportClusterID.ForeColor = System.Drawing.Color.Gray;
                textBoxConfigReportClusterID.Text = "Cluster (16-bit Hex)";
            }
        }

        private void textBoxConfigReportAttribType_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxConfigReportAttribType.Text))
            {
                textBoxConfigReportAttribType.ForeColor = System.Drawing.Color.Gray;
                textBoxConfigReportAttribType.Text = "Attrib Type";
            }
        }

        private void textBoxConfigReportAttribID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxConfigReportAttribID.Text))
            {
                textBoxConfigReportAttribID.ForeColor = System.Drawing.Color.Gray;
                textBoxConfigReportAttribID.Text = "Attrib (16-bit Hex)";
            }
        }

        private void textBoxConfigReportMinInterval_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxConfigReportMinInterval.Text))
            {
                textBoxConfigReportMinInterval.ForeColor = System.Drawing.Color.Gray;
                textBoxConfigReportMinInterval.Text = "Min Intv (16-bit Hex)";
            }
        }

        private void textBoxConfigReportMaxInterval_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxConfigReportMaxInterval.Text))
            {
                textBoxConfigReportMaxInterval.ForeColor = System.Drawing.Color.Gray;
                textBoxConfigReportMaxInterval.Text = "Max Intv (16-bit Hex)";
            }
        }

        private void textBoxConfigReportTimeOut_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxConfigReportTimeOut.Text))
            {
                textBoxConfigReportTimeOut.ForeColor = System.Drawing.Color.Gray;
                textBoxConfigReportTimeOut.Text = "TimeOut (16-bit Hex)";
            }
        }

        private void textBoxConfigReportChange_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxConfigReportChange.Text))
            {
                textBoxConfigReportChange.ForeColor = System.Drawing.Color.Gray;
                textBoxConfigReportChange.Text = "Change (8-bit Hex)";
            }
        }

        #endregion

        #region Read Rprt

        private void textBoxReadReportConfigTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadReportConfigTargetAddr.Text))
            {
                textBoxReadReportConfigTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxReadReportConfigTargetAddr.Text = "Target (16-bit Hex)";
            }
        }

        private void textBoxReadReportConfigSrcEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadReportConfigSrcEP.Text))
            {
                textBoxReadReportConfigSrcEP.ForeColor = System.Drawing.Color.Gray;
                textBoxReadReportConfigSrcEP.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxReadReportConfigDstEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadReportConfigDstEP.Text))
            {
                textBoxReadReportConfigDstEP.ForeColor = System.Drawing.Color.Gray;
                textBoxReadReportConfigDstEP.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxReadReportConfigClusterID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadReportConfigClusterID.Text))
            {
                textBoxReadReportConfigClusterID.ForeColor = System.Drawing.Color.Gray;
                textBoxReadReportConfigClusterID.Text = "Cluster (16-bit Hex)";
            }
        }

        private void textBoxReadReportConfigAttribID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadReportConfigAttribID.Text))
            {
                textBoxReadReportConfigAttribID.ForeColor = System.Drawing.Color.Gray;
                textBoxReadReportConfigAttribID.Text = "Attrib (16-bit Hex)";
            }
        }

        #endregion

        #region Read All Attrib

        private void textBoxReadAllAttribAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadAllAttribAddr.Text))
            {
                textBoxReadAllAttribAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxReadAllAttribAddr.Text = "Target (16-bit Hex)";
            }
        }

        private void textBoxReadAllAttribSrcEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadAllAttribSrcEP.Text))
            {
                textBoxReadAllAttribSrcEP.ForeColor = System.Drawing.Color.Gray;
                textBoxReadAllAttribSrcEP.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxReadAllAttribDstEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadAllAttribDstEP.Text))
            {
                textBoxReadAllAttribDstEP.ForeColor = System.Drawing.Color.Gray;
                textBoxReadAllAttribDstEP.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxReadAllAttribClusterID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxReadAllAttribClusterID.Text))
            {
                textBoxReadAllAttribClusterID.ForeColor = System.Drawing.Color.Gray;
                textBoxReadAllAttribClusterID.Text = "Cluster (16-bit Hex)";
            }
        }

        #endregion

        #region Disc Attribs

        private void textBoxDiscoverAttributesAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDiscoverAttributesAddr.Text))
            {
                textBoxDiscoverAttributesAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxDiscoverAttributesAddr.Text = "Target (16-bit Hex)";
            }
        }

        private void textBoxDiscoverAttributesSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDiscoverAttributesSrcEp.Text))
            {
                textBoxDiscoverAttributesSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxDiscoverAttributesSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxDiscoverAttributesDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDiscoverAttributesDstEp.Text))
            {
                textBoxDiscoverAttributesDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxDiscoverAttributesDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxDiscoverAttributesClusterID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDiscoverAttributesClusterID.Text))
            {
                textBoxDiscoverAttributesClusterID.ForeColor = System.Drawing.Color.Gray;
                textBoxDiscoverAttributesClusterID.Text = "Cluster (!6-bit Hex)";
            }
        }

        private void textBoxDiscoverAttributesStartAttrId_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDiscoverAttributesStartAttrId.Text))
            {
                textBoxDiscoverAttributesStartAttrId.ForeColor = System.Drawing.Color.Gray;
                textBoxDiscoverAttributesStartAttrId.Text = "Attrib (16-bit Hex)";
            }
        }

        private void textBoxDiscoverAttributesMaxIDs_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDiscoverAttributesMaxIDs.Text))
            {
                textBoxDiscoverAttributesMaxIDs.ForeColor = System.Drawing.Color.Gray;
                textBoxDiscoverAttributesMaxIDs.Text = "Max ID's (8-bit Hex)";
            }
        }

        #endregion

        #region MTO Rt Req

        private void textBoxManyToOneRouteRequesRadius_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxManyToOneRouteRequesRadius.Text))
            {
                textBoxManyToOneRouteRequesRadius.ForeColor = System.Drawing.Color.Gray;
                textBoxManyToOneRouteRequesRadius.Text = "Radius (8-bit Hex)";
            }
        }

        #endregion

        #region NWK Update

        private void textBoxMgmtNwkUpdateTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMgmtNwkUpdateTargetAddr.Text))
            {
                textBoxMgmtNwkUpdateTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxMgmtNwkUpdateTargetAddr.Text = "Target (16-bit Hex)";
            }
        }

        private void textBoxMgmtNwkUpdateChannelMask_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMgmtNwkUpdateChannelMask.Text))
            {
                textBoxMgmtNwkUpdateChannelMask.ForeColor = System.Drawing.Color.Gray;
                textBoxMgmtNwkUpdateChannelMask.Text = "ChanMask (32-bit Hex)";
            }
        }

        private void textBoxMgmtNwkUpdateScanDuration_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMgmtNwkUpdateScanDuration.Text))
            {
                textBoxMgmtNwkUpdateScanDuration.ForeColor = System.Drawing.Color.Gray;
                textBoxMgmtNwkUpdateScanDuration.Text = "Duration (8-bit Hex)";
            }
        }

        private void textBoxMgmtNwkUpdateScanCount_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMgmtNwkUpdateScanCount.Text))
            {
                textBoxMgmtNwkUpdateScanCount.ForeColor = System.Drawing.Color.Gray;
                textBoxMgmtNwkUpdateScanCount.Text = "Count (8-bit Hex)";
            }
        }

        private void textBoxMgmtNwkUpdateNwkManagerAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMgmtNwkUpdateNwkManagerAddr.Text))
            {
                textBoxMgmtNwkUpdateNwkManagerAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxMgmtNwkUpdateNwkManagerAddr.Text = "NwkMan Addr (16-bit Hex)";
            }
        }

        #endregion

        #region Disc Cmds

        private void textBoxDiscoverCommandsTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDiscoverCommandsTargetAddr.Text))
            {
                textBoxDiscoverCommandsTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxDiscoverCommandsTargetAddr.Text = "Target (16-bit Hex)";
            }
        }

        private void textBoxDiscoverCommandsSrcEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDiscoverCommandsSrcEP.Text))
            {
                textBoxDiscoverCommandsSrcEP.ForeColor = System.Drawing.Color.Gray;
                textBoxDiscoverCommandsSrcEP.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxDiscoverCommandsDstEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDiscoverCommandsDstEP.Text))
            {
                textBoxDiscoverCommandsDstEP.ForeColor = System.Drawing.Color.Gray;
                textBoxDiscoverCommandsDstEP.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxDiscoverCommandsClusterID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDiscoverCommandsClusterID.Text))
            {
                textBoxDiscoverCommandsClusterID.ForeColor = System.Drawing.Color.Gray;
                textBoxDiscoverCommandsClusterID.Text = "Cluster (16-bit Hex)";
            }
        }

        private void textBoxDiscoverCommandsCommandID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDiscoverCommandsCommandID.Text))
            {
                textBoxDiscoverCommandsCommandID.ForeColor = System.Drawing.Color.Gray;
                textBoxDiscoverCommandsCommandID.Text = "Cmd ID (8-bit Hex)";
            }
        }

        private void textBoxDiscoverCommandsManuID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDiscoverCommandsManuID.Text))
            {
                textBoxDiscoverCommandsManuID.ForeColor = System.Drawing.Color.Gray;
                textBoxDiscoverCommandsManuID.Text = "Manu ID (16-bit Hex)";
            }
        }

        private void textBoxDiscoverCommandsMaxCommands_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDiscoverCommandsMaxCommands.Text))
            {
                textBoxDiscoverCommandsMaxCommands.ForeColor = System.Drawing.Color.Gray;
                textBoxDiscoverCommandsMaxCommands.Text = "Max Cmds (8-bit Hex)";
            }
        }

        #endregion

        #region Raw Data

        private void textBoxRawDataCommandsTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRawDataCommandsTargetAddr.Text))
            {
                textBoxRawDataCommandsTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxRawDataCommandsTargetAddr.Text = "Target (16-bit Hex)";
            }
        }

        private void textBoxRawDataCommandsSrcEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRawDataCommandsSrcEP.Text))
            {
                textBoxRawDataCommandsSrcEP.ForeColor = System.Drawing.Color.Gray;
                textBoxRawDataCommandsSrcEP.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxRawDataCommandsDstEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRawDataCommandsDstEP.Text))
            {
                textBoxRawDataCommandsDstEP.ForeColor = System.Drawing.Color.Gray;
                textBoxRawDataCommandsDstEP.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxRawDataCommandsProfileID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRawDataCommandsProfileID.Text))
            {
                textBoxRawDataCommandsProfileID.ForeColor = System.Drawing.Color.Gray;
                textBoxRawDataCommandsProfileID.Text = "Profile (16-bit Hex)";
            }
        }

        private void textBoxRawDataCommandsClusterID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRawDataCommandsClusterID.Text))
            {
                textBoxRawDataCommandsClusterID.ForeColor = System.Drawing.Color.Gray;
                textBoxRawDataCommandsClusterID.Text = "Cluster (16-bit Hex)";
            }
        }

        private void textBoxRawDataCommandsRadius_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRawDataCommandsRadius.Text))
            {
                textBoxRawDataCommandsRadius.ForeColor = System.Drawing.Color.Gray;
                textBoxRawDataCommandsRadius.Text = "Radius (8-bit Hex)";
            }
        }

        private void textBoxRawDataCommandsSecurityMode_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRawDataCommandsSecurityMode.Text))
            {
                textBoxRawDataCommandsSecurityMode.ForeColor = System.Drawing.Color.Gray;
                textBoxRawDataCommandsSecurityMode.Text = "Security Mode (8-bit Hex)";
            }
        }

        private void textBoxRawDataCommandsData_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRawDataCommandsData.Text))
            {
                textBoxRawDataCommandsData.ForeColor = System.Drawing.Color.Gray;
                textBoxRawDataCommandsData.Text = "Raw Data (Format: Byte:Byte:Byte)";
            }
        }

        #endregion

        #region OOB Commissioning Data

        private void textBoxOOBDataAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOOBDataAddr.Text))
            {
                textBoxOOBDataAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxOOBDataAddr.Text = "Address (64-bit Hex)";
            }
        }

        private void textBoxOOBDataKey_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOOBDataKey.Text))
            {
                textBoxOOBDataKey.ForeColor = System.Drawing.Color.Gray;
                textBoxOOBDataKey.Text = "Key (Format: Byte:Byte:Byte)";
            }
        }

        #endregion

        #endregion

        #region AHIControlTab

        #region DIO Set Dir

        private void textBoxDioSetDirectionInputPinMask_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDioSetDirectionInputPinMask.Text))
            {
                textBoxDioSetDirectionInputPinMask.ForeColor = System.Drawing.Color.Gray;
                textBoxDioSetDirectionInputPinMask.Text = "DIO Mask (32-bit Hex)";
            }
        }

        private void textBoxDioSetDirectionOutputPinMask_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDioSetDirectionOutputPinMask.Text))
            {
                textBoxDioSetDirectionOutputPinMask.ForeColor = System.Drawing.Color.Gray;
                textBoxDioSetDirectionOutputPinMask.Text = "DIO Mask (32-bit Hex)";
            }
        }

        #endregion

        #region DIO Set

        private void textBoxDioSetOutputOnPinMask_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDioSetOutputOnPinMask.Text))
            {
                textBoxDioSetOutputOnPinMask.ForeColor = System.Drawing.Color.Gray;
                textBoxDioSetOutputOnPinMask.Text = "DIO Mask (32-bit Hex)";
            }
        }

        private void textBoxDioSetOutputOffPinMask_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxDioSetOutputOffPinMask.Text))
            {
                textBoxDioSetOutputOffPinMask.ForeColor = System.Drawing.Color.Gray;
                textBoxDioSetOutputOffPinMask.Text = "DIO Mask (32-bit Hex)";
            }
        }

        #endregion

        #region IPN Config

        private void textBoxIPNConfigDioRfActiveOutDioMask_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxIPNConfigDioRfActiveOutDioMask.Text))
            {
                textBoxIPNConfigDioRfActiveOutDioMask.ForeColor = System.Drawing.Color.Gray;
                textBoxIPNConfigDioRfActiveOutDioMask.Text = "DIO Mask (32-bit Hex)";
            }
        }

        private void textBoxIPNConfigDioStatusOutDioMask_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxIPNConfigDioStatusOutDioMask.Text))
            {
                textBoxIPNConfigDioStatusOutDioMask.ForeColor = System.Drawing.Color.Gray;
                textBoxIPNConfigDioStatusOutDioMask.Text = "DIO Mask (32-bit Hex)";
            }
        }

        private void textBoxIPNConfigDioTxConfInDioMask_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxIPNConfigDioTxConfInDioMask.Text))
            {
                textBoxIPNConfigDioTxConfInDioMask.ForeColor = System.Drawing.Color.Gray;
                textBoxIPNConfigDioTxConfInDioMask.Text = "DIO Mask (32-bit Hex)";
            }
        }

        private void textBoxIPNConfigPollPeriod_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxIPNConfigPollPeriod.Text))
            {
                textBoxIPNConfigPollPeriod.ForeColor = System.Drawing.Color.Gray;
                textBoxIPNConfigPollPeriod.Text = "Time (16-bit Hex)";
            }
        }

        #endregion

        #region TxPower

        private void textBoxAHITxPower_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAHITxPower.Text))
            {
                txPowerTextBoxInit(ref textBoxAHITxPower);
            }
        }

        #endregion

        #endregion

        #region BasicClusterTab

        #region Reset To FD

        private void textBoxBasicResetTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxBasicResetTargetAddr.Text))
            {
                textBoxBasicResetTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxBasicResetTargetAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxBasicResetSrcEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxBasicResetSrcEP.Text))
            {
                textBoxBasicResetSrcEP.ForeColor = System.Drawing.Color.Gray;
                textBoxBasicResetSrcEP.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxBasicResetDstEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxBasicResetDstEP.Text))
            {
                textBoxBasicResetDstEP.ForeColor = System.Drawing.Color.Gray;
                textBoxBasicResetDstEP.Text = "Dst EP (8-bit Hex)";
            }
        }

        #endregion

        #endregion

        #region GroupClusterTab

        #region Add Group

        private void textBoxAddGroupAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddGroupAddr.Text))
            {
                textBoxAddGroupAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxAddGroupAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxAddGroupSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddGroupSrcEp.Text))
            {
                textBoxAddGroupSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxAddGroupSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxAddGroupDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddGroupDstEp.Text))
            {
                textBoxAddGroupDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxAddGroupDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxAddGroupGroupAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddGroupGroupAddr.Text))
            {
                textBoxAddGroupGroupAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxAddGroupGroupAddr.Text = "Group ID (16-bit Hex)";
            }
        }

        private void textBoxGroupNameLength_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGroupNameLength.Text))
            {
                textBoxGroupNameLength.ForeColor = System.Drawing.Color.Gray;
                textBoxGroupNameLength.Text = "Name Len (8-bit Hex)";
            }
        }

        private void textBoxGroupNameMaxLength_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGroupNameMaxLength.Text))
            {
                textBoxGroupNameMaxLength.ForeColor = System.Drawing.Color.Gray;
                textBoxGroupNameMaxLength.Text = "Max Len (8-bit Hex)";
            }
        }

        private void textBoxGroupName_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGroupName.Text))
            {
                textBoxGroupName.ForeColor = System.Drawing.Color.Gray;
                textBoxGroupName.Text = "Group Name (String)";
            }
        }

        #endregion

        #region View Group

        private void textBoxViewGroupAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxViewGroupAddr.Text))
            {
                textBoxViewGroupAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxViewGroupAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxViewGroupSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxViewGroupSrcEp.Text))
            {
                textBoxViewGroupSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxViewGroupSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxViewGroupDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxViewGroupDstEp.Text))
            {
                textBoxViewGroupDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxViewGroupDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxViewGroupGroupAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxViewGroupGroupAddr.Text))
            {
                textBoxViewGroupGroupAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxViewGroupGroupAddr.Text = "Group ID (16-bit Hex)";
            }
        }

        #endregion

        #region Get Group

        private void textBoxGetGroupTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGetGroupTargetAddr.Text))
            {
                textBoxGetGroupTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxGetGroupTargetAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxGetGroupSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGetGroupSrcEp.Text))
            {
                textBoxGetGroupSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxGetGroupSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxGetGroupDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGetGroupDstEp.Text))
            {
                textBoxGetGroupDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxGetGroupDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxGetGroupCount_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGetGroupCount.Text))
            {
                textBoxGetGroupCount.ForeColor = System.Drawing.Color.Gray;
                textBoxGetGroupCount.Text = "Group ID (16-bit Hex)";
            }
        }

        #endregion

        #region Remove Grp

        private void textBoxRemoveGroupTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveGroupTargetAddr.Text))
            {
                textBoxRemoveGroupTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveGroupTargetAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxRemoveGroupSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveGroupSrcEp.Text))
            {
                textBoxRemoveGroupSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveGroupSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxRemoveGroupDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveGroupDstEp.Text))
            {
                textBoxRemoveGroupDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveGroupDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxRemoveGroupGroupAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveGroupGroupAddr.Text))
            {
                textBoxRemoveGroupGroupAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveGroupGroupAddr.Text = "Group ID (16-bit Hex)";
            }
        }

        #endregion

        #region Remove All

        private void textBoxRemoveAllGroupTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveAllGroupTargetAddr.Text))
            {
                textBoxRemoveAllGroupTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveAllGroupTargetAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxRemoveAllGroupSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveAllGroupSrcEp.Text))
            {
                textBoxRemoveAllGroupSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveAllGroupSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxRemoveAllGroupDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveAllGroupDstEp.Text))
            {
                textBoxRemoveAllGroupDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveAllGroupDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        #endregion

        #region Add If Ident

        private void textBoxGroupAddIfIndentifyingTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGroupAddIfIndentifyingTargetAddr.Text))
            {
                textBoxGroupAddIfIndentifyingTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxGroupAddIfIndentifyingTargetAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxGroupAddIfIdentifySrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGroupAddIfIdentifySrcEp.Text))
            {
                textBoxGroupAddIfIdentifySrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxGroupAddIfIdentifySrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxGroupAddIfIdentifyDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGroupAddIfIdentifyDstEp.Text))
            {
                textBoxGroupAddIfIdentifyDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxGroupAddIfIdentifyDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxGroupAddIfIdentifyGroupID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGroupAddIfIdentifyGroupID.Text))
            {
                textBoxGroupAddIfIdentifyGroupID.ForeColor = System.Drawing.Color.Gray;
                textBoxGroupAddIfIdentifyGroupID.Text = "Group ID (16-bit Hex)";
            }
        }

        #endregion

        #endregion

        #region IdentifyClusterTab

        #region ID Send

        private void textBoxSendIdAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxSendIdAddr.Text))
            {
                textBoxSendIdAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxSendIdAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxSendIdSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxSendIdSrcEp.Text))
            {
                textBoxSendIdSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxSendIdSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxIdSendDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxIdSendDstEp.Text))
            {
                textBoxIdSendDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxIdSendDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxIdSendTime_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxIdSendTime.Text))
            {
                textBoxIdSendTime.ForeColor = System.Drawing.Color.Gray;
                textBoxIdSendTime.Text = "Time (16-bit Hex)";
            }
        }

        #endregion

        #region ID Query

        private void textBoxIdQueryAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxIdQueryAddr.Text))
            {
                textBoxIdQueryAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxIdQueryAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxIdQuerySrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxIdQuerySrcEp.Text))
            {
                textBoxIdQuerySrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxIdQuerySrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxIdQueryDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxIdQueryDstEp.Text))
            {
                textBoxIdQueryDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxIdQueryDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        #endregion

        #endregion

        #region LevelClusterTab

        #region MoveToLevel

        private void textBoxMoveToLevelAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToLevelAddr.Text))
            {
                textBoxMoveToLevelAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToLevelAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxMoveToLevelSrcEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToLevelSrcEndPoint.Text))
            {
                textBoxMoveToLevelSrcEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToLevelSrcEndPoint.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxMoveToLevelDstEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToLevelDstEndPoint.Text))
            {
                textBoxMoveToLevelDstEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToLevelDstEndPoint.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxMoveToLevelLevel_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToLevelLevel.Text))
            {
                textBoxMoveToLevelLevel.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToLevelLevel.Text = "Level (8-bit Hex)";
            }
        }

        private void textBoxMoveToLevelTransTime_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToLevelTransTime.Text))
            {
                textBoxMoveToLevelTransTime.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToLevelTransTime.Text = "Time (16-bit Hex)";
            }
        }

        #endregion

        #endregion

        #region OnOffClusterTab

        #region OnOff

        private void textBoxOnOffAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOnOffAddr.Text))
            {
                textBoxOnOffAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxOnOffAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxOnOffSrcEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOnOffSrcEndPoint.Text))
            {
                textBoxOnOffSrcEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxOnOffSrcEndPoint.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxOnOffDstEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOnOffDstEndPoint.Text))
            {
                textBoxOnOffDstEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxOnOffDstEndPoint.Text = "Dst EP (8-bit Hex)";
            }
        }

        #endregion

        #endregion

        #region ScenesClusterTab

        #region View Scene

        private void textBoxViewSceneAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxViewSceneAddr.Text))
            {
                textBoxViewSceneAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxViewSceneAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxViewSceneSrcEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxViewSceneSrcEndPoint.Text))
            {
                textBoxViewSceneSrcEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxViewSceneSrcEndPoint.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxViewSceneDstEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxViewSceneDstEndPoint.Text))
            {
                textBoxViewSceneDstEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxViewSceneDstEndPoint.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxViewSceneGroupId_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxViewSceneGroupId.Text))
            {
                textBoxViewSceneGroupId.ForeColor = System.Drawing.Color.Gray;
                textBoxViewSceneGroupId.Text = "Group ID (16-bit Hex)";
            }
        }

        private void textBoxViewSceneSceneId_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxViewSceneSceneId.Text))
            {
                textBoxViewSceneSceneId.ForeColor = System.Drawing.Color.Gray;
                textBoxViewSceneSceneId.Text = "Scene ID (8-bit Hex)";
            }
        }

        #endregion

        #region Add Scene

        private void textBoxAddSceneAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddSceneAddr.Text))
            {
                textBoxAddSceneAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxAddSceneAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxAddSceneSrcEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddSceneSrcEndPoint.Text))
            {
                textBoxAddSceneSrcEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxAddSceneSrcEndPoint.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxAddSceneDstEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddSceneDstEndPoint.Text))
            {
                textBoxAddSceneDstEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxAddSceneDstEndPoint.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxAddSceneGroupId_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddSceneGroupId.Text))
            {
                textBoxAddSceneGroupId.ForeColor = System.Drawing.Color.Gray;
                textBoxAddSceneGroupId.Text = "Group ID (16-bit Hex)";
            }
        }

        private void textBoxAddSceneSceneId_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddSceneSceneId.Text))
            {
                textBoxAddSceneSceneId.ForeColor = System.Drawing.Color.Gray;
                textBoxAddSceneSceneId.Text = "Scene ID (8-bit Hex)";
            }
        }

        private void textBoxAddSceneTransTime_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddSceneTransTime.Text))
            {
                textBoxAddSceneTransTime.ForeColor = System.Drawing.Color.Gray;
                textBoxAddSceneTransTime.Text = "Time (16-bit Hex)";
            }
        }

        private void textBoxAddSceneName_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddSceneName.Text))
            {
                textBoxAddSceneName.ForeColor = System.Drawing.Color.Gray;
                textBoxAddSceneName.Text = "Name (String)";
            }
        }

        private void textBoxAddSceneNameLen_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddSceneNameLen.Text))
            {
                textBoxAddSceneNameLen.ForeColor = System.Drawing.Color.Gray;
                textBoxAddSceneNameLen.Text = "Len (8-bit Hex)";
            }
        }

        private void textBoxAddSceneMaxNameLen_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddSceneMaxNameLen.Text))
            {
                textBoxAddSceneMaxNameLen.ForeColor = System.Drawing.Color.Gray;
                textBoxAddSceneMaxNameLen.Text = "Max Len (8-bit Hex)";
            }
        }

        private void textBoxAddSceneExtLen_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddSceneExtLen.Text))
            {
                textBoxAddSceneExtLen.ForeColor = System.Drawing.Color.Gray;
                textBoxAddSceneExtLen.Text = "Ext Len (16-bit Hex)";
            }
        }

        private void textBoxAddSceneData_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxAddSceneData.Text))
            {
                textBoxAddSceneData.ForeColor = System.Drawing.Color.Gray;
                textBoxAddSceneData.Text = "Data (Format: Byte:Byte:Byte)";
            }
        }

        #endregion

        #region Store Scene

        private void textBoxStoreSceneAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxStoreSceneAddr.Text))
            {
                textBoxStoreSceneAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxStoreSceneAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxStoreSceneSrcEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxStoreSceneSrcEndPoint.Text))
            {
                textBoxStoreSceneSrcEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxStoreSceneSrcEndPoint.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxStoreSceneDstEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxStoreSceneDstEndPoint.Text))
            {
                textBoxStoreSceneDstEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxStoreSceneDstEndPoint.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxStoreSceneGroupId_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxStoreSceneGroupId.Text))
            {
                textBoxStoreSceneGroupId.ForeColor = System.Drawing.Color.Gray;
                textBoxStoreSceneGroupId.Text = "Group ID (16-bit Hex)";
            }
        }

        private void textBoxStoreSceneSceneId_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxStoreSceneSceneId.Text))
            {
                textBoxStoreSceneSceneId.ForeColor = System.Drawing.Color.Gray;
                textBoxStoreSceneSceneId.Text = "Scene ID (8-bit Hex)";
            }
        }

        #endregion

        #region Recall Scene

        private void textBoxRecallSceneAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRecallSceneAddr.Text))
            {
                textBoxRecallSceneAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxRecallSceneAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxRecallSceneSrcEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRecallSceneSrcEndPoint.Text))
            {
                textBoxRecallSceneSrcEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxRecallSceneSrcEndPoint.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxRecallSceneDstEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRecallSceneDstEndPoint.Text))
            {
                textBoxRecallSceneDstEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxRecallSceneDstEndPoint.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxRecallSceneGroupId_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRecallSceneGroupId.Text))
            {
                textBoxRecallSceneGroupId.ForeColor = System.Drawing.Color.Gray;
                textBoxRecallSceneGroupId.Text = "Group ID (16-bit Hex)";
            }
        }

        private void textBoxRecallSceneSceneId_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRecallSceneSceneId.Text))
            {
                textBoxRecallSceneSceneId.ForeColor = System.Drawing.Color.Gray;
                textBoxRecallSceneSceneId.Text = "Scene ID (8-bit Hex)";
            }
        }

        #endregion

        #region Get Member

        private void textBoxGetSceneMembershipAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGetSceneMembershipAddr.Text))
            {
                textBoxGetSceneMembershipAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxGetSceneMembershipAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxGetSceneMembershipSrcEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGetSceneMembershipSrcEndPoint.Text))
            {
                textBoxGetSceneMembershipSrcEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxGetSceneMembershipSrcEndPoint.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxGetSceneMembershipDstEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGetSceneMembershipDstEndPoint.Text))
            {
                textBoxGetSceneMembershipDstEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxGetSceneMembershipDstEndPoint.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxGetSceneMembershipGroupID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxGetSceneMembershipGroupID.Text))
            {
                textBoxGetSceneMembershipGroupID.ForeColor = System.Drawing.Color.Gray;
                textBoxGetSceneMembershipGroupID.Text = "Group ID (16-bit Hex)";
            }
        }

        #endregion

        #region Remove All

        private void textBoxRemoveAllScenesAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveAllScenesAddr.Text))
            {
                textBoxRemoveAllScenesAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveAllScenesAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxRemoveAllScenesSrcEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveAllScenesSrcEndPoint.Text))
            {
                textBoxRemoveAllScenesSrcEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveAllScenesSrcEndPoint.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxRemoveAllScenesDstEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveAllScenesDstEndPoint.Text))
            {
                textBoxRemoveAllScenesDstEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveAllScenesDstEndPoint.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxRemoveAllScenesGroupID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveAllScenesGroupID.Text))
            {
                textBoxRemoveAllScenesGroupID.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveAllScenesGroupID.Text = "Group ID (16-bit Hex)";
            }
        }

        #endregion

        #region Remove

        private void textBoxRemoveSceneAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveSceneAddr.Text))
            {
                textBoxRemoveSceneAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveSceneAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxRemoveSceneSrcEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveSceneSrcEndPoint.Text))
            {
                textBoxRemoveSceneSrcEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveSceneSrcEndPoint.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxRemoveSceneDstEndPoint_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveSceneDstEndPoint.Text))
            {
                textBoxRemoveSceneDstEndPoint.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveSceneDstEndPoint.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxRemoveSceneGroupID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveSceneGroupID.Text))
            {
                textBoxRemoveSceneGroupID.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveSceneGroupID.Text = "Group ID (16-bit Hex)";
            }
        }

        private void textBoxRemoveSceneSceneID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxRemoveSceneSceneID.Text))
            {
                textBoxRemoveSceneSceneID.ForeColor = System.Drawing.Color.Gray;
                textBoxRemoveSceneSceneID.Text = "Scene ID (8-bit Hex)";
            }
        }

        #endregion

        #endregion

        #region ColorClusterTab

        #region MoveToHue

        private void textBoxMoveToHueAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToHueAddr.Text))
            {
                textBoxMoveToHueAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToHueAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxMoveToHueSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToHueSrcEp.Text))
            {
                textBoxMoveToHueSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToHueSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxMoveToHueDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToHueDstEp.Text))
            {
                textBoxMoveToHueDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToHueDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxMoveToHueHue_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToHueHue.Text))
            {
                textBoxMoveToHueHue.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToHueHue.Text = "Hue (8-bit Hex)";
            }
        }

        private void textBoxMoveToHueDir_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToHueDir.Text))
            {
                textBoxMoveToHueDir.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToHueDir.Text = "Dir (8-bit Hex)";
            }
        }

        private void textBoxMoveToHueTime_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToHueTime.Text))
            {
                textBoxMoveToHueTime.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToHueTime.Text = "Time (16-bit Hex)";
            }
        }

        #endregion

        #region MoveToColor

        private void textBoxMoveToColorAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToColorAddr.Text))
            {
                textBoxMoveToColorAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToColorAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxMoveToColorSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToColorSrcEp.Text))
            {
                textBoxMoveToColorSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToColorSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxMoveToColorDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToColorDstEp.Text))
            {
                textBoxMoveToColorDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToColorDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxMoveToColorX_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToColorX.Text))
            {
                textBoxMoveToColorX.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToColorX.Text = "X (16-bit Hex)";
            }
        }

        private void textBoxMoveToColorY_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToColorY.Text))
            {
                textBoxMoveToColorY.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToColorY.Text = "Y (16-bit Hex)";
            }
        }

        private void textBoxMoveToColorTime_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToColorTime.Text))
            {
                textBoxMoveToColorTime.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToColorTime.Text = "Time (16-bit Hex)";
            }
        }

        #endregion

        #region MoveToSat

        private void textBoxMoveToSatAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToSatAddr.Text))
            {
                textBoxMoveToSatAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToSatAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxMoveToSatSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToSatSrcEp.Text))
            {
                textBoxMoveToSatSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToSatSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxMoveToSatDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToSatDstEp.Text))
            {
                textBoxMoveToSatDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToSatDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxMoveToSatSat_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToSatSat.Text))
            {
                textBoxMoveToSatSat.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToSatSat.Text = "Saturation (8-bit Hex)";
            }
        }

        private void textBoxMoveToSatTime_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToSatTime.Text))
            {
                textBoxMoveToSatTime.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToSatTime.Text = "Time (16-bit Hex)";
            }
        }

        #endregion

        #region MoveToTemp

        private void textBoxMoveToColorTempAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToColorTempAddr.Text))
            {
                textBoxMoveToColorTempAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToColorTempAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxMoveToColorTempSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToColorTempSrcEp.Text))
            {
                textBoxMoveToColorTempSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToColorTempSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxMoveToColorTempDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToColorTempDstEp.Text))
            {
                textBoxMoveToColorTempDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToColorTempDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxMoveToColorTempTemp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToColorTempTemp.Text))
            {
                textBoxMoveToColorTempTemp.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToColorTempTemp.Text = "TempK (16-bit Dec)";
            }
        }

        private void textBoxMoveToColorTempRate_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxMoveToColorTempRate.Text))
            {
                textBoxMoveToColorTempRate.ForeColor = System.Drawing.Color.Gray;
                textBoxMoveToColorTempRate.Text = "Time (16-bit Hex)";
            }
        }

        #endregion

        #endregion

        #region DoorLockClusterTab

        #region LockUnlock

        private void textBoxLockUnlockAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxLockUnlockAddr.Text))
            {
                textBoxLockUnlockAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxLockUnlockAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxLockUnlockSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxLockUnlockSrcEp.Text))
            {
                textBoxLockUnlockSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxLockUnlockSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxLockUnlockDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxLockUnlockDstEp.Text))
            {
                textBoxLockUnlockDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxLockUnlockDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        #endregion

        #endregion

        #region IASClusterTab

        #region EnrollRsp

        private void textBoxEnrollRspAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxEnrollRspAddr.Text))
            {
                textBoxEnrollRspAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxEnrollRspAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxEnrollRspSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxEnrollRspSrcEp.Text))
            {
                textBoxEnrollRspSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxEnrollRspSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxEnrollRspDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxEnrollRspDstEp.Text))
            {
                textBoxEnrollRspDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxEnrollRspDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxEnrollRspZone_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxEnrollRspZone.Text))
            {
                textBoxEnrollRspZone.ForeColor = System.Drawing.Color.Gray;
                textBoxEnrollRspZone.Text = "Zone ID (8-bit Hex)";
            }
        }

        #endregion

        #endregion

        #region ZLLOnOffClusterTab

        #region OnOff Effects

        private void textBoxZllOnOffEffectsAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxZllOnOffEffectsAddr.Text))
            {
                textBoxZllOnOffEffectsAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxZllOnOffEffectsAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxZllOnOffEffectsSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxZllOnOffEffectsSrcEp.Text))
            {
                textBoxZllOnOffEffectsSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxZllOnOffEffectsSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxZllOnOffEffectsDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxZllOnOffEffectsDstEp.Text))
            {
                textBoxZllOnOffEffectsDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxZllOnOffEffectsDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxZllOnOffEffectsGradient_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxZllOnOffEffectsGradient.Text))
            {
                textBoxZllOnOffEffectsGradient.ForeColor = System.Drawing.Color.Gray;
                textBoxZllOnOffEffectsGradient.Text = "Gradient (8-bit Hex)";
            }
        }

        #endregion

        #endregion

        #region ZLLColorClusterTab

        #region Move To Hue

        private void textBoxZllMoveToHueAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxZllMoveToHueAddr.Text))
            {
                textBoxZllMoveToHueAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxZllMoveToHueAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxZllMoveToHueSrcEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxZllMoveToHueSrcEp.Text))
            {
                textBoxZllMoveToHueSrcEp.ForeColor = System.Drawing.Color.Gray;
                textBoxZllMoveToHueSrcEp.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxZllMoveToHueDstEp_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxZllMoveToHueDstEp.Text))
            {
                textBoxZllMoveToHueDstEp.ForeColor = System.Drawing.Color.Gray;
                textBoxZllMoveToHueDstEp.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxZllMoveToHueHue_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxZllMoveToHueHue.Text))
            {
                textBoxZllMoveToHueHue.ForeColor = System.Drawing.Color.Gray;
                textBoxZllMoveToHueHue.Text = "Hue (16-bit Hex)";
            }
        }

        private void textBoxZllMoveToHueDirection_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxZllMoveToHueDirection.Text))
            {
                textBoxZllMoveToHueDirection.ForeColor = System.Drawing.Color.Gray;
                textBoxZllMoveToHueDirection.Text = "Dir (8-bit Hex)";
            }
        }

        private void textBoxZllMoveToHueTransTime_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxZllMoveToHueTransTime.Text))
            {
                textBoxZllMoveToHueTransTime.ForeColor = System.Drawing.Color.Gray;
                textBoxZllMoveToHueTransTime.Text = "Time (16-bit Hex)";
            }
        }

        #endregion

        #endregion

        #region OTAClusterTab

        #region Image Notify

        private void textBoxOTAImageNotifyTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOTAImageNotifyTargetAddr.Text))
            {
                textBoxOTAImageNotifyTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxOTAImageNotifyTargetAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxOTAImageNotifySrcEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOTAImageNotifySrcEP.Text))
            {
                textBoxOTAImageNotifySrcEP.ForeColor = System.Drawing.Color.Gray;
                textBoxOTAImageNotifySrcEP.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxOTAImageNotifyDstEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOTAImageNotifyDstEP.Text))
            {
                textBoxOTAImageNotifyDstEP.ForeColor = System.Drawing.Color.Gray;
                textBoxOTAImageNotifyDstEP.Text = "Dst EP (8-bit Hex)";
            }
        }

        private void textBoxOTAImageNotifyFileVersion_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOTAImageNotifyFileVersion.Text))
            {
                textBoxOTAImageNotifyFileVersion.ForeColor = System.Drawing.Color.Gray;
                textBoxOTAImageNotifyFileVersion.Text = "Version (32-bit Hex)";
            }
        }

        private void textBoxOTAImageNotifyImageType_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOTAImageNotifyImageType.Text))
            {
                textBoxOTAImageNotifyImageType.ForeColor = System.Drawing.Color.Gray;
                textBoxOTAImageNotifyImageType.Text = "Image Type (16-bit Hex)";
            }
        }

        private void textBoxOTAImageNotifyManuID_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOTAImageNotifyManuID.Text))
            {
                textBoxOTAImageNotifyManuID.ForeColor = System.Drawing.Color.Gray;
                textBoxOTAImageNotifyManuID.Text = "Manu ID (16-bit Hex)";
            }
        }

        private void textBoxOTAImageNotifyJitter_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOTAImageNotifyJitter.Text))
            {
                textBoxOTAImageNotifyJitter.ForeColor = System.Drawing.Color.Gray;
                textBoxOTAImageNotifyJitter.Text = "Query Jitter (8-bit Hex)";
            }
        }

        #endregion

        #region WaitParams

        private void textBoxOTASetWaitForDataParamsTargetAddr_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOTASetWaitForDataParamsTargetAddr.Text))
            {
                textBoxOTASetWaitForDataParamsTargetAddr.ForeColor = System.Drawing.Color.Gray;
                textBoxOTASetWaitForDataParamsTargetAddr.Text = "Address (16-bit Hex)";
            }
        }

        private void textBoxOTASetWaitForDataParamsSrcEP_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOTASetWaitForDataParamsSrcEP.Text))
            {
                textBoxOTASetWaitForDataParamsSrcEP.ForeColor = System.Drawing.Color.Gray;
                textBoxOTASetWaitForDataParamsSrcEP.Text = "Src EP (8-bit Hex)";
            }
        }

        private void textBoxOTASetWaitForDataParamsCurrentTime_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOTASetWaitForDataParamsCurrentTime.Text))
            {
                textBoxOTASetWaitForDataParamsCurrentTime.ForeColor = System.Drawing.Color.Gray;
                textBoxOTASetWaitForDataParamsCurrentTime.Text = "Current Time (32-bit Hex)";
            }
        }

        private void textBoxOTASetWaitForDataParamsRequestTime_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOTASetWaitForDataParamsRequestTime.Text))
            {
                textBoxOTASetWaitForDataParamsRequestTime.ForeColor = System.Drawing.Color.Gray;
                textBoxOTASetWaitForDataParamsRequestTime.Text = "Request Time (32-bit Hex)";
            }
        }

        private void textBoxOTASetWaitForDataParamsRequestBlockDelay_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxOTASetWaitForDataParamsRequestBlockDelay.Text))
            {
                textBoxOTASetWaitForDataParamsRequestBlockDelay.ForeColor = System.Drawing.Color.Gray;
                textBoxOTASetWaitForDataParamsRequestBlockDelay.Text = "Block Delay (16-bit Hex)";
            }
        }

        #endregion

        #endregion

        #region PollControlTab

        #region Check-In Rsp

        private void textBoxFastPollExpiryTime_Leave(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(textBoxFastPollExpiryTime.Text))
            {
                textBoxFastPollExpiryTime.ForeColor = System.Drawing.Color.Gray;
                textBoxFastPollExpiryTime.Text = "Fast Poll Expiry (16-bit Hex)";
            }
        }

        #endregion


        #endregion

        #region PageClick

        private void tabPage2_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPage12_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void AHIControl_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void BasicClusterTab_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPage3_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPage5_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPage6_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPage4_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPage7_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPage8_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPage1_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPage13_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPage15_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPage9_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPage10_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPage11_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPage14_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        private void tabPagePollControl_Click(object sender, EventArgs e)
        {
            richTextBoxCommandResponse.Focus();
        }

        #endregion

        #endregion

        private void comboBoxAddressList_SelectedIndexChanged(object sender, EventArgs e)
        {
            textBoxExtAddr.Text = au64ExtAddr[comboBoxAddressList.SelectedIndex].ToString("X8");
        }

        private void checkBoxShowExtension_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxShowExtension.Checked == true)
            {
                textBoxAddSceneTransTime.Visible = true;
                textBoxAddSceneName.Visible = true;
                textBoxAddSceneNameLen.Visible = true;
                textBoxAddSceneMaxNameLen.Visible = true;
                textBoxAddSceneExtLen.Visible = true;
                textBoxAddSceneData.Visible = true;
            }
            else if (checkBoxShowExtension.Checked != true)
            {

                textBoxAddSceneTransTime.Visible = false;
                textBoxAddSceneName.Visible = false;
                textBoxAddSceneNameLen.Visible = false;
                textBoxAddSceneMaxNameLen.Visible = false;
                textBoxAddSceneExtLen.Visible = false;
                textBoxAddSceneData.Visible = false;
            }
        }

        private void PollInterval_Click(object sender, EventArgs e)
        {
            byte[] commandData = null;
            commandData = new byte[32];
            byte u8Len = 0;
            UInt32 u32PollInterval;
            if (bStringToUint32(textBoxPollInterval.Text, out u32PollInterval) == true)
            {
                commandData[u8Len++] = (byte)(u32PollInterval >> 24);
                commandData[u8Len++] = (byte)(u32PollInterval >> 16);
                commandData[u8Len++] = (byte)(u32PollInterval >> 8);
                commandData[u8Len++] = (byte)(u32PollInterval);
                // Transmit command
                transmitCommand(0x002D, u8Len, commandData);
            }
        }

        private void textBoxPollInterval_MouseHover(object sender, EventArgs e)
        {
            showToolTipWindow("Poll Interval to be used (32-bit Hex) milliseconds");
        }

        private void textBoxPollInterval_MouseLeave(object sender, EventArgs e)
        {
            hideToolTipWindow();
        }

        private void textBoxPollInterval_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxPollInterval.ForeColor != System.Drawing.Color.Black)
            {
                textBoxPollInterval.ForeColor = System.Drawing.Color.Black;
                textBoxPollInterval.Text = "";
            }
        }

        private void buttonNciCmd_Click(object sender, EventArgs e)
        {
            setNciCmd((byte)comboBoxNciCmd.SelectedIndex);
        }
    }
}