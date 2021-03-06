/* $Id: odin_windowing.cpp,v 1.5 2004/03/10 15:36:41 bird Exp $
 *
 * Plugin Window Hacking.
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
/** Fake window class. */
#define WC_NPWIN_LEVEL_MINUS "WC_NPWIN_LEVEL_MINUS"
/** Fake window class. */
#define WC_NPWIN_LEVEL0     "WC_NPWIN_LEVEL0"
/** The windowed layered on top of the fake window. */
#define WC_NPWIN_LEVEL1     "WC_NPWIN_LEVEL1"

#define WC_NPWIN_FLASH_FS "ShockwaveFlashFullScreen"

/* Window property to associate PNPWINDATA with OS/2 HWND */
#define WP_NPWINDATA "ShockwaveFlashNPWINDATA"

/** Index of the os2 hwnd for Minus windows. */
#define LMINUS1_GWL_OS2HWND     0
/** Index of the os2 hwnd for the plugin window. */
#define L0_GWL_OS2PLUGINWINDOW  0
/** Index of the odin hwnd for level1 window. */
#define L0_GWL_LEVEL1_ODINHWND  4
/** Index of the os2 hwnd for the plugin window. */
#define L1_GWL_OS2PLUGINWINDOW  0
/** Index of the odin hwnd for level0 window. */
#define L1_GWL_LEVEL0_ODINHWND  4


/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/
/* the mozilla headers */
#ifdef __IBMCPP__
# include "moz_VACDefines.h"
#else
# include "moz_GCCDefines.h"
#endif
#define __OS2_H__

#include "windows.h"
typedef HANDLE HPS;
typedef HANDLE HAB;
typedef struct _MATRIXLF
{
    FIXED   fxM11;
    FIXED   fxM12;
    LONG    lM13;
    FIXED   fxM21;
    FIXED   fxM22;
    LONG    lM23;
    LONG    lM31;
    LONG    lM32;
    LONG    lM33;
} MATRIXLF;
typedef MATRIXLF *PMATRIXLF;

typedef const char *PCSZ;

#define INCL_NS4X
#include "common.h"

/*******************************************************************************
*   Structures and Typedefs                                                    *
*******************************************************************************/
typedef VOID *MRESULT;   /* mres  */
typedef VOID *MPARAM;    /* mp    */
typedef void * (*_System PFNWP)(HWND, ULONG, void*,void*);
#ifndef NULLHANDLE
#define NULLHANDLE ((HANDLE)0)
#endif
#ifndef PRIM_LINE
#define PRIM_LINE                       1L
#endif
#ifdef PRIM_IMAGE
#define PRIM_IMAGE                      5L
#endif


/*******************************************************************************
*   Global Variables                                                           *
*******************************************************************************/
/** Flag which tells if npwin is initiated or not. */
static BOOL         gfInited = FALSE;
/** Level -1 window class (fake - parent). */
static ATOM         gWCLevelMinus;
/** Level zero window class (fake). */
static ATOM         gWCLevel0;
/** Level one window class. */
static ATOM         gWCLevel1;

static ATOM         gWCFlashFS;

/*******************************************************************************
*   Internal Functions                                                         *
*******************************************************************************/
#ifdef EXPERIMENTAL
static MRESULT _System   npWinPluginSubClassWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#endif
static LRESULT __stdcall npWinLevelMinusWndProc(HWND hwnd, UINT msg, WPARAM mp1, LPARAM mp2);
static LRESULT __stdcall npWinLevel0WndProc(HWND hwnd, UINT msg, WPARAM mp1, LPARAM mp2);
static LRESULT __stdcall npWinLevel1WndProc(HWND hwnd, UINT msg, WPARAM mp1, LPARAM mp2);
static HWND              npWinCreateWindowWrapper(HWND hwndOS2, int x, int y, int cx, int cy);
static void              npWinFlipY(void *pvOdinWnd, HWND hwnd, int y, unsigned cy, BOOL fNS4x);
static void              npWinFakeWindowPosSize(HWND hwndOdin, HWND hwndOS2, int x, int y, int cx, int cy);

/*******************************************************************************
*   External Functions                                                         *
*******************************************************************************/
extern LONG _System     WinQueryClassName(HWND, LONG, char *);
extern HWND _System     WinQueryDesktopWindow(HANDLE, HDC);
extern HANDLE _System   WinQueryAnchorBlock(HWND);
extern BOOL _System     WinSetWindowPos(HWND, HWND, LONG, LONG, LONG, LONG, ULONG);
#define QW_PARENT   5
#define QW_OWNER    4
extern HWND _System     WinQueryWindow(HWND, int);
extern BOOL _System     WinQueryWindowPos(HWND, struct OS2SWP *pSwp);
extern ULONG _System    WinQueryWindowULong(HWND hwndOS2, LONG lIndex);
extern BOOL  _System    WinSetWindowULong(HWND hwndOS2, LONG lIndex, ULONG ul);
extern BOOL  _System    WinSetOwner(HWND hwndOS2, HWND hwndOS2NewOwner);
extern MRESULT  _System WinDefWindowProc(HWND hwndOS2, ULONG msg, MPARAM mp1, MPARAM mp2);
extern PFNWP  _System   WinSubclassWindow(HWND hwndOS2, PFNWP pfnNewWndProc);
extern HWND  _System    WinWindowFromDC(HDC hdc);
extern HPS  _System     WinGetPS(HWND hwnd);
extern BOOL _System     WinReleasePS(HPS hps);
extern HDC  _System     WinQueryWindowDC(HWND hwnd);
extern LONG _System     GpiQueryPS(HPS hps, PSIZEL psizl);
extern BOOL _System     GpiSetPS(HPS hps, PSIZEL psizl, LONG lOptions);
extern LONG _System     GpiSavePS(HPS hps);
extern BOOL _System     GpiRestorePS(HPS hps, LONG lSaveId);
extern ULONG _System    WinGetLastError(HAB hab);
extern PVOID _System    WinQueryProperty(HWND hwnd, PCSZ pszNameOrAtom);
extern PVOID _System    WinRemoveProperty(HWND hwnd, PCSZ pszNameOrAtom);
extern BOOL _System     WinSetProperty(HWND hwnd, PCSZ pszNameOrAtom, PVOID pvData, ULONG ulFlags);
#ifndef GPI_ERROR
#define GPI_ERROR   0
#endif

