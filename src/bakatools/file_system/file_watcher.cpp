#include "file_watcher.h"

FileWatcher::FileWatcher(std::string path, TimeSpan<Millisecond> ts)
: target(path), ttm(ts)
{
    for (const std::filesystem::directory_entry& file : std::filesystem::recursive_directory_iterator(target))
        paths[file.path().string()] = std::filesystem::last_write_time(file);
}

FileWatcher::~FileWatcher() { stop(); }

void FileWatcher::start(const std::function<void (std::string, FileStatus)>& action)
{
    std::function<void()> task([&]()
    {
        auto it = paths.begin();
        while (it != paths.end())
        {
            if (!std::filesystem::exists(it->first)) 
            {
                action(it->first, FileStatus::Deleted);
                it = paths.erase(it);
            }
            else it++;
        }
        for (const std::filesystem::directory_entry& file : std::filesystem::recursive_directory_iterator(target))
        {
            auto current_file_last_write_time = std::filesystem::last_write_time(file);
            if (contains(file.path().string()))
            {
                if(paths[file.path().string()] != current_file_last_write_time) {
                    paths[file.path().string()] = current_file_last_write_time;
                    action(file.path().string(), FileStatus::Modified);
                }
            } else 
            {
                paths[file.path().string()] = current_file_last_write_time;
                action(file.path().string(), FileStatus::Created);
            }
        }
    });
    ttm.start(std::make_unique<std::function<void()>>(task));
}

void FileWatcher::stop() { ttm.stop(); }

bool FileWatcher::contains(std::string path) { return paths.find(path) != paths.end(); }