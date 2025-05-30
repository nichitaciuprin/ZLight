@echo off
setlocal

set include=%~dp0include
set src=%~dp0src
set objs=%~dp0objs
set lib=%~dp0lib\libsyswin.a

if exist %objs% rmdir /S /Q %objs%
   mkdir %objs%

set flags=%flags% -Werror -Wall
set flags=%flags% -std=c99 -m64
@REM set flags=%flags% -g3 -Og
set flags=%flags% -g0 -O3 -D NDEBUG

gcc %flags% -c %src%\SysHelper.c  -o %objs%\SysHelper.o  -I%include%
gcc %flags% -c %src%\SysWindow.c  -o %objs%\SysWindow.o  -I%include%
gcc %flags% -c %src%\SysNet.c     -o %objs%\SysNet.o     -I%include%

if exist del %lib%

ar rcs %lib% %objs%\*.o

rmdir /S /Q %objs%
