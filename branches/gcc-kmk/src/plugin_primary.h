/* $Id: plugin_primary.h,v 1.2 2003/09/15 14:12:34 bird Exp $
 *
 * Include file for the Primary Plugin Wrapper.
 * This defines the external function(s) upon which plugin_primary.c depends.
 *
 * InnoTek Systemberatung GmbH confidential
 *
 * Copyright (c) 2003 InnoTek Systemberatung GmbH
 * Author: knut st. osmundsen <bird-srcspam@anduin.net>
 *
 * All Rights Reserved
 *
 */

#ifndef __plugin_primary_h__
#define __plugin_primary_h__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This function returns all the win32 dll names.
 *
 * Any version checking and such should be done when this function is called.
 *
 * @returns Success indicator.
 * @param   hmodWrapper         Wrapper DLL handle.
 * @param   pszPluginDllName    Buffer to store the DLL name.
 * @param   cchPluginDllName    Size of DLL name buffer.
 */
extern BOOL npprimaryGetPluginNames(HMODULE hmodWrapper, char *pszPluginDllName,
                                    int cchPluginDllName);

#if 0 // not currently used
/**
 * Checks the build number of the custombuild dll after the lazy init have
 * loaded it. Other checks can be performed as well.
 *
 * @returns TRUE if ok.
 * @returns FALSE if not ok and loading should be stopped.
 * @param   hmodOdin    Module handle of DosLoadModule'ed custombuild dll.
 */
extern BOOL npprimaryCheckBuildNumber(HMODULE hmodOdin);
#endif

/*
 * Drag in the right parts.
 */

#ifdef NPODIN_NS4X
extern int giNS4x;
static int *gOdinNS4x = &giNS4x;
#endif

#ifdef __cplusplus
}
#endif

#endif /* !__plugin_primary_h__ */
