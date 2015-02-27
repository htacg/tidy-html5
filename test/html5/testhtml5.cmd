@setlocal

@set TMPEXE=..\..\build\cmake\Release\tidy5.exe
@if NOT EXIST %TMPEXE% goto NOEXE
@set TMPINP=temphtml5.cfg
@set TMPDIR=tempout

@%TMPEXE% -h > nul
@if ERRORLEVEL 1 goto NOEXE

@if EXIST %TMPDIR%\nul goto GOTOUT
@echo Will create the folder %TMPDIR% for output...
@pause
@md %TMPDIR%
@if ERRORLEVEL 1 goto NOOUT
@if NOT EXIST %TMPDIR%\nul goto NODIR
:GOTOUT

@REM This option would be nice, but at present it is FARRRR TOOOOO agressive,
@REM dropping <html>, <body>, etc...  because they are marked CM_OPT
@REM which causes WARNINGS when tidy is run on the tidied file!!!
@REM echo omit-optional-tags: yes >> %TMPINP%

@if EXIST %TMPINP% goto GOTINP
@echo Creating a CONFIG file %TMPINP%
@pause
@echo wrap: 99 > %TMPINP%
@echo tidy-mark: no >> %TMPINP%
@echo indent: yes >> %TMPINP%
@echo break-before-br: yes >> %TMPINP%
@echo indent-attributes: yes >> %TMPINP%
@echo vertical-space: yes >> %TMPINP%
@echo indent-spaces: 1 >> %TMPINP%
@echo indent-cdata: no >> %TMPINP%
@echo wrap-asp: no >> %TMPINP%
@echo wrap-attributes: no >> %TMPINP%
@echo wrap-jste: no >> %TMPINP%
@echo wrap-php: no >> %TMPINP%
@echo wrap-script-literals: no >> %TMPINP%
@echo wrap-sections: no >> %TMPINP%
@echo tab-size: 4 >> %TMPINP%
@echo show-info: no >> %TMPINP%
@if NOT EXIST %TMPINP% goto NOINP
:GOTINP
@set TMPCNT1=0
@set TMPCNT2=0
@set TMPCNT3=0

@for %%i in (*.org.html) do @(call :CNTIT %%i)
@echo.
@echo Will process %TMPCNT1% files found...
@echo All should exit with NO WARNINGS or ERRORS
@echo *** CONTINUE? *** Only Ctlr+C aborts... all other keys continue...
@pause

@for %%i in (*.org.html) do @(call :DOONE %%i)

@echo.
@echo Done %TMPCNT2% files. See tidied output in %TMPDIR%...
@if "%TMPCNT3%x" == "0x" (
@echo With NO WARNINGS or ERRORS! This is a *** SUCCESS ***.
) ELSE (
@echo However have %TMPCNT3% WARNINGS or ERRORS! This is a *** FAILURE ***
)
@echo.

@goto END

:CNTIT
@if "%~1x" == "x" goto :EOF
@set /A TMPCNT1+=1
@goto :EOF

:DOONE
@if "%~1x" == "x" goto :EOF
@set /A TMPCNT2+=1
@echo %TMPCNT2% of %TMPCNT1%: %1
@set TMPOUT=%TMPDIR%\%~nx1
@%TMPEXE% -config %TMPINP% -o %TMPOUT% %1
@if ERRORLEVEL 1 goto FAILED
@goto :EOF

:FAILED
@echo The test of %1 FAILED!
@set /A TMPCNT3+=1
@pause
@goto :EOF

:NODIR
:NOOUT
@echo Error: Unable to create %TMPDIR%!
@goto END


:NOEXE
@echo Unable to find/run exe %TMPEXE%! *** FIX ME ***
@echo Set the name of the 'tidy' executable to use...
@goto END

:NOINP
@echo Error: Unable to create config file %TMPINP%!
@goto END


:END
