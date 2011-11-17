@echo off

REM alltest.cmd - execute all test cases
REM
REM (c) 1998-2006 (W3C) MIT, ERCIM, Keio University
REM See tidy.c for the copyright notice.
REM
REM <URL:http://tidy.sourceforge.net/>
REM
REM CVS Info:
REM
REM    $Author: arnaud02 $
REM    $Date: 2006/12/30 08:36:33 $
REM    $Revision: 1.3 $

REM (for MS compiler users):
REM call alltest1 ..\build\msvc\Release\tidy.exe .\tmp

call alltest1 ..\bin\tidy.exe .\tmp
