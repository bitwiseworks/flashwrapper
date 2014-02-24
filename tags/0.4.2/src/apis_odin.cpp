/* $Id: apis_odin.cpp,v 1.5 2003/09/30 12:42:36 sandervl Exp $
 *
 * We need to wrap all the Odin32 apis to make sure the exception handlers
 * and stuff is setup correctly before entering Odin32. This file contains
 * all the wrapping stuff.
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
*   Defined Constants And Macros                                               *
*******************************************************************************/
#ifdef DEBUG
#define ENTER_ODIN32_CONTEXT() \
    VERIFY_EXCEPTION_CHAIN();                                                   \
    ULONG   ExceptionRegRec[2] = {0,0};                                         \
    void *  pExceptionRegRec = &ExceptionRegRec[0];                             \
    USHORT usFSOld = pfnODIN_ThreadEnterOdinContext(pExceptionRegRec, TRUE);    \
    if (usFSOld != (USHORT)(unsigned)&DOS32TIB)                                 \
    {                                                                           \
        dprintff("usFSOld != DOS32TIB !!!");                                    \
        DebugInt3();                                                            \
    }//
#else
#define ENTER_ODIN32_CONTEXT() \
    VERIFY_EXCEPTION_CHAIN();                                                   \
    ULONG   ExceptionRegRec[2] = {0,0};                                         \
    void *  pExceptionRegRec = &ExceptionRegRec[0];                             \
    USHORT usFSOld = pfnODIN_ThreadEnterOdinContext(pExceptionRegRec, TRUE)
#endif

/** Debug helper for putting known garbage in the excpregrec. */
#ifdef DEBUG
#define LEAVE_EXCPT() \
    ExceptionRegRec[0] = 0xbeef1111; \
    ExceptionRegRec[1] = 0xdead2222
#else
#define LEAVE_EXCPT() ExceptionRegRec[0] = ExceptionRegRec[1] = 0
#endif

#define LEAVE_ODIN32_CONTEXT() \
    VERIFY_EXCEPTION_CHAIN();                                                   \
    pfnODIN_ThreadLeaveOdinContext(pExceptionRegRec, usFSOld);                  \
    LEAVE_EXCPT();                                                              \
    VERIFY_EXCEPTION_CHAIN()

#define ENTER_ODIN32_CONTEXT_IF_REQUIRED() \
    VERIFY_EXCEPTION_CHAIN();                                                   \
    ULONG   ExceptionRegRec[2] = {0,0};                                         \
    void *  pExceptionRegRec = NULL;                                            \
    extern USHORT _System GetFS(void);                                          \
    USHORT  usFSOld = GetFS();                                                  \
    if (usFSOld == (USHORT)(unsigned)&DOS32TIB)                                 \
    {                                                                           \
        pExceptionRegRec = &ExceptionRegRec[0];                                 \
        usFSOld = pfnODIN_ThreadEnterOdinContext(pExceptionRegRec, TRUE);       \
    }//

/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define  INCL_DOSMODULEMGR
#define  INCL_DOSMISC
#define  INCL_DOSPROCESS
#define  INCL_DOSERRORS
#define  INCL_DOSSEMAPHORES

#define INCL_BASE
#define INCL_PM
#include <os2.h>

#include "common.h"

/*******************************************************************************
*   Global Variables                                                           *
*******************************************************************************/
/** ODIN_ThreadEnterOdinContext - global */
USHORT (*WIN32API        pfnODIN_ThreadEnterOdinContext)(void *pExceptionRegRec, BOOL fForceFSSwitch);
/** ODIN_ThreadLeaveOdinContext - global */
void (*WIN32API          pfnODIN_ThreadLeaveOdinContext)(void *pExceptionRegRec, USHORT selFSOld);
/** ODIN_ThreadLeaveOdinContextNested - global */
USHORT (*WIN32API        pfnODIN_ThreadLeaveOdinContextNested)(void *pExceptionRegRec, BOOL fRemoveOdinExcpt);
/** ODIN_ThreadEnterOdinContextNested - global */
void (*WIN32API          pfnODIN_ThreadEnterOdinContextNested)(void *pExceptionRegRec, BOOL fRestoreOdinExcpt, USHORT selFSOld);
/** ODIN_ThreadContextSave - global */
void (*WIN32API          pfnODIN_ThreadContextSave)(PODINTHREADCTX pCtx, unsigned fFlags);
/** ODIN_ThreadContextRestore - global */
void (*WIN32API          pfnODIN_ThreadContextRestore)(PODINTHREADCTX pCtx, unsigned fFlags);
/** WriteLog */
int (*_System            pfnWriteLog)(const char *pszFormat, ...);

