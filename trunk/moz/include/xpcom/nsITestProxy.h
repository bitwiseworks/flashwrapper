/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/xpcom/proxy/tests/nsITestProxy.idl
 */

#ifndef __gen_nsITestProxy_h__
#define __gen_nsITestProxy_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsITestProxy */
#define NS_ITESTPROXY_IID_STR "1979e980-1cfd-11d3-915e-0000863011c4"

#define NS_ITESTPROXY_IID \
  {0x1979e980, 0x1cfd, 0x11d3, \
    { 0x91, 0x5e, 0x00, 0x00, 0x86, 0x30, 0x11, 0xc4 }}

class NS_NO_VTABLE nsITestProxy : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ITESTPROXY_IID)

  /* long Test (in long p1, in long p2); */
  NS_IMETHOD Test(PRInt32 p1, PRInt32 p2, PRInt32 *_retval) = 0;

  /* void Test2 (); */
  NS_IMETHOD Test2(void) = 0;

  /* void Test3 (in nsISupports p1, out nsISupports p2); */
  NS_IMETHOD Test3(nsISupports *p1, nsISupports **p2) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSITESTPROXY \
  NS_IMETHOD Test(PRInt32 p1, PRInt32 p2, PRInt32 *_retval); \
  NS_IMETHOD Test2(void); \
  NS_IMETHOD Test3(nsISupports *p1, nsISupports **p2); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSITESTPROXY(_to) \
  NS_IMETHOD Test(PRInt32 p1, PRInt32 p2, PRInt32 *_retval) { return _to Test(p1, p2, _retval); } \
  NS_IMETHOD Test2(void) { return _to Test2(); } \
  NS_IMETHOD Test3(nsISupports *p1, nsISupports **p2) { return _to Test3(p1, p2); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSITESTPROXY(_to) \
  NS_IMETHOD Test(PRInt32 p1, PRInt32 p2, PRInt32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Test(p1, p2, _retval); } \
  NS_IMETHOD Test2(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Test2(); } \
  NS_IMETHOD Test3(nsISupports *p1, nsISupports **p2) { return !_to ? NS_ERROR_NULL_POINTER : _to->Test3(p1, p2); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsTestProxy : public nsITestProxy
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSITESTPROXY

  nsTestProxy();
  virtual ~nsTestProxy();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsTestProxy, nsITestProxy)

nsTestProxy::nsTestProxy()
{
  /* member initializers and constructor code */
}

nsTestProxy::~nsTestProxy()
{
  /* destructor code */
}

/* long Test (in long p1, in long p2); */
NS_IMETHODIMP nsTestProxy::Test(PRInt32 p1, PRInt32 p2, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void Test2 (); */
NS_IMETHODIMP nsTestProxy::Test2()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void Test3 (in nsISupports p1, out nsISupports p2); */
NS_IMETHODIMP nsTestProxy::Test3(nsISupports *p1, nsISupports **p2)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsITestProxy_h__ */
