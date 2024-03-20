#pragma once 

#include <bakatoolspch.h>
namespace Bk::DataType {
    template <typename K, typename V>
    struct Trie
    {
        Trie() = default;
        ~Trie()
        {
            for (auto node : nodes)
                delete node.second;
        }

        void add_nodes(const K* path, unsigned int length, V val)
        {
            if (length)
            {
                if (nodes.find(*path) == nodes.end()) 
                    nodes.insert({ *path, new Trie<K, V>() });
                nodes[*path]->add_nodes(++path, --length, val);
            } 
            else if (!nodes.size())
            {
                value = val;
                terminal = true;
            }
            else 
            {
                value = val;
                terminal = false;
            }
        }

        Trie<K, V>* get_node(const K* path, unsigned int length)
        {
            if (length > 1)
            {
                if (nodes.find(*path) == nodes.end()) 
                    return nullptr;
                return nodes[*path]->get_node(++path, --length);
            }
            else if (length > 0)
            {
                if (nodes.find(*path) == nodes.end()) 
                    return nullptr;
                return nodes[*path];
            }
            else return this; 
        }

        std::unordered_map<K, Trie*> nodes;
        V value;
        bool terminal;
    };
}