typedef struct OS2SWP
{
    ULONG fl;
    LONG        cy;
    LONG        cx;
    LONG        y;
    LONG        x;
    HWND        hwndInsertBehind;
    HWND        hwnd;
    ULONG ulReserved1;
    ULONG ulReserved2;
} OS2SWP, *POS2SWP;


/**
 * Init the window faking.
 * @returns success indicator.
 */
BOOL npWinInit()
{
    VERIFY_EXCEPTION_CHAIN();
    if (!gfInited)
    {
        WNDCLASSA WndClass;
        memset(&WndClass, 0, sizeof(WndClass));
        WndClass.lpfnWndProc   = npWinLevel0WndProc;
        WndClass.lpszClassName = WC_NPWIN_LEVEL0;
        WndClass.cbWndExtra    = 8; //@todo sizeof(instance data)
        gWCLevel0 = odinRegisterClass(&WndClass);
        if (gWCLevel0)
        {
            dprintf("npWinInit: registered level0 atom=%x", gWCLevel0);
            memset(&WndClass, 0, sizeof(WndClass));
            WndClass.lpfnWndProc   = npWinLevel1WndProc;
            WndClass.lpszClassName = WC_NPWIN_LEVEL1;
            WndClass.cbWndExtra    = 8; //@todo sizeof(instance data)
            gWCLevel1 = odinRegisterClass(&WndClass);
            if (gWCLevel1)
            {
                dprintf("npWinInit: registerd level1 atom=%x", gWCLevel1);
                memset(&WndClass, 0, sizeof(WndClass));
                WndClass.lpfnWndProc   = npWinLevelMinusWndProc;
                WndClass.lpszClassName = WC_NPWIN_LEVEL_MINUS;
                WndClass.cbWndExtra    = 8; //@todo sizeof(instance data)
                gWCLevelMinus = odinRegisterClass(&WndClass);
                if (gWCLevelMinus)
                {
                    dprintf("npWinInit: registerd level -1 atom=%x", gWCLevelMinus);
                    gfInited = TRUE;
                }
                else
                    dprintf("npWinInit: failed to register %s.", WC_NPWIN_LEVEL1);
            }
            else
                dprintf("npWinInit: failed to register %s.", WC_NPWIN_LEVEL1);
        }
        else
            dprintf("npWinInit: failed to register %s.", WC_NPWIN_LEVEL0);
    }
    VERIFY_EXCEPTION_CHAIN();
    return gfInited;
}


/**
 * SetWindow worker - Called before invoking the plugin entry point.
 *
 * @returns Pointer to aWindow or wrapper structure.
 *          The caller doesn't need to care which and must not free it or anything.
 *          The wrapper is freed in WM_NCDESTROY.
 * @param   aWindow     Window structure from Mozilla/Netscape.
 * @param   ppWndData   Place to save/get the window data stuff in the plugin instance.
 *                      Will be set on window wrapper creation, and used if non zero.
 *                      Currently only used the NS4x interface (i.e. may be NULL).
 * @param   pSavedPS    Per call structure. If NULL we cannot do drawing.
 * @param   hwndDocOS2  Handle of the document window. May be NULLHANDLE.
 * @param   hwndDocOdin Handle of the document window. May be NULLHANDLE.
 * @remark  There is to much type casting here... And I really think the structure are identical.
 */
