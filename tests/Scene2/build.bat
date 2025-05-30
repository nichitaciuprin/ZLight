@echo off
setlocal

set deps=%~dp0..\..\deps
set build=%~dp0build
set main=%~dp0main.cpp

set flags=%flags% -Werror -Wall
set flags=%flags% -std=c++17 -m64
set flags=%flags% -g3 -Og

@REM set lib=%lib% -L%deps%\Sys\lib -lsyswin
set lib=%lib% -L%deps%\Sys\lib -lsyshelperwin
set lib=%lib% -L%deps%\Sys\lib -lsyswindowwin
set lib=%lib% -L%deps%\Sys\lib -lsysnetwin

@REM set include=%include% -I%~dp0src
set include=%include% -I%deps%\corelib
set include=%include% -I%deps%\shared
set include=%include% -I%deps%\sys\include

if exist %build% rmdir /S /Q %build%
   mkdir %build%

g++ %main% %src% -o %build%/corelib.exe %include% %lib% %flags%
