 /*
 * MODULE:      Utils
 *
 * COMPONENT:   appZpsBeaconHandler.c
 *
 * AUTHOR:      nxp29741
 *
 * DESCRIPTION:
 *
 * $HeadURL:  $
 *
 * $Revision:  $
 *
 * $LastChangedBy: nxp29741 $
 *
 * $LastChangedDate: $
 *
 * $Id:  $
 *
 *****************************************************************************
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
 ****************************************************************************/

/***********************/
/**** INCLUDE FILES ****/
/***********************/

#include "appZpsBeaconHandler.h"
#include "mac_sap.h"
#ifdef BEACON_ENABLE
#include "dbg.h"
#endif
/************************/
/**** MACROS/DEFINES ****/
/************************/
/**************************/
/**** TYPE DEFINITIONS ****/
/**************************/
/******************************/
/**** FORWARD DECLARATIONS ****/
/******************************/

/*****************/
/**** IMPORTS ****/
/*****************/
extern uint64 zps_u64NwkLibFromPayload(
    uint8 *pu8Buffer);
/*****************/
/**** EXPORTS ****/
/*****************/

#ifdef APP_PROCESS_BEACON
    extern void vAPPBeaconHandler(MAC_MlmeDcfmInd_s* psBeaconIndication);
#endif
tsBeaconFilterType *psBeaconFilter = NULL;
/**************/
/**** DATA ****/
/**************/

/**** LOCAL SCOPE ****/
PRIVATE bool_t bDiscovery = 0;
/**** MODULE SCOPE ****/

/*************************/
/*************************/
/**** PRIVATE METHODS ****/
/*************************/
/*************************/
/************************/
/************************/
/**** MODULE METHODS ****/
/************************/
/************************/

/************************/
/************************/
/**** PUBLIC METHODS ****/
/************************/
/************************/



/****************************************************************************
 *
 * NAME:       ZPS_bAppAddBeaconFilter
 */
/**
 * @param
 *            tsBeaconFilterType *
 * @return
 *
 * @note
 *
 * Function is called by application to enable filtering
 ****************************************************************************/

PUBLIC void ZPS_bAppAddBeaconFilter(tsBeaconFilterType *psAppBeaconStruct)
{
    psBeaconFilter = psAppBeaconStruct;
}


/****************************************************************************
 *
 * NAME:       ZPS_bAppRemoveBeaconFilter
 */
/**
 * @param
 *
 * @return
 *
 * @note
 * Funcation may be called to disable filtering. It is called from the stack
 * and may be called from the application
 *
 * WARNING DO NOT CHANGE FUNCTION NAME,PARAMETER LIST AND RETURN TYPE
 * THIS IS CALLED FROM THE STACK
 ****************************************************************************/

PUBLIC void ZPS_bAppRemoveBeaconFilter(void)
{
    psBeaconFilter = NULL;
}


/****************************************************************************
 *
 * NAME:       ZPS_bAppPassBeaconToHigherLayer
 */
/**
 * @param
 *            MAC_MlmeDcfmInd_s*
 * @return
 *            boolean
 * @note
 *
 * The function is called from the Zigbee pro stack to indicate beacon
 * notification. It provides a mechanism to be selective on the which beacons
 * we are interested in
 * WARNING DO NOT CHANGE FUNCTION NAME,PARAMETER LIST AND RETURN TYPE
 * THIS IS CALLED FROM THE STACK. THE BODY OF THE FUNCTION MAY BE CHANGED.
 ****************************************************************************/

