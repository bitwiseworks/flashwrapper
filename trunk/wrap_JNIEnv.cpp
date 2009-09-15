/* $Id: wrap_JNIEnv.cpp,v 1.4 2004/03/08 19:22:56 bird Exp $
 *
 * JNI Stuff.
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
#define JDK1_2
#define JDK1_4
#ifdef __IBMCPP__
# include "moz_VACDefines.h"
#else
# include "moz_GCCDefines.h"
#endif
#include "jri.h"
#include "jni.h"

#include <os2.h>
#include <builtin.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

#include "common.h"


/*******************************************************************************
*   Structures and Typedefs                                                    *
*******************************************************************************/
/**
 * Structure describing the JNIEnv wrapper we create on the stack.
 * The reason we cannot use the LXJNIENV structure directly is because
 * the JNIEnv pointer the native calls recieve also gives a fast path to the
 * current thread object (JavaThread::thread_from_jni_environment(env)).
 */
typedef struct NPJNIEnv
{
    /** Pointer to our wrapper function table. */
    void *          functions;
    /** Padding. */
    unsigned        uZero[20];
    /** Pointer to the passed in JNIEnv structure. */
    JNIEnv *        pOrgEnv;
    /** Odin Instance Handle - required for the use of NPJNICreateWrapper(). */
    HINSTANCE       hInstance;
} NPJNIENV, *PNPJNIENV;


/**
 * Structure describing the JRIEnv wrapper we create on the stack.
 * The reason we cannot use the LXJRIENV structure directly is because
 * the JRIEnv pointer the native calls recieve also gives a fast path to the
 * current thread object (JavaThread::thread_from_jri_environment(env)).
 */
typedef struct NPJRIEnv
{
    /** Pointer to our wrapper function table. */
    void *          functions;
    /** Padding. */
    unsigned        uZero;
    /** Pointer to the passed in JRIEnv structure. */
    JRIEnv *        pOrgEnv;
    /** Odin Instance Handle - required for the use of NPJRICreateWrapper(). */
    HINSTANCE       hInstance;
} NPJRIENV, *PNPJRIENV;



/**
 * Dynamically allocated JNIEnv and JavaVM wrapper.
 */
typedef struct NPJNI2nd
{
    /** Pointer to the next structure. */
    struct NPJNI2nd * volatile  pNext;

    /** Wrapper type. */
    unsigned            fType;

    /** Union of the different wrapper structures. */
    union the_wrapper
    {
        NPJNIENV    Env;
        NPJRIENV    Jri;
        //NPJNIVM     VM;
    } u;

} NPJNI2ND, * volatile PNPJNI2ND;



/*******************************************************************************
*   Global Variables                                                           *
*******************************************************************************/
/** This variable is used to drag in XPCOM in the linking of a primary wrapper. */
int                 giJNI;
/** LIFO of NPJNI2ND structures, operated atomically. */
static PNPJNI2ND    pNPJNI2ndHead = NULL;





/**
 * RegisterNatives wrapper.
 *
 * Prototype:
 *     jint (JNICALL *RegisterNatives)
 *         (JNIEnv *env, jclass clazz, const JNINativeMethod *methods, jint nMethods)
 */
jint __stdcall npjni_RegisterNatives(PNPJNIENV pEnv, jclass clazz, const JNINativeMethod *methods, jint nMethods)
{
    USHORT selFSOld = pfnODIN_ThreadLeaveOdinContextNested(NULL, FALSE);
    dprintf(("npJNIEnvWrapper: npjni_RegisterNatives enter"));
ReleaseInt3(0xdeadbeaf, 0xc00fe00, 0x10001000);
    jint rc = pEnv->pOrgEnv->functions->RegisterNatives(pEnv->pOrgEnv, clazz, methods, nMethods);
    dprintf(("npJNIEnvWrapper: npjni_RegisterNatives leave rc=%x", rc));
    pfnODIN_ThreadEnterOdinContextNested(NULL, FALSE, selFSOld);
    return rc;
}


/**
 * GetJavaVM wrapper.
 *
 * Prototype:
 *     jint (JNICALL *GetJavaVM)
 *         (JNIEnv *env, JavaVM **vm)
 */
