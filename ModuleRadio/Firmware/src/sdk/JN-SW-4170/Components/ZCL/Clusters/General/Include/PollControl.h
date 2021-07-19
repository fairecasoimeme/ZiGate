/*****************************************************************************
 *
 * MODULE:             Poll Control Cluster
 *
 * COMPONENT:          PollControl.h
 *
 * AUTHOR:             Shweta Chauhan
 * DESCRIPTION:        Header for PollControl Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/SmartEnergy/Branches/HA1_x_1v0/ZCL/Clusters/General/Include/PollControl.h $
 *
 * $Revision: 54140 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2013-05-21 14:04:40 +0530 (Tue, 21 May 2013) $
 *
 * $Id: PollControl.h 54140 2013-05-21 08:34:40Z nxp57621 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5148, JN5142, JN5139]. 
 * You, and any third parties must reproduce the copyright and warranty notice 
 * and any other legend of ownership on each  copy or partial copy of the software.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE. 
 *
 * Copyright NXP B.V. 2012. All rights reserved
 *
 ****************************************************************************/

#ifndef POLLCONTROL_H
#define POLLCONTROL_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"
#include "zcl_customcommand.h"
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/* Cluster ID's */
#define GENERAL_CLUSTER_ID_POLL_CONTROL                        0x0020

/****************************************************************************/
/*             POLL_CONTROL Control Cluster - Optional Attributes             */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the Poll Control cluster.                                 */
/****************************************************************************/

/* Checkin Interval Minimum attribute */
//#define CLD_POLL_CONTROL_ATTR_CHECKIN_INTERVAL_MIN

/* Long Poll Interval minimum attribute */
//#define CLD_POLL_CONTROL_ATTR_LONG_POLL_INTERVAL_MIN

/* Fast Poll Timeout Maximum attribute */
//#define CLD_POLL_CONTROL_ATTR_FAST_POLL_TIMEOUT_MAX

/****************************************************************************/
/*             POLL_CONTROL Control Cluster - Optional Commands             */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* commands to the Poll Control cluster.                                 */
/****************************************************************************/

/* Set Long Poll Interval Command */
//#define CLD_POLL_CONTROL_CMD_SET_LONG_POLL_INTERVAL

/* Set Short Poll Interval Command */
//#define CLD_POLL_CONTROL_CMD_SET_SHORT_POLL_INTERVAL

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
#ifndef CLD_POLL_CONTROL_CHECKIN_INTERVAL_MIN
    #define CLD_POLL_CONTROL_CHECKIN_INTERVAL_MIN       0
#endif
#ifndef CLD_POLL_CONTROL_CHECKIN_INTERVAL_MAX
    #define CLD_POLL_CONTROL_CHECKIN_INTERVAL_MAX       0x6e0000
#endif

#ifndef CLD_POLL_CONTROL_FAST_POLL_TIMEOUT_MAX
    #define CLD_POLL_CONTROL_FAST_POLL_TIMEOUT_MAX      0xffff
#endif

#ifndef CLD_POLL_CONTROL_FAST_POLL_TIMEOUT_MIN
    #define CLD_POLL_CONTROL_FAST_POLL_TIMEOUT_MIN      0x01
#endif

#ifndef CLD_POLL_CONTROL_LONG_POLL_INTERVAL_MAX
    #define CLD_POLL_CONTROL_LONG_POLL_INTERVAL_MAX     0x6e0000
#endif

#ifndef CLD_POLL_CONTROL_LONG_POLL_INTERVAL_MIN
    #define CLD_POLL_CONTROL_LONG_POLL_INTERVAL_MIN     0x04
#endif

#ifndef CLD_POLL_CONTROL_SHORT_POLL_INTERVAL_MAX
    #define CLD_POLL_CONTROL_SHORT_POLL_INTERVAL_MAX    0xffff
#endif

#ifndef CLD_POLL_CONTROL_SHORT_POLL_INTERVAL_MIN
    #define CLD_POLL_CONTROL_SHORT_POLL_INTERVAL_MIN    0x01
#endif

#ifndef CLD_POLL_CONTROL_NUMBER_OF_MULTIPLE_CLIENTS
    #define CLD_POLL_CONTROL_NUMBER_OF_MULTIPLE_CLIENTS  3
#endif

#ifndef CLD_POLL_CONTROL_CLUSTER_REVISION
    #define CLD_POLL_CONTROL_CLUSTER_REVISION                         1
