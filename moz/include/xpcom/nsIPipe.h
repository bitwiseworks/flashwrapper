/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/xpcom/io/nsIPipe.idl
 */

#ifndef __gen_nsIPipe_h__
#define __gen_nsIPipe_h__


#ifndef __gen_nsIAsyncInputStream_h__
#include "nsIAsyncInputStream.h"
#endif

#ifndef __gen_nsIAsyncOutputStream_h__
#include "nsIAsyncOutputStream.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIMemory; /* forward declaration */


/* starting interface:    nsIPipe */
#define NS_IPIPE_IID_STR "f4211abc-61b3-11d4-9877-00c04fa0cf4a"

#define NS_IPIPE_IID \
  {0xf4211abc, 0x61b3, 0x11d4, \
    { 0x98, 0x77, 0x00, 0xc0, 0x4f, 0xa0, 0xcf, 0x4a }}

class NS_NO_VTABLE nsIPipe : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IPIPE_IID)

  /**
     * initialize this pipe
     */
  /* void init (in boolean nonBlockingInput, in boolean nonBlockingOutput, in unsigned long segmentSize, in unsigned long segmentCount, in nsIMemory segmentAllocator); */
  NS_IMETHOD Init(PRBool nonBlockingInput, PRBool nonBlockingOutput, PRUint32 segmentSize, PRUint32 segmentCount, nsIMemory *segmentAllocator) = 0;

  /* readonly attribute nsIAsyncInputStream inputStream; */
  NS_IMETHOD GetInputStream(nsIAsyncInputStream * *aInputStream) = 0;

  /* readonly attribute nsIAsyncOutputStream outputStream; */
  NS_IMETHOD GetOutputStream(nsIAsyncOutputStream * *aOutputStream) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIPIPE \
  NS_IMETHOD Init(PRBool nonBlockingInput, PRBool nonBlockingOutput, PRUint32 segmentSize, PRUint32 segmentCount, nsIMemory *segmentAllocator); \
  NS_IMETHOD GetInputStream(nsIAsyncInputStream * *aInputStream); \
  NS_IMETHOD GetOutputStream(nsIAsyncOutputStream * *aOutputStream); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIPIPE(_to) \
  NS_IMETHOD Init(PRBool nonBlockingInput, PRBool nonBlockingOutput, PRUint32 segmentSize, PRUint32 segmentCount, nsIMemory *segmentAllocator) { return _to Init(nonBlockingInput, nonBlockingOutput, segmentSize, segmentCount, segmentAllocator); } \
  NS_IMETHOD GetInputStream(nsIAsyncInputStream * *aInputStream) { return _to GetInputStream(aInputStream); } \
  NS_IMETHOD GetOutputStream(nsIAsyncOutputStream * *aOutputStream) { return _to GetOutputStream(aOutputStream); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIPIPE(_to) \
  NS_IMETHOD Init(PRBool nonBlockingInput, PRBool nonBlockingOutput, PRUint32 segmentSize, PRUint32 segmentCount, nsIMemory *segmentAllocator) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(nonBlockingInput, nonBlockingOutput, segmentSize, segmentCount, segmentAllocator); } \
  NS_IMETHOD GetInputStream(nsIAsyncInputStream * *aInputStream) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInputStream(aInputStream); } \
  NS_IMETHOD GetOutputStream(nsIAsyncOutputStream * *aOutputStream) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOutputStream(aOutputStream); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsPipe : public nsIPipe
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIPIPE

  nsPipe();
  virtual ~nsPipe();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsPipe, nsIPipe)

nsPipe::nsPipe()
{
  /* member initializers and constructor code */
}

nsPipe::~nsPipe()
{
  /* destructor code */
}

/* void init (in boolean nonBlockingInput, in boolean nonBlockingOutput, in unsigned long segmentSize, in unsigned long segmentCount, in nsIMemory segmentAllocator); */
NS_IMETHODIMP nsPipe::Init(PRBool nonBlockingInput, PRBool nonBlockingOutput, PRUint32 segmentSize, PRUint32 segmentCount, nsIMemory *segmentAllocator)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIAsyncInputStream inputStream; */
NS_IMETHODIMP nsPipe::GetInputStream(nsIAsyncInputStream * *aInputStream)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIAsyncOutputStream outputStream; */
NS_IMETHODIMP nsPipe::GetOutputStream(nsIAsyncOutputStream * *aOutputStream)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsISearchableInputStream */
#define NS_ISEARCHABLEINPUTSTREAM_IID_STR "8c39ef62-f7c9-11d4-98f5-001083010e9b"

