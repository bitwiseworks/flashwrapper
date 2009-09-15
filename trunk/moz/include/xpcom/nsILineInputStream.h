/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/xpcom/io/nsILineInputStream.idl
 */

#ifndef __gen_nsILineInputStream_h__
#define __gen_nsILineInputStream_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
#include "nsString.h" // needed for AString -> nsAString, unfortunately
class nsILineInputStream; /* forward declaration */


/* starting interface:    nsILineInputStream */
#define NS_ILINEINPUTSTREAM_IID_STR "e7f17108-1dd1-11b2-8b9a-fda151ea0240"

#define NS_ILINEINPUTSTREAM_IID \
  {0xe7f17108, 0x1dd1, 0x11b2, \
    { 0x8b, 0x9a, 0xfd, 0xa1, 0x51, 0xea, 0x02, 0x40 }}

class NS_NO_VTABLE nsILineInputStream : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_ILINEINPUTSTREAM_IID)

  /**
   * Read a single line from the stream
   * Return false for end of file, true otherwise
   */
  /* boolean readLine (out AString aLine); */
  NS_IMETHOD ReadLine(nsAString & aLine, PRBool *_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSILINEINPUTSTREAM \
  NS_IMETHOD ReadLine(nsAString & aLine, PRBool *_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSILINEINPUTSTREAM(_to) \
  NS_IMETHOD ReadLine(nsAString & aLine, PRBool *_retval) { return _to ReadLine(aLine, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSILINEINPUTSTREAM(_to) \
  NS_IMETHOD ReadLine(nsAString & aLine, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->ReadLine(aLine, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsLineInputStream : public nsILineInputStream
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSILINEINPUTSTREAM

  nsLineInputStream();
  virtual ~nsLineInputStream();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsLineInputStream, nsILineInputStream)

nsLineInputStream::nsLineInputStream()
{
  /* member initializers and constructor code */
}

nsLineInputStream::~nsLineInputStream()
{
  /* destructor code */
}

/* boolean readLine (out AString aLine); */
NS_IMETHODIMP nsLineInputStream::ReadLine(nsAString & aLine, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsILineInputStream_h__ */
