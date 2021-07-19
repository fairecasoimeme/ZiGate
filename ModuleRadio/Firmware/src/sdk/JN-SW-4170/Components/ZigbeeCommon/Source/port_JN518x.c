/*****************************************************************************
 *
 * MODULE:
 *
 * COMPONENT:
 *
 * DESCRIPTION:
 *
 *****************************************************************************
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

/* Standard includes. */
#include <stdlib.h>
#include "dbg.h"
#include "aessw_ccm.h"
#include "portmacro_JN518x.h"
#include "MicroSpecific.h"


/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

typedef enum
{
    E_HEAP_ALLOC = 0,
    E_HEAP_RESET,
    E_FUNCTION_MAX
} eFunctionId;

typedef void *(*tprHeapAllocFn)(void *, uint32, bool_t);
typedef void (*tprResetHeapFn)(void);
/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
PRIVATE void *pvHeap_DefAlloc(void *pvPointer, uint32 u32BytesNeeded,
                              bool_t bClear);

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/
PUBLIC void *(*prHeap_AllocFunc)(void *, uint32, bool_t) = pvHeap_DefAlloc;

extern uint32 _pvHeapStart;
extern uint32 _pvHeapLimit;
/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

PUBLIC uint32 u32HeapStart = (uint32)&_pvHeapStart;
PUBLIC uint32 u32HeapEnd = (uint32)&_pvHeapLimit;

/****************************************************************************/
/***        Imported Functions                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************
 *
 * NAME:        pvHeap_Alloc
 *
 * DESCRIPTION:
 * Allocates a block of memory from the heap.
 *
 * RETURNS:
 * Pointer to block, or NULL if the heap didn't have enough space. If block
 * was already assigned, returns original value and doesn't take anything
 * from heap.
 *
 * NOTES:
 * If buffer has already been allocated, it is not cleared. If it is a fresh
 * allocation, it is cleared on request.
 *
 ****************************************************************************/


PUBLIC void *pvHeap_Alloc(void *pvPointer, uint32 u32BytesNeeded, bool_t bClear)
{
    return prHeap_AllocFunc(pvPointer, u32BytesNeeded, bClear);
}

