#include "vulkan-renderer.hpp"
#include <iostream>
#include <string>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace xeno
{
    namespace vulkan
    {
        VulkanRenderer::VulkanRenderer()
        {
            // Don't initialize immediately - let the engine control when to initialize
        }

        VulkanRenderer::~VulkanRenderer()
        {
        }

        void VulkanRenderer::initialize()
        {
            uint32_t extension_count = 0;
            const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&extension_count);

            std::cout << "Required GLFW extensions (" << extension_count << "):" << std::endl;
            for (uint32_t i = 0; i < extension_count; i++)
            {
                std::cout << "   ✓ " << glfwExtensions[i] << std::endl;
            }

            // Create a vector to hold all required extensions
            std::vector<const char *> extensions(glfwExtensions, glfwExtensions + extension_count);

            // Add portability enumeration extension for macOS/MoltenVK compatibility
            extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

            std::cout << "Total extensions to enable: " << extensions.size() << std::endl;

            uint32_t instanceExtensionCount = 0;
            vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, nullptr);
            std::cout << "Available Vulkan instance extensions: " << instanceExtensionCount << std::endl;

            // Check if Vulkan is available
            uint32_t vulkanVersion = 0;
            VkResult result = vkEnumerateInstanceVersion(&vulkanVersion);
            if (result != VK_SUCCESS)
            {
                throw std::runtime_error("Failed to query Vulkan version");
            }
            std::cout << "Vulkan version: " << VK_VERSION_MAJOR(vulkanVersion) << "."
                      << VK_VERSION_MINOR(vulkanVersion) << "."
                      << VK_VERSION_PATCH(vulkanVersion) << std::endl;

            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "Xeno Engine";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "Xeno Engine";
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            // Use Vulkan 1.1 which is well supported on macOS/MoltenVK
            appInfo.apiVersion = VK_API_VERSION_1_1;

            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;
            createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
            createInfo.ppEnabledExtensionNames = extensions.data();
            createInfo.enabledLayerCount = 0;
            // Enable portability subset for MoltenVK
            createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

            VkResult createResult = vkCreateInstance(&createInfo, nullptr, &instance);
            if (createResult != VK_SUCCESS)
            {
                std::string errorMsg = "Failed to create Vulkan instance. Error code: " + std::to_string(createResult);
                switch (createResult)
                {
                case VK_ERROR_OUT_OF_HOST_MEMORY:
                    errorMsg += " (VK_ERROR_OUT_OF_HOST_MEMORY)";
                    break;
                case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                    errorMsg += " (VK_ERROR_OUT_OF_DEVICE_MEMORY)";
                    break;
                case VK_ERROR_INITIALIZATION_FAILED:
                    errorMsg += " (VK_ERROR_INITIALIZATION_FAILED)";
                    break;
                case VK_ERROR_LAYER_NOT_PRESENT:
                    errorMsg += " (VK_ERROR_LAYER_NOT_PRESENT)";
                    break;
                case VK_ERROR_EXTENSION_NOT_PRESENT:
                    errorMsg += " (VK_ERROR_EXTENSION_NOT_PRESENT)";
                    break;
                case VK_ERROR_INCOMPATIBLE_DRIVER:
                    errorMsg += " (VK_ERROR_INCOMPATIBLE_DRIVER)";
                    break;
                default:
                    errorMsg += " (Unknown error)";
                    break;
                }
                throw std::runtime_error(errorMsg);
            }

            std::cout << "Vulkan instance created successfully!" << std::endl;
        }

        void VulkanRenderer::cleanup()
        {
            if (instance)
            {
                vkDestroyInstance(instance, nullptr);
                instance = VK_NULL_HANDLE;
            }
        }
    }
}