PUBLIC bool_t ZPS_bAppPassBeaconToHigherLayer(MAC_MlmeDcfmInd_s* psBeaconIndication)
{
    uint8 u8Traverse;
        /* we only want zigbee beacons */
    if((( psBeaconIndication->uParam.sIndBeacon.u8SDUlength > 0) &&
        ( psBeaconIndication->uParam.sIndBeacon.u8SDUlength >= 15) &&
        ( BF_BCN_PL_STACK_PROFILE(psBeaconIndication->uParam.sIndBeacon.u8SDU) == 1 ||
          BF_BCN_PL_STACK_PROFILE(psBeaconIndication->uParam.sIndBeacon.u8SDU) == 2 ) &&
        ( BF_PL_PROTOCOL_VER(psBeaconIndication->uParam.sIndBeacon.u8SDU) == 2) &&
      /*( BF_PL_RESERVED_BITS(psBeaconIndication->uParam.sIndBeacon.u8SDU) == 0) &&*/
        (BF_BCN_PL_PROTOCOL_ID(psBeaconIndication->uParam.sIndBeacon.u8SDU) == 0)))
    {
    #ifdef APP_PROCESS_BEACON
        vAPPBeaconHandler(psBeaconIndication);
    #endif
#ifdef BEACON_ENABLE
        uint32 c = 0;
        extern bool_t bBeaconPrint;
        if(bBeaconPrint)
        {
            DBG_vPrintf(TRUE, "beacon:rx 0x%04x, ", psBeaconIndication->uParam.sIndBeacon.sPANdescriptor.sCoord.u16PanId);
            DBG_vPrintf(TRUE, "AP %x, EP ", BF_GET_ASSOC_PERMIT(psBeaconIndication->uParam.sIndBeacon.sPANdescriptor.u16SuperframeSpec));
            for( c = 3; c < 11; c++)
            {
                DBG_vPrintf ( TRUE, "%02x ", psBeaconIndication->uParam.sIndBeacon.u8SDU [c] );
            }
            DBG_vPrintf ( TRUE , "\n");
        }
#endif
        /*if(bDiscovery == 1)
        {
            vScanDiscoveryOnlyResponse(psBeaconIndication);
            bDiscovery = FALSE;
            return FALSE;
        }*/

        /* Is filter registered */
        if(psBeaconFilter)
        {
            if(psBeaconFilter->u16FilterMap & BF_USED_BITMASK)
            {
                if((psBeaconFilter->u16FilterMap & (BF_BITMAP_BLACKLIST|BF_BITMAP_WHITELIST)) == (BF_BITMAP_BLACKLIST|BF_BITMAP_WHITELIST))
                {
                    return TRUE; /* invalid bitmask pass the upwards*/
                }

                if(psBeaconFilter->u16FilterMap & (BF_BITMAP_BLACKLIST|BF_BITMAP_WHITELIST))
                {
                    for(u8Traverse=0; u8Traverse < psBeaconFilter->u8ListSize; u8Traverse++)
                    {
                        uint64 u64ExtendedPanId = zps_u64NwkLibFromPayload(BF_BCN_PL_EXT_PAN_ID_PTR(psBeaconIndication->uParam.sIndBeacon.u8SDU));

                        if((u64ExtendedPanId == psBeaconFilter->pu64ExtendPanIdList[u8Traverse])
                           && psBeaconFilter->u16FilterMap & BF_BITMAP_BLACKLIST)
                        {
                            return FALSE;
                        }

                        if((u64ExtendedPanId == psBeaconFilter->pu64ExtendPanIdList[u8Traverse])
                            && psBeaconFilter->u16FilterMap & BF_BITMAP_WHITELIST)
                        {
                            break;
                        }
                    }

                    if((psBeaconFilter->u16FilterMap & BF_BITMAP_WHITELIST) &&
                    (u8Traverse == psBeaconFilter->u8ListSize))
                    {
                        return FALSE; /* Not in Whitelist */
                    }
                }

                /*check for any other filters */

                if((psBeaconFilter->u16FilterMap & BF_BITMAP_PERMIT_JOIN))
                {
                    if(BF_GET_ASSOC_PERMIT(psBeaconIndication->uParam.sIndBeacon.sPANdescriptor.u16SuperframeSpec) == 0)
                    {
                        return FALSE; /* Association not permitted */
                    }

                }

                if((psBeaconFilter->u16FilterMap & BF_BITMAP_CAP_ENDDEVICE))
                {
                    if(BF_BCN_PL_ZED_CAPACITY(psBeaconIndication->uParam.sIndBeacon.u8SDU) == 0)
                    {
                        return FALSE;/* no End device capacity  */
                    }
                }

                if((psBeaconFilter->u16FilterMap & BF_BITMAP_CAP_ROUTER))
                {
                    if(BF_BCN_PL_ZR_CAPACITY(psBeaconIndication->uParam.sIndBeacon.u8SDU) == 0)
                    {
                        return FALSE;/* no Router capacity  */
                    }
                }

                if((psBeaconFilter->u16FilterMap & BF_BITMAP_LQI))
                {
                    if(psBeaconIndication->uParam.sIndBeacon.sPANdescriptor.u8LinkQuality < psBeaconFilter->u8Lqi)
                    {
                        return FALSE; /* link quality isn't good enough */
                    }
                }

                if((psBeaconFilter->u16FilterMap & BF_BITMAP_SHORT_PAN))
                {
                    if ( psBeaconIndication->uParam.sIndBeacon.sPANdescriptor.sCoord.u16PanId != psBeaconFilter->u16Panid )
                    {
                        return FALSE; /* Association not permitted */
                    }

                }
                if((psBeaconFilter->u16FilterMap & BF_BITMAP_DEPTH))
                {
                    if(psBeaconFilter->u8Depth == 0xFF)
                    {
                        if((BF_BCN_PL_DEVICE_DEPTH(psBeaconIndication->uParam.sIndBeacon.u8SDU) > 0 ) )
                        {
                            return FALSE; /* Depth is greater than 0 ignore it since we only want to hear from Coordinators */
                        }
                    }
                    
                    if((BF_BCN_PL_DEVICE_DEPTH(psBeaconIndication->uParam.sIndBeacon.u8SDU) >= psBeaconFilter->u8Depth) )
                    {
                        return FALSE; /* depth isn't good enough */
                    }
                }
                /* passed all the filter tests */
                return TRUE;


            }
            else
            {
                return TRUE; /* invalid filter pass the beacon upwards */
            }
        }
        else /* no filter registered pass the beacon upwards */
        {
            return TRUE;
        }

    }

    return FALSE; /* We get here only if not a zigbee beacon,throw the beacon away*/


}

/*Local functions */
/****************************************************************************
 *
 * NAME:       ZPS_bAppDiscoveryReceived
 */
/**
 * @param
 *
 * @return
 *
 * @note
 *
 *
 ****************************************************************************/
PUBLIC void ZPS_bAppDiscoveryReceived(void)
{
    bDiscovery = TRUE;
}

/* End of file $Id: appZpsBeaconHandler.c 2014-01-08 17:21:12Z nxp29741 $ *******************************************/
