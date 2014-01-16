/* $Id: common.h,v 1.9 2004/03/10 15:36:41 bird Exp $
 *
 * Plugin global stuff.
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

#ifndef __common_h__
#define __common_h__

/*******************************************************************************
*   Defined Constants And Macros                                               *
*******************************************************************************/
/** Valid Pointer? */
#define VALID_PTR(pv)   \
    (   ((unsigned)(pv)) >= (unsigned)0x10000L    /* 64KB */ \
     && ((unsigned)(pv)) <  (unsigned)0xc0000000L /* 3GB */  \
        )

/** Valid Reference? */
#define VALID_REF(ref)  VALID_PTR(&(ref))


/** Debug printf */
#undef dprintf
#ifdef DEBUG
    #define dprintf(a)      npdprintf a
#else
    #define dprintf(a)      (void)0
#endif

/** Debug Interrupt. */
#ifdef DEBUG
    #define DebugInt3()     (void)0//_interrupt(3)
#else
    #define DebugInt3()     (void)0
#endif

/** Exception chain verify - debug only. */
#ifdef DEBUG
    #define VERIFY_EXCEPTION_CHAIN()     npVerifyExcptChain()
#else
    #define VERIFY_EXCEPTION_CHAIN()     ((void)0)
#endif


/** @name Structure Wrapper Types
 * fType param of NPJNICreateWrapper().
 * @{
 */
/** JRIEnv down wrapper. */
#define NPJS_TYPE_JRIENV_DOWN       0x00000040

/** @} */

/** Magic word for the plugin window data. */
#define NPWNDDATA_MAGIC             0xfdb97531


/** PRI calling convention */
#define PRICALL
/** PR calling convention */
#define PRCALL

/** Plugin v4 Export Calling Convention for Win32. */
#define W32OSCALL __stdcall // WINAPI

/** The ordinal number of the npGenericInit() export. */
#define NP_ORD_NPGENERICINIT        100

#if defined(__EMX__)
extern _System void * Dos32TIB(); /* absolute symbol */
#define DOS32TIB Dos32TIB
#else
extern void * DOS32TIB;
#endif


/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/
#include <win32type.h>
#include <odin.h>
#include <custombuild.h>

