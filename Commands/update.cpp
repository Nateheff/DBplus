#include "Commands.h"
#include "../B+_Tree.h"


void update(std::string table_name,Run*obj,std::vector<std::string>identifiers,uint16_t op, std::string value,std::string v_2){
    uint16_t key = obj->tree_attr.calc_name(table_name.c_str());
    std::cout<<"comp up"<<table_name<<" "<<key<<" "<<op<<std::endl;
    obj->tree_ind.search_catalog(key,48);
    std::cout<<"searched ind"<<std::endl;
    obj->tree_rel.search_catalog(key,28);
    std::cout<<"search rel"<<std::endl;
    obj->tree_attr.search_range_catalog(key,key,30);
    
    std::cout<<"post searches"<<std::endl;
    std::vector<uint16_t>positions{};
    std::vector<char>types{};
    std::vector<std::string>values{};
    Bp_Tree tree{};
    tree.info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    tree.info.ind = &obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
    // std::cout<<"pre loop "<<tree.info.relation.row_size<<std::endl;
    bool index_update{};
    for(size_t i = 1; i<identifiers.size()-2;i+=2){
        // std::cout<<i<<" "<<obj->tree_attr.rows.size()<<std::endl;
        for(auto row:obj->tree_attr.rows){
            
            // std::cout<<std::string{row.attr_name}<<" "<<identifiers.at(i)<<std::endl; 
            if(std::string{row.attr_name} == identifiers.at(i)){
                if(row.position == 0){
                    index_update = true;
                    std::cout<<"attr "<<row.attr_name<<std::endl;
                }
            positions.push_back(row.position);
            types.push_back(row.type);
            break;
            }
        }
        
    }
    std::cout<<"post first loop "<<identifiers.at(identifiers.size()-2)<<" "<<identifiers.at(identifiers.size()-1)<<std::endl;
    for(size_t i = 2; i<identifiers.size()-1;i+=2){
        values.push_back(identifiers.at(i));
    }
    uint16_t num_rows = 4087/tree.info.relation.row_size;
    std::cout<<op<<std::endl;
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
            std::cout<<"between"<<std::endl;
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
            std::cout<<"between"<<std::endl;
            tree.update_range(key,atof(identifiers.at(identifiers.size()-1).c_str()),num_rows,positions,types,obj,values);
            break;
        }
    }
    }
    }else{
        std::cout<<"updating INDEX"<<std::endl;
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
            std::cout<<"between"<<std::endl;
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
            std::cout<<"between"<<std::endl;
            tree.update_index_range(key,atof(identifiers.at(identifiers.size()-1).c_str()),num_rows,positions,types,obj,values);
            break;
        }
    }
    }
    }
}

void update_all(std::string table_name, Run* obj, std::vector<std::string>identifiers){
     uint16_t key = obj->tree_attr.calc_name(table_name.c_str());
    std::cout<<"comp up all"<<table_name<<key<<std::endl;
    obj->tree_ind.search_catalog(key,48);
    obj->tree_rel.search_catalog(key,28);
    obj->tree_attr.search_range_catalog(key,key,30);
    std::vector<uint16_t>positions{};
    std::vector<char>types{};
    std::vector<std::string>values{};
    Bp_Tree tree{};
    bool index_update{};
    for(size_t i = 1; i<identifiers.size()-2;i+=2){
        // std::cout<<i<<" "<<obj->tree_attr.rows.size()<<std::endl;
        for(auto row:obj->tree_attr.rows){
            // std::cout<<std::string{row.attr_name}<<" "<<identifiers.at(i)<<std::endl; 
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
        std::cout<<" updating index"<<std::endl;
        if(obj->tree_ind.info.rel.rows[obj->tree_ind.info.index].key_type == 'f'){
        tree.update_index_range(0.0,__FLT32_MAX__,num_rows,positions,types,obj,values);
    }else{
        tree.update_index_range(0,__UINT32_MAX__,num_rows,positions,types,obj,values);
    }

    }
}