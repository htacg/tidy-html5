@setlocal
@call setexe
@set TMPFIL=dir5.html
@if NOT EXIST %TMPFIL% (
@echo Unable to locate FILE %TMPFIL%
@exit /b 1
)

@REM %TMPEXE% -c -i --doctype html5 -o temptidy5.html --tidy-mark no --show-info no %TMPFIL%
@REM %TMPEXE% -i --doctype html5 -o temptidy5.html --tidy-mark no --show-info no %TMPFIL%

@call testone

@echo See %TMPINFO%
