deps=./../../deps
build=./build
main=./main.cpp

# flags="$flags -Werror -Wall"
flags="$flags -std=c++17 -m64 -pthread"
flags="$flags -g3 -Og"
# flags="$flags -g0 -O3 -D NDEBUG"

lib="$lib -lX11 -lXi -lXfixes"

rm -rf build
mkdir  build

g++ $main $src -o $build/main $include $lib $flags