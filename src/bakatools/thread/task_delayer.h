#pragma once

#include <thread>
#include <functional>
#include <chrono>
#include <ratio>

namespace Bk {
    class TaskDelayer 
    {
        public:
            TaskDelayer(int ts, bool repeat = false)
            : ts(ts), repeat(repeat) {}
            ~TaskDelayer() { stop(); }

            void start(std::unique_ptr<std::function<void()>> action)
            {
                if(running) stop();
                running = true;
                worker = std::thread([this](std::unique_ptr<std::function<void()>> action)
                {
                    std::function<void()>& task = *action;
                    while(running && repeat)
                    {
                        std::this_thread::sleep_for(ts);
                        task();
                    }
                }, std::move(action)); 
            }

            void stop()
            {
                if (!running) return;
                running = false;
                worker.join();
            }

        private:
            bool running = false;
            bool repeat;
            std::thread worker;
            std::chrono::duration<int, std::milli> ts;
    };
}