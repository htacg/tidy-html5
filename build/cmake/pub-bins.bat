@setlocal
@set TMPWV=win32
@set TMPSRC=../..
@set TMPNAME=tidy

@set TMPFIL=%TMPSRC%\version.txt
@if NOT EXIST %TMPFIL% goto NOFIL
@set /p TMPVER=<%TMPFIL%
@set DOPAUSE=pause
@echo Version %TMPVER%

if "%1x" == "NOPAUSEx" (
    set DOPAUSE=echo No pause requested...
)

@set TMPBIN=F:\Projects\tidy-bins
@set TMPBINS=%TMPBIN%\binaries
@if NOT EXIST %TMPBINS%\nul goto NOBIN
@set TMPDD=%TMPBINS%\tidy-%TMPVER%
@if EXIST %TMPDD%\nul goto GOTDST
@echo.
@echo This is a NEW installation in %TMPDD%
:GOTDST

@set TMPFIL1=%TMPNAME%-%TMPVER%-%TMPWV%.exe
@set TMPFIL2=%TMPNAME%-%TMPVER%-%TMPWV%.msi
@set TMPFIL3=%TMPNAME%-%TMPVER%-%TMPWV%.zip
@if NOT EXIST %TMPFIL1% goto NOFIL1
@if NOT EXIST %TMPFIL2% goto NOFIL2
@if NOT EXIST %TMPFIL3% goto NOFIL3
@echo.
@echo Will publish...
@echo %TMPFIL1%
@echo %TMPFIL2%
@echo %TMPFIL3%
@echo.
@echo *** CONTINUE?%
@%DOPAUSE%

@if NOT EXIST %TMPDD%\nul (
@md %TMPDD%
@if NOT EXIST %TMPDD%\nul goto NODST
)

@set TMPSRC=%TMPFIL1%
@set TMPDST=%TMPDD%\%TMPFIL1%
@call :CHKCOPY
@set TMPSRC=%TMPFIL2%
@set TMPDST=%TMPDD%\%TMPFIL2%
@call :CHKCOPY
@set TMPSRC=%TMPFIL3%
@set TMPDST=%TMPDD%\%TMPFIL3%
@call :CHKCOPY

@echo.
@echo Maybe time to run 'gentidyyml %TMPBIN%'
@echo.

@goto END

:CHKCOPY

@if NOT EXIST %TMPDST% goto DOCOPY

@echo Current destination %TMPDST%
@call dirmin %TMPDST%

@REM Compare
@fc4 -q -v0 -b %TMPSRC% %TMPDST% >nul
@if ERRORLEVEL 2 goto NOFC4
@if ERRORLEVEL 1 goto DOCOPY
@echo.
@echo Files are the SAME... Nothing done...
@echo.
@goto :EOF

:NOFC4
@echo Can NOT run fc4! so doing copy...
:DOCOPY
copy %TMPSRC% %TMPDST%
@if NOT EXIST %TMPDST% goto ERR3
@call dirmin %TMPDST%
@echo.
@echo Done file update...
@echo.
@goto :EOF

:NODST
@echo Error: Unable to create %TMPDD%
@goto END

:NOFIL1
@echo Can NOT locate %TMPFIL1%! *** FIX ME ***
@goto CHKBB

:NOFIL2
@echo Can NOT locate %TMPFIL2%! *** FIX ME ***
@goto CHKBB

:NOFIL3
@echo Can NOT locate %TMPFIL3%! *** FIX ME ***
@goto CHKBB

:CHKBB
@echo.
@echo Have you run build-bins.bat?
@echo.
@goto END


:NOFIL
@echo Can NOT locate %TMPFIL%! *** FIX ME ***
@goto END

:NOBIN
@echo Can NOT locate %TMPBINS%! *** FIX ME ***
@goto END

:END

@REM eof
