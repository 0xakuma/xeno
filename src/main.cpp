#include "engine/engine.hpp"
#include <iostream>

int main()
{
    xeno::EngineConfig config{800, 600, "Xeno Engine"};
    xeno::Engine engine(config);
    try
    {
        std::cout << "Starting Xeno Engine..." << std::endl;
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