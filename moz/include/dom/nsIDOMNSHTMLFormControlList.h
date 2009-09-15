/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/dom/public/idl/html/nsIDOMNSHTMLFormControlList.idl
 */

#ifndef __gen_nsIDOMNSHTMLFormControlList_h__
#define __gen_nsIDOMNSHTMLFormControlList_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMNSHTMLFormControlList */
#define NS_IDOMNSHTMLFORMCONTROLLIST_IID_STR "a6cf911a-15b3-11d2-932e-00805f8add32"

#define NS_IDOMNSHTMLFORMCONTROLLIST_IID \
  {0xa6cf911a, 0x15b3, 0x11d2, \
    { 0x93, 0x2e, 0x00, 0x80, 0x5f, 0x8a, 0xdd, 0x32 }}

class NS_NO_VTABLE nsIDOMNSHTMLFormControlList : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDOMNSHTMLFORMCONTROLLIST_IID)

  /* nsISupports namedItem (in DOMString name); */
  NS_IMETHOD NamedItem(const nsAString & name, nsISupports **_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMNSHTMLFORMCONTROLLIST \
  NS_IMETHOD NamedItem(const nsAString & name, nsISupports **_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMNSHTMLFORMCONTROLLIST(_to) \
  NS_IMETHOD NamedItem(const nsAString & name, nsISupports **_retval) { return _to NamedItem(name, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMNSHTMLFORMCONTROLLIST(_to) \
  NS_IMETHOD NamedItem(const nsAString & name, nsISupports **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->NamedItem(name, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMNSHTMLFormControlList : public nsIDOMNSHTMLFormControlList
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMNSHTMLFORMCONTROLLIST

  nsDOMNSHTMLFormControlList();
  virtual ~nsDOMNSHTMLFormControlList();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMNSHTMLFormControlList, nsIDOMNSHTMLFormControlList)

nsDOMNSHTMLFormControlList::nsDOMNSHTMLFormControlList()
{
  /* member initializers and constructor code */
}

nsDOMNSHTMLFormControlList::~nsDOMNSHTMLFormControlList()
{
  /* destructor code */
}

/* nsISupports namedItem (in DOMString name); */
NS_IMETHODIMP nsDOMNSHTMLFormControlList::NamedItem(const nsAString & name, nsISupports **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMNSHTMLFormControlList_h__ */
