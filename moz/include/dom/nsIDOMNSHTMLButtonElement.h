/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/dom/public/idl/html/nsIDOMNSHTMLButtonElement.idl
 */

#ifndef __gen_nsIDOMNSHTMLButtonElement_h__
#define __gen_nsIDOMNSHTMLButtonElement_h__


#ifndef __gen_domstubs_h__
#include "domstubs.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMNSHTMLButtonElement */
#define NS_IDOMNSHTMLBUTTONELEMENT_IID_STR "6fd344d0-7e5f-11d2-bd91-00805f8ae3f4"

#define NS_IDOMNSHTMLBUTTONELEMENT_IID \
  {0x6fd344d0, 0x7e5f, 0x11d2, \
    { 0xbd, 0x91, 0x00, 0x80, 0x5f, 0x8a, 0xe3, 0xf4 }}

class NS_NO_VTABLE nsIDOMNSHTMLButtonElement : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDOMNSHTMLBUTTONELEMENT_IID)

  /* void blur (); */
  NS_IMETHOD Blur(void) = 0;

  /* void focus (); */
  NS_IMETHOD Focus(void) = 0;

  /* void click (); */
  NS_IMETHOD Click(void) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMNSHTMLBUTTONELEMENT \
  NS_IMETHOD Blur(void); \
  NS_IMETHOD Focus(void); \
  NS_IMETHOD Click(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMNSHTMLBUTTONELEMENT(_to) \
  NS_IMETHOD Blur(void) { return _to Blur(); } \
  NS_IMETHOD Focus(void) { return _to Focus(); } \
  NS_IMETHOD Click(void) { return _to Click(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMNSHTMLBUTTONELEMENT(_to) \
  NS_IMETHOD Blur(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Blur(); } \
  NS_IMETHOD Focus(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Focus(); } \
  NS_IMETHOD Click(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Click(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMNSHTMLButtonElement : public nsIDOMNSHTMLButtonElement
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMNSHTMLBUTTONELEMENT

  nsDOMNSHTMLButtonElement();
  virtual ~nsDOMNSHTMLButtonElement();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMNSHTMLButtonElement, nsIDOMNSHTMLButtonElement)

nsDOMNSHTMLButtonElement::nsDOMNSHTMLButtonElement()
{
  /* member initializers and constructor code */
}

nsDOMNSHTMLButtonElement::~nsDOMNSHTMLButtonElement()
{
  /* destructor code */
}

/* void blur (); */
NS_IMETHODIMP nsDOMNSHTMLButtonElement::Blur()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void focus (); */
NS_IMETHODIMP nsDOMNSHTMLButtonElement::Focus()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void click (); */
NS_IMETHODIMP nsDOMNSHTMLButtonElement::Click()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMNSHTMLButtonElement_h__ */
