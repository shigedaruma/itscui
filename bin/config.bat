rem �R���t�B�O�ݒ�
rem startup.bat ����Ăяo�����z��
set PREFERENCE_BAT=bin\preference.bat
set XCOMP_BAT=bin\xcomp.bat

rem PREFERENCE �t�@�C��������Ύ��s���ďI��
if exist %PREFERENCE_BAT% goto exec_pref

rem PREFERENCE �t�@�C�����Ȃ���΍쐬
rem CYGPATH �̐ݒ�
set CYGPATH_DEF=c:\cygwin64
set /P CYGPATH=Enter cygwin path or skip by setting (%CYGPATH_DEF%) as default :
if not [%CYGPATH%]==[] goto compiler
set CYGPATH=%CYGPATH_DEF%
:compiler
set COMPILER_DEF=w64
set /P COMPILER=Select compiler with {w64 or cygwin} or skip by setting (%COMPILER_DEF%) as default :
if not [%COMPILER%]==[] goto make_pref
set COMPILER=%COMPILER_DEF%
:make_pref
echo set CYGPATH=%CYGPATH%> %PREFERENCE_BAT%
echo set COMPILER=%COMPILER%>> %PREFERENCE_BAT%

:exec_pref
call %PREFERENCE_BAT%
call %XCOMP_BAT% %COMPILER%
