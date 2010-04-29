/* $Id: plugin_primary.cpp,v 1.4 2004/03/08 19:22:56 bird Exp $
 *
 * Primary plugin Init / Term.
 *
 * InnoTek Systemberatung GmbH confidential
 *
 * Copyright (c) 2003 InnoTek Systemberatung GmbH
 * Author: knut st. osmundsen <bird@anduin.net>
 *
 * All Rights Reserved
 *
 */


/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/
#ifdef __IBMCPP__
# include "moz_VACDefines.h"
#else
# include "moz_GCCDefines.h"
#endif
#define  INCL_DOSMODULEMGR
#define  INCL_DOSMISC
#define  INCL_DOSPROCESS
#define  INCL_DOSERRORS
#define  INCL_DOSSEMAPHORES

#define INCL_BASE
#define INCL_PM
#include <os2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <initdll.h>                    /* odin stuff. */
#include "plugin_primary.h"
//#include <custombuild.h>
//#include <customloader.h>

#include "moz\sdk\xpcom\include\nsIServiceManager.h"
#include "moz\sdk\xpcom\include\nsIFactory.h"
#include "moz\include\plugin\npapi.h"
#include "moz\include\plugin\npupp.h"

#define INCL_MOZXPCOM
#define INCL_NS4X
#define INCL_MOZAPIS
#include "common.h"

#include "security\Securit2.h"
#include "security\ecomstation.inc"

/*******************************************************************************
*   Defined Constants And Macros                                               *
*******************************************************************************/
#ifndef DLL_PROCESS_DETACH
    #define DLL_PROCESS_DETACH  0       /* detach process (unload library) */
    #define DLL_PROCESS_ATTACH  1       /* attach process (load library) */
    #define DLL_THREAD_ATTACH   2       /* attach new thread */
    #define DLL_THREAD_DETACH   3       /* detach thread */
#endif


/*******************************************************************************
*   Global Variables                                                           *
*******************************************************************************/
/** Handle of the Custombbuild Odin Dll. */
//HMODULE                 ghmodOdinDll = NULLHANDLE;

/** OS/2 Handle of this DLL. */
HMODULE                 ghmodOurSelf = NULLHANDLE;

/** Odin32 Handle of this DLL. */
HINSTANCE               ghInstanceOurSelf = NULLHANDLE;

/** Flags wether or not to handle DLL_THREAD* events.
 * We need this for register/unregister process.
 */
BOOL                    gfHandleDllEvents = FALSE;

/** Global flag which tells if we init was successful or not.
 * If not successfull we have to stay in memory because Odin does so.
 */
BOOL                    gfInitSuccessful = FALSE;

BOOL                    gfLazyInitSuccessful = FALSE;

