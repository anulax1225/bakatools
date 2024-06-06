#include "json_parser.h"

namespace Bk::Json
{
    Parser::Parser(File& file)
    {
        Type::DataStream data;
        if (file.exists())
        {
            data = file.read(file.size());
            data.reverse();
        }
        lexer = Lexer(data);
    }

    Parser::Parser(const char* str, int length)
    {
        Type::DataStream data;
        data.payload = std::vector<char>(str, str + length);
        data.reverse();
        lexer = Lexer(data);
    }

    Parser::Parser(const std::string& str)
    {
        Type::DataStream data;
        data.payload = std::vector<char>(str.c_str(), str.c_str() + str.length());
        data.reverse();
        lexer = Lexer(data);
    }

    std::shared_ptr<Json::Node> Parser::parse() 
    {
        Token token;
        while (lexer.has_more_tokens()) {
            try 
            {
                token = lexer.get_token();
                switch (token.type) 
                {
                    case TokenType::CURLY_OPEN: 
                    {
                        std::shared_ptr<Json::Node> parsed_object = parse_object();
                        if (!root) {
                            root = parsed_object;
                        }
                        break;
                    }
                    case TokenType::ARRAY_OPEN: {
                        std::shared_ptr<Json::Node> parsed_list = parse_list();
                        if (!root) {
                            root = parsed_list;
                        }
                        break;
                    }

                    case TokenType::STRING: {
                        
                        std::shared_ptr<Json::Node> parsed_string = parse_string();
                        if (!root) {
                            root = parsed_string;
                        }
                        break;
                    }
                    case TokenType::NUMBER: {
                        std::shared_ptr<Json::Node> parsed_number = parse_number();
                        if (!root) {
                            root = parsed_number;
                        }
                        break;
                    }
                    
                    case TokenType::BOOLEAN: {
                        std::shared_ptr<Json::Node> parsed_boolean = parse_boolean();
                        break;
                    }
                }
            }
            catch(std::logic_error& e)
            {
                BK_INFO(e.what());
                auto node = std::shared_ptr<Json::Node>();
                node->set_null();
                root = node;
                break;
            }
        }
        return root;
    }

    std::shared_ptr<Json::Node> Parser::parse_list() 
    {
        std::shared_ptr<Json::Node> node = std::make_shared<Json::Node>();
        Json::List *list = new Json::List();
        bool has_completed = false;
        Token next_token;
        while (!has_completed) {
            if (!lexer.has_more_tokens()) 
            {
                throw std::logic_error("No more tokens");
            } 
            else 
            {
                next_token = lexer.get_token();
                if (next_token.type == TokenType::COLON || next_token.type == TokenType::COMMA)
                    continue;
                std::shared_ptr<Json::Node> node;
                switch (next_token.type) 
                {
                    case TokenType::ARRAY_OPEN: 
                    {
                        node = parse_list();
                        break;
                    }
                    case TokenType::CURLY_OPEN: 
                    {
                        node = parse_object();
                        break;
                    }
                    case TokenType::STRING: 
                    {
                        node = parse_string();
                        break;
                    }
                    case TokenType::NUMBER: 
                    {
                        node = parse_number();
                        break;
                    }
                    case TokenType::BOOLEAN: 
                    {
                        node = parse_boolean();
                        break;
                    }
                    case TokenType::NULL_TYPE: {
                        node = parse_null();
                        break;
                    }
                }
                list->push_back(node);
                if (next_token.type == TokenType::ARRAY_CLOSE) {
                    has_completed = true;
                }
            }
        }
        node->set_list(list);
        return node;
    }

    std::shared_ptr<Json::Node> Parser::parse_object() 
    {
        std::string key = "";
        std::shared_ptr<Json::Node> node = std::make_shared<Json::Node>();
        Json::Object *key_object_map = new Json::Object();
        bool has_completed = false;
        bool no_key = true;
        Token next_token;
        while (!has_completed) 
        {
            if (lexer.has_more_tokens()) 
            {
                if (no_key)
                {
                    next_token = lexer.get_token();
                    if (next_token.type == TokenType::CURLY_CLOSE) 
                    {
                        has_completed = true;
                        break;
                    }
                    if (next_token.type == TokenType::COLON || next_token.type == TokenType::COMMA)
                        continue;
                    key = next_token.value;
                    no_key = false;
                }
                next_token = lexer.get_token();
                if (next_token.type == TokenType::COLON || next_token.type == TokenType::COMMA)
                    continue;
                std::shared_ptr<Json::Node> node;
                switch (next_token.type) 
                {
                    case TokenType::STRING: 
                    {
                        (*key_object_map)[key] = parse_string();
                        break;
                    }
                    case TokenType::ARRAY_OPEN: 
                    {
                        (*key_object_map)[key] = parse_list();
                        break;
                    }
                    case TokenType::NUMBER: 
                    {
                        (*key_object_map)[key] = parse_number();
                    break;
                    }
                    case TokenType::CURLY_OPEN: 
                    {
                        (*key_object_map)[key] = parse_object();
                        break;
                    }
                    case TokenType::BOOLEAN: 
                    {
                        (*key_object_map)[key] = parse_boolean();
                        break;

                    }
                    case TokenType::NULL_TYPE: 
                    {
                        (*key_object_map)[key] = parse_null();
                        break;
                    }
                }
                if (next_token.type == TokenType::CURLY_CLOSE) 
                {
                    has_completed = true;
                    break;
                }
                no_key = true;
                key = "";
            }
            else 
            {
                throw std::logic_error("No more tokens");
            }
        }
        node->set_object(key_object_map);
        return node;    
    }

    std::shared_ptr<Json::Node> Parser::parse_string() 
    {
        std::shared_ptr<Json::Node> node = std::make_shared<Json::Node>();
        Token token = lexer.roll_back_token();
        std::string *sValue = new std::string(token.value);
        node->set_string(sValue);
        return node;
    }

    std::shared_ptr<Json::Node> Parser::parse_number() 
    {
        std::shared_ptr<Json::Node> node = std::make_shared<Json::Node>();
        Token token = lexer.roll_back_token();
        float fValue = std::stof(token.value);
        node->set_float(fValue);
        return node;
    }

    std::shared_ptr<Json::Node> Parser::parse_boolean() 
    {
        std::shared_ptr<Json::Node> node = std::make_shared<Json::Node>();
        Token token = lexer.roll_back_token();
        bool bValue = token.value == "True" ? true : false;
        node->set_bool(bValue);
        return node;
    }

    std::shared_ptr<Json::Node> Parser::parse_null() 
    {
        std::shared_ptr<Json::Node> node = std::make_shared<Json::Node>();
        Token token = lexer.roll_back_token();
        node->set_null();
        return node;
    }
}