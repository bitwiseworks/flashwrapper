/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/xpcom/io/nsIStorageStream.idl
 */

#ifndef __gen_nsIStorageStream_h__
#define __gen_nsIStorageStream_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsrootidl_h__
#include "nsrootidl.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIInputStream; /* forward declaration */

class nsIOutputStream; /* forward declaration */


/* starting interface:    nsIStorageStream */
#define NS_ISTORAGESTREAM_IID_STR "604ad9d0-753e-11d3-90ca-0040056a906e"

#define NS_ISTORAGESTREAM_IID \
  {0x604ad9d0, 0x753e, 0x11d3, \
    { 0x90, 0xca, 0x00, 0x40, 0x05, 0x6a, 0x90, 0x6e }}

/**
 * The nsIStorageStream interface maintains an internal data buffer that can be
 * filled using a single output stream.  One or more independent input streams
 * can be created to read the data from the buffer non-destructively.
 */
class NS_NO_VTABLE nsIStorageStream : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ISTORAGESTREAM_IID)

  /**
     * Get a reference to the one and only output stream for this instance.
     * The zero-based startPosition argument is used is used to set the initial
     * write cursor position.  The startPosition cannot be set larger than the
     * current buffer length.  Calling this method has the side-effect of
     * truncating the internal buffer to startPosition bytes.
     */
  /* nsIOutputStream getOutputStream (in PRInt32 startPosition); */
  NS_IMETHOD GetOutputStream(PRInt32 startPosition, nsIOutputStream **_retval) = 0;

  /**
     * Create a new input stream to read data (written by the singleton output
     * stream) from the internal buffer.  Multiple, independent input streams
     * can be created.
     */
  /* nsIInputStream newInputStream (in PRInt32 startPosition); */
  NS_IMETHOD NewInputStream(PRInt32 startPosition, nsIInputStream **_retval) = 0;

  /** 
     * The length attribute indicates the total number of bytes stored in the
     * nsIStorageStream internal buffer, regardless of any consumption by input
     * streams.  Assigning to the length field can be used to truncate the
     * buffer data, but can not be used when either the instance's output
     * stream is in use.
     *
     * @See #writeInProgress */
  /* attribute PRUint32 length; */
  NS_IMETHOD GetLength(PRUint32 *aLength) = 0;
  NS_IMETHOD SetLength(PRUint32 aLength) = 0;

  /**
     * True, when output stream has not yet been Close'ed
     */
  /* readonly attribute boolean writeInProgress; */
  NS_IMETHOD GetWriteInProgress(PRBool *aWriteInProgress) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISTORAGESTREAM \
  NS_IMETHOD GetOutputStream(PRInt32 startPosition, nsIOutputStream **_retval); \
  NS_IMETHOD NewInputStream(PRInt32 startPosition, nsIInputStream **_retval); \
  NS_IMETHOD GetLength(PRUint32 *aLength); \
  NS_IMETHOD SetLength(PRUint32 aLength); \
  NS_IMETHOD GetWriteInProgress(PRBool *aWriteInProgress); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISTORAGESTREAM(_to) \
  NS_IMETHOD GetOutputStream(PRInt32 startPosition, nsIOutputStream **_retval) { return _to GetOutputStream(startPosition, _retval); } \
  NS_IMETHOD NewInputStream(PRInt32 startPosition, nsIInputStream **_retval) { return _to NewInputStream(startPosition, _retval); } \
  NS_IMETHOD GetLength(PRUint32 *aLength) { return _to GetLength(aLength); } \
  NS_IMETHOD SetLength(PRUint32 aLength) { return _to SetLength(aLength); } \
  NS_IMETHOD GetWriteInProgress(PRBool *aWriteInProgress) { return _to GetWriteInProgress(aWriteInProgress); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISTORAGESTREAM(_to) \
  NS_IMETHOD GetOutputStream(PRInt32 startPosition, nsIOutputStream **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOutputStream(startPosition, _retval); } \
  NS_IMETHOD NewInputStream(PRInt32 startPosition, nsIInputStream **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->NewInputStream(startPosition, _retval); } \
  NS_IMETHOD GetLength(PRUint32 *aLength) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLength(aLength); } \
  NS_IMETHOD SetLength(PRUint32 aLength) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLength(aLength); } \
  NS_IMETHOD GetWriteInProgress(PRBool *aWriteInProgress) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWriteInProgress(aWriteInProgress); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsStorageStream : public nsIStorageStream
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISTORAGESTREAM

  nsStorageStream();
  virtual ~nsStorageStream();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsStorageStream, nsIStorageStream)

nsStorageStream::nsStorageStream()
{
  /* member initializers and constructor code */
}

nsStorageStream::~nsStorageStream()
{
  /* destructor code */
}

/* nsIOutputStream getOutputStream (in PRInt32 startPosition); */
NS_IMETHODIMP nsStorageStream::GetOutputStream(PRInt32 startPosition, nsIOutputStream **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIInputStream newInputStream (in PRInt32 startPosition); */
NS_IMETHODIMP nsStorageStream::NewInputStream(PRInt32 startPosition, nsIInputStream **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute PRUint32 length; */
NS_IMETHODIMP nsStorageStream::GetLength(PRUint32 *aLength)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsStorageStream::SetLength(PRUint32 aLength)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean writeInProgress; */
NS_IMETHODIMP nsStorageStream::GetWriteInProgress(PRBool *aWriteInProgress)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

// Factory method
NS_COM nsresult
NS_NewStorageStream(PRUint32 segmentSize, PRUint32 maxSize, nsIStorageStream **result);

#endif /* __gen_nsIStorageStream_h__ */
