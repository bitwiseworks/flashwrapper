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
#include <os2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <initdll.h>                    /* odin stuff. */
#include "plugin_primary.h"

#define INCL_NS4X
#define INCL_MOZAPIS
#include "common.h"

#include "security\Securit2.h"
#include "security\ecomstation12.inc"
#include "security\ecomstation20.inc"

/*******************************************************************************
*   Defined Constants And Macros                                               *
*******************************************************************************/
#ifndef DLL_PROCESS_DETACH
    #define DLL_PROCESS_DETACH  0       /* detach process (unload library) */
    #define DLL_PROCESS_ATTACH  1       /* attach process (load library) */
    #define DLL_THREAD_ATTACH   2       /* attach new thread */
    #define DLL_THREAD_DETACH   3       /* detach thread */
#endif

/* from winuser32.h */
#define OS2_APPEARANCE_SYSMENU  2

/*******************************************************************************
*   Global Variables                                                           *
*******************************************************************************/

// OS/2 Handle of this DLL
HMODULE         ghmodOurSelf = NULLHANDLE;

// Odin32 Handle of this DLL
HINSTANCE       ghInstanceOurSelf = NULLHANDLE;

// Flags whether or not to handle DLL_THREAD* events.
// We need this for register/unregister process.
BOOL            gfHandleDllEvents = FALSE;

// Global flag which tells if we init was successful or not.
// If not successfull we have to stay in memory because Odin does so.
BOOL            gfInitSuccessful = FALSE;

BOOL            gfLazyInitSuccessful = FALSE;

// Is eCS registered?
int             Registered = FALSE;

/** The plugin instance data. */
NPODINWRAPPER   gPlugin =
{
    sizeof(NPODINWRAPPER),  // cb
    "",                     // szPluginDllName
    "",                     // szPluginName
    NULLHANDLE,             // hmodPlugin
    NULL,                   // pfnNP_GetEntryPoints
    NULL,                   // pfnNP_Initialize
    NULL,                   // pfnNP_Shutdown
    NULL,                   // pfnNP_GetValue
    NULL,                   // pfnNP_GetMIMEDescription
    NULL,                   // pfnW32NP_GetEntryPoints
    NULL,                   // pfnW32NP_Initialize
    NULL,                   // pfnW32NP_Shutdown
    NULL,                   // pfnW32NP_GetValue
    NULL                    // pfnW32NP_GetMIMEDescription
};

