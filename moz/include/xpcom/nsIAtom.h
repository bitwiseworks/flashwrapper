/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM G:/Mozilla/Tree/mozilla/xpcom/ds/nsIAtom.idl
 */

#ifndef __gen_nsIAtom_h__
#define __gen_nsIAtom_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
#include "nsAString.h"
#include "nsCOMPtr.h"

/* starting interface:    nsIAtom */
#define NS_IATOM_IID_STR "3d1b15b0-93b4-11d1-895b-006008911b81"

#define NS_IATOM_IID \
  {0x3d1b15b0, 0x93b4, 0x11d1, \
    { 0x89, 0x5b, 0x00, 0x60, 0x08, 0x91, 0x1b, 0x81 }}

class NS_NO_VTABLE nsIAtom : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_IATOM_IID)

  /**
   * Translate the unicode string into the stringbuf.
   */
  /* [noscript] AString toString (); */
  NS_IMETHOD ToString(nsAString & _retval) = 0;

  /**
   * Return a pointer to a zero terminated unicode string.
   */
  /* void GetUnicode ([shared, retval] out wstring aResult); */
  NS_IMETHOD GetUnicode(const PRUnichar **aResult) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIATOM \
  NS_IMETHOD ToString(nsAString & _retval); \
  NS_IMETHOD GetUnicode(const PRUnichar **aResult); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIATOM(_to) \
  NS_IMETHOD ToString(nsAString & _retval) { return _to ToString(_retval); } \
  NS_IMETHOD GetUnicode(const PRUnichar **aResult) { return _to GetUnicode(aResult); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIATOM(_to) \
  NS_IMETHOD ToString(nsAString & _retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->ToString(_retval); } \
  NS_IMETHOD GetUnicode(const PRUnichar **aResult) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUnicode(aResult); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAtom : public nsIAtom
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIATOM

  nsAtom();
  virtual ~nsAtom();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAtom, nsIAtom)

nsAtom::nsAtom()
{
  /* member initializers and constructor code */
}

nsAtom::~nsAtom()
{
  /* destructor code */
}

/* [noscript] AString toString (); */
NS_IMETHODIMP nsAtom::ToString(nsAString & _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetUnicode ([shared, retval] out wstring aResult); */
NS_IMETHODIMP nsAtom::GetUnicode(const PRUnichar **aResult)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif

/*
 * The three forms of NS_NewAtom and do_GetAtom (for use with
 * |nsCOMPtr<nsIAtom>|) return the atom for the string given.  At any
 * given time there will always be one atom representing a given string.
 * Atoms are intended to make string comparison cheaper by simplifying
 * it to pointer equality.  A pointer to the atom that does not own a
 * reference is not guaranteed to be valid.
 *
 * The three forms of NS_NewPermanentAtom and do_GetPermanentAtom return
 * the atom for the given string and ensure that the atom is permanent.
 * An atom that is permanent will exist (occupy space at a specific
 * location in memory) until XPCOM is shut down.  The advantage of
 * permanent atoms is that they do not need to maintain a reference
 * count, which requires locking and hurts performance.
 */
/**
 * Find an atom that matches the given ISO-Latin1 C string. The
 * C string is translated into its unicode equivalent.
 */
extern NS_COM nsIAtom* NS_NewAtom(const char* isolatin1);
extern NS_COM nsIAtom* NS_NewPermanentAtom(const char* isolatin1);
inline already_AddRefed<nsIAtom> do_GetAtom(const char* isolatin1)
    { return NS_NewAtom(isolatin1); }
inline already_AddRefed<nsIAtom> do_GetPermanentAtom(const char* isolatin1)
    { return NS_NewPermanentAtom(isolatin1); }
/**
 * Find an atom that matches the given unicode string. The string is assumed
 * to be zero terminated.
 */
extern NS_COM nsIAtom* NS_NewAtom(const PRUnichar* unicode);
extern NS_COM nsIAtom* NS_NewPermanentAtom(const PRUnichar* unicode);
inline already_AddRefed<nsIAtom> do_GetAtom(const PRUnichar* unicode)
    { return NS_NewAtom(unicode); }
inline already_AddRefed<nsIAtom> do_GetPermanentAtom(const PRUnichar* unicode)
    { return NS_NewPermanentAtom(unicode); }
/**
 * Find an atom that matches the given string.
 */
extern NS_COM nsIAtom* NS_NewAtom(const nsAString& aString);
extern NS_COM nsIAtom* NS_NewPermanentAtom(const nsAString& aString);
inline already_AddRefed<nsIAtom> do_GetAtom(const nsAString& aString)
    { return NS_NewAtom(aString); }
inline already_AddRefed<nsIAtom> do_GetPermanentAtom(const nsAString& aString)
    { return NS_NewPermanentAtom(aString); }
/**
 * Return a count of the total number of atoms currently
 * alive in the system.
 */
extern NS_COM nsrefcnt NS_GetNumberOfAtoms(void);

#endif /* __gen_nsIAtom_h__ */
