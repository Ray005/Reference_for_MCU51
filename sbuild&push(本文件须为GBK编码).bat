@echo off
::请输入项目名称
set /p pro="请输入提交信息（不能含有空格）："
set da1=%date:~0,4%
set da2=%date:~-8,-6%
set da3=%date:~-5,-3%



git add -A
git add *
git commit -m %da1%%da2%%da3%%pro%

git push
echo 完成
echo %da1%%da2%%da3%%pro%
pause