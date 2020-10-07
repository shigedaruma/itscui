rem do it
rem 単体テストのテスト環境

%GPP% -I ../../../inc/ -D UNIT_TESTING=1 -D UNIT_TEST_TEST=1 -m64 --std=c++14 -Wall unit_test.cpp --static -l stdc++ 2> error.log
if errorlevel, 1 goto err
a.exe > test.log
echo eixt code = %errorlevel%
exit /b 0
:err
start error.log

