@echo off
%~d0
cd %~p0
echo ------------------------------------------------
echo cygwin command-line tool development environment
echo ------------------------------------------------

call bin\config.bat

path=%path%;%CYGPATH%\bin;bin
prompt=$T$H$H$H$H$H$H[$p]
cmd /K