/* taken from odinlx.h */
#ifdef __cplusplus
extern "C" {
#endif

typedef ULONG (* WIN32API WIN32DLLENTRY)(ULONG hInstance, ULONG reason, LPVOID reserved);
typedef int (* WIN32API WINMAIN)(HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

#ifdef __cplusplus
}
#endif

#ifdef INCL_MOZAPIS
#include "prthread.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*   Structures and Typedefs                                                    *
*******************************************************************************/
struct OdinEntryPoint
{
    int         fMandatory;
    void **     ppfn;
    const char *pszName;
    const char *pszModName;
    HMODULE modInst;
};


/**
 * A per set window structure which is used with npWinSetWindowBegin()
 * and npWinSetWindowEnd();
 */
typedef struct npwinSavedPS
{
    /** Save ID for the Mozilla HPS. */
    LONG    lSaveId;
    /** Options. */
    LONG    lOptions;
    /** Size */
    SIZEL   sizlPS;
    /** Y-inversion value. */
    LONG    lYInversion;
    /** Default View Matrix */
    MATRIXLF    matlfDefault;
    #if 0
    /** Viewing Transform Matrix */
    MATRIXLF    matlfViewing;
    /** Prims: array of default masks. */
    ULONG   aDefMasks[6];
    /** Prims: array of default masks. */
    char    achBundleData[1024];
    #endif

} NPSAVEDPS, *PNPSAVEDPS;


/**
 * Data associated with a print event.
 */
typedef struct npwinPluginPrintData
{
    /** OS/2 HPS */
    HPS             hpsOS2;
    /** Odin HDC */
    HDC             hdcOdin;

    /** Pointer to the nsPluginPrint we present to the Win32 layer. */
    void *          pvOdinPrt;

    /** Pointer to the nsPluginPrint we originally received. */
    const void *    pvMozPrt;

    /** Saved Browser PS state. */
    NPSAVEDPS       SavedPS;

} NPPRINTDATA, *PNPPRINTDATA;


/**
 * QWL_USER data associated with a wrapped plugin window.
 */
typedef struct npwinPluginWindowData
{
    /** Some magic word. */
    unsigned    uMagic;

    /** OS/2 Window. */
    HWND        hwndOS2;
    /** Odin L0 fake window. */
    HWND        hwndOdin;

    /** OS/2 HPS */
    HPS         hpsOS2;
    /** Odin HDC */
    HDC         hdcOdin;
    /** Saved Odin PS state. */
    NPSAVEDPS   SavedOdinPS;

    /** Pointer to the NPWindow we present to the Win32 layer.
     * @todo This should be freed in some WM_(NC)DESTROY case.
     */
    void *      pvOdinWnd;

    /** Pointer to the NPWindow we originally received.
     * Not sure if it's trusty or not, think it'll stay around it the window
     * is destroyed.
     */
    const void *  pvMozWnd;

#ifdef EXPERIMENTAL
    /** Pointer to the orignal window procedure.
     * Used if we subclass the plugin window.
     */
    void * (*_System pfnwpOrg)(HWND, ULONG, void*,void*);
#endif

} NPWINDATA, *PNPWINDATA;


typedef struct NPOdinPluginWrapper *PNPODINWRAPPER;

/*******************************************************************************
*   typedefs & structs that depend on the moz plugin headers                   *
*******************************************************************************/
#ifdef INCL_NS4X

#include "npfunctions.h"

/* callback versions */
typedef NPError     (* OSCALL PFN_NP_GetEntryPoints)(NPPluginFuncs* pCallbacks, PNPODINWRAPPER pPlugin);
typedef NPError     (* OSCALL PFN_NP_Initialize)(NPNetscapeFuncs * pFuncs, PNPODINWRAPPER pPlugin);
typedef NPError     (* OSCALL PFN_NP_Shutdown)(PNPODINWRAPPER pPlugin);
typedef NPError     (* OSCALL PFN_NP_GetValue)(NPP future, NPPVariable variable, void *value, PNPODINWRAPPER pPlugin);
typedef char *      (* OSCALL PFN_NP_GetMIMEDescription)(PNPODINWRAPPER pPlugin);

/* win32 versions */
typedef struct _NP32PluginFuncs    *PNP32PluginFuncs;
typedef struct _NP32NetscapeFuncs  *PNP32NetscapeFuncs;
typedef NPError (*W32OSCALL    PFNW32_NP_GetEntryPoints)(PNP32PluginFuncs pCallbacks);
typedef NPError (*W32OSCALL    PFNW32_NP_Initialize)(PNP32NetscapeFuncs pFuncs);
typedef NPError (*W32OSCALL    PFNW32_NP_Shutdown)(void);
typedef NPError (*W32OSCALL    PFNW32_NP_GetValue)(NPP future, NPPVariable variable, void *value);
typedef char * (*W32OSCALL     PFNW32_NP_GetMIMEDescription)(void);

/**
 * Per Plugin Structure.
 *
 * The first three members are initiated by the particular wrapper dll
 * before calling npGenericInit() to load the Win32 DLL and resolve the
 * entry points.
 */
typedef struct NPOdinPluginWrapper
{
    /** Size of this structure.
     * Used to validate it and prevent version trouble.
     * This is input to the npGenericInit().
     */
    unsigned        cb;

    /** The name of the plugin - fully qualified name.
     * This is input to the npGenericInit().
     */
    char            szPluginDllName[260];

    /** The Odin module handle of the wrapped plugin Dll.
     * npGenericLazyInit() will initialize this.
     * The workers use this as an indication on wether or not npGenericLazyInit() has been called.
     */
    HMODULE         hmodPlugin;

    /** @name Function pointers - the native ones.
     * npGenericInit() will initialize these. Noone will ever be NULL.
     * @{
     */
    PFN_NP_GetEntryPoints           pfnNP_GetEntryPoints;
    PFN_NP_Initialize               pfnNP_Initialize;
    PFN_NP_Shutdown                 pfnNP_Shutdown;
    PFN_NP_GetValue                 pfnNP_GetValue;
    PFN_NP_GetMIMEDescription       pfnNP_GetMIMEDescription;
    //@}

    /** @name Function pointers - the win32 ones.
     * npGenericInit() will resolve these.
     * @{
     */
    PFNW32_NP_GetEntryPoints        pfnW32NP_GetEntryPoints;
    PFNW32_NP_Initialize            pfnW32NP_Initialize;
    PFNW32_NP_Shutdown              pfnW32NP_Shutdown;
    PFNW32_NP_GetValue              pfnW32NP_GetValue;
    PFNW32_NP_GetMIMEDescription    pfnW32NP_GetMIMEDescription;
    //@}

} NPODINWRAPPER;

#pragma pack(1)
struct NPWindowW32
{
    void *        window;
    int32_t       x;
    int32_t       y;
    uint32_t      width;
    uint32_t      height;
    NPRect        clipRect;
    NPWindowType  type;
};

struct NPEmbedPrintW32
{
    NPWindowW32 window;
    void *      platformPrint;
};

struct NPPrintW32
{
    uint16_t            mode;
    uint16_t            dummy_padding;
    union
    {
        NPFullPrint     fullPrint;
        NPEmbedPrintW32 embedPrint;
    } print;
};
#pragma pack()

#endif /* INCL_NS4X */
/*******************************************************************************
*   Global Variables                                                           *
*******************************************************************************/

/** ODIN_ThreadEnterOdinContext - global */
extern USHORT (*WIN32API        pfnODIN_ThreadEnterOdinContext)(void *pExceptionRegRec, BOOL fForceFSSwitch);
/** ODIN_ThreadLeaveOdinContext - global */
extern void (*WIN32API          pfnODIN_ThreadLeaveOdinContext)(void *pExceptionRegRec, USHORT selFSOld);
/** ODIN_ThreadLeaveOdinContextNested - global */
extern USHORT (*WIN32API        pfnODIN_ThreadLeaveOdinContextNested)(void *pExceptionRegRec, BOOL fRemoveOdinExcpt);
/** ODIN_ThreadEnterOdinContextNested - global */
extern void (*WIN32API          pfnODIN_ThreadEnterOdinContextNested)(void *pExceptionRegRec, BOOL fRestoreOdinExcpt, USHORT selFSOld);
/** ODIN_ThreadContextSave - global */
extern void (*WIN32API          pfnODIN_ThreadContextSave)(PODINTHREADCTX pCtx, unsigned fFlags);
/** ODIN_ThreadContextRestore - global */
extern void (*WIN32API          pfnODIN_ThreadContextRestore)(PODINTHREADCTX pCtx, unsigned fFlags);
/** WriteLog */
extern int (*_System            pfnWriteLog)(const char *pszFormat, ...);

#ifdef INCL_MOZAPIS
extern PRThread* (*PRICALL      pfn_PRI_AttachThread)(PRThreadType type, PRThreadPriority priority, PRThreadStack *stack, PRUint32 flags);
extern void (*PRICALL           pfn_PRI_DetachThread)(void);
#endif


/** Global flag which tells if we init was successful or not.
 * If not successfull we have to stay in memory because Odin does so.
 */
extern BOOL                     gfInitSuccessful;

extern HMODULE                  ghmodOurSelf;

/*******************************************************************************
*   Functions                                                                  *
*******************************************************************************/
/* kernel32 apis */
FARPROC WIN32API    odinGetProcAddress(HMODULE hInst, LPCSTR lpszProc);
HMODULE WIN32API    odinLoadLibrary(LPCSTR lpszProc);
BOOL WIN32API       odinFreeLibrary(HMODULE hInst);
BOOL WIN32API       odinRegisterDummyExeEx(LPSTR pszExeName, PVOID pResData);
DWORD WIN32API      odinRegisterLxDll(HINSTANCE hInstance, WIN32DLLENTRY EntryPoint, PVOID pResData,
                                      DWORD MajorImageVersion, DWORD MinorImageVersion, DWORD Subsystem);
BOOL WIN32API       odinUnregisterLxDll(HINSTANCE hInstance);

/* user32 apis */
HWND WIN32API       odinCreateFakeWindowEx(HWND hwndOS2, ATOM classAtom);
BOOL WIN32API       odinDestroyFakeWindow(HWND hwnd);
ATOM WIN32API       odinRegisterClass(void *pvWndClass);
LONG WIN32API       odinGetWindowLong(HWND hwnd, int iIndex);
LONG WIN32API       odinSetWindowLong(HWND hwnd, int iIndex, ULONG ulValue);
LRESULT WIN32API    odinSendMessageA(HWND hwnd, UINT msg, WPARAM mp1, LPARAM mp2);
HWND WIN32API       odinCreateWindowEx(DWORD exStyle, LPCSTR className, LPCSTR windowName, DWORD style, INT x, INT y,
                                       INT width, INT height, HWND parent, HMENU menu, HINSTANCE instance, LPVOID data);
BOOL WIN32API       odinDestroyWindow(HWND hwnd);
LRESULT WIN32API    odinDefWindowProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL WIN32API       odinSetWindowPos(HWND hwnd, HWND hwndInsertAfter, INT x, INT y, INT cx, INT cy, UINT fuFlags);
HDC  WIN32API       odinGetDC(HWND hwnd);
HDC  WIN32API       odinHPSToHDC(HWND hwnd, HPS hps, LPCSTR pszDevice, LPRECT pRect);

BOOL WIN32API       odinJ2PluginHacks(int iHack, BOOL fEnable);
void WIN32API       odinSetFreeTypeIntegration(BOOL fEnabled);
ATOM WIN32API       odinFindAtom(LPCSTR atomStr);
void WIN32API       odinSetWindowAppearance(int fLooks);
BOOL WIN32API       odinEnableFlashAudio(BOOL fEnable);

/* window and ps/dc hacking. */
void *              npWinSetWindowBegin(void * aWindow, BOOL fNS4x, PNPWINDATA *ppWndData, PNPSAVEDPS pSetWindow, HWND hwndOS2, HWND hwndOdin);
void                npWinSetWindowEnd(void * aWindow, BOOL fNS4x, PNPWINDATA *ppWndData, PNPSAVEDPS pSetWindow);
PNPPRINTDATA        npWinPrintBegin(void * aPlatformPrint, BOOL fNS4x);
void                npWinPrintEnd(PNPPRINTDATA pPrintData);
void                npWinDestroyInstance(PNPWINDATA pWndData);
HWND                npWinDownNetscapeWindow(HWND hwndOS2);
BOOL                npWinSavePS(HPS hps, PNPSAVEDPS pSet);
BOOL                npWinRestorePS(HPS hps, PNPSAVEDPS pSet);

/* mozilla apis */
#ifdef INCL_MOZAPIS
PRThread*           mozPR_AttachThread(PRThreadType type, PRThreadPriority priority, PRThreadStack *stack);
void                mozPR_DetachThread(void);
PRThread *          mozPR_GetCurrentThread(void);
PRThread *          moz_PRI_AttachThread(PRThreadType type, PRThreadPriority priority, PRThreadStack *stack, PRUint32 flags);
void                moz_PRI_DetachThread(void);
BOOL                npResolveMozAPIs(void);
#endif

/* Misc Internal */
BOOL                npInitTerm_Lazy(void);
BOOL                npResolveOdinAPIs(void);
void *              NPJNICreateUpWrapper(HINSTANCE hInstance, unsigned fType, void *pv);
void *              NPJNICreateDownWrapper(HINSTANCE hInstance, unsigned fType, void *pv);
BOOL _Optlink       NPJNIEqual(unsigned *pu, unsigned uSet, unsigned uCurrent);
unsigned _System    npGetFS(void);
unsigned _System    npRestoreOS2FS(void);
unsigned _System    npSetFS(unsigned);

/* internal debug stuff */
int                 npdprintf(const char *pszFormat, ...);
void _Optlink       npVerifyExcptChain(void);
void _Optlink       ReleaseInt3(unsigned uEAX, unsigned uEDX, unsigned uECX);
#ifdef DEBUG
void                CleanStack(void);
#endif

/* Generic Plugin Wrapper External Interface. */
BOOL                npGenericInit(PNPODINWRAPPER pPlugin);

/* Generic Plugin Wrapper Internal Stuff */
BOOL                npGenericLazyInit(PNPODINWRAPPER pPlugin);
int                 npGenericErrorBox(const char *pszMessage, BOOL fYesNo);

#ifdef INCL_NS4X
NPError OSCALL npGenericNP_GetEntryPoints(NPPluginFuncs* pCallbacks, PNPODINWRAPPER pPlugin);
NPError OSCALL npGenericNP_Initialize(NPNetscapeFuncs * pFuncs, PNPODINWRAPPER pPlugin);
NPError OSCALL npGenericNP_Shutdown(PNPODINWRAPPER pPlugin);
NPError OSCALL npGenericNP_GetValue(NPP future, NPPVariable variable, void *value, PNPODINWRAPPER pPlugin);
char * OSCALL npGenericNP_GetMIMEDescription(PNPODINWRAPPER pPlugin);
#endif

#ifdef __cplusplus
}
#endif

#endif
