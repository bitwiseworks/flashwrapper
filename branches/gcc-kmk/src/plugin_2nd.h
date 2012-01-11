/* $Id: plugin_2nd.h,v 1.2 2003/09/14 22:37:30 bird Exp $
 *
 * Include file for the Secondary Plugin Wrappers.
 * This defines the external function(s) upon which plugin_2nd.c depends.
 *
 * InnoTek Systemberatung GmbH confidential
 *
 * Copyright (c) 2003 InnoTek Systemberatung GmbH
 * Author: knut st. osmundsen <bird-srcspam@anduin.net>
 *
 * All Rights Reserved
 *
 */

#ifndef __plugin_2nd_h__
#define __plugin_2nd_h__

#ifdef __cplusplus
extern "C" {
#endif


/** This function returns all the dll names required by the wrapping.
 * @returns Success indicator.
 * @param   pszPluginDllName    Buffer to store the DLL name.
 * @param   cchPluginDllName    Size of DLL name buffer.
 * @param   pszPluginName       Buffer to store the short name in.
 * @param   cchPluginName       Size of short name buffer.
 * @param   pszWrapperDLL       Name (no path) of the primary wrapper dll.
 * @param   cchWrapperDLL       Size of the wrapper dll buffer.
 */
extern BOOL np2ndaryGetPluginNames(char *pszPluginDllName, int cchPluginDllName,
                                   char *pszWrapperDll, int cchWrapperDll);


#ifdef __cplusplus
}
#endif

#endif /* !__plugin_2nd_h__ */
