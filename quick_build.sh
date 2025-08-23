#!/bin/bash

# Simple Xeno Engine Build Script (Minimal Dependencies)
# This script provides a basic build without external dependencies for testing

set -e

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

print_status() { echo -e "${BLUE}[INFO]${NC} $1"; }
print_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }
print_error() { echo -e "${RED}[ERROR]${NC} $1"; }

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"

print_status "Simple Xeno Engine build..."

# Create build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Try to build with existing configuration first
if [ -f "Makefile" ]; then
    print_status "Using existing configuration..."
    if make; then
        print_success "Build completed!"
        
        # Run tests if available
        if [ -f "./xeno_tests" ]; then
            print_status "Running tests..."
            ./xeno_tests
        fi
        
        # Run example if available
        if [ -f "./xeno_example_basic" ]; then
            print_status "Running example..."
            ./xeno_example_basic
        fi
        
        print_success "All done!"
    else
        print_error "Build failed"
        exit 1
    fi
else
    print_error "No existing build configuration found."
    print_error "Please run the full build script first: ./build.sh"
    print_error "Or configure manually: cd build && cmake .."
    exit 1
fi
