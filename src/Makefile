#
# Setup config.
#
ODIN_INST       = F:\rd\Odin\svn\trunk
TOOLKIT         = F:\dev\toolkit452

!if "$(BUILD_MODE)" == ""
#BUILD_MODE = DEBUG
BUILD_MODE = RELEASE
!endif

# Odin tradition, no exceptions.				
CXX_NO_XCPT     = 1

#
# Must *never* use debug mem stuff as we get a bunch of debug_mem* and debug_str*
# stuff with that which isn't wrapped yet. (look for __DEBUG_ALLOC__ in string.h)
#
ALL_NO_DBGMEM   = 1

#
# Includes
#
INCL            = -I.\include\vacpp \
                  -I.\moz\include\plugin \
                  -I.\moz\sdk\nspr\include \
                  -I$(ODIN_INST)\include \
                  -I$(ODIN_INST)\include\win

#
# Flags
#
!if "$(BUILD_MODE)" == "RELEASE"
CFLAGS          = -Ge- -Gm+ -Su4 -O+
CXXFLAGS        = -Ge- -Gm+ -Su4 -O+
ALL_DEFINES     = -DNPODIN -D__WIN32OS2__ -D__i386__ -DORIGINAL_VAC_FUNCTIONS
#-DEXPERIMENTAL
LDFLAGS         = /DLL /NOE /MAP:FULL /EXEPACK:2
!else
CFLAGS          = -Ge- -Gm+ -Su4 -O- -Ti+
CXXFLAGS        = -Ge- -Gm+ -Su4 -O- -Ti+
ALL_DEFINES     = -DNPODIN -D__WIN32OS2__ -D__i386__ -DORIGINAL_VAC_FUNCTIONS -DDEBUG
#-DEXPERIMENTAL
LDFLAGS         = /DLL /NOE /MAP:FULL /EXEPACK:2 /DEBUG 
TARGET_OBJS     = $(TARGET_OBJS) dbg_RegChecker.$(EXT_OBJ) dbg_VerifyExcptChain.$(EXT_OBJ)
!endif
		
#
# Target config.
#
TARGET_NAME     = NPFLOS2
TARGET_MODE     = DLL
EXT_OBJ         = OBJ

TARGET_OBJS     = \
    apis_mozilla.$(EXT_OBJ) \
    apis_odin.$(EXT_OBJ) \
    npflos2.$(EXT_OBJ) \
    odin_windowing.$(EXT_OBJ) \
    odin_windowing_os2.$(EXT_OBJ) \
    plugin_Generic.$(EXT_OBJ) \
    plugin_GenericWeaks.$(EXT_OBJ) \
    plugin_primary.$(EXT_OBJ) \
    util_asm.$(EXT_OBJ) \
    util_debug.$(EXT_OBJ) \
    vac_malloc.$(EXT_OBJ) \
    vac_odincrt.$(EXT_OBJ) \
    wrap_ns4x.$(EXT_OBJ) 

.c.obj:
	icc /Q $(INCL) $(CFLAGS) $(ALL_DEFINES) -o $@ -c $<

.cpp.obj:
	icc /Q $(INCL) $(CXXFLAGS) $(ALL_DEFINES) -o $@ -c $<

.asm.obj:
	alp -Mb -Fdi:$(TOOLKIT)\INC $<

.rc.res:
    rc -n -r -I . $*.rc

all: \
    $(BUILD_MODE)\$(TARGET_NAME).dll \
    $(TARGET_NAME).res

$(BUILD_MODE)\$(TARGET_NAME).dll: \
    $(TARGET_OBJS) \
    $(TARGET_NAME).def \
    $(TARGET_NAME).res
    ilink $(LDFLAGS) $(TARGET_OBJS) $(LIBS) security\securit2.lib $(TARGET_NAME).def -out:$@
    rc -n -p -x2 $(TARGET_NAME).res $@

clean:
    rm -f $(BUILD_MODE)\$(TARGET_NAME).dll 
    rm -f $(TARGET_NAME).res
    rm -f $(TARGET_NAME).map
    rm -f *.obj
