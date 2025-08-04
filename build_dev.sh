#!/bin/bash

echo "🧪 Building in DEVELOPMENT mode..."

# Clean and create fresh build directory
rm -rf build
mkdir build && cd build

# Configure CMake with development flags (with tests)
cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_TESTS=ON

# Compile using all CPU cores
make -j$(nproc)

echo "✅ Development build complete. Binaries are in ./bin/"

# (Optional) Run tests automatically
echo "🔍 Running tests..."
ctest --output-on-failure
