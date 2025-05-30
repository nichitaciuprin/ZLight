@echo off
setlocal

set include=%~dp0include
set src=%~dp0src
set objs=%~dp0objs

set mingwpaths=%~dp0mingwpaths
where gcc > %mingwpaths%
set /p mingw=<%mingwpaths%
del %mingwpaths%
set mingw=%mingw%\..\..
set mingwlib=%mingw%\x86_64-w64-mingw32\lib

set flags=%flags% -Werror -Wall
set flags=%flags% -std=c99 -m64
@REM set flags=%flags% -g3 -Og
set flags=%flags% -g0 -O3 -D NDEBUG

set libname=libsyswindowwin.a
set lib=%~dp0lib\%libname%
echo building %libname%
if exist %objs% rmdir /S /Q %objs%
   mkdir %objs%
if exist del %lib%
gcc %flags% -c %src%\SysWindow.c -o %objs%\SysWindow.o -I%include%
ar -x %mingwlib%\libgdi32.a  --output=%objs%
ar rcs %lib% %objs%\*.o
rmdir /S /Q %objs%
