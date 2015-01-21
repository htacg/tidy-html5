@setlocal
@set TMPCNT1=0
@if EXIST tempout (
@echo Cleaning and removing tempout folder...
@cd tempout
@del *.html >nul
@del *.txt >nul
@cd ..
@rd tempout
@set /A TMPCNT1+=1
)

@if EXIST temp* (
@echo Removing temp* file
@del temp* >nul
@set /A TMPCNT1+=1
)

@if "%TMPCNT1%x" == "0x" (
@echo Appears nothing to clean up!
)


