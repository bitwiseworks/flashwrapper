/* $Id: wrap_NS4x.cpp,v 1.12 2004/03/10 15:36:41 bird Exp $
 *
 * Netscape v4.x Plugin interface.
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
*   Defined Constants And Macros                                               *
*******************************************************************************/
/** safely dprintf a string. */
#define DPRINTF_STR(pszStr)  \
    do                                                                             \
    {                                                                              \
        if (VALID_PTR(pszStr))                                                     \
            dprintf(("%s: %s=%s", szFunction, #pszStr, pszStr));                   \
        else if (pszStr)                                                           \
            dprintf(("%s: %s=%p (illegal pointer)", szFunction, #pszStr, pszStr)); \
        else                                                                       \
            dprintf(("%s: %s=<NULL>", szFunction, #pszStr));                       \
    } while (0)

/** safely dprintf a string, if it's NULL it will be ignored. */
#define DPRINTF_STRNULL(pszStr)  \
    do                                                                             \
    {                                                                              \
        if (VALID_PTR(pszStr))                                                     \
            dprintf(("%s: %s=%s", szFunction, #pszStr, pszStr));                   \
        else if (pszStr)                                                           \
            dprintf(("%s: %s=%p (illegal pointer)", szFunction, #pszStr, pszStr)); \
    } while (0)

/** Print stream data */
#define DPRINTF_STREAM(pStream)                                                    \
    do                                                                             \
    {                                                                              \
        if (VALID_PTR(pStream))                                                    \
        {                                                                          \
            dprintf(("%s: *stream: pdata=%p ndata=%p url=%p end=%d lastmodified=%x notifyData=%p", \
                     szFunction, (pStream)->pdata, (pStream)->ndata,               \
                     (pStream)->url, (pStream)->end, (pStream)->lastmodified,      \
                     (pStream)->notifyData));                                      \
            DPRINTF_STR((pStream)->url);                                           \
        }                                                                          \
    } while (0)


/** Debug DOS32TIB assertion. */
#ifdef DEBUG
#define NPXP_ASSERT_OS2FS()     \
        extern void * DOS32TIB;                                                     \
        if (npGetFS() != (USHORT)(unsigned)&DOS32TIB)                               \
        {                                                                           \
            dprintf(("%s: fs is wrong (%x) !!!", szFunction, npGetFS()));           \
            DebugInt3();                                                            \
        }
#else
#define NPXP_ASSERT_OS2FS()     do {} while (0)
#endif

/** Get and validate the instance pointer */
#define NP4XUP_INSTANCE(fAllowNULL) \
    PNPLUGININSTANCE    pInst = (PNPLUGININSTANCE)instance->pdata;                  \
    if (!VALID_PTR(pInst) || pInst->auMagic != NPLUGININSTANCE_MAGIC)               \
    {                                                                               \
        if (!fAllowNULL || pInst)                                                   \
            dprintf(("%s: Invalid Instance Pointer %#x!!!\n", szFunction, pInst));  \
        pInst = NULL;                                                               \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        if (pInst->pOrgInstance != instance)                                        \
        {                                                                           \
            dprintf(("%s: Warning! pInst->pOrgInstance (%p) != instance (%p)!!!\n", \
                     szFunction, pInst->pOrgInstance, instance));                   \
            DebugInt3();                                                            \
            pInst->pOrgInstance = instance;                                         \
        }                                                                           \
        pInst->w32.ndata = pInst;                                                   \
    }

/** Get the 'correct' w32 instance pointer. */
#define NP4XUP_W32_INSTANCE() \
        pInst ? &pInst->w32 : instance

/** Get and validate the instance pointer */
#define NP4XDOWN_INSTANCE(fAllowNULL) \
    PNPLUGININSTANCE    pInst = NULL;                                               \
    if (VALID_PTR(instance))                                                        \
        pInst = (PNPLUGININSTANCE)instance->ndata;                                  \
    if (!VALID_PTR(pInst) || pInst->auMagic != NPLUGININSTANCE_MAGIC)               \
    {                                                                               \
        if (!fAllowNULL || pInst)                                                   \
            dprintf(("%s: Invalid Instance Pointer pInst=%p, instance=%p!!!\n",     \
                     szFunction, pInst, instance));                                 \
        pInst = NULL;                                                               \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        if ((char*)instance - offsetof(NPLUGININSTANCE, w32) != (char*)pInst)       \
            dprintf(("%s: Bogus Instance Pointer pInst=%p, instance=%p!!!\n",       \
                     szFunction, pInst, instance));                                 \
    }

/** Get the 'correct' netscape instance pointer. */
#define NP4XDOWN_NS_INSTANCE() \
        pInst ? pInst->pOrgInstance : instance

/** Enter odin context from OS/2 netscape/mozilla context. */
#define NP4XUP_ENTER_ODIN(fDebug) \
    VERIFY_EXCEPTION_CHAIN(); \
    NPXP_ASSERT_OS2FS(); \
    unsigned ExceptionRegRec[2] = {0,0}; \
    USHORT selFSOld = pfnODIN_ThreadEnterOdinContext(&ExceptionRegRec[0], TRUE); \
    VERIFY_EXCEPTION_CHAIN(); \
    if (fDebug) DebugInt3()

/** Leave odin context and go back into the OS/2 netscape/mozilla context. */
#define NP4XUP_LEAVE_ODIN(fDebug) \
    if (fDebug) DebugInt3();  \
    VERIFY_EXCEPTION_CHAIN(); \
    pfnODIN_ThreadLeaveOdinContext(&ExceptionRegRec[0], selFSOld); \
    ExceptionRegRec[0] = ExceptionRegRec[1] = 0; \
    VERIFY_EXCEPTION_CHAIN(); \
    NPXP_ASSERT_OS2FS()


/** Leave odin context to go into the OS/2 netscape/mozilla context temporarily. */
#define NP4XDOWN_LEAVE_ODIN(fDebug) \
    VERIFY_EXCEPTION_CHAIN(); \
    USHORT selFSOld = pfnODIN_ThreadLeaveOdinContextNested(NULL, FALSE); \
    VERIFY_EXCEPTION_CHAIN(); \
    NPXP_ASSERT_OS2FS(); \
    if (fDebug) DebugInt3()

/** Reenter odin context. */
#define NP4XDOWN_ENTER_ODIN(fDebug) \
    if (fDebug) DebugInt3();  \
    VERIFY_EXCEPTION_CHAIN(); \
    pfnODIN_ThreadEnterOdinContextNested(NULL, FALSE, selFSOld); \
    VERIFY_EXCEPTION_CHAIN()

/** dprintf a nsID structure (reference to such). */
#define DPRINTF_NSID(refID)  \
    if (VALID_REF(refID))                                                                     \
        dprintf(("%s: %s={%08x,%04x,%04x,%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x} %s (%p)",   \
                szFunction, #refID, (refID).m0, (refID).m1, (refID).m2, (refID).m3[0], (refID).m3[1],   \
                (refID).m3[2], (refID).m3[3], (refID).m3[4], (refID).m3[5], (refID).m3[6], (refID).m3[7], \
                getIIDCIDName(refID), &(refID)));                                             \
    else                                                                                      \
        dprintf(("%s: %s=%p (illegal pointer!!!)", szFunction, #refID, &(refID)))


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

#include "moz_IDs_Generated.h"

/*******************************************************************************
*   Structures and Typedefs                                                    *
*******************************************************************************/
#pragma pack(4)
/**
 * Win 32 Plugin Entrypoints.
 */
#define NPW32CALLBACK   __cdecl
struct _NP32PluginFuncs
{
    uint16                       size;
    uint16                       version;
    NPError     (* NPW32CALLBACK pfnNewUPP)(NPMIMEType pluginType, NPP instance, uint16 mode, int16 argc, char* argn[], char* argv[], NPSavedData* saved);
    NPError     (* NPW32CALLBACK pfnDestroyUPP)(NPP instance, NPSavedData** save);
    NPError     (* NPW32CALLBACK pfnSetWindowUPP)(NPP instance, NPWindow* window);
    NPError     (* NPW32CALLBACK pfnNewStreamUPP)(NPP instance, NPMIMEType type, NPStream* stream, NPBool seekable, uint16* stype);
    NPError     (* NPW32CALLBACK pfnDestroyStreamUPP)(NPP instance, NPStream* stream, NPReason reason);
    void        (* NPW32CALLBACK pfnStreamAsFileUPP)(NPP instance, NPStream* stream, const char* fname);
    int32       (* NPW32CALLBACK pfnWriteReadyUPP)(NPP instance, NPStream* stream);
    int32       (* NPW32CALLBACK pfnWriteUPP)(NPP instance, NPStream* stream, int32 offset, int32 len, void* buffer);
    void        (* NPW32CALLBACK pfnPrintUPP)(NPP instance, NPPrint* platformPrint);
    int16       (* NPW32CALLBACK pfnHandleEventUPP)(NPP instance, void* event);
    void        (* NPW32CALLBACK pfnURLNotifyUPP)(NPP instance, const char* url, NPReason reason, void* notifyData);
    JRIGlobalRef javaClass;
    NPError     (* NPW32CALLBACK pfnGetValueUPP)(NPP instance, NPPVariable variable, void *ret_alue);
    NPError     (* NPW32CALLBACK pfnSetValueUPP)(NPP instance, NPNVariable variable, void *ret_alue);
};


/**
 * Win32 Netscape Entrypoints.
 */
struct _NP32NetscapeFuncs
{
    uint16                       size;
    uint16                       version;
    NPError     (* NPW32CALLBACK pfnGetURLUPP)(NPP instance, const char* url, const char* window);
    NPError     (* NPW32CALLBACK pfnPostURLUPP)(NPP instance, const char* url, const char* window, uint32 len, const char* buf, NPBool file);
    NPError     (* NPW32CALLBACK pfnRequestReadUPP)(NPStream* stream, NPByteRange* rangeList);
    NPError     (* NPW32CALLBACK pfnNewStreamUPP)(NPP instance, NPMIMEType type, const char* window, NPStream** stream);
    int32       (* NPW32CALLBACK pfnWriteUPP)(NPP instance, NPStream* stream, int32 len, void* buffer);
    NPError     (* NPW32CALLBACK pfnDestroyStreamUPP)(NPP instance, NPStream* stream, NPReason reason);
    void        (* NPW32CALLBACK pfnStatusUPP)(NPP instance, const char* message);
    const char* (* NPW32CALLBACK pfnUserAgentUPP)(NPP instance);
    void*       (* NPW32CALLBACK pfnMemAllocUPP)(uint32 size);
    void        (* NPW32CALLBACK pfnMemFreeUPP)(void* ptr);
    uint32      (* NPW32CALLBACK pfnMemFlushUPP)(uint32 size);
    void        (* NPW32CALLBACK pfnReloadPluginsUPP)(NPBool reloadPages);
    JRIEnv*     (* NPW32CALLBACK pfnGetJavaEnvUPP)(void);
    jref        (* NPW32CALLBACK pfnGetJavaPeerUPP)(NPP instance);
    NPError     (* NPW32CALLBACK pfnGetURLNotifyUPP)(NPP instance, const char* url, const char* window, void* notifyData);
    NPError     (* NPW32CALLBACK pfnPostURLNotifyUPP)(NPP instance, const char* url, const char* window, uint32 len, const char* buf, NPBool file, void* notifyData);
    NPError     (* NPW32CALLBACK pfnGetValueUPP)(NPP instance, NPNVariable variable, void *ret_alue);
    NPError     (* NPW32CALLBACK pfnSetValueUPP)(NPP instance, NPPVariable variable, void *ret_alue);
    void        (* NPW32CALLBACK pfnInvalidateRectUPP)(NPP instance, NPRect *rect);
    void        (* NPW32CALLBACK pfnInvalidateRegionUPP)(NPP instance, NPRegion region);
    void        (* NPW32CALLBACK pfnForceRedrawUPP)(NPP instance);
/*
    NPN_GetStringIdentifierUPP getstringidentifier;
    NPN_GetStringIdentifiersUPP getstringidentifiers;
    NPN_GetIntIdentifierUPP getintidentifier;
    NPN_IdentifierIsStringUPP identifierisstring;
    NPN_UTF8FromIdentifierUPP utf8fromidentifier;
    NPN_IntFromIdentifierUPP intfromidentifier;
    NPN_CreateObjectUPP createobject;
    NPN_RetainObjectUPP retainobject;
    NPN_ReleaseObjectUPP releaseobject;
    NPN_InvokeUPP invoke;
    NPN_InvokeDefaultUPP invokeDefault;
    NPN_EvaluateUPP evaluate;
    NPN_GetPropertyUPP getproperty;
    NPN_SetPropertyUPP setproperty;
    NPN_RemovePropertyUPP removeproperty;
    NPN_HasPropertyUPP hasproperty;
    NPN_HasMethodUPP hasmethod;
    NPN_ReleaseVariantValueUPP releasevariantvalue;
    NPN_SetExceptionUPP setexception;
    NPN_PushPopupsEnabledStateUPP pushpopupsenabledstate;
    NPN_PopPopupsEnabledStateUPP poppopupsenabledstate;
    */

    /*
     * we are not implementing whole functions,
     * but have to reserve memory for them
     * currently, there is 21 missed functions
     */

    char buf[21*4];

};
#pragma pack()


#define INCL_NS4X
#define INCL_MOZXPCOM
#include "common.h"



/*******************************************************************************
*   Structures and Typedefs                                                    *
*******************************************************************************/
#pragma pack(1)
/**
 * Plugin Entrypoints wrapper.
 */
typedef struct _PluginFuncsWrapper
{
    /** Pointer to the next wrapper in the chain. */
    struct _PluginFuncsWrapper * pNext;

    /** Pointer to the original struct. (do we need to keep this around?) */
    NPPluginFuncs *     pNative;

    /** padding for 16byte code aligment. */
    char                uaPadding1[8];

    /** Stub code for each handler. */
    struct PluginFuncStuc
    {
        char            chPush;
        void *          pvImm32bit;
        char            chCall;
        int             offRel32bit;
        char            chPopEcx;
        char            chRet;
        char            achMagic[4];    /* 0xcccccccc */
    }   aStubs[32];

    /** The stuff we present to the Win32 side. */
    struct _NP32PluginFuncs     w32;
    /** Safety paddings */
    unsigned            auPadding2[64];
} NPLUGINFUNCSWRAPPER,  *PNPLUGINFUNCSWRAPPER;


/**
 * Netscape Entrypoints Wrapper.
 */
typedef struct _NetscapeFuncsWrapper
{
    /** Pointer to the next wrapper in the chain. */
    struct _NetscapeFuncsWrapper * pNext;

    /** Pointer to the original struct. (do we need to keep this around?) */
    NPNetscapeFuncs *   pNative;

    /** padding for 16byte code aligment. */
    char                auPadding[8];

    /** Stub code for each handler. */
    struct NetscapeFuncStuc
    {
        char            chPush;
        void *          pvImm32bit;
        char            chCall;
        int             offRel32bit;
        char            chPopEcx;
        char            chRet;
        char            achMagic[4];    /* 0xcccccccc */
    }   aStubs[32];

    /** The stuff we present to the Win32 side. */
    struct _NP32NetscapeFuncs     w32;
    /** Safety paddings */
    unsigned            auPadding2[64];
} NETSCAPEFUNCSWRAPPER,  *PNETSCAPEFUNCSWRAPPER;

#pragma pack()


/**
 * Plugin instance data.
 */
typedef struct _PluginInstance
{
    /** Magic number we check for. */
    #define NPLUGININSTANCE_MAGIC 0xc003c004
    unsigned    auMagic;

    /** Window data. Must be zeroed on creation! */
    PNPWINDATA  pWndData;

    /** Pointer to the orignal instance */
    NPP         pOrgInstance;

    /** Browser document window - quick hack for GetValue(). */
    HWND        hwndOS2;
    HWND        hwndOdin;

    /** The stuff we present to the plugin. */
    NPP_t       w32;
} NPLUGININSTANCE, *PNPLUGININSTANCE;



/*******************************************************************************
*   Global Variables                                                           *
*******************************************************************************/
/** This variable is used to drag in XPCOM in the linking of a primary wrapper. */
int             giNS4x;

#ifdef __IBMCPP__
/*
 * This weak resolving ASSUMES that the caller cleans the stack!
 * (i.e. anything but __stdcall calling convention will work very nicely.)
 */
extern "C" void *   NPJNICreateDownWrapperWeakStub(void);
extern "C" unsigned upCreateWrapperWeakStub(void **pv1, void *pv2, int rc);
extern "C" const char * getIIDCIDNameWeakStub(void *pv1);
#pragma weak(NPJNICreateDownWrapper, NPJNICreateDownWrapperWeakStub)
#pragma weak(upCreateWrapper, upCreateWrapperWeakStub)
#pragma weak(getIIDCIDName, getIIDCIDNameWeakStub)
#endif

/*
 * Disable conditinal warnings on VAC
 */
#pragma info(nocnd)
#pragma info(trd)



//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// UP wrappers (stuff that is presented to netscape/mozilla)
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//


NPError NP_LOADDS np4xUp_New(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPMIMEType pluginType, NPP instance,
                             uint16 mode, int16 argc, char* argn[],
                             char* argv[], NPSavedData* saved)
{
    static const char szFunction[] = "np4xUp_New";
    dprintf(("%s: enter - pWrapper=%p pluginType=%d instance=%p mode=%d argc=%d argn=%p argv=%p saved=%p",
             szFunction, pWrapper, pluginType, instance, mode, argc, argn, argv, saved));
    DPRINTF_STR(pluginType);
    int i;
    //for (i = 0; i < argc; i++)
    //    dprintf(("%s: '%s'='%s'", szFunction, argn[i], argv[i]));

    /* Windowless flash hack - make windows. */
    #if 1
    for (i = 0; i < argc; i++)
        if (!stricmp(argn[i], "wmode"))
        {
            argn[i][2] = 'x';
            argn[i][3] = 'x';
            argn[i][4] = 'x';
            dprintf(("%s: nuked wmode %d.", szFunction, i));
        }
        //dprintf(("%s: '%s'='%s'", szFunction, argn[i], argv[i]));
    #endif

    /*
     * Allocate and initialize a instance structure
     */
    PNPLUGININSTANCE    pInst = (PNPLUGININSTANCE)malloc(sizeof(*pInst));
    if (!pInst)
        return NPERR_OUT_OF_MEMORY_ERROR;
    pInst->auMagic = NPLUGININSTANCE_MAGIC;
    pInst->w32.pdata = instance->pdata;
    pInst->w32.ndata = pInst;
    pInst->pOrgInstance = instance;
    pInst->pWndData = NULL;
    instance->pdata = pInst;

    /*
     * Let the plugin initialize it self.
     */
    dprintf(("pfnNewUPP enter"));
    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = pWrapper->w32.pfnNewUPP(pluginType, NP4XUP_W32_INSTANCE(), mode, argc, argn, argv, saved);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf(("pfnNewUPP leave"));
    /*
     * Cleanup in case of error.
     */
    if (rc)
    {
        instance->pdata = NULL;
        free(pInst);
    }

    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


NPError NP_LOADDS np4xUp_Destroy(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPSavedData** save)
{
    static const char szFunction[] = "np4xUp_Destroy";
    dprintf(("%s: enter - pWrapper=%p instance=%p saved=%p",
             szFunction, pWrapper, instance, save));

    NP4XUP_INSTANCE(TRUE);

    dprintf(("pfnDestroyUPP enter"));
    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = pWrapper->w32.pfnDestroyUPP(NP4XUP_W32_INSTANCE(), save);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf(("pfnDestroyUPP leave"));

    /*
     * Cleanup any plugin instance data.
     */
    if (pInst)
    {
        if (pInst->pWndData)
        {
            npWinDestroyInstance(pInst->pWndData);
            pInst->pWndData = NULL;
        }
        instance->pdata = NULL;
        free(pInst);
    }

    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}

#include "moz\include\plugin\nsplugindefs.h"

static NPP old_instance = 0;

NPError NP_LOADDS np4xUp_SetWindow(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPWindow* window)
{
    static const char szFunction[] = "np4xUp_SetWindow";
    dprintf(("%s: enter - pWrapper=%p instance=%p window=%p",
             szFunction, pWrapper, instance, window));

    NP4XUP_INSTANCE(FALSE);

    dprintf(("Mozilla window before npWinSetWindowBegin "));
    dprintf(("window: %x win: (%i,%i)-(%i,%i), rect: (%i,%i)-(%i,%i)",
             window->window, window->x, window->y,
             window->width, window->height,
             window->clipRect.left, window->clipRect.top,
             window->clipRect.right, window->clipRect.bottom));

    /*
     * Start window/ps wrapping routine.
     * (Must be called out of Odin context!)
     */
    NPWindow *  pWindow;
    NPSAVEDPS   PerSetWindow;
    pWindow = (NPWindow *)npWinSetWindowBegin(window,
                                              TRUE,
                                              pInst ? &pInst->pWndData : NULL,
                                              &PerSetWindow,
                                              pInst ? pInst->hwndOS2 : NULLHANDLE,
                                              pInst ? pInst->hwndOdin : NULLHANDLE);

    dprintf(("Mozilla window after npWinSetWindowBegin "));
    dprintf(("window: %x win: (%i,%i)-(%i,%i), rect: (%i,%i)-(%i,%i)",
             pWindow->window, pWindow->x, pWindow->y,
             pWindow->width, pWindow->height,
             pWindow->clipRect.left, pWindow->clipRect.top,
             pWindow->clipRect.right, pWindow->clipRect.bottom));

    /*
     * Now enter Odin context and call the real method.
     */
    // vladest
    //////////////////////////////////
    //if (window->y < 0) window->y = 0;
    //if (pWindow->y < 0) pWindow->y = 0;
    //////////////////////////////////
    dprintf(("pfnSetWindowUPP enter. address %08X", pWrapper->w32.pfnSetWindowUPP));
    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = 1;
    rc = pWrapper->w32.pfnSetWindowUPP(NP4XUP_W32_INSTANCE(), pWindow);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf(("pfnSetWindowUPP leave"));
    #if 0
    /*
     * Fake a handle even call for WM_PAINT.
     */
    if (window->type == 2)
    {
        extern int16   NP_LOADDS np4xUp_HandleEvent(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, void* event);
        NPEvent event;
        event.event = WM_PAINT;
        event.wParam = (uint32)window->window;
        event.lParam = (uint32)&window->x; //???
        np4xUp_HandleEvent(pWrapper, pvCaller, instance, &event);
    }
    #endif

    /*
     * End the window/ps wrapping.
     * (Must be called out of Odin context!)
     */
    npWinSetWindowEnd(window, TRUE, pInst ? &pInst->pWndData : NULL, &PerSetWindow);
    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


NPError NP_LOADDS np4xUp_NewStream(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPMIMEType type,
                                   NPStream* stream, NPBool seekable,
                                   uint16* stype)
{
    static const char szFunction[] = "np4xUp_NewStream";
    dprintf(("%s: enter - pWrapper=%p instance=%p type=%p stream=%p seekable=%d stype=%p",
             szFunction, pWrapper, instance, type, stream, seekable, stype));
    DPRINTF_STR(type);
    DPRINTF_STREAM(stream);
    NP4XUP_INSTANCE(FALSE);

    NP4XUP_ENTER_ODIN(FALSE);
    dprintf(("pfnNewStreamUPP enter"));
    NPError rc = pWrapper->w32.pfnNewStreamUPP(NP4XUP_W32_INSTANCE(), type, stream, seekable, stype);
    dprintf(("pfnNewStreamUPP leave"));
    NP4XUP_LEAVE_ODIN(FALSE);

    if (!rc)
        DPRINTF_STREAM(stream);

    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


NPError NP_LOADDS np4xUp_DestroyStream(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPStream* stream, NPReason reason)
{
    static const char szFunction[] = "np4xUp_DestroyStream";
    dprintf(("%s: enter - pWrapper=%p instance=%p stream=%p reason=%d",
             szFunction, pWrapper, instance, stream, reason));
    DPRINTF_STREAM(stream);
    NP4XUP_INSTANCE(FALSE);

    NP4XUP_ENTER_ODIN(FALSE);
    dprintf(("pfnDestroyStreamUPP enter"));
    NPError rc = pWrapper->w32.pfnDestroyStreamUPP(NP4XUP_W32_INSTANCE(), stream, reason);
    dprintf(("pfnDestroyStreamUPP leave"));
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


int32   NP_LOADDS np4xUp_WriteReady(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPStream* stream)
{
    static const char szFunction[] = "np4xUp_WriteReady";
    dprintf(("%s: enter - pWrapper=%p instance=%p stream=%p",
             szFunction, pWrapper, instance, stream));
    DPRINTF_STREAM(stream);
    NP4XUP_INSTANCE(FALSE);

    dprintf(("pfnWriteReadyUPP enter"));
    NP4XUP_ENTER_ODIN(FALSE);
    int32 rc = pWrapper->w32.pfnWriteReadyUPP(NP4XUP_W32_INSTANCE(), stream);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf(("pfnWriteReadyUPP leave"));

    DPRINTF_STREAM(stream);
    dprintf(("%s: leave rc=%i", szFunction, rc));
    return rc;
}


int32   NP_LOADDS np4xUp_Write(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPStream* stream, int32 offset,
                               int32 len, void* buffer)
{
    static const char szFunction[] = "np4xUp_Write";
    dprintf(("%s: enter - pWrapper=%p instance=%p stream=%p offset=%d len=%d buffer=%p",
             szFunction, pWrapper, instance, stream, offset, len, buffer));
    DPRINTF_STREAM(stream);
    NP4XUP_INSTANCE(FALSE);
#if 0
    {
        int i;
        dprintf(("written buffer chunk: "));
        for (i=0;i < 16;i++)
            dprintf(("%02X",(unsigned char)*(((unsigned char*)buffer)+i+offset)));
    }
    {
        int i;
        dprintf(("without offset: "));
        for (i=0;i < 16;i++)
            dprintf(("%02X",(unsigned char)*(((unsigned char*)buffer)+i)));
    }
#endif
    dprintf(("pfnWriteUPP enter"));
    NP4XUP_ENTER_ODIN(FALSE);
    int32 rc = pWrapper->w32.pfnWriteUPP(NP4XUP_W32_INSTANCE(), stream, offset, len, buffer);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf(("pfnWriteUPP leave"));
    DPRINTF_STREAM(stream);
    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


void    NP_LOADDS np4xUp_StreamAsFile(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPStream* stream, const char* fname)
{
    static const char szFunction[] = "np4xUp_StreamAsFile";
    dprintf(("%s: enter - pWrapper=%p instance=%p stream=%p fname=%p",
             szFunction, pWrapper, instance, stream, fname));
    DPRINTF_STREAM(stream);
    DPRINTF_STR(fname);
    //@todo character conversion of filename!
    NP4XUP_INSTANCE(FALSE);

    NP4XUP_ENTER_ODIN(FALSE);
    dprintf(("pfnStreamAsFileUPP enter"));
    pWrapper->w32.pfnStreamAsFileUPP(NP4XUP_W32_INSTANCE(), stream, fname);
    dprintf(("pfnStreamAsFileUPP leave"));
    NP4XUP_LEAVE_ODIN(FALSE);

    DPRINTF_STREAM(stream);
    dprintf(("%s: leave", szFunction));
    return;
}


void    NP_LOADDS np4xUp_Print(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPPrint* platformPrint)
{
    static const char szFunction[] = "np4xUp_Print";
    dprintf(("%s: enter - pWrapper=%p instance=%p platformPrint=%p",
             szFunction, pWrapper, instance, platformPrint));
    if (platformPrint)
    {
        if (platformPrint->mode == NP_EMBED)
            dprintf(("%s: Embed: platformPrint=%08x windows: windows=%08x, (x,y,width,height)=(%d,%d,%d,%d) type=%d",
                     szFunction,
                     platformPrint->print.embedPrint.platformPrint,
                     platformPrint->print.embedPrint.window.window,
                     platformPrint->print.embedPrint.window.x,
                     platformPrint->print.embedPrint.window.y,
                     platformPrint->print.embedPrint.window.width,
                     platformPrint->print.embedPrint.window.height,
                     platformPrint->print.embedPrint.window.type));
        else if (platformPrint->mode == NP_FULL)
            dprintf(("%s: Full: platformPrint=%08x pluginPrinted=%d printOne=%d",
                     szFunction,
                     platformPrint->print.fullPrint.platformPrint,
                     platformPrint->print.fullPrint.pluginPrinted,
                     platformPrint->print.fullPrint.printOne));
        else
            dprintf(("%s: Unknown mode!", szFunction));
    }

    NP4XUP_INSTANCE(FALSE);

    NP4XUP_ENTER_ODIN(FALSE);
    /*
     * Straight forward stuff.
     *      - Full mode and no HPS. (Acrobat plugin)
     */
    if (    platformPrint->mode == NP_FULL
        &&  platformPrint->print.fullPrint.platformPrint == NULL)
    {   /* assumes struct is 100% idendical on windows. */
        dprintf(("*simple printing case*"));
        pWrapper->w32.pfnPrintUPP(NP4XUP_W32_INSTANCE(), platformPrint);
    }
    else
    {
        /*
         * Complex stuff, which means converting a HPS and perhaps a HWND.
         */
#if 0
        ReleaseInt3(0x44440001,0x44440001,0x44440001);
        pWrapper->w32.pfnPrintUPP(NP4XUP_W32_INSTANCE(), platformPrint);
#endif
    }
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintf(("%s: leave", szFunction));
    return;
}


int16   NP_LOADDS np4xUp_HandleEvent(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, void* event)
{
    static const char szFunction[] = "np4xUp_HandleEvent";
    dprintf(("%s: enter - pWrapper=%p instance=%p event=%p",
             szFunction, pWrapper, instance, event));
    NP4XUP_INSTANCE(FALSE);

    /** @todo WM_PAINT handling and stuff. */
    ReleaseInt3(0x44440002,0x44440002,0x44440002);

    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = pWrapper->w32.pfnHandleEventUPP(NP4XUP_W32_INSTANCE(), event);
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


void    NP_LOADDS np4xUp_URLNotify(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, const char* url,
                                   NPReason reason, void* notifyData)
{
    static const char szFunction[] = "np4xUp_URLNotify";
    dprintf(("%s: enter - pWrapper=%p instance=%p url=%p reaons=%d notifyData=%p",
             szFunction, pWrapper, instance, url, reason, notifyData));
    DPRINTF_STR(url);
    //@todo TEXT: url needs attention.
    NP4XUP_INSTANCE(FALSE);

    NP4XUP_ENTER_ODIN(FALSE);
    pWrapper->w32.pfnURLNotifyUPP(NP4XUP_W32_INSTANCE(), url, reason, notifyData);
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintf(("%s: leave", szFunction));
    return;
}


jref    NP_LOADDS np4xUp_GetJavaClass(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller)
{
    static const char szFunction[] = "np4xUp_GetJavaClass";
    dprintf(("%s: enter - pWrapper=%p", szFunction, pWrapper));

    NP4XUP_ENTER_ODIN(FALSE);
    ReleaseInt3(0x44440003,0x44440003,0x44440003);
    jref rc = 0;// = pWrapper->w32.pfnGetJavaClassUPP();
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintf(("%s: leave rc=%p", szFunction, rc));
    return rc;
}


NPError NP_LOADDS np4xUp_GetValue(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPPVariable variable, void *value)
{
    static const char szFunction[] = "np4xUp_GetValue";
    NPError rc = 0;

    dprintf(("%s: enter - pWrapper=%p instance=%p variable=%d value=%p",
             szFunction, pWrapper, instance, variable, value));
    NP4XUP_INSTANCE(FALSE);
    switch (variable)
    {
    case NPPVpluginDescriptionString:       dprintf(("variable=NPPVpluginDescriptionString")); break;
    case NPPVpluginNameString:              dprintf(("variable=NPPVpluginNameString")); break;
    case NPPVpluginWindowBool:              dprintf(("variable=NPPVpluginWindowBool")); break;
    case NPPVpluginTransparentBool:         dprintf(("variable=NPPVpluginTransparentBool")); break;
    case NPPVjavaClass:                     dprintf(("variable=NPPVjavaClass")); break;
    case NPPVpluginWindowSize:              dprintf(("variable=NPPVpluginWindowSize")); break;
    case NPPVpluginTimerInterval:           dprintf(("variable=NPPVpluginTimerInterval")); break;
    case NPPVpluginScriptableInstance:      dprintf(("variable=NPPVpluginScriptableInstance")); break;
    case NPPVpluginScriptableIID:           dprintf(("variable=NPPVpluginScriptableIID")); break;
    case NPPVjavascriptPushCallerBool:      dprintf(("variable=NPPVjavascriptPushCallerBool")); break;
    case NPPVpluginKeepLibraryInMemory:     dprintf(("variable=NPPVpluginKeepLibraryInMemory")); break;
    }

    //@todo TEXT: NPPVpluginNameString and NPPVpluginDescriptionString
    if (variable <= NPPVpluginKeepLibraryInMemory)
    {
        NP4XUP_ENTER_ODIN(FALSE);
        rc = pWrapper->w32.pfnGetValueUPP(NP4XUP_W32_INSTANCE(), variable, value);
        NP4XUP_LEAVE_ODIN(FALSE);
        if (!rc)
        {
            switch (variable)
            {
            case NPPVpluginDescriptionString:
            case NPPVpluginNameString:
                DPRINTF_STR((char*)value);
                break;
            case NPPVpluginScriptableIID:
                {
                    struct nsID *pnsID = *(struct nsID **)value;
                    DPRINTF_NSID(*pnsID);
                    break;
                }
            case NPPVpluginScriptableInstance:
                {
                    if (VALID_PTR(value))
                    {
                        nsresult rc2 = 0x80000001;
                        struct nsID *pnsID = NULL;
                        dprintf(("%s: *(void**)value=%p", szFunction, *(void**)value));
                        NP4XUP_ENTER_ODIN(FALSE);
                        NPError rc = pWrapper->w32.pfnGetValueUPP(NP4XUP_W32_INSTANCE(), NPPVpluginScriptableIID, (void*)&pnsID);
                        NP4XUP_LEAVE_ODIN(FALSE);
                        if (!rc && VALID_PTR(pnsID))
                        {
                            DPRINTF_NSID(*pnsID);
                            rc2 = upCreateWrapper((void**)value, *pnsID, NS_OK);
                        }

                        /* failed? */
                        if (rc2)
                        {
                            *(void**)value = 0;
                            rc = NPERR_GENERIC_ERROR;
                        }
                        /** @todo: aren't we leaking memory here. Don't care right now... */
                    }
                    break;
                }
            case NPPVpluginWindowBool:
            case NPPVpluginTransparentBool:
                if (VALID_PTR(value))
                {
                    dprintf(("%s: *value=%s", szFunction, *(PRBool*)value ? "true" : "false"));
                    /* Mozilla doesn't support this. */
                    if (variable == NPPVpluginWindowBool && !*(PRBool*)value)
                    {
                        *(PRBool*)value = TRUE;
                        dprintf(("%s: OS/2 Mozilla doesn't yet support windowless plugins, so we return true!!", szFunction));
                    }
                    if (variable == NPPVpluginTransparentBool && *(PRBool*)value)
                    {
                        *(PRBool*)value = FALSE;
                        dprintf(("%s: OS/2 Mozilla doesn't yet support windowless plugins, so we return false!!", szFunction));
                    }
                }
                break;
            case NPPVjavaClass:
            case NPPVpluginWindowSize:
            case NPPVpluginTimerInterval:
            case NPPVjavascriptPushCallerBool:
            case NPPVpluginKeepLibraryInMemory:
            default:
                if (VALID_PTR(value))
                    dprintf(("%s: *(void**)value=%p", szFunction, *(void**)value));
            }
        }
    } else if (variable == 15) /* check for NPPVpluginScriptableNPObject */
    {
#if 1
        /* we dont support any scriptable plugin objects atm */
        if (value) *(void**)value = NULL;
        rc = NPERR_GENERIC_ERROR;
#else
        InstanceData* instanceData = instance->pdata;
        NPObject* object = instanceData->scriptableObject;
        NP4XUP_ENTER_ODIN(FALSE);
        rc = pWrapper->w32.pfnGetValueUPP(NP4XUP_W32_INSTANCE(), variable, value);
        NP4XUP_LEAVE_ODIN(FALSE);
#endif
    }
    dprintf(("%s: leave rc=%p", szFunction, rc));
    return rc;
}

NPError NP_LOADDS np4xUp_SetValue(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPNVariable variable, void *value)
{
    static const char szFunction[] = "np4xUp_SetValue";
    dprintf(("%s: enter - pWrapper=%p instance=%p variable=%d value=%p",
             szFunction, pWrapper, instance, variable, value));
//@todo TEXT: NPPVpluginNameString and NPPVpluginDescriptionString ?
    NP4XUP_INSTANCE(FALSE);

    switch (variable)
    {
        case NPNVxDisplay:
            dprintf(("%s: NPNVxDisplay", szFunction));
            if (VALID_PTR(value))
                dprintf(("%s: *value=%#x", szFunction, *(void**)value));
            break;
        case NPNVxtAppContext:
            dprintf(("%s: NPNVxtAppContext", szFunction));
            if (VALID_PTR(value))
                dprintf(("%s: *value=%#x", szFunction, *(void**)value));
            break;
        case NPNVnetscapeWindow:
            dprintf(("%s: NPNVnetscapeWindow", szFunction));
            if (VALID_PTR(value))
                dprintf(("%s: *value=%#x", szFunction, *(void**)value));
            DebugInt3();
            //@todo wrapper!!!!
            break;
        case NPNVjavascriptEnabledBool:
            dprintf(("%s: NPNVjavascriptEnabledBool *value=%s", szFunction,
                     VALID_PTR(value) ? *((PRBool*)value) ? "true" : "false" : "invalid"));
            break;
        case NPNVasdEnabledBool:
            dprintf(("%s: NPNVasdEnabledBool *value=%s", szFunction,
                     VALID_PTR(value) ? *((PRBool*)value) ? "true" : "false" : "invalid"));
            break;
        case NPNVisOfflineBool:
            dprintf(("%s: NPNVisOfflineBool *value=%s", szFunction,
                     VALID_PTR(value) ? *((PRBool*)value) ? "true" : "false" : "invalid"));
            break;
        case NPNVserviceManager:
            dprintf(("%s: NPNVserviceManager", szFunction));
            if (VALID_PTR(value))
                dprintf(("%s: *value=%#x", szFunction, *(void**)value));
            break;
        case NPNVDOMElement:
            dprintf(("%s: NPNVDOMElement", szFunction));
            if (VALID_PTR(value))
                dprintf(("%s: *value=%#x", szFunction, *(void**)value));
            break;
        case NPNVDOMWindow:
            dprintf(("%s: NPNVDOMWindow", szFunction));
            if (VALID_PTR(value))
                dprintf(("%s: *value=%#x", szFunction, *(void**)value));
            break;
        default:
            dprintf(("%s: Unknown variable number %d", szFunction, variable));
            break;
    }

    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = pWrapper->w32.pfnSetValueUPP(NP4XUP_W32_INSTANCE(), variable, value);
    NP4XUP_LEAVE_ODIN(FALSE);
    if (!rc && VALID_PTR(value))
        dprintf(("%s: *(void**)value=%p", szFunction, *(void**)value));

    dprintf(("%s: leave rc=%p", szFunction, rc));
    return rc;
}



//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// DOWN wrappers (stuff that is to the plugin)
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//


/* This is not a callback, but something most plugins implememnts somehow, remove it! */
void    NPW32CALLBACK np4xDown_Version(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, int* plugin_major, int* plugin_minor,
                                       int* netscape_major, int* netscape_minor)
{
    static const char szFunction[] = "np4xDown_Version";
    dprintf(("%s: enter - pWrapper=%p plugin_major=%p plugin_minor=%p netscape_major=%p netscape_minor=%p",
             szFunction, pWrapper, plugin_major, plugin_minor, netscape_major, netscape_minor));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    ReleaseInt3(0x44440004,0x44440004,0x44440004);
    //pWrapper->pNative->??(plugin_major, plugin_minor, netscape_major, netscape_minor);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave", szFunction));
    return;
}


NPError NPW32CALLBACK np4xDown_GetURLNotify(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, const char* url, const char* target, void* notifyData)
{
    static const char szFunction[] = "np4xDown_GetURLNotify";
    dprintf(("%s: enter - pWrapper=%p instance%p url=%p target=%p notifyData=%p",
             szFunction, pWrapper, instance, url, target, notifyData));
    DPRINTF_STR(url);
    DPRINTF_STR(target);
    //@todo TEXT: url and target needs conversion.
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc = pWrapper->pNative->geturlnotify(NP4XDOWN_NS_INSTANCE(), url, target, notifyData);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%p", szFunction, rc));
    return rc;
}


NPError NPW32CALLBACK np4xDown_GetURL(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, const char* url, const char* target)
{
    static const char szFunction[] = "np4xDown_GetURL";
    dprintf(("%s: enter - pWrapper=%p instance%p url=%p target=%p",
             szFunction, pWrapper, instance, url, target));
    DPRINTF_STR(url);
    DPRINTF_STR(target);
    //@todo TEXT: url and target needs conversion.
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc = pWrapper->pNative->geturl(NP4XDOWN_NS_INSTANCE(), url, target);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%p", szFunction, rc));
    return rc;
}


NPError NPW32CALLBACK np4xDown_PostURLNotify(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, const char* url, const char* target, uint32 len,
                                             const char* buf, NPBool file, void* notifyData)
{
    static const char szFunction[] = "np4xDown_PostURLNotify";
    dprintf(("%s: enter - pWrapper=%p instance%p url=%p target=%p len=%d buf=%p file=%d notifyData=%p",
             szFunction, pWrapper, instance, url, target, len, buf, file, notifyData));
    DPRINTF_STR(url);
    DPRINTF_STR(target);
    //@todo TEXT: url and target needs conversion.
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc = pWrapper->pNative->posturlnotify(NP4XDOWN_NS_INSTANCE(), url, target, len, buf, file, notifyData);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%p", szFunction, rc));
    return rc;
}


NPError NPW32CALLBACK np4xDown_PostURL(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, const char* url,
                                       const char* target, uint32 len,
                                       const char* buf, NPBool file)
{
    static const char szFunction[] = "np4xDown_PostURL";
    dprintf(("%s: enter - pWrapper=%p instance%p url=%p target=%p len=%d buf=%p file=%d",
             szFunction, pWrapper, instance, url, target, len, buf, file));
    DPRINTF_STR(url);
    DPRINTF_STR(target);
    //@todo TEXT: url and target needs conversion.
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc = pWrapper->pNative->posturl(NP4XDOWN_NS_INSTANCE(), url, target, len, buf, file);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%p", szFunction, rc));
    return rc;
}


NPError NPW32CALLBACK np4xDown_RequestRead(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPStream* stream, NPByteRange* rangeList)
{
    static const char szFunction[] = "np4xDown_RequestRead";
    dprintf(("%s: enter - pWrapper=%p stream=%p rangeList=%p",
             szFunction, pWrapper, stream, rangeList));
    DPRINTF_STREAM(stream);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc = pWrapper->pNative->requestread(stream, rangeList);

    DPRINTF_STREAM(stream);
    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%p", szFunction, rc));
    return rc;
}


NPError NPW32CALLBACK np4xDown_NewStream(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPMIMEType type,
                                         const char* target, NPStream** stream)
{
    static const char szFunction[] = "np4xDown_NewStream";
    dprintf(("%s: enter - pWrapper=%p instance=%p type=%p target=%p stream=%p",
             szFunction, pWrapper, instance, type, target, stream));
    DPRINTF_STR(type);
    DPRINTF_STR(target);
    //@todo TEXT: target needs conversion.
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc = pWrapper->pNative->newstream(NP4XDOWN_NS_INSTANCE(), type, target, stream);
    if (!rc && VALID_PTR(*stream))
    {
        dprintf(("%s: *stream=%p", szFunction, *stream));
        DPRINTF_STREAM(*stream);
    }

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%p", szFunction, rc));
    return rc;
}


int32   NPW32CALLBACK np4xDown_Write(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPStream* stream, int32 len, void* buffer)
{
    static const char szFunction[] = "np4xDown_NewStream";
    dprintf(("%s: enter - pWrapper=%p instance=%p stream=%p len=%d buffer=%p",
             szFunction, pWrapper, instance, stream, len, buffer));
    DPRINTF_STREAM(stream);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    int32 rc = pWrapper->pNative->write(NP4XDOWN_NS_INSTANCE(), stream, len, buffer);

    NP4XDOWN_ENTER_ODIN(FALSE);
    DPRINTF_STREAM(stream);
    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


NPError NPW32CALLBACK np4xDown_DestroyStream(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPStream* stream, NPReason reason)
{
    static const char szFunction[] = "np4xDown_DestroyStream";
    dprintf(("%s: enter - pWrapper=%p instance=%p stream=%p reason=%d",
             szFunction, pWrapper, instance, stream, reason));
    DPRINTF_STREAM(stream);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc = pWrapper->pNative->destroystream(NP4XDOWN_NS_INSTANCE(), stream, reason);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


void    NPW32CALLBACK np4xDown_Status(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, const char* message)
{
    static const char szFunction[] = "np4xDown_Status";
    dprintf(("%s: enter - pWrapper=%p instance=%p message=%p",
             szFunction, pWrapper, instance, message));
    DPRINTF_STR(message);
    //@todo TEXT: attention to message
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pWrapper->pNative->status(NP4XDOWN_NS_INSTANCE(), message);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave", szFunction));
    return;
}


const char* NPW32CALLBACK np4xDown_UserAgent(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance)
{
    static const char szFunction[] = "np4xDown_UserAgent";
    dprintf(("%s: enter - pWrapper=%p instance=%p",
             szFunction, pWrapper, instance));
    NP4XDOWN_INSTANCE(TRUE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    const char * pszRc = pWrapper->pNative->uagent(NP4XDOWN_NS_INSTANCE());
    DPRINTF_STR(pszRc);

    dprintf(("%s: leave rc=%p", szFunction, pszRc));
    NP4XDOWN_ENTER_ODIN(FALSE);
    return pszRc;
}


void*   NPW32CALLBACK np4xDown_MemAlloc(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, uint32 size)
{
    static const char szFunction[] = "np4xDown_MemAlloc";
    dprintf(("%s: enter - pWrapper=%p size=%d",
             szFunction, pWrapper, size));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    void* pvRc = pWrapper->pNative->memalloc(size);

    dprintf(("%s: leave pvRc=%p", szFunction, pvRc));
    NP4XDOWN_ENTER_ODIN(FALSE);
    return pvRc;
}


void    NPW32CALLBACK np4xDown_MemFree(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, void* ptr)
{
    static const char szFunction[] = "np4xDown_MemFree";
    dprintf(("%s: enter - pWrapper=%p ptr=%p",
             szFunction, pWrapper, ptr));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pWrapper->pNative->memfree(ptr);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave", szFunction));
    return;
}


uint32  NPW32CALLBACK np4xDown_MemFlush(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, uint32 size)
{
    static const char szFunction[] = "np4xDown_MemFlush";
    dprintf(("%s: enter - pWrapper=%p size=%d",
             szFunction, pWrapper, size));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    uint32 rc = pWrapper->pNative->memflush(size);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


void    NPW32CALLBACK np4xDown_ReloadPlugins(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPBool reloadPages)
{
    static const char szFunction[] = "np4xDown_ReloadPlugins";
    dprintf(("%s: enter - pWrapper=%p reloadPages=%d",
             szFunction, pWrapper, reloadPages));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pWrapper->pNative->reloadplugins(reloadPages);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave", szFunction));
    return;
}


JRIEnv* NPW32CALLBACK np4xDown_GetJavaEnv(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller)
{
    static const char szFunction[] = "np4xDown_GetJavaEnv";
    dprintf(("%s: enter - pWrapper=%p", szFunction, pWrapper));
    NP4XDOWN_LEAVE_ODIN(FALSE);

  /*  ReleaseInt3(0x44440005,0x44440005,0x44440005); */
    JRIEnv * envRc = pWrapper->pNative->getJavaEnv();

    if (VALID_PTR(envRc))
    {
        JRIEnv *pvWrapped = (JRIEnv *)NPJNICreateDownWrapper(0, NPJS_TYPE_JRIENV_DOWN, envRc);
        if (pvWrapped)
            dprintf(("%s: Successfully created wrapper, %#p, for JRIEnv %#p", szFunction, pvWrapped, envRc));
        else
        {
            dprintf(("%s: failed to make wrapper for JRIEnv %#p", szFunction, envRc));
            DebugInt3();
        }
        envRc = pvWrapped;
    }

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave envRc=%p", szFunction, envRc));
    return envRc;
}


jref    NPW32CALLBACK np4xDown_GetJavaPeer(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance)
{
    static const char szFunction[] = "np4xDown_GetJavaPeer";
    dprintf(("%s: enter - pWrapper=%p instance=%p", szFunction, pWrapper, instance));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    jref rc = pWrapper->pNative->getJavaPeer(NP4XDOWN_NS_INSTANCE());

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%p", szFunction, rc));
    return rc;
}



NPError NPW32CALLBACK np4xDown_GetValue(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPNVariable variable, void *value)
{
    static const char szFunction[] = "np4xDown_GetValue";
    NPError rc = 1;
    dprintf(("%s: enter - pWrapper=%p instance=%p variable=%d value=%p",
             szFunction, pWrapper, instance, variable, value));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    switch (variable)
    {
        case NPNVxDisplay:              dprintf(("%s: NPNVxDisplay", szFunction)); break;
        case NPNVxtAppContext:          dprintf(("%s: NPNVxtAppContext", szFunction)); break;
        case NPNVnetscapeWindow:        dprintf(("%s: NPNVnetscapeWindow", szFunction)); break;
        case NPNVjavascriptEnabledBool: dprintf(("%s: NPNVjavascriptEnabledBool", szFunction)); break;
        case NPNVasdEnabledBool:        dprintf(("%s: NPNVasdEnabledBool", szFunction)); break;
        case NPNVisOfflineBool:         dprintf(("%s: NPNVisOfflineBool", szFunction)); break;
        default:
           dprintf(("%s: Unknown variable %d", szFunction, variable));
           break;
    }

    /* Win32 plugin crashes if operates value == 15 */
    if (variable <= NPNVisOfflineBool)
    {
        rc = pWrapper->pNative->getvalue(NP4XDOWN_NS_INSTANCE(), variable, value);

        if (!rc && VALID_PTR(value))
        {
            switch (variable)
            {
            case NPNVxDisplay:
            case NPNVxtAppContext:
                /* not implemented by OS/2 and Win32 I believe. */
                dprintf(("%s: *value=%#08x", szFunction, *((void**)value)));
                break;
            case NPNVnetscapeWindow:
                dprintf(("%s: *value=%#08x", szFunction, *(PHWND)value));
                if (pInst)
                    pInst->hwndOS2 = *(PHWND)value;
                *((PHWND)value) = npWinDownNetscapeWindow(*(PHWND)value);
                dprintf(("%s: wrapped *value=%#08x", szFunction, *(PHWND)value));
                if (pInst)
                    pInst->hwndOdin = *(PHWND)value;
                break;

            case NPNVjavascriptEnabledBool:
            case NPNVasdEnabledBool:
            case NPNVisOfflineBool:
                dprintf(("%s: *value=%s", szFunction, *((PRBool*)value) ? "true" : "false"));
                break;
            default:
                dprintf(("%s: unknown id *value=%#08x", szFunction, *((void**)value)));
                break;
            }
        }
    }
#if 0
    else if (variable == 15) /* check for private mode */
    {
        if (value) *(PRBool*)value = FALSE;
        rc = 0;
    }
#endif
    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


NPError NPW32CALLBACK np4xDown_SetValue(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPPVariable variable, void *value)
{
    static const char szFunction[] = "np4xDown_SetValue";
    dprintf(("%s: enter - pWrapper=%p instance=%p variable=%d value=%p",
             szFunction, pWrapper, instance, variable, value));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);
    PRBool fWindowLessReject = FALSE;
    switch (variable)
    {
        case NPPVpluginNameString:
            dprintf(("%s: NPPVpluginNameString", szFunction));
            DPRINTF_STR((const char*)value);
            break;
        case NPPVpluginDescriptionString:
            dprintf(("%s: NPPVpluginDescriptionString", szFunction));
            DPRINTF_STR((const char*)value);
            break;
        case NPPVpluginWindowBool:
            dprintf(("%s: NPPVpluginWindowBool value=%s", szFunction, value ? "true" : "false"));
            if (!(PRBool)value)
            {
                dprintf(("%s: OS/2 Mozilla doesn't yet support windowless plugins, so we set it to true!!", szFunction));
                value = (void*)TRUE;
                fWindowLessReject = TRUE;
            }
            break;
        case NPPVpluginTransparentBool:
            dprintf(("%s: NPPVpluginTransparentBool value=%s", szFunction, value ? "true" : "false"));
            if ((PRBool)value)
            {
                dprintf(("%s: OS/2 Mozilla doesn't yet support windowless plugins, so we set it to false!!", szFunction));
                value = (void*)FALSE;
                fWindowLessReject = TRUE;
            }
            break;
        case NPPVjavaClass: /* Not implemented in Mozilla 1.0 */
            dprintf(("%s: NPPVjavaClass", szFunction));
            break;
        case NPPVpluginWindowSize:
            dprintf(("%s: NPPVpluginWindowSize", szFunction));
            break;
        case NPPVpluginTimerInterval:
            dprintf(("%s: NPPVpluginTimerInterval", szFunction));
            break;
        case NPPVpluginScriptableInstance:  dprintf(("%s: NPPVpluginScriptableInstance", szFunction)); break;
        case NPPVpluginScriptableIID:       dprintf(("%s: NPPVpluginScriptableIID", szFunction)); break;
        case NPPVjavascriptPushCallerBool:
            dprintf(("%s: NPPVjavascriptPushCallerBool", szFunction));
            break;
        case NPPVpluginKeepLibraryInMemory:
            dprintf(("%s: NPPVpluginKeepLibraryInMemory", szFunction));
            break;

        default:
            dprintf(("%s: Invalid variable number %d!!!", szFunction, variable));
            break;
    }

    NPError rc = pWrapper->pNative->setvalue(NP4XDOWN_NS_INSTANCE(), variable, value);

    if (fWindowLessReject)
    {
        dprintf(("%s: OS/2 Mozilla doesn't yet support windowless plugins, we'll return failure just to be safe...", szFunction));
        rc = NPERR_INVALID_PARAM;
    }

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


void    NPW32CALLBACK np4xDown_InvalidateRect(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPRect *invalidRect)
{
    static const char szFunction[] = "np4xDown_InvalidateRect";
    dprintf(("%s: enter - pWrapper=%p instance=%p variable=%d invalidRect=%p",
             szFunction, pWrapper, instance, invalidRect));
    if (VALID_PTR(invalidRect))
        dprintf(("%s: (%d,%d)(%d,%d)", szFunction, invalidRect->top, invalidRect->left, invalidRect->bottom, invalidRect->right));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

#if 0
    /** @todo instance -> window association.
     * We're halfways f**ked here since we can't easily convert the NPRect
     * from Odin to OS/2 without knowing the window height.
     * bird 2003-09-17: Let's hope this is the same stuff on Win32 as on OS/2.
     */
    ReleaseInt3(0x44440006,0x44440006,0x44440006);
#endif

    pWrapper->pNative->invalidaterect(NP4XDOWN_NS_INSTANCE(), invalidRect);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave", szFunction));
    return;
}


void    NPW32CALLBACK np4xDown_InvalidateRegion(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPRegion invalidRegion)
{
    static const char szFunction[] = "np4xDown_InvalidateRegion";
    dprintf(("%s: enter - pWrapper=%p instance=%p invalidRegion=%p (HRGN)",
             szFunction, pWrapper, instance, invalidRegion));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    /** @todo Odin HRGN to OS/2 HRGN. */
    ReleaseInt3(0x44440007,0x44440007,0x44440007);

    pWrapper->pNative->invalidateregion(NP4XDOWN_NS_INSTANCE(), invalidRegion);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave", szFunction));
    return;
}


void    NPW32CALLBACK np4xDown_ForceRedraw(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance)
{
    static const char szFunction[] = "np4xDown_ForceRedraw";
    dprintf(("%s: enter - pWrapper=%p instance=%p",
             szFunction, pWrapper, instance));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pWrapper->pNative->forceredraw(NP4XDOWN_NS_INSTANCE());

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave", szFunction));
    return;
}



//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// Generic wrapping stuff.
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//


NPError             npGenericNP_GetEntryPoints(NPPluginFuncs* pCallbacks, PNPODINWRAPPER pPlugin)
{
    static const char szFunction[] = "npGenericNP_GetEntryPoints";
    dprintf(("%s: enter - pCallbacks=%p pPlugin=%p", szFunction, pCallbacks, pPlugin));
    DPRINTF_STR(pPlugin->szPluginName);
    NPError rc;

    /*
     * Lazy Init.
     */
    if (    !pPlugin->hmodPlugin
        &&  !npGenericLazyInit(pPlugin))
    {
        dprintf(("%s: npGenericLazyInit() failed returning NPERR_INVALID_PLUGIN_ERROR", szFunction));
        NPXP_ASSERT_OS2FS();
        return NPERR_INVALID_PLUGIN_ERROR;
    }

    /*
     * Is the entrypoint present?
     */
    if (!pPlugin->pfnW32NP_GetEntryPoints)
    {
        dprintf(("%s: pfnW32NP_GetEntryPoints is NULL returning NPERR_INVALID_PLUGIN_ERROR", szFunction));
        NPXP_ASSERT_OS2FS();
        return NPERR_INVALID_PLUGIN_ERROR;
    }

    /*
     * Ok. Here we must create an blank wrapper for this callback table.
     */
    PNPLUGINFUNCSWRAPPER pWrapper = (PNPLUGINFUNCSWRAPPER)malloc(sizeof(NPLUGINFUNCSWRAPPER));
    if (!pWrapper)
    {
        dprintf(("%s: out of memory! Can't allocate wrapper!", szFunction));
        NPXP_ASSERT_OS2FS();
        return NPERR_OUT_OF_MEMORY_ERROR;
    }

    memset(pWrapper, 0, sizeof(*pWrapper));
    pWrapper->pNative = pCallbacks;
    memcpy(&pWrapper->w32, pCallbacks, sizeof(*pCallbacks));
    dprintf(("%s: pCallback->version=%d pCallback->size=%d", szFunction, pCallbacks->version, pCallbacks->size));
    for (int iPadding = 0; iPadding < sizeof(pWrapper->auPadding2) / sizeof(pWrapper->auPadding2[0]); iPadding++)
        pWrapper->auPadding2[iPadding] = 0xbadd0000 | iPadding;

    /*
     * Call Real worker in Odin context.
     */
    unsigned ExceptionRegRec[2] = {0,0};
    USHORT selFSOld = pfnODIN_ThreadEnterOdinContext(&ExceptionRegRec[0], TRUE);
    rc = pPlugin->pfnW32NP_GetEntryPoints(&pWrapper->w32);
    pfnODIN_ThreadLeaveOdinContext(&ExceptionRegRec[0], selFSOld);
    ExceptionRegRec[0] = ExceptionRegRec[1] = 0;
    if (!rc)
    {
        pCallbacks->javaClass = pWrapper->w32.javaClass;

        /*
         * Now we must create the wrapper stubs and fill it in. (this sucks)
         * (I don't care using offsets of the pfns here, that just make it totaly unreable.)
         * @todo put this into a function use by both wrapper creators and use fixed struct offsets
         *       instead of creating the aStub on the stack.
         */
        struct GenerateStub
        {
            /** Pointer to the wrapper function. */
            void *  pfnWrapper;
            /** Pointer to the wrapped function entry. */
            void ** ppfnReal;
            /** Where to put the stub pointer. */
            void ** ppfn;
        }   aStubs[] =
        {
            {(void*)np4xUp_New,             (void**)&pWrapper->w32.pfnNewUPP,           (void**)&pCallbacks->newp },
            {(void*)np4xUp_Destroy,         (void**)&pWrapper->w32.pfnDestroyUPP,       (void**)&pCallbacks->destroy },
            {(void*)np4xUp_SetWindow,       (void**)&pWrapper->w32.pfnSetWindowUPP,     (void**)&pCallbacks->setwindow },
            {(void*)np4xUp_NewStream,       (void**)&pWrapper->w32.pfnNewStreamUPP,     (void**)&pCallbacks->newstream },
            {(void*)np4xUp_DestroyStream,   (void**)&pWrapper->w32.pfnDestroyStreamUPP, (void**)&pCallbacks->destroystream },
            {(void*)np4xUp_StreamAsFile,    (void**)&pWrapper->w32.pfnStreamAsFileUPP,  (void**)&pCallbacks->asfile },
            {(void*)np4xUp_WriteReady,      (void**)&pWrapper->w32.pfnWriteReadyUPP,    (void**)&pCallbacks->writeready },
            {(void*)np4xUp_Write,           (void**)&pWrapper->w32.pfnWriteUPP,         (void**)&pCallbacks->write },
            {(void*)np4xUp_Print,           (void**)&pWrapper->w32.pfnPrintUPP,         (void**)&pCallbacks->print },
            {(void*)np4xUp_HandleEvent,     (void**)&pWrapper->w32.pfnHandleEventUPP,   (void**)&pCallbacks->event },
            {(void*)np4xUp_URLNotify,       (void**)&pWrapper->w32.pfnURLNotifyUPP,     (void**)&pCallbacks->urlnotify },
            {(void*)np4xUp_GetValue,        (void**)&pWrapper->w32.pfnGetValueUPP,      (void**)&pCallbacks->getvalue },
            {(void*)np4xUp_SetValue,        (void**)&pWrapper->w32.pfnSetValueUPP,      (void**)&pCallbacks->setvalue },
        };
        for (int i = 0; i < sizeof(aStubs) / sizeof(aStubs[0]); i++)
        {
            memset(pWrapper->aStubs[i].achMagic, 0xcc, sizeof(pWrapper->aStubs[i].achMagic));
            pWrapper->aStubs[i].chPush      = 0x68;
            pWrapper->aStubs[i].pvImm32bit  = pWrapper;
            pWrapper->aStubs[i].chCall      = 0xe8;
            pWrapper->aStubs[i].offRel32bit = ((char*)aStubs[i].pfnWrapper - (char*)&pWrapper->aStubs[i].offRel32bit - 4);
            pWrapper->aStubs[i].chPopEcx    = 0x59;
            pWrapper->aStubs[i].chRet       = 0xc3;
            *aStubs[i].ppfn = *aStubs[i].ppfnReal ? (void*)&pWrapper->aStubs[i] : NULL;
            //dprintf(("%s: Win32 NP func pointer: %08X", szFunction, *(ULONG*)(*aStubs[i].ppfn)));
        }
        memset(&pWrapper->aStubs[i], 0xcc,
               (char*)&pWrapper->aStubs[sizeof(pWrapper->aStubs) / sizeof(pWrapper->aStubs[0])] - (char*)&pWrapper->aStubs[i]); /* nice, eh? */

        /** @todo Insert the wrapper into a list. */

        dprintf(("%s: Successfully created wrapper stubs and all.", szFunction));
    }
    else
    {
        /*
         * It failed, complain and do cleanup!
         */
        dprintf(("%s: NP_GetEntryPoints failed with rc=%d", szFunction, rc));
        memset(pWrapper, 0, sizeof(*pWrapper)); /* paranoia */
        free(pWrapper);
    }

    dprintf(("%s: leave rc=%x", szFunction, rc));
    NPXP_ASSERT_OS2FS();
    return rc;
}



NPError             npGenericNP_Initialize(NPNetscapeFuncs * pFuncs, PNPODINWRAPPER pPlugin)
{
    static const char szFunction[] = "npGenericNP_Initialize";
    dprintf(("%s: enter - pFuncs=%p pPlugin=%p", szFunction, pFuncs, pPlugin));
    DPRINTF_STR(pPlugin->szPluginName);
    NPError rc;

    /*
     * Lazy Init.
     */
    if (    !pPlugin->hmodPlugin
        &&  !npGenericLazyInit(pPlugin))
    {
        dprintf(("%s: npGenericLazyInit() failed returning NPERR_INVALID_PLUGIN_ERROR", szFunction));
        NPXP_ASSERT_OS2FS();
        return NPERR_INVALID_PLUGIN_ERROR;
    }

    /*
     * Is the entrypoint present?
     */
    if (!pPlugin->pfnW32NP_Initialize)
    {
        dprintf(("%s: pfnW32NP_Initialize is NULL returning NPERR_INVALID_PLUGIN_ERROR", szFunction));
        NPXP_ASSERT_OS2FS();
        return NPERR_INVALID_PLUGIN_ERROR;
    }

    /*
     * Create wrapper for the function table.
     *      Allocate.
     *      Initiate it.
     *      Create stubs.
     * @todo put this into a function use by both wrapper creators and use fixed struct offsets
     *       instead of creating the aStub on the stack.
     */
    PNETSCAPEFUNCSWRAPPER pWrapper = (PNETSCAPEFUNCSWRAPPER)malloc(sizeof(NETSCAPEFUNCSWRAPPER));
    if (!pWrapper)
    {
        dprintf(("%s: out of memory! Can't allocate wrapper!", szFunction));
        NPXP_ASSERT_OS2FS();
        return NPERR_OUT_OF_MEMORY_ERROR;
    }

    memset(pWrapper, 0, sizeof(*pWrapper));
    dprintf(("%s: pFuncs->version=%d pFuncs->size=%d", szFunction, pFuncs->version, pFuncs->size));
    for (int iPadding = 0; iPadding < sizeof(pWrapper->auPadding2) / sizeof(pWrapper->auPadding2[0]); iPadding++)
        pWrapper->auPadding2[iPadding] = 0xbbad0000 | iPadding;
    pWrapper->pNative = pFuncs;
   pWrapper->w32.version = pFuncs->version;
    pWrapper->w32.size = pFuncs->size;

    /* (I don't care using offsets of the pfns here, that just make it totaly unreable.) */
    struct GenerateStub
    {
        /** Pointer to the wrapper function. */
        void *  pfnWrapper;
        /** Pointer to the wrapped function entry. */
        void ** ppfnReal;
        /** Where to put the stub pointer. */
        void ** ppfn;
    }   aStubs[] =
    {
        {(void*)np4xDown_GetURL,            (void**)&pFuncs->geturl,            (void**)&pWrapper->w32.pfnGetURLUPP },
        {(void*)np4xDown_PostURL,           (void**)&pFuncs->posturl,           (void**)&pWrapper->w32.pfnPostURLUPP },
        {(void*)np4xDown_RequestRead,       (void**)&pFuncs->requestread,       (void**)&pWrapper->w32.pfnRequestReadUPP },
        {(void*)np4xDown_NewStream,         (void**)&pFuncs->newstream,         (void**)&pWrapper->w32.pfnNewStreamUPP },
        {(void*)np4xDown_Write,             (void**)&pFuncs->write,             (void**)&pWrapper->w32.pfnWriteUPP },
        {(void*)np4xDown_DestroyStream,     (void**)&pFuncs->destroystream,     (void**)&pWrapper->w32.pfnDestroyStreamUPP },
        {(void*)np4xDown_Status,            (void**)&pFuncs->status,            (void**)&pWrapper->w32.pfnStatusUPP },
        {(void*)np4xDown_UserAgent,         (void**)&pFuncs->uagent,            (void**)&pWrapper->w32.pfnUserAgentUPP },
        {(void*)np4xDown_MemAlloc,          (void**)&pFuncs->memalloc,          (void**)&pWrapper->w32.pfnMemAllocUPP },
        {(void*)np4xDown_MemFree,           (void**)&pFuncs->memfree,           (void**)&pWrapper->w32.pfnMemFreeUPP },
        {(void*)np4xDown_MemFlush,          (void**)&pFuncs->memflush,          (void**)&pWrapper->w32.pfnMemFlushUPP },
        {(void*)np4xDown_ReloadPlugins,     (void**)&pFuncs->reloadplugins,     (void**)&pWrapper->w32.pfnReloadPluginsUPP },
        {(void*)np4xDown_GetJavaEnv,        (void**)&pFuncs->getJavaEnv,        (void**)&pWrapper->w32.pfnGetJavaEnvUPP },
        {(void*)np4xDown_GetJavaPeer,       (void**)&pFuncs->getJavaPeer,       (void**)&pWrapper->w32.pfnGetJavaPeerUPP },
        {(void*)np4xDown_GetURLNotify,      (void**)&pFuncs->geturlnotify,      (void**)&pWrapper->w32.pfnGetURLNotifyUPP },
        {(void*)np4xDown_PostURLNotify,     (void**)&pFuncs->posturlnotify,     (void**)&pWrapper->w32.pfnPostURLNotifyUPP },
        {(void*)np4xDown_GetValue,          (void**)&pFuncs->getvalue,          (void**)&pWrapper->w32.pfnGetValueUPP },
        {(void*)np4xDown_SetValue,          (void**)&pFuncs->setvalue,          (void**)&pWrapper->w32.pfnSetValueUPP },
        {(void*)np4xDown_InvalidateRect,    (void**)&pFuncs->invalidaterect,    (void**)&pWrapper->w32.pfnInvalidateRectUPP },
        {(void*)np4xDown_InvalidateRegion,  (void**)&pFuncs->invalidateregion,  (void**)&pWrapper->w32.pfnInvalidateRegionUPP },
        {(void*)np4xDown_ForceRedraw,       (void**)&pFuncs->forceredraw,       (void**)&pWrapper->w32.pfnForceRedrawUPP },
    };
    for (int i = 0; i < sizeof(aStubs) / sizeof(aStubs[0]); i++)
    {
        pWrapper->aStubs[i].chPush      = 0x68;
        pWrapper->aStubs[i].pvImm32bit  = pWrapper;
        pWrapper->aStubs[i].chCall      = 0xe8;
        pWrapper->aStubs[i].offRel32bit = ((char*)aStubs[i].pfnWrapper - (char*)&pWrapper->aStubs[i].offRel32bit - 4);
        pWrapper->aStubs[i].chPopEcx    = 0x59;
        pWrapper->aStubs[i].chRet       = 0xc3;
        *aStubs[i].ppfn = *aStubs[i].ppfnReal ? (void*)&pWrapper->aStubs[i] : NULL;
        memset(pWrapper->aStubs[i].achMagic, 0xcc, sizeof(pWrapper->aStubs[i].achMagic));
    }
    memset(&pWrapper->aStubs[i], 0xcc,
           (char*)&pWrapper->aStubs[sizeof(pWrapper->aStubs) / sizeof(pWrapper->aStubs[0])] - (char*)&pWrapper->aStubs[i]); /* nice, eh? */


    /*
     * Call Real worker in Odin context.
     */
    unsigned ExceptionRegRec[2] = {0,0};
    USHORT selFSOld = pfnODIN_ThreadEnterOdinContext(&ExceptionRegRec[0], TRUE);
    rc = pPlugin->pfnW32NP_Initialize(&pWrapper->w32);
    pfnODIN_ThreadLeaveOdinContext(&ExceptionRegRec[0], selFSOld);
    ExceptionRegRec[0] = ExceptionRegRec[1] = 0;
    if (!rc)
    {
        /** @todo Insert the wrapper in some kind of list  */
        dprintf(("%s: NP_Initialize successful!", szFunction));
    }
    else
    {
        /*
         * It failed, cleanup the wrapper.
         */
        dprintf(("%s: NP_Initialize failed with rc=%x", szFunction, rc));
        memset(pWrapper, 0, sizeof(*pWrapper)); /* paranoid wie immer. */
        free(pWrapper);
    }

    dprintf(("%s: leave rc=%x", szFunction, rc));
    NPXP_ASSERT_OS2FS();
    return rc;
}


NPError             npGenericNP_Shutdown(PNPODINWRAPPER pPlugin)
{
    static const char szFunction[] = "npGenericNP_Shutdown";
    dprintf(("%s: enter - pPlugin=%p", szFunction, pPlugin));
    DPRINTF_STR(pPlugin->szPluginName);
    NPError rc;


    /*
     * Lazy Init.
     */
    if (    !pPlugin->hmodPlugin
        &&  !npGenericLazyInit(pPlugin))
    {
        dprintf(("%s: npGenericLazyInit() failed returning NPERR_INVALID_PLUGIN_ERROR", szFunction));
        NPXP_ASSERT_OS2FS();
        return NPERR_INVALID_PLUGIN_ERROR;
    }

    /*
     * Is the entrypoint present?
     */
    if (!pPlugin->pfnW32NP_Shutdown)
    {
        dprintf(("%s: pfnW32NP_Shutdown is NULL returning NPERR_INVALID_PLUGIN_ERROR", szFunction));
        NPXP_ASSERT_OS2FS();
        return NPERR_INVALID_PLUGIN_ERROR;
    }

    /*
     * Call Real worker in Odin context.
     */
    unsigned ExceptionRegRec[2] = {0,0};
    USHORT selFSOld = pfnODIN_ThreadEnterOdinContext(&ExceptionRegRec[0], TRUE);
    rc = pPlugin->pfnW32NP_Shutdown();
    pfnODIN_ThreadLeaveOdinContext(&ExceptionRegRec[0], selFSOld);
    ExceptionRegRec[0] = ExceptionRegRec[1] = 0;

    dprintf(("%s: leave rc=%x", szFunction, rc));
    NPXP_ASSERT_OS2FS();
    return rc;
}


/* Unix only? */
NPError             npGenericNP_GetValue(NPP future, NPPVariable variable, void *value, PNPODINWRAPPER pPlugin)
{
    static const char szFunction[] = "npGenericNP_GetMIMEDescription";
    dprintf(("%s: enter - future=%p variable=%d value=%p pPlugin=%p", szFunction, future, variable, value, pPlugin));
    DPRINTF_STR(pPlugin->szPluginName);
    NPError rc;

    /*
     * Lazy Init.
     */
    if (    !pPlugin->hmodPlugin
        &&  !npGenericLazyInit(pPlugin))
    {
        dprintf(("%s: npGenericLazyInit() failed returning NPERR_INVALID_PLUGIN_ERROR", szFunction));
        NPXP_ASSERT_OS2FS();
        return NPERR_INVALID_PLUGIN_ERROR;
    }

    /*
     * Is the entrypoint present?
     */
    if (!pPlugin->pfnW32NP_GetValue)
    {
        dprintf(("%s: pfnW32NP_GetValue is NULL returning NPERR_INVALID_PLUGIN_ERROR", szFunction));
        NPXP_ASSERT_OS2FS();
        return NPERR_INVALID_PLUGIN_ERROR;
    }

    /*
     * Call Real worker in Odin context.
     */
    unsigned ExceptionRegRec[2] = {0,0};
    USHORT selFSOld = pfnODIN_ThreadEnterOdinContext(&ExceptionRegRec[0], TRUE);
    rc = pPlugin->pfnW32NP_GetValue(future, variable, value);
    pfnODIN_ThreadLeaveOdinContext(&ExceptionRegRec[0], selFSOld);
    ExceptionRegRec[0] = ExceptionRegRec[1] = 0;

    dprintf(("%s: leave rc=%x", szFunction, rc));
    NPXP_ASSERT_OS2FS();
    return rc;
}


char *              npGenericNP_GetMIMEDescription(PNPODINWRAPPER pPlugin)
{
    static const char szFunction[] = "npGenericNP_GetMIMEDescription";
    dprintf(("%s: enter - pPlugin=%p", szFunction, pPlugin));
    DPRINTF_STR(pPlugin->szPluginName);
    char *pszRc;


    /*
     * Lazy Init.
     */
    if (    !pPlugin->hmodPlugin
        &&  !npGenericLazyInit(pPlugin))
    {
        dprintf(("%s: npGenericLazyInit() failed returning NULL", szFunction));
        NPXP_ASSERT_OS2FS();
        return NULL;
    }

    /*
     * Is the entrypoint present?
     */
    if (!pPlugin->pfnW32NP_GetMIMEDescription)
    {
        dprintf(("%s: pfnW32NP_GetMIMEDescription is NULL returning NULL", szFunction));
        NPXP_ASSERT_OS2FS();
        return NULL;
    }

    /*
     * Call Real worker in Odin context.
     */
    unsigned ExceptionRegRec[2] = {0,0};
    USHORT selFSOld = pfnODIN_ThreadEnterOdinContext(&ExceptionRegRec[0], TRUE);
    pszRc = pPlugin->pfnW32NP_GetMIMEDescription();
    pfnODIN_ThreadLeaveOdinContext(&ExceptionRegRec[0], selFSOld);
    ExceptionRegRec[0] = ExceptionRegRec[1] = 0;

    DPRINTF_STR(pszRc);
    dprintf(("%s: leave pszRc=%x", szFunction, pszRc));
    NPXP_ASSERT_OS2FS();
    return pszRc;
}

