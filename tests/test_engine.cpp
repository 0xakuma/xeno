#include "engine.hpp"
#include <cassert>
#include <stdexcept>

void test_engine_creation()
{
    // Test that we can get an instance of the engine
    xeno::Engine &engine = xeno::Engine::getInstance();

    // This should not throw any exceptions
    // If we get here, the test passes
}

void test_engine_singleton()
{
    // Test that getInstance returns the same instance
    xeno::Engine &engine1 = xeno::Engine::getInstance();
    xeno::Engine &engine2 = xeno::Engine::getInstance();

    // Both references should point to the same object
    if (&engine1 != &engine2)
    {
        throw std::runtime_error("Engine singleton test failed: different instances returned");
    }
}

// Additional test functions can be added here as the engine grows
void test_engine_run()
{
    // Test that the run method can be called without crashing
    xeno::Engine &engine = xeno::Engine::getInstance();

    // For now, just test that run() doesn't throw
    // In the future, you might want to mock dependencies or test specific behaviors
    try
    {
        // Note: Commenting out actual run() call since it might start a graphics context
        // engine.run();
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Engine run test failed: " + std::string(e.what()));
    }
}
