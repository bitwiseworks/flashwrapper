/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/xpcom/io/nsIAsyncOutputStream.idl
 */

#ifndef __gen_nsIAsyncOutputStream_h__
#define __gen_nsIAsyncOutputStream_h__


#ifndef __gen_nsIOutputStream_h__
#include "nsIOutputStream.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIOutputStreamNotify; /* forward declaration */

class nsIEventQueue; /* forward declaration */


/* starting interface:    nsIAsyncOutputStream */
#define NS_IASYNCOUTPUTSTREAM_IID_STR "04ba1b53-fad0-4033-91c9-3e24db22079c"

#define NS_IASYNCOUTPUTSTREAM_IID \
  {0x04ba1b53, 0xfad0, 0x4033, \
    { 0x91, 0xc9, 0x3e, 0x24, 0xdb, 0x22, 0x07, 0x9c }}

class NS_NO_VTABLE nsIAsyncOutputStream : public nsIOutputStream {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IASYNCOUTPUTSTREAM_IID)

  /**
     * This function extends nsIOutputStream::close, allowing the caller to
     * specify the reason for closing the stream.  Any future attempts to
     * access the stream (e.g., nsIInputStream::write) will result in an
     * exception with the value given by |reason|.
     *
     * close() is equivalent to closeEx(NS_BASE_STREAM_CLOSED).
     *
     * Any pending asyncWait will be notified.
     */
  /* void closeEx (in nsresult reason); */
  NS_IMETHOD CloseEx(nsresult reason) = 0;

  /**
     * Asynchronously wait for the stream to be writable or closed.
     * 
     * @param aNotify
     *        This object is notified when the stream becomes ready.
     * @param aRequestedCount
     *        Wait until at least this many bytes may be written.  This is
     *        only a suggestion to the underlying stream; it may be ignored.
     * @param aEventQ
     *        Specify NULL to receive notification on ANY thread, or specify
     *        that notification be delivered to a specific event queue.  Caller
     *        must pass a "resolved" event queue (see nsIEventQueueService).
     */
  /* void asyncWait (in nsIOutputStreamNotify aNotify, in unsigned long aRequestedCount, in nsIEventQueue aEventQ); */
  NS_IMETHOD AsyncWait(nsIOutputStreamNotify *aNotify, PRUint32 aRequestedCount, nsIEventQueue *aEventQ) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIASYNCOUTPUTSTREAM \
  NS_IMETHOD CloseEx(nsresult reason); \
  NS_IMETHOD AsyncWait(nsIOutputStreamNotify *aNotify, PRUint32 aRequestedCount, nsIEventQueue *aEventQ); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIASYNCOUTPUTSTREAM(_to) \
  NS_IMETHOD CloseEx(nsresult reason) { return _to CloseEx(reason); } \
  NS_IMETHOD AsyncWait(nsIOutputStreamNotify *aNotify, PRUint32 aRequestedCount, nsIEventQueue *aEventQ) { return _to AsyncWait(aNotify, aRequestedCount, aEventQ); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIASYNCOUTPUTSTREAM(_to) \
  NS_IMETHOD CloseEx(nsresult reason) { return !_to ? NS_ERROR_NULL_POINTER : _to->CloseEx(reason); } \
  NS_IMETHOD AsyncWait(nsIOutputStreamNotify *aNotify, PRUint32 aRequestedCount, nsIEventQueue *aEventQ) { return !_to ? NS_ERROR_NULL_POINTER : _to->AsyncWait(aNotify, aRequestedCount, aEventQ); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAsyncOutputStream : public nsIAsyncOutputStream
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIASYNCOUTPUTSTREAM

  nsAsyncOutputStream();
  virtual ~nsAsyncOutputStream();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAsyncOutputStream, nsIAsyncOutputStream)

nsAsyncOutputStream::nsAsyncOutputStream()
{
  /* member initializers and constructor code */
}

nsAsyncOutputStream::~nsAsyncOutputStream()
{
  /* destructor code */
}

/* void closeEx (in nsresult reason); */
NS_IMETHODIMP nsAsyncOutputStream::CloseEx(nsresult reason)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void asyncWait (in nsIOutputStreamNotify aNotify, in unsigned long aRequestedCount, in nsIEventQueue aEventQ); */
NS_IMETHODIMP nsAsyncOutputStream::AsyncWait(nsIOutputStreamNotify *aNotify, PRUint32 aRequestedCount, nsIEventQueue *aEventQ)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIOutputStreamNotify */
#define NS_IOUTPUTSTREAMNOTIFY_IID_STR "614def11-1d77-409b-8153-ea3ae5babc3c"

#define NS_IOUTPUTSTREAMNOTIFY_IID \
  {0x614def11, 0x1d77, 0x409b, \
    { 0x81, 0x53, 0xea, 0x3a, 0xe5, 0xba, 0xbc, 0x3c }}

class NS_NO_VTABLE nsIOutputStreamNotify : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IOUTPUTSTREAMNOTIFY_IID)

  /* void onOutputStreamReady (in nsIAsyncOutputStream aStream); */
  NS_IMETHOD OnOutputStreamReady(nsIAsyncOutputStream *aStream) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIOUTPUTSTREAMNOTIFY \
  NS_IMETHOD OnOutputStreamReady(nsIAsyncOutputStream *aStream); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIOUTPUTSTREAMNOTIFY(_to) \
  NS_IMETHOD OnOutputStreamReady(nsIAsyncOutputStream *aStream) { return _to OnOutputStreamReady(aStream); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIOUTPUTSTREAMNOTIFY(_to) \
  NS_IMETHOD OnOutputStreamReady(nsIAsyncOutputStream *aStream) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnOutputStreamReady(aStream); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsOutputStreamNotify : public nsIOutputStreamNotify
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIOUTPUTSTREAMNOTIFY

  nsOutputStreamNotify();
  virtual ~nsOutputStreamNotify();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsOutputStreamNotify, nsIOutputStreamNotify)

nsOutputStreamNotify::nsOutputStreamNotify()
{
  /* member initializers and constructor code */
}

nsOutputStreamNotify::~nsOutputStreamNotify()
{
  /* destructor code */
}

/* void onOutputStreamReady (in nsIAsyncOutputStream aStream); */
NS_IMETHODIMP nsOutputStreamNotify::OnOutputStreamReady(nsIAsyncOutputStream *aStream)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAsyncOutputStream_h__ */