#define static //while debugging.

/** Register Dummy Exe */
static BOOL (*WIN32API          pfnRegisterDummyExeEx)(LPSTR pszExeName, PVOID pResData);
/** RegisterLxDll */
static DWORD (*WIN32API         pfnRegisterLxDll)(HINSTANCE hInstance, WIN32DLLENTRY EntryPoint, PVOID pResData, DWORD MajorImageVersion,
                                                  DWORD MinorImageVersion, DWORD Subsystem);
/** UnregisterLxDll */
static BOOL (*WIN32API          pfnUnregisterLxDll)(HINSTANCE hInstance);
/** GetProcAddressA */
static FARPROC (*WIN32API       pfnGetProcAddress)(HMODULE hInst, LPCSTR lpszProc);
/** LoadLibraryA */
static HMODULE (*WIN32API       pfnLoadLibrary)(LPCSTR lpszProc);
/** FreeLibrary */
static BOOL (*WIN32API          pfnFreeLibrary)(HMODULE hInst);
/** SetFreeTypeIntegration */
static void (*WIN32API          pfnSetFreeTypeIntegration)(BOOL fEnabled);
/** CreateFakeWindowEx */
static HWND (*WIN32API          pfnCreateFakeWindowEx)(HWND hwndOS2, ATOM classAtom);
/** DestroyFakeWindow */
static HWND (*WIN32API          pfnDestroyFakeWindow)(HWND hwnd);
/** RegisterClassA */
static ATOM (*WIN32API          pfnRegisterClassA)(void *pvWndClass);
/** FindAtomA */
static ATOM (*WIN32API          pfnFindAtom)(LPCSTR atomStr);
/** GetWindowLongA */
static LONG (*WIN32API          pfnGetWindowLongA)(HWND hwnd, int iIndex);
/** SetWindowLongA */
static LONG (*WIN32API          pfnSetWindowLongA)(HWND hwnd, int iIndex, LONG lValue);
/** SendMessageA */
static LRESULT (*WIN32API       pfnSendMessageA)(HWND hwnd, UINT msg, WPARAM mp1, LPARAM mp2);
/** CreateWindowExA */
static HWND (*WIN32API          pfnCreateWindowExA)(DWORD exStyle, LPCSTR className, LPCSTR windowName, DWORD style, INT x, INT y,
                                                    INT width, INT height, HWND parent, HMENU menu, HINSTANCE instance, LPVOID data);
