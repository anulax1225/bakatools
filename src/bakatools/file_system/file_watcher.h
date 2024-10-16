#pragma once

#include "bakatools/thread/task_delayer.h"
#include <bakatoolspch.h>

namespace Bk {
    enum class FileStat
    {
        Created = 0,
        Modified = 1,
        Deleted = 2,
    };

    class FileWatcher
    {
        public:
            FileWatcher(std::string path, int ts = 1000);
            ~FileWatcher();

            void start(const std::function<void (std::string, FileStat)>& action);
            void stop();
            bool contains(std::string path);

        private:
            std::string target;
            std::unordered_map<std::string, std::filesystem::file_time_type> paths;
            TaskDelayer ttm;
    };
}