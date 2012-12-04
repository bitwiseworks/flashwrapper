/* $Id: wrap_NS4x.cpp,v 1.12 2004/03/10 15:36:41 bird Exp $
 *
 * Netscape v4.x Plugin interface.
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
        if (npGetFS() != (USHORT)(unsigned)&DOS32TIB)                               \
        {                                                                           \
            dprintf(("%s: fs is wrong (%x) !!!", szFunction, npGetFS()));           \
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
    }                                                                               \
    dprintf(("%s: w32_instance=%p", szFunction, pInst ? &pInst->w32 : NULL));


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
        if ((char*)instance - __offsetof(NPLUGININSTANCE, w32) != (char*)pInst)     \
            dprintf(("%s: Bogus Instance Pointer pInst=%p, instance=%p!!!\n",       \
                     szFunction, pInst, instance));                                 \
    }                                                                               \
    dprintf(("%s: os2_instance=%p", szFunction, pInst ? pInst->pOrgInstance : NULL));

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

/** Enter odin context from OS/2 netscape/mozilla class callback context. */
#define NP4XCLASS_SANITY_CHECK(retval) \
    if (npobj->_class != (NPClass *)&pInst->newClass) { \
        dprintf(("%s: ERROR: npobj->_class must be %p", szFunction, &pInst->newClass)); \
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
        dprintf(("%s: %s={%08x,%04x,%04x,%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x} %s (%p)",   \
                szFunction, #refID, (refID).m0, (refID).m1, (refID).m2, (refID).m3[0], (refID).m3[1],   \
                (refID).m3[2], (refID).m3[3], (refID).m3[4], (refID).m3[5], (refID).m3[6], (refID).m3[7], \
                getIIDCIDName(refID), &(refID)));                                             \
    else                                                                                      \
        dprintf(("%s: %s=%p (illegal pointer!!!)", szFunction, #refID, &(refID)))


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
            NPError     (* NP32_LOADDS pfnGetURL)(NPP instance, const char* url, const char* window);
            NPError     (* NP32_LOADDS pfnPostURL)(NPP instance, const char* url, const char* window, uint32_t len, const char* buf, NPBool file);
            NPError     (* NP32_LOADDS pfnRequestRead)(NPStream* stream, NPByteRange* rangeList);
            NPError     (* NP32_LOADDS pfnNewStream)(NPP instance, NPMIMEType type, const char* window, NPStream** stream);
            int32_t     (* NP32_LOADDS pfnWrite)(NPP instance, NPStream* stream, int32_t len, void* buffer);
            NPError     (* NP32_LOADDS pfnDestroyStream)(NPP instance, NPStream* stream, NPReason reason);
            void        (* NP32_LOADDS pfnStatus)(NPP instance, const char* message);
            const char* (* NP32_LOADDS pfnUserAgent)(NPP instance);
            void*       (* NP32_LOADDS pfnMemAlloc)(uint32_t size);
            void        (* NP32_LOADDS pfnMemFree)(void* ptr);
            uint32_t    (* NP32_LOADDS pfnMemFlush)(uint32_t size);
            void        (* NP32_LOADDS pfnReloadPlugins)(NPBool reloadPages);
            void*       (* NP32_LOADDS pfnGetJavaEnv)(void);
            void*       (* NP32_LOADDS pfnGetJavaPeer)(NPP instance);
            NPError     (* NP32_LOADDS pfnGetURLNotify)(NPP instance, const char* url, const char* window, void* notifyData);
            NPError     (* NP32_LOADDS pfnPostURLNotify)(NPP instance, const char* url, const char* window, uint32_t len, const char* buf, NPBool file, void* notifyData);
            NPError     (* NP32_LOADDS pfnGetValue)(NPP instance, NPNVariable variable, void *ret_alue);
            NPError     (* NP32_LOADDS pfnSetValue)(NPP instance, NPPVariable variable, void *ret_alue);
            void        (* NP32_LOADDS pfnInvalidateRect)(NPP instance, NPRect *rect);
            void        (* NP32_LOADDS pfnInvalidateRegion)(NPP instance, NPRegion region);
            void        (* NP32_LOADDS pfnForceRedraw)(NPP instance);

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
    /** Pointer to the next wrapper in the chain. */
    struct _NetscapeFuncsWrapper * pNext;

    /** Pointer to the original struct. (do we need to keep this around?) */
    NPNetscapeFuncs *   pNative;

    /** padding for 16byte code aligment. */
    char                auPadding[8];

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
    NP32NetscapeFuncs *w32;

} NETSCAPEFUNCSWRAPPER,  *PNETSCAPEFUNCSWRAPPER;


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

} NPLUGININSTANCE, *PNPLUGININSTANCE;


#pragma pack()


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


#ifdef DEBUG
static void dprintfNPVariant(const char *text, const NPVariant *value)
{
    if (!value)
    {
        dprintf(("%s: WARNING: NULL NPVariant pointer!", text));
        return;
    }

    switch (value->type)
    {
        case NPVariantType_Void:
            dprintf(("%s: void", text));
            break;
        case NPVariantType_Null:
            dprintf(("%s: null", text));
            break;
        case NPVariantType_Bool:
            dprintf(("%s: bool: %s", text, value->value.boolValue ? "true" : "false"));
            break;
        case NPVariantType_Int32:
            dprintf(("%s: integer: %d", text, value->value.intValue));
            break;
        case NPVariantType_Double:
            dprintf(("%s: double: %f", text, value->value.doubleValue));
            break;
        case NPVariantType_String:
            dprintf(("%s: string (%u): %s", text, value->value.stringValue.UTF8Length, value->value.stringValue.UTF8Characters));
            break;
        case NPVariantType_Object:
            dprintf(("%s: object: %p", text, value->value.objectValue));
            break;
    }
}
#else
#define dprintfNPVariant(a, b) do {} while (0)
#endif

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


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// UP wrappers (stuff that is presented to netscape/mozilla)
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//


NPObject *np4xClass_AllocateFunction(PNPLUGININSTANCE pInst, void *pvCaller, NPP instance, NPClass *aClass)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pInst=%p instance=%p aClass=%p", szFunction, pInst, instance, aClass));
    dprintf(("%s: pw32Class %p", szFunction, pInst->pw32Class));

    // sanity
    if (aClass != (NPClass *)&pInst->newClass)
    {
        dprintf(("%s: ERROR: aClass must be %p", szFunction, &pInst->newClass));
        return NULL;
    }

    NP4XUP_ENTER_ODIN(FALSE);

    NPObject *object = pInst->pw32Class->pfnAllocateFunction(NP4XUP_W32_INSTANCE(), &pInst->newClass);

    NP4XUP_LEAVE_ODIN(FALSE);

    if (object)
        object->_class = (NPClass *)&pInst->newClass;

    dprintf(("%s: leave object=%p", szFunction, object));
    return object;
}


