@echo off

REM Sébastien Millet, October 2015
REM Measure execution times with zsbc

set ZSBC="zsbc.exe"

time /T
%ZSBC% "%1" > NUL
time /T

