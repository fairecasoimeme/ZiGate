/****************************************************************************
 *
 * MODULE:             Driver for Sensirion SHT1x humidity and temp sensor
 *
 * DESCRIPTION:
 * Provides API for driving Sensirion SHT1x humidity and temp sensor.
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
#include "jendefs.h"
#include "HtsDriver.h"
#include "AppHardwareApi.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define vClearClock()         vAHI_DioSetOutput(0, HTS_CLK_DIO_BIT_MASK)
#define vSetClock()           vAHI_DioSetOutput(HTS_CLK_DIO_BIT_MASK, 0)
#define vClearData()          vAHI_DioSetOutput(0, HTS_DATA_DIO_BIT_MASK)
#define vSetData()            vAHI_DioSetOutput(HTS_DATA_DIO_BIT_MASK, 0)
#define vClearDataDirection() vAHI_DioSetDirection(HTS_DATA_DIO_BIT_MASK, 0)
#define vSetDataDirection()   vAHI_DioSetDirection(0, HTS_DATA_DIO_BIT_MASK)

#define HTS_SOFT_RESET    (0x1e)
#define HTS_READ_TEMP     (0x03)
#define HTS_READ_HUMIDITY (0x05)
#define HTS_WRITE_STATUS  (0x06)

#define WITH_ACK          (TRUE)
#define NO_ACK            (FALSE)
#define HTS_TIMEOUT       (3000000)

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
PRIVATE void   vStartSequence(void);
PRIVATE void   vSendByte(uint8 u8Val);
PRIVATE uint8  u8ReadByte(bool_t boAck);
PRIVATE void   vStartReadMeasurement(uint8 u8Command);
PRIVATE uint16 u16ReadMeasurementResult(void);
PRIVATE void   vWait(int iWait);
PRIVATE void   vWriteStatus(uint8 u8Status);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 *
 * NAME: vHTSreset
 *
 * DESCRIPTION:
 * Sets up the DIO pins used by the sensor and resets it.
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void vHTSreset(void)
{
    int i;

    /* Set DIO lines */
    vClearClock();
    vClearData();
    vSetDataDirection();
    vAHI_DioSetDirection(0, HTS_CLK_DIO_BIT_MASK);

    /* Connection reset sequence */
    vSetData();
    for (i = 0; i < 9; i++)
    {
        vSetClock();
        vWait(1);
        vClearClock();
        vWait(1);
    }

    /* Soft reset device */
    vStartSequence();
    vSendByte(HTS_SOFT_RESET);

    /* Wait for minimum 11ms after reset */
    vWait(1000);

    /* Write status */
    vWriteStatus(1);

    vClearDataDirection();
}

/****************************************************************************
 *
 * NAME: vHTSstartReadTemp
 *
 * DESCRIPTION:
 * Wrapper to start a read of the temperature sensor.
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void vHTSstartReadTemp(void)
{
    vStartReadMeasurement(HTS_READ_TEMP);
}

/****************************************************************************
 *
 * NAME: u16HTSreadTempResult
 *
 * DESCRIPTION:
 * Wrapper to read a measurement, followed by a conversion function to work
 * out the value in degrees Celcius.
 *
 * RETURNS:
 * uint16: temperature in degrees Celcius
 *
 * NOTES:
 * We use 12 bit conversion for temperature, for speed. The formula, taken
 * from the SHT1x datasheet and for a device powered at 3V, is:
 *    temp (degrees C) = 0.04 * ReadValue - 39.6
 *
 * Currently only positive values are allowed. A negative temperature will
 * result in a large positive value.
 *
 ****************************************************************************/
PUBLIC uint16 u16HTSreadTempResult(void)
{
    uint32 u32Result;

    u32Result = (uint32)u16ReadMeasurementResult();

    u32Result = u32Result * 41 - 40550;

    return (uint16)(u32Result / 1024);
}

/****************************************************************************
 *
 * NAME: vHTSstartReadHumidity
 *
 * DESCRIPTION:
 * Wrapper to start a read of the humidity sensor.
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PUBLIC void vHTSstartReadHumidity(void)
{
    vStartReadMeasurement(HTS_READ_HUMIDITY);
}

/****************************************************************************
 *
 * NAME:
 *
 * DESCRIPTION:
 * Wrapper to read a measurement, followed by a conversion function to work
 * out the value as a percentage.
 *
 * RETURNS:
 * uint16: relative humidity as a percentage
 *
 * NOTES:
 * We use 8 bit conversion for humidity, for speed. The formula, taken
 * from the SHT1x datasheet, is:
 *    humidity (%) = 0.648 * ReadValue - 4
 *
 ****************************************************************************/
