#include <thread>

class thread_guard
{
private:
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_) :t(t_)
    {
    }

    ~thread_guard()
    {
        if (t.joinable()) // 1
        {
            t.join(); // 2
        }
    }

    thread_guard(thread_guard const&) = delete; // 3
    thread_guard& operator=(thread_guard const&) = delete;
};