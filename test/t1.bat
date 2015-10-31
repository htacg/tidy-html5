@setlocal
@REM =================================================================
@REM A convenient run one test giving the number and expected exit
@REM
@REM This is to run just one, like "t1 1642186-1 0"
@REM
@REM Note it uses a relative path to the built exe file, and
@REM expects the ouput folder has to exist.
@REM
@REM Obviously you may want to adjust this file, like seen below to test
@REM different versions of tidy.exe...
@REM Rather than altering this file, which will be flagged by git,
@REM I copy it to say a temp1.bat, and modify that to suit my testing
@REM
@REM There is also an 'alltest.cmd' which runs some 227 tests that 
@REM gets the case listed in 'testcases.txt' file.
@REM
@REM =================================================================

@REM setup the ENVIRONMENT
@set TIDY=..\build\cmake\Release\tidy.exe
@REM set TIDY=C:\MDOS\tidy5.exe
@REM set TIDY=C:\MDOS\tidydev02.exe
@set TIDYOUT=temp-02
@set TMPTEST=temptest1.txt

@if NOT EXIST %TIDYOUT%\nul goto NOOUT
@if NOT EXIST %TIDY% goto NOEXE

@REM Check user input
@if "%~1x" == "x" goto HELP
@if "%~2x" == "x" goto HELP

@set TMPFIL=input\in_%1.xhtml
@if NOT EXIST %TMPFIL% (
@set TMPFIL==input\in_%1.html
)
@set TMPCFG=input\cfg_%1.txt
@if NOT EXIST %TMPCFG% (
@set TMPCFG=input\cfg_default.txt
)

@if NOT EXIST %TMPFIL% goto NOFIL
@if NOT EXIST %TMPCFG% goto NOCFG

@echo Test 1 case %DATE% %TIME% > %TMPTEST%
@%TIDY% -v >> %TMPTEST%
@if ERRORLEVEL 1 goto NOTIDY

%TIDY% -v
@echo.
@echo Doing '@call onetest.cmd %1 %2'
@echo Doing '@call onetest.cmd %1 %2' >> %TMPTEST%

@call onetest.cmd %1 %2

@echo See ouput in %TMPTEST%

@set TMPFIL1=testbase\out_%1.html
@set TMPOUT1=testbase\msg_%1.txt
@set TMPFIL2=%TIDYOUT%\out_%1.html
@set TMPOUT2=%TIDYOUT%\msg_%1.txt

@if NOT EXIST %TMPFIL1% goto NOFIL1
@if NOT EXIST %TMPFIL2% goto NOFIL1

@if NOT EXIST %TMPOUT1% goto NOFIL2
@if NOT EXIST %TMPOUT2% goto NOFIL2

@REM Compare the outputs, exactly
@set TMPOPTS=-ua
@set ERRCNT=0

@echo.
@echo Doing: '@diff %TMPOPTS% %TMPFIL1% %TMPFIL2%'
@diff %TMPOPTS% %TMPFIL1% %TMPFIL2%
@if ERRORLEVEL 1 goto GOTD1
@echo Files appear exactly the same...
@goto DODIF2
:GOTD1
@call :ISDIFF
@set /A ERRCNT+=1
:DODIF2

@echo.
@echo Doing: '@diff %TMPOPTS% %TMPOUT1% %TMPOUT2%'
@diff %TMPOPTS% %TMPOUT1% %TMPOUT2%
@if ERRORLEVEL 1 goto GOTD2
@echo Files appear exactly the same...
@goto DODIF3
:GOTD2
@call :ISDIFF
@set /A ERRCNT+=1
:DODIF3
@echo.
@if "%ERRCNT%x" == "0x" (
@echo Appears a successful test of %1 %2
) else (
@echo Carefully REVIEW the above differences on %1 %2! *** ACTION REQUIRED ***
)

@goto END

:ISDIFF
@echo.
@echo Check the above diff carefully. This may indicate a 'testbase', or
@echo a 'regression' in tidy output.
@echo.
@goto :EOF

:NOFIL1
@echo.
@echo Can NOT locate %TMPFIL1% or %TMPFIL2% 
@echo needed for the compare... but this may not be a problem...
@echo Maybe there is no 'testbase' file for test %1!
@echo.
@goto END

:NOFIL2
@echo.
@echo Can NOT locate  %TMPOUT1% or %TMPOUT2% 
@echo needed for the compare... but this may not be a problem...
@echo but it is strange one or both were not created!!! *** NEEDS CHECKING ***
@echo.
@goto END


:NOEXE
@echo.
@echo Error: Unable to locate file '%TIDY%'! Has it been built? *** FIX ME ***
@echo.
@goto END

:NOTIDY
@echo.
@echo Error: Unable to run '%TIDY% -v' successfully! *** FIX ME ***
@echo.
@goto END

:NOOUT
@echo.
@echo Error: Can NOT locate %TIDYOUT%! This MUST be created!
@echo This script does NOT create any directories...
@echo.
@goto END

:NOFIL
@echo.
@dir input\*%1*
@echo.
@echo Error: Can NOT locate %TMPFIL%! Is number correct? 
@echo.
@goto END

:NOCFG
@echo.
@echo Error: Can NOT locate %TMPCFG%!
@echo.
@goto END


:HELP
@echo.
@echo - Usage: %0 "value" "expected exit value"
@echo - That is give test number, and expected result, like
@echo - %0 1642186 1
@if "%~1x" == "x" goto HELP2
@echo - Missing expected value. See testcases.txt for list available...
@echo Checking testcases.txt for test %1
@fa4 "%~1" testcases.txt
:HELP2
@echo.

:END
