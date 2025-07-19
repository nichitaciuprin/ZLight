@echo off
setlocal

set root=%~dp0..\..
set deps=%~dp0..\..\deps
set build=%~dp0build
set main=%~dp0main.cpp

set flags=%flags% -std=c++17 -m64
set flags=%flags% -g0 -O3 -D NDEBUG

set lib=%lib% -L%deps%\sys\lib -lsyshelperwin
set lib=%lib% -L%deps%\sys\lib -lsyswindowwin
set lib=%lib% -L%deps%\sys\lib -lsysnetwin

set include=%include% -I%deps%\sys\include
set include=%include% -I%deps%\corelib
set include=%include% -I%deps%
set include=%include% -I%root%

if exist %build% rmdir /S /Q %build%
   mkdir %build%

g++ %main% %src% -o %build%/main.exe %lib% %include% %flags%
