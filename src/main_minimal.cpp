#include "engine/engine_minimal.hpp"
#include <iostream>

int main()
{
    xeno::Engine &engine = xeno::Engine::getInstance();
    try
    {
        engine.run();
    }
    catch (const std::exception &e)
    {
        std::cout << "An error occurred: " << e.what() << std::endl;
        // Handle exceptions appropriately (log them, clean up resources, etc.)
        return -1;
    }
    return 0;
}
