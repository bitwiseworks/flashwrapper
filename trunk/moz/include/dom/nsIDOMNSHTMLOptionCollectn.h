/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/dom/public/idl/html/nsIDOMNSHTMLOptionCollectn.idl
 */

#ifndef __gen_nsIDOMNSHTMLOptionCollectn_h__
#define __gen_nsIDOMNSHTMLOptionCollectn_h__


#ifndef __gen_domstubs_h__
#include "domstubs.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMHTMLOptionElement; /* forward declaration */


/* starting interface:    nsIDOMNSHTMLOptionCollection */
#define NS_IDOMNSHTMLOPTIONCOLLECTION_IID_STR "409bbf14-1dd2-11b2-91de-8d672d406276"

#define NS_IDOMNSHTMLOPTIONCOLLECTION_IID \
  {0x409bbf14, 0x1dd2, 0x11b2, \
    { 0x91, 0xde, 0x8d, 0x67, 0x2d, 0x40, 0x62, 0x76 }}

class NS_NO_VTABLE nsIDOMNSHTMLOptionCollection : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDOMNSHTMLOPTIONCOLLECTION_IID)

  /* attribute unsigned long length; */
  NS_IMETHOD GetLength(PRUint32 *aLength) = 0;
  NS_IMETHOD SetLength(PRUint32 aLength) = 0;

  /* attribute long selectedIndex; */
  NS_IMETHOD GetSelectedIndex(PRInt32 *aSelectedIndex) = 0;
  NS_IMETHOD SetSelectedIndex(PRInt32 aSelectedIndex) = 0;

  /* [noscript] void setOption (in long index, in nsIDOMHTMLOptionElement option); */
  NS_IMETHOD SetOption(PRInt32 index, nsIDOMHTMLOptionElement *option) = 0;

  /* void add (in nsIDOMHTMLOptionElement option); */
  NS_IMETHOD Add(nsIDOMHTMLOptionElement *option) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMNSHTMLOPTIONCOLLECTION \
  NS_IMETHOD GetLength(PRUint32 *aLength); \
  NS_IMETHOD SetLength(PRUint32 aLength); \
  NS_IMETHOD GetSelectedIndex(PRInt32 *aSelectedIndex); \
  NS_IMETHOD SetSelectedIndex(PRInt32 aSelectedIndex); \
  NS_IMETHOD SetOption(PRInt32 index, nsIDOMHTMLOptionElement *option); \
  NS_IMETHOD Add(nsIDOMHTMLOptionElement *option); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMNSHTMLOPTIONCOLLECTION(_to) \
  NS_IMETHOD GetLength(PRUint32 *aLength) { return _to GetLength(aLength); } \
  NS_IMETHOD SetLength(PRUint32 aLength) { return _to SetLength(aLength); } \
  NS_IMETHOD GetSelectedIndex(PRInt32 *aSelectedIndex) { return _to GetSelectedIndex(aSelectedIndex); } \
  NS_IMETHOD SetSelectedIndex(PRInt32 aSelectedIndex) { return _to SetSelectedIndex(aSelectedIndex); } \
  NS_IMETHOD SetOption(PRInt32 index, nsIDOMHTMLOptionElement *option) { return _to SetOption(index, option); } \
  NS_IMETHOD Add(nsIDOMHTMLOptionElement *option) { return _to Add(option); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMNSHTMLOPTIONCOLLECTION(_to) \
  NS_IMETHOD GetLength(PRUint32 *aLength) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLength(aLength); } \
  NS_IMETHOD SetLength(PRUint32 aLength) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLength(aLength); } \
  NS_IMETHOD GetSelectedIndex(PRInt32 *aSelectedIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSelectedIndex(aSelectedIndex); } \
  NS_IMETHOD SetSelectedIndex(PRInt32 aSelectedIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetSelectedIndex(aSelectedIndex); } \
  NS_IMETHOD SetOption(PRInt32 index, nsIDOMHTMLOptionElement *option) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetOption(index, option); } \
  NS_IMETHOD Add(nsIDOMHTMLOptionElement *option) { return !_to ? NS_ERROR_NULL_POINTER : _to->Add(option); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMNSHTMLOptionCollection : public nsIDOMNSHTMLOptionCollection
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMNSHTMLOPTIONCOLLECTION

  nsDOMNSHTMLOptionCollection();
  virtual ~nsDOMNSHTMLOptionCollection();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMNSHTMLOptionCollection, nsIDOMNSHTMLOptionCollection)

nsDOMNSHTMLOptionCollection::nsDOMNSHTMLOptionCollection()
{
  /* member initializers and constructor code */
}

nsDOMNSHTMLOptionCollection::~nsDOMNSHTMLOptionCollection()
{
  /* destructor code */
}

/* attribute unsigned long length; */
NS_IMETHODIMP nsDOMNSHTMLOptionCollection::GetLength(PRUint32 *aLength)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMNSHTMLOptionCollection::SetLength(PRUint32 aLength)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long selectedIndex; */
NS_IMETHODIMP nsDOMNSHTMLOptionCollection::GetSelectedIndex(PRInt32 *aSelectedIndex)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMNSHTMLOptionCollection::SetSelectedIndex(PRInt32 aSelectedIndex)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void setOption (in long index, in nsIDOMHTMLOptionElement option); */
NS_IMETHODIMP nsDOMNSHTMLOptionCollection::SetOption(PRInt32 index, nsIDOMHTMLOptionElement *option)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void add (in nsIDOMHTMLOptionElement option); */
NS_IMETHODIMP nsDOMNSHTMLOptionCollection::Add(nsIDOMHTMLOptionElement *option)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMNSHTMLOptionCollectn_h__ */
