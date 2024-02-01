rmdir /Q /S build
rmdir /Q /S .cache
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -G Ninja -B build .
