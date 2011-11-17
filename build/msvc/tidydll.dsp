# Microsoft Developer Studio Project File - Name="tidydll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=tidydll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tidydll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tidydll.mak" CFG="tidydll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tidydll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "tidydll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tidydll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "tidydll___Win32_Release"
# PROP BASE Intermediate_Dir "tidydll___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseDLL"
# PROP Intermediate_Dir "ReleaseDLL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TIDYDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TIDYDLL_EXPORTS" /D SUPPORT_UTF16_ENCODINGS=1 /D SUPPORT_ASIAN_ENCODINGS=1 /D SUPPORT_ACCESSIBILITY_CHECKS=1 /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"ReleaseDLL/libtidy.dll"

!ELSEIF  "$(CFG)" == "tidydll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "tidydll___Win32_Debug"
# PROP BASE Intermediate_Dir "tidydll___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugDLL"
# PROP Intermediate_Dir "DebugDLL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TIDYDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /ZI /Od /I "..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D SUPPORT_UTF16_ENCODINGS=1 /D SUPPORT_ASIAN_ENCODINGS=1 /D SUPPORT_ACCESSIBILITY_CHECKS=1 /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"DebugDLL/libtidy.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "tidydll - Win32 Release"
# Name "tidydll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\src\access.c
# End Source File
# Begin Source File

SOURCE=..\..\src\alloc.c
# End Source File
# Begin Source File

SOURCE=..\..\src\attrask.c
# End Source File
# Begin Source File

SOURCE=..\..\src\attrdict.c
# End Source File
# Begin Source File

SOURCE=..\..\src\attrget.c
# End Source File
# Begin Source File

SOURCE=..\..\src\attrs.c
# End Source File
# Begin Source File

SOURCE=..\..\src\buffio.c
# End Source File
# Begin Source File

SOURCE=..\..\src\clean.c
# End Source File
# Begin Source File

SOURCE=..\..\src\config.c
# End Source File
# Begin Source File

SOURCE=..\..\src\entities.c
# End Source File
# Begin Source File

SOURCE=..\..\src\fileio.c
# End Source File
# Begin Source File

SOURCE=..\..\src\istack.c
# End Source File
# Begin Source File

SOURCE=..\..\src\lexer.c
# End Source File
# Begin Source File

SOURCE=..\..\src\localize.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mappedio.c
# End Source File
# Begin Source File

SOURCE=..\..\src\parser.c
# End Source File
# Begin Source File

SOURCE=..\..\src\pprint.c
# End Source File
# Begin Source File

SOURCE=..\..\src\streamio.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tagask.c
# End Source File
# Begin Source File

SOURCE=.\tidy.def
# End Source File
# Begin Source File

SOURCE=..\..\src\tags.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tidylib.c
# End Source File
# Begin Source File

SOURCE=..\..\src\tmbstr.c
# End Source File
# Begin Source File

SOURCE=..\..\src\utf8.c
# End Source File
# Begin Source File

SOURCE=..\..\src\win32tc.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\src\access.h
# End Source File
# Begin Source File

SOURCE=..\..\src\attrdict.h
# End Source File
# Begin Source File

SOURCE=..\..\src\attrs.h
# End Source File
# Begin Source File

SOURCE=..\..\include\buffio.h
# End Source File
# Begin Source File

SOURCE=..\..\src\clean.h
# End Source File
# Begin Source File

SOURCE=..\..\src\config.h
# End Source File
# Begin Source File

SOURCE=..\..\src\entities.h
# End Source File
# Begin Source File

SOURCE=..\..\src\fileio.h
# End Source File
# Begin Source File

SOURCE=..\..\src\forward.h
# End Source File
# Begin Source File

SOURCE=..\..\src\lexer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\mappedio.h
# End Source File
# Begin Source File

SOURCE=..\..\src\message.h
# End Source File
# Begin Source File

SOURCE=..\..\src\parser.h
# End Source File
# Begin Source File

SOURCE=..\..\include\platform.h
# End Source File
# Begin Source File

SOURCE=..\..\src\pprint.h
# End Source File
# Begin Source File

SOURCE=..\..\src\streamio.h
# End Source File
# Begin Source File

SOURCE=..\..\src\tags.h
# End Source File
# Begin Source File

SOURCE="..\..\src\tidy-int.h"
# End Source File
# Begin Source File

SOURCE=..\..\include\tidy.h
# End Source File
# Begin Source File

SOURCE=..\..\include\tidyenum.h
# End Source File
# Begin Source File

SOURCE=..\..\src\tmbstr.h
# End Source File
# Begin Source File

SOURCE=..\..\src\utf8.h
# End Source File
# Begin Source File

SOURCE=..\..\src\version.h
# End Source File
# Begin Source File

SOURCE=..\..\src\win32tc.h
# End Source File
# End Group
# End Target
# End Project
