#pragma once

#include <spch.h>
#include <time/time.h>

namespace Bk {
    template<typename P>
    class TaskTimer 
    {
        public:
            TaskTimer(TimeSpan<P> ts)
            : ts(ts) {}
            ~TaskTimer() { stop(); }

            void start(std::unique_ptr<std::function<void()>> action)
            {
                if(running) stop();
                running = true;
                worker = std::thread([this](std::unique_ptr<std::function<void()>> action)
                {
                    std::function<void()>& task = *action;
                    while(running)
                    {
                        std::this_thread::sleep_for(ts.interval);
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
            std::thread worker;
            TimeSpan<P> ts;
    };
}