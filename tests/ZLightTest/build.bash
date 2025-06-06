deps=./../../deps
build=./build
main=./main.cpp

# flags="$flags -Werror -Wall"
# flags="$flags -std=c++17 -m64 -pthread"
# flags="$flags -g3 -Og"

flags="$flags -std=c++17 -m64 -pthread"
flags="$flags -g0 -O3 -D NDEBUG"

# lib="$lib -L$deps/sys/lib -lsyshelperlin"
# lib="$lib -L$deps/sys/lib -lsyswindowlin"
# lib="$lib -L$deps/sys/lib -lsysnetlin"

src="$src $deps/sys/src/SysHelper.c"
src="$src $deps/sys/src/SysWindow.c"
src="$src $deps/sys/src/SysNet.c"

include="$include -I$deps/corelib"
include="$include -I$deps/shared"
include="$include -I$deps/sys/include"

lib="$lib -lX11 -lXi -lXfixes"

rm -rf build
mkdir  build

g++ $main $src -o $build/main $include $lib $flags
# g++ $main -o $build/main.asm $include $lib $flags -E
# g++ $main -o $build/main.asm $include $lib $flags -S
# objdump -d $build/main > $build/main.txt