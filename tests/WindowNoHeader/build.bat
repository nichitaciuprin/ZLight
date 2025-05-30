@echo off
setlocal

set deps=%~dp0..\..\deps
set build=%~dp0build
set main=%~dp0main.cpp

set flags=%flags% -Werror -Wall
@REM set flags=%flags% -std=c17 -m64
set flags=%flags% -std=c++17 -m64
@REM set flags=%flags% -g3 -Og
set flags=%flags% -g0 -O3 -D NDEBUG

set include=%include% -I%~dp0src

set lib=%lib% -lgdi32

if exist build rmdir /S /Q build
   mkdir build

gcc %main% %src% -o %build%/main.exe %include% %lib% %flags%
