#include "xeno-pal.hpp"

namespace xeno
{
    class Engine
    {
    public:
        Engine();
        ~Engine();
        Engine(const Engine &) = delete;
        Engine &operator=(const Engine &) = delete;

        static Engine &getInstance();
        void run();

    private:
        xeno::pal::XenoWindow window;
    };

}