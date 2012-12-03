/* $Id: moz_GCCDefines.h,v 1.1 2004/03/08 19:22:56 bird Exp $
 *
 * The stuff defined to build Mozilla stuff correctly on OS/2.
 * (Sure, it's all in and not all is needed, but who care?)
 *
 * Copyright (c) 2003 InnoTek Systemberatung GmbH
 * Copyright (c) 2012 bww bitwise works GmbH
 *
 * Authors: knut st. osmundsen <bird@anduin.net>
 *          Dmitriy Kuminov <dmik@dmik.org>
 *
 * All Rights Reserved
 *
 */
#ifndef __mozos2defs_h__
#define __mozos2defs_h__


/*******************************************************************************
*   Defined Constants And Macros                                               *
*******************************************************************************/
#undef unix
#undef __unix
#undef __unix__
#define OSTYPE "OS22"
#define OSARCH "OS2"
#define MOZILLA_CLIENT

//stuff
#define XPCOM_GLUE          1
#define MOZILLA_STRICT_API  1
#define NO_ANSI
#define XP_OS2_EMX          1
#define NSCAP_DISABLE_DEBUG_PTR_TYPES  1
//mozilla-config.h
#define _MOZILLA_CONFIG_H_
#define ACCESSIBILITY 1
#define DETECT_WEBSHELL_LEAKS 1
#define D_INO d_ino
#define HAVE_DIRENT_H 1
#define HAVE_GETOPT_H 1
#define HAVE_I18N_LC_MESSAGES 1
#define HAVE_INT16_T 1
#define HAVE_INT32_T 1
#define HAVE_INT64_T 1
#define HAVE_LIBDL 1
#define HAVE_LIBM 1
#define HAVE_LIBSOCKET 1
#define HAVE_LOCALTIME_R 1
#define HAVE_MALLOC_H 1
#define HAVE_MEMMOVE 1
#define HAVE_MEMORY_H 1
#define HAVE_MMINTRIN_H 1
#define HAVE_RANDOM 1
#define HAVE_RINT 1
#define HAVE_SNPRINTF 1
#define HAVE_STRERROR 1
#define HAVE_ST_BLKSIZE 1
#define HAVE_SYS_CDEFS_H 1
#define HAVE_SYS_STATFS_H 1
#define HAVE_UINT 1
#define HAVE_UINT16_T 1
#define HAVE_UNISTD_H 1
#define HAVE_VA_COPY 1
#define IBMBIDI 1
#define JS_THREADSAFE 1
#define MMAP_MISSES_WRITES 1
#define MOZILLA_VERSION "1.6a"
#define MOZ_DEFAULT_TOOLKIT "os2"
#define MOZ_DLL_SUFFIX ".dll"
#define MOZ_ENABLE_COREXFONTS 1
#define MOZ_JSLOADER 1
#define MOZ_LOGGING 1
#define MOZ_MATHML 1
#define MOZ_PROFILELOCKING 1
#define MOZ_PROFILESHARING 1
#define MOZ_REFLOW_PERF 1
#define MOZ_REFLOW_PERF_DSP 1
#define MOZ_USER_DIR "Mozilla"
#define MOZ_VIEW_SOURCE 1
#define MOZ_XPINSTALL 1
#define MOZ_XUL 1
#define NO_X11 1
#define NS_PRINTING 1
#define NS_PRINT_PREVIEW 1
#define OJI 1
#define OS2 1
#define OS2EMX_PLAIN_CHAR 1
#define STDC_HEADERS 1
#define TCPV40HDRS 1
#define VA_COPY va_copy
#define XP_OS2 1
#define XP_OS2_EMX 1
#define X_DISPLAY_MISSING 1

#endif
