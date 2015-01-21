@setlocal
@call setexe
@set TMPFIL=bodyatts5.html
@if NOT EXIST %TMPEXE% (
@echo Unable to locate EXE %TMPEXE%
@exit /b 1
)
@if NOT EXIST %TMPFIL% (
@echo Can NOT locate %TMPFIL%! *** FIX ME ***
@exit /b 1
)

@call testone

@echo see %TMPINFO%

