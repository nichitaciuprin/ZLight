@echo off
setlocal

set build=%~dp0build

set flags=%flags% -std=c++17 -m64
set flags=%flags% -g0 -O3 -D NDEBUG

if exist %build% rmdir /S /Q %build%
   mkdir %build%

g++ %~dp0main.cpp -o %build%/main.exe -I%~dp0..\.. %flags%
