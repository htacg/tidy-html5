@setlocal
@set TMPPRJ=tidy5
@echo Build %TMPPRJ% project, in 64-bits
@set TMPLOG=bldlog-1.txt
@set BLDDIR=%CD%
@set SET_BAT=%ProgramFiles(x86)%\Microsoft Visual Studio 10.0\VC\vcvarsall.bat
@if NOT EXIST "%SET_BAT%" goto NOBAT

@echo Doing build output to %TMPLOG%
@echo Doing build output to %TMPLOG% > %TMPLOG%

@if /I "%PROCESSOR_ARCHITECTURE%" EQU "AMD64" (
@set TMPINST=..\..\..\3rdParty.x64
) ELSE (
 @if /I "%PROCESSOR_ARCHITECTURE%" EQU "x86_64" (
@set TMPINST=..\..\..\3rdParty.x64
 ) ELSE (
@set TMPINST=..\..\..\3rdParty
@echo WARNING: Appears 64-bit is NOT available
@echo Falling back to 32-bit build...
@pause
@goto DNARCH
 )
)

@echo Doing: 'call "%SET_BAT%" %PROCESSOR_ARCHITECTURE%'
@echo Doing: 'call "%SET_BAT%" %PROCESSOR_ARCHITECTURE%' >> %TMPLOG%
@call "%SET_BAT%" %PROCESSOR_ARCHITECTURE% >> %TMPLOG% 2>&1
@if ERRORLEVEL 1 goto ERR0
@REM call setupqt64
@cd %BLDDIR%

:DNARCH

@set TMPSRC=..\..
@REM ############################################
@REM NOTE: SPECIAL INSTALL LOCATION
@REM Adjust to suit your environment
@REM ##########################################
@REM set TMPINST=F:\Projects\software.x64
@set TMPOPTS=-DCMAKE_INSTALL_PREFIX=%TMPINST%
@set TMPOPTS=%TMPOPTS% -G "Visual Studio 10 Win64"
@REM Added to CMakeLists.txt set(CMAKE_DEBUG_POSTFIX d), and for each EXE

@call chkmsvc %TMPPRJ%

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
@echo.
@echo No INSTALL configured at this time
@goto END

@echo Note install location %TMPINST%
@echo *** CONTINUE with install? *** Only Ctrl+C aborts
@pause

@REM cmake -P cmake_install.cmake
@echo Doing: 'cmake --build . --config release --target INSTALL'
@echo Doing: 'cmake --build . --config release --target INSTALL' >> %TMPLOG%
@cmake --build . --config release --target INSTALL >> %TMPLOG% 2>&1

@fa4 " -- " %TMPLOG%

@echo Done build and install of %TMPPRJ%...

@goto END

:NOBAT
@echo Can NOT locate MSVC setup batch "%SET_BAT%"! *** FIX ME ***
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

:ISERR
@endlocal
@exit /b 1

:END
@endlocal
@exit /b 0

@REM eof