PUBLIC uint16 u16HTSreadHumidityResult(void)
{
    uint32 u32Result;

    u32Result = (uint32)u16ReadMeasurementResult();

    u32Result = u32Result * 1327 - 8192;

    return (uint16)(u32Result >> 11);
}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/
/****************************************************************************
 *
 * NAME: vStartSequence
 *
 * DESCRIPTION:
 * Implements the combination of clock and data logic levels to initiate a
 * communication sequence with the sensor.
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void vStartSequence(void)
{
    vSetDataDirection();

    vSetData();
    vClearClock();
    vWait(1);
    vSetClock();
    vWait(1);
    vClearData();
    vClearClock();
    vWait(3);
    vSetClock();
    vSetData();
    vWait(1);
    vClearClock();
}

/****************************************************************************
 *
 * NAME: vSendByte
 *
 * DESCRIPTION:
 * Implements the combination of clock and data logic levels to send a byte
 * of data to the sensor.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u8Val           R   Byte to send
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void vSendByte(uint8 u8Val)
{
    uint8 i;

    vSetDataDirection();

    /* Send byte, MSB first */
    for (i = 128; i > 0; i >>= 1)
    {
        if (u8Val & i)
        {
            vSetData();
        }
        else
        {
            vClearData();
        }
        vSetClock();
        vWait(1);
        vClearClock();
        vWait(1);
    }

    /* Get ack */
    vClearDataDirection();
    vSetClock();
    vWait(1);

    /* Can read ack here */

    vClearClock();
}

/****************************************************************************
 *
 * NAME: u8ReadByte
 *
 * DESCRIPTION:
 * Implements the combination of clock and data logic levels to read a byte
 * of data from the sensor.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  boAck           R   WITH_ACK to send an ack after the data
 *
 * RETURNS:
 * uint8: data received from sensor
 *
 ****************************************************************************/
PRIVATE uint8 u8ReadByte(bool_t boAck)
{
    uint8 i;
    uint8 u8Result = 0;

    vClearDataDirection();

    /* Get byte */
    for (i = 128; i > 0; i >>= 1)
    {
        vSetClock();
        vWait(1);
        if (u32AHI_DioReadInput() & HTS_DATA_DIO_BIT_MASK)
        {
            u8Result |= i;
        }
        vClearClock();
        vWait(1);
    }

    if (boAck == WITH_ACK)
    {
        vClearData();
    }
    else
    {
        vSetData();
    }

    vSetDataDirection();
    vSetClock();
    vWait(1);
    vClearClock();
    vSetData();

    return u8Result;
}

/****************************************************************************
 *
 * NAME: vStartReadMeasurement
 *
 * DESCRIPTION:
 * Sequence required to initiate a read from the sensor.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u8Command       R   Command to send to sensor
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void vStartReadMeasurement(uint8 u8Command)
{
    /* Send command */
    vStartSequence();
    vSendByte(u8Command);

    /* Wait for ready from device: this will always take at least 11ms */
    vClearDataDirection();
    vWait(50);
}

/****************************************************************************
 *
 * NAME: u16ReadMeasurementResult
 *
 * DESCRIPTION:
 * Sequence required to read a result from the sensor. If the sensor is not
 * ready when the function is entered, it sits in a loop until either the
 * sensor has finished or a simple watchdog timeout has timed out.
 *
 * If a value can be read, it is returned as a 16 bit value.
 *
 * RETURNS:
 * uint16: result received, or 65534 if no result
 *
 ****************************************************************************/
PRIVATE uint16 u16ReadMeasurementResult(void)
{
    int iTimeout;
    uint16 u16Result;

    iTimeout = 0;
    while ((iTimeout < HTS_TIMEOUT)
           && ((u32AHI_DioReadInput() & HTS_DATA_DIO_BIT_MASK) != 0))
    {
        iTimeout++;
    }

    if (iTimeout == HTS_TIMEOUT)
    {
        vHTSreset();
        return 65534;
    }

    u16Result = (uint16)u8ReadByte(WITH_ACK);
    u16Result = (u16Result << 8) | (uint16)u8ReadByte(NO_ACK);

    vClearDataDirection();
    return u16Result;
}

/****************************************************************************
 *
 * NAME: vWait
 *
 * DESCRIPTION:
 * Waits by looping around for the specified number of iterations.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  iWait           R   Number of iterations to wait for
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void vWait(int iWait)
{
    volatile int i;
    for (i = 0; i < iWait; i++);
}

/****************************************************************************
 *
 * NAME: vWriteStatus
 *
 * DESCRIPTION:
 * Sequence to write a status byte to the sensor.
 *
 * PARAMETERS:      Name            RW  Usage
 *                  u8Status        R   Status value to write
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void vWriteStatus(uint8 u8Status)
{
    vStartSequence();
    vSendByte(HTS_WRITE_STATUS);
    vSendByte(u8Status);
}

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
