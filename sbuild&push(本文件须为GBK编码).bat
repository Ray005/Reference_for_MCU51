@echo off

echo git push提交程序V1.0。包含以下命令：git add、git commit、git push\n                                                                                                                         
set /p pro="请输入提交信息（不能含有空格，并使用【方括号】包含你的信息）："
set da1=%date:~0,4%
set da2=%date:~-8,-6%
set da3=%date:~-5,-3%

echo " $$$$$$\                  $$\                 $$\       $$\                       $$\   $$\                     ";
echo "$$  __$$\                 $$ |                $$ |      $$ |                      $$ |  $$ |                    ";
echo "$$ /  \__| $$$$$$\   $$$$$$$ | $$$$$$\   $$$$$$$ |      $$$$$$$\  $$\   $$\       $$ |  $$ | $$$$$$\  $$$$$$$\  ";
echo "$$ |      $$  __$$\ $$  __$$ |$$  __$$\ $$  __$$ |      $$  __$$\ $$ |  $$ |      $$$$$$$$ | \____$$\ $$  __$$\ ";
echo "$$ |      $$ /  $$ |$$ /  $$ |$$$$$$$$ |$$ /  $$ |      $$ |  $$ |$$ |  $$ |      $$  __$$ | $$$$$$$ |$$ |  $$ |";
echo "$$ |  $$\ $$ |  $$ |$$ |  $$ |$$   ____|$$ |  $$ |      $$ |  $$ |$$ |  $$ |      $$ |  $$ |$$  __$$ |$$ |  $$ |";
echo "\$$$$$$  |\$$$$$$  |\$$$$$$$ |\$$$$$$$\ \$$$$$$$ |      $$$$$$$  |\$$$$$$$ |      $$ |  $$ |\$$$$$$$ |$$ |  $$ |";
echo " \______/  \______/  \_______| \_______| \_______|      \_______/  \____$$ |      \__|  \__| \_______|\__|  \__|";
echo "                                                                  $$\   $$ |                                    ";
echo "                                                                  \$$$$$$  |                                    ";
echo "                                                                   \______/                                     ";

echo "          $$\                                                                ";
echo "          $$ |                                                               ";
echo " $$$$$$\  $$ | $$$$$$\   $$$$$$\   $$$$$$$\ $$\   $$\     $$$$$$$\ $$$$$$$\  ";
echo "$$  __$$\ $$ |$$  __$$\  \____$$\ $$  _____|$$ |  $$ |   $$  _____|$$  __$$\ ";
echo "$$$$$$$$ |$$ |$$$$$$$$ | $$$$$$$ |\$$$$$$\  $$ |  $$ |   $$ /      $$ |  $$ |";
echo "$$   ____|$$ |$$   ____|$$  __$$ | \____$$\ $$ |  $$ |   $$ |      $$ |  $$ |";
echo "\$$$$$$$\ $$ |\$$$$$$$\ \$$$$$$$ |$$$$$$$  |\$$$$$$$ |$$\\$$$$$$$\ $$ |  $$ |";
echo " \_______|\__| \_______| \_______|\_______/  \____$$ |\__|\_______|\__|  \__|";
echo "                                            $$\   $$ |                       ";
echo "                                            \$$$$$$  |                       ";
echo "                                             \______/                        ";  


git add -A
git add *
git commit -m %da1%%da2%%da3%%pro%

git push
echo git push完成
echo %da1%%da2%%da3%%pro%
pause