/*****************************************************************************
 *
 * MODULE:             Smart Energy
 *
 * COMPONENT:          zcl_library_options.h
 *
 * AUTHOR:             we1
 *
 * DESCRIPTION:       Internal functions that are needed to build zcl_library_options.h
 *
 * $HeadURL: http://svn/sware/Projects/SmartEnergy/Trunk/ZCL/Source/zcl_internal.h $
 *
 * $Revision: 21492 $
 *
 * $LastChangedBy: dgave $
 *
 * $LastChangedDate: 2009-11-03 10:10:52 +0000 (Tue, 03 Nov 2009) $
 *
 * $Id: zcl_internal.h 21492 2009-11-03 10:10:52Z dgave $
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
 ****************************************************************************/

#ifndef  ZCL_LIBRARY_OPTIONS_H_INCLUDED
#define  ZCL_LIBRARY_OPTIONS_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/
#include "jendefs.h"
#include "dlist.h"
#include "zcl.h"
#include "zcl_heap.h"
#include "zcl_customcommand.h"

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC void vZCL_HandleAttributesReadRequest(
                    ZPS_tsAfEvent              *pZPSevent,
                    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                    tsZCL_ClusterInstance      *psClusterInstance);

PUBLIC void vZCL_HandleAttributesReadResponse(
                    ZPS_tsAfEvent              *pZPSevent,
                    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                    tsZCL_ClusterInstance      *psClusterInstance);

PUBLIC void vZCL_HandleAttributesWriteRequest(
                    ZPS_tsAfEvent              *pZPSevent,
                    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                    tsZCL_ClusterInstance      *psClusterInstance,
                    bool_t                      bIsUndivided,
                    bool_t                      bNoResponse);
PUBLIC void vZCL_HandleAttributesWriteResponse(
                    ZPS_tsAfEvent              *pZPSevent,
                    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                    tsZCL_ClusterInstance      *psClusterInstance);

PUBLIC void vZCL_HandleConfigureReportingCommand(
                    ZPS_tsAfEvent              *pZPSevent,
                    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                    tsZCL_ClusterInstance      *psClusterInstance);

PUBLIC void vZCL_HandleConfigureReportingResponse(
                    ZPS_tsAfEvent              *pZPSevent,
                    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                    tsZCL_ClusterInstance      *psClusterInstance);

PUBLIC void vZCL_HandleReadReportingConfigurationCommand(
                   ZPS_tsAfEvent              *pZPSevent,
                   tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                   tsZCL_ClusterInstance      *psClusterInstance);

PUBLIC void vZCL_HandleReadReportingConfigurationResponse(
                   ZPS_tsAfEvent              *pZPSevent,
                   tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                   tsZCL_ClusterInstance      *psClusterInstance);

PUBLIC void vZCL_HandleAttributesDiscoverRequest(
                    ZPS_tsAfEvent              *pZPSevent,
                    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                    tsZCL_ClusterInstance      *psClusterInstance);

PUBLIC void vZCL_HandleDiscoverAttributesResponse(
                    ZPS_tsAfEvent              *pZPSevent,
                    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                    tsZCL_ClusterInstance      *psClusterInstance);

PUBLIC teZCL_Status eZCL_CreateReportManager(
                    uint8                       u8NumberOfReports,
                    uint16                      u16SystemMinimumReportingInterval,
                    uint16                      u16SystemMaximumReportingInterval);

PUBLIC  void vZCL_HandleDiscoverCommandsReceivedRequest(
                                             ZPS_tsAfEvent              *pZPSevent,
                                             tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                                             tsZCL_ClusterInstance      *psClusterInstance);

PUBLIC  void vZCL_HandleDiscoverCommandsGeneratedRequest(
                                             ZPS_tsAfEvent              *pZPSevent,
                                             tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                                             tsZCL_ClusterInstance      *psClusterInstance);

PUBLIC void vZCL_HandleDiscoverCommandsReceivedResponse(
                                             ZPS_tsAfEvent              *pZPSevent,
                                             tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                                             tsZCL_ClusterInstance      *psClusterInstance);

PUBLIC void vZCL_HandleDiscoverCommandsGeneratedResponse(
                                             ZPS_tsAfEvent              *pZPSevent,
                                             tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                                             tsZCL_ClusterInstance      *psClusterInstance);                                             
                    
PUBLIC void vZCL_HandleAttributesDiscoverExtendedRequest(
                    ZPS_tsAfEvent              *pZPSevent,
                    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                    tsZCL_ClusterInstance      *psClusterInstance);

PUBLIC void vZCL_HandleDiscoverAttributesExtendedResponse(
                    ZPS_tsAfEvent              *pZPSevent,
                    tsZCL_EndPointDefinition   *psZCL_EndPointDefinition,
                    tsZCL_ClusterInstance      *psClusterInstance);    

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
                    
#if defined __cplusplus
}
#endif

#endif  /* ZCL_LIBRARY_OPTIONS_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