void np4xClass_DeallocateFunction(PNPLUGININSTANCE pInst, void *pvCaller, NPObject *npobj)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pInst=%p npobj=%p", szFunction, pInst, npobj));

    NP4XCLASS_SANITY_CHECK((void)0);

    NP4XCLASS_ENTER_ODIN(FALSE);

    pInst->pw32Class->pfnDeallocateFunction(npobj);

    // Must not use NP4XCLASS_LEAVE_ODIN() since it would try to modify the just freed npobj
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintf(("%s: leave", szFunction));
    return;
}


void np4xClass_InvalidateFunction(PNPLUGININSTANCE pInst, void *pvCaller, NPObject *npobj)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pInst=%p npobj=%p", szFunction, pInst, npobj));

    NP4XCLASS_SANITY_CHECK((void)0);

    NP4XCLASS_ENTER_ODIN(FALSE);

    pInst->pw32Class->pfnInvalidateFunction(npobj);

    NP4XCLASS_LEAVE_ODIN(FALSE);

    dprintf(("%s: leave", szFunction));
    return;
}


bool np4xClass_HasMethodFunction(PNPLUGININSTANCE pInst, void *pvCaller, NPObject *npobj, NPIdentifier name)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pInst=%p npobj=%p name=%p", szFunction, pInst, npobj, name));

    NP4XCLASS_SANITY_CHECK(false);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnHasMethodFunction(npobj, name);

    NP4XCLASS_LEAVE_ODIN(FALSE);

    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


