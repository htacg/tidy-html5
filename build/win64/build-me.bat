@setlocal
@REM 20170702 - Check branch
@set TMPBR=next
@REM 20161002 - Change to msvc140 build
@set VCVERS=14
@set GENERATOR=Visual Studio %VCVERS% Win64
@REM 20160324 - Change to relative, and use choice
@set TMPPRJ=tidy
@echo Build %TMPPRJ% project, in 64-bits
@set TMPLOG=bldlog-1.txt
@set BLDDIR=%CD%
@set TMPROOT=..\..\..
@set SET_BAT=%ProgramFiles(x86)%\Microsoft Visual Studio %VCVERS%.0\VC\vcvarsall.bat
@if NOT EXIST "%SET_BAT%" goto NOBAT
@REM if NOT EXIST %TMPROOT%\nul goto NOROOT
@set TMPSRC=..\..
@if NOT EXIST %TMPSRC%\CMakeLists.txt goto NOCM
@set DOPAUSE=1

@if /I "%PROCESSOR_ARCHITECTURE%" EQU "AMD64" (
@set TMPINST=%TMPROOT%\software.x64
) ELSE (
 @if /I "%PROCESSOR_ARCHITECTURE%" EQU "x86_64" (
@set TMPINST=%TMPROOT%\software.x64
 ) ELSE (
@echo ERROR: Appears 64-bit is NOT available... aborting...
@goto ISERR
 )
)
@if NOT EXIST %TMPINST%\nul goto NOINST

@echo Doing build output to %TMPLOG%
@echo Doing build output to %TMPLOG% > %TMPLOG%

@echo Doing: 'call "%SET_BAT%" %PROCESSOR_ARCHITECTURE%'
@echo Doing: 'call "%SET_BAT%" %PROCESSOR_ARCHITECTURE%' >> %TMPLOG%
@call "%SET_BAT%" %PROCESSOR_ARCHITECTURE% >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR0
@REM call setupqt64
@cd %BLDDIR%

@REM :DNARCH

@REM ############################################
@REM NOTE: SPECIAL INSTALL LOCATION
@REM Adjust to suit your environment
@REM ##########################################
@REM set TMPINST=F:\Projects\software.x64
@set TMPOPTS=-DCMAKE_INSTALL_PREFIX=%TMPINST%
@set TMPOPTS=%TMPOPTS% -G "%GENERATOR%"
@REM set TMPOPTS=%TMPOPTS% -DTIDY_CONFIG_FILE="C:\MDOS\tidy5.cfg"
@REM set TMPOPTS=%TMPOPTS% -DTIDY_USER_CONFIG_FILE="C:\MDOS\tidy5.cfg"
@set TMPOPTS=%TMPOPTS% -DBUILD_SHARED_LIB:BOOL=OFF

:RPT
@if "%~1x" == "x" goto GOTCMD
@if "%~1x" == "NOPAUSEx" (
    @set DOPAUSE=0
) else (
    @set TMPOPTS=%TMPOPTS% %1
)
@shift
@goto RPT
:GOTCMD

@call chkmsvc %TMPPRJ%
@call chkbranch %TMPBR%
@if ERRORLEVEL 1 goto BADBR
:GOTBR

@echo Begin %DATE% %TIME%, output to %TMPLOG%
@echo Begin %DATE% %TIME% >> %TMPLOG%

@echo Doing: 'cmake %TMPSRC% %TMPOPTS%'
@echo Doing: 'cmake %TMPSRC% %TMPOPTS%' >> %TMPLOG%
@cmake %TMPSRC% %TMPOPTS% >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR1

@echo Doing: 'cmake --build . --config debug'
@echo Doing: 'cmake --build . --config debug' >> %TMPLOG%
@cmake --build . --config debug >> %TMPLOG%
@if ERRORLEVEL 1 goto ERR2

@echo Doing: 'cmake --build . --config release'
@echo Doing: 'cmake --build . --config release' >> %TMPLOG%
@cmake --build . --config release >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR3
:DNREL

@echo Appears a successful build
@echo Note install location %TMPINST%
@echo.

@REM ##############################################
@REM Check if should continue with install
@REM ##############################################
@if "%DOPAUSE%x" == "0x" goto DOINST
@choice /? >nul 2>&1
@if ERRORLEVEL 1 goto NOCHOICE
@choice /D N /T 10 /M "Pausing for 10 seconds. Def=N"
@if ERRORLEVEL 2 goto GOTNO
@goto DOINST
:NOCHOICE
@echo Appears OS does not have the 'choice' command!
@ask *** CONTINUE with install? *** Only y continues
@if ERRORLEVEL 2 goto NOASK
@if ERRORLEVEL 1 goto DOINST
@echo Skipping install to %TMPINST% at this time...
@echo.
@goto END
:NOASK
@echo 'ask' utility not found in path...
@echo.
@echo *** CONTINUE with install? *** Only Ctrl+c aborts...
@echo.
@pause

:DOINST
@echo Proceeding with INSTALL...
@echo.
@REM cmake -P cmake_install.cmake
@echo Doing: 'cmake --build . --config debug --target INSTALL'
@echo Doing: 'cmake --build . --config debug --target INSTALL' >> %TMPLOG%
@cmake --build . --config debug --target INSTALL >> %TMPLOG% 2>&1

@echo Doing: 'cmake --build . --config release --target INSTALL'
@echo Doing: 'cmake --build . --config release --target INSTALL' >> %TMPLOG%
@cmake --build . --config release --target INSTALL >> %TMPLOG% 2>&1

@fa4 " -- " %TMPLOG%

@echo Done build and install of %TMPPRJ%...

@goto END

:GOTNO
@echo.
@echo No install at this time, but there may be an updexe.bat to copy the EXE to c:\MDOS...
@echo.
@goto END

:NOBAT
@echo Can NOT locate MSVC setup batch "%SET_BAT%"! *** FIX ME ***
@goto ISERR

@REM :NOROOT
@REM @echo Can NOT locate %TMPROOT%! *** FIX ME ***
@REM @goto ISERR

:NOCM
@echo Can NOT locate %TMPSRC%\CMakeLists.txt! *** FIX ME ***
@goto ISERR

:NOINST
@echo Can NOT locate directory %TMPINST%! *** FIX ME ***
@goto ISERR

:ERR0
@echo MSVC 10 setup error
@goto ISERR

:ERR1
@echo cmake config, generation error
@goto ISERR

:ERR2
@echo debug build error
@goto ISERR

:ERR3
@fa4 "mt.exe : general error c101008d:" %TMPLOG% >nul
@if ERRORLEVEL 1 goto ERR32
:ERR33
@echo release build error
@goto ISERR
:ERR32
@echo Stupid error... trying again...
@echo Doing: 'cmake --build . --config release'
@echo Doing: 'cmake --build . --config release' >> %TMPLOG%
@cmake --build . --config release >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR33
@goto DNREL

:BADBR
@call git checkout %TMPBR%
@call chkbranch %TMPBR%
@if ERRORLEVEL 1 goto BADBR2
@goto GOTBR
:BADBR2
@call shwbranch
@echo Not on correct branch %TMPBR%
@goto ISERR

:ISERR
@endlocal
@exit /b 1

:END
@endlocal
@exit /b 0

@REM eof
