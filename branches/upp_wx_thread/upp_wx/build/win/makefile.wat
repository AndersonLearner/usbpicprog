# =========================================================================
#     This makefile was generated by
#     Bakefile 0.2.5 (http://www.bakefile.org)
#     Do not modify, all changes will be overwritten!
# =========================================================================



# -------------------------------------------------------------------------
# These are configurable options:
# -------------------------------------------------------------------------

# C++ compiler 
CXX = wpp386

# Standard flags for C++ 
CXXFLAGS = 

# Standard preprocessor flags (common for CC and CXX) 
CPPFLAGS = 

# Standard linker flags 
LDFLAGS = 

# Use DLL build of wx library? [0,1]
#   0 - Static
#   1 - DLL
WX_SHARED = 0

# Use Unicode build of wxWidgets? [0,1]
#   0 - ANSI
#   1 - Unicode
WX_UNICODE = 0

# Use debug build of wxWidgets (define __WXDEBUG__)? [0,1]
#   0 - Release
#   1 - Debug
WX_DEBUG = 1

# Version of the wx library to build against. 
WX_VERSION = 28

# Use monolithic build of wxWidgets? [0,1]
#   0 - Multilib
#   1 - Monolithic
WX_MONOLITHIC = 0

# The directory where wxWidgets library is installed 
WX_DIR = $(%WXWIN)

# The directory where libusb library is installed 
LIBUSB_DIR = $(LIBUSB)



# -------------------------------------------------------------------------
# Do not modify the rest of this file!
# -------------------------------------------------------------------------

# Speed up compilation a bit:
!ifdef __LOADDLL__
!  loaddll wcc      wccd
!  loaddll wccaxp   wccdaxp
!  loaddll wcc386   wccd386
!  loaddll wpp      wppdi86
!  loaddll wppaxp   wppdaxp
!  loaddll wpp386   wppd386
!  loaddll wlink    wlink
!  loaddll wlib     wlibd
!endif

# We need these variables in some bakefile-made rules:
WATCOM_CWD = $+ $(%cdrive):$(%cwd) $-

### Conditionally set variables: ###

WX3RDPARTYLIBPOSTFIX =
!ifeq WX_DEBUG 1
WX3RDPARTYLIBPOSTFIX = d
!endif
_BUILDDIR_SHARED_SUFFIX =
!ifeq WX_SHARED 0
_BUILDDIR_SHARED_SUFFIX = 
!endif
!ifeq WX_SHARED 1
_BUILDDIR_SHARED_SUFFIX = _dll
!endif
____WX_SHARED_0_p =
!ifeq WX_SHARED 0
____WX_SHARED_0_p = 
!endif
!ifeq WX_SHARED 1
____WX_SHARED_0_p = -dWXUSINGDLL
!endif
__WXUNICODE_DEFINE_p =
!ifeq WX_UNICODE 1
__WXUNICODE_DEFINE_p = -d_UNICODE
!endif
__WXDEBUG_DEFINE_p =
!ifeq WX_DEBUG 1
__WXDEBUG_DEFINE_p = -d__WXDEBUG__
!endif
____upp_wx__OPT_2 =
!ifeq WX_DEBUG 0
____upp_wx__OPT_2 = -ot -ox
!endif
!ifeq WX_DEBUG 1
____upp_wx__OPT_2 = -od
!endif
____upp_wx__DEBUGINFO_3 =
!ifeq WX_DEBUG 0
____upp_wx__DEBUGINFO_3 = -d0
!endif
!ifeq WX_DEBUG 1
____upp_wx__DEBUGINFO_3 = -d2
!endif
____upp_wx__DEBUGINFO_4 =
!ifeq WX_DEBUG 0
____upp_wx__DEBUGINFO_4 = 
!endif
!ifeq WX_DEBUG 1
____upp_wx__DEBUGINFO_4 = debug all
!endif
__WXLIB_ADV_NAME_p =
!ifeq WX_MONOLITHIC 0
__WXLIB_ADV_NAME_p = wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_adv.lib
!endif
__WXLIB_CORE_NAME_p =
!ifeq WX_MONOLITHIC 0
__WXLIB_CORE_NAME_p = wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_core.lib
!endif
__WXLIB_BASE_NAME_p =
!ifeq WX_MONOLITHIC 0
__WXLIB_BASE_NAME_p = wxbase$(WX_VERSION)$(WXLIBPOSTFIX).lib
!endif
!ifeq WX_MONOLITHIC 1
__WXLIB_BASE_NAME_p = wxmsw$(WX_VERSION)$(WXLIBPOSTFIX).lib
!endif
WXLIBPOSTFIX =
!ifeq WX_DEBUG 0
!ifeq WX_UNICODE 1
WXLIBPOSTFIX = u
!endif
!endif
!ifeq WX_DEBUG 1
!ifeq WX_UNICODE 0
WXLIBPOSTFIX = d
!endif
!endif
!ifeq WX_DEBUG 1
!ifeq WX_UNICODE 1
WXLIBPOSTFIX = ud
!endif
!endif
WXLIBPATH =
!ifeq WX_SHARED 0
WXLIBPATH = \lib\wat_lib
!endif
!ifeq WX_SHARED 1
WXLIBPATH = \lib\wat_dll
!endif