bool np4xClass_InvokeFunction(PNPLUGININSTANCE pInst, void *pvCaller, NPObject *npobj, NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pInst=%p npobj=%p name=%p args=%p argCount=%d result=%p", szFunction, pInst, npobj, name, args, argCount, result));

    NP4XCLASS_SANITY_CHECK(false);

    NP4XUP_BEGIN_IN_NPVARIANTS(args, argCount);
    NP4XUP_BEGIN_OUT_NPVARIANT(result);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnInvokeFunction(npobj, name, NP4XUP_USE_IN_NPVARIANTS(args), argCount, NP4XUP_USE_IN_NPVARIANT(result));

    NP4XCLASS_LEAVE_ODIN(FALSE);

    NP4XUP_END_OUT_NPVARIANT(result);
    NP4XUP_END_IN_NPVARIANTS(args);

    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


bool np4xClass_InvokeDefaultFunction(PNPLUGININSTANCE pInst, void *pvCaller, NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pInst=%p npobj=%p args=%p argCount=%d result=%p", szFunction, pInst, npobj, args, argCount, result));

    NP4XCLASS_SANITY_CHECK(false);

    NP4XUP_BEGIN_IN_NPVARIANTS(args, argCount);
    NP4XUP_BEGIN_OUT_NPVARIANT(result);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnInvokeDefaultFunction(npobj, NP4XUP_USE_IN_NPVARIANTS(args), argCount, NP4XUP_USE_IN_NPVARIANT(result));

    NP4XCLASS_LEAVE_ODIN(FALSE);

    NP4XUP_END_OUT_NPVARIANT(result);
    NP4XUP_END_IN_NPVARIANTS(args);

    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


bool np4xClass_HasPropertyFunction(PNPLUGININSTANCE pInst, void *pvCaller, NPObject *npobj, NPIdentifier name)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pInst=%p npobj=%p name=%p", szFunction, pInst, npobj, name));

    NP4XCLASS_SANITY_CHECK(false);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnHasPropertyFunction(npobj, name);

    NP4XCLASS_LEAVE_ODIN(FALSE);

    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


bool np4xClass_GetPropertyFunction(PNPLUGININSTANCE pInst, void *pvCaller, NPObject *npobj, NPIdentifier name, NPVariant *result)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pInst=%p npobj=%p name=%p result=%p", szFunction, pInst, npobj, name, result));

    NP4XCLASS_SANITY_CHECK(false);

    NP4XUP_BEGIN_OUT_NPVARIANT(result);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnGetPropertyFunction(npobj, name, NP4XUP_USE_OUT_NPVARIANT(result));

    NP4XCLASS_LEAVE_ODIN(FALSE);

    NP4XUP_END_OUT_NPVARIANT(result);

    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


bool np4xClass_SetPropertyFunction(PNPLUGININSTANCE pInst, void *pvCaller, NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pInst=%p npobj=%p name=%p value=%p", szFunction, pInst, npobj, name, value));

    NP4XCLASS_SANITY_CHECK(false);

    NP4XUP_BEGIN_IN_NPVARIANT(value);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnSetPropertyFunction(npobj, name, NP4XUP_USE_IN_NPVARIANT(value));

    NP4XCLASS_LEAVE_ODIN(FALSE);

    NP4XUP_END_IN_NPVARIANT(value);

    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


bool np4xClass_RemovePropertyFunction(PNPLUGININSTANCE pInst, void *pvCaller, NPObject *npobj, NPIdentifier name)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pInst=%p npobj=%p name=%p", szFunction, pInst, npobj, name));

    NP4XCLASS_SANITY_CHECK(false);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnHasPropertyFunction(npobj, name);

    NP4XCLASS_LEAVE_ODIN(FALSE);

    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


bool np4xClass_EnumerationFunction(PNPLUGININSTANCE pInst, void *pvCaller, NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pInst=%p npobj=%p value=%p count=%p", szFunction, pInst, npobj, value, count));

    NP4XCLASS_SANITY_CHECK(false);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnEnumerationFunction(npobj, value, count);

    NP4XCLASS_LEAVE_ODIN(FALSE);

    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


bool np4xClass_ConstructFunction(PNPLUGININSTANCE pInst, void *pvCaller, NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pInst=%p npobj=%p args=%p argCount=%d result=%p", szFunction, pInst, npobj, args, argCount, result));

    NP4XCLASS_SANITY_CHECK(false);

    NP4XUP_BEGIN_IN_NPVARIANTS(args, argCount);
    NP4XUP_BEGIN_OUT_NPVARIANT(result);

    NP4XCLASS_ENTER_ODIN(FALSE);

    bool rc = pInst->pw32Class->pfnConstructFunction(npobj, NP4XUP_USE_IN_NPVARIANTS(args), argCount, NP4XUP_USE_IN_NPVARIANT(result));

    NP4XCLASS_LEAVE_ODIN(FALSE);

    NP4XUP_END_OUT_NPVARIANT(result);
    NP4XUP_END_IN_NPVARIANTS(args);

    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// UP wrappers (stuff that is presented to netscape/mozilla)
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//


NPError NP_LOADDS np4xUp_New(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPMIMEType pluginType, NPP instance,
                             uint16_t mode, int16_t argc, char* argn[],
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
    pInst->pw32Class = NULL;
    instance->pdata = pInst;

    /*
     * Let the plugin initialize it self.
     */
    dprintf(("pfnNew enter"));
    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = pWrapper->w32->pfnNew(pluginType, NP4XUP_W32_INSTANCE(), mode, argc, argn, argv, saved);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf(("pfnNew leave"));
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

    dprintf(("pfnDestroy enter"));
    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = pWrapper->w32->pfnDestroy(NP4XUP_W32_INSTANCE(), save);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf(("pfnDestroy leave"));

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
    dprintf(("pfnSetWindow enter. address %08X", pWrapper->w32->pfnSetWindow));
    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = 1;
    rc = pWrapper->w32->pfnSetWindow(NP4XUP_W32_INSTANCE(), pWindow);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf(("pfnSetWindow leave"));
    #if 0
    /*
     * Fake a handle even call for WM_PAINT.
     */
    if (window->type == 2)
    {
        extern int16_t   NP_LOADDS np4xUp_HandleEvent(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, void* event);
        NPEvent event;
        event.event = WM_PAINT;
        event.wParam = (uint32_t)window->window;
        event.lParam = (uint32_t)&window->x; //???
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
                                   uint16_t* stype)
{
    static const char szFunction[] = "np4xUp_NewStream";
    dprintf(("%s: enter - pWrapper=%p instance=%p type=%p stream=%p seekable=%d stype=%p",
             szFunction, pWrapper, instance, type, stream, seekable, stype));
    DPRINTF_STR(type);
    DPRINTF_STREAM(stream);
    NP4XUP_INSTANCE(FALSE);

    NP4XUP_ENTER_ODIN(FALSE);
    dprintf(("pfnNewStream enter"));
    NPError rc = pWrapper->w32->pfnNewStream(NP4XUP_W32_INSTANCE(), type, stream, seekable, stype);
    dprintf(("pfnNewStream leave"));
    NP4XUP_LEAVE_ODIN(FALSE);

    if (!rc)
        DPRINTF_STREAM(stream);

    dprintf(("%s: leave rc=%d *stype=%d", szFunction, rc, *stype));
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
    dprintf(("pfnDestroyStream enter"));
    NPError rc = pWrapper->w32->pfnDestroyStream(NP4XUP_W32_INSTANCE(), stream, reason);
    dprintf(("pfnDestroyStream leave"));
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


int32_t NP_LOADDS np4xUp_WriteReady(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPStream* stream)
{
    static const char szFunction[] = "np4xUp_WriteReady";
    dprintf(("%s: enter - pWrapper=%p instance=%p stream=%p",
             szFunction, pWrapper, instance, stream));
    DPRINTF_STREAM(stream);
    NP4XUP_INSTANCE(FALSE);

    dprintf(("pfnWriteReady enter"));
    NP4XUP_ENTER_ODIN(FALSE);
    int32_t rc = pWrapper->w32->pfnWriteReady(NP4XUP_W32_INSTANCE(), stream);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf(("pfnWriteReady leave"));

    DPRINTF_STREAM(stream);
    dprintf(("%s: leave rc=%i", szFunction, rc));
    return rc;
}


#define PRINTABLE_CHAR(ch) ((ch >= 32 && ch <= 127) ? ch : '.')

int32_t NP_LOADDS np4xUp_Write(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPStream* stream, int32_t offset,
                               int32_t len, void* buffer)
{
    static const char szFunction[] = "np4xUp_Write";
    dprintf(("%s: enter - pWrapper=%p instance=%p stream=%p offset=%d len=%d buffer=%p",
             szFunction, pWrapper, instance, stream, offset, len, buffer));
    DPRINTF_STREAM(stream);
    NP4XUP_INSTANCE(FALSE);
#ifdef DEBUG
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
        dprintf(("%s: first %d bytes of buffer:\n%s", szFunction, b_total, str));
    }
#endif
    dprintf(("pfnWrite enter"));
    NP4XUP_ENTER_ODIN(FALSE);
    int32_t rc = pWrapper->w32->pfnWrite(NP4XUP_W32_INSTANCE(), stream, offset, len, buffer);
    NP4XUP_LEAVE_ODIN(FALSE);
    dprintf(("pfnWrite leave"));
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
    dprintf(("pfnStreamAsFile enter"));
    pWrapper->w32->pfnStreamAsFile(NP4XUP_W32_INSTANCE(), stream, fname);
    dprintf(("pfnStreamAsFile leave"));
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
        pWrapper->w32->pfnPrint(NP4XUP_W32_INSTANCE(), platformPrint);
    }
    else
    {
        /*
         * Complex stuff, which means converting a HPS and perhaps a HWND.
         */
#if 0
        ReleaseInt3(0x44440001,0x44440001,0x44440001);
        pWrapper->w32->pfnPrint(NP4XUP_W32_INSTANCE(), platformPrint);
#endif
    }
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintf(("%s: leave", szFunction));
    return;
}


int16_t NP_LOADDS np4xUp_HandleEvent(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, void* event)
{
    static const char szFunction[] = "np4xUp_HandleEvent";
    dprintf(("%s: enter - pWrapper=%p instance=%p event=%p",
             szFunction, pWrapper, instance, event));
    NP4XUP_INSTANCE(FALSE);

    /** @todo WM_PAINT handling and stuff. */
    ReleaseInt3(0x44440002,0x44440002,0x44440002);

    NP4XUP_ENTER_ODIN(FALSE);
    NPError rc = pWrapper->w32->pfnHandleEvent(NP4XUP_W32_INSTANCE(), event);
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
    pWrapper->w32->pfnURLNotify(NP4XUP_W32_INSTANCE(), url, reason, notifyData);
    NP4XUP_LEAVE_ODIN(FALSE);

    dprintf(("%s: leave", szFunction));
    return;
}


void*   NP_LOADDS np4xUp_GetJavaClass(PNPLUGINFUNCSWRAPPER pWrapper, void *pvCaller)
{
    static const char szFunction[] = "np4xUp_GetJavaClass";
    dprintf(("%s: enter - pWrapper=%p", szFunction, pWrapper));

    NP4XUP_ENTER_ODIN(FALSE);
    ReleaseInt3(0x44440003,0x44440003,0x44440003);
    void* rc = 0;// = pWrapper->w32->pfnGetJavaClass();
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
        case NPPVpluginDescriptionString:   dprintf(("%s: NPPVpluginDescriptionString", szFunction)); break;
        case NPPVpluginNameString:          dprintf(("%s: NPPVpluginNameString", szFunction)); break;
        case NPPVpluginWindowBool:          dprintf(("%s: NPPVpluginWindowBool", szFunction)); break;
        case NPPVpluginTransparentBool:     dprintf(("%s: NPPVpluginTransparentBool", szFunction)); break;
        case NPPVjavaClass:                 dprintf(("%s: NPPVjavaClass", szFunction)); break;
        case NPPVpluginWindowSize:          dprintf(("%s: NPPVpluginWindowSize", szFunction)); break;
        case NPPVpluginTimerInterval:       dprintf(("%s: NPPVpluginTimerInterval", szFunction)); break;
        case NPPVpluginScriptableInstance:  dprintf(("%s: NPPVpluginScriptableInstance", szFunction)); break;
        case NPPVpluginScriptableIID:       dprintf(("%s: NPPVpluginScriptableIID", szFunction)); break;
        case NPPVjavascriptPushCallerBool:  dprintf(("%s: NPPVjavascriptPushCallerBool", szFunction)); break;
        case NPPVpluginKeepLibraryInMemory: dprintf(("%s: NPPVpluginKeepLibraryInMemory", szFunction)); break;
    }

    //@todo TEXT: NPPVpluginNameString and NPPVpluginDescriptionString
    if (variable <= NPPVpluginKeepLibraryInMemory)
    {
        NP4XUP_ENTER_ODIN(FALSE);
        rc = pWrapper->w32->pfnGetValue(NP4XUP_W32_INSTANCE(), variable, value);
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
                        dprintf(("%s: *(void**)value=%p", szFunction, *(void**)value));
                        NP4XUP_ENTER_ODIN(FALSE);
                        NPError rc = pWrapper->w32->pfnGetValue(NP4XUP_W32_INSTANCE(), NPPVpluginScriptableIID, (void*)&pnsID);
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
                    dprintf(("%s: *value=%s", szFunction, *(bool*)value ? "true" : "false"));
                    /* Mozilla doesn't support this. */
                    if (variable == NPPVpluginWindowBool && !*(bool*)value)
                    {
                        *(bool*)value = TRUE;
                        dprintf(("%s: OS/2 Mozilla doesn't yet support windowless plugins, so we return true!!", szFunction));
                    }
                    if (variable == NPPVpluginTransparentBool && *(bool*)value)
                    {
                        *(bool*)value = FALSE;
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
#if 0 // @todo temporary
        /* we dont support any scriptable plugin objects atm */
        if (value) *(void**)value = NULL;
        rc = NPERR_GENERIC_ERROR;
#else
        // InstanceData* instanceData = instance->pdata;
        // NPObject* object = instanceData->scriptableObject;

        NPObject *pObject = NULL;

        // set a flag that indicates to np4xDown_CreateObject() that we need class wrappers
        pInst->pw32Class = &pInst->newClass;

        NP4XUP_ENTER_ODIN(FALSE);
        rc = pWrapper->w32->pfnGetValue(NP4XUP_W32_INSTANCE(), variable, &pObject);
        NP4XUP_LEAVE_ODIN(FALSE);

        // sanity
        if (!rc && pObject->_class != (NPClass *)&pInst->newClass)
        {
            dprintf(("%s: ERROR: pObject->_class must be %p", szFunction, &pInst->newClass));
            rc = NPERR_GENERIC_ERROR;
        }

        if (!rc)
            *(void**)value = pObject;
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
                     VALID_PTR(value) ? *((bool*)value) ? "true" : "false" : "invalid"));
            break;
        case NPNVasdEnabledBool:
            dprintf(("%s: NPNVasdEnabledBool *value=%s", szFunction,
                     VALID_PTR(value) ? *((bool*)value) ? "true" : "false" : "invalid"));
            break;
        case NPNVisOfflineBool:
            dprintf(("%s: NPNVisOfflineBool *value=%s", szFunction,
                     VALID_PTR(value) ? *((bool*)value) ? "true" : "false" : "invalid"));
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
    NPError rc = pWrapper->w32->pfnSetValue(NP4XUP_W32_INSTANCE(), variable, value);
    NP4XUP_LEAVE_ODIN(FALSE);
    if (!rc && VALID_PTR(value))
        dprintf(("%s: *(void**)value=%p", szFunction, *(void**)value));

    dprintf(("%s: leave rc=%p", szFunction, rc));
    return rc;
}


/**
 * Stub for not implemented functions.
 *
 * @param ordinal   Ordinal function number.
 */
void NP_LOADDS np4xUp_NotImplementedStub(int ordinal)
{
    dprintf(("%s: enter - ordinal=%d", __FUNCTION__, ordinal));

    char msg[512];
    snprintf(msg, sizeof(msg),
             "The browser has called a Flash plugin function with ordinal %d which is not supported by this version of the Flash plugin wrapper.\n\n"
             "Please report the following information to the vendor:\n"
             "- Flash movie URL;\n"
             "- Flash plugin wrapper version;\n"
             "- Flash plugin DLL version;\n"
             "- Browser version.\n\n"
             "The application will now terminate.",
             ordinal);

    WinMessageBox(HWND_DESKTOP, HWND_DESKTOP, msg, NULL, 0, MB_ERROR | MB_OK | MB_SYSTEMMODAL);

    dprintf(("%s: Terminating the application.", __FUNCTION__));
    exit(333);
    return;
}


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// DOWN wrappers (stuff that is to the plugin)
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//


/* This is not a callback, but something most plugins implememnts somehow, remove it! */
void    NP32_LOADDS np4xDown_Version(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, int* plugin_major, int* plugin_minor,
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


NPError NP32_LOADDS np4xDown_GetURLNotify(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, const char* url, const char* target, void* notifyData)
{
    static const char szFunction[] = "np4xDown_GetURLNotify";
    dprintf(("%s: enter - pWrapper=%p instance=%p url=%p target=%p notifyData=%p",
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


NPError NP32_LOADDS np4xDown_GetURL(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, const char* url, const char* target)
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


NPError NP32_LOADDS np4xDown_PostURLNotify(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, const char* url, const char* target, uint32_t len,
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


NPError NP32_LOADDS np4xDown_PostURL(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, const char* url,
                                       const char* target, uint32_t len,
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


NPError NP32_LOADDS np4xDown_RequestRead(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPStream* stream, NPByteRange* rangeList)
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


NPError NP32_LOADDS np4xDown_NewStream(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPMIMEType type,
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


int32_t NP32_LOADDS np4xDown_Write(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPStream* stream, int32_t len, void* buffer)
{
    static const char szFunction[] = "np4xDown_NewStream";
    dprintf(("%s: enter - pWrapper=%p instance=%p stream=%p len=%d buffer=%p",
             szFunction, pWrapper, instance, stream, len, buffer));
    DPRINTF_STREAM(stream);
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    int32_t rc = pWrapper->pNative->write(NP4XDOWN_NS_INSTANCE(), stream, len, buffer);

    NP4XDOWN_ENTER_ODIN(FALSE);
    DPRINTF_STREAM(stream);
    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


NPError NP32_LOADDS np4xDown_DestroyStream(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPStream* stream, NPReason reason)
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


void    NP32_LOADDS np4xDown_Status(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, const char* message)
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


const char* NP32_LOADDS np4xDown_UserAgent(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance)
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


void*   NP32_LOADDS np4xDown_MemAlloc(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, uint32_t size)
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


void    NP32_LOADDS np4xDown_MemFree(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, void* ptr)
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


uint32_t NP32_LOADDS np4xDown_MemFlush(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, uint32_t size)
{
    static const char szFunction[] = "np4xDown_MemFlush";
    dprintf(("%s: enter - pWrapper=%p size=%d",
             szFunction, pWrapper, size));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    uint32_t rc = pWrapper->pNative->memflush(size);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


void    NP32_LOADDS np4xDown_ReloadPlugins(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPBool reloadPages)
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


void*   NP32_LOADDS np4xDown_GetJavaEnv(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller)
{
    static const char szFunction[] = "np4xDown_GetJavaEnv";
    dprintf(("%s: enter - pWrapper=%p", szFunction, pWrapper));
    NP4XDOWN_LEAVE_ODIN(FALSE);

  /*  ReleaseInt3(0x44440005,0x44440005,0x44440005); */
    void *envRc = pWrapper->pNative->getJavaEnv();

    if (VALID_PTR(envRc))
    {
        void *pvWrapped = (void *)NPJNICreateDownWrapper(0, NPJS_TYPE_JRIENV_DOWN, envRc);
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


void*   NP32_LOADDS np4xDown_GetJavaPeer(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance)
{
    static const char szFunction[] = "np4xDown_GetJavaPeer";
    dprintf(("%s: enter - pWrapper=%p instance=%p", szFunction, pWrapper, instance));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    void* rc = pWrapper->pNative->getJavaPeer(NP4XDOWN_NS_INSTANCE());

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%p", szFunction, rc));
    return rc;
}


NPError NP32_LOADDS np4xDown_GetValue(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPNVariable variable, void *value)
{
    static const char szFunction[] = "np4xDown_GetValue";
    dprintf(("%s: enter - pWrapper=%p instance=%p variable=%d value=%p",
             szFunction, pWrapper, instance, variable, value));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPError rc;
    bool bSupported = true;

    switch (variable)
    {
        case NPNVxDisplay:              dprintf(("%s: NPNVxDisplay", szFunction)); break;
        case NPNVxtAppContext:          dprintf(("%s: NPNVxtAppContext", szFunction)); break;
        case NPNVnetscapeWindow:        dprintf(("%s: NPNVnetscapeWindow", szFunction)); break;
        case NPNVjavascriptEnabledBool: dprintf(("%s: NPNVjavascriptEnabledBool", szFunction)); break;
        case NPNVasdEnabledBool:        dprintf(("%s: NPNVasdEnabledBool", szFunction)); break;
        case NPNVisOfflineBool:         dprintf(("%s: NPNVisOfflineBool", szFunction)); break;
        case NPNVWindowNPObject:        dprintf(("%s: NPNVWindowNPObject", szFunction)); break;
        case NPNVPluginElementNPObject: dprintf(("%s: NPNVPluginElementNPObject", szFunction)); break;
        case NPNVprivateModeBool:       dprintf(("%s: NPNVprivateModeBool", szFunction)); break;
        case NPNVdocumentOrigin:        dprintf(("%s: NPNVdocumentOrigin", szFunction)); break;
        default:
            bSupported = false;
            dprintf(("%s: Unsupported variable %d", szFunction, variable));
            break;
    }

    if (bSupported)
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
            case NPNVprivateModeBool:
                dprintf(("%s: *value=%s", szFunction, *((bool*)value) ? "true" : "false"));
                break;
            case NPNVdocumentOrigin:
                dprintf(("%s: *value=%s", szFunction, *((char**)value)));
                break;
            default:
                dprintf(("%s: *value=%#08x", szFunction, *((void**)value)));
                break;
            }
        }
    }
    else
    {
        rc = NPERR_GENERIC_ERROR;
    }

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%d", szFunction, rc));
    return rc;
}


NPError NP32_LOADDS np4xDown_SetValue(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPPVariable variable, void *value)
{
    static const char szFunction[] = "np4xDown_SetValue";
    dprintf(("%s: enter - pWrapper=%p instance=%p variable=%d value=%p",
             szFunction, pWrapper, instance, variable, value));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);
    bool fWindowLessReject = FALSE;
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
            if (!(bool)value)
            {
                dprintf(("%s: OS/2 Mozilla doesn't yet support windowless plugins, so we set it to true!!", szFunction));
                value = (void*)TRUE;
                fWindowLessReject = TRUE;
            }
            break;
        case NPPVpluginTransparentBool:
            dprintf(("%s: NPPVpluginTransparentBool value=%s", szFunction, value ? "true" : "false"));
            if ((bool)value)
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


void    NP32_LOADDS np4xDown_InvalidateRect(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPRect *invalidRect)
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


void    NP32_LOADDS np4xDown_InvalidateRegion(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPRegion invalidRegion)
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


void    NP32_LOADDS np4xDown_ForceRedraw(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance)
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


NPIdentifier NP32_LOADDS np4xDown_GetStringIdentifier(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, const NPUTF8* name)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p name=%s",
             szFunction, pWrapper, name));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPIdentifier identifier = pWrapper->pNative->getstringidentifier(name);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave identifier=%x", szFunction, identifier));
    return identifier;
}


void         NP32_LOADDS np4xDown_GetStringIdentifiers(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, const NPUTF8** names, int32_t nameCount, NPIdentifier* identifiers)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p names=%p nameCount=%d identifiers=%p",
             szFunction, pWrapper, names, nameCount, identifiers));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pWrapper->pNative->getstringidentifiers(names, nameCount, identifiers);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave", szFunction));
    return;
}


NPIdentifier NP32_LOADDS np4xDown_GetIntIdentifier(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, int32_t intid)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p intid=%d",
             szFunction, pWrapper, intid));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPIdentifier identifier = pWrapper->pNative->getintidentifier(intid);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave identifier=%x", szFunction, identifier));
    return identifier;
}


bool         NP32_LOADDS np4xDown_IdentifierIsString(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPIdentifier identifier)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p identifier=%p",
             szFunction, pWrapper, identifier));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    bool rc = pWrapper->pNative->identifierisstring(identifier);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


NPUTF8*      NP32_LOADDS np4xDown_UTF8FromIdentifier(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPIdentifier identifier)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p identifier=%p",
             szFunction, pWrapper, identifier));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPUTF8 *utf8 = pWrapper->pNative->utf8fromidentifier(identifier);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave utf8=%s", szFunction, utf8));
    return utf8;
}


