
@REM ##############################################################
@REM ### To be adjusted to suit your location of the EXE to use ###
@REM ##############################################################

@set TMPEXE=C:\Projects\tidy\tidy-fork\build\win64\Release\tidy5.exe
@REM set TMPEXE=C:\MDOS\tidygh.exe
@REM set TMPEXE=C:\MDOS\tidy5.exe
@if NOT EXIST %TMPEXE% (
:RPT
@echo Can NOT locate EXE %TMPEXE%!
@echo *** FIX ME %0 *** to point to the EXE to use...
@echo Use Ctrl+C to abort
@pause
@goto RPT
)
@set TMPINFO=tempinfo.html
@set TMPSHOW=
@REM set TMPSHOW=--show-info no

