#include "Commands.h"

#include "../B+_Tree.h"

void insert(std::string table_name,std::vector<std::string>identifiers,Run* obj){
    Bp_Tree tree{};
    Row row{};
    float key{};
    uint16_t key_c = obj->tree_rel.calc_name(table_name.c_str());
    obj->tree_rel.search_range_catalog(key_c,key_c,28);
    obj->tree_ind.search_range_catalog(key_c,key_c,48);
    for(size_t i = 0;i<obj->tree_rel.rows.size();i++){
        if(strcmp(obj->database.c_str(),obj->tree_rel.rows.at(i).rel_file)){
            obj->tree_ind.info.index+=i;
            obj->tree_rel.info.index+=i;
        }
    }
    tree.info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    tree.info.ind = &obj->tree_ind.info.rel.rows[obj->tree_rel.info.index];
   if(tree.info.ind->key_type=='f'){
    key = create_tuple_f(table_name,obj,&row,identifiers);
    tree.insert(key,(4087/tree.info.relation.row_size),tree.info.relation.row_size,obj,row);
   }
    else{
    create_tuple(table_name,obj,&row,identifiers);
    tree.insert(row.index,(4087/tree.info.relation.row_size),tree.info.relation.row_size,obj,row);
    }
    // std::cout<<"a "<<table_name<<std::endl;
    // for(size_t i = 0;i<14;i++)
    // std::cout<<row.data.data()[i];
    // std::cout<<std::endl;
    // std::cout<<row.index<<std::endl;
    // std::cout<<row.data.data()<<" a "<<row.index<<std::endl; 
    
    
    // std::cout<<"returned"<<std::endl;
    // for(size_t i = 0;i<identifiers.size()-1;i++){
    //     std::cout<<row.data.at(i).size()<<": "<<row.data.at(i).data()<<std::endl;
    // }
    
}