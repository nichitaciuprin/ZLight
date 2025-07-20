#!/bin/bash

flags="$flags -std=c++17 -m64"
flags="$flags -g0 -O3 -D NDEBUG"

rm -rf ./build
mkdir  ./build

g++ ./main.cpp $src -o ./build/main $flags -I../.. -lX11