int32_t      NP32_LOADDS np4xDown_IntFromIdentifier(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPIdentifier identifier)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p identifier=%p",
             szFunction, pWrapper, identifier));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    int32_t i = pWrapper->pNative->intfromidentifier(identifier);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave i=%d", szFunction, i));
    return i;
}


NPObject* NP32_LOADDS np4xDown_CreateObject(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPClass *aClass)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p instance=%p aClass=%p",
             szFunction, pWrapper, instance, aClass));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    // check if we are being called as a result of np4xUp_GetValue(NPPVpluginScriptableNPObject)
    if (pInst->pw32Class = &pInst->newClass)
    {
        dprintf(("%s: w32 class %p version %d", szFunction, aClass, aClass->structVersion));

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

    NPObject *object = pWrapper->pNative->createobject(NP4XDOWN_NS_INSTANCE(), aClass);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave object=%x", szFunction, object));
    return object;
}


NPObject* NP32_LOADDS np4xDown_RetainObject(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPObject *obj)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p obj=%p",
             szFunction, pWrapper, obj));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NPObject *object = pWrapper->pNative->retainobject(obj);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave object=%x", szFunction, object));
    return object;
}


void NP32_LOADDS np4xDown_ReleaseObject(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPObject *obj)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p obj=%p",
             szFunction, pWrapper, obj));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pWrapper->pNative->releaseobject(obj);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave", szFunction));
    return;
}


