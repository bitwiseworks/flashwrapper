/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/dom/public/idl/base/nsIDOMCrypto.idl
 */

#ifndef __gen_nsIDOMCrypto_h__
#define __gen_nsIDOMCrypto_h__


#ifndef __gen_domstubs_h__
#include "domstubs.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMCrypto */
#define NS_IDOMCRYPTO_IID_STR "f45efbe0-1d52-11d4-8a7c-006008c844c3"

#define NS_IDOMCRYPTO_IID \
  {0xf45efbe0, 0x1d52, 0x11d4, \
    { 0x8a, 0x7c, 0x00, 0x60, 0x08, 0xc8, 0x44, 0xc3 }}

class NS_NO_VTABLE nsIDOMCrypto : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDOMCRYPTO_IID)

  /* readonly attribute DOMString version; */
  NS_IMETHOD GetVersion(nsAString & aVersion) = 0;

  /* nsIDOMCRMFObject generateCRMFRequest (); */
  NS_IMETHOD GenerateCRMFRequest(nsIDOMCRMFObject **_retval) = 0;

  /* DOMString importUserCertificates (in DOMString nickname, in DOMString cmmfResponse, in boolean doForcedBackup); */
  NS_IMETHOD ImportUserCertificates(const nsAString & nickname, const nsAString & cmmfResponse, PRBool doForcedBackup, nsAString & _retval) = 0;

  /* DOMString popChallengeResponse (in DOMString challenge); */
  NS_IMETHOD PopChallengeResponse(const nsAString & challenge, nsAString & _retval) = 0;

  /* DOMString random (in long numBytes); */
  NS_IMETHOD Random(PRInt32 numBytes, nsAString & _retval) = 0;

  /* DOMString signText (); */
  NS_IMETHOD SignText(nsAString & _retval) = 0;

  /* void alert (in DOMString message); */
  NS_IMETHOD Alert(const nsAString & message) = 0;

  /* void logout (); */
  NS_IMETHOD Logout(void) = 0;

  /* void disableRightClick (); */
  NS_IMETHOD DisableRightClick(void) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMCRYPTO \
  NS_IMETHOD GetVersion(nsAString & aVersion); \
  NS_IMETHOD GenerateCRMFRequest(nsIDOMCRMFObject **_retval); \
  NS_IMETHOD ImportUserCertificates(const nsAString & nickname, const nsAString & cmmfResponse, PRBool doForcedBackup, nsAString & _retval); \
  NS_IMETHOD PopChallengeResponse(const nsAString & challenge, nsAString & _retval); \
  NS_IMETHOD Random(PRInt32 numBytes, nsAString & _retval); \
  NS_IMETHOD SignText(nsAString & _retval); \
  NS_IMETHOD Alert(const nsAString & message); \
  NS_IMETHOD Logout(void); \
  NS_IMETHOD DisableRightClick(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMCRYPTO(_to) \
  NS_IMETHOD GetVersion(nsAString & aVersion) { return _to GetVersion(aVersion); } \
  NS_IMETHOD GenerateCRMFRequest(nsIDOMCRMFObject **_retval) { return _to GenerateCRMFRequest(_retval); } \
  NS_IMETHOD ImportUserCertificates(const nsAString & nickname, const nsAString & cmmfResponse, PRBool doForcedBackup, nsAString & _retval) { return _to ImportUserCertificates(nickname, cmmfResponse, doForcedBackup, _retval); } \
  NS_IMETHOD PopChallengeResponse(const nsAString & challenge, nsAString & _retval) { return _to PopChallengeResponse(challenge, _retval); } \
  NS_IMETHOD Random(PRInt32 numBytes, nsAString & _retval) { return _to Random(numBytes, _retval); } \
  NS_IMETHOD SignText(nsAString & _retval) { return _to SignText(_retval); } \
  NS_IMETHOD Alert(const nsAString & message) { return _to Alert(message); } \
  NS_IMETHOD Logout(void) { return _to Logout(); } \
  NS_IMETHOD DisableRightClick(void) { return _to DisableRightClick(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMCRYPTO(_to) \
  NS_IMETHOD GetVersion(nsAString & aVersion) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetVersion(aVersion); } \
  NS_IMETHOD GenerateCRMFRequest(nsIDOMCRMFObject **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GenerateCRMFRequest(_retval); } \
  NS_IMETHOD ImportUserCertificates(const nsAString & nickname, const nsAString & cmmfResponse, PRBool doForcedBackup, nsAString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->ImportUserCertificates(nickname, cmmfResponse, doForcedBackup, _retval); } \
  NS_IMETHOD PopChallengeResponse(const nsAString & challenge, nsAString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->PopChallengeResponse(challenge, _retval); } \
  NS_IMETHOD Random(PRInt32 numBytes, nsAString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Random(numBytes, _retval); } \
  NS_IMETHOD SignText(nsAString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->SignText(_retval); } \
  NS_IMETHOD Alert(const nsAString & message) { return !_to ? NS_ERROR_NULL_POINTER : _to->Alert(message); } \
  NS_IMETHOD Logout(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Logout(); } \
  NS_IMETHOD DisableRightClick(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->DisableRightClick(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMCrypto : public nsIDOMCrypto
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMCRYPTO

  nsDOMCrypto();
  virtual ~nsDOMCrypto();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMCrypto, nsIDOMCrypto)

nsDOMCrypto::nsDOMCrypto()
{
  /* member initializers and constructor code */
}

nsDOMCrypto::~nsDOMCrypto()
{
  /* destructor code */
}

/* readonly attribute DOMString version; */
NS_IMETHODIMP nsDOMCrypto::GetVersion(nsAString & aVersion)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIDOMCRMFObject generateCRMFRequest (); */
NS_IMETHODIMP nsDOMCrypto::GenerateCRMFRequest(nsIDOMCRMFObject **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* DOMString importUserCertificates (in DOMString nickname, in DOMString cmmfResponse, in boolean doForcedBackup); */
NS_IMETHODIMP nsDOMCrypto::ImportUserCertificates(const nsAString & nickname, const nsAString & cmmfResponse, PRBool doForcedBackup, nsAString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* DOMString popChallengeResponse (in DOMString challenge); */
NS_IMETHODIMP nsDOMCrypto::PopChallengeResponse(const nsAString & challenge, nsAString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* DOMString random (in long numBytes); */
NS_IMETHODIMP nsDOMCrypto::Random(PRInt32 numBytes, nsAString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* DOMString signText (); */
NS_IMETHODIMP nsDOMCrypto::SignText(nsAString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void alert (in DOMString message); */
NS_IMETHODIMP nsDOMCrypto::Alert(const nsAString & message)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void logout (); */
NS_IMETHODIMP nsDOMCrypto::Logout()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void disableRightClick (); */
NS_IMETHODIMP nsDOMCrypto::DisableRightClick()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMCrypto_h__ */
