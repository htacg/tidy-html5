@echo off

REM alltest1.cmd - execute all test cases
REM
REM (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
REM See tidy.c for the copyright notice.
REM
REM <URL:http://tidy.sourceforge.net/>
REM
REM    $Author: arnaud02 $
REM    $Date: 2006/12/28 10:01:44 $
REM    $Revision: 1.1 $

@if "%1." == "." goto USE
@if "%2." == "." goto USE

REM check for input file
@if NOT EXIST testcases.txt goto Err0
@if NOT EXIST onetest.cmd goto Err3
@if NOT EXIST input\nul goto Err4

REM set the runtime exe file
set TIDY=%1
@if NOT EXIST %TIDY% goto ERR1

REM set the OUTPUT folder
set TIDYOUT=%2
@if EXIST %TIDYOUT%\nul goto GOTDIR
@echo Folder '%TIDYOUT%' does not exist ... it will be created? ... Ctrl+C to EXIT!
@pause
@md %TIDYOUT%
@if NOT EXIST %TIDYOUT%\nul goto Err2
:GOTDIR
@set ERRTESTS=
for /F "tokens=1*" %%i in (testcases.txt) do call onetest.cmd %%i %%j
@if "%ERRTESTS%." == "." goto END
@echo ERROR TESTS [%ERRTESTS%] ...
goto END

:ERR0
echo	ERROR: Can not locate 'testcases.txt' ... check name, and location ...
goto END
:ERR1
echo	ERROR: Can not locate %TIDY% ... check name, and location ...
goto END
:ERR2
echo	ERROR: Can not create %TIDYOUT% folder ... check name, and location ...
goto END
:ERR3
echo	ERROR: Can not locate 'onetest.cmd' ... check name, and location ...
goto END
:ERR4
echo	ERROR: Can not locate 'input' folder ... check name, and location ...
goto END

:USE
@echo	Usage of ALLTEST1.CMD .........................................
@echo	AllTest1 tidy.exe Out_Folder
@echo	tidy.exe - This is the Tidy.exe you want to use for the test.
@echo	Out_Folder  - This is the FOLDER where you want the results put.
@echo	This folder will be created if it does not already exist.
@echo	==================================
@echo	ALLTEST1.CMD will run a battery of test files in the input folder
@echo	Each test name, has an expected result, given in testcases.txt
@echo	There will be a warning if any test file fails to give this result.
@echo	==================================
@echo	But the main purpose is to compare the 'results' of two version of
@echo	any two Tidy runtime exe's. Thus after you have two sets of results,
@echo	in separate folders, the idea is to compare these two folders.
@echo	Any directory compare utility will do, or you can download, and use
@echo	a WIN32 port of GNU diff.exe from http://unxutils.sourceforge.net/
@echo	................................................................
@goto END

:END