#endif 
/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/* Poll Control Command - Payload */
typedef enum 
{
    E_CLD_POLL_CONTROL_CMD_CHECKIN                      = 0x00,        /* Mandatory */
    E_CLD_POLL_CONTROL_CMD_FAST_POLL_STOP,                              /* Mandatory */
    E_CLD_POLL_CONTROL_CMD_SET_LONG_POLL_INTERVAL,                      /* Optional */
    E_CLD_POLL_CONTROL_CMD_SET_SHORT_POLL_INTERVAL,                     /* Optional */
} teCLD_PollControl_CommandID;



typedef enum 
{
    /* Poll Control attribute set attribute ID's (A1) */
    E_CLD_POLL_CONTROL_ATTR_ID_CHECKIN_INTERVAL         = 0x0000,           /* 0.Mandatory */
    E_CLD_POLL_CONTROL_ATTR_ID_LONG_POLL_INTERVAL,                          /* 1.Mandatory */
    E_CLD_POLL_CONTROL_ATTR_ID_SHORT_POLL_INTERVAL,                         /* 2.Mandatory */
    E_CLD_POLL_CONTROL_ATTR_ID_FAST_POLL_TIMEOUT,                           /* 3.Mandatory */
    E_CLD_POLL_CONTROL_ATTR_ID_CHECKIN_INTERVAL_MIN ,                       /* 4.Optional */
    E_CLD_POLL_CONTROL_ATTR_ID_LONG_POLL_INTERVAL_MIN,                      /* 5.Optional */
    E_CLD_POLL_CONTROL_ATTR_ID_FAST_POLL_TIMEOUT_MAX,                       /* 6.Optional */
} teCLD_PollControl_Cluster_AttrID;

/* Poll Control Cluster */
typedef struct
{

#ifdef POLL_CONTROL_SERVER
    zuint32     u32CheckinInterval;                     
    zuint32     u32LongPollInterval;                     
    zuint16     u16ShortPollInterval;     
    zuint16     u16FastPollTimeout;          
                                   
#ifdef CLD_POLL_CONTROL_ATTR_CHECKIN_INTERVAL_MIN
    zuint32     u32CheckinIntervalMin;                     
#endif

#ifdef CLD_POLL_CONTROL_ATTR_LONG_POLL_INTERVAL_MIN
    zuint32     u32LongPollIntervalMin;                     
#endif

#ifdef CLD_POLL_CONTROL_ATTR_FAST_POLL_TIMEOUT_MAX
    zuint16     u16FastPollTimeoutMax;          
#endif
#endif
    zuint16     u16ClusterRevision;

} tsCLD_PollControl; 

typedef struct
{
    zbool                 bStartFastPolling;
    zuint16               u16FastPollTimeout;
}tsCLD_PollControl_CheckinResponsePayload;

#ifdef CLD_POLL_CONTROL_CMD_SET_LONG_POLL_INTERVAL
typedef struct
{
     zuint32         u32NewLongPollInterval;
}tsCLD_PollControl_SetLongPollIntervalPayload;
#endif

#ifdef CLD_POLL_CONTROL_CMD_SET_SHORT_POLL_INTERVAL
typedef struct
{
     zuint16         u16NewShortPollInterval;
}tsCLD_PollControl_SetShortPollIntervalPayload;
#endif

/* Definition of Poll Control Callback Event Structure */
typedef struct
{
    uint8                           u8CommandId;
        union
    {
        tsCLD_PollControl_CheckinResponsePayload              *psCheckinResponsePayload;
#ifdef CLD_POLL_CONTROL_CMD_SET_LONG_POLL_INTERVAL      
        tsCLD_PollControl_SetLongPollIntervalPayload          *psSetLongPollIntervalPayload;
#endif
#ifdef  CLD_POLL_CONTROL_CMD_SET_SHORT_POLL_INTERVAL    
        tsCLD_PollControl_SetShortPollIntervalPayload         *psSetShortPollIntervalPayload;
#endif
    } uMessage;
} tsCLD_PollControlCallBackMessage;

#ifdef POLL_CONTROL_SERVER 
/* Poll Control Entries */
typedef struct
{
    uint8                               u8EndPointId;
    uint16                              u16FastPollTimeout;
    uint16                              u16Address;
    bool                                bFastPollStop;
} tsCLD_PollControlCheckinEntry;

