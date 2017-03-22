@setlocal
@set TMPLOG=bldlog-p.txt

@echo Running: 'cmake --build . --config Release --target PACKAGE' out to %TMPLOG%
@echo Running: 'cmake --build . --config Release --target PACKAGE' > %TMPLOG%
cmake --build . --config Release --target PACKAGE >> %TMPLOG%
@if ERRORLEVEL 1 goto ISERR
@echo Build package done... see %TMPLOG%
@endlocal
@exit /b 0

:ISERR
@endlocal
@exit /b 1

@REM eof
