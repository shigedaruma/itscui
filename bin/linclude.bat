@echo off
%~d0
cd %~dp0\..\inc\
for /F %%f in (..\bin\lincludes.txt) do (del %%~nxf && mklink %%~nxf ..\prj\%%f)
pause

