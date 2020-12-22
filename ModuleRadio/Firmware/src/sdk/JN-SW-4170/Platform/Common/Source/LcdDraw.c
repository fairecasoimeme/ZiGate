/****************************************************************************
 *
 * MODULE:             LCD Draw
 *
 * DESCRIPTION:
 * Provides API for drawing functions for LCD driver.
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
#include "LcdDriver.h"
#include "LcdDraw.h"

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define MAXDEPTH 100
#define LCD_MIN_X 0
#define LCD_MIN_Y 0
#define LCD_MAX_X 127
#define LCD_MAX_Y 63
#define PUSH(XL, XR, Y, DY) \
    if( sp < stack+MAXDEPTH && Y+(DY) >= LCD_MIN_X && Y+(DY) <= LCD_MAX_Y ) \
    { sp->xl = XL; sp->xr = XR; sp->y = Y; sp->dy = DY; ++sp; }

#define POP(XL, XR, Y, DY) \
    { --sp; XL = sp->xl; XR = sp->xr; Y = sp->y+(DY = sp->dy); }

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
typedef struct { int xl, xr, y, dy; } LINESEGMENT;

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

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
 * NAME: vLcdPlotPoint
 *
 * DESCRIPTION:
 * Plots a single point in standard <x,y> coordinates onto shadow memory.
 * Point is OR'd with existing contents.
 *
 * PARAMETERS:      Name   RW  Usage
 *                  u8X    R   X coordinate of point (0-127)
 *                  u8Y    R   Y coordinate of point (0-63)
 *
 * NOTES:
 * Location in shadow is given by:
 *   u8X + (u8Y / 8) * 128
 * Bit in location is given by:
 *   2^(u8Y % 8)
 ****************************************************************************/
PUBLIC void vLcdPlotPoint(uint8 u8X, uint8 u8Y)
{
    uint16 u16ShadowLocation;
    uint8  u8BitField;

    if ((u8X <= LCD_MAX_X) && (u8Y <= LCD_MAX_Y))
    {
        u16ShadowLocation = u8X + (((uint16)(u8Y & 0x38)) << 4);
        u8BitField = 1 << (u8Y & 7);

        //au8Shadow[u16ShadowLocation] ^= u8BitField;
        au8Shadow[u16ShadowLocation] |= u8BitField;
    }
}

/****************************************************************************
 *
 * NAME: boLcdGetPixel
 *
 * DESCRIPTION:
 * Plots a single point in standard <x,y> coordinates onto shadow memory.
 * Point is OR'd with existing contents.
 *
 * PARAMETERS:      Name   RW  Usage
 *                  u8X    R   X coordinate of point (0-127)
 *                  u8Y    R   Y coordinate of point (0-63)
 *
 * NOTES:
 * Location in shadow is given by:
 *   u8X + (u8Y / 8) * 128
 * Bit in location is given by:
 *   2^(u8Y % 8)
 ****************************************************************************/

PUBLIC bool_t boLcdGetPixel(uint8 u8X, uint8 u8Y)
{
    uint16 u16ShadowLocation;
    uint8  u8BitField;

    if ((u8X < 128)&& (u8Y < 64))
    {
        u16ShadowLocation = u8X + (((uint16)(u8Y & 0x38)) << 4);
        u8BitField = 1 << (u8Y & 7);
        return (au8Shadow[u16ShadowLocation] & u8BitField);

    }
    else
    {
        return (TRUE);
    }
}


/****************************************************************************
 *
 * NAME:       vLcdDrawLine
 */
/**
 * Implements Bresenham's Integer Line Drawing Algoritm
 *
 *
 * @param i32x1     Start X coordinate
 * @param i32y1     Start Y coordinate
 * @param i32x2     End X coordinate
 * @param i32y2     End Y coordinate
 *
 * @return
 *
 * @note
 * This should only be called if it is sure that there is at least one
 * channel left to scan in psScan->u32Channels.
 *
 ****************************************************************************/
