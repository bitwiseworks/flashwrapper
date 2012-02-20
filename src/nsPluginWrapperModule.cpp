/*******************************************************************************
*   Defined Constants And Macros                                               *
*******************************************************************************/
/** define this to make a completely freestanding module (i.e. no XPCOM imports).
 * This is handy when making new builds for existing browsers since this
 * doesn't require to have the .libs for the browser in question.
 * For normal distros, do not use this.
 */
/*#define _NO_XPCOMDLL_ 1 */
/** define this to have minimal dependencies on XPCOM. */
#ifndef _MINIMAL_XPCOMDLL_
# ifdef _NO_XPCOMDLL_
#  define _MINIMAL_XPCOMDLL_ 1
# endif
#endif


/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/
#ifdef _NO_XPCOMDLL_
#define INCL_BASE
#include <os2.h>
#endif
#include "nsCOMPtr.h"
#include "nsIPlugin.h"
#include "nsIGenericFactory.h"
#include "nsILegacyPluginWrapperOS2.h"
#include "nsPluginWrapper.h"

/*******************************************************************************
*   Global Variables                                                           *
*******************************************************************************/
static NS_DEFINE_CID(kPluginCID, NS_PLUGIN_CID);
static NS_DEFINE_CID(kSupportsIID, NS_ISUPPORTS_IID);
static NS_DEFINE_CID(kLegacyPluginWrapperIID, NS_ILEGACYPLUGINWRAPPEROS2_IID);


/**
 * Implements a plugin wrapper factory.
 */
class nsPluginWrapper : public nsILegacyPluginWrapperOS2
{
#ifdef _MINIMAL_XPCOMDLL_
public:
    NS_IMETHOD QueryInterface(REFNSIID aIID, void** aInstancePtr);
    NS_IMETHOD_(nsrefcnt) AddRef(void);
    NS_IMETHOD_(nsrefcnt) Release(void);

protected:
    nsAutoRefCnt mRefCnt;
#else
    NS_DECL_ISUPPORTS
#endif

public:
    nsPluginWrapper();
    static nsresult Create(nsISupports* aOuter, REFNSIID aIID, void** aResult);

    /**
     * PR_FindSymbol(,"NSGetFactory") + NSGetFactory().
     */
    /* void getFactory (in nsIServiceManagerObsolete aServMgr, in REFNSIID aClass, in string aClassName, in string aContractID, in PRLibraryPtr aLibrary, out nsIPlugin aResult); */
    NS_IMETHOD GetFactory(nsIServiceManagerObsolete *aServMgr, REFNSIID aClass, const char *aClassName, const char *aContractID, PRLibrary * aLibrary, nsIPlugin **aResult);

    /**
     * Create a wrapper for the given interface if it's a legacy interface.
     * @returns NS_OK on success.
     * @returns NS_ERROR_INTERFACE if aIID isn't supported. aOut is nsnull.
     * @returns NS_ERROR_FAILURE on other error. aOut undefined.
     * @param   aIID    Interface Identifier of aIn and aOut.
     * @param   aIn     Interface of type aIID which may be a legacy interface
     *                  requiring a wrapper.
     * @param   aOut    The native interface.
     *                  If aIn is a legacy interface, this will be a wrappre.
     *                  If aIn is not a legacy interface, this is aIn.
     */
    /* void maybeWrap (in REFNSIID aIID, in nsISupports aIn, out nsISupports aOut); */
    NS_IMETHOD MaybeWrap(REFNSIID aIID, nsISupports *aIn, nsISupports **aOut);
};



#ifdef _MINIMAL_XPCOMDLL_
NS_IMETHODIMP_(nsrefcnt) nsPluginWrapper::AddRef(void)
{
    return ++mRefCnt;
}

NS_IMETHODIMP_(nsrefcnt) nsPluginWrapper::Release(void)
{
    --mRefCnt;
    if (mRefCnt == 0)
    {
        mRefCnt = 1; /* stabilize */
        delete this;
        return 0;
    }
    return mRefCnt;
}

NS_IMETHODIMP nsPluginWrapper::QueryInterface(REFNSIID aIID, void** aInstancePtr)
{
    if (aIID.Equals(kLegacyPluginWrapperIID))
    {
        //*aInstancePtr = static_cast< nsILegacyPluginWrapperOS2 * > (this);
        *aInstancePtr = (this);
        AddRef();
        return NS_OK;
    }

    if (aIID.Equals(kSupportsIID))
    {
        //*aInstancePtr = static_cast< nsISupports * > (this);
        *aInstancePtr = (this);
        AddRef();
        return NS_OK;
    }

    *aInstancePtr = nsnull;
    return NS_ERROR_NO_INTERFACE;
}

#else
NS_IMPL_ISUPPORTS1(nsPluginWrapper, nsILegacyPluginWrapperOS2)
#endif



/** Factory Constructor Object - do nothing. */
nsPluginWrapper::nsPluginWrapper()
{
    /* Create semaphores at a safe time */
    npXPCOMInitSems();
}

/**
 * Create the factory.
 * @returns NS_OK on success, with aResult containing the requested interface.
 * @returns NS_ERROR_* on failure, aResult is nsnull.
 */
