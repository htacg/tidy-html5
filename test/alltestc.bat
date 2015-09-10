@setlocal

@REM alltestc.bat - execute all test cases
@REM

@REM ########################################################
@REM ### *** SET LOCATION OF TIDY EXE TO USE FOR TEST *** ###
@REM ###           (for MS compiler users)                ###
@REM ########################################################
@REM This is the location of the cmake build output using the MSVC Generator
@set TMPEXE=..\build\cmake\Release\tidy.exe
@if NOT EXIST %TMPEXE% goto NOEXE

@set TMPTEST=temptests.txt
@if EXIST %TMPTEST% @del %TMPTEST%

@echo Doing: 'alltest2 %TMPEXE% temp-5'

@call alltest2 %TMPEXE% temp-5

@goto END

:NOEXE
@echo.
@echo Error: Can NOT locate %TMPEXE%! Has it been built?
@echo *** FIX ME *** setting the location of the EXE to use for the test
:END
