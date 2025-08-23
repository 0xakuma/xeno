#include "engine.hpp"

namespace xeno
{
    Engine::Engine(EngineConfig config) : window(config.width, config.height, config.title), config(config)
    {
        // Initialize renderer after window is created and GLFW is set up
        renderer.initialize();
    }
    Engine::~Engine()
    {
        renderer.cleanup();
    }

    Engine &Engine::getInstance()
    {
        static Engine instance;
        return instance;
    }

    void Engine::run()
    {
        while (!window.shouldClose())
        {
            window.pollEvents();
        }
    }
}
