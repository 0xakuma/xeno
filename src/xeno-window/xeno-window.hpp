#include <GLFW/glfw3.h>
#include <string>

#define GLFW_INCLUDE_VULKAN

namespace xeno
{
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