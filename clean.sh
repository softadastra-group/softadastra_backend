#!/bin/bash

echo "🧹 Cleaning build files..."

rm -rf build
rm -rf CMakeCache.txt CMakeFiles/ Makefile cmake_install.cmake

echo "✅ Build directory deleted."
