@echo off
::��������Ŀ����
set /p pro="�������ύ��Ϣ�����ܺ��пո񣩣�"
set da1=%date:~0,4%
set da2=%date:~-8,-6%
set da3=%date:~-5,-3%



git add -A
git add *
git commit -m %da1%%da2%%da3%%pro%

git push
echo ���
echo %da1%%da2%%da3%%pro%
pause