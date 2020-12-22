namespace ZGWUI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.settingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openPortToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusPort = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripPortSettings = new System.Windows.Forms.ToolStripStatusLabel();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.textBoxPollInterval = new System.Windows.Forms.TextBox();
            this.buttonPollInterval = new System.Windows.Forms.Button();
            this.buttonNWKState = new System.Windows.Forms.Button();
            this.buttonDiscoveryOnly = new System.Windows.Forms.Button();
            this.textBoxBindTargetExtAddr = new System.Windows.Forms.TextBox();
            this.textBoxUserSetReqDescription = new System.Windows.Forms.TextBox();
            this.textBoxUserSetReqAddr = new System.Windows.Forms.TextBox();
            this.buttonUserSetReq = new System.Windows.Forms.Button();
            this.textBoxUserReqAddr = new System.Windows.Forms.TextBox();
            this.buttonUserReq = new System.Windows.Forms.Button();
            this.textBoxRestoreNwkFrameCounter = new System.Windows.Forms.TextBox();
            this.comboBoxLeaveChildren = new System.Windows.Forms.ComboBox();
            this.comboBoxLeaveReJoin = new System.Windows.Forms.ComboBox();
            this.textBoxLeaveAddr = new System.Windows.Forms.TextBox();
            this.buttonLeave = new System.Windows.Forms.Button();
            this.textBoxRemoveChildAddr = new System.Windows.Forms.TextBox();
            this.textBoxRemoveParentAddr = new System.Windows.Forms.TextBox();
            this.buttonRemoveDevice = new System.Windows.Forms.Button();
            this.buttonPermitJoinState = new System.Windows.Forms.Button();
            this.buttonRestoreNwk = new System.Windows.Forms.Button();
            this.buttonRecoverNwk = new System.Windows.Forms.Button();
            this.comboBoxMgmtLeaveChildren = new System.Windows.Forms.ComboBox();
            this.comboBoxMgmtLeaveReJoin = new System.Windows.Forms.ComboBox();
            this.textBoxMgmtLeaveExtAddr = new System.Windows.Forms.TextBox();
            this.textBoxMgmtLeaveAddr = new System.Windows.Forms.TextBox();
            this.buttonMgmtLeave = new System.Windows.Forms.Button();
            this.textBoxUnBindDestEP = new System.Windows.Forms.TextBox();
            this.textBoxUnBindDestAddr = new System.Windows.Forms.TextBox();
            this.comboBoxUnBindAddrMode = new System.Windows.Forms.ComboBox();
            this.textBoxUnBindClusterID = new System.Windows.Forms.TextBox();
            this.textBoxUnBindTargetEP = new System.Windows.Forms.TextBox();
            this.textBoxUnBindTargetExtAddr = new System.Windows.Forms.TextBox();
            this.buttonUnBind = new System.Windows.Forms.Button();
            this.textBoxBindDestEP = new System.Windows.Forms.TextBox();
            this.textBoxBindDestAddr = new System.Windows.Forms.TextBox();
            this.comboBoxBindAddrMode = new System.Windows.Forms.ComboBox();
            this.textBoxBindClusterID = new System.Windows.Forms.TextBox();
            this.textBoxBindTargetEP = new System.Windows.Forms.TextBox();
            this.textBoxLqiReqStartIndex = new System.Windows.Forms.TextBox();
            this.textBoxLqiReqTargetAddr = new System.Windows.Forms.TextBox();
            this.buttonMgmtLqiReq = new System.Windows.Forms.Button();
            this.buttonStartScan = new System.Windows.Forms.Button();
            this.textBoxNwkAddrReqStartIndex = new System.Windows.Forms.TextBox();
            this.comboBoxNwkAddrReqType = new System.Windows.Forms.ComboBox();
            this.textBoxNwkAddrReqExtAddr = new System.Windows.Forms.TextBox();
            this.textBoxNwkAddrReqTargetAddr = new System.Windows.Forms.TextBox();
            this.textBoxIeeeReqStartIndex = new System.Windows.Forms.TextBox();
            this.comboBoxIeeeReqType = new System.Windows.Forms.ComboBox();
            this.textBoxIeeeReqAddr = new System.Windows.Forms.TextBox();
            this.textBoxIeeeReqTargetAddr = new System.Windows.Forms.TextBox();
            this.textBoxComplexReqAddr = new System.Windows.Forms.TextBox();
            this.buttonComplexReq = new System.Windows.Forms.Button();
            this.textBoxMatchReqOutputClusters = new System.Windows.Forms.TextBox();
            this.textBoxMatchReqInputClusters = new System.Windows.Forms.TextBox();
            this.textBoxMatchReqProfileID = new System.Windows.Forms.TextBox();
            this.textBoxMatchReqNbrOutputClusters = new System.Windows.Forms.TextBox();
            this.textBoxMatchReqNbrInputClusters = new System.Windows.Forms.TextBox();
            this.textBoxMatchReqAddr = new System.Windows.Forms.TextBox();
            this.textBoxActiveEpAddr = new System.Windows.Forms.TextBox();
            this.textBoxPowerReqAddr = new System.Windows.Forms.TextBox();
            this.textBoxSimpleReqEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxSimpleReqAddr = new System.Windows.Forms.TextBox();
            this.buttonMatchReq = new System.Windows.Forms.Button();
            this.buttonActiveEpReq = new System.Windows.Forms.Button();
            this.buttonPowerDescReq = new System.Windows.Forms.Button();
            this.buttonSimpleDescReq = new System.Windows.Forms.Button();
            this.textBoxNodeDescReq = new System.Windows.Forms.TextBox();
            this.buttonNodeDescReq = new System.Windows.Forms.Button();
            this.buttonIeeeAddrReq = new System.Windows.Forms.Button();
            this.buttonNwkAddrReq = new System.Windows.Forms.Button();
            this.comboBoxSecurityKey = new System.Windows.Forms.ComboBox();
            this.comboBoxPermitJoinTCsignificance = new System.Windows.Forms.ComboBox();
            this.textBoxPermitJoinInterval = new System.Windows.Forms.TextBox();
            this.textBoxPermitJoinAddr = new System.Windows.Forms.TextBox();
            this.buttonPermitJoin = new System.Windows.Forms.Button();
            this.comboBoxSetKeyType = new System.Windows.Forms.ComboBox();
            this.comboBoxSetKeyState = new System.Windows.Forms.ComboBox();
            this.comboBoxSetType = new System.Windows.Forms.ComboBox();
            this.buttonStartNWK = new System.Windows.Forms.Button();
            this.buttonBind = new System.Windows.Forms.Button();
            this.buttonErasePD = new System.Windows.Forms.Button();
            this.buttonReset = new System.Windows.Forms.Button();
            this.textBoxSetSecurityKeySeqNbr = new System.Windows.Forms.TextBox();
            this.buttonSetDeviceType = new System.Windows.Forms.Button();
            this.buttonSetSecurity = new System.Windows.Forms.Button();
            this.textBoxSetEPID = new System.Windows.Forms.TextBox();
            this.textBoxSetCMSK = new System.Windows.Forms.TextBox();
            this.buttonSetCMSK = new System.Windows.Forms.Button();
            this.buttonSetEPID = new System.Windows.Forms.Button();
            this.buttonGetVersion = new System.Windows.Forms.Button();
            this.tabPageDevice = new System.Windows.Forms.TabPage();
            this.buttonCopyAddr = new System.Windows.Forms.Button();
            this.buttonDiscoverDevices = new System.Windows.Forms.Button();
            this.textBoxExtAddr = new System.Windows.Forms.TextBox();
            this.label16 = new System.Windows.Forms.Label();
            this.comboBoxAddressList = new System.Windows.Forms.ComboBox();
            this.tabPage12 = new System.Windows.Forms.TabPage();
            this.textBoxOOBDataKey = new System.Windows.Forms.TextBox();
            this.textBoxOOBDataAddr = new System.Windows.Forms.TextBox();
            this.buttonOOBCommissioningData = new System.Windows.Forms.Button();
            this.textBoxDiscoverAttributesStartAttrId = new System.Windows.Forms.TextBox();
            this.textBoxRawDataCommandsProfileID = new System.Windows.Forms.TextBox();
            this.textBoxRawDataCommandsSecurityMode = new System.Windows.Forms.TextBox();
            this.textBoxRawDataCommandsRadius = new System.Windows.Forms.TextBox();
            this.textBoxRawDataCommandsData = new System.Windows.Forms.TextBox();
            this.textBoxRawDataCommandsClusterID = new System.Windows.Forms.TextBox();
            this.textBoxRawDataCommandsDstEP = new System.Windows.Forms.TextBox();
            this.textBoxRawDataCommandsSrcEP = new System.Windows.Forms.TextBox();
            this.textBoxRawDataCommandsTargetAddr = new System.Windows.Forms.TextBox();
            this.comboBoxRawDataCommandsAddrMode = new System.Windows.Forms.ComboBox();
            this.buttonRawDataSend = new System.Windows.Forms.Button();
            this.textBoxMgmtNwkUpdateNwkManagerAddr = new System.Windows.Forms.TextBox();
            this.comboBoxDiscoverCommandsRxGen = new System.Windows.Forms.ComboBox();
            this.comboBoxDiscoverAttributesExtended = new System.Windows.Forms.ComboBox();
            this.textBoxDiscoverCommandsMaxCommands = new System.Windows.Forms.TextBox();
            this.textBoxDiscoverCommandsManuID = new System.Windows.Forms.TextBox();
            this.comboBoxDiscoverCommandsManuSpecific = new System.Windows.Forms.ComboBox();
            this.textBoxDiscoverCommandsCommandID = new System.Windows.Forms.TextBox();
            this.comboBoxDiscoverCommandsDirection = new System.Windows.Forms.ComboBox();
            this.textBoxDiscoverCommandsClusterID = new System.Windows.Forms.TextBox();
            this.textBoxDiscoverCommandsDstEP = new System.Windows.Forms.TextBox();
            this.textBoxDiscoverCommandsSrcEP = new System.Windows.Forms.TextBox();
            this.textBoxDiscoverCommandsTargetAddr = new System.Windows.Forms.TextBox();
            this.comboBoxDiscoverCommandsAddrMode = new System.Windows.Forms.ComboBox();
            this.buttonDiscoverCommands = new System.Windows.Forms.Button();
            this.textBoxMgmtNwkUpdateScanCount = new System.Windows.Forms.TextBox();
            this.textBoxMgmtNwkUpdateScanDuration = new System.Windows.Forms.TextBox();
            this.textBoxMgmtNwkUpdateChannelMask = new System.Windows.Forms.TextBox();
            this.textBoxMgmtNwkUpdateTargetAddr = new System.Windows.Forms.TextBox();
            this.comboBoxMgmtNwkUpdateAddrMode = new System.Windows.Forms.ComboBox();
            this.buttonMgmtNwkUpdate = new System.Windows.Forms.Button();
            this.comboBoxManyToOneRouteRequestCacheRoute = new System.Windows.Forms.ComboBox();
            this.textBoxManyToOneRouteRequesRadius = new System.Windows.Forms.TextBox();
            this.buttonManyToOneRouteRequest = new System.Windows.Forms.Button();
            this.comboBoxReadReportConfigDirection = new System.Windows.Forms.ComboBox();
            this.comboBoxReadReportConfigDirIsRx = new System.Windows.Forms.ComboBox();
            this.textBoxReadReportConfigAttribID = new System.Windows.Forms.TextBox();
            this.textBoxReadReportConfigClusterID = new System.Windows.Forms.TextBox();
            this.textBoxReadReportConfigDstEP = new System.Windows.Forms.TextBox();
            this.textBoxReadReportConfigSrcEP = new System.Windows.Forms.TextBox();
            this.textBoxReadReportConfigTargetAddr = new System.Windows.Forms.TextBox();
            this.comboBoxReadReportConfigAddrMode = new System.Windows.Forms.ComboBox();
            this.buttonReadReportConfig = new System.Windows.Forms.Button();
            this.textBoxWriteAttribManuID = new System.Windows.Forms.TextBox();
            this.comboBoxWriteAttribManuSpecific = new System.Windows.Forms.ComboBox();
            this.textBoxWriteAttribDataType = new System.Windows.Forms.TextBox();
            this.textBoxReadAttribManuID = new System.Windows.Forms.TextBox();
            this.comboBoxReadAttribManuSpecific = new System.Windows.Forms.ComboBox();
            this.comboBoxConfigReportAddrMode = new System.Windows.Forms.ComboBox();
            this.textBoxWriteAttribData = new System.Windows.Forms.TextBox();
            this.textBoxWriteAttribID = new System.Windows.Forms.TextBox();
            this.comboBoxWriteAttribDirection = new System.Windows.Forms.ComboBox();
            this.textBoxWriteAttribClusterID = new System.Windows.Forms.TextBox();
            this.textBoxWriteAttribDstEP = new System.Windows.Forms.TextBox();
            this.textBoxWriteAttribSrcEP = new System.Windows.Forms.TextBox();
            this.textBoxWriteAttribTargetAddr = new System.Windows.Forms.TextBox();
            this.textBoxConfigReportChange = new System.Windows.Forms.TextBox();
            this.textBoxConfigReportTimeOut = new System.Windows.Forms.TextBox();
            this.textBoxConfigReportMaxInterval = new System.Windows.Forms.TextBox();
            this.textBoxDiscoverAttributesMaxIDs = new System.Windows.Forms.TextBox();
            this.comboBoxDiscoverAttributesDirection = new System.Windows.Forms.ComboBox();
            this.textBoxDiscoverAttributesClusterID = new System.Windows.Forms.TextBox();
            this.textBoxDiscoverAttributesDstEp = new System.Windows.Forms.TextBox();
            this.textBoxDiscoverAttributesSrcEp = new System.Windows.Forms.TextBox();
            this.textBoxDiscoverAttributesAddr = new System.Windows.Forms.TextBox();
            this.buttonDiscoverAttributes = new System.Windows.Forms.Button();
            this.comboBoxReadAllAttribDirection = new System.Windows.Forms.ComboBox();
            this.textBoxReadAllAttribClusterID = new System.Windows.Forms.TextBox();
            this.textBoxReadAllAttribDstEP = new System.Windows.Forms.TextBox();
            this.textBoxReadAllAttribSrcEP = new System.Windows.Forms.TextBox();
            this.textBoxReadAllAttribAddr = new System.Windows.Forms.TextBox();
            this.buttonReadAllAttrib = new System.Windows.Forms.Button();
            this.comboBoxConfigReportAttribDirection = new System.Windows.Forms.ComboBox();
            this.textBoxConfigReportAttribType = new System.Windows.Forms.TextBox();
            this.textBoxConfigReportMinInterval = new System.Windows.Forms.TextBox();
            this.textBoxConfigReportAttribID = new System.Windows.Forms.TextBox();
            this.comboBoxConfigReportDirection = new System.Windows.Forms.ComboBox();
            this.textBoxConfigReportClusterID = new System.Windows.Forms.TextBox();
            this.textBoxConfigReportDstEP = new System.Windows.Forms.TextBox();
            this.textBoxConfigReportSrcEP = new System.Windows.Forms.TextBox();
            this.textBoxConfigReportTargetAddr = new System.Windows.Forms.TextBox();
            this.buttonConfigReport = new System.Windows.Forms.Button();
            this.buttonWriteAttrib = new System.Windows.Forms.Button();
            this.textBoxReadAttribCount = new System.Windows.Forms.TextBox();
            this.comboBoxReadAttribDirection = new System.Windows.Forms.ComboBox();
            this.textBoxReadAttribID1 = new System.Windows.Forms.TextBox();
            this.textBoxReadAttribClusterID = new System.Windows.Forms.TextBox();
            this.textBoxReadAttribDstEP = new System.Windows.Forms.TextBox();
            this.textBoxReadAttribSrcEP = new System.Windows.Forms.TextBox();
            this.textBoxReadAttribTargetAddr = new System.Windows.Forms.TextBox();
            this.buttonReadAttrib = new System.Windows.Forms.Button();
            this.AHIControl = new System.Windows.Forms.TabPage();
            this.textBoxAHITxPower = new System.Windows.Forms.TextBox();
            this.buttonAHISetTxPower = new System.Windows.Forms.Button();
            this.labelUnimplemented = new System.Windows.Forms.Label();
            this.comboBoxIPNConfigTimerId = new System.Windows.Forms.ComboBox();
            this.textBoxIPNConfigDioTxConfInDioMask = new System.Windows.Forms.TextBox();
            this.textBoxDioSetOutputOffPinMask = new System.Windows.Forms.TextBox();
            this.textBoxDioSetOutputOnPinMask = new System.Windows.Forms.TextBox();
            this.buttonDioSetOutput = new System.Windows.Forms.Button();
            this.textBoxDioSetDirectionOutputPinMask = new System.Windows.Forms.TextBox();
            this.textBoxDioSetDirectionInputPinMask = new System.Windows.Forms.TextBox();
            this.buttonDioSetDirection = new System.Windows.Forms.Button();
            this.textBoxIPNConfigPollPeriod = new System.Windows.Forms.TextBox();
            this.comboBoxIPNConfigRegisterCallback = new System.Windows.Forms.ComboBox();
            this.textBoxIPNConfigDioStatusOutDioMask = new System.Windows.Forms.TextBox();
            this.textBoxIPNConfigDioRfActiveOutDioMask = new System.Windows.Forms.TextBox();
            this.comboBoxIPNConfigEnable = new System.Windows.Forms.ComboBox();
            this.buttonInPacketNotification = new System.Windows.Forms.Button();
            this.BasicClusterTab = new System.Windows.Forms.TabPage();
            this.textBoxBasicResetDstEP = new System.Windows.Forms.TextBox();
            this.textBoxBasicResetSrcEP = new System.Windows.Forms.TextBox();
            this.textBoxBasicResetTargetAddr = new System.Windows.Forms.TextBox();
            this.comboBoxBasicResetTargetAddrMode = new System.Windows.Forms.ComboBox();
            this.buttonBasicReset = new System.Windows.Forms.Button();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.textBoxGroupName = new System.Windows.Forms.TextBox();
            this.textBoxGroupNameMaxLength = new System.Windows.Forms.TextBox();
            this.textBoxGroupNameLength = new System.Windows.Forms.TextBox();
            this.buttonAddToList = new System.Windows.Forms.Button();
            this.textBoxGroupAddIfIdentifyGroupID = new System.Windows.Forms.TextBox();
            this.textBoxGroupAddIfIdentifySrcEp = new System.Windows.Forms.TextBox();
            this.textBoxGroupAddIfIdentifyDstEp = new System.Windows.Forms.TextBox();
            this.textBoxGroupAddIfIndentifyingTargetAddr = new System.Windows.Forms.TextBox();
            this.buttonGroupAddIfIdentifying = new System.Windows.Forms.Button();
            this.textBoxRemoveAllGroupDstEp = new System.Windows.Forms.TextBox();
            this.textBoxRemoveAllGroupSrcEp = new System.Windows.Forms.TextBox();
            this.textBoxRemoveAllGroupTargetAddr = new System.Windows.Forms.TextBox();
            this.buttonGroupRemoveAll = new System.Windows.Forms.Button();
            this.textBoxRemoveGroupGroupAddr = new System.Windows.Forms.TextBox();
            this.textBoxRemoveGroupDstEp = new System.Windows.Forms.TextBox();
            this.textBoxRemoveGroupSrcEp = new System.Windows.Forms.TextBox();
            this.textBoxRemoveGroupTargetAddr = new System.Windows.Forms.TextBox();
            this.buttonRemoveGroup = new System.Windows.Forms.Button();
            this.textBoxGetGroupCount = new System.Windows.Forms.TextBox();
            this.textBoxGetGroupDstEp = new System.Windows.Forms.TextBox();
            this.textBoxGetGroupSrcEp = new System.Windows.Forms.TextBox();
            this.textBoxGetGroupTargetAddr = new System.Windows.Forms.TextBox();
            this.buttonGetGroup = new System.Windows.Forms.Button();
            this.textBoxViewGroupGroupAddr = new System.Windows.Forms.TextBox();
            this.textBoxViewGroupDstEp = new System.Windows.Forms.TextBox();
            this.textBoxViewGroupSrcEp = new System.Windows.Forms.TextBox();
            this.textBoxViewGroupAddr = new System.Windows.Forms.TextBox();
            this.buttonViewGroup = new System.Windows.Forms.Button();
            this.textBoxAddGroupGroupAddr = new System.Windows.Forms.TextBox();
            this.textBoxAddGroupDstEp = new System.Windows.Forms.TextBox();
            this.textBoxAddGroupSrcEp = new System.Windows.Forms.TextBox();
            this.textBoxAddGroupAddr = new System.Windows.Forms.TextBox();
            this.buttonAddGroup = new System.Windows.Forms.Button();
            this.tabPage5 = new System.Windows.Forms.TabPage();
            this.textBoxIdQueryDstEp = new System.Windows.Forms.TextBox();
            this.textBoxIdQuerySrcEp = new System.Windows.Forms.TextBox();
            this.textBoxIdQueryAddr = new System.Windows.Forms.TextBox();
            this.textBoxIdSendTime = new System.Windows.Forms.TextBox();
            this.textBoxIdSendDstEp = new System.Windows.Forms.TextBox();
            this.textBoxSendIdSrcEp = new System.Windows.Forms.TextBox();
            this.textBoxSendIdAddr = new System.Windows.Forms.TextBox();
            this.buttonIdQuery = new System.Windows.Forms.Button();
            this.buttonIdSend = new System.Windows.Forms.Button();
            this.tabPage6 = new System.Windows.Forms.TabPage();
            this.comboBoxMoveToLevelOnOff = new System.Windows.Forms.ComboBox();
            this.comboBoxMoveToLevelAddrMode = new System.Windows.Forms.ComboBox();
            this.textBoxMoveToLevelTransTime = new System.Windows.Forms.TextBox();
            this.textBoxMoveToLevelLevel = new System.Windows.Forms.TextBox();
            this.textBoxMoveToLevelDstEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxMoveToLevelSrcEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxMoveToLevelAddr = new System.Windows.Forms.TextBox();
            this.buttonMoveToLevel = new System.Windows.Forms.Button();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.comboBoxOnOffAddrMode = new System.Windows.Forms.ComboBox();
            this.comboBoxOnOffCommand = new System.Windows.Forms.ComboBox();
            this.textBoxOnOffDstEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxOnOffSrcEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxOnOffAddr = new System.Windows.Forms.TextBox();
            this.buttonOnOff = new System.Windows.Forms.Button();
            this.tabPage7 = new System.Windows.Forms.TabPage();
            this.checkBoxShowExtension = new System.Windows.Forms.CheckBox();
            this.textBoxAddSceneData = new System.Windows.Forms.TextBox();
            this.textBoxAddSceneExtLen = new System.Windows.Forms.TextBox();
            this.textBoxRemoveSceneSceneID = new System.Windows.Forms.TextBox();
            this.textBoxRemoveSceneGroupID = new System.Windows.Forms.TextBox();
            this.textBoxRemoveSceneDstEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxRemoveSceneSrcEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxRemoveSceneAddr = new System.Windows.Forms.TextBox();
            this.comboBoxRemoveSceneAddrMode = new System.Windows.Forms.ComboBox();
            this.buttonRemoveScene = new System.Windows.Forms.Button();
            this.textBoxRemoveAllScenesGroupID = new System.Windows.Forms.TextBox();
            this.textBoxRemoveAllScenesDstEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxRemoveAllScenesSrcEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxRemoveAllScenesAddr = new System.Windows.Forms.TextBox();
            this.comboBoxRemoveAllScenesAddrMode = new System.Windows.Forms.ComboBox();
            this.buttonRemoveAllScenes = new System.Windows.Forms.Button();
            this.textBoxGetSceneMembershipGroupID = new System.Windows.Forms.TextBox();
            this.textBoxGetSceneMembershipDstEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxGetSceneMembershipSrcEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxGetSceneMembershipAddr = new System.Windows.Forms.TextBox();
            this.comboBoxGetSceneMembershipAddrMode = new System.Windows.Forms.ComboBox();
            this.buttonGetSceneMembership = new System.Windows.Forms.Button();
            this.textBoxRecallSceneSceneId = new System.Windows.Forms.TextBox();
            this.textBoxRecallSceneGroupId = new System.Windows.Forms.TextBox();
            this.textBoxRecallSceneDstEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxRecallSceneSrcEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxRecallSceneAddr = new System.Windows.Forms.TextBox();
            this.comboBoxRecallSceneAddrMode = new System.Windows.Forms.ComboBox();
            this.buttonRecallScene = new System.Windows.Forms.Button();
            this.textBoxStoreSceneSceneId = new System.Windows.Forms.TextBox();
            this.textBoxStoreSceneGroupId = new System.Windows.Forms.TextBox();
            this.textBoxStoreSceneDstEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxStoreSceneSrcEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxStoreSceneAddr = new System.Windows.Forms.TextBox();
            this.comboBoxStoreSceneAddrMode = new System.Windows.Forms.ComboBox();
            this.buttonStoreScene = new System.Windows.Forms.Button();
            this.textBoxAddSceneMaxNameLen = new System.Windows.Forms.TextBox();
            this.textBoxAddSceneNameLen = new System.Windows.Forms.TextBox();
            this.textBoxAddSceneName = new System.Windows.Forms.TextBox();
            this.textBoxAddSceneTransTime = new System.Windows.Forms.TextBox();
            this.textBoxAddSceneSceneId = new System.Windows.Forms.TextBox();
            this.textBoxAddSceneGroupId = new System.Windows.Forms.TextBox();
            this.textBoxAddSceneDstEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxAddSceneSrcEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxAddSceneAddr = new System.Windows.Forms.TextBox();
            this.comboBoxAddSceneAddrMode = new System.Windows.Forms.ComboBox();
            this.buttonAddScene = new System.Windows.Forms.Button();
            this.comboBoxViewSceneAddrMode = new System.Windows.Forms.ComboBox();
            this.textBoxViewSceneSceneId = new System.Windows.Forms.TextBox();
            this.textBoxViewSceneGroupId = new System.Windows.Forms.TextBox();
            this.textBoxViewSceneDstEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxViewSceneSrcEndPoint = new System.Windows.Forms.TextBox();
            this.textBoxViewSceneAddr = new System.Windows.Forms.TextBox();
            this.buttonViewScene = new System.Windows.Forms.Button();
            this.tabPage8 = new System.Windows.Forms.TabPage();
            this.textBoxMoveToSatTime = new System.Windows.Forms.TextBox();
            this.textBoxMoveToSatSat = new System.Windows.Forms.TextBox();
            this.textBoxMoveToSatDstEp = new System.Windows.Forms.TextBox();
            this.textBoxMoveToSatSrcEp = new System.Windows.Forms.TextBox();
            this.buttonMoveToSat = new System.Windows.Forms.Button();
            this.textBoxMoveToSatAddr = new System.Windows.Forms.TextBox();
            this.textBoxMoveToColorTempRate = new System.Windows.Forms.TextBox();
            this.textBoxMoveToColorTempTemp = new System.Windows.Forms.TextBox();
            this.textBoxMoveToColorTempDstEp = new System.Windows.Forms.TextBox();
            this.textBoxMoveToColorTempSrcEp = new System.Windows.Forms.TextBox();
            this.textBoxMoveToColorTempAddr = new System.Windows.Forms.TextBox();
            this.buttonMoveToColorTemp = new System.Windows.Forms.Button();
            this.textBoxMoveToColorTime = new System.Windows.Forms.TextBox();
            this.textBoxMoveToColorY = new System.Windows.Forms.TextBox();
            this.textBoxMoveToColorX = new System.Windows.Forms.TextBox();
            this.textBoxMoveToColorDstEp = new System.Windows.Forms.TextBox();
            this.textBoxMoveToColorSrcEp = new System.Windows.Forms.TextBox();
            this.textBoxMoveToColorAddr = new System.Windows.Forms.TextBox();
            this.buttonMoveToColor = new System.Windows.Forms.Button();
            this.textBoxMoveToHueTime = new System.Windows.Forms.TextBox();
            this.textBoxMoveToHueDir = new System.Windows.Forms.TextBox();
            this.textBoxMoveToHueHue = new System.Windows.Forms.TextBox();
            this.textBoxMoveToHueDstEp = new System.Windows.Forms.TextBox();
            this.textBoxMoveToHueSrcEp = new System.Windows.Forms.TextBox();
            this.buttonMoveToHue = new System.Windows.Forms.Button();
            this.textBoxMoveToHueAddr = new System.Windows.Forms.TextBox();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.comboBoxLockUnlock = new System.Windows.Forms.ComboBox();
            this.textBoxLockUnlockDstEp = new System.Windows.Forms.TextBox();
            this.textBoxLockUnlockSrcEp = new System.Windows.Forms.TextBox();
            this.textBoxLockUnlockAddr = new System.Windows.Forms.TextBox();
            this.buttonLockUnlock = new System.Windows.Forms.Button();
            this.tabPage13 = new System.Windows.Forms.TabPage();
            this.comboBoxEnrollRspCode = new System.Windows.Forms.ComboBox();
            this.textBoxEnrollRspZone = new System.Windows.Forms.TextBox();
            this.textBoxEnrollRspDstEp = new System.Windows.Forms.TextBox();
            this.textBoxEnrollRspSrcEp = new System.Windows.Forms.TextBox();
            this.textBoxEnrollRspAddr = new System.Windows.Forms.TextBox();
            this.comboBoxEnrollRspAddrMode = new System.Windows.Forms.ComboBox();
            this.buttonEnrollResponse = new System.Windows.Forms.Button();
            this.tabPage15 = new System.Windows.Forms.TabPage();
            this.label17 = new System.Windows.Forms.Label();
            this.tabPage9 = new System.Windows.Forms.TabPage();
            this.buttonZllTouchlinkFactoryReset = new System.Windows.Forms.Button();
            this.buttonZllTouchlinkInitiate = new System.Windows.Forms.Button();
            this.tabPage10 = new System.Windows.Forms.TabPage();
            this.comboBoxZllOnOffEffectID = new System.Windows.Forms.ComboBox();
            this.textBoxZllOnOffEffectsGradient = new System.Windows.Forms.TextBox();
            this.textBoxZllOnOffEffectsDstEp = new System.Windows.Forms.TextBox();
            this.textBoxZllOnOffEffectsSrcEp = new System.Windows.Forms.TextBox();
            this.textBoxZllOnOffEffectsAddr = new System.Windows.Forms.TextBox();
            this.buttonZllOnOffEffects = new System.Windows.Forms.Button();
            this.tabPage11 = new System.Windows.Forms.TabPage();
            this.textBoxZllMoveToHueHue = new System.Windows.Forms.TextBox();
            this.textBoxZllMoveToHueTransTime = new System.Windows.Forms.TextBox();
            this.textBoxZllMoveToHueDirection = new System.Windows.Forms.TextBox();
            this.textBoxZllMoveToHueDstEp = new System.Windows.Forms.TextBox();
            this.textBoxZllMoveToHueSrcEp = new System.Windows.Forms.TextBox();
            this.textBoxZllMoveToHueAddr = new System.Windows.Forms.TextBox();
            this.button8 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.buttonZllMoveToHue = new System.Windows.Forms.Button();
            this.tabPage14 = new System.Windows.Forms.TabPage();
            this.textBoxOtaFileStackVer = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.textBoxOtaFileHeaderVer = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.textBoxOtaFileHeaderLen = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.textBoxOtaFileHeaderFCTL = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.textBoxOtaFileID = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.textBoxOtaFileHeaderStr = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textBoxOTASetWaitForDataParamsRequestBlockDelay = new System.Windows.Forms.TextBox();
            this.textBoxOTASetWaitForDataParamsRequestTime = new System.Windows.Forms.TextBox();
            this.textBoxOTASetWaitForDataParamsCurrentTime = new System.Windows.Forms.TextBox();
            this.textBoxOTASetWaitForDataParamsSrcEP = new System.Windows.Forms.TextBox();
            this.textBoxOTASetWaitForDataParamsTargetAddr = new System.Windows.Forms.TextBox();
            this.buttonOTASetWaitForDataParams = new System.Windows.Forms.Button();
            this.textBoxOtaFileOffset = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.textBoxOtaDownloadStatus = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.progressBarOtaDownloadProgress = new System.Windows.Forms.ProgressBar();
            this.textBoxOTAImageNotifyJitter = new System.Windows.Forms.TextBox();
            this.textBoxOTAImageNotifyManuID = new System.Windows.Forms.TextBox();
            this.textBoxOTAImageNotifyImageType = new System.Windows.Forms.TextBox();
            this.textBoxOTAImageNotifyFileVersion = new System.Windows.Forms.TextBox();
            this.comboBoxOTAImageNotifyType = new System.Windows.Forms.ComboBox();
            this.textBoxOTAImageNotifyDstEP = new System.Windows.Forms.TextBox();
            this.textBoxOTAImageNotifySrcEP = new System.Windows.Forms.TextBox();
            this.textBoxOTAImageNotifyTargetAddr = new System.Windows.Forms.TextBox();
            this.comboBoxOTAImageNotifyAddrMode = new System.Windows.Forms.ComboBox();
            this.buttonOTAImageNotify = new System.Windows.Forms.Button();
            this.textBoxOtaFileSize = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.textBoxOtaFileVersion = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxOtaFileImageType = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxOtaFileManuCode = new System.Windows.Forms.TextBox();
            this.buttonOTALoadNewImage = new System.Windows.Forms.Button();
            this.tabPagePollControl = new System.Windows.Forms.TabPage();
            this.comboBoxFastPollEnable = new System.Windows.Forms.ComboBox();
            this.textBoxFastPollExpiryTime = new System.Windows.Forms.TextBox();
            this.buttonSetCheckinRspData = new System.Windows.Forms.Button();
            this.buttonMessageViewClear = new System.Windows.Forms.Button();
            this.buttonClearRaw = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.richTextBoxMessageView = new System.Windows.Forms.RichTextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.richTextBoxCommandResponse = new System.Windows.Forms.RichTextBox();
            this.openOtaFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.toolTipGeneralTooltip = new System.Windows.Forms.ToolTip(this.components);
            this.checkBoxDebug = new System.Windows.Forms.CheckBox();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.buttonNciCmd = new System.Windows.Forms.Button();
            this.comboBoxNciCmd = new System.Windows.Forms.ComboBox();
            this.menuStrip1.SuspendLayout();
            this.statusStrip.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPageDevice.SuspendLayout();
            this.tabPage12.SuspendLayout();
            this.AHIControl.SuspendLayout();
            this.BasicClusterTab.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.tabPage5.SuspendLayout();
            this.tabPage6.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.tabPage7.SuspendLayout();
            this.tabPage8.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage13.SuspendLayout();
            this.tabPage15.SuspendLayout();
            this.tabPage9.SuspendLayout();
            this.tabPage10.SuspendLayout();
            this.tabPage11.SuspendLayout();
            this.tabPage14.SuspendLayout();
            this.tabPagePollControl.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.settingsToolStripMenuItem,
            this.openPortToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1385, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // settingsToolStripMenuItem
            // 
            this.settingsToolStripMenuItem.Name = "settingsToolStripMenuItem";
            this.settingsToolStripMenuItem.Size = new System.Drawing.Size(61, 20);
            this.settingsToolStripMenuItem.Text = "Settings";
            this.settingsToolStripMenuItem.Click += new System.EventHandler(this.settingsToolStripMenuItem_Click);
            // 
            // openPortToolStripMenuItem
            // 
            this.openPortToolStripMenuItem.Name = "openPortToolStripMenuItem";
            this.openPortToolStripMenuItem.Size = new System.Drawing.Size(73, 20);
            this.openPortToolStripMenuItem.Text = "Open Port";
            this.openPortToolStripMenuItem.Click += new System.EventHandler(this.openPortToolStripMenuItem_Click);
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(52, 20);
            this.aboutToolStripMenuItem.Text = "About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // statusStrip
            // 
            this.statusStrip.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusPort,
            this.toolStripPortSettings});
            this.statusStrip.Location = new System.Drawing.Point(0, 743);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Padding = new System.Windows.Forms.Padding(1, 0, 15, 0);
            this.statusStrip.Size = new System.Drawing.Size(1385, 22);
            this.statusStrip.TabIndex = 1;
            this.statusStrip.Text = "statusStrip1";
            // 
            // toolStripStatusPort
            // 
            this.toolStripStatusPort.Name = "toolStripStatusPort";
            this.toolStripStatusPort.Size = new System.Drawing.Size(0, 17);
            // 
            // toolStripPortSettings
            // 
            this.toolStripPortSettings.Name = "toolStripPortSettings";
            this.toolStripPortSettings.Size = new System.Drawing.Size(0, 17);
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPageDevice);
            this.tabControl1.Controls.Add(this.tabPage12);
            this.tabControl1.Controls.Add(this.AHIControl);
            this.tabControl1.Controls.Add(this.BasicClusterTab);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage5);
            this.tabControl1.Controls.Add(this.tabPage6);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Controls.Add(this.tabPage7);
            this.tabControl1.Controls.Add(this.tabPage8);
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage13);
            this.tabControl1.Controls.Add(this.tabPage15);
            this.tabControl1.Controls.Add(this.tabPage9);
            this.tabControl1.Controls.Add(this.tabPage10);
            this.tabControl1.Controls.Add(this.tabPage11);
            this.tabControl1.Controls.Add(this.tabPage14);
            this.tabControl1.Controls.Add(this.tabPagePollControl);
            this.tabControl1.Location = new System.Drawing.Point(13, 26);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(1359, 442);
            this.tabControl1.TabIndex = 2;
            // 
            // tabPage2
            // 
            this.tabPage2.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage2.Controls.Add(this.comboBoxNciCmd);
            this.tabPage2.Controls.Add(this.buttonNciCmd);
            this.tabPage2.Controls.Add(this.textBoxPollInterval);
            this.tabPage2.Controls.Add(this.buttonPollInterval);
            this.tabPage2.Controls.Add(this.buttonNWKState);
            this.tabPage2.Controls.Add(this.buttonDiscoveryOnly);
            this.tabPage2.Controls.Add(this.textBoxBindTargetExtAddr);
            this.tabPage2.Controls.Add(this.textBoxUserSetReqDescription);
            this.tabPage2.Controls.Add(this.textBoxUserSetReqAddr);
            this.tabPage2.Controls.Add(this.buttonUserSetReq);
            this.tabPage2.Controls.Add(this.textBoxUserReqAddr);
            this.tabPage2.Controls.Add(this.buttonUserReq);
            this.tabPage2.Controls.Add(this.textBoxRestoreNwkFrameCounter);
            this.tabPage2.Controls.Add(this.comboBoxLeaveChildren);
            this.tabPage2.Controls.Add(this.comboBoxLeaveReJoin);
            this.tabPage2.Controls.Add(this.textBoxLeaveAddr);
            this.tabPage2.Controls.Add(this.buttonLeave);
            this.tabPage2.Controls.Add(this.textBoxRemoveChildAddr);
            this.tabPage2.Controls.Add(this.textBoxRemoveParentAddr);
            this.tabPage2.Controls.Add(this.buttonRemoveDevice);
            this.tabPage2.Controls.Add(this.buttonPermitJoinState);
            this.tabPage2.Controls.Add(this.buttonRestoreNwk);
            this.tabPage2.Controls.Add(this.buttonRecoverNwk);
            this.tabPage2.Controls.Add(this.comboBoxMgmtLeaveChildren);
            this.tabPage2.Controls.Add(this.comboBoxMgmtLeaveReJoin);
            this.tabPage2.Controls.Add(this.textBoxMgmtLeaveExtAddr);
            this.tabPage2.Controls.Add(this.textBoxMgmtLeaveAddr);
            this.tabPage2.Controls.Add(this.buttonMgmtLeave);
            this.tabPage2.Controls.Add(this.textBoxUnBindDestEP);
            this.tabPage2.Controls.Add(this.textBoxUnBindDestAddr);
            this.tabPage2.Controls.Add(this.comboBoxUnBindAddrMode);
            this.tabPage2.Controls.Add(this.textBoxUnBindClusterID);
            this.tabPage2.Controls.Add(this.textBoxUnBindTargetEP);
            this.tabPage2.Controls.Add(this.textBoxUnBindTargetExtAddr);
            this.tabPage2.Controls.Add(this.buttonUnBind);
            this.tabPage2.Controls.Add(this.textBoxBindDestEP);
            this.tabPage2.Controls.Add(this.textBoxBindDestAddr);
            this.tabPage2.Controls.Add(this.comboBoxBindAddrMode);
            this.tabPage2.Controls.Add(this.textBoxBindClusterID);
            this.tabPage2.Controls.Add(this.textBoxBindTargetEP);
            this.tabPage2.Controls.Add(this.textBoxLqiReqStartIndex);
            this.tabPage2.Controls.Add(this.textBoxLqiReqTargetAddr);
            this.tabPage2.Controls.Add(this.buttonMgmtLqiReq);
            this.tabPage2.Controls.Add(this.buttonStartScan);
            this.tabPage2.Controls.Add(this.textBoxNwkAddrReqStartIndex);
            this.tabPage2.Controls.Add(this.comboBoxNwkAddrReqType);
            this.tabPage2.Controls.Add(this.textBoxNwkAddrReqExtAddr);
            this.tabPage2.Controls.Add(this.textBoxNwkAddrReqTargetAddr);
            this.tabPage2.Controls.Add(this.textBoxIeeeReqStartIndex);
            this.tabPage2.Controls.Add(this.comboBoxIeeeReqType);
            this.tabPage2.Controls.Add(this.textBoxIeeeReqAddr);
            this.tabPage2.Controls.Add(this.textBoxIeeeReqTargetAddr);
            this.tabPage2.Controls.Add(this.textBoxComplexReqAddr);
            this.tabPage2.Controls.Add(this.buttonComplexReq);
            this.tabPage2.Controls.Add(this.textBoxMatchReqOutputClusters);
            this.tabPage2.Controls.Add(this.textBoxMatchReqInputClusters);
            this.tabPage2.Controls.Add(this.textBoxMatchReqProfileID);
            this.tabPage2.Controls.Add(this.textBoxMatchReqNbrOutputClusters);
            this.tabPage2.Controls.Add(this.textBoxMatchReqNbrInputClusters);
            this.tabPage2.Controls.Add(this.textBoxMatchReqAddr);
            this.tabPage2.Controls.Add(this.textBoxActiveEpAddr);
            this.tabPage2.Controls.Add(this.textBoxPowerReqAddr);
            this.tabPage2.Controls.Add(this.textBoxSimpleReqEndPoint);
            this.tabPage2.Controls.Add(this.textBoxSimpleReqAddr);
            this.tabPage2.Controls.Add(this.buttonMatchReq);
            this.tabPage2.Controls.Add(this.buttonActiveEpReq);
            this.tabPage2.Controls.Add(this.buttonPowerDescReq);
            this.tabPage2.Controls.Add(this.buttonSimpleDescReq);
            this.tabPage2.Controls.Add(this.textBoxNodeDescReq);
            this.tabPage2.Controls.Add(this.buttonNodeDescReq);
            this.tabPage2.Controls.Add(this.buttonIeeeAddrReq);
            this.tabPage2.Controls.Add(this.buttonNwkAddrReq);
            this.tabPage2.Controls.Add(this.comboBoxSecurityKey);
            this.tabPage2.Controls.Add(this.comboBoxPermitJoinTCsignificance);
            this.tabPage2.Controls.Add(this.textBoxPermitJoinInterval);
            this.tabPage2.Controls.Add(this.textBoxPermitJoinAddr);
            this.tabPage2.Controls.Add(this.buttonPermitJoin);
            this.tabPage2.Controls.Add(this.comboBoxSetKeyType);
            this.tabPage2.Controls.Add(this.comboBoxSetKeyState);
            this.tabPage2.Controls.Add(this.comboBoxSetType);
            this.tabPage2.Controls.Add(this.buttonStartNWK);
            this.tabPage2.Controls.Add(this.buttonBind);
            this.tabPage2.Controls.Add(this.buttonErasePD);
            this.tabPage2.Controls.Add(this.buttonReset);
            this.tabPage2.Controls.Add(this.textBoxSetSecurityKeySeqNbr);
            this.tabPage2.Controls.Add(this.buttonSetDeviceType);
            this.tabPage2.Controls.Add(this.buttonSetSecurity);
            this.tabPage2.Controls.Add(this.textBoxSetEPID);
            this.tabPage2.Controls.Add(this.textBoxSetCMSK);
            this.tabPage2.Controls.Add(this.buttonSetCMSK);
            this.tabPage2.Controls.Add(this.buttonSetEPID);
            this.tabPage2.Controls.Add(this.buttonGetVersion);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(1351, 416);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Management";
            this.tabPage2.Click += new System.EventHandler(this.tabPage2_Click);
            // 
            // textBoxPollInterval
            // 
            this.textBoxPollInterval.Location = new System.Drawing.Point(95, 386);
            this.textBoxPollInterval.Name = "textBoxPollInterval";
            this.textBoxPollInterval.Size = new System.Drawing.Size(129, 20);
            this.textBoxPollInterval.TabIndex = 89;
            this.textBoxPollInterval.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxPollInterval_MouseClick);
            this.textBoxPollInterval.MouseLeave += new System.EventHandler(this.textBoxPollInterval_MouseLeave);
            this.textBoxPollInterval.MouseHover += new System.EventHandler(this.textBoxPollInterval_MouseHover);
            // 
            // buttonPollInterval
            // 
            this.buttonPollInterval.Location = new System.Drawing.Point(6, 382);
            this.buttonPollInterval.Name = "buttonPollInterval";
            this.buttonPollInterval.Size = new System.Drawing.Size(80, 25);
            this.buttonPollInterval.TabIndex = 88;
            this.buttonPollInterval.Text = "PollInterval";
            this.buttonPollInterval.UseVisualStyleBackColor = true;
            this.buttonPollInterval.Click += new System.EventHandler(this.PollInterval_Click);
            // 
            // buttonNWKState
            // 
            this.buttonNWKState.Location = new System.Drawing.Point(752, 383);
            this.buttonNWKState.Name = "buttonNWKState";
            this.buttonNWKState.Size = new System.Drawing.Size(105, 22);
            this.buttonNWKState.TabIndex = 88;
            this.buttonNWKState.Text = "Network State";
            this.buttonNWKState.UseVisualStyleBackColor = true;
            this.buttonNWKState.Click += new System.EventHandler(this.buttonNWKState_Click);
            // 
            // buttonDiscoveryOnly
            // 
            this.buttonDiscoveryOnly.Location = new System.Drawing.Point(438, 6);
            this.buttonDiscoveryOnly.Name = "buttonDiscoveryOnly";
            this.buttonDiscoveryOnly.Size = new System.Drawing.Size(118, 22);
            this.buttonDiscoveryOnly.TabIndex = 6;
            this.buttonDiscoveryOnly.Text = "Scan Discovery Only";
            this.buttonDiscoveryOnly.UseVisualStyleBackColor = true;
            this.buttonDiscoveryOnly.Visible = false;
            this.buttonDiscoveryOnly.Click += new System.EventHandler(this.buttonDiscoveryOnly_Click);
            // 
            // textBoxBindTargetExtAddr
            // 
            this.textBoxBindTargetExtAddr.Location = new System.Drawing.Point(93, 326);
            this.textBoxBindTargetExtAddr.Name = "textBoxBindTargetExtAddr";
            this.textBoxBindTargetExtAddr.Size = new System.Drawing.Size(129, 20);
            this.textBoxBindTargetExtAddr.TabIndex = 43;
            this.textBoxBindTargetExtAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxBindTargetExtAddr_MouseClick);
            this.textBoxBindTargetExtAddr.Leave += new System.EventHandler(this.textBoxBindTargetExtAddr_Leave);
            this.textBoxBindTargetExtAddr.MouseLeave += new System.EventHandler(this.textBoxBindTargetExtAddr_MouseLeave);
            this.textBoxBindTargetExtAddr.MouseHover += new System.EventHandler(this.textBoxBindTargetExtAddr_MouseHover);
            // 
            // textBoxUserSetReqDescription
            // 
            this.textBoxUserSetReqDescription.Location = new System.Drawing.Point(951, 239);
            this.textBoxUserSetReqDescription.Name = "textBoxUserSetReqDescription";
            this.textBoxUserSetReqDescription.Size = new System.Drawing.Size(160, 20);
            this.textBoxUserSetReqDescription.TabIndex = 81;
            this.textBoxUserSetReqDescription.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxUserSetReqDescription_MouseClick);
            this.textBoxUserSetReqDescription.Leave += new System.EventHandler(this.textBoxUserSetReqDescription_Leave);
            this.textBoxUserSetReqDescription.MouseLeave += new System.EventHandler(this.textBoxUserSetReqDescription_MouseLeave);
            this.textBoxUserSetReqDescription.MouseHover += new System.EventHandler(this.textBoxUserSetReqDescription_MouseHover);
            // 
            // textBoxUserSetReqAddr
            // 
            this.textBoxUserSetReqAddr.Location = new System.Drawing.Point(838, 239);
            this.textBoxUserSetReqAddr.Name = "textBoxUserSetReqAddr";
            this.textBoxUserSetReqAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxUserSetReqAddr.TabIndex = 80;
            this.textBoxUserSetReqAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxUserSetReqAddr_MouseClick);
            this.textBoxUserSetReqAddr.Leave += new System.EventHandler(this.textBoxUserSetReqAddr_Leave);
            this.textBoxUserSetReqAddr.MouseLeave += new System.EventHandler(this.textBoxUserSetReqAddr_MouseLeave);
            this.textBoxUserSetReqAddr.MouseHover += new System.EventHandler(this.textBoxUserSetReqAddr_MouseHover);
            // 
            // buttonUserSetReq
            // 
            this.buttonUserSetReq.Location = new System.Drawing.Point(752, 238);
            this.buttonUserSetReq.Name = "buttonUserSetReq";
            this.buttonUserSetReq.Size = new System.Drawing.Size(80, 22);
            this.buttonUserSetReq.TabIndex = 79;
            this.buttonUserSetReq.Text = "UserSetReq";
            this.buttonUserSetReq.UseVisualStyleBackColor = true;
            this.buttonUserSetReq.Click += new System.EventHandler(this.buttonUserSetReq_Click);
            // 
            // textBoxUserReqAddr
            // 
            this.textBoxUserReqAddr.Location = new System.Drawing.Point(838, 210);
            this.textBoxUserReqAddr.Name = "textBoxUserReqAddr";
            this.textBoxUserReqAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxUserReqAddr.TabIndex = 78;
            this.textBoxUserReqAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxUserReqAddr_MouseClick);
            this.textBoxUserReqAddr.Leave += new System.EventHandler(this.textBoxUserReqAddr_Leave);
            this.textBoxUserReqAddr.MouseLeave += new System.EventHandler(this.textBoxUserReqAddr_MouseLeave);
            this.textBoxUserReqAddr.MouseHover += new System.EventHandler(this.textBoxUserReqAddr_MouseHover);
            // 
            // buttonUserReq
            // 
            this.buttonUserReq.Location = new System.Drawing.Point(752, 209);
            this.buttonUserReq.Name = "buttonUserReq";
            this.buttonUserReq.Size = new System.Drawing.Size(80, 22);
            this.buttonUserReq.TabIndex = 77;
            this.buttonUserReq.Text = "UserReq";
            this.buttonUserReq.UseVisualStyleBackColor = true;
            this.buttonUserReq.Click += new System.EventHandler(this.buttonUserReq_Click);
            // 
            // textBoxRestoreNwkFrameCounter
            // 
            this.textBoxRestoreNwkFrameCounter.Location = new System.Drawing.Point(838, 327);
            this.textBoxRestoreNwkFrameCounter.Name = "textBoxRestoreNwkFrameCounter";
            this.textBoxRestoreNwkFrameCounter.Size = new System.Drawing.Size(163, 20);
            this.textBoxRestoreNwkFrameCounter.TabIndex = 87;
            this.textBoxRestoreNwkFrameCounter.Visible = false;
            this.textBoxRestoreNwkFrameCounter.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRestoreNwkFrameCounter_MouseClick);
            this.textBoxRestoreNwkFrameCounter.MouseLeave += new System.EventHandler(this.textBoxRestoreNwkFrameCounter_MouseLeave);
            this.textBoxRestoreNwkFrameCounter.MouseHover += new System.EventHandler(this.textBoxRestoreNwkFrameCounter_MouseHover);
            // 
            // comboBoxLeaveChildren
            // 
            this.comboBoxLeaveChildren.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxLeaveChildren.FormattingEnabled = true;
            this.comboBoxLeaveChildren.Location = new System.Drawing.Point(434, 182);
            this.comboBoxLeaveChildren.Name = "comboBoxLeaveChildren";
            this.comboBoxLeaveChildren.Size = new System.Drawing.Size(196, 21);
            this.comboBoxLeaveChildren.TabIndex = 26;
            // 
            // comboBoxLeaveReJoin
            // 
            this.comboBoxLeaveReJoin.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxLeaveReJoin.FormattingEnabled = true;
            this.comboBoxLeaveReJoin.Location = new System.Drawing.Point(308, 182);
            this.comboBoxLeaveReJoin.Name = "comboBoxLeaveReJoin";
            this.comboBoxLeaveReJoin.Size = new System.Drawing.Size(119, 21);
            this.comboBoxLeaveReJoin.TabIndex = 25;
            // 
            // textBoxLeaveAddr
            // 
            this.textBoxLeaveAddr.Location = new System.Drawing.Point(93, 182);
            this.textBoxLeaveAddr.Name = "textBoxLeaveAddr";
            this.textBoxLeaveAddr.Size = new System.Drawing.Size(209, 20);
            this.textBoxLeaveAddr.TabIndex = 24;
            this.textBoxLeaveAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxLeaveAddr_MouseClick);
            this.textBoxLeaveAddr.Leave += new System.EventHandler(this.textBoxLeaveAddr_Leave);
            this.textBoxLeaveAddr.MouseLeave += new System.EventHandler(this.textBoxLeaveAddr_MouseLeave);
            this.textBoxLeaveAddr.MouseHover += new System.EventHandler(this.textBoxLeaveAddr_MouseHover);
            // 
            // buttonLeave
            // 
            this.buttonLeave.Location = new System.Drawing.Point(6, 180);
            this.buttonLeave.Name = "buttonLeave";
            this.buttonLeave.Size = new System.Drawing.Size(80, 22);
            this.buttonLeave.TabIndex = 23;
            this.buttonLeave.Text = "Leave";
            this.buttonLeave.UseVisualStyleBackColor = true;
            this.buttonLeave.Click += new System.EventHandler(this.buttonLeave_Click);
            // 
            // textBoxRemoveChildAddr
            // 
            this.textBoxRemoveChildAddr.Location = new System.Drawing.Point(321, 212);
            this.textBoxRemoveChildAddr.Name = "textBoxRemoveChildAddr";
            this.textBoxRemoveChildAddr.Size = new System.Drawing.Size(219, 20);
            this.textBoxRemoveChildAddr.TabIndex = 29;
            this.textBoxRemoveChildAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveChildAddr_MouseClick);
            this.textBoxRemoveChildAddr.Leave += new System.EventHandler(this.textBoxRemoveChildAddr_Leave);
            this.textBoxRemoveChildAddr.MouseLeave += new System.EventHandler(this.textBoxRemoveChildAddr_MouseLeave);
            this.textBoxRemoveChildAddr.MouseHover += new System.EventHandler(this.textBoxRemoveChildAddr_MouseHover);
            // 
            // textBoxRemoveParentAddr
            // 
            this.textBoxRemoveParentAddr.Location = new System.Drawing.Point(93, 212);
            this.textBoxRemoveParentAddr.Name = "textBoxRemoveParentAddr";
            this.textBoxRemoveParentAddr.Size = new System.Drawing.Size(219, 20);
            this.textBoxRemoveParentAddr.TabIndex = 28;
            this.textBoxRemoveParentAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveParentAddr_MouseClick);
            this.textBoxRemoveParentAddr.Leave += new System.EventHandler(this.textBoxRemoveParentAddr_Leave);
            this.textBoxRemoveParentAddr.MouseLeave += new System.EventHandler(this.textBoxRemoveParentAddr_MouseLeave);
            this.textBoxRemoveParentAddr.MouseHover += new System.EventHandler(this.textBoxRemoveParentAddr_MouseHover);
            // 
            // buttonRemoveDevice
            // 
            this.buttonRemoveDevice.Location = new System.Drawing.Point(6, 210);
            this.buttonRemoveDevice.Name = "buttonRemoveDevice";
            this.buttonRemoveDevice.Size = new System.Drawing.Size(80, 22);
            this.buttonRemoveDevice.TabIndex = 27;
            this.buttonRemoveDevice.Text = "Remove";
            this.buttonRemoveDevice.UseVisualStyleBackColor = true;
            this.buttonRemoveDevice.Click += new System.EventHandler(this.buttonRemoveDevice_Click);
            // 
            // buttonPermitJoinState
            // 
            this.buttonPermitJoinState.Location = new System.Drawing.Point(6, 267);
            this.buttonPermitJoinState.Name = "buttonPermitJoinState";
            this.buttonPermitJoinState.Size = new System.Drawing.Size(105, 22);
            this.buttonPermitJoinState.TabIndex = 34;
            this.buttonPermitJoinState.Text = "Permit Join State";
            this.buttonPermitJoinState.UseVisualStyleBackColor = true;
            this.buttonPermitJoinState.Click += new System.EventHandler(this.buttonPermitJoinState_Click);
            // 
            // buttonRestoreNwk
            // 
            this.buttonRestoreNwk.Location = new System.Drawing.Point(752, 324);
            this.buttonRestoreNwk.Name = "buttonRestoreNwk";
            this.buttonRestoreNwk.Size = new System.Drawing.Size(80, 22);
            this.buttonRestoreNwk.TabIndex = 86;
            this.buttonRestoreNwk.Text = "RES NWK";
            this.buttonRestoreNwk.UseVisualStyleBackColor = true;
            this.buttonRestoreNwk.Visible = false;
            this.buttonRestoreNwk.Click += new System.EventHandler(this.buttonRestoreNwk_Click);
            // 
            // buttonRecoverNwk
            // 
            this.buttonRecoverNwk.Location = new System.Drawing.Point(752, 295);
            this.buttonRecoverNwk.Name = "buttonRecoverNwk";
            this.buttonRecoverNwk.Size = new System.Drawing.Size(80, 22);
            this.buttonRecoverNwk.TabIndex = 85;
            this.buttonRecoverNwk.Text = "REC NWK";
            this.buttonRecoverNwk.UseVisualStyleBackColor = true;
            this.buttonRecoverNwk.Visible = false;
            this.buttonRecoverNwk.Click += new System.EventHandler(this.buttonRecoverNwk_Click);
            // 
            // comboBoxMgmtLeaveChildren
            // 
            this.comboBoxMgmtLeaveChildren.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxMgmtLeaveChildren.FormattingEnabled = true;
            this.comboBoxMgmtLeaveChildren.Location = new System.Drawing.Point(547, 154);
            this.comboBoxMgmtLeaveChildren.Name = "comboBoxMgmtLeaveChildren";
            this.comboBoxMgmtLeaveChildren.Size = new System.Drawing.Size(196, 21);
            this.comboBoxMgmtLeaveChildren.TabIndex = 22;
            // 
            // comboBoxMgmtLeaveReJoin
            // 
            this.comboBoxMgmtLeaveReJoin.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxMgmtLeaveReJoin.FormattingEnabled = true;
            this.comboBoxMgmtLeaveReJoin.Location = new System.Drawing.Point(422, 154);
            this.comboBoxMgmtLeaveReJoin.Name = "comboBoxMgmtLeaveReJoin";
            this.comboBoxMgmtLeaveReJoin.Size = new System.Drawing.Size(119, 21);
            this.comboBoxMgmtLeaveReJoin.TabIndex = 21;
            // 
            // textBoxMgmtLeaveExtAddr
            // 
            this.textBoxMgmtLeaveExtAddr.Location = new System.Drawing.Point(206, 154);
            this.textBoxMgmtLeaveExtAddr.Name = "textBoxMgmtLeaveExtAddr";
            this.textBoxMgmtLeaveExtAddr.Size = new System.Drawing.Size(209, 20);
            this.textBoxMgmtLeaveExtAddr.TabIndex = 20;
            this.textBoxMgmtLeaveExtAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMgmtLeaveExtAddr_MouseClick);
            this.textBoxMgmtLeaveExtAddr.Leave += new System.EventHandler(this.textBoxMgmtLeaveExtAddr_Leave);
            this.textBoxMgmtLeaveExtAddr.MouseLeave += new System.EventHandler(this.textBoxMgmtLeaveExtAddr_MouseLeave);
            this.textBoxMgmtLeaveExtAddr.MouseHover += new System.EventHandler(this.textBoxMgmtLeaveExtAddr_MouseHover);
            // 
            // textBoxMgmtLeaveAddr
            // 
            this.textBoxMgmtLeaveAddr.Location = new System.Drawing.Point(93, 154);
            this.textBoxMgmtLeaveAddr.Name = "textBoxMgmtLeaveAddr";
            this.textBoxMgmtLeaveAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxMgmtLeaveAddr.TabIndex = 19;
            this.textBoxMgmtLeaveAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMgmtLeaveAddr_MouseClick);
            this.textBoxMgmtLeaveAddr.Leave += new System.EventHandler(this.textBoxMgmtLeaveAddr_Leave);
            this.textBoxMgmtLeaveAddr.MouseLeave += new System.EventHandler(this.textBoxMgmtLeaveAddr_MouseLeave);
            this.textBoxMgmtLeaveAddr.MouseHover += new System.EventHandler(this.textBoxMgmtLeaveAddr_MouseHover);
            // 
            // buttonMgmtLeave
            // 
            this.buttonMgmtLeave.Location = new System.Drawing.Point(6, 152);
            this.buttonMgmtLeave.Name = "buttonMgmtLeave";
            this.buttonMgmtLeave.Size = new System.Drawing.Size(80, 22);
            this.buttonMgmtLeave.TabIndex = 18;
            this.buttonMgmtLeave.Text = "Mgmt Leave";
            this.buttonMgmtLeave.UseVisualStyleBackColor = true;
            this.buttonMgmtLeave.Click += new System.EventHandler(this.buttonMgmtLeave_Click);
            // 
            // textBoxUnBindDestEP
            // 
            this.textBoxUnBindDestEP.Location = new System.Drawing.Point(652, 351);
            this.textBoxUnBindDestEP.Name = "textBoxUnBindDestEP";
            this.textBoxUnBindDestEP.Size = new System.Drawing.Size(88, 20);
            this.textBoxUnBindDestEP.TabIndex = 55;
            this.textBoxUnBindDestEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxUnBindDestEP_MouseClick);
            this.textBoxUnBindDestEP.Leave += new System.EventHandler(this.textBoxUnBindDestEP_Leave);
            this.textBoxUnBindDestEP.MouseLeave += new System.EventHandler(this.textBoxUnBindDestEP_MouseLeave);
            this.textBoxUnBindDestEP.MouseHover += new System.EventHandler(this.textBoxUnBindDestEP_MouseHover);
            // 
            // textBoxUnBindDestAddr
            // 
            this.textBoxUnBindDestAddr.Location = new System.Drawing.Point(411, 351);
            this.textBoxUnBindDestAddr.Name = "textBoxUnBindDestAddr";
            this.textBoxUnBindDestAddr.Size = new System.Drawing.Size(133, 20);
            this.textBoxUnBindDestAddr.TabIndex = 53;
            this.textBoxUnBindDestAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxUnBindDestAddr_MouseClick);
            this.textBoxUnBindDestAddr.Leave += new System.EventHandler(this.textBoxUnBindDestAddr_Leave);
            this.textBoxUnBindDestAddr.MouseLeave += new System.EventHandler(this.textBoxUnBindDestAddr_MouseLeave);
            this.textBoxUnBindDestAddr.MouseHover += new System.EventHandler(this.textBoxUnBindDestAddr_MouseHover);
            // 
            // comboBoxUnBindAddrMode
            // 
            this.comboBoxUnBindAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxUnBindAddrMode.FormattingEnabled = true;
            this.comboBoxUnBindAddrMode.Location = new System.Drawing.Point(322, 351);
            this.comboBoxUnBindAddrMode.Name = "comboBoxUnBindAddrMode";
            this.comboBoxUnBindAddrMode.Size = new System.Drawing.Size(84, 21);
            this.comboBoxUnBindAddrMode.TabIndex = 52;
            this.comboBoxUnBindAddrMode.MouseLeave += new System.EventHandler(this.comboBoxUnBindAddrMode_MouseLeave);
            this.comboBoxUnBindAddrMode.MouseHover += new System.EventHandler(this.comboBoxUnBindAddrMode_MouseHover);
            // 
            // textBoxUnBindClusterID
            // 
            this.textBoxUnBindClusterID.Location = new System.Drawing.Point(550, 351);
            this.textBoxUnBindClusterID.Name = "textBoxUnBindClusterID";
            this.textBoxUnBindClusterID.Size = new System.Drawing.Size(96, 20);
            this.textBoxUnBindClusterID.TabIndex = 54;
            this.textBoxUnBindClusterID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxUnBindClusterID_MouseClick);
            this.textBoxUnBindClusterID.Leave += new System.EventHandler(this.textBoxUnBindClusterID_Leave);
            this.textBoxUnBindClusterID.MouseLeave += new System.EventHandler(this.textBoxUnBindClusterID_MouseLeave);
            this.textBoxUnBindClusterID.MouseHover += new System.EventHandler(this.textBoxUnBindClusterID_MouseHover);
            // 
            // textBoxUnBindTargetEP
            // 
            this.textBoxUnBindTargetEP.Location = new System.Drawing.Point(228, 351);
            this.textBoxUnBindTargetEP.Name = "textBoxUnBindTargetEP";
            this.textBoxUnBindTargetEP.Size = new System.Drawing.Size(84, 20);
            this.textBoxUnBindTargetEP.TabIndex = 51;
            this.textBoxUnBindTargetEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxUnBindTargetEP_MouseClick);
            this.textBoxUnBindTargetEP.Leave += new System.EventHandler(this.textBoxUnBindTargetEP_Leave);
            this.textBoxUnBindTargetEP.MouseLeave += new System.EventHandler(this.textBoxUnBindTargetEP_MouseLeave);
            this.textBoxUnBindTargetEP.MouseHover += new System.EventHandler(this.textBoxUnBindTargetEP_MouseHover);
            // 
            // textBoxUnBindTargetExtAddr
            // 
            this.textBoxUnBindTargetExtAddr.Location = new System.Drawing.Point(93, 353);
            this.textBoxUnBindTargetExtAddr.Name = "textBoxUnBindTargetExtAddr";
            this.textBoxUnBindTargetExtAddr.Size = new System.Drawing.Size(129, 20);
            this.textBoxUnBindTargetExtAddr.TabIndex = 50;
            this.textBoxUnBindTargetExtAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxUnBindTargetExtAddr_MouseClick);
            this.textBoxUnBindTargetExtAddr.Leave += new System.EventHandler(this.textBoxUnBindTargetExtAddr_Leave);
            this.textBoxUnBindTargetExtAddr.MouseLeave += new System.EventHandler(this.textBoxUnBindTargetExtAddr_MouseLeave);
            this.textBoxUnBindTargetExtAddr.MouseHover += new System.EventHandler(this.textBoxUnBindTargetExtAddr_MouseHover);
            // 
            // buttonUnBind
            // 
            this.buttonUnBind.Location = new System.Drawing.Point(6, 351);
            this.buttonUnBind.Name = "buttonUnBind";
            this.buttonUnBind.Size = new System.Drawing.Size(80, 25);
            this.buttonUnBind.TabIndex = 49;
            this.buttonUnBind.Text = "UnBind";
            this.buttonUnBind.UseVisualStyleBackColor = true;
            this.buttonUnBind.Click += new System.EventHandler(this.buttonUnBind_Click);
            // 
            // textBoxBindDestEP
            // 
            this.textBoxBindDestEP.Location = new System.Drawing.Point(652, 327);
            this.textBoxBindDestEP.Name = "textBoxBindDestEP";
            this.textBoxBindDestEP.Size = new System.Drawing.Size(88, 20);
            this.textBoxBindDestEP.TabIndex = 48;
            this.textBoxBindDestEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxBindDestEP_MouseClick);
            this.textBoxBindDestEP.Leave += new System.EventHandler(this.textBoxBindDestEP_Leave);
            this.textBoxBindDestEP.MouseLeave += new System.EventHandler(this.textBoxBindDestEP_MouseLeave);
            this.textBoxBindDestEP.MouseHover += new System.EventHandler(this.textBoxBindDestEP_MouseHover);
            // 
            // textBoxBindDestAddr
            // 
            this.textBoxBindDestAddr.Location = new System.Drawing.Point(411, 326);
            this.textBoxBindDestAddr.Name = "textBoxBindDestAddr";
            this.textBoxBindDestAddr.Size = new System.Drawing.Size(133, 20);
            this.textBoxBindDestAddr.TabIndex = 46;
            this.textBoxBindDestAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxBindDestAddr_MouseClick);
            this.textBoxBindDestAddr.Leave += new System.EventHandler(this.textBoxBindDestAddr_Leave);
            this.textBoxBindDestAddr.MouseLeave += new System.EventHandler(this.textBoxBindDestAddr_MouseLeave);
            this.textBoxBindDestAddr.MouseHover += new System.EventHandler(this.textBoxBindDestAddr_MouseHover);
            // 
            // comboBoxBindAddrMode
            // 
            this.comboBoxBindAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxBindAddrMode.FormattingEnabled = true;
            this.comboBoxBindAddrMode.Location = new System.Drawing.Point(322, 326);
            this.comboBoxBindAddrMode.Name = "comboBoxBindAddrMode";
            this.comboBoxBindAddrMode.Size = new System.Drawing.Size(84, 21);
            this.comboBoxBindAddrMode.TabIndex = 45;
            this.comboBoxBindAddrMode.MouseLeave += new System.EventHandler(this.comboBoxBindAddrMode_MouseLeave);
            this.comboBoxBindAddrMode.MouseHover += new System.EventHandler(this.comboBoxBindAddrMode_MouseHover);
            // 
            // textBoxBindClusterID
            // 
            this.textBoxBindClusterID.Location = new System.Drawing.Point(550, 327);
            this.textBoxBindClusterID.Name = "textBoxBindClusterID";
            this.textBoxBindClusterID.Size = new System.Drawing.Size(96, 20);
            this.textBoxBindClusterID.TabIndex = 47;
            this.textBoxBindClusterID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxBindClusterID_MouseClick);
            this.textBoxBindClusterID.Leave += new System.EventHandler(this.textBoxBindClusterID_Leave);
            this.textBoxBindClusterID.MouseLeave += new System.EventHandler(this.textBoxBindClusterID_MouseLeave);
            this.textBoxBindClusterID.MouseHover += new System.EventHandler(this.textBoxBindClusterID_MouseHover);
            // 
            // textBoxBindTargetEP
            // 
            this.textBoxBindTargetEP.Location = new System.Drawing.Point(228, 326);
            this.textBoxBindTargetEP.Name = "textBoxBindTargetEP";
            this.textBoxBindTargetEP.Size = new System.Drawing.Size(84, 20);
            this.textBoxBindTargetEP.TabIndex = 44;
            this.textBoxBindTargetEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxBindTargetEP_MouseClick);
            this.textBoxBindTargetEP.Leave += new System.EventHandler(this.textBoxBindTargetEP_Leave);
            this.textBoxBindTargetEP.MouseLeave += new System.EventHandler(this.textBoxBindTargetEP_MouseLeave);
            this.textBoxBindTargetEP.MouseHover += new System.EventHandler(this.textBoxBindTargetEP_MouseHover);
            // 
            // textBoxLqiReqStartIndex
            // 
            this.textBoxLqiReqStartIndex.Location = new System.Drawing.Point(951, 268);
            this.textBoxLqiReqStartIndex.Name = "textBoxLqiReqStartIndex";
            this.textBoxLqiReqStartIndex.Size = new System.Drawing.Size(106, 20);
            this.textBoxLqiReqStartIndex.TabIndex = 84;
            this.textBoxLqiReqStartIndex.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxLqiReqStartIndex_MouseClick);
            this.textBoxLqiReqStartIndex.Leave += new System.EventHandler(this.textBoxLqiReqStartIndex_Leave);
            this.textBoxLqiReqStartIndex.MouseLeave += new System.EventHandler(this.textBoxLqiReqStartIndex_MouseLeave);
            this.textBoxLqiReqStartIndex.MouseHover += new System.EventHandler(this.textBoxLqiReqStartIndex_MouseHover);
            // 
            // textBoxLqiReqTargetAddr
            // 
            this.textBoxLqiReqTargetAddr.Location = new System.Drawing.Point(838, 269);
            this.textBoxLqiReqTargetAddr.Name = "textBoxLqiReqTargetAddr";
            this.textBoxLqiReqTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxLqiReqTargetAddr.TabIndex = 83;
            this.textBoxLqiReqTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxLqiReqTargetAddr_MouseClick);
            this.textBoxLqiReqTargetAddr.Leave += new System.EventHandler(this.textBoxLqiReqTargetAddr_Leave);
            this.textBoxLqiReqTargetAddr.MouseLeave += new System.EventHandler(this.textBoxLqiReqTargetAddr_MouseLeave);
            this.textBoxLqiReqTargetAddr.MouseHover += new System.EventHandler(this.textBoxLqiReqTargetAddr_MouseHover);
            // 
            // buttonMgmtLqiReq
            // 
            this.buttonMgmtLqiReq.Location = new System.Drawing.Point(752, 267);
            this.buttonMgmtLqiReq.Name = "buttonMgmtLqiReq";
            this.buttonMgmtLqiReq.Size = new System.Drawing.Size(80, 22);
            this.buttonMgmtLqiReq.TabIndex = 82;
            this.buttonMgmtLqiReq.Text = "Lqi Req";
            this.buttonMgmtLqiReq.UseVisualStyleBackColor = true;
            this.buttonMgmtLqiReq.Click += new System.EventHandler(this.buttonMgmtLqiReq_Click_1);
            // 
            // buttonStartScan
            // 
            this.buttonStartScan.Location = new System.Drawing.Point(352, 6);
            this.buttonStartScan.Name = "buttonStartScan";
            this.buttonStartScan.Size = new System.Drawing.Size(80, 22);
            this.buttonStartScan.TabIndex = 5;
            this.buttonStartScan.Text = "Start Scan";
            this.buttonStartScan.UseVisualStyleBackColor = true;
            this.buttonStartScan.Click += new System.EventHandler(this.buttonStartScan_Click);
            // 
            // textBoxNwkAddrReqStartIndex
            // 
            this.textBoxNwkAddrReqStartIndex.Location = new System.Drawing.Point(1200, 64);
            this.textBoxNwkAddrReqStartIndex.Name = "textBoxNwkAddrReqStartIndex";
            this.textBoxNwkAddrReqStartIndex.Size = new System.Drawing.Size(106, 20);
            this.textBoxNwkAddrReqStartIndex.TabIndex = 67;
            this.textBoxNwkAddrReqStartIndex.Leave += new System.EventHandler(this.textBoxNwkAddrReqStartIndex_Leave);
            this.textBoxNwkAddrReqStartIndex.MouseLeave += new System.EventHandler(this.textBoxNwkAddrReqStartIndex_MouseLeave);
            this.textBoxNwkAddrReqStartIndex.MouseHover += new System.EventHandler(this.textBoxNwkAddrReqStartIndex_MouseHover);
            // 
            // comboBoxNwkAddrReqType
            // 
            this.comboBoxNwkAddrReqType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxNwkAddrReqType.FormattingEnabled = true;
            this.comboBoxNwkAddrReqType.Location = new System.Drawing.Point(1065, 64);
            this.comboBoxNwkAddrReqType.Name = "comboBoxNwkAddrReqType";
            this.comboBoxNwkAddrReqType.Size = new System.Drawing.Size(129, 21);
            this.comboBoxNwkAddrReqType.TabIndex = 66;
            // 
            // textBoxNwkAddrReqExtAddr
            // 
            this.textBoxNwkAddrReqExtAddr.Location = new System.Drawing.Point(951, 65);
            this.textBoxNwkAddrReqExtAddr.Name = "textBoxNwkAddrReqExtAddr";
            this.textBoxNwkAddrReqExtAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxNwkAddrReqExtAddr.TabIndex = 65;
            this.textBoxNwkAddrReqExtAddr.Leave += new System.EventHandler(this.textBoxNwkAddrReqExtAddr_Leave);
            this.textBoxNwkAddrReqExtAddr.MouseLeave += new System.EventHandler(this.textBoxNwkAddrReqExtAddr_MouseLeave);
            this.textBoxNwkAddrReqExtAddr.MouseHover += new System.EventHandler(this.textBoxNwkAddrReqExtAddr_MouseHover);
            // 
            // textBoxNwkAddrReqTargetAddr
            // 
            this.textBoxNwkAddrReqTargetAddr.Location = new System.Drawing.Point(838, 65);
            this.textBoxNwkAddrReqTargetAddr.Name = "textBoxNwkAddrReqTargetAddr";
            this.textBoxNwkAddrReqTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxNwkAddrReqTargetAddr.TabIndex = 64;
            this.textBoxNwkAddrReqTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxNwkAddrReqTargetAddr_MouseClick);
            this.textBoxNwkAddrReqTargetAddr.Leave += new System.EventHandler(this.textBoxNwkAddrReqTargetAddr_Leave);
            this.textBoxNwkAddrReqTargetAddr.MouseLeave += new System.EventHandler(this.textBoxNwkAddrReqTargetAddr_MouseLeave);
            this.textBoxNwkAddrReqTargetAddr.MouseHover += new System.EventHandler(this.textBoxNwkAddrReqTargetAddr_MouseHover);
            // 
            // textBoxIeeeReqStartIndex
            // 
            this.textBoxIeeeReqStartIndex.Location = new System.Drawing.Point(1200, 35);
            this.textBoxIeeeReqStartIndex.Name = "textBoxIeeeReqStartIndex";
            this.textBoxIeeeReqStartIndex.Size = new System.Drawing.Size(106, 20);
            this.textBoxIeeeReqStartIndex.TabIndex = 62;
            this.textBoxIeeeReqStartIndex.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxIeeeReqStartIndex_MouseClick);
            this.textBoxIeeeReqStartIndex.Leave += new System.EventHandler(this.textBoxIeeeReqStartIndex_Leave);
            this.textBoxIeeeReqStartIndex.MouseLeave += new System.EventHandler(this.textBoxIeeeReqStartIndex_MouseLeave);
            this.textBoxIeeeReqStartIndex.MouseHover += new System.EventHandler(this.textBoxIeeeReqStartIndex_MouseHover);
            // 
            // comboBoxIeeeReqType
            // 
            this.comboBoxIeeeReqType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxIeeeReqType.FormattingEnabled = true;
            this.comboBoxIeeeReqType.Location = new System.Drawing.Point(1065, 35);
            this.comboBoxIeeeReqType.Name = "comboBoxIeeeReqType";
            this.comboBoxIeeeReqType.Size = new System.Drawing.Size(129, 21);
            this.comboBoxIeeeReqType.TabIndex = 61;
            // 
            // textBoxIeeeReqAddr
            // 
            this.textBoxIeeeReqAddr.Location = new System.Drawing.Point(951, 37);
            this.textBoxIeeeReqAddr.Name = "textBoxIeeeReqAddr";
            this.textBoxIeeeReqAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxIeeeReqAddr.TabIndex = 60;
            this.textBoxIeeeReqAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxIeeeReqAddr_MouseClick);
            this.textBoxIeeeReqAddr.Leave += new System.EventHandler(this.textBoxIeeeReqAddr_Leave);
            this.textBoxIeeeReqAddr.MouseLeave += new System.EventHandler(this.textBoxIeeeReqAddr_MouseLeave);
            this.textBoxIeeeReqAddr.MouseHover += new System.EventHandler(this.textBoxIeeeReqAddr_MouseHover);
            // 
            // textBoxIeeeReqTargetAddr
            // 
            this.textBoxIeeeReqTargetAddr.Location = new System.Drawing.Point(838, 37);
            this.textBoxIeeeReqTargetAddr.Name = "textBoxIeeeReqTargetAddr";
            this.textBoxIeeeReqTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxIeeeReqTargetAddr.TabIndex = 59;
            this.textBoxIeeeReqTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxIeeeReqTargetAddr_MouseClick);
            this.textBoxIeeeReqTargetAddr.Leave += new System.EventHandler(this.textBoxIeeeReqTargetAddr_Leave);
            this.textBoxIeeeReqTargetAddr.MouseLeave += new System.EventHandler(this.textBoxIeeeReqTargetAddr_MouseLeave);
            this.textBoxIeeeReqTargetAddr.MouseHover += new System.EventHandler(this.textBoxIeeeReqTargetAddr_MouseHover);
            // 
            // textBoxComplexReqAddr
            // 
            this.textBoxComplexReqAddr.Location = new System.Drawing.Point(838, 182);
            this.textBoxComplexReqAddr.Name = "textBoxComplexReqAddr";
            this.textBoxComplexReqAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxComplexReqAddr.TabIndex = 76;
            this.textBoxComplexReqAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxComplexReqAddr_MouseClick);
            this.textBoxComplexReqAddr.Leave += new System.EventHandler(this.textBoxComplexReqAddr_Leave);
            this.textBoxComplexReqAddr.MouseLeave += new System.EventHandler(this.textBoxComplexReqAddr_MouseLeave);
            this.textBoxComplexReqAddr.MouseHover += new System.EventHandler(this.textBoxComplexReqAddr_MouseHover);
            // 
            // buttonComplexReq
            // 
            this.buttonComplexReq.Location = new System.Drawing.Point(752, 180);
            this.buttonComplexReq.Name = "buttonComplexReq";
            this.buttonComplexReq.Size = new System.Drawing.Size(80, 22);
            this.buttonComplexReq.TabIndex = 75;
            this.buttonComplexReq.Text = "ComplexReq";
            this.buttonComplexReq.UseVisualStyleBackColor = true;
            this.buttonComplexReq.Click += new System.EventHandler(this.buttonComplexReq_Click);
            // 
            // textBoxMatchReqOutputClusters
            // 
            this.textBoxMatchReqOutputClusters.Location = new System.Drawing.Point(637, 298);
            this.textBoxMatchReqOutputClusters.Name = "textBoxMatchReqOutputClusters";
            this.textBoxMatchReqOutputClusters.Size = new System.Drawing.Size(103, 20);
            this.textBoxMatchReqOutputClusters.TabIndex = 41;
            this.textBoxMatchReqOutputClusters.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMatchReqOutputClusters_MouseClick);
            this.textBoxMatchReqOutputClusters.Leave += new System.EventHandler(this.textBoxMatchReqOutputClusters_Leave);
            this.textBoxMatchReqOutputClusters.MouseLeave += new System.EventHandler(this.textBoxMatchReqOutputClusters_MouseLeave);
            this.textBoxMatchReqOutputClusters.MouseHover += new System.EventHandler(this.textBoxMatchReqOutputClusters_MouseHover);
            // 
            // textBoxMatchReqInputClusters
            // 
            this.textBoxMatchReqInputClusters.Location = new System.Drawing.Point(422, 298);
            this.textBoxMatchReqInputClusters.Name = "textBoxMatchReqInputClusters";
            this.textBoxMatchReqInputClusters.Size = new System.Drawing.Size(106, 20);
            this.textBoxMatchReqInputClusters.TabIndex = 39;
            this.textBoxMatchReqInputClusters.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMatchReqInputClusters_MouseClick);
            this.textBoxMatchReqInputClusters.Leave += new System.EventHandler(this.textBoxMatchReqInputClusters_Leave);
            this.textBoxMatchReqInputClusters.MouseLeave += new System.EventHandler(this.textBoxMatchReqInputClusters_MouseLeave);
            this.textBoxMatchReqInputClusters.MouseHover += new System.EventHandler(this.textBoxMatchReqInputClusters_MouseHover);
            // 
            // textBoxMatchReqProfileID
            // 
            this.textBoxMatchReqProfileID.Location = new System.Drawing.Point(206, 298);
            this.textBoxMatchReqProfileID.Name = "textBoxMatchReqProfileID";
            this.textBoxMatchReqProfileID.Size = new System.Drawing.Size(106, 20);
            this.textBoxMatchReqProfileID.TabIndex = 37;
            this.textBoxMatchReqProfileID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMatchReqProfileID_MouseClick);
            this.textBoxMatchReqProfileID.Leave += new System.EventHandler(this.textBoxMatchReqProfileID_Leave);
            this.textBoxMatchReqProfileID.MouseLeave += new System.EventHandler(this.textBoxMatchReqProfileID_MouseLeave);
            this.textBoxMatchReqProfileID.MouseHover += new System.EventHandler(this.textBoxMatchReqProfileID_MouseHover);
            // 
            // textBoxMatchReqNbrOutputClusters
            // 
            this.textBoxMatchReqNbrOutputClusters.Location = new System.Drawing.Point(534, 298);
            this.textBoxMatchReqNbrOutputClusters.Name = "textBoxMatchReqNbrOutputClusters";
            this.textBoxMatchReqNbrOutputClusters.Size = new System.Drawing.Size(96, 20);
            this.textBoxMatchReqNbrOutputClusters.TabIndex = 40;
            this.textBoxMatchReqNbrOutputClusters.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMatchReqNbrOutputClusters_MouseClick);
            this.textBoxMatchReqNbrOutputClusters.Leave += new System.EventHandler(this.textBoxMatchReqNbrOutputClusters_Leave);
            this.textBoxMatchReqNbrOutputClusters.MouseLeave += new System.EventHandler(this.textBoxMatchReqNbrOutputClusters_MouseLeave);
            this.textBoxMatchReqNbrOutputClusters.MouseHover += new System.EventHandler(this.textBoxMatchReqNbrOutputClusters_MouseHover);
            // 
            // textBoxMatchReqNbrInputClusters
            // 
            this.textBoxMatchReqNbrInputClusters.Location = new System.Drawing.Point(319, 298);
            this.textBoxMatchReqNbrInputClusters.Name = "textBoxMatchReqNbrInputClusters";
            this.textBoxMatchReqNbrInputClusters.Size = new System.Drawing.Size(96, 20);
            this.textBoxMatchReqNbrInputClusters.TabIndex = 38;
            this.textBoxMatchReqNbrInputClusters.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMatchReqNbrInputClusters_MouseClick);
            this.textBoxMatchReqNbrInputClusters.Leave += new System.EventHandler(this.textBoxMatchReqNbrInputClusters_Leave);
            this.textBoxMatchReqNbrInputClusters.MouseLeave += new System.EventHandler(this.textBoxMatchReqNbrInputClusters_MouseLeave);
            this.textBoxMatchReqNbrInputClusters.MouseHover += new System.EventHandler(this.textBoxMatchReqNbrInputClusters_MouseHover);
            // 
            // textBoxMatchReqAddr
            // 
            this.textBoxMatchReqAddr.Location = new System.Drawing.Point(93, 298);
            this.textBoxMatchReqAddr.Name = "textBoxMatchReqAddr";
            this.textBoxMatchReqAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxMatchReqAddr.TabIndex = 36;
            this.textBoxMatchReqAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMatchReqAddr_MouseClick);
            this.textBoxMatchReqAddr.Leave += new System.EventHandler(this.textBoxMatchReqAddr_Leave);
            this.textBoxMatchReqAddr.MouseLeave += new System.EventHandler(this.textBoxMatchReqAddr_MouseLeave);
            this.textBoxMatchReqAddr.MouseHover += new System.EventHandler(this.textBoxMatchReqAddr_MouseHover);
            // 
            // textBoxActiveEpAddr
            // 
            this.textBoxActiveEpAddr.Location = new System.Drawing.Point(838, 8);
            this.textBoxActiveEpAddr.Name = "textBoxActiveEpAddr";
            this.textBoxActiveEpAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxActiveEpAddr.TabIndex = 57;
            this.textBoxActiveEpAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxActiveEpAddr_MouseClick);
            this.textBoxActiveEpAddr.Leave += new System.EventHandler(this.textBoxActiveEpAddr_Leave);
            this.textBoxActiveEpAddr.MouseLeave += new System.EventHandler(this.textBoxActiveEpAddr_MouseLeave);
            this.textBoxActiveEpAddr.MouseHover += new System.EventHandler(this.textBoxActiveEpAddr_MouseHover);
            // 
            // textBoxPowerReqAddr
            // 
            this.textBoxPowerReqAddr.Location = new System.Drawing.Point(838, 124);
            this.textBoxPowerReqAddr.Name = "textBoxPowerReqAddr";
            this.textBoxPowerReqAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxPowerReqAddr.TabIndex = 71;
            this.textBoxPowerReqAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxPowerReqAddr_MouseClick);
            this.textBoxPowerReqAddr.Leave += new System.EventHandler(this.textBoxPowerReqAddr_Leave);
            this.textBoxPowerReqAddr.MouseLeave += new System.EventHandler(this.textBoxPowerReqAddr_MouseLeave);
            this.textBoxPowerReqAddr.MouseHover += new System.EventHandler(this.textBoxPowerReqAddr_MouseHover);
            // 
            // textBoxSimpleReqEndPoint
            // 
            this.textBoxSimpleReqEndPoint.Location = new System.Drawing.Point(951, 153);
            this.textBoxSimpleReqEndPoint.Name = "textBoxSimpleReqEndPoint";
            this.textBoxSimpleReqEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxSimpleReqEndPoint.TabIndex = 74;
            this.textBoxSimpleReqEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxSimpleReqEndPoint_MouseClick);
            this.textBoxSimpleReqEndPoint.Leave += new System.EventHandler(this.textBoxSimpleReqEndPoint_Leave);
            this.textBoxSimpleReqEndPoint.MouseLeave += new System.EventHandler(this.textBoxSimpleReqEndPoint_MouseLeave);
            this.textBoxSimpleReqEndPoint.MouseHover += new System.EventHandler(this.textBoxSimpleReqEndPoint_MouseHover);
            // 
            // textBoxSimpleReqAddr
            // 
            this.textBoxSimpleReqAddr.Location = new System.Drawing.Point(838, 153);
            this.textBoxSimpleReqAddr.Name = "textBoxSimpleReqAddr";
            this.textBoxSimpleReqAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxSimpleReqAddr.TabIndex = 73;
            this.textBoxSimpleReqAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxSimpleReqAddr_MouseClick);
            this.textBoxSimpleReqAddr.Leave += new System.EventHandler(this.textBoxSimpleReqAddr_Leave);
            this.textBoxSimpleReqAddr.MouseLeave += new System.EventHandler(this.textBoxSimpleReqAddr_MouseLeave);
            this.textBoxSimpleReqAddr.MouseHover += new System.EventHandler(this.textBoxSimpleReqAddr_MouseHover);
            // 
            // buttonMatchReq
            // 
            this.buttonMatchReq.Location = new System.Drawing.Point(6, 295);
            this.buttonMatchReq.Name = "buttonMatchReq";
            this.buttonMatchReq.Size = new System.Drawing.Size(80, 22);
            this.buttonMatchReq.TabIndex = 35;
            this.buttonMatchReq.Text = "Match Req";
            this.buttonMatchReq.UseVisualStyleBackColor = true;
            this.buttonMatchReq.Click += new System.EventHandler(this.buttonMatchReq_Click);
            // 
            // buttonActiveEpReq
            // 
            this.buttonActiveEpReq.Location = new System.Drawing.Point(752, 6);
            this.buttonActiveEpReq.Name = "buttonActiveEpReq";
            this.buttonActiveEpReq.Size = new System.Drawing.Size(80, 22);
            this.buttonActiveEpReq.TabIndex = 56;
            this.buttonActiveEpReq.Text = "Active Req";
            this.buttonActiveEpReq.UseVisualStyleBackColor = true;
            this.buttonActiveEpReq.Click += new System.EventHandler(this.buttonActiveEpReq_Click);
            // 
            // buttonPowerDescReq
            // 
            this.buttonPowerDescReq.Location = new System.Drawing.Point(752, 122);
            this.buttonPowerDescReq.Name = "buttonPowerDescReq";
            this.buttonPowerDescReq.Size = new System.Drawing.Size(80, 22);
            this.buttonPowerDescReq.TabIndex = 70;
            this.buttonPowerDescReq.Text = "Power Req";
            this.buttonPowerDescReq.UseVisualStyleBackColor = true;
            this.buttonPowerDescReq.Click += new System.EventHandler(this.buttonPowerDescReq_Click);
            // 
            // buttonSimpleDescReq
            // 
            this.buttonSimpleDescReq.Location = new System.Drawing.Point(752, 150);
            this.buttonSimpleDescReq.Name = "buttonSimpleDescReq";
            this.buttonSimpleDescReq.Size = new System.Drawing.Size(80, 22);
            this.buttonSimpleDescReq.TabIndex = 72;
            this.buttonSimpleDescReq.Text = "Simple Req";
            this.buttonSimpleDescReq.UseVisualStyleBackColor = true;
            this.buttonSimpleDescReq.Click += new System.EventHandler(this.buttonSimpleDescReq_Click);
            // 
            // textBoxNodeDescReq
            // 
            this.textBoxNodeDescReq.Location = new System.Drawing.Point(838, 94);
            this.textBoxNodeDescReq.Name = "textBoxNodeDescReq";
            this.textBoxNodeDescReq.Size = new System.Drawing.Size(106, 20);
            this.textBoxNodeDescReq.TabIndex = 69;
            this.textBoxNodeDescReq.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxNodeDescReq_MouseClick);
            this.textBoxNodeDescReq.Leave += new System.EventHandler(this.textBoxNodeDescReq_Leave);
            this.textBoxNodeDescReq.MouseLeave += new System.EventHandler(this.textBoxNodeDescReq_MouseLeave);
            this.textBoxNodeDescReq.MouseHover += new System.EventHandler(this.textBoxNodeDescReq_MouseHover);
            // 
            // buttonNodeDescReq
            // 
            this.buttonNodeDescReq.Location = new System.Drawing.Point(752, 93);
            this.buttonNodeDescReq.Name = "buttonNodeDescReq";
            this.buttonNodeDescReq.Size = new System.Drawing.Size(80, 22);
            this.buttonNodeDescReq.TabIndex = 68;
            this.buttonNodeDescReq.Text = "Node Req";
            this.buttonNodeDescReq.UseVisualStyleBackColor = true;
            this.buttonNodeDescReq.Click += new System.EventHandler(this.buttonNodeDescReq_Click);
            // 
            // buttonIeeeAddrReq
            // 
            this.buttonIeeeAddrReq.Location = new System.Drawing.Point(752, 34);
            this.buttonIeeeAddrReq.Name = "buttonIeeeAddrReq";
            this.buttonIeeeAddrReq.Size = new System.Drawing.Size(80, 22);
            this.buttonIeeeAddrReq.TabIndex = 58;
            this.buttonIeeeAddrReq.Text = "IEEE Req";
            this.buttonIeeeAddrReq.UseVisualStyleBackColor = true;
            this.buttonIeeeAddrReq.Click += new System.EventHandler(this.buttonIeeeAddrReq_Click);
            // 
            // buttonNwkAddrReq
            // 
            this.buttonNwkAddrReq.Location = new System.Drawing.Point(752, 63);
            this.buttonNwkAddrReq.Name = "buttonNwkAddrReq";
            this.buttonNwkAddrReq.Size = new System.Drawing.Size(80, 22);
            this.buttonNwkAddrReq.TabIndex = 63;
            this.buttonNwkAddrReq.Text = "Addr Req";
            this.buttonNwkAddrReq.UseVisualStyleBackColor = true;
            this.buttonNwkAddrReq.Click += new System.EventHandler(this.buttonNwkAddrReq_Click);
            // 
            // comboBoxSecurityKey
            // 
            this.comboBoxSecurityKey.FormattingEnabled = true;
            this.comboBoxSecurityKey.Location = new System.Drawing.Point(512, 94);
            this.comboBoxSecurityKey.Name = "comboBoxSecurityKey";
            this.comboBoxSecurityKey.Size = new System.Drawing.Size(237, 21);
            this.comboBoxSecurityKey.TabIndex = 15;
            // 
            // comboBoxPermitJoinTCsignificance
            // 
            this.comboBoxPermitJoinTCsignificance.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxPermitJoinTCsignificance.FormattingEnabled = true;
            this.comboBoxPermitJoinTCsignificance.Location = new System.Drawing.Point(319, 238);
            this.comboBoxPermitJoinTCsignificance.Name = "comboBoxPermitJoinTCsignificance";
            this.comboBoxPermitJoinTCsignificance.Size = new System.Drawing.Size(129, 21);
            this.comboBoxPermitJoinTCsignificance.TabIndex = 33;
            // 
            // textBoxPermitJoinInterval
            // 
            this.textBoxPermitJoinInterval.Location = new System.Drawing.Point(206, 238);
            this.textBoxPermitJoinInterval.Name = "textBoxPermitJoinInterval";
            this.textBoxPermitJoinInterval.Size = new System.Drawing.Size(106, 20);
            this.textBoxPermitJoinInterval.TabIndex = 32;
            this.textBoxPermitJoinInterval.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxPermitJoinInterval_MouseClick);
            this.textBoxPermitJoinInterval.Leave += new System.EventHandler(this.textBoxPermitJoinInterval_Leave);
            this.textBoxPermitJoinInterval.MouseLeave += new System.EventHandler(this.textBoxPermitJoinInterval_MouseLeave);
            this.textBoxPermitJoinInterval.MouseHover += new System.EventHandler(this.textBoxPermitJoinInterval_MouseHover);
            // 
            // textBoxPermitJoinAddr
            // 
            this.textBoxPermitJoinAddr.Location = new System.Drawing.Point(93, 238);
            this.textBoxPermitJoinAddr.Name = "textBoxPermitJoinAddr";
            this.textBoxPermitJoinAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxPermitJoinAddr.TabIndex = 31;
            this.textBoxPermitJoinAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxPermitJoinAddr_MouseClick);
            this.textBoxPermitJoinAddr.Leave += new System.EventHandler(this.textBoxPermitJoinAddr_Leave);
            this.textBoxPermitJoinAddr.MouseLeave += new System.EventHandler(this.textBoxPermitJoinAddr_MouseLeave);
            this.textBoxPermitJoinAddr.MouseHover += new System.EventHandler(this.textBoxPermitJoinAddr_MouseHover);
            // 
            // buttonPermitJoin
            // 
            this.buttonPermitJoin.Location = new System.Drawing.Point(6, 238);
            this.buttonPermitJoin.Name = "buttonPermitJoin";
            this.buttonPermitJoin.Size = new System.Drawing.Size(80, 22);
            this.buttonPermitJoin.TabIndex = 30;
            this.buttonPermitJoin.Text = "Permit Join";
            this.buttonPermitJoin.UseVisualStyleBackColor = true;
            this.buttonPermitJoin.Click += new System.EventHandler(this.buttonPermitJoin_Click);
            // 
            // comboBoxSetKeyType
            // 
            this.comboBoxSetKeyType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxSetKeyType.FormattingEnabled = true;
            this.comboBoxSetKeyType.Location = new System.Drawing.Point(377, 93);
            this.comboBoxSetKeyType.Name = "comboBoxSetKeyType";
            this.comboBoxSetKeyType.Size = new System.Drawing.Size(129, 21);
            this.comboBoxSetKeyType.TabIndex = 14;
            // 
            // comboBoxSetKeyState
            // 
            this.comboBoxSetKeyState.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxSetKeyState.FormattingEnabled = true;
            this.comboBoxSetKeyState.Location = new System.Drawing.Point(95, 94);
            this.comboBoxSetKeyState.Name = "comboBoxSetKeyState";
            this.comboBoxSetKeyState.Size = new System.Drawing.Size(213, 21);
            this.comboBoxSetKeyState.TabIndex = 12;
            // 
            // comboBoxSetType
            // 
            this.comboBoxSetType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxSetType.FormattingEnabled = true;
            this.comboBoxSetType.Location = new System.Drawing.Point(95, 124);
            this.comboBoxSetType.Name = "comboBoxSetType";
            this.comboBoxSetType.Size = new System.Drawing.Size(213, 21);
            this.comboBoxSetType.TabIndex = 17;
            // 
            // buttonStartNWK
            // 
            this.buttonStartNWK.Location = new System.Drawing.Point(266, 6);
            this.buttonStartNWK.Name = "buttonStartNWK";
            this.buttonStartNWK.Size = new System.Drawing.Size(80, 22);
            this.buttonStartNWK.TabIndex = 4;
            this.buttonStartNWK.Text = "Start NWK";
            this.buttonStartNWK.UseVisualStyleBackColor = true;
            this.buttonStartNWK.Click += new System.EventHandler(this.buttonStartNWK_Click);
            // 
            // buttonBind
            // 
            this.buttonBind.Location = new System.Drawing.Point(6, 324);
            this.buttonBind.Name = "buttonBind";
            this.buttonBind.Size = new System.Drawing.Size(80, 22);
            this.buttonBind.TabIndex = 42;
            this.buttonBind.Text = "Bind";
            this.buttonBind.UseVisualStyleBackColor = true;
            this.buttonBind.Click += new System.EventHandler(this.buttonBind_Click);
            // 
            // buttonErasePD
            // 
            this.buttonErasePD.Location = new System.Drawing.Point(6, 6);
            this.buttonErasePD.Name = "buttonErasePD";
            this.buttonErasePD.Size = new System.Drawing.Size(80, 22);
            this.buttonErasePD.TabIndex = 1;
            this.buttonErasePD.Text = "Erase PD";
            this.buttonErasePD.UseVisualStyleBackColor = true;
            this.buttonErasePD.Click += new System.EventHandler(this.buttonErasePD_Click);
            // 
            // buttonReset
            // 
            this.buttonReset.Location = new System.Drawing.Point(93, 6);
            this.buttonReset.Name = "buttonReset";
            this.buttonReset.Size = new System.Drawing.Size(80, 22);
            this.buttonReset.TabIndex = 2;
            this.buttonReset.Text = "Reset";
            this.buttonReset.UseVisualStyleBackColor = true;
            this.buttonReset.Click += new System.EventHandler(this.buttonReset_Click);
            // 
            // textBoxSetSecurityKeySeqNbr
            // 
            this.textBoxSetSecurityKeySeqNbr.Location = new System.Drawing.Point(314, 94);
            this.textBoxSetSecurityKeySeqNbr.Name = "textBoxSetSecurityKeySeqNbr";
            this.textBoxSetSecurityKeySeqNbr.Size = new System.Drawing.Size(55, 20);
            this.textBoxSetSecurityKeySeqNbr.TabIndex = 13;
            this.textBoxSetSecurityKeySeqNbr.Click += new System.EventHandler(this.textBoxSetSecurityKeySeqNbr_Click);
            this.textBoxSetSecurityKeySeqNbr.Leave += new System.EventHandler(this.textBoxSetSecurityKeySeqNbr_Leave);
            // 
            // buttonSetDeviceType
            // 
            this.buttonSetDeviceType.Location = new System.Drawing.Point(6, 122);
            this.buttonSetDeviceType.Name = "buttonSetDeviceType";
            this.buttonSetDeviceType.Size = new System.Drawing.Size(80, 22);
            this.buttonSetDeviceType.TabIndex = 16;
            this.buttonSetDeviceType.Text = "Set Type";
            this.buttonSetDeviceType.UseVisualStyleBackColor = true;
            this.buttonSetDeviceType.Click += new System.EventHandler(this.buttonSetDeviceType_Click);
            // 
            // buttonSetSecurity
            // 
            this.buttonSetSecurity.Location = new System.Drawing.Point(6, 93);
            this.buttonSetSecurity.Name = "buttonSetSecurity";
            this.buttonSetSecurity.Size = new System.Drawing.Size(80, 22);
            this.buttonSetSecurity.TabIndex = 11;
            this.buttonSetSecurity.Text = "Set Security";
            this.buttonSetSecurity.UseVisualStyleBackColor = true;
            this.buttonSetSecurity.Click += new System.EventHandler(this.buttonSetSecurity_Click);
            // 
            // textBoxSetEPID
            // 
            this.textBoxSetEPID.Location = new System.Drawing.Point(95, 37);
            this.textBoxSetEPID.Name = "textBoxSetEPID";
            this.textBoxSetEPID.Size = new System.Drawing.Size(213, 20);
            this.textBoxSetEPID.TabIndex = 8;
            this.textBoxSetEPID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxSetEPID_MouseClick);
            this.textBoxSetEPID.Leave += new System.EventHandler(this.textBoxSetEPID_Leave);
            this.textBoxSetEPID.MouseLeave += new System.EventHandler(this.textBoxSetEPID_MouseLeave);
            this.textBoxSetEPID.MouseHover += new System.EventHandler(this.textBoxSetEPID_MouseHover);
            // 
            // textBoxSetCMSK
            // 
            this.textBoxSetCMSK.Location = new System.Drawing.Point(95, 65);
            this.textBoxSetCMSK.Name = "textBoxSetCMSK";
            this.textBoxSetCMSK.Size = new System.Drawing.Size(213, 20);
            this.textBoxSetCMSK.TabIndex = 10;
            this.textBoxSetCMSK.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxSetCMSK_MouseClick);
            this.textBoxSetCMSK.Leave += new System.EventHandler(this.textBoxSetCMSK_Leave);
            this.textBoxSetCMSK.MouseLeave += new System.EventHandler(this.textBoxSetCMSK_MouseLeave);
            this.textBoxSetCMSK.MouseHover += new System.EventHandler(this.textBoxSetCMSK_MouseHover);
            // 
            // buttonSetCMSK
            // 
            this.buttonSetCMSK.Location = new System.Drawing.Point(6, 63);
            this.buttonSetCMSK.Name = "buttonSetCMSK";
            this.buttonSetCMSK.Size = new System.Drawing.Size(80, 22);
            this.buttonSetCMSK.TabIndex = 9;
            this.buttonSetCMSK.Text = "Set CMSK";
            this.buttonSetCMSK.UseVisualStyleBackColor = true;
            this.buttonSetCMSK.Click += new System.EventHandler(this.buttonSetCMSK_Click);
            // 
            // buttonSetEPID
            // 
            this.buttonSetEPID.Location = new System.Drawing.Point(6, 34);
            this.buttonSetEPID.Name = "buttonSetEPID";
            this.buttonSetEPID.Size = new System.Drawing.Size(80, 22);
            this.buttonSetEPID.TabIndex = 7;
            this.buttonSetEPID.Text = "Set EPID";
            this.buttonSetEPID.UseVisualStyleBackColor = true;
            this.buttonSetEPID.Click += new System.EventHandler(this.buttonSetEPID_Click);
            // 
            // buttonGetVersion
            // 
            this.buttonGetVersion.Location = new System.Drawing.Point(179, 6);
            this.buttonGetVersion.Name = "buttonGetVersion";
            this.buttonGetVersion.Size = new System.Drawing.Size(80, 22);
            this.buttonGetVersion.TabIndex = 3;
            this.buttonGetVersion.Text = "Get Version";
            this.buttonGetVersion.UseVisualStyleBackColor = true;
            this.buttonGetVersion.Click += new System.EventHandler(this.buttonGetVersion_Click);
            // 
            // tabPageDevice
            // 
            this.tabPageDevice.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPageDevice.Controls.Add(this.buttonCopyAddr);
            this.tabPageDevice.Controls.Add(this.buttonDiscoverDevices);
            this.tabPageDevice.Controls.Add(this.textBoxExtAddr);
            this.tabPageDevice.Controls.Add(this.label16);
            this.tabPageDevice.Controls.Add(this.comboBoxAddressList);
            this.tabPageDevice.Location = new System.Drawing.Point(4, 22);
            this.tabPageDevice.Margin = new System.Windows.Forms.Padding(2);
            this.tabPageDevice.Name = "tabPageDevice";
            this.tabPageDevice.Padding = new System.Windows.Forms.Padding(2);
            this.tabPageDevice.Size = new System.Drawing.Size(1351, 416);
            this.tabPageDevice.TabIndex = 18;
            this.tabPageDevice.Text = "Discover Devices";
            // 
            // buttonCopyAddr
            // 
            this.buttonCopyAddr.Location = new System.Drawing.Point(212, 86);
            this.buttonCopyAddr.Margin = new System.Windows.Forms.Padding(2);
            this.buttonCopyAddr.Name = "buttonCopyAddr";
            this.buttonCopyAddr.Size = new System.Drawing.Size(97, 26);
            this.buttonCopyAddr.TabIndex = 3;
            this.buttonCopyAddr.Text = "Copy";
            this.buttonCopyAddr.UseVisualStyleBackColor = true;
            this.buttonCopyAddr.Click += new System.EventHandler(this.buttonCopyAddr_Click);
            // 
            // buttonDiscoverDevices
            // 
            this.buttonDiscoverDevices.Location = new System.Drawing.Point(27, 30);
            this.buttonDiscoverDevices.Margin = new System.Windows.Forms.Padding(2);
            this.buttonDiscoverDevices.Name = "buttonDiscoverDevices";
            this.buttonDiscoverDevices.Size = new System.Drawing.Size(180, 26);
            this.buttonDiscoverDevices.TabIndex = 0;
            this.buttonDiscoverDevices.Text = "Discover devices";
            this.buttonDiscoverDevices.UseVisualStyleBackColor = true;
            this.buttonDiscoverDevices.Click += new System.EventHandler(this.buttonDiscoverDevices_Click);
            // 
            // textBoxExtAddr
            // 
            this.textBoxExtAddr.Location = new System.Drawing.Point(27, 94);
            this.textBoxExtAddr.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxExtAddr.Name = "textBoxExtAddr";
            this.textBoxExtAddr.ReadOnly = true;
            this.textBoxExtAddr.Size = new System.Drawing.Size(181, 20);
            this.textBoxExtAddr.TabIndex = 2;
            this.textBoxExtAddr.Text = " ";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(25, 78);
            this.label16.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(93, 13);
            this.label16.TabIndex = 6;
            this.label16.Text = "Extended Address";
            // 
            // comboBoxAddressList
            // 
            this.comboBoxAddressList.FormattingEnabled = true;
            this.comboBoxAddressList.Location = new System.Drawing.Point(212, 34);
            this.comboBoxAddressList.Margin = new System.Windows.Forms.Padding(2);
            this.comboBoxAddressList.Name = "comboBoxAddressList";
            this.comboBoxAddressList.Size = new System.Drawing.Size(98, 21);
            this.comboBoxAddressList.TabIndex = 1;
            this.comboBoxAddressList.SelectedIndexChanged += new System.EventHandler(this.comboBoxAddressList_SelectedIndexChanged);
            // 
            // tabPage12
            // 
            this.tabPage12.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage12.Controls.Add(this.textBoxOOBDataKey);
            this.tabPage12.Controls.Add(this.textBoxOOBDataAddr);
            this.tabPage12.Controls.Add(this.buttonOOBCommissioningData);
            this.tabPage12.Controls.Add(this.textBoxDiscoverAttributesStartAttrId);
            this.tabPage12.Controls.Add(this.textBoxRawDataCommandsProfileID);
            this.tabPage12.Controls.Add(this.textBoxRawDataCommandsSecurityMode);
            this.tabPage12.Controls.Add(this.textBoxRawDataCommandsRadius);
            this.tabPage12.Controls.Add(this.textBoxRawDataCommandsData);
            this.tabPage12.Controls.Add(this.textBoxRawDataCommandsClusterID);
            this.tabPage12.Controls.Add(this.textBoxRawDataCommandsDstEP);
            this.tabPage12.Controls.Add(this.textBoxRawDataCommandsSrcEP);
            this.tabPage12.Controls.Add(this.textBoxRawDataCommandsTargetAddr);
            this.tabPage12.Controls.Add(this.comboBoxRawDataCommandsAddrMode);
            this.tabPage12.Controls.Add(this.buttonRawDataSend);
            this.tabPage12.Controls.Add(this.textBoxMgmtNwkUpdateNwkManagerAddr);
            this.tabPage12.Controls.Add(this.comboBoxDiscoverCommandsRxGen);
            this.tabPage12.Controls.Add(this.comboBoxDiscoverAttributesExtended);
            this.tabPage12.Controls.Add(this.textBoxDiscoverCommandsMaxCommands);
            this.tabPage12.Controls.Add(this.textBoxDiscoverCommandsManuID);
            this.tabPage12.Controls.Add(this.comboBoxDiscoverCommandsManuSpecific);
            this.tabPage12.Controls.Add(this.textBoxDiscoverCommandsCommandID);
            this.tabPage12.Controls.Add(this.comboBoxDiscoverCommandsDirection);
            this.tabPage12.Controls.Add(this.textBoxDiscoverCommandsClusterID);
            this.tabPage12.Controls.Add(this.textBoxDiscoverCommandsDstEP);
            this.tabPage12.Controls.Add(this.textBoxDiscoverCommandsSrcEP);
            this.tabPage12.Controls.Add(this.textBoxDiscoverCommandsTargetAddr);
            this.tabPage12.Controls.Add(this.comboBoxDiscoverCommandsAddrMode);
            this.tabPage12.Controls.Add(this.buttonDiscoverCommands);
            this.tabPage12.Controls.Add(this.textBoxMgmtNwkUpdateScanCount);
            this.tabPage12.Controls.Add(this.textBoxMgmtNwkUpdateScanDuration);
            this.tabPage12.Controls.Add(this.textBoxMgmtNwkUpdateChannelMask);
            this.tabPage12.Controls.Add(this.textBoxMgmtNwkUpdateTargetAddr);
            this.tabPage12.Controls.Add(this.comboBoxMgmtNwkUpdateAddrMode);
            this.tabPage12.Controls.Add(this.buttonMgmtNwkUpdate);
            this.tabPage12.Controls.Add(this.comboBoxManyToOneRouteRequestCacheRoute);
            this.tabPage12.Controls.Add(this.textBoxManyToOneRouteRequesRadius);
            this.tabPage12.Controls.Add(this.buttonManyToOneRouteRequest);
            this.tabPage12.Controls.Add(this.comboBoxReadReportConfigDirection);
            this.tabPage12.Controls.Add(this.comboBoxReadReportConfigDirIsRx);
            this.tabPage12.Controls.Add(this.textBoxReadReportConfigAttribID);
            this.tabPage12.Controls.Add(this.textBoxReadReportConfigClusterID);
            this.tabPage12.Controls.Add(this.textBoxReadReportConfigDstEP);
            this.tabPage12.Controls.Add(this.textBoxReadReportConfigSrcEP);
            this.tabPage12.Controls.Add(this.textBoxReadReportConfigTargetAddr);
            this.tabPage12.Controls.Add(this.comboBoxReadReportConfigAddrMode);
            this.tabPage12.Controls.Add(this.buttonReadReportConfig);
            this.tabPage12.Controls.Add(this.textBoxWriteAttribManuID);
            this.tabPage12.Controls.Add(this.comboBoxWriteAttribManuSpecific);
            this.tabPage12.Controls.Add(this.textBoxWriteAttribDataType);
            this.tabPage12.Controls.Add(this.textBoxReadAttribManuID);
            this.tabPage12.Controls.Add(this.comboBoxReadAttribManuSpecific);
            this.tabPage12.Controls.Add(this.comboBoxConfigReportAddrMode);
            this.tabPage12.Controls.Add(this.textBoxWriteAttribData);
            this.tabPage12.Controls.Add(this.textBoxWriteAttribID);
            this.tabPage12.Controls.Add(this.comboBoxWriteAttribDirection);
            this.tabPage12.Controls.Add(this.textBoxWriteAttribClusterID);
            this.tabPage12.Controls.Add(this.textBoxWriteAttribDstEP);
            this.tabPage12.Controls.Add(this.textBoxWriteAttribSrcEP);
            this.tabPage12.Controls.Add(this.textBoxWriteAttribTargetAddr);
            this.tabPage12.Controls.Add(this.textBoxConfigReportChange);
            this.tabPage12.Controls.Add(this.textBoxConfigReportTimeOut);
            this.tabPage12.Controls.Add(this.textBoxConfigReportMaxInterval);
            this.tabPage12.Controls.Add(this.textBoxDiscoverAttributesMaxIDs);
            this.tabPage12.Controls.Add(this.comboBoxDiscoverAttributesDirection);
            this.tabPage12.Controls.Add(this.textBoxDiscoverAttributesClusterID);
            this.tabPage12.Controls.Add(this.textBoxDiscoverAttributesDstEp);
            this.tabPage12.Controls.Add(this.textBoxDiscoverAttributesSrcEp);
            this.tabPage12.Controls.Add(this.textBoxDiscoverAttributesAddr);
            this.tabPage12.Controls.Add(this.buttonDiscoverAttributes);
            this.tabPage12.Controls.Add(this.comboBoxReadAllAttribDirection);
            this.tabPage12.Controls.Add(this.textBoxReadAllAttribClusterID);
            this.tabPage12.Controls.Add(this.textBoxReadAllAttribDstEP);
            this.tabPage12.Controls.Add(this.textBoxReadAllAttribSrcEP);
            this.tabPage12.Controls.Add(this.textBoxReadAllAttribAddr);
            this.tabPage12.Controls.Add(this.buttonReadAllAttrib);
            this.tabPage12.Controls.Add(this.comboBoxConfigReportAttribDirection);
            this.tabPage12.Controls.Add(this.textBoxConfigReportAttribType);
            this.tabPage12.Controls.Add(this.textBoxConfigReportMinInterval);
            this.tabPage12.Controls.Add(this.textBoxConfigReportAttribID);
            this.tabPage12.Controls.Add(this.comboBoxConfigReportDirection);
            this.tabPage12.Controls.Add(this.textBoxConfigReportClusterID);
            this.tabPage12.Controls.Add(this.textBoxConfigReportDstEP);
            this.tabPage12.Controls.Add(this.textBoxConfigReportSrcEP);
            this.tabPage12.Controls.Add(this.textBoxConfigReportTargetAddr);
            this.tabPage12.Controls.Add(this.buttonConfigReport);
            this.tabPage12.Controls.Add(this.buttonWriteAttrib);
            this.tabPage12.Controls.Add(this.textBoxReadAttribCount);
            this.tabPage12.Controls.Add(this.comboBoxReadAttribDirection);
            this.tabPage12.Controls.Add(this.textBoxReadAttribID1);
            this.tabPage12.Controls.Add(this.textBoxReadAttribClusterID);
            this.tabPage12.Controls.Add(this.textBoxReadAttribDstEP);
            this.tabPage12.Controls.Add(this.textBoxReadAttribSrcEP);
            this.tabPage12.Controls.Add(this.textBoxReadAttribTargetAddr);
            this.tabPage12.Controls.Add(this.buttonReadAttrib);
            this.tabPage12.Location = new System.Drawing.Point(4, 22);
            this.tabPage12.Name = "tabPage12";
            this.tabPage12.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage12.Size = new System.Drawing.Size(1351, 416);
            this.tabPage12.TabIndex = 12;
            this.tabPage12.Text = "General";
            this.tabPage12.Click += new System.EventHandler(this.tabPage12_Click);
            // 
            // textBoxOOBDataKey
            // 
            this.textBoxOOBDataKey.Location = new System.Drawing.Point(270, 350);
            this.textBoxOOBDataKey.Name = "textBoxOOBDataKey";
            this.textBoxOOBDataKey.Size = new System.Drawing.Size(266, 20);
            this.textBoxOOBDataKey.TabIndex = 96;
            this.textBoxOOBDataKey.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOOBDataKey_MouseClick);
            this.textBoxOOBDataKey.Leave += new System.EventHandler(this.textBoxOOBDataKey_Leave);
            this.textBoxOOBDataKey.MouseLeave += new System.EventHandler(this.textBoxOOBDataKey_MouseLeave);
            this.textBoxOOBDataKey.MouseHover += new System.EventHandler(this.textBoxOOBDataKey_MouseHover);
            // 
            // textBoxOOBDataAddr
            // 
            this.textBoxOOBDataAddr.Location = new System.Drawing.Point(158, 350);
            this.textBoxOOBDataAddr.Name = "textBoxOOBDataAddr";
            this.textBoxOOBDataAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxOOBDataAddr.TabIndex = 95;
            this.textBoxOOBDataAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOOBDataAddr_MouseClick);
            this.textBoxOOBDataAddr.Leave += new System.EventHandler(this.textBoxOOBDataAddr_Leave);
            this.textBoxOOBDataAddr.MouseLeave += new System.EventHandler(this.textBoxOOBDataAddr_MouseLeave);
            this.textBoxOOBDataAddr.MouseHover += new System.EventHandler(this.textBoxOOBDataAddr_MouseHover);
            // 
            // buttonOOBCommissioningData
            // 
            this.buttonOOBCommissioningData.Location = new System.Drawing.Point(6, 348);
            this.buttonOOBCommissioningData.Name = "buttonOOBCommissioningData";
            this.buttonOOBCommissioningData.Size = new System.Drawing.Size(146, 22);
            this.buttonOOBCommissioningData.TabIndex = 91;
            this.buttonOOBCommissioningData.Text = "OOB Commissioning Data";
            this.buttonOOBCommissioningData.UseVisualStyleBackColor = true;
            this.buttonOOBCommissioningData.Click += new System.EventHandler(this.buttonOOBCommissioningData_Click);
            // 
            // textBoxDiscoverAttributesStartAttrId
            // 
            this.textBoxDiscoverAttributesStartAttrId.Location = new System.Drawing.Point(541, 210);
            this.textBoxDiscoverAttributesStartAttrId.Name = "textBoxDiscoverAttributesStartAttrId";
            this.textBoxDiscoverAttributesStartAttrId.Size = new System.Drawing.Size(110, 20);
            this.textBoxDiscoverAttributesStartAttrId.TabIndex = 55;
            this.textBoxDiscoverAttributesStartAttrId.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDiscoverAttributesStartAttrId_MouseClick);
            this.textBoxDiscoverAttributesStartAttrId.Leave += new System.EventHandler(this.textBoxDiscoverAttributesStartAttrId_Leave);
            this.textBoxDiscoverAttributesStartAttrId.MouseLeave += new System.EventHandler(this.textBoxDiscoverAttributesStartAttrId_MouseLeave);
            this.textBoxDiscoverAttributesStartAttrId.MouseHover += new System.EventHandler(this.textBoxDiscoverAttributesStartAttrId_MouseHover);
            // 
            // textBoxRawDataCommandsProfileID
            // 
            this.textBoxRawDataCommandsProfileID.Location = new System.Drawing.Point(541, 320);
            this.textBoxRawDataCommandsProfileID.Name = "textBoxRawDataCommandsProfileID";
            this.textBoxRawDataCommandsProfileID.Size = new System.Drawing.Size(110, 20);
            this.textBoxRawDataCommandsProfileID.TabIndex = 86;
            this.textBoxRawDataCommandsProfileID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRawDataCommandsProfileID_MouseClick);
            this.textBoxRawDataCommandsProfileID.Leave += new System.EventHandler(this.textBoxRawDataCommandsProfileID_Leave);
            this.textBoxRawDataCommandsProfileID.MouseLeave += new System.EventHandler(this.textBoxRawDataCommandsProfileID_MouseLeave);
            this.textBoxRawDataCommandsProfileID.MouseHover += new System.EventHandler(this.textBoxRawDataCommandsProfileID_MouseHover);
            // 
            // textBoxRawDataCommandsSecurityMode
            // 
            this.textBoxRawDataCommandsSecurityMode.Location = new System.Drawing.Point(884, 320);
            this.textBoxRawDataCommandsSecurityMode.Name = "textBoxRawDataCommandsSecurityMode";
            this.textBoxRawDataCommandsSecurityMode.Size = new System.Drawing.Size(208, 20);
            this.textBoxRawDataCommandsSecurityMode.TabIndex = 89;
            this.textBoxRawDataCommandsSecurityMode.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRawDataCommandsSecurityMode_MouseClick);
            this.textBoxRawDataCommandsSecurityMode.Leave += new System.EventHandler(this.textBoxRawDataCommandsSecurityMode_Leave);
            this.textBoxRawDataCommandsSecurityMode.MouseLeave += new System.EventHandler(this.textBoxRawDataCommandsSecurityMode_MouseLeave);
            this.textBoxRawDataCommandsSecurityMode.MouseHover += new System.EventHandler(this.textBoxRawDataCommandsSecurityMode_MouseHover);
            // 
            // textBoxRawDataCommandsRadius
            // 
            this.textBoxRawDataCommandsRadius.Location = new System.Drawing.Point(771, 320);
            this.textBoxRawDataCommandsRadius.Name = "textBoxRawDataCommandsRadius";
            this.textBoxRawDataCommandsRadius.Size = new System.Drawing.Size(106, 20);
            this.textBoxRawDataCommandsRadius.TabIndex = 88;
            this.textBoxRawDataCommandsRadius.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRawDataCommandsRadius_MouseClick);
            this.textBoxRawDataCommandsRadius.Leave += new System.EventHandler(this.textBoxRawDataCommandsRadius_Leave);
            this.textBoxRawDataCommandsRadius.MouseLeave += new System.EventHandler(this.textBoxRawDataCommandsRadius_MouseLeave);
            this.textBoxRawDataCommandsRadius.MouseHover += new System.EventHandler(this.textBoxRawDataCommandsRadius_MouseHover);
            // 
            // textBoxRawDataCommandsData
            // 
            this.textBoxRawDataCommandsData.Location = new System.Drawing.Point(1098, 320);
            this.textBoxRawDataCommandsData.Name = "textBoxRawDataCommandsData";
            this.textBoxRawDataCommandsData.Size = new System.Drawing.Size(248, 20);
            this.textBoxRawDataCommandsData.TabIndex = 90;
            this.textBoxRawDataCommandsData.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRawDataCommandsData_MouseClick);
            this.textBoxRawDataCommandsData.Leave += new System.EventHandler(this.textBoxRawDataCommandsData_Leave);
            this.textBoxRawDataCommandsData.MouseLeave += new System.EventHandler(this.textBoxRawDataCommandsData_MouseLeave);
            this.textBoxRawDataCommandsData.MouseHover += new System.EventHandler(this.textBoxRawDataCommandsData_MouseHover);
            // 
            // textBoxRawDataCommandsClusterID
            // 
            this.textBoxRawDataCommandsClusterID.Location = new System.Drawing.Point(658, 320);
            this.textBoxRawDataCommandsClusterID.Name = "textBoxRawDataCommandsClusterID";
            this.textBoxRawDataCommandsClusterID.Size = new System.Drawing.Size(109, 20);
            this.textBoxRawDataCommandsClusterID.TabIndex = 87;
            this.textBoxRawDataCommandsClusterID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRawDataCommandsClusterID_MouseClick);
            this.textBoxRawDataCommandsClusterID.Leave += new System.EventHandler(this.textBoxRawDataCommandsClusterID_Leave);
            this.textBoxRawDataCommandsClusterID.MouseLeave += new System.EventHandler(this.textBoxRawDataCommandsClusterID_MouseLeave);
            this.textBoxRawDataCommandsClusterID.MouseHover += new System.EventHandler(this.textBoxRawDataCommandsClusterID_MouseHover);
            // 
            // textBoxRawDataCommandsDstEP
            // 
            this.textBoxRawDataCommandsDstEP.Location = new System.Drawing.Point(432, 320);
            this.textBoxRawDataCommandsDstEP.Name = "textBoxRawDataCommandsDstEP";
            this.textBoxRawDataCommandsDstEP.Size = new System.Drawing.Size(103, 20);
            this.textBoxRawDataCommandsDstEP.TabIndex = 85;
            this.textBoxRawDataCommandsDstEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRawDataCommandsDstEP_MouseClick);
            this.textBoxRawDataCommandsDstEP.Leave += new System.EventHandler(this.textBoxRawDataCommandsDstEP_Leave);
            this.textBoxRawDataCommandsDstEP.MouseLeave += new System.EventHandler(this.textBoxRawDataCommandsDstEP_MouseLeave);
            this.textBoxRawDataCommandsDstEP.MouseHover += new System.EventHandler(this.textBoxRawDataCommandsDstEP_MouseHover);
            // 
            // textBoxRawDataCommandsSrcEP
            // 
            this.textBoxRawDataCommandsSrcEP.Location = new System.Drawing.Point(319, 320);
            this.textBoxRawDataCommandsSrcEP.Name = "textBoxRawDataCommandsSrcEP";
            this.textBoxRawDataCommandsSrcEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxRawDataCommandsSrcEP.TabIndex = 84;
            this.textBoxRawDataCommandsSrcEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRawDataCommandsSrcEP_MouseClick);
            this.textBoxRawDataCommandsSrcEP.Leave += new System.EventHandler(this.textBoxRawDataCommandsSrcEP_Leave);
            this.textBoxRawDataCommandsSrcEP.MouseLeave += new System.EventHandler(this.textBoxRawDataCommandsSrcEP_MouseLeave);
            this.textBoxRawDataCommandsSrcEP.MouseHover += new System.EventHandler(this.textBoxRawDataCommandsSrcEP_MouseHover);
            // 
            // textBoxRawDataCommandsTargetAddr
            // 
            this.textBoxRawDataCommandsTargetAddr.Location = new System.Drawing.Point(208, 320);
            this.textBoxRawDataCommandsTargetAddr.Name = "textBoxRawDataCommandsTargetAddr";
            this.textBoxRawDataCommandsTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxRawDataCommandsTargetAddr.TabIndex = 83;
            this.textBoxRawDataCommandsTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRawDataCommandsTargetAddr_MouseClick);
            this.textBoxRawDataCommandsTargetAddr.Leave += new System.EventHandler(this.textBoxRawDataCommandsTargetAddr_Leave);
            this.textBoxRawDataCommandsTargetAddr.MouseLeave += new System.EventHandler(this.textBoxRawDataCommandsTargetAddr_MouseLeave);
            this.textBoxRawDataCommandsTargetAddr.MouseHover += new System.EventHandler(this.textBoxRawDataCommandsTargetAddr_MouseHover);
            // 
            // comboBoxRawDataCommandsAddrMode
            // 
            this.comboBoxRawDataCommandsAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxRawDataCommandsAddrMode.FormattingEnabled = true;
            this.comboBoxRawDataCommandsAddrMode.Location = new System.Drawing.Point(108, 321);
            this.comboBoxRawDataCommandsAddrMode.Name = "comboBoxRawDataCommandsAddrMode";
            this.comboBoxRawDataCommandsAddrMode.Size = new System.Drawing.Size(94, 21);
            this.comboBoxRawDataCommandsAddrMode.TabIndex = 82;
            // 
            // buttonRawDataSend
            // 
            this.buttonRawDataSend.Location = new System.Drawing.Point(6, 320);
            this.buttonRawDataSend.Name = "buttonRawDataSend";
            this.buttonRawDataSend.Size = new System.Drawing.Size(95, 22);
            this.buttonRawDataSend.TabIndex = 81;
            this.buttonRawDataSend.Text = "Raw Data";
            this.buttonRawDataSend.UseVisualStyleBackColor = true;
            this.buttonRawDataSend.Click += new System.EventHandler(this.buttonRawDataSend_Click);
            // 
            // textBoxMgmtNwkUpdateNwkManagerAddr
            // 
            this.textBoxMgmtNwkUpdateNwkManagerAddr.Location = new System.Drawing.Point(658, 267);
            this.textBoxMgmtNwkUpdateNwkManagerAddr.Name = "textBoxMgmtNwkUpdateNwkManagerAddr";
            this.textBoxMgmtNwkUpdateNwkManagerAddr.Size = new System.Drawing.Size(141, 20);
            this.textBoxMgmtNwkUpdateNwkManagerAddr.TabIndex = 68;
            this.textBoxMgmtNwkUpdateNwkManagerAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMgmtNwkUpdateNwkManagerAddr_MouseClick);
            this.textBoxMgmtNwkUpdateNwkManagerAddr.Leave += new System.EventHandler(this.textBoxMgmtNwkUpdateNwkManagerAddr_Leave);
            this.textBoxMgmtNwkUpdateNwkManagerAddr.MouseLeave += new System.EventHandler(this.textBoxMgmtNwkUpdateNwkManagerAddr_MouseLeave);
            this.textBoxMgmtNwkUpdateNwkManagerAddr.MouseHover += new System.EventHandler(this.textBoxMgmtNwkUpdateNwkManagerAddr_MouseHover);
            // 
            // comboBoxDiscoverCommandsRxGen
            // 
            this.comboBoxDiscoverCommandsRxGen.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDiscoverCommandsRxGen.FormattingEnabled = true;
            this.comboBoxDiscoverCommandsRxGen.Location = new System.Drawing.Point(1217, 294);
            this.comboBoxDiscoverCommandsRxGen.Name = "comboBoxDiscoverCommandsRxGen";
            this.comboBoxDiscoverCommandsRxGen.Size = new System.Drawing.Size(96, 21);
            this.comboBoxDiscoverCommandsRxGen.TabIndex = 80;
            this.comboBoxDiscoverCommandsRxGen.MouseLeave += new System.EventHandler(this.comboBoxDiscoverCommandsRxGen_MouseLeave);
            this.comboBoxDiscoverCommandsRxGen.MouseHover += new System.EventHandler(this.comboBoxDiscoverCommandsRxGen_MouseHover);
            // 
            // comboBoxDiscoverAttributesExtended
            // 
            this.comboBoxDiscoverAttributesExtended.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDiscoverAttributesExtended.FormattingEnabled = true;
            this.comboBoxDiscoverAttributesExtended.Location = new System.Drawing.Point(883, 209);
            this.comboBoxDiscoverAttributesExtended.Name = "comboBoxDiscoverAttributesExtended";
            this.comboBoxDiscoverAttributesExtended.Size = new System.Drawing.Size(106, 21);
            this.comboBoxDiscoverAttributesExtended.TabIndex = 58;
            this.comboBoxDiscoverAttributesExtended.MouseLeave += new System.EventHandler(this.comboBoxDiscoverAttributesExtended_MouseLeave);
            this.comboBoxDiscoverAttributesExtended.MouseHover += new System.EventHandler(this.comboBoxDiscoverAttributesExtended_MouseHover);
            // 
            // textBoxDiscoverCommandsMaxCommands
            // 
            this.textBoxDiscoverCommandsMaxCommands.Location = new System.Drawing.Point(1098, 294);
            this.textBoxDiscoverCommandsMaxCommands.Name = "textBoxDiscoverCommandsMaxCommands";
            this.textBoxDiscoverCommandsMaxCommands.Size = new System.Drawing.Size(112, 20);
            this.textBoxDiscoverCommandsMaxCommands.TabIndex = 79;
            this.textBoxDiscoverCommandsMaxCommands.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDiscoverCommandsMaxCommands_MouseClick);
            this.textBoxDiscoverCommandsMaxCommands.Leave += new System.EventHandler(this.textBoxDiscoverCommandsMaxCommands_Leave);
            this.textBoxDiscoverCommandsMaxCommands.MouseLeave += new System.EventHandler(this.textBoxDiscoverCommandsMaxCommands_MouseLeave);
            this.textBoxDiscoverCommandsMaxCommands.MouseHover += new System.EventHandler(this.textBoxDiscoverCommandsMaxCommands_MouseHover);
            // 
            // textBoxDiscoverCommandsManuID
            // 
            this.textBoxDiscoverCommandsManuID.Location = new System.Drawing.Point(982, 294);
            this.textBoxDiscoverCommandsManuID.Name = "textBoxDiscoverCommandsManuID";
            this.textBoxDiscoverCommandsManuID.Size = new System.Drawing.Size(112, 20);
            this.textBoxDiscoverCommandsManuID.TabIndex = 78;
            this.textBoxDiscoverCommandsManuID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDiscoverCommandsManuID_MouseClick);
            this.textBoxDiscoverCommandsManuID.Leave += new System.EventHandler(this.textBoxDiscoverCommandsManuID_Leave);
            this.textBoxDiscoverCommandsManuID.MouseLeave += new System.EventHandler(this.textBoxDiscoverCommandsManuID_MouseLeave);
            this.textBoxDiscoverCommandsManuID.MouseHover += new System.EventHandler(this.textBoxDiscoverCommandsManuID_MouseHover);
            // 
            // comboBoxDiscoverCommandsManuSpecific
            // 
            this.comboBoxDiscoverCommandsManuSpecific.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDiscoverCommandsManuSpecific.FormattingEnabled = true;
            this.comboBoxDiscoverCommandsManuSpecific.Location = new System.Drawing.Point(884, 294);
            this.comboBoxDiscoverCommandsManuSpecific.Name = "comboBoxDiscoverCommandsManuSpecific";
            this.comboBoxDiscoverCommandsManuSpecific.Size = new System.Drawing.Size(91, 21);
            this.comboBoxDiscoverCommandsManuSpecific.TabIndex = 77;
            this.comboBoxDiscoverCommandsManuSpecific.MouseLeave += new System.EventHandler(this.comboBoxDiscoverCommandsManuSpecific_MouseLeave);
            this.comboBoxDiscoverCommandsManuSpecific.MouseHover += new System.EventHandler(this.comboBoxDiscoverCommandsManuSpecific_MouseHover);
            // 
            // textBoxDiscoverCommandsCommandID
            // 
            this.textBoxDiscoverCommandsCommandID.Location = new System.Drawing.Point(770, 294);
            this.textBoxDiscoverCommandsCommandID.Name = "textBoxDiscoverCommandsCommandID";
            this.textBoxDiscoverCommandsCommandID.Size = new System.Drawing.Size(109, 20);
            this.textBoxDiscoverCommandsCommandID.TabIndex = 76;
            this.textBoxDiscoverCommandsCommandID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDiscoverCommandsCommandID_MouseClick);
            this.textBoxDiscoverCommandsCommandID.Leave += new System.EventHandler(this.textBoxDiscoverCommandsCommandID_Leave);
            this.textBoxDiscoverCommandsCommandID.MouseLeave += new System.EventHandler(this.textBoxDiscoverCommandsCommandID_MouseLeave);
            this.textBoxDiscoverCommandsCommandID.MouseHover += new System.EventHandler(this.textBoxDiscoverCommandsCommandID_MouseHover);
            // 
            // comboBoxDiscoverCommandsDirection
            // 
            this.comboBoxDiscoverCommandsDirection.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDiscoverCommandsDirection.FormattingEnabled = true;
            this.comboBoxDiscoverCommandsDirection.Location = new System.Drawing.Point(658, 294);
            this.comboBoxDiscoverCommandsDirection.Name = "comboBoxDiscoverCommandsDirection";
            this.comboBoxDiscoverCommandsDirection.Size = new System.Drawing.Size(106, 21);
            this.comboBoxDiscoverCommandsDirection.TabIndex = 75;
            this.comboBoxDiscoverCommandsDirection.MouseLeave += new System.EventHandler(this.comboBoxDiscoverCommandsDirection_MouseLeave);
            this.comboBoxDiscoverCommandsDirection.MouseHover += new System.EventHandler(this.comboBoxDiscoverCommandsDirection_MouseHover);
            // 
            // textBoxDiscoverCommandsClusterID
            // 
            this.textBoxDiscoverCommandsClusterID.Location = new System.Drawing.Point(538, 294);
            this.textBoxDiscoverCommandsClusterID.Name = "textBoxDiscoverCommandsClusterID";
            this.textBoxDiscoverCommandsClusterID.Size = new System.Drawing.Size(113, 20);
            this.textBoxDiscoverCommandsClusterID.TabIndex = 74;
            this.textBoxDiscoverCommandsClusterID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDiscoverCommandsClusterID_MouseClick);
            this.textBoxDiscoverCommandsClusterID.Leave += new System.EventHandler(this.textBoxDiscoverCommandsClusterID_Leave);
            this.textBoxDiscoverCommandsClusterID.MouseLeave += new System.EventHandler(this.textBoxDiscoverCommandsClusterID_MouseLeave);
            this.textBoxDiscoverCommandsClusterID.MouseHover += new System.EventHandler(this.textBoxDiscoverCommandsClusterID_MouseHover);
            // 
            // textBoxDiscoverCommandsDstEP
            // 
            this.textBoxDiscoverCommandsDstEP.Location = new System.Drawing.Point(431, 294);
            this.textBoxDiscoverCommandsDstEP.Name = "textBoxDiscoverCommandsDstEP";
            this.textBoxDiscoverCommandsDstEP.Size = new System.Drawing.Size(103, 20);
            this.textBoxDiscoverCommandsDstEP.TabIndex = 73;
            this.textBoxDiscoverCommandsDstEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDiscoverCommandsDstEP_MouseClick);
            this.textBoxDiscoverCommandsDstEP.Leave += new System.EventHandler(this.textBoxDiscoverCommandsDstEP_Leave);
            this.textBoxDiscoverCommandsDstEP.MouseLeave += new System.EventHandler(this.textBoxDiscoverCommandsDstEP_MouseLeave);
            this.textBoxDiscoverCommandsDstEP.MouseHover += new System.EventHandler(this.textBoxDiscoverCommandsDstEP_MouseHover);
            // 
            // textBoxDiscoverCommandsSrcEP
            // 
            this.textBoxDiscoverCommandsSrcEP.Location = new System.Drawing.Point(319, 294);
            this.textBoxDiscoverCommandsSrcEP.Name = "textBoxDiscoverCommandsSrcEP";
            this.textBoxDiscoverCommandsSrcEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxDiscoverCommandsSrcEP.TabIndex = 72;
            this.textBoxDiscoverCommandsSrcEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDiscoverCommandsSrcEP_MouseClick);
            this.textBoxDiscoverCommandsSrcEP.Leave += new System.EventHandler(this.textBoxDiscoverCommandsSrcEP_Leave);
            this.textBoxDiscoverCommandsSrcEP.MouseLeave += new System.EventHandler(this.textBoxDiscoverCommandsSrcEP_MouseLeave);
            this.textBoxDiscoverCommandsSrcEP.MouseHover += new System.EventHandler(this.textBoxDiscoverCommandsSrcEP_MouseHover);
            // 
            // textBoxDiscoverCommandsTargetAddr
            // 
            this.textBoxDiscoverCommandsTargetAddr.Location = new System.Drawing.Point(206, 294);
            this.textBoxDiscoverCommandsTargetAddr.Name = "textBoxDiscoverCommandsTargetAddr";
            this.textBoxDiscoverCommandsTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxDiscoverCommandsTargetAddr.TabIndex = 71;
            this.textBoxDiscoverCommandsTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDiscoverCommandsTargetAddr_MouseClick);
            this.textBoxDiscoverCommandsTargetAddr.Leave += new System.EventHandler(this.textBoxDiscoverCommandsTargetAddr_Leave);
            this.textBoxDiscoverCommandsTargetAddr.MouseLeave += new System.EventHandler(this.textBoxDiscoverCommandsTargetAddr_MouseLeave);
            this.textBoxDiscoverCommandsTargetAddr.MouseHover += new System.EventHandler(this.textBoxDiscoverCommandsTargetAddr_MouseHover);
            // 
            // comboBoxDiscoverCommandsAddrMode
            // 
            this.comboBoxDiscoverCommandsAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDiscoverCommandsAddrMode.FormattingEnabled = true;
            this.comboBoxDiscoverCommandsAddrMode.Location = new System.Drawing.Point(108, 294);
            this.comboBoxDiscoverCommandsAddrMode.Name = "comboBoxDiscoverCommandsAddrMode";
            this.comboBoxDiscoverCommandsAddrMode.Size = new System.Drawing.Size(94, 21);
            this.comboBoxDiscoverCommandsAddrMode.TabIndex = 70;
            this.comboBoxDiscoverCommandsAddrMode.MouseLeave += new System.EventHandler(this.comboBoxDiscoverCommandsAddrMode_MouseLeave);
            this.comboBoxDiscoverCommandsAddrMode.MouseHover += new System.EventHandler(this.comboBoxDiscoverCommandsAddrMode_MouseHover);
            // 
            // buttonDiscoverCommands
            // 
            this.buttonDiscoverCommands.Location = new System.Drawing.Point(6, 293);
            this.buttonDiscoverCommands.Name = "buttonDiscoverCommands";
            this.buttonDiscoverCommands.Size = new System.Drawing.Size(95, 22);
            this.buttonDiscoverCommands.TabIndex = 69;
            this.buttonDiscoverCommands.Text = "Disc Cmds";
            this.buttonDiscoverCommands.UseVisualStyleBackColor = true;
            this.buttonDiscoverCommands.Click += new System.EventHandler(this.buttonDiscoverCommands_Click);
            // 
            // textBoxMgmtNwkUpdateScanCount
            // 
            this.textBoxMgmtNwkUpdateScanCount.Location = new System.Drawing.Point(538, 267);
            this.textBoxMgmtNwkUpdateScanCount.Name = "textBoxMgmtNwkUpdateScanCount";
            this.textBoxMgmtNwkUpdateScanCount.Size = new System.Drawing.Size(113, 20);
            this.textBoxMgmtNwkUpdateScanCount.TabIndex = 67;
            this.textBoxMgmtNwkUpdateScanCount.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMgmtNwkUpdateScanCount_MouseClick);
            this.textBoxMgmtNwkUpdateScanCount.Leave += new System.EventHandler(this.textBoxMgmtNwkUpdateScanCount_Leave);
            this.textBoxMgmtNwkUpdateScanCount.MouseLeave += new System.EventHandler(this.textBoxMgmtNwkUpdateScanCount_MouseLeave);
            this.textBoxMgmtNwkUpdateScanCount.MouseHover += new System.EventHandler(this.textBoxMgmtNwkUpdateScanCount_MouseHover);
            // 
            // textBoxMgmtNwkUpdateScanDuration
            // 
            this.textBoxMgmtNwkUpdateScanDuration.Location = new System.Drawing.Point(431, 267);
            this.textBoxMgmtNwkUpdateScanDuration.Name = "textBoxMgmtNwkUpdateScanDuration";
            this.textBoxMgmtNwkUpdateScanDuration.Size = new System.Drawing.Size(103, 20);
            this.textBoxMgmtNwkUpdateScanDuration.TabIndex = 66;
            this.textBoxMgmtNwkUpdateScanDuration.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMgmtNwkUpdateScanDuration_MouseClick);
            this.textBoxMgmtNwkUpdateScanDuration.Leave += new System.EventHandler(this.textBoxMgmtNwkUpdateScanDuration_Leave);
            this.textBoxMgmtNwkUpdateScanDuration.MouseLeave += new System.EventHandler(this.textBoxMgmtNwkUpdateScanDuration_MouseLeave);
            this.textBoxMgmtNwkUpdateScanDuration.MouseHover += new System.EventHandler(this.textBoxMgmtNwkUpdateScanDuration_MouseHover);
            // 
            // textBoxMgmtNwkUpdateChannelMask
            // 
            this.textBoxMgmtNwkUpdateChannelMask.Location = new System.Drawing.Point(319, 267);
            this.textBoxMgmtNwkUpdateChannelMask.Name = "textBoxMgmtNwkUpdateChannelMask";
            this.textBoxMgmtNwkUpdateChannelMask.Size = new System.Drawing.Size(106, 20);
            this.textBoxMgmtNwkUpdateChannelMask.TabIndex = 65;
            this.textBoxMgmtNwkUpdateChannelMask.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMgmtNwkUpdateChannelMask_MouseClick);
            this.textBoxMgmtNwkUpdateChannelMask.Leave += new System.EventHandler(this.textBoxMgmtNwkUpdateChannelMask_Leave);
            this.textBoxMgmtNwkUpdateChannelMask.MouseLeave += new System.EventHandler(this.textBoxMgmtNwkUpdateChannelMask_MouseLeave);
            this.textBoxMgmtNwkUpdateChannelMask.MouseHover += new System.EventHandler(this.textBoxMgmtNwkUpdateChannelMask_MouseHover);
            // 
            // textBoxMgmtNwkUpdateTargetAddr
            // 
            this.textBoxMgmtNwkUpdateTargetAddr.Location = new System.Drawing.Point(207, 267);
            this.textBoxMgmtNwkUpdateTargetAddr.Name = "textBoxMgmtNwkUpdateTargetAddr";
            this.textBoxMgmtNwkUpdateTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxMgmtNwkUpdateTargetAddr.TabIndex = 64;
            this.textBoxMgmtNwkUpdateTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMgmtNwkUpdateTargetAddr_MouseClick);
            this.textBoxMgmtNwkUpdateTargetAddr.Leave += new System.EventHandler(this.textBoxMgmtNwkUpdateTargetAddr_Leave);
            this.textBoxMgmtNwkUpdateTargetAddr.MouseLeave += new System.EventHandler(this.textBoxMgmtNwkUpdateTargetAddr_MouseLeave);
            this.textBoxMgmtNwkUpdateTargetAddr.MouseHover += new System.EventHandler(this.textBoxMgmtNwkUpdateTargetAddr_MouseHover);
            // 
            // comboBoxMgmtNwkUpdateAddrMode
            // 
            this.comboBoxMgmtNwkUpdateAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxMgmtNwkUpdateAddrMode.FormattingEnabled = true;
            this.comboBoxMgmtNwkUpdateAddrMode.Location = new System.Drawing.Point(108, 267);
            this.comboBoxMgmtNwkUpdateAddrMode.Name = "comboBoxMgmtNwkUpdateAddrMode";
            this.comboBoxMgmtNwkUpdateAddrMode.Size = new System.Drawing.Size(94, 21);
            this.comboBoxMgmtNwkUpdateAddrMode.TabIndex = 63;
            this.comboBoxMgmtNwkUpdateAddrMode.MouseLeave += new System.EventHandler(this.comboBoxMgmtNwkUpdateAddrMode_MouseLeave);
            this.comboBoxMgmtNwkUpdateAddrMode.MouseHover += new System.EventHandler(this.comboBoxMgmtNwkUpdateAddrMode_MouseHover);
            // 
            // buttonMgmtNwkUpdate
            // 
            this.buttonMgmtNwkUpdate.Location = new System.Drawing.Point(6, 265);
            this.buttonMgmtNwkUpdate.Name = "buttonMgmtNwkUpdate";
            this.buttonMgmtNwkUpdate.Size = new System.Drawing.Size(95, 22);
            this.buttonMgmtNwkUpdate.TabIndex = 62;
            this.buttonMgmtNwkUpdate.Text = "NWK Update";
            this.buttonMgmtNwkUpdate.UseVisualStyleBackColor = true;
            this.buttonMgmtNwkUpdate.Click += new System.EventHandler(this.buttonMgmtNwkUpdate_Click);
            // 
            // comboBoxManyToOneRouteRequestCacheRoute
            // 
            this.comboBoxManyToOneRouteRequestCacheRoute.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxManyToOneRouteRequestCacheRoute.FormattingEnabled = true;
            this.comboBoxManyToOneRouteRequestCacheRoute.Location = new System.Drawing.Point(108, 238);
            this.comboBoxManyToOneRouteRequestCacheRoute.Name = "comboBoxManyToOneRouteRequestCacheRoute";
            this.comboBoxManyToOneRouteRequestCacheRoute.Size = new System.Drawing.Size(91, 21);
            this.comboBoxManyToOneRouteRequestCacheRoute.TabIndex = 60;
            this.comboBoxManyToOneRouteRequestCacheRoute.MouseLeave += new System.EventHandler(this.comboBoxManyToOneRouteRequestCacheRoute_MouseLeave);
            this.comboBoxManyToOneRouteRequestCacheRoute.MouseHover += new System.EventHandler(this.comboBoxManyToOneRouteRequestCacheRoute_MouseHover);
            // 
            // textBoxManyToOneRouteRequesRadius
            // 
            this.textBoxManyToOneRouteRequesRadius.Location = new System.Drawing.Point(207, 238);
            this.textBoxManyToOneRouteRequesRadius.Name = "textBoxManyToOneRouteRequesRadius";
            this.textBoxManyToOneRouteRequesRadius.Size = new System.Drawing.Size(106, 20);
            this.textBoxManyToOneRouteRequesRadius.TabIndex = 61;
            this.textBoxManyToOneRouteRequesRadius.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxManyToOneRouteRequesRadius_MouseClick);
            this.textBoxManyToOneRouteRequesRadius.Leave += new System.EventHandler(this.textBoxManyToOneRouteRequesRadius_Leave);
            this.textBoxManyToOneRouteRequesRadius.MouseLeave += new System.EventHandler(this.textBoxManyToOneRouteRequesRadius_MouseLeave);
            this.textBoxManyToOneRouteRequesRadius.MouseHover += new System.EventHandler(this.textBoxManyToOneRouteRequesRadius_MouseHover);
            // 
            // buttonManyToOneRouteRequest
            // 
            this.buttonManyToOneRouteRequest.Location = new System.Drawing.Point(6, 235);
            this.buttonManyToOneRouteRequest.Name = "buttonManyToOneRouteRequest";
            this.buttonManyToOneRouteRequest.Size = new System.Drawing.Size(95, 24);
            this.buttonManyToOneRouteRequest.TabIndex = 59;
            this.buttonManyToOneRouteRequest.Text = "MTO Rt Req";
            this.buttonManyToOneRouteRequest.UseVisualStyleBackColor = true;
            this.buttonManyToOneRouteRequest.Click += new System.EventHandler(this.buttonManyToOneRouteRequest_Click);
            // 
            // comboBoxReadReportConfigDirection
            // 
            this.comboBoxReadReportConfigDirection.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxReadReportConfigDirection.FormattingEnabled = true;
            this.comboBoxReadReportConfigDirection.Location = new System.Drawing.Point(654, 152);
            this.comboBoxReadReportConfigDirection.Name = "comboBoxReadReportConfigDirection";
            this.comboBoxReadReportConfigDirection.Size = new System.Drawing.Size(110, 21);
            this.comboBoxReadReportConfigDirection.TabIndex = 41;
            this.comboBoxReadReportConfigDirection.MouseLeave += new System.EventHandler(this.comboBoxReadReportConfigDirection_MouseLeave);
            this.comboBoxReadReportConfigDirection.MouseHover += new System.EventHandler(this.comboBoxReadReportConfigDirection_MouseHover);
            // 
            // comboBoxReadReportConfigDirIsRx
            // 
            this.comboBoxReadReportConfigDirIsRx.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxReadReportConfigDirIsRx.FormattingEnabled = true;
            this.comboBoxReadReportConfigDirIsRx.Location = new System.Drawing.Point(884, 152);
            this.comboBoxReadReportConfigDirIsRx.Name = "comboBoxReadReportConfigDirIsRx";
            this.comboBoxReadReportConfigDirIsRx.Size = new System.Drawing.Size(106, 21);
            this.comboBoxReadReportConfigDirIsRx.TabIndex = 43;
            this.comboBoxReadReportConfigDirIsRx.MouseLeave += new System.EventHandler(this.comboBoxReadReportConfigDirIsRx_MouseLeave);
            this.comboBoxReadReportConfigDirIsRx.MouseHover += new System.EventHandler(this.comboBoxReadReportConfigDirIsRx_MouseHover);
            // 
            // textBoxReadReportConfigAttribID
            // 
            this.textBoxReadReportConfigAttribID.Location = new System.Drawing.Point(770, 153);
            this.textBoxReadReportConfigAttribID.Name = "textBoxReadReportConfigAttribID";
            this.textBoxReadReportConfigAttribID.Size = new System.Drawing.Size(107, 20);
            this.textBoxReadReportConfigAttribID.TabIndex = 42;
            this.textBoxReadReportConfigAttribID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadReportConfigAttribID_MouseClick);
            this.textBoxReadReportConfigAttribID.Leave += new System.EventHandler(this.textBoxReadReportConfigAttribID_Leave);
            this.textBoxReadReportConfigAttribID.MouseLeave += new System.EventHandler(this.textBoxReadReportConfigAttribID_MouseLeave);
            this.textBoxReadReportConfigAttribID.MouseHover += new System.EventHandler(this.textBoxReadReportConfigAttribID_MouseHover);
            // 
            // textBoxReadReportConfigClusterID
            // 
            this.textBoxReadReportConfigClusterID.Location = new System.Drawing.Point(545, 153);
            this.textBoxReadReportConfigClusterID.Name = "textBoxReadReportConfigClusterID";
            this.textBoxReadReportConfigClusterID.Size = new System.Drawing.Size(106, 20);
            this.textBoxReadReportConfigClusterID.TabIndex = 40;
            this.textBoxReadReportConfigClusterID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadReportConfigClusterID_MouseClick);
            this.textBoxReadReportConfigClusterID.Leave += new System.EventHandler(this.textBoxReadReportConfigClusterID_Leave);
            this.textBoxReadReportConfigClusterID.MouseLeave += new System.EventHandler(this.textBoxReadReportConfigClusterID_MouseLeave);
            this.textBoxReadReportConfigClusterID.MouseHover += new System.EventHandler(this.textBoxReadReportConfigClusterID_MouseHover);
            // 
            // textBoxReadReportConfigDstEP
            // 
            this.textBoxReadReportConfigDstEP.Location = new System.Drawing.Point(432, 153);
            this.textBoxReadReportConfigDstEP.Name = "textBoxReadReportConfigDstEP";
            this.textBoxReadReportConfigDstEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxReadReportConfigDstEP.TabIndex = 39;
            this.textBoxReadReportConfigDstEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadReportConfigDstEP_MouseClick);
            this.textBoxReadReportConfigDstEP.Leave += new System.EventHandler(this.textBoxReadReportConfigDstEP_Leave);
            this.textBoxReadReportConfigDstEP.MouseLeave += new System.EventHandler(this.textBoxReadReportConfigDstEP_MouseLeave);
            this.textBoxReadReportConfigDstEP.MouseHover += new System.EventHandler(this.textBoxReadReportConfigDstEP_MouseHover);
            // 
            // textBoxReadReportConfigSrcEP
            // 
            this.textBoxReadReportConfigSrcEP.Location = new System.Drawing.Point(318, 153);
            this.textBoxReadReportConfigSrcEP.Name = "textBoxReadReportConfigSrcEP";
            this.textBoxReadReportConfigSrcEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxReadReportConfigSrcEP.TabIndex = 38;
            this.textBoxReadReportConfigSrcEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadReportConfigSrcEP_MouseClick);
            this.textBoxReadReportConfigSrcEP.Leave += new System.EventHandler(this.textBoxReadReportConfigSrcEP_Leave);
            this.textBoxReadReportConfigSrcEP.MouseLeave += new System.EventHandler(this.textBoxReadReportConfigSrcEP_MouseLeave);
            this.textBoxReadReportConfigSrcEP.MouseHover += new System.EventHandler(this.textBoxReadReportConfigSrcEP_MouseHover);
            // 
            // textBoxReadReportConfigTargetAddr
            // 
            this.textBoxReadReportConfigTargetAddr.Location = new System.Drawing.Point(205, 153);
            this.textBoxReadReportConfigTargetAddr.Name = "textBoxReadReportConfigTargetAddr";
            this.textBoxReadReportConfigTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxReadReportConfigTargetAddr.TabIndex = 37;
            this.textBoxReadReportConfigTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadReportConfigTargetAddr_MouseClick);
            this.textBoxReadReportConfigTargetAddr.Leave += new System.EventHandler(this.textBoxReadReportConfigTargetAddr_Leave);
            this.textBoxReadReportConfigTargetAddr.MouseLeave += new System.EventHandler(this.textBoxReadReportConfigTargetAddr_MouseLeave);
            this.textBoxReadReportConfigTargetAddr.MouseHover += new System.EventHandler(this.textBoxReadReportConfigTargetAddr_MouseHover);
            // 
            // comboBoxReadReportConfigAddrMode
            // 
            this.comboBoxReadReportConfigAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxReadReportConfigAddrMode.FormattingEnabled = true;
            this.comboBoxReadReportConfigAddrMode.Location = new System.Drawing.Point(93, 153);
            this.comboBoxReadReportConfigAddrMode.Name = "comboBoxReadReportConfigAddrMode";
            this.comboBoxReadReportConfigAddrMode.Size = new System.Drawing.Size(106, 21);
            this.comboBoxReadReportConfigAddrMode.TabIndex = 36;
            this.comboBoxReadReportConfigAddrMode.MouseLeave += new System.EventHandler(this.comboBoxReadReportConfigAddrMode_MouseLeave);
            this.comboBoxReadReportConfigAddrMode.MouseHover += new System.EventHandler(this.comboBoxReadReportConfigAddrMode_MouseHover);
            // 
            // buttonReadReportConfig
            // 
            this.buttonReadReportConfig.Location = new System.Drawing.Point(6, 150);
            this.buttonReadReportConfig.Name = "buttonReadReportConfig";
            this.buttonReadReportConfig.Size = new System.Drawing.Size(80, 24);
            this.buttonReadReportConfig.TabIndex = 35;
            this.buttonReadReportConfig.Text = "Read Rprt";
            this.buttonReadReportConfig.UseVisualStyleBackColor = true;
            this.buttonReadReportConfig.Click += new System.EventHandler(this.buttonReadReportConfig_Click);
            // 
            // textBoxWriteAttribManuID
            // 
            this.textBoxWriteAttribManuID.Location = new System.Drawing.Point(1110, 37);
            this.textBoxWriteAttribManuID.Name = "textBoxWriteAttribManuID";
            this.textBoxWriteAttribManuID.Size = new System.Drawing.Size(106, 20);
            this.textBoxWriteAttribManuID.TabIndex = 20;
            this.textBoxWriteAttribManuID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxWriteAttribManuID_MouseClick);
            this.textBoxWriteAttribManuID.Leave += new System.EventHandler(this.textBoxWriteAttribManuID_Leave);
            this.textBoxWriteAttribManuID.MouseLeave += new System.EventHandler(this.textBoxWriteAttribManuID_MouseLeave);
            this.textBoxWriteAttribManuID.MouseHover += new System.EventHandler(this.textBoxWriteAttribManuID_MouseHover);
            // 
            // comboBoxWriteAttribManuSpecific
            // 
            this.comboBoxWriteAttribManuSpecific.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxWriteAttribManuSpecific.FormattingEnabled = true;
            this.comboBoxWriteAttribManuSpecific.Location = new System.Drawing.Point(998, 37);
            this.comboBoxWriteAttribManuSpecific.Name = "comboBoxWriteAttribManuSpecific";
            this.comboBoxWriteAttribManuSpecific.Size = new System.Drawing.Size(106, 21);
            this.comboBoxWriteAttribManuSpecific.TabIndex = 19;
            this.comboBoxWriteAttribManuSpecific.MouseLeave += new System.EventHandler(this.comboBoxWriteAttribManuSpecific_MouseLeave);
            this.comboBoxWriteAttribManuSpecific.MouseHover += new System.EventHandler(this.comboBoxWriteAttribManuSpecific_MouseHover);
            // 
            // textBoxWriteAttribDataType
            // 
            this.textBoxWriteAttribDataType.Location = new System.Drawing.Point(771, 37);
            this.textBoxWriteAttribDataType.Name = "textBoxWriteAttribDataType";
            this.textBoxWriteAttribDataType.Size = new System.Drawing.Size(107, 20);
            this.textBoxWriteAttribDataType.TabIndex = 17;
            this.textBoxWriteAttribDataType.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxWriteAttribDataType_MouseClick);
            this.textBoxWriteAttribDataType.Leave += new System.EventHandler(this.textBoxWriteAttribDataType_Leave);
            this.textBoxWriteAttribDataType.MouseLeave += new System.EventHandler(this.textBoxWriteAttribDataType_MouseLeave);
            this.textBoxWriteAttribDataType.MouseHover += new System.EventHandler(this.textBoxWriteAttribDataType_MouseHover);
            // 
            // textBoxReadAttribManuID
            // 
            this.textBoxReadAttribManuID.Location = new System.Drawing.Point(998, 8);
            this.textBoxReadAttribManuID.Name = "textBoxReadAttribManuID";
            this.textBoxReadAttribManuID.Size = new System.Drawing.Size(106, 20);
            this.textBoxReadAttribManuID.TabIndex = 9;
            this.textBoxReadAttribManuID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadAttribManuID_MouseClick);
            this.textBoxReadAttribManuID.Leave += new System.EventHandler(this.textBoxReadAttribManuID_Leave);
            this.textBoxReadAttribManuID.MouseLeave += new System.EventHandler(this.textBoxReadAttribManuID_MouseLeave);
            this.textBoxReadAttribManuID.MouseHover += new System.EventHandler(this.textBoxReadAttribManuID_MouseHover);
            // 
            // comboBoxReadAttribManuSpecific
            // 
            this.comboBoxReadAttribManuSpecific.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxReadAttribManuSpecific.FormattingEnabled = true;
            this.comboBoxReadAttribManuSpecific.Location = new System.Drawing.Point(884, 8);
            this.comboBoxReadAttribManuSpecific.Name = "comboBoxReadAttribManuSpecific";
            this.comboBoxReadAttribManuSpecific.Size = new System.Drawing.Size(106, 21);
            this.comboBoxReadAttribManuSpecific.TabIndex = 8;
            this.comboBoxReadAttribManuSpecific.MouseLeave += new System.EventHandler(this.comboBoxReadAttribManuSpecific_MouseLeave);
            this.comboBoxReadAttribManuSpecific.MouseHover += new System.EventHandler(this.comboBoxReadAttribManuSpecific_MouseHover);
            // 
            // comboBoxConfigReportAddrMode
            // 
            this.comboBoxConfigReportAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxConfigReportAddrMode.FormattingEnabled = true;
            this.comboBoxConfigReportAddrMode.Location = new System.Drawing.Point(93, 66);
            this.comboBoxConfigReportAddrMode.Name = "comboBoxConfigReportAddrMode";
            this.comboBoxConfigReportAddrMode.Size = new System.Drawing.Size(106, 21);
            this.comboBoxConfigReportAddrMode.TabIndex = 22;
            this.comboBoxConfigReportAddrMode.MouseLeave += new System.EventHandler(this.comboBoxConfigReportAddrMode_MouseLeave);
            this.comboBoxConfigReportAddrMode.MouseHover += new System.EventHandler(this.comboBoxConfigReportAddrMode_MouseHover);
            // 
            // textBoxWriteAttribData
            // 
            this.textBoxWriteAttribData.Location = new System.Drawing.Point(884, 37);
            this.textBoxWriteAttribData.Name = "textBoxWriteAttribData";
            this.textBoxWriteAttribData.Size = new System.Drawing.Size(106, 20);
            this.textBoxWriteAttribData.TabIndex = 18;
            this.textBoxWriteAttribData.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxWriteAttribData_MouseClick);
            this.textBoxWriteAttribData.Leave += new System.EventHandler(this.textBoxWriteAttribData_Leave);
            this.textBoxWriteAttribData.MouseLeave += new System.EventHandler(this.textBoxWriteAttribData_MouseLeave);
            this.textBoxWriteAttribData.MouseHover += new System.EventHandler(this.textBoxWriteAttribData_MouseHover);
            // 
            // textBoxWriteAttribID
            // 
            this.textBoxWriteAttribID.Location = new System.Drawing.Point(658, 37);
            this.textBoxWriteAttribID.Name = "textBoxWriteAttribID";
            this.textBoxWriteAttribID.Size = new System.Drawing.Size(106, 20);
            this.textBoxWriteAttribID.TabIndex = 16;
            this.textBoxWriteAttribID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxWriteAttribID_MouseClick);
            this.textBoxWriteAttribID.Leave += new System.EventHandler(this.textBoxWriteAttribID_Leave);
            this.textBoxWriteAttribID.MouseLeave += new System.EventHandler(this.textBoxWriteAttribID_MouseLeave);
            this.textBoxWriteAttribID.MouseHover += new System.EventHandler(this.textBoxWriteAttribID_MouseHover);
            // 
            // comboBoxWriteAttribDirection
            // 
            this.comboBoxWriteAttribDirection.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxWriteAttribDirection.FormattingEnabled = true;
            this.comboBoxWriteAttribDirection.Location = new System.Drawing.Point(545, 37);
            this.comboBoxWriteAttribDirection.Name = "comboBoxWriteAttribDirection";
            this.comboBoxWriteAttribDirection.Size = new System.Drawing.Size(106, 21);
            this.comboBoxWriteAttribDirection.TabIndex = 15;
            this.comboBoxWriteAttribDirection.MouseLeave += new System.EventHandler(this.comboBoxWriteAttribDirection_MouseLeave);
            this.comboBoxWriteAttribDirection.MouseHover += new System.EventHandler(this.comboBoxWriteAttribDirection_MouseHover);
            // 
            // textBoxWriteAttribClusterID
            // 
            this.textBoxWriteAttribClusterID.Location = new System.Drawing.Point(432, 37);
            this.textBoxWriteAttribClusterID.Name = "textBoxWriteAttribClusterID";
            this.textBoxWriteAttribClusterID.Size = new System.Drawing.Size(106, 20);
            this.textBoxWriteAttribClusterID.TabIndex = 14;
            this.textBoxWriteAttribClusterID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxWriteAttribClusterID_MouseClick);
            this.textBoxWriteAttribClusterID.Leave += new System.EventHandler(this.textBoxWriteAttribClusterID_Leave);
            this.textBoxWriteAttribClusterID.MouseLeave += new System.EventHandler(this.textBoxWriteAttribClusterID_MouseLeave);
            this.textBoxWriteAttribClusterID.MouseHover += new System.EventHandler(this.textBoxWriteAttribClusterID_MouseHover);
            // 
            // textBoxWriteAttribDstEP
            // 
            this.textBoxWriteAttribDstEP.Location = new System.Drawing.Point(319, 37);
            this.textBoxWriteAttribDstEP.Name = "textBoxWriteAttribDstEP";
            this.textBoxWriteAttribDstEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxWriteAttribDstEP.TabIndex = 13;
            this.textBoxWriteAttribDstEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxWriteAttribDstEP_MouseClick);
            this.textBoxWriteAttribDstEP.Leave += new System.EventHandler(this.textBoxWriteAttribDstEP_Leave);
            this.textBoxWriteAttribDstEP.MouseLeave += new System.EventHandler(this.textBoxWriteAttribDstEP_MouseLeave);
            this.textBoxWriteAttribDstEP.MouseHover += new System.EventHandler(this.textBoxWriteAttribDstEP_MouseHover);
            // 
            // textBoxWriteAttribSrcEP
            // 
            this.textBoxWriteAttribSrcEP.Location = new System.Drawing.Point(206, 37);
            this.textBoxWriteAttribSrcEP.Name = "textBoxWriteAttribSrcEP";
            this.textBoxWriteAttribSrcEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxWriteAttribSrcEP.TabIndex = 12;
            this.textBoxWriteAttribSrcEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxWriteAttribSrcEP_MouseClick);
            this.textBoxWriteAttribSrcEP.Leave += new System.EventHandler(this.textBoxWriteAttribSrcEP_Leave);
            this.textBoxWriteAttribSrcEP.MouseLeave += new System.EventHandler(this.textBoxWriteAttribSrcEP_MouseLeave);
            this.textBoxWriteAttribSrcEP.MouseHover += new System.EventHandler(this.textBoxWriteAttribSrcEP_MouseHover);
            // 
            // textBoxWriteAttribTargetAddr
            // 
            this.textBoxWriteAttribTargetAddr.Location = new System.Drawing.Point(93, 37);
            this.textBoxWriteAttribTargetAddr.Name = "textBoxWriteAttribTargetAddr";
            this.textBoxWriteAttribTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxWriteAttribTargetAddr.TabIndex = 11;
            this.textBoxWriteAttribTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxWriteAttribTargetAddr_MouseClick);
            this.textBoxWriteAttribTargetAddr.Leave += new System.EventHandler(this.textBoxWriteAttribTargetAddr_Leave);
            this.textBoxWriteAttribTargetAddr.MouseLeave += new System.EventHandler(this.textBoxWriteAttribTargetAddr_MouseLeave);
            this.textBoxWriteAttribTargetAddr.MouseHover += new System.EventHandler(this.textBoxWriteAttribTargetAddr_MouseHover);
            // 
            // textBoxConfigReportChange
            // 
            this.textBoxConfigReportChange.Location = new System.Drawing.Point(998, 117);
            this.textBoxConfigReportChange.Name = "textBoxConfigReportChange";
            this.textBoxConfigReportChange.Size = new System.Drawing.Size(106, 20);
            this.textBoxConfigReportChange.TabIndex = 34;
            this.textBoxConfigReportChange.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxConfigReportChange_MouseClick);
            this.textBoxConfigReportChange.Leave += new System.EventHandler(this.textBoxConfigReportChange_Leave);
            this.textBoxConfigReportChange.MouseLeave += new System.EventHandler(this.textBoxConfigReportChange_MouseLeave);
            this.textBoxConfigReportChange.MouseHover += new System.EventHandler(this.textBoxConfigReportChange_MouseHover);
            // 
            // textBoxConfigReportTimeOut
            // 
            this.textBoxConfigReportTimeOut.Location = new System.Drawing.Point(886, 117);
            this.textBoxConfigReportTimeOut.Name = "textBoxConfigReportTimeOut";
            this.textBoxConfigReportTimeOut.Size = new System.Drawing.Size(106, 20);
            this.textBoxConfigReportTimeOut.TabIndex = 33;
            this.textBoxConfigReportTimeOut.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxConfigReportTimeOut_MouseClick);
            this.textBoxConfigReportTimeOut.Leave += new System.EventHandler(this.textBoxConfigReportTimeOut_Leave);
            this.textBoxConfigReportTimeOut.MouseLeave += new System.EventHandler(this.textBoxConfigReportTimeOut_MouseLeave);
            this.textBoxConfigReportTimeOut.MouseHover += new System.EventHandler(this.textBoxConfigReportTimeOut_MouseHover);
            // 
            // textBoxConfigReportMaxInterval
            // 
            this.textBoxConfigReportMaxInterval.Location = new System.Drawing.Point(998, 91);
            this.textBoxConfigReportMaxInterval.Name = "textBoxConfigReportMaxInterval";
            this.textBoxConfigReportMaxInterval.Size = new System.Drawing.Size(106, 20);
            this.textBoxConfigReportMaxInterval.TabIndex = 32;
            this.textBoxConfigReportMaxInterval.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxConfigReportMaxInterval_MouseClick);
            this.textBoxConfigReportMaxInterval.Leave += new System.EventHandler(this.textBoxConfigReportMaxInterval_Leave);
            this.textBoxConfigReportMaxInterval.MouseLeave += new System.EventHandler(this.textBoxConfigReportMaxInterval_MouseLeave);
            this.textBoxConfigReportMaxInterval.MouseHover += new System.EventHandler(this.textBoxConfigReportMaxInterval_MouseHover);
            // 
            // textBoxDiscoverAttributesMaxIDs
            // 
            this.textBoxDiscoverAttributesMaxIDs.Location = new System.Drawing.Point(767, 210);
            this.textBoxDiscoverAttributesMaxIDs.Name = "textBoxDiscoverAttributesMaxIDs";
            this.textBoxDiscoverAttributesMaxIDs.Size = new System.Drawing.Size(110, 20);
            this.textBoxDiscoverAttributesMaxIDs.TabIndex = 57;
            this.textBoxDiscoverAttributesMaxIDs.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDiscoverAttributesMaxIDs_MouseClick);
            this.textBoxDiscoverAttributesMaxIDs.Leave += new System.EventHandler(this.textBoxDiscoverAttributesMaxIDs_Leave);
            this.textBoxDiscoverAttributesMaxIDs.MouseLeave += new System.EventHandler(this.textBoxDiscoverAttributesMaxIDs_MouseLeave);
            this.textBoxDiscoverAttributesMaxIDs.MouseHover += new System.EventHandler(this.textBoxDiscoverAttributesMaxIDs_MouseHover);
            // 
            // comboBoxDiscoverAttributesDirection
            // 
            this.comboBoxDiscoverAttributesDirection.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDiscoverAttributesDirection.FormattingEnabled = true;
            this.comboBoxDiscoverAttributesDirection.Location = new System.Drawing.Point(654, 210);
            this.comboBoxDiscoverAttributesDirection.Name = "comboBoxDiscoverAttributesDirection";
            this.comboBoxDiscoverAttributesDirection.Size = new System.Drawing.Size(106, 21);
            this.comboBoxDiscoverAttributesDirection.TabIndex = 56;
            this.comboBoxDiscoverAttributesDirection.MouseLeave += new System.EventHandler(this.comboBoxDiscoverAttributesDirection_MouseLeave);
            this.comboBoxDiscoverAttributesDirection.MouseHover += new System.EventHandler(this.comboBoxDiscoverAttributesDirection_MouseHover);
            // 
            // textBoxDiscoverAttributesClusterID
            // 
            this.textBoxDiscoverAttributesClusterID.Location = new System.Drawing.Point(431, 210);
            this.textBoxDiscoverAttributesClusterID.Name = "textBoxDiscoverAttributesClusterID";
            this.textBoxDiscoverAttributesClusterID.Size = new System.Drawing.Size(102, 20);
            this.textBoxDiscoverAttributesClusterID.TabIndex = 54;
            this.textBoxDiscoverAttributesClusterID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDiscoverAttributesClusterID_MouseClick);
            this.textBoxDiscoverAttributesClusterID.Leave += new System.EventHandler(this.textBoxDiscoverAttributesClusterID_Leave);
            this.textBoxDiscoverAttributesClusterID.MouseLeave += new System.EventHandler(this.textBoxDiscoverAttributesClusterID_MouseLeave);
            this.textBoxDiscoverAttributesClusterID.MouseHover += new System.EventHandler(this.textBoxDiscoverAttributesClusterID_MouseHover);
            // 
            // textBoxDiscoverAttributesDstEp
            // 
            this.textBoxDiscoverAttributesDstEp.Location = new System.Drawing.Point(319, 210);
            this.textBoxDiscoverAttributesDstEp.Name = "textBoxDiscoverAttributesDstEp";
            this.textBoxDiscoverAttributesDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxDiscoverAttributesDstEp.TabIndex = 53;
            this.textBoxDiscoverAttributesDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDiscoverAttributesDstEp_MouseClick);
            this.textBoxDiscoverAttributesDstEp.Leave += new System.EventHandler(this.textBoxDiscoverAttributesDstEp_Leave);
            this.textBoxDiscoverAttributesDstEp.MouseLeave += new System.EventHandler(this.textBoxDiscoverAttributesDstEp_MouseLeave);
            this.textBoxDiscoverAttributesDstEp.MouseHover += new System.EventHandler(this.textBoxDiscoverAttributesDstEp_MouseHover);
            // 
            // textBoxDiscoverAttributesSrcEp
            // 
            this.textBoxDiscoverAttributesSrcEp.Location = new System.Drawing.Point(206, 210);
            this.textBoxDiscoverAttributesSrcEp.Name = "textBoxDiscoverAttributesSrcEp";
            this.textBoxDiscoverAttributesSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxDiscoverAttributesSrcEp.TabIndex = 52;
            this.textBoxDiscoverAttributesSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDiscoverAttributesSrcEp_MouseClick);
            this.textBoxDiscoverAttributesSrcEp.Leave += new System.EventHandler(this.textBoxDiscoverAttributesSrcEp_Leave);
            this.textBoxDiscoverAttributesSrcEp.MouseLeave += new System.EventHandler(this.textBoxDiscoverAttributesSrcEp_MouseLeave);
            this.textBoxDiscoverAttributesSrcEp.MouseHover += new System.EventHandler(this.textBoxDiscoverAttributesSrcEp_MouseHover);
            // 
            // textBoxDiscoverAttributesAddr
            // 
            this.textBoxDiscoverAttributesAddr.Location = new System.Drawing.Point(108, 210);
            this.textBoxDiscoverAttributesAddr.Name = "textBoxDiscoverAttributesAddr";
            this.textBoxDiscoverAttributesAddr.Size = new System.Drawing.Size(91, 20);
            this.textBoxDiscoverAttributesAddr.TabIndex = 51;
            this.textBoxDiscoverAttributesAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDiscoverAttributesAddr_MouseClick);
            this.textBoxDiscoverAttributesAddr.Leave += new System.EventHandler(this.textBoxDiscoverAttributesAddr_Leave);
            this.textBoxDiscoverAttributesAddr.MouseLeave += new System.EventHandler(this.textBoxDiscoverAttributesAddr_MouseLeave);
            this.textBoxDiscoverAttributesAddr.MouseHover += new System.EventHandler(this.textBoxDiscoverAttributesAddr_MouseHover);
            // 
            // buttonDiscoverAttributes
            // 
            this.buttonDiscoverAttributes.Location = new System.Drawing.Point(6, 208);
            this.buttonDiscoverAttributes.Name = "buttonDiscoverAttributes";
            this.buttonDiscoverAttributes.Size = new System.Drawing.Size(95, 22);
            this.buttonDiscoverAttributes.TabIndex = 50;
            this.buttonDiscoverAttributes.Text = "Disc Attribs";
            this.buttonDiscoverAttributes.UseVisualStyleBackColor = true;
            this.buttonDiscoverAttributes.Click += new System.EventHandler(this.buttonDiscoverAttributes_Click);
            // 
            // comboBoxReadAllAttribDirection
            // 
            this.comboBoxReadAllAttribDirection.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxReadAllAttribDirection.FormattingEnabled = true;
            this.comboBoxReadAllAttribDirection.Location = new System.Drawing.Point(541, 181);
            this.comboBoxReadAllAttribDirection.Name = "comboBoxReadAllAttribDirection";
            this.comboBoxReadAllAttribDirection.Size = new System.Drawing.Size(106, 21);
            this.comboBoxReadAllAttribDirection.TabIndex = 49;
            this.comboBoxReadAllAttribDirection.Visible = false;
            this.comboBoxReadAllAttribDirection.MouseLeave += new System.EventHandler(this.comboBoxReadAllAttribDirection_MouseLeave);
            this.comboBoxReadAllAttribDirection.MouseHover += new System.EventHandler(this.comboBoxReadAllAttribDirection_MouseHover);
            // 
            // textBoxReadAllAttribClusterID
            // 
            this.textBoxReadAllAttribClusterID.Location = new System.Drawing.Point(431, 182);
            this.textBoxReadAllAttribClusterID.Name = "textBoxReadAllAttribClusterID";
            this.textBoxReadAllAttribClusterID.Size = new System.Drawing.Size(103, 20);
            this.textBoxReadAllAttribClusterID.TabIndex = 48;
            this.textBoxReadAllAttribClusterID.Visible = false;
            this.textBoxReadAllAttribClusterID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadAllAttribClusterID_MouseClick);
            this.textBoxReadAllAttribClusterID.Leave += new System.EventHandler(this.textBoxReadAllAttribClusterID_Leave);
            this.textBoxReadAllAttribClusterID.MouseLeave += new System.EventHandler(this.textBoxReadAllAttribClusterID_MouseLeave);
            this.textBoxReadAllAttribClusterID.MouseHover += new System.EventHandler(this.textBoxReadAllAttribClusterID_MouseHover);
            // 
            // textBoxReadAllAttribDstEP
            // 
            this.textBoxReadAllAttribDstEP.Location = new System.Drawing.Point(319, 182);
            this.textBoxReadAllAttribDstEP.Name = "textBoxReadAllAttribDstEP";
            this.textBoxReadAllAttribDstEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxReadAllAttribDstEP.TabIndex = 47;
            this.textBoxReadAllAttribDstEP.Visible = false;
            this.textBoxReadAllAttribDstEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadAllAttribDstEP_MouseClick);
            this.textBoxReadAllAttribDstEP.Leave += new System.EventHandler(this.textBoxReadAllAttribDstEP_Leave);
            this.textBoxReadAllAttribDstEP.MouseLeave += new System.EventHandler(this.textBoxReadAllAttribDstEP_MouseLeave);
            this.textBoxReadAllAttribDstEP.MouseHover += new System.EventHandler(this.textBoxReadAllAttribDstEP_MouseHover);
            // 
            // textBoxReadAllAttribSrcEP
            // 
            this.textBoxReadAllAttribSrcEP.Location = new System.Drawing.Point(206, 183);
            this.textBoxReadAllAttribSrcEP.Name = "textBoxReadAllAttribSrcEP";
            this.textBoxReadAllAttribSrcEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxReadAllAttribSrcEP.TabIndex = 46;
            this.textBoxReadAllAttribSrcEP.Visible = false;
            this.textBoxReadAllAttribSrcEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadAllAttribSrcEP_MouseClick);
            this.textBoxReadAllAttribSrcEP.Leave += new System.EventHandler(this.textBoxReadAllAttribSrcEP_Leave);
            this.textBoxReadAllAttribSrcEP.MouseLeave += new System.EventHandler(this.textBoxReadAllAttribSrcEP_MouseLeave);
            this.textBoxReadAllAttribSrcEP.MouseHover += new System.EventHandler(this.textBoxReadAllAttribSrcEP_MouseHover);
            // 
            // textBoxReadAllAttribAddr
            // 
            this.textBoxReadAllAttribAddr.Location = new System.Drawing.Point(108, 183);
            this.textBoxReadAllAttribAddr.Name = "textBoxReadAllAttribAddr";
            this.textBoxReadAllAttribAddr.Size = new System.Drawing.Size(91, 20);
            this.textBoxReadAllAttribAddr.TabIndex = 45;
            this.textBoxReadAllAttribAddr.Visible = false;
            this.textBoxReadAllAttribAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadAllAttribAddr_MouseClick);
            this.textBoxReadAllAttribAddr.Leave += new System.EventHandler(this.textBoxReadAllAttribAddr_Leave);
            this.textBoxReadAllAttribAddr.MouseLeave += new System.EventHandler(this.textBoxReadAllAttribAddr_MouseLeave);
            this.textBoxReadAllAttribAddr.MouseHover += new System.EventHandler(this.textBoxReadAllAttribAddr_MouseHover);
            // 
            // buttonReadAllAttrib
            // 
            this.buttonReadAllAttrib.Location = new System.Drawing.Point(6, 182);
            this.buttonReadAllAttrib.Name = "buttonReadAllAttrib";
            this.buttonReadAllAttrib.Size = new System.Drawing.Size(95, 20);
            this.buttonReadAllAttrib.TabIndex = 44;
            this.buttonReadAllAttrib.Text = "Read All Attrib";
            this.buttonReadAllAttrib.UseVisualStyleBackColor = true;
            this.buttonReadAllAttrib.Visible = false;
            // 
            // comboBoxConfigReportAttribDirection
            // 
            this.comboBoxConfigReportAttribDirection.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxConfigReportAttribDirection.FormattingEnabled = true;
            this.comboBoxConfigReportAttribDirection.Location = new System.Drawing.Point(771, 66);
            this.comboBoxConfigReportAttribDirection.Name = "comboBoxConfigReportAttribDirection";
            this.comboBoxConfigReportAttribDirection.Size = new System.Drawing.Size(107, 21);
            this.comboBoxConfigReportAttribDirection.TabIndex = 28;
            this.comboBoxConfigReportAttribDirection.SelectedIndexChanged += new System.EventHandler(this.comboBoxConfigReportAttribDirection_SelectedIndexChanged);
            this.comboBoxConfigReportAttribDirection.MouseLeave += new System.EventHandler(this.comboBoxConfigReportAttribDirection_MouseLeave);
            this.comboBoxConfigReportAttribDirection.MouseHover += new System.EventHandler(this.comboBoxConfigReportAttribDirection_MouseHover);
            // 
            // textBoxConfigReportAttribType
            // 
            this.textBoxConfigReportAttribType.Location = new System.Drawing.Point(886, 66);
            this.textBoxConfigReportAttribType.Name = "textBoxConfigReportAttribType";
            this.textBoxConfigReportAttribType.Size = new System.Drawing.Size(106, 20);
            this.textBoxConfigReportAttribType.TabIndex = 29;
            this.textBoxConfigReportAttribType.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxConfigReportAttribType_MouseClick);
            this.textBoxConfigReportAttribType.Leave += new System.EventHandler(this.textBoxConfigReportAttribType_Leave);
            this.textBoxConfigReportAttribType.MouseLeave += new System.EventHandler(this.textBoxConfigReportAttribType_MouseLeave);
            this.textBoxConfigReportAttribType.MouseHover += new System.EventHandler(this.textBoxConfigReportAttribType_MouseHover);
            // 
            // textBoxConfigReportMinInterval
            // 
            this.textBoxConfigReportMinInterval.Location = new System.Drawing.Point(886, 91);
            this.textBoxConfigReportMinInterval.Name = "textBoxConfigReportMinInterval";
            this.textBoxConfigReportMinInterval.Size = new System.Drawing.Size(106, 20);
            this.textBoxConfigReportMinInterval.TabIndex = 31;
            this.textBoxConfigReportMinInterval.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxConfigReportMinInterval_MouseClick);
            this.textBoxConfigReportMinInterval.Leave += new System.EventHandler(this.textBoxConfigReportMinInterval_Leave);
            this.textBoxConfigReportMinInterval.MouseLeave += new System.EventHandler(this.textBoxConfigReportMinInterval_MouseLeave);
            this.textBoxConfigReportMinInterval.MouseHover += new System.EventHandler(this.textBoxConfigReportMinInterval_MouseHover);
            // 
            // textBoxConfigReportAttribID
            // 
            this.textBoxConfigReportAttribID.Location = new System.Drawing.Point(998, 66);
            this.textBoxConfigReportAttribID.Name = "textBoxConfigReportAttribID";
            this.textBoxConfigReportAttribID.Size = new System.Drawing.Size(106, 20);
            this.textBoxConfigReportAttribID.TabIndex = 30;
            this.textBoxConfigReportAttribID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxConfigReportAttribID_MouseClick);
            this.textBoxConfigReportAttribID.Leave += new System.EventHandler(this.textBoxConfigReportAttribID_Leave);
            this.textBoxConfigReportAttribID.MouseLeave += new System.EventHandler(this.textBoxConfigReportAttribID_MouseLeave);
            this.textBoxConfigReportAttribID.MouseHover += new System.EventHandler(this.textBoxConfigReportAttribID_MouseHover);
            // 
            // comboBoxConfigReportDirection
            // 
            this.comboBoxConfigReportDirection.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxConfigReportDirection.FormattingEnabled = true;
            this.comboBoxConfigReportDirection.Location = new System.Drawing.Point(658, 66);
            this.comboBoxConfigReportDirection.Name = "comboBoxConfigReportDirection";
            this.comboBoxConfigReportDirection.Size = new System.Drawing.Size(106, 21);
            this.comboBoxConfigReportDirection.TabIndex = 27;
            this.comboBoxConfigReportDirection.MouseLeave += new System.EventHandler(this.comboBoxConfigReportDirection_MouseLeave);
            this.comboBoxConfigReportDirection.MouseHover += new System.EventHandler(this.comboBoxConfigReportDirection_MouseHover);
            // 
            // textBoxConfigReportClusterID
            // 
            this.textBoxConfigReportClusterID.Location = new System.Drawing.Point(545, 66);
            this.textBoxConfigReportClusterID.Name = "textBoxConfigReportClusterID";
            this.textBoxConfigReportClusterID.Size = new System.Drawing.Size(106, 20);
            this.textBoxConfigReportClusterID.TabIndex = 26;
            this.textBoxConfigReportClusterID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxConfigReportClusterID_MouseClick);
            this.textBoxConfigReportClusterID.Leave += new System.EventHandler(this.textBoxConfigReportClusterID_Leave);
            this.textBoxConfigReportClusterID.MouseLeave += new System.EventHandler(this.textBoxConfigReportClusterID_MouseLeave);
            this.textBoxConfigReportClusterID.MouseHover += new System.EventHandler(this.textBoxConfigReportClusterID_MouseHover);
            // 
            // textBoxConfigReportDstEP
            // 
            this.textBoxConfigReportDstEP.Location = new System.Drawing.Point(432, 66);
            this.textBoxConfigReportDstEP.Name = "textBoxConfigReportDstEP";
            this.textBoxConfigReportDstEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxConfigReportDstEP.TabIndex = 25;
            this.textBoxConfigReportDstEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxConfigReportDstEP_MouseClick);
            this.textBoxConfigReportDstEP.Leave += new System.EventHandler(this.textBoxConfigReportDstEP_Leave);
            this.textBoxConfigReportDstEP.MouseLeave += new System.EventHandler(this.textBoxConfigReportDstEP_MouseLeave);
            this.textBoxConfigReportDstEP.MouseHover += new System.EventHandler(this.textBoxConfigReportDstEP_MouseHover);
            // 
            // textBoxConfigReportSrcEP
            // 
            this.textBoxConfigReportSrcEP.Location = new System.Drawing.Point(319, 66);
            this.textBoxConfigReportSrcEP.Name = "textBoxConfigReportSrcEP";
            this.textBoxConfigReportSrcEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxConfigReportSrcEP.TabIndex = 24;
            this.textBoxConfigReportSrcEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxConfigReportSrcEP_MouseClick);
            this.textBoxConfigReportSrcEP.Leave += new System.EventHandler(this.textBoxConfigReportSrcEP_Leave);
            this.textBoxConfigReportSrcEP.MouseLeave += new System.EventHandler(this.textBoxConfigReportSrcEP_MouseLeave);
            this.textBoxConfigReportSrcEP.MouseHover += new System.EventHandler(this.textBoxConfigReportSrcEP_MouseHover);
            // 
            // textBoxConfigReportTargetAddr
            // 
            this.textBoxConfigReportTargetAddr.Location = new System.Drawing.Point(206, 66);
            this.textBoxConfigReportTargetAddr.Name = "textBoxConfigReportTargetAddr";
            this.textBoxConfigReportTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxConfigReportTargetAddr.TabIndex = 23;
            this.textBoxConfigReportTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxConfigReportTargetAddr_MouseClick);
            this.textBoxConfigReportTargetAddr.Leave += new System.EventHandler(this.textBoxConfigReportTargetAddr_Leave);
            this.textBoxConfigReportTargetAddr.MouseLeave += new System.EventHandler(this.textBoxConfigReportTargetAddr_MouseLeave);
            this.textBoxConfigReportTargetAddr.MouseHover += new System.EventHandler(this.textBoxConfigReportTargetAddr_MouseHover);
            // 
            // buttonConfigReport
            // 
            this.buttonConfigReport.Location = new System.Drawing.Point(6, 63);
            this.buttonConfigReport.Name = "buttonConfigReport";
            this.buttonConfigReport.Size = new System.Drawing.Size(80, 24);
            this.buttonConfigReport.TabIndex = 21;
            this.buttonConfigReport.Text = "Config Rprt";
            this.buttonConfigReport.UseVisualStyleBackColor = true;
            this.buttonConfigReport.Click += new System.EventHandler(this.buttonConfigReport_Click_1);
            // 
            // buttonWriteAttrib
            // 
            this.buttonWriteAttrib.Location = new System.Drawing.Point(6, 34);
            this.buttonWriteAttrib.Name = "buttonWriteAttrib";
            this.buttonWriteAttrib.Size = new System.Drawing.Size(80, 22);
            this.buttonWriteAttrib.TabIndex = 10;
            this.buttonWriteAttrib.Text = "Write Attrib";
            this.buttonWriteAttrib.UseVisualStyleBackColor = true;
            this.buttonWriteAttrib.Click += new System.EventHandler(this.buttonWriteAttrib_Click_1);
            // 
            // textBoxReadAttribCount
            // 
            this.textBoxReadAttribCount.Location = new System.Drawing.Point(658, 8);
            this.textBoxReadAttribCount.Name = "textBoxReadAttribCount";
            this.textBoxReadAttribCount.Size = new System.Drawing.Size(106, 20);
            this.textBoxReadAttribCount.TabIndex = 6;
            this.textBoxReadAttribCount.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadAttribCount_MouseClick);
            this.textBoxReadAttribCount.Leave += new System.EventHandler(this.textBoxReadAttribCount_Leave);
            this.textBoxReadAttribCount.MouseLeave += new System.EventHandler(this.textBoxReadAttribCount_MouseLeave);
            this.textBoxReadAttribCount.MouseHover += new System.EventHandler(this.textBoxReadAttribCount_MouseHover);
            // 
            // comboBoxReadAttribDirection
            // 
            this.comboBoxReadAttribDirection.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxReadAttribDirection.FormattingEnabled = true;
            this.comboBoxReadAttribDirection.Location = new System.Drawing.Point(545, 8);
            this.comboBoxReadAttribDirection.Name = "comboBoxReadAttribDirection";
            this.comboBoxReadAttribDirection.Size = new System.Drawing.Size(106, 21);
            this.comboBoxReadAttribDirection.TabIndex = 5;
            this.comboBoxReadAttribDirection.MouseLeave += new System.EventHandler(this.comboBoxReadAttribDirection_MouseLeave);
            this.comboBoxReadAttribDirection.MouseHover += new System.EventHandler(this.comboBoxReadAttribDirection_MouseHover);
            // 
            // textBoxReadAttribID1
            // 
            this.textBoxReadAttribID1.Location = new System.Drawing.Point(771, 8);
            this.textBoxReadAttribID1.Name = "textBoxReadAttribID1";
            this.textBoxReadAttribID1.Size = new System.Drawing.Size(106, 20);
            this.textBoxReadAttribID1.TabIndex = 7;
            this.textBoxReadAttribID1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadAttribID1_MouseClick);
            this.textBoxReadAttribID1.Leave += new System.EventHandler(this.textBoxReadAttribID1_Leave);
            this.textBoxReadAttribID1.MouseLeave += new System.EventHandler(this.textBoxReadAttribID1_MouseLeave);
            this.textBoxReadAttribID1.MouseHover += new System.EventHandler(this.textBoxReadAttribID1_MouseHover);
            // 
            // textBoxReadAttribClusterID
            // 
            this.textBoxReadAttribClusterID.Location = new System.Drawing.Point(432, 8);
            this.textBoxReadAttribClusterID.Name = "textBoxReadAttribClusterID";
            this.textBoxReadAttribClusterID.Size = new System.Drawing.Size(106, 20);
            this.textBoxReadAttribClusterID.TabIndex = 4;
            this.textBoxReadAttribClusterID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadAttribClusterID_MouseClick);
            this.textBoxReadAttribClusterID.Leave += new System.EventHandler(this.textBoxReadAttribClusterID_Leave);
            this.textBoxReadAttribClusterID.MouseLeave += new System.EventHandler(this.textBoxReadAttribClusterID_MouseLeave);
            this.textBoxReadAttribClusterID.MouseHover += new System.EventHandler(this.textBoxReadAttribClusterID_MouseHover);
            // 
            // textBoxReadAttribDstEP
            // 
            this.textBoxReadAttribDstEP.Location = new System.Drawing.Point(319, 8);
            this.textBoxReadAttribDstEP.Name = "textBoxReadAttribDstEP";
            this.textBoxReadAttribDstEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxReadAttribDstEP.TabIndex = 3;
            this.textBoxReadAttribDstEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadAttribDstEP_MouseClick);
            this.textBoxReadAttribDstEP.Leave += new System.EventHandler(this.textBoxReadAttribDstEP_Leave);
            this.textBoxReadAttribDstEP.MouseLeave += new System.EventHandler(this.textBoxReadAttribDstEP_MouseLeave);
            this.textBoxReadAttribDstEP.MouseHover += new System.EventHandler(this.textBoxReadAttribDstEP_MouseHover);
            // 
            // textBoxReadAttribSrcEP
            // 
            this.textBoxReadAttribSrcEP.Location = new System.Drawing.Point(206, 8);
            this.textBoxReadAttribSrcEP.Name = "textBoxReadAttribSrcEP";
            this.textBoxReadAttribSrcEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxReadAttribSrcEP.TabIndex = 2;
            this.textBoxReadAttribSrcEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadAttribSrcEP_MouseClick);
            this.textBoxReadAttribSrcEP.Leave += new System.EventHandler(this.textBoxReadAttribSrcEP_Leave);
            this.textBoxReadAttribSrcEP.MouseLeave += new System.EventHandler(this.textBoxReadAttribSrcEP_MouseLeave);
            this.textBoxReadAttribSrcEP.MouseHover += new System.EventHandler(this.textBoxReadAttribSrcEP_MouseHover);
            // 
            // textBoxReadAttribTargetAddr
            // 
            this.textBoxReadAttribTargetAddr.Location = new System.Drawing.Point(93, 8);
            this.textBoxReadAttribTargetAddr.Name = "textBoxReadAttribTargetAddr";
            this.textBoxReadAttribTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxReadAttribTargetAddr.TabIndex = 1;
            this.textBoxReadAttribTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxReadAttribTargetAddr_MouseClick);
            this.textBoxReadAttribTargetAddr.Leave += new System.EventHandler(this.textBoxReadAttribTargetAddr_Leave);
            this.textBoxReadAttribTargetAddr.MouseLeave += new System.EventHandler(this.textBoxReadAttribTargetAddr_MouseLeave);
            this.textBoxReadAttribTargetAddr.MouseHover += new System.EventHandler(this.textBoxReadAttribTargetAddr_MouseHover);
            // 
            // buttonReadAttrib
            // 
            this.buttonReadAttrib.Location = new System.Drawing.Point(6, 6);
            this.buttonReadAttrib.Name = "buttonReadAttrib";
            this.buttonReadAttrib.Size = new System.Drawing.Size(80, 22);
            this.buttonReadAttrib.TabIndex = 0;
            this.buttonReadAttrib.Text = "Read Attrib";
            this.buttonReadAttrib.UseVisualStyleBackColor = true;
            this.buttonReadAttrib.Click += new System.EventHandler(this.buttonReadAttrib_Click_1);
            // 
            // AHIControl
            // 
            this.AHIControl.BackColor = System.Drawing.Color.WhiteSmoke;
            this.AHIControl.Controls.Add(this.textBoxAHITxPower);
            this.AHIControl.Controls.Add(this.buttonAHISetTxPower);
            this.AHIControl.Controls.Add(this.labelUnimplemented);
            this.AHIControl.Controls.Add(this.comboBoxIPNConfigTimerId);
            this.AHIControl.Controls.Add(this.textBoxIPNConfigDioTxConfInDioMask);
            this.AHIControl.Controls.Add(this.textBoxDioSetOutputOffPinMask);
            this.AHIControl.Controls.Add(this.textBoxDioSetOutputOnPinMask);
            this.AHIControl.Controls.Add(this.buttonDioSetOutput);
            this.AHIControl.Controls.Add(this.textBoxDioSetDirectionOutputPinMask);
            this.AHIControl.Controls.Add(this.textBoxDioSetDirectionInputPinMask);
            this.AHIControl.Controls.Add(this.buttonDioSetDirection);
            this.AHIControl.Controls.Add(this.textBoxIPNConfigPollPeriod);
            this.AHIControl.Controls.Add(this.comboBoxIPNConfigRegisterCallback);
            this.AHIControl.Controls.Add(this.textBoxIPNConfigDioStatusOutDioMask);
            this.AHIControl.Controls.Add(this.textBoxIPNConfigDioRfActiveOutDioMask);
            this.AHIControl.Controls.Add(this.comboBoxIPNConfigEnable);
            this.AHIControl.Controls.Add(this.buttonInPacketNotification);
            this.AHIControl.Location = new System.Drawing.Point(4, 22);
            this.AHIControl.Name = "AHIControl";
            this.AHIControl.Padding = new System.Windows.Forms.Padding(3);
            this.AHIControl.Size = new System.Drawing.Size(1351, 416);
            this.AHIControl.TabIndex = 16;
            this.AHIControl.Text = "AHI Control";
            this.AHIControl.Click += new System.EventHandler(this.AHIControl_Click);
            // 
            // textBoxAHITxPower
            // 
            this.textBoxAHITxPower.Location = new System.Drawing.Point(94, 94);
            this.textBoxAHITxPower.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxAHITxPower.Name = "textBoxAHITxPower";
            this.textBoxAHITxPower.Size = new System.Drawing.Size(106, 20);
            this.textBoxAHITxPower.TabIndex = 17;
            this.textBoxAHITxPower.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAHITxPower_MouseClick);
            this.textBoxAHITxPower.Leave += new System.EventHandler(this.textBoxAHITxPower_Leave);
            this.textBoxAHITxPower.MouseLeave += new System.EventHandler(this.textBoxAHITxPower_MouseLeave);
            this.textBoxAHITxPower.MouseHover += new System.EventHandler(this.textBoxAHITxPower_MouseHover);
            // 
            // buttonAHISetTxPower
            // 
            this.buttonAHISetTxPower.Location = new System.Drawing.Point(7, 93);
            this.buttonAHISetTxPower.Margin = new System.Windows.Forms.Padding(2);
            this.buttonAHISetTxPower.Name = "buttonAHISetTxPower";
            this.buttonAHISetTxPower.Size = new System.Drawing.Size(79, 22);
            this.buttonAHISetTxPower.TabIndex = 16;
            this.buttonAHISetTxPower.Text = "TX Power";
            this.buttonAHISetTxPower.UseVisualStyleBackColor = true;
            this.buttonAHISetTxPower.Click += new System.EventHandler(this.buttonAHISetTxPower_Click);
            // 
            // labelUnimplemented
            // 
            this.labelUnimplemented.AutoSize = true;
            this.labelUnimplemented.Font = new System.Drawing.Font("Microsoft Sans Serif", 30F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelUnimplemented.Location = new System.Drawing.Point(518, 185);
            this.labelUnimplemented.Name = "labelUnimplemented";
            this.labelUnimplemented.Size = new System.Drawing.Size(311, 46);
            this.labelUnimplemented.TabIndex = 15;
            this.labelUnimplemented.Text = "Unimplemented";
            // 
            // comboBoxIPNConfigTimerId
            // 
            this.comboBoxIPNConfigTimerId.FormattingEnabled = true;
            this.comboBoxIPNConfigTimerId.Items.AddRange(new object[] {
            "TIMER 0",
            "TIMER 1",
            "TIMER 2",
            "TIMER 3",
            "TIMER 4"});
            this.comboBoxIPNConfigTimerId.Location = new System.Drawing.Point(732, 68);
            this.comboBoxIPNConfigTimerId.Name = "comboBoxIPNConfigTimerId";
            this.comboBoxIPNConfigTimerId.Size = new System.Drawing.Size(85, 21);
            this.comboBoxIPNConfigTimerId.TabIndex = 13;
            this.comboBoxIPNConfigTimerId.MouseLeave += new System.EventHandler(this.comboBoxIPNConfigTimerId_MouseLeave);
            this.comboBoxIPNConfigTimerId.MouseHover += new System.EventHandler(this.comboBoxIPNConfigTimerId_MouseHover);
            // 
            // textBoxIPNConfigDioTxConfInDioMask
            // 
            this.textBoxIPNConfigDioTxConfInDioMask.Location = new System.Drawing.Point(413, 68);
            this.textBoxIPNConfigDioTxConfInDioMask.Name = "textBoxIPNConfigDioTxConfInDioMask";
            this.textBoxIPNConfigDioTxConfInDioMask.Size = new System.Drawing.Size(106, 20);
            this.textBoxIPNConfigDioTxConfInDioMask.TabIndex = 10;
            this.textBoxIPNConfigDioTxConfInDioMask.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxIPNConfigDioTxConfInDioMask_MouseClick);
            this.textBoxIPNConfigDioTxConfInDioMask.Leave += new System.EventHandler(this.textBoxIPNConfigDioTxConfInDioMask_Leave);
            this.textBoxIPNConfigDioTxConfInDioMask.MouseLeave += new System.EventHandler(this.textBoxIPNConfigDioTxConfInDioMask_MouseLeave);
            this.textBoxIPNConfigDioTxConfInDioMask.MouseHover += new System.EventHandler(this.textBoxIPNConfigDioTxConfInDioMask_MouseHover);
            // 
            // textBoxDioSetOutputOffPinMask
            // 
            this.textBoxDioSetOutputOffPinMask.Location = new System.Drawing.Point(207, 38);
            this.textBoxDioSetOutputOffPinMask.Name = "textBoxDioSetOutputOffPinMask";
            this.textBoxDioSetOutputOffPinMask.Size = new System.Drawing.Size(106, 20);
            this.textBoxDioSetOutputOffPinMask.TabIndex = 5;
            this.textBoxDioSetOutputOffPinMask.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDioSetOutputOffPinMask_MouseClick);
            this.textBoxDioSetOutputOffPinMask.Leave += new System.EventHandler(this.textBoxDioSetOutputOffPinMask_Leave);
            this.textBoxDioSetOutputOffPinMask.MouseLeave += new System.EventHandler(this.textBoxDioSetOutputOffPinMask_MouseLeave);
            this.textBoxDioSetOutputOffPinMask.MouseHover += new System.EventHandler(this.textBoxDioSetOutputOffPinMask_MouseHover);
            // 
            // textBoxDioSetOutputOnPinMask
            // 
            this.textBoxDioSetOutputOnPinMask.Location = new System.Drawing.Point(94, 38);
            this.textBoxDioSetOutputOnPinMask.Name = "textBoxDioSetOutputOnPinMask";
            this.textBoxDioSetOutputOnPinMask.Size = new System.Drawing.Size(106, 20);
            this.textBoxDioSetOutputOnPinMask.TabIndex = 4;
            this.textBoxDioSetOutputOnPinMask.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDioSetOutputOnPinMask_MouseClick);
            this.textBoxDioSetOutputOnPinMask.Leave += new System.EventHandler(this.textBoxDioSetOutputOnPinMask_Leave);
            this.textBoxDioSetOutputOnPinMask.MouseLeave += new System.EventHandler(this.textBoxDioSetOutputOnPinMask_MouseLeave);
            this.textBoxDioSetOutputOnPinMask.MouseHover += new System.EventHandler(this.textBoxDioSetOutputOnPinMask_MouseHover);
            // 
            // buttonDioSetOutput
            // 
            this.buttonDioSetOutput.Location = new System.Drawing.Point(7, 37);
            this.buttonDioSetOutput.Name = "buttonDioSetOutput";
            this.buttonDioSetOutput.Size = new System.Drawing.Size(80, 22);
            this.buttonDioSetOutput.TabIndex = 3;
            this.buttonDioSetOutput.Text = "DIO Set";
            this.buttonDioSetOutput.UseVisualStyleBackColor = true;
            this.buttonDioSetOutput.Click += new System.EventHandler(this.buttonDioSetOutput_Click);
            // 
            // textBoxDioSetDirectionOutputPinMask
            // 
            this.textBoxDioSetDirectionOutputPinMask.Location = new System.Drawing.Point(207, 10);
            this.textBoxDioSetDirectionOutputPinMask.Name = "textBoxDioSetDirectionOutputPinMask";
            this.textBoxDioSetDirectionOutputPinMask.Size = new System.Drawing.Size(106, 20);
            this.textBoxDioSetDirectionOutputPinMask.TabIndex = 2;
            this.textBoxDioSetDirectionOutputPinMask.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDioSetDirectionOutputPinMask_MouseClick);
            this.textBoxDioSetDirectionOutputPinMask.Leave += new System.EventHandler(this.textBoxDioSetDirectionOutputPinMask_Leave);
            this.textBoxDioSetDirectionOutputPinMask.MouseLeave += new System.EventHandler(this.textBoxDioSetDirectionOutputPinMask_MouseLeave);
            this.textBoxDioSetDirectionOutputPinMask.MouseHover += new System.EventHandler(this.textBoxDioSetDirectionOutputPinMask_MouseHover);
            // 
            // textBoxDioSetDirectionInputPinMask
            // 
            this.textBoxDioSetDirectionInputPinMask.Location = new System.Drawing.Point(94, 10);
            this.textBoxDioSetDirectionInputPinMask.Name = "textBoxDioSetDirectionInputPinMask";
            this.textBoxDioSetDirectionInputPinMask.Size = new System.Drawing.Size(106, 20);
            this.textBoxDioSetDirectionInputPinMask.TabIndex = 1;
            this.textBoxDioSetDirectionInputPinMask.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxDioSetDirectionInputPinMask_MouseClick);
            this.textBoxDioSetDirectionInputPinMask.Leave += new System.EventHandler(this.textBoxDioSetDirectionInputPinMask_Leave);
            this.textBoxDioSetDirectionInputPinMask.MouseLeave += new System.EventHandler(this.textBoxDioSetDirectionInputPinMask_MouseLeave);
            this.textBoxDioSetDirectionInputPinMask.MouseHover += new System.EventHandler(this.textBoxDioSetDirectionInputPinMask_MouseHover);
            // 
            // buttonDioSetDirection
            // 
            this.buttonDioSetDirection.Location = new System.Drawing.Point(7, 8);
            this.buttonDioSetDirection.Name = "buttonDioSetDirection";
            this.buttonDioSetDirection.Size = new System.Drawing.Size(80, 22);
            this.buttonDioSetDirection.TabIndex = 0;
            this.buttonDioSetDirection.Text = "DIO Set Dir";
            this.buttonDioSetDirection.UseVisualStyleBackColor = true;
            this.buttonDioSetDirection.Click += new System.EventHandler(this.buttonDioSetDirection_Click);
            // 
            // textBoxIPNConfigPollPeriod
            // 
            this.textBoxIPNConfigPollPeriod.Location = new System.Drawing.Point(618, 68);
            this.textBoxIPNConfigPollPeriod.Name = "textBoxIPNConfigPollPeriod";
            this.textBoxIPNConfigPollPeriod.Size = new System.Drawing.Size(106, 20);
            this.textBoxIPNConfigPollPeriod.TabIndex = 12;
            this.textBoxIPNConfigPollPeriod.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxIPNConfigPollPeriod_MouseClick);
            this.textBoxIPNConfigPollPeriod.Leave += new System.EventHandler(this.textBoxIPNConfigPollPeriod_Leave);
            this.textBoxIPNConfigPollPeriod.MouseLeave += new System.EventHandler(this.textBoxIPNConfigPollPeriod_MouseLeave);
            this.textBoxIPNConfigPollPeriod.MouseHover += new System.EventHandler(this.textBoxIPNConfigPollPeriod_MouseHover);
            // 
            // comboBoxIPNConfigRegisterCallback
            // 
            this.comboBoxIPNConfigRegisterCallback.FormattingEnabled = true;
            this.comboBoxIPNConfigRegisterCallback.Items.AddRange(new object[] {
            "DISABLED",
            "ENABLED"});
            this.comboBoxIPNConfigRegisterCallback.Location = new System.Drawing.Point(526, 68);
            this.comboBoxIPNConfigRegisterCallback.Name = "comboBoxIPNConfigRegisterCallback";
            this.comboBoxIPNConfigRegisterCallback.Size = new System.Drawing.Size(85, 21);
            this.comboBoxIPNConfigRegisterCallback.TabIndex = 11;
            this.comboBoxIPNConfigRegisterCallback.MouseLeave += new System.EventHandler(this.comboBoxIPNConfigRegisterCallback_MouseLeave);
            this.comboBoxIPNConfigRegisterCallback.MouseHover += new System.EventHandler(this.comboBoxIPNConfigRegisterCallback_MouseHover);
            // 
            // textBoxIPNConfigDioStatusOutDioMask
            // 
            this.textBoxIPNConfigDioStatusOutDioMask.Location = new System.Drawing.Point(300, 68);
            this.textBoxIPNConfigDioStatusOutDioMask.Name = "textBoxIPNConfigDioStatusOutDioMask";
            this.textBoxIPNConfigDioStatusOutDioMask.Size = new System.Drawing.Size(106, 20);
            this.textBoxIPNConfigDioStatusOutDioMask.TabIndex = 9;
            this.textBoxIPNConfigDioStatusOutDioMask.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxIPNConfigDioStatusOutDioMask_MouseClick);
            this.textBoxIPNConfigDioStatusOutDioMask.Leave += new System.EventHandler(this.textBoxIPNConfigDioStatusOutDioMask_Leave);
            this.textBoxIPNConfigDioStatusOutDioMask.MouseLeave += new System.EventHandler(this.textBoxIPNConfigDioStatusOutDioMask_MouseLeave);
            this.textBoxIPNConfigDioStatusOutDioMask.MouseHover += new System.EventHandler(this.textBoxIPNConfigDioStatusOutDioMask_MouseHover);
            // 
            // textBoxIPNConfigDioRfActiveOutDioMask
            // 
            this.textBoxIPNConfigDioRfActiveOutDioMask.Location = new System.Drawing.Point(186, 68);
            this.textBoxIPNConfigDioRfActiveOutDioMask.Name = "textBoxIPNConfigDioRfActiveOutDioMask";
            this.textBoxIPNConfigDioRfActiveOutDioMask.Size = new System.Drawing.Size(106, 20);
            this.textBoxIPNConfigDioRfActiveOutDioMask.TabIndex = 8;
            this.textBoxIPNConfigDioRfActiveOutDioMask.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxIPNConfigDioRfActiveOutDioMask_MouseClick);
            this.textBoxIPNConfigDioRfActiveOutDioMask.Leave += new System.EventHandler(this.textBoxIPNConfigDioRfActiveOutDioMask_Leave);
            this.textBoxIPNConfigDioRfActiveOutDioMask.MouseLeave += new System.EventHandler(this.textBoxIPNConfigDioRfActiveOutDioMask_MouseLeave);
            this.textBoxIPNConfigDioRfActiveOutDioMask.MouseHover += new System.EventHandler(this.textBoxIPNConfigDioRfActiveOutDioMask_MouseHover);
            // 
            // comboBoxIPNConfigEnable
            // 
            this.comboBoxIPNConfigEnable.FormattingEnabled = true;
            this.comboBoxIPNConfigEnable.Items.AddRange(new object[] {
            "DISABLE",
            "ENABLE"});
            this.comboBoxIPNConfigEnable.Location = new System.Drawing.Point(94, 67);
            this.comboBoxIPNConfigEnable.Name = "comboBoxIPNConfigEnable";
            this.comboBoxIPNConfigEnable.Size = new System.Drawing.Size(85, 21);
            this.comboBoxIPNConfigEnable.TabIndex = 7;
            this.comboBoxIPNConfigEnable.MouseLeave += new System.EventHandler(this.comboBoxIPNConfigEnable_MouseLeave);
            this.comboBoxIPNConfigEnable.MouseHover += new System.EventHandler(this.comboBoxIPNConfigEnable_MouseHover);
            // 
            // buttonInPacketNotification
            // 
            this.buttonInPacketNotification.Location = new System.Drawing.Point(7, 65);
            this.buttonInPacketNotification.Name = "buttonInPacketNotification";
            this.buttonInPacketNotification.Size = new System.Drawing.Size(80, 22);
            this.buttonInPacketNotification.TabIndex = 6;
            this.buttonInPacketNotification.Text = "IPN Config";
            this.buttonInPacketNotification.UseVisualStyleBackColor = true;
            this.buttonInPacketNotification.Click += new System.EventHandler(this.buttonInPacketNotification_Click);
            // 
            // BasicClusterTab
            // 
            this.BasicClusterTab.BackColor = System.Drawing.Color.WhiteSmoke;
            this.BasicClusterTab.Controls.Add(this.textBoxBasicResetDstEP);
            this.BasicClusterTab.Controls.Add(this.textBoxBasicResetSrcEP);
            this.BasicClusterTab.Controls.Add(this.textBoxBasicResetTargetAddr);
            this.BasicClusterTab.Controls.Add(this.comboBoxBasicResetTargetAddrMode);
            this.BasicClusterTab.Controls.Add(this.buttonBasicReset);
            this.BasicClusterTab.Location = new System.Drawing.Point(4, 22);
            this.BasicClusterTab.Name = "BasicClusterTab";
            this.BasicClusterTab.Size = new System.Drawing.Size(1351, 416);
            this.BasicClusterTab.TabIndex = 15;
            this.BasicClusterTab.Text = "Basic Cluster";
            this.BasicClusterTab.Click += new System.EventHandler(this.BasicClusterTab_Click);
            // 
            // textBoxBasicResetDstEP
            // 
            this.textBoxBasicResetDstEP.Location = new System.Drawing.Point(442, 6);
            this.textBoxBasicResetDstEP.Name = "textBoxBasicResetDstEP";
            this.textBoxBasicResetDstEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxBasicResetDstEP.TabIndex = 4;
            this.textBoxBasicResetDstEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxBasicResetDstEP_MouseClick);
            this.textBoxBasicResetDstEP.Leave += new System.EventHandler(this.textBoxBasicResetDstEP_Leave);
            this.textBoxBasicResetDstEP.MouseLeave += new System.EventHandler(this.textBoxBasicResetDstEP_MouseLeave);
            this.textBoxBasicResetDstEP.MouseHover += new System.EventHandler(this.textBoxBasicResetDstEP_MouseHover);
            // 
            // textBoxBasicResetSrcEP
            // 
            this.textBoxBasicResetSrcEP.Location = new System.Drawing.Point(329, 6);
            this.textBoxBasicResetSrcEP.Name = "textBoxBasicResetSrcEP";
            this.textBoxBasicResetSrcEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxBasicResetSrcEP.TabIndex = 3;
            this.textBoxBasicResetSrcEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxBasicResetSrcEP_MouseClick);
            this.textBoxBasicResetSrcEP.Leave += new System.EventHandler(this.textBoxBasicResetSrcEP_Leave);
            this.textBoxBasicResetSrcEP.MouseLeave += new System.EventHandler(this.textBoxBasicResetSrcEP_MouseLeave);
            this.textBoxBasicResetSrcEP.MouseHover += new System.EventHandler(this.textBoxBasicResetSrcEP_MouseHover);
            // 
            // textBoxBasicResetTargetAddr
            // 
            this.textBoxBasicResetTargetAddr.Location = new System.Drawing.Point(215, 6);
            this.textBoxBasicResetTargetAddr.Name = "textBoxBasicResetTargetAddr";
            this.textBoxBasicResetTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxBasicResetTargetAddr.TabIndex = 2;
            this.textBoxBasicResetTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxBasicResetTargetAddr_MouseClick);
            this.textBoxBasicResetTargetAddr.TextChanged += new System.EventHandler(this.textBoxBasicResetTargetAddr_TextChanged);
            this.textBoxBasicResetTargetAddr.Leave += new System.EventHandler(this.textBoxBasicResetTargetAddr_Leave);
            this.textBoxBasicResetTargetAddr.MouseLeave += new System.EventHandler(this.textBoxBasicResetTargetAddr_MouseLeave);
            this.textBoxBasicResetTargetAddr.MouseHover += new System.EventHandler(this.textBoxBasicResetTargetAddr_MouseHover);
            // 
            // comboBoxBasicResetTargetAddrMode
            // 
            this.comboBoxBasicResetTargetAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxBasicResetTargetAddrMode.FormattingEnabled = true;
            this.comboBoxBasicResetTargetAddrMode.Location = new System.Drawing.Point(102, 6);
            this.comboBoxBasicResetTargetAddrMode.Name = "comboBoxBasicResetTargetAddrMode";
            this.comboBoxBasicResetTargetAddrMode.Size = new System.Drawing.Size(106, 21);
            this.comboBoxBasicResetTargetAddrMode.TabIndex = 1;
            this.comboBoxBasicResetTargetAddrMode.MouseLeave += new System.EventHandler(this.comboBoxBasicResetTargetAddrMode_MouseLeave);
            this.comboBoxBasicResetTargetAddrMode.MouseHover += new System.EventHandler(this.comboBoxBasicResetTargetAddrMode_MouseHover);
            // 
            // buttonBasicReset
            // 
            this.buttonBasicReset.Location = new System.Drawing.Point(3, 3);
            this.buttonBasicReset.Name = "buttonBasicReset";
            this.buttonBasicReset.Size = new System.Drawing.Size(93, 25);
            this.buttonBasicReset.TabIndex = 0;
            this.buttonBasicReset.Text = "Reset To FD";
            this.buttonBasicReset.UseVisualStyleBackColor = true;
            this.buttonBasicReset.Click += new System.EventHandler(this.buttonBasicReset_Click);
            // 
            // tabPage3
            // 
            this.tabPage3.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage3.Controls.Add(this.textBoxGroupName);
            this.tabPage3.Controls.Add(this.textBoxGroupNameMaxLength);
            this.tabPage3.Controls.Add(this.textBoxGroupNameLength);
            this.tabPage3.Controls.Add(this.buttonAddToList);
            this.tabPage3.Controls.Add(this.textBoxGroupAddIfIdentifyGroupID);
            this.tabPage3.Controls.Add(this.textBoxGroupAddIfIdentifySrcEp);
            this.tabPage3.Controls.Add(this.textBoxGroupAddIfIdentifyDstEp);
            this.tabPage3.Controls.Add(this.textBoxGroupAddIfIndentifyingTargetAddr);
            this.tabPage3.Controls.Add(this.buttonGroupAddIfIdentifying);
            this.tabPage3.Controls.Add(this.textBoxRemoveAllGroupDstEp);
            this.tabPage3.Controls.Add(this.textBoxRemoveAllGroupSrcEp);
            this.tabPage3.Controls.Add(this.textBoxRemoveAllGroupTargetAddr);
            this.tabPage3.Controls.Add(this.buttonGroupRemoveAll);
            this.tabPage3.Controls.Add(this.textBoxRemoveGroupGroupAddr);
            this.tabPage3.Controls.Add(this.textBoxRemoveGroupDstEp);
            this.tabPage3.Controls.Add(this.textBoxRemoveGroupSrcEp);
            this.tabPage3.Controls.Add(this.textBoxRemoveGroupTargetAddr);
            this.tabPage3.Controls.Add(this.buttonRemoveGroup);
            this.tabPage3.Controls.Add(this.textBoxGetGroupCount);
            this.tabPage3.Controls.Add(this.textBoxGetGroupDstEp);
            this.tabPage3.Controls.Add(this.textBoxGetGroupSrcEp);
            this.tabPage3.Controls.Add(this.textBoxGetGroupTargetAddr);
            this.tabPage3.Controls.Add(this.buttonGetGroup);
            this.tabPage3.Controls.Add(this.textBoxViewGroupGroupAddr);
            this.tabPage3.Controls.Add(this.textBoxViewGroupDstEp);
            this.tabPage3.Controls.Add(this.textBoxViewGroupSrcEp);
            this.tabPage3.Controls.Add(this.textBoxViewGroupAddr);
            this.tabPage3.Controls.Add(this.buttonViewGroup);
            this.tabPage3.Controls.Add(this.textBoxAddGroupGroupAddr);
            this.tabPage3.Controls.Add(this.textBoxAddGroupDstEp);
            this.tabPage3.Controls.Add(this.textBoxAddGroupSrcEp);
            this.tabPage3.Controls.Add(this.textBoxAddGroupAddr);
            this.tabPage3.Controls.Add(this.buttonAddGroup);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(1351, 416);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Group Cluster";
            this.tabPage3.Click += new System.EventHandler(this.tabPage3_Click);
            // 
            // textBoxGroupName
            // 
            this.textBoxGroupName.Location = new System.Drawing.Point(785, 6);
            this.textBoxGroupName.Name = "textBoxGroupName";
            this.textBoxGroupName.Size = new System.Drawing.Size(113, 20);
            this.textBoxGroupName.TabIndex = 7;
            this.textBoxGroupName.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGroupName_MouseClick);
            this.textBoxGroupName.Leave += new System.EventHandler(this.textBoxGroupName_Leave);
            this.textBoxGroupName.MouseLeave += new System.EventHandler(this.textBoxGroupName_MouseLeave);
            this.textBoxGroupName.MouseHover += new System.EventHandler(this.textBoxGroupName_MouseHover);
            // 
            // textBoxGroupNameMaxLength
            // 
            this.textBoxGroupNameMaxLength.Location = new System.Drawing.Point(666, 6);
            this.textBoxGroupNameMaxLength.Name = "textBoxGroupNameMaxLength";
            this.textBoxGroupNameMaxLength.Size = new System.Drawing.Size(113, 20);
            this.textBoxGroupNameMaxLength.TabIndex = 6;
            this.textBoxGroupNameMaxLength.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGroupNameMaxLength_MouseClick);
            this.textBoxGroupNameMaxLength.Leave += new System.EventHandler(this.textBoxGroupNameMaxLength_Leave);
            this.textBoxGroupNameMaxLength.MouseLeave += new System.EventHandler(this.textBoxGroupNameMaxLength_MouseLeave);
            this.textBoxGroupNameMaxLength.MouseHover += new System.EventHandler(this.textBoxGroupNameMaxLength_MouseHover);
            // 
            // textBoxGroupNameLength
            // 
            this.textBoxGroupNameLength.Location = new System.Drawing.Point(548, 6);
            this.textBoxGroupNameLength.Name = "textBoxGroupNameLength";
            this.textBoxGroupNameLength.Size = new System.Drawing.Size(113, 20);
            this.textBoxGroupNameLength.TabIndex = 5;
            this.textBoxGroupNameLength.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGroupNameLength_MouseClick);
            this.textBoxGroupNameLength.Leave += new System.EventHandler(this.textBoxGroupNameLength_Leave);
            this.textBoxGroupNameLength.MouseLeave += new System.EventHandler(this.textBoxGroupNameLength_MouseLeave);
            this.textBoxGroupNameLength.MouseHover += new System.EventHandler(this.textBoxGroupNameLength_MouseHover);
            // 
            // buttonAddToList
            // 
            this.buttonAddToList.Location = new System.Drawing.Point(550, 61);
            this.buttonAddToList.Name = "buttonAddToList";
            this.buttonAddToList.Size = new System.Drawing.Size(105, 22);
            this.buttonAddToList.TabIndex = 18;
            this.buttonAddToList.Text = "Add Group List";
            this.buttonAddToList.UseVisualStyleBackColor = true;
            this.buttonAddToList.Click += new System.EventHandler(this.buttonAddToList_Click);
            // 
            // textBoxGroupAddIfIdentifyGroupID
            // 
            this.textBoxGroupAddIfIdentifyGroupID.Location = new System.Drawing.Point(429, 149);
            this.textBoxGroupAddIfIdentifyGroupID.Name = "textBoxGroupAddIfIdentifyGroupID";
            this.textBoxGroupAddIfIdentifyGroupID.Size = new System.Drawing.Size(113, 20);
            this.textBoxGroupAddIfIdentifyGroupID.TabIndex = 32;
            this.textBoxGroupAddIfIdentifyGroupID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGroupAddIfIdentifyGroupID_MouseClick);
            this.textBoxGroupAddIfIdentifyGroupID.Leave += new System.EventHandler(this.textBoxGroupAddIfIdentifyGroupID_Leave);
            this.textBoxGroupAddIfIdentifyGroupID.MouseLeave += new System.EventHandler(this.textBoxGroupAddIfIdentifyGroupID_MouseLeave);
            this.textBoxGroupAddIfIdentifyGroupID.MouseHover += new System.EventHandler(this.textBoxGroupAddIfIdentifyGroupID_MouseHover);
            // 
            // textBoxGroupAddIfIdentifySrcEp
            // 
            this.textBoxGroupAddIfIdentifySrcEp.Location = new System.Drawing.Point(204, 149);
            this.textBoxGroupAddIfIdentifySrcEp.Name = "textBoxGroupAddIfIdentifySrcEp";
            this.textBoxGroupAddIfIdentifySrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxGroupAddIfIdentifySrcEp.TabIndex = 30;
            this.textBoxGroupAddIfIdentifySrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGroupAddIfIdentifySrcEp_MouseClick);
            this.textBoxGroupAddIfIdentifySrcEp.Leave += new System.EventHandler(this.textBoxGroupAddIfIdentifySrcEp_Leave);
            this.textBoxGroupAddIfIdentifySrcEp.MouseLeave += new System.EventHandler(this.textBoxGroupAddIfIdentifySrcEp_MouseLeave);
            this.textBoxGroupAddIfIdentifySrcEp.MouseHover += new System.EventHandler(this.textBoxGroupAddIfIdentifySrcEp_MouseHover);
            // 
            // textBoxGroupAddIfIdentifyDstEp
            // 
            this.textBoxGroupAddIfIdentifyDstEp.Location = new System.Drawing.Point(317, 149);
            this.textBoxGroupAddIfIdentifyDstEp.Name = "textBoxGroupAddIfIdentifyDstEp";
            this.textBoxGroupAddIfIdentifyDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxGroupAddIfIdentifyDstEp.TabIndex = 31;
            this.textBoxGroupAddIfIdentifyDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGroupAddIfIdentifyDstEp_MouseClick);
            this.textBoxGroupAddIfIdentifyDstEp.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            this.textBoxGroupAddIfIdentifyDstEp.Leave += new System.EventHandler(this.textBoxGroupAddIfIdentifyDstEp_Leave);
            this.textBoxGroupAddIfIdentifyDstEp.MouseLeave += new System.EventHandler(this.textBoxGroupAddIfIdentifyDstEp_MouseLeave);
            this.textBoxGroupAddIfIdentifyDstEp.MouseHover += new System.EventHandler(this.textBoxGroupAddIfIdentifyDstEp_MouseHover);
            // 
            // textBoxGroupAddIfIndentifyingTargetAddr
            // 
            this.textBoxGroupAddIfIndentifyingTargetAddr.Location = new System.Drawing.Point(90, 149);
            this.textBoxGroupAddIfIndentifyingTargetAddr.Name = "textBoxGroupAddIfIndentifyingTargetAddr";
            this.textBoxGroupAddIfIndentifyingTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxGroupAddIfIndentifyingTargetAddr.TabIndex = 29;
            this.textBoxGroupAddIfIndentifyingTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGroupAddIfIndentifyingTargetAddr_MouseClick);
            this.textBoxGroupAddIfIndentifyingTargetAddr.Leave += new System.EventHandler(this.textBoxGroupAddIfIndentifyingTargetAddr_Leave);
            this.textBoxGroupAddIfIndentifyingTargetAddr.MouseLeave += new System.EventHandler(this.textBoxGroupAddIfIndentifyingTargetAddr_MouseLeave);
            this.textBoxGroupAddIfIndentifyingTargetAddr.MouseHover += new System.EventHandler(this.textBoxGroupAddIfIndentifyingTargetAddr_MouseHover);
            // 
            // buttonGroupAddIfIdentifying
            // 
            this.buttonGroupAddIfIdentifying.Location = new System.Drawing.Point(4, 146);
            this.buttonGroupAddIfIdentifying.Name = "buttonGroupAddIfIdentifying";
            this.buttonGroupAddIfIdentifying.Size = new System.Drawing.Size(80, 22);
            this.buttonGroupAddIfIdentifying.TabIndex = 28;
            this.buttonGroupAddIfIdentifying.Text = "Add If Ident";
            this.buttonGroupAddIfIdentifying.UseVisualStyleBackColor = true;
            this.buttonGroupAddIfIdentifying.Click += new System.EventHandler(this.buttonGroupAddIfIdentifying_Click);
            // 
            // textBoxRemoveAllGroupDstEp
            // 
            this.textBoxRemoveAllGroupDstEp.Location = new System.Drawing.Point(317, 120);
            this.textBoxRemoveAllGroupDstEp.Name = "textBoxRemoveAllGroupDstEp";
            this.textBoxRemoveAllGroupDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveAllGroupDstEp.TabIndex = 27;
            this.textBoxRemoveAllGroupDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveAllGroupDstEp_MouseClick);
            this.textBoxRemoveAllGroupDstEp.Leave += new System.EventHandler(this.textBoxRemoveAllGroupDstEp_Leave);
            this.textBoxRemoveAllGroupDstEp.MouseLeave += new System.EventHandler(this.textBoxRemoveAllGroupDstEp_MouseLeave);
            this.textBoxRemoveAllGroupDstEp.MouseHover += new System.EventHandler(this.textBoxRemoveAllGroupDstEp_MouseHover);
            // 
            // textBoxRemoveAllGroupSrcEp
            // 
            this.textBoxRemoveAllGroupSrcEp.Location = new System.Drawing.Point(204, 121);
            this.textBoxRemoveAllGroupSrcEp.Name = "textBoxRemoveAllGroupSrcEp";
            this.textBoxRemoveAllGroupSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveAllGroupSrcEp.TabIndex = 26;
            this.textBoxRemoveAllGroupSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveAllGroupSrcEp_MouseClick);
            this.textBoxRemoveAllGroupSrcEp.Leave += new System.EventHandler(this.textBoxRemoveAllGroupSrcEp_Leave);
            this.textBoxRemoveAllGroupSrcEp.MouseLeave += new System.EventHandler(this.textBoxRemoveAllGroupSrcEp_MouseLeave);
            this.textBoxRemoveAllGroupSrcEp.MouseHover += new System.EventHandler(this.textBoxRemoveAllGroupSrcEp_MouseHover);
            // 
            // textBoxRemoveAllGroupTargetAddr
            // 
            this.textBoxRemoveAllGroupTargetAddr.Location = new System.Drawing.Point(90, 120);
            this.textBoxRemoveAllGroupTargetAddr.Name = "textBoxRemoveAllGroupTargetAddr";
            this.textBoxRemoveAllGroupTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveAllGroupTargetAddr.TabIndex = 25;
            this.textBoxRemoveAllGroupTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveAllGroupTargetAddr_MouseClick);
            this.textBoxRemoveAllGroupTargetAddr.Leave += new System.EventHandler(this.textBoxRemoveAllGroupTargetAddr_Leave);
            this.textBoxRemoveAllGroupTargetAddr.MouseLeave += new System.EventHandler(this.textBoxRemoveAllGroupTargetAddr_MouseLeave);
            this.textBoxRemoveAllGroupTargetAddr.MouseHover += new System.EventHandler(this.textBoxRemoveAllGroupTargetAddr_MouseHover);
            // 
            // buttonGroupRemoveAll
            // 
            this.buttonGroupRemoveAll.Location = new System.Drawing.Point(4, 118);
            this.buttonGroupRemoveAll.Name = "buttonGroupRemoveAll";
            this.buttonGroupRemoveAll.Size = new System.Drawing.Size(80, 22);
            this.buttonGroupRemoveAll.TabIndex = 24;
            this.buttonGroupRemoveAll.Text = "Remove All";
            this.buttonGroupRemoveAll.UseVisualStyleBackColor = true;
            this.buttonGroupRemoveAll.Click += new System.EventHandler(this.buttonGroupRemoveAll_Click);
            // 
            // textBoxRemoveGroupGroupAddr
            // 
            this.textBoxRemoveGroupGroupAddr.Location = new System.Drawing.Point(429, 91);
            this.textBoxRemoveGroupGroupAddr.Name = "textBoxRemoveGroupGroupAddr";
            this.textBoxRemoveGroupGroupAddr.Size = new System.Drawing.Size(114, 20);
            this.textBoxRemoveGroupGroupAddr.TabIndex = 23;
            this.textBoxRemoveGroupGroupAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveGroupGroupAddr_MouseClick);
            this.textBoxRemoveGroupGroupAddr.Leave += new System.EventHandler(this.textBoxRemoveGroupGroupAddr_Leave);
            this.textBoxRemoveGroupGroupAddr.MouseLeave += new System.EventHandler(this.textBoxRemoveGroupGroupAddr_MouseLeave);
            this.textBoxRemoveGroupGroupAddr.MouseHover += new System.EventHandler(this.textBoxRemoveGroupGroupAddr_MouseHover);
            // 
            // textBoxRemoveGroupDstEp
            // 
            this.textBoxRemoveGroupDstEp.Location = new System.Drawing.Point(317, 91);
            this.textBoxRemoveGroupDstEp.Name = "textBoxRemoveGroupDstEp";
            this.textBoxRemoveGroupDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveGroupDstEp.TabIndex = 22;
            this.textBoxRemoveGroupDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveGroupDstEp_MouseClick);
            this.textBoxRemoveGroupDstEp.Leave += new System.EventHandler(this.textBoxRemoveGroupDstEp_Leave);
            this.textBoxRemoveGroupDstEp.MouseLeave += new System.EventHandler(this.textBoxRemoveGroupDstEp_MouseLeave);
            this.textBoxRemoveGroupDstEp.MouseHover += new System.EventHandler(this.textBoxRemoveGroupDstEp_MouseHover);
            // 
            // textBoxRemoveGroupSrcEp
            // 
            this.textBoxRemoveGroupSrcEp.Location = new System.Drawing.Point(204, 91);
            this.textBoxRemoveGroupSrcEp.Name = "textBoxRemoveGroupSrcEp";
            this.textBoxRemoveGroupSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveGroupSrcEp.TabIndex = 21;
            this.textBoxRemoveGroupSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveGroupSrcEp_MouseClick);
            this.textBoxRemoveGroupSrcEp.Leave += new System.EventHandler(this.textBoxRemoveGroupSrcEp_Leave);
            this.textBoxRemoveGroupSrcEp.MouseLeave += new System.EventHandler(this.textBoxRemoveGroupSrcEp_MouseLeave);
            this.textBoxRemoveGroupSrcEp.MouseHover += new System.EventHandler(this.textBoxRemoveGroupSrcEp_MouseHover);
            // 
            // textBoxRemoveGroupTargetAddr
            // 
            this.textBoxRemoveGroupTargetAddr.Location = new System.Drawing.Point(90, 91);
            this.textBoxRemoveGroupTargetAddr.Name = "textBoxRemoveGroupTargetAddr";
            this.textBoxRemoveGroupTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveGroupTargetAddr.TabIndex = 20;
            this.textBoxRemoveGroupTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveGroupTargetAddr_MouseClick);
            this.textBoxRemoveGroupTargetAddr.Leave += new System.EventHandler(this.textBoxRemoveGroupTargetAddr_Leave);
            this.textBoxRemoveGroupTargetAddr.MouseLeave += new System.EventHandler(this.textBoxRemoveGroupTargetAddr_MouseLeave);
            this.textBoxRemoveGroupTargetAddr.MouseHover += new System.EventHandler(this.textBoxRemoveGroupTargetAddr_MouseHover);
            // 
            // buttonRemoveGroup
            // 
            this.buttonRemoveGroup.Location = new System.Drawing.Point(4, 90);
            this.buttonRemoveGroup.Name = "buttonRemoveGroup";
            this.buttonRemoveGroup.Size = new System.Drawing.Size(80, 22);
            this.buttonRemoveGroup.TabIndex = 19;
            this.buttonRemoveGroup.Text = "Remove Grp";
            this.buttonRemoveGroup.UseVisualStyleBackColor = true;
            this.buttonRemoveGroup.Click += new System.EventHandler(this.buttonRemoveGroup_Click);
            // 
            // textBoxGetGroupCount
            // 
            this.textBoxGetGroupCount.Location = new System.Drawing.Point(430, 63);
            this.textBoxGetGroupCount.Name = "textBoxGetGroupCount";
            this.textBoxGetGroupCount.Size = new System.Drawing.Size(113, 20);
            this.textBoxGetGroupCount.TabIndex = 17;
            this.textBoxGetGroupCount.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGetGroupCount_MouseClick);
            this.textBoxGetGroupCount.Leave += new System.EventHandler(this.textBoxGetGroupCount_Leave);
            this.textBoxGetGroupCount.MouseLeave += new System.EventHandler(this.textBoxGetGroupCount_MouseLeave);
            this.textBoxGetGroupCount.MouseHover += new System.EventHandler(this.textBoxGetGroupCount_MouseHover);
            // 
            // textBoxGetGroupDstEp
            // 
            this.textBoxGetGroupDstEp.Location = new System.Drawing.Point(317, 63);
            this.textBoxGetGroupDstEp.Name = "textBoxGetGroupDstEp";
            this.textBoxGetGroupDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxGetGroupDstEp.TabIndex = 16;
            this.textBoxGetGroupDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGetGroupDstEp_MouseClick);
            this.textBoxGetGroupDstEp.Leave += new System.EventHandler(this.textBoxGetGroupDstEp_Leave);
            this.textBoxGetGroupDstEp.MouseLeave += new System.EventHandler(this.textBoxGetGroupDstEp_MouseLeave);
            this.textBoxGetGroupDstEp.MouseHover += new System.EventHandler(this.textBoxGetGroupDstEp_MouseHover);
            // 
            // textBoxGetGroupSrcEp
            // 
            this.textBoxGetGroupSrcEp.Location = new System.Drawing.Point(204, 63);
            this.textBoxGetGroupSrcEp.Name = "textBoxGetGroupSrcEp";
            this.textBoxGetGroupSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxGetGroupSrcEp.TabIndex = 15;
            this.textBoxGetGroupSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGetGroupSrcEp_MouseClick);
            this.textBoxGetGroupSrcEp.Leave += new System.EventHandler(this.textBoxGetGroupSrcEp_Leave);
            this.textBoxGetGroupSrcEp.MouseLeave += new System.EventHandler(this.textBoxGetGroupSrcEp_MouseLeave);
            this.textBoxGetGroupSrcEp.MouseHover += new System.EventHandler(this.textBoxGetGroupSrcEp_MouseHover);
            // 
            // textBoxGetGroupTargetAddr
            // 
            this.textBoxGetGroupTargetAddr.Location = new System.Drawing.Point(90, 63);
            this.textBoxGetGroupTargetAddr.Name = "textBoxGetGroupTargetAddr";
            this.textBoxGetGroupTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxGetGroupTargetAddr.TabIndex = 14;
            this.textBoxGetGroupTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGetGroupTargetAddr_MouseClick);
            this.textBoxGetGroupTargetAddr.Leave += new System.EventHandler(this.textBoxGetGroupTargetAddr_Leave);
            this.textBoxGetGroupTargetAddr.MouseLeave += new System.EventHandler(this.textBoxGetGroupTargetAddr_MouseLeave);
            this.textBoxGetGroupTargetAddr.MouseHover += new System.EventHandler(this.textBoxGetGroupTargetAddr_MouseHover);
            // 
            // buttonGetGroup
            // 
            this.buttonGetGroup.Location = new System.Drawing.Point(4, 61);
            this.buttonGetGroup.Name = "buttonGetGroup";
            this.buttonGetGroup.Size = new System.Drawing.Size(80, 22);
            this.buttonGetGroup.TabIndex = 13;
            this.buttonGetGroup.Text = "Get Group";
            this.buttonGetGroup.UseVisualStyleBackColor = true;
            this.buttonGetGroup.Click += new System.EventHandler(this.buttonGetGroup_Click);
            // 
            // textBoxViewGroupGroupAddr
            // 
            this.textBoxViewGroupGroupAddr.Location = new System.Drawing.Point(430, 34);
            this.textBoxViewGroupGroupAddr.Name = "textBoxViewGroupGroupAddr";
            this.textBoxViewGroupGroupAddr.Size = new System.Drawing.Size(113, 20);
            this.textBoxViewGroupGroupAddr.TabIndex = 12;
            this.textBoxViewGroupGroupAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxViewGroupGroupAddr_MouseClick);
            this.textBoxViewGroupGroupAddr.Leave += new System.EventHandler(this.textBoxViewGroupGroupAddr_Leave);
            this.textBoxViewGroupGroupAddr.MouseLeave += new System.EventHandler(this.textBoxViewGroupGroupAddr_MouseLeave);
            this.textBoxViewGroupGroupAddr.MouseHover += new System.EventHandler(this.textBoxViewGroupGroupAddr_MouseHover);
            // 
            // textBoxViewGroupDstEp
            // 
            this.textBoxViewGroupDstEp.Location = new System.Drawing.Point(317, 34);
            this.textBoxViewGroupDstEp.Name = "textBoxViewGroupDstEp";
            this.textBoxViewGroupDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxViewGroupDstEp.TabIndex = 11;
            this.textBoxViewGroupDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxViewGroupDstEp_MouseClick);
            this.textBoxViewGroupDstEp.Leave += new System.EventHandler(this.textBoxViewGroupDstEp_Leave);
            this.textBoxViewGroupDstEp.MouseLeave += new System.EventHandler(this.textBoxViewGroupDstEp_MouseLeave);
            this.textBoxViewGroupDstEp.MouseHover += new System.EventHandler(this.textBoxViewGroupDstEp_MouseHover);
            // 
            // textBoxViewGroupSrcEp
            // 
            this.textBoxViewGroupSrcEp.Location = new System.Drawing.Point(204, 34);
            this.textBoxViewGroupSrcEp.Name = "textBoxViewGroupSrcEp";
            this.textBoxViewGroupSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxViewGroupSrcEp.TabIndex = 10;
            this.textBoxViewGroupSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxViewGroupSrcEp_MouseClick);
            this.textBoxViewGroupSrcEp.Leave += new System.EventHandler(this.textBoxViewGroupSrcEp_Leave);
            this.textBoxViewGroupSrcEp.MouseLeave += new System.EventHandler(this.textBoxViewGroupSrcEp_MouseLeave);
            this.textBoxViewGroupSrcEp.MouseHover += new System.EventHandler(this.textBoxViewGroupSrcEp_MouseHover);
            // 
            // textBoxViewGroupAddr
            // 
            this.textBoxViewGroupAddr.Location = new System.Drawing.Point(90, 34);
            this.textBoxViewGroupAddr.Name = "textBoxViewGroupAddr";
            this.textBoxViewGroupAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxViewGroupAddr.TabIndex = 9;
            this.textBoxViewGroupAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxViewGroupAddr_MouseClick);
            this.textBoxViewGroupAddr.Leave += new System.EventHandler(this.textBoxViewGroupAddr_Leave);
            this.textBoxViewGroupAddr.MouseLeave += new System.EventHandler(this.textBoxViewGroupAddr_MouseLeave);
            this.textBoxViewGroupAddr.MouseHover += new System.EventHandler(this.textBoxViewGroupAddr_MouseHover);
            // 
            // buttonViewGroup
            // 
            this.buttonViewGroup.Location = new System.Drawing.Point(4, 33);
            this.buttonViewGroup.Name = "buttonViewGroup";
            this.buttonViewGroup.Size = new System.Drawing.Size(80, 22);
            this.buttonViewGroup.TabIndex = 8;
            this.buttonViewGroup.Text = "View Group";
            this.buttonViewGroup.UseVisualStyleBackColor = true;
            this.buttonViewGroup.Click += new System.EventHandler(this.buttonViewGroup_Click);
            // 
            // textBoxAddGroupGroupAddr
            // 
            this.textBoxAddGroupGroupAddr.Location = new System.Drawing.Point(430, 6);
            this.textBoxAddGroupGroupAddr.Name = "textBoxAddGroupGroupAddr";
            this.textBoxAddGroupGroupAddr.Size = new System.Drawing.Size(113, 20);
            this.textBoxAddGroupGroupAddr.TabIndex = 4;
            this.textBoxAddGroupGroupAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddGroupGroupAddr_MouseClick);
            this.textBoxAddGroupGroupAddr.Leave += new System.EventHandler(this.textBoxAddGroupGroupAddr_Leave);
            this.textBoxAddGroupGroupAddr.MouseLeave += new System.EventHandler(this.textBoxAddGroupGroupAddr_MouseLeave);
            this.textBoxAddGroupGroupAddr.MouseHover += new System.EventHandler(this.textBoxAddGroupGroupAddr_MouseHover);
            // 
            // textBoxAddGroupDstEp
            // 
            this.textBoxAddGroupDstEp.Location = new System.Drawing.Point(317, 6);
            this.textBoxAddGroupDstEp.Name = "textBoxAddGroupDstEp";
            this.textBoxAddGroupDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxAddGroupDstEp.TabIndex = 3;
            this.textBoxAddGroupDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddGroupDstEp_MouseClick);
            this.textBoxAddGroupDstEp.Leave += new System.EventHandler(this.textBoxAddGroupDstEp_Leave);
            this.textBoxAddGroupDstEp.MouseLeave += new System.EventHandler(this.textBoxAddGroupDstEp_MouseLeave);
            this.textBoxAddGroupDstEp.MouseHover += new System.EventHandler(this.textBoxAddGroupDstEp_MouseHover);
            // 
            // textBoxAddGroupSrcEp
            // 
            this.textBoxAddGroupSrcEp.Location = new System.Drawing.Point(204, 6);
            this.textBoxAddGroupSrcEp.Name = "textBoxAddGroupSrcEp";
            this.textBoxAddGroupSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxAddGroupSrcEp.TabIndex = 2;
            this.textBoxAddGroupSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddGroupSrcEp_MouseClick);
            this.textBoxAddGroupSrcEp.Leave += new System.EventHandler(this.textBoxAddGroupSrcEp_Leave);
            this.textBoxAddGroupSrcEp.MouseLeave += new System.EventHandler(this.textBoxAddGroupSrcEp_MouseLeave);
            this.textBoxAddGroupSrcEp.MouseHover += new System.EventHandler(this.textBoxAddGroupSrcEp_MouseHover);
            // 
            // textBoxAddGroupAddr
            // 
            this.textBoxAddGroupAddr.Location = new System.Drawing.Point(90, 6);
            this.textBoxAddGroupAddr.Name = "textBoxAddGroupAddr";
            this.textBoxAddGroupAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxAddGroupAddr.TabIndex = 1;
            this.textBoxAddGroupAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddGroupAddr_MouseClick);
            this.textBoxAddGroupAddr.Leave += new System.EventHandler(this.textBoxAddGroupAddr_Leave);
            this.textBoxAddGroupAddr.MouseLeave += new System.EventHandler(this.textBoxAddGroupAddr_MouseLeave);
            this.textBoxAddGroupAddr.MouseHover += new System.EventHandler(this.textBoxAddGroupAddr_MouseHover);
            // 
            // buttonAddGroup
            // 
            this.buttonAddGroup.Location = new System.Drawing.Point(4, 4);
            this.buttonAddGroup.Name = "buttonAddGroup";
            this.buttonAddGroup.Size = new System.Drawing.Size(80, 22);
            this.buttonAddGroup.TabIndex = 0;
            this.buttonAddGroup.Text = "Add Group";
            this.buttonAddGroup.UseVisualStyleBackColor = true;
            this.buttonAddGroup.Click += new System.EventHandler(this.buttonAddGroup_Click);
            // 
            // tabPage5
            // 
            this.tabPage5.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage5.Controls.Add(this.textBoxIdQueryDstEp);
            this.tabPage5.Controls.Add(this.textBoxIdQuerySrcEp);
            this.tabPage5.Controls.Add(this.textBoxIdQueryAddr);
            this.tabPage5.Controls.Add(this.textBoxIdSendTime);
            this.tabPage5.Controls.Add(this.textBoxIdSendDstEp);
            this.tabPage5.Controls.Add(this.textBoxSendIdSrcEp);
            this.tabPage5.Controls.Add(this.textBoxSendIdAddr);
            this.tabPage5.Controls.Add(this.buttonIdQuery);
            this.tabPage5.Controls.Add(this.buttonIdSend);
            this.tabPage5.Location = new System.Drawing.Point(4, 22);
            this.tabPage5.Name = "tabPage5";
            this.tabPage5.Size = new System.Drawing.Size(1351, 416);
            this.tabPage5.TabIndex = 4;
            this.tabPage5.Text = "Identify Cluster";
            this.tabPage5.Click += new System.EventHandler(this.tabPage5_Click);
            // 
            // textBoxIdQueryDstEp
            // 
            this.textBoxIdQueryDstEp.Location = new System.Drawing.Point(317, 35);
            this.textBoxIdQueryDstEp.Name = "textBoxIdQueryDstEp";
            this.textBoxIdQueryDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxIdQueryDstEp.TabIndex = 8;
            this.textBoxIdQueryDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxIdQueryDstEp_MouseClick);
            this.textBoxIdQueryDstEp.Leave += new System.EventHandler(this.textBoxIdQueryDstEp_Leave);
            this.textBoxIdQueryDstEp.MouseLeave += new System.EventHandler(this.textBoxIdQueryDstEp_MouseLeave);
            this.textBoxIdQueryDstEp.MouseHover += new System.EventHandler(this.textBoxIdQueryDstEp_MouseHover);
            // 
            // textBoxIdQuerySrcEp
            // 
            this.textBoxIdQuerySrcEp.Location = new System.Drawing.Point(204, 35);
            this.textBoxIdQuerySrcEp.Name = "textBoxIdQuerySrcEp";
            this.textBoxIdQuerySrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxIdQuerySrcEp.TabIndex = 7;
            this.textBoxIdQuerySrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxIdQuerySrcEp_MouseClick);
            this.textBoxIdQuerySrcEp.Leave += new System.EventHandler(this.textBoxIdQuerySrcEp_Leave);
            this.textBoxIdQuerySrcEp.MouseLeave += new System.EventHandler(this.textBoxIdQuerySrcEp_MouseLeave);
            this.textBoxIdQuerySrcEp.MouseHover += new System.EventHandler(this.textBoxIdQuerySrcEp_MouseHover);
            // 
            // textBoxIdQueryAddr
            // 
            this.textBoxIdQueryAddr.Location = new System.Drawing.Point(90, 35);
            this.textBoxIdQueryAddr.Name = "textBoxIdQueryAddr";
            this.textBoxIdQueryAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxIdQueryAddr.TabIndex = 6;
            this.textBoxIdQueryAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxIdQueryAddr_MouseClick);
            this.textBoxIdQueryAddr.Leave += new System.EventHandler(this.textBoxIdQueryAddr_Leave);
            this.textBoxIdQueryAddr.MouseLeave += new System.EventHandler(this.textBoxIdQueryAddr_MouseLeave);
            this.textBoxIdQueryAddr.MouseHover += new System.EventHandler(this.textBoxIdQueryAddr_MouseHover);
            // 
            // textBoxIdSendTime
            // 
            this.textBoxIdSendTime.Location = new System.Drawing.Point(430, 6);
            this.textBoxIdSendTime.Name = "textBoxIdSendTime";
            this.textBoxIdSendTime.Size = new System.Drawing.Size(106, 20);
            this.textBoxIdSendTime.TabIndex = 4;
            this.textBoxIdSendTime.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxIdSendTime_MouseClick);
            this.textBoxIdSendTime.Leave += new System.EventHandler(this.textBoxIdSendTime_Leave);
            this.textBoxIdSendTime.MouseLeave += new System.EventHandler(this.textBoxIdSendTime_MouseLeave);
            this.textBoxIdSendTime.MouseHover += new System.EventHandler(this.textBoxIdSendTime_MouseHover);
            // 
            // textBoxIdSendDstEp
            // 
            this.textBoxIdSendDstEp.Location = new System.Drawing.Point(317, 6);
            this.textBoxIdSendDstEp.Name = "textBoxIdSendDstEp";
            this.textBoxIdSendDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxIdSendDstEp.TabIndex = 3;
            this.textBoxIdSendDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxIdSendDstEp_MouseClick);
            this.textBoxIdSendDstEp.Leave += new System.EventHandler(this.textBoxIdSendDstEp_Leave);
            this.textBoxIdSendDstEp.MouseLeave += new System.EventHandler(this.textBoxIdSendDstEp_MouseLeave);
            this.textBoxIdSendDstEp.MouseHover += new System.EventHandler(this.textBoxIdSendDstEp_MouseHover);
            // 
            // textBoxSendIdSrcEp
            // 
            this.textBoxSendIdSrcEp.Location = new System.Drawing.Point(204, 6);
            this.textBoxSendIdSrcEp.Name = "textBoxSendIdSrcEp";
            this.textBoxSendIdSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxSendIdSrcEp.TabIndex = 2;
            this.textBoxSendIdSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxSendIdSrcEp_MouseClick);
            this.textBoxSendIdSrcEp.Leave += new System.EventHandler(this.textBoxSendIdSrcEp_Leave);
            this.textBoxSendIdSrcEp.MouseLeave += new System.EventHandler(this.textBoxSendIdSrcEp_MouseLeave);
            this.textBoxSendIdSrcEp.MouseHover += new System.EventHandler(this.textBoxSendIdSrcEp_MouseHover);
            // 
            // textBoxSendIdAddr
            // 
            this.textBoxSendIdAddr.Location = new System.Drawing.Point(90, 6);
            this.textBoxSendIdAddr.Name = "textBoxSendIdAddr";
            this.textBoxSendIdAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxSendIdAddr.TabIndex = 1;
            this.textBoxSendIdAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxSendIdAddr_MouseClick);
            this.textBoxSendIdAddr.Leave += new System.EventHandler(this.textBoxSendIdAddr_Leave);
            this.textBoxSendIdAddr.MouseLeave += new System.EventHandler(this.textBoxSendIdAddr_MouseLeave);
            this.textBoxSendIdAddr.MouseHover += new System.EventHandler(this.textBoxSendIdAddr_MouseHover);
            // 
            // buttonIdQuery
            // 
            this.buttonIdQuery.Location = new System.Drawing.Point(4, 34);
            this.buttonIdQuery.Name = "buttonIdQuery";
            this.buttonIdQuery.Size = new System.Drawing.Size(80, 22);
            this.buttonIdQuery.TabIndex = 5;
            this.buttonIdQuery.Text = "ID Query";
            this.buttonIdQuery.UseVisualStyleBackColor = true;
            this.buttonIdQuery.Click += new System.EventHandler(this.buttonIdQuery_Click);
            // 
            // buttonIdSend
            // 
            this.buttonIdSend.Location = new System.Drawing.Point(4, 4);
            this.buttonIdSend.Name = "buttonIdSend";
            this.buttonIdSend.Size = new System.Drawing.Size(80, 22);
            this.buttonIdSend.TabIndex = 0;
            this.buttonIdSend.Text = "ID Send";
            this.buttonIdSend.UseVisualStyleBackColor = true;
            this.buttonIdSend.Click += new System.EventHandler(this.buttonIdSend_Click);
            // 
            // tabPage6
            // 
            this.tabPage6.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage6.Controls.Add(this.comboBoxMoveToLevelOnOff);
            this.tabPage6.Controls.Add(this.comboBoxMoveToLevelAddrMode);
            this.tabPage6.Controls.Add(this.textBoxMoveToLevelTransTime);
            this.tabPage6.Controls.Add(this.textBoxMoveToLevelLevel);
            this.tabPage6.Controls.Add(this.textBoxMoveToLevelDstEndPoint);
            this.tabPage6.Controls.Add(this.textBoxMoveToLevelSrcEndPoint);
            this.tabPage6.Controls.Add(this.textBoxMoveToLevelAddr);
            this.tabPage6.Controls.Add(this.buttonMoveToLevel);
            this.tabPage6.Location = new System.Drawing.Point(4, 22);
            this.tabPage6.Name = "tabPage6";
            this.tabPage6.Size = new System.Drawing.Size(1351, 416);
            this.tabPage6.TabIndex = 5;
            this.tabPage6.Text = "Level Cluster";
            this.tabPage6.Click += new System.EventHandler(this.tabPage6_Click);
            // 
            // comboBoxMoveToLevelOnOff
            // 
            this.comboBoxMoveToLevelOnOff.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxMoveToLevelOnOff.FormattingEnabled = true;
            this.comboBoxMoveToLevelOnOff.Location = new System.Drawing.Point(553, 7);
            this.comboBoxMoveToLevelOnOff.Name = "comboBoxMoveToLevelOnOff";
            this.comboBoxMoveToLevelOnOff.Size = new System.Drawing.Size(106, 21);
            this.comboBoxMoveToLevelOnOff.TabIndex = 5;
            this.comboBoxMoveToLevelOnOff.MouseLeave += new System.EventHandler(this.comboBoxMoveToLevelOnOff_MouseLeave);
            this.comboBoxMoveToLevelOnOff.MouseHover += new System.EventHandler(this.comboBoxMoveToLevelOnOff_MouseHover);
            // 
            // comboBoxMoveToLevelAddrMode
            // 
            this.comboBoxMoveToLevelAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxMoveToLevelAddrMode.FormattingEnabled = true;
            this.comboBoxMoveToLevelAddrMode.Location = new System.Drawing.Point(100, 7);
            this.comboBoxMoveToLevelAddrMode.Name = "comboBoxMoveToLevelAddrMode";
            this.comboBoxMoveToLevelAddrMode.Size = new System.Drawing.Size(106, 21);
            this.comboBoxMoveToLevelAddrMode.TabIndex = 1;
            this.comboBoxMoveToLevelAddrMode.MouseLeave += new System.EventHandler(this.comboBoxMoveToLevelAddrMode_MouseLeave);
            this.comboBoxMoveToLevelAddrMode.MouseHover += new System.EventHandler(this.comboBoxMoveToLevelAddrMode_MouseHover);
            // 
            // textBoxMoveToLevelTransTime
            // 
            this.textBoxMoveToLevelTransTime.Location = new System.Drawing.Point(778, 7);
            this.textBoxMoveToLevelTransTime.Name = "textBoxMoveToLevelTransTime";
            this.textBoxMoveToLevelTransTime.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToLevelTransTime.TabIndex = 7;
            this.textBoxMoveToLevelTransTime.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToLevelTransTime_MouseClick);
            this.textBoxMoveToLevelTransTime.Leave += new System.EventHandler(this.textBoxMoveToLevelTransTime_Leave);
            this.textBoxMoveToLevelTransTime.MouseLeave += new System.EventHandler(this.textBoxMoveToLevelTransTime_MouseLeave);
            this.textBoxMoveToLevelTransTime.MouseHover += new System.EventHandler(this.textBoxMoveToLevelTransTime_MouseHover);
            // 
            // textBoxMoveToLevelLevel
            // 
            this.textBoxMoveToLevelLevel.Location = new System.Drawing.Point(666, 7);
            this.textBoxMoveToLevelLevel.Name = "textBoxMoveToLevelLevel";
            this.textBoxMoveToLevelLevel.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToLevelLevel.TabIndex = 6;
            this.textBoxMoveToLevelLevel.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToLevelLevel_MouseClick);
            this.textBoxMoveToLevelLevel.Leave += new System.EventHandler(this.textBoxMoveToLevelLevel_Leave);
            this.textBoxMoveToLevelLevel.MouseLeave += new System.EventHandler(this.textBoxMoveToLevelLevel_MouseLeave);
            this.textBoxMoveToLevelLevel.MouseHover += new System.EventHandler(this.textBoxMoveToLevelLevel_MouseHover);
            // 
            // textBoxMoveToLevelDstEndPoint
            // 
            this.textBoxMoveToLevelDstEndPoint.Location = new System.Drawing.Point(439, 7);
            this.textBoxMoveToLevelDstEndPoint.Name = "textBoxMoveToLevelDstEndPoint";
            this.textBoxMoveToLevelDstEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToLevelDstEndPoint.TabIndex = 4;
            this.textBoxMoveToLevelDstEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToLevelDstEndPoint_MouseClick);
            this.textBoxMoveToLevelDstEndPoint.Leave += new System.EventHandler(this.textBoxMoveToLevelDstEndPoint_Leave);
            this.textBoxMoveToLevelDstEndPoint.MouseLeave += new System.EventHandler(this.textBoxMoveToLevelDstEndPoint_MouseLeave);
            this.textBoxMoveToLevelDstEndPoint.MouseHover += new System.EventHandler(this.textBoxMoveToLevelDstEndPoint_MouseHover);
            // 
            // textBoxMoveToLevelSrcEndPoint
            // 
            this.textBoxMoveToLevelSrcEndPoint.Location = new System.Drawing.Point(326, 7);
            this.textBoxMoveToLevelSrcEndPoint.Name = "textBoxMoveToLevelSrcEndPoint";
            this.textBoxMoveToLevelSrcEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToLevelSrcEndPoint.TabIndex = 3;
            this.textBoxMoveToLevelSrcEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToLevelSrcEndPoint_MouseClick);
            this.textBoxMoveToLevelSrcEndPoint.Leave += new System.EventHandler(this.textBoxMoveToLevelSrcEndPoint_Leave);
            this.textBoxMoveToLevelSrcEndPoint.MouseLeave += new System.EventHandler(this.textBoxMoveToLevelSrcEndPoint_MouseLeave);
            this.textBoxMoveToLevelSrcEndPoint.MouseHover += new System.EventHandler(this.textBoxMoveToLevelSrcEndPoint_MouseHover);
            // 
            // textBoxMoveToLevelAddr
            // 
            this.textBoxMoveToLevelAddr.Location = new System.Drawing.Point(214, 7);
            this.textBoxMoveToLevelAddr.Name = "textBoxMoveToLevelAddr";
            this.textBoxMoveToLevelAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToLevelAddr.TabIndex = 2;
            this.textBoxMoveToLevelAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToLevelAddr_MouseClick);
            this.textBoxMoveToLevelAddr.Leave += new System.EventHandler(this.textBoxMoveToLevelAddr_Leave);
            this.textBoxMoveToLevelAddr.MouseLeave += new System.EventHandler(this.textBoxMoveToLevelAddr_MouseLeave);
            this.textBoxMoveToLevelAddr.MouseHover += new System.EventHandler(this.textBoxMoveToLevelAddr_MouseHover);
            // 
            // buttonMoveToLevel
            // 
            this.buttonMoveToLevel.Location = new System.Drawing.Point(3, 5);
            this.buttonMoveToLevel.Name = "buttonMoveToLevel";
            this.buttonMoveToLevel.Size = new System.Drawing.Size(90, 22);
            this.buttonMoveToLevel.TabIndex = 0;
            this.buttonMoveToLevel.Text = "MoveToLevel";
            this.buttonMoveToLevel.UseVisualStyleBackColor = true;
            this.buttonMoveToLevel.Click += new System.EventHandler(this.buttonMoveToLevel_Click_1);
            // 
            // tabPage4
            // 
            this.tabPage4.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage4.Controls.Add(this.comboBoxOnOffAddrMode);
            this.tabPage4.Controls.Add(this.comboBoxOnOffCommand);
            this.tabPage4.Controls.Add(this.textBoxOnOffDstEndPoint);
            this.tabPage4.Controls.Add(this.textBoxOnOffSrcEndPoint);
            this.tabPage4.Controls.Add(this.textBoxOnOffAddr);
            this.tabPage4.Controls.Add(this.buttonOnOff);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(1351, 416);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "On/Off Cluster";
            this.tabPage4.Click += new System.EventHandler(this.tabPage4_Click);
            // 
            // comboBoxOnOffAddrMode
            // 
            this.comboBoxOnOffAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxOnOffAddrMode.FormattingEnabled = true;
            this.comboBoxOnOffAddrMode.Location = new System.Drawing.Point(90, 5);
            this.comboBoxOnOffAddrMode.Name = "comboBoxOnOffAddrMode";
            this.comboBoxOnOffAddrMode.Size = new System.Drawing.Size(106, 21);
            this.comboBoxOnOffAddrMode.TabIndex = 1;
            this.comboBoxOnOffAddrMode.MouseLeave += new System.EventHandler(this.comboBoxOnOffAddrMode_MouseLeave);
            this.comboBoxOnOffAddrMode.MouseHover += new System.EventHandler(this.comboBoxOnOffAddrMode_MouseHover);
            // 
            // comboBoxOnOffCommand
            // 
            this.comboBoxOnOffCommand.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxOnOffCommand.FormattingEnabled = true;
            this.comboBoxOnOffCommand.Location = new System.Drawing.Point(543, 5);
            this.comboBoxOnOffCommand.Name = "comboBoxOnOffCommand";
            this.comboBoxOnOffCommand.Size = new System.Drawing.Size(129, 21);
            this.comboBoxOnOffCommand.TabIndex = 5;
            this.comboBoxOnOffCommand.MouseLeave += new System.EventHandler(this.comboBoxOnOffCommand_MouseLeave);
            this.comboBoxOnOffCommand.MouseHover += new System.EventHandler(this.comboBoxOnOffCommand_MouseHover);
            // 
            // textBoxOnOffDstEndPoint
            // 
            this.textBoxOnOffDstEndPoint.Location = new System.Drawing.Point(430, 5);
            this.textBoxOnOffDstEndPoint.Name = "textBoxOnOffDstEndPoint";
            this.textBoxOnOffDstEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxOnOffDstEndPoint.TabIndex = 4;
            this.textBoxOnOffDstEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOnOffDstEndPoint_MouseClick);
            this.textBoxOnOffDstEndPoint.Leave += new System.EventHandler(this.textBoxOnOffDstEndPoint_Leave);
            this.textBoxOnOffDstEndPoint.MouseLeave += new System.EventHandler(this.textBoxOnOffDstEndPoint_MouseLeave);
            this.textBoxOnOffDstEndPoint.MouseHover += new System.EventHandler(this.textBoxOnOffDstEndPoint_MouseHover);
            // 
            // textBoxOnOffSrcEndPoint
            // 
            this.textBoxOnOffSrcEndPoint.Location = new System.Drawing.Point(317, 6);
            this.textBoxOnOffSrcEndPoint.Name = "textBoxOnOffSrcEndPoint";
            this.textBoxOnOffSrcEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxOnOffSrcEndPoint.TabIndex = 3;
            this.textBoxOnOffSrcEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOnOffSrcEndPoint_MouseClick);
            this.textBoxOnOffSrcEndPoint.Leave += new System.EventHandler(this.textBoxOnOffSrcEndPoint_Leave);
            this.textBoxOnOffSrcEndPoint.MouseLeave += new System.EventHandler(this.textBoxOnOffSrcEndPoint_MouseLeave);
            this.textBoxOnOffSrcEndPoint.MouseHover += new System.EventHandler(this.textBoxOnOffSrcEndPoint_MouseHover);
            // 
            // textBoxOnOffAddr
            // 
            this.textBoxOnOffAddr.Location = new System.Drawing.Point(204, 6);
            this.textBoxOnOffAddr.Name = "textBoxOnOffAddr";
            this.textBoxOnOffAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxOnOffAddr.TabIndex = 2;
            this.textBoxOnOffAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOnOffAddr_MouseClick);
            this.textBoxOnOffAddr.Leave += new System.EventHandler(this.textBoxOnOffAddr_Leave);
            this.textBoxOnOffAddr.MouseLeave += new System.EventHandler(this.textBoxOnOffAddr_MouseLeave);
            this.textBoxOnOffAddr.MouseHover += new System.EventHandler(this.textBoxOnOffAddr_MouseHover);
            // 
            // buttonOnOff
            // 
            this.buttonOnOff.Location = new System.Drawing.Point(4, 4);
            this.buttonOnOff.Name = "buttonOnOff";
            this.buttonOnOff.Size = new System.Drawing.Size(80, 22);
            this.buttonOnOff.TabIndex = 0;
            this.buttonOnOff.Text = "OnOff";
            this.buttonOnOff.UseVisualStyleBackColor = true;
            this.buttonOnOff.Click += new System.EventHandler(this.buttonOnOff_Click);
            // 
            // tabPage7
            // 
            this.tabPage7.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage7.Controls.Add(this.checkBoxShowExtension);
            this.tabPage7.Controls.Add(this.textBoxAddSceneData);
            this.tabPage7.Controls.Add(this.textBoxAddSceneExtLen);
            this.tabPage7.Controls.Add(this.textBoxRemoveSceneSceneID);
            this.tabPage7.Controls.Add(this.textBoxRemoveSceneGroupID);
            this.tabPage7.Controls.Add(this.textBoxRemoveSceneDstEndPoint);
            this.tabPage7.Controls.Add(this.textBoxRemoveSceneSrcEndPoint);
            this.tabPage7.Controls.Add(this.textBoxRemoveSceneAddr);
            this.tabPage7.Controls.Add(this.comboBoxRemoveSceneAddrMode);
            this.tabPage7.Controls.Add(this.buttonRemoveScene);
            this.tabPage7.Controls.Add(this.textBoxRemoveAllScenesGroupID);
            this.tabPage7.Controls.Add(this.textBoxRemoveAllScenesDstEndPoint);
            this.tabPage7.Controls.Add(this.textBoxRemoveAllScenesSrcEndPoint);
            this.tabPage7.Controls.Add(this.textBoxRemoveAllScenesAddr);
            this.tabPage7.Controls.Add(this.comboBoxRemoveAllScenesAddrMode);
            this.tabPage7.Controls.Add(this.buttonRemoveAllScenes);
            this.tabPage7.Controls.Add(this.textBoxGetSceneMembershipGroupID);
            this.tabPage7.Controls.Add(this.textBoxGetSceneMembershipDstEndPoint);
            this.tabPage7.Controls.Add(this.textBoxGetSceneMembershipSrcEndPoint);
            this.tabPage7.Controls.Add(this.textBoxGetSceneMembershipAddr);
            this.tabPage7.Controls.Add(this.comboBoxGetSceneMembershipAddrMode);
            this.tabPage7.Controls.Add(this.buttonGetSceneMembership);
            this.tabPage7.Controls.Add(this.textBoxRecallSceneSceneId);
            this.tabPage7.Controls.Add(this.textBoxRecallSceneGroupId);
            this.tabPage7.Controls.Add(this.textBoxRecallSceneDstEndPoint);
            this.tabPage7.Controls.Add(this.textBoxRecallSceneSrcEndPoint);
            this.tabPage7.Controls.Add(this.textBoxRecallSceneAddr);
            this.tabPage7.Controls.Add(this.comboBoxRecallSceneAddrMode);
            this.tabPage7.Controls.Add(this.buttonRecallScene);
            this.tabPage7.Controls.Add(this.textBoxStoreSceneSceneId);
            this.tabPage7.Controls.Add(this.textBoxStoreSceneGroupId);
            this.tabPage7.Controls.Add(this.textBoxStoreSceneDstEndPoint);
            this.tabPage7.Controls.Add(this.textBoxStoreSceneSrcEndPoint);
            this.tabPage7.Controls.Add(this.textBoxStoreSceneAddr);
            this.tabPage7.Controls.Add(this.comboBoxStoreSceneAddrMode);
            this.tabPage7.Controls.Add(this.buttonStoreScene);
            this.tabPage7.Controls.Add(this.textBoxAddSceneMaxNameLen);
            this.tabPage7.Controls.Add(this.textBoxAddSceneNameLen);
            this.tabPage7.Controls.Add(this.textBoxAddSceneName);
            this.tabPage7.Controls.Add(this.textBoxAddSceneTransTime);
            this.tabPage7.Controls.Add(this.textBoxAddSceneSceneId);
            this.tabPage7.Controls.Add(this.textBoxAddSceneGroupId);
            this.tabPage7.Controls.Add(this.textBoxAddSceneDstEndPoint);
            this.tabPage7.Controls.Add(this.textBoxAddSceneSrcEndPoint);
            this.tabPage7.Controls.Add(this.textBoxAddSceneAddr);
            this.tabPage7.Controls.Add(this.comboBoxAddSceneAddrMode);
            this.tabPage7.Controls.Add(this.buttonAddScene);
            this.tabPage7.Controls.Add(this.comboBoxViewSceneAddrMode);
            this.tabPage7.Controls.Add(this.textBoxViewSceneSceneId);
            this.tabPage7.Controls.Add(this.textBoxViewSceneGroupId);
            this.tabPage7.Controls.Add(this.textBoxViewSceneDstEndPoint);
            this.tabPage7.Controls.Add(this.textBoxViewSceneSrcEndPoint);
            this.tabPage7.Controls.Add(this.textBoxViewSceneAddr);
            this.tabPage7.Controls.Add(this.buttonViewScene);
            this.tabPage7.Location = new System.Drawing.Point(4, 22);
            this.tabPage7.Name = "tabPage7";
            this.tabPage7.Size = new System.Drawing.Size(1351, 416);
            this.tabPage7.TabIndex = 6;
            this.tabPage7.Text = "Scenes Cluster";
            this.tabPage7.Click += new System.EventHandler(this.tabPage7_Click);
            // 
            // checkBoxShowExtension
            // 
            this.checkBoxShowExtension.AutoSize = true;
            this.checkBoxShowExtension.Location = new System.Drawing.Point(767, 34);
            this.checkBoxShowExtension.Margin = new System.Windows.Forms.Padding(2);
            this.checkBoxShowExtension.Name = "checkBoxShowExtension";
            this.checkBoxShowExtension.Size = new System.Drawing.Size(134, 17);
            this.checkBoxShowExtension.TabIndex = 53;
            this.checkBoxShowExtension.Text = "Show extension fields?";
            this.checkBoxShowExtension.UseVisualStyleBackColor = true;
            this.checkBoxShowExtension.CheckedChanged += new System.EventHandler(this.checkBoxShowExtension_CheckedChanged);
            // 
            // textBoxAddSceneData
            // 
            this.textBoxAddSceneData.Location = new System.Drawing.Point(767, 58);
            this.textBoxAddSceneData.Name = "textBoxAddSceneData";
            this.textBoxAddSceneData.Size = new System.Drawing.Size(220, 20);
            this.textBoxAddSceneData.TabIndex = 19;
            this.textBoxAddSceneData.Visible = false;
            this.textBoxAddSceneData.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddSceneData_MouseClick);
            this.textBoxAddSceneData.Leave += new System.EventHandler(this.textBoxAddSceneData_Leave);
            this.textBoxAddSceneData.MouseLeave += new System.EventHandler(this.textBoxAddSceneData_MouseLeave);
            this.textBoxAddSceneData.MouseHover += new System.EventHandler(this.textBoxAddSceneData_MouseHover);
            // 
            // textBoxAddSceneExtLen
            // 
            this.textBoxAddSceneExtLen.Location = new System.Drawing.Point(655, 58);
            this.textBoxAddSceneExtLen.Name = "textBoxAddSceneExtLen";
            this.textBoxAddSceneExtLen.Size = new System.Drawing.Size(106, 20);
            this.textBoxAddSceneExtLen.TabIndex = 18;
            this.textBoxAddSceneExtLen.Visible = false;
            this.textBoxAddSceneExtLen.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddSceneExtLen_MouseClick);
            this.textBoxAddSceneExtLen.Leave += new System.EventHandler(this.textBoxAddSceneExtLen_Leave);
            this.textBoxAddSceneExtLen.MouseLeave += new System.EventHandler(this.textBoxAddSceneExtLen_MouseLeave);
            this.textBoxAddSceneExtLen.MouseHover += new System.EventHandler(this.textBoxAddSceneExtLen_MouseHover);
            // 
            // textBoxRemoveSceneSceneID
            // 
            this.textBoxRemoveSceneSceneID.Location = new System.Drawing.Point(655, 201);
            this.textBoxRemoveSceneSceneID.Name = "textBoxRemoveSceneSceneID";
            this.textBoxRemoveSceneSceneID.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveSceneSceneID.TabIndex = 52;
            this.textBoxRemoveSceneSceneID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveSceneSceneID_MouseClick);
            this.textBoxRemoveSceneSceneID.Leave += new System.EventHandler(this.textBoxRemoveSceneSceneID_Leave);
            this.textBoxRemoveSceneSceneID.MouseLeave += new System.EventHandler(this.textBoxRemoveSceneSceneID_MouseLeave);
            this.textBoxRemoveSceneSceneID.MouseHover += new System.EventHandler(this.textBoxRemoveSceneSceneID_MouseHover);
            // 
            // textBoxRemoveSceneGroupID
            // 
            this.textBoxRemoveSceneGroupID.Location = new System.Drawing.Point(542, 202);
            this.textBoxRemoveSceneGroupID.Name = "textBoxRemoveSceneGroupID";
            this.textBoxRemoveSceneGroupID.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveSceneGroupID.TabIndex = 51;
            this.textBoxRemoveSceneGroupID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveSceneGroupID_MouseClick);
            this.textBoxRemoveSceneGroupID.Leave += new System.EventHandler(this.textBoxRemoveSceneGroupID_Leave);
            this.textBoxRemoveSceneGroupID.MouseLeave += new System.EventHandler(this.textBoxRemoveSceneGroupID_MouseLeave);
            this.textBoxRemoveSceneGroupID.MouseHover += new System.EventHandler(this.textBoxRemoveSceneGroupID_MouseHover);
            // 
            // textBoxRemoveSceneDstEndPoint
            // 
            this.textBoxRemoveSceneDstEndPoint.Location = new System.Drawing.Point(429, 201);
            this.textBoxRemoveSceneDstEndPoint.Name = "textBoxRemoveSceneDstEndPoint";
            this.textBoxRemoveSceneDstEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveSceneDstEndPoint.TabIndex = 50;
            this.textBoxRemoveSceneDstEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveSceneDstEndPoint_MouseClick);
            this.textBoxRemoveSceneDstEndPoint.Leave += new System.EventHandler(this.textBoxRemoveSceneDstEndPoint_Leave);
            this.textBoxRemoveSceneDstEndPoint.MouseLeave += new System.EventHandler(this.textBoxRemoveSceneDstEndPoint_MouseLeave);
            this.textBoxRemoveSceneDstEndPoint.MouseHover += new System.EventHandler(this.textBoxRemoveSceneDstEndPoint_MouseHover);
            // 
            // textBoxRemoveSceneSrcEndPoint
            // 
            this.textBoxRemoveSceneSrcEndPoint.Location = new System.Drawing.Point(316, 201);
            this.textBoxRemoveSceneSrcEndPoint.Name = "textBoxRemoveSceneSrcEndPoint";
            this.textBoxRemoveSceneSrcEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveSceneSrcEndPoint.TabIndex = 49;
            this.textBoxRemoveSceneSrcEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveSceneSrcEndPoint_MouseClick);
            this.textBoxRemoveSceneSrcEndPoint.Leave += new System.EventHandler(this.textBoxRemoveSceneSrcEndPoint_Leave);
            this.textBoxRemoveSceneSrcEndPoint.MouseLeave += new System.EventHandler(this.textBoxRemoveSceneSrcEndPoint_MouseLeave);
            this.textBoxRemoveSceneSrcEndPoint.MouseHover += new System.EventHandler(this.textBoxRemoveSceneSrcEndPoint_MouseHover);
            // 
            // textBoxRemoveSceneAddr
            // 
            this.textBoxRemoveSceneAddr.Location = new System.Drawing.Point(202, 201);
            this.textBoxRemoveSceneAddr.Name = "textBoxRemoveSceneAddr";
            this.textBoxRemoveSceneAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveSceneAddr.TabIndex = 48;
            this.textBoxRemoveSceneAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveSceneAddr_MouseClick);
            this.textBoxRemoveSceneAddr.Leave += new System.EventHandler(this.textBoxRemoveSceneAddr_Leave);
            this.textBoxRemoveSceneAddr.MouseLeave += new System.EventHandler(this.textBoxRemoveSceneAddr_MouseLeave);
            this.textBoxRemoveSceneAddr.MouseHover += new System.EventHandler(this.textBoxRemoveSceneAddr_MouseHover);
            // 
            // comboBoxRemoveSceneAddrMode
            // 
            this.comboBoxRemoveSceneAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxRemoveSceneAddrMode.FormattingEnabled = true;
            this.comboBoxRemoveSceneAddrMode.Location = new System.Drawing.Point(90, 201);
            this.comboBoxRemoveSceneAddrMode.Name = "comboBoxRemoveSceneAddrMode";
            this.comboBoxRemoveSceneAddrMode.Size = new System.Drawing.Size(106, 21);
            this.comboBoxRemoveSceneAddrMode.TabIndex = 47;
            this.comboBoxRemoveSceneAddrMode.MouseLeave += new System.EventHandler(this.comboBoxRemoveSceneAddrMode_MouseLeave);
            this.comboBoxRemoveSceneAddrMode.MouseHover += new System.EventHandler(this.comboBoxRemoveSceneAddrMode_MouseHover);
            // 
            // buttonRemoveScene
            // 
            this.buttonRemoveScene.Location = new System.Drawing.Point(3, 198);
            this.buttonRemoveScene.Name = "buttonRemoveScene";
            this.buttonRemoveScene.Size = new System.Drawing.Size(80, 25);
            this.buttonRemoveScene.TabIndex = 46;
            this.buttonRemoveScene.Text = "Remove";
            this.buttonRemoveScene.UseVisualStyleBackColor = true;
            this.buttonRemoveScene.Click += new System.EventHandler(this.buttonRemoveScene_Click);
            // 
            // textBoxRemoveAllScenesGroupID
            // 
            this.textBoxRemoveAllScenesGroupID.Location = new System.Drawing.Point(542, 170);
            this.textBoxRemoveAllScenesGroupID.Name = "textBoxRemoveAllScenesGroupID";
            this.textBoxRemoveAllScenesGroupID.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveAllScenesGroupID.TabIndex = 45;
            this.textBoxRemoveAllScenesGroupID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveAllScenesGroupID_MouseClick);
            this.textBoxRemoveAllScenesGroupID.Leave += new System.EventHandler(this.textBoxRemoveAllScenesGroupID_Leave);
            this.textBoxRemoveAllScenesGroupID.MouseLeave += new System.EventHandler(this.textBoxRemoveAllScenesGroupID_MouseLeave);
            this.textBoxRemoveAllScenesGroupID.MouseHover += new System.EventHandler(this.textBoxRemoveAllScenesGroupID_MouseHover);
            // 
            // textBoxRemoveAllScenesDstEndPoint
            // 
            this.textBoxRemoveAllScenesDstEndPoint.Location = new System.Drawing.Point(429, 170);
            this.textBoxRemoveAllScenesDstEndPoint.Name = "textBoxRemoveAllScenesDstEndPoint";
            this.textBoxRemoveAllScenesDstEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveAllScenesDstEndPoint.TabIndex = 44;
            this.textBoxRemoveAllScenesDstEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveAllScenesDstEndPoint_MouseClick);
            this.textBoxRemoveAllScenesDstEndPoint.Leave += new System.EventHandler(this.textBoxRemoveAllScenesDstEndPoint_Leave);
            this.textBoxRemoveAllScenesDstEndPoint.MouseLeave += new System.EventHandler(this.textBoxRemoveAllScenesDstEndPoint_MouseLeave);
            this.textBoxRemoveAllScenesDstEndPoint.MouseHover += new System.EventHandler(this.textBoxRemoveAllScenesDstEndPoint_MouseHover);
            // 
            // textBoxRemoveAllScenesSrcEndPoint
            // 
            this.textBoxRemoveAllScenesSrcEndPoint.Location = new System.Drawing.Point(316, 170);
            this.textBoxRemoveAllScenesSrcEndPoint.Name = "textBoxRemoveAllScenesSrcEndPoint";
            this.textBoxRemoveAllScenesSrcEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveAllScenesSrcEndPoint.TabIndex = 43;
            this.textBoxRemoveAllScenesSrcEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveAllScenesSrcEndPoint_MouseClick);
            this.textBoxRemoveAllScenesSrcEndPoint.Leave += new System.EventHandler(this.textBoxRemoveAllScenesSrcEndPoint_Leave);
            this.textBoxRemoveAllScenesSrcEndPoint.MouseLeave += new System.EventHandler(this.textBoxRemoveAllScenesSrcEndPoint_MouseLeave);
            this.textBoxRemoveAllScenesSrcEndPoint.MouseHover += new System.EventHandler(this.textBoxRemoveAllScenesSrcEndPoint_MouseHover);
            // 
            // textBoxRemoveAllScenesAddr
            // 
            this.textBoxRemoveAllScenesAddr.Location = new System.Drawing.Point(202, 170);
            this.textBoxRemoveAllScenesAddr.Name = "textBoxRemoveAllScenesAddr";
            this.textBoxRemoveAllScenesAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxRemoveAllScenesAddr.TabIndex = 42;
            this.textBoxRemoveAllScenesAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRemoveAllScenesAddr_MouseClick);
            this.textBoxRemoveAllScenesAddr.Leave += new System.EventHandler(this.textBoxRemoveAllScenesAddr_Leave);
            this.textBoxRemoveAllScenesAddr.MouseLeave += new System.EventHandler(this.textBoxRemoveAllScenesAddr_MouseLeave);
            this.textBoxRemoveAllScenesAddr.MouseHover += new System.EventHandler(this.textBoxRemoveAllScenesAddr_MouseHover);
            // 
            // comboBoxRemoveAllScenesAddrMode
            // 
            this.comboBoxRemoveAllScenesAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxRemoveAllScenesAddrMode.FormattingEnabled = true;
            this.comboBoxRemoveAllScenesAddrMode.Location = new System.Drawing.Point(90, 170);
            this.comboBoxRemoveAllScenesAddrMode.Name = "comboBoxRemoveAllScenesAddrMode";
            this.comboBoxRemoveAllScenesAddrMode.Size = new System.Drawing.Size(106, 21);
            this.comboBoxRemoveAllScenesAddrMode.TabIndex = 41;
            this.comboBoxRemoveAllScenesAddrMode.MouseLeave += new System.EventHandler(this.comboBoxRemoveAllScenesAddrMode_MouseLeave);
            this.comboBoxRemoveAllScenesAddrMode.MouseHover += new System.EventHandler(this.comboBoxRemoveAllScenesAddrMode_MouseHover);
            // 
            // buttonRemoveAllScenes
            // 
            this.buttonRemoveAllScenes.Location = new System.Drawing.Point(3, 167);
            this.buttonRemoveAllScenes.Name = "buttonRemoveAllScenes";
            this.buttonRemoveAllScenes.Size = new System.Drawing.Size(80, 25);
            this.buttonRemoveAllScenes.TabIndex = 40;
            this.buttonRemoveAllScenes.Text = "Remove All";
            this.buttonRemoveAllScenes.UseVisualStyleBackColor = true;
            this.buttonRemoveAllScenes.Click += new System.EventHandler(this.buttonRemoveAllScenes_Click);
            // 
            // textBoxGetSceneMembershipGroupID
            // 
            this.textBoxGetSceneMembershipGroupID.Location = new System.Drawing.Point(542, 141);
            this.textBoxGetSceneMembershipGroupID.Name = "textBoxGetSceneMembershipGroupID";
            this.textBoxGetSceneMembershipGroupID.Size = new System.Drawing.Size(106, 20);
            this.textBoxGetSceneMembershipGroupID.TabIndex = 39;
            this.textBoxGetSceneMembershipGroupID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGetSceneMembershipGroupID_MouseClick);
            this.textBoxGetSceneMembershipGroupID.Leave += new System.EventHandler(this.textBoxGetSceneMembershipGroupID_Leave);
            this.textBoxGetSceneMembershipGroupID.MouseLeave += new System.EventHandler(this.textBoxGetSceneMembershipGroupID_MouseLeave);
            this.textBoxGetSceneMembershipGroupID.MouseHover += new System.EventHandler(this.textBoxGetSceneMembershipGroupID_MouseHover);
            // 
            // textBoxGetSceneMembershipDstEndPoint
            // 
            this.textBoxGetSceneMembershipDstEndPoint.Location = new System.Drawing.Point(429, 141);
            this.textBoxGetSceneMembershipDstEndPoint.Name = "textBoxGetSceneMembershipDstEndPoint";
            this.textBoxGetSceneMembershipDstEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxGetSceneMembershipDstEndPoint.TabIndex = 38;
            this.textBoxGetSceneMembershipDstEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGetSceneMembershipDstEndPoint_MouseClick);
            this.textBoxGetSceneMembershipDstEndPoint.Leave += new System.EventHandler(this.textBoxGetSceneMembershipDstEndPoint_Leave);
            this.textBoxGetSceneMembershipDstEndPoint.MouseLeave += new System.EventHandler(this.textBoxGetSceneMembershipDstEndPoint_MouseLeave);
            this.textBoxGetSceneMembershipDstEndPoint.MouseHover += new System.EventHandler(this.textBoxGetSceneMembershipDstEndPoint_MouseHover);
            // 
            // textBoxGetSceneMembershipSrcEndPoint
            // 
            this.textBoxGetSceneMembershipSrcEndPoint.Location = new System.Drawing.Point(316, 141);
            this.textBoxGetSceneMembershipSrcEndPoint.Name = "textBoxGetSceneMembershipSrcEndPoint";
            this.textBoxGetSceneMembershipSrcEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxGetSceneMembershipSrcEndPoint.TabIndex = 37;
            this.textBoxGetSceneMembershipSrcEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGetSceneMembershipSrcEndPoint_MouseClick);
            this.textBoxGetSceneMembershipSrcEndPoint.Leave += new System.EventHandler(this.textBoxGetSceneMembershipSrcEndPoint_Leave);
            this.textBoxGetSceneMembershipSrcEndPoint.MouseLeave += new System.EventHandler(this.textBoxGetSceneMembershipSrcEndPoint_MouseLeave);
            this.textBoxGetSceneMembershipSrcEndPoint.MouseHover += new System.EventHandler(this.textBoxGetSceneMembershipSrcEndPoint_MouseHover);
            // 
            // textBoxGetSceneMembershipAddr
            // 
            this.textBoxGetSceneMembershipAddr.Location = new System.Drawing.Point(202, 141);
            this.textBoxGetSceneMembershipAddr.Name = "textBoxGetSceneMembershipAddr";
            this.textBoxGetSceneMembershipAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxGetSceneMembershipAddr.TabIndex = 36;
            this.textBoxGetSceneMembershipAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxGetSceneMembershipAddr_MouseClick);
            this.textBoxGetSceneMembershipAddr.Leave += new System.EventHandler(this.textBoxGetSceneMembershipAddr_Leave);
            this.textBoxGetSceneMembershipAddr.MouseLeave += new System.EventHandler(this.textBoxGetSceneMembershipAddr_MouseLeave);
            this.textBoxGetSceneMembershipAddr.MouseHover += new System.EventHandler(this.textBoxGetSceneMembershipAddr_MouseHover);
            // 
            // comboBoxGetSceneMembershipAddrMode
            // 
            this.comboBoxGetSceneMembershipAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxGetSceneMembershipAddrMode.FormattingEnabled = true;
            this.comboBoxGetSceneMembershipAddrMode.Location = new System.Drawing.Point(90, 141);
            this.comboBoxGetSceneMembershipAddrMode.Name = "comboBoxGetSceneMembershipAddrMode";
            this.comboBoxGetSceneMembershipAddrMode.Size = new System.Drawing.Size(106, 21);
            this.comboBoxGetSceneMembershipAddrMode.TabIndex = 35;
            this.comboBoxGetSceneMembershipAddrMode.MouseLeave += new System.EventHandler(this.comboBoxGetSceneMembershipAddrMode_MouseLeave);
            this.comboBoxGetSceneMembershipAddrMode.MouseHover += new System.EventHandler(this.comboBoxGetSceneMembershipAddrMode_MouseHover);
            // 
            // buttonGetSceneMembership
            // 
            this.buttonGetSceneMembership.Location = new System.Drawing.Point(3, 139);
            this.buttonGetSceneMembership.Name = "buttonGetSceneMembership";
            this.buttonGetSceneMembership.Size = new System.Drawing.Size(80, 22);
            this.buttonGetSceneMembership.TabIndex = 34;
            this.buttonGetSceneMembership.Text = "Get Memb";
            this.buttonGetSceneMembership.UseVisualStyleBackColor = true;
            this.buttonGetSceneMembership.Click += new System.EventHandler(this.buttonGetSceneMembership_Click);
            // 
            // textBoxRecallSceneSceneId
            // 
            this.textBoxRecallSceneSceneId.Location = new System.Drawing.Point(655, 112);
            this.textBoxRecallSceneSceneId.Name = "textBoxRecallSceneSceneId";
            this.textBoxRecallSceneSceneId.Size = new System.Drawing.Size(106, 20);
            this.textBoxRecallSceneSceneId.TabIndex = 33;
            this.textBoxRecallSceneSceneId.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRecallSceneSceneId_MouseClick);
            this.textBoxRecallSceneSceneId.Leave += new System.EventHandler(this.textBoxRecallSceneSceneId_Leave);
            this.textBoxRecallSceneSceneId.MouseLeave += new System.EventHandler(this.textBoxRecallSceneSceneId_MouseLeave);
            this.textBoxRecallSceneSceneId.MouseHover += new System.EventHandler(this.textBoxRecallSceneSceneId_MouseHover);
            // 
            // textBoxRecallSceneGroupId
            // 
            this.textBoxRecallSceneGroupId.Location = new System.Drawing.Point(542, 114);
            this.textBoxRecallSceneGroupId.Name = "textBoxRecallSceneGroupId";
            this.textBoxRecallSceneGroupId.Size = new System.Drawing.Size(106, 20);
            this.textBoxRecallSceneGroupId.TabIndex = 32;
            this.textBoxRecallSceneGroupId.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRecallSceneGroupId_MouseClick);
            this.textBoxRecallSceneGroupId.Leave += new System.EventHandler(this.textBoxRecallSceneGroupId_Leave);
            this.textBoxRecallSceneGroupId.MouseLeave += new System.EventHandler(this.textBoxRecallSceneGroupId_MouseLeave);
            this.textBoxRecallSceneGroupId.MouseHover += new System.EventHandler(this.textBoxRecallSceneGroupId_MouseHover);
            // 
            // textBoxRecallSceneDstEndPoint
            // 
            this.textBoxRecallSceneDstEndPoint.Location = new System.Drawing.Point(429, 112);
            this.textBoxRecallSceneDstEndPoint.Name = "textBoxRecallSceneDstEndPoint";
            this.textBoxRecallSceneDstEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxRecallSceneDstEndPoint.TabIndex = 31;
            this.textBoxRecallSceneDstEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRecallSceneDstEndPoint_MouseClick);
            this.textBoxRecallSceneDstEndPoint.Leave += new System.EventHandler(this.textBoxRecallSceneDstEndPoint_Leave);
            this.textBoxRecallSceneDstEndPoint.MouseLeave += new System.EventHandler(this.textBoxRecallSceneDstEndPoint_MouseLeave);
            this.textBoxRecallSceneDstEndPoint.MouseHover += new System.EventHandler(this.textBoxRecallSceneDstEndPoint_MouseHover);
            // 
            // textBoxRecallSceneSrcEndPoint
            // 
            this.textBoxRecallSceneSrcEndPoint.Location = new System.Drawing.Point(316, 112);
            this.textBoxRecallSceneSrcEndPoint.Name = "textBoxRecallSceneSrcEndPoint";
            this.textBoxRecallSceneSrcEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxRecallSceneSrcEndPoint.TabIndex = 30;
            this.textBoxRecallSceneSrcEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRecallSceneSrcEndPoint_MouseClick);
            this.textBoxRecallSceneSrcEndPoint.Leave += new System.EventHandler(this.textBoxRecallSceneSrcEndPoint_Leave);
            this.textBoxRecallSceneSrcEndPoint.MouseLeave += new System.EventHandler(this.textBoxRecallSceneSrcEndPoint_MouseLeave);
            this.textBoxRecallSceneSrcEndPoint.MouseHover += new System.EventHandler(this.textBoxRecallSceneSrcEndPoint_MouseHover);
            // 
            // textBoxRecallSceneAddr
            // 
            this.textBoxRecallSceneAddr.Location = new System.Drawing.Point(202, 112);
            this.textBoxRecallSceneAddr.Name = "textBoxRecallSceneAddr";
            this.textBoxRecallSceneAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxRecallSceneAddr.TabIndex = 29;
            this.textBoxRecallSceneAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxRecallSceneAddr_MouseClick);
            this.textBoxRecallSceneAddr.Leave += new System.EventHandler(this.textBoxRecallSceneAddr_Leave);
            this.textBoxRecallSceneAddr.MouseLeave += new System.EventHandler(this.textBoxRecallSceneAddr_MouseLeave);
            this.textBoxRecallSceneAddr.MouseHover += new System.EventHandler(this.textBoxRecallSceneAddr_MouseHover);
            // 
            // comboBoxRecallSceneAddrMode
            // 
            this.comboBoxRecallSceneAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxRecallSceneAddrMode.FormattingEnabled = true;
            this.comboBoxRecallSceneAddrMode.Location = new System.Drawing.Point(90, 112);
            this.comboBoxRecallSceneAddrMode.Name = "comboBoxRecallSceneAddrMode";
            this.comboBoxRecallSceneAddrMode.Size = new System.Drawing.Size(106, 21);
            this.comboBoxRecallSceneAddrMode.TabIndex = 28;
            this.comboBoxRecallSceneAddrMode.MouseLeave += new System.EventHandler(this.comboBoxRecallSceneAddrMode_MouseLeave);
            this.comboBoxRecallSceneAddrMode.MouseHover += new System.EventHandler(this.comboBoxRecallSceneAddrMode_MouseHover);
            // 
            // buttonRecallScene
            // 
            this.buttonRecallScene.Location = new System.Drawing.Point(3, 110);
            this.buttonRecallScene.Name = "buttonRecallScene";
            this.buttonRecallScene.Size = new System.Drawing.Size(80, 22);
            this.buttonRecallScene.TabIndex = 27;
            this.buttonRecallScene.Text = "Recall Scn";
            this.buttonRecallScene.UseVisualStyleBackColor = true;
            this.buttonRecallScene.Click += new System.EventHandler(this.buttonRecallScene_Click_1);
            // 
            // textBoxStoreSceneSceneId
            // 
            this.textBoxStoreSceneSceneId.Location = new System.Drawing.Point(655, 84);
            this.textBoxStoreSceneSceneId.Name = "textBoxStoreSceneSceneId";
            this.textBoxStoreSceneSceneId.Size = new System.Drawing.Size(106, 20);
            this.textBoxStoreSceneSceneId.TabIndex = 26;
            this.textBoxStoreSceneSceneId.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxStoreSceneSceneId_MouseClick);
            this.textBoxStoreSceneSceneId.Leave += new System.EventHandler(this.textBoxStoreSceneSceneId_Leave);
            this.textBoxStoreSceneSceneId.MouseLeave += new System.EventHandler(this.textBoxStoreSceneSceneId_MouseLeave);
            this.textBoxStoreSceneSceneId.MouseHover += new System.EventHandler(this.textBoxStoreSceneSceneId_MouseHover);
            // 
            // textBoxStoreSceneGroupId
            // 
            this.textBoxStoreSceneGroupId.Location = new System.Drawing.Point(542, 84);
            this.textBoxStoreSceneGroupId.Name = "textBoxStoreSceneGroupId";
            this.textBoxStoreSceneGroupId.Size = new System.Drawing.Size(106, 20);
            this.textBoxStoreSceneGroupId.TabIndex = 25;
            this.textBoxStoreSceneGroupId.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxStoreSceneGroupId_MouseClick);
            this.textBoxStoreSceneGroupId.Leave += new System.EventHandler(this.textBoxStoreSceneGroupId_Leave);
            this.textBoxStoreSceneGroupId.MouseLeave += new System.EventHandler(this.textBoxStoreSceneGroupId_MouseLeave);
            this.textBoxStoreSceneGroupId.MouseHover += new System.EventHandler(this.textBoxStoreSceneGroupId_MouseHover);
            // 
            // textBoxStoreSceneDstEndPoint
            // 
            this.textBoxStoreSceneDstEndPoint.Location = new System.Drawing.Point(429, 84);
            this.textBoxStoreSceneDstEndPoint.Name = "textBoxStoreSceneDstEndPoint";
            this.textBoxStoreSceneDstEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxStoreSceneDstEndPoint.TabIndex = 24;
            this.textBoxStoreSceneDstEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxStoreSceneDstEndPoint_MouseClick);
            this.textBoxStoreSceneDstEndPoint.Leave += new System.EventHandler(this.textBoxStoreSceneDstEndPoint_Leave);
            this.textBoxStoreSceneDstEndPoint.MouseLeave += new System.EventHandler(this.textBoxStoreSceneDstEndPoint_MouseLeave);
            this.textBoxStoreSceneDstEndPoint.MouseHover += new System.EventHandler(this.textBoxStoreSceneDstEndPoint_MouseHover);
            // 
            // textBoxStoreSceneSrcEndPoint
            // 
            this.textBoxStoreSceneSrcEndPoint.Location = new System.Drawing.Point(316, 84);
            this.textBoxStoreSceneSrcEndPoint.Name = "textBoxStoreSceneSrcEndPoint";
            this.textBoxStoreSceneSrcEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxStoreSceneSrcEndPoint.TabIndex = 23;
            this.textBoxStoreSceneSrcEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxStoreSceneSrcEndPoint_MouseClick);
            this.textBoxStoreSceneSrcEndPoint.Leave += new System.EventHandler(this.textBoxStoreSceneSrcEndPoint_Leave);
            this.textBoxStoreSceneSrcEndPoint.MouseLeave += new System.EventHandler(this.textBoxStoreSceneSrcEndPoint_MouseLeave);
            this.textBoxStoreSceneSrcEndPoint.MouseHover += new System.EventHandler(this.textBoxStoreSceneSrcEndPoint_MouseHover);
            // 
            // textBoxStoreSceneAddr
            // 
            this.textBoxStoreSceneAddr.Location = new System.Drawing.Point(202, 84);
            this.textBoxStoreSceneAddr.Name = "textBoxStoreSceneAddr";
            this.textBoxStoreSceneAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxStoreSceneAddr.TabIndex = 22;
            this.textBoxStoreSceneAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxStoreSceneAddr_MouseClick);
            this.textBoxStoreSceneAddr.Leave += new System.EventHandler(this.textBoxStoreSceneAddr_Leave);
            this.textBoxStoreSceneAddr.MouseLeave += new System.EventHandler(this.textBoxStoreSceneAddr_MouseLeave);
            this.textBoxStoreSceneAddr.MouseHover += new System.EventHandler(this.textBoxStoreSceneAddr_MouseHover);
            // 
            // comboBoxStoreSceneAddrMode
            // 
            this.comboBoxStoreSceneAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxStoreSceneAddrMode.FormattingEnabled = true;
            this.comboBoxStoreSceneAddrMode.Location = new System.Drawing.Point(90, 84);
            this.comboBoxStoreSceneAddrMode.Name = "comboBoxStoreSceneAddrMode";
            this.comboBoxStoreSceneAddrMode.Size = new System.Drawing.Size(106, 21);
            this.comboBoxStoreSceneAddrMode.TabIndex = 21;
            this.comboBoxStoreSceneAddrMode.MouseLeave += new System.EventHandler(this.comboBoxStoreSceneAddrMode_MouseLeave);
            this.comboBoxStoreSceneAddrMode.MouseHover += new System.EventHandler(this.comboBoxStoreSceneAddrMode_MouseHover);
            // 
            // buttonStoreScene
            // 
            this.buttonStoreScene.Location = new System.Drawing.Point(3, 82);
            this.buttonStoreScene.Name = "buttonStoreScene";
            this.buttonStoreScene.Size = new System.Drawing.Size(80, 22);
            this.buttonStoreScene.TabIndex = 20;
            this.buttonStoreScene.Text = "Store Scene";
            this.buttonStoreScene.UseVisualStyleBackColor = true;
            this.buttonStoreScene.Click += new System.EventHandler(this.buttonStoreScene_Click);
            // 
            // textBoxAddSceneMaxNameLen
            // 
            this.textBoxAddSceneMaxNameLen.Location = new System.Drawing.Point(542, 58);
            this.textBoxAddSceneMaxNameLen.Name = "textBoxAddSceneMaxNameLen";
            this.textBoxAddSceneMaxNameLen.Size = new System.Drawing.Size(106, 20);
            this.textBoxAddSceneMaxNameLen.TabIndex = 17;
            this.textBoxAddSceneMaxNameLen.Visible = false;
            this.textBoxAddSceneMaxNameLen.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddSceneMaxNameLen_MouseClick);
            this.textBoxAddSceneMaxNameLen.Leave += new System.EventHandler(this.textBoxAddSceneMaxNameLen_Leave);
            this.textBoxAddSceneMaxNameLen.MouseLeave += new System.EventHandler(this.textBoxAddSceneMaxNameLen_MouseLeave);
            this.textBoxAddSceneMaxNameLen.MouseHover += new System.EventHandler(this.textBoxAddSceneMaxNameLen_MouseHover);
            // 
            // textBoxAddSceneNameLen
            // 
            this.textBoxAddSceneNameLen.Location = new System.Drawing.Point(429, 58);
            this.textBoxAddSceneNameLen.Name = "textBoxAddSceneNameLen";
            this.textBoxAddSceneNameLen.Size = new System.Drawing.Size(106, 20);
            this.textBoxAddSceneNameLen.TabIndex = 16;
            this.textBoxAddSceneNameLen.Visible = false;
            this.textBoxAddSceneNameLen.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddSceneNameLen_MouseClick);
            this.textBoxAddSceneNameLen.Leave += new System.EventHandler(this.textBoxAddSceneNameLen_Leave);
            this.textBoxAddSceneNameLen.MouseLeave += new System.EventHandler(this.textBoxAddSceneNameLen_MouseLeave);
            this.textBoxAddSceneNameLen.MouseHover += new System.EventHandler(this.textBoxAddSceneNameLen_MouseHover);
            // 
            // textBoxAddSceneName
            // 
            this.textBoxAddSceneName.Location = new System.Drawing.Point(316, 58);
            this.textBoxAddSceneName.Name = "textBoxAddSceneName";
            this.textBoxAddSceneName.Size = new System.Drawing.Size(106, 20);
            this.textBoxAddSceneName.TabIndex = 15;
            this.textBoxAddSceneName.Visible = false;
            this.textBoxAddSceneName.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddSceneName_MouseClick);
            this.textBoxAddSceneName.Leave += new System.EventHandler(this.textBoxAddSceneName_Leave);
            this.textBoxAddSceneName.MouseLeave += new System.EventHandler(this.textBoxAddSceneName_MouseLeave);
            this.textBoxAddSceneName.MouseHover += new System.EventHandler(this.textBoxAddSceneName_MouseHover);
            // 
            // textBoxAddSceneTransTime
            // 
            this.textBoxAddSceneTransTime.Location = new System.Drawing.Point(202, 58);
            this.textBoxAddSceneTransTime.Name = "textBoxAddSceneTransTime";
            this.textBoxAddSceneTransTime.Size = new System.Drawing.Size(106, 20);
            this.textBoxAddSceneTransTime.TabIndex = 14;
            this.textBoxAddSceneTransTime.Visible = false;
            this.textBoxAddSceneTransTime.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddSceneTransTime_MouseClick);
            this.textBoxAddSceneTransTime.Leave += new System.EventHandler(this.textBoxAddSceneTransTime_Leave);
            this.textBoxAddSceneTransTime.MouseLeave += new System.EventHandler(this.textBoxAddSceneTransTime_MouseLeave);
            this.textBoxAddSceneTransTime.MouseHover += new System.EventHandler(this.textBoxAddSceneTransTime_MouseHover);
            // 
            // textBoxAddSceneSceneId
            // 
            this.textBoxAddSceneSceneId.Location = new System.Drawing.Point(655, 34);
            this.textBoxAddSceneSceneId.Name = "textBoxAddSceneSceneId";
            this.textBoxAddSceneSceneId.Size = new System.Drawing.Size(106, 20);
            this.textBoxAddSceneSceneId.TabIndex = 13;
            this.textBoxAddSceneSceneId.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddSceneSceneId_MouseClick);
            this.textBoxAddSceneSceneId.Leave += new System.EventHandler(this.textBoxAddSceneSceneId_Leave);
            this.textBoxAddSceneSceneId.MouseLeave += new System.EventHandler(this.textBoxAddSceneSceneId_MouseLeave);
            this.textBoxAddSceneSceneId.MouseHover += new System.EventHandler(this.textBoxAddSceneSceneId_MouseHover);
            // 
            // textBoxAddSceneGroupId
            // 
            this.textBoxAddSceneGroupId.Location = new System.Drawing.Point(542, 34);
            this.textBoxAddSceneGroupId.Name = "textBoxAddSceneGroupId";
            this.textBoxAddSceneGroupId.Size = new System.Drawing.Size(106, 20);
            this.textBoxAddSceneGroupId.TabIndex = 12;
            this.textBoxAddSceneGroupId.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddSceneGroupId_MouseClick);
            this.textBoxAddSceneGroupId.Leave += new System.EventHandler(this.textBoxAddSceneGroupId_Leave);
            this.textBoxAddSceneGroupId.MouseLeave += new System.EventHandler(this.textBoxAddSceneGroupId_MouseLeave);
            this.textBoxAddSceneGroupId.MouseHover += new System.EventHandler(this.textBoxAddSceneGroupId_MouseHover);
            // 
            // textBoxAddSceneDstEndPoint
            // 
            this.textBoxAddSceneDstEndPoint.Location = new System.Drawing.Point(429, 34);
            this.textBoxAddSceneDstEndPoint.Name = "textBoxAddSceneDstEndPoint";
            this.textBoxAddSceneDstEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxAddSceneDstEndPoint.TabIndex = 11;
            this.textBoxAddSceneDstEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddSceneDstEndPoint_MouseClick);
            this.textBoxAddSceneDstEndPoint.Leave += new System.EventHandler(this.textBoxAddSceneDstEndPoint_Leave);
            this.textBoxAddSceneDstEndPoint.MouseLeave += new System.EventHandler(this.textBoxAddSceneDstEndPoint_MouseLeave);
            this.textBoxAddSceneDstEndPoint.MouseHover += new System.EventHandler(this.textBoxAddSceneDstEndPoint_MouseHover);
            // 
            // textBoxAddSceneSrcEndPoint
            // 
            this.textBoxAddSceneSrcEndPoint.Location = new System.Drawing.Point(316, 34);
            this.textBoxAddSceneSrcEndPoint.Name = "textBoxAddSceneSrcEndPoint";
            this.textBoxAddSceneSrcEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxAddSceneSrcEndPoint.TabIndex = 10;
            this.textBoxAddSceneSrcEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddSceneSrcEndPoint_MouseClick);
            this.textBoxAddSceneSrcEndPoint.Leave += new System.EventHandler(this.textBoxAddSceneSrcEndPoint_Leave);
            this.textBoxAddSceneSrcEndPoint.MouseLeave += new System.EventHandler(this.textBoxAddSceneSrcEndPoint_MouseLeave);
            this.textBoxAddSceneSrcEndPoint.MouseHover += new System.EventHandler(this.textBoxAddSceneSrcEndPoint_MouseHover);
            // 
            // textBoxAddSceneAddr
            // 
            this.textBoxAddSceneAddr.Location = new System.Drawing.Point(202, 34);
            this.textBoxAddSceneAddr.Name = "textBoxAddSceneAddr";
            this.textBoxAddSceneAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxAddSceneAddr.TabIndex = 9;
            this.textBoxAddSceneAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxAddSceneAddr_MouseClick);
            this.textBoxAddSceneAddr.Leave += new System.EventHandler(this.textBoxAddSceneAddr_Leave);
            this.textBoxAddSceneAddr.MouseLeave += new System.EventHandler(this.textBoxAddSceneAddr_MouseLeave);
            this.textBoxAddSceneAddr.MouseHover += new System.EventHandler(this.textBoxAddSceneAddr_MouseHover);
            // 
            // comboBoxAddSceneAddrMode
            // 
            this.comboBoxAddSceneAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxAddSceneAddrMode.FormattingEnabled = true;
            this.comboBoxAddSceneAddrMode.Location = new System.Drawing.Point(90, 34);
            this.comboBoxAddSceneAddrMode.Name = "comboBoxAddSceneAddrMode";
            this.comboBoxAddSceneAddrMode.Size = new System.Drawing.Size(106, 21);
            this.comboBoxAddSceneAddrMode.TabIndex = 8;
            this.comboBoxAddSceneAddrMode.MouseLeave += new System.EventHandler(this.comboBoxAddSceneAddrMode_MouseLeave);
            this.comboBoxAddSceneAddrMode.MouseHover += new System.EventHandler(this.comboBoxAddSceneAddrMode_MouseHover);
            // 
            // buttonAddScene
            // 
            this.buttonAddScene.Location = new System.Drawing.Point(3, 31);
            this.buttonAddScene.Name = "buttonAddScene";
            this.buttonAddScene.Size = new System.Drawing.Size(80, 22);
            this.buttonAddScene.TabIndex = 7;
            this.buttonAddScene.Text = "Add Scene";
            this.buttonAddScene.UseVisualStyleBackColor = true;
            this.buttonAddScene.Click += new System.EventHandler(this.buttonAddScene_Click);
            // 
            // comboBoxViewSceneAddrMode
            // 
            this.comboBoxViewSceneAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxViewSceneAddrMode.FormattingEnabled = true;
            this.comboBoxViewSceneAddrMode.Location = new System.Drawing.Point(90, 5);
            this.comboBoxViewSceneAddrMode.Name = "comboBoxViewSceneAddrMode";
            this.comboBoxViewSceneAddrMode.Size = new System.Drawing.Size(106, 21);
            this.comboBoxViewSceneAddrMode.TabIndex = 1;
            this.comboBoxViewSceneAddrMode.MouseLeave += new System.EventHandler(this.comboBoxViewSceneAddrMode_MouseLeave);
            this.comboBoxViewSceneAddrMode.MouseHover += new System.EventHandler(this.comboBoxViewSceneAddrMode_MouseHover);
            // 
            // textBoxViewSceneSceneId
            // 
            this.textBoxViewSceneSceneId.Location = new System.Drawing.Point(655, 5);
            this.textBoxViewSceneSceneId.Name = "textBoxViewSceneSceneId";
            this.textBoxViewSceneSceneId.Size = new System.Drawing.Size(106, 20);
            this.textBoxViewSceneSceneId.TabIndex = 6;
            this.textBoxViewSceneSceneId.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxViewSceneSceneId_MouseClick);
            this.textBoxViewSceneSceneId.Leave += new System.EventHandler(this.textBoxViewSceneSceneId_Leave);
            this.textBoxViewSceneSceneId.MouseLeave += new System.EventHandler(this.textBoxViewSceneSceneId_MouseLeave);
            this.textBoxViewSceneSceneId.MouseHover += new System.EventHandler(this.textBoxViewSceneSceneId_MouseHover);
            // 
            // textBoxViewSceneGroupId
            // 
            this.textBoxViewSceneGroupId.Location = new System.Drawing.Point(542, 5);
            this.textBoxViewSceneGroupId.Name = "textBoxViewSceneGroupId";
            this.textBoxViewSceneGroupId.Size = new System.Drawing.Size(106, 20);
            this.textBoxViewSceneGroupId.TabIndex = 5;
            this.textBoxViewSceneGroupId.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxViewSceneGroupId_MouseClick);
            this.textBoxViewSceneGroupId.Leave += new System.EventHandler(this.textBoxViewSceneGroupId_Leave);
            this.textBoxViewSceneGroupId.MouseLeave += new System.EventHandler(this.textBoxViewSceneGroupId_MouseLeave);
            this.textBoxViewSceneGroupId.MouseHover += new System.EventHandler(this.textBoxViewSceneGroupId_MouseHover);
            // 
            // textBoxViewSceneDstEndPoint
            // 
            this.textBoxViewSceneDstEndPoint.Location = new System.Drawing.Point(429, 5);
            this.textBoxViewSceneDstEndPoint.Name = "textBoxViewSceneDstEndPoint";
            this.textBoxViewSceneDstEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxViewSceneDstEndPoint.TabIndex = 4;
            this.textBoxViewSceneDstEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxViewSceneDstEndPoint_MouseClick);
            this.textBoxViewSceneDstEndPoint.Leave += new System.EventHandler(this.textBoxViewSceneDstEndPoint_Leave);
            this.textBoxViewSceneDstEndPoint.MouseLeave += new System.EventHandler(this.textBoxViewSceneDstEndPoint_MouseLeave);
            this.textBoxViewSceneDstEndPoint.MouseHover += new System.EventHandler(this.textBoxViewSceneDstEndPoint_MouseHover);
            // 
            // textBoxViewSceneSrcEndPoint
            // 
            this.textBoxViewSceneSrcEndPoint.Location = new System.Drawing.Point(316, 6);
            this.textBoxViewSceneSrcEndPoint.Name = "textBoxViewSceneSrcEndPoint";
            this.textBoxViewSceneSrcEndPoint.Size = new System.Drawing.Size(106, 20);
            this.textBoxViewSceneSrcEndPoint.TabIndex = 3;
            this.textBoxViewSceneSrcEndPoint.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxViewSceneSrcEndPoint_MouseClick);
            this.textBoxViewSceneSrcEndPoint.Leave += new System.EventHandler(this.textBoxViewSceneSrcEndPoint_Leave);
            this.textBoxViewSceneSrcEndPoint.MouseLeave += new System.EventHandler(this.textBoxViewSceneSrcEndPoint_MouseLeave);
            this.textBoxViewSceneSrcEndPoint.MouseHover += new System.EventHandler(this.textBoxViewSceneSrcEndPoint_MouseHover);
            // 
            // textBoxViewSceneAddr
            // 
            this.textBoxViewSceneAddr.Location = new System.Drawing.Point(202, 5);
            this.textBoxViewSceneAddr.Name = "textBoxViewSceneAddr";
            this.textBoxViewSceneAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxViewSceneAddr.TabIndex = 2;
            this.textBoxViewSceneAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxViewSceneAddr_MouseClick);
            this.textBoxViewSceneAddr.Leave += new System.EventHandler(this.textBoxViewSceneAddr_Leave);
            this.textBoxViewSceneAddr.MouseLeave += new System.EventHandler(this.textBoxViewSceneAddr_MouseLeave);
            this.textBoxViewSceneAddr.MouseHover += new System.EventHandler(this.textBoxViewSceneAddr_MouseHover);
            // 
            // buttonViewScene
            // 
            this.buttonViewScene.Location = new System.Drawing.Point(3, 3);
            this.buttonViewScene.Name = "buttonViewScene";
            this.buttonViewScene.Size = new System.Drawing.Size(80, 22);
            this.buttonViewScene.TabIndex = 0;
            this.buttonViewScene.Text = "View Scene";
            this.buttonViewScene.UseVisualStyleBackColor = true;
            this.buttonViewScene.Click += new System.EventHandler(this.buttonViewScene_Click);
            // 
            // tabPage8
            // 
            this.tabPage8.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage8.Controls.Add(this.textBoxMoveToSatTime);
            this.tabPage8.Controls.Add(this.textBoxMoveToSatSat);
            this.tabPage8.Controls.Add(this.textBoxMoveToSatDstEp);
            this.tabPage8.Controls.Add(this.textBoxMoveToSatSrcEp);
            this.tabPage8.Controls.Add(this.buttonMoveToSat);
            this.tabPage8.Controls.Add(this.textBoxMoveToSatAddr);
            this.tabPage8.Controls.Add(this.textBoxMoveToColorTempRate);
            this.tabPage8.Controls.Add(this.textBoxMoveToColorTempTemp);
            this.tabPage8.Controls.Add(this.textBoxMoveToColorTempDstEp);
            this.tabPage8.Controls.Add(this.textBoxMoveToColorTempSrcEp);
            this.tabPage8.Controls.Add(this.textBoxMoveToColorTempAddr);
            this.tabPage8.Controls.Add(this.buttonMoveToColorTemp);
            this.tabPage8.Controls.Add(this.textBoxMoveToColorTime);
            this.tabPage8.Controls.Add(this.textBoxMoveToColorY);
            this.tabPage8.Controls.Add(this.textBoxMoveToColorX);
            this.tabPage8.Controls.Add(this.textBoxMoveToColorDstEp);
            this.tabPage8.Controls.Add(this.textBoxMoveToColorSrcEp);
            this.tabPage8.Controls.Add(this.textBoxMoveToColorAddr);
            this.tabPage8.Controls.Add(this.buttonMoveToColor);
            this.tabPage8.Controls.Add(this.textBoxMoveToHueTime);
            this.tabPage8.Controls.Add(this.textBoxMoveToHueDir);
            this.tabPage8.Controls.Add(this.textBoxMoveToHueHue);
            this.tabPage8.Controls.Add(this.textBoxMoveToHueDstEp);
            this.tabPage8.Controls.Add(this.textBoxMoveToHueSrcEp);
            this.tabPage8.Controls.Add(this.buttonMoveToHue);
            this.tabPage8.Controls.Add(this.textBoxMoveToHueAddr);
            this.tabPage8.Location = new System.Drawing.Point(4, 22);
            this.tabPage8.Name = "tabPage8";
            this.tabPage8.Size = new System.Drawing.Size(1351, 416);
            this.tabPage8.TabIndex = 7;
            this.tabPage8.Text = "Color Cluster";
            this.tabPage8.Click += new System.EventHandler(this.tabPage8_Click);
            // 
            // textBoxMoveToSatTime
            // 
            this.textBoxMoveToSatTime.Location = new System.Drawing.Point(554, 63);
            this.textBoxMoveToSatTime.Name = "textBoxMoveToSatTime";
            this.textBoxMoveToSatTime.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToSatTime.TabIndex = 19;
            this.textBoxMoveToSatTime.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToSatTime_MouseClick);
            this.textBoxMoveToSatTime.Leave += new System.EventHandler(this.textBoxMoveToSatTime_Leave);
            this.textBoxMoveToSatTime.MouseLeave += new System.EventHandler(this.textBoxMoveToSatTime_MouseLeave);
            this.textBoxMoveToSatTime.MouseHover += new System.EventHandler(this.textBoxMoveToSatTime_MouseHover);
            // 
            // textBoxMoveToSatSat
            // 
            this.textBoxMoveToSatSat.Location = new System.Drawing.Point(442, 63);
            this.textBoxMoveToSatSat.Name = "textBoxMoveToSatSat";
            this.textBoxMoveToSatSat.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToSatSat.TabIndex = 18;
            this.textBoxMoveToSatSat.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToSatSat_MouseClick);
            this.textBoxMoveToSatSat.Leave += new System.EventHandler(this.textBoxMoveToSatSat_Leave);
            this.textBoxMoveToSatSat.MouseLeave += new System.EventHandler(this.textBoxMoveToSatSat_MouseLeave);
            this.textBoxMoveToSatSat.MouseHover += new System.EventHandler(this.textBoxMoveToSatSat_MouseHover);
            // 
            // textBoxMoveToSatDstEp
            // 
            this.textBoxMoveToSatDstEp.Location = new System.Drawing.Point(329, 63);
            this.textBoxMoveToSatDstEp.Name = "textBoxMoveToSatDstEp";
            this.textBoxMoveToSatDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToSatDstEp.TabIndex = 17;
            this.textBoxMoveToSatDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToSatDstEp_MouseClick);
            this.textBoxMoveToSatDstEp.Leave += new System.EventHandler(this.textBoxMoveToSatDstEp_Leave);
            this.textBoxMoveToSatDstEp.MouseLeave += new System.EventHandler(this.textBoxMoveToSatDstEp_MouseLeave);
            this.textBoxMoveToSatDstEp.MouseHover += new System.EventHandler(this.textBoxMoveToSatDstEp_MouseHover);
            // 
            // textBoxMoveToSatSrcEp
            // 
            this.textBoxMoveToSatSrcEp.Location = new System.Drawing.Point(215, 63);
            this.textBoxMoveToSatSrcEp.Name = "textBoxMoveToSatSrcEp";
            this.textBoxMoveToSatSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToSatSrcEp.TabIndex = 16;
            this.textBoxMoveToSatSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToSatSrcEp_MouseClick);
            this.textBoxMoveToSatSrcEp.Leave += new System.EventHandler(this.textBoxMoveToSatSrcEp_Leave);
            this.textBoxMoveToSatSrcEp.MouseLeave += new System.EventHandler(this.textBoxMoveToSatSrcEp_MouseLeave);
            this.textBoxMoveToSatSrcEp.MouseHover += new System.EventHandler(this.textBoxMoveToSatSrcEp_MouseHover);
            // 
            // buttonMoveToSat
            // 
            this.buttonMoveToSat.Location = new System.Drawing.Point(4, 62);
            this.buttonMoveToSat.Name = "buttonMoveToSat";
            this.buttonMoveToSat.Size = new System.Drawing.Size(90, 22);
            this.buttonMoveToSat.TabIndex = 14;
            this.buttonMoveToSat.Text = "MoveToSat";
            this.buttonMoveToSat.UseVisualStyleBackColor = true;
            this.buttonMoveToSat.Click += new System.EventHandler(this.buttonMoveToSat_Click);
            // 
            // textBoxMoveToSatAddr
            // 
            this.textBoxMoveToSatAddr.Location = new System.Drawing.Point(102, 63);
            this.textBoxMoveToSatAddr.Name = "textBoxMoveToSatAddr";
            this.textBoxMoveToSatAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToSatAddr.TabIndex = 15;
            this.textBoxMoveToSatAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToSatAddr_MouseClick);
            this.textBoxMoveToSatAddr.Leave += new System.EventHandler(this.textBoxMoveToSatAddr_Leave);
            this.textBoxMoveToSatAddr.MouseLeave += new System.EventHandler(this.textBoxMoveToSatAddr_MouseLeave);
            this.textBoxMoveToSatAddr.MouseHover += new System.EventHandler(this.textBoxMoveToSatAddr_MouseHover);
            // 
            // textBoxMoveToColorTempRate
            // 
            this.textBoxMoveToColorTempRate.Location = new System.Drawing.Point(554, 93);
            this.textBoxMoveToColorTempRate.Name = "textBoxMoveToColorTempRate";
            this.textBoxMoveToColorTempRate.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToColorTempRate.TabIndex = 25;
            this.textBoxMoveToColorTempRate.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToColorTempRate_MouseClick);
            this.textBoxMoveToColorTempRate.Leave += new System.EventHandler(this.textBoxMoveToColorTempRate_Leave);
            this.textBoxMoveToColorTempRate.MouseLeave += new System.EventHandler(this.textBoxMoveToColorTempRate_MouseLeave);
            this.textBoxMoveToColorTempRate.MouseHover += new System.EventHandler(this.textBoxMoveToColorTempRate_MouseHover);
            // 
            // textBoxMoveToColorTempTemp
            // 
            this.textBoxMoveToColorTempTemp.Location = new System.Drawing.Point(442, 93);
            this.textBoxMoveToColorTempTemp.Name = "textBoxMoveToColorTempTemp";
            this.textBoxMoveToColorTempTemp.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToColorTempTemp.TabIndex = 24;
            this.textBoxMoveToColorTempTemp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToColorTempTemp_MouseClick);
            this.textBoxMoveToColorTempTemp.Leave += new System.EventHandler(this.textBoxMoveToColorTempTemp_Leave);
            this.textBoxMoveToColorTempTemp.MouseLeave += new System.EventHandler(this.textBoxMoveToColorTempTemp_MouseLeave);
            this.textBoxMoveToColorTempTemp.MouseHover += new System.EventHandler(this.textBoxMoveToColorTempTemp_MouseHover);
            // 
            // textBoxMoveToColorTempDstEp
            // 
            this.textBoxMoveToColorTempDstEp.Location = new System.Drawing.Point(329, 93);
            this.textBoxMoveToColorTempDstEp.Name = "textBoxMoveToColorTempDstEp";
            this.textBoxMoveToColorTempDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToColorTempDstEp.TabIndex = 23;
            this.textBoxMoveToColorTempDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToColorTempDstEp_MouseClick);
            this.textBoxMoveToColorTempDstEp.Leave += new System.EventHandler(this.textBoxMoveToColorTempDstEp_Leave);
            this.textBoxMoveToColorTempDstEp.MouseLeave += new System.EventHandler(this.textBoxMoveToColorTempDstEp_MouseLeave);
            this.textBoxMoveToColorTempDstEp.MouseHover += new System.EventHandler(this.textBoxMoveToColorTempDstEp_MouseHover);
            // 
            // textBoxMoveToColorTempSrcEp
            // 
            this.textBoxMoveToColorTempSrcEp.Location = new System.Drawing.Point(215, 93);
            this.textBoxMoveToColorTempSrcEp.Name = "textBoxMoveToColorTempSrcEp";
            this.textBoxMoveToColorTempSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToColorTempSrcEp.TabIndex = 22;
            this.textBoxMoveToColorTempSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToColorTempSrcEp_MouseClick);
            this.textBoxMoveToColorTempSrcEp.Leave += new System.EventHandler(this.textBoxMoveToColorTempSrcEp_Leave);
            this.textBoxMoveToColorTempSrcEp.MouseLeave += new System.EventHandler(this.textBoxMoveToColorTempSrcEp_MouseLeave);
            this.textBoxMoveToColorTempSrcEp.MouseHover += new System.EventHandler(this.textBoxMoveToColorTempSrcEp_MouseHover);
            // 
            // textBoxMoveToColorTempAddr
            // 
            this.textBoxMoveToColorTempAddr.Location = new System.Drawing.Point(102, 93);
            this.textBoxMoveToColorTempAddr.Name = "textBoxMoveToColorTempAddr";
            this.textBoxMoveToColorTempAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToColorTempAddr.TabIndex = 21;
            this.textBoxMoveToColorTempAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToColorTempAddr_MouseClick);
            this.textBoxMoveToColorTempAddr.Leave += new System.EventHandler(this.textBoxMoveToColorTempAddr_Leave);
            this.textBoxMoveToColorTempAddr.MouseLeave += new System.EventHandler(this.textBoxMoveToColorTempAddr_MouseLeave);
            this.textBoxMoveToColorTempAddr.MouseHover += new System.EventHandler(this.textBoxMoveToColorTempAddr_MouseHover);
            // 
            // buttonMoveToColorTemp
            // 
            this.buttonMoveToColorTemp.Location = new System.Drawing.Point(4, 90);
            this.buttonMoveToColorTemp.Name = "buttonMoveToColorTemp";
            this.buttonMoveToColorTemp.Size = new System.Drawing.Size(90, 22);
            this.buttonMoveToColorTemp.TabIndex = 20;
            this.buttonMoveToColorTemp.Text = "MoveToTemp";
            this.buttonMoveToColorTemp.UseVisualStyleBackColor = true;
            this.buttonMoveToColorTemp.Click += new System.EventHandler(this.buttonMoveToColorTemp_Click);
            // 
            // textBoxMoveToColorTime
            // 
            this.textBoxMoveToColorTime.Location = new System.Drawing.Point(668, 34);
            this.textBoxMoveToColorTime.Name = "textBoxMoveToColorTime";
            this.textBoxMoveToColorTime.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToColorTime.TabIndex = 13;
            this.textBoxMoveToColorTime.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToColorTime_MouseClick);
            this.textBoxMoveToColorTime.Leave += new System.EventHandler(this.textBoxMoveToColorTime_Leave);
            this.textBoxMoveToColorTime.MouseLeave += new System.EventHandler(this.textBoxMoveToColorTime_MouseLeave);
            this.textBoxMoveToColorTime.MouseHover += new System.EventHandler(this.textBoxMoveToColorTime_MouseHover);
            // 
            // textBoxMoveToColorY
            // 
            this.textBoxMoveToColorY.Location = new System.Drawing.Point(554, 34);
            this.textBoxMoveToColorY.Name = "textBoxMoveToColorY";
            this.textBoxMoveToColorY.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToColorY.TabIndex = 12;
            this.textBoxMoveToColorY.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToColorY_MouseClick);
            this.textBoxMoveToColorY.Leave += new System.EventHandler(this.textBoxMoveToColorY_Leave);
            this.textBoxMoveToColorY.MouseLeave += new System.EventHandler(this.textBoxMoveToColorY_MouseLeave);
            this.textBoxMoveToColorY.MouseHover += new System.EventHandler(this.textBoxMoveToColorY_MouseHover);
            // 
            // textBoxMoveToColorX
            // 
            this.textBoxMoveToColorX.Location = new System.Drawing.Point(442, 35);
            this.textBoxMoveToColorX.Name = "textBoxMoveToColorX";
            this.textBoxMoveToColorX.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToColorX.TabIndex = 11;
            this.textBoxMoveToColorX.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToColorX_MouseClick);
            this.textBoxMoveToColorX.Leave += new System.EventHandler(this.textBoxMoveToColorX_Leave);
            this.textBoxMoveToColorX.MouseLeave += new System.EventHandler(this.textBoxMoveToColorX_MouseLeave);
            this.textBoxMoveToColorX.MouseHover += new System.EventHandler(this.textBoxMoveToColorX_MouseHover);
            // 
            // textBoxMoveToColorDstEp
            // 
            this.textBoxMoveToColorDstEp.Location = new System.Drawing.Point(329, 34);
            this.textBoxMoveToColorDstEp.Name = "textBoxMoveToColorDstEp";
            this.textBoxMoveToColorDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToColorDstEp.TabIndex = 10;
            this.textBoxMoveToColorDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToColorDstEp_MouseClick);
            this.textBoxMoveToColorDstEp.Leave += new System.EventHandler(this.textBoxMoveToColorDstEp_Leave);
            this.textBoxMoveToColorDstEp.MouseLeave += new System.EventHandler(this.textBoxMoveToColorDstEp_MouseLeave);
            this.textBoxMoveToColorDstEp.MouseHover += new System.EventHandler(this.textBoxMoveToColorDstEp_MouseHover);
            // 
            // textBoxMoveToColorSrcEp
            // 
            this.textBoxMoveToColorSrcEp.Location = new System.Drawing.Point(215, 34);
            this.textBoxMoveToColorSrcEp.Name = "textBoxMoveToColorSrcEp";
            this.textBoxMoveToColorSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToColorSrcEp.TabIndex = 9;
            this.textBoxMoveToColorSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToColorSrcEp_MouseClick);
            this.textBoxMoveToColorSrcEp.Leave += new System.EventHandler(this.textBoxMoveToColorSrcEp_Leave);
            this.textBoxMoveToColorSrcEp.MouseLeave += new System.EventHandler(this.textBoxMoveToColorSrcEp_MouseLeave);
            this.textBoxMoveToColorSrcEp.MouseHover += new System.EventHandler(this.textBoxMoveToColorSrcEp_MouseHover);
            // 
            // textBoxMoveToColorAddr
            // 
            this.textBoxMoveToColorAddr.Location = new System.Drawing.Point(102, 35);
            this.textBoxMoveToColorAddr.Name = "textBoxMoveToColorAddr";
            this.textBoxMoveToColorAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToColorAddr.TabIndex = 8;
            this.textBoxMoveToColorAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToColorAddr_MouseClick);
            this.textBoxMoveToColorAddr.Leave += new System.EventHandler(this.textBoxMoveToColorAddr_Leave);
            this.textBoxMoveToColorAddr.MouseLeave += new System.EventHandler(this.textBoxMoveToColorAddr_MouseLeave);
            this.textBoxMoveToColorAddr.MouseHover += new System.EventHandler(this.textBoxMoveToColorAddr_MouseHover);
            // 
            // buttonMoveToColor
            // 
            this.buttonMoveToColor.Location = new System.Drawing.Point(4, 33);
            this.buttonMoveToColor.Name = "buttonMoveToColor";
            this.buttonMoveToColor.Size = new System.Drawing.Size(90, 22);
            this.buttonMoveToColor.TabIndex = 7;
            this.buttonMoveToColor.Text = "MoveToColor";
            this.buttonMoveToColor.UseVisualStyleBackColor = true;
            this.buttonMoveToColor.Click += new System.EventHandler(this.buttonMoveToColor_Click);
            // 
            // textBoxMoveToHueTime
            // 
            this.textBoxMoveToHueTime.Location = new System.Drawing.Point(668, 6);
            this.textBoxMoveToHueTime.Name = "textBoxMoveToHueTime";
            this.textBoxMoveToHueTime.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToHueTime.TabIndex = 6;
            this.textBoxMoveToHueTime.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToHueTime_MouseClick);
            this.textBoxMoveToHueTime.Leave += new System.EventHandler(this.textBoxMoveToHueTime_Leave);
            this.textBoxMoveToHueTime.MouseLeave += new System.EventHandler(this.textBoxMoveToHueTime_MouseLeave);
            this.textBoxMoveToHueTime.MouseHover += new System.EventHandler(this.textBoxMoveToHueTime_MouseHover);
            // 
            // textBoxMoveToHueDir
            // 
            this.textBoxMoveToHueDir.Location = new System.Drawing.Point(554, 6);
            this.textBoxMoveToHueDir.Name = "textBoxMoveToHueDir";
            this.textBoxMoveToHueDir.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToHueDir.TabIndex = 5;
            this.textBoxMoveToHueDir.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToHueDir_MouseClick);
            this.textBoxMoveToHueDir.Leave += new System.EventHandler(this.textBoxMoveToHueDir_Leave);
            this.textBoxMoveToHueDir.MouseLeave += new System.EventHandler(this.textBoxMoveToHueDir_MouseLeave);
            this.textBoxMoveToHueDir.MouseHover += new System.EventHandler(this.textBoxMoveToHueDir_MouseHover);
            // 
            // textBoxMoveToHueHue
            // 
            this.textBoxMoveToHueHue.Location = new System.Drawing.Point(442, 6);
            this.textBoxMoveToHueHue.Name = "textBoxMoveToHueHue";
            this.textBoxMoveToHueHue.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToHueHue.TabIndex = 4;
            this.textBoxMoveToHueHue.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToHueHue_MouseClick);
            this.textBoxMoveToHueHue.Leave += new System.EventHandler(this.textBoxMoveToHueHue_Leave);
            this.textBoxMoveToHueHue.MouseLeave += new System.EventHandler(this.textBoxMoveToHueHue_MouseLeave);
            this.textBoxMoveToHueHue.MouseHover += new System.EventHandler(this.textBoxMoveToHueHue_MouseHover);
            // 
            // textBoxMoveToHueDstEp
            // 
            this.textBoxMoveToHueDstEp.Location = new System.Drawing.Point(329, 6);
            this.textBoxMoveToHueDstEp.Name = "textBoxMoveToHueDstEp";
            this.textBoxMoveToHueDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToHueDstEp.TabIndex = 3;
            this.textBoxMoveToHueDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToHueDstEp_MouseClick);
            this.textBoxMoveToHueDstEp.Leave += new System.EventHandler(this.textBoxMoveToHueDstEp_Leave);
            this.textBoxMoveToHueDstEp.MouseLeave += new System.EventHandler(this.textBoxMoveToHueDstEp_MouseLeave);
            this.textBoxMoveToHueDstEp.MouseHover += new System.EventHandler(this.textBoxMoveToHueDstEp_MouseHover);
            // 
            // textBoxMoveToHueSrcEp
            // 
            this.textBoxMoveToHueSrcEp.Location = new System.Drawing.Point(215, 6);
            this.textBoxMoveToHueSrcEp.Name = "textBoxMoveToHueSrcEp";
            this.textBoxMoveToHueSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToHueSrcEp.TabIndex = 2;
            this.textBoxMoveToHueSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToHueSrcEp_MouseClick);
            this.textBoxMoveToHueSrcEp.Leave += new System.EventHandler(this.textBoxMoveToHueSrcEp_Leave);
            this.textBoxMoveToHueSrcEp.MouseLeave += new System.EventHandler(this.textBoxMoveToHueSrcEp_MouseLeave);
            this.textBoxMoveToHueSrcEp.MouseHover += new System.EventHandler(this.textBoxMoveToHueSrcEp_MouseHover);
            // 
            // buttonMoveToHue
            // 
            this.buttonMoveToHue.Location = new System.Drawing.Point(4, 4);
            this.buttonMoveToHue.Name = "buttonMoveToHue";
            this.buttonMoveToHue.Size = new System.Drawing.Size(90, 22);
            this.buttonMoveToHue.TabIndex = 0;
            this.buttonMoveToHue.Text = "MoveToHue";
            this.buttonMoveToHue.UseVisualStyleBackColor = true;
            this.buttonMoveToHue.Click += new System.EventHandler(this.buttonMoveToHue_Click);
            // 
            // textBoxMoveToHueAddr
            // 
            this.textBoxMoveToHueAddr.Location = new System.Drawing.Point(102, 6);
            this.textBoxMoveToHueAddr.Name = "textBoxMoveToHueAddr";
            this.textBoxMoveToHueAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxMoveToHueAddr.TabIndex = 1;
            this.textBoxMoveToHueAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxMoveToHueAddr_MouseClick);
            this.textBoxMoveToHueAddr.Leave += new System.EventHandler(this.textBoxMoveToHueAddr_Leave);
            this.textBoxMoveToHueAddr.MouseLeave += new System.EventHandler(this.textBoxMoveToHueAddr_MouseLeave);
            this.textBoxMoveToHueAddr.MouseHover += new System.EventHandler(this.textBoxMoveToHueAddr_MouseHover);
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage1.Controls.Add(this.comboBoxLockUnlock);
            this.tabPage1.Controls.Add(this.textBoxLockUnlockDstEp);
            this.tabPage1.Controls.Add(this.textBoxLockUnlockSrcEp);
            this.tabPage1.Controls.Add(this.textBoxLockUnlockAddr);
            this.tabPage1.Controls.Add(this.buttonLockUnlock);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Size = new System.Drawing.Size(1351, 416);
            this.tabPage1.TabIndex = 8;
            this.tabPage1.Text = "Door Lock Cluster";
            this.tabPage1.Click += new System.EventHandler(this.tabPage1_Click);
            // 
            // comboBoxLockUnlock
            // 
            this.comboBoxLockUnlock.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxLockUnlock.FormattingEnabled = true;
            this.comboBoxLockUnlock.Location = new System.Drawing.Point(430, 6);
            this.comboBoxLockUnlock.Name = "comboBoxLockUnlock";
            this.comboBoxLockUnlock.Size = new System.Drawing.Size(129, 21);
            this.comboBoxLockUnlock.TabIndex = 4;
            this.comboBoxLockUnlock.MouseLeave += new System.EventHandler(this.comboBoxLockUnlock_MouseLeave);
            this.comboBoxLockUnlock.MouseHover += new System.EventHandler(this.comboBoxLockUnlock_MouseHover);
            // 
            // textBoxLockUnlockDstEp
            // 
            this.textBoxLockUnlockDstEp.Location = new System.Drawing.Point(317, 6);
            this.textBoxLockUnlockDstEp.Name = "textBoxLockUnlockDstEp";
            this.textBoxLockUnlockDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxLockUnlockDstEp.TabIndex = 3;
            this.textBoxLockUnlockDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxLockUnlockDstEp_MouseClick);
            this.textBoxLockUnlockDstEp.Leave += new System.EventHandler(this.textBoxLockUnlockDstEp_Leave);
            this.textBoxLockUnlockDstEp.MouseLeave += new System.EventHandler(this.textBoxLockUnlockDstEp_MouseLeave);
            this.textBoxLockUnlockDstEp.MouseHover += new System.EventHandler(this.textBoxLockUnlockDstEp_MouseHover);
            // 
            // textBoxLockUnlockSrcEp
            // 
            this.textBoxLockUnlockSrcEp.Location = new System.Drawing.Point(204, 6);
            this.textBoxLockUnlockSrcEp.Name = "textBoxLockUnlockSrcEp";
            this.textBoxLockUnlockSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxLockUnlockSrcEp.TabIndex = 2;
            this.textBoxLockUnlockSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxLockUnlockSrcEp_MouseClick);
            this.textBoxLockUnlockSrcEp.Leave += new System.EventHandler(this.textBoxLockUnlockSrcEp_Leave);
            this.textBoxLockUnlockSrcEp.MouseLeave += new System.EventHandler(this.textBoxLockUnlockSrcEp_MouseLeave);
            this.textBoxLockUnlockSrcEp.MouseHover += new System.EventHandler(this.textBoxLockUnlockSrcEp_MouseHover);
            // 
            // textBoxLockUnlockAddr
            // 
            this.textBoxLockUnlockAddr.Location = new System.Drawing.Point(90, 6);
            this.textBoxLockUnlockAddr.Name = "textBoxLockUnlockAddr";
            this.textBoxLockUnlockAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxLockUnlockAddr.TabIndex = 1;
            this.textBoxLockUnlockAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxLockUnlockAddr_MouseClick);
            this.textBoxLockUnlockAddr.Leave += new System.EventHandler(this.textBoxLockUnlockAddr_Leave);
            this.textBoxLockUnlockAddr.MouseLeave += new System.EventHandler(this.textBoxLockUnlockAddr_MouseLeave);
            this.textBoxLockUnlockAddr.MouseHover += new System.EventHandler(this.textBoxLockUnlockAddr_MouseHover);
            // 
            // buttonLockUnlock
            // 
            this.buttonLockUnlock.Location = new System.Drawing.Point(4, 4);
            this.buttonLockUnlock.Name = "buttonLockUnlock";
            this.buttonLockUnlock.Size = new System.Drawing.Size(80, 22);
            this.buttonLockUnlock.TabIndex = 0;
            this.buttonLockUnlock.Text = "LockUnlock";
            this.buttonLockUnlock.UseVisualStyleBackColor = true;
            this.buttonLockUnlock.Click += new System.EventHandler(this.buttonLockUnlock_Click);
            // 
            // tabPage13
            // 
            this.tabPage13.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage13.Controls.Add(this.comboBoxEnrollRspCode);
            this.tabPage13.Controls.Add(this.textBoxEnrollRspZone);
            this.tabPage13.Controls.Add(this.textBoxEnrollRspDstEp);
            this.tabPage13.Controls.Add(this.textBoxEnrollRspSrcEp);
            this.tabPage13.Controls.Add(this.textBoxEnrollRspAddr);
            this.tabPage13.Controls.Add(this.comboBoxEnrollRspAddrMode);
            this.tabPage13.Controls.Add(this.buttonEnrollResponse);
            this.tabPage13.Location = new System.Drawing.Point(4, 22);
            this.tabPage13.Name = "tabPage13";
            this.tabPage13.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage13.Size = new System.Drawing.Size(1351, 416);
            this.tabPage13.TabIndex = 13;
            this.tabPage13.Text = "IAS Zone Cluster";
            this.tabPage13.Click += new System.EventHandler(this.tabPage13_Click);
            // 
            // comboBoxEnrollRspCode
            // 
            this.comboBoxEnrollRspCode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxEnrollRspCode.FormattingEnabled = true;
            this.comboBoxEnrollRspCode.Location = new System.Drawing.Point(545, 9);
            this.comboBoxEnrollRspCode.Name = "comboBoxEnrollRspCode";
            this.comboBoxEnrollRspCode.Size = new System.Drawing.Size(138, 21);
            this.comboBoxEnrollRspCode.TabIndex = 5;
            this.comboBoxEnrollRspCode.MouseLeave += new System.EventHandler(this.comboBoxEnrollRspCode_MouseLeave);
            this.comboBoxEnrollRspCode.MouseHover += new System.EventHandler(this.comboBoxEnrollRspCode_MouseHover);
            // 
            // textBoxEnrollRspZone
            // 
            this.textBoxEnrollRspZone.Location = new System.Drawing.Point(690, 8);
            this.textBoxEnrollRspZone.Name = "textBoxEnrollRspZone";
            this.textBoxEnrollRspZone.Size = new System.Drawing.Size(106, 20);
            this.textBoxEnrollRspZone.TabIndex = 6;
            this.textBoxEnrollRspZone.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxEnrollRspZone_MouseClick);
            this.textBoxEnrollRspZone.Leave += new System.EventHandler(this.textBoxEnrollRspZone_Leave);
            this.textBoxEnrollRspZone.MouseLeave += new System.EventHandler(this.textBoxEnrollRspZone_MouseLeave);
            this.textBoxEnrollRspZone.MouseHover += new System.EventHandler(this.textBoxEnrollRspZone_MouseHover);
            // 
            // textBoxEnrollRspDstEp
            // 
            this.textBoxEnrollRspDstEp.Location = new System.Drawing.Point(432, 9);
            this.textBoxEnrollRspDstEp.Name = "textBoxEnrollRspDstEp";
            this.textBoxEnrollRspDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxEnrollRspDstEp.TabIndex = 4;
            this.textBoxEnrollRspDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxEnrollRspDstEp_MouseClick);
            this.textBoxEnrollRspDstEp.Leave += new System.EventHandler(this.textBoxEnrollRspDstEp_Leave);
            this.textBoxEnrollRspDstEp.MouseLeave += new System.EventHandler(this.textBoxEnrollRspDstEp_MouseLeave);
            this.textBoxEnrollRspDstEp.MouseHover += new System.EventHandler(this.textBoxEnrollRspDstEp_MouseHover);
            // 
            // textBoxEnrollRspSrcEp
            // 
            this.textBoxEnrollRspSrcEp.Location = new System.Drawing.Point(319, 9);
            this.textBoxEnrollRspSrcEp.Name = "textBoxEnrollRspSrcEp";
            this.textBoxEnrollRspSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxEnrollRspSrcEp.TabIndex = 3;
            this.textBoxEnrollRspSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxEnrollRspSrcEp_MouseClick);
            this.textBoxEnrollRspSrcEp.Leave += new System.EventHandler(this.textBoxEnrollRspSrcEp_Leave);
            this.textBoxEnrollRspSrcEp.MouseLeave += new System.EventHandler(this.textBoxEnrollRspSrcEp_MouseLeave);
            this.textBoxEnrollRspSrcEp.MouseHover += new System.EventHandler(this.textBoxEnrollRspSrcEp_MouseHover);
            // 
            // textBoxEnrollRspAddr
            // 
            this.textBoxEnrollRspAddr.Location = new System.Drawing.Point(206, 9);
            this.textBoxEnrollRspAddr.Name = "textBoxEnrollRspAddr";
            this.textBoxEnrollRspAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxEnrollRspAddr.TabIndex = 2;
            this.textBoxEnrollRspAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxEnrollRspAddr_MouseClick);
            this.textBoxEnrollRspAddr.Leave += new System.EventHandler(this.textBoxEnrollRspAddr_Leave);
            this.textBoxEnrollRspAddr.MouseLeave += new System.EventHandler(this.textBoxEnrollRspAddr_MouseLeave);
            this.textBoxEnrollRspAddr.MouseHover += new System.EventHandler(this.textBoxEnrollRspAddr_MouseHover);
            // 
            // comboBoxEnrollRspAddrMode
            // 
            this.comboBoxEnrollRspAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxEnrollRspAddrMode.FormattingEnabled = true;
            this.comboBoxEnrollRspAddrMode.Location = new System.Drawing.Point(93, 8);
            this.comboBoxEnrollRspAddrMode.Name = "comboBoxEnrollRspAddrMode";
            this.comboBoxEnrollRspAddrMode.Size = new System.Drawing.Size(106, 21);
            this.comboBoxEnrollRspAddrMode.TabIndex = 1;
            this.comboBoxEnrollRspAddrMode.MouseLeave += new System.EventHandler(this.comboBoxEnrollRspAddrMode_MouseLeave);
            this.comboBoxEnrollRspAddrMode.MouseHover += new System.EventHandler(this.comboBoxEnrollRspAddrMode_MouseHover);
            // 
            // buttonEnrollResponse
            // 
            this.buttonEnrollResponse.Location = new System.Drawing.Point(6, 6);
            this.buttonEnrollResponse.Name = "buttonEnrollResponse";
            this.buttonEnrollResponse.Size = new System.Drawing.Size(80, 22);
            this.buttonEnrollResponse.TabIndex = 0;
            this.buttonEnrollResponse.Text = "Enroll Rsp";
            this.buttonEnrollResponse.UseVisualStyleBackColor = true;
            this.buttonEnrollResponse.Click += new System.EventHandler(this.buttonEnrollResponse_Click);
            // 
            // tabPage15
            // 
            this.tabPage15.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage15.Controls.Add(this.label17);
            this.tabPage15.Location = new System.Drawing.Point(4, 22);
            this.tabPage15.Margin = new System.Windows.Forms.Padding(2);
            this.tabPage15.Name = "tabPage15";
            this.tabPage15.Size = new System.Drawing.Size(1351, 416);
            this.tabPage15.TabIndex = 19;
            this.tabPage15.Text = "IAS WD Cluster";
            this.tabPage15.Click += new System.EventHandler(this.tabPage15_Click);
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Font = new System.Drawing.Font("Microsoft Sans Serif", 30F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label17.Location = new System.Drawing.Point(520, 186);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(311, 46);
            this.label17.TabIndex = 16;
            this.label17.Text = "Unimplemented";
            // 
            // tabPage9
            // 
            this.tabPage9.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage9.Controls.Add(this.buttonZllTouchlinkFactoryReset);
            this.tabPage9.Controls.Add(this.buttonZllTouchlinkInitiate);
            this.tabPage9.Location = new System.Drawing.Point(4, 22);
            this.tabPage9.Name = "tabPage9";
            this.tabPage9.Size = new System.Drawing.Size(1351, 416);
            this.tabPage9.TabIndex = 9;
            this.tabPage9.Text = "ZLL Touchlink";
            this.tabPage9.Click += new System.EventHandler(this.tabPage9_Click);
            // 
            // buttonZllTouchlinkFactoryReset
            // 
            this.buttonZllTouchlinkFactoryReset.Location = new System.Drawing.Point(4, 34);
            this.buttonZllTouchlinkFactoryReset.Name = "buttonZllTouchlinkFactoryReset";
            this.buttonZllTouchlinkFactoryReset.Size = new System.Drawing.Size(80, 22);
            this.buttonZllTouchlinkFactoryReset.TabIndex = 1;
            this.buttonZllTouchlinkFactoryReset.Text = "Reset";
            this.buttonZllTouchlinkFactoryReset.UseVisualStyleBackColor = true;
            this.buttonZllTouchlinkFactoryReset.Click += new System.EventHandler(this.buttonZllTouchlinkFactoryReset_Click);
            // 
            // buttonZllTouchlinkInitiate
            // 
            this.buttonZllTouchlinkInitiate.Location = new System.Drawing.Point(4, 4);
            this.buttonZllTouchlinkInitiate.Name = "buttonZllTouchlinkInitiate";
            this.buttonZllTouchlinkInitiate.Size = new System.Drawing.Size(80, 22);
            this.buttonZllTouchlinkInitiate.TabIndex = 0;
            this.buttonZllTouchlinkInitiate.Text = "Initiate";
            this.buttonZllTouchlinkInitiate.UseVisualStyleBackColor = true;
            this.buttonZllTouchlinkInitiate.Click += new System.EventHandler(this.buttonZllTouchlinkInitiate_Click);
            // 
            // tabPage10
            // 
            this.tabPage10.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage10.Controls.Add(this.comboBoxZllOnOffEffectID);
            this.tabPage10.Controls.Add(this.textBoxZllOnOffEffectsGradient);
            this.tabPage10.Controls.Add(this.textBoxZllOnOffEffectsDstEp);
            this.tabPage10.Controls.Add(this.textBoxZllOnOffEffectsSrcEp);
            this.tabPage10.Controls.Add(this.textBoxZllOnOffEffectsAddr);
            this.tabPage10.Controls.Add(this.buttonZllOnOffEffects);
            this.tabPage10.Location = new System.Drawing.Point(4, 22);
            this.tabPage10.Name = "tabPage10";
            this.tabPage10.Size = new System.Drawing.Size(1351, 416);
            this.tabPage10.TabIndex = 10;
            this.tabPage10.Text = "ZLL On/Off Cluster";
            this.tabPage10.Click += new System.EventHandler(this.tabPage10_Click);
            // 
            // comboBoxZllOnOffEffectID
            // 
            this.comboBoxZllOnOffEffectID.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxZllOnOffEffectID.FormattingEnabled = true;
            this.comboBoxZllOnOffEffectID.Location = new System.Drawing.Point(441, 6);
            this.comboBoxZllOnOffEffectID.Name = "comboBoxZllOnOffEffectID";
            this.comboBoxZllOnOffEffectID.Size = new System.Drawing.Size(129, 21);
            this.comboBoxZllOnOffEffectID.TabIndex = 4;
            this.comboBoxZllOnOffEffectID.MouseLeave += new System.EventHandler(this.comboBoxZllOnOffEffectID_MouseLeave);
            this.comboBoxZllOnOffEffectID.MouseHover += new System.EventHandler(this.comboBoxZllOnOffEffectID_MouseHover);
            // 
            // textBoxZllOnOffEffectsGradient
            // 
            this.textBoxZllOnOffEffectsGradient.Location = new System.Drawing.Point(576, 6);
            this.textBoxZllOnOffEffectsGradient.Name = "textBoxZllOnOffEffectsGradient";
            this.textBoxZllOnOffEffectsGradient.Size = new System.Drawing.Size(106, 20);
            this.textBoxZllOnOffEffectsGradient.TabIndex = 5;
            this.textBoxZllOnOffEffectsGradient.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxZllOnOffEffectsGradient_MouseClick);
            this.textBoxZllOnOffEffectsGradient.Leave += new System.EventHandler(this.textBoxZllOnOffEffectsGradient_Leave);
            this.textBoxZllOnOffEffectsGradient.MouseLeave += new System.EventHandler(this.textBoxZllOnOffEffectsGradient_MouseLeave);
            this.textBoxZllOnOffEffectsGradient.MouseHover += new System.EventHandler(this.textBoxZllOnOffEffectsGradient_MouseHover);
            // 
            // textBoxZllOnOffEffectsDstEp
            // 
            this.textBoxZllOnOffEffectsDstEp.Location = new System.Drawing.Point(327, 6);
            this.textBoxZllOnOffEffectsDstEp.Name = "textBoxZllOnOffEffectsDstEp";
            this.textBoxZllOnOffEffectsDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxZllOnOffEffectsDstEp.TabIndex = 3;
            this.textBoxZllOnOffEffectsDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxZllOnOffEffectsDstEp_MouseClick);
            this.textBoxZllOnOffEffectsDstEp.Leave += new System.EventHandler(this.textBoxZllOnOffEffectsDstEp_Leave);
            this.textBoxZllOnOffEffectsDstEp.MouseHover += new System.EventHandler(this.textBoxZllOnOffEffectsDstEp_MouseHover);
            // 
            // textBoxZllOnOffEffectsSrcEp
            // 
            this.textBoxZllOnOffEffectsSrcEp.Location = new System.Drawing.Point(214, 6);
            this.textBoxZllOnOffEffectsSrcEp.Name = "textBoxZllOnOffEffectsSrcEp";
            this.textBoxZllOnOffEffectsSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxZllOnOffEffectsSrcEp.TabIndex = 2;
            this.textBoxZllOnOffEffectsSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxZllOnOffEffectsSrcEp_MouseClick);
            this.textBoxZllOnOffEffectsSrcEp.Leave += new System.EventHandler(this.textBoxZllOnOffEffectsSrcEp_Leave);
            this.textBoxZllOnOffEffectsSrcEp.MouseLeave += new System.EventHandler(this.textBoxZllOnOffEffectsSrcEp_MouseLeave);
            this.textBoxZllOnOffEffectsSrcEp.MouseHover += new System.EventHandler(this.textBoxZllOnOffEffectsSrcEp_MouseHover);
            // 
            // textBoxZllOnOffEffectsAddr
            // 
            this.textBoxZllOnOffEffectsAddr.Location = new System.Drawing.Point(102, 6);
            this.textBoxZllOnOffEffectsAddr.Name = "textBoxZllOnOffEffectsAddr";
            this.textBoxZllOnOffEffectsAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxZllOnOffEffectsAddr.TabIndex = 1;
            this.textBoxZllOnOffEffectsAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxZllOnOffEffectsAddr_MouseClick);
            this.textBoxZllOnOffEffectsAddr.Leave += new System.EventHandler(this.textBoxZllOnOffEffectsAddr_Leave);
            this.textBoxZllOnOffEffectsAddr.MouseLeave += new System.EventHandler(this.textBoxZllOnOffEffectsAddr_MouseLeave);
            this.textBoxZllOnOffEffectsAddr.MouseHover += new System.EventHandler(this.textBoxZllOnOffEffectsAddr_MouseHover);
            // 
            // buttonZllOnOffEffects
            // 
            this.buttonZllOnOffEffects.Location = new System.Drawing.Point(4, 4);
            this.buttonZllOnOffEffects.Name = "buttonZllOnOffEffects";
            this.buttonZllOnOffEffects.Size = new System.Drawing.Size(90, 22);
            this.buttonZllOnOffEffects.TabIndex = 0;
            this.buttonZllOnOffEffects.Text = "On/Off Effects";
            this.buttonZllOnOffEffects.UseVisualStyleBackColor = true;
            this.buttonZllOnOffEffects.Click += new System.EventHandler(this.buttonZllOnOffEffects_Click);
            // 
            // tabPage11
            // 
            this.tabPage11.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage11.Controls.Add(this.textBoxZllMoveToHueHue);
            this.tabPage11.Controls.Add(this.textBoxZllMoveToHueTransTime);
            this.tabPage11.Controls.Add(this.textBoxZllMoveToHueDirection);
            this.tabPage11.Controls.Add(this.textBoxZllMoveToHueDstEp);
            this.tabPage11.Controls.Add(this.textBoxZllMoveToHueSrcEp);
            this.tabPage11.Controls.Add(this.textBoxZllMoveToHueAddr);
            this.tabPage11.Controls.Add(this.button8);
            this.tabPage11.Controls.Add(this.button7);
            this.tabPage11.Controls.Add(this.button6);
            this.tabPage11.Controls.Add(this.button5);
            this.tabPage11.Controls.Add(this.buttonZllMoveToHue);
            this.tabPage11.Location = new System.Drawing.Point(4, 22);
            this.tabPage11.Name = "tabPage11";
            this.tabPage11.Size = new System.Drawing.Size(1351, 416);
            this.tabPage11.TabIndex = 11;
            this.tabPage11.Text = "ZLL Color Cluster";
            this.tabPage11.Click += new System.EventHandler(this.tabPage11_Click);
            // 
            // textBoxZllMoveToHueHue
            // 
            this.textBoxZllMoveToHueHue.Location = new System.Drawing.Point(441, 6);
            this.textBoxZllMoveToHueHue.Name = "textBoxZllMoveToHueHue";
            this.textBoxZllMoveToHueHue.Size = new System.Drawing.Size(106, 20);
            this.textBoxZllMoveToHueHue.TabIndex = 4;
            this.textBoxZllMoveToHueHue.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxZllMoveToHueHue_MouseClick);
            this.textBoxZllMoveToHueHue.Leave += new System.EventHandler(this.textBoxZllMoveToHueHue_Leave);
            this.textBoxZllMoveToHueHue.MouseLeave += new System.EventHandler(this.textBoxZllMoveToHueHue_MouseLeave);
            this.textBoxZllMoveToHueHue.MouseHover += new System.EventHandler(this.textBoxZllMoveToHueHue_MouseHover);
            // 
            // textBoxZllMoveToHueTransTime
            // 
            this.textBoxZllMoveToHueTransTime.Location = new System.Drawing.Point(666, 6);
            this.textBoxZllMoveToHueTransTime.Name = "textBoxZllMoveToHueTransTime";
            this.textBoxZllMoveToHueTransTime.Size = new System.Drawing.Size(106, 20);
            this.textBoxZllMoveToHueTransTime.TabIndex = 6;
            this.textBoxZllMoveToHueTransTime.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxZllMoveToHueTransTime_MouseClick);
            this.textBoxZllMoveToHueTransTime.Leave += new System.EventHandler(this.textBoxZllMoveToHueTransTime_Leave);
            this.textBoxZllMoveToHueTransTime.MouseLeave += new System.EventHandler(this.textBoxZllMoveToHueTransTime_MouseLeave);
            this.textBoxZllMoveToHueTransTime.MouseHover += new System.EventHandler(this.textBoxZllMoveToHueTransTime_MouseHover);
            // 
            // textBoxZllMoveToHueDirection
            // 
            this.textBoxZllMoveToHueDirection.Location = new System.Drawing.Point(554, 6);
            this.textBoxZllMoveToHueDirection.Name = "textBoxZllMoveToHueDirection";
            this.textBoxZllMoveToHueDirection.Size = new System.Drawing.Size(106, 20);
            this.textBoxZllMoveToHueDirection.TabIndex = 5;
            this.textBoxZllMoveToHueDirection.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxZllMoveToHueDirection_MouseClick);
            this.textBoxZllMoveToHueDirection.Leave += new System.EventHandler(this.textBoxZllMoveToHueDirection_Leave);
            this.textBoxZllMoveToHueDirection.MouseLeave += new System.EventHandler(this.textBoxZllMoveToHueDirection_MouseLeave);
            this.textBoxZllMoveToHueDirection.MouseHover += new System.EventHandler(this.textBoxZllMoveToHueDirection_MouseHover);
            // 
            // textBoxZllMoveToHueDstEp
            // 
            this.textBoxZllMoveToHueDstEp.Location = new System.Drawing.Point(327, 6);
            this.textBoxZllMoveToHueDstEp.Name = "textBoxZllMoveToHueDstEp";
            this.textBoxZllMoveToHueDstEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxZllMoveToHueDstEp.TabIndex = 3;
            this.textBoxZllMoveToHueDstEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxZllMoveToHueDstEp_MouseClick);
            this.textBoxZllMoveToHueDstEp.Leave += new System.EventHandler(this.textBoxZllMoveToHueDstEp_Leave);
            this.textBoxZllMoveToHueDstEp.MouseLeave += new System.EventHandler(this.textBoxZllMoveToHueDstEp_MouseLeave);
            this.textBoxZllMoveToHueDstEp.MouseHover += new System.EventHandler(this.textBoxZllMoveToHueDstEp_MouseHover);
            // 
            // textBoxZllMoveToHueSrcEp
            // 
            this.textBoxZllMoveToHueSrcEp.Location = new System.Drawing.Point(214, 6);
            this.textBoxZllMoveToHueSrcEp.Name = "textBoxZllMoveToHueSrcEp";
            this.textBoxZllMoveToHueSrcEp.Size = new System.Drawing.Size(106, 20);
            this.textBoxZllMoveToHueSrcEp.TabIndex = 2;
            this.textBoxZllMoveToHueSrcEp.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxZllMoveToHueSrcEp_MouseClick);
            this.textBoxZllMoveToHueSrcEp.Leave += new System.EventHandler(this.textBoxZllMoveToHueSrcEp_Leave);
            this.textBoxZllMoveToHueSrcEp.MouseLeave += new System.EventHandler(this.textBoxZllMoveToHueSrcEp_MouseLeave);
            this.textBoxZllMoveToHueSrcEp.MouseHover += new System.EventHandler(this.textBoxZllMoveToHueSrcEp_MouseHover);
            // 
            // textBoxZllMoveToHueAddr
            // 
            this.textBoxZllMoveToHueAddr.Location = new System.Drawing.Point(102, 6);
            this.textBoxZllMoveToHueAddr.Name = "textBoxZllMoveToHueAddr";
            this.textBoxZllMoveToHueAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxZllMoveToHueAddr.TabIndex = 1;
            this.textBoxZllMoveToHueAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxZllMoveToHueAddr_MouseClick);
            this.textBoxZllMoveToHueAddr.Leave += new System.EventHandler(this.textBoxZllMoveToHueAddr_Leave);
            this.textBoxZllMoveToHueAddr.MouseLeave += new System.EventHandler(this.textBoxZllMoveToHueAddr_MouseLeave);
            this.textBoxZllMoveToHueAddr.MouseHover += new System.EventHandler(this.textBoxZllMoveToHueAddr_MouseHover);
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(4, 122);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(90, 22);
            this.button8.TabIndex = 0;
            this.button8.Text = "Color Loop";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Visible = false;
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(4, 93);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(90, 22);
            this.button7.TabIndex = 0;
            this.button7.Text = "Hue and Sat";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Visible = false;
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(4, 63);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(90, 22);
            this.button6.TabIndex = 0;
            this.button6.Text = "Step Hue";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Visible = false;
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(4, 34);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(90, 22);
            this.button5.TabIndex = 0;
            this.button5.Text = "Move Hue";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Visible = false;
            // 
            // buttonZllMoveToHue
            // 
            this.buttonZllMoveToHue.Location = new System.Drawing.Point(4, 4);
            this.buttonZllMoveToHue.Name = "buttonZllMoveToHue";
            this.buttonZllMoveToHue.Size = new System.Drawing.Size(90, 22);
            this.buttonZllMoveToHue.TabIndex = 0;
            this.buttonZllMoveToHue.Text = "Move to Hue";
            this.buttonZllMoveToHue.UseVisualStyleBackColor = true;
            this.buttonZllMoveToHue.Click += new System.EventHandler(this.buttonZllMoveToHue_Click);
            // 
            // tabPage14
            // 
            this.tabPage14.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPage14.Controls.Add(this.textBoxOtaFileStackVer);
            this.tabPage14.Controls.Add(this.label15);
            this.tabPage14.Controls.Add(this.textBoxOtaFileHeaderVer);
            this.tabPage14.Controls.Add(this.label14);
            this.tabPage14.Controls.Add(this.textBoxOtaFileHeaderLen);
            this.tabPage14.Controls.Add(this.label13);
            this.tabPage14.Controls.Add(this.textBoxOtaFileHeaderFCTL);
            this.tabPage14.Controls.Add(this.label12);
            this.tabPage14.Controls.Add(this.textBoxOtaFileID);
            this.tabPage14.Controls.Add(this.label11);
            this.tabPage14.Controls.Add(this.textBoxOtaFileHeaderStr);
            this.tabPage14.Controls.Add(this.label10);
            this.tabPage14.Controls.Add(this.textBoxOTASetWaitForDataParamsRequestBlockDelay);
            this.tabPage14.Controls.Add(this.textBoxOTASetWaitForDataParamsRequestTime);
            this.tabPage14.Controls.Add(this.textBoxOTASetWaitForDataParamsCurrentTime);
            this.tabPage14.Controls.Add(this.textBoxOTASetWaitForDataParamsSrcEP);
            this.tabPage14.Controls.Add(this.textBoxOTASetWaitForDataParamsTargetAddr);
            this.tabPage14.Controls.Add(this.buttonOTASetWaitForDataParams);
            this.tabPage14.Controls.Add(this.textBoxOtaFileOffset);
            this.tabPage14.Controls.Add(this.label9);
            this.tabPage14.Controls.Add(this.label8);
            this.tabPage14.Controls.Add(this.textBoxOtaDownloadStatus);
            this.tabPage14.Controls.Add(this.label7);
            this.tabPage14.Controls.Add(this.progressBarOtaDownloadProgress);
            this.tabPage14.Controls.Add(this.textBoxOTAImageNotifyJitter);
            this.tabPage14.Controls.Add(this.textBoxOTAImageNotifyManuID);
            this.tabPage14.Controls.Add(this.textBoxOTAImageNotifyImageType);
            this.tabPage14.Controls.Add(this.textBoxOTAImageNotifyFileVersion);
            this.tabPage14.Controls.Add(this.comboBoxOTAImageNotifyType);
            this.tabPage14.Controls.Add(this.textBoxOTAImageNotifyDstEP);
            this.tabPage14.Controls.Add(this.textBoxOTAImageNotifySrcEP);
            this.tabPage14.Controls.Add(this.textBoxOTAImageNotifyTargetAddr);
            this.tabPage14.Controls.Add(this.comboBoxOTAImageNotifyAddrMode);
            this.tabPage14.Controls.Add(this.buttonOTAImageNotify);
            this.tabPage14.Controls.Add(this.textBoxOtaFileSize);
            this.tabPage14.Controls.Add(this.label6);
            this.tabPage14.Controls.Add(this.textBoxOtaFileVersion);
            this.tabPage14.Controls.Add(this.label5);
            this.tabPage14.Controls.Add(this.textBoxOtaFileImageType);
            this.tabPage14.Controls.Add(this.label2);
            this.tabPage14.Controls.Add(this.label1);
            this.tabPage14.Controls.Add(this.textBoxOtaFileManuCode);
            this.tabPage14.Controls.Add(this.buttonOTALoadNewImage);
            this.tabPage14.Location = new System.Drawing.Point(4, 22);
            this.tabPage14.Name = "tabPage14";
            this.tabPage14.Size = new System.Drawing.Size(1351, 416);
            this.tabPage14.TabIndex = 14;
            this.tabPage14.Text = "OTA Cluster";
            this.tabPage14.Click += new System.EventHandler(this.tabPage14_Click);
            // 
            // textBoxOtaFileStackVer
            // 
            this.textBoxOtaFileStackVer.Location = new System.Drawing.Point(156, 33);
            this.textBoxOtaFileStackVer.Name = "textBoxOtaFileStackVer";
            this.textBoxOtaFileStackVer.ReadOnly = true;
            this.textBoxOtaFileStackVer.Size = new System.Drawing.Size(91, 20);
            this.textBoxOtaFileStackVer.TabIndex = 8;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(94, 35);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(54, 13);
            this.label15.TabIndex = 0;
            this.label15.Text = "Stack Ver";
            // 
            // textBoxOtaFileHeaderVer
            // 
            this.textBoxOtaFileHeaderVer.Location = new System.Drawing.Point(290, 7);
            this.textBoxOtaFileHeaderVer.Name = "textBoxOtaFileHeaderVer";
            this.textBoxOtaFileHeaderVer.ReadOnly = true;
            this.textBoxOtaFileHeaderVer.Size = new System.Drawing.Size(74, 20);
            this.textBoxOtaFileHeaderVer.TabIndex = 2;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(218, 10);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(61, 13);
            this.label14.TabIndex = 0;
            this.label14.Text = "Header Ver";
            // 
            // textBoxOtaFileHeaderLen
            // 
            this.textBoxOtaFileHeaderLen.Location = new System.Drawing.Point(442, 7);
            this.textBoxOtaFileHeaderLen.Name = "textBoxOtaFileHeaderLen";
            this.textBoxOtaFileHeaderLen.ReadOnly = true;
            this.textBoxOtaFileHeaderLen.Size = new System.Drawing.Size(74, 20);
            this.textBoxOtaFileHeaderLen.TabIndex = 3;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(369, 10);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(63, 13);
            this.label13.TabIndex = 0;
            this.label13.Text = "Header Len";
            // 
            // textBoxOtaFileHeaderFCTL
            // 
            this.textBoxOtaFileHeaderFCTL.Location = new System.Drawing.Point(604, 7);
            this.textBoxOtaFileHeaderFCTL.Name = "textBoxOtaFileHeaderFCTL";
            this.textBoxOtaFileHeaderFCTL.ReadOnly = true;
            this.textBoxOtaFileHeaderFCTL.Size = new System.Drawing.Size(74, 20);
            this.textBoxOtaFileHeaderFCTL.TabIndex = 4;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(522, 10);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(71, 13);
            this.label12.TabIndex = 0;
            this.label12.Text = "Header FCTL";
            // 
            // textBoxOtaFileID
            // 
            this.textBoxOtaFileID.Location = new System.Drawing.Point(138, 7);
            this.textBoxOtaFileID.Name = "textBoxOtaFileID";
            this.textBoxOtaFileID.ReadOnly = true;
            this.textBoxOtaFileID.Size = new System.Drawing.Size(74, 20);
            this.textBoxOtaFileID.TabIndex = 1;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(94, 10);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(37, 13);
            this.label11.TabIndex = 0;
            this.label11.Text = "File ID";
            // 
            // textBoxOtaFileHeaderStr
            // 
            this.textBoxOtaFileHeaderStr.Location = new System.Drawing.Point(438, 33);
            this.textBoxOtaFileHeaderStr.Name = "textBoxOtaFileHeaderStr";
            this.textBoxOtaFileHeaderStr.ReadOnly = true;
            this.textBoxOtaFileHeaderStr.Size = new System.Drawing.Size(222, 20);
            this.textBoxOtaFileHeaderStr.TabIndex = 10;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(369, 35);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(58, 13);
            this.label10.TabIndex = 0;
            this.label10.Text = "Header Str";
            // 
            // textBoxOTASetWaitForDataParamsRequestBlockDelay
            // 
            this.textBoxOTASetWaitForDataParamsRequestBlockDelay.Location = new System.Drawing.Point(579, 88);
            this.textBoxOTASetWaitForDataParamsRequestBlockDelay.Name = "textBoxOTASetWaitForDataParamsRequestBlockDelay";
            this.textBoxOTASetWaitForDataParamsRequestBlockDelay.Size = new System.Drawing.Size(122, 20);
            this.textBoxOTASetWaitForDataParamsRequestBlockDelay.TabIndex = 26;
            this.textBoxOTASetWaitForDataParamsRequestBlockDelay.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOTASetWaitForDataParamsRequestBlockDelay_MouseClick);
            this.textBoxOTASetWaitForDataParamsRequestBlockDelay.Leave += new System.EventHandler(this.textBoxOTASetWaitForDataParamsRequestBlockDelay_Leave);
            this.textBoxOTASetWaitForDataParamsRequestBlockDelay.MouseLeave += new System.EventHandler(this.textBoxOTASetWaitForDataParamsRequestBlockDelay_MouseLeave);
            this.textBoxOTASetWaitForDataParamsRequestBlockDelay.MouseHover += new System.EventHandler(this.textBoxOTASetWaitForDataParamsRequestBlockDelay_MouseHover);
            // 
            // textBoxOTASetWaitForDataParamsRequestTime
            // 
            this.textBoxOTASetWaitForDataParamsRequestTime.Location = new System.Drawing.Point(450, 88);
            this.textBoxOTASetWaitForDataParamsRequestTime.Name = "textBoxOTASetWaitForDataParamsRequestTime";
            this.textBoxOTASetWaitForDataParamsRequestTime.Size = new System.Drawing.Size(122, 20);
            this.textBoxOTASetWaitForDataParamsRequestTime.TabIndex = 25;
            this.textBoxOTASetWaitForDataParamsRequestTime.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOTASetWaitForDataParamsRequestTime_MouseClick);
            this.textBoxOTASetWaitForDataParamsRequestTime.Leave += new System.EventHandler(this.textBoxOTASetWaitForDataParamsRequestTime_Leave);
            this.textBoxOTASetWaitForDataParamsRequestTime.MouseLeave += new System.EventHandler(this.textBoxOTASetWaitForDataParamsRequestTime_MouseLeave);
            this.textBoxOTASetWaitForDataParamsRequestTime.MouseHover += new System.EventHandler(this.textBoxOTASetWaitForDataParamsRequestTime_MouseHover);
            // 
            // textBoxOTASetWaitForDataParamsCurrentTime
            // 
            this.textBoxOTASetWaitForDataParamsCurrentTime.Location = new System.Drawing.Point(321, 88);
            this.textBoxOTASetWaitForDataParamsCurrentTime.Name = "textBoxOTASetWaitForDataParamsCurrentTime";
            this.textBoxOTASetWaitForDataParamsCurrentTime.Size = new System.Drawing.Size(122, 20);
            this.textBoxOTASetWaitForDataParamsCurrentTime.TabIndex = 24;
            this.textBoxOTASetWaitForDataParamsCurrentTime.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOTASetWaitForDataParamsCurrentTime_MouseClick);
            this.textBoxOTASetWaitForDataParamsCurrentTime.Leave += new System.EventHandler(this.textBoxOTASetWaitForDataParamsCurrentTime_Leave);
            this.textBoxOTASetWaitForDataParamsCurrentTime.MouseLeave += new System.EventHandler(this.textBoxOTASetWaitForDataParamsCurrentTime_MouseLeave);
            this.textBoxOTASetWaitForDataParamsCurrentTime.MouseHover += new System.EventHandler(this.textBoxOTASetWaitForDataParamsCurrentTime_MouseHover);
            // 
            // textBoxOTASetWaitForDataParamsSrcEP
            // 
            this.textBoxOTASetWaitForDataParamsSrcEP.Location = new System.Drawing.Point(209, 88);
            this.textBoxOTASetWaitForDataParamsSrcEP.Name = "textBoxOTASetWaitForDataParamsSrcEP";
            this.textBoxOTASetWaitForDataParamsSrcEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxOTASetWaitForDataParamsSrcEP.TabIndex = 23;
            this.textBoxOTASetWaitForDataParamsSrcEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOTASetWaitForDataParamsSrcEP_MouseClick);
            this.textBoxOTASetWaitForDataParamsSrcEP.Leave += new System.EventHandler(this.textBoxOTASetWaitForDataParamsSrcEP_Leave);
            this.textBoxOTASetWaitForDataParamsSrcEP.MouseLeave += new System.EventHandler(this.textBoxOTASetWaitForDataParamsSrcEP_MouseLeave);
            this.textBoxOTASetWaitForDataParamsSrcEP.MouseHover += new System.EventHandler(this.textBoxOTASetWaitForDataParamsSrcEP_MouseHover);
            // 
            // textBoxOTASetWaitForDataParamsTargetAddr
            // 
            this.textBoxOTASetWaitForDataParamsTargetAddr.Location = new System.Drawing.Point(97, 88);
            this.textBoxOTASetWaitForDataParamsTargetAddr.Name = "textBoxOTASetWaitForDataParamsTargetAddr";
            this.textBoxOTASetWaitForDataParamsTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxOTASetWaitForDataParamsTargetAddr.TabIndex = 22;
            this.textBoxOTASetWaitForDataParamsTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOTASetWaitForDataParamsTargetAddr_MouseClick);
            this.textBoxOTASetWaitForDataParamsTargetAddr.Leave += new System.EventHandler(this.textBoxOTASetWaitForDataParamsTargetAddr_Leave);
            this.textBoxOTASetWaitForDataParamsTargetAddr.MouseLeave += new System.EventHandler(this.textBoxOTASetWaitForDataParamsTargetAddr_MouseLeave);
            this.textBoxOTASetWaitForDataParamsTargetAddr.MouseHover += new System.EventHandler(this.textBoxOTASetWaitForDataParamsTargetAddr_MouseHover);
            // 
            // buttonOTASetWaitForDataParams
            // 
            this.buttonOTASetWaitForDataParams.Location = new System.Drawing.Point(4, 84);
            this.buttonOTASetWaitForDataParams.Name = "buttonOTASetWaitForDataParams";
            this.buttonOTASetWaitForDataParams.Size = new System.Drawing.Size(86, 26);
            this.buttonOTASetWaitForDataParams.TabIndex = 21;
            this.buttonOTASetWaitForDataParams.Text = "WaitParams";
            this.buttonOTASetWaitForDataParams.UseVisualStyleBackColor = true;
            this.buttonOTASetWaitForDataParams.Click += new System.EventHandler(this.buttonOTASetWaitForDataParams_Click);
            // 
            // textBoxOtaFileOffset
            // 
            this.textBoxOtaFileOffset.Location = new System.Drawing.Point(759, 116);
            this.textBoxOtaFileOffset.Name = "textBoxOtaFileOffset";
            this.textBoxOtaFileOffset.ReadOnly = true;
            this.textBoxOtaFileOffset.Size = new System.Drawing.Size(103, 20);
            this.textBoxOtaFileOffset.TabIndex = 28;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(695, 119);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(54, 13);
            this.label9.TabIndex = 0;
            this.label9.Text = "File Offset";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(209, 119);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(48, 13);
            this.label8.TabIndex = 0;
            this.label8.Text = "Progress";
            // 
            // textBoxOtaDownloadStatus
            // 
            this.textBoxOtaDownloadStatus.Location = new System.Drawing.Point(97, 116);
            this.textBoxOtaDownloadStatus.Name = "textBoxOtaDownloadStatus";
            this.textBoxOtaDownloadStatus.ReadOnly = true;
            this.textBoxOtaDownloadStatus.Size = new System.Drawing.Size(106, 20);
            this.textBoxOtaDownloadStatus.TabIndex = 27;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(4, 119);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(88, 13);
            this.label7.TabIndex = 0;
            this.label7.Text = "Download Status";
            this.label7.Click += new System.EventHandler(this.label7_Click);
            // 
            // progressBarOtaDownloadProgress
            // 
            this.progressBarOtaDownloadProgress.Location = new System.Drawing.Point(266, 114);
            this.progressBarOtaDownloadProgress.Maximum = 1000;
            this.progressBarOtaDownloadProgress.Name = "progressBarOtaDownloadProgress";
            this.progressBarOtaDownloadProgress.Size = new System.Drawing.Size(422, 22);
            this.progressBarOtaDownloadProgress.TabIndex = 0;
            // 
            // textBoxOTAImageNotifyJitter
            // 
            this.textBoxOTAImageNotifyJitter.Location = new System.Drawing.Point(1060, 56);
            this.textBoxOTAImageNotifyJitter.Name = "textBoxOTAImageNotifyJitter";
            this.textBoxOTAImageNotifyJitter.Size = new System.Drawing.Size(117, 20);
            this.textBoxOTAImageNotifyJitter.TabIndex = 20;
            this.textBoxOTAImageNotifyJitter.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOTAImageNotifyJitter_MouseClick);
            this.textBoxOTAImageNotifyJitter.Leave += new System.EventHandler(this.textBoxOTAImageNotifyJitter_Leave);
            this.textBoxOTAImageNotifyJitter.MouseLeave += new System.EventHandler(this.textBoxOTAImageNotifyJitter_MouseLeave);
            this.textBoxOTAImageNotifyJitter.MouseHover += new System.EventHandler(this.textBoxOTAImageNotifyJitter_MouseHover);
            // 
            // textBoxOTAImageNotifyManuID
            // 
            this.textBoxOTAImageNotifyManuID.Location = new System.Drawing.Point(943, 56);
            this.textBoxOTAImageNotifyManuID.Name = "textBoxOTAImageNotifyManuID";
            this.textBoxOTAImageNotifyManuID.Size = new System.Drawing.Size(112, 20);
            this.textBoxOTAImageNotifyManuID.TabIndex = 19;
            this.textBoxOTAImageNotifyManuID.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOTAImageNotifyManuID_MouseClick);
            this.textBoxOTAImageNotifyManuID.Leave += new System.EventHandler(this.textBoxOTAImageNotifyManuID_Leave);
            this.textBoxOTAImageNotifyManuID.MouseLeave += new System.EventHandler(this.textBoxOTAImageNotifyManuID_MouseLeave);
            this.textBoxOTAImageNotifyManuID.MouseHover += new System.EventHandler(this.textBoxOTAImageNotifyManuID_MouseHover);
            // 
            // textBoxOTAImageNotifyImageType
            // 
            this.textBoxOTAImageNotifyImageType.Location = new System.Drawing.Point(809, 56);
            this.textBoxOTAImageNotifyImageType.Name = "textBoxOTAImageNotifyImageType";
            this.textBoxOTAImageNotifyImageType.Size = new System.Drawing.Size(128, 20);
            this.textBoxOTAImageNotifyImageType.TabIndex = 18;
            this.textBoxOTAImageNotifyImageType.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOTAImageNotifyImageType_MouseClick);
            this.textBoxOTAImageNotifyImageType.Leave += new System.EventHandler(this.textBoxOTAImageNotifyImageType_Leave);
            this.textBoxOTAImageNotifyImageType.MouseLeave += new System.EventHandler(this.textBoxOTAImageNotifyImageType_MouseLeave);
            this.textBoxOTAImageNotifyImageType.MouseHover += new System.EventHandler(this.textBoxOTAImageNotifyImageType_MouseHover);
            // 
            // textBoxOTAImageNotifyFileVersion
            // 
            this.textBoxOTAImageNotifyFileVersion.Location = new System.Drawing.Point(695, 56);
            this.textBoxOTAImageNotifyFileVersion.Name = "textBoxOTAImageNotifyFileVersion";
            this.textBoxOTAImageNotifyFileVersion.Size = new System.Drawing.Size(106, 20);
            this.textBoxOTAImageNotifyFileVersion.TabIndex = 17;
            this.textBoxOTAImageNotifyFileVersion.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOTAImageNotifyFileVersion_MouseClick);
            this.textBoxOTAImageNotifyFileVersion.Leave += new System.EventHandler(this.textBoxOTAImageNotifyFileVersion_Leave);
            this.textBoxOTAImageNotifyFileVersion.MouseLeave += new System.EventHandler(this.textBoxOTAImageNotifyFileVersion_MouseLeave);
            this.textBoxOTAImageNotifyFileVersion.MouseHover += new System.EventHandler(this.textBoxOTAImageNotifyFileVersion_MouseHover);
            // 
            // comboBoxOTAImageNotifyType
            // 
            this.comboBoxOTAImageNotifyType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxOTAImageNotifyType.FormattingEnabled = true;
            this.comboBoxOTAImageNotifyType.Location = new System.Drawing.Point(550, 56);
            this.comboBoxOTAImageNotifyType.Name = "comboBoxOTAImageNotifyType";
            this.comboBoxOTAImageNotifyType.Size = new System.Drawing.Size(138, 21);
            this.comboBoxOTAImageNotifyType.TabIndex = 16;
            this.comboBoxOTAImageNotifyType.MouseLeave += new System.EventHandler(this.comboBoxOTAImageNotifyType_MouseLeave);
            this.comboBoxOTAImageNotifyType.MouseHover += new System.EventHandler(this.comboBoxOTAImageNotifyType_MouseHover);
            // 
            // textBoxOTAImageNotifyDstEP
            // 
            this.textBoxOTAImageNotifyDstEP.Location = new System.Drawing.Point(438, 57);
            this.textBoxOTAImageNotifyDstEP.Name = "textBoxOTAImageNotifyDstEP";
            this.textBoxOTAImageNotifyDstEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxOTAImageNotifyDstEP.TabIndex = 15;
            this.textBoxOTAImageNotifyDstEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOTAImageNotifyDstEP_MouseClick);
            this.textBoxOTAImageNotifyDstEP.Leave += new System.EventHandler(this.textBoxOTAImageNotifyDstEP_Leave);
            this.textBoxOTAImageNotifyDstEP.MouseLeave += new System.EventHandler(this.textBoxOTAImageNotifyDstEP_MouseLeave);
            this.textBoxOTAImageNotifyDstEP.MouseHover += new System.EventHandler(this.textBoxOTAImageNotifyDstEP_MouseHover);
            // 
            // textBoxOTAImageNotifySrcEP
            // 
            this.textBoxOTAImageNotifySrcEP.Location = new System.Drawing.Point(323, 57);
            this.textBoxOTAImageNotifySrcEP.Name = "textBoxOTAImageNotifySrcEP";
            this.textBoxOTAImageNotifySrcEP.Size = new System.Drawing.Size(106, 20);
            this.textBoxOTAImageNotifySrcEP.TabIndex = 14;
            this.textBoxOTAImageNotifySrcEP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOTAImageNotifySrcEP_MouseClick);
            this.textBoxOTAImageNotifySrcEP.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            this.textBoxOTAImageNotifySrcEP.Leave += new System.EventHandler(this.textBoxOTAImageNotifySrcEP_Leave);
            this.textBoxOTAImageNotifySrcEP.MouseLeave += new System.EventHandler(this.textBoxOTAImageNotifySrcEP_MouseLeave);
            this.textBoxOTAImageNotifySrcEP.MouseHover += new System.EventHandler(this.textBoxOTAImageNotifySrcEP_MouseHover);
            // 
            // textBoxOTAImageNotifyTargetAddr
            // 
            this.textBoxOTAImageNotifyTargetAddr.Location = new System.Drawing.Point(209, 57);
            this.textBoxOTAImageNotifyTargetAddr.Name = "textBoxOTAImageNotifyTargetAddr";
            this.textBoxOTAImageNotifyTargetAddr.Size = new System.Drawing.Size(106, 20);
            this.textBoxOTAImageNotifyTargetAddr.TabIndex = 13;
            this.textBoxOTAImageNotifyTargetAddr.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxOTAImageNotifyTargetAddr_MouseClick);
            this.textBoxOTAImageNotifyTargetAddr.Leave += new System.EventHandler(this.textBoxOTAImageNotifyTargetAddr_Leave);
            this.textBoxOTAImageNotifyTargetAddr.MouseLeave += new System.EventHandler(this.textBoxOTAImageNotifyTargetAddr_MouseLeave);
            this.textBoxOTAImageNotifyTargetAddr.MouseHover += new System.EventHandler(this.textBoxOTAImageNotifyTargetAddr_MouseHover);
            // 
            // comboBoxOTAImageNotifyAddrMode
            // 
            this.comboBoxOTAImageNotifyAddrMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxOTAImageNotifyAddrMode.FormattingEnabled = true;
            this.comboBoxOTAImageNotifyAddrMode.Location = new System.Drawing.Point(97, 57);
            this.comboBoxOTAImageNotifyAddrMode.Name = "comboBoxOTAImageNotifyAddrMode";
            this.comboBoxOTAImageNotifyAddrMode.Size = new System.Drawing.Size(106, 21);
            this.comboBoxOTAImageNotifyAddrMode.TabIndex = 12;
            this.comboBoxOTAImageNotifyAddrMode.MouseLeave += new System.EventHandler(this.comboBoxOTAImageNotifyAddrMode_MouseLeave);
            this.comboBoxOTAImageNotifyAddrMode.MouseHover += new System.EventHandler(this.comboBoxOTAImageNotifyAddrMode_MouseHover);
            // 
            // buttonOTAImageNotify
            // 
            this.buttonOTAImageNotify.Location = new System.Drawing.Point(4, 53);
            this.buttonOTAImageNotify.Name = "buttonOTAImageNotify";
            this.buttonOTAImageNotify.Size = new System.Drawing.Size(86, 26);
            this.buttonOTAImageNotify.TabIndex = 11;
            this.buttonOTAImageNotify.Text = "Image Notify";
            this.buttonOTAImageNotify.UseVisualStyleBackColor = true;
            this.buttonOTAImageNotify.Click += new System.EventHandler(this.buttonOTAImageNotify_Click);
            // 
            // textBoxOtaFileSize
            // 
            this.textBoxOtaFileSize.Location = new System.Drawing.Point(290, 33);
            this.textBoxOtaFileSize.Name = "textBoxOtaFileSize";
            this.textBoxOtaFileSize.ReadOnly = true;
            this.textBoxOtaFileSize.Size = new System.Drawing.Size(74, 20);
            this.textBoxOtaFileSize.TabIndex = 9;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(255, 35);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(27, 13);
            this.label6.TabIndex = 0;
            this.label6.Text = "Size";
            // 
            // textBoxOtaFileVersion
            // 
            this.textBoxOtaFileVersion.Location = new System.Drawing.Point(1014, 7);
            this.textBoxOtaFileVersion.Name = "textBoxOtaFileVersion";
            this.textBoxOtaFileVersion.ReadOnly = true;
            this.textBoxOtaFileVersion.Size = new System.Drawing.Size(74, 20);
            this.textBoxOtaFileVersion.TabIndex = 7;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(943, 10);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(61, 13);
            this.label5.TabIndex = 0;
            this.label5.Text = "File Version";
            // 
            // textBoxOtaFileImageType
            // 
            this.textBoxOtaFileImageType.Location = new System.Drawing.Point(884, 7);
            this.textBoxOtaFileImageType.Name = "textBoxOtaFileImageType";
            this.textBoxOtaFileImageType.ReadOnly = true;
            this.textBoxOtaFileImageType.Size = new System.Drawing.Size(53, 20);
            this.textBoxOtaFileImageType.TabIndex = 6;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(812, 10);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(63, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Image Type";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(682, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Manu Code";
            // 
            // textBoxOtaFileManuCode
            // 
            this.textBoxOtaFileManuCode.Location = new System.Drawing.Point(753, 7);
            this.textBoxOtaFileManuCode.Name = "textBoxOtaFileManuCode";
            this.textBoxOtaFileManuCode.ReadOnly = true;
            this.textBoxOtaFileManuCode.Size = new System.Drawing.Size(53, 20);
            this.textBoxOtaFileManuCode.TabIndex = 5;
            // 
            // buttonOTALoadNewImage
            // 
            this.buttonOTALoadNewImage.Location = new System.Drawing.Point(3, 3);
            this.buttonOTALoadNewImage.Name = "buttonOTALoadNewImage";
            this.buttonOTALoadNewImage.Size = new System.Drawing.Size(86, 26);
            this.buttonOTALoadNewImage.TabIndex = 0;
            this.buttonOTALoadNewImage.Text = "Load Image";
            this.buttonOTALoadNewImage.UseVisualStyleBackColor = true;
            this.buttonOTALoadNewImage.Click += new System.EventHandler(this.buttonOTALoadNewImage_Click);
            // 
            // tabPagePollControl
            // 
            this.tabPagePollControl.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tabPagePollControl.Controls.Add(this.comboBoxFastPollEnable);
            this.tabPagePollControl.Controls.Add(this.textBoxFastPollExpiryTime);
            this.tabPagePollControl.Controls.Add(this.buttonSetCheckinRspData);
            this.tabPagePollControl.Location = new System.Drawing.Point(4, 22);
            this.tabPagePollControl.Name = "tabPagePollControl";
            this.tabPagePollControl.Size = new System.Drawing.Size(1351, 416);
            this.tabPagePollControl.TabIndex = 17;
            this.tabPagePollControl.Text = "Poll Control";
            this.tabPagePollControl.Click += new System.EventHandler(this.tabPagePollControl_Click);
            // 
            // comboBoxFastPollEnable
            // 
            this.comboBoxFastPollEnable.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxFastPollEnable.FormattingEnabled = true;
            this.comboBoxFastPollEnable.Items.AddRange(new object[] {
            "DISABLED",
            "ENABLED"});
            this.comboBoxFastPollEnable.Location = new System.Drawing.Point(102, 6);
            this.comboBoxFastPollEnable.Name = "comboBoxFastPollEnable";
            this.comboBoxFastPollEnable.Size = new System.Drawing.Size(106, 21);
            this.comboBoxFastPollEnable.TabIndex = 1;
            this.comboBoxFastPollEnable.MouseLeave += new System.EventHandler(this.comboBoxFastPollEnable_MouseLeave);
            this.comboBoxFastPollEnable.MouseHover += new System.EventHandler(this.comboBoxFastPollEnable_MouseHover);
            // 
            // textBoxFastPollExpiryTime
            // 
            this.textBoxFastPollExpiryTime.Location = new System.Drawing.Point(214, 7);
            this.textBoxFastPollExpiryTime.Name = "textBoxFastPollExpiryTime";
            this.textBoxFastPollExpiryTime.Size = new System.Drawing.Size(154, 20);
            this.textBoxFastPollExpiryTime.TabIndex = 2;
            this.textBoxFastPollExpiryTime.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textBoxFastPollExpiryTime_MouseClick);
            this.textBoxFastPollExpiryTime.Leave += new System.EventHandler(this.textBoxFastPollExpiryTime_Leave);
            this.textBoxFastPollExpiryTime.MouseLeave += new System.EventHandler(this.textBoxFastPollExpiryTime_MouseLeave);
            this.textBoxFastPollExpiryTime.MouseHover += new System.EventHandler(this.textBoxFastPollExpiryTime_MouseHover);
            // 
            // buttonSetCheckinRspData
            // 
            this.buttonSetCheckinRspData.Location = new System.Drawing.Point(3, 3);
            this.buttonSetCheckinRspData.Name = "buttonSetCheckinRspData";
            this.buttonSetCheckinRspData.Size = new System.Drawing.Size(92, 26);
            this.buttonSetCheckinRspData.TabIndex = 0;
            this.buttonSetCheckinRspData.Text = "Check-In Rsp";
            this.buttonSetCheckinRspData.UseVisualStyleBackColor = true;
            this.buttonSetCheckinRspData.Click += new System.EventHandler(this.buttonSetCheckinRspData_Click);
            // 
            // buttonMessageViewClear
            // 
            this.buttonMessageViewClear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonMessageViewClear.Location = new System.Drawing.Point(589, 6);
            this.buttonMessageViewClear.Name = "buttonMessageViewClear";
            this.buttonMessageViewClear.Size = new System.Drawing.Size(80, 22);
            this.buttonMessageViewClear.TabIndex = 92;
            this.buttonMessageViewClear.Text = "Clear";
            this.buttonMessageViewClear.UseVisualStyleBackColor = true;
            this.buttonMessageViewClear.Click += new System.EventHandler(this.buttonMessageViewClear_Click);
            // 
            // buttonClearRaw
            // 
            this.buttonClearRaw.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonClearRaw.Location = new System.Drawing.Point(599, 6);
            this.buttonClearRaw.Name = "buttonClearRaw";
            this.buttonClearRaw.Size = new System.Drawing.Size(80, 22);
            this.buttonClearRaw.TabIndex = 91;
            this.buttonClearRaw.Text = "Clear";
            this.buttonClearRaw.UseVisualStyleBackColor = true;
            this.buttonClearRaw.Click += new System.EventHandler(this.buttonClearRaw_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(3, 7);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(125, 13);
            this.label4.TabIndex = 18;
            this.label4.Text = "Received Message View";
            // 
            // richTextBoxMessageView
            // 
            this.richTextBoxMessageView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.richTextBoxMessageView.Location = new System.Drawing.Point(6, 30);
            this.richTextBoxMessageView.Name = "richTextBoxMessageView";
            this.richTextBoxMessageView.Size = new System.Drawing.Size(663, 238);
            this.richTextBoxMessageView.TabIndex = 17;
            this.richTextBoxMessageView.Text = "";
            this.richTextBoxMessageView.TextChanged += new System.EventHandler(this.richTextBoxMessageView_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 7);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(55, 13);
            this.label3.TabIndex = 16;
            this.label3.Text = "Raw Data";
            // 
            // richTextBoxCommandResponse
            // 
            this.richTextBoxCommandResponse.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.richTextBoxCommandResponse.Location = new System.Drawing.Point(6, 30);
            this.richTextBoxCommandResponse.Name = "richTextBoxCommandResponse";
            this.richTextBoxCommandResponse.Size = new System.Drawing.Size(673, 238);
            this.richTextBoxCommandResponse.TabIndex = 4;
            this.richTextBoxCommandResponse.Text = "";
            this.richTextBoxCommandResponse.TextChanged += new System.EventHandler(this.richTextBoxCommandResponse_TextChanged);
            // 
            // openOtaFileDialog
            // 
            this.openOtaFileDialog.FileName = "openFileDialog1";
            this.openOtaFileDialog.Filter = "OTA|*.ota";
            this.openOtaFileDialog.Title = "Select an OTA Image";
            // 
            // checkBoxDebug
            // 
            this.checkBoxDebug.AutoSize = true;
            this.checkBoxDebug.Location = new System.Drawing.Point(133, 6);
            this.checkBoxDebug.Margin = new System.Windows.Forms.Padding(2);
            this.checkBoxDebug.Name = "checkBoxDebug";
            this.checkBoxDebug.Size = new System.Drawing.Size(139, 17);
            this.checkBoxDebug.TabIndex = 93;
            this.checkBoxDebug.Text = "View Additional Debug?";
            this.checkBoxDebug.UseVisualStyleBackColor = true;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer1.Location = new System.Drawing.Point(13, 471);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.label3);
            this.splitContainer1.Panel1.Controls.Add(this.richTextBoxCommandResponse);
            this.splitContainer1.Panel1.Controls.Add(this.buttonClearRaw);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.label4);
            this.splitContainer1.Panel2.Controls.Add(this.checkBoxDebug);
            this.splitContainer1.Panel2.Controls.Add(this.buttonMessageViewClear);
            this.splitContainer1.Panel2.Controls.Add(this.richTextBoxMessageView);
            this.splitContainer1.Size = new System.Drawing.Size(1359, 269);
            this.splitContainer1.SplitterDistance = 682;
            this.splitContainer1.TabIndex = 94;
            // 
            // buttonNciCmd
            // 
            this.buttonNciCmd.Location = new System.Drawing.Point(752, 354);
            this.buttonNciCmd.Name = "buttonNciCmd";
            this.buttonNciCmd.Size = new System.Drawing.Size(80, 22);
            this.buttonNciCmd.TabIndex = 90;
            this.buttonNciCmd.Text = "NCI Cmd";
            this.buttonNciCmd.UseVisualStyleBackColor = true;
            this.buttonNciCmd.Click += new System.EventHandler(this.buttonNciCmd_Click);
            // 
            // comboBoxNciCmd
            // 
            this.comboBoxNciCmd.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxNciCmd.FormattingEnabled = true;
            this.comboBoxNciCmd.Location = new System.Drawing.Point(838, 354);
            this.comboBoxNciCmd.Name = "comboBoxNciCmd";
            this.comboBoxNciCmd.Size = new System.Drawing.Size(129, 21);
            this.comboBoxNciCmd.TabIndex = 91;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.ClientSize = new System.Drawing.Size(1385, 765);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "ZigBee Gateway User Interface";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.Form1_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPageDevice.ResumeLayout(false);
            this.tabPageDevice.PerformLayout();
            this.tabPage12.ResumeLayout(false);
            this.tabPage12.PerformLayout();
            this.AHIControl.ResumeLayout(false);
            this.AHIControl.PerformLayout();
            this.BasicClusterTab.ResumeLayout(false);
            this.BasicClusterTab.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.tabPage5.ResumeLayout(false);
            this.tabPage5.PerformLayout();
            this.tabPage6.ResumeLayout(false);
            this.tabPage6.PerformLayout();
            this.tabPage4.ResumeLayout(false);
            this.tabPage4.PerformLayout();
            this.tabPage7.ResumeLayout(false);
            this.tabPage7.PerformLayout();
            this.tabPage8.ResumeLayout(false);
            this.tabPage8.PerformLayout();
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage13.ResumeLayout(false);
            this.tabPage13.PerformLayout();
            this.tabPage15.ResumeLayout(false);
            this.tabPage15.PerformLayout();
            this.tabPage9.ResumeLayout(false);
            this.tabPage10.ResumeLayout(false);
            this.tabPage10.PerformLayout();
            this.tabPage11.ResumeLayout(false);
            this.tabPage11.PerformLayout();
            this.tabPage14.ResumeLayout(false);
            this.tabPage14.PerformLayout();
            this.tabPagePollControl.ResumeLayout(false);
            this.tabPagePollControl.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem settingsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openPortToolStripMenuItem;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusPort;
        private System.Windows.Forms.ToolStripStatusLabel toolStripPortSettings;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button buttonSetEPID;
        private System.Windows.Forms.Button buttonGetVersion;
        private System.Windows.Forms.Button buttonSetCMSK;
        private System.Windows.Forms.RichTextBox richTextBoxCommandResponse;
        private System.Windows.Forms.TextBox textBoxSetEPID;
        private System.Windows.Forms.TextBox textBoxSetCMSK;
        private System.Windows.Forms.Button buttonSetSecurity;
        private System.Windows.Forms.Button buttonSetDeviceType;
        private System.Windows.Forms.TextBox textBoxSetSecurityKeySeqNbr;
        private System.Windows.Forms.Button buttonErasePD;
        private System.Windows.Forms.Button buttonReset;
        private System.Windows.Forms.Button buttonBind;
        private System.Windows.Forms.Button buttonStartNWK;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.RichTextBox richTextBoxMessageView;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button buttonClearRaw;
        private System.Windows.Forms.Button buttonMessageViewClear;
        private System.Windows.Forms.ComboBox comboBoxSetType;
        private System.Windows.Forms.ComboBox comboBoxSetKeyState;
        private System.Windows.Forms.ComboBox comboBoxSetKeyType;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.Button buttonPermitJoin;
        private System.Windows.Forms.TextBox textBoxPermitJoinAddr;
        private System.Windows.Forms.TextBox textBoxPermitJoinInterval;
        private System.Windows.Forms.ComboBox comboBoxPermitJoinTCsignificance;
        private System.Windows.Forms.ComboBox comboBoxSecurityKey;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Button buttonIeeeAddrReq;
        private System.Windows.Forms.Button buttonNwkAddrReq;
        private System.Windows.Forms.TextBox textBoxNodeDescReq;
        private System.Windows.Forms.Button buttonNodeDescReq;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.Button buttonOnOff;
        private System.Windows.Forms.TextBox textBoxOnOffAddr;
        private System.Windows.Forms.TextBox textBoxOnOffSrcEndPoint;
        private System.Windows.Forms.TextBox textBoxOnOffDstEndPoint;
        private System.Windows.Forms.Button buttonMatchReq;
        private System.Windows.Forms.Button buttonActiveEpReq;
        private System.Windows.Forms.Button buttonPowerDescReq;
        private System.Windows.Forms.Button buttonSimpleDescReq;
        private System.Windows.Forms.TextBox textBoxSimpleReqEndPoint;
        private System.Windows.Forms.TextBox textBoxSimpleReqAddr;
        private System.Windows.Forms.TextBox textBoxPowerReqAddr;
        private System.Windows.Forms.TextBox textBoxActiveEpAddr;
        private System.Windows.Forms.TextBox textBoxMatchReqAddr;
        private System.Windows.Forms.TextBox textBoxMatchReqNbrInputClusters;
        private System.Windows.Forms.TextBox textBoxMatchReqNbrOutputClusters;
        private System.Windows.Forms.TextBox textBoxMatchReqProfileID;
        private System.Windows.Forms.TextBox textBoxMatchReqInputClusters;
        private System.Windows.Forms.TextBox textBoxMatchReqOutputClusters;
        private System.Windows.Forms.TextBox textBoxComplexReqAddr;
        private System.Windows.Forms.Button buttonComplexReq;
        private System.Windows.Forms.TabPage tabPage5;
        private System.Windows.Forms.TabPage tabPage6;
        private System.Windows.Forms.TabPage tabPage8;
        private System.Windows.Forms.TextBox textBoxMoveToLevelAddr;
        private System.Windows.Forms.Button buttonMoveToLevel;
        private System.Windows.Forms.TextBox textBoxMoveToLevelTransTime;
        private System.Windows.Forms.TextBox textBoxMoveToLevelLevel;
        private System.Windows.Forms.TextBox textBoxMoveToLevelDstEndPoint;
        private System.Windows.Forms.TextBox textBoxMoveToLevelSrcEndPoint;
        private System.Windows.Forms.Button buttonIdQuery;
        private System.Windows.Forms.Button buttonIdSend;
        private System.Windows.Forms.TextBox textBoxIdSendTime;
        private System.Windows.Forms.TextBox textBoxIdSendDstEp;
        private System.Windows.Forms.TextBox textBoxSendIdSrcEp;
        private System.Windows.Forms.TextBox textBoxSendIdAddr;
        private System.Windows.Forms.TextBox textBoxIdQueryDstEp;
        private System.Windows.Forms.TextBox textBoxIdQuerySrcEp;
        private System.Windows.Forms.TextBox textBoxIdQueryAddr;
        private System.Windows.Forms.TextBox textBoxMoveToHueTime;
        private System.Windows.Forms.TextBox textBoxMoveToHueDir;
        private System.Windows.Forms.TextBox textBoxMoveToHueHue;
        private System.Windows.Forms.TextBox textBoxMoveToHueDstEp;
        private System.Windows.Forms.TextBox textBoxMoveToHueSrcEp;
        private System.Windows.Forms.Button buttonMoveToHue;
        private System.Windows.Forms.TextBox textBoxMoveToHueAddr;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.ComboBox comboBoxLockUnlock;
        private System.Windows.Forms.TextBox textBoxLockUnlockDstEp;
        private System.Windows.Forms.TextBox textBoxLockUnlockSrcEp;
        private System.Windows.Forms.TextBox textBoxLockUnlockAddr;
        private System.Windows.Forms.Button buttonLockUnlock;
        private System.Windows.Forms.TabPage tabPage9;
        private System.Windows.Forms.Button buttonZllTouchlinkInitiate;
        private System.Windows.Forms.Button buttonZllTouchlinkFactoryReset;
        private System.Windows.Forms.TabPage tabPage10;
        private System.Windows.Forms.TextBox textBoxZllOnOffEffectsGradient;
        private System.Windows.Forms.TextBox textBoxZllOnOffEffectsDstEp;
        private System.Windows.Forms.TextBox textBoxZllOnOffEffectsSrcEp;
        private System.Windows.Forms.TextBox textBoxZllOnOffEffectsAddr;
        private System.Windows.Forms.Button buttonZllOnOffEffects;
        private System.Windows.Forms.ComboBox comboBoxZllOnOffEffectID;
        private System.Windows.Forms.TabPage tabPage11;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button buttonZllMoveToHue;
        private System.Windows.Forms.TextBox textBoxZllMoveToHueAddr;
        private System.Windows.Forms.TextBox textBoxZllMoveToHueSrcEp;
        private System.Windows.Forms.TextBox textBoxZllMoveToHueDstEp;
        private System.Windows.Forms.TextBox textBoxZllMoveToHueDirection;
        private System.Windows.Forms.TextBox textBoxZllMoveToHueTransTime;
        private System.Windows.Forms.TextBox textBoxZllMoveToHueHue;
        private System.Windows.Forms.Button buttonAddGroup;
        private System.Windows.Forms.TextBox textBoxAddGroupDstEp;
        private System.Windows.Forms.TextBox textBoxAddGroupSrcEp;
        private System.Windows.Forms.TextBox textBoxAddGroupAddr;
        private System.Windows.Forms.TextBox textBoxAddGroupGroupAddr;
        private System.Windows.Forms.TextBox textBoxIeeeReqStartIndex;
        private System.Windows.Forms.ComboBox comboBoxIeeeReqType;
        private System.Windows.Forms.TextBox textBoxIeeeReqAddr;
        private System.Windows.Forms.TextBox textBoxIeeeReqTargetAddr;
        private System.Windows.Forms.TextBox textBoxNwkAddrReqTargetAddr;
        private System.Windows.Forms.TextBox textBoxNwkAddrReqExtAddr;
        private System.Windows.Forms.TextBox textBoxNwkAddrReqStartIndex;
        private System.Windows.Forms.ComboBox comboBoxNwkAddrReqType;
        private System.Windows.Forms.TextBox textBoxViewGroupGroupAddr;
        private System.Windows.Forms.TextBox textBoxViewGroupDstEp;
        private System.Windows.Forms.TextBox textBoxViewGroupSrcEp;
        private System.Windows.Forms.TextBox textBoxViewGroupAddr;
        private System.Windows.Forms.Button buttonViewGroup;
        private System.Windows.Forms.Button buttonStartScan;
        private System.Windows.Forms.ComboBox comboBoxOnOffCommand;
        private System.Windows.Forms.Button buttonRecoverNwk;
        private System.Windows.Forms.Button buttonRestoreNwk;
        private System.Windows.Forms.Button buttonMgmtLqiReq;
        private System.Windows.Forms.TextBox textBoxBindTargetEP;
        private System.Windows.Forms.TextBox textBoxBindClusterID;
        private System.Windows.Forms.TabPage tabPage12;
        private System.Windows.Forms.Button buttonReadAttrib;
        private System.Windows.Forms.TextBox textBoxReadAttribTargetAddr;
        private System.Windows.Forms.TextBox textBoxReadAttribSrcEP;
        private System.Windows.Forms.TextBox textBoxReadAttribDstEP;
        private System.Windows.Forms.TextBox textBoxReadAttribClusterID;
        private System.Windows.Forms.TextBox textBoxReadAttribID1;
        private System.Windows.Forms.ComboBox comboBoxReadAttribDirection;
        private System.Windows.Forms.TextBox textBoxReadAttribCount;
        private System.Windows.Forms.Button buttonWriteAttrib;
        private System.Windows.Forms.TextBox textBoxConfigReportTargetAddr;
        private System.Windows.Forms.Button buttonConfigReport;
        private System.Windows.Forms.TextBox textBoxConfigReportSrcEP;
        private System.Windows.Forms.TextBox textBoxConfigReportClusterID;
        private System.Windows.Forms.TextBox textBoxConfigReportDstEP;
        private System.Windows.Forms.ComboBox comboBoxConfigReportDirection;
        private System.Windows.Forms.TextBox textBoxConfigReportMinInterval;
        private System.Windows.Forms.TextBox textBoxConfigReportAttribID;
        private System.Windows.Forms.TextBox textBoxConfigReportAttribType;
        private System.Windows.Forms.ComboBox comboBoxConfigReportAttribDirection;
        private System.Windows.Forms.ComboBox comboBoxBindAddrMode;
        private System.Windows.Forms.TextBox textBoxBindDestAddr;
        private System.Windows.Forms.TextBox textBoxBindDestEP;
        private System.Windows.Forms.TextBox textBoxReadAllAttribAddr;
        private System.Windows.Forms.Button buttonReadAllAttrib;
        private System.Windows.Forms.TextBox textBoxReadAllAttribDstEP;
        private System.Windows.Forms.TextBox textBoxReadAllAttribSrcEP;
        private System.Windows.Forms.ComboBox comboBoxReadAllAttribDirection;
        private System.Windows.Forms.TextBox textBoxReadAllAttribClusterID;
        private System.Windows.Forms.TextBox textBoxGetGroupDstEp;
        private System.Windows.Forms.TextBox textBoxGetGroupSrcEp;
        private System.Windows.Forms.TextBox textBoxGetGroupTargetAddr;
        private System.Windows.Forms.Button buttonGetGroup;
        private System.Windows.Forms.TextBox textBoxGetGroupCount;
        private System.Windows.Forms.Button buttonRemoveGroup;
        private System.Windows.Forms.TextBox textBoxRemoveGroupGroupAddr;
        private System.Windows.Forms.TextBox textBoxRemoveGroupDstEp;
        private System.Windows.Forms.TextBox textBoxRemoveGroupSrcEp;
        private System.Windows.Forms.TextBox textBoxRemoveGroupTargetAddr;
        private System.Windows.Forms.TextBox textBoxRemoveAllGroupDstEp;
        private System.Windows.Forms.TextBox textBoxRemoveAllGroupSrcEp;
        private System.Windows.Forms.TextBox textBoxRemoveAllGroupTargetAddr;
        private System.Windows.Forms.Button buttonGroupRemoveAll;
        private System.Windows.Forms.ComboBox comboBoxOnOffAddrMode;
        private System.Windows.Forms.ComboBox comboBoxMoveToLevelAddrMode;
        private System.Windows.Forms.Button buttonUnBind;
        private System.Windows.Forms.TextBox textBoxUnBindTargetExtAddr;
        private System.Windows.Forms.TextBox textBoxUnBindTargetEP;
        private System.Windows.Forms.TextBox textBoxUnBindClusterID;
        private System.Windows.Forms.TextBox textBoxUnBindDestAddr;
        private System.Windows.Forms.ComboBox comboBoxUnBindAddrMode;
        private System.Windows.Forms.TextBox textBoxUnBindDestEP;
        private System.Windows.Forms.Button buttonMoveToColor;
        private System.Windows.Forms.TextBox textBoxMoveToColorTime;
        private System.Windows.Forms.TextBox textBoxMoveToColorY;
        private System.Windows.Forms.TextBox textBoxMoveToColorX;
        private System.Windows.Forms.TextBox textBoxMoveToColorDstEp;
        private System.Windows.Forms.TextBox textBoxMoveToColorSrcEp;
        private System.Windows.Forms.TextBox textBoxMoveToColorAddr;
        private System.Windows.Forms.Button buttonDiscoverAttributes;
        private System.Windows.Forms.TextBox textBoxDiscoverAttributesMaxIDs;
        private System.Windows.Forms.ComboBox comboBoxDiscoverAttributesDirection;
        private System.Windows.Forms.TextBox textBoxDiscoverAttributesClusterID;
        private System.Windows.Forms.TextBox textBoxDiscoverAttributesDstEp;
        private System.Windows.Forms.TextBox textBoxDiscoverAttributesSrcEp;
        private System.Windows.Forms.TextBox textBoxDiscoverAttributesAddr;
        private System.Windows.Forms.Button buttonMgmtLeave;
        private System.Windows.Forms.ComboBox comboBoxMgmtLeaveChildren;
        private System.Windows.Forms.ComboBox comboBoxMgmtLeaveReJoin;
        private System.Windows.Forms.TextBox textBoxMgmtLeaveExtAddr;
        private System.Windows.Forms.TextBox textBoxMgmtLeaveAddr;
        private System.Windows.Forms.TextBox textBoxConfigReportChange;
        private System.Windows.Forms.TextBox textBoxConfigReportTimeOut;
        private System.Windows.Forms.TextBox textBoxConfigReportMaxInterval;
        private System.Windows.Forms.ComboBox comboBoxWriteAttribDirection;
        private System.Windows.Forms.TextBox textBoxWriteAttribClusterID;
        private System.Windows.Forms.TextBox textBoxWriteAttribDstEP;
        private System.Windows.Forms.TextBox textBoxWriteAttribSrcEP;
        private System.Windows.Forms.TextBox textBoxWriteAttribTargetAddr;
        private System.Windows.Forms.TextBox textBoxWriteAttribData;
        private System.Windows.Forms.TextBox textBoxWriteAttribID;
        private System.Windows.Forms.TextBox textBoxMoveToColorTempDstEp;
        private System.Windows.Forms.TextBox textBoxMoveToColorTempSrcEp;
        private System.Windows.Forms.TextBox textBoxMoveToColorTempAddr;
        private System.Windows.Forms.Button buttonMoveToColorTemp;
        private System.Windows.Forms.TextBox textBoxMoveToColorTempRate;
        private System.Windows.Forms.TextBox textBoxMoveToColorTempTemp;
        private System.Windows.Forms.ComboBox comboBoxMoveToLevelOnOff;
        private System.Windows.Forms.ComboBox comboBoxConfigReportAddrMode;
        private System.Windows.Forms.TabPage tabPage13;
        private System.Windows.Forms.ComboBox comboBoxEnrollRspAddrMode;
        private System.Windows.Forms.Button buttonEnrollResponse;
        private System.Windows.Forms.TextBox textBoxEnrollRspDstEp;
        private System.Windows.Forms.TextBox textBoxEnrollRspSrcEp;
        private System.Windows.Forms.TextBox textBoxEnrollRspAddr;
        private System.Windows.Forms.TextBox textBoxEnrollRspZone;
        private System.Windows.Forms.ComboBox comboBoxEnrollRspCode;
        private System.Windows.Forms.TextBox textBoxWriteAttribDataType;
        private System.Windows.Forms.TabPage tabPage14;
        private System.Windows.Forms.Button buttonOTALoadNewImage;
        private System.Windows.Forms.OpenFileDialog openOtaFileDialog;
        private System.Windows.Forms.TextBox textBoxOtaFileManuCode;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxOtaFileImageType;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxOtaFileVersion;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBoxOtaFileSize;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox comboBoxReadAttribManuSpecific;
        private System.Windows.Forms.TextBox textBoxReadAttribManuID;
        private System.Windows.Forms.TextBox textBoxWriteAttribManuID;
        private System.Windows.Forms.ComboBox comboBoxWriteAttribManuSpecific;
        private System.Windows.Forms.Button buttonReadReportConfig;
        private System.Windows.Forms.ComboBox comboBoxReadReportConfigAddrMode;
        private System.Windows.Forms.TextBox textBoxReadReportConfigTargetAddr;
        private System.Windows.Forms.TextBox textBoxReadReportConfigDstEP;
        private System.Windows.Forms.TextBox textBoxReadReportConfigSrcEP;
        private System.Windows.Forms.TextBox textBoxReadReportConfigClusterID;
        private System.Windows.Forms.TextBox textBoxReadReportConfigAttribID;
        private System.Windows.Forms.ComboBox comboBoxReadReportConfigDirIsRx;
        private System.Windows.Forms.ComboBox comboBoxReadReportConfigDirection;
        private System.Windows.Forms.TextBox textBoxManyToOneRouteRequesRadius;
        private System.Windows.Forms.Button buttonManyToOneRouteRequest;
        private System.Windows.Forms.ComboBox comboBoxManyToOneRouteRequestCacheRoute;
        private System.Windows.Forms.Button buttonMgmtNwkUpdate;
        private System.Windows.Forms.ComboBox comboBoxMgmtNwkUpdateAddrMode;
        private System.Windows.Forms.TextBox textBoxMgmtNwkUpdateTargetAddr;
        private System.Windows.Forms.TextBox textBoxMgmtNwkUpdateChannelMask;
        private System.Windows.Forms.TextBox textBoxMgmtNwkUpdateScanDuration;
        private System.Windows.Forms.TextBox textBoxMgmtNwkUpdateScanCount;
        private System.Windows.Forms.Button buttonDiscoverCommands;
        private System.Windows.Forms.ComboBox comboBoxDiscoverCommandsAddrMode;
        private System.Windows.Forms.TextBox textBoxDiscoverCommandsTargetAddr;
        private System.Windows.Forms.TextBox textBoxDiscoverCommandsDstEP;
        private System.Windows.Forms.TextBox textBoxDiscoverCommandsSrcEP;
        private System.Windows.Forms.TextBox textBoxDiscoverCommandsClusterID;
        private System.Windows.Forms.ComboBox comboBoxDiscoverCommandsDirection;
        private System.Windows.Forms.TextBox textBoxDiscoverCommandsCommandID;
        private System.Windows.Forms.ComboBox comboBoxDiscoverCommandsManuSpecific;
        private System.Windows.Forms.TextBox textBoxDiscoverCommandsManuID;
        private System.Windows.Forms.TextBox textBoxDiscoverCommandsMaxCommands;
        private System.Windows.Forms.ComboBox comboBoxDiscoverAttributesExtended;
        private System.Windows.Forms.ComboBox comboBoxDiscoverCommandsRxGen;
        private System.Windows.Forms.TextBox textBoxMgmtNwkUpdateNwkManagerAddr;
        private System.Windows.Forms.TabPage BasicClusterTab;
        private System.Windows.Forms.ComboBox comboBoxBasicResetTargetAddrMode;
        private System.Windows.Forms.Button buttonBasicReset;
        private System.Windows.Forms.TextBox textBoxBasicResetDstEP;
        private System.Windows.Forms.TextBox textBoxBasicResetSrcEP;
        private System.Windows.Forms.TextBox textBoxBasicResetTargetAddr;
        private System.Windows.Forms.Button buttonOTAImageNotify;
        private System.Windows.Forms.ComboBox comboBoxOTAImageNotifyAddrMode;
        private System.Windows.Forms.TextBox textBoxOTAImageNotifyTargetAddr;
        private System.Windows.Forms.TextBox textBoxOTAImageNotifyDstEP;
        private System.Windows.Forms.TextBox textBoxOTAImageNotifySrcEP;
        private System.Windows.Forms.ComboBox comboBoxOTAImageNotifyType;
        private System.Windows.Forms.TextBox textBoxOTAImageNotifyFileVersion;
        private System.Windows.Forms.TextBox textBoxOTAImageNotifyImageType;
        private System.Windows.Forms.TextBox textBoxOTAImageNotifyManuID;
        private System.Windows.Forms.TextBox textBoxOTAImageNotifyJitter;
        private System.Windows.Forms.ProgressBar progressBarOtaDownloadProgress;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBoxOtaDownloadStatus;
        private System.Windows.Forms.TextBox textBoxOtaFileOffset;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textBoxGroupAddIfIdentifyDstEp;
        private System.Windows.Forms.TextBox textBoxGroupAddIfIndentifyingTargetAddr;
        private System.Windows.Forms.Button buttonGroupAddIfIdentifying;
        private System.Windows.Forms.TextBox textBoxGroupAddIfIdentifyGroupID;
        private System.Windows.Forms.TextBox textBoxGroupAddIfIdentifySrcEp;
        private System.Windows.Forms.TabPage tabPage7;
        private System.Windows.Forms.TextBox textBoxGetSceneMembershipGroupID;
        private System.Windows.Forms.TextBox textBoxGetSceneMembershipDstEndPoint;
        private System.Windows.Forms.TextBox textBoxGetSceneMembershipSrcEndPoint;
        private System.Windows.Forms.TextBox textBoxGetSceneMembershipAddr;
        private System.Windows.Forms.ComboBox comboBoxGetSceneMembershipAddrMode;
        private System.Windows.Forms.Button buttonGetSceneMembership;
        private System.Windows.Forms.TextBox textBoxRecallSceneSceneId;
        private System.Windows.Forms.TextBox textBoxRecallSceneGroupId;
        private System.Windows.Forms.TextBox textBoxRecallSceneDstEndPoint;
        private System.Windows.Forms.TextBox textBoxRecallSceneSrcEndPoint;
        private System.Windows.Forms.TextBox textBoxRecallSceneAddr;
        private System.Windows.Forms.ComboBox comboBoxRecallSceneAddrMode;
        private System.Windows.Forms.Button buttonRecallScene;
        private System.Windows.Forms.TextBox textBoxStoreSceneSceneId;
        private System.Windows.Forms.TextBox textBoxStoreSceneGroupId;
        private System.Windows.Forms.TextBox textBoxStoreSceneDstEndPoint;
        private System.Windows.Forms.TextBox textBoxStoreSceneSrcEndPoint;
        private System.Windows.Forms.TextBox textBoxStoreSceneAddr;
        private System.Windows.Forms.ComboBox comboBoxStoreSceneAddrMode;
        private System.Windows.Forms.Button buttonStoreScene;
        private System.Windows.Forms.TextBox textBoxAddSceneMaxNameLen;
        private System.Windows.Forms.TextBox textBoxAddSceneNameLen;
        private System.Windows.Forms.TextBox textBoxAddSceneName;
        private System.Windows.Forms.TextBox textBoxAddSceneTransTime;
        private System.Windows.Forms.TextBox textBoxAddSceneSceneId;
        private System.Windows.Forms.TextBox textBoxAddSceneGroupId;
        private System.Windows.Forms.TextBox textBoxAddSceneDstEndPoint;
        private System.Windows.Forms.TextBox textBoxAddSceneSrcEndPoint;
        private System.Windows.Forms.TextBox textBoxAddSceneAddr;
        private System.Windows.Forms.ComboBox comboBoxAddSceneAddrMode;
        private System.Windows.Forms.Button buttonAddScene;
        private System.Windows.Forms.ComboBox comboBoxViewSceneAddrMode;
        private System.Windows.Forms.TextBox textBoxViewSceneSceneId;
        private System.Windows.Forms.TextBox textBoxViewSceneGroupId;
        private System.Windows.Forms.TextBox textBoxViewSceneDstEndPoint;
        private System.Windows.Forms.TextBox textBoxViewSceneSrcEndPoint;
        private System.Windows.Forms.TextBox textBoxViewSceneAddr;
        private System.Windows.Forms.Button buttonViewScene;
        private System.Windows.Forms.Button buttonRemoveAllScenes;
        private System.Windows.Forms.TextBox textBoxRemoveAllScenesGroupID;
        private System.Windows.Forms.TextBox textBoxRemoveAllScenesDstEndPoint;
        private System.Windows.Forms.TextBox textBoxRemoveAllScenesSrcEndPoint;
        private System.Windows.Forms.TextBox textBoxRemoveAllScenesAddr;
        private System.Windows.Forms.ComboBox comboBoxRemoveAllScenesAddrMode;
        private System.Windows.Forms.Button buttonRemoveScene;
        private System.Windows.Forms.TextBox textBoxRemoveSceneSceneID;
        private System.Windows.Forms.TextBox textBoxRemoveSceneGroupID;
        private System.Windows.Forms.TextBox textBoxRemoveSceneDstEndPoint;
        private System.Windows.Forms.TextBox textBoxRemoveSceneSrcEndPoint;
        private System.Windows.Forms.TextBox textBoxRemoveSceneAddr;
        private System.Windows.Forms.ComboBox comboBoxRemoveSceneAddrMode;
        private System.Windows.Forms.Button buttonPermitJoinState;
        private System.Windows.Forms.TextBox textBoxRemoveChildAddr;
        private System.Windows.Forms.TextBox textBoxRemoveParentAddr;
        private System.Windows.Forms.Button buttonRemoveDevice;
        private System.Windows.Forms.ComboBox comboBoxLeaveChildren;
        private System.Windows.Forms.ComboBox comboBoxLeaveReJoin;
        private System.Windows.Forms.TextBox textBoxLeaveAddr;
        private System.Windows.Forms.Button buttonLeave;
        private System.Windows.Forms.TextBox textBoxLqiReqStartIndex;
        private System.Windows.Forms.TextBox textBoxLqiReqTargetAddr;
        private System.Windows.Forms.TextBox textBoxRestoreNwkFrameCounter;
        private System.Windows.Forms.ToolTip toolTipGeneralTooltip;
        private System.Windows.Forms.Button buttonAddToList;
        private System.Windows.Forms.TextBox textBoxRawDataCommandsData;
        private System.Windows.Forms.TextBox textBoxRawDataCommandsClusterID;
        private System.Windows.Forms.TextBox textBoxRawDataCommandsDstEP;
        private System.Windows.Forms.TextBox textBoxRawDataCommandsSrcEP;
        private System.Windows.Forms.TextBox textBoxRawDataCommandsTargetAddr;
        private System.Windows.Forms.ComboBox comboBoxRawDataCommandsAddrMode;
        private System.Windows.Forms.Button buttonRawDataSend;
        private System.Windows.Forms.TextBox textBoxRawDataCommandsRadius;
        private System.Windows.Forms.TextBox textBoxRawDataCommandsSecurityMode;
        private System.Windows.Forms.TextBox textBoxRawDataCommandsProfileID;
        private System.Windows.Forms.TextBox textBoxUserReqAddr;
        private System.Windows.Forms.Button buttonUserReq;
        private System.Windows.Forms.TextBox textBoxUserSetReqAddr;
        private System.Windows.Forms.Button buttonUserSetReq;
        private System.Windows.Forms.TextBox textBoxUserSetReqDescription;
        private System.Windows.Forms.TextBox textBoxOTASetWaitForDataParamsRequestBlockDelay;
        private System.Windows.Forms.TextBox textBoxOTASetWaitForDataParamsRequestTime;
        private System.Windows.Forms.TextBox textBoxOTASetWaitForDataParamsCurrentTime;
        private System.Windows.Forms.TextBox textBoxOTASetWaitForDataParamsSrcEP;
        private System.Windows.Forms.TextBox textBoxOTASetWaitForDataParamsTargetAddr;
        private System.Windows.Forms.Button buttonOTASetWaitForDataParams;
        private System.Windows.Forms.TextBox textBoxDiscoverAttributesStartAttrId;
        private System.Windows.Forms.TextBox textBoxBindTargetExtAddr;
        private System.Windows.Forms.TabPage AHIControl;
        private System.Windows.Forms.TextBox textBoxDioSetDirectionOutputPinMask;
        private System.Windows.Forms.TextBox textBoxDioSetDirectionInputPinMask;
        private System.Windows.Forms.Button buttonDioSetDirection;
        private System.Windows.Forms.TextBox textBoxIPNConfigPollPeriod;
        private System.Windows.Forms.ComboBox comboBoxIPNConfigRegisterCallback;
        private System.Windows.Forms.TextBox textBoxIPNConfigDioStatusOutDioMask;
        private System.Windows.Forms.TextBox textBoxIPNConfigDioRfActiveOutDioMask;
        private System.Windows.Forms.ComboBox comboBoxIPNConfigEnable;
        private System.Windows.Forms.Button buttonInPacketNotification;
        private System.Windows.Forms.TextBox textBoxDioSetOutputOffPinMask;
        private System.Windows.Forms.TextBox textBoxDioSetOutputOnPinMask;
        private System.Windows.Forms.Button buttonDioSetOutput;
        private System.Windows.Forms.TextBox textBoxIPNConfigDioTxConfInDioMask;
        private System.Windows.Forms.ComboBox comboBoxIPNConfigTimerId;
        private System.Windows.Forms.Label labelUnimplemented;
        private System.Windows.Forms.TabPage tabPagePollControl;
        private System.Windows.Forms.ComboBox comboBoxFastPollEnable;
        private System.Windows.Forms.TextBox textBoxFastPollExpiryTime;
        private System.Windows.Forms.Button buttonSetCheckinRspData;

        private System.Windows.Forms.Button buttonAHISetTxPower;
        private System.Windows.Forms.TextBox textBoxAHITxPower;

        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBoxOtaFileHeaderStr;
        private System.Windows.Forms.TextBox textBoxOtaFileHeaderVer;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox textBoxOtaFileHeaderLen;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox textBoxOtaFileHeaderFCTL;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox textBoxOtaFileID;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textBoxOtaFileStackVer;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TextBox textBoxAddSceneData;
        private System.Windows.Forms.TextBox textBoxAddSceneExtLen;
        private System.Windows.Forms.TextBox textBoxMoveToSatTime;
        private System.Windows.Forms.TextBox textBoxMoveToSatSat;
        private System.Windows.Forms.TextBox textBoxMoveToSatDstEp;
        private System.Windows.Forms.TextBox textBoxMoveToSatSrcEp;
        private System.Windows.Forms.Button buttonMoveToSat;
        private System.Windows.Forms.TextBox textBoxMoveToSatAddr;
        private System.Windows.Forms.TabPage tabPageDevice;
        private System.Windows.Forms.Button buttonCopyAddr;
        private System.Windows.Forms.Button buttonDiscoverDevices;
        private System.Windows.Forms.TextBox textBoxExtAddr;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.ComboBox comboBoxAddressList;
        private System.Windows.Forms.TextBox textBoxGroupName;
        private System.Windows.Forms.TextBox textBoxGroupNameMaxLength;
        private System.Windows.Forms.TextBox textBoxGroupNameLength;
        private System.Windows.Forms.TextBox textBoxOOBDataKey;
        private System.Windows.Forms.TextBox textBoxOOBDataAddr;
        private System.Windows.Forms.Button buttonOOBCommissioningData;
        private System.Windows.Forms.Button buttonDiscoveryOnly;
        private System.Windows.Forms.TabPage tabPage15;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.CheckBox checkBoxShowExtension;
        private System.Windows.Forms.CheckBox checkBoxDebug;
        private System.Windows.Forms.Button buttonNWKState;
        private System.Windows.Forms.TextBox textBoxPollInterval;
        private System.Windows.Forms.Button buttonPollInterval;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Button buttonNciCmd;
        private System.Windows.Forms.ComboBox comboBoxNciCmd;
    }
}

