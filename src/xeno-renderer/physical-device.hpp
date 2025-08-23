#pragma once

#include <vulkan/vulkan.h>

namespace xeno
{
    class PhysicalDevice
    {
    public:
        PhysicalDevice(VkInstance instance);

    private:
        VkPhysicalDevice physicalDevice;
    };
}