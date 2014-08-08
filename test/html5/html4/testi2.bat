@setlocal
@call setexe
@set TMPFIL=index2.html

@call testone

@REM tidy5 -c -i --doctype html5 -o temptidy5.html --tidy-mark no index2.html

