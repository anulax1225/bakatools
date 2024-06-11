#pragma once

#include <bakatoolspch.h>
#include "lexer.h"

namespace Bk::Json
{
    class Parser 
    {
        Pointer root;
        std::unique_ptr<Json::Node> current;
        Lexer lexer;
        
        Pointer parse_object();
        Pointer parse_string();
        Pointer parse_number();
        Pointer parse_list();
        Pointer parse_boolean();
        Pointer parse_null();

        public:
            Parser(const Type::DataStream data)
            :lexer(data) {}
            Parser(File& file);
            Parser(const char* data, int length);
            Parser(const std::string& str);

            Pointer parse();
    };
}