// used to unload the Odin dlls at termination
extern struct OdinEntryPoint aAPIs[];
extern int                   registered_apis;

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
    switch (ulFlag) {

        case 0: {
            gfInitSuccessful = FALSE;

            // Init CRT and do C++ static initializations.
            int rc = _CRT_init();
            if (rc) {
                //dprintf(("CRT_init rc: %d", rc));
                return 0;
            }

            ctordtorInit();

#if 0
            SetThreadAffinity();
#endif

            //dprintf(("Flash plugin init term"));

#if defined(DEBUG)
	    Registered = TRUE;
#else

            // check for ECS 1.2 key via SecureIt API
#if defined(DEBUG)
            KeyAllowDebugger();
#endif

            ULONG  ulBootDrv;
            CHAR pszRegName[] = "D:\\OS2\\ECSREG11.INI";

            DosQuerySysInfo(QSV_BOOT_DRIVE, QSV_BOOT_DRIVE, &ulBootDrv, sizeof(ulBootDrv));
            pszRegName[0] = (char)(ulBootDrv + 'A' - 1);

            // test 1.2 key
            KeySetup(TRUE, FALSE, TRUE, 0x010101, &SIBlob, SIBlobLen);

            // must be always set after KeySetup
            if (!KeySetNamePswIni(pszRegName, "eComStationRegistration")) {
                dprintf(("ECSREG11.INI not found\n"));
                Registered = FALSE;
            } else if (!KeyCheck(TRUE)) {

                // Check why KeyCheck failed
                switch (KeyGetSerialNumberStatus()) {
                    case snExpired:
                        dprintf(("Serial number expired"));
                        break;
                    case snLocked:
                        dprintf(("Key is locked"));
                        break;
                    default:
                        dprintf(("Unregistered"));
                        break;
                }
                Registered = FALSE;
            } else {
		dprintf(("Test 1.2: registered"));
                Registered = TRUE;
	    }

	    if (Registered == FALSE) {
		// test 2.0 key
		dprintf(("Testing 2.0 key\n"));
		KeySetup(TRUE, FALSE, TRUE, 0x010121, &SIBlob20, SIBlobLen20);

		// must be always set after KeySetup
		if (!KeySetNamePswIni(pszRegName, "eComStationRegistration")) {
		    dprintf(("ECSREG11.INI not found\n"));
		    Registered = FALSE;
		} else if (!KeyCheck(TRUE)) {
    
		    // Check why KeyCheck failed
		    switch (KeyGetSerialNumberStatus()) {
			case snExpired:
			    dprintf(("Serial number expired"));
			    break;
			case snLocked:
			    dprintf(("Key is locked"));
			    break;
			default:
			    dprintf(("Unregistered"));
			    break;
		    }
		    Registered = FALSE;
		} else {
		    dprintf(("Test 2.0: registered"));
		    Registered = TRUE;
		}

	    }
#endif // DEBUG

            // Save the module handle as we will need it further down in the lazy init.
            ghmodOurSelf = hmod;

            // Get the plugin names.
            if (!npprimaryGetPluginNames(gPlugin.szPluginDllName,
                                        sizeof(gPlugin.szPluginDllName),
                                        gPlugin.szPluginName,
                                        sizeof(gPlugin.szPluginName))) {
                dprintf(("Flash plugin init failed in npprimaryGetPluginNames [%s]",
                         gPlugin.szPluginDllName));
                return 0;
            }

            if (!npInitTerm_Lazy()) {
                dprintf(("Flash plugin init failed in npInitTerm_Lazy"));
                return 0;
            }

            if (!npGenericInit(&gPlugin)) {
                dprintf(("Flash plugin init failed in npGenericInit"));
                return 0;
            }

            gfInitSuccessful = TRUE;
            dprintf(("Flash plugin inited successfully"));
            return 1;
        }

        case 1: {
            // Get memory stats if debug build.
            // This is too late for dprintf unfortunately
            if (!gfInitSuccessful)
                return 1;

            // already detached
            //if (!gfHandleDllEvents)
            //    return 1; 

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

            // Deregister ourselfs.
            dprintf(("starting unload procedure"));
            gfHandleDllEvents = FALSE;

            if (ghInstanceOurSelf) {
                odinUnregisterLxDll(ghInstanceOurSelf);
                ghInstanceOurSelf = NULLHANDLE;
            }
            dprintf(("DLL unregistered"));

            // Unload the ODIN dlls.
            for (int i = registered_apis-1; i >= 0; i--) {
                if (aAPIs[i].modInst && oldmod != aAPIs[i].modInst) {
                    DosFreeModule(aAPIs[i].modInst);
                    oldmod = aAPIs[i].modInst;
                    aAPIs[i].modInst = NULLHANDLE;
                }
            }
            registered_apis = 0;
            dprintf(("DLLs unloaded"));

            // Do C++ static terminations and terminate the CRT.
            ctordtorTerm();
            _CRT_term();

            // Done.
            gfInitSuccessful = FALSE;
            return 1;
        }
    }

    // We should never reach here.
    return 0;
}

/**
 * Lazy inititiation of Odin and more.
 * @returns Success indicator.
 */
