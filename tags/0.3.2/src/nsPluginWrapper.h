#ifndef __nsPluginWrapper_h__
#define __nsPluginWrapper_h__


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
    #define dprintf(a)      do { } while (0)
#endif

/** Debug Interrupt. */
#ifdef DEBUG
    #define DebugInt3()     asm("int $3")
#else
    #define DebugInt3()     do { } while (0)
#endif

/** Exception chain verify - debug only. */
#ifdef DEBUG
    #define VERIFY_EXCEPTION_CHAIN()     npVerifyExcptChain()
#else
    #define VERIFY_EXCEPTION_CHAIN()     do { } while (0)
#endif


/*******************************************************************************
*   Functions                                                                  *
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
int     npdprintf(const char *pszFormat, ...);
void _Optlink   ReleaseInt3(unsigned uEAX, unsigned uEDX, unsigned uECX);

#ifdef __cplusplus
}
nsresult            downCreateWrapper(void **ppvResult, const void *pvVFT, nsresult rc);
nsresult            downCreateWrapper(void **ppvResult, REFNSIID aIID, nsresult rc);
extern "C" {
nsresult            upCreateWrapper(void **ppvResult, REFNSIID aIID, nsresult rc);
const char *        getIIDCIDName(REFNSIID aIID);
const nsID *        getIIDCIDFromName(const char *pszStrID);
#endif

#ifdef __cplusplus
}
#endif
#endif