PRIVATE void *pvHeap_DefAlloc(void *pvPointer, uint32 u32BytesNeeded, bool_t bClear)
{

    /* If value already assigned, use that value. Otherwise, try to grab space
       from heap */
    if (pvPointer == NULL)
    {
        /* Assume heap start is already word aligned. If not enough space,
           return null */
        if ((u32HeapStart + u32BytesNeeded) > u32HeapEnd)
        {
            /* Trap: immediate value is bit # in SR: if bit is set, trap
               occurs. Wanted to use 15, as this bit is fixed at 1, but
               compiler doesn't seem able to cope with anything other than 0,
               which should also be valid */
            MICRO_TRAP();
            return NULL;
        }

        /* Clear assigned space, if requested */
        if (bClear)
        {
            memset((void *)u32HeapStart, 0, u32BytesNeeded);
        }

        /* Record current heap start to return to caller */
        pvPointer = (void *)u32HeapStart;

        /* Move heap start along and align it */
        u32HeapStart += u32BytesNeeded;
        u32HeapStart = (u32HeapStart + 3) & 0xfffffffc;
    }


    return pvPointer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
static int u32OverwriteCheckStart = 0;
#define HEAP_OVERWRITE_CHECK_CHAR 0x12


/****************************************************************************
 *
 * NAME:        iHeap_InitialiseOverwriteCheck
 *
 * DESCRIPTION:
 * Initialise the remaining free space with a check character
 *
 * RETURNS:
 * The number of remaining free bytes on the heap.
 *
 * NOTES:
 * Designed to be called after everything has been allocated.
 * Used to see how close the heap is to running out of memory.
 * Used in conjunction with iHeap_ReturnNumberOfOverwrittenBytes() to see
 * if the free area of the heap is getting overwritten by the stack and thus get
 * an early warning that the stack may be overwriting the heap and causing a crash.
 *
 ****************************************************************************/

PUBLIC int iHeap_InitialiseOverwriteCheck()
{
    // Start on aligned boundary
    u32OverwriteCheckStart = (u32HeapStart + 3) & 0xfffffffc;;
    memset((void *)u32OverwriteCheckStart, HEAP_OVERWRITE_CHECK_CHAR, u32HeapEnd - u32OverwriteCheckStart);
    return u32HeapEnd - u32OverwriteCheckStart;
}

/****************************************************************************
 *
 * NAME:        iHeap_ReturnNumberOfOverwrittenBytes
 *
 * DESCRIPTION:
 *  Checks how many bytes of the free heap space have been overwritten.
 *
 * RETURNS:
 * The number of bytes that have been overwritten by a stack overflow.
 *
 * NOTES:
 * Following a call to iHeap_InitialiseOverwriteCheck,
 * Checks how many bytes of the free heap space have been overwritten
 * from the end of the free space.
 *
 * Checks from start of free space until it finds a bad byte.
 * This means it will immediately find a changed byte and
 * return the total free space if anything has been allocated
 * from the heap after the call to iHeap_InitialiseOverwriteCheck.
 *
 ****************************************************************************/


PUBLIC int iHeap_ReturnNumberOfOverwrittenBytes()
{
    char *pPos = (char*)u32OverwriteCheckStart;

    while (*pPos == HEAP_OVERWRITE_CHECK_CHAR && (int)pPos < u32HeapEnd)
    {
        pPos++;
    }

    return u32HeapEnd - (int)pPos;
}


//PUBLIC void (*prFunctionLookup[E_FUNCTION_MAX])(void);


PUBLIC void vHeap_ResetHeap(void)
{

}

PUBLIC bool_t bACI_WriteKey(tsReg128 *psKeyData)
{
    status_t status;
    status = AES_SetKey(AES0, (uint8 *)psKeyData, 16);
    if (status != kStatus_Success)
    {
        return FALSE;
    }
    return TRUE;
}

#ifdef JENNIC_DEBUG_ENABLE
#define BUFFER_SIZE 24


PRIVATE bool_t bIsNewline = TRUE;
PRIVATE void vNewLine(const char *pcFileName, uint32 u32LineNumber);
PRIVATE void vWriteUIntToBuffer(unsigned long long ullInteger,
                                int iBase,
                                char acOutBuffer[BUFFER_SIZE],
                                int *piOutBufferStart,
                                int *piOutBufferSize);


PRIVATE const char *pccHandlePlaceHolder(const char *pcFileName,
                                         uint32 u32LineNumber,
                                         const char *pcFormat,
                                         va_list *pap) __attribute__((unused));

PRIVATE void (*vPutchFn)    (char c)    = NULL;
PRIVATE void (*vFlushFn)    (void)      = NULL;

#endif

/****************************************************************************
 *
 * NAME: ZPS_u8GrabMutexLock
 *
 * DESCRIPTION:  Provides mutex protection for function re-entrancy
 *               
 *               
 *
 * RETURNS: uint8 
 *
 *
 ****************************************************************************/
uint8 ZPS_u8GrabMutexLock( void* hMutex , uint32* psIntStore )
{
    if( hMutex != NULL )
    {
    

        if(*( (bool_t*)(( (void* (*) (void))hMutex )())))
        {
          * ( (uint32*) (0xBADADD04) ) = 1;
        }
    }

    /* disable interrupts */
    MICRO_DISABLE_AND_SAVE_INTERRUPTS(*psIntStore);

    if( hMutex != NULL )
        (*( (bool_t*)(( (void* (*) (void))hMutex )()))) = TRUE;

    MICRO_RESTORE_INTERRUPTS(*psIntStore);
    return 0;

}


/****************************************************************************
 *
 * NAME: ZPS_u8ReleaseMutexLock
 *
 * DESCRIPTION:  Provides mutex protection for function re-entrancy
 *               
 *               
 *
 * RETURNS: uint8 
 *
 *
 ****************************************************************************/
uint8 ZPS_u8ReleaseMutexLock( void* hMutex , uint32* psIntStore )
{
    /* disable interrupts */
    MICRO_DISABLE_AND_SAVE_INTERRUPTS(*psIntStore);

    if( hMutex != NULL )
        (*( (bool_t*)(( (void* (*) (void))hMutex )()))) = FALSE;

    MICRO_RESTORE_INTERRUPTS(*psIntStore);
    return 0;
}


/****************************************************************************
 *
 * NAME: ZPS_eEnterCriticalSection
 *
 * DESCRIPTION:  Provides protection from function re-entrancy and interrupt
 *               pre-emption.
 *               
 *
 * RETURNS:
 *
 *
 ****************************************************************************/
PUBLIC uint8 ZPS_eEnterCriticalSection(void* hMutex, uint32* psIntStore)
{
    if( hMutex != NULL )
    {
    
        if(*( (bool_t*)(( (void* (*) (void))hMutex )())))
        {
          * ( (uint32*) (0xBADADD08) ) = 1;
        }
    }
    /* disable interrupts */
    MICRO_DISABLE_AND_SAVE_INTERRUPTS(*psIntStore);

    if( hMutex != NULL )
        (*( (bool_t*)(( (void* (*) (void))hMutex )()))) = TRUE;

    return 0;
}

/****************************************************************************
 *
 * NAME: ZPS_eExitCriticalSection
 *
 * DESCRIPTION:  Allows interrupt pre-emption and function re-entrancy.
 *               
 *
 * RETURNS:
 *
 *
 ****************************************************************************/
PUBLIC uint8 ZPS_eExitCriticalSection(void* hMutex , uint32* psIntStore)
{
    if( hMutex != NULL )
        (*( (bool_t*)(( (void* (*) (void))hMutex )()))) = FALSE;

    MICRO_RESTORE_INTERRUPTS(*psIntStore);
    return 0;
}

/****************************************************************************
 *
 * NAME: ZPS_u32Reverse
 *
 * DESCRIPTION:  reverse the byte order of a word
 *               
 *
 * RETURNS:
 *
 *
 ****************************************************************************/
PUBLIC uint32 u32Reverse(uint32 u32InWord)
{
    uint32 u32OutWord;

    asm volatile ("REV %[reverse], %[input];"
                  : [reverse] "=r" (u32OutWord)
                  : [input]  "r"  (u32InWord)   );

    return u32OutWord;
}


#ifdef JENNIC_DEBUG_ENABLE


PUBLIC void DBG_vInit(tsDBG_FunctionTbl *psFunctionTbl)
{
    vPutchFn = psFunctionTbl->prPutchCb;
    vFlushFn = psFunctionTbl->prFlushCb;
}
/****************************************************************************
 *
 * NAME: vNewLine
 *
 * DESCRIPTION:
 * Outputs the filename and line number
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void vNewLine(const char *pcFileName, uint32 u32LineNumber)
{
    char acBuffer[BUFFER_SIZE];
    int iStart;
    int iSize;

    if(*pcFileName == '\0')
    {
        return;
    }

    while(*pcFileName != '\0')
    {
        vPutchFn(*pcFileName);
        pcFileName++;
    }

    vPutchFn(':');

    vWriteUIntToBuffer(u32LineNumber,
                       10,
                       acBuffer,
                       &iStart,
                       &iSize);

    while(iSize)
    {
        vPutchFn(acBuffer[iStart]);
        iStart++;
        iSize--;
    }

    vPutchFn(':');
    vPutchFn(' ');
}

/****************************************************************************
 *
 * NAME: DbgConsole_Printf
 *
 * DESCRIPTION:
 * Verbose version of printf
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/

PUBLIC int DbgConsole_Printf( const char *pcFormat,
                            ...)
{
    va_list ap;

	if(!vPutchFn)
	{
	    return -1;
	}

	if(!pcFormat)
	{
	    return -1;
	}
    va_start(ap, pcFormat);

    for(; *pcFormat != '\0'; pcFormat++)
    {
        if(bIsNewline)
        {
            bIsNewline = FALSE;

            vNewLine("", 0);
        }

        if(*pcFormat == '%')
        {
            pcFormat = pccHandlePlaceHolder("",
                                            0,
                                            pcFormat + 1,
                                            &ap);
        }
        else if(*pcFormat == '\n')
        {
            vPutchFn('\r');
            vPutchFn('\n');

            bIsNewline = TRUE;
        }
        else
        {
            vPutchFn(*pcFormat);
        }
    }

    /* call flush before exit */
    if(vFlushFn)
    {
       vFlushFn();
    }
	va_end(ap);
	return 0;
}

