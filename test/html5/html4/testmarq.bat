@setlocal
@call setexe
@set TMPFIL=marquee5.html
@if NOT EXIST %TMPFIL% (
@echo Unable to locate FILE %TMPFIL%
@exit /b 1
)

@call testone

@echo See %TMPINFO%

