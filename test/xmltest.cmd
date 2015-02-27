@echo off

REM xmltest.cmd - execute all XML test cases
REM
REM (c) 1998-2003 (W3C) MIT, ERCIM, Keio University
REM See tidy.c for the copyright notice.
REM
REM <URL:http://www.html-tidy.org/>
REM

for /F "tokens=1*" %%i in (xmlcases.txt) do call onetest.cmd %%i %%j
