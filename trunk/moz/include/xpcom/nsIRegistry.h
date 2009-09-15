/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/xpcom/components/nsIRegistry.idl
 */

#ifndef __gen_nsIRegistry_h__
#define __gen_nsIRegistry_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIEnumerator_h__
#include "nsIEnumerator.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIFile; /* forward declaration */

typedef PRUint32 nsRegistryKey;

typedef PRInt32 nsWellKnownRegistry;


/* starting interface:    nsIRegistry */
#define NS_IREGISTRY_IID_STR "5d41a440-8e37-11d2-8059-00600811a9c3"

#define NS_IREGISTRY_IID \
  {0x5d41a440, 0x8e37, 0x11d2, \
    { 0x80, 0x59, 0x00, 0x60, 0x08, 0x11, 0xa9, 0xc3 }}

class NS_NO_VTABLE nsIRegistry : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IREGISTRY_IID)

  enum { None = 0 };

  enum { Users = 1 };

  enum { Common = 2 };

  enum { CurrentUser = 3 };

  enum { ApplicationComponentRegistry = 1 };

  enum { ApplicationRegistry = 2 };

  enum { ApplicationCustomRegistry = -1 };

  /* void open (in nsIFile regFile); */
  NS_IMETHOD Open(nsIFile *regFile) = 0;

  /* void openWellKnownRegistry (in nsWellKnownRegistry regid); */
  NS_IMETHOD OpenWellKnownRegistry(nsWellKnownRegistry regid) = 0;

  /* void flush (); */
  NS_IMETHOD Flush(void) = 0;

  /* boolean isOpen (); */
  NS_IMETHOD IsOpen(PRBool *_retval) = 0;

  /* nsRegistryKey addKey (in nsRegistryKey baseKey, in wstring keyname); */
  NS_IMETHOD AddKey(nsRegistryKey baseKey, const PRUnichar *keyname, nsRegistryKey *_retval) = 0;

  /* nsRegistryKey getKey (in nsRegistryKey baseKey, in wstring keyname); */
  NS_IMETHOD GetKey(nsRegistryKey baseKey, const PRUnichar *keyname, nsRegistryKey *_retval) = 0;

  /* void removeKey (in nsRegistryKey baseKey, in wstring keyname); */
  NS_IMETHOD RemoveKey(nsRegistryKey baseKey, const PRUnichar *keyname) = 0;

  /* wstring getString (in nsRegistryKey baseKey, in wstring valname); */
  NS_IMETHOD GetString(nsRegistryKey baseKey, const PRUnichar *valname, PRUnichar **_retval) = 0;

  /* void setString (in nsRegistryKey baseKey, in wstring valname, in wstring value); */
  NS_IMETHOD SetString(nsRegistryKey baseKey, const PRUnichar *valname, const PRUnichar *value) = 0;

  /* string getStringUTF8 (in nsRegistryKey baseKey, in string path); */
  NS_IMETHOD GetStringUTF8(nsRegistryKey baseKey, const char *path, char **_retval) = 0;

  /* void setStringUTF8 (in nsRegistryKey baseKey, in string path, in string value); */
  NS_IMETHOD SetStringUTF8(nsRegistryKey baseKey, const char *path, const char *value) = 0;

  /* void getBytesUTF8 (in nsRegistryKey baseKey, in string path, out PRUint32 length, [array, size_is (length), retval] out PRUint8 valueArray); */
  NS_IMETHOD GetBytesUTF8(nsRegistryKey baseKey, const char *path, PRUint32 *length, PRUint8 **valueArray) = 0;

  /* void setBytesUTF8 (in nsRegistryKey baseKey, in string path, in PRUint32 length, [array, size_is (length)] in PRUint8 valueArray); */
  NS_IMETHOD SetBytesUTF8(nsRegistryKey baseKey, const char *path, PRUint32 length, PRUint8 *valueArray) = 0;

  /* PRInt32 getInt (in nsRegistryKey baseKey, in string path); */
  NS_IMETHOD GetInt(nsRegistryKey baseKey, const char *path, PRInt32 *_retval) = 0;

  /* void setInt (in nsRegistryKey baseKey, in string path, in PRInt32 value); */
  NS_IMETHOD SetInt(nsRegistryKey baseKey, const char *path, PRInt32 value) = 0;

  /* PRInt64 getLongLong (in nsRegistryKey baseKey, in string path); */
  NS_IMETHOD GetLongLong(nsRegistryKey baseKey, const char *path, PRInt64 *_retval) = 0;

  /* void setLongLong (in nsRegistryKey baseKey, in string path, inout PRInt64 value); */
  NS_IMETHOD SetLongLong(nsRegistryKey baseKey, const char *path, PRInt64 *value) = 0;

  /**
     * addSubtree() and friends need to be renamed to addKeyUTF8().
     * If you are using these forms make sure you pass UTF8 data
     */
  /* nsRegistryKey addSubtree (in nsRegistryKey baseKey, in string path); */
  NS_IMETHOD AddSubtree(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval) = 0;

  /* void removeSubtree (in nsRegistryKey baseKey, in string path); */
  NS_IMETHOD RemoveSubtree(nsRegistryKey baseKey, const char *path) = 0;

  /* nsRegistryKey getSubtree (in nsRegistryKey baseKey, in string path); */
  NS_IMETHOD GetSubtree(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval) = 0;

  /* nsRegistryKey addSubtreeRaw (in nsRegistryKey baseKey, in string path); */
  NS_IMETHOD AddSubtreeRaw(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval) = 0;

  /* void removeSubtreeRaw (in nsRegistryKey baseKey, in string path); */
  NS_IMETHOD RemoveSubtreeRaw(nsRegistryKey baseKey, const char *path) = 0;

  /* nsRegistryKey getSubtreeRaw (in nsRegistryKey baseKey, in string path); */
  NS_IMETHOD GetSubtreeRaw(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval) = 0;

  /* nsIEnumerator enumerateSubtrees (in nsRegistryKey baseKey); */
  NS_IMETHOD EnumerateSubtrees(nsRegistryKey baseKey, nsIEnumerator **_retval) = 0;

  /* nsIEnumerator enumerateAllSubtrees (in nsRegistryKey baseKey); */
  NS_IMETHOD EnumerateAllSubtrees(nsRegistryKey baseKey, nsIEnumerator **_retval) = 0;

  /* nsIEnumerator enumerateValues (in nsRegistryKey baseKey); */
  NS_IMETHOD EnumerateValues(nsRegistryKey baseKey, nsIEnumerator **_retval) = 0;

  enum { String = 1U };

  enum { Int32 = 2U };

  enum { Bytes = 3U };

  enum { File = 4U };

  /* unsigned long getValueType (in nsRegistryKey baseKey, in string path); */
  NS_IMETHOD GetValueType(nsRegistryKey baseKey, const char *path, PRUint32 *_retval) = 0;

  /* PRUint32 getValueLength (in nsRegistryKey baseKey, in string path); */
  NS_IMETHOD GetValueLength(nsRegistryKey baseKey, const char *path, PRUint32 *_retval) = 0;

  /* void deleteValue (in nsRegistryKey baseKey, in string path); */
  NS_IMETHOD DeleteValue(nsRegistryKey baseKey, const char *path) = 0;

  /**
     * escapeKey() takes arbitrary binary data and converts it into
     * valid ASCII which can be used as registry key or value names
     */
  /* void escapeKey ([array, size_is (length)] in PRUint8 key, in PRUint32 terminator, inout PRUint32 length, [array, size_is (length), retval] out PRUint8 escaped); */
  NS_IMETHOD EscapeKey(PRUint8 *key, PRUint32 terminator, PRUint32 *length, PRUint8 **escaped) = 0;

  /* void unescapeKey ([array, size_is (length)] in PRUint8 escaped, in PRUint32 terminator, inout PRUint32 length, [array, size_is (length), retval] out PRUint8 key); */
  NS_IMETHOD UnescapeKey(PRUint8 *escaped, PRUint32 terminator, PRUint32 *length, PRUint8 **key) = 0;

  /* attribute string currentUserName; */
  NS_IMETHOD GetCurrentUserName(char * *aCurrentUserName) = 0;
  NS_IMETHOD SetCurrentUserName(const char * aCurrentUserName) = 0;

  /* void pack (); */
  NS_IMETHOD Pack(void) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIREGISTRY \
  NS_IMETHOD Open(nsIFile *regFile); \
  NS_IMETHOD OpenWellKnownRegistry(nsWellKnownRegistry regid); \
  NS_IMETHOD Flush(void); \
  NS_IMETHOD IsOpen(PRBool *_retval); \
  NS_IMETHOD AddKey(nsRegistryKey baseKey, const PRUnichar *keyname, nsRegistryKey *_retval); \
  NS_IMETHOD GetKey(nsRegistryKey baseKey, const PRUnichar *keyname, nsRegistryKey *_retval); \
  NS_IMETHOD RemoveKey(nsRegistryKey baseKey, const PRUnichar *keyname); \
  NS_IMETHOD GetString(nsRegistryKey baseKey, const PRUnichar *valname, PRUnichar **_retval); \
  NS_IMETHOD SetString(nsRegistryKey baseKey, const PRUnichar *valname, const PRUnichar *value); \
  NS_IMETHOD GetStringUTF8(nsRegistryKey baseKey, const char *path, char **_retval); \
  NS_IMETHOD SetStringUTF8(nsRegistryKey baseKey, const char *path, const char *value); \
  NS_IMETHOD GetBytesUTF8(nsRegistryKey baseKey, const char *path, PRUint32 *length, PRUint8 **valueArray); \
  NS_IMETHOD SetBytesUTF8(nsRegistryKey baseKey, const char *path, PRUint32 length, PRUint8 *valueArray); \
  NS_IMETHOD GetInt(nsRegistryKey baseKey, const char *path, PRInt32 *_retval); \
  NS_IMETHOD SetInt(nsRegistryKey baseKey, const char *path, PRInt32 value); \
  NS_IMETHOD GetLongLong(nsRegistryKey baseKey, const char *path, PRInt64 *_retval); \
  NS_IMETHOD SetLongLong(nsRegistryKey baseKey, const char *path, PRInt64 *value); \
  NS_IMETHOD AddSubtree(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval); \
  NS_IMETHOD RemoveSubtree(nsRegistryKey baseKey, const char *path); \
  NS_IMETHOD GetSubtree(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval); \
  NS_IMETHOD AddSubtreeRaw(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval); \
  NS_IMETHOD RemoveSubtreeRaw(nsRegistryKey baseKey, const char *path); \
  NS_IMETHOD GetSubtreeRaw(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval); \
  NS_IMETHOD EnumerateSubtrees(nsRegistryKey baseKey, nsIEnumerator **_retval); \
  NS_IMETHOD EnumerateAllSubtrees(nsRegistryKey baseKey, nsIEnumerator **_retval); \
  NS_IMETHOD EnumerateValues(nsRegistryKey baseKey, nsIEnumerator **_retval); \
  NS_IMETHOD GetValueType(nsRegistryKey baseKey, const char *path, PRUint32 *_retval); \
  NS_IMETHOD GetValueLength(nsRegistryKey baseKey, const char *path, PRUint32 *_retval); \
  NS_IMETHOD DeleteValue(nsRegistryKey baseKey, const char *path); \
  NS_IMETHOD EscapeKey(PRUint8 *key, PRUint32 terminator, PRUint32 *length, PRUint8 **escaped); \
  NS_IMETHOD UnescapeKey(PRUint8 *escaped, PRUint32 terminator, PRUint32 *length, PRUint8 **key); \
  NS_IMETHOD GetCurrentUserName(char * *aCurrentUserName); \
  NS_IMETHOD SetCurrentUserName(const char * aCurrentUserName); \
  NS_IMETHOD Pack(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIREGISTRY(_to) \
  NS_IMETHOD Open(nsIFile *regFile) { return _to Open(regFile); } \
  NS_IMETHOD OpenWellKnownRegistry(nsWellKnownRegistry regid) { return _to OpenWellKnownRegistry(regid); } \
  NS_IMETHOD Flush(void) { return _to Flush(); } \
  NS_IMETHOD IsOpen(PRBool *_retval) { return _to IsOpen(_retval); } \
  NS_IMETHOD AddKey(nsRegistryKey baseKey, const PRUnichar *keyname, nsRegistryKey *_retval) { return _to AddKey(baseKey, keyname, _retval); } \
  NS_IMETHOD GetKey(nsRegistryKey baseKey, const PRUnichar *keyname, nsRegistryKey *_retval) { return _to GetKey(baseKey, keyname, _retval); } \
  NS_IMETHOD RemoveKey(nsRegistryKey baseKey, const PRUnichar *keyname) { return _to RemoveKey(baseKey, keyname); } \
  NS_IMETHOD GetString(nsRegistryKey baseKey, const PRUnichar *valname, PRUnichar **_retval) { return _to GetString(baseKey, valname, _retval); } \
  NS_IMETHOD SetString(nsRegistryKey baseKey, const PRUnichar *valname, const PRUnichar *value) { return _to SetString(baseKey, valname, value); } \
  NS_IMETHOD GetStringUTF8(nsRegistryKey baseKey, const char *path, char **_retval) { return _to GetStringUTF8(baseKey, path, _retval); } \
  NS_IMETHOD SetStringUTF8(nsRegistryKey baseKey, const char *path, const char *value) { return _to SetStringUTF8(baseKey, path, value); } \
  NS_IMETHOD GetBytesUTF8(nsRegistryKey baseKey, const char *path, PRUint32 *length, PRUint8 **valueArray) { return _to GetBytesUTF8(baseKey, path, length, valueArray); } \
  NS_IMETHOD SetBytesUTF8(nsRegistryKey baseKey, const char *path, PRUint32 length, PRUint8 *valueArray) { return _to SetBytesUTF8(baseKey, path, length, valueArray); } \
  NS_IMETHOD GetInt(nsRegistryKey baseKey, const char *path, PRInt32 *_retval) { return _to GetInt(baseKey, path, _retval); } \
  NS_IMETHOD SetInt(nsRegistryKey baseKey, const char *path, PRInt32 value) { return _to SetInt(baseKey, path, value); } \
  NS_IMETHOD GetLongLong(nsRegistryKey baseKey, const char *path, PRInt64 *_retval) { return _to GetLongLong(baseKey, path, _retval); } \
  NS_IMETHOD SetLongLong(nsRegistryKey baseKey, const char *path, PRInt64 *value) { return _to SetLongLong(baseKey, path, value); } \
  NS_IMETHOD AddSubtree(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval) { return _to AddSubtree(baseKey, path, _retval); } \
  NS_IMETHOD RemoveSubtree(nsRegistryKey baseKey, const char *path) { return _to RemoveSubtree(baseKey, path); } \
  NS_IMETHOD GetSubtree(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval) { return _to GetSubtree(baseKey, path, _retval); } \
  NS_IMETHOD AddSubtreeRaw(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval) { return _to AddSubtreeRaw(baseKey, path, _retval); } \
  NS_IMETHOD RemoveSubtreeRaw(nsRegistryKey baseKey, const char *path) { return _to RemoveSubtreeRaw(baseKey, path); } \
  NS_IMETHOD GetSubtreeRaw(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval) { return _to GetSubtreeRaw(baseKey, path, _retval); } \
  NS_IMETHOD EnumerateSubtrees(nsRegistryKey baseKey, nsIEnumerator **_retval) { return _to EnumerateSubtrees(baseKey, _retval); } \
  NS_IMETHOD EnumerateAllSubtrees(nsRegistryKey baseKey, nsIEnumerator **_retval) { return _to EnumerateAllSubtrees(baseKey, _retval); } \
  NS_IMETHOD EnumerateValues(nsRegistryKey baseKey, nsIEnumerator **_retval) { return _to EnumerateValues(baseKey, _retval); } \
  NS_IMETHOD GetValueType(nsRegistryKey baseKey, const char *path, PRUint32 *_retval) { return _to GetValueType(baseKey, path, _retval); } \
  NS_IMETHOD GetValueLength(nsRegistryKey baseKey, const char *path, PRUint32 *_retval) { return _to GetValueLength(baseKey, path, _retval); } \
  NS_IMETHOD DeleteValue(nsRegistryKey baseKey, const char *path) { return _to DeleteValue(baseKey, path); } \
  NS_IMETHOD EscapeKey(PRUint8 *key, PRUint32 terminator, PRUint32 *length, PRUint8 **escaped) { return _to EscapeKey(key, terminator, length, escaped); } \
  NS_IMETHOD UnescapeKey(PRUint8 *escaped, PRUint32 terminator, PRUint32 *length, PRUint8 **key) { return _to UnescapeKey(escaped, terminator, length, key); } \
  NS_IMETHOD GetCurrentUserName(char * *aCurrentUserName) { return _to GetCurrentUserName(aCurrentUserName); } \
  NS_IMETHOD SetCurrentUserName(const char * aCurrentUserName) { return _to SetCurrentUserName(aCurrentUserName); } \
  NS_IMETHOD Pack(void) { return _to Pack(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIREGISTRY(_to) \
  NS_IMETHOD Open(nsIFile *regFile) { return !_to ? NS_ERROR_NULL_POINTER : _to->Open(regFile); } \
  NS_IMETHOD OpenWellKnownRegistry(nsWellKnownRegistry regid) { return !_to ? NS_ERROR_NULL_POINTER : _to->OpenWellKnownRegistry(regid); } \
  NS_IMETHOD Flush(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Flush(); } \
  NS_IMETHOD IsOpen(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsOpen(_retval); } \
  NS_IMETHOD AddKey(nsRegistryKey baseKey, const PRUnichar *keyname, nsRegistryKey *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddKey(baseKey, keyname, _retval); } \
  NS_IMETHOD GetKey(nsRegistryKey baseKey, const PRUnichar *keyname, nsRegistryKey *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetKey(baseKey, keyname, _retval); } \
  NS_IMETHOD RemoveKey(nsRegistryKey baseKey, const PRUnichar *keyname) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveKey(baseKey, keyname); } \
  NS_IMETHOD GetString(nsRegistryKey baseKey, const PRUnichar *valname, PRUnichar **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetString(baseKey, valname, _retval); } \
  NS_IMETHOD SetString(nsRegistryKey baseKey, const PRUnichar *valname, const PRUnichar *value) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetString(baseKey, valname, value); } \
  NS_IMETHOD GetStringUTF8(nsRegistryKey baseKey, const char *path, char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetStringUTF8(baseKey, path, _retval); } \
  NS_IMETHOD SetStringUTF8(nsRegistryKey baseKey, const char *path, const char *value) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetStringUTF8(baseKey, path, value); } \
  NS_IMETHOD GetBytesUTF8(nsRegistryKey baseKey, const char *path, PRUint32 *length, PRUint8 **valueArray) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBytesUTF8(baseKey, path, length, valueArray); } \
  NS_IMETHOD SetBytesUTF8(nsRegistryKey baseKey, const char *path, PRUint32 length, PRUint8 *valueArray) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetBytesUTF8(baseKey, path, length, valueArray); } \
  NS_IMETHOD GetInt(nsRegistryKey baseKey, const char *path, PRInt32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInt(baseKey, path, _retval); } \
  NS_IMETHOD SetInt(nsRegistryKey baseKey, const char *path, PRInt32 value) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetInt(baseKey, path, value); } \
  NS_IMETHOD GetLongLong(nsRegistryKey baseKey, const char *path, PRInt64 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLongLong(baseKey, path, _retval); } \
  NS_IMETHOD SetLongLong(nsRegistryKey baseKey, const char *path, PRInt64 *value) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLongLong(baseKey, path, value); } \
  NS_IMETHOD AddSubtree(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddSubtree(baseKey, path, _retval); } \
  NS_IMETHOD RemoveSubtree(nsRegistryKey baseKey, const char *path) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveSubtree(baseKey, path); } \
  NS_IMETHOD GetSubtree(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSubtree(baseKey, path, _retval); } \
  NS_IMETHOD AddSubtreeRaw(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddSubtreeRaw(baseKey, path, _retval); } \
  NS_IMETHOD RemoveSubtreeRaw(nsRegistryKey baseKey, const char *path) { return !_to ? NS_ERROR_NULL_POINTER : _to->RemoveSubtreeRaw(baseKey, path); } \
  NS_IMETHOD GetSubtreeRaw(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSubtreeRaw(baseKey, path, _retval); } \
  NS_IMETHOD EnumerateSubtrees(nsRegistryKey baseKey, nsIEnumerator **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->EnumerateSubtrees(baseKey, _retval); } \
  NS_IMETHOD EnumerateAllSubtrees(nsRegistryKey baseKey, nsIEnumerator **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->EnumerateAllSubtrees(baseKey, _retval); } \
  NS_IMETHOD EnumerateValues(nsRegistryKey baseKey, nsIEnumerator **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->EnumerateValues(baseKey, _retval); } \
  NS_IMETHOD GetValueType(nsRegistryKey baseKey, const char *path, PRUint32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetValueType(baseKey, path, _retval); } \
  NS_IMETHOD GetValueLength(nsRegistryKey baseKey, const char *path, PRUint32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetValueLength(baseKey, path, _retval); } \
  NS_IMETHOD DeleteValue(nsRegistryKey baseKey, const char *path) { return !_to ? NS_ERROR_NULL_POINTER : _to->DeleteValue(baseKey, path); } \
  NS_IMETHOD EscapeKey(PRUint8 *key, PRUint32 terminator, PRUint32 *length, PRUint8 **escaped) { return !_to ? NS_ERROR_NULL_POINTER : _to->EscapeKey(key, terminator, length, escaped); } \
  NS_IMETHOD UnescapeKey(PRUint8 *escaped, PRUint32 terminator, PRUint32 *length, PRUint8 **key) { return !_to ? NS_ERROR_NULL_POINTER : _to->UnescapeKey(escaped, terminator, length, key); } \
  NS_IMETHOD GetCurrentUserName(char * *aCurrentUserName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCurrentUserName(aCurrentUserName); } \
  NS_IMETHOD SetCurrentUserName(const char * aCurrentUserName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCurrentUserName(aCurrentUserName); } \
  NS_IMETHOD Pack(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Pack(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsRegistry : public nsIRegistry
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIREGISTRY

  nsRegistry();
  virtual ~nsRegistry();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsRegistry, nsIRegistry)

nsRegistry::nsRegistry()
{
  /* member initializers and constructor code */
}

nsRegistry::~nsRegistry()
{
  /* destructor code */
}

/* void open (in nsIFile regFile); */
NS_IMETHODIMP nsRegistry::Open(nsIFile *regFile)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void openWellKnownRegistry (in nsWellKnownRegistry regid); */
NS_IMETHODIMP nsRegistry::OpenWellKnownRegistry(nsWellKnownRegistry regid)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void flush (); */
NS_IMETHODIMP nsRegistry::Flush()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isOpen (); */
NS_IMETHODIMP nsRegistry::IsOpen(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsRegistryKey addKey (in nsRegistryKey baseKey, in wstring keyname); */
NS_IMETHODIMP nsRegistry::AddKey(nsRegistryKey baseKey, const PRUnichar *keyname, nsRegistryKey *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsRegistryKey getKey (in nsRegistryKey baseKey, in wstring keyname); */
NS_IMETHODIMP nsRegistry::GetKey(nsRegistryKey baseKey, const PRUnichar *keyname, nsRegistryKey *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeKey (in nsRegistryKey baseKey, in wstring keyname); */
NS_IMETHODIMP nsRegistry::RemoveKey(nsRegistryKey baseKey, const PRUnichar *keyname)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring getString (in nsRegistryKey baseKey, in wstring valname); */
NS_IMETHODIMP nsRegistry::GetString(nsRegistryKey baseKey, const PRUnichar *valname, PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setString (in nsRegistryKey baseKey, in wstring valname, in wstring value); */
NS_IMETHODIMP nsRegistry::SetString(nsRegistryKey baseKey, const PRUnichar *valname, const PRUnichar *value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string getStringUTF8 (in nsRegistryKey baseKey, in string path); */
NS_IMETHODIMP nsRegistry::GetStringUTF8(nsRegistryKey baseKey, const char *path, char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setStringUTF8 (in nsRegistryKey baseKey, in string path, in string value); */
NS_IMETHODIMP nsRegistry::SetStringUTF8(nsRegistryKey baseKey, const char *path, const char *value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getBytesUTF8 (in nsRegistryKey baseKey, in string path, out PRUint32 length, [array, size_is (length), retval] out PRUint8 valueArray); */
NS_IMETHODIMP nsRegistry::GetBytesUTF8(nsRegistryKey baseKey, const char *path, PRUint32 *length, PRUint8 **valueArray)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setBytesUTF8 (in nsRegistryKey baseKey, in string path, in PRUint32 length, [array, size_is (length)] in PRUint8 valueArray); */
NS_IMETHODIMP nsRegistry::SetBytesUTF8(nsRegistryKey baseKey, const char *path, PRUint32 length, PRUint8 *valueArray)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* PRInt32 getInt (in nsRegistryKey baseKey, in string path); */
NS_IMETHODIMP nsRegistry::GetInt(nsRegistryKey baseKey, const char *path, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setInt (in nsRegistryKey baseKey, in string path, in PRInt32 value); */
NS_IMETHODIMP nsRegistry::SetInt(nsRegistryKey baseKey, const char *path, PRInt32 value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* PRInt64 getLongLong (in nsRegistryKey baseKey, in string path); */
NS_IMETHODIMP nsRegistry::GetLongLong(nsRegistryKey baseKey, const char *path, PRInt64 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setLongLong (in nsRegistryKey baseKey, in string path, inout PRInt64 value); */
NS_IMETHODIMP nsRegistry::SetLongLong(nsRegistryKey baseKey, const char *path, PRInt64 *value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsRegistryKey addSubtree (in nsRegistryKey baseKey, in string path); */
NS_IMETHODIMP nsRegistry::AddSubtree(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeSubtree (in nsRegistryKey baseKey, in string path); */
NS_IMETHODIMP nsRegistry::RemoveSubtree(nsRegistryKey baseKey, const char *path)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsRegistryKey getSubtree (in nsRegistryKey baseKey, in string path); */
NS_IMETHODIMP nsRegistry::GetSubtree(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsRegistryKey addSubtreeRaw (in nsRegistryKey baseKey, in string path); */
NS_IMETHODIMP nsRegistry::AddSubtreeRaw(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void removeSubtreeRaw (in nsRegistryKey baseKey, in string path); */
NS_IMETHODIMP nsRegistry::RemoveSubtreeRaw(nsRegistryKey baseKey, const char *path)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsRegistryKey getSubtreeRaw (in nsRegistryKey baseKey, in string path); */
NS_IMETHODIMP nsRegistry::GetSubtreeRaw(nsRegistryKey baseKey, const char *path, nsRegistryKey *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIEnumerator enumerateSubtrees (in nsRegistryKey baseKey); */
NS_IMETHODIMP nsRegistry::EnumerateSubtrees(nsRegistryKey baseKey, nsIEnumerator **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIEnumerator enumerateAllSubtrees (in nsRegistryKey baseKey); */
NS_IMETHODIMP nsRegistry::EnumerateAllSubtrees(nsRegistryKey baseKey, nsIEnumerator **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIEnumerator enumerateValues (in nsRegistryKey baseKey); */
NS_IMETHODIMP nsRegistry::EnumerateValues(nsRegistryKey baseKey, nsIEnumerator **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* unsigned long getValueType (in nsRegistryKey baseKey, in string path); */
NS_IMETHODIMP nsRegistry::GetValueType(nsRegistryKey baseKey, const char *path, PRUint32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* PRUint32 getValueLength (in nsRegistryKey baseKey, in string path); */
NS_IMETHODIMP nsRegistry::GetValueLength(nsRegistryKey baseKey, const char *path, PRUint32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void deleteValue (in nsRegistryKey baseKey, in string path); */
NS_IMETHODIMP nsRegistry::DeleteValue(nsRegistryKey baseKey, const char *path)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void escapeKey ([array, size_is (length)] in PRUint8 key, in PRUint32 terminator, inout PRUint32 length, [array, size_is (length), retval] out PRUint8 escaped); */
NS_IMETHODIMP nsRegistry::EscapeKey(PRUint8 *key, PRUint32 terminator, PRUint32 *length, PRUint8 **escaped)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void unescapeKey ([array, size_is (length)] in PRUint8 escaped, in PRUint32 terminator, inout PRUint32 length, [array, size_is (length), retval] out PRUint8 key); */
NS_IMETHODIMP nsRegistry::UnescapeKey(PRUint8 *escaped, PRUint32 terminator, PRUint32 *length, PRUint8 **key)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute string currentUserName; */
NS_IMETHODIMP nsRegistry::GetCurrentUserName(char * *aCurrentUserName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsRegistry::SetCurrentUserName(const char * aCurrentUserName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void pack (); */
NS_IMETHODIMP nsRegistry::Pack()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIRegistryEnumerator */
#define NS_IREGISTRYENUMERATOR_IID_STR "8cecf236-1dd2-11b2-893c-f9848956eaec"

#define NS_IREGISTRYENUMERATOR_IID \
  {0x8cecf236, 0x1dd2, 0x11b2, \
    { 0x89, 0x3c, 0xf9, 0x84, 0x89, 0x56, 0xea, 0xec }}

class NS_NO_VTABLE nsIRegistryEnumerator : public nsIEnumerator {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IREGISTRYENUMERATOR_IID)

  /* void currentItemInPlaceUTF8 (out nsRegistryKey key, [shared, retval] out string item); */
  NS_IMETHOD CurrentItemInPlaceUTF8(nsRegistryKey *key, const char **item) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIREGISTRYENUMERATOR \
  NS_IMETHOD CurrentItemInPlaceUTF8(nsRegistryKey *key, const char **item); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIREGISTRYENUMERATOR(_to) \
  NS_IMETHOD CurrentItemInPlaceUTF8(nsRegistryKey *key, const char **item) { return _to CurrentItemInPlaceUTF8(key, item); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIREGISTRYENUMERATOR(_to) \
  NS_IMETHOD CurrentItemInPlaceUTF8(nsRegistryKey *key, const char **item) { return !_to ? NS_ERROR_NULL_POINTER : _to->CurrentItemInPlaceUTF8(key, item); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsRegistryEnumerator : public nsIRegistryEnumerator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIREGISTRYENUMERATOR

  nsRegistryEnumerator();
  virtual ~nsRegistryEnumerator();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsRegistryEnumerator, nsIRegistryEnumerator)

nsRegistryEnumerator::nsRegistryEnumerator()
{
  /* member initializers and constructor code */
}

nsRegistryEnumerator::~nsRegistryEnumerator()
{
  /* destructor code */
}

/* void currentItemInPlaceUTF8 (out nsRegistryKey key, [shared, retval] out string item); */
NS_IMETHODIMP nsRegistryEnumerator::CurrentItemInPlaceUTF8(nsRegistryKey *key, const char **item)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIRegistryNode */
#define NS_IREGISTRYNODE_IID_STR "d1b54831-ac07-11d2-805e-00600811a9c3"

#define NS_IREGISTRYNODE_IID \
  {0xd1b54831, 0xac07, 0x11d2, \
    { 0x80, 0x5e, 0x00, 0x60, 0x08, 0x11, 0xa9, 0xc3 }}

class NS_NO_VTABLE nsIRegistryNode : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IREGISTRYNODE_IID)

  /* readonly attribute string nameUTF8; */
  NS_IMETHOD GetNameUTF8(char * *aNameUTF8) = 0;

  /* readonly attribute wstring name; */
  NS_IMETHOD GetName(PRUnichar * *aName) = 0;

  /* readonly attribute nsRegistryKey key; */
  NS_IMETHOD GetKey(nsRegistryKey *aKey) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIREGISTRYNODE \
  NS_IMETHOD GetNameUTF8(char * *aNameUTF8); \
  NS_IMETHOD GetName(PRUnichar * *aName); \
  NS_IMETHOD GetKey(nsRegistryKey *aKey); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIREGISTRYNODE(_to) \
  NS_IMETHOD GetNameUTF8(char * *aNameUTF8) { return _to GetNameUTF8(aNameUTF8); } \
  NS_IMETHOD GetName(PRUnichar * *aName) { return _to GetName(aName); } \
  NS_IMETHOD GetKey(nsRegistryKey *aKey) { return _to GetKey(aKey); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIREGISTRYNODE(_to) \
  NS_IMETHOD GetNameUTF8(char * *aNameUTF8) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNameUTF8(aNameUTF8); } \
  NS_IMETHOD GetName(PRUnichar * *aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetName(aName); } \
  NS_IMETHOD GetKey(nsRegistryKey *aKey) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetKey(aKey); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsRegistryNode : public nsIRegistryNode
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIREGISTRYNODE

  nsRegistryNode();
  virtual ~nsRegistryNode();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsRegistryNode, nsIRegistryNode)

nsRegistryNode::nsRegistryNode()
{
  /* member initializers and constructor code */
}

nsRegistryNode::~nsRegistryNode()
{
  /* destructor code */
}

/* readonly attribute string nameUTF8; */
NS_IMETHODIMP nsRegistryNode::GetNameUTF8(char * *aNameUTF8)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute wstring name; */
NS_IMETHODIMP nsRegistryNode::GetName(PRUnichar * *aName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsRegistryKey key; */
NS_IMETHODIMP nsRegistryNode::GetKey(nsRegistryKey *aKey)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIRegistryValue */
#define NS_IREGISTRYVALUE_IID_STR "5316c380-b2f8-11d2-a374-0080c6f80e4b"

#define NS_IREGISTRYVALUE_IID \
  {0x5316c380, 0xb2f8, 0x11d2, \
    { 0xa3, 0x74, 0x00, 0x80, 0xc6, 0xf8, 0x0e, 0x4b }}

class NS_NO_VTABLE nsIRegistryValue : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IREGISTRYVALUE_IID)

  /* readonly attribute wstring name; */
  NS_IMETHOD GetName(PRUnichar * *aName) = 0;

  /* readonly attribute string nameUTF8; */
  NS_IMETHOD GetNameUTF8(char * *aNameUTF8) = 0;

  /* readonly attribute unsigned long type; */
  NS_IMETHOD GetType(PRUint32 *aType) = 0;

  /* readonly attribute PRUint32 length; */
  NS_IMETHOD GetLength(PRUint32 *aLength) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIREGISTRYVALUE \
  NS_IMETHOD GetName(PRUnichar * *aName); \
  NS_IMETHOD GetNameUTF8(char * *aNameUTF8); \
  NS_IMETHOD GetType(PRUint32 *aType); \
  NS_IMETHOD GetLength(PRUint32 *aLength); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIREGISTRYVALUE(_to) \
  NS_IMETHOD GetName(PRUnichar * *aName) { return _to GetName(aName); } \
  NS_IMETHOD GetNameUTF8(char * *aNameUTF8) { return _to GetNameUTF8(aNameUTF8); } \
  NS_IMETHOD GetType(PRUint32 *aType) { return _to GetType(aType); } \
  NS_IMETHOD GetLength(PRUint32 *aLength) { return _to GetLength(aLength); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIREGISTRYVALUE(_to) \
  NS_IMETHOD GetName(PRUnichar * *aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetName(aName); } \
  NS_IMETHOD GetNameUTF8(char * *aNameUTF8) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNameUTF8(aNameUTF8); } \
  NS_IMETHOD GetType(PRUint32 *aType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetType(aType); } \
  NS_IMETHOD GetLength(PRUint32 *aLength) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLength(aLength); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsRegistryValue : public nsIRegistryValue
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIREGISTRYVALUE

  nsRegistryValue();
  virtual ~nsRegistryValue();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsRegistryValue, nsIRegistryValue)

nsRegistryValue::nsRegistryValue()
{
  /* member initializers and constructor code */
}

nsRegistryValue::~nsRegistryValue()
{
  /* destructor code */
}

/* readonly attribute wstring name; */
NS_IMETHODIMP nsRegistryValue::GetName(PRUnichar * *aName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute string nameUTF8; */
NS_IMETHODIMP nsRegistryValue::GetNameUTF8(char * *aNameUTF8)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute unsigned long type; */
NS_IMETHODIMP nsRegistryValue::GetType(PRUint32 *aType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute PRUint32 length; */
NS_IMETHODIMP nsRegistryValue::GetLength(PRUint32 *aLength)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIRegistryGetter */
#define NS_IREGISTRYGETTER_IID_STR "3a15fc88-7a61-4ab4-8e58-31e95fab3da8"

#define NS_IREGISTRYGETTER_IID \
  {0x3a15fc88, 0x7a61, 0x4ab4, \
    { 0x8e, 0x58, 0x31, 0xe9, 0x5f, 0xab, 0x3d, 0xa8 }}

/**
 * It sucks that nsIRegistry has to always allocate and return
 * strings. nsIRegistryGetter adds in interfaces for non allocating getters
 * to registry values.
 */
class NS_NO_VTABLE nsIRegistryGetter : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IREGISTRYGETTER_IID)

  /**
     * Get a string value of attribute valname in widestring or utf8 format
     *
     * @return
     *  NS_OK on success.
     *    buf has the string value copied into it. length is NOT changed.
     *  NS_ERROR_REG_BUFFER_TOO_SMALL if not enough buffer space.
     *    length is updated to actual length in chars including
     *    terminating NULL and buf will be unchanged.
     *  NS_ERROR_FAILURE if an unknown error happened. state of buf and
     *    length undefined.
     *  various failure codes otherwise. buf and length wont be updated.
     */
  /* void getStringUTF8IntoBuffer (in nsRegistryKey baseKey, in string path, inout char buf, inout PRUint32 length); */
  NS_IMETHOD GetStringUTF8IntoBuffer(nsRegistryKey baseKey, const char *path, char *buf, PRUint32 *length) = 0;

  /**
     * Get a a byte array value of attribute valname
     *
     * @return
     *  NS_OK on success. buf has the string value copied into it.
     *    length is updated to actual number of bytes copied into buf.
     *  NS_ERROR_REG_BUFFER_TOO_SMALL if not enough buffer space.
     *    length is updated to actual length in PRUint8s including
     *    terminating NULL and buf will be unchanged.
     *  NS_ERROR_FAILURE if an unknown error happened. state of buf and
     *    length undefined.
     *  various other failure codes otherwise. buf and length wont be updated.
     */
  /* void getBytesUTF8IntoBuffer (in nsRegistryKey baseKey, in string path, inout PRUint8 buf, inout PRUint32 length); */
  NS_IMETHOD GetBytesUTF8IntoBuffer(nsRegistryKey baseKey, const char *path, PRUint8 *buf, PRUint32 *length) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIREGISTRYGETTER \
  NS_IMETHOD GetStringUTF8IntoBuffer(nsRegistryKey baseKey, const char *path, char *buf, PRUint32 *length); \
  NS_IMETHOD GetBytesUTF8IntoBuffer(nsRegistryKey baseKey, const char *path, PRUint8 *buf, PRUint32 *length); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIREGISTRYGETTER(_to) \
  NS_IMETHOD GetStringUTF8IntoBuffer(nsRegistryKey baseKey, const char *path, char *buf, PRUint32 *length) { return _to GetStringUTF8IntoBuffer(baseKey, path, buf, length); } \
  NS_IMETHOD GetBytesUTF8IntoBuffer(nsRegistryKey baseKey, const char *path, PRUint8 *buf, PRUint32 *length) { return _to GetBytesUTF8IntoBuffer(baseKey, path, buf, length); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIREGISTRYGETTER(_to) \
  NS_IMETHOD GetStringUTF8IntoBuffer(nsRegistryKey baseKey, const char *path, char *buf, PRUint32 *length) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetStringUTF8IntoBuffer(baseKey, path, buf, length); } \
  NS_IMETHOD GetBytesUTF8IntoBuffer(nsRegistryKey baseKey, const char *path, PRUint8 *buf, PRUint32 *length) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetBytesUTF8IntoBuffer(baseKey, path, buf, length); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsRegistryGetter : public nsIRegistryGetter
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIREGISTRYGETTER

  nsRegistryGetter();
  virtual ~nsRegistryGetter();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsRegistryGetter, nsIRegistryGetter)

nsRegistryGetter::nsRegistryGetter()
{
  /* member initializers and constructor code */
}

nsRegistryGetter::~nsRegistryGetter()
{
  /* destructor code */
}

/* void getStringUTF8IntoBuffer (in nsRegistryKey baseKey, in string path, inout char buf, inout PRUint32 length); */
NS_IMETHODIMP nsRegistryGetter::GetStringUTF8IntoBuffer(nsRegistryKey baseKey, const char *path, char *buf, PRUint32 *length)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void getBytesUTF8IntoBuffer (in nsRegistryKey baseKey, in string path, inout PRUint8 buf, inout PRUint32 length); */
NS_IMETHODIMP nsRegistryGetter::GetBytesUTF8IntoBuffer(nsRegistryKey baseKey, const char *path, PRUint8 *buf, PRUint32 *length)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

#include "nsIRegistryUtils.h"

#endif /* __gen_nsIRegistry_h__ */
