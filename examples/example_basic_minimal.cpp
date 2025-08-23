#include "engine/engine_minimal.hpp"
#include <iostream>

int main()
{
    std::cout << "Xeno Engine Example Application (Minimal)" << std::endl;

    try
    {
        // Get the engine instance
        xeno::Engine &engine = xeno::Engine::getInstance();

        std::cout << "Engine initialized successfully!" << std::endl;

        // Call run method
        engine.run();

        std::cout << "Example application completed successfully!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in example application: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