bool NP32_LOADDS np4xDown_Invoke(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPObject* obj, NPIdentifier methodName, const NP32Variant *args, uint32_t argCount, NP32Variant *result)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p instance=%p obj=%p methodName=%p args=%p argCount=%d result=%p",
             szFunction, pWrapper, instance, obj, methodName, args, argCount, result));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NP4XDOWN_BEGIN_IN_NPVARIANTS(args, argCount);
    NP4XDOWN_BEGIN_OUT_NPVARIANT(result);

    bool rc = pWrapper->pNative->invoke(NP4XDOWN_NS_INSTANCE(), obj, methodName, NP4XDOWN_USE_IN_NPVARIANTS(args), argCount, NP4XDOWN_USE_OUT_NPVARIANT(result));

    NP4XDOWN_END_OUT_NPVARIANT(result);
    NP4XDOWN_END_IN_NPVARIANTS(args);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}

bool NP32_LOADDS np4xDown_InvokeDefault(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPObject* obj, const NP32Variant *args, uint32_t argCount, NP32Variant *result)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p instance=%p obj=%p args=%p argCount=%d result=%p",
             szFunction, pWrapper, instance, obj, args, argCount, result));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NP4XDOWN_BEGIN_IN_NPVARIANTS(args, argCount);
    NP4XDOWN_BEGIN_OUT_NPVARIANT(result);

    bool rc = pWrapper->pNative->invokeDefault(NP4XDOWN_NS_INSTANCE(), obj, NP4XDOWN_USE_IN_NPVARIANTS(args), argCount, NP4XDOWN_USE_OUT_NPVARIANT(result));

    NP4XDOWN_END_OUT_NPVARIANT(result);
    NP4XDOWN_END_IN_NPVARIANTS(args);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


