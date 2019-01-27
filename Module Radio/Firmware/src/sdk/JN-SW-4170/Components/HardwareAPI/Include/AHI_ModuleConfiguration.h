/****************************************************************************
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

#ifndef AHI_MODULE_CONF_H 
#define AHI_MODULE_CONF_H

#if defined __cplusplus 
extern "C" { 
#endif 

/****************************************************************************/ 
/*** Include Files ***/ 
/****************************************************************************/ 
#include <jendefs.h>

/****************************************************************************/ 
/*** Macro Definitions ***/ 
/****************************************************************************/ 

/****************************************************************************/ 
/*** Type Definitions ***/ 
/****************************************************************************/ 

/* Enumerated type to indicate the module configuration to use. Enumeration
   names are of the form E_MODULE_xxx_yyy or E_MODULE_xxx_yyy_zzz where:
     xxx is the hardware module name (JN5168_001_M00, JN5179_001_M16, etc.)
     yyy is the region:
       ETSI      For Europe
       FCC       For USA
       ETSI_FCC  Configuration is suitable for both Europe and USA
     zzz is a module-specific conifiguration option:
       LNA_BYPASS  For JN5179_001_M16 only, the LNA on the RX path is bypassed;
                   note that an IO input to the module must also be driven low
                   to enable this mode, which is outside the scope of this API

   The E_MODULE_DEFAULT enumeration is a generic enumeration which is 
   equivalent to the most stringent compliance limits for a module without an 
   external amplifier. The mapping to the specific configurations for each 
   supported chip is:
     JN5161/4/8    E_MODULE_JN5168_001_M00_ETSI_FCC
     JN5169        E_MODULE_JN5169_001_M00_FCC
     JN5171/4/8/9  E_MODULE_JN5179_001_M10_FCC
 */                
typedef enum
{
    E_MODULE_DEFAULT = 0,
#if (defined JENNIC_CHIP_FAMILY_JN516x) && !(defined JENNIC_CHIP_JN5169)
    E_MODULE_JN5168_001_M00_ETSI_FCC = 0x10,
    E_MODULE_JN5168_001_M03_ETSI_FCC,
    E_MODULE_JN5168_001_M05_ETSI,
    E_MODULE_JN5168_001_M06_FCC,
#elif (defined JENNIC_CHIP_JN5169)
    E_MODULE_JN5169_001_M00_ETSI = 0x20,
    E_MODULE_JN5169_001_M03_ETSI,
    E_MODULE_JN5169_001_M00_FCC,
    E_MODULE_JN5169_001_M03_FCC,
    E_MODULE_JN5169_001_M06_FCC,
#elif (defined JENNIC_CHIP_FAMILY_JN517x)
    E_MODULE_JN5179_001_M10_ETSI = 0x30,
    E_MODULE_JN5179_001_M13_ETSI,
    E_MODULE_JN5179_001_M10_FCC,
    E_MODULE_JN5179_001_M13_FCC,
    E_MODULE_JN5179_001_M16_FCC,
    E_MODULE_JN5179_001_M16_FCC_LNA_BYPASS
#endif
} teModule;

/****************************************************************************/ 
/*** Exported Functions ***/ 
/****************************************************************************/ 
PUBLIC void vAHI_ModuleConfigure(teModule eModule);

/****************************************************************************/ 
/*** Exported Variables ***/ 
/****************************************************************************/ 


#if defined __cplusplus
}
#endif 

#endif /* AHI_MODULE_CONF_H */ 

/****************************************************************************/ 
/*** END OF FILE ***/ 
/****************************************************************************/
