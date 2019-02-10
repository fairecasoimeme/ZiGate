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

/****************************************************************************/
/*** Include files ***/ 
/****************************************************************************/ 
#include <jendefs.h> 
#include "AppApi.h"
#include "AppHardwareApi.h"
#include "AHI_ModuleConfiguration.h"

/****************************************************************************/ 
/*** Macro Definitions ***/ 
/****************************************************************************/ 

/****************************************************************************/ 
/*** Type Definitions ***/ 
/****************************************************************************/ 

/****************************************************************************/ 
/*** Local Function Prototypes ***/ 
/****************************************************************************/ 

/****************************************************************************/ 
/*** Exported Variables ***/ 
/****************************************************************************/ 

/****************************************************************************/ 
/*** Local Variables ***/ 
/****************************************************************************/ 

/****************************************************************************/ 
/*** Exported Functions ***/ 
/****************************************************************************/ 
PUBLIC void vAHI_ModuleConfigure(teModule eModule)
{
    switch (eModule)
    {
#if (defined JENNIC_CHIP_FAMILY_JN516x) && !(defined JENNIC_CHIP_JN5169)

    case E_MODULE_JN5168_001_M00_ETSI_FCC:
    case E_MODULE_JN5168_001_M03_ETSI_FCC:
    case E_MODULE_DEFAULT:
        /* Nothing required: default settings are valid */
        break;
        
    case E_MODULE_JN5168_001_M05_ETSI:
        vAppApiSetHighPowerMode(APP_API_MODULE_HPM05, TRUE);
        break;
        
    case E_MODULE_JN5168_001_M06_FCC:
        vAppApiSetHighPowerMode(APP_API_MODULE_HPM06, TRUE);
        break;
        
#elif (defined JENNIC_CHIP_JN5169)
 
    case E_MODULE_JN5169_001_M00_ETSI:
    case E_MODULE_JN5169_001_M03_ETSI:
        vAppApiSetComplianceLimits(8, 8, 48);
        break;
        
    case E_MODULE_JN5169_001_M00_FCC:
    case E_MODULE_JN5169_001_M03_FCC:
    case E_MODULE_DEFAULT:
        vAppApiSetComplianceLimits(8, 4, 48);
        break;
        
    case E_MODULE_JN5169_001_M06_FCC:
        vAppApiSetComplianceLimits(0, -10, 81);
        vAHI_HighPowerModuleEnable(TRUE, TRUE);
        break;
        
#elif (defined JENNIC_CHIP_FAMILY_JN517x)

    case E_MODULE_JN5179_001_M10_ETSI:
    case E_MODULE_JN5179_001_M13_ETSI:
        vAppApiSetComplianceLimits(8, 8, 48);
        break;
        
    case E_MODULE_JN5179_001_M10_FCC:
    case E_MODULE_JN5179_001_M13_FCC:
    case E_MODULE_DEFAULT:
        vAppApiSetComplianceLimits(8, 0, 48);
        break;
        
    case E_MODULE_JN5179_001_M16_FCC:
        vAppApiSetComplianceLimits(0, -18, 85);
        vAHI_SetDIOpinMultiplexValue(0, 1); /* RFRX on DIO0 */
        vAHI_SetDIOpinMultiplexValue(1, 1); /* RFTX on DIO1 */
        break;
        
    case E_MODULE_JN5179_001_M16_FCC_LNA_BYPASS:
        /* Note that the DIO to enable LNA bypass is not set as part of this
           function, as it is application specific */
        vAppApiSetComplianceLimits(0, -18, 48);
        vAHI_SetDIOpinMultiplexValue(0, 1); /* RFRX on DIO0 */
        vAHI_SetDIOpinMultiplexValue(1, 1); /* RFTX on DIO1 */
        break;
        
#endif
    }
}

/****************************************************************************/ 
/*** Local Functions ***/ 
/****************************************************************************/ 

/****************************************************************************/ 
/*** END OF FILE ***/ 
/****************************************************************************/
