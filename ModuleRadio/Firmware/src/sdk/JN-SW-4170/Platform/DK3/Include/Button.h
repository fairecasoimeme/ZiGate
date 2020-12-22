/****************************************************************************
 *
 * MODULE:             Exposes module for Button driver on DK3 platform
 *
 * COMPONENT:          Button.h
 *
 * VERSION:            R and D Release 6 JAN 2011
 *
 * REVISION:           1.0
 *
 * DATED:              2011/01/07
 *
 * AUTHOR:             mredf
 *
 *
 *
 ****************************************************************************
 *
 * This software is owned by Jennic and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on Jennic products. You, and any third parties must reproduce
 * the copyright and warranty notice and any other legend of ownership on each
 * copy or partial copy of the software.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". JENNIC MAKES NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE,
 * ACCURACY OR LACK OF NEGLIGENCE. JENNIC SHALL NOT, IN ANY CIRCUMSTANCES,
 * BE LIABLE FOR ANY DAMAGES, INCLUDING, BUT NOT LIMITED TO, SPECIAL,
 * INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER.
 *
 * Copyright Jennic Ltd 2010. All rights reserved
 *
 ****************************************************************************/

#ifndef BUTTON_H_
#define BUTTON_H_

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC void vButton_Enable(uint32 u32ButtonMask);
PUBLIC void vButton_Disable(uint32 u32ButtonMask);
PUBLIC uint32 u32Button_Read(void);
PUBLIC uint32 u32Button_Changed(void);
PUBLIC uint32 u32Button_Pressed(void);
PUBLIC uint32 u32Button_Released(void);
PUBLIC uint32 u32Button_Timer(void);

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Inlined Functions                                            ***/
/****************************************************************************/


#endif /*BUTTON_H_*/