PUBLIC void vLcdDrawLine(uint8 u8x1, uint8 u8y1, uint8 u8x2, uint8 u8y2)
{

    int i32CurrentX, i32CurrentY;
    int i32Xinc,     i32Yinc;
    int i32Dx,       i32Dy;
    int i32TwoDx,    i32TwoDy;
    int i32TwoDxAccErr;
    int i32TwoDyAccErr;

    i32Dx       = u8x2 - u8x1;
    i32Dy       = u8y2 - u8y1;
    i32TwoDx    = i32Dx + i32Dx;
    i32TwoDy    = i32Dy + i32Dy;
    i32CurrentX = u8x1;            /*start at (i32x1,i32y1) and move towards (i32x2,i32y2)*/
    i32CurrentY = u8y1;
    i32Xinc     = 1;                /*X and/or Y are incremented/decremented by 1 only */
    i32Yinc     = 1;

    if (i32Dx < 0)
    {
        i32Xinc  = -1; /*  decrement X's  */
        i32Dx    = -i32Dx;
        i32TwoDx = -i32TwoDx;
    }

    if (i32Dy < 0) /*  insure i32Dy >= 0  */
    {
        i32Yinc  = -1;
        i32Dy    = -i32Dy;
        i32TwoDy = -i32TwoDy;
    }

    vLcdPlotPoint(u8x1, u8y1); /* { the first point is a special case } */

    if ((i32Dx !=0) || (i32Dy != 0))  /* are other points on the line ? */
    {
        if (i32Dy <= i32Dx)  /* is the slope <= 1 */
        {
            i32TwoDxAccErr = 0; /* initialize the error */
            do
            {
                i32CurrentX    += i32Xinc;
                i32TwoDxAccErr += i32TwoDy;
                if (i32TwoDxAccErr>i32Dx)
                {
                    i32CurrentY    += i32Yinc;
                    i32TwoDxAccErr -= i32TwoDx;
                }
                vLcdPlotPoint(i32CurrentX, i32CurrentY);  /* process next point  */
            } while (i32CurrentX != u8x2);
        }
        else /* then the slope is large, reverse roles of X & Y */
        {
            i32TwoDyAccErr = 0; /* initialize the error */
            do
            {
                i32CurrentY    += i32Yinc;                 /* consider Y's from i32y1 to i32y2 */
                i32TwoDyAccErr += i32TwoDx;
                if (i32TwoDyAccErr > i32Dy)
                {
                    i32CurrentX    += i32Xinc;
                    i32TwoDyAccErr -= i32TwoDy;
                }
                vLcdPlotPoint(i32CurrentX, i32CurrentY); /* { process next point } */
            } while (i32CurrentY != u8y2);
        }
    }
}

/****************************************************************************
 *
 * NAME:       vLcdDrawCircle
 */
/**
 * Implements Bresenham's Integer Circle Drawing Algoritm
 *
 *
 * @param Xc     Centre X coordinate
 * @param Yc     Centre Y coordinate
 * @param Radius Circle Radius
 *
 * @return
 *
 *
 ****************************************************************************/

PUBLIC void vLcdDrawCircle(int Xc,int Yc,int Radius)
{
    int x,y,d;

    d = 3 - (Radius<<1);
    x = 0;
    y = Radius;

    while(y>=x)
    {
        vLcdPlotPoint(Xc+x,Yc+y);
        vLcdPlotPoint(Xc+x,Yc-y);
        vLcdPlotPoint(Xc-x,Yc+y);
        vLcdPlotPoint(Xc-x,Yc-y);
        vLcdPlotPoint(Xc+y,Yc+x);
        vLcdPlotPoint(Xc+y,Yc-x);
        vLcdPlotPoint(Xc-y,Yc+x);
        vLcdPlotPoint(Xc-y,Yc-x);

        if(d<0)
        {
            d = d + (x <<2 ) + 6;
        }
        else
        {
            d = d + ((x-y) << 2) + 10;
            y--;
        }
        x++;
    }
}

/****************************************************************************
 *
 * NAME: vLcdFloodFill
 *
 * DESCRIPTION:
 * solid Fills any enclosed region
 *
 * PARAMETERS:      Name   RW  Usage
 *                  x    R   X coordinate of point (0-127)
 *                  y    R   Y coordinate of point (0-63)
 *
 * NOTES:
 * starting coordinates must be inside region and not on boundary for algoritm
 * to work. Also region to be filled must have continuous bounder or fill
 * will 'leak' and corrupt the display
 ****************************************************************************/

PUBLIC void vLcdFloodFill(int x, int y)
{
    int left, x1, x2, dy;
    LINESEGMENT stack[MAXDEPTH], *sp = stack;

    if(boLcdGetPixel(x, y))
        return;

    if( x < LCD_MIN_X || x > LCD_MAX_X || y < LCD_MIN_Y || y > LCD_MAX_Y )
        return;

    PUSH(x, x, y, 1);        /* needed in some cases */
    PUSH(x, x, y+1, -1);    /* seed segment (popped 1st) */

    while( sp > stack ) {
        POP(x1, x2, y, dy);

        for( x = x1; x >= LCD_MIN_X && !boLcdGetPixel(x, y); --x )
            vLcdPlotPoint(x, y);

        if( x >= x1 )
            goto SKIP;

        left = x+1;
        if( left < x1 )
            PUSH(y, left, x1-1, -dy);    /* leak on left? */

        x = x1+1;

        do {
            for( ; x<=LCD_MAX_X && !boLcdGetPixel(x, y); ++x )
                vLcdPlotPoint(x, y);

            PUSH(left, x-1, y, dy);

            if( x > x2+1 )
                PUSH(x2+1, x-1, y, -dy);    /* leak on right? */

SKIP:        for( ++x; x <= x2 && boLcdGetPixel(x, y) ; ++x ) {;}

            left = x;
        } while( x<=x2 );
    }
}

/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/
