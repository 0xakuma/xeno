#include <vulkan/vulkan.h>

namespace xeno
{
    namespace vulkan
    {
        class VulkanRenderer
        {
        public:
            VulkanRenderer();
            ~VulkanRenderer();
            void initialize();
            void cleanup();

        private:
            VkInstance instance;
        };
    }
}