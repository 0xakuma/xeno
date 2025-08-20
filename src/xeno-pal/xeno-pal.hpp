#pragma once;

#include <cstddef>
#include <vector>
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <thread>
#define GLFW_INCLUDE_VULKAN

namespace xeno
{
    namespace pal
    {
        // Forward declaration
        class XenoWindow;

        class InputHandler
        {
        public:
            InputHandler(XenoWindow *window);
            ~InputHandler();

            // Keyboard input
            bool isKeyPressed(int key) const;
            bool isKeyReleased(int key) const;
            bool isKeyHeld(int key) const;

            // Mouse input
            bool isMouseButtonPressed(int button) const;
            bool isMouseButtonReleased(int button) const;
            bool isMouseButtonHeld(int button) const;
            void getMousePosition(double &x, double &y) const;
            void getCursorDelta(double &deltaX, double &deltaY) const;

            // Scroll wheel
            void getScrollOffset(double &xOffset, double &yOffset) const;

            // Callbacks (optional for advanced usage)
            void setKeyCallback(std::function<void(int, int, int, int)> callback);
            void setMouseButtonCallback(std::function<void(int, int, int)> callback);
            void setCursorPosCallback(std::function<void(double, double)> callback);
            void setScrollCallback(std::function<void(double, double)> callback);

            // Update input state (call once per frame)
            void update();

        private:
            XenoWindow *m_window;
            GLFWwindow *m_glfwWindow;

            // Input state tracking
            std::unordered_map<int, bool> m_keyPressed;
            std::unordered_map<int, bool> m_keyReleased;
            std::unordered_map<int, bool> m_keyHeld;

            std::unordered_map<int, bool> m_mousePressed;
            std::unordered_map<int, bool> m_mouseReleased;
            std::unordered_map<int, bool> m_mouseHeld;

            double m_mouseX, m_mouseY;
            double m_lastMouseX, m_lastMouseY;
            double m_mouseDeltaX, m_mouseDeltaY;
            double m_scrollX, m_scrollY;

            // User callbacks
            std::function<void(int, int, int, int)> m_keyCallback;
            std::function<void(int, int, int)> m_mouseButtonCallback;
            std::function<void(double, double)> m_cursorPosCallback;
            std::function<void(double, double)> m_scrollCallback;

            // Static callback functions for GLFW
            static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
            static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
            static void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);
            static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

            // Helper methods
            void resetFrameState();
        };

        class File
        {
        public:
            File(const char *filename);
            ~File();

            void open();
            void close();
            std::vector<char> read(size_t size);
            bool isOpen() const;

        private:
            std::ifstream file;
            size_t fileSize;
            bool openFlag;
        };

        class XenoWindow
        {
        public:
            XenoWindow(int width, int height, std::string title);
            ~XenoWindow();
            GLFWwindow *getInstance() const { return window; }
            bool shouldClose() const { return glfwWindowShouldClose(window); }

        private:
            int width;
            int height;
            std::string title;

            GLFWwindow *window;
            void initWindow(int width, int height, const char *title);
        };
    }
    class Arena
    {
    public:
        Arena(size_t size);
        ~Arena();
        Arena(const Arena &) = delete;
        Arena &operator=(const Arena &) = delete;

        void *allocate(size_t size);

        template <class T>
        T *alloc(size_t count)
        {
            return static_cast<T *>(allocate(sizeof(T) * count));
        }

        void reset();

    private:
        char *m_memory;
        size_t m_size;
        size_t m_offset;
    };

    class ThreadPool
    {
    public:
        ThreadPool(size_t numThreads = std::thread::hardware_concurrency());
        ~ThreadPool();
        template <typename F>
        void enqueue(F &&f)
        {
            {
                std::unique_lock<std::mutex> lock(mutex_);
                tasks_.emplace(std::forward<F>(f));
                condition_.notify_one();
            }
        }

    private:
        std::vector<std::thread> threads_;
        std::queue<std::function<void()>> tasks_;
        std::mutex mutex_;
        std::condition_variable condition_;
        bool stopping_ = false;
    };
}
