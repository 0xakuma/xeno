# Xeno Engine

A C++ game engine built with Vulkan, designed as a modular library with a comprehensive testing system.

## Project Structure

The Xeno Engine is now structured as a library (`xenoengine`) with the following components:

- **Core Engine** (`src/engine/`) - Main engine singleton and core functionality
- **Platform Abstraction Layer** (`src/xeno-pal/`) - Cross-platform abstractions for windowing, input, memory management, and threading
- **Renderer** (`src/xeno-renderer/`) - Vulkan-based rendering system
- **Tests** (`tests/`) - Comprehensive test suite
- **Examples** (`examples/`) - Example applications demonstrating engine usage

## Building

### Prerequisites

- CMake 3.15 or higher
- C++17 compatible compiler
- vcpkg package manager (configured in CMakeLists.txt)
- Vulkan SDK

### Build Steps

1. Create and enter build directory:
```bash
mkdir build && cd build
```

2. Configure with CMake:
```bash
cmake ..
```

3. Build the project:
```bash
make
```

**Or use the automated build scripts:**

- **Full build**: `./build.sh --clean --all`
- **Minimal build** (no external deps): `./universal_build.sh --minimal --all`  
- **Quick rebuild**: `./quick_build.sh`

See [BUILD_SCRIPTS.md](BUILD_SCRIPTS.md) for detailed script documentation.

Or use the VS Code tasks:
- **Configure Xeno Engine** - Configure CMake
- **Build Xeno Engine** - Build all targets
- **Run Tests** - Execute the test suite
- **Run Example Basic** - Run the basic example

## Available Targets

After building, the following executables will be available in the `build/` directory:

- **xenoengine** - Static library containing the engine
- **xeno** - Main application executable
- **xeno_tests** - Test executable
- **xeno_example_basic** - Basic example application

## Testing

Run tests using either:

```bash
# Using CTest
cd build && ctest

# Direct execution
cd build && ./xeno_tests
```

Tests verify:
- Engine singleton pattern
- Basic instantiation
- Core functionality

## Using as a Library

To use Xeno Engine in your own projects:

1. Link against the `xenoengine` static library
2. Include headers from `src/` directory
3. Use the singleton pattern to access the engine:

```cpp
#include "engine/engine.hpp"

int main() {
    xeno::Engine& engine = xeno::Engine::getInstance();
    engine.run();
    return 0;
}
```

## Dependencies

- **GLFW** - Window management
- **Vulkan** - Graphics API
- **GLM** - Mathematics library
- **Dear ImGui** - Immediate mode GUI

All dependencies are managed through vcpkg.

## Development

The engine uses a modular architecture with clear separation between:
- Core engine functionality
- Platform-specific code (PAL)
- Rendering subsystem
- Example applications

Add new features by extending the appropriate module and adding corresponding tests.