void * npWinSetWindowBegin(void * aWindow, BOOL fNS4x, PNPWINDATA *ppWndData, PNPSAVEDPS pSavedPS, HWND hwndDocOS2, HWND hwndDocOdin)
{
    VERIFY_EXCEPTION_CHAIN();

#define GETMEMB_WND(ptr, memb, type) (fNS4x ? (type)(((NPWindow*)(ptr))->memb) : (type)(((NPWindow*)(ptr))->memb))

    /*
     * Create wrapper if needed.
     */
    void * pvWindow = aWindow;
    if (VALID_PTR(pvWindow))
    {
        HWND        hwnd = GETMEMB_WND(pvWindow, window, HWND);
        HPS         hps = (HPS)hwnd;
        int         x    = GETMEMB_WND(pvWindow, x, int);
        int         y    = GETMEMB_WND(pvWindow, y, int);
        unsigned    cx   = GETMEMB_WND(pvWindow, width, unsigned);
        unsigned    cy   = GETMEMB_WND(pvWindow, height, unsigned);
        unsigned    type = GETMEMB_WND(pvWindow, type, unsigned);
        unsigned    cb   = fNS4x ? sizeof(NPWindow) : sizeof(NPWindow);

        dprintff("hwnd=%x  x,y=(%d,%d) cx,cy=(%d,%d)  type=%d  fNS4x=%d", hwnd, x, y, cx, cy, type, fNS4x);

        /*
         * Try find the associated window data.
         */
        void *          pvOdinWnd = NULL;
        PNPWINDATA      pWndData = NULL;
        if (ppWndData)
            pWndData = *ppWndData;
        if (!pWndData && type == NPWindowTypeWindow)
            pWndData = (PNPWINDATA)WinQueryProperty(hwnd, WP_NPWINDATA);

        /*
         * Take action on whether or not we succeeded...
         */
        switch (type)
        {
            case NPWindowTypeWindow:
                dprintff("NPWindowTypeWindow: hwnd=%#x", hwnd);
                if (!pWndData)
                {
                    /*
                     * We can and must try a create wrapper window.
                     */
                    dprintff("Creating Window Wrapper....");
                    pWndData = (PNPWINDATA)calloc(sizeof(NPWINDATA), 1);
                    if (pWndData)
                    {
                        pWndData->uMagic = NPWNDDATA_MAGIC;
                        pWndData->pvMozWnd = aWindow;
                        pWndData->hwndOS2 = hwnd;
                        pWndData->pvOdinWnd = pvOdinWnd = calloc(cb, 1);
                        if (pvOdinWnd)
                        {
                            pWndData->hwndOdin = npWinCreateWindowWrapper(hwnd, x, y, cx, cx);
                            if (pWndData->hwndOdin)
                            {
                                memcpy(pvOdinWnd, aWindow, cb);
                                ((NPWindow*)pvOdinWnd)->window = (void*)pWndData->hwndOdin;

                                if (WinSetProperty(hwnd, WP_NPWINDATA, pWndData, 0))
                                {
                                    dprintff("Created wrapper pvOdinWnd->window=%x for  aWindow->window=%x.",
                                             pWndData->hwndOdin, pWndData->hwndOS2);
                                    npWinFlipY(pvOdinWnd, hwnd, y, cy, fNS4x);
                                    #ifdef EXPERIMENTAL
                                    pWndData->pfnwpOrg = WinSubclassWindow(pWndData->hwndOS2, npWinPluginSubClassWndProc);
                                    dprintff("pWndData->pfnwpOrg=%x", pWndData->pfnwpOrg);
                                    #endif
                                    if (ppWndData)
                                        *ppWndData = pWndData;
                                }
                                else
                                {
                                    dprintff("arg!!! WinSetWindowULong failed %#x !!!", hwnd);
                                    free(pvOdinWnd);
                                    free(pWndData);
                                    pWndData = NULL;
                                }
                            }
                            else
                            {
                                dprintff("arg!!! failed to create wrapper window !!!");
                                free(pvOdinWnd);
                                free(pWndData);
                                pWndData = NULL;
                            }
                        }
                        else
                        {
                            free(pWndData);
                            pWndData = NULL;
                            dprintff("!!!!! Out Of memory !!!!!!");
                        }
                    }
                    else
                        dprintff("!!!!! Out Of memory !!!!!!");
                }
                else
                {
                    /*
                     * Must notify size/pos change.
                     */
                    dprintff("Size/pos change....");
                    pvOdinWnd = pWndData->pvOdinWnd;

                    #ifdef DEBUG
                    /*
                     * Wonder if any properties have changed?
                     */
                    if (aWindow != pWndData->pvMozWnd)
                        dprintff("aWindow != pOrgWnd");
                    if (hwnd != pWndData->hwndOS2)
                        dprintff("hwnd changed !!!");
                    if (x != GETMEMB_WND(pvOdinWnd, x, int))
                        dprintff("x changed");
                    if (y != GETMEMB_WND(pvOdinWnd, y, int))
                        dprintff("y changed");
                    if (cx != GETMEMB_WND(pvOdinWnd, width, unsigned))
                        dprintff("width changed");
                    if (cy != GETMEMB_WND(pvOdinWnd, height, unsigned))
                        dprintff("height changed");
                    if (type != GETMEMB_WND(pvOdinWnd, type, unsigned))
                        dprintff("height changed");
                    #endif

                    /*
                     * Update the structure.
                     */
                    memcpy(pvOdinWnd, pvWindow, cb);
                    ((NPWindow *)pvOdinWnd)->window = (void*)pWndData->hwndOdin;
                    npWinFlipY(pvOdinWnd, hwnd, y, cy, fNS4x);

                    /*
                     * Do sizing of wrapper windows.
                     */
                    npWinFakeWindowPosSize(pWndData->hwndOdin, pWndData->hwndOS2, x, y, cx, cy);
                }
                break;


            case NPWindowTypeDrawable:
                dprintff("NPWindowTypeDrawable: hps=%#x hwndOS2=%#x hwndOdin=%#x", hwnd, hwndDocOS2, hwndDocOdin);
                if (!pWndData)
                {
                    /*
                     * Create wrapper from OS/2 HPS to Odin HDC.
                     */
                    dprintff("Creating Presentation Space Wrapper....");
                    pWndData = (PNPWINDATA)calloc(sizeof(NPWINDATA), 1);
                    if (pWndData)
                    {
                        pWndData->uMagic    = NPWNDDATA_MAGIC;
                        pWndData->pvMozWnd  = aWindow;
                        pWndData->hpsOS2    = hps;
                        pWndData->pvOdinWnd = pvOdinWnd = calloc(cb, 1);
                        if (pvOdinWnd)
                        {
                            memcpy(pvOdinWnd, aWindow, cb);
                            if (ppWndData)
                                *ppWndData = pWndData;
                        }
                        else
                        {
                            free(pWndData);
                            pWndData = NULL;
                            dprintff("!!!!! Out Of memory !!!!!!");
                        }
                    }
                    else
                        dprintff("!!!!! Out Of memory !!!!!!");
                }

                if (pWndData && pSavedPS)
                {
                    /*
                     * Paint operation - ASSUMES nothing failes!
                     */
                    dprintff("Paint");
                    pvOdinWnd = pWndData->pvOdinWnd;

                    /*
                     * Save browser PS settings.
                     */
                    //npWinSavePS(hps, pSavedPS);
                    if (!pWndData->hdcOdin || pWndData->hpsOS2 != hps)
                    {
                        /*
                         * Create the HPS -> HDC Odin wrapping.
                         */
                        //DebugInt3();
                        #if 0
                        pWndData->hdcOdin = odinHPSToHDC(NULLHANDLE, hps, NULL, NULL);
                        npWinSavePS(hps, &pWndData->SavedOdinPS);
                        #else
                        pWndData->hdcOdin = odinGetDC(hwndDocOdin);
                        #endif
                    }
                    #if 0
                    else
                    {
                        /*
                         * Restore Odin PS settings.
                         */
                        npWinRestorePS(hps, &pWndData->SavedOdinPS);
                        pWndData->SavedOdinPS.lSaveId = GpiSavePS(hps);
                    }
                    #endif

                    /*
                     * Update the structure.
                     */
                    memcpy(pvOdinWnd, pvWindow, cb);
                    ((NPWindow *)pvOdinWnd)->window = (void*)pWndData->hdcOdin;

                    /* flip y ??? */
                    #if 0
                    int yOdin = pSavedPS->sizlPS.cy - y - cy;
                    dprintff("os2y=%d  ->  odiny=%d;  height=%d  parent height=%d!",
                             y, yOdin, cy, pSavedPS->sizlPS.cy);
                    if (fNS4x)
                        ((NPWindow*)pvOdinWnd)->y       = yOdin;
                    else
                        ((NPWindow*)pvOdinWnd)->y = yOdin;
                    #endif
                }
                break;

            default:
                dprintff("Invalid window type %d!!!", type);
                DebugInt3();
                break;
        }


        /*
         * We're done! Return pointer to the wrapper window structure.
         */
        pvWindow = pvOdinWnd;
    }
    else
        dprintff("invalid ptr aWindow(=%x)", aWindow);

    VERIFY_EXCEPTION_CHAIN();
    return pvWindow;
}