BOOL    npInitTerm_Lazy(void)
{
    // Check if we're allready initialized
    if (gfLazyInitSuccessful)
        return TRUE;

    gfInitSuccessful = FALSE;

    // Resolv the OdinAPIs we will use.
    if (!npResolveOdinAPIs()) {
        //@todo complain
        return FALSE;
    }

    // set OS/2 look&feel
    odinSetWindowAppearance( OS2_APPEARANCE_SYSMENU);
    // enable flash audio code
    odinEnableFlashAudio( TRUE);
    
    // Register fake exe.
    char    szFakeName[CCHMAXPATH];
    PPIB    ppib;
    PTIB    ptib;

    // this *must* include one or more '\\' !
    if (DosGetInfoBlocks(&ptib, &ppib) ||
        DosQueryModuleName(ppib->pib_hmte, sizeof(szFakeName), szFakeName))
        strcpy(&szFakeName[0], "c:\\mozilla\\mozilla.exe"); 

    dprintf(("npInitTerm_Lazy: register fake exe [%s]", szFakeName));
    //odinSetFreeTypeIntegration(TRUE);
    if (!odinRegisterDummyExe(szFakeName)) {
        dprintf(("npInitTerm_Lazy: odinRegisterDummyExe failed!"));
        return FALSE;
    }

    // Resolve mozilla APIs
    if (!npResolveMozAPIs()) {
        dprintf(("npInitTerm_Lazy: ResolveMozAPIs failed!"));
        return FALSE;
    }

    // Register ourself as an LxDll so we can catch CreateThread() events
    gfHandleDllEvents = FALSE;
    ghInstanceOurSelf = odinRegisterLxDll(ghmodOurSelf, npOdinInitTerm, NULL, 0, 0, 0);
    if (!ghInstanceOurSelf) {
        dprintf(("npInitTerm_Lazy: odinRegisterLxDll failed!"));
        return FALSE;
    }

    gfHandleDllEvents = TRUE;
    gfLazyInitSuccessful = TRUE;
    dprintf(("npInitTerm_Lazy: ghInstanceOurSelf=%x", ghInstanceOurSelf));
    return TRUE;
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

    switch (fReason) {

        case DLL_THREAD_ATTACH: {

            dprintf(("%s: DLL_THREAD_ATTACH. Instance: 0x%X", szFunction, hInstance));
            if (gfHandleDllEvents) {

                USHORT selFSOld = pfnODIN_ThreadLeaveOdinContextNested(NULL, FALSE);

                // On Win32 PR_GetCurrentThread actually calls _PRI_AttachThread()
                // we here work around that OS/2 bug. If this is fixed in the
                // OS/2 Mozilla this code will still work as PR_GetCurrentThread
                // will succeed.

                PRThread * pThread = mozPR_GetCurrentThread();
                if (!pThread) {
                    if (pfn_PRI_AttachThread) {
                        dprintf(("%s: calling moz_PRI_AttachThread", szFunction));
                        pThread = moz_PRI_AttachThread(PR_USER_THREAD, PR_PRIORITY_NORMAL, NULL, 0);
                    }
                    else
                        dprintf(("%s: DLL_THREAD_ATTACH we're f**ked mozilla 1.3b or final !!!!", szFunction));
                }
                pfnODIN_ThreadEnterOdinContextNested(NULL, FALSE, selFSOld);
            }

            dprintf(("%s: DLL_THREAD_ATTACHED", szFunction));
            return TRUE;
        }

        case DLL_THREAD_DETACH: {

            dprintf(("%s: DLL_THREAD_DETACH. Instance: 0x%X", szFunction, hInstance));
            if (gfHandleDllEvents) {

                USHORT selFSOld = pfnODIN_ThreadLeaveOdinContextNested(NULL, FALSE);

                // On Win32 NSPR4 will also receive this event and do what we now
                // are doing here.

                PRThread * pThread = mozPR_GetCurrentThread();
                //@todo should test on these flags!
                if (pThread/* && pThread->flags & _PR_ATTACHED */) {
                    if (pfn_PRI_DetachThread) {
                        dprintf(("%s: calling moz_PRI_DetachThread", szFunction));
                        moz_PRI_DetachThread();
                    }
                    else {
                        dprintf(("%s: calling mozPR_DetachThread", szFunction));
                        mozPR_DetachThread();
                    }
                }
                pfnODIN_ThreadEnterOdinContextNested(NULL, FALSE, selFSOld);
            }

            // Get memory stats if debug build.
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

        // Ignore these
        case DLL_PROCESS_DETACH:
        case DLL_PROCESS_ATTACH:
            dprintf(("%s: DLL_PROCESS_ATTACH/DETACH", szFunction));
            return TRUE;
    }

    // Failure if we ever get here (default)
    return FALSE;
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

// unix only?!?
NPError OSCALL NP_GetValue(NPP future, NPPVariable aVariable, void *aValue)
{
    return gPlugin.pfnNP_GetValue(future, aVariable, aValue, &gPlugin);
}

