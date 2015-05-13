@setlocal
@echo off

@REM xmltest.cmd - execute all XML test cases
@REM
@REM (c) 1998-2003 (W3C) MIT, ERCIM, Keio University
@REM See tidy.c for the copyright notice.
@REM
@REM <URL:http://www.html-tidy.org/>
@REM
@set TIDY=..\build\cmake\Release\tidy5.exe
@if NOT EXIST %TIDY% goto NOEXE
@if NOT EXIST xmlcases.txt goto NOXML
@REM set OUTPUT folder
@set TIDYOUT=tmp
@if EXIST %TIDYOUT%\nul goto DOTEST
@md tmp
:DOTEST
@set TMPTEST=temptest.txt
@if EXIST %TMPTEST% @del %TMPTEST%
@echo Commencing xml tests from xmlcases.txt

@for /F "tokens=1*" %%i in (xmlcases.txt) do @(call onetest.cmd %%i %%j)

@echo Full output written to %TMPTEST%

@goto END

:NOXML
@echo Error: Can NOT locate xmlcases.txt! *** FIX ME ***
@goto END

:NOEXE
@echo Can NOT locate %TIDY% executable! *** FIX ME ***
@goto END

:END
