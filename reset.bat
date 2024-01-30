rmdir /Q /S build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -G Ninja -B build .
