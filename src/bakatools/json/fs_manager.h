#include <bakatoolspch.h>
#include "parser.h"

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

            void set_config(Object* object);
            void write(File file, Pointer& node);
            void write_config();
            Object get_config() { return config->get_object(); }
            int get_page(float id) { return (int)(id/100.0f); }

            void insert(Object* object);
            void update(Object* object);
            void remove(int id);
            Object findby_id(int id);
    };
}