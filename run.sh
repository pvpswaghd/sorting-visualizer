#!/bin/bash

if [ -d "./build" ]; then
    echo "'build' directory detected. Removing all contents..."
    rm -r "./build"
fi

cmake -B build
cmake --build build --config Release
mv ./build/_deps/sfml-src/extlibs/bin/x64/openal32.dll ./build/Release/openal32.dll

echo "Now go to ./build/Release/visualizer.exe to start the program!"
