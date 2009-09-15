/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/modules/plugin/base/public/nsIPluginViewer.idl
 */

#ifndef __gen_nsIPluginViewer_h__
#define __gen_nsIPluginViewer_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIRequest_h__
#include "nsIRequest.h"
#endif

#ifndef __gen_nsIStreamListener_h__
#include "nsIStreamListener.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIPluginViewer */
#define NS_IPLUGINVIEWER_IID_STR "506967e5-837f-44af-91bd-018b959476c0"

#define NS_IPLUGINVIEWER_IID \
  {0x506967e5, 0x837f, 0x44af, \
    { 0x91, 0xbd, 0x01, 0x8b, 0x95, 0x94, 0x76, 0xc0 }}

class nsIPluginViewer : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IPLUGINVIEWER_IID)

    /**
     * Creates a new plugin viewer, based on a nsIRequest.
     */
    void StartLoad (nsIRequest * aRequest, nsIStreamListener *&aResult);
};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIPLUGINVIEWER \

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIPLUGINVIEWER(_to) \

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIPLUGINVIEWER(_to) \

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsPluginViewer : public nsIPluginViewer
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIPLUGINVIEWER

  nsPluginViewer();
  virtual ~nsPluginViewer();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsPluginViewer, nsIPluginViewer)

nsPluginViewer::nsPluginViewer()
{
  /* member initializers and constructor code */
}

nsPluginViewer::~nsPluginViewer()
{
  /* destructor code */
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIPluginViewer_h__ */
