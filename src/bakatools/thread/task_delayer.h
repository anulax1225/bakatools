#pragma once

#include <spch.h>
#include <time/time.h>

namespace Bk {
    template<typename P>
    class TaskDelayer 
    {
        public:
            TaskDelayer(int n_ts, 
            std::unique_ptr<std::function<void()>> action
            ): ts(n_ts) 
            {
                worker = std::thread([this](std::unique_ptr<std::function<void()>> action)
                {
                    std::function<void()>& task = *action;
                    std::this_thread::sleep_for(ts.interval);
                    task();
                }, std::move(action)); 
            }

            ~TaskDelayer() { worker.join(); }

        private:
            std::thread worker;
            TimeSpan<P> ts;
    };
}