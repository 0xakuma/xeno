#include "xeno-pal.hpp"
#include <stdexcept>

namespace xeno
{
    namespace pal
    {
        InputHandler::InputHandler(XenoWindow *window)
            : m_window(window), m_glfwWindow(window->getInstance()), m_mouseX(0.0), m_mouseY(0.0), m_lastMouseX(0.0), m_lastMouseY(0.0), m_mouseDeltaX(0.0), m_mouseDeltaY(0.0), m_scrollX(0.0), m_scrollY(0.0)
        {
            if (!m_glfwWindow)
            {
                throw std::runtime_error("Invalid GLFW window provided to InputHandler");
            }

            // Set this instance as user pointer for GLFW callbacks
            glfwSetWindowUserPointer(m_glfwWindow, this);

            // Set GLFW callbacks
            glfwSetKeyCallback(m_glfwWindow, InputHandler::keyCallback);
            glfwSetMouseButtonCallback(m_glfwWindow, InputHandler::mouseButtonCallback);
            glfwSetCursorPosCallback(m_glfwWindow, InputHandler::cursorPosCallback);
            glfwSetScrollCallback(m_glfwWindow, InputHandler::scrollCallback);

            // Get initial mouse position
            glfwGetCursorPos(m_glfwWindow, &m_mouseX, &m_mouseY);
            m_lastMouseX = m_mouseX;
            m_lastMouseY = m_mouseY;
        }

        InputHandler::~InputHandler()
        {
            // Reset GLFW callbacks to null
            if (m_glfwWindow)
            {
                glfwSetKeyCallback(m_glfwWindow, nullptr);
                glfwSetMouseButtonCallback(m_glfwWindow, nullptr);
                glfwSetCursorPosCallback(m_glfwWindow, nullptr);
                glfwSetScrollCallback(m_glfwWindow, nullptr);
                glfwSetWindowUserPointer(m_glfwWindow, nullptr);
            }
        }

        bool InputHandler::isKeyPressed(int key) const
        {
            auto it = m_keyPressed.find(key);
            return it != m_keyPressed.end() && it->second;
        }

        bool InputHandler::isKeyReleased(int key) const
        {
            auto it = m_keyReleased.find(key);
            return it != m_keyReleased.end() && it->second;
        }

        bool InputHandler::isKeyHeld(int key) const
        {
            auto it = m_keyHeld.find(key);
            return it != m_keyHeld.end() && it->second;
        }

        bool InputHandler::isMouseButtonPressed(int button) const
        {
            auto it = m_mousePressed.find(button);
            return it != m_mousePressed.end() && it->second;
        }

        bool InputHandler::isMouseButtonReleased(int button) const
        {
            auto it = m_mouseReleased.find(button);
            return it != m_mouseReleased.end() && it->second;
        }

        bool InputHandler::isMouseButtonHeld(int button) const
        {
            auto it = m_mouseHeld.find(button);
            return it != m_mouseHeld.end() && it->second;
        }

        void InputHandler::getMousePosition(double &x, double &y) const
        {
            x = m_mouseX;
            y = m_mouseY;
        }

        void InputHandler::getCursorDelta(double &deltaX, double &deltaY) const
        {
            deltaX = m_mouseDeltaX;
            deltaY = m_mouseDeltaY;
        }

        void InputHandler::getScrollOffset(double &xOffset, double &yOffset) const
        {
            xOffset = m_scrollX;
            yOffset = m_scrollY;
        }

        void InputHandler::setKeyCallback(std::function<void(int, int, int, int)> callback)
        {
            m_keyCallback = callback;
        }

        void InputHandler::setMouseButtonCallback(std::function<void(int, int, int)> callback)
        {
            m_mouseButtonCallback = callback;
        }

        void InputHandler::setCursorPosCallback(std::function<void(double, double)> callback)
        {
            m_cursorPosCallback = callback;
        }

        void InputHandler::setScrollCallback(std::function<void(double, double)> callback)
        {
            m_scrollCallback = callback;
        }

        void InputHandler::update()
        {
            // Reset frame-specific states
            resetFrameState();

            // Poll GLFW events
            glfwPollEvents();

            // Update mouse delta
            double currentMouseX, currentMouseY;
            glfwGetCursorPos(m_glfwWindow, &currentMouseX, &currentMouseY);

            m_mouseDeltaX = currentMouseX - m_lastMouseX;
            m_mouseDeltaY = currentMouseY - m_lastMouseY;

            m_lastMouseX = currentMouseX;
            m_lastMouseY = currentMouseY;
            m_mouseX = currentMouseX;
            m_mouseY = currentMouseY;

            // Reset scroll offset (it's only valid for one frame)
            m_scrollX = 0.0;
            m_scrollY = 0.0;
        }

        void InputHandler::resetFrameState()
        {
            // Clear pressed/released states (these are only valid for one frame)
            for (auto &pair : m_keyPressed)
                pair.second = false;
            for (auto &pair : m_keyReleased)
                pair.second = false;
            for (auto &pair : m_mousePressed)
                pair.second = false;
            for (auto &pair : m_mouseReleased)
                pair.second = false;
        }

        // Static callback functions
        void InputHandler::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            InputHandler *handler = static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
            if (!handler)
                return;

            if (action == GLFW_PRESS)
            {
                handler->m_keyPressed[key] = true;
                handler->m_keyHeld[key] = true;
            }
            else if (action == GLFW_RELEASE)
            {
                handler->m_keyReleased[key] = true;
                handler->m_keyHeld[key] = false;
            }

            // Call user callback if set
            if (handler->m_keyCallback)
            {
                handler->m_keyCallback(key, scancode, action, mods);
            }
        }

        void InputHandler::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
        {
            InputHandler *handler = static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
            if (!handler)
                return;

            if (action == GLFW_PRESS)
            {
                handler->m_mousePressed[button] = true;
                handler->m_mouseHeld[button] = true;
            }
            else if (action == GLFW_RELEASE)
            {
                handler->m_mouseReleased[button] = true;
                handler->m_mouseHeld[button] = false;
            }

            // Call user callback if set
            if (handler->m_mouseButtonCallback)
            {
                handler->m_mouseButtonCallback(button, action, mods);
            }
        }

        void InputHandler::cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
        {
            InputHandler *handler = static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
            if (!handler)
                return;

            handler->m_mouseX = xpos;
            handler->m_mouseY = ypos;

            // Call user callback if set
            if (handler->m_cursorPosCallback)
            {
                handler->m_cursorPosCallback(xpos, ypos);
            }
        }

        void InputHandler::scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
        {
            InputHandler *handler = static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
            if (!handler)
                return;

            handler->m_scrollX = xoffset;
            handler->m_scrollY = yoffset;

            // Call user callback if set
            if (handler->m_scrollCallback)
            {
                handler->m_scrollCallback(xoffset, yoffset);
            }
        }
    }
}
