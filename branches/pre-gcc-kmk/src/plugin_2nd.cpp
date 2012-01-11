/* $Id: plugin_2nd.cpp,v 1.4 2004/03/08 19:22:56 bird Exp $
 *
 * Generic Mozilla Plugin Wrapper for Odin.
 *
 * InnoTek Systemberatung GmbHconfidential
 *
 * Copyright (c) 2003 InnoTek Systemberatung GmbH
 * Author: knut st. osmundsen <bird@anduin.net>
 *
 * All Rights Reserved
 *
 */

#ifdef __IBMCPP__
/* Try get ridd of the CONST32_RO segment.*/
#pragma strings(writable)
#endif


/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/
#ifdef __IBMCPP__
# include "moz_VACDefines.h"
#else
# include "moz_GCCDefines.h"
#endif

#define INCL_BASE
#include <os2.h>

#include <string.h>

/* the mozilla headers */
#include "moz\sdk\xpcom\include\nsIServiceManager.h"
#include "moz\sdk\xpcom\include\nsIFactory.h"
#include "moz\include\plugin\npapi.h"
#include "moz\include\plugin\npupp.h"

#define INCL_MOZXPCOM
#define INCL_NS4X
#include "common.h"
#include "plugin_2nd.h"


/*******************************************************************************
*   Global Variables                                                           *
*******************************************************************************/
/** Handle of the Odin Plugin wrapper DLL. */
HMODULE             ghmodNpOdin = NULLHANDLE;

/** The plugin instance data. */
NPODINWRAPPER       gPlugin =
{
    sizeof(NPODINWRAPPER),
    "",
    "",
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL
};


/*******************************************************************************
*   External Functions                                                         *
*******************************************************************************/

/**
 * DLL Initialization and Termination entry point.
 * @returns 1 on success.
 * @returns 0 on failure
 * @param   hmod    Handle of this DLL.
 * @param   flFlags Flag(s) telling us which kind of call this is.
 *                  0: init
 *                  1: term
 */
extern ULONG EXPENTRY _DLL_InitTerm(HMODULE hmod, ULONG flFlags)
{
    switch (flFlags)
    {
        case 0:
            int     rc;
            char    szPrimaryDLL[8+3+2];

            /*
             * Get the (DLL) names.
             */
            if (np2ndaryGetPluginNames(gPlugin.szPluginDllName, sizeof(gPlugin.szPluginDllName),
                                       gPlugin.szPluginName, sizeof(gPlugin.szPluginName),
                                       szPrimaryDLL, sizeof(szPrimaryDLL)))
            {
                /*
                 * Figure out where the Odin Plugin Wrapper DLL is located.
                 *      Same directory as ourselfs, so we just need to figure that out
                 *      and replace the filename.
                 */
                PPIB    ppib;
                PTIB    ptib;
                CHAR    szPath[CCHMAXPATH];
                if (    DosQueryModuleName(hmod, sizeof(szPath), &szPath[0])
                    ||  !strchr(&szPath[0], '\\')
                        )
                {
                    /* this shouldn't happen! */
                    DebugInt3();
                    strcpy(&szPath[0], ".\\plugins\\");
                }
                strcpy(strrchr(&szPath[0], '\\') + 1, szPrimaryDLL);

                /*
                 * Try load this DLL!
                 */
                rc = DosLoadModule(NULL, 0, &szPath[0], &ghmodNpOdin);
                if (!rc)
                {
                    PFNNPGENERICINIT pfnGenericInit = NULL;
                    rc = DosQueryProcAddr(ghmodNpOdin, NP_ORD_NPGENERICINIT, NULL, (PFN*)&pfnGenericInit);
                    if (!rc)
                    {
                        if (pfnGenericInit(&gPlugin))
                        {
                            /* Successfully initiated! */
                            return 1;
                        }
                        else
                            DebugInt3();
                    }
                    else
                        DebugInt3();
                    DosFreeModule(ghmodNpOdin);
                    ghmodNpOdin = NULLHANDLE;
                }
                else
                    DebugInt3();
            }
            else
                DebugInt3();
            break;


        case 1:
            #ifdef DEBUG
            /*
             * Assert that we don't get here unless we're 100% successfully loaded!
             */
            if (!ghmodNpOdin)
                DebugInt3();
            #endif

            /*
             * Unload the Odin Plugin Wrapper DLL.
             */
            if (ghmodNpOdin)
            {
                DosFreeModule(ghmodNpOdin);
                ghmodNpOdin = NULLHANDLE;
            }
            return 1;
        }

    /*
     * If we get here we failed!
     */
    return 0;
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

