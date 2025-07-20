#!/bin/bash

root=./../..
deps=./../../deps
build=./build
main=./main.cpp

# flags="$flags -std=c++17 -m64 -pthread"
# flags="$flags -g3 -Og"

flags="$flags -std=c++17 -m64"
flags="$flags -g0 -O3 -D NDEBUG"

include="$include -I$deps/corelib"
include="$include -I$deps/shared"
include="$include -I$deps/sys/include"
include="$include -I$root"

lib="$lib -lX11"

rm -rf build
mkdir  build

g++ $main $src -o $build/main $include $lib $flags