bool NP32_LOADDS np4xDown_Evaluate(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPObject *obj, NPString *script, NP32Variant *result)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p instance=%p obj=%p script=%p result=%p",
             szFunction, pWrapper, instance, obj, script, result));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NP4XDOWN_BEGIN_OUT_NPVARIANT(result);

    bool rc = pWrapper->pNative->evaluate(NP4XDOWN_NS_INSTANCE(), obj, script, NP4XDOWN_USE_OUT_NPVARIANT(result));

    NP4XDOWN_END_OUT_NPVARIANT(result);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


bool NP32_LOADDS np4xDown_GetProperty(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPObject *obj, NPIdentifier propertyName, NP32Variant *result)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p instance=%p obj=%p propertyName=%p result=%p",
             szFunction, pWrapper, instance, obj, propertyName, result));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NP4XDOWN_BEGIN_OUT_NPVARIANT(result);

    bool rc = pWrapper->pNative->getproperty(NP4XDOWN_NS_INSTANCE(), obj, propertyName, NP4XDOWN_USE_OUT_NPVARIANT(result));
    if (rc)
        dprintfNPVariant(szFunction, NP4XDOWN_USE_OUT_NPVARIANT(result));

    NP4XDOWN_END_OUT_NPVARIANT(result);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


bool NP32_LOADDS np4xDown_SetProperty(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPObject *obj, NPIdentifier propertyName, const NP32Variant *value)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p instance=%p obj=%p propertyName=%p value=%p",
             szFunction, pWrapper, instance, obj, propertyName, value));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NP4XDOWN_BEGIN_IN_NPVARIANT(value);

    dprintfNPVariant(szFunction, NP4XDOWN_USE_IN_NPVARIANT(value));

    bool rc = pWrapper->pNative->setproperty(NP4XDOWN_NS_INSTANCE(), obj, propertyName, NP4XDOWN_USE_IN_NPVARIANT(value));

    NP4XDOWN_END_IN_NPVARIANT(value);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


bool NP32_LOADDS np4xDown_RemoveProperty(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPObject *obj, NPIdentifier propertyName)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p instance=%p obj=%p propertyName=%p",
             szFunction, pWrapper, instance, obj, propertyName));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    bool rc = pWrapper->pNative->removeproperty(NP4XDOWN_NS_INSTANCE(), obj, propertyName);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


bool NP32_LOADDS np4xDown_HasProperty(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPObject *obj, NPIdentifier propertyName)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p instance=%p obj=%p propertyName=%p",
             szFunction, pWrapper, instance, obj, propertyName));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    bool rc = pWrapper->pNative->hasproperty(NP4XDOWN_NS_INSTANCE(), obj, propertyName);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


bool NP32_LOADDS np4xDown_HasMethod(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPP instance, NPObject *obj, NPIdentifier propertyName)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p instance=%p obj=%p propertyName=%p",
             szFunction, pWrapper, instance, obj, propertyName));
    NP4XDOWN_INSTANCE(FALSE);
    NP4XDOWN_LEAVE_ODIN(FALSE);

    bool rc = pWrapper->pNative->hasmethod(NP4XDOWN_NS_INSTANCE(), obj, propertyName);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave rc=%s", szFunction, rc ? "true" : "false"));
    return rc;
}


void NP32_LOADDS np4xDown_ReleaseVariantValue(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NP32Variant *variant)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p variant=%p",
             szFunction, pWrapper, variant));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    NP4XDOWN_BEGIN_OUT_NPVARIANT(variant);

    dprintfNPVariant(szFunction, NP4XDOWN_USE_OUT_NPVARIANT(variant));

    pWrapper->pNative->releasevariantvalue(NP4XDOWN_USE_OUT_NPVARIANT(variant));

    NP4XDOWN_END_OUT_NPVARIANT(variant);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave", szFunction));
    return;
}


