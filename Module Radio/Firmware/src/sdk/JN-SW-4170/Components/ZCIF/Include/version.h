/*****************************************************************************
 *
 * MODULE:             n/a
 *
 * COMPONENT:          version.template
 *
 * AUTHOR:             MRW
 *
 * DESCRIPTION:        *** Note that this version is a manually generated file. It should never appear
 * in a released build because the release script overwrites this file.  It is only included to allow the ZCL
 * to be built from a clean checkout rather than an unzip of a release. <<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 * $HeadURL: http://svn/sware/Projects/Cortex/Modules/PWRM/Trunk/Source/version.template $
 *
 * $Revision: 1994 $
 *
 * $LastChangedBy: mwild $
 *
 * $LastChangedDate: 2008-07-09 11:49:02 +0100 (Wed, 09 Jul 2008) $
 *
 * $Id: version.template 1994 2008-07-09 10:49:02Z mwild $
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

#ifndef _VERSION_H_
#define _VERSION_H_

#if defined __cplusplus
extern "C" {
#endif
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#define SVN_VERSION         (0x40000000UL|0x80000000UL|9999UL)  // These values are overwritten by the release script
#define SVN_VERSIONSTR      "UNCONTROLLED"                      // But not when building from a checkout.
#define SVN_REVDATESTR      "UNCONTROLLED"                      // UNCONTROLLED should be replaced by the svn information when using version.h from a release.zip
#define SVN_BUILDDATESTR    "UNCONTROLLED"

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
}
#endif

#endif /*_VESRION_H_*/

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
