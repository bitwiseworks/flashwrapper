/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/xpcom/io/nsIFileSpec.idl
 */

#ifndef __gen_nsIFileSpec_h__
#define __gen_nsIFileSpec_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
#include "nsFileSpec.h" // for factory method
class nsIFileURL; /* forward declaration */

class nsIFilePath; /* forward declaration */

class nsIOutputStream; /* forward declaration */

class nsIInputStream; /* forward declaration */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
    THIS INTERFACE IS DEPRECATED AND UNSUPPORTED!  USE |nsIFile| and |nsILocalFile|.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// {A5740FA2-146E-11d3-B00D-00C04FC2E79B} 
#define NS_FILESPEC_CID \
{ 0xa5740fa2, 0x146e, 0x11d3, { 0xb0, 0xd, 0x0, 0xc0, 0x4f, 0xc2, 0xe7, 0x9b } }
#define NS_FILESPEC_CONTRACTID "@mozilla.org/filespec;1"
#define NS_FILESPEC_CLASSNAME "File Spec"

/* starting interface:    nsIFileSpec */
#define NS_IFILESPEC_IID_STR "d8c0a080-0868-11d3-915f-d9d889d48e3c"

#define NS_IFILESPEC_IID \
  {0xd8c0a080, 0x0868, 0x11d3, \
    { 0x91, 0x5f, 0xd9, 0xd8, 0x89, 0xd4, 0x8e, 0x3c }}

