# Xeno Input Handler

The `InputHandler` class provides a comprehensive input management system for keyboard and mouse input using GLFW. It tracks input states across frames and provides convenient methods for checking input events.

## Features

- **Keyboard Input**: Check for key press, release, and hold states
- **Mouse Input**: Handle mouse button presses, releases, and hold states
- **Mouse Movement**: Track cursor position and movement delta
- **Scroll Wheel**: Handle scroll wheel input
- **Custom Callbacks**: Set custom callbacks for advanced input handling
- **Frame-based State Management**: Properly handles input states across frames

## Basic Usage

```cpp
#include "xeno-pal/xeno-pal.hpp"

// Create window and input handler
xeno::pal::XenoWindow window(800, 600, "My Game");
xeno::pal::InputHandler input(&window);

// Main game loop
while (!window.shouldClose()) {
    // IMPORTANT: Call update() once per frame
    input.update();
    
    // Check keyboard input
    if (input.isKeyPressed(GLFW_KEY_SPACE)) {
        // Space was just pressed this frame
    }
    
    if (input.isKeyHeld(GLFW_KEY_W)) {
        // W key is being held down
    }
    
    if (input.isKeyReleased(GLFW_KEY_ESCAPE)) {
        // Escape was just released this frame
    }
    
    // Check mouse input
    if (input.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        double x, y;
        input.getMousePosition(x, y);
        // Handle left mouse button press at position (x, y)
    }
    
    // Get mouse movement
    double deltaX, deltaY;
    input.getCursorDelta(deltaX, deltaY);
    // Use deltaX, deltaY for camera rotation, etc.
    
    // Check scroll wheel
    double scrollX, scrollY;
    input.getScrollOffset(scrollX, scrollY);
    if (scrollY != 0.0) {
        // Handle scroll wheel input
    }
}
```

## Input State Types

### Keyboard States
- **`isKeyPressed(key)`**: Returns true only on the frame the key was pressed
- **`isKeyReleased(key)`**: Returns true only on the frame the key was released  
- **`isKeyHeld(key)`**: Returns true while the key is being held down

### Mouse States
- **`isMouseButtonPressed(button)`**: Returns true only on the frame the button was pressed
- **`isMouseButtonReleased(button)`**: Returns true only on the frame the button was released
- **`isMouseButtonHeld(button)`**: Returns true while the button is being held down

## Common GLFW Key Codes

```cpp
// Arrow keys
GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_LEFT, GLFW_KEY_RIGHT

// WASD keys
GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D

// Special keys
GLFW_KEY_SPACE, GLFW_KEY_ENTER, GLFW_KEY_ESCAPE, GLFW_KEY_TAB

// Function keys
GLFW_KEY_F1, GLFW_KEY_F2, ... GLFW_KEY_F12

// Mouse buttons
GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_MIDDLE
```

## Advanced Usage with Callbacks

```cpp
// Set custom key callback
input.setKeyCallback([](int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        std::cout << "Key " << key << " pressed" << std::endl;
    }
});

// Set custom mouse callback
input.setMouseButtonCallback([](int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        std::cout << "Left mouse button pressed" << std::endl;
    }
});

// Set cursor position callback
input.setCursorPosCallback([](double x, double y) {
    std::cout << "Mouse at: " << x << ", " << y << std::endl;
});

// Set scroll callback
input.setScrollCallback([](double xOffset, double yOffset) {
    std::cout << "Scroll: " << yOffset << std::endl;
});
```

## Important Notes

1. **Call `update()` once per frame**: This is crucial for proper input state management
2. **Input states are frame-based**: Pressed/Released states are only true for one frame
3. **Thread safety**: The InputHandler is not thread-safe, use from main thread only
4. **Window lifetime**: The InputHandler must not outlive the XenoWindow it's attached to

## Example: First Person Camera Controls

```cpp
void handleCameraInput(InputHandler& input, Camera& camera, float deltaTime) {
    const float moveSpeed = 5.0f;
    const float mouseSensitivity = 0.1f;
    
    // Movement
    if (input.isKeyHeld(GLFW_KEY_W)) {
        camera.moveForward(moveSpeed * deltaTime);
    }
    if (input.isKeyHeld(GLFW_KEY_S)) {
        camera.moveBackward(moveSpeed * deltaTime);
    }
    if (input.isKeyHeld(GLFW_KEY_A)) {
        camera.moveLeft(moveSpeed * deltaTime);
    }
    if (input.isKeyHeld(GLFW_KEY_D)) {
        camera.moveRight(moveSpeed * deltaTime);
    }
    
    // Mouse look
    double deltaX, deltaY;
    input.getCursorDelta(deltaX, deltaY);
    camera.rotate(deltaX * mouseSensitivity, deltaY * mouseSensitivity);
    
    // Zoom with scroll wheel
    double scrollX, scrollY;
    input.getScrollOffset(scrollX, scrollY);
    if (scrollY != 0.0) {
        camera.zoom(scrollY);
    }
}
```
