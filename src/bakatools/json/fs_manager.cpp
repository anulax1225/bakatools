#include "fs_manager.h"

namespace Bk::Json
{
    FsManager::FsManager(std::string path)
    : path(path) 
    {
        auto dir = Directory(path);
        if (dir.exists())
        {
            File f_conf(path + "/collection.json");
            if (f_conf.exists())
            {
                config = Parser(f_conf).parse(); 
                write_config();
            } 
            else 
            {
                Pointer node(new Node());
                node->set_null();
                config = node;
            }
        } 
        else 
        {
            Pointer node(new Node());
            node->set_null();
            config = node;
        }
    }

    void FsManager::config_Init(int page_size)
    {
        auto dir = Directory(path);
        std::string s_config = "\n"
        "{\n"
        "   \"name\": \"" + dir.name() + "\",\n"
        "   \"id_count\": 0,\n"
        "   \"page_size\": " + std::to_string(page_size) + "\n" 
        "}";
        config = Parser(s_config).parse(); 
        write_config();
    }

    void FsManager::Init(bool force, int page_size)
    {

        auto dir = Directory(path);
        if (dir.exists() && force) dir = dir.remove();
        if (!dir.exists())
        {
            Directory::create(dir.path());
            config_Init(page_size);
        } 
        else 
        {
            File f_conf(path + "/collection.json");
            if (!f_conf.exists())
            {
                config_Init(page_size);
            } 
        }
    }

    void FsManager::set_config(Object* object) 
    { 
        config->set_object(object);
        write_config();
    }

    void FsManager::write(File file, Pointer& node)
    {
        Type::DataStream data;
        auto raw = node->ToString();
        data.push<char>(raw.c_str(), raw.length());
        file.write(data);
    }

    void FsManager::write_config()
    {
        if (!config->is_null())
        {
            File f_config = File(path + "/collection.json");
            write(f_config, config);
        }
    }

    int FsManager::insert(Object* object)
    {
        if (!config->is_null())
        {
            Object* conf_obj = config->get_p_object();
            (*object)["id"] = Pointer(new Node());
            (*object)["id"]->set_int((*conf_obj)["id_count"]->get_int());
            auto f_list = File(Tools::string_format("%s/%d.json", path, get_page((*conf_obj)["id_count"]->get_int())));
            if(f_list.exists()) 
            {
                auto ls = Parser(f_list).parse();
                auto new_node = Pointer(new Node());
                new_node->set_object(object);
                ls->get_p_list()->push_back(new_node);
                write(f_list, ls);
            } 
            else 
            {
                auto ls = Pointer(new Node());
                auto new_node = new Node();
                new_node->set_object(object);
                auto new_ls = new List();
                new_ls->push_back(Pointer(new_node));
                ls->set_list(new_ls);
                write(f_list, ls);
            }
            (*conf_obj)["id_count"]->set_float((*conf_obj)["id_count"]->get_int() + 1);
            set_config(conf_obj);
            return (*object)["id"]->get_int();
        }
        return -1;
    }

    bool FsManager::update(Object* object)
    {
        if (Json::as_key("id", *object))
        {
            int id = (*object)["id"]->get_int();
            auto f_list = File(Tools::string_format("%s/%d.json", path, get_page(id)));
            if (f_list.exists())
            {
                auto ls = Parser(f_list).parse();
                for (int i = 0; i < ls->get_list().size(); i++)
                {
                    auto node = ls->get_p_list()->at(i);
                    if (Json::as_key("id", node->get_object()) && node->get_object()["id"]->get_int() == id)
                    {
                        ls->get_p_list()->at(i)->set_object(object);
                        write(f_list, ls);
                        return true;
                    }
                }
            }
        } 
        return false;
    }

    bool FsManager::remove(int id)
    {
        auto f_path = Tools::string_format("%s/%d.json", path, get_page(id));
        auto f_list = File(f_path);
        if (f_list.exists())
        {
            auto ls = Parser(f_list).parse();
            for (int i = 0; i < ls->get_list().size(); i++)
            {
                auto node = ls->get_p_list()->at(i);
                if (Json::as_key("id", node->get_object()) && node->get_object()["id"]->get_int() == id)
                {
                    ls->get_p_list()->erase(ls->get_p_list()->begin() + i);
                    write(f_list, ls);
                    return true;
                }
            }
        }
        return false;
    }

    Pointer FsManager::findby_id(int id)
    {
        if (!config->is_null()) 
        {
            auto f_path = Tools::string_format("%s/%d.json", path, get_page(id));
            auto f_list = File(f_path);
            if (f_list.exists())
            {
                auto ls = Parser(f_list).parse();
                for (int i = 0; i < ls->get_list().size(); i++)
                {
                    auto node = ls->get_p_list()->at(i);
                    if (Json::as_key("id", node->get_object()))
                    {
                        if (node->get_object()["id"]->get_int() == id)
                        {
                            return node;
                        }
                    }
                }
            }
        }
        Pointer node(new Node);
        node->set_null();
        return node;
    }

    Pointer FsManager::find_all()
    {
        if (!config->is_null()) 
        {
            Pointer full_list(new Node);
            full_list->set_list(new List);
            int max_page = get_page(config->get_object()["id_count"]->get_int());
            for (int i = 0; i <= max_page; i++)
            {
                auto f_path = Tools::string_format("%s/%d.json", path, i);
                auto f_list = File(f_path);
                if (f_list.exists())
                {
                    auto ls = Parser(f_list).parse();
                    full_list = Json::concat(full_list->get_list(), ls->get_list());
                }
            }
            return full_list;
        }
        Pointer node(new Node);
        node->set_null();
        return node;
    }
}