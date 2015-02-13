@setlocal

@REM alltest.cmd - execute all test cases
@REM
@REM (c) 1998-2014 (W3C) MIT, ERCIM, Keio University
@REM See include/tidy.h for the copyright notice.
@REM
@REM <URL:http://www.html-tidy.org/>
@REM

@REM ########################################################
@REM ### *** SET LOCATION OF TIDY EXE TO USE FOR TEST *** ###
@REM ###           (for MS compiler users)                ###
@REM ########################################################
@REM call alltest1 ..\build\msvc\Release\tidy.exe .\tmp
@REM call alltest1 ..\bin\tidy.exe .\tmp
@REM ########################################################################
@REM This is the location of the cmake build output using the MSVC Generator
@set TMPEXE=..\build\cmake\Release\tidy5.exe
@REM === some other test EXE I can use for compare ===
@REM set TMPEXE=C:\Projects\tidy\tidy-cvs\build\msvc\Release\tidy.exe
@REM set TMPEXE=C:\MDOS\tidydev.exe
@REM ########################################################################
@if NOT EXIST %TMPEXE% goto NOEXE

@set TMPTEST=temptests.txt
@if EXIST %TMPTEST% @del %TMPTEST%

@call alltest1 %TMPEXE% temp-5

@goto END

:NOEXE
@echo.
@echo Error: Can NOT locate %TMPEXE%! Has it been built?
@echo *** FIX ME *** setting the location of the EXE to use for the test
:END
