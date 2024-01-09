#!/bin/bash

# Create a build directory if it doesn't exist
cd ..
mkdir -p build
cd build

# Run CMake to configure the project
cmake ..

# Build the project
make

# Optionally, you can install the executable
# make install

# Return to the main project directory
cd ..
