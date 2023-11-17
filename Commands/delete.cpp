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
           tree.get_range(key+1,UINT32_MAX,num_rows);
           break; 
        }
        case(22)://<
        {
            tree.get_range(0,key-1,num_rows);
            break;
        }
        case(26)://=
        {
            tree.get_range(key,key,num_rows);
            break;
        }
        case(29)://<=
        {
            tree.get_range(0,key,num_rows);
            break;
            
        }
        case(30)://>=
        {
            tree.get_range(key,UINT32_MAX,num_rows); 
           break;
        }
        case(14):
        {
            std::cout<<"between"<<std::endl;
            tree.get_range(key,atoi(identifiers.at(identifiers.size()-1).c_str()),num_rows);
            break;
        }
    }
    
    std::fstream fs;
    fs.open(tree.info.relation.rel_file, std::ios_base::binary|std::ios_base::in|std::ios_base::out);

    for(size_t j = tree.info.index;j<tree.info.pages.at(0).num_rows+tree.info.index;j++){
            memcpy(&tree.info.pages.at(0).page.data[j*tree.info.relation.row_size],row.data.data(),tree.info.relation.row_size);
            fs.seekp(tree.info.pages.at(0).page.page_id*4096+tree.info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&tree.info.pages.at(0).page),sizeof(tree.info.pages.at(0).page));
    }

    if(tree.info.pages.size()>1){

    for(size_t i = 1; i<tree.info.pages.size();i++){
        for(size_t j = 0;j<tree.info.pages.at(i).num_rows;j++){
            memcpy(&tree.info.pages.at(i).page.data[j*tree.info.relation.row_size],row.data.data(),tree.info.relation.row_size);
        }
        fs.seekp(tree.info.pages.at(i).page.page_id*4096+tree.info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&tree.info.pages.at(i).page),sizeof(tree.info.pages.at(i).page));
    }

    

    }
    T_Node* page = &tree.info.pages.at(tree.info.pages.size()-1);
    for(size_t i = 0;i<num_rows;i++){
        memcpy(&page->page.data[i*tree.info.relation.row_size],&page->page.data[(i+page->num_rows)*tree.info.relation.row_size],tree.info.relation.row_size);
    }
    fs.seekp(page->page.page_id*4096+tree.info.ind->ind_start);
    fs.write(reinterpret_cast<char*>(&page->page),sizeof(page->page));
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

    tree.delete_row(key,4087/tree.info.relation.row_size,tree.info.relation.row_size,obj);
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
    

    if(ind->ind_start == 0 && ind->key_type !='f'){
        
        fs.open(rel->rel_file,std::ios_base::binary|std::ios_base::out);
        Curr_Node empty{};
        fs.write(reinterpret_cast<char*>(&empty),sizeof(empty));

    }else if(ind->ind_start > 0){
        Syst_Root dump{};
        fs.open(rel->rel_file,std::ios_base::binary|std::ios_base::out|std::ios_base::in);
        fs.seekp(ind->ind_start);
        fs.write(reinterpret_cast<char*>(&dump),sizeof(dump));
        
    }else
    delete_all_f(table_name,obj);
    *ind = em;
    *rel = empty;
    obj->tree_rel.dirty = true;
    obj->tree_ind.dirty = true;
    fs.close();
}

void delete_all_f(std::string table_name,Run* obj){
    uint16_t key = obj->tree_rel.calc_name(table_name.c_str());
    obj->tree_rel.search_catalog(key,28);
    obj->tree_ind.search_catalog(key,48);
    obj->tree_attr.search_range_catalog(key,key,30);
    Syst_Index_Row em{};
    System_Rel_Row empty{};

    Syst_Index_Row* ind = &obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
    System_Rel_Row* rel = &obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    std::fstream fs;
    

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
    *ind = em;
    *rel = empty;
    obj->tree_rel.dirty = true;
    obj->tree_ind.dirty = true;
    fs.close();
}