## @file
# Local Project Configuration File (Template)
#
# The local project configuration file is used to specify local paths to
# external tools and libraries and also to optioanlly override the global
# project configuration options.
#
# NOTES:
#
#   This file is a template! Copy it to a file named LocalConfig.kmk in 
#   the same directory and modify the copy to fit your local environment.
#
#   All paths in this file are specified using forward slashes unless specified
#   otherwise.
#

#
# Base directory where all build output will go. The directory will be created
# if does not exist. The default is "out" in the root of the source tree.
#
# PATH_OUT_BASE := out

#
# Path to Odin SDK. If not set, it is assumed that it is accessible through the
# environment. Optionally, a path to the library directory is given (defaults
# to $(PATH_SDK_ODIN)/lib).
#
# PATH_SDK_ODIN := D:/Coding/odin/odin32
# PATH_SDK_ODIN_BIN := D:/Coding/odin/odin32-build/os2.x86/release/stage/bin
# PATH_SDK_ODIN_LIB := D:/Coding/odin/odin32-build/os2.x86/release/stage/lib

#
# Path to the OS/2 Toolkit versoin 4.x. If not set, it is assumed that the
# toolkit is accessible through the environment.
#
# PATH_SDK_OS2TK4 := D:/Dev/OS2TK45

#
# Path to the IBM Assembly Language Processor (may be found in the
# OS/2 toolkit). Defaults to '$(PATH_SDK_OS2TK4)/bin/alp.exe' if
# PATH_SDK_OS2TK4 is set, or to 'alp.exe' otherwise.
#
# PATH_TOOL_ALP := alp.exe

#
# Path to the Unix cp utility. Used to copy files for install packages
# instead of the kmk version due bugs in processing of the '-p' option.
# Defaults to 'cp'.
#
# CP := cp
