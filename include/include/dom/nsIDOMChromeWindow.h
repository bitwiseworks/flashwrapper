/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/dom/public/idl/base/nsIDOMChromeWindow.idl
 */

#ifndef __gen_nsIDOMChromeWindow_h__
#define __gen_nsIDOMChromeWindow_h__


#ifndef __gen_domstubs_h__
#include "domstubs.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIDOMChromeWindow */
#define NS_IDOMCHROMEWINDOW_IID_STR "876d6f96-2420-4f78-bc17-00b1a2ec12ba"

#define NS_IDOMCHROMEWINDOW_IID \
  {0x876d6f96, 0x2420, 0x4f78, \
    { 0xbc, 0x17, 0x00, 0xb1, 0xa2, 0xec, 0x12, 0xba }}

class NS_NO_VTABLE nsIDOMChromeWindow : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDOMCHROMEWINDOW_IID)

  enum { STATE_MAXIMIZED = 1U };

  enum { STATE_MINIMIZED = 2U };

  enum { STATE_NORMAL = 3U };

  /* attribute DOMString title; */
  NS_IMETHOD GetTitle(nsAString & aTitle) = 0;
  NS_IMETHOD SetTitle(const nsAString & aTitle) = 0;

  /* readonly attribute unsigned short windowState; */
  NS_IMETHOD GetWindowState(PRUint16 *aWindowState) = 0;

  /* void getAttention (); */
  NS_IMETHOD GetAttention(void) = 0;

  /* void setCursor (in DOMString cursor); */
  NS_IMETHOD SetCursor(const nsAString & cursor) = 0;

  /* void maximize (); */
  NS_IMETHOD Maximize(void) = 0;

  /* void minimize (); */
  NS_IMETHOD Minimize(void) = 0;

  /* void restore (); */
  NS_IMETHOD Restore(void) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMCHROMEWINDOW \
  NS_IMETHOD GetTitle(nsAString & aTitle); \
  NS_IMETHOD SetTitle(const nsAString & aTitle); \
  NS_IMETHOD GetWindowState(PRUint16 *aWindowState); \
  NS_IMETHOD GetAttention(void); \
  NS_IMETHOD SetCursor(const nsAString & cursor); \
  NS_IMETHOD Maximize(void); \
  NS_IMETHOD Minimize(void); \
  NS_IMETHOD Restore(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMCHROMEWINDOW(_to) \
  NS_IMETHOD GetTitle(nsAString & aTitle) { return _to GetTitle(aTitle); } \
  NS_IMETHOD SetTitle(const nsAString & aTitle) { return _to SetTitle(aTitle); } \
  NS_IMETHOD GetWindowState(PRUint16 *aWindowState) { return _to GetWindowState(aWindowState); } \
  NS_IMETHOD GetAttention(void) { return _to GetAttention(); } \
  NS_IMETHOD SetCursor(const nsAString & cursor) { return _to SetCursor(cursor); } \
  NS_IMETHOD Maximize(void) { return _to Maximize(); } \
  NS_IMETHOD Minimize(void) { return _to Minimize(); } \
  NS_IMETHOD Restore(void) { return _to Restore(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMCHROMEWINDOW(_to) \
  NS_IMETHOD GetTitle(nsAString & aTitle) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTitle(aTitle); } \
  NS_IMETHOD SetTitle(const nsAString & aTitle) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTitle(aTitle); } \
  NS_IMETHOD GetWindowState(PRUint16 *aWindowState) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWindowState(aWindowState); } \
  NS_IMETHOD GetAttention(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAttention(); } \
  NS_IMETHOD SetCursor(const nsAString & cursor) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCursor(cursor); } \
  NS_IMETHOD Maximize(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Maximize(); } \
  NS_IMETHOD Minimize(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Minimize(); } \
  NS_IMETHOD Restore(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Restore(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDOMChromeWindow : public nsIDOMChromeWindow
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMCHROMEWINDOW

  nsDOMChromeWindow();
  virtual ~nsDOMChromeWindow();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDOMChromeWindow, nsIDOMChromeWindow)

nsDOMChromeWindow::nsDOMChromeWindow()
{
  /* member initializers and constructor code */
}

nsDOMChromeWindow::~nsDOMChromeWindow()
{
  /* destructor code */
}

/* attribute DOMString title; */
NS_IMETHODIMP nsDOMChromeWindow::GetTitle(nsAString & aTitle)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDOMChromeWindow::SetTitle(const nsAString & aTitle)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute unsigned short windowState; */
NS_IMETHODIMP nsDOMChromeWindow::GetWindowState(PRUint16 *aWindowState)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getAttention (); */
NS_IMETHODIMP nsDOMChromeWindow::GetAttention()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setCursor (in DOMString cursor); */
NS_IMETHODIMP nsDOMChromeWindow::SetCursor(const nsAString & cursor)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void maximize (); */
NS_IMETHODIMP nsDOMChromeWindow::Maximize()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void minimize (); */
NS_IMETHODIMP nsDOMChromeWindow::Minimize()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void restore (); */
NS_IMETHODIMP nsDOMChromeWindow::Restore()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDOMChromeWindow_h__ */
