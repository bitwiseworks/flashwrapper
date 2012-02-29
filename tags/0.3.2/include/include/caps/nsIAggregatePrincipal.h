/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM E:/mozilla/tree/mozilla/caps/idl/nsIAggregatePrincipal.idl
 */

#ifndef __gen_nsIAggregatePrincipal_h__
#define __gen_nsIAggregatePrincipal_h__


#ifndef __gen_nsIPrincipal_h__
#include "nsIPrincipal.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
#define NS_AGGREGATEPRINCIPAL_CONTRACTID "@mozilla.org/aggregateprincipal;1"
#define NS_AGGREGATEPRINCIPAL_CLASSNAME "aggregateprincipal"

/* starting interface:    nsIAggregatePrincipal */
#define NS_IAGGREGATEPRINCIPAL_IID_STR "1c30a682-1dd2-11b2-ba9b-86a86f300cbc"

#define NS_IAGGREGATEPRINCIPAL_IID \
  {0x1c30a682, 0x1dd2, 0x11b2, \
    { 0xba, 0x9b, 0x86, 0xa8, 0x6f, 0x30, 0x0c, 0xbc }}

class NS_NO_VTABLE nsIAggregatePrincipal : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IAGGREGATEPRINCIPAL_IID)

  /* attribute nsIPrincipal certificate; */
  NS_IMETHOD GetCertificate(nsIPrincipal * *aCertificate) = 0;
  NS_IMETHOD SetCertificate(nsIPrincipal * aCertificate) = 0;

  /* attribute nsIPrincipal codebase; */
  NS_IMETHOD GetCodebase(nsIPrincipal * *aCodebase) = 0;
  NS_IMETHOD SetCodebase(nsIPrincipal * aCodebase) = 0;

  /* readonly attribute nsIPrincipal originalCodebase; */
  NS_IMETHOD GetOriginalCodebase(nsIPrincipal * *aOriginalCodebase) = 0;

  /* readonly attribute nsIPrincipal primaryChild; */
  NS_IMETHOD GetPrimaryChild(nsIPrincipal * *aPrimaryChild) = 0;

  /* void intersect (in nsIPrincipal other); */
  NS_IMETHOD Intersect(nsIPrincipal *other) = 0;

  /* boolean wasCodebaseChanged (); */
  NS_IMETHOD WasCodebaseChanged(PRBool *_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIAGGREGATEPRINCIPAL \
  NS_IMETHOD GetCertificate(nsIPrincipal * *aCertificate); \
  NS_IMETHOD SetCertificate(nsIPrincipal * aCertificate); \
  NS_IMETHOD GetCodebase(nsIPrincipal * *aCodebase); \
  NS_IMETHOD SetCodebase(nsIPrincipal * aCodebase); \
  NS_IMETHOD GetOriginalCodebase(nsIPrincipal * *aOriginalCodebase); \
  NS_IMETHOD GetPrimaryChild(nsIPrincipal * *aPrimaryChild); \
  NS_IMETHOD Intersect(nsIPrincipal *other); \
  NS_IMETHOD WasCodebaseChanged(PRBool *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIAGGREGATEPRINCIPAL(_to) \
  NS_IMETHOD GetCertificate(nsIPrincipal * *aCertificate) { return _to GetCertificate(aCertificate); } \
  NS_IMETHOD SetCertificate(nsIPrincipal * aCertificate) { return _to SetCertificate(aCertificate); } \
  NS_IMETHOD GetCodebase(nsIPrincipal * *aCodebase) { return _to GetCodebase(aCodebase); } \
  NS_IMETHOD SetCodebase(nsIPrincipal * aCodebase) { return _to SetCodebase(aCodebase); } \
  NS_IMETHOD GetOriginalCodebase(nsIPrincipal * *aOriginalCodebase) { return _to GetOriginalCodebase(aOriginalCodebase); } \
  NS_IMETHOD GetPrimaryChild(nsIPrincipal * *aPrimaryChild) { return _to GetPrimaryChild(aPrimaryChild); } \
  NS_IMETHOD Intersect(nsIPrincipal *other) { return _to Intersect(other); } \
  NS_IMETHOD WasCodebaseChanged(PRBool *_retval) { return _to WasCodebaseChanged(_retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIAGGREGATEPRINCIPAL(_to) \
  NS_IMETHOD GetCertificate(nsIPrincipal * *aCertificate) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCertificate(aCertificate); } \
  NS_IMETHOD SetCertificate(nsIPrincipal * aCertificate) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCertificate(aCertificate); } \
  NS_IMETHOD GetCodebase(nsIPrincipal * *aCodebase) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCodebase(aCodebase); } \
  NS_IMETHOD SetCodebase(nsIPrincipal * aCodebase) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCodebase(aCodebase); } \
  NS_IMETHOD GetOriginalCodebase(nsIPrincipal * *aOriginalCodebase) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOriginalCodebase(aOriginalCodebase); } \
  NS_IMETHOD GetPrimaryChild(nsIPrincipal * *aPrimaryChild) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPrimaryChild(aPrimaryChild); } \
  NS_IMETHOD Intersect(nsIPrincipal *other) { return !_to ? NS_ERROR_NULL_POINTER : _to->Intersect(other); } \
  NS_IMETHOD WasCodebaseChanged(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->WasCodebaseChanged(_retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAggregatePrincipal : public nsIAggregatePrincipal
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIAGGREGATEPRINCIPAL

  nsAggregatePrincipal();
  virtual ~nsAggregatePrincipal();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAggregatePrincipal, nsIAggregatePrincipal)

nsAggregatePrincipal::nsAggregatePrincipal()
{
  /* member initializers and constructor code */
}

nsAggregatePrincipal::~nsAggregatePrincipal()
{
  /* destructor code */
}

/* attribute nsIPrincipal certificate; */
NS_IMETHODIMP nsAggregatePrincipal::GetCertificate(nsIPrincipal * *aCertificate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsAggregatePrincipal::SetCertificate(nsIPrincipal * aCertificate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIPrincipal codebase; */
NS_IMETHODIMP nsAggregatePrincipal::GetCodebase(nsIPrincipal * *aCodebase)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsAggregatePrincipal::SetCodebase(nsIPrincipal * aCodebase)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIPrincipal originalCodebase; */
NS_IMETHODIMP nsAggregatePrincipal::GetOriginalCodebase(nsIPrincipal * *aOriginalCodebase)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIPrincipal primaryChild; */
NS_IMETHODIMP nsAggregatePrincipal::GetPrimaryChild(nsIPrincipal * *aPrimaryChild)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void intersect (in nsIPrincipal other); */
NS_IMETHODIMP nsAggregatePrincipal::Intersect(nsIPrincipal *other)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean wasCodebaseChanged (); */
NS_IMETHODIMP nsAggregatePrincipal::WasCodebaseChanged(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAggregatePrincipal_h__ */
