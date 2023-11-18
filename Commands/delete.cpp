#include "Commands.h"
// #include "../Nodes/Node.h"
#include "../B+_Tree.h"

void delete_row(std::string table_name,std::vector<std::string>identifiers,Run* obj, uint16_t op, std::string value){
    Bp_Tree tree{};
    Row row{};
   
   uint32_t key{};
    tree.info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    tree.info.ind = &obj->tree_ind.info.rel.rows[obj->tree_rel.info.index];
    row.data.resize(tree.info.relation.row_size);
    switch(tree.info.ind->key_type){
        case 's':
        case 'i':
        case 'b':
        {
        // std::cout<<"int/short/bool"<<std::endl;
        key = atoi(identifiers.at(2).c_str());
        break;
        }
        case('f'):{
            delete_row_f(table_name,identifiers,obj,op,value);
            return;
        }
        case('c'):
        {
        key = identifiers.at(2).at(0);
        break;
        }
        case('v'):
        {
        key = obj->tree_attr.calc_name(identifiers.at(2).c_str());
        break;
        }
    }
    

    uint16_t num_rows = 4087/tree.info.relation.row_size;
    switch(op){
        case(21)://>
        {
           tree.delete_range(key+1,UINT32_MAX,num_rows,row);
           break; 
        }
        case(22)://<
        {
            tree.delete_range(0,key-1,num_rows,row);
            break;
        }
        case(26)://=
        {
            tree.delete_range(key,key,num_rows,row);
            break;
        }
        case(29)://<=
        {
            tree.delete_range(0,key,num_rows,row);
            break;
            
        }
        case(30)://>=
        {
            tree.delete_range(key,UINT32_MAX,num_rows,row); 
           break;
        }
        case(14):
        {
            std::cout<<"between"<<std::endl;
            tree.delete_range(key,atoi(identifiers.at(identifiers.size()-1).c_str()),num_rows,row);
            break;
        }
    }
    
    // tree.delete_row(obj,tree.info.index,tree.info.index_last);
    // tree.delete_row(key,4087/tree.info.relation.row_size,tree.info.relation.row_size,obj);
}

void delete_row_f(std::string table_name,std::vector<std::string>identifiers,Run* obj, uint16_t op, std::string value){
    Bp_Tree tree{};
    Row row{};
   
   float key{};
    tree.info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    tree.info.ind = &obj->tree_ind.info.rel.rows[obj->tree_rel.info.index];
    if(tree.info.ind->key_type != 'f'){
    delete_row(table_name,identifiers,obj,op,value);
    return;
    }
    key = atof(identifiers.at(2).c_str());
    row.data.resize(tree.info.relation.row_size);
    uint16_t num_rows = 4087/tree.info.relation.row_size;
    std::cout<<op<<std::endl;
    switch(op){
        case(21)://>
        {
           tree.delete_range(key+__FLT32_MIN__,__FLT32_MAX__,num_rows,row);
           break; 
        }
        case(22)://<
        {
            tree.delete_range(0.0,key-__FLT16_MIN__,num_rows,row);
            break;
        }
        case(26)://=
        {
            tree.delete_range(key,key,num_rows,row);
            break;
        }
        case(29)://<=
        {
            tree.delete_range(0.0,key,num_rows,row);
            break;
            
        }
        case(30)://>=
        {
            tree.delete_range(key,__FLT32_MAX__,num_rows,row); 
           break;
        }
        case(14):
        {
            std::cout<<"between"<<std::endl;
            tree.delete_range(key,atof(identifiers.at(identifiers.size()-1).c_str()),num_rows,row);
            break;
        }
    }


    // tree.delete_row(obj,tree.info.index,tree.info.index_last);
}


void delete_all(std::string table_name,Run* obj){
    uint16_t key = obj->tree_rel.calc_name(table_name.c_str());
    obj->tree_rel.search_catalog(key,28);
    obj->tree_ind.search_catalog(key,48);
    obj->tree_attr.search_range_catalog(key,key,30);
    Syst_Index_Row em{};
    System_Rel_Row empty{};

    Syst_Index_Row* ind = &obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
    System_Rel_Row* rel = &obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    std::fstream fs;
    if(ind->key_type == 'f'){
    delete_all_f(table_name,obj);
    return;
    }
    if(ind->ind_start == 0){
        
        fs.open(rel->rel_file,std::ios_base::binary|std::ios_base::out);
        Curr_Node empty{};
        fs.write(reinterpret_cast<char*>(&empty),sizeof(empty));

    }else if(ind->ind_start > 0){
        Syst_Root dump{};
        fs.open(rel->rel_file,std::ios_base::binary|std::ios_base::out|std::ios_base::in);
        fs.seekp(ind->ind_start);
        fs.write(reinterpret_cast<char*>(&dump),sizeof(dump));
        
    }
    ind->ind_height = 0;
    ind->ind_min = 0;
    ind->ind_max = 0;
    rel->num_pages = 0;
    rel->num_rows = 0;
    obj->tree_rel.dirty = true;
    obj->tree_ind.dirty = true;
    fs.close();
}

void delete_all_f(std::string table_name,Run* obj){
    std::cout<<"delete all float"<<std::endl;
    uint16_t key = obj->tree_rel.calc_name(table_name.c_str());
    obj->tree_rel.search_catalog(key,28);
    obj->tree_ind.search_catalog(key,48);
    obj->tree_attr.search_range_catalog(key,key,30);
    Syst_Index_Row em{};
    System_Rel_Row empty{};

    Syst_Index_Row* ind = &obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
    System_Rel_Row* rel = &obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    std::fstream fs;
    if(ind->key_type != 'f'){
    delete_all(table_name,obj);
    return;
    }
    if(ind->ind_start == 0){
        
        fs.open(rel->rel_file,std::ios_base::binary|std::ios_base::out);
        Curr_Node empty{};
        fs.write(reinterpret_cast<char*>(&empty),sizeof(empty));

    }else if(ind->ind_start > 0){
        Syst_Root_f dump{};
        fs.open(rel->rel_file,std::ios_base::binary|std::ios_base::out|std::ios_base::in);
        fs.seekp(ind->ind_start);
        fs.write(reinterpret_cast<char*>(&dump),sizeof(dump));
        
    }
    ind->ind_height = 0;
    ind->ind_min = 0;
    ind->ind_max = 0;
    rel->num_pages = 0;
    rel->num_rows = 0;
    obj->tree_rel.dirty = true;
    obj->tree_ind.dirty = true;
    fs.close();
}