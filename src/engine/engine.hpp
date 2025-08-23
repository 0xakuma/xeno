#include "xeno-pal.hpp"
#include "vulkan-renderer.hpp"

namespace xeno
{
    struct EngineConfig
    {
        int width;
        int height;
        const char *title;
    };

    class Engine
    {
    public:
        Engine(xeno::EngineConfig config = {800, 600, "Xeno Engine"});
        ~Engine();
        Engine(const Engine &) = delete;
        Engine &operator=(const Engine &) = delete;

        static Engine &getInstance();
        void run();

    private:
        xeno::pal::XenoWindow window;
        xeno::EngineConfig config;
        xeno::vulkan::VulkanRenderer renderer;
    };
}