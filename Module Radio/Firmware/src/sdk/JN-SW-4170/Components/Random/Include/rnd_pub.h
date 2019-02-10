
/*****************************************************************************
 *
 * MODULE:             RND
 *
 * COMPONENT:          rnd_pub.h
 *
 * AUTHOR:             rcc
 *
 * DESCRIPTION:        Random number generator
 *
 *
 * $HeadURL:  $
 *
 * $Revision: $
 *
 * $LastChangedBy:  $
 *
 * $LastChangedDate:  $
 *
 * $Id:  $
 *
 *****************************************************************************
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
 * Copyright Jennic Ltd. 2007 All rights reserved
 *
 ****************************************************************************/


#ifndef RND_PUB_H_INCLUDED
#define RND_PUB_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/***********************/
/**** INCLUDE FILES ****/
/***********************/

#include "jendefs.h"

/**
 * @defgroup RND Random Number Generator
 * \n<b>Random number generator</b>
 *
 * We can either use the functions \p srand() and \p rand(), if we have the C
 * standard library available, or we use our own which is entirely contained
 * in this file. To use the C standard library version, make sure
 * \p USE_STDLIB_RAND is defined either externally or at the top of this file.
 *
 * Our own version uses the very simple Linear Congruential method, which is
 * not perfect, but will suffice for Inquiry Scan backoffs and Periodic
 * Inquiry Mode.
 *
 * The random number s is calculated as:
 *
 * <KBD>
 * x[n+1] = (Ax[n] + C) % M
 * </KBD>
 *
 * where \p % is the modulo operator, and \p n is the iterator.
 *
 * \p x[0] must be seeded with an appropriate prime, The coefficients \p A and
 * \p C must be chosen to give an even spread of numbers. The coefficent \p M
 * gives the effective range.
 *
 * I have arbitrarily picked:
 *
 * - \p seed = 629
 * - \p A    = 5
 * - \p C    = 11
 *
 * We require \p M to be 65536 to give us the maximum possible range for the
 * \p uint16 random number we require (note that \p uint32 is returned more
 * for convenience in case we need to update this)
 *
 * The resultant number is then scaled and offset to give a number in the
 * required range.
 *
 * Running this through a test gave an even spread of numbers throughout the
 * range, thus satisfying the requirement.
 *
 * See Knuth, The Art Of Computer Programming, Vol. 2 for a detailed
 * discussion of random number generation.
 */

/************************/
/**** MACROS/DEFINES ****/
/************************/

/**************************/
/**** TYPE DEFINITIONS ****/
/**************************/

/**** Elemental types ****/

/**** Parameters ****/

/**** Objects ****/

/****************************/
/**** EXPORTED VARIABLES ****/
/****************************/

/****************************/
/**** EXPORTED FUNCTIONS ****/
/****************************/

/* Init methods */
PUBLIC void
RND_vInit(uint32 u32Seed);

#ifndef RND_256_ONLY
/* Get number */
PUBLIC uint32
RND_u32GetRand(uint32 u32Min,
               uint32 u32Max);
#endif

/* Get number */
PUBLIC uint32
RND_u32GetRand256(void);

#ifdef __cplusplus
};
#endif

#endif /* RND_PUB_INCLUDED */

/* End of file $RCSfile: rnd_pub.h,v $ *******************************************/

/****************************************************************************
 *
 * CHANGE HISTORY:
 *
 * $Log: rnd_pub.h,v $
 * Revision 1.3  2008/11/28 17:27:52  dclar
 * changed coefficients gives a better spread of numbers
 *
 * Revision 1.2  2004/03/25 09:33:35  rcc
 * Added 0-255 only fn, improving efficiency
 *
 * Revision 1.1.1.1  2003/07/15 08:51:47  rcc
 * Initial checkin
 *
 *
 ****************************************************************************/
