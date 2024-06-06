#include "json_lexer.h"

namespace Bk::Json 
{
    std::string Token::to_string()
    {
        return Tools::string_format("%s %d", this->value, (int)this->type);
    }
    
    char Lexer::get_next_char()
    {
        char c = data.pull<char>();
        return c;
    }

    bool Lexer::has_more_tokens()
    {
        return (bool)data.size();
    }

    char Lexer::get_without_white_space()
    {
        char c = ' ';
        while ((c == ' ' || c == '\n'))
        {
            c = get_next_char(); // check
            if ((c == ' ' || c == '\n') && !data.size())
            {
                throw std::logic_error("Ran out of tokens");
            }
            else if (!data.size())
            {
                return c;
            }
        }
        return c;
    }

    Token Lexer::get_token()
    {
        char c;
        if (!data.size())
        {
            throw std::logic_error("Exhausted tokens");
        }
        c = get_without_white_space();

        Token token;
        if (c == '"')
        {
            token.type = TokenType::STRING;
            token.value = "";
            c = get_next_char();
            while (c != '"')
            {
                token.value += c;
                c = get_next_char();
            }
        }
        else if (c == '{')
        {
            token.type = TokenType::CURLY_OPEN;
        }
        else if (c == '}')
        {
            token.type = TokenType::CURLY_CLOSE;
        }
        else if (c=='-' || (c >= '0' && c <= '9'))
        {
            token.type = TokenType::NUMBER;
            token.value = "";
            token.value += c;
            while ((c=='-')||(c >= '0' && c <= '9') || c == '.')
            {
                c = get_next_char();
                if (!data.size())
                {
                    break;
                }
                else
                {
                    if ((c=='-')||(c >= '0' && c <= '9')||(c=='.'))
                    {
                        token.value += c;
                    }
                    else if (c == ',')
                    {
                        roll_back_char(c);
                        break;
                    }
                    else if (c == '\n') break;
                    else
                    {
                        throw std::logic_error("Bad Numeric format");
                    }
                }
            }
        }
        else if(c=='f'){
            token.type = TokenType::BOOLEAN;
            token.value = "false";
            data.pull<char>(4);
        }
        else if(c=='t'){
            token.type = TokenType::BOOLEAN;
            token.value = "true";
            data.pull<char>(3);
        }
        else if(c=='n'){
            token.type = TokenType::NULL_TYPE;
            token.value = "null";
            data.pull<char>(3);
        }
        else if (c == '[')
        {
            token.type = TokenType::ARRAY_OPEN;
        }
        else if (c == ']')
        {
            token.type = TokenType::ARRAY_CLOSE;
        }
        else if (c == ':')
        {
            token.type = TokenType::COLON;
        }
        else if (c == ',')
        {
            token.type = TokenType::COMMA;
        }
        lexed_token.push_back(token);
        return token;
    }

    Token Lexer::roll_back_token()
    {
        auto token = lexed_token.back();
        return token;
    }

    void Lexer::roll_back_char(char c)
    {
        data.push<char>(c);
    }
}