void NP32_LOADDS np4xDown_SetException(PNETSCAPEFUNCSWRAPPER pWrapper, void *pvCaller, NPObject *obj, const NPUTF8 *message)
{
    static const char *szFunction = __FUNCTION__;
    dprintf(("%s: enter - pWrapper=%p obj=%p message=%s",
             szFunction, pWrapper, obj, message));
    NP4XDOWN_LEAVE_ODIN(FALSE);

    pWrapper->pNative->setexception(obj, message);

    NP4XDOWN_ENTER_ODIN(FALSE);
    dprintf(("%s: leave", szFunction));
    return;
}


/**
 * Stub for not implemented functions.
 *
 * @param ordinal   Ordinal function number.
 */
void NP32_LOADDS np4xDown_NotImplementedStub(int ordinal)
{
    dprintf(("%s: enter - ordinal=%d", __FUNCTION__, ordinal));

    char msg[512];
    snprintf(msg, sizeof(msg),
             "The Flash plugin has called a browser function with ordinal %d which is not supported by this version of the Flash plugin wrapper.\n\n"
             "Please report the following information to the vendor:\n"
             "- Flash movie URL;\n"
             "- Flash plugin wrapper version;\n"
             "- Flash plugin DLL version;\n"
             "- Browser version.\n\n"
             "The application will now terminate.",
             ordinal);

    WinMessageBox(HWND_DESKTOP, HWND_DESKTOP, msg, NULL, 0, MB_ERROR | MB_OK | MB_SYSTEMMODAL);

    dprintf(("%s: Terminating the application.", __FUNCTION__));
    exit(333);
    return;
}


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// Generic wrapping stuff.
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//


