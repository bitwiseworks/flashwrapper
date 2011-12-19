/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * The contents of this file are subject to the Netscape Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code is Mozilla Communicator client code,
 * released March 31, 1998.
 *
 * The Initial Developer of the Original Code is Netscape Communications
 * Corporation.  Portions created by Netscape are
 * Copyright (C) 1998-1999 Netscape Communications Corporation. All
 * Rights Reserved.
 *
 * Contributor(s):
 */

#ifndef nsDirectoryServiceUtils_h___
#define nsDirectoryServiceUtils_h___

#include "nsIServiceManager.h"
#include "nsIProperties.h"
#include "nsCOMPtr.h"

#define NS_DIRECTORY_SERVICE_CID  {0xf00152d0,0xb40b,0x11d3,{0x8c, 0x9c, 0x00, 0x00, 0x64, 0x65, 0x73, 0x74}}

inline nsresult
NS_GetSpecialDirectory(const char* specialDirName, nsIFile* *result)
{
    nsresult rv;
    static NS_DEFINE_CID(kDirectoryServiceCID, NS_DIRECTORY_SERVICE_CID);
    nsCOMPtr<nsIProperties> serv(do_GetService(kDirectoryServiceCID, &rv));
    if (NS_FAILED(rv)) return rv;

    nsCOMPtr<nsISupports> dir;
    rv = serv->Get(specialDirName, NS_GET_IID(nsIFile), getter_AddRefs(dir));
    if (NS_FAILED(rv)) return rv;

    *result = NS_STATIC_CAST(nsIFile*, NS_STATIC_CAST(nsISupports*, dir));
    if (*result)
        NS_ADDREF(*result);
    return NS_OK;
}

#endif
