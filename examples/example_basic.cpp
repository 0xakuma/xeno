#include "engine/engine.hpp"
#include <iostream>

int main()
{
    std::cout << "Xeno Engine Example Application" << std::endl;
    
    try {
        // Get the engine instance
        xeno::Engine& engine = xeno::Engine::getInstance();
        
        std::cout << "Engine initialized successfully!" << std::endl;
        
        // For now, just demonstrate that we can access the engine
        // In the future, you might call engine.run() or other methods
        
        std::cout << "Example application completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error in example application: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
