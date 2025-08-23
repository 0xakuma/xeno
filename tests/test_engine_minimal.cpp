#include "engine/engine_minimal.hpp"
#include <cassert>
#include <stdexcept>
#include <string>

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

void test_engine_run()
{
    // Test that the run method can be called without crashing
    xeno::Engine &engine = xeno::Engine::getInstance();

    // Test that run() doesn't throw
    try
    {
        engine.run();
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Engine run test failed: " + std::string(e.what()));
    }
}
