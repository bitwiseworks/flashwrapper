/* $Id: nparos2.cpp,v 1.8 2004/02/13 16:38:28 bird Exp $
 *
 * nparos2.cpp - initterm helpers for main wrapper dll.
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
#define INCL_WINSHELLDATA
#define INCL_BASE
#include <os2.h>
#include <string.h>
#include <stdio.h>
#include <win32type.h>
//#include <custombuild.h>
//#include <aros2build.h>

#define NPODIN_NS4X
#include "plugin_primary.h"
#include "common.h"


/*******************************************************************************
*   External Functions                                                         *
*******************************************************************************/
extern "C" {
extern unsigned _System RegOpenKey(HANDLE hKey, const char *pszSubKey, PHANDLE phKey);
extern unsigned _System RegCloseKey(HANDLE hKey);
extern unsigned _System RegQueryValueEx (HANDLE hKey, const char *pszValueName, unsigned uReserved,
                                        unsigned *pfType, void *pvValue, unsigned *pcbValue);
}
#define HKEY_LOCAL_MACHINE      ((HANDLE)0xFFFFFFEFL)
#define KEY_READ                0x00020019

#define MAKE_BUILDNR(major, minor)      ((major << 16) | minor)
#define MAJOR_BUILDNR(buildnr)          (buildnr >> 16)
#define MINOR_BUILDNR(buildnr)          (buildnr & 0xffff)

#define INNOWIN_REGISTRY_BASE      "Software\\"
#define INNOWIN_REG_CURRENTUSER    "REGROOT_HKEY_CurrentUser"
#define INNOWIN_REG_LOCAL_MACHINE  "REGROOT_HKEY_LocalMachine"
#define INNOWIN_REG_USERS          "REGROOT_HKEY_Users"


/**
 * Get the full path to the ODIN dlls to use for the plugins.
 *
 * @returns Success indicator.
 * @param   pszCustomDllName    Buffer to store the custom dll name in.
 * @param   cchCustomDllName    Size of the buffer.
 */

extern BOOL npprimaryGetOdinPath(char *pszCustomDllName, int cchCustomDllName)
{
    APIRET rc  = 1;
    ULONG  ulBootDrv;
    PSZ szODINPath = "";

    if (!pszCustomDllName)
        return FALSE;

    rc=DosScanEnv("FLASH10_ODIN",(PCSZ*)&szODINPath);
    if (rc != NO_ERROR || szODINPath[0] == '\0')
    {
        ULONG cbs = cchCustomDllName;
        rc = PrfQueryProfileData(HINI_USERPROFILE, "Flash10_Plugin", "OdinPath", pszCustomDllName, &cbs);
        if (!rc || pszCustomDllName[0] == '\0')
        {
            return FALSE;
        }
        else
        {
            strcat(pszCustomDllName, "\\");
            return TRUE;
        }
    } else
    {
        dprintf(("Environment variable ODIN: [%s]", szODINPath));
        //strcat(pszCustomDllName, "\\SYSTEM32\\");
    }
    strcpy(pszCustomDllName, szODINPath);
    return TRUE;
}

/**
 * This function returns all the win32 dll names.
 *
 * Any version checking and such should be done when this function is called.
 *
 * @returns Success indicator.
 * @param   pszPluginDllName    Buffer to store the DLL name.
 * @param   cchPluginDllName    Size of DLL name buffer.
 * @param   pszPluginName       Buffer to store the short name in.
 * @param   cchPluginName       Size of short name buffer.
 */
extern BOOL npprimaryGetPluginNames(char *pszPluginDllName, int cchPluginDllName,
                                    char *pszPluginName, int cchPluginName)
{
    /*
     * Get the full path name of the Win32 plugin dll.
     */
    HANDLE  hKey = NULLHANDLE;
    int     rc;

#if 1
    rc = PrfQueryProfileData(HINI_USERPROFILE, "Flash10_Plugin", "AdobePluginPath", pszPluginDllName, (PULONG)&cchPluginDllName);
    if (rc)
    {
        strcat(pszPluginDllName, "\\npswf32.dll");
        strcpy(pszPluginName, "npswf32.dll");
        return TRUE;
    }
#else
    rc = RegOpenKey(HKEY_LOCAL_MACHINE,
                    "Software\\Macromedia\\FlashPlayerPlugin",
                    &hKey);
    if (!rc)
    {
        unsigned fType = 0;
        unsigned cb = cchPluginDllName;
        rc = RegQueryValueEx(hKey, "Path", 0, &fType, pszPluginDllName, &cb);
        RegCloseKey(hKey);
    }
    if (!rc)
    {
        strcat(pszPluginDllName, "\\npswf32.dll");
        strcpy(pszPluginName, "npswf32.dll");
        return TRUE;
    }
#endif
    return FALSE;

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
