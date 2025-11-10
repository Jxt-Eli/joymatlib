#!/bin/bash

echo "Building Matrix Library Examples..."

# Create build directory
mkdir -p build
cd build

# Build the comprehensive example
echo "Building comprehensive example..."
mkdir -p example_usage
cd example_usage
cmake ../../example_usage
make
cd ..

# Build the simple example
echo "Building simple example..."
mkdir -p simple_example
cd simple_example
cmake ../../simple_example
make
cd ..

echo "Build complete!"
echo ""
echo "To run the comprehensive example:"
echo "  cd build/example_usage && ./example_app"
echo ""
echo "To run the simple example:"
echo "  cd build/simple_example && ./simple_example" 