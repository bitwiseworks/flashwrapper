/* $Id: apis_mozilla.cpp,v 1.2 2003/09/14 22:37:29 bird Exp $
 *
 * Mozilla APIs.
 *
 * Copyright (c) 2003 InnoTek Systemberatung GmbH
 * Copyright (c) 2012 bww bitwise works GmbH
 *
 * Authors: knut st. osmundsen <bird@anduin.net>
 *          Dmitriy Kuminov <coding@dmik.org>
 *
 * All Rights Reserved
 *
 */


/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  INCL_BASE
#include <os2.h>

#define INCL_MOZAPIS
#include "common.h"



/*******************************************************************************
*   Global Variables                                                           *
*******************************************************************************/
/** NSPR API for attaching a thread to mozilla. (broken < 1.4x) */
static PRThread* (*PRICALL      pfnPR_AttachThread)(PRThreadType type, PRThreadPriority priority, PRThreadStack *stack);
/** NSPR API for detaching a thread from mozilla. (broken < 1.4x) */
static void (*PRICALL           pfnPR_DetachThread)(void);
/** NSPR API for getting the current thread info. */
static PRThread* (*PRCALL       pfnPR_GetCurrentThread)(void);


/** internal NSPR API for attaching a thread to mozilla. (not present > 1.3a) */
PRThread* (*PRICALL             pfn_PRI_AttachThread)(PRThreadType type, PRThreadPriority priority, PRThreadStack *stack, PRUint32 flags);
/** internal NSPR API for detaching a thread from mozilla. (not present > 1.3a) */
void (*PRICALL                  pfn_PRI_DetachThread)(void);



/**
 * Checks if the specified dll (by handle!) is loaded into this process or not.
 *
 * @returns TRUE if the dll is present in this process.
 * @returns FLASE if the dll isn't present in this process.
 * @param   pszDll  Name of the dll.
 */
