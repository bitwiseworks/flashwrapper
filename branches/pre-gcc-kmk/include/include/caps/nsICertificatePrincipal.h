/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM E:/mozilla/tree/mozilla/caps/idl/nsICertificatePrincipal.idl
 */

#ifndef __gen_nsICertificatePrincipal_h__
#define __gen_nsICertificatePrincipal_h__


#ifndef __gen_nsIPrincipal_h__
#include "nsIPrincipal.h"
#endif

#ifndef __gen_nsIZipReader_h__
#include "nsIZipReader.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
#define NS_CERTIFICATEPRINCIPAL_CONTRACTID "@mozilla.org/certificateprincipal;1"
#define NS_CERTIFICATEPRINCIPAL_CLASSNAME "certificateprincipal"

/* starting interface:    nsICertificatePrincipal */
#define NS_ICERTIFICATEPRINCIPAL_IID_STR "ebfefcd0-25e1-11d2-8160-006008119d7a"

#define NS_ICERTIFICATEPRINCIPAL_IID \
  {0xebfefcd0, 0x25e1, 0x11d2, \
    { 0x81, 0x60, 0x00, 0x60, 0x08, 0x11, 0x9d, 0x7a }}

class NS_NO_VTABLE nsICertificatePrincipal : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ICERTIFICATEPRINCIPAL_IID)

  /* readonly attribute string certificateID; */
  NS_IMETHOD GetCertificateID(char * *aCertificateID) = 0;

  /* attribute string commonName; */
  NS_IMETHOD GetCommonName(char * *aCommonName) = 0;
  NS_IMETHOD SetCommonName(const char * aCommonName) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICERTIFICATEPRINCIPAL \
  NS_IMETHOD GetCertificateID(char * *aCertificateID); \
  NS_IMETHOD GetCommonName(char * *aCommonName); \
  NS_IMETHOD SetCommonName(const char * aCommonName); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICERTIFICATEPRINCIPAL(_to) \
  NS_IMETHOD GetCertificateID(char * *aCertificateID) { return _to GetCertificateID(aCertificateID); } \
  NS_IMETHOD GetCommonName(char * *aCommonName) { return _to GetCommonName(aCommonName); } \
  NS_IMETHOD SetCommonName(const char * aCommonName) { return _to SetCommonName(aCommonName); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICERTIFICATEPRINCIPAL(_to) \
  NS_IMETHOD GetCertificateID(char * *aCertificateID) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCertificateID(aCertificateID); } \
  NS_IMETHOD GetCommonName(char * *aCommonName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCommonName(aCommonName); } \
  NS_IMETHOD SetCommonName(const char * aCommonName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCommonName(aCommonName); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsCertificatePrincipal : public nsICertificatePrincipal
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICERTIFICATEPRINCIPAL

  nsCertificatePrincipal();
  virtual ~nsCertificatePrincipal();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsCertificatePrincipal, nsICertificatePrincipal)

nsCertificatePrincipal::nsCertificatePrincipal()
{
  /* member initializers and constructor code */
}

nsCertificatePrincipal::~nsCertificatePrincipal()
{
  /* destructor code */
}

/* readonly attribute string certificateID; */
NS_IMETHODIMP nsCertificatePrincipal::GetCertificateID(char * *aCertificateID)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute string commonName; */
NS_IMETHODIMP nsCertificatePrincipal::GetCommonName(char * *aCommonName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsCertificatePrincipal::SetCommonName(const char * aCommonName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsICertificatePrincipal_h__ */
