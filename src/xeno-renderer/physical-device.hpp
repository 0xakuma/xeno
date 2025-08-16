#pragma once

#include <vulkan/vulkan.h>

class PhysicalDevice
{
public:
    PhysicalDevice(VkInstance instance);

private:
    VkPhysicalDevice physicalDevice;
};