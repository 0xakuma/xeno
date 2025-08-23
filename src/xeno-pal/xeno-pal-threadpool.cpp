#include "xeno-pal.hpp"

namespace xeno
{
    namespace pal
    {
        ThreadPool::ThreadPool(size_t num_threads)
        {
            for (size_t i = 0; i < num_threads; ++i)
            {
                threads_.emplace_back([this]()
                                      {
                for(;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mutex_);
                        condition_.wait(lock, [this]() {
                            return stopping_ || !tasks_.empty();
                        });
                        if (stopping_ && tasks_.empty()) {
                            return;
                        }
                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    task();
                } });
            }
        }

        ThreadPool::~ThreadPool()
        {
            {
                std::unique_lock<std::mutex> lock(mutex_);
                stopping_ = true;
            }
            condition_.notify_all();
            for (std::thread &thread : threads_)
            {
                thread.join();
            }
        }
    }
}