BOOL isDllInThisProcess(const char *pszDll)
{
    static const char szFunction[] = "isDllInThisProcess";
    PVOID   pv;
    int     rc;
    ULONG   cb = 1024*1024;

    /*
     * Allocate a hugh buffer for DosQuerySysState.
     */
    if (DosAllocMem(&pv, cb, PAG_READ | PAG_WRITE | PAG_COMMIT))
    {
        cb = 1024*256;
        if (DosAllocMem(&pv, cb, PAG_READ | PAG_WRITE | PAG_COMMIT))
        {
            dprintf(("%s: DosAllocMem fails! (256KB)", szFunction));
            return TRUE; //assume presence.
        }
    }

    /*
     * Get the correct filename.
     */
    if (!DosQueryPathInfo(pszDll, FIL_QUERYFULLNAME, pv, CCHMAXPATH))
        pszDll = (const char*)pv;


    /*
     * Get object information of the load modules system.
     */
    QSPTRREC *  pPtrRec = (QSPTRREC*)((char*)pv + CCHMAXPATH);
    rc = DosQuerySysState(QS_MTE, QS_MTE, 0L, 0L, pPtrRec, cb);
    if (rc != NO_ERROR)
    {
        DosFreeMem(pv);
        dprintf(("%s: DosQuerySysState failed with rc=%d.", szFunction, rc));
        DebugInt3();
        return FALSE;
    }

    QSLREC *      pLrec = pPtrRec->pLibRec;
    while (pLrec != NULL)
    {
        /*
         * Bug detected in OS/2 FP13. Probably a problem which occurs
         * in _LDRSysMteInfo when qsCheckCache is calle before writing
         * object info. The result is that the cache flushed and the
         * attempt of updating the QSLREC next and object pointer is
         * not done. This used to work earlier and on Aurora AFAIK.
         *
         * The fix for this problem is to check if the pObjInfo is NULL
         * while the number of objects isn't 0 and correct this. pNextRec
         * will also be NULL at this time. This will be have to corrected
         * before we exit the loop or moves to the next record.
         * There is also a nasty alignment of the object info... Hope
         * I got it right. (This aligment seems new to FP13.)
         */
        if (pLrec->pObjInfo == NULL /*&& pLrec->pNextRec == NULL*/ && pLrec->ctObj > 0)
            {
            pLrec->pObjInfo = (QSLOBJREC*)(void*)(
                (char*)(void*)pLrec
                + ((sizeof(QSLREC)                            /* size of the lib record */
                   + pLrec->ctImpMod * sizeof(short)            /* size of the array of imported modules */
                   + strlen((char*)(void*)pLrec->pName) + 1     /* size of the filename */
                   + 3) & ~3));                                 /* the size is align on 4 bytes boundrary */
#if defined (__EMX__) && !defined (USE_OS2_TOOLKIT_HEADERS)
            pLrec->pNextRec = (PVOID*)(void*)((char*)(void*)pLrec->pObjInfo
                                                 + sizeof(QSLOBJREC) * pLrec->ctObj);
#else
            pLrec->pNextRec = (QSLREC*)(void*)((char*)(void*)pLrec->pObjInfo
                                                 + sizeof(QSLOBJREC) * pLrec->ctObj);
#endif
            }
        if (pLrec->pName && !strnicmp((char*)pLrec->pName, pszDll, CCHMAXPATH)) /* paranoia */
            break;

        /*
         * Next record
         */
        pLrec = (QSLREC*)pLrec->pNextRec;
    }

    /*
     * Analyse result.
     */
    BOOL fRc = FALSE;
    if (pLrec != NULL)
    {
        if (pLrec->ctObj && pLrec->pObjInfo)
        {
            dprintf(("%s: hmod=%#x: first object at %#x %#x bytes", szFunction, pLrec->hmte,
                     pLrec->pObjInfo[0].oaddr, pLrec->pObjInfo[0].osize));

            /*
             * Now check if the first object is physically present in this process.
             * ASSUME first segment is not resources!
             *
             * Note. DosQueryMem twice as it (in this type of query) may fail the first
             *       time on some Warp4 fixpack levels.
             */
            ULONG   cb = ~0;
            ULONG   fFlags = ~0;
            if (    !(rc = DosQueryMem((PVOID)pLrec->pObjInfo[0].oaddr, &cb, &fFlags))
                ||  !(rc = DosQueryMem((PVOID)pLrec->pObjInfo[0].oaddr, &cb, &fFlags)))
            {
                dprintf(("%s: hmod=%#x DosQueryMem returns cb=%#x and fFlags=%#x", szFunction, pLrec->hmte, cb, fFlags));
                if (fFlags & (PAG_READ | PAG_WRITE | PAG_EXECUTE))
                {
                    dprintf(("%s: the object is accessible. (return TRUE)", szFunction));
                    fRc = TRUE;
                }
                else
                    dprintf(("%s: object isn't accessible. (return FALSE)", szFunction));
            }
            else
                dprintf(("%s: hmod=%#x DosQueryMem failed rc=%d (return FALSE)", szFunction, pLrec->hmte, rc));
        }
        else
            dprintf(("%s: hmod=%#x has no object info! (return FALSE)", szFunction, pLrec->hmte));
    }
    else
        dprintf(("%s: %s not found! (return FALSE)", szFunction, pszDll));

    DosFreeMem(pv);
    return fRc;
}


/**
 * Find the start of the filename.
 *
 * @returns pointer to start of filename.
 * @param   pszPath Path to examin.
 */
static char *GetBasename(char *pszPath)
{
    char *pszName;
    char *psz;

    pszName = strrchr(pszPath, '\\');
    psz = strrchr(pszName ? pszName : pszPath, '/');
    if (psz)
        pszName = psz;
    if (!pszName)
        pszName = strchr(pszPath, ':');
    if (pszName)
        pszName++;
    else
        pszName = pszPath;

    return pszName;
}


/**
 * Resolve dynamically stuff from mozilla.
 * @returns Successs indicator.
 * @remark  There is only two type of processes we allow loading within.
 *          Netscape 4.x and Mozilla.
 * @remark  We really have to be very careful because these DLLs are likely to
 *          be located in the config.sys LIBPATH, which mean DosLoadModule
 *          easily load WGSS46.DLL from within mozilla, or it could load
 *          NSPR4.DLL from one of the IWBs when in Netscape. We must not
 *          mistake which browser we're in, that would be very very silly!
 */
