/* $Id: util_debug.c,v 1.5 2004/03/12 16:31:08 bird Exp $
 *
 * Debug Stuff.
 *
 * InnoTek Systemberatung GmbH confidential
 *
 * Copyright (c) 2003-2004 InnoTek Systemberatung GmbH
 * Author: knut st. osmundsen <knut@innotek.de>
 *
 * All Rights Reserved
 *
 */

#define INCL_WIN
#include <os2.h>

/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/
#define ORIGINAL_VAC_FUNCTIONS

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __IBMC__
#include <builtin.h>
#endif

#define INCL_BASE
#include <os2.h>

#undef NPODIN

#ifdef NPODIN
#include "common.h"
#else
#define INCL_DEBUGONLY
#include "nsPluginWrapper.h"
#endif

#ifdef NPODIN
/*******************************************************************************
*   External Functions                                                         *
*******************************************************************************/
int _System WriteLog(const char *, ...);
#endif


/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/
#ifdef NPODIN
static const char szPrefix[] = "";
#else
static const char szPrefix[] = "";
#endif


/**
 * Writes to log.
 */
int     npdprintf(const char *pszFormat, ...)
{
#ifdef NPODIN
    unsigned    selOldFS = npRestoreOS2FS();
#else
    static int      fInited = 0;
    static FILE *   phFile;
#endif
    char    szMsg[4096] = {0};
    int     rc;
    va_list args;

    strcpy(szMsg, szPrefix);
    sprintf(szMsg, "(%x) ", WinGetCurrentTime(0));

    rc = strlen(szMsg);
    va_start(args, pszFormat);
    rc += vsprintf(&szMsg[rc], pszFormat, args);
    va_end(args);
    if (rc > (int)sizeof(szMsg) - 32)
    {
        /* we're most likely toasted now. */
#ifdef __IBMC__
//        _interrupt(3);
#else
//        asm("int $3");
#endif
    }

#ifdef NPODIN
    npSetFS(selOldFS);
    if (pfnWriteLog)
        pfnWriteLog("%s", &szMsg[0]);

#else
    if (rc > 0 && szMsg[rc - 1] != '\n')
    {
        szMsg[rc++] = '\n';
        szMsg[rc] = '\0';
    }

    if (!fInited)
    {
        fInited = 1;
        phFile = fopen("npflos2.log", "w");
        if (phFile)
        {
            DATETIME dt;
            DosGetDateTime(&dt);
            fprintf(phFile, "*** Log Opened on %04d-%02d-%02d %02d:%02d:%02d ***\n",
                    dt.year, dt.month, dt.day, dt.hours, dt.minutes, dt.seconds);
            fprintf(phFile, "*** Build Date: " __DATE__ " " __TIME__ " ***\n");
        }
    }
    if (phFile)
    {
        fwrite(&szMsg[0], 1, rc, phFile);
        fflush(phFile);
        //fclose(phFile);
    }
#endif

    return rc;
}


/**
 * Release int 3.
 */
void _Optlink ReleaseInt3(unsigned uEAX, unsigned uEDX, unsigned uECX)
{
#ifdef __IBMC__
//    _interrupt(3);
#else
//    asm("int $3");
#endif
}


#ifdef NPODIN
#ifdef DEBUG
/**
 * Debug function which padds the stack.
 * Used to try messup the stack up in a recognizable way.
 */
void CleanStack(void)
{
    USHORT  selFS = npGetFS();
    char *  pStack;
    char *  pStackBottom;
    PTIB    ptib;

    DosGetInfoBlocks(&ptib, NULL);
    pStack = ptib->tib_pstacklimit;
    pStackBottom = (char*)ptib->tib_pstack - 0x1000; /* don't touch the last page. */
    if (pStack > (char*)&ptib && pStackBottom < (char*)&ptib && pStack > pStackBottom)
    {
        int         cb;
        unsigned *  puch;

        /* can't use memcpy */
        puch = (unsigned*)((char*)&ptib - 0x20);
        cb = min((char*)puch - pStackBottom, 0x100);
        for (; cb > 0; cb -= 4, puch--)
            *puch = 0xbbdeadbb;
    }

    npSetFS(selFS);
}
#endif
#endif

