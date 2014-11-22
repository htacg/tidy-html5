@if NOT EXIST %TMPEXE% goto NOEXE
@if NOT EXIST %TMPFIL% goto NOFIL

@echo Tests on %TMPFIL% using %TMPEXE%, output to %TMPINFO%
@echo Tests on %TMPFIL% using %TMPEXE% > %TMPINFO%
@echo ================================================ >> %TMPINFO%
@echo Using configure DOCTYPE AND CLEAN >> %TMPINFO%
@echo ================================================  >> %TMPINFO%
@echo Doing: -c -i --doctype html5 -o temp1c.html --tidy-mark no %TMPSHOW% %TMPFIL% >> %TMPINFO%
@%TMPEXE% -c -i --doctype html5 -o temp1c.html --tidy-mark no %TMPSHOW% %TMPFIL% >> %TMPINFO% 2>&1
@type temp1c.html >> %TMPINFO%
@echo ================================================ >> %TMPINFO%
@echo Using configure DOCTYPE but NO CLEAN >> %TMPINFO%
@echo ================================================  >> %TMPINFO%
@echo Doing: -i --doctype html5 -o temp1nc.html --tidy-mark no %TMPSHOW% %TMPFIL% >> %TMPINFO%
@%TMPEXE%    -i --doctype html5 -o temp1nc.html --tidy-mark no %TMPSHOW% %TMPFIL% >> %TMPINFO% 2>&1
@type temp1nc.html >> %TMPINFO%
@echo ================================================ >> %TMPINFO%
@echo Using configure CLEAN but NO DOCTYPE >> %TMPINFO%
@echo ================================================  >> %TMPINFO%
@echo Doing: -c -i -o temp1cndt.html --tidy-mark no %TMPSHOW% %TMPFIL% >> %TMPINFO%
@%TMPEXE% -c -i -o temp1cndt.html --tidy-mark no %TMPSHOW% %TMPFIL% >> %TMPINFO%  2>&1
@type temp1cndt.html >> %TMPINFO%
@echo ================================================ >> %TMPINFO%
@echo Using configure NO CLEAN and NO DOCTYPE >> %TMPINFO%
@echo ================================================  >> %TMPINFO%
@echo Doing: -i -o temp1ncndt.html --tidy-mark no %TMPSHOW% %TMPFIL% >> %TMPINFO%
@%TMPEXE%    -i -o temp1ncndt.html --tidy-mark no %TMPSHOW% %TMPFIL% >> %TMPINFO%  2>&1
@type temp1ncndt.html >> %TMPINFO%

@REM call ff -d -n %TMPINFo% -o-tempinf2.html

@goto END

:NOEXE
@echo Error: Can NOT locate the EXE '%TMPEXE%' *** Fix setexe.bat accordingly
@goto FAILED
:NOFIL
@echo Error: Can NOT locate the input file '%TMPFIL%' *** Fix test*.bat accordingly
@goto FAILED

:FAILED
@echo Use Ctrl+C to abort and fix this situation
@pause
@goto FAILED

:END



@REM eof
