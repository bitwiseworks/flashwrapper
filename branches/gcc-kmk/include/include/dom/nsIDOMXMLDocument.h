/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/dom/public/idl/core/nsIDOMXMLDocument.idl
 */

#ifndef __gen_nsIDOMXMLDocument_h__
#define __gen_nsIDOMXMLDocument_h__


#ifndef __gen_nsIDOMDocument_h__
#include "nsIDOMDocument.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMXMLDocument */
#define NS_IDOMXMLDOCUMENT_IID_STR "8816d003-e7c8-4065-8827-829b8d07b6e0"

#define NS_IDOMXMLDOCUMENT_IID \
  {0x8816d003, 0xe7c8, 0x4065, \
    { 0x88, 0x27, 0x82, 0x9b, 0x8d, 0x07, 0xb6, 0xe0 }}

class NS_NO_VTABLE nsIDOMXMLDocument : public nsIDOMDocument {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDOMXMLDOCUMENT_IID)

  /* void load (in DOMString url); */
  NS_IMETHOD Load(const nsAString & url) = 0;

  /**
  * Evaluate FIXptr expression. FIXptr is a W3C NOTE, see
  *
  * http://lists.w3.org/Archives/Public/www-xml-linking-comments/2001AprJun/att-0074/01-NOTE-FIXptr-20010425.htm
  *
  * @param  expression FIXptr string.
  * @return            The range object that results from evaluation
  */
  /* nsIDOMRange evaluateFIXptr (in DOMString expression); */
  NS_IMETHOD EvaluateFIXptr(const nsAString & expression, nsIDOMRange **_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMXMLDOCUMENT \
  NS_IMETHOD Load(const nsAString & url); \
  NS_IMETHOD EvaluateFIXptr(const nsAString & expression, nsIDOMRange **_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMXMLDOCUMENT(_to) \
  NS_IMETHOD Load(const nsAString & url) { return _to Load(url); } \
  NS_IMETHOD EvaluateFIXptr(const nsAString & expression, nsIDOMRange **_retval) { return _to EvaluateFIXptr(expression, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMXMLDOCUMENT(_to) \
  NS_IMETHOD Load(const nsAString & url) { return !_to ? NS_ERROR_NULL_POINTER : _to->Load(url); } \
  NS_IMETHOD EvaluateFIXptr(const nsAString & expression, nsIDOMRange **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->EvaluateFIXptr(expression, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMXMLDocument : public nsIDOMXMLDocument
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMXMLDOCUMENT

  nsDOMXMLDocument();
  virtual ~nsDOMXMLDocument();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMXMLDocument, nsIDOMXMLDocument)

nsDOMXMLDocument::nsDOMXMLDocument()
{
  /* member initializers and constructor code */
}

nsDOMXMLDocument::~nsDOMXMLDocument()
{
  /* destructor code */
}

/* void load (in DOMString url); */
NS_IMETHODIMP nsDOMXMLDocument::Load(const nsAString & url)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIDOMRange evaluateFIXptr (in DOMString expression); */
NS_IMETHODIMP nsDOMXMLDocument::EvaluateFIXptr(const nsAString & expression, nsIDOMRange **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMXMLDocument_h__ */
