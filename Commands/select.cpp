#include "Commands.h"
#include "../B_Tree.h"
#include "../B+_Tree.h"

void select(std::string table_name, Run* obj,std::vector<std::string>identifiers){
    Bp_Tree tree{};
    for(auto id:identifiers)
    std::cout<<id<<std::endl;
    // std::cout<<"comp"<<std::endl;
    uint16_t key = obj->tree_attr.calc_name(table_name.c_str());
    
    obj->tree_rel.search_catalog(key,28); 
    obj->tree_ind.search_catalog(key,48);
    obj->tree_attr.search_range_catalog(key,key,30);
    std::cout<<"YEP "<<obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].row_size<<std::endl;
    uint16_t row_size = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].row_size;
    // tree.search(key,(4087/obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].row_size),obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].row_size,obj->tree_ind.info.rel.rows[obj->tree_ind.info.index].key_type,obj);
    
}

void select(std::string table_name, Run* obj, std::vector<std::string>identifiers,std::string attr, uint16_t op,std::string value){
     std::cout<<"selects all where "<<attr<<" "<<op<<" "<<value<<std::endl;
     
};

void select_all(std::string table_name, Run* obj){
    std::cout<<"Select All"<<std::endl;
    
}
void select_all(std::string table_name,Run*obj,std::string attr,uint16_t op,std::string value)
{
    std::cout<<"select all where "<<attr<<" "<<op<<" "<<value<<std::endl;
};