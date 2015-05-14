@setlocal
@echo off

REM alltest2.bat - execute all test cases
REM

@if "%1." == "." goto USE
@if "%2." == "." goto USE

REM check for input file
@if NOT EXIST testcases.txt goto Err0
@if NOT EXIST onetest2.bat goto Err3
@if NOT EXIST input\nul goto Err4
@if NOT EXIST testbase\nul goto Err5
@diff --version >nul
@if ERRORLEVEL 1 goto Err6

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
@set TMPTEST=temptest.txt
@if EXIST %TMPTEST% @del %TMPTEST%

@echo Processing input test case list from testcases.txt
@echo Each test will be passed to onetest1.bat for processing...

@set ERRTESTS=
for /F "tokens=1*" %%i in (testcases.txt) do call onetest2.bat %%i %%j
@if "%ERRTESTS%." == "." goto DONE
@echo ERROR TESTS [%ERRTESTS%] ...
:DONE
@echo Completed all test... full output written to %TMPTEST%
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
echo	ERROR: Can not locate 'onetest2.bat' ... check name, and location ...
goto END
:ERR4
echo	ERROR: Can not locate 'input' folder ... check name, and location ...
goto END
:ERR5
echo	ERROR: Can not locate 'testbase' folder ... check name, and location ...
goto END
:ERR6
echo	ERROR: Seem unable to run 'diff'! Either intall 'diff' in your path,
@echo   or *** FIX ME *** to use a some other file compare untility.
goto END

:USE
@echo  Usage of ALLTEST2.BAT .........................................
@echo  AllTest2 tidy.exe Out_Folder
@echo  tidy.exe - This is the Tidy.exe you want to use for the test.
@echo  Out_Folder  - This is the FOLDER where you want the results put.
@echo  This folder will be created if it does not already exist.
@echo  ==================================
@echo  ALLTEST2.BAT will run a battery of test files in the input folder
@echo  Each test name, has an expected result, given in testcases.txt
@echo  There will be a warning if any test file fails to give this result.
@echo  ==================================
@echo  But the main purpose is to compare the 'results' of two version of
@echo  any two Tidy runtime exe's. Thus the NEW sets of results,
@echo  will be compareed these two folders.
@echo  Probably any file compare utility can be used, but here 'diff'
@echo  is used.
@echo  ==================================
@echo  Essentially this batch file should be run using alltestc.bat, 
@echo  which establishes some of the variable needed.
@echo  ................................................................
@goto END

:END