/** DestroyWindow */
static BOOL (*WIN32API          pfnDestroyWindow)(HWND hwnd);
/** DefWindowProcA */
static LRESULT (*WIN32API       pfnDefWindowProcA)(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
/** SetWindowPos */
static BOOL (*WIN32API          pfnSetWindowPos)(HWND hwnd, HWND hwndInsertAfter, INT x, INT y, INT cx, INT cy, UINT fuFlags);
/** GetDC */
static HDC (*WIN32API           pfnGetDC)(HWND hwnd);
/** HPSToHDC */
static HDC (*WIN32API           pfnHPSToHDC)(HWND hwnd, HPS hps, LPCSTR pszDevice, LPRECT pRect);

/** J2PluginHacks */
static BOOL (*WIN32API          pfnJ2PluginHacks)(int iHack, BOOL fEnable);

/** Change window look&feel */
static void (*WIN32API          pfnSetWindowAppearance)(int fLooks);

/** Enable Flash Audio */
static BOOL (*WIN32API          pfnEnableFlashAudio)(BOOL fEnable);

static DWORD (*WIN32API         pfnGetFileVersionInfoSize)(LPCSTR filename, LPDWORD handle);
static BOOL (*WIN32API          pfnGetFileVersionInfo)(LPCSTR filename, DWORD handle, DWORD datasize, LPVOID data);
static DWORD (*WIN32API         pfnVerQueryValue)(LPVOID pBlock, LPCSTR lpSubBlock, LPVOID *lpBuffer, UINT *puLen);

#undef static //debugging

int registered_apis = 0;

struct OdinEntryPoint aAPIs[] =
{
    {1, (void**)&pfnRegisterDummyExeEx,                "_RegisterDummyExeEx@8", "KERNEL32", NULLHANDLE},
    {1, (void**)&pfnRegisterLxDll,                     "_RegisterLxDll@24", "KERNEL32", NULLHANDLE},
    {1, (void**)&pfnUnregisterLxDll,                   "_UnregisterLxDll@4", "KERNEL32", NULLHANDLE},
    {1, (void**)&pfnGetProcAddress,                    "GetProcAddress", "KERNEL32", NULLHANDLE},
    {1, (void**)&pfnLoadLibrary,                       "LoadLibraryA", "KERNEL32", NULLHANDLE},
    {1, (void**)&pfnFreeLibrary,                       "FreeLibrary", "KERNEL32", NULLHANDLE},
    {1, (void**)&pfnFindAtom,                          "GlobalFindAtomA", "KERNEL32", NULLHANDLE},
    {1, (void**)&pfnODIN_ThreadEnterOdinContext,       "_ODIN_ThreadEnterOdinContext@8", "KERNEL32", NULLHANDLE},
    {1, (void**)&pfnODIN_ThreadLeaveOdinContext,       "_ODIN_ThreadLeaveOdinContext@8", "KERNEL32", NULLHANDLE},
    {1, (void**)&pfnODIN_ThreadLeaveOdinContextNested, "_ODIN_ThreadLeaveOdinContextNested@8", "KERNEL32", NULLHANDLE},
    {1, (void**)&pfnODIN_ThreadEnterOdinContextNested, "_ODIN_ThreadEnterOdinContextNested@12", "KERNEL32", NULLHANDLE},
    {1, (void**)&pfnODIN_ThreadContextSave,            "_ODIN_ThreadContextSave@8", "KERNEL32", NULLHANDLE},
    {1, (void**)&pfnODIN_ThreadContextRestore,         "_ODIN_ThreadContextRestore@8", "KERNEL32", NULLHANDLE},
    {1, (void**)&pfnSetFreeTypeIntegration,            "SetFreeTypeIntegration", "GDI32", NULLHANDLE},
    {1, (void**)&pfnCreateFakeWindowEx,                "_CreateFakeWindowEx@8", "USER32", NULLHANDLE},
    {1, (void**)&pfnDestroyFakeWindow,                 "_DestroyFakeWindow@4", "USER32", NULLHANDLE},
    {1, (void**)&pfnRegisterClassA,                    "RegisterClassA", "USER32", NULLHANDLE},
    {1, (void**)&pfnGetWindowLongA,                    "GetWindowLongA", "USER32", NULLHANDLE},
    {1, (void**)&pfnSetWindowLongA,                    "SetWindowLongA", "USER32", NULLHANDLE},
    {1, (void**)&pfnSendMessageA,                      "SendMessageA", "USER32", NULLHANDLE},
    {1, (void**)&pfnCreateWindowExA,                   "CreateWindowExA", "USER32", NULLHANDLE},
    {1, (void**)&pfnDefWindowProcA,                    "DefWindowProcA", "USER32", NULLHANDLE},
    {1, (void**)&pfnSetWindowPos,                      "SetWindowPos", "USER32", NULLHANDLE},
    {0, (void**)&pfnGetDC,                             "GetDC", "USER32", NULLHANDLE},
    {0, (void**)&pfnHPSToHDC,                          "_HPSToHDC", "USER32", NULLHANDLE},
    {1, (void**)&pfnSetWindowAppearance,               "_SetWindowAppearance@4", "USER32", NULLHANDLE},
    {1, (void**)&pfnEnableFlashAudio,                  "ODIN_EnableFlashAudio", "WINMM", NULLHANDLE},
    //vladest        {0, (void**)&pfnJ2PluginHacks,                     "_J2PluginHacks@8"},
    {1, (void**)&pfnGetFileVersionInfoSize,            "GetFileVersionInfoSizeA", "VERSION", NULLHANDLE},
    {1, (void**)&pfnGetFileVersionInfo,                "GetFileVersionInfoA", "VERSION", NULLHANDLE},
    {1, (void**)&pfnVerQueryValue,                     "VerQueryValueA", "VERSION", NULLHANDLE},
};

/**
 * Resolves the Odin32 apis we require.
 */
BOOL    npResolveOdinAPIs(void)
{
    int rc;
    int i;
    char szPath[CCHMAXPATH * 2];
    char szBuf[CCHMAXPATH];
#if 0
    ULONG ulSavedCodePage;
#endif

    dprintf("Resolving Odin APIs...");

    const char *szOdinPath = getenv("NPFLOS2_ODINDLLPATH");
#ifdef DEBUG
    if (szOdinPath)
        dprintf("NPFLOS2_ODINDLLPATH is '%s', will use it", szOdinPath);
    else
        dprintf("NPFLOS2_ODINDLLPATH is not set, will rely on [BEGIN]LIBPATH");

#endif

    /*
     * Load the ODIN dlls. If NPFLOS2_ODINDLLPATH is given, we must set
     * BEGINLIBPATH as well to make sure that the right DLLs will be found
     * first.
     */
    if (szOdinPath)
    {
        strcpy(szPath, szOdinPath);
        strcat(szPath, ";%BEGINLIBPATH%");
        DosSetExtLIBPATH(szPath, BEGIN_LIBPATH);
        /* Also set LIBPATHSTRICT=T to allow for multiple DLL copies */
        DosSetExtLIBPATH("T", 3);
    }

#if 0
    /*
     * We must save and restore the current code page since user32
     * init code will change this.
     */
    ulSavedCodePage = WinQueryCp (HMQ_CURRENT);
    dprintf("Codepage: %i", ulSavedCodePage);
#endif

#ifdef DEBUG
    // CPREF says the length of Dos*ExtLIBPATH() (after expansion) is 1024 max
    char szBigBuf[1024];
    if (DosQueryExtLIBPATH(szBigBuf, BEGIN_LIBPATH) == NO_ERROR)
        dprintf("BEGINLIBPATH=%s", szBigBuf);
    if (DosQueryExtLIBPATH(szBigBuf, 3) == NO_ERROR)
        dprintf("LIBPATHSTRICT=%c", szBigBuf[0]);
#endif

    /*
     * Now resolve the Odin32 entrypoints we need.
     *
     * NOTE: Our custom build dlls export a limited number of functions
     *       If this list is changed, make sure the def files are updated too!
     */
    for (i = 0; i < sizeof(aAPIs) / sizeof(aAPIs[0]); i++)
    {
        if (szOdinPath)
        {
            strcpy(szPath, szOdinPath);
            strcat(szPath, "\\");
            strcat(szPath, aAPIs[i].pszModName);
            // when we have a full path there must be an extension as well
            strcat(szPath, ".DLL");
        }
        else
        {
            // otherwise there must be no extension (or the DLL won't be
            // searched in LIBPATH in LIBPATHSTRICT=T mode)
            strcpy(szPath, aAPIs[i].pszModName);
        }

        rc = DosLoadModule(szBuf, sizeof(szBuf), szPath, &aAPIs[i].modInst);
        if (rc && aAPIs[i].modInst == 0)
        {
            dprintf("ERROR: DosLoadModule(%s) returned %d (reason '%s')",
                    szPath, rc, szBuf);
            return FALSE;
        }
#ifdef DEBUG
        if (rc)
            dprintf("WARNING: DosLoadModule(%s) returned rc %d and HMOD %x",
                    szPath, rc, aAPIs[i].modInst);
#endif

        rc = DosQueryProcAddr(aAPIs[i].modInst, 0, aAPIs[i].pszName, (PFN*)aAPIs[i].ppfn);
        if (rc)
        {
            if (!aAPIs[i].fMandatory)
            {
                dprintf("WARNING: DosQueryProcAddr(%s,%s) returned %d (not mandatory)",
                        aAPIs[i].pszModName, aAPIs[i].pszName, rc);
                *aAPIs[i].ppfn = NULL;
                continue;
            }
            dprintf("ERROR: DosQueryProcAddr(%s,%s) returned %d (mandatory)",
                    aAPIs[i].pszModName, aAPIs[i].pszName, rc);
            //ReleaseInt3(0xdeaddead, 0xdeadf001, i);
            return FALSE;
        }

#ifdef DEBUG
        DosQueryModuleName(aAPIs[i].modInst, sizeof(szBuf), szBuf);
        dprintf("Loaded '%s' from '%s'", aAPIs[i].pszName, szBuf);
#endif
    }

    registered_apis = i + 1;

    dprintf("Successfully resolved all Odin APIs");
    return TRUE;
}


/**
 * LoadLibrary wrapper.
 * Assumes called from OS/2 context.
 */
BOOL WIN32API       odinRegisterDummyExeEx(LPSTR pszExeName, PVOID pResData)
{
    BOOL fRc;
    ENTER_ODIN32_CONTEXT();
    fRc = pfnRegisterDummyExeEx(pszExeName, pResData);
    LEAVE_ODIN32_CONTEXT();
    return fRc;
}


/**
 * RegisterLxDll wrapper.
 * Assumes called from OS/2 context.
 */
DWORD WIN32API      odinRegisterLxDll(HINSTANCE hInstance, WIN32DLLENTRY EntryPoint, PVOID pResData,
                                      DWORD MajorImageVersion, DWORD MinorImageVersion, DWORD Subsystem)
{
    DWORD rc;
    ENTER_ODIN32_CONTEXT();
    rc = pfnRegisterLxDll(hInstance, EntryPoint, pResData, MajorImageVersion, MinorImageVersion, Subsystem);
    LEAVE_ODIN32_CONTEXT();
    return rc;
}


/**
 * UnRegisterLxDll wrapper.
 * Assumes called from OS/2 context.
 * @remark this Odin API must not enter Odin context, at this time we might
 *         be pretty dead you see.
 */
BOOL WIN32API       odinUnregisterLxDll(HINSTANCE hInstance)
{
    BOOL fRc;
    fRc = pfnUnregisterLxDll(hInstance);
    return fRc;
}


/**
 * GetProcAddress wrapper.
 * Assumes called from OS/2 context.
 */
FARPROC WIN32API       odinGetProcAddress(HMODULE hInst, LPCSTR lpszProc)
{
    FARPROC pfn;
    ENTER_ODIN32_CONTEXT();
    pfn = pfnGetProcAddress(hInst, lpszProc);
    LEAVE_ODIN32_CONTEXT();
    return pfn;
}

void WIN32API       odinSetFreeTypeIntegration(BOOL fEnabled)
{
    FARPROC pfn;
    ENTER_ODIN32_CONTEXT();
    //Must do this before USER32 init!
    pfnSetFreeTypeIntegration(fEnabled);
    LEAVE_ODIN32_CONTEXT();
    return;
}


/**
 * LoadLibrary wrapper.
 * Assumes called from OS/2 context.
 */
HMODULE WIN32API    odinLoadLibrary(LPCSTR lpszProc)
{
    HMODULE hmod;
    ENTER_ODIN32_CONTEXT();
    hmod = pfnLoadLibrary(lpszProc);
    LEAVE_ODIN32_CONTEXT();
    return hmod;
}

/**
 * FreeLibrary wrapper.
 * Assumes called from OS/2 context.
 */
BOOL WIN32API    odinFreeLibrary(HMODULE hInst)
{
    BOOL fRc;
    ENTER_ODIN32_CONTEXT();
    fRc = pfnFreeLibrary(hInst);
    LEAVE_ODIN32_CONTEXT();
    return fRc;
}

/**
 * CreateFakeWindowEx wrapper.
 * Assumes called from OS/2 context.
 */
HWND WIN32API       odinCreateFakeWindowEx(HWND hwndOS2, ATOM classAtom)
{
    HWND hwndRc;
    ENTER_ODIN32_CONTEXT();
    hwndRc = pfnCreateFakeWindowEx(hwndOS2, classAtom);
    LEAVE_ODIN32_CONTEXT();
    return hwndRc;
}

/**
 * CreateFakeWindowEx wrapper.
 * Assumes called from OS/2 context.
 */
ATOM WIN32API odinFindAtom(LPCSTR atomStr)
{
    ATOM hwndRc;
    ENTER_ODIN32_CONTEXT();
    hwndRc = pfnFindAtom(atomStr);
    LEAVE_ODIN32_CONTEXT();
    return hwndRc;
}

/**
 * DestroyFakeWindow wrapper.
 * Assumes called from OS/2 context.
 */
BOOL WIN32API       odinDestroyFakeWindow(HWND hwnd)
{
    BOOL fRc;
    ENTER_ODIN32_CONTEXT();
    fRc = pfnDestroyFakeWindow(hwnd);
    LEAVE_ODIN32_CONTEXT();
    return fRc;
}


/**
 * DestroyFakeWindow wrapper.
 * Assumes called from OS/2 context.
 */
ATOM WIN32API       odinRegisterClass(void *pvWndClass)
{
    ATOM AtomRc;
    ENTER_ODIN32_CONTEXT();
    AtomRc = pfnRegisterClassA(pvWndClass);
    LEAVE_ODIN32_CONTEXT();
    return AtomRc;
}


/**
 * GetWindowLong wrapper.
 * Assumes called from OS/2 context.
 */
LONG WIN32API       odinGetWindowLong(HWND hwnd, int iIndex)
{
    LONG lRc;
    ENTER_ODIN32_CONTEXT_IF_REQUIRED();
    lRc = pfnGetWindowLongA(hwnd, iIndex);
    LEAVE_ODIN32_CONTEXT();
    return lRc;
}

/**
 * SetWindowLong wrapper.
 * Assumes called from OS/2 context.
 */
LONG WIN32API       odinSetWindowLong(HWND hwnd, int iIndex, ULONG ulValue)
{
    LONG lRc;
    ENTER_ODIN32_CONTEXT_IF_REQUIRED();
    lRc = pfnSetWindowLongA(hwnd, iIndex, ulValue);
    LEAVE_ODIN32_CONTEXT();
    return lRc;
}


/**
 * SendMessage
 */
LRESULT WIN32API    odinSendMessageA(HWND hwnd, UINT msg, WPARAM mp1, LPARAM mp2)
{
    LRESULT lrRc;
    ENTER_ODIN32_CONTEXT_IF_REQUIRED();
    lrRc = pfnSendMessageA(hwnd, msg, mp1, mp2);
    LEAVE_ODIN32_CONTEXT();
    return lrRc;
}


/**
 * CreateWindowExA
 */
HWND WIN32API    odinCreateWindowEx(DWORD exStyle, LPCSTR className, LPCSTR windowName, DWORD style, INT x, INT y,
                                    INT width, INT height, HWND parent, HMENU menu, HINSTANCE instance, LPVOID data)
{
    HWND hwndRc;
    ENTER_ODIN32_CONTEXT_IF_REQUIRED();
    hwndRc = pfnCreateWindowExA(exStyle, className, windowName, style, x, y, width, height, parent, menu, instance, data);
    LEAVE_ODIN32_CONTEXT();
    return hwndRc;
}


/**
 * DestroyWindow
 */
BOOL WIN32API    odinDestroyWindow(HWND hwnd)
{
    BOOL fRc;
    ENTER_ODIN32_CONTEXT_IF_REQUIRED();
    fRc = pfnDestroyWindow(hwnd);
    LEAVE_ODIN32_CONTEXT();
    return fRc;
}


/**
 * DefWindowProcA
 */
LRESULT WIN32API    odinDefWindowProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    BOOL fRc;
    ENTER_ODIN32_CONTEXT_IF_REQUIRED();
    fRc = pfnDefWindowProcA(hwnd, Msg, wParam, lParam);
    LEAVE_ODIN32_CONTEXT();
    return fRc;
}


