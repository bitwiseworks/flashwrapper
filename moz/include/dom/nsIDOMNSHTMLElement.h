/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/dom/public/idl/html/nsIDOMNSHTMLElement.idl
 */

#ifndef __gen_nsIDOMNSHTMLElement_h__
#define __gen_nsIDOMNSHTMLElement_h__


#ifndef __gen_domstubs_h__
#include "domstubs.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMNSHTMLElement */
#define NS_IDOMNSHTMLELEMENT_IID_STR "da83b2ec-8264-4410-8496-ada3acd2ae42"

#define NS_IDOMNSHTMLELEMENT_IID \
  {0xda83b2ec, 0x8264, 0x4410, \
    { 0x84, 0x96, 0xad, 0xa3, 0xac, 0xd2, 0xae, 0x42 }}

class NS_NO_VTABLE nsIDOMNSHTMLElement : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDOMNSHTMLELEMENT_IID)

  /* readonly attribute long offsetTop; */
  NS_IMETHOD GetOffsetTop(PRInt32 *aOffsetTop) = 0;

  /* readonly attribute long offsetLeft; */
  NS_IMETHOD GetOffsetLeft(PRInt32 *aOffsetLeft) = 0;

  /* readonly attribute long offsetWidth; */
  NS_IMETHOD GetOffsetWidth(PRInt32 *aOffsetWidth) = 0;

  /* readonly attribute long offsetHeight; */
  NS_IMETHOD GetOffsetHeight(PRInt32 *aOffsetHeight) = 0;

  /* readonly attribute nsIDOMElement offsetParent; */
  NS_IMETHOD GetOffsetParent(nsIDOMElement * *aOffsetParent) = 0;

  /* attribute DOMString innerHTML; */
  NS_IMETHOD GetInnerHTML(nsAString & aInnerHTML) = 0;
  NS_IMETHOD SetInnerHTML(const nsAString & aInnerHTML) = 0;

  /* attribute long scrollTop; */
  NS_IMETHOD GetScrollTop(PRInt32 *aScrollTop) = 0;
  NS_IMETHOD SetScrollTop(PRInt32 aScrollTop) = 0;

  /* attribute long scrollLeft; */
  NS_IMETHOD GetScrollLeft(PRInt32 *aScrollLeft) = 0;
  NS_IMETHOD SetScrollLeft(PRInt32 aScrollLeft) = 0;

  /* readonly attribute long scrollHeight; */
  NS_IMETHOD GetScrollHeight(PRInt32 *aScrollHeight) = 0;

  /* readonly attribute long scrollWidth; */
  NS_IMETHOD GetScrollWidth(PRInt32 *aScrollWidth) = 0;

  /* readonly attribute long clientHeight; */
  NS_IMETHOD GetClientHeight(PRInt32 *aClientHeight) = 0;

  /* readonly attribute long clientWidth; */
  NS_IMETHOD GetClientWidth(PRInt32 *aClientWidth) = 0;

  /* [noscript] void scrollIntoView (in boolean top); */
  NS_IMETHOD ScrollIntoView(PRBool top) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMNSHTMLELEMENT \
  NS_IMETHOD GetOffsetTop(PRInt32 *aOffsetTop); \
  NS_IMETHOD GetOffsetLeft(PRInt32 *aOffsetLeft); \
  NS_IMETHOD GetOffsetWidth(PRInt32 *aOffsetWidth); \
  NS_IMETHOD GetOffsetHeight(PRInt32 *aOffsetHeight); \
  NS_IMETHOD GetOffsetParent(nsIDOMElement * *aOffsetParent); \
  NS_IMETHOD GetInnerHTML(nsAString & aInnerHTML); \
  NS_IMETHOD SetInnerHTML(const nsAString & aInnerHTML); \
  NS_IMETHOD GetScrollTop(PRInt32 *aScrollTop); \
  NS_IMETHOD SetScrollTop(PRInt32 aScrollTop); \
  NS_IMETHOD GetScrollLeft(PRInt32 *aScrollLeft); \
  NS_IMETHOD SetScrollLeft(PRInt32 aScrollLeft); \
  NS_IMETHOD GetScrollHeight(PRInt32 *aScrollHeight); \
  NS_IMETHOD GetScrollWidth(PRInt32 *aScrollWidth); \
  NS_IMETHOD GetClientHeight(PRInt32 *aClientHeight); \
  NS_IMETHOD GetClientWidth(PRInt32 *aClientWidth); \
  NS_IMETHOD ScrollIntoView(PRBool top); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMNSHTMLELEMENT(_to) \
  NS_IMETHOD GetOffsetTop(PRInt32 *aOffsetTop) { return _to GetOffsetTop(aOffsetTop); } \
  NS_IMETHOD GetOffsetLeft(PRInt32 *aOffsetLeft) { return _to GetOffsetLeft(aOffsetLeft); } \
  NS_IMETHOD GetOffsetWidth(PRInt32 *aOffsetWidth) { return _to GetOffsetWidth(aOffsetWidth); } \
  NS_IMETHOD GetOffsetHeight(PRInt32 *aOffsetHeight) { return _to GetOffsetHeight(aOffsetHeight); } \
  NS_IMETHOD GetOffsetParent(nsIDOMElement * *aOffsetParent) { return _to GetOffsetParent(aOffsetParent); } \
  NS_IMETHOD GetInnerHTML(nsAString & aInnerHTML) { return _to GetInnerHTML(aInnerHTML); } \
  NS_IMETHOD SetInnerHTML(const nsAString & aInnerHTML) { return _to SetInnerHTML(aInnerHTML); } \
  NS_IMETHOD GetScrollTop(PRInt32 *aScrollTop) { return _to GetScrollTop(aScrollTop); } \
  NS_IMETHOD SetScrollTop(PRInt32 aScrollTop) { return _to SetScrollTop(aScrollTop); } \
  NS_IMETHOD GetScrollLeft(PRInt32 *aScrollLeft) { return _to GetScrollLeft(aScrollLeft); } \
  NS_IMETHOD SetScrollLeft(PRInt32 aScrollLeft) { return _to SetScrollLeft(aScrollLeft); } \
  NS_IMETHOD GetScrollHeight(PRInt32 *aScrollHeight) { return _to GetScrollHeight(aScrollHeight); } \
  NS_IMETHOD GetScrollWidth(PRInt32 *aScrollWidth) { return _to GetScrollWidth(aScrollWidth); } \
  NS_IMETHOD GetClientHeight(PRInt32 *aClientHeight) { return _to GetClientHeight(aClientHeight); } \
  NS_IMETHOD GetClientWidth(PRInt32 *aClientWidth) { return _to GetClientWidth(aClientWidth); } \
  NS_IMETHOD ScrollIntoView(PRBool top) { return _to ScrollIntoView(top); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMNSHTMLELEMENT(_to) \
  NS_IMETHOD GetOffsetTop(PRInt32 *aOffsetTop) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOffsetTop(aOffsetTop); } \
  NS_IMETHOD GetOffsetLeft(PRInt32 *aOffsetLeft) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOffsetLeft(aOffsetLeft); } \
  NS_IMETHOD GetOffsetWidth(PRInt32 *aOffsetWidth) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOffsetWidth(aOffsetWidth); } \
  NS_IMETHOD GetOffsetHeight(PRInt32 *aOffsetHeight) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOffsetHeight(aOffsetHeight); } \
  NS_IMETHOD GetOffsetParent(nsIDOMElement * *aOffsetParent) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOffsetParent(aOffsetParent); } \
  NS_IMETHOD GetInnerHTML(nsAString & aInnerHTML) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInnerHTML(aInnerHTML); } \
  NS_IMETHOD SetInnerHTML(const nsAString & aInnerHTML) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetInnerHTML(aInnerHTML); } \
  NS_IMETHOD GetScrollTop(PRInt32 *aScrollTop) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetScrollTop(aScrollTop); } \
  NS_IMETHOD SetScrollTop(PRInt32 aScrollTop) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetScrollTop(aScrollTop); } \
  NS_IMETHOD GetScrollLeft(PRInt32 *aScrollLeft) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetScrollLeft(aScrollLeft); } \
  NS_IMETHOD SetScrollLeft(PRInt32 aScrollLeft) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetScrollLeft(aScrollLeft); } \
  NS_IMETHOD GetScrollHeight(PRInt32 *aScrollHeight) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetScrollHeight(aScrollHeight); } \
  NS_IMETHOD GetScrollWidth(PRInt32 *aScrollWidth) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetScrollWidth(aScrollWidth); } \
  NS_IMETHOD GetClientHeight(PRInt32 *aClientHeight) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClientHeight(aClientHeight); } \
  NS_IMETHOD GetClientWidth(PRInt32 *aClientWidth) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClientWidth(aClientWidth); } \
  NS_IMETHOD ScrollIntoView(PRBool top) { return !_to ? NS_ERROR_NULL_POINTER : _to->ScrollIntoView(top); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMNSHTMLElement : public nsIDOMNSHTMLElement
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMNSHTMLELEMENT

  nsDOMNSHTMLElement();
  virtual ~nsDOMNSHTMLElement();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMNSHTMLElement, nsIDOMNSHTMLElement)

