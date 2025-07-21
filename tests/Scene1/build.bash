#!/bin/bash

flags="$flags -std=c99 -m64"
flags="$flags -g0 -O3 -D NDEBUG"

rm -rf ./build
mkdir  ./build

gcc ./main.c $src -o ./build/main $flags -I../.. -lX11 -lm
