/* $Id: util_debug.c,v 1.5 2004/03/12 16:31:08 bird Exp $
 *
 * Debug Stuff.
 *
 * Copyright (c) 2003-2004 InnoTek Systemberatung GmbH
 * Copyright (c) 2012 bww bitwise works GmbH
 *
 * Authors: knut st. osmundsen <bird@anduin.net>
 *          Dmitriy Kuminov <coding@dmik.org>
 *
 * All Rights Reserved
 *
 */

#define INCL_WIN
#define INCL_DOSPROCESS
#include <os2.h>

/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/

#ifndef ORIGINAL_VAC_FUNCTIONS
#define ORIGINAL_VAC_FUNCTIONS
#endif

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __IBMC__
#include <builtin.h>
#endif

#include "common.h"

#ifdef ODIN_LOG
/*******************************************************************************
*   External Functions                                                         *
*******************************************************************************/
int _System WriteLog(const char *, ...);
#endif


/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/
#ifdef ODIN_LOG
static const char szPrefix[] = "";
#else
static const char szPrefix[] = "";
#endif

/**
 * Writes to log.
 */
int     npdprintf(const char *pszFormat, ...)
{
    // we may be called in the Win32, so switch to OS/2 before calling LIBC
    unsigned    selOldFS = npRestoreOS2FS();

#ifndef ODIN_LOG
    static int      fInited = 0;
    static FILE *   phFile;
    static ULONG    startTicks = 0;
    static ULONG    startTime = 0;
#endif
    char    szMsg[4096] = {0};
    int     rc;
    va_list args;

#ifndef ODIN_LOG
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

            // initialize the current time counter
            startTicks = WinGetCurrentTime(0);
            startTime = dt.hours * 3600 + dt.minutes * 60 + dt.seconds;
            startTime = (startTime * 1000) + dt.hundredths * 10;
        }
    }
#endif

    strcpy(szMsg, szPrefix);

#ifndef ODIN_LOG
    // get human readable time values
    DWORD time = startTime + (WinGetCurrentTime(0) - startTicks);
    DWORD h = (time / 3600000) % 24;
    DWORD m = (time %= 3600000) / 60000;
    DWORD s = (time %= 60000) / 1000;
    DWORD ms = time % 1000;
    // get thread info
    PTIB ptib;
    DosGetInfoBlocks(&ptib, NULL);
    // put it all together
    sprintf(szMsg, "%02d:%02d:%02d.%03d t%02d: ", h, m, s, ms, ptib->tib_ptib2->tib2_ultid);
#else
    strcpy(szMsg, " ");
#endif

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

#ifdef ODIN_LOG
    npSetFS(selOldFS);
    if (pfnWriteLog)
        pfnWriteLog("%s", &szMsg[0]);

#else
    if (rc > 0 && szMsg[rc - 1] != '\n')
    {
        szMsg[rc++] = '\n';
        szMsg[rc] = '\0';
    }

    if (phFile)
    {
        fwrite(&szMsg[0], 1, rc, phFile);
        fflush(phFile);
        //fclose(phFile);
    }

    // restore the previous context
    npSetFS(selOldFS);
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


#if 0
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

