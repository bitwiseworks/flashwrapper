/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: NPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998-2000
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

/* describes principals by their orginating URIs */

#ifndef _NS_CODEBASE_PRINCIPAL_H_
#define _NS_CODEBASE_PRINCIPAL_H_

#include "jsapi.h"
#include "nsBasePrincipal.h"
#include "nsICodebasePrincipal.h"
#include "nsIURI.h"
#include "nsCOMPtr.h"

#define NS_CODEBASEPRINCIPAL_CID \
{ 0x7ee2a400, 0x0b91, 0xaad3, \
{ 0xba, 0x18, 0xd7, 0x60, 0xb0, 0xf1, 0x99, 0xa2 }}

class nsCodebasePrincipal : public nsBasePrincipal, public nsICodebasePrincipal {
public:
    
    NS_DEFINE_STATIC_CID_ACCESSOR(NS_CODEBASEPRINCIPAL_CID)
        
    NS_DECL_ISUPPORTS
    NS_DECL_NSISERIALIZABLE
    NS_DECL_NSICODEBASEPRINCIPAL
    
    NS_IMETHOD ToString(char **result);

    NS_IMETHOD ToUserVisibleString(char **result);
    
    NS_IMETHOD GetPreferences(char** aPrefName, char** aID, 
                              char** aGrantedList, char** aDeniedList);
    
    NS_IMETHOD Equals(nsIPrincipal *other, PRBool *result);

    NS_IMETHOD HashValue(PRUint32 *result);

    NS_IMETHOD CanEnableCapability(const char *capability, PRInt16 *result);

    nsCodebasePrincipal();
    
    nsresult
    Init(nsIURI *uri);

    nsresult
    InitFromPersistent(const char* aPrefName, const char* aID, 
                       const char* aGrantedList, const char* aDeniedList,
                       PRBool aTrusted);

    virtual ~nsCodebasePrincipal(void);
    
protected:
    nsCOMPtr<nsIURI> mURI;
    PRBool mTrusted;
};

#endif // _NS_CODEBASE_PRINCIPAL_H_