/****************************************************************************
 *
 * NAME: vWriteUIntToBuffer
 *
 * DESCRIPTION:
 * Converts a number of the specified base to a string
 *
 * RETURNS:
 * void
 *
 ****************************************************************************/
PRIVATE void vWriteUIntToBuffer(unsigned long long ullInteger,
                                int iBase,
                                char acOutBuffer[BUFFER_SIZE],
                                int *piOutBufferStart,
                                int *piOutBufferSize)
{
    int i = BUFFER_SIZE;

    do
    {
        /* cheap way to get a mod and a divide together -
         * multiply is way cheaper! */
        unsigned long long ullIntegerTmp = ullInteger / iBase;
        unsigned int uCurrentDigit = ullInteger - ullIntegerTmp * iBase;
        ullInteger = ullIntegerTmp;

        i--;
        if(uCurrentDigit < 0xA)
        {
            acOutBuffer[i] = '0' + uCurrentDigit;
        }
        else
        {
            acOutBuffer[i] = 'a' + uCurrentDigit - 0xA;
        }

    } while(ullInteger);

    *piOutBufferStart = i;
    *piOutBufferSize = BUFFER_SIZE - i;
}


/****************************************************************************
 *
 * NAME: pccHandlePlaceHolder
 *
 * DESCRIPTION:
 * Handles format specifiers
 *
 * RETURNS:
 * const char *
 *
 ****************************************************************************/
