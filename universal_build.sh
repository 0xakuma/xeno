#!/bin/bash

# Universal Xeno Engine Build Script
# Works with both full and minimal dependency configurations

set -e

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

print_status() { echo -e "${BLUE}[INFO]${NC} $1"; }
print_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }
print_error() { echo -e "${RED}[ERROR]${NC} $1"; }
print_warning() { echo -e "${YELLOW}[WARNING]${NC} $1"; }

show_usage() {
    echo "Usage: $0 [options]"
    echo ""
    echo "Options:"
    echo "  -h, --help       Show this help"
    echo "  -c, --clean      Clean build directory"
    echo "  -m, --minimal    Use minimal build (no external deps)"
    echo "  -t, --test       Run tests after building"
    echo "  -e, --example    Run example after building"
    echo "  -a, --all        Run tests and example"
    echo "  --debug          Debug build"
    echo ""
}

# Defaults
CLEAN_BUILD=false
USE_MINIMAL=false
RUN_TESTS=false
RUN_EXAMPLE=false
BUILD_TYPE="Release"

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help) show_usage; exit 0 ;;
        -c|--clean) CLEAN_BUILD=true; shift ;;
        -m|--minimal) USE_MINIMAL=true; shift ;;
        -t|--test) RUN_TESTS=true; shift ;;
        -e|--example) RUN_EXAMPLE=true; shift ;;
        -a|--all) RUN_TESTS=true; RUN_EXAMPLE=true; shift ;;
        --debug) BUILD_TYPE="Debug"; shift ;;
        *) print_error "Unknown option: $1"; show_usage; exit 1 ;;
    esac
done

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"

print_status "Starting Xeno Engine build..."

# Clean if requested
if [ "$CLEAN_BUILD" = true ]; then
    print_status "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
fi

# Create build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure
print_status "Configuring with CMake..."
if [ "$USE_MINIMAL" = true ]; then
    print_status "Using minimal build configuration (no external dependencies)"
    # Use minimal CMakeLists.txt by copying it to the expected location
    cp ../CMakeLists.txt ../CMakeLists.txt.backup 2>/dev/null || true
    cp ../CMakeLists_minimal.txt ../CMakeLists.txt
    CMAKE_ARGS="-DCMAKE_BUILD_TYPE=$BUILD_TYPE"
else
    print_status "Using full build configuration"
    CMAKE_ARGS="-DCMAKE_BUILD_TYPE=$BUILD_TYPE"
fi

if cmake $CMAKE_ARGS ..; then
    print_success "Configuration successful"
else
    if [ "$USE_MINIMAL" = false ]; then
        print_warning "Full build failed, trying minimal build..."
        cp ../CMakeLists_minimal.txt ./CMakeLists.txt
        if cmake $CMAKE_ARGS .; then
            print_success "Minimal configuration successful"
            USE_MINIMAL=true
        else
            print_error "Both configurations failed"
            exit 1
        fi
    else
        print_error "Configuration failed"
        exit 1
    fi
fi

# Build
print_status "Building..."
if make; then
    print_success "Build completed!"
else
    print_error "Build failed"
    exit 1
fi

# Run tests
if [ "$RUN_TESTS" = true ] && [ -f "./xeno_tests" ]; then
    print_status "Running tests..."
    if ./xeno_tests; then
        print_success "Tests passed!"
    else
        print_error "Tests failed"
        exit 1
    fi
fi

# Run example
if [ "$RUN_EXAMPLE" = true ] && [ -f "./xeno_example_basic" ]; then
    print_status "Running example..."
    ./xeno_example_basic
fi

print_success "Build script completed!"

# Restore original CMakeLists.txt if we used minimal
if [ "$USE_MINIMAL" = true ] && [ -f "../CMakeLists.txt.backup" ]; then
    print_status "Restoring original CMakeLists.txt..."
    mv ../CMakeLists.txt.backup ../CMakeLists.txt
fi

print_status "Available executables in build/:"
ls -la | grep -E "(xeno|test)" | grep -v ".o" | grep -v ".dir" || true
