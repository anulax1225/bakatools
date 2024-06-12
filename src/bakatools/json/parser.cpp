#include "parser.h"

namespace Bk::Json
{
    Parser::Parser(File& file)
    {
        root = Pointer(new Node());
        root->set_null();
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
        root = Pointer(new Node());
        root->set_null();
        Type::DataStream data;
        data.push<char>(str, length);
        data.reverse();
        lexer = Lexer(data);
    }

    Parser::Parser(const std::string& str)
    {
        root = Pointer(new Node());
        root->set_null();
        Type::DataStream data;
        data.payload = std::vector<char>(str.begin(), str.end());
        data.reverse();
        lexer = Lexer(data);
    }

    Pointer Parser::parse() 
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
                        Pointer parsed_object = parse_object();
                        root = parsed_object;
                        break;
                    }
                    case TokenType::ARRAY_OPEN: 
                    {
                        Pointer parsed_list = parse_list();
                        root = parsed_list;
                        break;
                    }

                    case TokenType::STRING: 
                    {
                        Pointer parsed_string = parse_string();
                        root = parsed_string;
                        break;
                    }
                    case TokenType::NUMBER: 
                    {
                        Pointer parsed_number = parse_number();
                        root = parsed_number;
                        break;
                    }
                    
                    case TokenType::BOOLEAN: 
                    {
                        Pointer parsed_boolean = parse_boolean();
                        break;
                    }
                }
            }
            catch(std::logic_error& e)
            {
                BK_TRACE(e.what());
                auto node = Pointer();
                node->set_null();
                root = node;
                break;
            }
        }
        return root;
    }

    Pointer Parser::parse_list() 
    {
        Pointer node = Pointer(new Node());
        Json::List* list = new Json::List();
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
                if (next_token.type == TokenType::ARRAY_CLOSE) {
                    has_completed = true;
                    break;
                }
                Pointer node;
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
            }
        }
        node->set_list(list);
        return node;
    }

    Pointer Parser::parse_object() 
    {
        std::string key = "";
        Pointer node = Pointer(new Node());
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

    Pointer Parser::parse_string() 
    {
        Pointer node = Pointer(new Node());
        Token token = lexer.roll_back_token();
        std::string *sValue = new std::string(token.value);
        node->set_string(sValue);
        return node;
    }

    Pointer Parser::parse_number() 
    {
        Pointer node = Pointer(new Node());
        Token token = lexer.roll_back_token();
        float fValue = std::stof(token.value);
        node->set_float(fValue);
        return node;
    }

    Pointer Parser::parse_boolean() 
    {
        Pointer node = Pointer(new Node());
        Token token = lexer.roll_back_token();
        bool bValue = token.value == "True" ? true : false;
        node->set_bool(bValue);
        return node;
    }

    Pointer Parser::parse_null() 
    {
        Pointer node = Pointer(new Node());
        Token token = lexer.roll_back_token();
        node->set_null();
        return node;
    }
}