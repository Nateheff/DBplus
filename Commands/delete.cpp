#include "Commands.h"
// #include "../Nodes/Node.h"
#include "../B+_Tree.h"

void delete_row(std::string table_name,std::vector<std::string>identifiers,Run* obj){
    Bp_Tree tree{};
    Row row{};
   
   uint32_t key{};
    tree.info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    tree.info.ind = &obj->tree_ind.info.rel.rows[obj->tree_rel.info.index];
    switch(tree.info.ind->key_type){
        case 's':
        case 'i':
        case 'b':
        {
        // std::cout<<"int/short/bool"<<std::endl;
        key = atoi(identifiers.at(2).c_str());
        break;
        }
        case('f'):
        {
        key = atof(identifiers.at(2).c_str());
        break;
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
    

    if(ind->ind_start == 0){
        
        fs.open(rel->rel_file,std::ios_base::binary|std::ios_base::out);
        Curr_Node empty;
        fs.write(reinterpret_cast<char*>(&empty),sizeof(empty));

    }else if(ind->ind_start > 0){
        Syst_Root dump{};
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