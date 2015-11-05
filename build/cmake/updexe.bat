@setlocal
@REM copy the EXE into C:\MDOS, IFF changed
@set TMPDIR=C:\MDOS
@set TMPFIL1=tidy.exe
@set TMPFIL2=tidy32.exe
@set TMPSRC=Release\%TMPFIL1%
@if NOT EXIST %TMPSRC% goto ERR1
@echo Current source %TMPSRC%
@call dirmin %TMPSRC%

@if NOT EXIST %TMPDIR%\nul goto ERR2
@set TMPDST=%TMPDIR%\%TMPFIL2%
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
@goto END

:NOFC4
@echo Can NOT run fc4! so doing copy...
:DOCOPY
copy %TMPSRC% %TMPDST%
@if NOT EXIST %TMPDST% goto ERR3
@call dirmin %TMPDST%
@echo Done file update...
@goto END

:ERR1
@echo Source %TMPSRC% does NOT exist! Has it been built? *** FIX ME ***
@goto ISERR

:ERR2
@echo Destination %TMPDIR% does NOT exist!
@goto ISERR

:ERR3
@echo Copy of %TMPSRC% to %TMPDST% FAILED!
@goto ISERR

:ISERR
@endlocal
@exit /b 1

:END
@endlocal
@exit /b 0

@REM eof

