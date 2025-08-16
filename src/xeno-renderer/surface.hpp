#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

class Surface
{
public:
    Surface(VkInstance instance, GLFWwindow *window);

private:
    VkInstance instance;
    VkSurfaceKHR surface;
};