/**
 * SetWindowPos
 */
BOOL WIN32API odinSetWindowPos(HWND hwnd, HWND hwndInsertAfter, INT x, INT y, INT cx, INT cy, UINT fuFlags)
{
    BOOL fRc;
    ENTER_ODIN32_CONTEXT_IF_REQUIRED();
    fRc = pfnSetWindowPos(hwnd, hwndInsertAfter, x, y, cx, cy, fuFlags);
    LEAVE_ODIN32_CONTEXT();
    return fRc;
}


/**
 * GetDC
 */
HDC  WIN32API       odinGetDC(HWND hwnd)
{
    HDC hdc = NULLHANDLE;
    if (pfnGetDC)
        hdc = pfnGetDC(hwnd);
    return hdc;
}


/**
 * HPSToHDC
 */
HDC  WIN32API       odinHPSToHDC(HWND hwnd, HPS hps, LPCSTR pszDevice, LPRECT pRect)
{
    HDC hdc = NULLHANDLE;
    if (pfnHPSToHDC)
        hdc = pfnHPSToHDC(hwnd, hps, pszDevice, pRect);
    return hdc;
}


/** J2PluginHacks */
BOOL WIN32API   odinJ2PluginHacks(int iHack, BOOL fEnable)
{
    if (!pfnJ2PluginHacks)
        return FALSE;
    BOOL fRc;
    ENTER_ODIN32_CONTEXT_IF_REQUIRED();
    fRc = pfnJ2PluginHacks(iHack, fEnable);
    LEAVE_ODIN32_CONTEXT();
    return fRc;
}


