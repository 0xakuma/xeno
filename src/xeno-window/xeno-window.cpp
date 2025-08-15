#include "xeno-window.hpp"

namespace xeno
{
    XenoWindow::XenoWindow(int width, int height, std::string title)
        : width(width), height(height), title(title)
    {
        initWindow(width, height, title.c_str());
    }

    XenoWindow::~XenoWindow()
    {
        if (window)
        {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
    }

    void XenoWindow::initWindow(int width, int height, const char *title)
    {
        if (!glfwInit())
        {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
    }
}