#define NS_ISEARCHABLEINPUTSTREAM_IID \
  {0x8c39ef62, 0xf7c9, 0x11d4, \
    { 0x98, 0xf5, 0x00, 0x10, 0x83, 0x01, 0x0e, 0x9b }}

class NS_NO_VTABLE nsISearchableInputStream : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ISEARCHABLEINPUTSTREAM_IID)

  /**
     * Searches for a string in the input stream. Since the stream has a notion
     * of EOF, it is possible that the string may at some time be in the 
     * buffer, but is is not currently found up to some offset. Consequently,
     * both the found and not found cases return an offset:
     *    if found, return offset where it was found
     *    if not found, return offset of the first byte not searched
     * In the case the stream is at EOF and the string is not found, the first
     * byte not searched will correspond to the length of the buffer.
     */
  /* void search (in string forString, in boolean ignoreCase, out boolean found, out unsigned long offsetSearchedTo); */
  NS_IMETHOD Search(const char *forString, PRBool ignoreCase, PRBool *found, PRUint32 *offsetSearchedTo) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISEARCHABLEINPUTSTREAM \
  NS_IMETHOD Search(const char *forString, PRBool ignoreCase, PRBool *found, PRUint32 *offsetSearchedTo); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISEARCHABLEINPUTSTREAM(_to) \
  NS_IMETHOD Search(const char *forString, PRBool ignoreCase, PRBool *found, PRUint32 *offsetSearchedTo) { return _to Search(forString, ignoreCase, found, offsetSearchedTo); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISEARCHABLEINPUTSTREAM(_to) \
  NS_IMETHOD Search(const char *forString, PRBool ignoreCase, PRBool *found, PRUint32 *offsetSearchedTo) { return !_to ? NS_ERROR_NULL_POINTER : _to->Search(forString, ignoreCase, found, offsetSearchedTo); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSearchableInputStream : public nsISearchableInputStream
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISEARCHABLEINPUTSTREAM

  nsSearchableInputStream();
  virtual ~nsSearchableInputStream();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSearchableInputStream, nsISearchableInputStream)

nsSearchableInputStream::nsSearchableInputStream()
{
  /* member initializers and constructor code */
}

nsSearchableInputStream::~nsSearchableInputStream()
{
  /* destructor code */
}

/* void search (in string forString, in boolean ignoreCase, out boolean found, out unsigned long offsetSearchedTo); */
NS_IMETHODIMP nsSearchableInputStream::Search(const char *forString, PRBool ignoreCase, PRBool *found, PRUint32 *offsetSearchedTo)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

extern NS_COM nsresult
NS_NewPipe2(nsIAsyncInputStream **pipeIn,
            nsIAsyncOutputStream **pipeOut,
            PRBool nonBlockingInput = PR_FALSE,
            PRBool nonBlockingOutput = PR_FALSE,
            PRUint32 segmentSize = 0,
            PRUint32 segmentCount = 0,
            nsIMemory *segmentAlloc = nsnull);
inline nsresult
NS_NewPipe(nsIInputStream **pipeIn,
           nsIOutputStream **pipeOut,
           PRUint32 segmentSize = 0,
           PRUint32 maxSize = 0,
           PRBool nonBlockingInput = PR_FALSE,
           PRBool nonBlockingOutput = PR_FALSE,
           nsIMemory *segmentAlloc = nsnull)
{
    PRUint32 segmentCount;
    if (segmentSize == 0)
        segmentCount = 0; // use default
    else
        segmentCount = maxSize / segmentSize;
    nsIAsyncInputStream *in;
    nsIAsyncOutputStream *out;
    nsresult rv = NS_NewPipe2(&in, &out, nonBlockingInput, nonBlockingOutput,
                              segmentSize, segmentCount, segmentAlloc);
    if (NS_FAILED(rv)) return rv;
    *pipeIn = in;
    *pipeOut = out;
    return NS_OK;
}

#endif /* __gen_nsIPipe_h__ */