NPError OSCALL npGenericNP_GetEntryPoints(NPPluginFuncs* pCallbacks, PNPODINWRAPPER pPlugin)
{
    static const char szFunction[] = "npGenericNP_GetEntryPoints";
    dprintf(("%s: enter - pCallbacks=%p pPlugin=%p", szFunction, pCallbacks, pPlugin));
    DPRINTF_STR(pPlugin->szPluginDllName);
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
     * Create wrapper for the function table.
     *      Allocate.
     *      Initiate it.
     *      Create stubs.
     */

    size_t funcCnt = (pCallbacks->size - sizeof(NPPluginFuncs::size) - sizeof(NPPluginFuncs::version)) / sizeof(PFN);

    size_t w32StructSize = sizeof(NP32PluginFuncs::size) + sizeof(NP32PluginFuncs::version) + funcCnt * sizeof(PFN);

    dprintf(("%s: pCallbacks->version=%d pCallbacks->size=%d funcCnt=%u w32StructSize=%u", szFunction, pCallbacks->version, pCallbacks->size, funcCnt, w32StructSize));

    // allocate the main struct with space enough for NPLUGINFUNCSWRAPPER::Stub[funcCnt] and
    // NP32PluginFuncs (i.e. incluing the functions we don't currently implement)
    size_t totalStructSize = sizeof(NPLUGINFUNCSWRAPPER) + sizeof(NPLUGINFUNCSWRAPPER::Stub) * funcCnt + w32StructSize;

    PNPLUGINFUNCSWRAPPER pWrapper = (PNPLUGINFUNCSWRAPPER)malloc(totalStructSize);
    if (!pWrapper)
    {
        dprintf(("%s: out of memory! Can't allocate wrapper!", szFunction));
        NPXP_ASSERT_OS2FS();
        return NPERR_OUT_OF_MEMORY_ERROR;
    }

    memset(pWrapper, 0, totalStructSize);

    // set up pointers to function tables following the main struct
    pWrapper->w32 = (NP32PluginFuncs *) (pWrapper + 1);
    pWrapper->pStubs = (NPLUGINFUNCSWRAPPER::Stub *)(((char *)pWrapper->w32) + w32StructSize);

    pWrapper->w32->size = pCallbacks->size;
    pWrapper->w32->version = pCallbacks->version;

    pWrapper->pNative = pCallbacks;

    PFN *nativeFuncs = (PFN *) (&pCallbacks->version + 1);

    // fill up the native function table with dummy stubs as flags (wrappers for implemented functions will overwrite them below and all dummy stubs will be replaced by a special callback sequence)
    for (size_t i = 0; i < funcCnt; ++i)
        nativeFuncs[i] = (PFN)&np4xUp_NotImplementedStub;

    // fill up the function table with wrappers
    PFN implementedWrappers[] =
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
        (PFN)&pCallbacks->javaClass,
        (PFN)&np4xUp_GetValue,
        (PFN)&np4xUp_SetValue,
    };

    enum { implementedWrappersCnt = sizeof(implementedWrappers) / sizeof(implementedWrappers[0]) };

    dprintf(("%s: will create not-implemented stubs for %d functions", szFunction, funcCnt - implementedWrappersCnt));

    /*
     * Call Real worker in Odin context.
     */
    unsigned ExceptionRegRec[2] = {0,0};
    USHORT selFSOld = pfnODIN_ThreadEnterOdinContext(&ExceptionRegRec[0], TRUE);
    rc = pPlugin->pfnW32NP_GetEntryPoints(pWrapper->w32);
    pfnODIN_ThreadLeaveOdinContext(&ExceptionRegRec[0], selFSOld);
    ExceptionRegRec[0] = ExceptionRegRec[1] = 0;
    if (!rc)
    {
        pCallbacks->javaClass = pWrapper->w32->javaClass;

        for (size_t i = 0; i < implementedWrappersCnt; ++i)
        {
            if (implementedWrappers[i] == NULL ||
                implementedWrappers[i] == (PFN)&pCallbacks->javaClass)
                continue;

            pWrapper->pStubs[i].chPush      = 0x68;
            pWrapper->pStubs[i].pvImm32bit  = pWrapper;
            pWrapper->pStubs[i].chCall      = 0xe8;
            pWrapper->pStubs[i].offRel32bit = (char*)implementedWrappers[i] - (char*)&pWrapper->pStubs[i].offRel32bit - 4;
            pWrapper->pStubs[i].chPopEcx    = 0x59;
            pWrapper->pStubs[i].chRet       = 0xc3;

            // point to a stub only if plugin provides a function, otherwise set it also to NULL
            nativeFuncs[i] = pWrapper->w32->functions[i] != NULL ? (PFN)&pWrapper->pStubs[i] : NULL;

            memset(pWrapper->pStubs[i].achMagic, 0xcc, sizeof(pWrapper->pStubs[i].achMagic));
        }

        // set up stubs stubs for unused functions
        for (size_t i = 0; i < funcCnt; ++i)
        {
            if (nativeFuncs[i] == (PFN)&np4xUp_NotImplementedStub)
            {
                pWrapper->pStubs[i].chPush      = 0x68;
                pWrapper->pStubs[i].pvImm32bit  = (void *)i;
                pWrapper->pStubs[i].chCall      = 0xe8;
                pWrapper->pStubs[i].offRel32bit = (char *)&np4xUp_NotImplementedStub - (char *)&pWrapper->pStubs[i].offRel32bit - 4;
                pWrapper->pStubs[i].chPopEcx    = 0x59;
                pWrapper->pStubs[i].chRet       = 0xc3;

                nativeFuncs[i] = (PFN)&pWrapper->pStubs[i];

                memset(pWrapper->pStubs[i].achMagic, 0xcc, sizeof(pWrapper->pStubs[i].achMagic));
            }
        }

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


NPError OSCALL npGenericNP_Initialize(NPNetscapeFuncs * pFuncs, PNPODINWRAPPER pPlugin)
{
    static const char szFunction[] = "npGenericNP_Initialize";
    dprintf(("%s: enter - pFuncs=%p pPlugin=%p", szFunction, pFuncs, pPlugin));
    DPRINTF_STR(pPlugin->szPluginDllName);
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
     */

    size_t funcCnt = (pFuncs->size - sizeof(NPNetscapeFuncs::size) - sizeof(NPNetscapeFuncs::version)) / sizeof(PFN);

    size_t w32StructSize = sizeof(NP32NetscapeFuncs::size) + sizeof(NP32NetscapeFuncs::version) + funcCnt * sizeof(PFN);

    dprintf(("%s: pFuncs->version=%d pFuncs->size=%d funcCnt=%u w32StructSize=%u", szFunction, pFuncs->version, pFuncs->size, funcCnt, w32StructSize));

    // allocate the main struct with space enough for NETSCAPEFUNCSWRAPPER::Stub[funcCnt] and
    // NP32NetscapeFuncs (i.e. incluing the functions we don't currently implement)
    size_t totalStructSize = sizeof(NETSCAPEFUNCSWRAPPER) + sizeof(NETSCAPEFUNCSWRAPPER::Stub) * funcCnt + w32StructSize;

    PNETSCAPEFUNCSWRAPPER pWrapper = (PNETSCAPEFUNCSWRAPPER)malloc(totalStructSize);
    if (!pWrapper)
    {
        dprintf(("%s: out of memory! Can't allocate wrapper!", szFunction));
        NPXP_ASSERT_OS2FS();
        return NPERR_OUT_OF_MEMORY_ERROR;
    }

    memset(pWrapper, 0, totalStructSize);

    // set up pointers to function tables following the main struct
    pWrapper->w32 = (NP32NetscapeFuncs *) (pWrapper + 1);
    pWrapper->pStubs = (NETSCAPEFUNCSWRAPPER::Stub *)(((char *)pWrapper->w32) + w32StructSize);

    pWrapper->w32->size = pFuncs->size;
    pWrapper->w32->version = pFuncs->version;

    pWrapper->pNative = pFuncs;

    PFN *nativeFuncs = (PFN *) (&pFuncs->version + 1);

    // fill up the w32 function table with dummy stubs as flags (wrappers for implemented functions will overwrite them below and all dummy stubs will be replaced by a special callback sequence)
    for (size_t i = 0; i < funcCnt; ++i)
        pWrapper->w32->functions[i] = (PFN)&np4xDown_NotImplementedStub;

    // fill up the function table with wrappers
    PFN implementedWrappers[] =
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
    };

    enum { implementedWrappersCnt = sizeof(implementedWrappers) / sizeof(implementedWrappers[0]) };

    dprintf(("%s: will create not-implemented stubs for %d functions", szFunction, funcCnt - implementedWrappersCnt));

    for (size_t i = 0; i < implementedWrappersCnt; ++i)
    {
        if (implementedWrappers[i] == NULL)
            continue;

        pWrapper->pStubs[i].chPush      = 0x68;
        pWrapper->pStubs[i].pvImm32bit  = pWrapper;
        pWrapper->pStubs[i].chCall      = 0xe8;
        pWrapper->pStubs[i].offRel32bit = (char *)implementedWrappers[i] - (char *)&pWrapper->pStubs[i].offRel32bit - 4;
        pWrapper->pStubs[i].chPopEcx    = 0x59;
        pWrapper->pStubs[i].chRet       = 0xc3;

        // point to a stub only if Mozilla provides a function, otherwise set it also to NULL
        pWrapper->w32->functions[i] = nativeFuncs[i] != NULL ? (PFN)&pWrapper->pStubs[i] : NULL;

        memset(pWrapper->pStubs[i].achMagic, 0xcc, sizeof(pWrapper->pStubs[i].achMagic));
    }

    // set up stubs stubs for unused functions
    for (size_t i = 0; i < funcCnt; ++i)
    {
        if (pWrapper->w32->functions[i] == (PFN)&np4xDown_NotImplementedStub)
        {
            pWrapper->pStubs[i].chPush      = 0x68;
            pWrapper->pStubs[i].pvImm32bit  = (void *)i;
            pWrapper->pStubs[i].chCall      = 0xe8;
            pWrapper->pStubs[i].offRel32bit = (char *)&np4xDown_NotImplementedStub - (char *)&pWrapper->pStubs[i].offRel32bit - 4;
            pWrapper->pStubs[i].chPopEcx    = 0x59;
            pWrapper->pStubs[i].chRet       = 0xc3;

            pWrapper->w32->functions[i] = (PFN)&pWrapper->pStubs[i];

            memset(pWrapper->pStubs[i].achMagic, 0xcc, sizeof(pWrapper->pStubs[i].achMagic));
        }
    }

    /*
     * Call Real worker in Odin context.
     */
    unsigned ExceptionRegRec[2] = {0,0};
    USHORT selFSOld = pfnODIN_ThreadEnterOdinContext(&ExceptionRegRec[0], TRUE);
    rc = pPlugin->pfnW32NP_Initialize(pWrapper->w32);
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


NPError OSCALL npGenericNP_Shutdown(PNPODINWRAPPER pPlugin)
{
    static const char szFunction[] = "npGenericNP_Shutdown";
    dprintf(("%s: enter - pPlugin=%p", szFunction, pPlugin));
    DPRINTF_STR(pPlugin->szPluginDllName);
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
NPError OSCALL npGenericNP_GetValue(NPP future, NPPVariable variable, void *value, PNPODINWRAPPER pPlugin)
{
    static const char szFunction[] = "npGenericNP_GetMIMEDescription";
    dprintf(("%s: enter - future=%p variable=%d value=%p pPlugin=%p", szFunction, future, variable, value, pPlugin));
    DPRINTF_STR(pPlugin->szPluginDllName);
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


char * OSCALL npGenericNP_GetMIMEDescription(PNPODINWRAPPER pPlugin)
{
    static const char szFunction[] = "npGenericNP_GetMIMEDescription";
    dprintf(("%s: enter - pPlugin=%p", szFunction, pPlugin));
    DPRINTF_STR(pPlugin->szPluginDllName);
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

