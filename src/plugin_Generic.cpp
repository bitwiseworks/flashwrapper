/* $Id: plugin_Generic.cpp,v 1.3 2004/03/08 19:22:56 bird Exp $
 *
 * Odin Generic Plugin Wrapper.
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
#ifdef __IBMCPP__
# include "moz_VACDefines.h"
#else
# include "moz_GCCDefines.h"
#endif

#define INCL_BASE
#define INCL_PM
#include <os2.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define INCL_NS4X
#include "common.h"

#ifdef __IBMCPP__
/*
 * This weak resolving ASSUMES that the caller cleans the stack!
 * (i.e. anything but __stdcall calling convention will work very nicely.)
 */
extern "C" unsigned npGenericNPWeakStub(void);
#pragma weak(npGenericNP_GetEntryPoints,        npGenericNPWeakStub)
#pragma weak(npGenericNP_Initialize,            npGenericNPWeakStub)
#pragma weak(npGenericNP_Shutdown,              npGenericNPWeakStub)
#pragma weak(npGenericNP_GetValue,              npGenericNPWeakStub)
#pragma weak(npGenericNP_GetMIMEDescription,    npGenericNPWeakStub)
#endif

/**
 * Query the XPM interface of the
 * @returns Success indicator.
 * @param   pPlugin     Pointer to plugin wrapper instance structure.
 * @remark  dprintf() doesn't work at this time as it uses the odin log facility.
 */
BOOL    npGenericInit(PNPODINWRAPPER pPlugin)
{
    // Validate input.
    if (!VALID_PTR(pPlugin) || pPlugin->cb != sizeof(*pPlugin) ||
        !pPlugin->szPluginDllName[0]) {
        dprintff("pPlugin is invalid !!!");
        //DebugInt3();
        return FALSE;
    }

    // Verify the existence of the Plugin DLL.
    FILESTATUS3     fst3;
    APIRET arc;
    if ((arc = DosQueryPathInfo(pPlugin->szPluginDllName, FIL_STANDARD,
                         &fst3, sizeof(fst3))) ||
        (fst3.attrFile & FILE_DIRECTORY) || fst3.cbFile < 1024) {
        dprintff("Bad plugin file [%s]", pPlugin->szPluginDllName);
        //DebugInt3();
        char msg[CCHMAXPATH + 128];
        sprintf(msg, "Plugin file '%s' %s!\n\nDOS Error: %d", pPlugin->szPluginDllName,
                arc ? "could not be found" : "is invalid", arc);
        npGenericErrorBox(msg, FALSE);
        return FALSE;
    }

    // Get plugin description
    DWORD dummy, versize;
    void *verbuf;
    versize = odinGetFileVersionInfoSize(pPlugin->szPluginDllName, &dummy);
    dprintff("Win32 versize %d", versize);
    if (versize > 0)
      verbuf = malloc(versize);
    if (verbuf) {
        if (odinGetFileVersionInfo(pPlugin->szPluginDllName, NULL, versize, verbuf)) {
            // For now, we use language 1033 (English) and CP 1252 (Western) as this is
            // what seems to be used in Firefox too
            char *buf;
            UINT len;
            if (odinVerQueryValue(verbuf, "\\StringFileInfo\\040904E4\\FileDescription",
                                  (void **)&buf, &len)) {
                dprintf("Win32 FileDescription %*.*s", len, len, buf);
                // @todo export FileDescription through NP_GetValue(NPPVpluginDescriptionString),
                // see nsPluginsDirUnix.cpp in mozilla (needs altering nsPluginsDirOS2.cpp as well)
            }
        }
        free(verbuf);
    }

    // Initialize the native entry points.
    pPlugin->pfnNP_GetEntryPoints     = npGenericNP_GetEntryPoints;
    pPlugin->pfnNP_Initialize         = npGenericNP_Initialize;
    pPlugin->pfnNP_Shutdown           = npGenericNP_Shutdown;
    pPlugin->pfnNP_GetValue           = npGenericNP_GetValue;
    pPlugin->pfnNP_GetMIMEDescription = npGenericNP_GetMIMEDescription;

    dprintff("Successfully initialized '%s'", pPlugin->szPluginDllName);
    return TRUE;
}


/**
 * Lazy init which the workers will call the first time a plugin is accessed.
 *
 * This lazy init of the plugin wrapper was done to speed up brower startup.
 * However this only works with old Netscape styled plugins.
 *
 * @returns Success indicator.
 * @param   pPlugin     Pointer to plugin wrapper instance structure.
 */
