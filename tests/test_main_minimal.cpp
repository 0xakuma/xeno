#include <iostream>
#include <cassert>

// Forward declarations of test functions
void test_engine_creation();
void test_engine_singleton();
void test_engine_run();

int main()
{
    std::cout << "Running Xeno Engine Tests (Minimal)..." << std::endl;

    try
    {
        test_engine_creation();
        std::cout << "✓ Engine creation test passed" << std::endl;

        test_engine_singleton();
        std::cout << "✓ Engine singleton test passed" << std::endl;

        test_engine_run();
        std::cout << "✓ Engine run test passed" << std::endl;

        std::cout << "All tests passed!" << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
