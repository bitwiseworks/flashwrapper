#
# (c) 2010 Mensys BV
# npflos2 - Flash plugin wrapper
#
# Setup config.
#
# Create Makefile.inc using Makefile.in_ as template.
#
!include Makefile.inc

!if "$(BUILD_MODE)" == ""
BUILD_MODE = release
!else
BUILD_MODE = debug
!endif

OBJDIR = ..\obj\$(BUILD_MODE)
BINDIR = ..\bin\$(BUILD_MODE)

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
INCL            = -I..\include\incl_vac \
                  -I..\include\include\plugin \
                  -I..\include\sdk\nspr\include \
                  -I$(ODIN_INST)\include \
                  -I$(ODIN_INST)\include\win

#
# Flags
#
!if "$(BUILD_MODE)" == "release"
CFLAGS          = -Ge- -Gm+ -Su4 -O+
CXXFLAGS        = -Ge- -Gm+ -Su4 -O+
ALL_DEFINES     = -DNPODIN -D__WIN32OS2__ -D__i386__ -DORIGINAL_VAC_FUNCTIONS
#-DEXPERIMENTAL
LDFLAGS         = /DLL /NOE /MAP:$(BINDIR)\$(TARGET_NAME).map /EXEPACK:2
!else
CFLAGS          = -Ge- -Gm+ -Su4 -O- -Ti+
CXXFLAGS        = -Ge- -Gm+ -Su4 -O- -Ti+
ALL_DEFINES     = -DNPODIN -D__WIN32OS2__ -D__i386__ -DORIGINAL_VAC_FUNCTIONS -DDEBUG
#-DEXPERIMENTAL
LDFLAGS         = /DLL /NOE /MAP:$(BINDIR)\$(TARGET_NAME).map /EXEPACK:2 /DEBUG 
!endif
		
#
# Target config.
#
TARGET_NAME     = npflos2
TARGET_MODE     = dll
EXT_OBJ         = obj

TARGET_OBJS     = \
    $(OBJDIR)\apis_mozilla.$(EXT_OBJ) \
    $(OBJDIR)\apis_odin.$(EXT_OBJ) \
    $(OBJDIR)\npflos2.$(EXT_OBJ) \
    $(OBJDIR)\odin_windowing.$(EXT_OBJ) \
    $(OBJDIR)\odin_windowing_os2.$(EXT_OBJ) \
    $(OBJDIR)\plugin_Generic.$(EXT_OBJ) \
    $(OBJDIR)\plugin_GenericWeaks.$(EXT_OBJ) \
    $(OBJDIR)\plugin_primary.$(EXT_OBJ) \
    $(OBJDIR)\util_asm.$(EXT_OBJ) \
    $(OBJDIR)\util_debug.$(EXT_OBJ) \
    $(OBJDIR)\vac_malloc.$(EXT_OBJ) \
    $(OBJDIR)\vac_odincrt.$(EXT_OBJ) \
    $(OBJDIR)\wrap_ns4x.$(EXT_OBJ) 

!if "$(BUILD_MODE)" == "debug"
TARGET_OBJS     = $(TARGET_OBJS) \
    $(OBJDIR)\dbg_RegChecker.$(EXT_OBJ) \
    $(OBJDIR)\dbg_VerifyExcptChain.$(EXT_OBJ)
!endif

.c{$(OBJDIR)}.obj:
	icc /Q $(INCL) $(CFLAGS) $(ALL_DEFINES) -Fo$* -c $<

.cpp{$(OBJDIR)}.obj:
	icc /Q $(INCL) $(CXXFLAGS) $(ALL_DEFINES) -Fo$* -c $<

.asm{$(OBJDIR)}.obj:
	alp -Mb -Fdi:$(TOOLKIT)\INC -Fdo:$(OBJDIR) $<

.rc{$(OBJDIR)}.res:
    rc -n -r -I . $< $@

all: \
    outtree \
    $(BINDIR)\$(TARGET_NAME).dll \
    $(OBJDIR)\$(TARGET_NAME).res

outtree:
    @if not exist ..\bin mkdir ..\bin
    @if not exist $(BINDIR) mkdir $(BINDIR)
    @if not exist ..\obj mkdir ..\obj
    @if not exist $(OBJDIR) mkdir $(OBJDIR)

# update bldlevel info
$(OBJDIR)\$(TARGET_NAME).res: Makefile.inc npflos2.rc
	@echo Writing build level informations
	@copy npflos2.rc $(OBJDIR)\npflos2-bld.rc
	@BldLevelInf0.cmd $(VERSION) $(BUILD) $(OBJDIR)\npflos2-bld.rc
        rc -n -r -I . -I $(OBJDIR) npflos2.rc $@

$(BINDIR)\$(TARGET_NAME).dll: \
    $(TARGET_OBJS) \
    $(TARGET_NAME).def \
    $(OBJDIR)\$(TARGET_NAME).res
    ilink $(LDFLAGS) $(TARGET_OBJS) $(LIBS) security\securit2.lib $(TARGET_NAME).def -out:$@
    rc -n -p -x2 $(OBJDIR)\$(TARGET_NAME).res $@

clean:
    -rm -f $(BINDIR)\*
    -rmdir $(BINDIR)
    -rmdir ..\bin
    -rm -f $(OBJDIR)\*
    -rmdir $(OBJDIR)
    -rmdir ..\obj
