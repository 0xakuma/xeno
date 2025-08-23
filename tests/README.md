# Xeno Engine Testing System

This document describes how to build and test the Xeno Engine library.

## Building the Project

The project is now structured as a library (`xenoengine`) with separate executables for the main application, tests, and examples.

### Build Steps

1. Create a build directory:
```bash
mkdir -p build
cd build
```

2. Configure with CMake:
```bash
cmake ..
```

3. Build the project:
```bash
make
```

## Available Targets

After building, you'll have the following targets:

- **xenoengine** - The static library containing the engine code
- **xeno** - The main application executable
- **xeno_tests** - The test executable
- **xeno_example_basic** - A basic example application

## Running Tests

### Using CTest
```bash
cd build
ctest
```

### Running Tests Directly
```bash
cd build
./xeno_tests
```

## Running Examples

```bash
cd build
./xeno_example_basic
```

## Project Structure

```
xeno/
├── src/                    # Source code for the engine library
│   ├── engine/            # Core engine code
│   ├── xeno-pal/          # Platform abstraction layer
│   ├── xeno-renderer/     # Rendering subsystem
│   └── main.cpp           # Main application entry point
├── tests/                 # Test files
│   ├── test_main.cpp      # Test runner
│   └── test_engine.cpp    # Engine-specific tests
├── examples/              # Example applications
│   └── example_basic.cpp  # Basic usage example
└── CMakeLists.txt         # Build configuration
```

## Adding New Tests

To add new tests:

1. Create a new test file in the `tests/` directory
2. Implement your test functions
3. Add a forward declaration in `test_main.cpp`
4. Call your test function in the `main()` function

## Using the Engine Library

To use the Xeno Engine in your own applications:

1. Link against the `xenoengine` library
2. Include the appropriate headers from the `src/` directory
3. Use the singleton pattern to access the engine: `xeno::Engine::getInstance()`

Example:
```cpp
#include "engine/engine.hpp"

int main() {
    xeno::Engine& engine = xeno::Engine::getInstance();
    engine.run();
    return 0;
}
```