/**
 * SetWindow worker - Called after invoking the plugin entry point.
 *
 * @returns Pointer to aWindow or wrapper structure.
 *          The caller doesn't need to care which and must not free it or anything.
 *          The wrapper is freed in WM_NCDESTROY.
 * @param   aWindow     Window structure from Mozilla/Netscape.
 * @param   ppWndData   Place to save/get the window data stuff in the plugin instance.
 *                      Will be set on window wrapper creation, and used if non zero.
 *                      Currently only used the NS4x interface (i.e. may be NULL).
 * @param   pSavedPS    Per call structure. If NULL we cannot do drawing.
 */
void npWinSetWindowEnd(void * aWindow, BOOL fNS4x, PNPWINDATA *ppWndData, PNPSAVEDPS pSavedPS)
{
    VERIFY_EXCEPTION_CHAIN();
    dprintff("enter");

    void * pvWindow = aWindow;
    if (VALID_PTR(pvWindow))
    {
        HPS         hps  = GETMEMB_WND(pvWindow, window, HPS);
        unsigned    type = GETMEMB_WND(pvWindow, type, unsigned);

        switch (type)
        {
            case NPWindowTypeDrawable:
                dprintff("NPWindowTypeDrawable: hps=%#x", hps);
                if (ppWndData && VALID_PTR(*ppWndData) && !pSavedPS)
                {
                    /*
                     * Restore Browser PS settings.
                     */
                    //npWinRestorePS(hps, pSavedPS);
                }
                break;
        }
    }

    dprintff("leave");
}


/**
 *
 */
