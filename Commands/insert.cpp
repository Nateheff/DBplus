#include "Commands.h"
#include "../Nodes/Node.h"
#include "../B+_Tree.h"

void insert(std::string table_name,std::vector<std::string>identifiers,Run* obj){
    Bp_Tree tree{};
    Row row{};
   
    create_tuple(table_name,obj,&row,identifiers);
    std::cout<<"a "<<table_name<<std::endl;
    std::cout<<row.data.data()<<" "<<row.index<<std::endl;
    tree.info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    tree.search(row.index,tree.info.relation.num_rows,tree.info.relation.row_size,obj);
    std::cout<<tree.info.index<<std::endl;
    // for(size_t i = 0;i<identifiers.size()-1;i++){
    //     std::cout<<row.data.at(i).size()<<": "<<row.data.at(i).data()<<std::endl;
    // }
    
}