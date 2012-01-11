/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM E:/mozilla/tree/mozilla/caps/idl/nsIPrincipal.idl
 */

#ifndef __gen_nsIPrincipal_h__
#define __gen_nsIPrincipal_h__


#ifndef __gen_nsISerializable_h__
#include "nsISerializable.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
struct JSPrincipals;

/* starting interface:    nsIPrincipal */
#define NS_IPRINCIPAL_IID_STR "ff9313d0-25e1-11d2-8160-006008119d7a"

#define NS_IPRINCIPAL_IID \
  {0xff9313d0, 0x25e1, 0x11d2, \
    { 0x81, 0x60, 0x00, 0x60, 0x08, 0x11, 0x9d, 0x7a }}

class NS_NO_VTABLE nsIPrincipal : public nsISerializable {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IPRINCIPAL_IID)

  enum { ENABLE_DENIED = 1 };

  enum { ENABLE_UNKNOWN = 2 };

  enum { ENABLE_WITH_USER_PERMISSION = 3 };

  enum { ENABLE_GRANTED = 4 };

  /* string ToString (); */
  NS_IMETHOD ToString(char **_retval) = 0;

  /* string ToUserVisibleString (); */
  NS_IMETHOD ToUserVisibleString(char **_retval) = 0;

  /* void GetPreferences (out string prefName, out string id, out string grantedList, out string deniedList); */
  NS_IMETHOD GetPreferences(char **prefName, char **id, char **grantedList, char **deniedList) = 0;

  /* boolean Equals (in nsIPrincipal other); */
  NS_IMETHOD Equals(nsIPrincipal *other, PRBool *_retval) = 0;

  /* unsigned long HashValue (); */
  NS_IMETHOD HashValue(PRUint32 *_retval) = 0;

  /* JSPrincipals GetJSPrincipals (); */
  NS_IMETHOD GetJSPrincipals(JSPrincipals * *_retval) = 0;

  /* short CanEnableCapability (in string capability); */
  NS_IMETHOD CanEnableCapability(const char *capability, PRInt16 *_retval) = 0;

  /* void SetCanEnableCapability (in string capability, in short canEnable); */
  NS_IMETHOD SetCanEnableCapability(const char *capability, PRInt16 canEnable) = 0;

  /* boolean IsCapabilityEnabled (in string capability, in voidPtr annotation); */
  NS_IMETHOD IsCapabilityEnabled(const char *capability, void * annotation, PRBool *_retval) = 0;

  /* void EnableCapability (in string capability, inout voidPtr annotation); */
  NS_IMETHOD EnableCapability(const char *capability, void * *annotation) = 0;

  /* void RevertCapability (in string capability, inout voidPtr annotation); */
  NS_IMETHOD RevertCapability(const char *capability, void * *annotation) = 0;

  /* void DisableCapability (in string capability, inout voidPtr annotation); */
  NS_IMETHOD DisableCapability(const char *capability, void * *annotation) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIPRINCIPAL \
  NS_IMETHOD ToString(char **_retval); \
  NS_IMETHOD ToUserVisibleString(char **_retval); \
  NS_IMETHOD GetPreferences(char **prefName, char **id, char **grantedList, char **deniedList); \
  NS_IMETHOD Equals(nsIPrincipal *other, PRBool *_retval); \
  NS_IMETHOD HashValue(PRUint32 *_retval); \
  NS_IMETHOD GetJSPrincipals(JSPrincipals * *_retval); \
  NS_IMETHOD CanEnableCapability(const char *capability, PRInt16 *_retval); \
  NS_IMETHOD SetCanEnableCapability(const char *capability, PRInt16 canEnable); \
  NS_IMETHOD IsCapabilityEnabled(const char *capability, void * annotation, PRBool *_retval); \
  NS_IMETHOD EnableCapability(const char *capability, void * *annotation); \
  NS_IMETHOD RevertCapability(const char *capability, void * *annotation); \
  NS_IMETHOD DisableCapability(const char *capability, void * *annotation); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIPRINCIPAL(_to) \
  NS_IMETHOD ToString(char **_retval) { return _to ToString(_retval); } \
  NS_IMETHOD ToUserVisibleString(char **_retval) { return _to ToUserVisibleString(_retval); } \
  NS_IMETHOD GetPreferences(char **prefName, char **id, char **grantedList, char **deniedList) { return _to GetPreferences(prefName, id, grantedList, deniedList); } \
  NS_IMETHOD Equals(nsIPrincipal *other, PRBool *_retval) { return _to Equals(other, _retval); } \
  NS_IMETHOD HashValue(PRUint32 *_retval) { return _to HashValue(_retval); } \
  NS_IMETHOD GetJSPrincipals(JSPrincipals * *_retval) { return _to GetJSPrincipals(_retval); } \
  NS_IMETHOD CanEnableCapability(const char *capability, PRInt16 *_retval) { return _to CanEnableCapability(capability, _retval); } \
  NS_IMETHOD SetCanEnableCapability(const char *capability, PRInt16 canEnable) { return _to SetCanEnableCapability(capability, canEnable); } \
  NS_IMETHOD IsCapabilityEnabled(const char *capability, void * annotation, PRBool *_retval) { return _to IsCapabilityEnabled(capability, annotation, _retval); } \
  NS_IMETHOD EnableCapability(const char *capability, void * *annotation) { return _to EnableCapability(capability, annotation); } \
  NS_IMETHOD RevertCapability(const char *capability, void * *annotation) { return _to RevertCapability(capability, annotation); } \
  NS_IMETHOD DisableCapability(const char *capability, void * *annotation) { return _to DisableCapability(capability, annotation); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIPRINCIPAL(_to) \
  NS_IMETHOD ToString(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->ToString(_retval); } \
  NS_IMETHOD ToUserVisibleString(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->ToUserVisibleString(_retval); } \
  NS_IMETHOD GetPreferences(char **prefName, char **id, char **grantedList, char **deniedList) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPreferences(prefName, id, grantedList, deniedList); } \
  NS_IMETHOD Equals(nsIPrincipal *other, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Equals(other, _retval); } \
  NS_IMETHOD HashValue(PRUint32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->HashValue(_retval); } \
  NS_IMETHOD GetJSPrincipals(JSPrincipals * *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetJSPrincipals(_retval); } \
  NS_IMETHOD CanEnableCapability(const char *capability, PRInt16 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CanEnableCapability(capability, _retval); } \
  NS_IMETHOD SetCanEnableCapability(const char *capability, PRInt16 canEnable) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCanEnableCapability(capability, canEnable); } \
  NS_IMETHOD IsCapabilityEnabled(const char *capability, void * annotation, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsCapabilityEnabled(capability, annotation, _retval); } \
  NS_IMETHOD EnableCapability(const char *capability, void * *annotation) { return !_to ? NS_ERROR_NULL_POINTER : _to->EnableCapability(capability, annotation); } \
  NS_IMETHOD RevertCapability(const char *capability, void * *annotation) { return !_to ? NS_ERROR_NULL_POINTER : _to->RevertCapability(capability, annotation); } \
  NS_IMETHOD DisableCapability(const char *capability, void * *annotation) { return !_to ? NS_ERROR_NULL_POINTER : _to->DisableCapability(capability, annotation); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsPrincipal : public nsIPrincipal
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIPRINCIPAL

  nsPrincipal();
  virtual ~nsPrincipal();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsPrincipal, nsIPrincipal)