/** The plugin instance data. */
NPODINWRAPPER           gPlugin =
{
    sizeof(NPODINWRAPPER),
    "",
    "",
    NULLHANDLE,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

extern struct OdinEntryPoint aAPIs[];
extern int registered_apis;
int Registered = TRUE;

/*******************************************************************************
*   Internal Functions                                                         *
*******************************************************************************/
ULONG WIN32API      npOdinInitTerm(ULONG hInstance, ULONG reason, LPVOID reserved);

typedef APIRET (* APIENTRY PROC_DosSetThreadAffinity)(PMPAFFINITY pAffinity);

BOOL SetThreadAffinity()
{
    static PROC_DosSetThreadAffinity pfnDosSetThreadAffinity = NULL;
    MPAFFINITY  mask;
    APIRET      rc;

    ULONG nrCPUs;

    rc = DosQuerySysInfo(QSV_NUMPROCESSORS, QSV_NUMPROCESSORS, &nrCPUs, sizeof(nrCPUs));
    if (rc != 0 || nrCPUs == 1)
    {//not supported
        return TRUE;
    }

    HMODULE hDoscalls;
    if(DosQueryModuleHandle("DOSCALLS", &hDoscalls) == NO_ERROR) {
        DosQueryProcAddr(hDoscalls, 564, NULL, (PFN *)&pfnDosSetThreadAffinity);
    }
    if(pfnDosSetThreadAffinity == NULL) {
        return TRUE;
    }
    /* always run on 1st CPU */
    mask.mask[0] = 0x00000001;
    mask.mask[1] = 0; //TODO: this might not be a good idea, but then again, not many people have > 32 cpus

    rc = pfnDosSetThreadAffinity(&mask);

    return (rc == NO_ERROR);
}


/**
 * DLL Initialization and Termination entry point.
 * @returns 1 on success.
 * @returns 0 on failure
 * @param   hmod    Handle of this DLL.
 * @param   flFlags Flag(s) telling us which kind of call this is.
 *                  0: init
 *                  1: term
 */
unsigned long _System _DLL_InitTerm(unsigned long hmod, unsigned long
                                    ulFlag)
{
    switch (ulFlag)
    {
    case 0:
        {
            ULONG  ulBootDrv;
            CHAR pszRegName[] = "D:\\OS2\\ECSREG11.INI";

            /*
             * Init CRT and do C++ static initializations.
             */
            int rc = _CRT_init();
            if (rc)
            {
                //dprintf(("CRT_init rc: %d", rc));
                break;
            }
            ghmodOurSelf = hmod;

            ctordtorInit();

            SetThreadAffinity();

            //dprintf(("Flash plugin init term"));
#if 0
            /* checking for ECS 1.2 key via SecureIt API */
#if defined(DEBUG)
            KeyAllowDebugger();
#endif
            KeySetup(TRUE, FALSE, TRUE, 0x010101, &SIBlob, SIBlobLen);

            DosQuerySysInfo(QSV_BOOT_DRIVE, QSV_BOOT_DRIVE, &ulBootDrv, sizeof(ulBootDrv));

            pszRegName[0] = (char)(ulBootDrv + 'A' - 1);

            if (!KeySetNamePswIni(pszRegName, "eComStationRegistration"))
            {
                dprintf(("ECSREG11.INI not found\n"));
                Registered = FALSE;
            }

            if (!KeyCheck(TRUE))
            {
                // Check why KeyCheck failed
                switch (KeyGetSerialNumberStatus())
                {
                case snExpired:
                    dprintf(("Serial number expired")); break;

                case snLocked:
                    dprintf(("Key is locked")); break;

                default :
                    dprintf(("Unregistered")); break;
                }
                Registered = FALSE;
            }
#endif
            /*
             * Save the module handle as we will need it further down in the lazy init.
             */
            /*
             * Get the plugin names.
             */
            if (npprimaryGetPluginNames(gPlugin.szPluginDllName, sizeof(gPlugin.szPluginDllName),
                                        gPlugin.szPluginName, sizeof(gPlugin.szPluginName)))
            {
                if (npGenericInit(&gPlugin))
                {
                    gfInitSuccessful = TRUE;
                    dprintf(("Flash plugin inited successfully"));
                    return 1;
                }
                else
                {
                    dprintf(("Flash plugin init failed in npGenericInit"));
                    //@todo complain in any way?
                }
            }
            else
            {
                dprintf(("Flash plugin init failed in npprimaryGetPluginNames [%s]", gPlugin.szPluginDllName));
                //@todo complain in any way?
            }
            break;
        }

    case 1:
        {
            /*
             * Get memory stats if debug build.
             * This is too late for dprintf unfortunately :/
             */
            if (!gfInitSuccessful)
                return 1;
            //if (!gfHandleDllEvents)
            //    return 1; /* already detached */
            //#ifdef DEBUG
#if 0
            extern void _LNK_CONV getcrtstat(unsigned long *pnrcalls_malloc, unsigned long *pnrcalls_free, unsigned long *ptotalmemalloc);
            unsigned long cAllocs;
            unsigned long cFrees;
            unsigned long cbCurAllocated;
            getcrtstat(&cAllocs, &cFrees, &cbCurAllocated);
            dprintf(("#####OS/2######### Heap statistics (initterm) #####OS/2########"));
            dprintf((" cAllocs        = %d (%#x)", cAllocs, cAllocs));
            dprintf((" cFrees         = %d (%#x)", cFrees,  cFrees));
            dprintf((" cbCurAllocated = %d (%#x)", cbCurAllocated, cbCurAllocated));
            dprintf(("#####OS/2######### Heap statistics (initterm) #####OS/2########"));
#endif

            unsigned long oldmod = 0;

            /*
             * Deregister ourselfs.
             */
            dprintf(("starting unload procedure"));
            gfHandleDllEvents = FALSE;
            if (ghInstanceOurSelf)
            {
                odinUnregisterLxDll(ghInstanceOurSelf);
                ghInstanceOurSelf = NULLHANDLE;
            }
            dprintf(("DLL unregistered"));
#if 1
            /*
             * Unload the ODIN dlls.
             */
            for (int i = registered_apis-1; i >= 0; i--)
            {
                if (aAPIs[i].modInst && oldmod != aAPIs[i].modInst)
                {
                    DosFreeModule(aAPIs[i].modInst);
                    oldmod = aAPIs[i].modInst;
                    aAPIs[i].modInst = NULLHANDLE;
                }
            }
            registered_apis = 0;
            dprintf(("DLLs unloaded"));
#endif
            /*
             * Do C++ static terminatinos and terminate the CRT.
             */
            ctordtorTerm();
            _CRT_term();

            /*
             * Done.
             */
            gfInitSuccessful = FALSE;
            return 1;
        }
    }

    /*
     * Failure.
     */
    gfInitSuccessful = FALSE;
    return 0;
}

/**
 * Lazy inititiation of Odin and more.
 *
 * @returns Success indicator.
 */
BOOL    npInitTerm_Lazy(void)
{
    /*
     * Check if we're allready initiated.
     */
    if (gfLazyInitSuccessful)
        return TRUE;

    /*
     * Resolv the OdinAPIs we will use.
     */
    if (npResolveOdinAPIs())
    {
        /*
         * Register fake exe.
         */
        char    szFakeName[CCHMAXPATH];
        PPIB    ppib;
        PTIB    ptib;
        if (    DosGetInfoBlocks(&ptib, &ppib)
            ||  DosQueryModuleName(ppib->pib_hmte, sizeof(szFakeName), &szFakeName[0]))
            strcpy(&szFakeName[0], "c:\\mozilla\\mozilla.exe"); /* *must* include one or more '\\'!  */

        dprintf(("npInitTerm_Lazy: register fake exe [%s]", szFakeName));
        //odinSetFreeTypeIntegration(TRUE);
        if (odinRegisterDummyExe(&szFakeName[0]))
        {
            /*
             * Resolve mozilla APIs
             */
            if (npResolveMozAPIs())
            {
                /*
                 * Register our selfs a LxDll so we can catch CreateThread() events.
                 */
                gfHandleDllEvents = FALSE;
                ghInstanceOurSelf = odinRegisterLxDll(ghmodOurSelf, npOdinInitTerm, NULL, 0, 0, 0);
                if (ghInstanceOurSelf)
                {
                    gfHandleDllEvents = TRUE;
                    gfLazyInitSuccessful = TRUE;
                    dprintf(("npInitTerm_Lazy: ghInstanceOurSelf=%x", ghInstanceOurSelf));
                    return TRUE;
                }
                else
                    dprintf(("npInitTerm_Lazy: odinRegisterLxDll failed!"));
            }
            else
                dprintf(("npInitTerm_Lazy: ResolveMozAPIs failed!"));
        }
        else
            dprintf(("npInitTerm_Lazy: odinRegisterDummyExe failed!"));
    }
    else
    {
        //@todo complain
    }
    gfInitSuccessful = FALSE;
    return FALSE;
}


/**
 * Odin DLL entry point.
 * We use this for getting Thread Create and Destroy notifications so we can
 * help mozilla keep track of the threads.
 * @returns success indicator (TRUE/FALSE).
 */
ULONG WIN32API npOdinInitTerm(ULONG hInstance, ULONG fReason, LPVOID reserved)
{
    static const char szFunction[] = "npOdinInitTerm";

    switch (fReason)
    {
        case DLL_THREAD_ATTACH:
        {
            dprintf(("%s: DLL_THREAD_ATTACH. Instance: 0x%X", szFunction, hInstance));
            if (gfHandleDllEvents)
            {
                USHORT selFSOld = pfnODIN_ThreadLeaveOdinContextNested(NULL, FALSE);
                /*
                 * On Win32 PR_GetCurrentThread actually calls _PRI_AttachThread()
                 * we here work around that OS/2 bug. If this is fixed in the
                 * OS/2 Mozilla this code will still work as PR_GetCurrentThread
                 * will succeed.
                 */
                PRThread * pThread = mozPR_GetCurrentThread();
                if (!pThread)
                {
                    if (pfn_PRI_AttachThread)
                    {
                        dprintf(("%s: calling moz_PRI_AttachThread", szFunction));
                        pThread = moz_PRI_AttachThread(PR_USER_THREAD, PR_PRIORITY_NORMAL, NULL, 0);
                    }
                    else
                    {
                        dprintf(("%s: DLL_THREAD_ATTACH we're f**ked mozilla 1.3b or final !!!!", szFunction));
                    }
                }
                pfnODIN_ThreadEnterOdinContextNested(NULL, FALSE, selFSOld);
            }
            dprintf(("%s: DLL_THREAD_ATTACHED", szFunction));
            return TRUE;
        }

        case DLL_THREAD_DETACH:
        {
            dprintf(("%s: DLL_THREAD_DETACH. Instance: 0x%X", szFunction, hInstance));
            if (gfHandleDllEvents)
            {
                #if 1
                USHORT selFSOld = pfnODIN_ThreadLeaveOdinContextNested(NULL, FALSE);
                /*
                 * On Win32 NSPR4 will also receive this event and do what we now
                 * are doing here.
                 */
                PRThread * pThread = mozPR_GetCurrentThread();
                if (pThread/* && pThread->flags & _PR_ATTACHED */) //@todo should test on these flags!
                {
                    if (pfn_PRI_DetachThread)
                    {
                        dprintf(("%s: calling moz_PRI_DetachThread", szFunction));
                        moz_PRI_DetachThread();
                    }
                    else
                    {
                        dprintf(("%s: calling mozPR_DetachThread", szFunction));
                        mozPR_DetachThread();
                    }
                }
                pfnODIN_ThreadEnterOdinContextNested(NULL, FALSE, selFSOld);
                #endif
            }

            /*
             * Get memory stats if debug build.
             */
            #ifdef DEBUG
            extern void _LNK_CONV getcrtstat(unsigned long *pnrcalls_malloc, unsigned long *pnrcalls_free, unsigned long *ptotalmemalloc);
            unsigned long cAllocs;
            unsigned long cFrees;
            unsigned long cbCurAllocated;
            getcrtstat(&cAllocs, &cFrees, &cbCurAllocated);
            dprintf(("#####ODIN######### npj2 Heap statistics ######ODIN#######"));
            dprintf((" cAllocs        = %d (%#x)", cAllocs, cAllocs));
            dprintf((" cFrees         = %d (%#x)", cFrees,  cFrees));
            dprintf((" cbCurAllocated = %d (%#x)", cbCurAllocated, cbCurAllocated));
            dprintf(("####InitTerm###### npj2 Heap statistics ####InitTerm#####"));
            #endif
            return TRUE;
        }

        /* Ignore these */
        case DLL_PROCESS_DETACH:
        case DLL_PROCESS_ATTACH:
            dprintf(("%s: DLL_THREAD_ATTACH/DETACH", szFunction));
            return TRUE;
    }

    /* Failure if we ever get here (default) */
    return FALSE;
}



/*
 * XPCOM interfaces
 */
extern "C" PR_IMPLEMENT(nsresult) NSGetFactory(nsISupports* aServMgr, const nsCID &aClass, const char *aClassName,
                                               const char *aContractID, nsIFactory **aFactory)
{
    return gPlugin.pfnNSGetFactory(aServMgr, aClass, aClassName, aContractID, aFactory, &gPlugin);
}

extern "C" PR_IMPLEMENT(PRBool)   NSCanUnload(nsISupports* aServMgr)
{
    return gPlugin.pfnNSCanUnload(aServMgr, &gPlugin);
}

extern "C" PR_IMPLEMENT(nsresult) NSRegisterSelf(nsISupports* aServMgr, const char *fullpath)
{
    return gPlugin.pfnNSRegisterSelf(aServMgr, fullpath, &gPlugin);
}

extern "C" PR_IMPLEMENT(nsresult) NSUnregisterSelf(nsISupports* aServMgr, const char *fullpath)
{
    return gPlugin.pfnNSUnregisterSelf(aServMgr, fullpath, &gPlugin);
}


/*
 * Netscape v4.x interfaces
 */
NPError OSCALL NP_GetEntryPoints(NPPluginFuncs* pFuncs)
{
    return gPlugin.pfnNP_GetEntryPoints(pFuncs, &gPlugin);
}

NPError OSCALL NP_Initialize(NPNetscapeFuncs* pFuncs)
{
    return gPlugin.pfnNP_Initialize(pFuncs, &gPlugin);
}

NPError OSCALL NP_Shutdown()
{
    return gPlugin.pfnNP_Shutdown(&gPlugin);
}

char * NP_GetMIMEDescription()
{
    return gPlugin.pfnNP_GetMIMEDescription(&gPlugin);
}

/* unix only?!? */
NPError OSCALL NP_GetValue(NPP future, NPPVariable aVariable, void *aValue)
{
    return gPlugin.pfnNP_GetValue(future, aVariable, aValue, &gPlugin);
}