/* Poll Control Parameter Structure */
typedef struct
{    
    bool                                bFastPollMode;
    uint8                               u8CurrentClient;
    uint16                              u16FastPollTimeoutMax;
    uint16                              u16CurrentFastPollTimeout;
    uint32                              u32CurrentPollInterval;
    uint32                              u32CheckinTickUpdate;
    uint32                              u32PollTickUpdate;
    tsCLD_PollControlCheckinEntry       asCheckinEntry[CLD_POLL_CONTROL_NUMBER_OF_MULTIPLE_CLIENTS];
} tsCLD_PollControlParameters;
#endif

/* Custom data structure */
typedef struct
{
#ifdef POLL_CONTROL_SERVER 
    tsCLD_PollControlParameters         sControlParameters;
#endif    
    tsZCL_ReceiveEventAddress           sReceiveEventAddress;
    tsZCL_CallBackEvent                 sCustomCallBackEvent;
    tsCLD_PollControlCallBackMessage    sCallBackMessage;
} tsCLD_PollControlCustomDataStructure;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_PollControlCreatePollControl(
                tsZCL_ClusterInstance                  *psClusterInstance,
                bool_t                                 bIsServer,
                tsZCL_ClusterDefinition                *psClusterDefinition,
                void                                   *pvEndPointSharedStructPtr,
                uint8                                  *pu8AttributeControlBits,
                tsCLD_PollControlCustomDataStructure   *psCustomDataStructure);

#ifdef POLL_CONTROL_CLIENT   

PUBLIC teZCL_Status eCLD_PollControlFastPollStopSend(
                    uint8                                           u8SourceEndPointId,
                    uint8                                           u8DestinationEndPointId,
                    tsZCL_Address                                   *psDestinationAddress,
                    uint8                                           *pu8TransactionSequenceNumber);
                    
#ifdef CLD_POLL_CONTROL_CMD_SET_LONG_POLL_INTERVAL
PUBLIC teZCL_Status eCLD_PollControlSetLongPollIntervalSend(
                    uint8                                           u8SourceEndPointId,
                    uint8                                           u8DestinationEndPointId,
                    tsZCL_Address                                   *psDestinationAddress,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_PollControl_SetLongPollIntervalPayload    *psPayload);
#endif                  
                    
#ifdef CLD_POLL_CONTROL_CMD_SET_SHORT_POLL_INTERVAL               
PUBLIC teZCL_Status eCLD_PollControlSetShortPollIntervalSend(
                    uint8                                           u8SourceEndPointId,
                    uint8                                           u8DestinationEndPointId,
                    tsZCL_Address                                   *psDestinationAddress,
                    uint8                                           *pu8TransactionSequenceNumber,
                    tsCLD_PollControl_SetShortPollIntervalPayload   *psPayload);
#endif                  
#endif

#ifdef POLL_CONTROL_SERVER 

PUBLIC teZCL_Status eCLD_PollControlUpdate(void);

PUBLIC teZCL_Status eCLD_PollControlWriteHandler(
                                          uint8             u8SourceEndPointId,
                                          uint16            u16AttributeId,
                                          uint32            *pu32AttributeData,
                                          uint8             *pu8ErrorCode);
    
PUBLIC teZCL_Status eCLD_PollControlCheckinSend(
                                        uint8                u8SourceEndPointId,
                                        uint8                u8DestinationEndPointId,
                                        tsZCL_Address        *psDestinationAddress,
                                        uint8                *pu8TransactionSequenceNumber);
PUBLIC teZCL_Status eCLD_PollControlSetAttribute(
                                        uint8               u8SourceEndPointId,
                                        uint8               u8AttributeId,
                                        uint32              u32AttributeValue); 
PUBLIC uint8 u8CLD_PollControlFindCheckinEntry(
                                        tsCLD_PollControlCheckinEntry      *psCheckinEntry,
                                        bool                               *pbEntryFound);

PUBLIC teZCL_Status eCLD_PollControlUpdateSleepInterval(
                                        uint32           u32QuarterSecondsAsleep);                                        
#endif
/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
extern tsZCL_ClusterDefinition sCLD_PollControl;
extern const tsZCL_AttributeDefinition asCLD_PollControlClusterAttrDefs[];
extern uint8 au8PollControlAttributeControlBits[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* POLLCONTROL_H */
