#include "Commands.h"
#include "../B+_Tree.h"


void update(std::string table_name,Run*obj,std::vector<std::string>identifiers,uint16_t op, std::string value,std::string v_2){
    uint16_t key = obj->tree_attr.calc_name(table_name.c_str());

    obj->tree_ind.search_range_catalog(key,key,48);
    obj->tree_rel.search_range_catalog(key,key,28);

    for(size_t i = 0;i<obj->tree_rel.rows.size();i++){
        if(strcmp(obj->database.c_str(),obj->tree_rel.rows.at(i).rel_file)){
            obj->tree_ind.info.index+=i;
            obj->tree_rel.info.index+=i;
        }
    }
    obj->tree_attr.search_range_catalog(key,key,30);
    
    std::vector<uint16_t>positions{};
    std::vector<char>types{};
    std::vector<std::string>values{};
    Bp_Tree tree{};
    tree.info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    tree.info.ind = &obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
    bool index_update{};
    
    for(size_t i = 1; i<identifiers.size()-2;i+=2){
        for(auto row:obj->tree_attr.rows){
            
            if(std::string{row.attr_name} == identifiers.at(i)){
                if(row.position == 0){
                    index_update = true;
                }
            positions.push_back(row.position);
            types.push_back(row.type);
            break;
            }
        }
        
    }
    for(size_t i = 2; i<identifiers.size()-1;i+=2){
        values.push_back(identifiers.at(i));
    }
    uint16_t num_rows = 4087/tree.info.relation.row_size;
    if(!index_update){
        if(obj->tree_ind.info.rel.rows[obj->tree_ind.info.index].key_type == 'f'){
            float key{};
            key = atof(value.c_str());
    

        switch(op){
            case(21)://>
            {
            tree.update_range(key+__FLT16_MIN__,__FLT32_MAX__,num_rows,positions,types,obj,values);
             break; 
            }
            case(22)://<
            {
                tree.update_range(0.0,key-__FLT16_MIN__,num_rows,positions,types,obj,values);
                break;
            }
            case(26)://=
            {
                tree.update_range(key,key,num_rows,positions,types,obj,values);
                break;
            }
            case(29)://<=
            {
                tree.update_range(0.0,key,num_rows,positions,types,obj,values);
                break;
            
            }
            case(30)://>=
            {
                tree.update_range(key,__FLT32_MAX__,num_rows,positions,types,obj,values); 
                break;
            }
            case(14):
            {
            tree.update_range(key,atof(identifiers.at(identifiers.size()-2).c_str()),num_rows,positions,types,obj,values);
            break;
            }
        }
    }else{
        uint32_t key{};
    key = atoi(value.c_str());
    switch(op){
        case(21)://>
        {
           tree.update_range(key+1,__UINT32_MAX__,num_rows,positions,types,obj,values);
           break; 
        }
        case(22)://<
        {
            tree.update_range(0,key-1,num_rows,positions,types,obj,values);
            break;
        }
        case(26)://=
        {
            tree.update_range(key,key,num_rows,positions,types,obj,values);
            break;
        }
        case(29)://<=
        {
            tree.update_range(0,key,num_rows,positions,types,obj,values);
            break;
            
        }
        case(30)://>=
        {
            tree.update_range(key,__UINT32_MAX__,num_rows,positions,types,obj,values); 
           break;
           
        }
        case(14):
        {
            tree.update_range(key,atof(identifiers.at(identifiers.size()-1).c_str()),num_rows,positions,types,obj,values);
            break;
        }
    }
    }
    }else{
        if(obj->tree_ind.info.rel.rows[obj->tree_ind.info.index].key_type == 'f'){
            float key{};
            key = atof(value.c_str());
    

        switch(op){
            case(21)://>
            {
            tree.update_index_range(key+__FLT16_MIN__,__FLT32_MAX__,num_rows,positions,types,obj,values);
             break; 
            }
            case(22)://<
            {
                tree.update_index_range(0.0,key-__FLT16_MIN__,num_rows,positions,types,obj,values);
                break;
            }
            case(26)://=
            {
                tree.update_index_range(key,key,num_rows,positions,types,obj,values);
                break;
            }
            case(29)://<=
            {
                tree.update_index_range(0.0,key,num_rows,positions,types,obj,values);
                break;
            
            }
            case(30)://>=
            {
                tree.update_index_range(key,__FLT32_MAX__,num_rows,positions,types,obj,values); 
                break;
            }
            case(14):
            {
            tree.update_index_range(key,atof(identifiers.at(identifiers.size()-1).c_str()),num_rows,positions,types,obj,values);
            break;
            }
        }
    }else{
        uint32_t key{};
    key = atoi(value.c_str());
    switch(op){
        case(21)://>
        {
           tree.update_index_range(key+1,__UINT32_MAX__,num_rows,positions,types,obj,values);
           break; 
        }
        case(22)://<
        {
            tree.update_index_range(0,key-1,num_rows,positions,types,obj,values);
            break;
        }
        case(26)://=
        {
            tree.update_index_range(key,key,num_rows,positions,types,obj,values);
            break;
        }
        case(29)://<=
        {
            tree.update_index_range(0,key,num_rows,positions,types,obj,values);
            break;
            
        }
        case(30)://>=
        {
            tree.update_index_range(key,__UINT32_MAX__,num_rows,positions,types,obj,values); 
           break;
        }
        case(14):
        {
            tree.update_index_range(key,atof(identifiers.at(identifiers.size()-1).c_str()),num_rows,positions,types,obj,values);
            break;
        }
    }
    }
    }
}

void update_all(std::string table_name, Run* obj, std::vector<std::string>identifiers){
     uint16_t key = obj->tree_attr.calc_name(table_name.c_str());
    obj->tree_ind.search_range_catalog(key,key,48);
    obj->tree_rel.search_range_catalog(key,key,28);
    for(size_t i = 0;i<obj->tree_rel.rows.size();i++){
        if(strcmp(obj->database.c_str(),obj->tree_rel.rows.at(i).rel_file)){
            obj->tree_ind.info.index+=i;
            obj->tree_rel.info.index+=i;
        }
    }
    obj->tree_attr.search_range_catalog(key,key,30);
    std::vector<uint16_t>positions{};
    std::vector<char>types{};
    std::vector<std::string>values{};
    Bp_Tree tree{};
    bool index_update{};
    for(size_t i = 1; i<identifiers.size()-2;i+=2){
        for(auto row:obj->tree_attr.rows){
            if(std::string{row.attr_name} == identifiers.at(i)){
                if(row.position == 0)
                index_update = true;
            positions.push_back(row.position);
            types.push_back(row.type);
            break;
            }
        }
        
    }

    for(size_t i = 2; i<identifiers.size()-2;i+=2){
        values.push_back(identifiers.at(i));
    }
    uint16_t num_rows = 4087/tree.info.relation.row_size;
    if(!index_update){
    if(obj->tree_ind.info.rel.rows[obj->tree_ind.info.index].key_type == 'f'){
        tree.update_range(0.0,__FLT32_MAX__,num_rows,positions,types,obj,values);
    }else{
        tree.update_range(0,__UINT32_MAX__,num_rows,positions,types,obj,values);
    }
    }else{
        if(obj->tree_ind.info.rel.rows[obj->tree_ind.info.index].key_type == 'f'){
        tree.update_index_range(0.0,__FLT32_MAX__,num_rows,positions,types,obj,values);
    }else{
        tree.update_index_range(0,__UINT32_MAX__,num_rows,positions,types,obj,values);
    }

    }
}