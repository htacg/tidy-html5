@echo off

REM alltest.cmd - execute all test cases
REM
REM (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
REM See tidy.c for the copyright notice.
REM
REM <URL:http://tidy.sourceforge.net/>
REM

REM (for MS compiler users):
REM call alltest1 ..\build\msvc\Release\tidy.exe .\tmp

call alltest1 ..\bin\tidy.exe .\tmp
