#pragma once

#include <bakatoolspch.h>

namespace Bk::Json
{
    class Node;
    
    using Object = std::map<std::string, std::shared_ptr<Node>>;
    using List = std::vector<std::shared_ptr<Node>>;

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
            Object get_object();

            void set_list(List* list);
            List get_list();

            void set_string(std::string* str);
            std::string get_string();

            void set_bool(bool value);
            bool get_bool();

            void set_float(float value);
            float get_float();

            void set_null();
            bool is_null();

            std::string to_string(int indent  = 3);

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