PNPPRINTDATA        npWinPrintBegin(void * aPlatformPrint, BOOL fNS4x)
{
    VERIFY_EXCEPTION_CHAIN();
    dprintff("enter");

    NPPrint *pPrint = (NPPrint *)aPlatformPrint;

#ifdef DEBUG
    /*
     * !!ASSUMPTIONS!!
     *     1. pPrint->print.embed.window.window must be NULLHANDLE!!!
     *     2. The mode must be known.
     *     3. Netscape and mozilla must use the same structures. - WRONG!!! FIXME!!!!
     */
    if (    pPrint->mode == NP_EMBED
        &&  pPrint->print.embedPrint.window.window)
    {
        dprintff("window handle ASSUMPTION failed\n");
        DebugInt3();
    }
    if (pPrint->mode != NP_EMBED && pPrint->mode != NP_FULL)
    {
        dprintff("mode ASSUMPTION failed\n");
        DebugInt3();
    }
    #if 0 /** @todo fix wrong assumption for netscape!!! */
    if (    offsetof(nsPluginPrint, mode)                       != offsetof(NPPrint, mode)
        ||  offsetof(nsPluginPrint, print)                      != offsetof(NPPrint, print)
        ||  offsetof(nsPluginPrint, print.embedPrint.platformPrint)  != offsetof(NPPrint, print.embedPrint.platformPrint)
        ||  offsetof(nsPluginPrint, print.embedPrint.window)         != offsetof(NPPrint, print.embedPrint.window)
        ||  offsetof(nsPluginPrint, print.embedPrint.window.x)       != offsetof(NPPrint, print.embedPrint.window.x)
        ||  offsetof(nsPluginPrint, print.embedPrint.window.type)    != offsetof(NPPrint, print.embedPrint.window.type)
        )
    {
        dprintff("bad offsets New vs. Old\n");
        dprintf("%d %d\n", offsetof(nsPluginPrint, mode),                          offsetof(NPPrint, mode));
        dprintf("%d %d\n", offsetof(nsPluginPrint, print),                         offsetof(NPPrint, print));
        dprintf("%d %d\n", offsetof(nsPluginPrint, print.embedPrint.platformPrint),offsetof(NPPrint, print.embedPrint.platformPrint));
        dprintf("%d %d\n", offsetof(nsPluginPrint, print.embedPrint.window),       offsetof(NPPrint, print.embedPrint.window));
        dprintf("%d %d\n", offsetof(nsPluginPrint, print.embedPrint.window.x),     offsetof(NPPrint, print.embedPrint.window.x));
        dprintf("%d %d\n", offsetof(nsPluginPrint, print.embedPrint.window.type),  offsetof(NPPrint, print.embedPrint.window.type));
        /*DebugInt3(); @todo fix this! */
    }
    #endif
    #if 0
    if (    offsetof(nsPluginPrintW32, mode)                            != offsetof(nsPluginPrint, mode)
        ||  offsetof(nsPluginPrintW32, print)                           != offsetof(nsPluginPrint, print) + 2
        ||  offsetof(nsPluginPrintW32, print.embedPrint.platformPrint)  != offsetof(nsPluginPrint, print.embedPrint.platformPrint) + 2
        ||  offsetof(nsPluginPrintW32, print.embedPrint.window)         != offsetof(nsPluginPrint, print.embedPrint.window) + 2
        ||  offsetof(nsPluginPrintW32, print.embedPrint.window.x)       != offsetof(nsPluginPrint, print.embedPrint.window.x) + 2
        ||  offsetof(nsPluginPrintW32, print.embedPrint.window.type)    != offsetof(nsPluginPrint, print.embedPrint.window.type) + 2
        )
    {
        dprintff("bad W32 vs. OS/2 (new) offsets\n");
        dprintf("%d %d\n", offsetof(nsPluginPrintW32, mode),                          offsetof(nsPluginPrint, mode));
        dprintf("%d %d\n", offsetof(nsPluginPrintW32, print),                         offsetof(nsPluginPrint, print));
        dprintf("%d %d\n", offsetof(nsPluginPrintW32, print.embedPrint.platformPrint),offsetof(nsPluginPrint, print.embedPrint.platformPrint));
        dprintf("%d %d\n", offsetof(nsPluginPrintW32, print.embedPrint.window),       offsetof(nsPluginPrint, print.embedPrint.window));
        dprintf("%d %d\n", offsetof(nsPluginPrintW32, print.embedPrint.window.x),     offsetof(nsPluginPrint, print.embedPrint.window.x));
        dprintf("%d %d\n", offsetof(nsPluginPrintW32, print.embedPrint.window.type),  offsetof(nsPluginPrint, print.embedPrint.window.type));
    }
    #endif
#endif

    /*
     * Allocate and initiate the print data.
     */
    PNPPRINTDATA pPrtData;
    pPrtData = (PNPPRINTDATA)calloc(sizeof(*pPrtData), 1);
    if (!pPrtData)
    {
        dprintff("Out of memory!!!\n");
        DebugInt3();
        return NULL;
    }
    pPrtData->pvOdinPrt = calloc(sizeof(NPPrintW32), 1);
    if (!pPrtData->pvOdinPrt)
    {
        dprintff("Out of memory !!!\n");
        DebugInt3();
        free(pPrtData);
        return NULL;
    }
    HPS hps = pPrint->mode == NP_FULL
        ? (HPS)pPrint->print.fullPrint.platformPrint
        : (HPS)pPrint->print.embedPrint.platformPrint;
    pPrtData->hpsOS2    = hps;
    pPrtData->pvMozPrt  = aPlatformPrint;

    /*
     * Create the HPS -> HDC Odin wrapping.
     */
    if (hps)
    {
        //DebugInt3();
        npWinSavePS(hps, &pPrtData->SavedPS);
        pPrtData->hdcOdin = odinHPSToHDC(NULLHANDLE, hps, NULL, NULL);
    }

    /*
     * Create the plugin print structure the structure.
     */
    NPPrintW32 *pOdinPrint = (NPPrintW32 *)pPrtData->pvOdinPrt; /* struct can't have NPPrint */
    memcpy(pOdinPrint, aPlatformPrint, sizeof(NPPrintW32)); /* assumes target is smaller. */
    switch (pPrint->mode)
    {
        case NP_FULL:
            pOdinPrint->print.fullPrint.platformPrint   = (void*)pPrtData->hdcOdin;
            pOdinPrint->print.fullPrint.pluginPrinted   = pPrint->print.fullPrint.pluginPrinted;
            pOdinPrint->print.fullPrint.printOne        = pPrint->print.fullPrint.printOne;
            dprintff("Odin Full: platformPrint=%08x pluginPrinted=%d printOne=%d",
                     pOdinPrint->print.fullPrint.platformPrint,
                     pOdinPrint->print.fullPrint.pluginPrinted,
                     pOdinPrint->print.fullPrint.printOne);
            break;

        case NP_EMBED:
            pOdinPrint->print.embedPrint.platformPrint = (void*)pPrtData->hdcOdin;
            pOdinPrint->print.embedPrint.window.window      = pPrint->print.embedPrint.window.window;
            pOdinPrint->print.embedPrint.window.x           = pPrint->print.embedPrint.window.x;
            pOdinPrint->print.embedPrint.window.y           = pPrint->print.embedPrint.window.y;
            pOdinPrint->print.embedPrint.window.width       = pPrint->print.embedPrint.window.width;
            pOdinPrint->print.embedPrint.window.height      = pPrint->print.embedPrint.window.height;
            pOdinPrint->print.embedPrint.window.clipRect    = pPrint->print.embedPrint.window.clipRect;
            pOdinPrint->print.embedPrint.window.type        = pPrint->print.embedPrint.window.type;
            int yOdin = pPrtData->SavedPS.sizlPS.cy
                - pOdinPrint->print.embedPrint.window.y
                - pOdinPrint->print.embedPrint.window.height;
            dprintff("os2y=%d  ->  odiny=%d;  height=%d  parent height=%d!",
                     pOdinPrint->print.embedPrint.window.y, yOdin,
                     pOdinPrint->print.embedPrint.window.height,
                     pPrtData->SavedPS.sizlPS.cy);
            pOdinPrint->print.embedPrint.window.y      = yOdin;
            dprintff("Odin Embed: platformPrint=%08x windows: windows=%08x, (x,y,width,height)=(%d,%d,%d,%d) type=%d",
                     pOdinPrint->print.embedPrint.platformPrint,
                     pOdinPrint->print.embedPrint.window.window,
                     pOdinPrint->print.embedPrint.window.x,
                     pOdinPrint->print.embedPrint.window.y,
                     pOdinPrint->print.embedPrint.window.width,
                     pOdinPrint->print.embedPrint.window.height,
                     pOdinPrint->print.embedPrint.window.type);
            break;
    }

    dprintff("leave");
    VERIFY_EXCEPTION_CHAIN();
    return pPrtData;
}