/** SetWindowAppearance */
void WIN32API   odinSetWindowAppearance(int fLooks)
{
    if (!pfnSetWindowAppearance)
        return;
    BOOL fRc;
    ENTER_ODIN32_CONTEXT_IF_REQUIRED();
    pfnSetWindowAppearance(fLooks);
    LEAVE_ODIN32_CONTEXT();
}


/** ODIN_EnableFlashAudio */
BOOL WIN32API   odinEnableFlashAudio(BOOL fEnable)
{
    if (!pfnEnableFlashAudio)
        return FALSE;
    BOOL fRc;
    ENTER_ODIN32_CONTEXT_IF_REQUIRED();
    fRc = pfnEnableFlashAudio(fEnable);
    LEAVE_ODIN32_CONTEXT();
    return fRc;
}

DWORD WIN32API odinGetFileVersionInfoSize(LPCSTR filename, LPDWORD handle)
{
    if (!pfnGetFileVersionInfoSize)
        return 0;
    DWORD size;
    ENTER_ODIN32_CONTEXT_IF_REQUIRED();
    size = pfnGetFileVersionInfoSize(filename, handle);
    LEAVE_ODIN32_CONTEXT();
    return size;
}

BOOL WIN32API odinGetFileVersionInfo(LPCSTR filename, DWORD handle, DWORD datasize, LPVOID data)
{
    if (!pfnGetFileVersionInfo)
        return FALSE;
    BOOL fRc;
    ENTER_ODIN32_CONTEXT_IF_REQUIRED();
    fRc = pfnGetFileVersionInfo(filename, handle, datasize, data);
    LEAVE_ODIN32_CONTEXT();
    return fRc;
}

DWORD WIN32API odinVerQueryValue(LPVOID pBlock, LPCSTR lpSubBlock, LPVOID *lpBuffer, UINT *puLen)
{
    if (!pfnVerQueryValue)
        return FALSE;
    DWORD fRc;
    ENTER_ODIN32_CONTEXT_IF_REQUIRED();
    fRc = pfnVerQueryValue(pBlock, lpSubBlock, lpBuffer, puLen);
    LEAVE_ODIN32_CONTEXT();
    return fRc;
}
