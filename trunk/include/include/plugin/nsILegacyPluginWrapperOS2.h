/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM E:/mozilla/Tree4/mozilla/modules/plugin/base/public/nsILegacyPluginWrapperOS2.idl
 */

#ifndef __gen_nsILegacyPluginWrapperOS2_h__
#define __gen_nsILegacyPluginWrapperOS2_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nspluginroot_h__
#include "nspluginroot.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
#include "nsplugindefs.h"
// {7c4f689b-8c2a-11d7-911e-0003ffba5169}
#define NS_LEGACY_PLUGIN_WRAPPER_CID \
{ 0x7c4f689b, 0x8c2a, 0x11d7, { 0x91, 0x1e, 0x00, 0x03, 0xff, 0xba, 0x51, 0x69 } }
#define NS_LEGACY_PLUGIN_WRAPPER_CONTRACTID "@mozilla.org/plugin/legacypluginwrapper;1"
struct PRLibrary;
class nsIServiceManagerObsolete; /* forward declaration */

class nsIPlugin; /* forward declaration */


/* starting interface:    nsILegacyPluginWrapperOS2 */
#define NS_ILEGACYPLUGINWRAPPEROS2_IID_STR "7c4f689b-8c2a-11d7-911e-0003ffba5169"

#define NS_ILEGACYPLUGINWRAPPEROS2_IID \
  {0x7c4f689b, 0x8c2a, 0x11d7, \
    { 0x91, 0x1e, 0x00, 0x03, 0xff, 0xba, 0x51, 0x69 }}

class NS_NO_VTABLE nsILegacyPluginWrapperOS2 : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ILEGACYPLUGINWRAPPEROS2_IID)

  /**
     * PR_FindSymbol(,"NSGetFactory") + NSGetFactory().
     */
  /* void getFactory (in nsIServiceManagerObsolete aServMgr, in REFNSIID aClass, in string aClassName, in string aContractID, in PRLibraryPtr aLibrary, out nsIPlugin aResult); */
  NS_IMETHOD GetFactory(nsIServiceManagerObsolete *aServMgr, REFNSIID aClass, const char *aClassName, const char *aContractID, PRLibrary * aLibrary, nsIPlugin **aResult) = 0;

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
  /* void maybeWrap (in REFNSIID aIID, in nsISupports aIn, out nsISupports aOut); */
  NS_IMETHOD MaybeWrap(REFNSIID aIID, nsISupports *aIn, nsISupports **aOut) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILEGACYPLUGINWRAPPEROS2 \
  NS_IMETHOD GetFactory(nsIServiceManagerObsolete *aServMgr, REFNSIID aClass, const char *aClassName, const char *aContractID, PRLibrary * aLibrary, nsIPlugin **aResult); \
  NS_IMETHOD MaybeWrap(REFNSIID aIID, nsISupports *aIn, nsISupports **aOut); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILEGACYPLUGINWRAPPEROS2(_to) \
  NS_IMETHOD GetFactory(nsIServiceManagerObsolete *aServMgr, REFNSIID aClass, const char *aClassName, const char *aContractID, PRLibrary * aLibrary, nsIPlugin **aResult) { return _to GetFactory(aServMgr, aClass, aClassName, aContractID, aLibrary, aResult); } \
  NS_IMETHOD MaybeWrap(REFNSIID aIID, nsISupports *aIn, nsISupports **aOut) { return _to MaybeWrap(aIID, aIn, aOut); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILEGACYPLUGINWRAPPEROS2(_to) \
  NS_IMETHOD GetFactory(nsIServiceManagerObsolete *aServMgr, REFNSIID aClass, const char *aClassName, const char *aContractID, PRLibrary * aLibrary, nsIPlugin **aResult) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFactory(aServMgr, aClass, aClassName, aContractID, aLibrary, aResult); } \
  NS_IMETHOD MaybeWrap(REFNSIID aIID, nsISupports *aIn, nsISupports **aOut) { return !_to ? NS_ERROR_NULL_POINTER : _to->MaybeWrap(aIID, aIn, aOut); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLegacyPluginWrapperOS2 : public nsILegacyPluginWrapperOS2
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILEGACYPLUGINWRAPPEROS2

  nsLegacyPluginWrapperOS2();
  virtual ~nsLegacyPluginWrapperOS2();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLegacyPluginWrapperOS2, nsILegacyPluginWrapperOS2)

nsLegacyPluginWrapperOS2::nsLegacyPluginWrapperOS2()
{
  /* member initializers and constructor code */
}

nsLegacyPluginWrapperOS2::~nsLegacyPluginWrapperOS2()
{
  /* destructor code */
}

/* void getFactory (in nsIServiceManagerObsolete aServMgr, in REFNSIID aClass, in string aClassName, in string aContractID, in PRLibraryPtr aLibrary, out nsIPlugin aResult); */
NS_IMETHODIMP nsLegacyPluginWrapperOS2::GetFactory(nsIServiceManagerObsolete *aServMgr, REFNSIID aClass, const char *aClassName, const char *aContractID, PRLibrary * aLibrary, nsIPlugin **aResult)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void maybeWrap (in REFNSIID aIID, in nsISupports aIn, out nsISupports aOut); */
NS_IMETHODIMP nsLegacyPluginWrapperOS2::MaybeWrap(REFNSIID aIID, nsISupports *aIn, nsISupports **aOut)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsILegacyPluginWrapperOS2_h__ */
