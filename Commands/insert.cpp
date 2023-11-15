#include "Commands.h"
#include "../Nodes/Node.h"
#include "../B+_Tree.h"

void insert(std::string table_name,std::vector<std::string>identifiers,Run* obj){
    Bp_Tree tree{};
    Row row{};
   
    create_tuple(table_name,obj,&row,identifiers);
    // std::cout<<"a "<<table_name<<std::endl;
    // for(size_t i = 0;i<14;i++)
    // std::cout<<row.data.data()[i];
    // std::cout<<std::endl;
    // std::cout<<row.index<<std::endl;
    // std::cout<<row.data.data()<<" a "<<row.index<<std::endl; 
    tree.info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    tree.info.ind = &obj->tree_ind.info.rel.rows[obj->tree_rel.info.index];
    tree.insert(row.index,(4087/tree.info.relation.row_size),tree.info.relation.row_size,obj,row);
    // std::cout<<"returned"<<std::endl;
    // for(size_t i = 0;i<identifiers.size()-1;i++){
    //     std::cout<<row.data.at(i).size()<<": "<<row.data.at(i).data()<<std::endl;
    // }
    
}