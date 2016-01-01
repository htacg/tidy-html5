# tools/ README

This directory contains miscellaneous tools for development use.

## poconvert

Converts between gettext po format and Tidy's special header file format.
If a .po file is specified, then a .h file will be generated. If a .h file
is specified, then a .po file will be generated.

usage: poconvert file.po
       poconvert file.h
