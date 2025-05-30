# TODO skip confirmation
# echo y | gdb -q -ex=run -ex=backtrace -ex=quit --args ./build/main
gdb -q -ex=run -ex=backtrace -ex=quit --args ./build/level
# ./build/main