### Variables: ###

UPP_WX_CXXFLAGS = $(____WX_SHARED_0_p) $(__WXUNICODE_DEFINE_p) &
	$(__WXDEBUG_DEFINE_p) -d__WXMSW__ &
	-i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include &
	$(____upp_wx__OPT_2) $(____upp_wx__DEBUGINFO_3) -i=..\..\src &
	-i=$(LIBUSB_DIR)\src $(CPPFLAGS) $(CXXFLAGS)
UPP_WX_OBJECTS =  &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_hardware.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_hexview.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_main.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_pictype.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_preferences.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_read_hexfile.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_uppmainwindow.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_uppmainwindow_callback.obj


all : watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)
watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX) :
	-if not exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX) mkdir watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)

### Targets: ###

all : .SYMBOLIC test_for_selected_wxbuild watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx.exe

clean : .SYMBOLIC 
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.obj del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.obj
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.res del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.res
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.lbc del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.lbc
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.ilk del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.ilk
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.pch del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.pch
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx.exe del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx.exe

test_for_selected_wxbuild :  
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo ----------------------------------------------------------------------------
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo The selected wxWidgets build is not available!
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo Please use the options prefixed with WX_ to select another wxWidgets build.
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo ----------------------------------------------------------------------------
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	exit 1

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx.exe :  $(UPP_WX_OBJECTS)
	@%create watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx.lbc
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx.lbc option quiet
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx.lbc name $^@
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx.lbc option caseexact
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx.lbc  libpath $(WX_DIR)$(WXLIBPATH) system nt_win ref '_WinMain@16' $(____upp_wx__DEBUGINFO_4) libpath $(LIBUSB_DIR)\lib\msvc $(LDFLAGS)
	@for %i in ($(UPP_WX_OBJECTS)) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx.lbc file %i
	@for %i in ( libusb.lib $(__WXLIB_ADV_NAME_p) $(__WXLIB_CORE_NAME_p) $(__WXLIB_BASE_NAME_p) wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx.lbc library %i
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx.lbc
	@for %i in () do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx.lbc option stack=%i
	wlink @watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx.lbc

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_hardware.obj :  .AUTODEPEND ..\..\src\hardware.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(UPP_WX_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_hexview.obj :  .AUTODEPEND ..\..\src\hexview.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(UPP_WX_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_main.obj :  .AUTODEPEND ..\..\src\main.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(UPP_WX_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_pictype.obj :  .AUTODEPEND ..\..\src\pictype.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(UPP_WX_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_preferences.obj :  .AUTODEPEND ..\..\src\preferences.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(UPP_WX_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_read_hexfile.obj :  .AUTODEPEND ..\..\src\read_hexfile.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(UPP_WX_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_uppmainwindow.obj :  .AUTODEPEND ..\..\src\uppmainwindow.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(UPP_WX_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\upp_wx_uppmainwindow_callback.obj :  .AUTODEPEND ..\..\src\uppmainwindow_callback.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(UPP_WX_CXXFLAGS) $<

