/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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
 * The Original Code is Mozilla Communicator client code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
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

#ifndef nsPluginViewer_h__
#define nsPluginViewer_h__

#include "nsCOMPtr.h"
#include "nscore.h"
#include "nsCRT.h"
#include "nsIContentViewer.h"
#include "nsIContentViewerEdit.h"
#include "nsIWebBrowserPrint.h"
#include "nsIWidget.h"
#include "nsIPluginManager.h"
#include "nsIPluginViewer.h"

class nsIStreamListener;
class nsIContentViewer;
class pluginInstanceOwner;

class PluginViewerImpl : public nsIPluginViewer,
                         public nsIContentViewer,
                         public nsIContentViewerEdit,
                         public nsIWebBrowserPrint
{
public:
  PluginViewerImpl(const char* aCommand);
  nsresult Init(nsIStreamListener** aDocListener);
    
  NS_DECL_AND_IMPL_ZEROING_OPERATOR_NEW

  // nsISupports
  NS_DECL_ISUPPORTS

  // nsIPluginViewer
  NS_IMETHOD StartLoad(nsIRequest* request, nsIStreamListener*& aResult);

  // nsIContentViewer
  NS_DECL_NSICONTENTVIEWER

  // nsIContentViewerEdit
  NS_DECL_NSICONTENTVIEWEREDIT

  // nsIWebBrowserPrint
  NS_DECL_NSIWEBBROWSERPRINT

#ifdef XP_WIN
  NS_IMETHOD GetPluginPort(HWND *aPort);
#endif

  virtual ~PluginViewerImpl();

  nsresult CreatePlugin(nsIRequest* request, nsIPluginHost* aHost, const nsRect& aBounds,
                        nsIStreamListener*& aResult);

  nsresult MakeWindow(nsNativeWidget aParent,
                      nsIDeviceContext* aDeviceContext,
                      const nsRect& aBounds);

  void ForceRefresh(void);

  nsresult GetURI(nsIURI* *aURI);

  nsresult GetDocument(nsIDocument* *aDocument);

  nsIWidget* mWindow;
  nsIDocument* mDocument;
  nsCOMPtr<nsISupports> mContainer;
  nsIChannel* mChannel;
  pluginInstanceOwner *mOwner;
  PRBool mEnableRendering;

};

extern nsresult
NS_NewPluginContentViewer(const char* aCommand,
                          nsIStreamListener** aDocListener,
                          nsIContentViewer** aDocViewer);


#endif // nsPluginViewer_h__

