/*****************************************************************************
 *
 * MODULE:             Window Covering Cluster
 *
 * COMPONENT:          WindowCovering.h
 *
 * AUTHOR:             Vesa 'ISO-B' Ylikylä
 * DESCRIPTION:        Header for WindowCovering Client Cluster
 *
 * $HeadURL:  $
 *
 * $Revision: 1 $
 *
 * $LastChangedBy: isob $
 *
 * $LastChangedDate: 2019-01-19 12:00:00 +0200 (Sat, 19 Jan 2018) $
 *
 * $Id: WindowCovering.h 1 2019-01-19 10:00:00Z isob $
 *
 ****************************************************************************/

#ifndef WINDOWCOVERING_H
#define WINDOWCOVERING_H

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/* Cluster ID's */
#define CLOSURE_CLUSTER_ID_WINDOWCOVERING                         0x0102

/****************************************************************************/
/*         Window Covering Control Cluster - Optional Attributes            */
/*                                                                          */
/* Optional attributes are not implemented since client doesn't need those  */
/****************************************************************************/

#ifndef CLD_WINDOWCOVERING_CLUSTER_REVISION
    #define CLD_WINDOWCOVERING_CLUSTER_REVISION                         1
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* Window Covering Command - Payload */
typedef enum
{
    E_CLD_WINDOWCOVERING_CMD_UP_OPEN                      = 0x00,   /* Mandatory */
    E_CLD_WINDOWCOVERING_CMD_DOWN_CLOSE,                            /* Mandatory */
    E_CLD_WINDOWCOVERING_CMD_STOP,                                  /* Mandatory */
    E_CLD_WINDOWCOVERING_CMD_GO_TO_LIFT_VALUE             = 0x04,   /* Optional */
    E_CLD_WINDOWCOVERING_CMD_GO_TO_LIFT_PERCENTAGE,                 /* Optional */
    E_CLD_WINDOWCOVERING_CMD_GO_TO_TILT_VALUE             = 0x07,   /* Optional */
    E_CLD_WINDOWCOVERING_CMD_GO_TO_TILT_PERCENTAGE,                 /* Optional */
} teCLD_WindowCovering_CommandID;


typedef enum
{
    /* Window Covering attribute set: Information */
    E_CLD_WINDOWCOVERING_ATTR_ID_WINDOW_COVERING_TYPE                 = 0x00,  /* 0.Mandatory */
    E_CLD_WINDOWCOVERING_ATTR_ID_PHYSICAL_CLOSED_LIMIT_LIFT_CM,                /* 1.Optional */
    E_CLD_WINDOWCOVERING_ATTR_ID_PHYSICAL_CLOSED_LIMIT_TILT_DEGREE,            /* 2.Optional */
    E_CLD_WINDOWCOVERING_ATTR_ID_CURRENT_POSITION_LIFT_CM,                     /* 3.Optional */
    E_CLD_WINDOWCOVERING_ATTR_ID_CURRENT_POSITION_TILT_DEGREE,                 /* 4.Optional */
    E_CLD_WINDOWCOVERING_ATTR_ID_NUMBER_OF_ACTUATIONS_LIFT,                    /* 5.Optional */
    E_CLD_WINDOWCOVERING_ATTR_ID_NUMBER_OF_ACTUATIONS_TILT,                    /* 6.Optional */
    E_CLD_WINDOWCOVERING_ATTR_ID_CONFIG_STATUS,                                /* 7.Optional */
    E_CLD_WINDOWCOVERING_ATTR_ID_CURRENT_POSITION_LIFT_PERCENTAGE,             /* 8.Mandatory if */
    E_CLD_WINDOWCOVERING_ATTR_ID_CURRENT_POSITION_TILT_PERCENTAGE,             /* 9.Mandatory if */
    /* Window Covering attribute set: Settings */
    E_CLD_WINDOWCOVERING_ATTR_ID_INSTALLED_OPEN_LIMIT_LIFT_CM         = 0x10,  /* 0.Mandatory if */
    E_CLD_WINDOWCOVERING_ATTR_ID_INSTALLED_CLOSED_LIMIT_LIFT_CM,               /* 1.Mandatory if */
    E_CLD_WINDOWCOVERING_ATTR_ID_INSTALLED_OPEN_LIMIT_TILT_DEGREE,             /* 2.Mandatory if */
    E_CLD_WINDOWCOVERING_ATTR_ID_INSTALLED_CLOSED_LIMIT_TILT_DEGREE,           /* 3.Mandatory if */
    E_CLD_WINDOWCOVERING_ATTR_ID_VELOCITY,                                     /* 4.Optional */
    E_CLD_WINDOWCOVERING_ATTR_ID_ACCELRATION_TIME_LIFT,                        /* 5.Optional */
    E_CLD_WINDOWCOVERING_ATTR_ID_DECELRATION_TIME_LIFT,                        /* 6.Optional */
    E_CLD_WINDOWCOVERING_ATTR_ID_MODE,                                         /* 7.Mandatory */
    E_CLD_WINDOWCOVERING_ATTR_ID_INTERMEDIATE_SETPOINTS_LIFT,                  /* 8.Optional */
    E_CLD_WINDOWCOVERING_ATTR_ID_INTERMEDIATE_SETPOINTS_TILT,                  /* 9.Optional */
} teCLD_WindowCovering_Cluster_AttrID;

