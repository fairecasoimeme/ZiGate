/*****************************************************************************
 *
 * MODULE:             On/Off Switch Configuration Cluster
 *
 * COMPONENT:          OOSC.h
 *
 * AUTHOR:             Lee Mitchell
 *
 * DESCRIPTION:        Header for On/Off Switch Configuration Cluster
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Trunk/Clusters/General/Include/OOSC.h $
 *
 * $Revision: 72591 $
 *
 * $LastChangedBy: nxp57621 $
 *
 * $LastChangedDate: 2015-09-08 14:41:01 +0200 (Tue, 08 Sep 2015) $
 *
 * $Id: OOSC.h 72591 2015-09-08 12:41:01Z nxp57621 $
 *
 *****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products  [NXP Microcontrollers such as JN5168, JN5164,
 * JN5161, JN5148, JN5142, JN5139]. 
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

#ifndef OOSC_H
#define OOSC_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/* Cluster ID's */
#define GENERAL_CLUSTER_ID_ONOFF_SWITCH_CONFIGURATION   0x0007

#ifndef CLD_OOSC_CLUSTER_REVISION
    #define CLD_OOSC_CLUSTER_REVISION                         1
#endif 

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* On/Off switch configuration attribute ID's (3.9.2.2) */
typedef enum 
{
    E_CLD_OOSC_ATTR_ID_SWITCH_TYPE          = 0x0000,   /* Mandatory */
    E_CLD_OOSC_ATTR_ID_SWITCH_ACTIONS       = 0x0010,   /* Mandatory */
} teCLD_OOSC_ClusterID;


/* On/Off switch types */
typedef enum 
{
    E_CLD_OOSC_TYPE_TOGGLE,
    E_CLD_OOSC_TYPE_MOMENTARY,
    E_CLD_OOSC_TYPE_MULTI_FUNCTION
} teCLD_OOSC_SwitchType;


/* On/Off switch actions */
typedef enum 
{
    E_CLD_OOSC_ACTION_S2ON_S1OFF,
    E_CLD_OOSC_ACTION_S2OFF_S1ON,
    E_CLD_OOSC_ACTION_TOGGLE
} teCLD_OOSC_SwitchAction;


/* On/Off Switch Configuration Cluster */
typedef struct
{
#ifdef OOSC_SERVER    
    zenum8                  eSwitchType;                /* Mandatory */
    zenum8                  eSwitchActions;             /* Mandatory */
#endif    
    zuint16                 u16ClusterRevision;
} tsCLD_OOSC;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_OOSCCreateOnOffSwitchConfig(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8              *pu8AttributeControlBits);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
extern tsZCL_ClusterDefinition sCLD_OOSC;
extern uint8 au8OOSCAttributeControlBits[];
extern const tsZCL_AttributeDefinition asCLD_OOSCClusterAttributeDefinitions[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* OOSC_H */
