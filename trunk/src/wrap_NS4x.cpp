/* $Id: wrap_NS4x.cpp,v 1.12 2004/03/10 15:36:41 bird Exp $
 *
 * Netscape v4.x Plugin interface.
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
/** safely dprintf a string. */
#define DPRINTF_STR(pszStr)  \
    do                                                                             \
    {                                                                              \
        if (VALID_PTR(pszStr))                                                     \
            dprintff("%s=%s", #pszStr, pszStr);                                    \
        else if (pszStr)                                                           \
            dprintff("%s=%p (illegal pointer)", #pszStr, pszStr);                  \
        else                                                                       \
            dprintff("%s=<NULL>", #pszStr);                                        \
    } while (0)

/** safely dprintf a string, if it's NULL it will be ignored. */
#define DPRINTF_STRNULL(pszStr)  \
    do                                                                             \
    {                                                                              \
        if (VALID_PTR(pszStr))                                                     \
            dprintff("%s=%s", #pszStr, pszStr);                                    \
        else if (pszStr)                                                           \
            dprintff("%s=%p (illegal pointer)", #pszStr, pszStr);                  \
    } while (0)

/** Print stream data */
#define DPRINTF_STREAM(pStream)                                                    \
    do                                                                             \
    {                                                                              \
        if (VALID_PTR(pStream))                                                    \
        {                                                                          \
            dprintff("%s: *stream: pdata=%p ndata=%p url=%p end=%d lastmodified=%x notifyData=%p", \
                     (pStream)->pdata, (pStream)->ndata,                           \
                     (pStream)->url, (pStream)->end, (pStream)->lastmodified,      \
                     (pStream)->notifyData);                                       \
            DPRINTF_STR((pStream)->url);                                           \
        }                                                                          \
    } while (0)


/** Debug DOS32TIB assertion. */
#ifdef DEBUG
#define NPXP_ASSERT_OS2FS()     \
        if (npGetFS() != (USHORT)(unsigned)&DOS32TIB)                               \
        {                                                                           \
            dprintff("fs is wrong (%x) !!!", npGetFS());                            \
            DebugInt3();                                                            \
        }
#else
#define NPXP_ASSERT_OS2FS()     do {} while (0)
#endif

/*
 * NPVariant32 to NPVariant wrapper macros
 */

/** Set up input NP32Variant to NPVariant conversion */
#define NP4XDOWN_BEGIN_IN_NPVARIANT(w32)                                            \
    NPVariant os2##w32;                                                             \
    const NPVariant *os2##w32##Ptr = NULL;                                          \
    if (w32) {                                                                      \
        os2##w32##Ptr = &os2##w32;                                                  \
        convertNPVariant(w32, &os2##w32);                                           \
    }

/** Get ptr to input NPVariant converted from NP32Variant */
#define NP4XDOWN_USE_IN_NPVARIANT(w32) os2##w32##Ptr

/** Finalize input NP32Variant to NPVariant conversion */
#define NP4XDOWN_END_IN_NPVARIANT(w32) do {} while (0)

/** Set up in/out NP32Variant to NPVariant conversion */
#define NP4XDOWN_BEGIN_OUT_NPVARIANT(w32)                                           \
    NPVariant os2##w32, *os2##w32##Ptr = NULL;                                      \
    if (w32) {                                                                      \
        os2##w32##Ptr = &os2##w32;                                                  \
        convertNPVariant(w32, &os2##w32);                                           \
    }

/** Get ptr to in/out NPVariant converted from NP32Variant */
#define NP4XDOWN_USE_OUT_NPVARIANT(w32) os2##w32##Ptr

/** Finalize in/out NP32Variant to NPVariant conversion */
#define NP4XDOWN_END_OUT_NPVARIANT(w32)                                             \
    if (w32)                                                                        \
        convertNPVariant(&os2##w32, w32);

/** Set up input array of NP32Variant to NPVariant conversion */
#define NP4XDOWN_BEGIN_IN_NPVARIANTS(w32, cnt)                                      \
    NPVariant *os2##w32##Ptr = NULL;                                                \
    if (w32) {                                                                      \
        os2##w32##Ptr = (NPVariant *)malloc(sizeof(NPVariant) * cnt);               \
        for (int i = 0; i < cnt; i++)                                               \
            convertNPVariant(&w32[i], &os2##w32##Ptr[i]);                           \
    }

/** Get ptr to input array of NPVariant converted from NP32Variant */
#define NP4XDOWN_USE_IN_NPVARIANTS(w32) (const NPVariant *)os2##w32##Ptr

/** Finalize input array NP32Variant to NPVariant conversion */
#define NP4XDOWN_END_IN_NPVARIANTS(w32)                                             \
    if (os2##w32##Ptr)                                                              \
        free(os2##w32##Ptr);

/*
 * NPVariant to NPVariant32 wrapper macros
 */

/** Set up input NPVariant to NP32Variant conversion */
#define NP4XUP_BEGIN_IN_NPVARIANT(os2)                                              \
    NP32Variant w32##os2;                                                           \
    const NP32Variant *w32##os2##Ptr = NULL;                                        \
    if (os2) {                                                                      \
        w32##os2##Ptr = &w32##os2;                                                  \
        convertNPVariant(os2, &w32##os2);                                           \
    }

/** Get ptr to input NP32Variant converted from NPVariant */
#define NP4XUP_USE_IN_NPVARIANT(os2) w32##os2##Ptr

/** Finalize input NPVariant to NP32Variant conversion */
#define NP4XUP_END_IN_NPVARIANT(os2) do {} while (0)

/** Set up in/out NPVariant to NP32Variant conversion */
#define NP4XUP_BEGIN_OUT_NPVARIANT(os2)                                             \
    NP32Variant w32##os2, *w32##os2##Ptr = NULL;                                    \
    if (os2) {                                                                      \
        w32##os2##Ptr = &w32##os2;                                                  \
        convertNPVariant(os2, &w32##os2);                                           \
    }

/** Get ptr to in/out NP32Variant converted from NPVariant */
#define NP4XUP_USE_OUT_NPVARIANT(os2) w32##os2##Ptr

/** Finalize in/out NPVariant to NP32Variant conversion */
#define NP4XUP_END_OUT_NPVARIANT(os2)                                               \
    if (os2)                                                                        \
        convertNPVariant(&w32##os2, os2);

/** Set up input array of NPVariant to NP32Variant conversion */
#define NP4XUP_BEGIN_IN_NPVARIANTS(os2, cnt)                                        \
    NP32Variant *w32##os2##Ptr = NULL;                                              \
    if (os2) {                                                                      \
        w32##os2##Ptr = (NP32Variant *)malloc(sizeof(NP32Variant) * cnt);           \
        for (int i = 0; i < cnt; i++)                                               \
            convertNPVariant(&os2[i], &w32##os2##Ptr[i]);                           \
    }

/** Get ptr to input array of NP32Variant converted from NPVariant */
#define NP4XUP_USE_IN_NPVARIANTS(os2) (const NP32Variant *)w32##os2##Ptr

/** Finalize input array NPVariant to NP32Variant conversion */
#define NP4XUP_END_IN_NPVARIANTS(os2)                                               \
    if (w32##os2##Ptr)                                                              \
        free(w32##os2##Ptr);

/*
 * Other stuff
 */

/** Get and validate the instance pointer */
#define NP4XUP_INSTANCE(fAllowNULL) \
    PluginInstance *pInst = (PluginInstance *)instance->pdata;                  \
    if (!VALID_PTR(pInst) || pInst->auMagic != PluginInstance::MAGIC)               \
    {                                                                               \
        if (!fAllowNULL || pInst)                                                   \
            dprintff("Invalid Instance Pointer %#x!!!\n", pInst);                   \
        pInst = NULL;                                                               \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        if (pInst->pOrgInstance != instance)                                        \
        {                                                                           \
            dprintff("Warning! pInst->pOrgInstance (%p) != instance (%p)!!!\n",     \
                     pInst->pOrgInstance, instance);                                \
            DebugInt3();                                                            \
            pInst->pOrgInstance = instance;                                         \
        }                                                                           \
        pInst->w32.ndata = pInst;                                                   \
    }                                                                               \
    dprintff("w32_instance=%p", pInst ? &pInst->w32 : NULL);


/** Get the 'correct' w32 instance pointer. */
#define NP4XUP_W32_INSTANCE() \
        pInst ? &pInst->w32 : instance

/** Get and validate the instance pointer */
#define NP4XDOWN_INSTANCE(fAllowNULL) \
    PluginInstance *pInst = NULL;                                               \
    if (VALID_PTR(instance))                                                        \
        pInst = (PluginInstance *)instance->ndata;                                  \
    if (!VALID_PTR(pInst) || pInst->auMagic != PluginInstance::MAGIC)               \
    {                                                                               \
        if (!fAllowNULL || pInst)                                                   \
            dprintff("Invalid Instance Pointer pInst=%p, instance=%p!!!\n",         \
                     pInst, instance);                                              \
        pInst = NULL;                                                               \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        if ((char*)instance - __offsetof(PluginInstance, w32) != (char*)pInst)     \
            dprintff("Bogus Instance Pointer pInst=%p, instance=%p!!!\n",           \
                     pInst, instance);                                              \
    }                                                                               \
    dprintff("os2_instance=%p", pInst ? pInst->pOrgInstance : NULL);

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
    ODINTHREADCTX ctx; \
    pfnODIN_ThreadContextSave(&ctx, OTCTXF_SAVE_FPU | OTCTXF_LOAD_FPU_ODIN32); \
    if (fDebug) DebugInt3()

/** Leave odin context and go back into the OS/2 netscape/mozilla context. */
#define NP4XUP_LEAVE_ODIN(fDebug) \
    if (fDebug) DebugInt3();  \
    pfnODIN_ThreadContextRestore(&ctx, OTCTXF_SAVE_FPU); \
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

/** Enter odin context from OS/2 netscape/mozilla class callback context. */
#define NP4XCLASS_SANITY_CHECK(retval) \
    if (npobj->_class != (NPClass *)&pInst->newClass) { \
        dprintff("ERROR: npobj->_class must be %p", &pInst->newClass); \
        return retval; \
    } do {} while (0)

/** Enter odin context from OS/2 netscape/mozilla class callback context. */
#define NP4XCLASS_ENTER_ODIN(fDebug) \
    npobj->_class = (NPClass *)pInst->pw32Class; \
    NP4XUP_ENTER_ODIN(fDebug)

/** Leave odin context and go back into the OS/2 netscape/mozilla class callbackcontext. */
#define NP4XCLASS_LEAVE_ODIN(fDebug) \
    NP4XUP_LEAVE_ODIN(fDebug); \
    npobj->_class = (NPClass *)&pInst->newClass

/** dprintf a nsID structure (reference to such). */
#define DPRINTF_NSID(refID)  \
    if (VALID_REF(refID))                                                                     \
        dprintff("%s={%08x,%04x,%04x,%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x} %s (%p)",   \
                 #refID, (refID).m0, (refID).m1, (refID).m2, (refID).m3[0], (refID).m3[1],   \
                 (refID).m3[2], (refID).m3[3], (refID).m3[4], (refID).m3[5], (refID).m3[6], (refID).m3[7], \
                 getIIDCIDName(refID), &(refID));                                             \
    else                                                                                      \
        dprintff("%s=%p (illegal pointer!!!)", #refID, &(refID))


/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/
#include "moz_GCCDefines.h"

#define INCL_BASE
#include <os2.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCL_NS4X
#include "common.h"

/*******************************************************************************
*   Structures and Typedefs                                                    *
*******************************************************************************/

#define NP32_LOADDS   __cdecl

#pragma pack(4)

/**
 * Win 32 Plugin Entrypoints.
 */
typedef struct _NP32PluginFuncs
{
    uint16_t size;
    uint16_t version;
    union
    {
        struct
        {
            NPError     (* NP32_LOADDS pfnNew)(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, char* argn[], char* argv[], NPSavedData* saved);
            NPError     (* NP32_LOADDS pfnDestroy)(NPP instance, NPSavedData** save);
            NPError     (* NP32_LOADDS pfnSetWindow)(NPP instance, NPWindow* window);
            NPError     (* NP32_LOADDS pfnNewStream)(NPP instance, NPMIMEType type, NPStream* stream, NPBool seekable, uint16_t* stype);
            NPError     (* NP32_LOADDS pfnDestroyStream)(NPP instance, NPStream* stream, NPReason reason);
            void        (* NP32_LOADDS pfnStreamAsFile)(NPP instance, NPStream* stream, const char* fname);
            int32_t     (* NP32_LOADDS pfnWriteReady)(NPP instance, NPStream* stream);
            int32_t     (* NP32_LOADDS pfnWrite)(NPP instance, NPStream* stream, int32_t offset, int32_t len, void* buffer);
            void        (* NP32_LOADDS pfnPrint)(NPP instance, NPPrint* platformPrint);
            int16_t     (* NP32_LOADDS pfnHandleEvent)(NPP instance, void* event);
            void        (* NP32_LOADDS pfnURLNotify)(NPP instance, const char* url, NPReason reason, void* notifyData);
            void*       javaClass;
            NPError     (* NP32_LOADDS pfnGetValue)(NPP instance, NPPVariable variable, void *ret_alue);
            NPError     (* NP32_LOADDS pfnSetValue)(NPP instance, NPNVariable variable, void *ret_alue);
            NPBool      (* NP32_LOADDS pfnGotFocus)(NPP instance, NPFocusDirection direction);
            void        (* NP32_LOADDS pfnLostFocus)(NPP instance);
            void        (* NP32_LOADDS pfnURLRedirectNotify)(NPP instance, const char* url, int32_t status, void* notifyData);
            NPError     (* NP32_LOADDS pfnClearSiteData)(const char* site, uint64_t flags, uint64_t maxAge);
            char**      (* NP32_LOADDS pfnGetSitesWithData)(void);
        };
        PFN functions[0];
    };
} NP32PluginFuncs;


/**
 * Win32 Netscape Entrypoints.
 */
typedef struct _NP32NetscapeFuncs
{
    uint16_t size;
    uint16_t version;
    union
    {
        struct
        {
            // Note: we don't need Win32-like Netscape function pointers here since we would never
            // call these from our code and the whole struct is only used as a placeholder for
            // stub creation magic
        };
        PFN functions[0];
    };
} NP32NetscapeFuncs;

/**
 * NPVariant is 16 bytes on Win32 (12 bytes on all GCC platforms).
 */
typedef struct _NP32Variant
{
    NPVariantType type;
    uint32_t padding;
    union
    {
        bool boolValue;
        int32_t intValue;
        double doubleValue;
        NPString stringValue;
        NPObject *objectValue;
    } value;

} NP32Variant;

/**
 * NPClass for Win32 with the correct NPVariant.
 */
typedef struct _NP32Class
{
    uint32_t structVersion;

#if NP_CLASS_STRUCT_VERSION != 3
#error Check _NP32Class::functions length!
#endif

    union
    {
        struct
        {
            NPObject *(*pfnAllocateFunction)(NPP npp, _NP32Class *aClass);
            void (*pfnDeallocateFunction)(NPObject *npobj);
            void (*pfnInvalidateFunction)(NPObject *npobj);
            bool (*pfnHasMethodFunction)(NPObject *npobj, NPIdentifier name);
            bool (*pfnInvokeFunction)(NPObject *npobj, NPIdentifier name, const NP32Variant *args, uint32_t argCount, NP32Variant *result);
            bool (*pfnInvokeDefaultFunction)(NPObject *npobj, const NP32Variant *args, uint32_t argCount, NP32Variant *result);
            bool (*pfnHasPropertyFunction)(NPObject *npobj, NPIdentifier name);
            bool (*pfnGetPropertyFunction)(NPObject *npobj, NPIdentifier name, NP32Variant *result);
            bool (*pfnSetPropertyFunction)(NPObject *npobj, NPIdentifier name, const NP32Variant *value);
            bool (*pfnRemovePropertyFunction)(NPObject *npobj, NPIdentifier name);
            bool (*pfnEnumerationFunction)(NPObject *npobj, NPIdentifier **value, uint32_t *count);
            bool (*pfnConstructFunction)(NPObject *npobj, const NP32Variant *args, uint32_t argCount, NP32Variant *result);
        };
        PFN functions[12]; /* as of NP_CLASS_STRUCT_VERSION */
    };

    enum { FunctionCount = sizeof(functions) / sizeof(functions[0]) };

} NP32Class;

#pragma pack()

/*******************************************************************************
*   Structures and Typedefs                                                    *
*******************************************************************************/

#pragma pack(1)

/**
 * Stub code for callback wrappers.
 *
 * Used to generate the following assembly:
 * <pre>
 *    push ADDR
 *    call near FUNC
 *    pop ecx
 *    ret
 * </pre>
 *
 * This code effectively prepends ADDR to the original argument list and hands
 * control over to FUNC.
 */
struct WrapperStub
{
    char            chPush;
    void *          pvImm32bit;
    char            chCall;
    int             offRel32bit;
    char            chPopEcx;
    char            chRet;
    char            achMagic[4];    /* 0xcccccccc */
};

#if 0
/**
 * Plugin Entrypoints wrapper.
 */
typedef struct _PluginFuncsWrapper
{
//    /** Pointer to the original struct. (do we need to keep this around?) */
//    NPPluginFuncs *     pNative;

//    /** padding for 16byte code aligment. */
//    char                uaPadding1[8];

    /** Stub code for each handler. */
    struct Stub
    {
        char            chPush;
        void *          pvImm32bit;
        char            chCall;
        int             offRel32bit;
        char            chPopEcx;
        char            chRet;
        char            achMagic[4];    /* 0xcccccccc */
    }   *pStubs;

    /** The stuff we present to the Win32 side. */
    NP32PluginFuncs *w32;

} NPLUGINFUNCSWRAPPER,  *PNPLUGINFUNCSWRAPPER;


/**
 * Netscape Entrypoints Wrapper.
 */
typedef struct _NetscapeFuncsWrapper
{
    /** Pointer to the original struct. (do we need to keep this around?) */
    NPNetscapeFuncs *   pNative;

//    /** padding for 16byte code aligment. */
//    char                auPadding[8];

    /** Stub code for each handler. */
    struct Stub
    {
        char            chPush;
        void *          pvImm32bit;
        char            chCall;
        int             offRel32bit;
        char            chPopEcx;
        char            chRet;
        char            achMagic[4];    /* 0xcccccccc */
    }   *pStubs;

//    /** The stuff we present to the Win32 side. */
//    NP32NetscapeFuncs *w32;

} NETSCAPEFUNCSWRAPPER,  *PNETSCAPEFUNCSWRAPPER;
#endif

/**
 * Plugin instance data.
 */
struct PluginInstance
{
    /** Magic number we check for. */
    enum { MAGIC = 0xc003c004 };
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

    /** Stub code for each NPClass method of the scriptable object (NPPVpluginScriptableNPObject) */
    struct Stub
    {
        char            chPush;
        void *          pvImm32bit;
        char            chCall;
        int             offRel32bit;
        char            chPopEcx;
        char            chRet;
        char            achMagic[4];    /* 0xcccccccc */
    }   aStubs[NP32Class::FunctionCount];

    /** Original Win32 class of the scriptable object (NPPVpluginScriptableNPObject) */
    NP32Class *pw32Class;

    /** Substituted class */
    NP32Class newClass;

    /** Flag indicating that we're making the NPPVpluginScriptableNPObject request */
    bool bInGetScriptableObject;

};

#pragma pack()

/**
 * Auxiliary plugin wrapper data
 */
struct NPOdinPluginWrapperData
{
    /* OS/2 wrappers around Win32 plugin functions presented to the browser. */
    WrapperStub *pPluginStubsOS2;

    /* Original Win32 plugin function table */
    NP32PluginFuncs *pPluginFuncsW32;

    /* Win32 wrappers around OS/2 browser presented to the plugin. */
    WrapperStub *pNetscapeStubsW32;

    /* Win32 browser function table presented to the plugin (with wrappers) */
    NP32NetscapeFuncs *pNetscapeFuncsW32;

    /* Original OS/2 browser callback function table (not owned by us) */
    NPNetscapeFuncs *pNetscapeFuncsOS2;
};

/*******************************************************************************
*   Global Variables                                                           *
*******************************************************************************/
/** This variable is used to drag in XPCOM in the linking of a primary wrapper. */
int             giNS4x;

extern "C" void *   NPJNICreateDownWrapperWeakStub(void);
extern "C" unsigned upCreateWrapperWeakStub(void **pv1, void *pv2, int rc);
extern "C" const char * getIIDCIDNameWeakStub(void *pv1);

#if defined(__IBMCPP__)
/*
 * This weak resolving ASSUMES that the caller cleans the stack!
 * (i.e. anything but __stdcall calling convention will work very nicely.)
 */
#pragma weak(NPJNICreateDownWrapper, NPJNICreateDownWrapperWeakStub)
#pragma weak(upCreateWrapper, upCreateWrapperWeakStub)
#pragma weak(getIIDCIDName, getIIDCIDNameWeakStub)

#elif defined(__GNUC__)

#include "plugin_GenericWeaks.cpp"

extern "C" void *   NPJNICreateDownWrapper(HINSTANCE hInstance, unsigned fType, void *pv) __attribute__ ((weak, alias ("NPJNICreateDownWrapperWeakStub")));
extern "C" unsigned upCreateWrapperWeak(void **pv1, void *pv2, int rc) __attribute__  ((weak, alias ("upCreateWrapperWeakStub")));
extern "C" const char * getIIDCIDNameWeak(void *pv1) __attribute__  ((weak, alias ("getIIDCIDNameWeakStub")));

#endif

/*
 * Disable conditinal warnings on VAC
 */
#pragma info(nocnd)
#pragma info(trd)


#define PRINTABLE_CHAR(ch) ((ch >= 32 && ch <= 127) ? ch : '.')

#ifdef DEBUG

static void dprintfBuf(const char *text, const char *buffer, int len)
{
    enum { b_total = 256, b_line = 32,
           len_line = b_line * 4 + 1 + 1,
           num_line = (b_total + b_line - 1) / b_line,
           len_total = len_line * num_line };
    char str[len_total];
    int off = 0;
    for (int str_off = 0; str_off < len_total; str_off += len_line)
    {
        for (int i = 0; i < b_line; i++)
        {
            if (off < len)
            {
                sprintf(str + str_off + i * 3, "%02X ", ((unsigned char *)buffer)[off]);
                str[str_off + b_line * 3 + 1 + i] = PRINTABLE_CHAR(((unsigned char *)buffer)[off]);
                off++;
            }
            else
            {
                sprintf(str + str_off + i * 3, "   ", ((unsigned char *)buffer)[off]);
                str[str_off + b_line * 3 + 1 + i] = ' ';
            }
        }
        str[str_off + b_line * 3] = ' ';
        if (off == b_total || off == len)
        {
            str[str_off + b_line * 4 + 1] = '\0';
            break;
        }
        else
            str[str_off + b_line * 4 + 1] = '\n';
    }
    dprintf("%s: first %d bytes of buffer %p:\n%s", text, b_total, buffer, str);
}

static void dprintfNPVariant(const char *text, const NPVariant *value)
{
    if (!value)
    {
        dprintf("%s: WARNING: NULL NPVariant pointer!", text);
        return;
    }

    switch (value->type)
    {
        case NPVariantType_Void:
            dprintf("%s: void", text);
            break;
        case NPVariantType_Null:
            dprintf("%s: null", text);
            break;
        case NPVariantType_Bool:
            dprintf("%s: bool: %s", text, value->value.boolValue ? "true" : "false");
            break;
        case NPVariantType_Int32:
            dprintf("%s: integer: %d", text, value->value.intValue);
            break;
        case NPVariantType_Double:
            dprintf("%s: double: %f", text, value->value.doubleValue);
            break;
        case NPVariantType_String:
            dprintf("%s: string (%p, %u bytes):", text, value->value.stringValue.UTF8Characters, value->value.stringValue.UTF8Length);
            dprintfBuf(text, value->value.stringValue.UTF8Characters, value->value.stringValue.UTF8Length);
            break;
        case NPVariantType_Object:
            dprintf("%s: object: %p", text, value->value.objectValue);
            break;
    }
}

#define dprintffBuf(buffer, len) dprintfBuf(__FUNCTION__, buffer, len)
#define dprintffNPVariant(value) dprintfNPVariant(__FUNCTION__, value)

#else // DEBUG

#define dprintfNPVariant(a, b)  do {} while (0)
#define dprintfBuf(a, b, c)     do {} while (0)
#define dprintffNPVariant(a)    do {} while (0)
#define dprintffBuf(b, c)       do {} while (0)

#endif // DEBUG

void convertNPVariant(const NP32Variant *from, NPVariant *to)
{
    memcpy((char *)&to->type, (char *)&from->type, sizeof(NPVariantType));
    memcpy((char *)&to->value, (char *)&from->value, sizeof(NPVariant::value));
}

void convertNPVariant(const NPVariant *from, NP32Variant *to)
{
    memcpy((char *)&to->type, (char *)&from->type, sizeof(NPVariantType));
    memset((char *)&to->padding, 0, sizeof(NP32Variant::padding));
    memcpy((char *)&to->value, (char *)&from->value, sizeof(NPVariant::value));
}

static void showMissingOrdinalMsg(int ordinal, const char *errString, const char *errString2)
{
    FILE *phErrFile;
    char msg[512];
    char *env;
    char logfile[_MAX_PATH +1] = {0};
    char logfilename[] = "npflos2_error.txt";

    // create the logfile variable
    env = getenv("TEMP");
    if (env == NULL)
    {
        env = getenv("TMP");
    }
    if (env != NULL)
    {
        strncpy(logfile, env, sizeof(logfile) -1);
        strncat(logfile, "\\", sizeof(logfile) - strlen(logfile) -1);
        strncat(logfile, logfilename, sizeof(logfile) - strlen(logfile) -1);
    }
    else
    {
        strncat(logfile, logfilename, sizeof(logfile) -1);
    }

    snprintf(msg, sizeof(msg),
             "The %s has called a %s function with ordinal %d which is not supported by this version of the Flash plugin wrapper.\n"
             "For your convience a file called %s was created.\n\n"
             "Please report the following information to the vendor:\n"
             "- Flash movie URL;\n"
             "- Flash plugin wrapper version;\n"
             "- Flash plugin DLL version;\n"
             "- Browser version.\n\n"
             "The application will now terminate.",
             errString, errString2, ordinal, logfile);

    phErrFile = fopen(logfile, "w");
    if (phErrFile)
    {
        DATETIME dt;
        DosGetDateTime(&dt);
        fprintf(phErrFile, "*** Log Opened on %04d-%02d-%02d %02d:%02d:%02d ***\n",
                dt.year, dt.month, dt.day, dt.hours, dt.minutes, dt.seconds);
        fprintf(phErrFile, "*** Build Date: " __DATE__ " " __TIME__ " ***\n");
        fprintf(phErrFile, msg);
        fclose(phErrFile);
    }

    WinMessageBox(HWND_DESKTOP, HWND_DESKTOP, msg, NULL, 0, MB_ERROR | MB_OK | MB_SYSTEMMODAL);

    return;
}


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// UP wrappers (stuff that is presented to netscape/mozilla)
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//


NPObject *np4xClass_AllocateFunction(PluginInstance *pInst, void *pvCaller, NPP instance, NPClass *aClass)
{
    dprintff("enter - pInst=%p instance=%p aClass=%p", pInst, instance, aClass);
    dprintff("pw32Class %p", pInst->pw32Class);

    // sanity
    if (aClass != (NPClass *)&pInst->newClass)
    {
        dprintff("ERROR: aClass must be %p", &pInst->newClass);
        return NULL;
    }

    NP4XUP_ENTER_ODIN(FALSE);

    NPObject *object = pInst->pw32Class->pfnAllocateFunction(NP4XUP_W32_INSTANCE(), &pInst->newClass);

    NP4XUP_LEAVE_ODIN(FALSE);

    if (object)
        object->_class = (NPClass *)&pInst->newClass;

    dprintff("leave object=%p", object);
    return object;
}


void np4xClass_DeallocateFunction(PluginInstance *pInst, void *pvCaller, NPObject *npobj)
{
    dprintff("enter - pInst=%p npobj=%p", pInst, npobj);

    NP4XCLASS_SANITY_CHECK((void)0);

    NP4XCLASS_ENTER_ODIN(FALSE);

    pInst->pw32Class->pfnDeallocateFunction(npobj);

    // Must not use NP4XCLASS_LEAVE_ODIN() since it would try to modify the just freed npobj
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintff("leave");
    return;
}


void np4xClass_InvalidateFunction(PluginInstance *pInst, void *pvCaller, NPObject *npobj)
{
    dprintff("enter - pInst=%p npobj=%p", pInst, npobj);

    NP4XCLASS_SANITY_CHECK((void)0);

    NP4XCLASS_ENTER_ODIN(FALSE);

    pInst->pw32Class->pfnInvalidateFunction(npobj);

    NP4XCLASS_LEAVE_ODIN(FALSE);

    dprintff("leave");
    return;
}


bool np4xClass_HasMethodFunction(PluginInstance *pInst, void *pvCaller, NPObject *npobj, NPIdentifier name)
{
    dprintff("enter - pInst=%p npobj=%p name=%p", pInst, npobj, name);

    NP4XCLASS_SANITY_CHECK(false);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnHasMethodFunction(npobj, name);

    NP4XCLASS_LEAVE_ODIN(FALSE);

    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


bool np4xClass_InvokeFunction(PluginInstance *pInst, void *pvCaller, NPObject *npobj, NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    dprintff("enter - pInst=%p npobj=%p name=%p args=%p argCount=%d result=%p", pInst, npobj, name, args, argCount, result);

    NP4XCLASS_SANITY_CHECK(false);

    NP4XUP_BEGIN_IN_NPVARIANTS(args, argCount);
    NP4XUP_BEGIN_OUT_NPVARIANT(result);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnInvokeFunction(npobj, name, NP4XUP_USE_IN_NPVARIANTS(args), argCount, NP4XUP_USE_IN_NPVARIANT(result));

    NP4XCLASS_LEAVE_ODIN(FALSE);

    NP4XUP_END_OUT_NPVARIANT(result);
    NP4XUP_END_IN_NPVARIANTS(args);

    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


bool np4xClass_InvokeDefaultFunction(PluginInstance *pInst, void *pvCaller, NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    dprintff("enter - pInst=%p npobj=%p args=%p argCount=%d result=%p", pInst, npobj, args, argCount, result);

    NP4XCLASS_SANITY_CHECK(false);

    NP4XUP_BEGIN_IN_NPVARIANTS(args, argCount);
    NP4XUP_BEGIN_OUT_NPVARIANT(result);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnInvokeDefaultFunction(npobj, NP4XUP_USE_IN_NPVARIANTS(args), argCount, NP4XUP_USE_IN_NPVARIANT(result));

    NP4XCLASS_LEAVE_ODIN(FALSE);

    NP4XUP_END_OUT_NPVARIANT(result);
    NP4XUP_END_IN_NPVARIANTS(args);

    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


bool np4xClass_HasPropertyFunction(PluginInstance *pInst, void *pvCaller, NPObject *npobj, NPIdentifier name)
{
    dprintff("enter - pInst=%p npobj=%p name=%p", pInst, npobj, name);

    NP4XCLASS_SANITY_CHECK(false);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnHasPropertyFunction(npobj, name);

    NP4XCLASS_LEAVE_ODIN(FALSE);

    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


bool np4xClass_GetPropertyFunction(PluginInstance *pInst, void *pvCaller, NPObject *npobj, NPIdentifier name, NPVariant *result)
{
    dprintff("enter - pInst=%p npobj=%p name=%p result=%p", pInst, npobj, name, result);

    NP4XCLASS_SANITY_CHECK(false);

    NP4XUP_BEGIN_OUT_NPVARIANT(result);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnGetPropertyFunction(npobj, name, NP4XUP_USE_OUT_NPVARIANT(result));

    NP4XCLASS_LEAVE_ODIN(FALSE);

    NP4XUP_END_OUT_NPVARIANT(result);

    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


bool np4xClass_SetPropertyFunction(PluginInstance *pInst, void *pvCaller, NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
    dprintff("enter - pInst=%p npobj=%p name=%p value=%p", pInst, npobj, name, value);

    NP4XCLASS_SANITY_CHECK(false);

    NP4XUP_BEGIN_IN_NPVARIANT(value);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnSetPropertyFunction(npobj, name, NP4XUP_USE_IN_NPVARIANT(value));

    NP4XCLASS_LEAVE_ODIN(FALSE);

    NP4XUP_END_IN_NPVARIANT(value);

    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


bool np4xClass_RemovePropertyFunction(PluginInstance *pInst, void *pvCaller, NPObject *npobj, NPIdentifier name)
{
    dprintff("enter - pInst=%p npobj=%p name=%p", pInst, npobj, name);

    NP4XCLASS_SANITY_CHECK(false);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnHasPropertyFunction(npobj, name);

    NP4XCLASS_LEAVE_ODIN(FALSE);

    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


bool np4xClass_EnumerationFunction(PluginInstance *pInst, void *pvCaller, NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
    dprintff("enter - pInst=%p npobj=%p value=%p count=%p", pInst, npobj, value, count);

    NP4XCLASS_SANITY_CHECK(false);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnEnumerationFunction(npobj, value, count);

    NP4XCLASS_LEAVE_ODIN(FALSE);

    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


bool np4xClass_ConstructFunction(PluginInstance *pInst, void *pvCaller, NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    dprintff("enter - pInst=%p npobj=%p args=%p argCount=%d result=%p", pInst, npobj, args, argCount, result);

    NP4XCLASS_SANITY_CHECK(false);

    NP4XUP_BEGIN_IN_NPVARIANTS(args, argCount);
    NP4XUP_BEGIN_OUT_NPVARIANT(result);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnConstructFunction(npobj, NP4XUP_USE_IN_NPVARIANTS(args), argCount, NP4XUP_USE_IN_NPVARIANT(result));

    NP4XCLASS_LEAVE_ODIN(FALSE);

    NP4XUP_END_OUT_NPVARIANT(result);
    NP4XUP_END_IN_NPVARIANTS(args);

    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// UP wrappers (stuff that is presented to netscape/mozilla)
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//


NPError NP_LOADDS np4xUp_New(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPMIMEType pluginType, NPP instance,
                             uint16_t mode, int16_t argc, char* argn[],
                             char* argv[], NPSavedData* saved)
{
    dprintff("enter - pPlugin=%p pluginType=%d instance=%p mode=%d argc=%d argn=%p argv=%p saved=%p",
             pPlugin, pluginType, instance, mode, argc, argn, argv, saved);
    DPRINTF_STR(pluginType);
    int i;
    //for (i = 0; i < argc; i++)
    //    dprintff("'%s'='%s'", argn[i], argv[i]);

    /* Windowless flash hack - make windows. */
    #if 1
    for (i = 0; i < argc; i++)
        if (!stricmp(argn[i], "wmode"))
        {
            argn[i][2] = 'x';
            argn[i][3] = 'x';
            argn[i][4] = 'x';
            dprintff("nuked wmode %d.", i);
        }
        //dprintff("'%s'='%s'", argn[i], argv[i]);
    #endif

    /*
     * Allocate and initialize a instance structure
     */
    PluginInstance *pInst = (PluginInstance *)malloc(sizeof(*pInst));
    if (!pInst)
        return NPERR_OUT_OF_MEMORY_ERROR;
    pInst->auMagic = PluginInstance::MAGIC;
    pInst->w32.pdata = instance->pdata;
    pInst->w32.ndata = pInst;
    pInst->pOrgInstance = instance;
    pInst->pWndData = NULL;
    pInst->pw32Class = NULL;
    memset(&pInst->newClass, 0, sizeof(pInst->newClass));
    pInst->bInGetScriptableObject = false;
    instance->pdata = pInst;

    /*
     * Let the plugin initialize it self.
     */
    dprintf("pfnNew enter");
    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = pPlugin->pData->pPluginFuncsW32->pfnNew(pluginType, NP4XUP_W32_INSTANCE(), mode, argc, argn, argv, saved);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf("pfnNew leave");
    /*
     * Cleanup in case of error.
     */
    if (rc)
    {
        instance->pdata = NULL;
        free(pInst);
    }

    dprintff("leave rc=%d", rc);
    return rc;
}


NPError NP_LOADDS np4xUp_Destroy(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPSavedData** save)
{
    dprintff("enter - pPlugin=%p instance=%p saved=%p",
             pPlugin, instance, save);

    NP4XUP_INSTANCE(TRUE);

    dprintf("pfnDestroy enter");
    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = pPlugin->pData->pPluginFuncsW32->pfnDestroy(NP4XUP_W32_INSTANCE(), save);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf("pfnDestroy leave");

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

    dprintff("leave rc=%d", rc);
    return rc;
}


NPError NP_LOADDS np4xUp_SetWindow(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPWindow* window)
{
    dprintff("enter - pPlugin=%p instance=%p window=%p",
             pPlugin, instance, window);

    NP4XUP_INSTANCE(FALSE);

    dprintf("Mozilla window before npWinSetWindowBegin ");
    dprintf("window: %x win: (%i,%i)-(%i,%i), rect: (%i,%i)-(%i,%i)",
            window->window, window->x, window->y,
            window->width, window->height,
            window->clipRect.left, window->clipRect.top,
            window->clipRect.right, window->clipRect.bottom);

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

    dprintf("Mozilla window after npWinSetWindowBegin ");
    dprintf("window: %x win: (%i,%i)-(%i,%i), rect: (%i,%i)-(%i,%i)",
            pWindow->window, pWindow->x, pWindow->y,
            pWindow->width, pWindow->height,
            pWindow->clipRect.left, pWindow->clipRect.top,
            pWindow->clipRect.right, pWindow->clipRect.bottom);

    /*
     * Now enter Odin context and call the real method.
     */
    // vladest
    //////////////////////////////////
    //if (window->y < 0) window->y = 0;
    //if (pWindow->y < 0) pWindow->y = 0;
    //////////////////////////////////
    dprintf("pfnSetWindow enter. address %08X", pPlugin->pData->pPluginFuncsW32->pfnSetWindow);
    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = 1;
    rc = pPlugin->pData->pPluginFuncsW32->pfnSetWindow(NP4XUP_W32_INSTANCE(), pWindow);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf("pfnSetWindow leave");
    #if 0
    /*
     * Fake a handle even call for WM_PAINT.
     */
    if (window->type == 2)
    {
        extern int16_t   NP_LOADDS np4xUp_HandleEvent(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, void* event);
        NPEvent event;
        event.event = WM_PAINT;
        event.wParam = (uint32_t)window->window;
        event.lParam = (uint32_t)&window->x; //???
        np4xUp_HandleEvent(pPlugin, pvCaller, instance, &event);
    }
    #endif

    /*
     * End the window/ps wrapping.
     * (Must be called out of Odin context!)
     */
    npWinSetWindowEnd(window, TRUE, pInst ? &pInst->pWndData : NULL, &PerSetWindow);
    dprintff("leave rc=%d", rc);
    return rc;
}


NPError NP_LOADDS np4xUp_NewStream(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPMIMEType type,
                                   NPStream* stream, NPBool seekable,
                                   uint16_t* stype)
{
    dprintff("enter - pPlugin=%p instance=%p type=%p stream=%p seekable=%d stype=%p",
             pPlugin, instance, type, stream, seekable, stype);
    DPRINTF_STR(type);
    DPRINTF_STREAM(stream);
    NP4XUP_INSTANCE(FALSE);

    NP4XUP_ENTER_ODIN(FALSE);
    dprintf("pfnNewStream enter");
    NPError rc = pPlugin->pData->pPluginFuncsW32->pfnNewStream(NP4XUP_W32_INSTANCE(), type, stream, seekable, stype);
    dprintf("pfnNewStream leave");
    NP4XUP_LEAVE_ODIN(FALSE);

    if (!rc)
        DPRINTF_STREAM(stream);

    dprintff("leave rc=%d *stype=%d", rc, *stype);
    return rc;
}


NPError NP_LOADDS np4xUp_DestroyStream(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPStream* stream, NPReason reason)
{
    dprintff("enter - pPlugin=%p instance=%p stream=%p reason=%d",
             pPlugin, instance, stream, reason);
    DPRINTF_STREAM(stream);
    NP4XUP_INSTANCE(FALSE);

    NP4XUP_ENTER_ODIN(FALSE);
    dprintf("pfnDestroyStream enter");
    NPError rc = pPlugin->pData->pPluginFuncsW32->pfnDestroyStream(NP4XUP_W32_INSTANCE(), stream, reason);
    dprintf("pfnDestroyStream leave");
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintff("leave rc=%d", rc);
    return rc;
}


int32_t NP_LOADDS np4xUp_WriteReady(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPStream* stream)
{
    dprintff("enter - pPlugin=%p instance=%p stream=%p",
             pPlugin, instance, stream);
    DPRINTF_STREAM(stream);
    NP4XUP_INSTANCE(FALSE);

    dprintf("pfnWriteReady enter");
    NP4XUP_ENTER_ODIN(FALSE);
    int32_t rc = pPlugin->pData->pPluginFuncsW32->pfnWriteReady(NP4XUP_W32_INSTANCE(), stream);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf("pfnWriteReady leave");

    DPRINTF_STREAM(stream);
    dprintff("leave rc=%i", rc);
    return rc;
}


int32_t NP_LOADDS np4xUp_Write(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPStream* stream, int32_t offset,
                               int32_t len, void* buffer)
{
    dprintff("enter - pPlugin=%p instance=%p stream=%p offset=%d len=%d buffer=%p",
             pPlugin, instance, stream, offset, len, buffer);
    DPRINTF_STREAM(stream);
    NP4XUP_INSTANCE(FALSE);
    dprintffBuf((const char *)buffer, len);

    dprintf("pfnWrite enter");
    NP4XUP_ENTER_ODIN(FALSE);
    int32_t rc = pPlugin->pData->pPluginFuncsW32->pfnWrite(NP4XUP_W32_INSTANCE(), stream, offset, len, buffer);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf("pfnWrite leave");
    DPRINTF_STREAM(stream);
    dprintff("leave rc=%d", rc);
    return rc;
}


void    NP_LOADDS np4xUp_StreamAsFile(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPStream* stream, const char* fname)
{
    dprintff("enter - pPlugin=%p instance=%p stream=%p fname=%p",
             pPlugin, instance, stream, fname);
    DPRINTF_STREAM(stream);
    DPRINTF_STR(fname);
    //@todo character conversion of filename!
    NP4XUP_INSTANCE(FALSE);

    NP4XUP_ENTER_ODIN(FALSE);
    dprintf("pfnStreamAsFile enter");
    pPlugin->pData->pPluginFuncsW32->pfnStreamAsFile(NP4XUP_W32_INSTANCE(), stream, fname);
    dprintf("pfnStreamAsFile leave");
    NP4XUP_LEAVE_ODIN(FALSE);

    DPRINTF_STREAM(stream);
    dprintff("leave");
    return;
}


void    NP_LOADDS np4xUp_Print(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPPrint* platformPrint)
{
    dprintff("enter - pPlugin=%p instance=%p platformPrint=%p",
             pPlugin, instance, platformPrint);
    if (platformPrint)
    {
        if (platformPrint->mode == NP_EMBED)
            dprintff("Embed: platformPrint=%08x windows: windows=%08x, (x,y,width,height)=(%d,%d,%d,%d) type=%d",
                     platformPrint->print.embedPrint.platformPrint,
                     platformPrint->print.embedPrint.window.window,
                     platformPrint->print.embedPrint.window.x,
                     platformPrint->print.embedPrint.window.y,
                     platformPrint->print.embedPrint.window.width,
                     platformPrint->print.embedPrint.window.height,
                     platformPrint->print.embedPrint.window.type);
        else if (platformPrint->mode == NP_FULL)
            dprintff("Full: platformPrint=%08x pluginPrinted=%d printOne=%d",
                     platformPrint->print.fullPrint.platformPrint,
                     platformPrint->print.fullPrint.pluginPrinted,
                     platformPrint->print.fullPrint.printOne);
        else
            dprintff("Unknown mode!");
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
        dprintf("*simple printing case*");
        pPlugin->pData->pPluginFuncsW32->pfnPrint(NP4XUP_W32_INSTANCE(), platformPrint);
    }
    else
    {
        /*
         * Complex stuff, which means converting a HPS and perhaps a HWND.
         */
#if 0
        ReleaseInt3(0x44440001,0x44440001,0x44440001);
        pPlugin->pData->pPluginFuncsW32->pfnPrint(NP4XUP_W32_INSTANCE(), platformPrint);
#endif
    }
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintff("leave");
    return;
}


int16_t NP_LOADDS np4xUp_HandleEvent(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, void* event)
{
    dprintff("enter - pPlugin=%p instance=%p event=%p",
             pPlugin, instance, event);
    NP4XUP_INSTANCE(FALSE);

    /** @todo WM_PAINT handling and stuff. */
    ReleaseInt3(0x44440002,0x44440002,0x44440002);

    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = pPlugin->pData->pPluginFuncsW32->pfnHandleEvent(NP4XUP_W32_INSTANCE(), event);
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintff("leave rc=%d", rc);
    return rc;
}


void    NP_LOADDS np4xUp_URLNotify(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, const char* url,
                                   NPReason reason, void* notifyData)
{
    dprintff("enter - pPlugin=%p instance=%p url=%p reaons=%d notifyData=%p",
             pPlugin, instance, url, reason, notifyData);
    DPRINTF_STR(url);
    //@todo TEXT: url needs attention.
    NP4XUP_INSTANCE(FALSE);

    NP4XUP_ENTER_ODIN(FALSE);
    pPlugin->pData->pPluginFuncsW32->pfnURLNotify(NP4XUP_W32_INSTANCE(), url, reason, notifyData);
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintff("leave");
    return;
}


void*   NP_LOADDS np4xUp_GetJavaClass(NPOdinPluginWrapper *pPlugin, void *pvCaller)
{
    dprintff("enter - pPlugin=%p", pPlugin);

    NP4XUP_ENTER_ODIN(FALSE);
    ReleaseInt3(0x44440003,0x44440003,0x44440003);
    void* rc = 0;// = pPlugin->pData->pPluginFuncsW32->pfnGetJavaClass();
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintff("leave rc=%p", rc);
    return rc;
}


NPError NP_LOADDS np4xUp_GetValue(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPPVariable variable, void *value)
{
    NPError rc = 0;

    dprintff("enter - pPlugin=%p instance=%p variable=%d value=%p",
             pPlugin, instance, variable, value);
    NP4XUP_INSTANCE(FALSE);

    bool bSupported = true;

    switch (variable)
    {
        case NPPVpluginDescriptionString:   dprintff("NPPVpluginDescriptionString"); break;
        case NPPVpluginNameString:          dprintff("NPPVpluginNameString"); break;
        case NPPVpluginWindowBool:          dprintff("NPPVpluginWindowBool"); break;
        case NPPVpluginTransparentBool:     dprintff("NPPVpluginTransparentBool"); break;
        case NPPVjavaClass:                 dprintff("NPPVjavaClass"); break;
        case NPPVpluginWindowSize:          dprintff("NPPVpluginWindowSize"); break;
        case NPPVpluginTimerInterval:       dprintff("NPPVpluginTimerInterval"); break;
        case NPPVpluginScriptableInstance:  dprintff("NPPVpluginScriptableInstance"); break;
        case NPPVpluginScriptableIID:       dprintff("NPPVpluginScriptableIID"); break;
        case NPPVjavascriptPushCallerBool:  dprintff("NPPVjavascriptPushCallerBool"); break;
        case NPPVpluginKeepLibraryInMemory: dprintff("NPPVpluginKeepLibraryInMemory"); break;
        case NPPVpluginScriptableNPObject:  dprintff("NPPVpluginScriptableNPObject"); break;
        default:
            bSupported = false;
            dprintff("Unsupported variable %d", variable);
            break;
    }

    //@todo TEXT: NPPVpluginNameString and NPPVpluginDescriptionString
    if (bSupported)
    {
        switch (variable)
        {
        case NPPVpluginScriptableNPObject:
            {
                NPObject *pObject = NULL;

                // set a flag that indicates to np4xDown_CreateObject() that we need class wrappers
                pInst->bInGetScriptableObject = true;

                NP4XUP_ENTER_ODIN(FALSE);
                rc = pPlugin->pData->pPluginFuncsW32->pfnGetValue(NP4XUP_W32_INSTANCE(), variable, &pObject);
                NP4XUP_LEAVE_ODIN(FALSE);

                pInst->bInGetScriptableObject = false;

                // sanity
                if (!rc && pObject->_class != (NPClass *)&pInst->newClass)
                {
                    dprintff("ERROR: pObject->_class must be %p", &pInst->newClass);
                    rc = NPERR_GENERIC_ERROR;
                }

                if (!rc)
                    *(void**)value = pObject;
            }
            break;

        default:
            NP4XUP_ENTER_ODIN(FALSE);
            rc = pPlugin->pData->pPluginFuncsW32->pfnGetValue(NP4XUP_W32_INSTANCE(), variable, value);
            NP4XUP_LEAVE_ODIN(FALSE);

            if (rc)
                break;

            switch (variable)
            {
            case NPPVpluginDescriptionString:
            case NPPVpluginNameString:
                DPRINTF_STR((char*)value);
                break;
            case NPPVpluginScriptableIID:
                {
                    struct nsID *pnsID = *(struct nsID **)value;
//                    DPRINTF_NSID(*pnsID);
                    break;
                }
            case NPPVpluginScriptableInstance:
                {
                    if (VALID_PTR(value))
                    {
                        uint32_t rc2 = 0x80000001;
#if 0 // @TODO rwalsh disabled this, why?
                        struct nsID *pnsID = NULL;
                        dprintff("*(void**)value=%p", *(void**)value);
                        NP4XUP_ENTER_ODIN(FALSE);
                        NPError rc = pPlugin->pData->pPluginFuncsW32->pfnGetValue(NP4XUP_W32_INSTANCE(), NPPVpluginScriptableIID, (void*)&pnsID);
                        NP4XUP_LEAVE_ODIN(FALSE);
                        if (!rc && VALID_PTR(pnsID))
                        {
//                            DPRINTF_NSID(*pnsID);
                            rc2 = upCreateWrapper((void**)value, *pnsID, /*NS_OK*/0);
                        }
#endif
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
                    dprintff("*value=%s", *(bool*)value ? "true" : "false");
                    /* Mozilla doesn't support this. */
                    if (variable == NPPVpluginWindowBool && !*(bool*)value)
                    {
                        *(bool*)value = TRUE;
                        dprintff("OS/2 Mozilla doesn't yet support windowless plugins, so we return true!!");
                    }
                    if (variable == NPPVpluginTransparentBool && *(bool*)value)
                    {
                        *(bool*)value = FALSE;
                        dprintff("OS/2 Mozilla doesn't yet support windowless plugins, so we return false!!");
                    }
                }
                break;

            case NPPVpluginScriptableNPObject:
                {
                    NPObject *pObject = NULL;

                    // set a flag that indicates to np4xDown_CreateObject() that we need class wrappers
                    pInst->bInGetScriptableObject = true;

                    NP4XUP_ENTER_ODIN(FALSE);
                    rc = pPlugin->pData->pPluginFuncsW32->pfnGetValue(NP4XUP_W32_INSTANCE(), variable, &pObject);
                    NP4XUP_LEAVE_ODIN(FALSE);

                    pInst->bInGetScriptableObject = false;

                    // sanity
                    if (!rc && pObject->_class != (NPClass *)&pInst->newClass)
                    {
                        dprintff("ERROR: pObject->_class must be %p", &pInst->newClass);
                        rc = NPERR_GENERIC_ERROR;
                    }

                    if (!rc)
                        *(void**)value = pObject;
                }
                break;

            case NPPVjavaClass:
            case NPPVpluginWindowSize:
            case NPPVpluginTimerInterval:
            case NPPVjavascriptPushCallerBool:
            case NPPVpluginKeepLibraryInMemory:
            default:
                if (VALID_PTR(value))
                    dprintff("*(void**)value=%p", *(void**)value);
                break;
            }
            break;
        }
    }
    else
    {
        rc = NPERR_GENERIC_ERROR;
    }

    dprintff("leave rc=%p", rc);
    return rc;
}

NPError NP_LOADDS np4xUp_SetValue(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPNVariable variable, void *value)
{
    dprintff("enter - pPlugin=%p instance=%p variable=%d value=%p",
             pPlugin, instance, variable, value);
//@todo TEXT: NPPVpluginNameString and NPPVpluginDescriptionString ?
    NP4XUP_INSTANCE(FALSE);

    switch (variable)
    {
        case NPNVxDisplay:
            dprintff("NPNVxDisplay");
            if (VALID_PTR(value))
                dprintff("*value=%#x", *(void**)value);
            break;
        case NPNVxtAppContext:
            dprintff("NPNVxtAppContext");
            if (VALID_PTR(value))
                dprintff("*value=%#x", *(void**)value);
            break;
        case NPNVnetscapeWindow:
            dprintff("NPNVnetscapeWindow");
            if (VALID_PTR(value))
                dprintff("*value=%#x", *(void**)value);
            DebugInt3();
            //@todo wrapper!!!!
            break;
        case NPNVjavascriptEnabledBool:
            dprintff("%s: NPNVjavascriptEnabledBool *value=%s",
                     VALID_PTR(value) ? *((bool*)value) ? "true" : "false" : "invalid");
            break;
        case NPNVasdEnabledBool:
            dprintff("%s: NPNVasdEnabledBool *value=%s",
                     VALID_PTR(value) ? *((bool*)value) ? "true" : "false" : "invalid");
            break;
        case NPNVisOfflineBool:
            dprintff("%s: NPNVisOfflineBool *value=%s",
                     VALID_PTR(value) ? *((bool*)value) ? "true" : "false" : "invalid");
            break;
        case NPNVserviceManager:
            dprintff("NPNVserviceManager");
            if (VALID_PTR(value))
                dprintff("*value=%#x", *(void**)value);
            break;
        case NPNVDOMElement:
            dprintff("NPNVDOMElement");
            if (VALID_PTR(value))
                dprintff("*value=%#x", *(void**)value);
            break;
        case NPNVDOMWindow:
            dprintff("NPNVDOMWindow");
            if (VALID_PTR(value))
                dprintff("*value=%#x", *(void**)value);
            break;
        default:
            dprintff("Unknown variable number %d", variable);
            break;
    }

    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = pPlugin->pData->pPluginFuncsW32->pfnSetValue(NP4XUP_W32_INSTANCE(), variable, value);
    NP4XUP_LEAVE_ODIN(FALSE);
    if (!rc && VALID_PTR(value))
        dprintff("*(void**)value=%p", *(void**)value);

    dprintff("leave rc=%p", rc);
    return rc;
}


NPBool  NP_LOADDS np4xUp_GotFocus(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPFocusDirection direction)
{
    dprintff("enter - pPlugin=%p instance=%p directions=%p",
             pPlugin, instance, direction);
    NP4XUP_INSTANCE(FALSE);

    NP4XUP_ENTER_ODIN(FALSE);
    NPBool rc = pPlugin->pData->pPluginFuncsW32->pfnGotFocus(NP4XUP_W32_INSTANCE(), direction);
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintff("leave rc=%p", rc);
    return rc;
}

void    NP_LOADDS np4xUp_LostFocus(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance)
{
    dprintff("enter - pPlugin=%p instance=%p",
             pPlugin, instance);
    NP4XUP_INSTANCE(FALSE);

    NP4XUP_ENTER_ODIN(FALSE);
    pPlugin->pData->pPluginFuncsW32->pfnLostFocus(NP4XUP_W32_INSTANCE());
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintff("leave");
    return;
}


void    NP_LOADDS np4xUp_URLRedirectNotify(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, const char* url, int32_t status, void* notifyData)
{
    dprintff("enter - pPlugin=%p instance=%p url=%p status=%x notifyData=%p",
             pPlugin, instance, url, status, notifyData);
    DPRINTF_STR(url);
    NP4XUP_INSTANCE(FALSE);

    NP4XUP_ENTER_ODIN(FALSE);
    pPlugin->pData->pPluginFuncsW32->pfnURLRedirectNotify(NP4XUP_W32_INSTANCE(), url, status, notifyData);
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintff("leave");
    return;
}


NPError NP_LOADDS np4xUp_ClearSiteData(NPOdinPluginWrapper *pPlugin, void *pvCaller, const char* site, uint64_t flags, uint64_t maxAge)
{
    dprintff("enter - pPlugin=%p site=%p flags=%lx maxAge=%ld",
             pPlugin, site, flags, maxAge);
    DPRINTF_STR(site);

    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = pPlugin->pData->pPluginFuncsW32->pfnClearSiteData(site, flags, maxAge);
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintff("leave rc=%p", rc);
    return rc;
}


char**  NP_LOADDS np4xUp_GetSitesWithData(NPOdinPluginWrapper *pPlugin, void *pvCaller)
{
    dprintff("enter - pPlugin=%p",
             pPlugin);

    NP4XUP_ENTER_ODIN(FALSE);
    char **ret = pPlugin->pData->pPluginFuncsW32->pfnGetSitesWithData();
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintff("leave ret=%p", ret);
    return ret;
}


/**
 * Stub for not implemented functions.
 *
 * @param ordinal   Ordinal function number.
 */
void NP_LOADDS np4xUp_NotImplementedStub(int ordinal)
{
    dprintff("enter - ordinal=%d", ordinal);

    showMissingOrdinalMsg(ordinal, "browser", "Flash plugin");

    dprintff("Terminating the application.");
    exit(333);
    return;
}


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// DOWN wrappers (stuff that is to the plugin)
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//


/* This is not a callback, but something most plugins implememnts somehow, remove it! */
void    NP32_LOADDS np4xDown_Version(NPOdinPluginWrapper *pPlugin, void *pvCaller, int* plugin_major, int* plugin_minor,
                                       int* netscape_major, int* netscape_minor)
{
    dprintff("enter - pPlugin=%p plugin_major=%p plugin_minor=%p netscape_major=%p netscape_minor=%p",
             pPlugin, plugin_major, plugin_minor, netscape_major, netscape_minor);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    ReleaseInt3(0x44440004,0x44440004,0x44440004);
    //pPlugin->pData->pNetscapeFuncsOS2->??(plugin_major, plugin_minor, netscape_major, netscape_minor);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave");
    return;
}


NPError NP32_LOADDS np4xDown_GetURLNotify(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, const char* url, const char* target, void* notifyData)
{
    dprintff("enter - pPlugin=%p instance=%p url=%p target=%p notifyData=%p",
             pPlugin, instance, url, target, notifyData);
    DPRINTF_STR(url);
    DPRINTF_STR(target);
    //@todo TEXT: url and target needs conversion.
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc = pPlugin->pData->pNetscapeFuncsOS2->geturlnotify(NP4XDOWN_NS_INSTANCE(), url, target, notifyData);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%p", rc);
    return rc;
}


NPError NP32_LOADDS np4xDown_GetURL(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, const char* url, const char* target)
{
    dprintff("enter - pPlugin=%p instance%p url=%p target=%p",
             pPlugin, instance, url, target);
    DPRINTF_STR(url);
    DPRINTF_STR(target);
    //@todo TEXT: url and target needs conversion.
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc = pPlugin->pData->pNetscapeFuncsOS2->geturl(NP4XDOWN_NS_INSTANCE(), url, target);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%p", rc);
    return rc;
}


NPError NP32_LOADDS np4xDown_PostURLNotify(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, const char* url, const char* target, uint32_t len,
                                             const char* buf, NPBool file, void* notifyData)
{
    dprintff("enter - pPlugin=%p instance%p url=%p target=%p len=%d buf=%p file=%d notifyData=%p",
             pPlugin, instance, url, target, len, buf, file, notifyData);
    DPRINTF_STR(url);
    DPRINTF_STR(target);
    //@todo TEXT: url and target needs conversion.
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc = pPlugin->pData->pNetscapeFuncsOS2->posturlnotify(NP4XDOWN_NS_INSTANCE(), url, target, len, buf, file, notifyData);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%p", rc);
    return rc;
}


NPError NP32_LOADDS np4xDown_PostURL(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, const char* url,
                                       const char* target, uint32_t len,
                                       const char* buf, NPBool file)
{
    dprintff("enter - pPlugin=%p instance%p url=%p target=%p len=%d buf=%p file=%d",
             pPlugin, instance, url, target, len, buf, file);
    DPRINTF_STR(url);
    DPRINTF_STR(target);
    //@todo TEXT: url and target needs conversion.
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc = pPlugin->pData->pNetscapeFuncsOS2->posturl(NP4XDOWN_NS_INSTANCE(), url, target, len, buf, file);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%p", rc);
    return rc;
}


NPError NP32_LOADDS np4xDown_RequestRead(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPStream* stream, NPByteRange* rangeList)
{
    dprintff("enter - pPlugin=%p stream=%p rangeList=%p",
             pPlugin, stream, rangeList);
    DPRINTF_STREAM(stream);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc = pPlugin->pData->pNetscapeFuncsOS2->requestread(stream, rangeList);

    DPRINTF_STREAM(stream);
    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%p", rc);
    return rc;
}


NPError NP32_LOADDS np4xDown_NewStream(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPMIMEType type,
                                         const char* target, NPStream** stream)
{
    dprintff("enter - pPlugin=%p instance=%p type=%p target=%p stream=%p",
             pPlugin, instance, type, target, stream);
    DPRINTF_STR(type);
    DPRINTF_STR(target);
    //@todo TEXT: target needs conversion.
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc = pPlugin->pData->pNetscapeFuncsOS2->newstream(NP4XDOWN_NS_INSTANCE(), type, target, stream);
    if (!rc && VALID_PTR(*stream))
    {
        dprintff("*stream=%p", *stream);
        DPRINTF_STREAM(*stream);
    }

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%p", rc);
    return rc;
}


int32_t NP32_LOADDS np4xDown_Write(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPStream* stream, int32_t len, void* buffer)
{
    dprintff("enter - pPlugin=%p instance=%p stream=%p len=%d buffer=%p",
             pPlugin, instance, stream, len, buffer);
    DPRINTF_STREAM(stream);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    int32_t rc = pPlugin->pData->pNetscapeFuncsOS2->write(NP4XDOWN_NS_INSTANCE(), stream, len, buffer);

    NP4XDOWN_ENTER_ODIN(FALSE);
    DPRINTF_STREAM(stream);
    dprintff("leave rc=%d", rc);
    return rc;
}


NPError NP32_LOADDS np4xDown_DestroyStream(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPStream* stream, NPReason reason)
{
    dprintff("enter - pPlugin=%p instance=%p stream=%p reason=%d",
             pPlugin, instance, stream, reason);
    DPRINTF_STREAM(stream);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc = pPlugin->pData->pNetscapeFuncsOS2->destroystream(NP4XDOWN_NS_INSTANCE(), stream, reason);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%d", rc);
    return rc;
}


void    NP32_LOADDS np4xDown_Status(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, const char* message)
{
    dprintff("enter - pPlugin=%p instance=%p message=%p",
             pPlugin, instance, message);
    DPRINTF_STR(message);
    //@todo TEXT: attention to message
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pPlugin->pData->pNetscapeFuncsOS2->status(NP4XDOWN_NS_INSTANCE(), message);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave");
    return;
}


const char* NP32_LOADDS np4xDown_UserAgent(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance)
{
    dprintff("enter - pPlugin=%p instance=%p",
             pPlugin, instance);
    NP4XDOWN_INSTANCE(TRUE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    const char * pszRc = pPlugin->pData->pNetscapeFuncsOS2->uagent(NP4XDOWN_NS_INSTANCE());
    DPRINTF_STR(pszRc);

    dprintff("leave rc=%p", pszRc);
    NP4XDOWN_ENTER_ODIN(FALSE);
    return pszRc;
}


void*   NP32_LOADDS np4xDown_MemAlloc(NPOdinPluginWrapper *pPlugin, void *pvCaller, uint32_t size)
{
    dprintff("enter - pPlugin=%p size=%d",
             pPlugin, size);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    void* pvRc = pPlugin->pData->pNetscapeFuncsOS2->memalloc(size);

    dprintff("leave pvRc=%p", pvRc);
    NP4XDOWN_ENTER_ODIN(FALSE);
    return pvRc;
}


void    NP32_LOADDS np4xDown_MemFree(NPOdinPluginWrapper *pPlugin, void *pvCaller, void* ptr)
{
    dprintff("enter - pPlugin=%p ptr=%p",
             pPlugin, ptr);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pPlugin->pData->pNetscapeFuncsOS2->memfree(ptr);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave");
    return;
}


uint32_t NP32_LOADDS np4xDown_MemFlush(NPOdinPluginWrapper *pPlugin, void *pvCaller, uint32_t size)
{
    dprintff("enter - pPlugin=%p size=%d",
             pPlugin, size);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    uint32_t rc = pPlugin->pData->pNetscapeFuncsOS2->memflush(size);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%d", rc);
    return rc;
}


void    NP32_LOADDS np4xDown_ReloadPlugins(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPBool reloadPages)
{
    dprintff("enter - pPlugin=%p reloadPages=%d",
             pPlugin, reloadPages);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pPlugin->pData->pNetscapeFuncsOS2->reloadplugins(reloadPages);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave");
    return;
}


void*   NP32_LOADDS np4xDown_GetJavaEnv(NPOdinPluginWrapper *pPlugin, void *pvCaller)
{
    dprintff("enter - pPlugin=%p", pPlugin);
    NP4XDOWN_LEAVE_ODIN(FALSE);

  /*  ReleaseInt3(0x44440005,0x44440005,0x44440005); */
    void *envRc = pPlugin->pData->pNetscapeFuncsOS2->getJavaEnv();

    if (VALID_PTR(envRc))
    {
        void *pvWrapped = (void *)NPJNICreateDownWrapper(0, NPJS_TYPE_JRIENV_DOWN, envRc);
        if (pvWrapped)
            dprintff("Successfully created wrapper, %#p, for JRIEnv %#p", pvWrapped, envRc);
        else
        {
            dprintff("failed to make wrapper for JRIEnv %#p", envRc);
            DebugInt3();
        }
        envRc = pvWrapped;
    }

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave envRc=%p", envRc);
    return envRc;
}


void*   NP32_LOADDS np4xDown_GetJavaPeer(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance)
{
    dprintff("enter - pPlugin=%p instance=%p", pPlugin, instance);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    void* rc = pPlugin->pData->pNetscapeFuncsOS2->getJavaPeer(NP4XDOWN_NS_INSTANCE());

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%p", rc);
    return rc;
}


NPError NP32_LOADDS np4xDown_GetValue(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPNVariable variable, void *value)
{
    dprintff("enter - pPlugin=%p instance=%p variable=%d value=%p",
             pPlugin, instance, variable, value);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc;
    bool bSupported = true;

    switch (variable)
    {
        case NPNVxDisplay:              dprintff("NPNVxDisplay"); break;
        case NPNVxtAppContext:          dprintff("NPNVxtAppContext"); break;
        case NPNVnetscapeWindow:        dprintff("NPNVnetscapeWindow"); break;
        case NPNVjavascriptEnabledBool: dprintff("NPNVjavascriptEnabledBool"); break;
        case NPNVasdEnabledBool:        dprintff("NPNVasdEnabledBool"); break;
        case NPNVisOfflineBool:         dprintff("NPNVisOfflineBool"); break;
        case NPNVWindowNPObject:        dprintff("NPNVWindowNPObject"); break;
        case NPNVPluginElementNPObject: dprintff("NPNVPluginElementNPObject"); break;
        case NPNVprivateModeBool:       dprintff("NPNVprivateModeBool"); break;
        case NPNVdocumentOrigin:        dprintff("NPNVdocumentOrigin"); break;
        default:
            bSupported = false;
            dprintff("Unsupported variable %d", variable);
            break;
    }

    if (bSupported)
    {
        rc = pPlugin->pData->pNetscapeFuncsOS2->getvalue(NP4XDOWN_NS_INSTANCE(), variable, value);

        if (!rc && VALID_PTR(value))
        {
            switch (variable)
            {
            case NPNVxDisplay:
            case NPNVxtAppContext:
                /* not implemented by OS/2 and Win32 I believe. */
                dprintff("*value=%#08x", *((void**)value));
                break;
            case NPNVnetscapeWindow:
                dprintff("*value=%#08x", *(PHWND)value);
                if (pInst)
                    pInst->hwndOS2 = *(PHWND)value;
                *((PHWND)value) = npWinDownNetscapeWindow(*(PHWND)value);
                dprintff("wrapped *value=%#08x", *(PHWND)value);
                if (pInst)
                    pInst->hwndOdin = *(PHWND)value;
                break;

            case NPNVjavascriptEnabledBool:
            case NPNVasdEnabledBool:
            case NPNVisOfflineBool:
            case NPNVprivateModeBool:
                dprintff("*value=%s", *((bool*)value) ? "true" : "false");
                break;
            case NPNVdocumentOrigin:
                dprintff("*value=%s", *((char**)value));
                break;
            default:
                dprintff("*value=%#08x", *((void**)value));
                break;
            }
        }
    }
    else
    {
        rc = NPERR_GENERIC_ERROR;
    }

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%d", rc);
    return rc;
}


NPError NP32_LOADDS np4xDown_SetValue(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPPVariable variable, void *value)
{
    dprintff("enter - pPlugin=%p instance=%p variable=%d value=%p",
             pPlugin, instance, variable, value);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);
    bool fWindowLessReject = FALSE;
    switch (variable)
    {
        case NPPVpluginNameString:
            dprintff("NPPVpluginNameString");
            DPRINTF_STR((const char*)value);
            break;
        case NPPVpluginDescriptionString:
            dprintff("NPPVpluginDescriptionString");
            DPRINTF_STR((const char*)value);
            break;
        case NPPVpluginWindowBool:
            dprintff("NPPVpluginWindowBool value=%s", value ? "true" : "false");
            if (!(bool)value)
            {
                dprintff("OS/2 Mozilla doesn't yet support windowless plugins, so we set it to true!!");
                value = (void*)TRUE;
                fWindowLessReject = TRUE;
            }
            break;
        case NPPVpluginTransparentBool:
            dprintff("NPPVpluginTransparentBool value=%s", value ? "true" : "false");
            if ((bool)value)
            {
                dprintff("OS/2 Mozilla doesn't yet support windowless plugins, so we set it to false!!");
                value = (void*)FALSE;
                fWindowLessReject = TRUE;
            }
            break;
        case NPPVjavaClass: /* Not implemented in Mozilla 1.0 */
            dprintff("NPPVjavaClass");
            break;
        case NPPVpluginWindowSize:
            dprintff("NPPVpluginWindowSize");
            break;
        case NPPVpluginTimerInterval:
            dprintff("NPPVpluginTimerInterval");
            break;
        case NPPVpluginScriptableInstance:  dprintff("NPPVpluginScriptableInstance"); break;
        case NPPVpluginScriptableIID:       dprintff("NPPVpluginScriptableIID"); break;
        case NPPVjavascriptPushCallerBool:
            dprintff("NPPVjavascriptPushCallerBool");
            break;
        case NPPVpluginKeepLibraryInMemory:
            dprintff("NPPVpluginKeepLibraryInMemory");
            break;

        default:
            dprintff("Invalid variable number %d!!!", variable);
            break;
    }

    NPError rc = pPlugin->pData->pNetscapeFuncsOS2->setvalue(NP4XDOWN_NS_INSTANCE(), variable, value);

    if (fWindowLessReject)
    {
        dprintff("OS/2 Mozilla doesn't yet support windowless plugins, we'll return failure just to be safe...");
        rc = NPERR_INVALID_PARAM;
    }

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%d", rc);
    return rc;
}


void    NP32_LOADDS np4xDown_InvalidateRect(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPRect *invalidRect)
{
    dprintff("enter - pPlugin=%p instance=%p variable=%d invalidRect=%p",
             pPlugin, instance, invalidRect);
    if (VALID_PTR(invalidRect))
        dprintff("(%d,%d)(%d,%d)", invalidRect->top, invalidRect->left, invalidRect->bottom, invalidRect->right);
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

    pPlugin->pData->pNetscapeFuncsOS2->invalidaterect(NP4XDOWN_NS_INSTANCE(), invalidRect);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave");
    return;
}


void    NP32_LOADDS np4xDown_InvalidateRegion(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPRegion invalidRegion)
{
    dprintff("enter - pPlugin=%p instance=%p invalidRegion=%p (HRGN)",
             pPlugin, instance, invalidRegion);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    /** @todo Odin HRGN to OS/2 HRGN. */
    ReleaseInt3(0x44440007,0x44440007,0x44440007);

    pPlugin->pData->pNetscapeFuncsOS2->invalidateregion(NP4XDOWN_NS_INSTANCE(), invalidRegion);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave");
    return;
}


void    NP32_LOADDS np4xDown_ForceRedraw(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance)
{
    dprintff("enter - pPlugin=%p instance=%p",
             pPlugin, instance);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pPlugin->pData->pNetscapeFuncsOS2->forceredraw(NP4XDOWN_NS_INSTANCE());

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave");
    return;
}


NPIdentifier NP32_LOADDS np4xDown_GetStringIdentifier(NPOdinPluginWrapper *pPlugin, void *pvCaller, const NPUTF8* name)
{
    dprintff("enter - pPlugin=%p name=%s",
             pPlugin, name);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPIdentifier identifier = pPlugin->pData->pNetscapeFuncsOS2->getstringidentifier(name);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave identifier=%x", identifier);
    return identifier;
}


void         NP32_LOADDS np4xDown_GetStringIdentifiers(NPOdinPluginWrapper *pPlugin, void *pvCaller, const NPUTF8** names, int32_t nameCount, NPIdentifier* identifiers)
{
    dprintff("enter - pPlugin=%p names=%p nameCount=%d identifiers=%p",
             pPlugin, names, nameCount, identifiers);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pPlugin->pData->pNetscapeFuncsOS2->getstringidentifiers(names, nameCount, identifiers);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave");
    return;
}


NPIdentifier NP32_LOADDS np4xDown_GetIntIdentifier(NPOdinPluginWrapper *pPlugin, void *pvCaller, int32_t intid)
{
    dprintff("enter - pPlugin=%p intid=%d",
             pPlugin, intid);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPIdentifier identifier = pPlugin->pData->pNetscapeFuncsOS2->getintidentifier(intid);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave identifier=%x", identifier);
    return identifier;
}


bool         NP32_LOADDS np4xDown_IdentifierIsString(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPIdentifier identifier)
{
    dprintff("enter - pPlugin=%p identifier=%p",
             pPlugin, identifier);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    bool rc = pPlugin->pData->pNetscapeFuncsOS2->identifierisstring(identifier);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


NPUTF8*      NP32_LOADDS np4xDown_UTF8FromIdentifier(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPIdentifier identifier)
{
    dprintff("enter - pPlugin=%p identifier=%p",
             pPlugin, identifier);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPUTF8 *utf8 = pPlugin->pData->pNetscapeFuncsOS2->utf8fromidentifier(identifier);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave utf8=%s", utf8);
    return utf8;
}


int32_t      NP32_LOADDS np4xDown_IntFromIdentifier(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPIdentifier identifier)
{
    dprintff("enter - pPlugin=%p identifier=%p",
             pPlugin, identifier);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    int32_t i = pPlugin->pData->pNetscapeFuncsOS2->intfromidentifier(identifier);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave i=%d", i);
    return i;
}


NPObject* NP32_LOADDS np4xDown_CreateObject(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPClass *aClass)
{
    dprintff("enter - pPlugin=%p instance=%p aClass=%p",
             pPlugin, instance, aClass);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    // check if we are being called as a result of np4xUp_GetValue(NPPVpluginScriptableNPObject)
    if (pInst->bInGetScriptableObject)
    {
        dprintff("w32 class %p version %d", aClass, aClass->structVersion);

        // save the original class
        pInst->pw32Class = (NP32Class *)aClass;

        memset(&pInst->newClass, 0, sizeof(pInst->newClass));
        pInst->newClass.structVersion = aClass->structVersion;

        // fill up the function table with wrappers
        PFN implementedWrappers[NP32Class::FunctionCount] =
        {
            (PFN)&np4xClass_AllocateFunction,
            (PFN)&np4xClass_DeallocateFunction,
            (PFN)&np4xClass_InvalidateFunction,
            (PFN)&np4xClass_HasMethodFunction,
            (PFN)&np4xClass_InvokeFunction,
            (PFN)&np4xClass_InvokeDefaultFunction,
            (PFN)&np4xClass_HasPropertyFunction,
            (PFN)&np4xClass_GetPropertyFunction,
            (PFN)&np4xClass_SetPropertyFunction,
            (PFN)&np4xClass_RemovePropertyFunction,
            (PFN)&np4xClass_EnumerationFunction,
            (PFN)&np4xClass_ConstructFunction,
        };

        // Set up wrappers for NPClass methods
        for (size_t i = 0; i < NP32Class::FunctionCount; ++i)
        {
            pInst->aStubs[i].chPush      = 0x68;
            pInst->aStubs[i].pvImm32bit  = pInst;
            pInst->aStubs[i].chCall      = 0xe8;
            pInst->aStubs[i].offRel32bit = (char*)implementedWrappers[i] - (char*)&pInst->aStubs[i].offRel32bit - 4;
            pInst->aStubs[i].chPopEcx    = 0x59;
            pInst->aStubs[i].chRet       = 0xc3;

            // point to a stub only if plugin provides a function, otherwise set it also to NULL
            pInst->newClass.functions[i] = pInst->pw32Class->functions[i] != NULL ? (PFN)&pInst->aStubs[i] : NULL;

            memset(pInst->aStubs[i].achMagic, 0xcc, sizeof(pInst->aStubs[i].achMagic));
        }

        // replace the class to be used
        aClass = (NPClass *)&pInst->newClass;
    }

    NPObject *object = pPlugin->pData->pNetscapeFuncsOS2->createobject(NP4XDOWN_NS_INSTANCE(), aClass);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave object=%x (refcnt=%d)", object, object ? object->referenceCount : 0);
    return object;
}


NPObject* NP32_LOADDS np4xDown_RetainObject(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPObject *obj)
{
    dprintff("enter - pPlugin=%p obj=%p (refcnt=%d)",
             pPlugin, obj, obj ? obj->referenceCount : 0);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPObject *object = pPlugin->pData->pNetscapeFuncsOS2->retainobject(obj);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave object=%x (refcnt=%d)", object, object ? object->referenceCount : 0);
    return object;
}


void NP32_LOADDS np4xDown_ReleaseObject(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPObject *obj)
{
    dprintff("enter - pPlugin=%p obj=%p (refcnt=%d)",
             pPlugin, obj, obj ? obj->referenceCount : 0);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pPlugin->pData->pNetscapeFuncsOS2->releaseobject(obj);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave");
    return;
}


bool NP32_LOADDS np4xDown_Invoke(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPObject* obj, NPIdentifier methodName, const NP32Variant *args, uint32_t argCount, NP32Variant *result)
{
    dprintff("enter - pPlugin=%p instance=%p obj=%p methodName=%p args=%p argCount=%d result=%p",
             pPlugin, instance, obj, methodName, args, argCount, result);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NP4XDOWN_BEGIN_IN_NPVARIANTS(args, argCount);
    NP4XDOWN_BEGIN_OUT_NPVARIANT(result);

    bool rc = pPlugin->pData->pNetscapeFuncsOS2->invoke(NP4XDOWN_NS_INSTANCE(), obj, methodName, NP4XDOWN_USE_IN_NPVARIANTS(args), argCount, NP4XDOWN_USE_OUT_NPVARIANT(result));

    NP4XDOWN_END_OUT_NPVARIANT(result);
    NP4XDOWN_END_IN_NPVARIANTS(args);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}

bool NP32_LOADDS np4xDown_InvokeDefault(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPObject* obj, const NP32Variant *args, uint32_t argCount, NP32Variant *result)
{
    dprintff("enter - pPlugin=%p instance=%p obj=%p args=%p argCount=%d result=%p",
             pPlugin, instance, obj, args, argCount, result);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NP4XDOWN_BEGIN_IN_NPVARIANTS(args, argCount);
    NP4XDOWN_BEGIN_OUT_NPVARIANT(result);

    bool rc = pPlugin->pData->pNetscapeFuncsOS2->invokeDefault(NP4XDOWN_NS_INSTANCE(), obj, NP4XDOWN_USE_IN_NPVARIANTS(args), argCount, NP4XDOWN_USE_OUT_NPVARIANT(result));

    NP4XDOWN_END_OUT_NPVARIANT(result);
    NP4XDOWN_END_IN_NPVARIANTS(args);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


bool NP32_LOADDS np4xDown_Evaluate(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPObject *obj, NPString *script, NP32Variant *result)
{
    dprintff("enter - pPlugin=%p instance=%p obj=%p script=%p result=%p",
             pPlugin, instance, obj, script, result);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NP4XDOWN_BEGIN_OUT_NPVARIANT(result);

    bool rc = pPlugin->pData->pNetscapeFuncsOS2->evaluate(NP4XDOWN_NS_INSTANCE(), obj, script, NP4XDOWN_USE_OUT_NPVARIANT(result));

    NP4XDOWN_END_OUT_NPVARIANT(result);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


bool NP32_LOADDS np4xDown_GetProperty(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPObject *obj, NPIdentifier propertyName, NP32Variant *result)
{
    dprintff("enter - pPlugin=%p instance=%p obj=%p propertyName=%p result=%p",
             pPlugin, instance, obj, propertyName, result);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NP4XDOWN_BEGIN_OUT_NPVARIANT(result);

    bool rc = pPlugin->pData->pNetscapeFuncsOS2->getproperty(NP4XDOWN_NS_INSTANCE(), obj, propertyName, NP4XDOWN_USE_OUT_NPVARIANT(result));
    if (rc)
        dprintffNPVariant(NP4XDOWN_USE_OUT_NPVARIANT(result));

    NP4XDOWN_END_OUT_NPVARIANT(result);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


bool NP32_LOADDS np4xDown_SetProperty(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPObject *obj, NPIdentifier propertyName, const NP32Variant *value)
{
    dprintff("enter - pPlugin=%p instance=%p obj=%p propertyName=%p value=%p",
             pPlugin, instance, obj, propertyName, value);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NP4XDOWN_BEGIN_IN_NPVARIANT(value);

    dprintffNPVariant(NP4XDOWN_USE_IN_NPVARIANT(value));

    bool rc = pPlugin->pData->pNetscapeFuncsOS2->setproperty(NP4XDOWN_NS_INSTANCE(), obj, propertyName, NP4XDOWN_USE_IN_NPVARIANT(value));

    NP4XDOWN_END_IN_NPVARIANT(value);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


bool NP32_LOADDS np4xDown_RemoveProperty(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPObject *obj, NPIdentifier propertyName)
{
    dprintff("enter - pPlugin=%p instance=%p obj=%p propertyName=%p",
             pPlugin, instance, obj, propertyName);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    bool rc = pPlugin->pData->pNetscapeFuncsOS2->removeproperty(NP4XDOWN_NS_INSTANCE(), obj, propertyName);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


bool NP32_LOADDS np4xDown_HasProperty(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPObject *obj, NPIdentifier propertyName)
{
    dprintff("enter - pPlugin=%p instance=%p obj=%p propertyName=%p",
             pPlugin, instance, obj, propertyName);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    bool rc = pPlugin->pData->pNetscapeFuncsOS2->hasproperty(NP4XDOWN_NS_INSTANCE(), obj, propertyName);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


bool NP32_LOADDS np4xDown_HasMethod(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPObject *obj, NPIdentifier propertyName)
{
    dprintff("enter - pPlugin=%p instance=%p obj=%p propertyName=%p",
             pPlugin, instance, obj, propertyName);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    bool rc = pPlugin->pData->pNetscapeFuncsOS2->hasmethod(NP4XDOWN_NS_INSTANCE(), obj, propertyName);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave rc=%s", rc ? "true" : "false");
    return rc;
}


void NP32_LOADDS np4xDown_ReleaseVariantValue(NPOdinPluginWrapper *pPlugin, void *pvCaller, NP32Variant *variant)
{
    dprintff("enter - pPlugin=%p variant=%p",
             pPlugin, variant);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NP4XDOWN_BEGIN_OUT_NPVARIANT(variant);

    dprintffNPVariant(NP4XDOWN_USE_OUT_NPVARIANT(variant));

    pPlugin->pData->pNetscapeFuncsOS2->releasevariantvalue(NP4XDOWN_USE_OUT_NPVARIANT(variant));

    // makes no sense to copy it back since it should all be deallocated

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave");
    return;
}


void NP32_LOADDS np4xDown_SetException(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPObject *obj, const NPUTF8 *message)
{
    dprintff("enter - pPlugin=%p obj=%p message=%s",
             pPlugin, obj, message);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pPlugin->pData->pNetscapeFuncsOS2->setexception(obj, message);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave");
    return;
}


void NP32_LOADDS np4xDown_PushPopupsEnabledState(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, NPBool enabled)
{
    dprintff("enter - pPlugin=%p instance=%p enabled=%d",
             pPlugin, instance, enabled);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pPlugin->pData->pNetscapeFuncsOS2->pushpopupsenabledstate(NP4XDOWN_NS_INSTANCE(), enabled);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave");
    return;
}


void NP32_LOADDS np4xDown_PopPopupsEnabledState(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance)
{
    dprintff("enter - pPlugin=%p instance=%p",
             pPlugin, instance);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pPlugin->pData->pNetscapeFuncsOS2->poppopupsenabledstate(NP4XDOWN_NS_INSTANCE());

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave");
    return;
}


void NP32_LOADDS np4xDown_URLRedirectResponse(NPOdinPluginWrapper *pPlugin, void *pvCaller, NPP instance, void* notifyData, NPBool allow)
{
    dprintff("enter - pPlugin=%p instance=%p notifyData=%p allow=%d",
             pPlugin, instance, allow);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pPlugin->pData->pNetscapeFuncsOS2->urlredirectresponse(NP4XDOWN_NS_INSTANCE(), notifyData, allow);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintff("leave");
    return;
}


/**
 * Stub for not implemented functions.
 *
 * @param ordinal   Ordinal function number.
 */
void NP32_LOADDS np4xDown_NotImplementedStub(int ordinal)
{
    dprintff("enter - ordinal=%d", ordinal);

    showMissingOrdinalMsg(ordinal, "Flash plugin", "browser");

    dprintff("Terminating the application.");
    exit(333);
    return;
}


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// Generic wrapping stuff.
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

/**
 * Called once when the browser initializes the plugin module after loading it. This is done either
 * through NP_GetEntryPoints or NP_Initialize callbacks. Data allocated in this function must be
 * freed in WrapperDataDestoy().
 */
static BOOL PluginDataInit(PNPODINWRAPPER pPlugin)
{
    /* Check if already inited */
    if (pPlugin->pData)
        return TRUE;

    /* Call generic lazy init */
    if (!pPlugin->hmodPlugin && !npGenericLazyInit(pPlugin))
        return FALSE;

    pPlugin->pData = new NPOdinPluginWrapperData;
    if (!pPlugin->pData)
    {
        dprintff("Out of memory!");
        return FALSE;
    }

    memset(pPlugin->pData, 0, sizeof(NPOdinPluginWrapperData));

    return TRUE;
}

/**
 * Called once when the browser destroys the plugin module before before unloading it. This is done
 * through the NP_Shutdown callback. Must free all resources allocated in WrapperDataInit().
 */
static void PluginDataDestoy(PNPODINWRAPPER pPlugin)
{
    /* Check if already destroyed */
    if (!pPlugin->pData)
        return;

    /* Free stuff allocated in NP_GetEntryPoints/NP_Initialize */
    if (pPlugin->pData->pPluginStubsOS2)
        free(pPlugin->pData->pPluginStubsOS2);
    if (pPlugin->pData->pPluginFuncsW32)
        free(pPlugin->pData->pPluginFuncsW32);
    if (pPlugin->pData->pNetscapeStubsW32)
        free(pPlugin->pData->pNetscapeStubsW32);
    if (pPlugin->pData->pNetscapeFuncsW32)
        free(pPlugin->pData->pNetscapeFuncsW32);

    free(pPlugin->pData);
    pPlugin->pData = NULL;

    return;
}

/**
 * Called by the browser to fill in the plugin function table (retrieve implemented plugin
 * callbacks).
 */
NPError OSCALL npGenericNP_GetEntryPoints(NPPluginFuncs *pCallbacks, PNPODINWRAPPER pPlugin)
{
    dprintff("enter - pCallbacks=%p pPlugin=%p", pCallbacks, pPlugin);
    DPRINTF_STR(pPlugin->szPluginDllName);
    NPError rc;

    /*
     * Lazy Init.
     */
    if (    !pPlugin->pData
        &&  !PluginDataInit(pPlugin))
    {
        dprintff("WrapperDataInit() failed, returning NPERR_INVALID_PLUGIN_ERROR");
        NPXP_ASSERT_OS2FS();
        return NPERR_INVALID_PLUGIN_ERROR;
    }

    /*
     * Is the entrypoint present?
     */
    if (!pPlugin->pfnW32NP_GetEntryPoints)
    {
        dprintff("pfnW32NP_GetEntryPoints is NULL, returning NPERR_INVALID_PLUGIN_ERROR");
        NPXP_ASSERT_OS2FS();
        return NPERR_INVALID_PLUGIN_ERROR;
    }

    /*
     * Create wrappers for the function table:
     *
     *      Allocate.
     *      Call Win32 routine.
     *      Create stubs.
     */

    /* The number of functions the browser expects us to fill */
    size_t funcCnt = (pCallbacks->size - sizeof(NPPluginFuncs::size) - sizeof(NPPluginFuncs::version)) / sizeof(PFN);

    /* The size of the Win32 function table */
    size_t w32StructSize = sizeof(NP32PluginFuncs::size) + sizeof(NP32PluginFuncs::version) + funcCnt * sizeof(PFN);

    dprintff("pCallbacks->version=%d pCallbacks->size=%d funcCnt=%u w32StructSize=%u", pCallbacks->version, pCallbacks->size, funcCnt, w32StructSize);

    pPlugin->pData->pPluginStubsOS2 = (WrapperStub *)malloc(funcCnt * sizeof(WrapperStub));
    pPlugin->pData->pPluginFuncsW32 = (NP32PluginFuncs *)malloc(w32StructSize);

    if (!pPlugin->pData->pPluginStubsOS2 || !pPlugin->pData->pPluginStubsOS2)
    {
        dprintff("out of memory! Can't allocate wrapper!");
        if (pPlugin->pData->pPluginStubsOS2)
        {
            free(pPlugin->pData->pPluginStubsOS2);
            pPlugin->pData->pPluginStubsOS2 = NULL;
        }
        NPXP_ASSERT_OS2FS();
        return NPERR_OUT_OF_MEMORY_ERROR;
    }

    memset(pPlugin->pData->pPluginStubsOS2, 0, funcCnt * sizeof(WrapperStub));
    memset(pPlugin->pData->pPluginFuncsW32, 0, w32StructSize);

    NP32PluginFuncs *w32Funcs = pPlugin->pData->pPluginFuncsW32;

    /* Pass size/version info from the OS/2 struct to Win32 unchanged */
    w32Funcs->size = pCallbacks->size;
    w32Funcs->version = pCallbacks->version;

    /*
     * Call the real Win32 worker in Odin context.
     */
    unsigned ExceptionRegRec[2] = {0,0};
    USHORT selFSOld = pfnODIN_ThreadEnterOdinContext(&ExceptionRegRec[0], TRUE);
    rc = pPlugin->pfnW32NP_GetEntryPoints(w32Funcs);
    pfnODIN_ThreadLeaveOdinContext(&ExceptionRegRec[0], selFSOld);
    ExceptionRegRec[0] = ExceptionRegRec[1] = 0;
    if (!rc)
    {
        dprintff("Win32 NP_GetEntryPoints successful!");

        /* The beginning of the function table to fill for the browser */
        PFN *os2Funcs = (PFN *) (&pCallbacks->version + 1);

        /* Fill up the OS/2 function table with dummy stubs as flags (wrappers to supported
         * functions will overwrite them below and all dummy stubs will be replaced by a special
         * callback sequence) */
        for (size_t i = 0; i < funcCnt; ++i)
            os2Funcs[i] = (PFN)&np4xUp_NotImplementedStub;

        /* This is not a callback but instead some data pointer, pass it as is */
        pCallbacks->javaClass = w32Funcs->javaClass;

        /* Wrappers for functions we support */
        PFN wrappers[] =
        {
            (PFN)&np4xUp_New,
            (PFN)&np4xUp_Destroy,
            (PFN)&np4xUp_SetWindow,
            (PFN)&np4xUp_NewStream,
            (PFN)&np4xUp_DestroyStream,
            (PFN)&np4xUp_StreamAsFile,
            (PFN)&np4xUp_WriteReady,
            (PFN)&np4xUp_Write,
            (PFN)&np4xUp_Print,
            (PFN)&np4xUp_HandleEvent,
            (PFN)&np4xUp_URLNotify,
            NULL, // javaClass,
            (PFN)&np4xUp_GetValue,
            (PFN)&np4xUp_SetValue,
            (PFN)&np4xUp_GotFocus,
            (PFN)&np4xUp_LostFocus,
            (PFN)&np4xUp_URLRedirectNotify,
            (PFN)&np4xUp_ClearSiteData,
            (PFN)&np4xUp_GetSitesWithData,
        };

        enum { wrappersCnt = sizeof(wrappers) / sizeof(wrappers[0]) };

        dprintff("will create 'not-implemented' stubs for %d functions", funcCnt - wrappersCnt);

        WrapperStub *stubs = pPlugin->pData->pPluginStubsOS2;

        for (size_t i = 0; i < wrappersCnt; ++i)
        {
            if (wrappers[i] == NULL)
                continue;

            stubs[i].chPush      = 0x68;
            stubs[i].pvImm32bit  = pPlugin;
            stubs[i].chCall      = 0xe8;
            stubs[i].offRel32bit = (char*)wrappers[i] - (char*)&stubs[i].offRel32bit - 4;
            stubs[i].chPopEcx    = 0x59;
            stubs[i].chRet       = 0xc3;

            /* Point to the stub only if plugin provides a function, otherwise set it also to NULL */
            os2Funcs[i] = w32Funcs->functions[i] != NULL ? (PFN)&stubs[i] : NULL;

            memset(stubs[i].achMagic, 0xcc, sizeof(stubs[i].achMagic));
        }

        /* Set up stubs for unused functions */
        for (size_t i = 0; i < funcCnt; ++i)
        {
            if (os2Funcs[i] == (PFN)&np4xUp_NotImplementedStub)
            {
                stubs[i].chPush      = 0x68;
                stubs[i].pvImm32bit  = (void *)i;
                stubs[i].chCall      = 0xe8;
                stubs[i].offRel32bit = (char *)&np4xUp_NotImplementedStub - (char *)&stubs[i].offRel32bit - 4;
                stubs[i].chPopEcx    = 0x59;
                stubs[i].chRet       = 0xc3;

                os2Funcs[i] = (PFN)&stubs[i];

                memset(stubs[i].achMagic, 0xcc, sizeof(stubs[i].achMagic));
            }
        }
    }
    else
    {
        /*
         * It failed, complain and do cleanup!
         */
        dprintff("Win32 NP_GetEntryPoints failed with rc=%d", rc);
        free(pPlugin->pData->pPluginStubsOS2);
        free(pPlugin->pData->pPluginFuncsW32);
        pPlugin->pData->pPluginStubsOS2 = NULL;
        pPlugin->pData->pPluginFuncsW32 = NULL;
    }

    dprintff("leave rc=%x", rc);
    NPXP_ASSERT_OS2FS();
    return rc;
}


NPError OSCALL npGenericNP_Initialize(NPNetscapeFuncs *pFuncs, PNPODINWRAPPER pPlugin)
{
    dprintff("enter - pFuncs=%p pPlugin=%p", pFuncs, pPlugin);
    DPRINTF_STR(pPlugin->szPluginDllName);
    NPError rc;

    /*
     * Lazy Init.
     */
    if (    !pPlugin->pData
        &&  !PluginDataInit(pPlugin))
    {
        dprintff("WrapperDataInit() failed, returning NPERR_INVALID_PLUGIN_ERROR");
        NPXP_ASSERT_OS2FS();
        return NPERR_INVALID_PLUGIN_ERROR;
    }

    /*
     * Is the entrypoint present?
     */
    if (!pPlugin->pfnW32NP_Initialize)
    {
        dprintff("pfnW32NP_Initialize is NULL, returning NPERR_INVALID_PLUGIN_ERROR");
        NPXP_ASSERT_OS2FS();
        return NPERR_INVALID_PLUGIN_ERROR;
    }

    /*
     * Create wrapper for the function table.
     *      Allocate.
     *      Create stubs.
     *      Call Win32 routine.
     */

    /* The number of functions the browser presents to us */
    size_t funcCnt = (pFuncs->size - sizeof(NPNetscapeFuncs::size) - sizeof(NPNetscapeFuncs::version)) / sizeof(PFN);

    /* The size of the Win32 function table */
    size_t w32StructSize = sizeof(NP32NetscapeFuncs::size) + sizeof(NP32NetscapeFuncs::version) + funcCnt * sizeof(PFN);

    dprintff("pFuncs->version=%d pFuncs->size=%d funcCnt=%u w32StructSize=%u", pFuncs->version, pFuncs->size, funcCnt, w32StructSize);

    pPlugin->pData->pNetscapeStubsW32 = (WrapperStub *)malloc(funcCnt * sizeof(WrapperStub));
    pPlugin->pData->pNetscapeFuncsW32 = (NP32NetscapeFuncs *)malloc(w32StructSize);

    if (!pPlugin->pData->pNetscapeStubsW32 || !pPlugin->pData->pNetscapeFuncsW32)
    {
        dprintff("out of memory! Can't allocate wrapper!");
        if (pPlugin->pData->pNetscapeStubsW32)
        {
            free(pPlugin->pData->pNetscapeStubsW32);
            pPlugin->pData->pNetscapeStubsW32 = NULL;
        }
        NPXP_ASSERT_OS2FS();
        return NPERR_OUT_OF_MEMORY_ERROR;
    }

    memset(pPlugin->pData->pNetscapeStubsW32, 0, funcCnt * sizeof(WrapperStub));
    memset(pPlugin->pData->pNetscapeFuncsW32, 0, w32StructSize);

    /* Memorize the original OS/2 browser function table */
    pPlugin->pData->pNetscapeFuncsOS2 = pFuncs;

    NP32NetscapeFuncs *w32Funcs = pPlugin->pData->pNetscapeFuncsW32;

    /* Pass size/version info from the OS/2 struct to Win32 unchanged */
    w32Funcs->size = pFuncs->size;
    w32Funcs->version = pFuncs->version;

    /* The beginning of the function table to wrap for the plugin */
    PFN *os2Funcs = (PFN *) (&pFuncs->version + 1);

    /* fill up the Win32 function table with dummy stubs as flags (wrappers to supported functions
     * will overwrite them below and all dummy stubs will be replaced by a special callback
     * sequence) */
    for (size_t i = 0; i < funcCnt; ++i)
        w32Funcs->functions[i] = (PFN)&np4xDown_NotImplementedStub;

    /* Wrappers to functions we support */
    PFN wrappers[] =
    {
        (PFN)&np4xDown_GetURL,
        (PFN)&np4xDown_PostURL,
        (PFN)&np4xDown_RequestRead,
        (PFN)&np4xDown_NewStream,
        (PFN)&np4xDown_Write,
        (PFN)&np4xDown_DestroyStream,
        (PFN)&np4xDown_Status,
        (PFN)&np4xDown_UserAgent,
        (PFN)&np4xDown_MemAlloc,
        (PFN)&np4xDown_MemFree,
        (PFN)&np4xDown_MemFlush,
        (PFN)&np4xDown_ReloadPlugins,
        (PFN)&np4xDown_GetJavaEnv,
        (PFN)&np4xDown_GetJavaPeer,
        (PFN)&np4xDown_GetURLNotify,
        (PFN)&np4xDown_PostURLNotify,
        (PFN)&np4xDown_GetValue,
        (PFN)&np4xDown_SetValue,
        (PFN)&np4xDown_InvalidateRect,
        (PFN)&np4xDown_InvalidateRegion,
        (PFN)&np4xDown_ForceRedraw,
        (PFN)&np4xDown_GetStringIdentifier,
        (PFN)&np4xDown_GetStringIdentifiers,
        (PFN)&np4xDown_GetIntIdentifier,
        (PFN)&np4xDown_IdentifierIsString,
        (PFN)&np4xDown_UTF8FromIdentifier,
        (PFN)&np4xDown_IntFromIdentifier,
        (PFN)&np4xDown_CreateObject,
        (PFN)&np4xDown_RetainObject,
        (PFN)&np4xDown_ReleaseObject,
        (PFN)&np4xDown_Invoke,
        (PFN)&np4xDown_InvokeDefault,
        (PFN)&np4xDown_Evaluate,
        (PFN)&np4xDown_GetProperty,
        (PFN)&np4xDown_SetProperty,
        (PFN)&np4xDown_RemoveProperty,
        (PFN)&np4xDown_HasProperty,
        (PFN)&np4xDown_HasMethod,
        (PFN)&np4xDown_ReleaseVariantValue,
        (PFN)&np4xDown_SetException,
        (PFN)&np4xDown_PushPopupsEnabledState,
        (PFN)&np4xDown_PopPopupsEnabledState,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        (PFN)&np4xDown_URLRedirectResponse,
    };

    enum { wrappersCnt = sizeof(wrappers) / sizeof(wrappers[0]) };

    dprintff("will create 'not-implemented stubs' for %d functions", funcCnt - wrappersCnt);

    WrapperStub *stubs = pPlugin->pData->pNetscapeStubsW32;

    for (size_t i = 0; i < wrappersCnt; ++i)
    {
        if (wrappers[i] == NULL)
            continue;

        stubs[i].chPush      = 0x68;
        stubs[i].pvImm32bit  = pPlugin;
        stubs[i].chCall      = 0xe8;
        stubs[i].offRel32bit = (char *)wrappers[i] - (char *)&stubs[i].offRel32bit - 4;
        stubs[i].chPopEcx    = 0x59;
        stubs[i].chRet       = 0xc3;

        /* Point to a stub only if browser provides a function, otherwise set it also to NULL */
        w32Funcs->functions[i] = os2Funcs[i] != NULL ? (PFN)&stubs[i] : NULL;

        memset(stubs[i].achMagic, 0xcc, sizeof(stubs[i].achMagic));
    }

    /* Set up stubs for unused functions */
    for (size_t i = 0; i < funcCnt; ++i)
    {
        if (w32Funcs->functions[i] == (PFN)&np4xDown_NotImplementedStub)
        {
            stubs[i].chPush      = 0x68;
            stubs[i].pvImm32bit  = (void *)i;
            stubs[i].chCall      = 0xe8;
            stubs[i].offRel32bit = (char *)&np4xDown_NotImplementedStub - (char *)&stubs[i].offRel32bit - 4;
            stubs[i].chPopEcx    = 0x59;
            stubs[i].chRet       = 0xc3;

            w32Funcs->functions[i] = (PFN)&stubs[i];

            memset(stubs[i].achMagic, 0xcc, sizeof(stubs[i].achMagic));
        }
    }

    /*
     * Call the real Win32 worker in Odin context.
     */
    unsigned ExceptionRegRec[2] = {0,0};
    USHORT selFSOld = pfnODIN_ThreadEnterOdinContext(&ExceptionRegRec[0], TRUE);
    rc = pPlugin->pfnW32NP_Initialize(w32Funcs);
    pfnODIN_ThreadLeaveOdinContext(&ExceptionRegRec[0], selFSOld);
    ExceptionRegRec[0] = ExceptionRegRec[1] = 0;
    if (!rc)
    {
        dprintff("Win32 NP_Initialize successful!");
    }
    else
    {
        /*
         * It failed, cleanup the wrapper.
         */
        dprintff("Win32 NP_Initialize failed with rc=%x", rc);
        free(pPlugin->pData->pNetscapeStubsW32);
        free(pPlugin->pData->pNetscapeFuncsW32);
        pPlugin->pData->pNetscapeStubsW32 = NULL;
        pPlugin->pData->pNetscapeFuncsW32 = NULL;
    }

    dprintff("leave rc=%x", rc);
    NPXP_ASSERT_OS2FS();
    return rc;
}


NPError OSCALL npGenericNP_Shutdown(PNPODINWRAPPER pPlugin)
{
    dprintff("enter - pPlugin=%p", pPlugin);
    DPRINTF_STR(pPlugin->szPluginDllName);
    NPError rc;


    /*
     * Check for Init.
     */
    if (!pPlugin->pData)
    {
        dprintff("called before NP_Initialize, returning NPERR_INVALID_PLUGIN_ERROR");
        NPXP_ASSERT_OS2FS();
        return NPERR_INVALID_PLUGIN_ERROR;
    }

    /*
     * Is the entrypoint present?
     */
    if (!pPlugin->pfnW32NP_Shutdown)
    {
        dprintff("pfnW32NP_Shutdown is NULL, returning NPERR_INVALID_PLUGIN_ERROR");
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

    /*
     * Destroy own data.
     */
    PluginDataDestoy(pPlugin);

    dprintff("leave rc=%x", rc);
    NPXP_ASSERT_OS2FS();
    return rc;
}


/* Unix only? */
NPError OSCALL npGenericNP_GetValue(NPP future, NPPVariable variable, void *value, PNPODINWRAPPER pPlugin)
{
    dprintff("enter - future=%p variable=%d value=%p pPlugin=%p", future, variable, value, pPlugin);
    DPRINTF_STR(pPlugin->szPluginDllName);
    NPError rc;

    /*
     * Generic Lazy Init.
     */
    if (    !pPlugin->hmodPlugin
        &&  !npGenericLazyInit(pPlugin))
    {
        dprintff("npGenericLazyInit() failed, returning NPERR_INVALID_PLUGIN_ERROR");
        NPXP_ASSERT_OS2FS();
        return NPERR_INVALID_PLUGIN_ERROR;
    }

    /*
     * Is the entrypoint present?
     */
    if (!pPlugin->pfnW32NP_GetValue)
    {
        dprintff("pfnW32NP_GetValue is NULL, returning NPERR_INVALID_PLUGIN_ERROR");
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

    dprintff("leave rc=%x", rc);
    NPXP_ASSERT_OS2FS();
    return rc;
}


char * OSCALL npGenericNP_GetMIMEDescription(PNPODINWRAPPER pPlugin)
{
    dprintff("enter - pPlugin=%p", pPlugin);
    DPRINTF_STR(pPlugin->szPluginDllName);
    char *pszRc;


    /*
     * Generic Lazy Init.
     */
    if (    !pPlugin->hmodPlugin
        &&  !npGenericLazyInit(pPlugin))
    {
        dprintff("npGenericLazyInit() failed, returning NULL");
        NPXP_ASSERT_OS2FS();
        return NULL;
    }

    /*
     * Is the entrypoint present?
     */
    if (!pPlugin->pfnW32NP_GetMIMEDescription)
    {
        dprintff("pfnW32NP_GetMIMEDescription is NULL, returning NULL");
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
    dprintff("leave pszRc=%x", pszRc);
    NPXP_ASSERT_OS2FS();
    return pszRc;
}

