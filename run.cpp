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
    std::cout<<"got height"<<catalog_ind.height<<std::endl;
    
    
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

void Run::begin(){
    Catalog_Index catalog_ind{};
    catalog_ind.has_height();
    std::cout<<"got height"<<catalog_ind.height<<std::endl;
    
    
    tree_ind.height = catalog_ind.height;
    std::cout<<"here ind"<<std::endl;
    tree_ind.search_catalog(1149,48);
    tree_rel.height = tree_ind.info.rel.rows[tree_ind.info.index].ind_height;
    tree_ind.search_catalog(1269,48);
    tree_attr.height = tree_ind.info.rel.rows[tree_ind.info.index].ind_height;
}
/*

*/

void Run::flush(){
    std::fstream fs;

    if(tree_ind.dirty && tree_rel.dirty){
        
        std::cout<<"tree and rel dirty"<<std::endl;
        fs.open("catalog_ind.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_ind.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_ind.info.rel), sizeof(Syst_Index));
        fs.close();
        fs.open("catalog_rel.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_rel.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_rel.info.rel),sizeof(Syst_Rel));
        fs.close();
        std::cout<<"flushed index and rel"<<std::endl;

    }
    else if(tree_ind.dirty){
        std::cout<<"tree dirty"<<std::endl;
        fs.open("catalog_ind.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_ind.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_ind.info.rel), sizeof(Syst_Index));
        fs.close();
        std::cout<<"flushed index"<<std::endl;
    }else if(tree_rel.dirty){
        std::cout<<"rel dirty"<<std::endl;
        fs.open("catalog_rel.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_rel.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_rel.info.rel),sizeof(Syst_Rel));
        fs.close();
    }
}
Run::~Run(){
    std::fstream fs;

    if(tree_ind.dirty && tree_rel.dirty){
        std::cout<<"tree and rel dirty"<<std::endl;
        fs.open("catalog_ind.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_ind.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_ind.info.rel), sizeof(Syst_Index));
        fs.close();
        fs.open("catalog_rel.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_rel.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_rel.info.rel),sizeof(Syst_Rel));
        fs.close();
        std::cout<<"flushed index and rel"<<std::endl;

    }
    else if(tree_ind.dirty){
        std::cout<<"tree dirty"<<std::endl;
        fs.open("catalog_ind.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_ind.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_ind.info.rel), sizeof(Syst_Index));
        fs.close();
        std::cout<<"flushed index"<<std::endl;
    }else if(tree_rel.dirty){
        std::cout<<"rel dirty"<<std::endl;
        fs.open("catalog_rel.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_rel.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_rel.info.rel),sizeof(Syst_Rel));
        fs.close();
    }
    std::cout<<"closed"<<std::endl;
}