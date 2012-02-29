/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/dom/public/nsIScriptGlobalObjectOwner.idl
 */

#ifndef __gen_nsIScriptGlobalObjectOwner_h__
#define __gen_nsIScriptGlobalObjectOwner_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
#include "nscore.h"
#include "nsIScriptGlobalObject.h"
/**
 * Implemented by any object capable of supplying a nsIScriptGlobalObject.
 * The implentor may create the script global object on demand and is
 * allowed (though not expected) to throw it away on release.
 */
class nsIScriptGlobalObject; /* forward declaration */

class nsIScriptError; /* forward declaration */


/* starting interface:    nsIScriptGlobalObjectOwner */
#define NS_ISCRIPTGLOBALOBJECTOWNER_IID_STR "413e8400-a87f-11d3-afc6-00a024ffc08c"

#define NS_ISCRIPTGLOBALOBJECTOWNER_IID \
  {0x413e8400, 0xa87f, 0x11d3, \
    { 0xaf, 0xc6, 0x00, 0xa0, 0x24, 0xff, 0xc0, 0x8c }}

class NS_NO_VTABLE nsIScriptGlobalObjectOwner : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ISCRIPTGLOBALOBJECTOWNER_IID)

  /**
   * Returns the script global object
   */
  /* nsIScriptGlobalObject getScriptGlobalObject (); */
  NS_IMETHOD GetScriptGlobalObject(nsIScriptGlobalObject **_retval) = 0;

  /**
   * Error notification method. Informs the owner that an error 
   * occurred while a script was being evaluted.
   *
   */
  /* void reportScriptError (in nsIScriptError aError); */
  NS_IMETHOD ReportScriptError(nsIScriptError *aError) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISCRIPTGLOBALOBJECTOWNER \
  NS_IMETHOD GetScriptGlobalObject(nsIScriptGlobalObject **_retval); \
  NS_IMETHOD ReportScriptError(nsIScriptError *aError); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISCRIPTGLOBALOBJECTOWNER(_to) \
  NS_IMETHOD GetScriptGlobalObject(nsIScriptGlobalObject **_retval) { return _to GetScriptGlobalObject(_retval); } \
  NS_IMETHOD ReportScriptError(nsIScriptError *aError) { return _to ReportScriptError(aError); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISCRIPTGLOBALOBJECTOWNER(_to) \
  NS_IMETHOD GetScriptGlobalObject(nsIScriptGlobalObject **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetScriptGlobalObject(_retval); } \
  NS_IMETHOD ReportScriptError(nsIScriptError *aError) { return !_to ? NS_ERROR_NULL_POINTER : _to->ReportScriptError(aError); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsScriptGlobalObjectOwner : public nsIScriptGlobalObjectOwner
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISCRIPTGLOBALOBJECTOWNER

  nsScriptGlobalObjectOwner();
  virtual ~nsScriptGlobalObjectOwner();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsScriptGlobalObjectOwner, nsIScriptGlobalObjectOwner)

nsScriptGlobalObjectOwner::nsScriptGlobalObjectOwner()
{
  /* member initializers and constructor code */
}

nsScriptGlobalObjectOwner::~nsScriptGlobalObjectOwner()
{
  /* destructor code */
}

/* nsIScriptGlobalObject getScriptGlobalObject (); */
NS_IMETHODIMP nsScriptGlobalObjectOwner::GetScriptGlobalObject(nsIScriptGlobalObject **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void reportScriptError (in nsIScriptError aError); */
NS_IMETHODIMP nsScriptGlobalObjectOwner::ReportScriptError(nsIScriptError *aError)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIScriptGlobalObjectOwner_h__ */
