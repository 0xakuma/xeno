#include "engine.hpp"

namespace xeno
{
    Engine::Engine() : window(800, 600, "Xeno Engine")
    {
    }
    Engine::~Engine()
    {
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
