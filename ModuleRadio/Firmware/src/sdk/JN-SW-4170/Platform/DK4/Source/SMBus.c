/****************************************************************************
 *
 * MODULE:             SMBus functions
 * DESCRIPTION:
 * A set of functions to communicate with devices on the SMBus
*/
/****************************************************************************
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

* Copyright NXP B.V. 2012. All rights reserved
*
***************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/

#include <jendefs.h>
#include <AppHardwareApi.h>

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

PRIVATE bool_t bSMBusWait(void);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/

PUBLIC void vSMBusInit(void)
{

	/* run bus at 400KHz */
	vAHI_SiConfigure(TRUE, FALSE, 31);

}


PUBLIC bool_t bSMBusWrite(uint8 u8Address, uint8 u8Command, uint8 u8Length, uint8* pu8Data)
{

	bool_t bCommandSent = FALSE;

	/* Send address with write bit set */
	vAHI_SiWriteSlaveAddr(u8Address, E_AHI_SI_SLAVE_RW_SET);

	vAHI_SiSetCmdReg(E_AHI_SI_START_BIT,
					 E_AHI_SI_NO_STOP_BIT,
					 E_AHI_SI_NO_SLAVE_READ,
					 E_AHI_SI_SLAVE_WRITE,
					 E_AHI_SI_SEND_ACK,
					 E_AHI_SI_NO_IRQ_ACK);

	if(!bSMBusWait()) return(FALSE);

	while(bCommandSent == FALSE || u8Length > 0){

		if(!bCommandSent){

			/* Send command byte */
			vAHI_SiWriteData8(u8Command);
			bCommandSent = TRUE;

		} else {

			u8Length--;

			/* Send data byte */
			vAHI_SiWriteData8(*pu8Data++);

		}

		/*
		 * If its the last byte to be sent, send with
		 * stop sequence set
		 */
		if(u8Length == 0){

			vAHI_SiSetCmdReg(E_AHI_SI_NO_START_BIT,
							 E_AHI_SI_STOP_BIT,
							 E_AHI_SI_NO_SLAVE_READ,
							 E_AHI_SI_SLAVE_WRITE,
							 E_AHI_SI_SEND_ACK,
							 E_AHI_SI_NO_IRQ_ACK);

		} else {

			vAHI_SiSetCmdReg(E_AHI_SI_NO_START_BIT,
							 E_AHI_SI_NO_STOP_BIT,
							 E_AHI_SI_NO_SLAVE_READ,
							 E_AHI_SI_SLAVE_WRITE,
							 E_AHI_SI_SEND_ACK,
							 E_AHI_SI_NO_IRQ_ACK);

		}

		if(!bSMBusWait()) return(FALSE);

	}

	return(TRUE);

}


PUBLIC bool_t bSMBusRandomRead(uint8 u8Address, uint8 u8Command, uint8 u8Length, uint8* pu8Data)
{

	/* Send address with write bit set */
	vAHI_SiWriteSlaveAddr(u8Address, !E_AHI_SI_SLAVE_RW_SET);

	vAHI_SiSetCmdReg(E_AHI_SI_START_BIT,
					 E_AHI_SI_NO_STOP_BIT,
					 E_AHI_SI_NO_SLAVE_READ,
					 E_AHI_SI_SLAVE_WRITE,
					 E_AHI_SI_SEND_ACK,
					 E_AHI_SI_NO_IRQ_ACK);

	if(!bSMBusWait()) return(FALSE);


	/* Send command byte */
	vAHI_SiWriteData8(u8Command);
	vAHI_SiSetCmdReg(E_AHI_SI_NO_START_BIT,
					 E_AHI_SI_NO_STOP_BIT,
					 E_AHI_SI_NO_SLAVE_READ,
					 E_AHI_SI_SLAVE_WRITE,
					 E_AHI_SI_SEND_ACK,
					 E_AHI_SI_NO_IRQ_ACK);

	if(!bSMBusWait()) return(FALSE);



	while(u8Length > 0){

		u8Length--;

		/*
		 * If its the last byte to be sent, send with
		 * stop sequence set
		 */
		if(u8Length == 0){

			vAHI_SiSetCmdReg(E_AHI_SI_NO_START_BIT,
							 E_AHI_SI_STOP_BIT,
							 E_AHI_SI_SLAVE_READ,
							 E_AHI_SI_NO_SLAVE_WRITE,
							 E_AHI_SI_SEND_NACK,
							 E_AHI_SI_NO_IRQ_ACK);

		} else {

			vAHI_SiSetCmdReg(E_AHI_SI_NO_START_BIT,
							 E_AHI_SI_NO_STOP_BIT,
							 E_AHI_SI_NO_SLAVE_READ,
							 E_AHI_SI_SLAVE_WRITE,
							 E_AHI_SI_SEND_ACK,
							 E_AHI_SI_NO_IRQ_ACK);

		}

		while(bAHI_SiPollTransferInProgress()); /* busy wait */

		*pu8Data++ = u8AHI_SiReadData8();

	}

	return(TRUE);

}


PUBLIC bool_t bSMBusSequentialRead(uint8 u8Address, uint8 u8Length, uint8* pu8Data)
{

	/* Send address with write bit set */
	vAHI_SiWriteSlaveAddr(u8Address, !E_AHI_SI_SLAVE_RW_SET);

	vAHI_SiSetCmdReg(E_AHI_SI_START_BIT,
					 E_AHI_SI_NO_STOP_BIT,
					 E_AHI_SI_NO_SLAVE_READ,
					 E_AHI_SI_SLAVE_WRITE,
					 E_AHI_SI_SEND_ACK,
					 E_AHI_SI_NO_IRQ_ACK);

	if(!bSMBusWait()) return(FALSE);


	while(u8Length > 0){

		u8Length--;

		/*
		 * If its the last byte to be sent, send with
		 * stop sequence set
		 */
		if(u8Length == 0){

			vAHI_SiSetCmdReg(E_AHI_SI_NO_START_BIT,
							 E_AHI_SI_STOP_BIT,
							 E_AHI_SI_SLAVE_READ,
							 E_AHI_SI_NO_SLAVE_WRITE,
							 E_AHI_SI_SEND_NACK,
							 E_AHI_SI_NO_IRQ_ACK);

		} else {

			vAHI_SiSetCmdReg(E_AHI_SI_NO_START_BIT,
							 E_AHI_SI_NO_STOP_BIT,
							 E_AHI_SI_SLAVE_READ,
							 E_AHI_SI_NO_SLAVE_WRITE,
							 E_AHI_SI_SEND_ACK,
							 E_AHI_SI_NO_IRQ_ACK);

		}

		while(bAHI_SiPollTransferInProgress()); /* busy wait */

		*pu8Data++ = u8AHI_SiReadData8();

	}

	return(TRUE);

}


/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

PRIVATE bool_t bSMBusWait(void)
{

	while(bAHI_SiPollTransferInProgress()); /* busy wait */

	if (bAHI_SiPollArbitrationLost() | bAHI_SiPollRxNack())	{

		/* release bus & abort */
		vAHI_SiSetCmdReg(E_AHI_SI_NO_START_BIT,
						 E_AHI_SI_STOP_BIT,
						 E_AHI_SI_NO_SLAVE_READ,
						 E_AHI_SI_SLAVE_WRITE,
						 E_AHI_SI_SEND_ACK,
						 E_AHI_SI_NO_IRQ_ACK);
		return(FALSE);
	}

	return(TRUE);

}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
