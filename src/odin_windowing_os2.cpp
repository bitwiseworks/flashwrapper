/* $Id: odin_windowing_os2.cpp,v 1.2 2004/03/10 15:36:41 bird Exp $
 *
 * Plugin Window Hacking - OS2.h dependant code.
 *
 * Copyright (c) 2003 InnoTek Systemberatung GmbH
 * Copyright (c) 2012 bww bitwise works GmbH
 *
 * Authors: knut st. osmundsen <bird@anduin.net>
 *          Dmitriy Kuminov <dmik@dmik.org>
 *
 * All Rights Reserved
 *
 */


/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/
#define INCL_PM
#include <os2.h>

#ifdef __IBMCPP__
# include "moz_VACDefines.h"
#else
# include "moz_GCCDefines.h"
#endif

#include "common.h"
#include <string.h>

/*******************************************************************************
*   External Functions                                                         *
*******************************************************************************/
extern BOOL APIENTRY GpiEnableYInversion(HPS hps, LONG lHeight);
#pragma import (GpiEnableYInversion,, "PMGPI", 723)
extern LONG APIENTRY GpiQueryYInversion(HPS hps);
#pragma import (GpiQueryYInversion,, "PMGPI", 726)



/*******************************************************************************
*   Global Variables                                                           *
*******************************************************************************/
static unsigned acbBundles[PRIM_IMAGE + 1] =
{
    0,
    sizeof(LINEBUNDLE),
    sizeof(CHARBUNDLE),
    sizeof(MARKERBUNDLE),
    sizeof(AREABUNDLE),
    sizeof(IMAGEBUNDLE)
};

static ULONG afAttrMasks[PRIM_IMAGE + 1] =
{
    0,
    LBB_COLOR | LBB_BACK_COLOR | LBB_MIX_MODE  | LBB_BACK_MIX_MODE | LBB_WIDTH | LBB_GEOM_WIDTH | LBB_TYPE | LBB_END | LBB_JOIN,
    CBB_COLOR | CBB_BACK_COLOR | CBB_MIX_MODE  | CBB_BACK_MIX_MODE | CBB_SET | CBB_MODE | CBB_BOX | CBB_ANGLE | CBB_SHEAR | CBB_DIRECTION | CBB_TEXT_ALIGN | CBB_EXTRA | CBB_BREAK_EXTRA,
    MBB_COLOR | MBB_BACK_COLOR | MBB_MIX_MODE  | MBB_BACK_MIX_MODE | MBB_SET | MBB_SYMBOL | MBB_BOX,
    ABB_COLOR | ABB_BACK_COLOR | ABB_MIX_MODE  | ABB_BACK_MIX_MODE | ABB_SET | ABB_SYMBOL | ABB_REF_POINT,
    IBB_COLOR | IBB_BACK_COLOR | IBB_MIX_MODE  | IBB_BACK_MIX_MODE
};


/**
 * Save the Presentation Space to the structure point to by pSet.
 *
 * @returns Success indicator.
 * @param   hps     Handle to the presentation space.
 * @param   pSet    Where to save the PS value.
 */
BOOL              npWinSavePS(HPS hps, PNPSAVEDPS pSet)
{
    memset(pSet, 0, sizeof(*pSet));

    pSet->lSaveId = GpiSavePS(hps);
    if (pSet->lSaveId == GPI_ERROR)
    {
        dprintf(("npWinSavePS: GpiSavePS failed. lastterr=%#x hps=%#x", WinGetLastError(NULLHANDLE), hps));
        return FALSE;
    }
    pSet->lOptions = GpiQueryPS(hps, &pSet->sizlPS);
    pSet->lYInversion = GpiQueryYInversion(hps);
    GpiQueryDefaultViewMatrix(hps, 9, &pSet->matlfDefault);
    #if 0
    GpiQueryViewingTransformMatrix(hps, 9, &pSet->matlfViewing);

    char * pBundle = &pSet->achBundleData[0];
    for (int iPrimType = PRIM_LINE; iPrimType <= PRIM_IMAGE; iPrimType++)
    {
       pSet->aDefMasks[iPrimType] = GpiQueryAttrs(hps, iPrimType, afAttrMasks[iPrimType], pBundle);
       pBundle += acbBundles[iPrimType];
    }

    #ifdef DEBUG
    if (iPrimType > sizeof(pSet->aDefMasks) / sizeof(pSet->aDefMasks[0]))
        DebugInt3();

    if (&pSet->achBundleData[sizeof(pSet->achBundleData)] <= pBundle)
        DebugInt3();
    #endif
    #endif

    return TRUE;
}

/**
 * Restores the Presentation Space using the saved values of pSet.
 *
 * @returns Success indicator.
 * @param   hps     Handle to the presentation space.
 * @param   pSet    Pointer to saved PS values.
 * @remark  pSet->lSaveId will be invalidated by this call.
 */
BOOL              npWinRestorePS(HPS hps, PNPSAVEDPS  pSet)
{
    BOOL    fRc = TRUE;
    ERRORID errid;

    if (!GpiRestorePS(hps, pSet->lSaveId))
    {
        fRc = FALSE;
        dprintf(("npWinRestorePS: GpiRestorePS failed. lastterr=%#x hps=%#x", errid = WinGetLastError(NULLHANDLE), hps));
        DebugInt3();
    }
    if (!GpiSetPS(hps, &pSet->sizlPS, pSet->lOptions))
    {
        fRc = FALSE;
        dprintf(("npWinRestorePS: GpiSetPS failed. lastterr=%#x hps=%#x", errid = WinGetLastError(NULLHANDLE), hps));
        DebugInt3();
    }
    if (!GpiEnableYInversion(hps, pSet->lYInversion))
    {
        fRc = FALSE;
        dprintf(("npWinRestorePS: GpiEnableYInversion failed. lastterr=%#x hps=%#x", errid = WinGetLastError(NULLHANDLE), hps));
        DebugInt3();
    }
    if (!GpiSetDefaultViewMatrix(hps, 9, &pSet->matlfDefault, TRANSFORM_REPLACE))
    {
        fRc = FALSE;
        dprintf(("npWinRestorePS: GpiSetDefaultViewMatrix failed. lastterr=%#x hps=%#x", errid = WinGetLastError(NULLHANDLE), hps));
        DebugInt3();
    }
    #if 0 /* PMERR_INV_MICROPS_FUNCTION */
    if (!GpiSetViewingTransformMatrix(hps, 9, &pSet->matlfViewing, TRANSFORM_REPLACE))
    {
        fRc = FALSE;
        dprintf(("npWinRestorePS: GpiSetViewingTransformMatrix failed. lastterr=%#x hps=%#x", errid = WinGetLastError(NULLHANDLE), hps));
        DebugInt3();
    }

    char * pBundle = &pSet->achBundleData[0];
    for (int iPrimType = PRIM_LINE; iPrimType <= PRIM_IMAGE; iPrimType++)
    {
       if (!GpiSetAttrs(hps, iPrimType, afAttrMasks[iPrimType], pSet->aDefMasks[iPrimType], pBundle))
       {
           fRc = FALSE;
           dprintf(("npWinRestorePS: GpiSetAttrs %i failed. lastterr=%#x hps=%#x", iPrimType, errid = WinGetLastError(NULLHANDLE), hps));
           //DebugInt3();
       }
       pBundle += acbBundles[iPrimType];
    }
    #endif
    if (!fRc)
        dprintf(("npWinRestorePS: one or more operations failed. lastterr=%#x hps=%#x", WinGetLastError(NULLHANDLE), hps));
    return fRc;
}

