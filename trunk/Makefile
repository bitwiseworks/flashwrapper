#
# Setup config.
#
ODIN_INST       = e:\dev\oxp
MOZ_SDK         =.\moz\sdk
MOZ_DIST_INC    =.\moz\include

!if "$(BUILD_MODE)" == ""
BUILD_MODE = DEBUG
!endif

!if "$(BUILD_MODE)" == "RELEASE"
ALL_DEFINES     = -DNPODIN -D__WIN32OS2__ -D__i386__ -DORIGINAL_VAC_FUNCTIONS -D_NO_XPCOMDLL_ 
#-DEXPERIMENTAL
!else
ALL_DEFINES     = -DNPODIN -D__WIN32OS2__ -D__i386__ -DORIGINAL_VAC_FUNCTIONS -D_NO_XPCOMDLL_ -DDEBUG 
#-DEXPERIMENTAL
!endif

ALL_INCLUDES    = -I$(PATH_J2SE_ROOT)\include -I$(PATH_VAC365)\include

INCL    = -I.\incl_vac \
                  -I$(MOZ_SDK)\xpcom\include \
                  -I$(MOZ_SDK)\nspr\include \
                  -I$(MOZ_SDK)\java\include \
                  -I$(MOZ_SDK)\plugin\include \
                  -I$(MOZ_SDK)\necko\include \
                  -I$(MOZ_SDK)\string\include \
                  -I$(MOZ_DIST_INC)\plugin \
                  -I$(MOZ_DIST_INC)\oji \
                  -I$(MOZ_DIST_INC)\caps \
                  -I$(MOZ_DIST_INC)\liveconnect \
                  -I.\moz\include\xpcom \
		  -I$(ODIN_INST)\include \
		  -I$(ODIN_INST)\include\win

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
CXX_DEFINES     = /Ge- -Su4 -Oq+ -O- /G4 -qtune=blend -DDO_DELETE
!else
CXX_DEFINES     = /Ge- -Su4 -DDO_DELETE /Ti+ #/Gh 
!endif

PATH_ROOT = ..\..\..

			
#
# Walk config.
#
POSTMAKEFILES_LIB   = np2ndary.mak npjni.mak npns4x.mak npxpcom.mak


#
# Target config.
#
TARGET_NAME     = NPFLOS2
TARGET_MODE     = DLL
EXT_OBJ = OBJ

LDTARGETFLAGS    = 

TARGET_OBJS     = \
	apis_mozilla.$(EXT_OBJ) \
	apis_odin.$(EXT_OBJ) \
	npflos2.$(EXT_OBJ) \
	odin_windowing.$(EXT_OBJ) \
	odin_windowing_os2.$(EXT_OBJ) \
	plugin_primary.$(EXT_OBJ) \
	plugin_Generic.$(EXT_OBJ) \
	plugin_GenericWeaks.$(EXT_OBJ) \
	util_asm.$(EXT_OBJ) \
	util_debug.$(EXT_OBJ) \
	vac_malloc.$(EXT_OBJ) \
	vac_odincrt.$(EXT_OBJ) \
        wrap_ns4x.$(EXT_OBJ) 
#       nsPluginWrapperModule.$(EXT_OBJ) \
#	wrap_XPCOM.$(EXT_OBJ) \
#	wrap_JNIEnv.$(EXT_OBJ) \

!if "$(BUILD_MODE)" == "RELEASE"
LDFLAGS          = /DLL /NOE /MAP:FULL /EXEPACK:2
!else
LDFLAGS          = /DLL /NOE /MAP:FULL /EXEPACK:2 /DEBUG 
TARGET_OBJS     = $(TARGET_OBJS) dbg_RegChecker.$(EXT_OBJ) dbg_VerifyExcptChain.$(EXT_OBJ) \
!endif

#
# Export the ipluginw sources to ipluginw\
#
#ipluginwexport:
#    .\PreProcess.cmd nsInnotekPluginWrapper.h         > ipluginw\nsInnotekPluginWrapper.h
#    .\PreProcess.cmd nsInnotekPluginWrapperModule.cpp > ipluginw\nsInnotekPluginWrapperModule.cpp
#    .\PreProcess.cmd wrap_XPCOM.cpp                   > ipluginw\wrap_XPCOM.cpp
#    .\PreProcess.cmd wrap_XPCOM_3rdparty.h            > ipluginw\wrap_XPCOM_3rdparty.h
#    .\PreProcess.cmd wrap_VFTs.h                      > ipluginw\wrap_VFTs.h
#    .\PreProcess.cmd util_debug.c                     > ipluginw\util_debug.c
#    .\PreProcess.cmd moz_IDs.cmd                      > ipluginw\moz_IDs.cmd
#    .\PreProcess.cmd moz_IDs_Generated.h              > ipluginw\moz_IDs_Generated.h
#    .\PreProcess.cmd moz_IDs_Input.lst                > ipluginw\moz_IDs_Input.lst

.c.obj:
	icc $(INCL) $(CFLAGS) $(DFLAGS) $(OFLAGS) -o $@ -c $<

.cpp.obj:
	icc $(INCL) $(CXX_DEFINES) $(DFLAGS) $(OFLAGS) $(ALL_DEFINES) -o $@ -c $<

.asm.obj:
	alp $<

.rc.res:
    rc -r $*.rc

all: $(BUILD_MODE)\$(TARGET_NAME).dll $(TARGET_NAME).res

$(BUILD_MODE)\$(TARGET_NAME).dll: $(TARGET_OBJS) $(TARGET_NAME).def $(TARGET_NAME).res
   ilink $(LDFLAGS) $(TARGET_OBJS) $(LIBS) security\securit2.lib $(TARGET_NAME).def -out:$@
   rc -n -p -x $(TARGET_NAME).res $@
