/* $Id: moz_VACDefines.h,v 1.1.1.1 2003/09/13 01:30:16 bird Exp $
 *
 * The stuff defined to build Mozilla stuff correctly on OS/2.
 * (Sure, it's all in and not all is needed, but who care?)
 *
 * InnoTek Systemberatung GmbH confidential
 *
 * Copyright (c) 2003 InnoTek Systemberatung GmbH
 * Author: knut st. osmundsen <bird@anduin.net>
 *
 * All Rights Reserved
 *
 */
#ifndef __mozos2defs_h__
#define __mozos2defs_h__


/*******************************************************************************
*   Defined Constants And Macros                                               *
*******************************************************************************/
#define XPCOM_GLUE          1
#define MOZILLA_STRICT_API  1
#define NO_ANSI
#define XP_OS2_VACPP        1
#define NSCAP_DISABLE_DEBUG_PTR_TYPES  1
#define STDC_HEADERS        1
#define D_INO               d_ino
#define mode_t              int
#define off_t              long
#define pid_t              int
#define size_t              unsigned
#define uid_t              int
#define gid_t              int
#define __size_t              1
#define __off_t              1
#define HAVE_CPP_2BYTE_WCHAR_T              1
#define HAVE_WCRTOMB              1
#define HAVE_MBRTOWC              1
#define HAVE_MEMORY_H              1
#define HAVE_NL_TYPES_H              1
#define NEW_H              <new.h>
#define HAVE_LIBM              1
#define NO_X11              1
#define MMAP_MISSES_WRITES              1
#define HAVE_STRERROR              1
#define HAVE_MEMMOVE              1
#define HAVE_NL_LANGINFO              1
#define HAVE_IOS_BINARY              1
#define HAVE_IOS_BIN              1
#define NEED_CPP_UNUSED_IMPLEMENTATIONS              1
#define HAVE_CPP_TROUBLE_COMPARING_TO_ZERO              1
#define HAVE_I18N_LC_MESSAGES              1
#define MOZ_DEFAULT_TOOLKIT              "os2"
#define MOZ_ENABLE_COREXFONTS              1
#define IBMBIDI              1
#define ACCESSIBILITY              1
#define MOZ_MATHML              1
#define MOZ_LOGGING              1
#define DETECT_WEBSHELL_LEAKS              1
#define MOZ_USER_DIR              ".mozilla"
#define NSCAP_DONT_PROVIDE_NONCONST_OPEQ              1
#define CPP_THROW_NEW
#define MOZ_XUL              1
#define INCLUDE_XUL              1
#define NS_MT_SUPPORTED              1
#define MOZ_DLL_SUFFIX              ".dll"
#define XP_PC              1
#define XP_OS2              1
#define JS_THREADSAFE              1
#define NS_PRINT_PREVIEW              1
#define NS_PRINTING              1
#define MOZ_REFLOW_PERF              1
#define MOZ_REFLOW_PERF_DSP              1
#define MOZILLA_VERSION              "1.3b"
#define _MOZILLA_CONFIG_H_
#define MOZILLA_CLIENT


#endif
