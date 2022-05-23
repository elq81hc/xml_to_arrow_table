#!/bin/bash
# rm -rf build/*
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake -T host=x64 -A x64

cmake --build build/.

