#!/bin/bash

deps=./../../deps
build=./build
main=./main.cpp

# flags="$flags -Werror -Wall"
flags="$flags -std=c++17 -m64"
flags="$flags -g0 -O3 -D NDEBUG"

src="$src $deps/sys/src/SysHelper.c"
src="$src $deps/sys/src/SysWindow.c"
src="$src $deps/sys/src/SysNet.c"

include="$include -I$deps/sys/include"
include="$include -I$deps/corelib"
include="$include -I$deps/zlight"
include="$include -I$deps/shared"

lib="$lib -lX11"

rm -rf ./build
mkdir  ./build

g++ ./main.cpp $src -o ./build/main $include $lib $flags
