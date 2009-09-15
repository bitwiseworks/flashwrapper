/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/xpcom/components/nsINativeComponentLoader.idl
 */

#ifndef __gen_nsINativeComponentLoader_h__
#define __gen_nsINativeComponentLoader_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIFile; /* forward declaration */


/* starting interface:    nsINativeComponentLoader */
#define NS_INATIVECOMPONENTLOADER_IID_STR "aa610f20-a889-11d3-8c81-000064657374"

#define NS_INATIVECOMPONENTLOADER_IID \
  {0xaa610f20, 0xa889, 0x11d3, \
    { 0x8c, 0x81, 0x00, 0x00, 0x64, 0x65, 0x73, 0x74 }}

class NS_NO_VTABLE nsINativeComponentLoader : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_INATIVECOMPONENTLOADER_IID)

  /**
   *  addDependentLibrary
   *
   *  This method informs the native component loader that the 
   *  given component library referenced by |aFile| requires 
   *  symbols that can be found in the library named |aLibName|.
   *  
   *  The native component loader is expected to resolve these 
   *  external symobls prior to loading the component library.  
   *
   *  @param aFile
   *       The native component file location that is declaring a 
   *       a dependency. This file is expected to be a DSO/DLL.
   *
   *  @param aLibName
   *       This is a name of a library that the component requires.
   *       This file name is found in either the GRE bin directory 
   *       or the application's bin directory.  Full file path are 
   *       also accepted.  Passing nsnull for the |aLibName| will 
   *       clear all dependencies.  Note that non null aLibName
   *       values are expected to be in the native charset.
   */
  /* void addDependentLibrary (in nsIFile aFile, in string aLibName); */
  NS_IMETHOD AddDependentLibrary(nsIFile *aFile, const char *aLibName) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSINATIVECOMPONENTLOADER \
  NS_IMETHOD AddDependentLibrary(nsIFile *aFile, const char *aLibName); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSINATIVECOMPONENTLOADER(_to) \
  NS_IMETHOD AddDependentLibrary(nsIFile *aFile, const char *aLibName) { return _to AddDependentLibrary(aFile, aLibName); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSINATIVECOMPONENTLOADER(_to) \
  NS_IMETHOD AddDependentLibrary(nsIFile *aFile, const char *aLibName) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddDependentLibrary(aFile, aLibName); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsNativeComponentLoader : public nsINativeComponentLoader
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSINATIVECOMPONENTLOADER

  nsNativeComponentLoader();
  virtual ~nsNativeComponentLoader();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsNativeComponentLoader, nsINativeComponentLoader)

nsNativeComponentLoader::nsNativeComponentLoader()
{
  /* member initializers and constructor code */
}

nsNativeComponentLoader::~nsNativeComponentLoader()
{
  /* destructor code */
}

/* void addDependentLibrary (in nsIFile aFile, in string aLibName); */
NS_IMETHODIMP nsNativeComponentLoader::AddDependentLibrary(nsIFile *aFile, const char *aLibName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsINativeComponentLoader_h__ */
