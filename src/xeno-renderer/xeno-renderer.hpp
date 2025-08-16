#pragma once

#include <vulkan/vulkan.h>
#include "surface.hpp"
#include "xeno-window.hpp"
#include "physical-device.hpp"

namespace xeno
{

    class XenoRenderer
    {
    public:
        XenoRenderer();
        ~XenoRenderer();

        void createLogicalDevice();
        void createSwapChain();
        void createImageViews();
        void createRenderPass();
        void createFramebuffers();
        void createCommandPool();
        void createCommandBuffers();
        void createSyncObjects();
        void drawFrame();
        void cleanup();

    private:
        Surface *surface;
        VkInstance instance;
        XenoWindow *window;
        PhysicalDevice *physicalDevice;

        void createInstance();
        void createSurface();
        void pickPhysicalDevice();
        void initVulkan();
    };

};
