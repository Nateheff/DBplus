#pragma once
#include <map> 

#include "Serializable.hpp"
/*
 * We need:
 * max order (# of keys and children) sturcutre(key,child pointer)
 * fill first node, then split, then fill, then split
*/

using namespace Serialize;

template <typename T>
class Internal_Index_Node: public Serializable<Internal_Index_Node<T>>
{
public:
bool root;
uint32_t num_keys;
std::shared_ptr<Internal_Index_Node> parent_prt;
std::map<T ,std::shared_ptr<Internal_Index_Node>>cell;
const uint32_t max_size = 4096;
const uint8_t header_size = 4 + sizeof(parent_prt);
const uint32_t total_size = header_size + (sizeof(cell) * num_keys);
const uint16_t max_cells = (max_size - header_size)/sizeof(cell);


void check_add(T key, std::shared_ptr<Internal_Index_Node<T>>ptr){
    if(max_cells == cell.size()){
        this->split(key);
    }else{
        auto it= cell.find(key);
        cell.insert(it,std::make_pair(key,ptr));
    }
};

void split(T key){
    
};


    Internal_Index_Node(uint32_t num_Keys,std::shared_ptr<Internal_Index_Node>p_ptr={},std::map<T,std::shared_ptr<Internal_Index_Node>>cells={},bool is_root=false)
:num_keys(num_Keys), parent_prt(p_ptr),cell(cells),root(is_root){};
    ~Internal_Index_Node()=default;

};


