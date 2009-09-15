/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM E:/mozilla/tree/mozilla/caps/idl/nsISignatureVerifier.idl
 */

#ifndef __gen_nsISignatureVerifier_h__
#define __gen_nsISignatureVerifier_h__


#ifndef __gen_nsIPrincipal_h__
#include "nsIPrincipal.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
struct HASHContextStr;

/* starting interface:    nsISignatureVerifier */
#define NS_ISIGNATUREVERIFIER_IID_STR "7bdbdb36-1dd2-11b2-a44f-e303037f214d"

#define NS_ISIGNATUREVERIFIER_IID \
  {0x7bdbdb36, 0x1dd2, 0x11b2, \
    { 0xa4, 0x4f, 0xe3, 0x03, 0x03, 0x7f, 0x21, 0x4d }}

class NS_NO_VTABLE nsISignatureVerifier : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ISIGNATUREVERIFIER_IID)

  enum { VERIFY_OK = 0 };

  enum { VERIFY_ERROR_UNKNOWN_CA = -8172 };

  enum { MD2 = 1 };

  enum { MD5 = 2 };

  enum { SHA1 = 3 };

  enum { MD2_LENGTH = 16U };

  enum { MD5_LENGTH = 16U };

  enum { SHA1_LENGTH = 20U };

  enum { MAX_HASH_LENGTH = 20U };

  /* HASHContextPtr hashBegin (in unsigned long alg); */
  NS_IMETHOD HashBegin(PRUint32 alg, HASHContextStr * *_retval) = 0;

  /* void hashUpdate (in HASHContextPtr id, in string buf, in unsigned long buflen); */
  NS_IMETHOD HashUpdate(HASHContextStr * id, const char *buf, PRUint32 buflen) = 0;

  /* [noscript] void hashEnd (in HASHContextPtr id, out UnsignedCharPtr hash, out unsigned long hashlen, in unsigned long maxLen); */
  NS_IMETHOD HashEnd(HASHContextStr * id, unsigned char * *hash, PRUint32 *hashlen, PRUint32 maxLen) = 0;

  /* nsIPrincipal verifySignature (in string aSignature, in unsigned long aSignatureLen, in string plaintext, in unsigned long plaintextLen, out long errorCode); */
  NS_IMETHOD VerifySignature(const char *aSignature, PRUint32 aSignatureLen, const char *plaintext, PRUint32 plaintextLen, PRInt32 *errorCode, nsIPrincipal **_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISIGNATUREVERIFIER \
  NS_IMETHOD HashBegin(PRUint32 alg, HASHContextStr * *_retval); \
  NS_IMETHOD HashUpdate(HASHContextStr * id, const char *buf, PRUint32 buflen); \
  NS_IMETHOD HashEnd(HASHContextStr * id, unsigned char * *hash, PRUint32 *hashlen, PRUint32 maxLen); \
  NS_IMETHOD VerifySignature(const char *aSignature, PRUint32 aSignatureLen, const char *plaintext, PRUint32 plaintextLen, PRInt32 *errorCode, nsIPrincipal **_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISIGNATUREVERIFIER(_to) \
  NS_IMETHOD HashBegin(PRUint32 alg, HASHContextStr * *_retval) { return _to HashBegin(alg, _retval); } \
  NS_IMETHOD HashUpdate(HASHContextStr * id, const char *buf, PRUint32 buflen) { return _to HashUpdate(id, buf, buflen); } \
  NS_IMETHOD HashEnd(HASHContextStr * id, unsigned char * *hash, PRUint32 *hashlen, PRUint32 maxLen) { return _to HashEnd(id, hash, hashlen, maxLen); } \
  NS_IMETHOD VerifySignature(const char *aSignature, PRUint32 aSignatureLen, const char *plaintext, PRUint32 plaintextLen, PRInt32 *errorCode, nsIPrincipal **_retval) { return _to VerifySignature(aSignature, aSignatureLen, plaintext, plaintextLen, errorCode, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISIGNATUREVERIFIER(_to) \
  NS_IMETHOD HashBegin(PRUint32 alg, HASHContextStr * *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->HashBegin(alg, _retval); } \
  NS_IMETHOD HashUpdate(HASHContextStr * id, const char *buf, PRUint32 buflen) { return !_to ? NS_ERROR_NULL_POINTER : _to->HashUpdate(id, buf, buflen); } \
  NS_IMETHOD HashEnd(HASHContextStr * id, unsigned char * *hash, PRUint32 *hashlen, PRUint32 maxLen) { return !_to ? NS_ERROR_NULL_POINTER : _to->HashEnd(id, hash, hashlen, maxLen); } \
  NS_IMETHOD VerifySignature(const char *aSignature, PRUint32 aSignatureLen, const char *plaintext, PRUint32 plaintextLen, PRInt32 *errorCode, nsIPrincipal **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->VerifySignature(aSignature, aSignatureLen, plaintext, plaintextLen, errorCode, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSignatureVerifier : public nsISignatureVerifier
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISIGNATUREVERIFIER

  nsSignatureVerifier();
  virtual ~nsSignatureVerifier();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSignatureVerifier, nsISignatureVerifier)

nsSignatureVerifier::nsSignatureVerifier()
{
  /* member initializers and constructor code */
}

nsSignatureVerifier::~nsSignatureVerifier()
{
  /* destructor code */
}

/* HASHContextPtr hashBegin (in unsigned long alg); */
NS_IMETHODIMP nsSignatureVerifier::HashBegin(PRUint32 alg, HASHContextStr * *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void hashUpdate (in HASHContextPtr id, in string buf, in unsigned long buflen); */
NS_IMETHODIMP nsSignatureVerifier::HashUpdate(HASHContextStr * id, const char *buf, PRUint32 buflen)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void hashEnd (in HASHContextPtr id, out UnsignedCharPtr hash, out unsigned long hashlen, in unsigned long maxLen); */
NS_IMETHODIMP nsSignatureVerifier::HashEnd(HASHContextStr * id, unsigned char * *hash, PRUint32 *hashlen, PRUint32 maxLen)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIPrincipal verifySignature (in string aSignature, in unsigned long aSignatureLen, in string plaintext, in unsigned long plaintextLen, out long errorCode); */
NS_IMETHODIMP nsSignatureVerifier::VerifySignature(const char *aSignature, PRUint32 aSignatureLen, const char *plaintext, PRUint32 plaintextLen, PRInt32 *errorCode, nsIPrincipal **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

#define SIGNATURE_VERIFIER_CONTRACTID "@mozilla.org/psm;1"

#endif /* __gen_nsISignatureVerifier_h__ */
