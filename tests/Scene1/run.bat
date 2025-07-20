@echo off
setlocal

@REM echo y | gdb -q -ex=run -ex=backtrace -ex=quit --args build\main.exe
%~dp0build\main.exe