/* Window Covering Type */
typedef enum
{
    E_CLD_WINDOWCOVERING_WINDOW_COVERING_TYPE_ROLLERSHADE  = 0x00,
    E_CLD_WINDOWCOVERING_WINDOW_COVERING_TYPE_ROLLERSHADE_2_MOTOR,
    E_CLD_WINDOWCOVERING_WINDOW_COVERING_TYPE_ROLLERSHADE_EXTERIOR,
    E_CLD_WINDOWCOVERING_WINDOW_COVERING_TYPE_ROLLERSHADE_EXTERIOR_2_MOTOR,
    E_CLD_WINDOWCOVERING_WINDOW_COVERING_TYPE_DRAPERY,
    E_CLD_WINDOWCOVERING_WINDOW_COVERING_TYPE_AWNING,
    E_CLD_WINDOWCOVERING_WINDOW_COVERING_TYPE_SHUTTER,
    E_CLD_WINDOWCOVERING_WINDOW_COVERING_TYPE_TILT_BLIND_TILT_ONLY,
    E_CLD_WINDOWCOVERING_WINDOW_COVERING_TYPE_TILT_BLIND_TILT_AND_LIFT,
    E_CLD_WINDOWCOVERING_WINDOW_COVERING_TYPE_PROJECTOR_SCREEN,
    E_CLD_WINDOWCOVERING_WINDOW_COVERING_TYPE_UNDEFINED         = 0xFF
} teCLD_WindowCovering_WindowCoveringType;

/* Window Covering Cluster */
typedef struct
{
    zuint16                    u16ClusterRevision;
} tsCLD_WindowCovering;

/* Go To (Tilt|Lift) Value - Command request payload */
typedef struct
{
    uint16                    u16Value;
} tsCLD_WindowCovering_GoToValueRequestPayload;

/* Go To (Tilt|Lift) Percentage - Command request payload */
typedef struct
{
    uint8                    u8Percentage;
} tsCLD_WindowCovering_GoToPercentageRequestPayload;

typedef struct
{
    zenum8                  eStatus;
}tsCLD_WindowCovering_DefaultResponsePayload;

/* Definition of Window Covering Callback Event Structure */
typedef struct
{
    uint8                           u8CommandId;
        union
    {
        tsCLD_WindowCovering_DefaultResponsePayload            *psDefaultResponsePayload;
    } uMessage;
} tsCLD_WindowCoveringCallBackMessage;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC teZCL_Status eCLD_WindowCoveringCreateWindowCovering(
                tsZCL_ClusterInstance                  *psClusterInstance,
                bool_t                                 bIsServer,
                tsZCL_ClusterDefinition                *psClusterDefinition,
                void                                   *pvEndPointSharedStructPtr,
                uint8                                  *pu8AttributeControlBits);

#ifdef WINDOWCOVERING_CLIENT
PUBLIC teZCL_Status eCLD_WindowCoveringCommandOpenCloseStopRequestSend(
                    uint8                              u8SourceEndPointId,
                    uint8                           u8DestinationEndPointId,
                    tsZCL_Address                   *psDestinationAddress,
                    uint8                           *pu8TransactionSequenceNumber,
                    teCLD_WindowCovering_CommandID          eCommand);

PUBLIC  teZCL_Status  eCLD_WindowCoveringCommandGotoValueRequestSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    teCLD_WindowCovering_CommandID     eCommand,
                    tsCLD_WindowCovering_GoToValueRequestPayload *psPayload);

PUBLIC  teZCL_Status  eCLD_WindowCoveringCommandGotoPercentageRequestSend(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8DestinationEndPointId,
                    tsZCL_Address               *psDestinationAddress,
                    uint8                       *pu8TransactionSequenceNumber,
                    teCLD_WindowCovering_CommandID     eCommand,
                    tsCLD_WindowCovering_GoToPercentageRequestPayload *psPayload);
#endif

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

extern tsZCL_ClusterDefinition sCLD_WindowCovering;
extern const tsZCL_AttributeDefinition asCLD_WindowCoveringClusterAttributeDefinitions[];
extern uint8 au8WindowCoveringAttributeControlBits[];
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* WINDOWCOVERING_H */
