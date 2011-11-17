# Microsoft Developer Studio Project File - Name="tidylib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=tidylib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tidylib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tidylib.mak" CFG="tidylib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tidylib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "tidylib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tidylib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "../../include" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /D "SUPPORT_UTF16_ENCODINGS" /D "SUPPORT_ASIAN_ENCODINGS" /D "SUPPORT_ACCESSIBILITY_CHECKS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Release\libtidy.lib"

!ELSEIF  "$(CFG)" == "tidylib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /Za /W4 /Gm /ZI /Od /I "../../include" /D "_DEBUG" /D "_WIN32" /D "_LIB" /D "WIN32" /D "_MBCS" /D "SUPPORT_UTF16_ENCODINGS" /D "SUPPORT_ASIAN_ENCODINGS" /D "SUPPORT_ACCESSIBILITY_CHECKS" /U "WINDOWS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\libtidy.lib"

!ENDIF 

# Begin Target

# Name "tidylib - Win32 Release"
# Name "tidylib - Win32 Debug"
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

!IF  "$(CFG)" == "tidylib - Win32 Release"

!ELSEIF  "$(CFG)" == "tidylib - Win32 Debug"

# ADD CPP /Ze

!ENDIF 

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
