/*
 * npflos2.cpp - initterm helpers for main wrapper dll.
 *      We implement the custombuild specifics for find the dll and initiating
 *      the plugin wrapper here. initterm calls us.
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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define INCL_WINSHELLDATA
#define INCL_BASE
#include <os2.h>
#include <win32type.h>

#define NPODIN_NS4X
#include "plugin_primary.h"
#include "common.h"

/*******************************************************************************
*   External Functions                                                         *
*******************************************************************************/

#define MAKE_BUILDNR(major, minor)      ((major << 16) | minor)
#define MAJOR_BUILDNR(buildnr)          (buildnr >> 16)
#define MINOR_BUILDNR(buildnr)          (buildnr & 0xffff)

#define WIN32DLL_DEFAULT_NAME           "npswf32.dll"

/**
 * This function returns all the win32 dll names.
 *
 * Any version checking and such should be done when this function is called.
 *
 * @returns Success indicator.
 * @param   hmodWrapper         Wrapper DLL handle.
 * @param   pszPluginDllName    Buffer to store the DLL name.
 * @param   cchPluginDllName    Size of DLL name buffer.
 */
extern BOOL npprimaryGetPluginNames(HMODULE hmodWrapper, char *pszPluginDllName,
                                    int cchPluginDllName)
{
    APIRET rc;

    /*
     * First, see if there is a direct specification of the DLL in the env.
     */
    const char *pszWin32Dll = getenv("NPFLOS2_WIN32DLL");
    if (pszWin32Dll)
    {
        if (strlen(pszWin32Dll) + 1 > cchPluginDllName)
            return FALSE;
        strcpy(pszPluginDllName, pszWin32Dll);
        return TRUE;
    }

    /*
     * If not, deduce the path from the wrapper DLL location.
     */
    rc = DosQueryModuleName(hmodWrapper, cchPluginDllName, pszPluginDllName);
    if (rc != NO_ERROR)
        return FALSE;

    char *psz = strrchr(pszPluginDllName, '\\');
    if (!psz ||
        (psz - pszPluginDllName) + 1 + sizeof(WIN32DLL_DEFAULT_NAME) > cchPluginDllName)
        return FALSE;

    strcpy(psz + 1, WIN32DLL_DEFAULT_NAME);
    return TRUE;
}

/**
 * Checks the build number of the custombuild dll after the lazy init have
 * loaded it. Other checks can be performed as well.
 *
 * @returns TRUE if ok.
 * @returns FALSE if not ok and loading should be stopped.
 * @param   hmodOdin    Module handle of DosLoadModule'ed custombuild dll.
 */
extern BOOL npprimaryCheckBuildNumber(HMODULE hmodOdin)
{
    unsigned    uBuild = 0;
    unsigned (*WIN32API      pfnGetBuildNumber)(void);
    void     (*WIN32API      pfnSetPluginVersion)(ULONG);

    if (!DosQueryProcAddr(hmodOdin, 0, "SetPluginVersion", (PFN*)&pfnSetPluginVersion))
    {
        pfnSetPluginVersion(90);
    }
    else goto fail;

    if (!DosQueryProcAddr(hmodOdin, 0, "_GetBuildNumber@0", (PFN*)&pfnGetBuildNumber))
        if ((uBuild = pfnGetBuildNumber()) == MAKE_BUILDNR(9, 0))
            return TRUE;

fail:
    char szMsg[256];
    sprintf(szMsg, "Flash Plugin build mismatch!\r\rPlugin build: %d\r\rFlash build: %d\r\rUse the plugin anyway?",
            10, uBuild);
    DosSleep(0);
    int rc = WinMessageBox(HWND_DESKTOP, HWND_DESKTOP, szMsg, "Flash Plugin (NPFL)", 0,
                           MB_YESNO | MB_MOVEABLE | MB_WARNING | MB_APPLMODAL);
    return (rc == MBID_YES);
}

