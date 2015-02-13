@echo off
@set TMPTEST=temptest.txt
REM onetest.cmd - execute a single test case
REM
REM (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
REM See tidy.c for the copyright notice.
REM
REM <URL:http://www.html-tidy.org/>
REM

@if "%TIDY%." == "." goto Err1
@if NOT EXIST %TIDY% goto Err2
@if "%TIDYOUT%." == "." goto Err3
@if NOT EXIST %TIDYOUT%\nul goto Err4
@if NOT EXIST input\nul goto Err5

set TESTNO=%1
set EXPECTED=%2

set INFILES=input\in_%1.*ml
set CFGFILE=input\cfg_%1.txt

set TIDYFILE=%TIDYOUT%\out_%1.html
set MSGFILE=%TIDYOUT%\msg_%1.txt

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

@if %STATUS% EQU %EXPECTED% goto done
@set ERRTESTS=%ERRTESTS% %TESTNO%
@echo *** Failed - got %STATUS%, expected %EXPECTED% ***
@type %MSGFILE%
@echo *** Failed - got %STATUS%, expected %EXPECTED% *** >> %TMPTEST%
@type %MSGFILE% >> %TMPTEST%
goto done

:Err1
@echo ==============================================================
@echo ERROR: runtime exe not set in TIDY environment variable ...
@echo ==============================================================
@goto TRYAT

:Err2
@echo ==============================================================
@echo ERROR: runtime exe %TIDY% not found ... check name, location ...
@echo ==============================================================
@goto TRYAT

:Err3
@echo ==============================================================
@echo ERROR: output folder TIDYOUT not set in environment ...
@echo ==============================================================
@goto TRYAT

:Err4
@echo ==============================================================
@echo ERROR: output folder %TIDYOUT% does not exist ...
@echo ==============================================================
@goto TRYAT

:Err5
@echo ==============================================================
@echo ERROR: input folder 'input' does not exist ... check name, location ..
@echo ==============================================================
@goto TRYAT

:TRYAT
@echo Try running alltest1.cmd ..\build\cmake\Release\Tidy5.exe tmp
@echo ==============================================================
@pause
@goto done

:Err6
@echo ==============================================================
@echo ERROR: Failed to find input matching '%INFILES%'!!!
@echo ==============================================================
@pause
@goto done

:Err7
@echo ==============================================================
@echo ERROR: Failed to find input file '%INFILE%'!!!
@echo ==============================================================
@pause
@goto done

:done
