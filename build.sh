#!/bin/bash

# Xeno Engine Build Script
# This script configures, builds, and optionally tests the Xeno Engine

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to show usage
show_usage() {
    echo "Usage: $0 [options]"
    echo ""
    echo "Options:"
    echo "  -h, --help          Show this help message"
    echo "  -c, --clean         Clean build directory before building"
    echo "  -t, --test          Run tests after building"
    echo "  -r, --run           Run the main application after building"
    echo "  -e, --example       Run the basic example after building"
    echo "  -a, --all           Build, test, and run example (equivalent to -t -e)"
    echo "  --debug             Build in debug mode (default is Release)"
    echo "  --verbose           Enable verbose build output"
    echo ""
    echo "Examples:"
    echo "  $0                  # Just build the project"
    echo "  $0 -c -t            # Clean build and run tests"
    echo "  $0 --clean --all    # Clean build, run tests and example"
    echo "  $0 --debug -t       # Debug build with tests"
}

# Default options
CLEAN_BUILD=false
RUN_TESTS=false
RUN_MAIN=false
RUN_EXAMPLE=false
BUILD_TYPE="Release"
VERBOSE=false

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_usage
            exit 0
            ;;
        -c|--clean)
            CLEAN_BUILD=true
            shift
            ;;
        -t|--test)
            RUN_TESTS=true
            shift
            ;;
        -r|--run)
            RUN_MAIN=true
            shift
            ;;
        -e|--example)
            RUN_EXAMPLE=true
            shift
            ;;
        -a|--all)
            RUN_TESTS=true
            RUN_EXAMPLE=true
            shift
            ;;
        --debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        --verbose)
            VERBOSE=true
            shift
            ;;
        *)
            print_error "Unknown option: $1"
            show_usage
            exit 1
            ;;
    esac
done

# Get script directory (where this script is located)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"

print_status "Starting Xeno Engine build process..."
print_status "Build type: $BUILD_TYPE"
print_status "Build directory: $BUILD_DIR"

# Clean build directory if requested
if [ "$CLEAN_BUILD" = true ]; then
    print_status "Cleaning build directory..."
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
        print_success "Build directory cleaned"
    else
        print_warning "Build directory doesn't exist, nothing to clean"
    fi
fi

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    print_status "Creating build directory..."
    mkdir -p "$BUILD_DIR"
fi

# Navigate to build directory
cd "$BUILD_DIR"

# Configure with CMake
print_status "Configuring with CMake..."
CMAKE_ARGS="-DCMAKE_BUILD_TYPE=$BUILD_TYPE"

if [ "$VERBOSE" = true ]; then
    CMAKE_ARGS="$CMAKE_ARGS -DCMAKE_VERBOSE_MAKEFILE=ON"
fi

# Check if vcpkg toolchain file exists
VCPKG_TOOLCHAIN="/Users/akuma/dev/vcpkg/scripts/buildsystems/vcpkg.cmake"
if [ ! -f "$VCPKG_TOOLCHAIN" ]; then
    print_warning "vcpkg toolchain not found at $VCPKG_TOOLCHAIN"
    print_warning "You may need to install dependencies manually or adjust the path in CMakeLists.txt"
fi

if cmake .. $CMAKE_ARGS; then
    print_success "CMake configuration completed"
else
    print_error "CMake configuration failed"
    print_error "This might be due to missing dependencies. Please ensure:"
    print_error "1. vcpkg is installed and configured"
    print_error "2. Required packages are installed: glfw3, imgui, glm, vulkan"
    print_error "3. Vulkan SDK is installed"
    exit 1
fi

# Build the project
print_status "Building Xeno Engine..."
if [ "$VERBOSE" = true ]; then
    MAKE_ARGS="VERBOSE=1"
else
    MAKE_ARGS=""
fi

if make $MAKE_ARGS; then
    print_success "Build completed successfully!"
else
    print_error "Build failed"
    exit 1
fi

# List built targets
print_status "Built targets:"
echo "  - xenoengine (static library)"
echo "  - xeno (main application)"
echo "  - xeno_tests (test executable)"
echo "  - xeno_example_basic (basic example)"

# Run tests if requested
if [ "$RUN_TESTS" = true ]; then
    print_status "Running tests..."
    if ctest --output-on-failure; then
        print_success "All tests passed!"
    else
        print_error "Some tests failed"
        exit 1
    fi
fi

# Run main application if requested
if [ "$RUN_MAIN" = true ]; then
    print_status "Running main application..."
    if [ -f "./xeno" ]; then
        ./xeno
    else
        print_error "Main executable not found"
        exit 1
    fi
fi

# Run example if requested
if [ "$RUN_EXAMPLE" = true ]; then
    print_status "Running basic example..."
    if [ -f "./xeno_example_basic" ]; then
        ./xeno_example_basic
    else
        print_error "Example executable not found"
        exit 1
    fi
fi

print_success "Build script completed successfully!"
print_status "You can now run:"
print_status "  ./build/xeno                 # Main application"
print_status "  ./build/xeno_tests           # Tests"
print_status "  ./build/xeno_example_basic   # Basic example"
print_status "  cd build && ctest            # Run tests via CTest"