nsresult nsPluginWrapper::Create(nsISupports* aOuter, REFNSIID aIID, void** aResult)
{
    *aResult = nsnull;
#ifndef _MINIMAL_XPCOMDLL_
    NS_PRECONDITION(aOuter == nsnull, "no aggregation");
#endif
    if (aOuter)
        return NS_ERROR_NO_AGGREGATION;

#ifdef _MINIMAL_XPCOMDLL_
    nsILegacyPluginWrapperOS2 *
#else
    nsCOMPtr<nsILegacyPluginWrapperOS2>
#endif
        factory  = new nsPluginWrapper();
    if (!factory)
        return NS_ERROR_OUT_OF_MEMORY;

    return factory->QueryInterface(aIID, aResult);
}


/**
 * This is where we create the initial wrapper.
 */
NS_IMETHODIMP nsPluginWrapper::GetFactory(nsIServiceManagerObsolete *aServMgr,
                                                 REFNSIID aClass,
                                                 const char *aClassName,
                                                 const char *aContractID,
                                                 PRLibrary * aLibrary,
                                                 nsIPlugin **aResult)
{
    nsresult rc;
    dprintf(("nsPluginWrapper::CreatePlugin: enter"));

    /*
     * Do NSGetFactory.
     */
#ifdef NPODIN
    rc = NS_OK;
        //npGenericNSGetFactory(aServMgr, aClass, aClassName, aContractID, aLibrary, aResult);
#else
    rc = npXPCOMGenericGetFactory(aServMgr, aClass, aClassName, aContractID, aLibrary, aResult);
#endif
    dprintf(("nsPluginWrapper::CreatePlugin: npXPCOMGenericGetFactory -> rc=%d and *aResult=%x",
             rc, *aResult));

    return rc;
}


/**
 * Create a wrapper for the given interface if it's a legacy interface.
 * @returns NS_OK on success.
 * @returns NS_ERROR_NO_INTERFACE if aIID isn't supported. aOut is nsnull.
 * @returns NS_ERROR_FAILURE on other error. aOut undefined.
 * @param   aIID    Interface Identifier of aIn and aOut.
 * @param   aIn     Interface of type aIID which may be a legacy interface
 *                  requiring a wrapper.
 * @param   aOut    The native interface.
 *                  If aIn is a legacy interface, this will be a wrappre.
 *                  If aIn is not a legacy interface, this is aIn.
 * @remark  Typically used for the flash plugin.
 */
NS_IMETHODIMP nsPluginWrapper::MaybeWrap(REFNSIID aIID, nsISupports *aIn, nsISupports **aOut)
{
   return npXPCOMGenericMaybeWrap(aIID, aIn, aOut);
}




/** Component Info */
static const nsModuleComponentInfo gComponentInfo[] =
{
    {
        "XPCOM Plugin Wrapper",
        NS_LEGACY_PLUGIN_WRAPPER_CID,
        NS_LEGACY_PLUGIN_WRAPPER_CONTRACTID,
        nsPluginWrapper::Create
    }
};



/** NSGetModule(); */
NS_IMPL_NSGETMODULE(nsPluginWrapperModule, gComponentInfo)


#ifdef _NO_XPCOMDLL_
/**
 * Find the start of the filename.
 *
 * @returns pointer to start of filename.
 * @param   pszPath Path to examin.
 */
static char *GetBasename(char *pszPath)
{
    char *pszName;
    char *psz;

    pszName = strrchr(pszPath, '\\');
    psz = strrchr(pszName ? pszName : pszPath, '/');
    if (psz)
        pszName = psz;
    if (!pszName)
        pszName = strchr(pszPath, ':');
    if (pszName)
        pszName++;
    else
        pszName = pszPath;

    return pszName;
}

nsresult NS_NewGenericModule2(nsModuleInfo *info, nsIModule* *result)
{
    HMODULE     hmod;
    nsresult    rc = NS_ERROR_UNEXPECTED;
    APIRET      rc2;

    /*
     * Because of the LIBPATHSTRICT feature we have to specific the full path
     * of the DLL to make sure we get the right handle.
     * (We're of course making assumptions about the executable and the XPCOM.DLL
     * begin at the same location.)
     */
    char    szXPCOM[CCHMAXPATH];
    char *  pszName;
    PPIB    ppib;
    PTIB    ptib;
    DosGetInfoBlocks(&ptib, &ppib);
    pszName = GetBasename(strcpy(szXPCOM, ppib->pib_pchcmd));
    strcpy(pszName, "XPCOM");
    rc2 = DosLoadModule(NULL, 0, (PCSZ)szXPCOM, &hmod);
    if (!rc2)
    {
        NS_COM nsresult (* pfnNS_NewGenericModule2)(nsModuleInfo *info, nsIModule* *result);

        /* demangled name: NS_NewGenericModule2(nsModuleInfo*, nsIModule**) */
        rc2 = DosQueryProcAddr(hmod, 0, (PCSZ)"__Z20NS_NewGenericModule2P12nsModuleInfoPP9nsIModule",
                               (PFN*)&pfnNS_NewGenericModule2);
        if (!rc2)
             rc = pfnNS_NewGenericModule2(info, result);
        #ifdef DEBUG
        else
            fprintf(stderr, "ipluginw: DosQueryProcAddr -> %ld\n", rc2);
        #endif
        DosFreeModule(hmod);
    }
    #ifdef DEBUG
    else
        fprintf(stderr, "ipluginw: DosLoadModule -> %ld\n", rc2);
    if (rc)
        fprintf(stderr, "ipluginw: NS_NewGenericModule2 -> %#x\n", rc);
    #endif

    return rc;
}
#endif