BOOL    npResolveMozAPIs(void)
{
    static const char szFunction[] = "npResolveMozAPIs";
    int     i;
    int     rc;
    BOOL    fRc = TRUE;
    FILESTATUS3 fsts3;


    /*
     * Is *THIS* process a mozilla process?
     *      How the hell can we tell?
     *      The safe way is to figure out that we're not a netscape 4.x process...
     *
     * I wonder, if the presens of WGSS.DLL and WGSS46.DLL in the process
     * might do the trick. Not, LIBPATHSTRICT=T f**ks this up.
     *
     * New try:
     * We'll get the executable path and look for the presence of certain dlls there.
     */

    /* find end of executable name */
    char    szExeName[CCHMAXPATH];
    char *  pszName;
    char *  psz;
    PPIB    ppib;
    PTIB    ptib;
    DosGetInfoBlocks(&ptib, &ppib);
    pszName = GetBasename(strcpy(szExeName, ppib->pib_pchcmd));
    *pszName = '\0';

    /** Table of Netscape 4.x indicator DLLs. */
    static const char *apszDlls[] =
    {
        "WGSS",
        "WGSS46"
    };
    /* Check if this is Netscape 4.x, and in that case we'll simply do nothing */
    for (i = 0; i < sizeof(apszDlls) / sizeof(apszDlls[0]); i++)
    {
        strcpy(pszName, apszDlls[i]);
        strcat(pszName, ".DLL");
        rc = DosQueryPathInfo(&szExeName[0], FIL_STANDARD, &fsts3, sizeof(fsts3));
        if (!rc)
        {
            if (isDllInThisProcess(&szExeName[0]))
            {
                /* If we get here it's netscape. */
                dprintf(("%s: Netscape process! %s proves so.", szFunction, apszDlls[i]));
                return TRUE;
            }
        }
    }
    dprintf(("%s: Not netscape process, so it must be mozilla.", szFunction));


    /* Check of NSPR4.DLL - which proves mozilla. */
    strcpy(pszName, "NSPR4.DLL");
    rc = DosQueryPathInfo(&szExeName[0], FIL_STANDARD, &fsts3, sizeof(fsts3));
    if (rc)
    {
        dprintf(("%s: No NSPR4.DLL in executable directory!", szFunction));
        /*
         * Last resort. We know we're in "\plugins", which means we take our name
         * and goes up one level.
         */
        HMODULE hmod;
        rc = DosQueryModuleName(ghmodOurSelf, sizeof(szExeName), &szExeName[0]);
        if (!rc)
        {
            /* strip of name and directory. */
            pszName = GetBasename(szExeName);
            if (pszName > szExeName)
            {
                pszName--;
                *pszName = '\0';
                pszName = GetBasename(szExeName);
                *pszName = '\0';

                /* retry */
                strcpy(pszName, "NSPR4.DLL");
                rc = DosQueryPathInfo(&szExeName[0], FIL_STANDARD, &fsts3, sizeof(fsts3));
            }
        }
    }

    /* If the DLL wasn't found or it's not in this process we'll fail. */
    if (    rc
        ||  !isDllInThisProcess(&szExeName[0]))
    {
        dprintf(("%s: Shit! can't figure out where NSPR4.DLL is!", szFunction));
        npGenericErrorBox("Counldn't find NSPR4.DLL. Probably unsupported browser.", FALSE);
        return FALSE;
    }


    /*
     * Now resolv the Mozilla entrypoints we need.
     *      1. Load the required DLLs.
     *      2. Query the exports.
     *      3. Unload the DLLs.
     */
    /** Table of Mozilla Modules. */
    struct Modules
    {
        HMODULE     hmod;
        const char *pszDll;
    }   aMods[] =
    {
        #define iNSPR4      0
        { NULLHANDLE,   "NSPR4" },
    };
    /* Load dlls */
    for (i = 0; i < sizeof(aMods) / sizeof(aMods[0]); i++)
    {
        strcpy(pszName, aMods[i].pszDll);
        // when we have a full path there must be an extension as well
        strcat(pszName, ".DLL");
        aMods[i].hmod = NULLHANDLE;
        rc = DosLoadModule(NULL, 0, &szExeName[0], &aMods[i].hmod);
        if (rc)
        {
            dprintf(("%s: DosLoadModule(0,0,%s,) -> %d", szFunction, &szExeName[0], rc));
            fRc = FALSE;
            break;
        }
    }

    if (fRc)    /* no sense in doing this unless we've managed to all load the shit */
    {
        /** Table of Mozilla APIs to resolve. */
        static struct EntryPoint
        {
            int         fMandatory;
            void **     ppfn;
            int         iMod;
            const char *pszName;
        }   aAPIs[] =
        {
            { 1, (void**)&pfnPR_AttachThread,           iNSPR4,     "PR_AttachThread"  },
            { 1, (void**)&pfnPR_DetachThread,           iNSPR4,     "PR_DetachThread"  },
            { 1, (void**)&pfnPR_GetCurrentThread,       iNSPR4,     "PR_GetCurrentThread"  },
            { 0, (void**)&pfn_PRI_AttachThread,         iNSPR4,     "__PRI_AttachThread"  },
            { 0, (void**)&pfn_PRI_DetachThread,         iNSPR4,     "__PRI_DetachThread"  },
        };
        /* query addresses. */
        for (i = 0; i < sizeof(aAPIs) / sizeof(aAPIs[0]); i++)
        {
            rc = DosQueryProcAddr(aMods[aAPIs[i].iMod].hmod, 0, aAPIs[i].pszName, (PFN*)aAPIs[i].ppfn);
            if (rc)
            {
                if (!aAPIs[i].fMandatory)
                {
                    dprintf(("%s: DosQueryProcAddr('%s',0,'%s',) -> %d (not mandatory)",
                             szFunction, aMods[aAPIs[i].iMod].pszDll, aAPIs[i].pszName, rc));
                    *aAPIs[i].ppfn = NULL;
                    continue;
                }
                dprintf(("%s: DosQueryProcAddr('%s',0,'%s',) -> %d !!!",
                         szFunction, aMods[aAPIs[i].iMod].pszDll, aAPIs[i].pszName, rc));
                ReleaseInt3(0xdeaddead, 0xdeadf003, i);
                fRc = FALSE;
                break;
            }
        }
    }

    /* Unload the DLLs. */
    for (i = 0; i < sizeof(aMods) / sizeof(aMods[0]); i++)
        if (aMods[i].hmod != NULLHANDLE)
            DosFreeModule(aMods[i].hmod);

    dprintf(("%s: Successfully resolved all Mozilla APIs", szFunction));
    return fRc;
}