BOOL    npGenericLazyInit(PNPODINWRAPPER pPlugin)
{
    // No use to pretend plugins load when we didn't init correctly ourselves.
    if (!gfInitSuccessful) {
        //DebugInt3();
        return FALSE;
    }

    // Check that the plugin isn't already initialized.
    if (pPlugin->hmodPlugin)
        return TRUE;

    // Init the odin++ stuff first.
    if (!npInitTerm_Lazy()) {
        //DebugInt3();
        //@todo proper complaint.
        npGenericErrorBox("Failed to load Flash Win32 plugin.", FALSE);
        return FALSE;
    }

    // Load the Wrapped Plugin DLL.
    pPlugin->hmodPlugin = odinLoadLibrary(pPlugin->szPluginDllName);
    if (!pPlugin->hmodPlugin) {
        dprintff("odinLoadLibrary(%s) failed !!!", pPlugin->szPluginDllName);
        //DebugInt3();
        npGenericErrorBox("Failed to load Flash Win32 plugin.", FALSE);
        return FALSE;
    }

    // Resolve entry points.
    // @todo perhaps change this to use offsets into pPlugin and hence being static...
    struct EntryPoints
    {
        FARPROC *   ppfn;
        const char *psz;
    }   aExports[] =
    {
        { (FARPROC*)&pPlugin->pfnW32NP_GetEntryPoints,      "NP_GetEntryPoints" },
        { (FARPROC*)&pPlugin->pfnW32NP_Initialize,          "NP_Initialize" },
        { (FARPROC*)&pPlugin->pfnW32NP_Shutdown,            "NP_Shutdown" },
        { (FARPROC*)&pPlugin->pfnW32NP_GetValue,            "NP_GetValue" },
        { (FARPROC*)&pPlugin->pfnW32NP_GetMIMEDescription,  "NP_GetMIMEDescription" },
    };

    for (int i = 0; i < sizeof(aExports) / sizeof(aExports[0]); i++) {
        *aExports[i].ppfn = odinGetProcAddress(pPlugin->hmodPlugin, aExports[i].psz);
        dprintff("%s -> 0x%08x", aExports[i].psz, *aExports[i].ppfn);
    }

    // Minimum requirement is NP_GetEntryPoints support
    if (!pPlugin->pfnW32NP_GetEntryPoints) {
        dprintff("no NP_GetEntryPoints export!");
        odinFreeLibrary(pPlugin->hmodPlugin);
        //DebugInt3();
        npGenericErrorBox("Invalid Flash Win32 plugin.", FALSE);
        return FALSE;
    }

    dprintff("Successfully initialized '%s'", pPlugin->szPluginDllName);
    return TRUE;
}



/**
 * Sets up an error box to inform the user of some kind of failure.
 *
 * Note that when fYesNo is TRUE, the message box is application modal (i.e. this function does not
 * return until the user dismisses the message box). This is known to cause problems (crashes, etc)
 * when used at inappropriate times (i.e. during DLL init).
 *
 * @returns 0 on success and !fYesNo.
 * @returns 0 if fYesNo and user pressed YES.
 * @returns 1 if fYesNo and user pressed NO.
 * @returns -1 on failure.
 * @param   pszMessage  The message which the users should be presented with.
 * @param   fYesNo      If clear it will become a OK only dialog.
 *                      If set a YES NO dialog is displayed.
 */
int     npGenericErrorBox(const char *pszMessage, BOOL fYesNo)
{
    dprintff("pszMessage '%s', fYesNo %d", pszMessage, fYesNo);

    ULONG rc;
    ULONG fFlags = MB_ERROR | MB_MOVEABLE;

    MB2D buttons[] = {
        { "OK", MBID_OK, BS_PUSHBUTTON | BS_DEFAULT },
        { "Yes", MBID_YES, BS_PUSHBUTTON },
        { "No", MBID_NO, BS_PUSHBUTTON },
    };

    MB2D *pbuttons;
    ULONG cbuttons;
    if (fYesNo) {
        pbuttons = &buttons[1];
        cbuttons = 2;
    } else {
        pbuttons = &buttons[0];
        cbuttons = 1;
        fFlags |= MB_NONMODAL;
    }

    MB2INFO *info;
    ULONG cinfo = sizeof(MB2INFO) + sizeof(MB2D) * cbuttons;
    info = (MB2INFO *)malloc(cinfo);
    info->cb = cinfo;
    info->hIcon = NULLHANDLE;
    info->cButtons = cbuttons;
    info->flStyle = fFlags;
    info->hwndNotify = NULLHANDLE;

    memcpy(info->mb2d, pbuttons, sizeof(MB2D) * cbuttons);

    rc = WinMessageBox2(HWND_DESKTOP, WinQueryActiveWindow(HWND_DESKTOP), pszMessage,
                        "Flash Plugin: Error", 0, info);

    free(info);

    dprintff("rc %d", rc);

    return rc == MBID_ERROR ? -1 :
           !fYesNo || rc == MBID_YES ? 0 : 1;
}

