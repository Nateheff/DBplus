#include "Leaf_Node.h"


void Leaf_Node::Get_Table(){
    std::fstream fs;
    fs.open("catalog_attr.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
    
    uint16_t key = tree_attr.calc_name(file.c_str());
    tree_attr.search_range_catalog(key,key,30);
}