nsPrincipal::nsPrincipal()
{
  /* member initializers and constructor code */
}

nsPrincipal::~nsPrincipal()
{
  /* destructor code */
}

/* string ToString (); */
NS_IMETHODIMP nsPrincipal::ToString(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string ToUserVisibleString (); */
NS_IMETHODIMP nsPrincipal::ToUserVisibleString(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetPreferences (out string prefName, out string id, out string grantedList, out string deniedList); */
NS_IMETHODIMP nsPrincipal::GetPreferences(char **prefName, char **id, char **grantedList, char **deniedList)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean Equals (in nsIPrincipal other); */
NS_IMETHODIMP nsPrincipal::Equals(nsIPrincipal *other, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* unsigned long HashValue (); */
NS_IMETHODIMP nsPrincipal::HashValue(PRUint32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* JSPrincipals GetJSPrincipals (); */
NS_IMETHODIMP nsPrincipal::GetJSPrincipals(JSPrincipals * *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* short CanEnableCapability (in string capability); */
NS_IMETHODIMP nsPrincipal::CanEnableCapability(const char *capability, PRInt16 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetCanEnableCapability (in string capability, in short canEnable); */
NS_IMETHODIMP nsPrincipal::SetCanEnableCapability(const char *capability, PRInt16 canEnable)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean IsCapabilityEnabled (in string capability, in voidPtr annotation); */
NS_IMETHODIMP nsPrincipal::IsCapabilityEnabled(const char *capability, void * annotation, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void EnableCapability (in string capability, inout voidPtr annotation); */
NS_IMETHODIMP nsPrincipal::EnableCapability(const char *capability, void * *annotation)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void RevertCapability (in string capability, inout voidPtr annotation); */
NS_IMETHODIMP nsPrincipal::RevertCapability(const char *capability, void * *annotation)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void DisableCapability (in string capability, inout voidPtr annotation); */
NS_IMETHODIMP nsPrincipal::DisableCapability(const char *capability, void * *annotation)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIPrincipal_h__ */
