#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace xeno
{
    class Surface
    {
    public:
        Surface(VkInstance instance, GLFWwindow *window);
        ~Surface();

    private:
        VkInstance instance;
        VkSurfaceKHR surface;
    };
}