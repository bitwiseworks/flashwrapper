/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/xpcom/io/nsIAsyncInputStream.idl
 */

#ifndef __gen_nsIAsyncInputStream_h__
#define __gen_nsIAsyncInputStream_h__


#ifndef __gen_nsIInputStream_h__
#include "nsIInputStream.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIInputStreamNotify; /* forward declaration */

class nsIEventQueue; /* forward declaration */


/* starting interface:    nsIAsyncInputStream */
#define NS_IASYNCINPUTSTREAM_IID_STR "cc911e09-2a02-4d2d-ba4b-b2afb173e96d"

#define NS_IASYNCINPUTSTREAM_IID \
  {0xcc911e09, 0x2a02, 0x4d2d, \
    { 0xba, 0x4b, 0xb2, 0xaf, 0xb1, 0x73, 0xe9, 0x6d }}

class NS_NO_VTABLE nsIAsyncInputStream : public nsIInputStream {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IASYNCINPUTSTREAM_IID)

  /**
     * This function extends nsIInputStream::close, allowing the caller to
     * specify the reason for closing the stream.  Any future attempts to
     * access the stream (e.g., nsIInputStream::read) will result in an
     * exception with the value given by |reason|.
     *
     * close() is equivalent to closeEx(NS_BASE_STREAM_CLOSED).
     *
     * Any pending asyncWait will be notified.
     */
  /* void closeEx (in nsresult reason); */
  NS_IMETHOD CloseEx(nsresult reason) = 0;

  /**
     * Asynchronously wait for the stream to be readable or closed.
     * 
     * @param aNotify
     *        This object is notified when the stream becomes ready.
     * @param aRequestedCount
     *        Wait until at least this many bytes may be read.  This is only
     *        a suggestion to the underlying stream; it may be ignored.
     * @param aEventQ
     *        Specify NULL to receive notification on ANY thread, or specify
     *        that notification be delivered to a specific event queue.  Caller
     *        must pass a "resolved" event queue (see nsIEventQueueService).
     */
  /* void asyncWait (in nsIInputStreamNotify aNotify, in unsigned long aRequestedCount, in nsIEventQueue aEventQ); */
  NS_IMETHOD AsyncWait(nsIInputStreamNotify *aNotify, PRUint32 aRequestedCount, nsIEventQueue *aEventQ) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIASYNCINPUTSTREAM \
  NS_IMETHOD CloseEx(nsresult reason); \
  NS_IMETHOD AsyncWait(nsIInputStreamNotify *aNotify, PRUint32 aRequestedCount, nsIEventQueue *aEventQ); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIASYNCINPUTSTREAM(_to) \
  NS_IMETHOD CloseEx(nsresult reason) { return _to CloseEx(reason); } \
  NS_IMETHOD AsyncWait(nsIInputStreamNotify *aNotify, PRUint32 aRequestedCount, nsIEventQueue *aEventQ) { return _to AsyncWait(aNotify, aRequestedCount, aEventQ); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIASYNCINPUTSTREAM(_to) \
  NS_IMETHOD CloseEx(nsresult reason) { return !_to ? NS_ERROR_NULL_POINTER : _to->CloseEx(reason); } \
  NS_IMETHOD AsyncWait(nsIInputStreamNotify *aNotify, PRUint32 aRequestedCount, nsIEventQueue *aEventQ) { return !_to ? NS_ERROR_NULL_POINTER : _to->AsyncWait(aNotify, aRequestedCount, aEventQ); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAsyncInputStream : public nsIAsyncInputStream
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIASYNCINPUTSTREAM

  nsAsyncInputStream();
  virtual ~nsAsyncInputStream();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAsyncInputStream, nsIAsyncInputStream)

nsAsyncInputStream::nsAsyncInputStream()
{
  /* member initializers and constructor code */
}

nsAsyncInputStream::~nsAsyncInputStream()
{
  /* destructor code */
}

/* void closeEx (in nsresult reason); */
NS_IMETHODIMP nsAsyncInputStream::CloseEx(nsresult reason)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void asyncWait (in nsIInputStreamNotify aNotify, in unsigned long aRequestedCount, in nsIEventQueue aEventQ); */
NS_IMETHODIMP nsAsyncInputStream::AsyncWait(nsIInputStreamNotify *aNotify, PRUint32 aRequestedCount, nsIEventQueue *aEventQ)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIInputStreamNotify */
#define NS_IINPUTSTREAMNOTIFY_IID_STR "20c665a3-0ebf-4ebb-97ba-794248bfa8fe"

#define NS_IINPUTSTREAMNOTIFY_IID \
  {0x20c665a3, 0x0ebf, 0x4ebb, \
    { 0x97, 0xba, 0x79, 0x42, 0x48, 0xbf, 0xa8, 0xfe }}

class NS_NO_VTABLE nsIInputStreamNotify : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IINPUTSTREAMNOTIFY_IID)

  /* void onInputStreamReady (in nsIAsyncInputStream aStream); */
  NS_IMETHOD OnInputStreamReady(nsIAsyncInputStream *aStream) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIINPUTSTREAMNOTIFY \
  NS_IMETHOD OnInputStreamReady(nsIAsyncInputStream *aStream); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIINPUTSTREAMNOTIFY(_to) \
  NS_IMETHOD OnInputStreamReady(nsIAsyncInputStream *aStream) { return _to OnInputStreamReady(aStream); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIINPUTSTREAMNOTIFY(_to) \
  NS_IMETHOD OnInputStreamReady(nsIAsyncInputStream *aStream) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnInputStreamReady(aStream); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsInputStreamNotify : public nsIInputStreamNotify
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIINPUTSTREAMNOTIFY

  nsInputStreamNotify();
  virtual ~nsInputStreamNotify();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsInputStreamNotify, nsIInputStreamNotify)

nsInputStreamNotify::nsInputStreamNotify()
{
  /* member initializers and constructor code */
}

nsInputStreamNotify::~nsInputStreamNotify()
{
  /* destructor code */
}

/* void onInputStreamReady (in nsIAsyncInputStream aStream); */
NS_IMETHODIMP nsInputStreamNotify::OnInputStreamReady(nsIAsyncInputStream *aStream)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAsyncInputStream_h__ */