PRIVATE const char *pccHandlePlaceHolder(const char *pcFileName,
                                         uint32 u32LineNumber,
                                         const char *pcFormat,
                                         va_list *pap)
{
    char acBuffer[BUFFER_SIZE];

    bool_t bLeftAlign           = FALSE;
    bool_t bPadWith0NotSpace    = FALSE;
    bool_t bSignWithPlus        = FALSE;
    bool_t bSignWithSpace       = FALSE;

    int iMinWidth = 0;

    bool_t bIsShort    = FALSE;
    bool_t bIsLong     = FALSE;
    bool_t bIsLongLong = FALSE;

    unsigned long long ullArg = 0;


    /* flags */
    while(1)
    {
        bool_t bQuit = FALSE;

        switch(*pcFormat)
        {
        case '-':
            bLeftAlign = TRUE;
            break;
        case '0':
            bPadWith0NotSpace = TRUE;
            break;
        case '+':
            bSignWithPlus = TRUE;
            break;
        case ' ':
            bSignWithSpace = TRUE;
            break;
        default:
            bQuit = TRUE;
            break;
        }

        if(bQuit)
        {
            break;
        }
        pcFormat++;
    }

    /* min field width */
    if(*pcFormat >= '1' && *pcFormat <= '9')
    {
        while(1)
        {
            int iThisDigit = *pcFormat - '0';

            if(iThisDigit < 0 || iThisDigit > 9)
            {
                break;
            }

            pcFormat++;

            iMinWidth *= 10;
            iMinWidth += iThisDigit;
        }
    }

    /* size modifier */
    if(*pcFormat == 'l')
    {
        /* long */
        pcFormat++;
        bIsLong = TRUE;

        if(*pcFormat == 'l')
        {
            /* long long */
            pcFormat++;
            bIsLongLong = TRUE;
        }
    }
    else if(*pcFormat == 'h')
    {
        /* short */
        bIsShort = TRUE;
        pcFormat++;
    }

    if(*pcFormat == 'i' ||
       *pcFormat == 'd' ||
       *pcFormat == 'u' ||
       *pcFormat == 'x' ||
       *pcFormat == 'p')
    {
        int iStart = 0;
        int iSize = 0;

        bool_t bIsSigned = FALSE;
        bool_t bIsHex = FALSE;
        bool_t bIsNegative = FALSE;
        bool_t bIsPtr = FALSE;

        char cSign = '\0';

        if(*pcFormat == 'i' ||
           *pcFormat == 'd')
        {
            bIsSigned = TRUE;
        }
        else if(*pcFormat == 'x')
        {
            bIsHex = TRUE;
        }
        else if(*pcFormat == 'p')
        {
            bIsPtr = TRUE;

            bIsLongLong = (sizeof(void *) >= sizeof(long long));
            bIsLong     = (sizeof(void *) >= sizeof(long));
        }

        if(!bIsSigned)
        {
            bSignWithPlus = FALSE;
            bSignWithSpace = FALSE;
        }

        if(bIsLongLong)
        {
            if(bIsSigned)
            {
                ullArg = va_arg(*pap, long long);
            }
            else
            {
                ullArg = va_arg(*pap, unsigned long long);
            }
        }
        else if(bIsLong)
        {
            if(bIsSigned)
            {
                ullArg = va_arg(*pap, long);
            }
            else
            {
                ullArg = va_arg(*pap, unsigned long);
            }
        }
        else if(bIsShort)
        {
            /* take account of lower limits */
            if(bIsSigned)
            {
                short s = va_arg(*pap, int);
                ullArg = s;
            }
            else
            {
                unsigned short us = va_arg(*pap, unsigned int);
                ullArg = us;
            }
        }
        else
        {
            if(bIsSigned)
            {
                ullArg = va_arg(*pap, int);
            }
            else
            {
                ullArg = va_arg(*pap, unsigned int);
            }
        }

        if(bIsSigned)
        {
            long long llArg = ullArg;
            if(llArg < 0)
            {
                bIsNegative = TRUE;

                /* scalar value */
                ullArg = 0 - ullArg;
            }
        }

        vWriteUIntToBuffer(ullArg,
                           (bIsHex || bIsPtr) ? 16 : 10,
                           acBuffer,
                           &iStart,
                           &iSize);

        if(bIsNegative)
        {
            cSign = '-';
        }
        else
        {
            if(bSignWithPlus)
            {
                cSign = '+';
            }
            else if(bSignWithSpace)
            {
                cSign = ' ';
            }
        }

        iMinWidth -= iSize;

        if(cSign)
        {
            iMinWidth--;
        }

        if(bIsPtr)
        {
            iMinWidth -= 2;
        }

        if(bLeftAlign)
        {
            if(cSign)
            {
                /* write the sign */
                vPutchFn(cSign);
            }

            if(bIsPtr)
            {
                vPutchFn('0');
                vPutchFn('x');
            }

            /* write the digits */
            for(;iSize > 0; iSize--)
            {
                vPutchFn(acBuffer[iStart++]);
            }

            /* write the pad char */
            for(; iMinWidth > 0; iMinWidth--)
            {
                /* note, '0' is ignored when the '-' flag is set */
                vPutchFn(' ');
            }
        }
        else
        {
            if(bPadWith0NotSpace)
            {
                if(cSign)
                {
                    vPutchFn(cSign);
                }

                if(bIsPtr)
                {
                    vPutchFn('0');
                    vPutchFn('x');
                }

                /* write the pad char */
                for(; iMinWidth > 0; iMinWidth--)
                {
                    vPutchFn('0');
                }

                /* write the digits */
                for(;iSize > 0; iSize--)
                {
                    vPutchFn(acBuffer[iStart++]);
                }
            }
            else
            {
                /* write the pad char */
                for(; iMinWidth > 0; iMinWidth--)
                {
                    vPutchFn(' ');
                }

                if(cSign)
                {
                    vPutchFn(cSign);
                }

                if(bIsPtr)
                {
                    vPutchFn('0');
                    vPutchFn('x');
                }

                /* write the digits */
                for(;iSize > 0; iSize--)
                {
                    vPutchFn(acBuffer[iStart++]);
                }
            }
        }
    }
    else
    {
        char c = '\0';
        const char *pc = NULL;

        switch(*pcFormat)
        {
        case 'c':
            c = va_arg(*pap, int);
            if (c == '\n')
            {
                vPutchFn('\r');
                vPutchFn('\n');
                bIsNewline = TRUE;
            }
            else /* PR #21 http://trac/Cortex/ticket/21 - output character if it's not a new line */
            {
                vPutchFn(c);
            }
            break;

        case 's':
            {
                const char *pcc;
                pc = va_arg(*pap, char *);
                pcc = pc;
                for(;*pcc != '\0';pcc++)
                {
                    if(bIsNewline)
                    {
                        bIsNewline = FALSE;

                        vNewLine(pcFileName, u32LineNumber);
                    }

                    if(*pcc == '\n')
                    {
                        vPutchFn('\r');
                        vPutchFn('\n');

                        bIsNewline = TRUE;
                    }
                    else
                    {
                        vPutchFn(*pcc);
                    }
                }
            }
            break;

        case '%':
            vPutchFn(*pcFormat);
            break;
        default:
            /* error */
            return pcFormat - 1;
        }
    }

    return pcFormat;
}
#endif

/****************************************************************************
 *
 * NAME:       vSwipeEndian
 */
/**
 * Reverses 1282bit data between AESSW_Block_u and tsReg128
 *
 *
 * @param puBlock  128 bit data of type AESSW_Block_u
 *
 * @param psReg  128 bit data of type  tsReg128
 *
 * @param bBlockToReg  direction of converesion
 * 						1 = AESSW_Block_u to tsReg128
 *						0 = tsReg128 to AESSW_Block_u
 *
 * @return
 *
 * @note
 *
 ****************************************************************************/
PUBLIC void vSwipeEndian(AESSW_Block_u *puBlock, tsReg128 *psReg, bool_t bBlockToReg)
{
    int i=0;
    for (i = 0; i < 4 ; i++)
    {
        if(bBlockToReg)
            ((uint32*)psReg)[i] = u32Reverse((uint32)(puBlock->au32[i]));
        else
            puBlock->au32[i]  = u32Reverse(((uint32*)psReg)[i]);
	}
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

