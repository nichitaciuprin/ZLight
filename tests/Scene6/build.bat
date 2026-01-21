@echo off
setlocal

set build=%~dp0build

set flags=%flags% -Werror -Wall
set flags=%flags% -std=c99 -m64
set flags=%flags% -g0 -O3 -D NDEBUG

if exist %build% rmdir /S /Q %build%
   mkdir %build%

gcc %~dp0main.c -o %build%/main.exe -I%~dp0..\.. %flags% -lgdi32 -lwinmm