/** GetWindowLongA */
//static LONG (*WIN32API          pfnGetWindowLongA)(HWND hwnd, int iIndex);


/**
 * Ends the plugin printing session, restoring the PS and freeing memory.
 * @param   pPrintData  Pointer to the structure returned by npWinPrintBegin().
 */
void                npWinPrintEnd(PNPPRINTDATA pPrintData)
{
    VERIFY_EXCEPTION_CHAIN();
    dprintff("enter");

    /*
     * Restore any saved PS.
     */
    if (pPrintData && pPrintData->hdcOdin)
    {
        npWinRestorePS(pPrintData->hpsOS2, &pPrintData->SavedPS);
    }

    /*
     * Free it.
     */
    if (pPrintData)
    {
        free(pPrintData->pvOdinPrt);
        free(pPrintData);
    }

    dprintff("leave");
}


/**
 * Cleans up data for a plugin instance.
 *
 * @param   pWndData    Pointer to window instance data.
 * @todo    Must not be used till we fix the window destruction stuff.
 */
void                npWinDestroyInstance(PNPWINDATA pWndData)
{
    /** @todo implement cleanup! HDC and such. */
    return;
}


/**
 * Create/Find the wrapper for the Netscape Window (document window).
 *
 * @returns Odin handle for hwndOS2.
 * @param   hwndOS2     OS/2 Window handle of browser document window.
 *                      (The window to be wrapped.)
 */
HWND                npWinDownNetscapeWindow(HWND hwndOS2)
{
    dprintff("enter hwndOS2=%#x", hwndOS2);
    HWND hwndFake = NULLHANDLE;

    if (!gfInited)
        npWinInit();
    if (gfInited)
    {
        hwndFake = odinCreateFakeWindowEx(hwndOS2, gWCLevelMinus);
        if (hwndFake)
            odinSetWindowLong(hwndFake, LMINUS1_GWL_OS2HWND, (LONG)hwndOS2);
    }

    #ifdef DEBUG
    HPS hps = WinGetPS(hwndOS2);
    HPS hps2 = WinGetPS(hwndOS2);
    dprintff("leave returning hwndFake=%#x for %#x hps=%#x hps2=%#x", hwndFake, hwndOS2, hps, hps2);
    WinReleasePS(hps);
    WinReleasePS(hps2);
    #endif
    return hwndFake;
}


/**
 * Create a plugin window wrapper.
 * @returns Odin window handle.
 */
