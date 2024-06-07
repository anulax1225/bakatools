#pragma once

#include <bakatoolspch.h>
#include "json_lexer.h"

namespace Bk::Json
{
    class Parser 
    {
        std::shared_ptr<Json::Node> root;
        std::unique_ptr<Json::Node> current;
        Lexer lexer;
        
        std::shared_ptr<Json::Node> parse_object();
        std::shared_ptr<Json::Node> parse_string();
        std::shared_ptr<Json::Node> parse_number();
        std::shared_ptr<Json::Node> parse_list();
        std::shared_ptr<Json::Node> parse_boolean();
        std::shared_ptr<Json::Node> parse_null();

        public:
            Parser(const Type::DataStream data)
            :lexer(data) {}
            Parser(File& file);
            Parser(const char* data, int length);
            Parser(const std::string& str);

            std::shared_ptr<Json::Node> parse();
    };
}