#pragma once

#include <bakatoolspch.h>
#include <bakatools/thread/task_timer.h>

namespace Bk::Tools {
    enum class FileStat
    {
        Created = 0,
        Modified = 1,
        Deleted = 2,
    };

    class FileWatcher
    {
        public:
            FileWatcher(std::string path, TimeSpan<Millisecond> ts);
            ~FileWatcher();

            void start(const std::function<void (std::string, FileStat)>& action);
            void stop();
            bool contains(std::string path);

        private:
            std::string target;
            std::unordered_map<std::string, std::filesystem::file_time_type> paths;
            TaskTimer<Millisecond> ttm;
    };
}