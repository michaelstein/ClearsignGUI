call "%VS140COMNTOOLS%\..\..\Vc\vcvarsall.bat" amd64

rem Create debug build directory.
cd /d %~dp0
if not exist build_win_x64 mkdir build_win_x64
cd build_win_x64
cmake -DQTDIR="%QTDIR%" -G "Visual Studio 14 2015 Win64" ..

pause