HWND                npWinCreateWindowWrapper(HWND hwndOS2, int x, int y, int cx, int cy)
{
    VERIFY_EXCEPTION_CHAIN();
    HWND    hwndRc = NULL;
    if (!gfInited)
        npWinInit();
    if (gfInited)
    {
        /* try to find ShockwaveFlashFullScreen class */

        gWCFlashFS = odinFindAtom(WC_NPWIN_FLASH_FS);
        if (!gWCFlashFS)
        {
            dprintf("npWinInit: failed to register %s.", WC_NPWIN_FLASH_FS);
        } else
        {
            dprintf("npWinInit: Atom [%s] found %x.", WC_NPWIN_FLASH_FS, gWCFlashFS);
        }

        /*
         * Now Acrobat shows us that we must make fake wrappers for every f**king
         * window till we find the browser frame window. (ie. stop at destop)
         *
         * We *must* create these from top to bottom so we get the parent
         * child relationship right.
         */
        HWND    hwndDesktop = WinQueryDesktopWindow(WinQueryAnchorBlock(hwndOS2), NULL);
        HWND    ahwndParents[100 + 1];
        int     cParents = 0;

        HWND    hwndCur = WinQueryWindow(hwndOS2, QW_PARENT);
        while (cParents < 100 && hwndCur != hwndDesktop && hwndCur != HWND_DESKTOP)
        {
            ahwndParents[cParents++] = hwndCur;
            hwndCur = WinQueryWindow(hwndCur, QW_PARENT);
        }


        /*
         * Create wrappers for parents top to bottom.
         *  Note that we assume that this is working and that when
         *  CreateFakeWindowEx returns 0 it's because the window already is wrapped.
         */
        ahwndParents[cParents] = NULL;  /* initialize the +1 entry */
#ifdef EXPERIMENTAL
        if (cParents > 0)
            WinSetOwner(ahwndParents[cParents - 1], ahwndParents[cParents - 1]);
#endif
#if 1
        while (cParents-- > 0)
        {
            HWND hwndFake = odinCreateFakeWindowEx(ahwndParents[cParents], gWCLevelMinus);
            if (hwndFake)
            {
                dprintf("npWinCreateWindowWrapper: created fake window %X", hwndFake);
                odinSetWindowLong(hwndFake, LMINUS1_GWL_OS2HWND, (LONG)ahwndParents[cParents]);
            }
        }
#endif
        /*
         * Now we have established parents and so can create the child.
         */
        HWND hwndFake = odinCreateFakeWindowEx(hwndOS2, gWCLevel0);
        if (hwndFake)
        {
            dprintf("npWinCreateWindowWrapper: fake window level 0 created: %08x", hwndFake);
            hwndRc = odinCreateWindowEx(0 /*??*/,
                                        WC_NPWIN_LEVEL1,
                                        NULL, /* name */
                                        WS_VISIBLE | WS_CHILD | WS_TABSTOP,
                                        0,  0,
                                        cx, cy,
                                        hwndFake,
                                        NULL,
                                        NULL,
                                        (LPVOID)hwndOS2);
            if (hwndRc)
            {
                dprintf("npWinCreateWindowWrapper: window level 1 created: %08x", hwndRc);
                odinSetWindowLong(hwndFake, L0_GWL_OS2PLUGINWINDOW, (LONG)hwndOS2);
                odinSetWindowLong(hwndFake, L0_GWL_LEVEL1_ODINHWND, (LONG)hwndRc);
                odinSetWindowLong(hwndRc,   L1_GWL_OS2PLUGINWINDOW, (LONG)hwndOS2);
                odinSetWindowLong(hwndRc,   L1_GWL_LEVEL0_ODINHWND, (LONG)hwndFake);
            }
            else
            {
                dprintf("npWinCreateWindowWrapper: failed to create window. Returning fake window since that's better than nothing.");
                hwndRc = hwndFake;
            }
        }
        else
            dprintf("npWinCreateWindowWrapper: failed to create fake window. lasterr=@todo");
    }

    dprintf("npWinCreateWindowWrapper: hwndRc=%x", hwndRc);
    VERIFY_EXCEPTION_CHAIN();
    return hwndRc;
}


/**
 * Helper for chaning the Y coordinate from lower-left to upper-left origin.
 *
 * @param   pvOdinWnd   Pointer to window structure.
 * @param   hwnd        OS/2 window handle to the plugin window.
 * @param   y           The OS/2 y position.
 * @param   cy          The OS/2 height.
 * @param   fNS4x       Flags which structure pvOdinWnd is actually pointing to.
 *                      TRUE:   NPWindow
 *                      FALSE:  NPWindow
 */
void npWinFlipY(void *pvOdinWnd, HWND hwnd, int y, unsigned cy, BOOL fNS4x)
{
    HWND hwndParent = WinQueryWindow(hwnd, QW_PARENT);
    if (hwndParent != NULL)
    {
        OS2SWP swp = {0,0,0,0,0,0};
        if (WinQueryWindowPos(hwndParent, &swp))
        {
            int yOdin = swp.cy - y - cy;
            dprintff("os2y=%d  ->  odiny=%d;  height=%d  parent height=%d!",
                     y, yOdin, cy, swp.cy);
            if (fNS4x)
                ((NPWindow*)pvOdinWnd)->y       = yOdin;
            else
                ((NPWindow*)pvOdinWnd)->y = yOdin;
        }
        else
        {
            dprintff("WinQueryWindowPos(%x, QW_PARENT) failed!", hwndParent);
            DebugInt3();
        }
    }
    else
    {
        dprintff("WinQueryWindow(%x, QW_PARENT) failed!", hwnd);
        DebugInt3();
    }
}


/**
 * Notify size/pos change.
 */
void                npWinFakeWindowPosSize(HWND hwndOdin, HWND hwndOS2, int x, int y, int cx, int cy)
{
    VERIFY_EXCEPTION_CHAIN();

    HWND hwndOS2L0 = (HWND)odinGetWindowLong(hwndOdin, L1_GWL_OS2PLUGINWINDOW);
    HWND hwndOdinL0 = (HWND)odinGetWindowLong(hwndOdin, L1_GWL_LEVEL0_ODINHWND);
    if (hwndOS2L0 && hwndOdinL0)
    {
        /*
         * Notify the L0 window. This is a fake window an will handle
         * SetWindowPos as change notification, not an order.
         */
        if (odinSetWindowPos(hwndOdinL0, NULL, 0, 0, cx, cy, SWP_NOZORDER))
            dprintff("successfully notified the pos/size of the fake window");
        else
            dprintff("odinSetWindowPos failed on L0 !!!");

        /*
         * Resize the L1 odin window.
         *  The window should exactly cover the real plugin window.
         */
        if (odinSetWindowPos(hwndOdin, NULL, 0, 0, cx, cy, SWP_NOZORDER))
            dprintff("Successfully changed the pos/size of the L1 wrapper window.");
        else
            dprintff("odinSetWindowPos failed on L1 !!!");

    }
    else
        dprintff("hoom! didn't find hwndOdinL0/hwndOS2L0!!!!");
    VERIFY_EXCEPTION_CHAIN();
}


/**
 * Window procedure for the fake Odin window.
 */
