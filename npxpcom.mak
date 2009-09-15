#/* $Id: npxpcom.mak,v 1.2 2003/09/15 17:40:00 bird Exp $ */

#
# Mozilla plugin wrapper for Java2
#


#
# Setup config.
#
BUILD_PLATFORM = OS2
BUILD_MODE = RELEASE
BUILD_ENV_FORCE = VAC365
BUILD_ENV	 = VAC365
MOZ_SDK         =.\moz\sdk
MOZ_DIST_INC    =.\moz\include
ALL_DEFINES     = -DNPODIN
ALL_INCLUDES    = -I$(PATH_J2SE_ROOT)\include -I$(PATH_VAC365)\include
CXX_INCLUDES    = -I.\incl_vac \
                  -I$(MOZ_SDK)\xpcom\include \
                  -I$(MOZ_SDK)\nspr\include \
                  -I$(MOZ_SDK)\java\include \
                  -I$(MOZ_SDK)\java\include \
                  -I.\moz\include\xpcom
# Odin tradition, no exceptions.				
CXX_NO_XCPT     = 1

#
# Must *never* use debug mem stuff as we get a bunch of debug_mem* and debug_str*
# stuff with that which isn't wrapped yet. (look for __DEBUG_ALLOC__ in string.h)
#
ALL_NO_DBGMEM   = 1

#
# Hack allert
#
!if "$(BUILD_MODE)" == "RELEASE"
CXX_DEFINES     = -Su4 -Oq+ -O- /G4 -qtune=blend -DDO_DELETE
!else
CXX_DEFINES     = -Su4 -DDO_DELETE #/Gh
!endif

PATH_ROOT = ..\..\..
!include $(PATH_ROOT)\make\setup.mak


#
# Target config.
#
TARGET_NAME     = npxpcom
TARGET_MODE     = LIB
TARGET_PUBLIC   = 1
MAKEFILE		= npxpcom.mak

TARGET_OBJS     = \
$(PATH_TARGET)\wrap_xpcom.$(EXT_OBJ) \
#$(PATH_TARGET)\npjni.$(EXT_OBJ) \
#$(PATH_TARGET)\npjniwrappers.$(EXT_OBJ) \


#
# Rules config.
#
!include $(MAKE_INCLUDE_PROCESS)
