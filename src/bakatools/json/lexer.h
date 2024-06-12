#pragma once

#include <bakatoolspch.h>
#include <bakatools/file_system/file.h>
#include <bakatools/container/data_stream.h>
#include <bakatools/string/format.h>
#include "node.h"

namespace Bk::Json 
{
    enum class TokenType
    {
        CURLY_OPEN,
        CURLY_CLOSE,
        COLON,
        STRING,
        NUMBER,
        ARRAY_OPEN,
        ARRAY_CLOSE,
        COMMA,
        BOOLEAN,
        NULL_TYPE
    };

    struct Token
    {
        std::string value;
        TokenType type = TokenType::NULL_TYPE;
        
        std::string to_string();
    };

    class Lexer
    {
        std::vector<Token> lexed_token;

        public:
            Lexer() {}
            Lexer(Type::DataStream data)
            : data(data) {}

            Type::DataStream data;

            char get_next_char();
            char get_without_white_space();
            Token get_token();
            bool has_more_tokens();
            Token roll_back_token();
            void roll_back_char(char c);
    };
}