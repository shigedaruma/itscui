@echo off
rem �N���X�R���p�C���̑I��
set GPP=x86_64-w64-mingw32-g++
set CSET=932
if [%1]==[w64] goto exec
set GPP=g++
set CSET=65001
:exec
chcp %CSET%>nul