class NS_NO_VTABLE nsIFileSpec : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IFILESPEC_IID)

  /* void fromFileSpec ([const] in nsIFileSpec original); */
  NS_IMETHOD FromFileSpec(const nsIFileSpec *original) = 0;

  /* attribute string URLString; */
  NS_IMETHOD GetURLString(char * *aURLString) = 0;
  NS_IMETHOD SetURLString(const char * aURLString) = 0;

  /* attribute string unixStyleFilePath; */
  NS_IMETHOD GetUnixStyleFilePath(char * *aUnixStyleFilePath) = 0;
  NS_IMETHOD SetUnixStyleFilePath(const char * aUnixStyleFilePath) = 0;

  /* attribute string persistentDescriptorString; */
  NS_IMETHOD GetPersistentDescriptorString(char * *aPersistentDescriptorString) = 0;
  NS_IMETHOD SetPersistentDescriptorString(const char * aPersistentDescriptorString) = 0;

  /* attribute string nativePath; */
  NS_IMETHOD GetNativePath(char * *aNativePath) = 0;
  NS_IMETHOD SetNativePath(const char * aNativePath) = 0;

  /* readonly attribute string NSPRPath; */
  NS_IMETHOD GetNSPRPath(char * *aNSPRPath) = 0;

  /* void error (); */
  NS_IMETHOD Error(void) = 0;

  /* boolean isValid (); */
  NS_IMETHOD IsValid(PRBool *_retval) = 0;

  /* boolean failed (); */
  NS_IMETHOD Failed(PRBool *_retval) = 0;

  /* attribute string leafName; */
  NS_IMETHOD GetLeafName(char * *aLeafName) = 0;
  NS_IMETHOD SetLeafName(const char * aLeafName) = 0;

  /* readonly attribute nsIFileSpec parent; */
  NS_IMETHOD GetParent(nsIFileSpec * *aParent) = 0;

  /* readonly attribute nsIInputStream inputStream; */
  NS_IMETHOD GetInputStream(nsIInputStream * *aInputStream) = 0;

  /* readonly attribute nsIOutputStream outputStream; */
  NS_IMETHOD GetOutputStream(nsIOutputStream * *aOutputStream) = 0;

  /* boolean isChildOf (in nsIFileSpec possibleParent); */
  NS_IMETHOD IsChildOf(nsIFileSpec *possibleParent, PRBool *_retval) = 0;

  /* [noscript] readonly attribute nsFileSpec fileSpec; */
  NS_IMETHOD GetFileSpec(nsFileSpec *aFileSpec) = 0;

  /* [noscript] void setFromFileSpec ([const] in nsFileSpecRef spec); */
  NS_IMETHOD SetFromFileSpec(const nsFileSpec & spec) = 0;

  /* attribute string fileContents; */
  NS_IMETHOD GetFileContents(char * *aFileContents) = 0;
  NS_IMETHOD SetFileContents(const char * aFileContents) = 0;

  /* void makeUnique (); */
  NS_IMETHOD MakeUnique(void) = 0;

  /* void makeUniqueWithSuggestedName (in string suggestedName); */
  NS_IMETHOD MakeUniqueWithSuggestedName(const char *suggestedName) = 0;

  /* readonly attribute unsigned long modDate; */
  NS_IMETHOD GetModDate(PRUint32 *aModDate) = 0;

  /* boolean modDateChanged (in unsigned long oldStamp); */
  NS_IMETHOD ModDateChanged(PRUint32 oldStamp, PRBool *_retval) = 0;

  /* boolean isDirectory (); */
  NS_IMETHOD IsDirectory(PRBool *_retval) = 0;

  /* boolean isFile (); */
  NS_IMETHOD IsFile(PRBool *_retval) = 0;

  /* boolean exists (); */
  NS_IMETHOD Exists(PRBool *_retval) = 0;

  /* boolean isHidden (); */
  NS_IMETHOD IsHidden(PRBool *_retval) = 0;

  /* boolean equals (in nsIFileSpec spec); */
  NS_IMETHOD Equals(nsIFileSpec *spec, PRBool *_retval) = 0;

  /* readonly attribute unsigned long fileSize; */
  NS_IMETHOD GetFileSize(PRUint32 *aFileSize) = 0;

  /* readonly attribute long long diskSpaceAvailable; */
  NS_IMETHOD GetDiskSpaceAvailable(PRInt64 *aDiskSpaceAvailable) = 0;

  /* void appendRelativeUnixPath (in string relativePath); */
  NS_IMETHOD AppendRelativeUnixPath(const char *relativePath) = 0;

  /* void createDir (); */
  NS_IMETHOD CreateDir(void) = 0;

  /* void touch (); */
  NS_IMETHOD Touch(void) = 0;

  /* boolean isSymlink (); */
  NS_IMETHOD IsSymlink(PRBool *_retval) = 0;

  /* void resolveSymlink (); */
  NS_IMETHOD ResolveSymlink(void) = 0;

  /* void delete (in boolean recursive); */
  NS_IMETHOD Delete(PRBool recursive) = 0;

  /* void truncate (in long aNewLength); */
  NS_IMETHOD Truncate(PRInt32 aNewLength) = 0;

  /* void rename ([const] in string newLeafName); */
  NS_IMETHOD Rename(const char *newLeafName) = 0;

  /* void copyToDir ([const] in nsIFileSpec newParentDir); */
  NS_IMETHOD CopyToDir(const nsIFileSpec *newParentDir) = 0;

  /* void moveToDir ([const] in nsIFileSpec newParentDir); */
  NS_IMETHOD MoveToDir(const nsIFileSpec *newParentDir) = 0;

  /* void execute ([const] in string args); */
  NS_IMETHOD Execute(const char *args) = 0;

  /* void openStreamForReading (); */
  NS_IMETHOD OpenStreamForReading(void) = 0;

  /* void openStreamForWriting (); */
  NS_IMETHOD OpenStreamForWriting(void) = 0;

  /* void openStreamForReadingAndWriting (); */
  NS_IMETHOD OpenStreamForReadingAndWriting(void) = 0;

  /* void closeStream (); */
  NS_IMETHOD CloseStream(void) = 0;

  /* boolean isStreamOpen (); */
  NS_IMETHOD IsStreamOpen(PRBool *_retval) = 0;

  /* boolean eof (); */
  NS_IMETHOD Eof(PRBool *_retval) = 0;

  /* long read (inout string buffer, in long requestedCount); */
  NS_IMETHOD Read(char **buffer, PRInt32 requestedCount, PRInt32 *_retval) = 0;

  /* void readLine (inout string line, in long bufferSize, out boolean wasTruncated); */
  NS_IMETHOD ReadLine(char **line, PRInt32 bufferSize, PRBool *wasTruncated) = 0;

  /** Check eof() before each call.
     * CAUTION: false result only indicates line was truncated
     * to fit buffer, or an error occurred (OTHER THAN eof).
     */
  /* long write (in string data, in long requestedCount); */
  NS_IMETHOD Write(const char *data, PRInt32 requestedCount, PRInt32 *_retval) = 0;

  /* void flush (); */
  NS_IMETHOD Flush(void) = 0;

  /* void seek (in long offset); */
  NS_IMETHOD Seek(PRInt32 offset) = 0;

  /* long tell (); */
  NS_IMETHOD Tell(PRInt32 *_retval) = 0;

  /* void endLine (); */
  NS_IMETHOD EndLine(void) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIFILESPEC \
  NS_IMETHOD FromFileSpec(const nsIFileSpec *original); \
  NS_IMETHOD GetURLString(char * *aURLString); \
  NS_IMETHOD SetURLString(const char * aURLString); \
  NS_IMETHOD GetUnixStyleFilePath(char * *aUnixStyleFilePath); \
  NS_IMETHOD SetUnixStyleFilePath(const char * aUnixStyleFilePath); \
  NS_IMETHOD GetPersistentDescriptorString(char * *aPersistentDescriptorString); \
  NS_IMETHOD SetPersistentDescriptorString(const char * aPersistentDescriptorString); \
  NS_IMETHOD GetNativePath(char * *aNativePath); \
  NS_IMETHOD SetNativePath(const char * aNativePath); \
  NS_IMETHOD GetNSPRPath(char * *aNSPRPath); \
  NS_IMETHOD Error(void); \
  NS_IMETHOD IsValid(PRBool *_retval); \
  NS_IMETHOD Failed(PRBool *_retval); \
  NS_IMETHOD GetLeafName(char * *aLeafName); \
  NS_IMETHOD SetLeafName(const char * aLeafName); \
  NS_IMETHOD GetParent(nsIFileSpec * *aParent); \
  NS_IMETHOD GetInputStream(nsIInputStream * *aInputStream); \
  NS_IMETHOD GetOutputStream(nsIOutputStream * *aOutputStream); \
  NS_IMETHOD IsChildOf(nsIFileSpec *possibleParent, PRBool *_retval); \
  NS_IMETHOD GetFileSpec(nsFileSpec *aFileSpec); \
  NS_IMETHOD SetFromFileSpec(const nsFileSpec & spec); \
  NS_IMETHOD GetFileContents(char * *aFileContents); \
  NS_IMETHOD SetFileContents(const char * aFileContents); \
  NS_IMETHOD MakeUnique(void); \
  NS_IMETHOD MakeUniqueWithSuggestedName(const char *suggestedName); \
  NS_IMETHOD GetModDate(PRUint32 *aModDate); \
  NS_IMETHOD ModDateChanged(PRUint32 oldStamp, PRBool *_retval); \
  NS_IMETHOD IsDirectory(PRBool *_retval); \
  NS_IMETHOD IsFile(PRBool *_retval); \
  NS_IMETHOD Exists(PRBool *_retval); \
  NS_IMETHOD IsHidden(PRBool *_retval); \
  NS_IMETHOD Equals(nsIFileSpec *spec, PRBool *_retval); \
  NS_IMETHOD GetFileSize(PRUint32 *aFileSize); \
  NS_IMETHOD GetDiskSpaceAvailable(PRInt64 *aDiskSpaceAvailable); \
  NS_IMETHOD AppendRelativeUnixPath(const char *relativePath); \
  NS_IMETHOD CreateDir(void); \
  NS_IMETHOD Touch(void); \
  NS_IMETHOD IsSymlink(PRBool *_retval); \
  NS_IMETHOD ResolveSymlink(void); \
  NS_IMETHOD Delete(PRBool recursive); \
  NS_IMETHOD Truncate(PRInt32 aNewLength); \
  NS_IMETHOD Rename(const char *newLeafName); \
  NS_IMETHOD CopyToDir(const nsIFileSpec *newParentDir); \
  NS_IMETHOD MoveToDir(const nsIFileSpec *newParentDir); \
  NS_IMETHOD Execute(const char *args); \
  NS_IMETHOD OpenStreamForReading(void); \
  NS_IMETHOD OpenStreamForWriting(void); \
  NS_IMETHOD OpenStreamForReadingAndWriting(void); \
  NS_IMETHOD CloseStream(void); \
  NS_IMETHOD IsStreamOpen(PRBool *_retval); \
  NS_IMETHOD Eof(PRBool *_retval); \
  NS_IMETHOD Read(char **buffer, PRInt32 requestedCount, PRInt32 *_retval); \
  NS_IMETHOD ReadLine(char **line, PRInt32 bufferSize, PRBool *wasTruncated); \
  NS_IMETHOD Write(const char *data, PRInt32 requestedCount, PRInt32 *_retval); \
  NS_IMETHOD Flush(void); \
  NS_IMETHOD Seek(PRInt32 offset); \
  NS_IMETHOD Tell(PRInt32 *_retval); \
  NS_IMETHOD EndLine(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIFILESPEC(_to) \
  NS_IMETHOD FromFileSpec(const nsIFileSpec *original) { return _to FromFileSpec(original); } \
  NS_IMETHOD GetURLString(char * *aURLString) { return _to GetURLString(aURLString); } \
  NS_IMETHOD SetURLString(const char * aURLString) { return _to SetURLString(aURLString); } \
  NS_IMETHOD GetUnixStyleFilePath(char * *aUnixStyleFilePath) { return _to GetUnixStyleFilePath(aUnixStyleFilePath); } \
  NS_IMETHOD SetUnixStyleFilePath(const char * aUnixStyleFilePath) { return _to SetUnixStyleFilePath(aUnixStyleFilePath); } \
  NS_IMETHOD GetPersistentDescriptorString(char * *aPersistentDescriptorString) { return _to GetPersistentDescriptorString(aPersistentDescriptorString); } \
  NS_IMETHOD SetPersistentDescriptorString(const char * aPersistentDescriptorString) { return _to SetPersistentDescriptorString(aPersistentDescriptorString); } \
  NS_IMETHOD GetNativePath(char * *aNativePath) { return _to GetNativePath(aNativePath); } \
  NS_IMETHOD SetNativePath(const char * aNativePath) { return _to SetNativePath(aNativePath); } \
  NS_IMETHOD GetNSPRPath(char * *aNSPRPath) { return _to GetNSPRPath(aNSPRPath); } \
  NS_IMETHOD Error(void) { return _to Error(); } \
  NS_IMETHOD IsValid(PRBool *_retval) { return _to IsValid(_retval); } \
  NS_IMETHOD Failed(PRBool *_retval) { return _to Failed(_retval); } \
  NS_IMETHOD GetLeafName(char * *aLeafName) { return _to GetLeafName(aLeafName); } \
  NS_IMETHOD SetLeafName(const char * aLeafName) { return _to SetLeafName(aLeafName); } \
  NS_IMETHOD GetParent(nsIFileSpec * *aParent) { return _to GetParent(aParent); } \
  NS_IMETHOD GetInputStream(nsIInputStream * *aInputStream) { return _to GetInputStream(aInputStream); } \
  NS_IMETHOD GetOutputStream(nsIOutputStream * *aOutputStream) { return _to GetOutputStream(aOutputStream); } \
  NS_IMETHOD IsChildOf(nsIFileSpec *possibleParent, PRBool *_retval) { return _to IsChildOf(possibleParent, _retval); } \
  NS_IMETHOD GetFileSpec(nsFileSpec *aFileSpec) { return _to GetFileSpec(aFileSpec); } \
  NS_IMETHOD SetFromFileSpec(const nsFileSpec & spec) { return _to SetFromFileSpec(spec); } \
  NS_IMETHOD GetFileContents(char * *aFileContents) { return _to GetFileContents(aFileContents); } \
  NS_IMETHOD SetFileContents(const char * aFileContents) { return _to SetFileContents(aFileContents); } \
  NS_IMETHOD MakeUnique(void) { return _to MakeUnique(); } \
  NS_IMETHOD MakeUniqueWithSuggestedName(const char *suggestedName) { return _to MakeUniqueWithSuggestedName(suggestedName); } \
  NS_IMETHOD GetModDate(PRUint32 *aModDate) { return _to GetModDate(aModDate); } \
  NS_IMETHOD ModDateChanged(PRUint32 oldStamp, PRBool *_retval) { return _to ModDateChanged(oldStamp, _retval); } \
  NS_IMETHOD IsDirectory(PRBool *_retval) { return _to IsDirectory(_retval); } \
  NS_IMETHOD IsFile(PRBool *_retval) { return _to IsFile(_retval); } \
  NS_IMETHOD Exists(PRBool *_retval) { return _to Exists(_retval); } \
  NS_IMETHOD IsHidden(PRBool *_retval) { return _to IsHidden(_retval); } \
  NS_IMETHOD Equals(nsIFileSpec *spec, PRBool *_retval) { return _to Equals(spec, _retval); } \
  NS_IMETHOD GetFileSize(PRUint32 *aFileSize) { return _to GetFileSize(aFileSize); } \
  NS_IMETHOD GetDiskSpaceAvailable(PRInt64 *aDiskSpaceAvailable) { return _to GetDiskSpaceAvailable(aDiskSpaceAvailable); } \
  NS_IMETHOD AppendRelativeUnixPath(const char *relativePath) { return _to AppendRelativeUnixPath(relativePath); } \
  NS_IMETHOD CreateDir(void) { return _to CreateDir(); } \
  NS_IMETHOD Touch(void) { return _to Touch(); } \
  NS_IMETHOD IsSymlink(PRBool *_retval) { return _to IsSymlink(_retval); } \
  NS_IMETHOD ResolveSymlink(void) { return _to ResolveSymlink(); } \
  NS_IMETHOD Delete(PRBool recursive) { return _to Delete(recursive); } \
  NS_IMETHOD Truncate(PRInt32 aNewLength) { return _to Truncate(aNewLength); } \
  NS_IMETHOD Rename(const char *newLeafName) { return _to Rename(newLeafName); } \
  NS_IMETHOD CopyToDir(const nsIFileSpec *newParentDir) { return _to CopyToDir(newParentDir); } \
  NS_IMETHOD MoveToDir(const nsIFileSpec *newParentDir) { return _to MoveToDir(newParentDir); } \
  NS_IMETHOD Execute(const char *args) { return _to Execute(args); } \
  NS_IMETHOD OpenStreamForReading(void) { return _to OpenStreamForReading(); } \
  NS_IMETHOD OpenStreamForWriting(void) { return _to OpenStreamForWriting(); } \
  NS_IMETHOD OpenStreamForReadingAndWriting(void) { return _to OpenStreamForReadingAndWriting(); } \
  NS_IMETHOD CloseStream(void) { return _to CloseStream(); } \
  NS_IMETHOD IsStreamOpen(PRBool *_retval) { return _to IsStreamOpen(_retval); } \
  NS_IMETHOD Eof(PRBool *_retval) { return _to Eof(_retval); } \
  NS_IMETHOD Read(char **buffer, PRInt32 requestedCount, PRInt32 *_retval) { return _to Read(buffer, requestedCount, _retval); } \
  NS_IMETHOD ReadLine(char **line, PRInt32 bufferSize, PRBool *wasTruncated) { return _to ReadLine(line, bufferSize, wasTruncated); } \
  NS_IMETHOD Write(const char *data, PRInt32 requestedCount, PRInt32 *_retval) { return _to Write(data, requestedCount, _retval); } \
  NS_IMETHOD Flush(void) { return _to Flush(); } \
  NS_IMETHOD Seek(PRInt32 offset) { return _to Seek(offset); } \
  NS_IMETHOD Tell(PRInt32 *_retval) { return _to Tell(_retval); } \
  NS_IMETHOD EndLine(void) { return _to EndLine(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIFILESPEC(_to) \
  NS_IMETHOD FromFileSpec(const nsIFileSpec *original) { return !_to ? NS_ERROR_NULL_POINTER : _to->FromFileSpec(original); } \
  NS_IMETHOD GetURLString(char * *aURLString) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetURLString(aURLString); } \
  NS_IMETHOD SetURLString(const char * aURLString) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetURLString(aURLString); } \
  NS_IMETHOD GetUnixStyleFilePath(char * *aUnixStyleFilePath) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUnixStyleFilePath(aUnixStyleFilePath); } \
  NS_IMETHOD SetUnixStyleFilePath(const char * aUnixStyleFilePath) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetUnixStyleFilePath(aUnixStyleFilePath); } \
  NS_IMETHOD GetPersistentDescriptorString(char * *aPersistentDescriptorString) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPersistentDescriptorString(aPersistentDescriptorString); } \
  NS_IMETHOD SetPersistentDescriptorString(const char * aPersistentDescriptorString) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetPersistentDescriptorString(aPersistentDescriptorString); } \
  NS_IMETHOD GetNativePath(char * *aNativePath) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNativePath(aNativePath); } \
  NS_IMETHOD SetNativePath(const char * aNativePath) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetNativePath(aNativePath); } \
  NS_IMETHOD GetNSPRPath(char * *aNSPRPath) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNSPRPath(aNSPRPath); } \
  NS_IMETHOD Error(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Error(); } \
  NS_IMETHOD IsValid(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsValid(_retval); } \
  NS_IMETHOD Failed(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Failed(_retval); } \
  NS_IMETHOD GetLeafName(char * *aLeafName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLeafName(aLeafName); } \
  NS_IMETHOD SetLeafName(const char * aLeafName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLeafName(aLeafName); } \
  NS_IMETHOD GetParent(nsIFileSpec * *aParent) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetParent(aParent); } \
  NS_IMETHOD GetInputStream(nsIInputStream * *aInputStream) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInputStream(aInputStream); } \
  NS_IMETHOD GetOutputStream(nsIOutputStream * *aOutputStream) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOutputStream(aOutputStream); } \
  NS_IMETHOD IsChildOf(nsIFileSpec *possibleParent, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsChildOf(possibleParent, _retval); } \
  NS_IMETHOD GetFileSpec(nsFileSpec *aFileSpec) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFileSpec(aFileSpec); } \
  NS_IMETHOD SetFromFileSpec(const nsFileSpec & spec) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFromFileSpec(spec); } \
  NS_IMETHOD GetFileContents(char * *aFileContents) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFileContents(aFileContents); } \
  NS_IMETHOD SetFileContents(const char * aFileContents) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFileContents(aFileContents); } \
  NS_IMETHOD MakeUnique(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->MakeUnique(); } \
  NS_IMETHOD MakeUniqueWithSuggestedName(const char *suggestedName) { return !_to ? NS_ERROR_NULL_POINTER : _to->MakeUniqueWithSuggestedName(suggestedName); } \
  NS_IMETHOD GetModDate(PRUint32 *aModDate) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetModDate(aModDate); } \
  NS_IMETHOD ModDateChanged(PRUint32 oldStamp, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->ModDateChanged(oldStamp, _retval); } \
  NS_IMETHOD IsDirectory(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsDirectory(_retval); } \
  NS_IMETHOD IsFile(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsFile(_retval); } \
  NS_IMETHOD Exists(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Exists(_retval); } \
  NS_IMETHOD IsHidden(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsHidden(_retval); } \
  NS_IMETHOD Equals(nsIFileSpec *spec, PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Equals(spec, _retval); } \
  NS_IMETHOD GetFileSize(PRUint32 *aFileSize) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFileSize(aFileSize); } \
  NS_IMETHOD GetDiskSpaceAvailable(PRInt64 *aDiskSpaceAvailable) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDiskSpaceAvailable(aDiskSpaceAvailable); } \
  NS_IMETHOD AppendRelativeUnixPath(const char *relativePath) { return !_to ? NS_ERROR_NULL_POINTER : _to->AppendRelativeUnixPath(relativePath); } \
  NS_IMETHOD CreateDir(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->CreateDir(); } \
  NS_IMETHOD Touch(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Touch(); } \
  NS_IMETHOD IsSymlink(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsSymlink(_retval); } \
  NS_IMETHOD ResolveSymlink(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ResolveSymlink(); } \
  NS_IMETHOD Delete(PRBool recursive) { return !_to ? NS_ERROR_NULL_POINTER : _to->Delete(recursive); } \
  NS_IMETHOD Truncate(PRInt32 aNewLength) { return !_to ? NS_ERROR_NULL_POINTER : _to->Truncate(aNewLength); } \
  NS_IMETHOD Rename(const char *newLeafName) { return !_to ? NS_ERROR_NULL_POINTER : _to->Rename(newLeafName); } \
  NS_IMETHOD CopyToDir(const nsIFileSpec *newParentDir) { return !_to ? NS_ERROR_NULL_POINTER : _to->CopyToDir(newParentDir); } \
  NS_IMETHOD MoveToDir(const nsIFileSpec *newParentDir) { return !_to ? NS_ERROR_NULL_POINTER : _to->MoveToDir(newParentDir); } \
  NS_IMETHOD Execute(const char *args) { return !_to ? NS_ERROR_NULL_POINTER : _to->Execute(args); } \
  NS_IMETHOD OpenStreamForReading(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->OpenStreamForReading(); } \
  NS_IMETHOD OpenStreamForWriting(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->OpenStreamForWriting(); } \
  NS_IMETHOD OpenStreamForReadingAndWriting(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->OpenStreamForReadingAndWriting(); } \
  NS_IMETHOD CloseStream(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->CloseStream(); } \
  NS_IMETHOD IsStreamOpen(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsStreamOpen(_retval); } \
  NS_IMETHOD Eof(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Eof(_retval); } \
  NS_IMETHOD Read(char **buffer, PRInt32 requestedCount, PRInt32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Read(buffer, requestedCount, _retval); } \
  NS_IMETHOD ReadLine(char **line, PRInt32 bufferSize, PRBool *wasTruncated) { return !_to ? NS_ERROR_NULL_POINTER : _to->ReadLine(line, bufferSize, wasTruncated); } \
  NS_IMETHOD Write(const char *data, PRInt32 requestedCount, PRInt32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Write(data, requestedCount, _retval); } \
  NS_IMETHOD Flush(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Flush(); } \
  NS_IMETHOD Seek(PRInt32 offset) { return !_to ? NS_ERROR_NULL_POINTER : _to->Seek(offset); } \
  NS_IMETHOD Tell(PRInt32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Tell(_retval); } \
  NS_IMETHOD EndLine(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->EndLine(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsFileSpec : public nsIFileSpec
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIFILESPEC

  nsFileSpec();
  virtual ~nsFileSpec();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsFileSpec, nsIFileSpec)

nsFileSpec::nsFileSpec()
{
  /* member initializers and constructor code */
}

nsFileSpec::~nsFileSpec()
{
  /* destructor code */
}

/* void fromFileSpec ([const] in nsIFileSpec original); */
NS_IMETHODIMP nsFileSpec::FromFileSpec(const nsIFileSpec *original)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute string URLString; */
NS_IMETHODIMP nsFileSpec::GetURLString(char * *aURLString)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsFileSpec::SetURLString(const char * aURLString)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute string unixStyleFilePath; */
NS_IMETHODIMP nsFileSpec::GetUnixStyleFilePath(char * *aUnixStyleFilePath)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsFileSpec::SetUnixStyleFilePath(const char * aUnixStyleFilePath)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute string persistentDescriptorString; */
NS_IMETHODIMP nsFileSpec::GetPersistentDescriptorString(char * *aPersistentDescriptorString)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsFileSpec::SetPersistentDescriptorString(const char * aPersistentDescriptorString)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute string nativePath; */
NS_IMETHODIMP nsFileSpec::GetNativePath(char * *aNativePath)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsFileSpec::SetNativePath(const char * aNativePath)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute string NSPRPath; */
NS_IMETHODIMP nsFileSpec::GetNSPRPath(char * *aNSPRPath)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void error (); */
NS_IMETHODIMP nsFileSpec::Error()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isValid (); */
NS_IMETHODIMP nsFileSpec::IsValid(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean failed (); */
NS_IMETHODIMP nsFileSpec::Failed(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute string leafName; */
NS_IMETHODIMP nsFileSpec::GetLeafName(char * *aLeafName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsFileSpec::SetLeafName(const char * aLeafName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIFileSpec parent; */
NS_IMETHODIMP nsFileSpec::GetParent(nsIFileSpec * *aParent)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIInputStream inputStream; */
NS_IMETHODIMP nsFileSpec::GetInputStream(nsIInputStream * *aInputStream)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIOutputStream outputStream; */
NS_IMETHODIMP nsFileSpec::GetOutputStream(nsIOutputStream * *aOutputStream)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isChildOf (in nsIFileSpec possibleParent); */
NS_IMETHODIMP nsFileSpec::IsChildOf(nsIFileSpec *possibleParent, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] readonly attribute nsFileSpec fileSpec; */
NS_IMETHODIMP nsFileSpec::GetFileSpec(nsFileSpec *aFileSpec)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* [noscript] void setFromFileSpec ([const] in nsFileSpecRef spec); */
NS_IMETHODIMP nsFileSpec::SetFromFileSpec(const nsFileSpec & spec)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute string fileContents; */
NS_IMETHODIMP nsFileSpec::GetFileContents(char * *aFileContents)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsFileSpec::SetFileContents(const char * aFileContents)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void makeUnique (); */
NS_IMETHODIMP nsFileSpec::MakeUnique()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void makeUniqueWithSuggestedName (in string suggestedName); */
NS_IMETHODIMP nsFileSpec::MakeUniqueWithSuggestedName(const char *suggestedName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute unsigned long modDate; */
NS_IMETHODIMP nsFileSpec::GetModDate(PRUint32 *aModDate)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean modDateChanged (in unsigned long oldStamp); */
NS_IMETHODIMP nsFileSpec::ModDateChanged(PRUint32 oldStamp, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isDirectory (); */
NS_IMETHODIMP nsFileSpec::IsDirectory(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isFile (); */
NS_IMETHODIMP nsFileSpec::IsFile(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean exists (); */
NS_IMETHODIMP nsFileSpec::Exists(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isHidden (); */
NS_IMETHODIMP nsFileSpec::IsHidden(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean equals (in nsIFileSpec spec); */
NS_IMETHODIMP nsFileSpec::Equals(nsIFileSpec *spec, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute unsigned long fileSize; */
NS_IMETHODIMP nsFileSpec::GetFileSize(PRUint32 *aFileSize)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute long long diskSpaceAvailable; */
NS_IMETHODIMP nsFileSpec::GetDiskSpaceAvailable(PRInt64 *aDiskSpaceAvailable)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void appendRelativeUnixPath (in string relativePath); */
NS_IMETHODIMP nsFileSpec::AppendRelativeUnixPath(const char *relativePath)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void createDir (); */
NS_IMETHODIMP nsFileSpec::CreateDir()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void touch (); */
NS_IMETHODIMP nsFileSpec::Touch()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isSymlink (); */
NS_IMETHODIMP nsFileSpec::IsSymlink(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void resolveSymlink (); */
NS_IMETHODIMP nsFileSpec::ResolveSymlink()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void delete (in boolean recursive); */
NS_IMETHODIMP nsFileSpec::Delete(PRBool recursive)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void truncate (in long aNewLength); */
NS_IMETHODIMP nsFileSpec::Truncate(PRInt32 aNewLength)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void rename ([const] in string newLeafName); */
NS_IMETHODIMP nsFileSpec::Rename(const char *newLeafName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void copyToDir ([const] in nsIFileSpec newParentDir); */
NS_IMETHODIMP nsFileSpec::CopyToDir(const nsIFileSpec *newParentDir)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void moveToDir ([const] in nsIFileSpec newParentDir); */
NS_IMETHODIMP nsFileSpec::MoveToDir(const nsIFileSpec *newParentDir)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void execute ([const] in string args); */
NS_IMETHODIMP nsFileSpec::Execute(const char *args)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void openStreamForReading (); */
NS_IMETHODIMP nsFileSpec::OpenStreamForReading()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void openStreamForWriting (); */
NS_IMETHODIMP nsFileSpec::OpenStreamForWriting()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void openStreamForReadingAndWriting (); */
NS_IMETHODIMP nsFileSpec::OpenStreamForReadingAndWriting()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void closeStream (); */
NS_IMETHODIMP nsFileSpec::CloseStream()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isStreamOpen (); */
NS_IMETHODIMP nsFileSpec::IsStreamOpen(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean eof (); */
NS_IMETHODIMP nsFileSpec::Eof(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long read (inout string buffer, in long requestedCount); */
NS_IMETHODIMP nsFileSpec::Read(char **buffer, PRInt32 requestedCount, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void readLine (inout string line, in long bufferSize, out boolean wasTruncated); */
NS_IMETHODIMP nsFileSpec::ReadLine(char **line, PRInt32 bufferSize, PRBool *wasTruncated)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long write (in string data, in long requestedCount); */
NS_IMETHODIMP nsFileSpec::Write(const char *data, PRInt32 requestedCount, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void flush (); */
NS_IMETHODIMP nsFileSpec::Flush()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void seek (in long offset); */
NS_IMETHODIMP nsFileSpec::Seek(PRInt32 offset)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long tell (); */
NS_IMETHODIMP nsFileSpec::Tell(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void endLine (); */
NS_IMETHODIMP nsFileSpec::EndLine()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

// {a3020981-2018-11d3-915f-a957795b7ebc}
#define NS_DIRECTORYITERATOR_CID \
{ 0xa3020981, 0x2018, 0x11d3, { 0x91, 0x5f, 0xa9, 0x57, 0x79, 0x5b, 0x7e, 0xbc } }
#define NS_DIRECTORYITERATOR_CONTRACTID "@mozilla.org/directoryiterator;1"
#define NS_DIRECTORYITERATOR_CLASSNAME "nsIDirectoryIterator"

/* starting interface:    nsIDirectoryIterator */
#define NS_IDIRECTORYITERATOR_IID_STR "d8c0a083-0868-11d3-915f-d9d889d48e3c"

#define NS_IDIRECTORYITERATOR_IID \
  {0xd8c0a083, 0x0868, 0x11d3, \
    { 0x91, 0x5f, 0xd9, 0xd8, 0x89, 0xd4, 0x8e, 0x3c }}

class NS_NO_VTABLE nsIDirectoryIterator : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IDIRECTORYITERATOR_IID)

  /* void init (in nsIFileSpec parent, in boolean resolveSymlink); */
  NS_IMETHOD Init(nsIFileSpec *parent, PRBool resolveSymlink) = 0;

  /* boolean exists (); */
  NS_IMETHOD Exists(PRBool *_retval) = 0;

  /* void next (); */
  NS_IMETHOD Next(void) = 0;

  /* readonly attribute nsIFileSpec currentSpec; */
  NS_IMETHOD GetCurrentSpec(nsIFileSpec * *aCurrentSpec) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDIRECTORYITERATOR \
  NS_IMETHOD Init(nsIFileSpec *parent, PRBool resolveSymlink); \
  NS_IMETHOD Exists(PRBool *_retval); \
  NS_IMETHOD Next(void); \
  NS_IMETHOD GetCurrentSpec(nsIFileSpec * *aCurrentSpec); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDIRECTORYITERATOR(_to) \
  NS_IMETHOD Init(nsIFileSpec *parent, PRBool resolveSymlink) { return _to Init(parent, resolveSymlink); } \
  NS_IMETHOD Exists(PRBool *_retval) { return _to Exists(_retval); } \
  NS_IMETHOD Next(void) { return _to Next(); } \
  NS_IMETHOD GetCurrentSpec(nsIFileSpec * *aCurrentSpec) { return _to GetCurrentSpec(aCurrentSpec); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDIRECTORYITERATOR(_to) \
  NS_IMETHOD Init(nsIFileSpec *parent, PRBool resolveSymlink) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(parent, resolveSymlink); } \
  NS_IMETHOD Exists(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Exists(_retval); } \
  NS_IMETHOD Next(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Next(); } \
  NS_IMETHOD GetCurrentSpec(nsIFileSpec * *aCurrentSpec) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCurrentSpec(aCurrentSpec); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDirectoryIterator : public nsIDirectoryIterator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDIRECTORYITERATOR

  nsDirectoryIterator();
  virtual ~nsDirectoryIterator();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDirectoryIterator, nsIDirectoryIterator)

nsDirectoryIterator::nsDirectoryIterator()
{
  /* member initializers and constructor code */
}

nsDirectoryIterator::~nsDirectoryIterator()
{
  /* destructor code */
}

/* void init (in nsIFileSpec parent, in boolean resolveSymlink); */
NS_IMETHODIMP nsDirectoryIterator::Init(nsIFileSpec *parent, PRBool resolveSymlink)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean exists (); */
NS_IMETHODIMP nsDirectoryIterator::Exists(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void next (); */
NS_IMETHODIMP nsDirectoryIterator::Next()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIFileSpec currentSpec; */
NS_IMETHODIMP nsDirectoryIterator::GetCurrentSpec(nsIFileSpec * *aCurrentSpec)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

// Factory methods if you link with xpcom
NS_COM nsresult NS_NewFileSpecWithSpec(const nsFileSpec& aSrcFileSpec, nsIFileSpec **result);
NS_COM nsresult NS_NewFileSpec(nsIFileSpec** result);
NS_COM nsresult NS_NewDirectoryIterator(nsIDirectoryIterator** result);
// Convert from nsIFile to nsIFileSpec
//
// XXX This function is here only to assist with the migration from nsIFileSpec
// to nsIFile.  This function will dissappear in future mozilla releases.
//
// ...ripped from nsPrefService.cpp:
//
//   "So discouraged is the use of nsIFileSpec, nobody wanted to have this routine be
//    public - It might lead to continued use of nsIFileSpec. Right now, [mozilla] has
//    such a need for it, here it is. Let's stop having to use it though."
//
NS_COM nsresult NS_NewFileSpecFromIFile(nsIFile *aFile, nsIFileSpec **result);
#define NS_BOOL_ACCESSOR(_method) { PRBool yes; return NS_SUCCEEDED(f->_method(&yes)) && yes; }
inline PRBool Exists(nsIFileSpec* f) NS_BOOL_ACCESSOR(Exists)
inline PRBool Exists(nsIDirectoryIterator* f) NS_BOOL_ACCESSOR(Exists)
inline PRBool IsDirectory(nsIFileSpec* f) NS_BOOL_ACCESSOR(IsDirectory)

#endif /* __gen_nsIFileSpec_h__ */