LRESULT npWinLevelMinusWndProc(HWND hwnd, UINT msg, WPARAM mp1, LPARAM mp2)
{
    VERIFY_EXCEPTION_CHAIN();
    dprintff("hwnd=%08x  msg=%08x  mp1=%08x  mp2=%08x !!",
             hwnd, msg, mp1, mp2);

    switch (msg)
    {
        case WM_NCDESTROY:
        {
            dprintff("WM_NCDESTROY - cleaning up memory associated with this window.");
            break;
        }
    }
    return odinDefWindowProc(hwnd, msg, mp1, mp2);
}


#ifdef EXPERIMENTAL
/**
 * Subclassing of the plugin window.
 */
MRESULT _System npWinPluginSubClassWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    VERIFY_EXCEPTION_CHAIN();
    __interrupt(3);
    MRESULT     mres;
    PNPWINDATA      pWndData = (PNPWINDATA)WinQueryProperty(hwnd, WP_NPWINDATA);

    switch (msg)
    {
        case /*WM_QUERYFOCUSCHAIN*/ 0x0051:
        {
            if (LOWORD(mp1) == /* */ 5)
            {
                dprintf("npWinPluginSubClassWndProc: WM_QUERYFOCUSCHAIN: %x %x %x -> TRUE", hwnd, mp1, mp2);
                return (MRESULT)TRUE;
            }
            break;
        }
    }

    mres = pWndData && pWndData->pfnwpOrg ?
        pWndData->pfnwpOrg(hwnd, msg, mp1, mp2) : WinDefWindowProc(hwnd, msg, mp1, mp2);

    switch (msg)
    {
        case /*WM_QUERYFOCUSCHAIN*/ 0x0051:
        {

            dprintf("npWinPluginSubClassWndProc: WM_QUERYFOCUSCHAIN: %x %x %x -> %x", hwnd, mp1, mp2, mres);
            break;
        }
    }

    return mres;
}
#endif

/**
 * Window procedure for the fake Odin window.
 */
LRESULT npWinLevel0WndProc(HWND hwnd, UINT msg, WPARAM mp1, LPARAM mp2)
{
    VERIFY_EXCEPTION_CHAIN();
    dprintff("hwnd=%08x  msg=%08x  mp1=%08x  mp2=%08x !!",
             hwnd, msg, mp1, mp2);

    //    odinSendMessageA(0x68000005, msg, mp1, mp2);

    switch (msg)
    {
#if 0
        case WM_STYLECHANGING:
            if (    mp1 == GWL_STYLE
                &&  ((LPSTYLESTRUCT)mp2)->styleNew & WS_CHILD
                )
                ((LPSTYLESTRUCT)mp2)->styleNew &= ~WS_CHILD;
            break;
#endif
        case WM_NCDESTROY:
        {
            dprintff("WM_NCDESTROY - cleaning up memory associated with this window.");
            /** @sketch Cleanup:
             * Get the OS/2 plugin window handle (Level 0).
             * Get the OS/2 WP_NPWINDATA for the handle. This should point to a
             *      NPWINDATA structure, and is placed there in npxpcom SetWindow().
             * Remove the OS/2 WP_NPWINDATA.
             * Validate the returned pointer.
             * If valid Then free it and its members.
             *
             * Note! We're in Odin context here. take care when calling WinQuery/SetWindowULong()!
             */

            HWND hwndOS2 = (HWND)odinGetWindowLong(hwnd, L0_GWL_OS2PLUGINWINDOW);
            if (((ULONG)hwndOS2 & 0x80000000) /* paranoid validation */)
            {
                USHORT selFSOld = pfnODIN_ThreadLeaveOdinContextNested(NULL, FALSE);
                PNPWINDATA pWndData = (PNPWINDATA)WinQueryProperty(hwndOS2, WP_NPWINDATA);
                WinRemoveProperty(hwndOS2, WP_NPWINDATA);
                if (pWndData)
                {
                    if (    (unsigned)pWndData >= 0x00010000
                        &&  (unsigned)pWndData <  0xc0000000
                        &&  pWndData->uMagic == NPWNDDATA_MAGIC
                        )
                    {
                        //#ifdef DO_DELETE
                        if (pWndData->pvOdinWnd)
                        {
                            /** @todo This free of this member should be delayed perhaps.. we'll see. */
                            delete ((NPWindow*)pWndData->pvOdinWnd);
                        }
                        memset(pWndData, 0, sizeof(*pWndData));
                        delete pWndData;
                        //#endif
                    }
                    else
                    {
                        dprintff("invalid pWndData=%p associated with hwndOS2=%x hwndOdin=%x !!!",
                                 pWndData, hwndOS2, hwnd);
                        DebugInt3();
                    }
                }
                pfnODIN_ThreadEnterOdinContextNested(NULL, FALSE, selFSOld);
            }
            break;
        }
    }
//    odinSendMessageA(0x68000006, msg, mp1, mp2);
    return odinDefWindowProc(hwnd, msg, mp1, mp2);
}

/**
 * Window procedure for the fake Odin window.
 */
LRESULT npWinLevel1WndProc(HWND hwnd, UINT msg, WPARAM mp1, LPARAM mp2)
{
    VERIFY_EXCEPTION_CHAIN();
    if (msg != WM_DESTROY)
        dprintf("npWinLevel1WndProc: hwnd=%08x  msg=%08x  mp1=%08x  mp2=%08x !!",
                hwnd, msg, mp1, mp2);
    else
        dprintf("npWinLevel1WndProc: hwnd=%08x  msg=%08x  mp1=%08x  mp2=%08x WM_DESTROY !!",
                hwnd, msg, mp1, mp2);

    return odinDefWindowProc(hwnd, msg, mp1, mp2);
}

