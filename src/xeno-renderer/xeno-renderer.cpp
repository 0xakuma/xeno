#include <xeno-renderer/xeno-renderer.hpp>
#include <iostream>
#include <GLFW/glfw3.h>

namespace xeno
{
    XenoRenderer::XenoRenderer()
    {
        initVulkan();
    }

    XenoRenderer::~XenoRenderer()
    {
        // Destructor implementation
        std::cout << "XenoRenderer destroyed!" << std::endl;
    }
    void XenoRenderer::createInstance()
    {

        if (!glfwVulkanSupported())
        {
            throw std::runtime_error("GLFW: Vulkan not supported!");
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Vulkan Terrain";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // Get required extensions
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        if (glfwExtensions == nullptr)
        {
            throw std::runtime_error("Failed to get required GLFW extensions!");
        }

        // Add extensions to vector for easier manipulation
        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        // Add portability extension for macOS (MoltenVK)
        extensions.push_back("VK_KHR_portability_enumeration");

        // Print required extensions for debugging
        std::cout << "Required extensions:" << std::endl;
        for (const auto &ext : extensions)
        {
            std::cout << "  " << ext << std::endl;
        }

        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();
        createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        createInfo.enabledLayerCount = 0;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS)
        {
            std::cerr << "Vulkan instance creation failed with error code: " << result << std::endl;
            throw std::runtime_error("failed to create instance!");
        }

        std::cout << "✅ Vulkan instance created successfully!" << std::endl;
    }

    void XenoRenderer::createSurface()
    {
        surface = new Surface(instance, window->getInstance());
    }

    void XenoRenderer::pickPhysicalDevice()
    {
        physicalDevice = new PhysicalDevice(instance);
        if (!physicalDevice)
        {
            throw std::runtime_error("Failed to pick a physical device!");
        }
        std::cout << "Physical device picked successfully!" << std::endl;
    }

    void XenoRenderer::initVulkan()
    {
        createInstance();
        createSurface();
        pickPhysicalDevice();
    }
}
