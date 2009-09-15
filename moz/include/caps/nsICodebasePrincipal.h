/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM E:/mozilla/tree/mozilla/caps/idl/nsICodebasePrincipal.idl
 */

#ifndef __gen_nsICodebasePrincipal_h__
#define __gen_nsICodebasePrincipal_h__


#ifndef __gen_nsIPrincipal_h__
#include "nsIPrincipal.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIURI; /* forward declaration */

#define NS_CODEBASEPRINCIPAL_CONTRACTID "@mozilla.org/codebaseprincipal;1"
#define NS_CODEBASEPRINCIPAL_CLASSNAME "codebaseprincipal"

/* starting interface:    nsICodebasePrincipal */
#define NS_ICODEBASEPRINCIPAL_IID_STR "829fe440-25e1-11d2-8160-006008119d7a"

#define NS_ICODEBASEPRINCIPAL_IID \
  {0x829fe440, 0x25e1, 0x11d2, \
    { 0x81, 0x60, 0x00, 0x60, 0x08, 0x11, 0x9d, 0x7a }}

class NS_NO_VTABLE nsICodebasePrincipal : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ICODEBASEPRINCIPAL_IID)

  /* readonly attribute nsIURI URI; */
  NS_IMETHOD GetURI(nsIURI * *aURI) = 0;

  /* readonly attribute string origin; */
  NS_IMETHOD GetOrigin(char * *aOrigin) = 0;

  /* readonly attribute string spec; */
  NS_IMETHOD GetSpec(char * *aSpec) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICODEBASEPRINCIPAL \
  NS_IMETHOD GetURI(nsIURI * *aURI); \
  NS_IMETHOD GetOrigin(char * *aOrigin); \
  NS_IMETHOD GetSpec(char * *aSpec); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICODEBASEPRINCIPAL(_to) \
  NS_IMETHOD GetURI(nsIURI * *aURI) { return _to GetURI(aURI); } \
  NS_IMETHOD GetOrigin(char * *aOrigin) { return _to GetOrigin(aOrigin); } \
  NS_IMETHOD GetSpec(char * *aSpec) { return _to GetSpec(aSpec); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICODEBASEPRINCIPAL(_to) \
  NS_IMETHOD GetURI(nsIURI * *aURI) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetURI(aURI); } \
  NS_IMETHOD GetOrigin(char * *aOrigin) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOrigin(aOrigin); } \
  NS_IMETHOD GetSpec(char * *aSpec) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSpec(aSpec); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsCodebasePrincipal : public nsICodebasePrincipal
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICODEBASEPRINCIPAL

  nsCodebasePrincipal();
  virtual ~nsCodebasePrincipal();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsCodebasePrincipal, nsICodebasePrincipal)

nsCodebasePrincipal::nsCodebasePrincipal()
{
  /* member initializers and constructor code */
}

nsCodebasePrincipal::~nsCodebasePrincipal()
{
  /* destructor code */
}

/* readonly attribute nsIURI URI; */
NS_IMETHODIMP nsCodebasePrincipal::GetURI(nsIURI * *aURI)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute string origin; */
NS_IMETHODIMP nsCodebasePrincipal::GetOrigin(char * *aOrigin)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute string spec; */
NS_IMETHODIMP nsCodebasePrincipal::GetSpec(char * *aSpec)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsICodebasePrincipal_h__ */
