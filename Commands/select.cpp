#include "Commands.h"
#include "../B_Tree.h"
#include "../B+_Tree.h"

std::vector<Row> select(std::string table_name, Run* obj, std::vector<std::string>identifiers){
    Bp_Tree tree{};
    for(auto id:identifiers)
    std::cout<<id<<std::endl;
    // std::cout<<"comp"<<std::endl;
    uint32_t key = obj->tree_attr.calc_name(table_name.c_str());
    
    obj->tree_rel.search_catalog(key,28); 
    obj->tree_ind.search_catalog(key,48);
    obj->tree_attr.search_range_catalog(key,key,30);
    std::cout<<"YEP "<<obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].row_size<<std::endl;
    uint16_t row_size = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].row_size;
    if(obj->tree_ind.info.rel.rows[obj->tree_ind.info.index].key_type=='f'){
        float k{};
        tree.search_range(k,__FLT32_MAX__,(4087/obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].row_size));
    }
    else{
    key = 0;
    tree.search_range(key,UINT32_MAX,(4087/obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].row_size));
    }
    // Row row{};
    // memcpy(&row.data,&tree.info.leaf.data[tree.info.index*row_size],row_size);
    // memcpy(&row.index,&row.data,4);
    return tree.info.rows;
    
}

std::vector<Row> select_all(std::string table_name,Run*obj,std::string attr,uint16_t op,std::string value)
{
    std::cout<<"select all where "<<attr<<" "<<op<<" "<<value<<std::endl;
    Bp_Tree tree{};
    uint32_t index{};
    float ind{};
    
    
    // std::cout<<"comp"<<std::endl;
    uint16_t key = obj->tree_attr.calc_name(table_name.c_str());
    
    obj->tree_rel.search_catalog(key,28); 
    obj->tree_ind.search_catalog(key,48);
    obj->tree_attr.search_range_catalog(key,key,30);
    
    tree.info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    tree.info.ind = &obj->tree_ind.info.rel.rows[obj->tree_rel.info.index];

    if(tree.info.ind->key_type != 'f'){

        switch(obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1).type){
        case 's':
        case 'i':
        case 'b':
        {
        // std::cout<<"int/short/bool"<<std::endl;
        index = atoi(value.c_str());
        break;
        }
        // case('f'):
        // {
        // row->index = atof(identifiers.at(1).c_str());
        // break;
        // }
        case('c'):
        {
        index = value.at(0);
        break;
        }
        case('v'):
        {
        index = obj->tree_attr.calc_name(value.c_str());
        break;
        }
    }
    uint16_t row_size = tree.info.relation.row_size;
    uint16_t num_rows = (4087/row_size);
    
    switch(op){
        case(21)://>
        {
           tree.search_range(index+1,UINT32_MAX,num_rows); 
           return tree.info.rows;
        }
        case(22)://<
        {
            tree.search_range(0,index-1,num_rows);
            return tree.info.rows;
        }
        case(26)://=
        {
            tree.search_range(index,index,num_rows);
            return tree.info.rows;
        }
        case(29)://<=
        {
            tree.search_range(0,index,num_rows);
            return tree.info.rows;
        }
        case(30)://>=
        {
            tree.search_range(index,UINT32_MAX,num_rows); 
           return tree.info.rows;
        }
    }
    }else{
        ind = atof(value.c_str());
        uint16_t row_size = tree.info.relation.row_size;
    uint16_t num_rows = (4087/row_size);
    
    switch(op){
        case(21)://>
        {
           tree.search_range(ind+__FLT32_MIN__,__FLT32_MAX__,num_rows); 
           return tree.info.rows;
        }
        case(22)://<
        {
            tree.search_range(0.0,ind-__FLT32_MIN__,num_rows);
            return tree.info.rows;
        }
        case(26)://=
        {
            tree.search_range(ind,ind,num_rows);
            return tree.info.rows;
        }
        case(29)://<=
        {
            tree.search_range(0.0,ind,num_rows);
            return tree.info.rows;
        }
        case(30)://>=
        {
            tree.search_range(ind,__FLT32_MAX__,num_rows); 
           return tree.info.rows;
        }
    }
    }
};