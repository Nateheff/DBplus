#include "run.h"


bool Run::run(){
    Catalog_Index catalog_ind{};
    Catalog_Rel catalog_rel{};
    Catalog_Attr catalog_attr{};
    // std::string str{"catalog_ind"};
    // std::string str2{"catalog_rel"};
    // B_Tree<Syst_Index,Syst_Index_Row>tree_ind(str);
    // B_Tree<Syst_Rel,System_Rel_Row>tree_rel(str2);
  
    catalog_ind.create_catalog();
    catalog_attr.create_catalog();
    catalog_rel.create_catalog(); 
    
    catalog_ind.has_height();
    // std::cout<<"got height"<<catalog_ind.height<<std::endl;
    
    
    tree_ind.height = catalog_ind.height;
    std::cout<<"here ind"<<std::endl;
    tree_ind.search_catalog(1149,48);
    tree_rel.height = tree_ind.info.rel.rows[tree_ind.info.index].ind_height;
    tree_ind.search_catalog(1269,48);
    tree_attr.height = tree_ind.info.rel.rows[tree_ind.info.index].ind_height;
    // std::cout<<"ran "<<tree_attr.height<<" "<<tree_rel.height<<std::endl;
    //1141
    return true;
    
}
/*

*/
Run::~Run(){
    std::fstream fs;
    if(tree_ind.dirty && tree_rel.dirty){
        fs.seekp(tree_ind.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_ind.info.rel), sizeof(Syst_Index));
        fs.seekp(tree_rel.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_rel.info.rel),sizeof(Syst_Rel));
    }
    else if(tree_ind.dirty){
        fs.seekp(tree_ind.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_ind.info.rel), sizeof(Syst_Index));
    }else if(tree_rel.dirty){
        fs.seekp(tree_rel.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_rel.info.rel),sizeof(Syst_Rel));
    }
    // std::cout<<"closed"<<std::endl;
}