/**
 * PR_GetCurrentThread wrapper.
 * Assumes OS/2 context.
 */
PRThread *  mozPR_GetCurrentThread(void)
{
    return pfnPR_GetCurrentThread();
}

/**
 * PR_AttachThread wrapper.
 * Assumes OS/2 context.
 */
PRThread*   mozPR_AttachThread(PRThreadType type, PRThreadPriority priority, PRThreadStack *stack)
{
    return pfnPR_AttachThread(type, priority, stack);
}

/**
 * PR_DetachThread wrapper.
 * Assumes OS/2 context.
 */
void        mozPR_DetachThread(void)
{
    pfnPR_DetachThread();
}

/**
 * _PRI_AttachThread wrapper.
 * Assumes OS/2 context.
 */
PRThread*   moz_PRI_AttachThread(PRThreadType type, PRThreadPriority priority, PRThreadStack *stack, PRUint32 flags)
{
    if (pfn_PRI_AttachThread)
        return pfn_PRI_AttachThread(type, priority, stack, flags);
    return NULL;
}

/**
 * _PRI_DetachThread wrapper.
 * Assumes OS/2 context.
 */
void        moz_PRI_DetachThread(void)
{
    if (pfn_PRI_DetachThread)
        pfn_PRI_DetachThread();
}

