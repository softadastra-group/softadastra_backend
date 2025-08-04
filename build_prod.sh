#!/bin/bash

echo "🚀 Building in PRODUCTION mode..."

# Clean and create fresh build directory
rm -rf build
mkdir build && cd build

# Configure CMake with production flags
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_TESTS=OFF \
    -DENABLE_OPTIMIZATION=ON

# Compile using all CPU cores
make -j$(nproc)

echo "✅ Production build complete. Binary available in ./bin/"
