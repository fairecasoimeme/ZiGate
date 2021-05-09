/*****************************************************************************
 *
 * MODULE:             Fan Control Cluster
 *
 * COMPONENT:          FanControl.h
 *
 * DESCRIPTION:        Fan Control Cluster Definition
 *
 ****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5168, JN5179].
 * You, and any third parties must reproduce the copyright and warranty notice
 * and any other legend of ownership on each copy or partial copy of the
 * software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
 * Copyright NXP B.V. 2016. All rights reserved
 *
 ***************************************************************************/

#ifndef FAN_CONTROL_H
#define FAN_CONTROL_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/*             Fan Control Cluster - Optional Attributes                    */
/*                                                                          */
/* Add the following #define's to your zcl_options.h file to add optional   */
/* attributes to the time cluster.                                          */
/****************************************************************************/
    /* None at the moment */
/* End of optional attributes */

#ifndef CLD_FAN_CONTROL_CLUSTER_REVISION
#define CLD_FAN_CONTROL_CLUSTER_REVISION                (1)
#endif

/* Cluster ID's */
#define HVAC_CLUSTER_ID_FAN_CONTROL                     (0x0202)

#define CLD_FAN_CONTROL_NUMBER_OF_MANDATORY_ATTRIBUTE   (2)
#define CLD_FAN_CONTROL_NUMBER_OF_OPTIONAL_ATTRIBUTE    (0)

#define CLD_FAN_CONTROL_MAX_NUMBER_OF_ATTRIBUTE       \
    CLD_FAN_CONTROL_NUMBER_OF_OPTIONAL_ATTRIBUTE +    \
    CLD_FAN_CONTROL_NUMBER_OF_MANDATORY_ATTRIBUTE

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* Fan Control attribute set attribute ID's (6.4.2.2) */
typedef enum 
{
    E_CLD_FAN_CONTROL_ATTR_ID_FAN_MODE              = 0x0000,  /* Mandatory */
    E_CLD_FAN_CONTROL_ATTR_ID_FAN_MODE_SEQUENCE,               /* Mandatory */
} teCLD_FanControl_AttributeID;

/* FanMode Attribute Values (6.4.2.2.1 ) */
typedef enum 
{
    E_CLD_FC_FAN_MODE_OFF       = 0x00,
    E_CLD_FC_FAN_MODE_LOW,      //0x01
    E_CLD_FC_FAN_MODE_MEDIUM,   //0x02
    E_CLD_FC_FAN_MODE_HIGH,     //0x03
    E_CLD_FC_FAN_MODE_ON,       //0x04
    E_CLD_FC_FAN_MODE_AUTO,     //0x05
    E_CLD_FC_FAN_MODE_SMART,    //0x06
} teCLD_FC_FanMode;

/* FanModeSequence Attribute Values (6.4.2.2.2 ) */
typedef enum 
{
    E_CLD_FC_FAN_MODE_SEQUENCE_LOW_MED_HIGH         = 0x00,
    E_CLD_FC_FAN_MODE_SEQUENCE_LOW_HIGH,            //0x01
    E_CLD_FC_FAN_MODE_SEQUENCE_LOW_MED_HIGH_AUTO,   //0x02
    E_CLD_FC_FAN_MODE_SEQUENCE_LOW_HIGH_AUTO,       //0x03
    E_CLD_FC_FAN_MODE_SEQUENCE_ON_AUTO,             //0x04
} teCLD_FC_FanModeSequence;

/* Fan Control Cluster */
typedef struct
{
    #ifdef FAN_CONTROL_SERVER    
        zenum8  e8FanMode;
        zenum8  e8FanModeSequence;
    #endif

    zuint16 u16ClusterRevision;
} tsCLD_FanControl;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC teZCL_Status eCLD_CreateFanControl(
                tsZCL_ClusterInstance              *psClusterInstance,
                bool_t                              bIsServer,
                tsZCL_ClusterDefinition            *psClusterDefinition,
                void                               *pvEndPointSharedStructPtr,
                uint8                              *pu8AttributeControlBits);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
extern tsZCL_ClusterDefinition sCLD_FanControl;
extern const tsZCL_AttributeDefinition asCLD_FanControlClusterAttributeDefinitions[];
extern uint8 au8FanControlClusterAttributeControlBits[];

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* TIME_H */