nsDOMNSHTMLElement::nsDOMNSHTMLElement()
{
  /* member initializers and constructor code */
}

nsDOMNSHTMLElement::~nsDOMNSHTMLElement()
{
  /* destructor code */
}

/* readonly attribute long offsetTop; */
NS_IMETHODIMP nsDOMNSHTMLElement::GetOffsetTop(PRInt32 *aOffsetTop)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long offsetLeft; */
NS_IMETHODIMP nsDOMNSHTMLElement::GetOffsetLeft(PRInt32 *aOffsetLeft)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long offsetWidth; */
NS_IMETHODIMP nsDOMNSHTMLElement::GetOffsetWidth(PRInt32 *aOffsetWidth)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long offsetHeight; */
NS_IMETHODIMP nsDOMNSHTMLElement::GetOffsetHeight(PRInt32 *aOffsetHeight)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIDOMElement offsetParent; */
NS_IMETHODIMP nsDOMNSHTMLElement::GetOffsetParent(nsIDOMElement * *aOffsetParent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute DOMString innerHTML; */
NS_IMETHODIMP nsDOMNSHTMLElement::GetInnerHTML(nsAString & aInnerHTML)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMNSHTMLElement::SetInnerHTML(const nsAString & aInnerHTML)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long scrollTop; */
NS_IMETHODIMP nsDOMNSHTMLElement::GetScrollTop(PRInt32 *aScrollTop)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMNSHTMLElement::SetScrollTop(PRInt32 aScrollTop)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long scrollLeft; */
NS_IMETHODIMP nsDOMNSHTMLElement::GetScrollLeft(PRInt32 *aScrollLeft)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMNSHTMLElement::SetScrollLeft(PRInt32 aScrollLeft)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long scrollHeight; */
NS_IMETHODIMP nsDOMNSHTMLElement::GetScrollHeight(PRInt32 *aScrollHeight)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long scrollWidth; */
NS_IMETHODIMP nsDOMNSHTMLElement::GetScrollWidth(PRInt32 *aScrollWidth)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long clientHeight; */
NS_IMETHODIMP nsDOMNSHTMLElement::GetClientHeight(PRInt32 *aClientHeight)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long clientWidth; */
NS_IMETHODIMP nsDOMNSHTMLElement::GetClientWidth(PRInt32 *aClientWidth)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void scrollIntoView (in boolean top); */
NS_IMETHODIMP nsDOMNSHTMLElement::ScrollIntoView(PRBool top)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMNSHTMLElement_h__ */