jint __stdcall npjni_GetJavaVM(PNPJNIENV pEnv, JavaVM **vm)
{
    USHORT selFSOld = pfnODIN_ThreadLeaveOdinContextNested(NULL, FALSE);
    dprintf(("npJNIEnvWrapper: npjni_GetJavaVM enter"));
ReleaseInt3(0xdeadbeaf, 0xc00fe00, 0x20002000);
    jint rc = pEnv->pOrgEnv->functions->GetJavaVM(pEnv->pOrgEnv, vm);
    dprintf(("npJNIEnvWrapper: npjni_GetJavaVM leave rc=%x", rc));
    pfnODIN_ThreadEnterOdinContextNested(NULL, FALSE, selFSOld);
    return rc;
}


#include "wrap_JNIEnv_Generated.cpp"



/**
 * RegisterNatives wrapper.
 *
 * Prototype:
 *     void    (JRICALL *RegisterNatives)
 *         (JRIEnv* env, jint op, struct java_lang_Class* a, char** b, void** c)
 */
void __cdecl npjridown_RegisterNatives(PNPJRIENV pEnv, jint op, struct java_lang_Class* a, char** b, void** c)
{
    USHORT selFSOld = pfnODIN_ThreadLeaveOdinContextNested(NULL, FALSE);
    dprintf(("npJRIEnvWrapper: npjridown_RegisterNatives enter"));
ReleaseInt3(0xdeadbeaf, 0xc00fe00, 0x30003000);
    (*pEnv->pOrgEnv)->RegisterNatives(pEnv->pOrgEnv, op, a, b, c);
    dprintf(("npJRIEnvWrapper: npjridown_RegisterNatives leave"));
    pfnODIN_ThreadEnterOdinContextNested(NULL, FALSE, selFSOld);
}

#include "wrap_JRIEnv_Generated.cpp"




/**
 * Create a 2nd level struct wrapper.
 *
 * This is very similar to J2LxJNIDllGenericWrapperWorkerEnter, but this must
 * allocate memory from the heap and maintain a linked list of wrappers. This
 * is because it's called when we're in the JNIEnv or JavaVM wrappers and is
 * supposed to return a wrapped structure of this kind.
 *
 * The function maintains a list of these wrappers in order to try reuse them
 * and not eat too much heap. The list is protected by mtxJNILx2nd.
 *
 * @returns Pointer to wrapped structure.
 * @returns NULL on failure.
 * @param   fType       Wrapper type, one of the NPJS_TYPE_* defines.
 *                      This tell us what pv points to.
 * @param   pv          Pointer to the structure we're wrapping.
 * @param   hInstance   Instance handle this wrapper should be related to.
 *
 */
void *              NPJNICreateDownWrapper(HINSTANCE hInstance, unsigned fType, void *pv)
{
    static const char szFunction[] = "NPJNICreateDownWrapper";
    NPJNI2ND    tmp;
    memset(&tmp, 0, sizeof(tmp));

    /*
     * Now make a wrapper template for this type so we
     * can memcmp our way thru the list without switching on the type.
     */
    tmp.fType = fType;
    switch (fType)
    {
        case NPJS_TYPE_JNIENV:
            tmp.u.Env.functions = (void*)&apfnJNIEnv[0];
            tmp.u.Env.pOrgEnv   = (JNIEnv *)pv;
            tmp.u.Env.hInstance = hInstance;
            break;

        case NPJS_TYPE_JRIENV_DOWN:
            tmp.u.Jri.functions = (void*)&apfnJRIEnvDown[0];
            tmp.u.Jri.pOrgEnv   = (JRIEnv *)pv;
            tmp.u.Jri.hInstance = hInstance;
            break;

        #if 0
        case NPJS_TYPE_JAVAVM:
            tmp.u.VM.functions   = (void*)&apfnJNIVM[0];
            tmp.u.VM.pOrgVM      = (JavaVM *)pv;
            tmp.u.VM.hInstance   = hInstance;
            break;
        #endif

        default:
            dprintf(("%s: INTERNAL ERROR!!! INVALID WRAPPER TYPE %x", szFunction, fType));
            ReleaseInt3(0x00c0ffe, 1, 0);
            return NULL;
    }


    /*
     * Walk the list looking for this pv/pvFunction combination.
     */
    PNPJNI2ND   pCur;
    for (pCur = pNPJNI2ndHead; pCur; pCur = pCur->pNext)
    {
        if (    pCur->fType == fType
            &&  !memcmp(&pCur->u, &tmp.u, sizeof(tmp.u)))
        {
            dprintf(("%s: Found wrapper for pv=0x%x/fType=%d in list. returns 0x%x", szFunction, pv, fType, &pCur->u));
            return &pCur->u;
        }
    }


    /*
     * Allocate add new entry to list.
     */
    pCur = (PNPJNI2ND)malloc(sizeof(NPJNI2ND));
    if (pCur)
    {
        memcpy(pCur, &tmp, sizeof(tmp));
        do
        {
            pCur->pNext = pNPJNI2ndHead;
        } while (!NPJNIEqual((unsigned*)&pNPJNI2ndHead, (unsigned)pCur, (unsigned)pCur->pNext));

        dprintf(("%s: Created new wrapper for pv=0x%x/fType=%d. returns 0x%x", szFunction, pv, fType, &pCur->u));
        return &pCur->u;
    }

    return NULL;
}


