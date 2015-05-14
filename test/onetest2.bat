@setlocal
@echo off
@set TMPTEST=temptest.txt
REM onetest2.bat - execute a single test case
REM

@if "%TIDY%." == "." goto Err1
@if NOT EXIST %TIDY% goto Err2
@if "%TIDYOUT%." == "." goto Err3
@if NOT EXIST %TIDYOUT%\nul goto Err4
@if NOT EXIST input\nul goto Err5
@if NOT EXIST testbase\nul goto Err8
@if "%1x" == "x" goto Err9
@if "%2x" == "x" goto Err10

set TESTNO=%1
set EXPECTED=%2

set INFILES=input\in_%1.*ml
set CFGFILE=input\cfg_%1.txt

set TIDYFILE=%TIDYOUT%\out_%1.html
set MSGFILE=%TIDYOUT%\msg_%1.txt

@rem Setup the BASE file
@set TIDYBASE=testbase\out_%1.html

set HTML_TIDY=

REM If no test specific config file, use default.
if NOT exist %CFGFILE% set CFGFILE=input\cfg_default.txt

REM Get specific input file name
@set INFILE=
for %%F in ( %INFILES% ) do set INFILE=%%F 
@if "%INFILE%." == "." goto Err6
@if NOT EXIST %INFILE% goto Err7

REM Remove any pre-exising test outputs
if exist %MSGFILE%  del %MSGFILE%
if exist %TIDYFILE% del %TIDYFILE%

@REM Noisy output, or quiet
@REM echo Testing %1 input %INFILE% config %CFGFILE% ...
@echo Doing: '%TIDY% -f %MSGFILE% -config %CFGFILE% %3 %4 %5 %6 %7 %8 %9 --tidy-mark no -o %TIDYFILE% %INFILE% >> %TMPTEST%

@%TIDY% -f %MSGFILE% -config %CFGFILE% %3 %4 %5 %6 %7 %8 %9 --tidy-mark no -o %TIDYFILE% %INFILE%
@set STATUS=%ERRORLEVEL%
@echo Testing %1, expect %EXPECTED%, got %STATUS%
@echo Testing %1, expect %EXPECTED%, got %STATUS% >> %TMPTEST%

@if %STATUS% EQU %EXPECTED% goto EXITOK
@set ERRTESTS=%ERRTESTS% %TESTNO%
@echo *** Failed - got %STATUS%, expected %EXPECTED% ***
@type %MSGFILE%
@echo *** Failed - got %STATUS%, expected %EXPECTED% *** >> %TMPTEST%
@type %MSGFILE% >> %TMPTEST%

:EXITOK
@if NOT EXIST %TIDYBASE% goto NOBASE
@if NOT EXIST %TIDYFILE% goto NOOUT
@echo Doing: 'diff -u %TIDYBASE% %TIDYFILE%' >> %TMPTEST%
@diff -u %TIDYBASE% %TIDYFILE% >> %TMPTEST%
@if ERRORLEVEL 1 goto GOTDIFF
@goto done

:GOTDIFF
@echo Got a DIFFERENCE between %TIDYBASE% and %TIDYFILE% 
@echo Got a DIFFERENCE between %TIDYBASE% and %TIDYFILE% >> %TMPTEST%
@goto done

:NOBASE
@REM If errorlevel 2 then normally no output generated, to this is OK
@if "%STATUS%" == "2" goto done
@REM If no output generated this time, then this is probably OK
@if NOT EXIST %TIDYFILE% goto done
@echo Can NOT locate %TIDYBASE%. This may be ok if not file generated
@goto done
:NOOUT
@echo *** FAILED: A base file exists, but none geneated this time!
@echo *** FAILED: A base file exists, but none geneated this time! >> %TMPTEST%
@goto done

:Err1
@echo.
@echo ERROR: runtime exe not set in TIDY environment variable ...
@echo.
@goto TRYAT

:Err2
@echo.
@echo ERROR: runtime exe %TIDY% not found ... check name, location ...
@echo.
@goto TRYAT

:Err3
@echo.
@echo ERROR: output folder TIDYOUT not set in environment ...
@echo.
@goto TRYAT

:Err4
@echo.
@echo ERROR: output folder %TIDYOUT% does not exist ...
@echo.
@goto TRYAT

:Err5
@echo.
@echo ERROR: input folder 'input' does not exist ... check name, location ..
@echo.
@goto TRYAT

:TRYAT
@echo You could try running alltest1.cmd ..\build\cmake\Release\Tidy5.exe tmp
@echo but essentially this file should be run using the alltestc.bat batch file.
@echo.
@pause
@goto done

:Err6
@echo.
@echo ERROR: Failed to find input matching '%INFILES%'!!!
@echo.
@pause
@goto done

:Err7
@echo.
@echo ERROR: Failed to find input file '%INFILE%'!!!
@echo.
@pause
@goto done

:Err8
@echo.
@echo ERROR: Failed to find 'testbase' folder!!!
@echo.
@pause
@goto done

:Err9
@echo.
@echo ERROR: No input test number given as 1st parameter!
:Err10
@echo ERROR: No expected exit value given as 2nd parameter!
@echo.
@echo Essentially this bat is intended to be used by alltest2.bat,
@echo which in turn is used by alltestc.bat, so try alltestc.bat.
@echo It is not intended that this batch file be run in isolation,
@echo even when TIDY and TIDYOUT have been set in the environent.
@echo.
@goto done

:done
