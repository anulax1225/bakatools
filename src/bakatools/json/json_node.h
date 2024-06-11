#pragma once

#include <bakatoolspch.h>

namespace Bk::Json
{
    class Node;
    
    using Pointer = std::shared_ptr<Node>;
    using Object = std::map<std::string, Pointer>;
    using List = std::vector<Pointer>;

    class Node 
    {
        public:
            enum class Type 
            { 
                OBJECT, 
                LIST, 
                STRING, 
                NUMBER, 
                BOOLEAN, 
                NULL_TYPE
            }; 
            void set_object(Object* object);
            Object* get_p_object();
            Object get_object();

            void set_list(List* list);
            List* get_p_list();
            List get_list();

            void set_string(std::string* str);
            std::string* get_p_string();
            std::string get_string();

            void set_bool(bool value);
            bool get_bool();

            void set_float(float value);
            float get_float();

            void set_int(int value);
            int get_int();

            void set_null();
            bool is_null();

            std::string to_string(int indent = 0);

        private:
            union Values {
                Object* object;
                List* list;
                std::string* s;
                float fValue;
                bool bValue;
            };
            Values values;
            Type type;
    };
}