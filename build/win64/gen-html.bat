@setlocal
@REM Build HTML from log of 'version.txt'
@REM Versify the tools used
@call verhist -? >nul
@if ERRORLEVEL 1 (
@echo Unable to run 'verhist.pl'! *** FIX ME ***
@exit /b 1
)
@call emailobfuscate -? >nul
@if ERRORLEVEL 1 (
@echo Unable to run 'emailobfuscate.pl'! *** FIX ME ***
@exit /b 1
)

@set TMPFIL1=..\..\version.txt
@if NOT EXIST %TMPFIL1% (
@echo Can NOT locate %TMPFIL1%, in %CD% - *** FIX ME ***
@exit /b 1
)

@call dirmin %TMPFIL1%

@set /P TMPVER=<%TMPFIL1%

@echo Current version '%TMPVER%' ...
@set TMPLOG1=..\..\..\temp-%TMPVER%.log
@set TMPLOG2=..\..\..\temp2-%TMPVER%.log
@set TMPLOG3=..\..\..\temp3-%TMPVER%.log

@if EXIST %TMPLOG1% goto GOTL1
@call git log -p %TMPFIL1% > %TMPLOG1%
@if NOT EXIST %TMPLOG1% (
@echo Gen of %TMPLOG1% FAILED! *** FIX ME ***
@exit /b 1
)
:GOTL1
@echo Got log 1 '%TMPLOG1%' ...
@call dirmin %TMPLOG1%

@if EXIST %TMPLOG2% goto GOTL2
@call verhist %TMPLOG1% -o %TMPLOG2%
@if EXIST %TMPLOG2% goto GOTL2
@echo Gen of %TMPLOG2% FAILED! *** FIX ME ***
@exit /b 1
:GOTL2
@echo Got log 2 '%TMPLOG2%' ...
@call dirmin %TMPLOG2%

@set TMPV=%1
@if "%TMPV%x" == "x" (
@echo Give the cut-off version, like 5.6.0, to continue..
@exit /b 1
)

@echo Doing: 'call grep %TMPV% %TMPLOG2%' ...
@call grep %TMPV% %TMPLOG2%
@if ERRORLEVEL 1 (
@echo Failed to find '%TMPV%'... check the file '%TMPLOG2%'
@exit /b 1
)

@set TMPD=%~2
@if "%TMPD%x" == "x" (
@echo Give the DATE of the cut-off, like 'Sat Nov 25 14:50:00 2017 +0100', to continue...
@exit /b 1
)

@if EXIST %TMPLOG3% goto GOTL3
@call git log "--decorate=full" "--since=%TMPD%" > %TMPLOG3%
@if EXIST %TMPLOG3% goto GOTL3
@echo Failed to generate 'git log ...' - *** FIX ME ***
@exit /b 1
:GOTL3
@echo Got log 3 '%TMPLOG3%' ...
@call dirmin %TMPLOG3%

@REM at last generate the release HTML

@set TMPHTM=..\..\..\temp-%TMPVER%.html
@if EXIST %TMPHTM% goto GOTL4
@call emailobfuscate %TMPLOG3% -o %TMPHTM% -a %TMPVER% -i
@if EXIST %TMPHTM% goto GOTL4
@echo FAILED to generate %TMPHTM%! *** FIX ME ***
@exit /b 1
:GOTL4
@echo Got HTML '%TMPHTM%' ...
@call dirmin %TMPHTM%

@REM All success - check image
@call start %TMPHTM%

@REM eof

