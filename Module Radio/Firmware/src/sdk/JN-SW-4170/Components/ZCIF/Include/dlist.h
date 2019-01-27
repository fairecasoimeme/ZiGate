/*****************************************************************************
 *
 * MODULE:             Smart Energy
 *
 * COMPONENT:          dlist.h
 *
 * AUTHOR:             we1
 *
 * DESCRIPTION:       Doubly Linked list definitions
 *
 * $HeadURL: https://www.collabnet.nxp.com/svn/lprf_sware/Projects/Components/ZCL/Branches/Zigbee_3_0/Include/dlist.h $
 *
 * $Revision: 66071 $
 *
 * $LastChangedBy: nxp58432 $
 *
 * $LastChangedDate: 2014-11-27 17:06:41 +0530 (Thu, 27 Nov 2014) $
 *
 * $Id: dlist.h 66071 2014-11-27 11:36:41Z nxp58432 $
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

#ifndef DLIST_H_INCLUDED
#define DLIST_H_INCLUDED

#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

#include "jendefs.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/* DLNODE - Doubly linked-list node */
typedef struct tagDNODE DNODE;

struct tagDNODE
{
  DNODE *psNext;
  DNODE *psPrevious;
};

/* DLIST - Doubly-linked-list header */
typedef struct tagDLIST 
{
  DNODE *psFirst;  /* First node in list (Points to NULL if none) */
  DNODE *psLast;   /* Last node in list (Points to NULL if none) */
} DLIST;

typedef bool (boDLISTtest)(void *pvSearchParam, void *psNodeUnderTest);

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/* Linked-list initialisation */
PUBLIC void vDLISTinitialise( DLIST *psList );

/* Search operations */
PUBLIC void *psDLISTgetHead( DLIST *psList );
PUBLIC void *psDLISTgetTail( DLIST *psList );

PUBLIC void *psDLISTgetNext( DNODE *psCurrentNode );
PUBLIC void *psDLISTgetPrevious( DNODE *psCurrentNode );

/* Addition operations */
PUBLIC void vDLISTaddToHead( DLIST *psList, DNODE *psNewNode );
PUBLIC void vDLISTinsertBefore( DLIST  *psList,
                                DNODE *psCurrentNode,
                                DNODE *psNewNode);
PUBLIC void vDLISTinsertAfter( DLIST  *psList,
                               DNODE *psCurrentNode,
                               DNODE *psNewNode);
PUBLIC void vDLISTaddToTail( DLIST *psList, DNODE *psNewNode );

/* Removal operations */
PUBLIC DNODE *psDLISTremove( DLIST *psList, DNODE *psNode );
PUBLIC DNODE *psDLISTremoveFromTail( DLIST *psList );
PUBLIC DNODE *psDLISTremoveFromHead( DLIST *psList );

/* Searching operations */
extern PUBLIC void *psDLISTsearchFromHead( DLIST *psList,
                                            boDLISTtest *prTest,
                                            void *pvSearchElement);
extern PUBLIC void *psDLISTsearchForward( DNODE *psCurrentNode,
                                           boDLISTtest *prTest,
                                           void *pvSearchElement);
extern PUBLIC void *psDLISTsearchBackward( DNODE *psCurrentNode,
                                            boDLISTtest *prTest,
                                            void *pvSearchElement);
extern PUBLIC void *psDLISTsearchFromTail( DLIST *psList,
                                            boDLISTtest *prTest,
                                            void *pvSearchElement);

/* Status operations */
PUBLIC int iDLISTnumberOfNodes( DLIST *psList );
PUBLIC bool boDLISTisEmpty( DLIST *psList );

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* DLIST_H_INCLUDED */

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
