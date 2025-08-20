#include "xeno-pal/xeno-pal.hpp"
#include <iostream>

int main()
{
    try
    {
        // Create a window
        xeno::pal::XenoWindow window(800, 600, "Input Handler Example");

        // Create input handler
        xeno::pal::InputHandler input(&window);

        // Optional: Set custom callbacks
        input.setKeyCallback([](int key, int scancode, int action, int mods)
                             {
            if (action == GLFW_PRESS)
            {
                std::cout << "Key pressed: " << key << std::endl;
            } });

        // Main loop
        while (!window.shouldClose())
        {
            // Update input state
            input.update();

            // Check for specific key inputs
            if (input.isKeyPressed(GLFW_KEY_ESCAPE))
            {
                std::cout << "Escape key pressed - exiting" << std::endl;
                break;
            }

            if (input.isKeyHeld(GLFW_KEY_W))
            {
                std::cout << "W key held" << std::endl;
            }

            // Check mouse input
            if (input.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
            {
                double x, y;
                input.getMousePosition(x, y);
                std::cout << "Left mouse button pressed at: " << x << ", " << y << std::endl;
            }

            // Check mouse movement
            double deltaX, deltaY;
            input.getCursorDelta(deltaX, deltaY);
            if (deltaX != 0.0 || deltaY != 0.0)
            {
                std::cout << "Mouse delta: " << deltaX << ", " << deltaY << std::endl;
            }

            // Check scroll wheel
            double scrollX, scrollY;
            input.getScrollOffset(scrollX, scrollY);
            if (scrollY != 0.0)
            {
                std::cout << "Scroll: " << scrollY << std::endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