/**
 * We must check (and pray) that the passed in pointer is a pointer to an wrapper
 * created in NPJNICreateDownWrapper.
 *
 * If not we must make wrappers going the othere way too.
 *
 * @returns Pointer to wrapped structure.
 * @returns NULL on failure.
 * @param   fType       Wrapper type, one of the NPJS_TYPE_* defines.
 *                      This tell us what pv points to.
 * @param   pv          Pointer to the structure we're wrapping.
 * @param   hInstance   Instance handle this wrapper should be related to.
 *
 */
void *              NPJNICreateUpWrapper(HINSTANCE hInstance, unsigned fType, void *pv)
{
    static const char szFunction[] = "NPJNICreateUpWrapper";
    /*
     * Validate input.
     */
    switch (fType)
    {
        case NPJS_TYPE_JNIENV:
        case NPJS_TYPE_JRIENV_DOWN:
        case NPJS_TYPE_JAVAVM:
            break;

        default:
            dprintf(("%s: INTERNAL ERROR!!! INVALID WRAPPER TYPE %x", szFunction, fType));
            ReleaseInt3(0x00c0ffe, 0xffffffff, 0);
            return NULL;
    }

    /*
     * Walk to see if this is actually a pointer to an existing wrapper.
     */
    PNPJNI2ND   pCur;
    for (pCur = pNPJNI2ndHead; pCur; pCur = pCur->pNext)
    {
        if (&pCur->u == pv)
        {
            void *pvRet;
            switch (pCur->fType)
            {
                case NPJS_TYPE_JNIENV:      pvRet = pCur->u.Env.pOrgEnv; break;
                case NPJS_TYPE_JRIENV_DOWN: pvRet = pCur->u.Jri.pOrgEnv; break;
                case NPJS_TYPE_JAVAVM:      ReleaseInt3(0x00c0ffe, 0xffffffff, 1);  break;
                default:
                    dprintf(("%s: Internal error!!!! bad fType %d found in list entry!", szFunction, pCur->fType));
                    ReleaseInt3(0x00c0ffe, 0xffffffff, 2);
                    break;
            }
            dprintf(("%s: Found wrapper for pv=0x%x/fType=%d in list. returns 0x%x", szFunction, pv, fType, pvRet));
            if (pCur->fType != fType)
            {
                dprintf(("%s: type mismatched !!!", szFunction));
                DebugInt3();
            }
            return pvRet;
        }
    }

    /*
     * Must create up JNI wrapper.
     */
    dprintf(("%s: Must create JNI UP wrapper!", szFunction));

    //@todo implememnt JNIEnv and JavaVM UP wrappers.
    dprintf(("%s: F**K!!!!!!!!!!!", szFunction));
    ReleaseInt3(0x00c0ffe, 0xffffffff, 3);

    return NULL;
}


