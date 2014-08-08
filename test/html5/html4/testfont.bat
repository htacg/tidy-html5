@setlocal
@call setexe
@set TMPFIL=C:\HOMEPAGE\Orange\font5.html
@if NOT EXIST %TMPFIL% (
@echo Unable to locate FILE %TMPFIL%
@exit /b 1
)

@call testone

@echo See %TMPINFO%

