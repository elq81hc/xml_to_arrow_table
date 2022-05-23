#!/bin/bash
rm -rf build/*
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/IDE/vcpkg/scripts/buildsystems/vcpkg.cmake

MSBuild.exe build/xml_to_arrow_table.sln

