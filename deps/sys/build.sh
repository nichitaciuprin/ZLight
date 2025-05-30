include="./include"
src="./src"
objs="./objs"

flags="$flags -Werror -Wall"
# flags="$flags -std=gnu99 -m64"
# flags="$flags -std=c99 -m64"
flags="$flags -std=c++17 -m64"
# flags="$flags -g3 -Og"
flags="$flags -g0 -O3 -D NDEBUG"

# libname="libsyshelperlin.a"
# lib=./lib/$libname
# echo building $libname
# rm -rf $objs
# rm -rf $lib
# mkdir $objs
# gcc $flags -c $src/SysHelper.c -o $objs/SysHelper.o -I$include
# ar -x /usr/lib/x86_64-linux-gnu/libX11.a --output=$objs
# ar -x /usr/lib/x86_64-linux-gnu/libdl.a  --output=$objs
# ar -x /usr/lib/x86_64-linux-gnu/libxcb.a --output=$objs
# ar rcs $lib $objs/*.o
# rm -rf $objs

libname="libsyswindowlin.a"
lib=./lib/$libname
echo building $libname
rm -rf $objs
rm -rf $lib
mkdir $objs
g++ $flags -c $src/SysWindow.c -o $objs/SysWindow.o -I$include
# ar -x /usr/lib/x86_64-linux-gnu/libX11.a --output=$objs
# ar -x /usr/lib/x86_64-linux-gnu/libdl.a  --output=$objs
# ar -x /usr/lib/x86_64-linux-gnu/libxcb.a --output=$objs
ar rcs $lib $objs/*.o
rm -rf $objs

# libname="libsysnetlin.a"
# lib=./lib/$libname
# echo building $libname
# rm -rf $objs
# rm -rf $lib
# mkdir $objs
# gcc $flags -c $src/SysNet.c -o $objs/SysNet.o -I$include
# ar -x /usr/lib/x86_64-linux-gnu/libX11.a --output=$objs
# ar -x /usr/lib/x86_64-linux-gnu/libdl.a  --output=$objs
# ar -x /usr/lib/x86_64-linux-gnu/libxcb.a --output=$objs
# ar rcs $lib $objs/*.o
# rm -rf $objs
