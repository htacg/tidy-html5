@setlocal
@REM echo off

@REM execute a single test case of the accessibility test suite
@REM
@REM (c) 2006 (W3C) MIT, ERCIM, Keio University
@REM See tidy.c for the copyright notice.
@REM
@REM <URL:http://www.html-tidy.org/>
@REM
@echo Testing %1 %2 %3
@set TESTNO=%1
@set TESTEXPECTED=%2
@set ACCESSLEVEL=%3
@if "%1x" == "x" goto NOTEST
@if "%2x" == "x" goto NOEXPECT
@if "%3x" == "x" goto NOLEVEL
@if "%TIDYLOG%x" == "x" goto NOLOG

@set INFILES=%TIDYINPUT%\%1.*ml
@set CFGFILE=%TIDYINPUT%\cfg_%1.txt

@set TIDYFILE=%TIDYOUT%\out_%1.html
@set MSGFILE=%TIDYout%\msg_%1.txt

@set HTML_TIDY=

@REM If no test specific config file, use default.
@if NOT exist %CFGFILE% @set CFGFILE=%TIDYINPUT%\cfg_default.txt

@REM Get specific input file name
@for %%F in ( %INFILES% ) do @set INFILE=%%F

@if EXIST %INFILE% goto DOIT
@echo ERROR: Can NOT locate [%INFILE%] ... aborting test ...
@echo ======================================= >> %TIDYLOG%
@echo Testing %1 %2 %3 >> %TIDYLOG%
@echo ERROR: Can NOT locate [%INFILE%] ... aborting test ... >> %TIDYLOG%
@goto done

:DOIT
@REM Remove any pre-existing test outputs
@if exist %MSGFILE%  del %MSGFILE%
@if exist %TIDYFILE% del %TIDYFILE%

@REM this has to all one line ...
@%TIDY% -f %MSGFILE% --accessibility-check %ACCESSLEVEL% -config %CFGFILE% --gnu-emacs yes --tidy-mark no -o %TIDYFILE% %INFILE%

@REM output the FIND count to the a result file
@find /c "%TESTEXPECTED%" %MSGFILE% > tempres.txt
@REM load the find count, token 3, into variable RESULT
@for /F "tokens=3" %%i in (tempres.txt) do @set RESULT=%%i
@REM test the RESULT variable ...
@if "%RESULT%." == "0." goto Err
@if "%RESULT%." == "1." goto done
@REM echo note - test '%TESTEXPECTED%' found %RESULT% times in file '%INFILE%'
@goto done

:Err
@echo FAILED --- test '%TESTEXPECTED%' not detected in file '%INFILE%'
@type %MSGFILE%
@echo FAILED --- test '%TESTEXPECTED%' not detected in above
@set FAILEDACC=%FAILEDACC% %1
@REM append results to the ACCERR.TXT file
@echo ======================================= >> %TIDYLOG%
@echo %TIDY% -f %MSGFILE% --accessibility-check %ACCESSLEVEL% -config %CFGFILE% --gnu-emacs yes --tidy-mark no -o %TIDYFILE% %INFILE% >> %TIDYLOG%
@echo FAILED --- test '%TESTEXPECTED%' not detected in file '%MSGFILE%', as follows - >> %TIDYLOG%
@type %MSGFILE% >> %TIDYLOG%
@echo FAILED --- test '%TESTEXPECTED%' not detected in above >> %TIDYLOG%
@goto done

:NOTEST
@echo Error: NO test number given as the first command!
:NOEXPECT
@echo Error: NO expected result given as the second command!
:NOLEVEL
@echo Error: NO accesslevel given as the thrid command!
@goto HELP

:NOLOG
@echo.
@echo Error: TIDYLOG NOT set in the environment!!! This is set in acctest.cmd
:HELP
@echo The file acctest.cmd should be used to run this cmd...
@echo Use Ctrl+c to abort, to fix...
@pause
@goto NOLOG

:done
@endlocal
