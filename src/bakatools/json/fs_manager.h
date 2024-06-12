#include <bakatoolspch.h>
#include <bakatools/file_system/directory.h>
#include <bakatools/file_system/file.h>
#include "parser.h"
#include "tools.h"

namespace Bk::Json
{
    class FsManager 
    {
        std::string path;
        Pointer config;
        public:
            FsManager(std::string path);

            void init(bool force = false, int page_size = 100);
            void config_init(int page_size);
            bool exists() { return File(path + "/collection.json").exists(); }
            void erase() { Directory(path).remove(); }

            void set_config(Object* object);
            void write(File file, Pointer& node);
            void write_config();
            Object get_config() { return config->get_object(); }
            int get_page(float id) { return (int)(id/100.0f); }
            int get_page(int id) { return (int)(id/100.0f); }

            int insert(Object* object);
            bool update(Object* object);
            bool remove(int id);
            Pointer findby_id(int id);
            Pointer find_all();
    };
}