#include "json_node.h"
namespace Bk::Json 
{
    std::string Node::to_string(int indent) {
        std::string spaceString = std::string(indent, ' ');
        std::string outputString = "";
        switch (type) {
            case Type::STRING: 
            {
                outputString += spaceString + *values.s;
                break;
            }
            case Type::NUMBER: 
            {
                outputString += spaceString + std::to_string(values.fValue);
                break;
            }
            case Type::BOOLEAN: 
            {
                outputString += spaceString + (values.bValue ? "true" : "false");
                break;
            }
            case Type::NULL_TYPE: 
            {
                outputString += spaceString + "null";
                break;
            }
            case Type::LIST: 
            {
                // std::cout << "[";
                outputString += spaceString + "[\n";
                int index = 0;
                for (auto node : (*values.list)) {
                    outputString += node->toString(indent + 1);
                    if (index < (*values.list).size() - 1) {
                    outputString += ",\n";
                    }
                    index++;
                }
                outputString += "\n"  + spaceString + "]\n";
                break;
            }
            case Type::OBJECT: 
            {
                outputString += spaceString + "{\n";
                for (JSONObject::iterator i = (*values.object).begin(); i != (*values.object).end(); i++) 
                {
                    outputString += spaceString + " " + "\"" + i->first + "\"" + ": ";
                    outputString += i->second->toString(indent + 1);
                    JSONObject::iterator next = i;
                    next++;
                    if ((next) != (*values.object).end()) 
                    {
                        outputString += ",\n";
                    }
                    outputString += spaceString + "\n";
                }
                outputString += spaceString + "}";
            }
        }
        return outputString;
    }
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