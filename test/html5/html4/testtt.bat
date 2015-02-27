@setlocal
@call setexe
@set TMPFIL=tt5.html
@if NOT EXIST %TMPFIL% (
@echo Unable to locate FILE %TMPFIL%
@exit /b 1
)

@call testone
@REM %TMPEXE% -c -i --doctype html5 -o tempclean.html --tidy-mark no --show-info no %TMPFIL%
@REM %TMPEXE% -i --doctype html5 -o tempnoclean.html --tidy-mark no --show-info no %TMPFIL%

@echo See %TMPINFO%
