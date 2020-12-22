/*****************************************************************************
 *
 * MODULE:             Debug tracing uart driver
 *
 * DESCRIPTION:        Provide output to either if the UARTs
 *
 ****************************************************************************
 *
 * This software is owned by NXP B.V. and/or its supplier and is protected
 * under applicable copyright laws. All rights are reserved. We grant You,
 * and any third parties, a license to use this software solely and
 * exclusively on NXP products [NXP Microcontrollers such as JN5148, JN5142, JN5139]. 
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
 * Copyright NXP B.V. 2012. All rights reserved
 *
 ***************************************************************************/

#ifndef DBG_UART_H_
#define DBG_UART_H_

/****************************************************************************/
/***        Include Files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include "dbg.h"
#include "AppHardwareApi.h"


#if defined __cplusplus
extern "C" {
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

#ifndef DBG_ENABLE
#define DBG_vUartInit(eUart, eBaudRate)
#define DBG_vUartInitHardware()
#define DBG_vUartPutch(c)
#define DBG_vUartFlush()
#define DBG_vUartFailedAssert()
#define DBG_iUartGetChar() (-1)
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum
{
    DBG_E_UART_0,
    DBG_E_UART_1

} DBG_teUart;

typedef enum
{
    DBG_E_UART_BAUD_RATE_4800,
    DBG_E_UART_BAUD_RATE_9600,
    DBG_E_UART_BAUD_RATE_19200,
    DBG_E_UART_BAUD_RATE_38400,
    DBG_E_UART_BAUD_RATE_76800,
    DBG_E_UART_BAUD_RATE_115200

} DBG_teUartBaudRate;

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

#ifdef DBG_ENABLE
PUBLIC void DBG_vUartInit(DBG_teUart eUart, DBG_teUartBaudRate eBaudRate);

PUBLIC void DBG_vUartInitHardware(void);
PUBLIC void DBG_vUartPutch(char c);
PUBLIC void DBG_vUartFlush(void);
PUBLIC void DBG_vUartFailedAssert(void);
PUBLIC int  DBG_iUartGetChar(void);
#endif

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

#if defined __cplusplus
};
#endif

#endif /*DBG_UART_H_*/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
