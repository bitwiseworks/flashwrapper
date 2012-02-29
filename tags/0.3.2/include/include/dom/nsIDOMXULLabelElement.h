/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/dom/public/idl/xul/nsIDOMXULLabelElement.idl
 */

#ifndef __gen_nsIDOMXULLabelElement_h__
#define __gen_nsIDOMXULLabelElement_h__


#ifndef __gen_nsIDOMXULDescriptionElement_h__
#include "nsIDOMXULDescriptionElement.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMXULLabelElement */
#define NS_IDOMXULLABELELEMENT_IID_STR "f68136d6-1dd1-11b2-a184-a55a337e8507"

#define NS_IDOMXULLABELELEMENT_IID \
  {0xf68136d6, 0x1dd1, 0x11b2, \
    { 0xa1, 0x84, 0xa5, 0x5a, 0x33, 0x7e, 0x85, 0x07 }}

class NS_NO_VTABLE nsIDOMXULLabelElement : public nsIDOMXULDescriptionElement {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDOMXULLABELELEMENT_IID)

  /* attribute boolean accessKey; */
  NS_IMETHOD GetAccessKey(PRBool *aAccessKey) = 0;
  NS_IMETHOD SetAccessKey(PRBool aAccessKey) = 0;

  /* attribute DOMString control; */
  NS_IMETHOD GetControl(nsAString & aControl) = 0;
  NS_IMETHOD SetControl(const nsAString & aControl) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMXULLABELELEMENT \
  NS_IMETHOD GetAccessKey(PRBool *aAccessKey); \
  NS_IMETHOD SetAccessKey(PRBool aAccessKey); \
  NS_IMETHOD GetControl(nsAString & aControl); \
  NS_IMETHOD SetControl(const nsAString & aControl); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMXULLABELELEMENT(_to) \
  NS_IMETHOD GetAccessKey(PRBool *aAccessKey) { return _to GetAccessKey(aAccessKey); } \
  NS_IMETHOD SetAccessKey(PRBool aAccessKey) { return _to SetAccessKey(aAccessKey); } \
  NS_IMETHOD GetControl(nsAString & aControl) { return _to GetControl(aControl); } \
  NS_IMETHOD SetControl(const nsAString & aControl) { return _to SetControl(aControl); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMXULLABELELEMENT(_to) \
  NS_IMETHOD GetAccessKey(PRBool *aAccessKey) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAccessKey(aAccessKey); } \
  NS_IMETHOD SetAccessKey(PRBool aAccessKey) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAccessKey(aAccessKey); } \
  NS_IMETHOD GetControl(nsAString & aControl) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetControl(aControl); } \
  NS_IMETHOD SetControl(const nsAString & aControl) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetControl(aControl); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMXULLabelElement : public nsIDOMXULLabelElement
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMXULLABELELEMENT

  nsDOMXULLabelElement();
  virtual ~nsDOMXULLabelElement();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMXULLabelElement, nsIDOMXULLabelElement)

nsDOMXULLabelElement::nsDOMXULLabelElement()
{
  /* member initializers and constructor code */
}

nsDOMXULLabelElement::~nsDOMXULLabelElement()
{
  /* destructor code */
}

/* attribute boolean accessKey; */
NS_IMETHODIMP nsDOMXULLabelElement::GetAccessKey(PRBool *aAccessKey)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMXULLabelElement::SetAccessKey(PRBool aAccessKey)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute DOMString control; */
NS_IMETHODIMP nsDOMXULLabelElement::GetControl(nsAString & aControl)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMXULLabelElement::SetControl(const nsAString & aControl)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMXULLabelElement_h__ */
