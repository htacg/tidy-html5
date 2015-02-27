@setlocal

@set TMPEXE=..\..\build\cmake\Release\tidy5.exe
@if NOT EXIST %TMPEXE% goto NOEXE
@set TMPINP=temphtml5.cfg
@if NOT EXIST %TMPINP% goto NOINP
@set TMPDIR=tempout
@if NOT EXIST %TMPDIR%\nul goto NODIR
@if "%~1x" == "x" goto HELP
@if NOT EXIST %1 goto NOFIL

@set TMPOUT=%TMPDIR%\%~nx1
@%TMPEXE% -config %TMPINP% -o %TMPOUT% %1
@if ERRORLEVEL 1 goto FAILED
@echo Output to %TMPOUT%
@goto END

:FAILED
@echo The test of %1 FAILED!
@echo Output to %TMPOUT%
@pause

@goto END

:NOEXE
@echo Can NOT locate EXE %TMPEXE%! *** FIX ME ***
@goto END

:NOINP
@echo Can NOT locate config %TMPINP%! *** FIX ME ***
@goto END

:NODIR
@echo Can NOT locate output directory %TMPDIR%! *** FIX ME ***
@goto END

:NOFIL
@echo Can NOT locate input file %1
:HELP
@echo Give the name of a HTML5 file to tidy
:END
