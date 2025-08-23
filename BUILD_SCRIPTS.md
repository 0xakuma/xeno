# Xeno Engine Build Scripts

This document describes the available build scripts for the Xeno Engine project.

## Available Scripts

### 1. `build.sh` - Comprehensive Build Script

The main build script with full dependency support and comprehensive options.

**Usage:**
```bash
./build.sh [options]
```

**Options:**
- `-h, --help` - Show help message
- `-c, --clean` - Clean build directory before building
- `-t, --test` - Run tests after building
- `-r, --run` - Run the main application after building
- `-e, --example` - Run the basic example after building
- `-a, --all` - Build, test, and run example (equivalent to -t -e)
- `--debug` - Build in debug mode (default is Release)
- `--verbose` - Enable verbose build output

**Examples:**
```bash
./build.sh                  # Just build the project
./build.sh -c -t            # Clean build and run tests
./build.sh --clean --all    # Clean build, run tests and example
./build.sh --debug -t       # Debug build with tests
```

**Requirements:** vcpkg with glfw3, imgui, glm, and Vulkan SDK

### 2. `universal_build.sh` - Universal Build Script

A flexible build script that can work with both full and minimal configurations.

**Usage:**
```bash
./universal_build.sh [options]
```

**Options:**
- `-h, --help` - Show help message
- `-c, --clean` - Clean build directory
- `-m, --minimal` - Use minimal build (no external dependencies)
- `-t, --test` - Run tests after building
- `-e, --example` - Run example after building
- `-a, --all` - Run tests and example
- `--debug` - Debug build

**Examples:**
```bash
./universal_build.sh                    # Try full build, fallback to minimal
./universal_build.sh --minimal --all    # Minimal build with tests and example
./universal_build.sh --clean --all      # Clean full build with tests
```

**Features:**
- Automatically falls back to minimal build if dependencies are missing
- Temporarily swaps CMakeLists.txt files for minimal builds
- Restores original configuration after build

### 3. `quick_build.sh` - Quick Incremental Build

A simple script for quick rebuilds using existing configuration.

**Usage:**
```bash
./quick_build.sh
```

**Features:**
- Uses existing Makefile if available
- Runs tests and examples automatically
- Minimal output for quick iteration

**Requirements:** Must have existing build configuration

## Build Configurations

### Full Build (CMakeLists.txt)
- Includes all engine components
- Requires external dependencies: GLFW, ImGui, GLM, Vulkan
- Supports full rendering pipeline and platform abstraction

### Minimal Build (CMakeLists_minimal.txt)
- Self-contained with no external dependencies
- Uses simplified engine components
- Perfect for testing build system and basic functionality

## Dependencies

### Full Build Dependencies
```bash
# vcpkg packages
vcpkg install glfw3 imgui glm

# System requirements
- Vulkan SDK
- CMake 3.15+
- C++17 compiler
```

### Minimal Build Dependencies
```bash
# System requirements only
- CMake 3.15+
- C++17 compiler
- pthreads (included with most systems)
```

## Troubleshooting

### Common Issues

1. **vcpkg not found**
   - Solution: Use `--minimal` flag or install vcpkg and update CMakeLists.txt path

2. **Vulkan SDK missing**
   - Solution: Install Vulkan SDK or use minimal build

3. **ImGui/GLFW not found**
   - Solution: Install packages via vcpkg or use minimal build

### Build Script Selection Guide

- **Development with full features**: Use `build.sh`
- **Testing without dependencies**: Use `universal_build.sh --minimal`
- **Quick iteration**: Use `quick_build.sh`
- **CI/Automated builds**: Use `universal_build.sh` with appropriate flags

## Output

All scripts generate the following targets in the `build/` directory:
- `xenoengine` - Static library
- `xeno` - Main application
- `xeno_tests` - Test executable  
- `xeno_example_basic` - Example application

## Integration with VS Code

The build scripts complement the VS Code tasks defined in `.vscode/tasks.json`:
- Use tasks for IDE integration
- Use scripts for command-line builds and CI/CD
