#include "json_node.h"
namespace Bk::Json 
{
    void Node::set_object(Object *object) 
    {
        values.object = object;
        type = Type::OBJECT;
    }

    Object Node::get_object()
    {
        if (type == Type::OBJECT) 
            return *values.object;
        throw std::logic_error("Improper return");
    }

    void Node::set_list(List* list)
    {
        values.list = list;
        type = Type::LIST;
    }

    List Node::get_list()
    {
        if (type == Type::LIST) 
            return *values.list;
        throw std::logic_error("Improper return");
    }

    void Node::set_string(std::string* str)
    {
        values.s = str;
        type = Type::STRING;
    }

    std::string Node::get_string()
    {
        if (type == Type::STRING) 
            return *values.s;
        throw std::logic_error("Improper return");
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
        throw std::logic_error("Improper return");
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
        throw std::logic_error("Improper return");
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