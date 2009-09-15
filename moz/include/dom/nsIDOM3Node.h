/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/dom/public/idl/core/nsIDOM3Node.idl
 */

#ifndef __gen_nsIDOM3Node_h__
#define __gen_nsIDOM3Node_h__


#ifndef __gen_domstubs_h__
#include "domstubs.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOM3Node */
#define NS_IDOM3NODE_IID_STR "29fb2a18-1dd2-11b2-8dd9-a6fd5d5ad12f"

#define NS_IDOM3NODE_IID \
  {0x29fb2a18, 0x1dd2, 0x11b2, \
    { 0x8d, 0xd9, 0xa6, 0xfd, 0x5d, 0x5a, 0xd1, 0x2f }}

class NS_NO_VTABLE nsIDOM3Node : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDOM3NODE_IID)

  /* readonly attribute DOMString baseURI; */
  NS_IMETHOD GetBaseURI(nsAString & aBaseURI) = 0;

  /* unsigned short compareDocumentPosition (in nsIDOMNode other); */
  NS_IMETHOD CompareDocumentPosition(nsIDOMNode *other, PRUint16 *_retval) = 0;

  /* boolean isSameNode (in nsIDOMNode other); */
  NS_IMETHOD IsSameNode(nsIDOMNode *other, PRBool *_retval) = 0;

  /* DOMString lookupNamespacePrefix (in DOMString namespaceURI); */
  NS_IMETHOD LookupNamespacePrefix(const nsAString & namespaceURI, nsAString & _retval) = 0;

  /* DOMString lookupNamespaceURI (in DOMString prefix); */
  NS_IMETHOD LookupNamespaceURI(const nsAString & prefix, nsAString & _retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOM3NODE \
  NS_IMETHOD GetBaseURI(nsAString & aBaseURI); \
  NS_IMETHOD CompareDocumentPosition(nsIDOMNode *other, PRUint16 *_retval); \
  NS_IMETHOD IsSameNode(nsIDOMNode *other, PRBool *_retval); \
  NS_IMETHOD LookupNamespacePrefix(const nsAString & namespaceURI, nsAString & _retval); \
  NS_IMETHOD LookupNamespaceURI(const nsAString & prefix, nsAString & _retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOM3NODE(_to) \
  NS_IMETHOD GetBaseURI(nsAString & aBaseURI) { return _to GetBaseURI(aBaseURI); } \
  NS_IMETHOD CompareDocumentPosition(nsIDOMNode *other, PRUint16 *_retval) { return _to CompareDocumentPosition(other, _retval); } \
  NS_IMETHOD IsSameNode(nsIDOMNode *other, PRBool *_retval) { return _to IsSameNode(other, _retval); } \
  NS_IMETHOD LookupNamespacePrefix(const nsAString & namespaceURI, nsAString & _retval) { return _to LookupNamespacePrefix(namespaceURI, _retval); } \
  NS_IMETHOD LookupNamespaceURI(const nsAString & prefix, nsAString & _retval) { return _to LookupNamespaceURI(prefix, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOM3NODE(_to) \
  NS_IMETHOD GetBaseURI(nsAString & aBaseURI) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBaseURI(aBaseURI); } \
  NS_IMETHOD CompareDocumentPosition(nsIDOMNode *other, PRUint16 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->CompareDocumentPosition(other, _retval); } \
  NS_IMETHOD IsSameNode(nsIDOMNode *other, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsSameNode(other, _retval); } \
  NS_IMETHOD LookupNamespacePrefix(const nsAString & namespaceURI, nsAString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->LookupNamespacePrefix(namespaceURI, _retval); } \
  NS_IMETHOD LookupNamespaceURI(const nsAString & prefix, nsAString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->LookupNamespaceURI(prefix, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOM3Node : public nsIDOM3Node
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOM3NODE

  nsDOM3Node();
  virtual ~nsDOM3Node();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOM3Node, nsIDOM3Node)

nsDOM3Node::nsDOM3Node()
{
  /* member initializers and constructor code */
}

nsDOM3Node::~nsDOM3Node()
{
  /* destructor code */
}

/* readonly attribute DOMString baseURI; */
NS_IMETHODIMP nsDOM3Node::GetBaseURI(nsAString & aBaseURI)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* unsigned short compareDocumentPosition (in nsIDOMNode other); */
NS_IMETHODIMP nsDOM3Node::CompareDocumentPosition(nsIDOMNode *other, PRUint16 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isSameNode (in nsIDOMNode other); */
NS_IMETHODIMP nsDOM3Node::IsSameNode(nsIDOMNode *other, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* DOMString lookupNamespacePrefix (in DOMString namespaceURI); */
NS_IMETHODIMP nsDOM3Node::LookupNamespacePrefix(const nsAString & namespaceURI, nsAString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* DOMString lookupNamespaceURI (in DOMString prefix); */
NS_IMETHODIMP nsDOM3Node::LookupNamespaceURI(const nsAString & prefix, nsAString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOM3Node_h__ */
