#include "node.h"
namespace Bk::Json 
{
    // Node::~Node()
    // {
    //     switch(type)
    //     {
    //         case Type::OBJECT:
    //         {
    //             delete values.object;
    //             break;
    //         }
    //         case Type::LIST:
    //         {
    //             delete values.list;
    //             break;
    //         }
    //         case Type::STRING:
    //         {
    //             delete values.s;
    //             break;
    //         }
    //     }
    // } 
    
    std::string Node::to_string(int indent) 
    {
        std::string space_string = std::string(indent, ' ');
        std::string output_string = "";
        switch (type) 
        {
            case Type::STRING: 
            {
                output_string += '"' + *values.s + '"';        
                return output_string;
            }
            case Type::NUMBER: 
            {
                output_string += std::to_string(values.fValue);
                return output_string;
            }
            case Type::BOOLEAN: 
            {
                output_string += (values.bValue ? "true" : "false");
                return output_string;
            }
            case Type::NULL_TYPE: 
            {
                output_string += "null";
                return output_string;
            }
            case Type::LIST: 
            {
                output_string += space_string + "[\n";
                for (int i = 0; i < (*values.list).size(); i++) 
                {
                    output_string += get_list()[i]->to_string(indent + 4);
                    if (i < (*values.list).size() - 1) 
                    {
                        output_string += ",\n";
                    }
                }
                output_string += "\n"  + space_string + "]";
                return output_string;
            }
            case Type::OBJECT: 
            {
                output_string += space_string + "{\n";
                for (Object::iterator i = (*values.object).begin(); i != (*values.object).end(); i++) 
                {
                    output_string += space_string + "    " + "\"" + i->first + "\"" + ": ";
                    output_string += i->second->to_string(indent + 4);
                    Object::iterator next = i;
                    next++;
                    if ((next) != (*values.object).end()) 
                    {
                        output_string += ",\n";
                    }
                }
                output_string += "\n" + space_string + "}";
                return output_string;
            }
        }
        return "";
    }
    void Node::set_object(Object *object) 
    {
        values.object = object;
        type = Type::OBJECT;
    }

    Object* Node::get_p_object()
    {
        if (type == Type::OBJECT) 
            return values.object;
        throw std::logic_error("Json value not an object");
    }

    Object Node::get_object()
    {
        if (type == Type::OBJECT) 
            return *values.object;
        throw std::logic_error("Json value not an object");
    }

    void Node::set_list(List* list)
    {
        values.list = list;
        type = Type::LIST;
    }

    List* Node::get_p_list()
    {
        if (type == Type::LIST) 
            return values.list;
        throw std::logic_error("Json value not a list");
    }

    List Node::get_list()
    {
        if (type == Type::LIST) 
            return *values.list;
        throw std::logic_error("Json value not a list");
    }

    void Node::set_string(std::string* str)
    {
        values.s = str;
        type = Type::STRING;
    }

    std::string* Node::get_p_string()
    {
        if (type == Type::STRING) 
            return values.s;
        throw std::logic_error("Json value not a string");
    }

    std::string Node::get_string()
    {
        if (type == Type::STRING) 
            return *values.s;
        throw std::logic_error("Json value not a string");
    }

    void Node::set_bool(bool value)
    {
        values.bValue = value;
        type = Type::BOOLEAN;
    }

    bool Node::get_bool()
    {
        if (type == Type::BOOLEAN) 
            return values.bValue;
        throw std::logic_error("Json value not a boolean");
    }

    void Node::set_float(float value)
    {
        values.fValue = value;
        type = Type::NUMBER;
    }

    float Node::get_float()
    {
        if (type == Type::NUMBER) 
            return values.fValue;
        throw std::logic_error("Json value not a number");
    }

    void Node::set_int(int value)
    {
        values.fValue = value;
        type = Type::NUMBER;
    }

    int Node::get_int()
    {
        if (type == Type::NUMBER) 
            return (int)values.fValue;
        throw std::logic_error("Json value not a number");
    }

    void Node::set_null()
    {
        type = Type::NULL_TYPE;
    }

    bool Node::is_null()
    {
        return type == Type::NULL_TYPE;
    }
}