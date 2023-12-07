#include "run.h"


bool Run::run(){
    std::fstream fs;
    fs.open("databases.txt",std::ios_base::out|std::ios_base::in|std::ios_base::binary|std::ios_base::ate);
    if(fs.tellp()>0){
    begin();
    return true;
    }else{
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
    
    
    tree_ind.height = catalog_ind.height;
    tree_ind.search_catalog(1149,48);
    tree_rel.height = tree_ind.info.rel.rows[tree_ind.info.index].ind_height;
    tree_ind.search_catalog(1269,48);
    tree_attr.height = tree_ind.info.rel.rows[tree_ind.info.index].ind_height;
    
    std::fstream fs;
    fs.open("databases.txt",std::ios_base::out|std::ios_base::binary);
    fs.close();
    return true;
    }
}

void Run::begin(){
    Catalog_Index catalog_ind{};
    catalog_ind.has_height();
    
    
    tree_ind.height = catalog_ind.height;
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
        
        fs.open("catalog_ind.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_ind.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_ind.info.rel), sizeof(Syst_Index));
        fs.close();
        fs.open("catalog_rel.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_rel.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_rel.info.rel),sizeof(Syst_Rel));
        fs.close();

    }
    else if(tree_ind.dirty){
        fs.open("catalog_ind.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_ind.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_ind.info.rel), sizeof(Syst_Index));
        fs.close();
    }else if(tree_rel.dirty){
        fs.open("catalog_rel.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_rel.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_rel.info.rel),sizeof(Syst_Rel));
        fs.close();
    }
    tree_rel.dirty = false;
    tree_ind.dirty = false;
}
Run::~Run(){
    std::fstream fs;

    if(tree_ind.dirty && tree_rel.dirty){
        fs.open("catalog_ind.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_ind.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_ind.info.rel), sizeof(Syst_Index));
        fs.close();
        fs.open("catalog_rel.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_rel.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_rel.info.rel),sizeof(Syst_Rel));
        fs.close();

    }
    else if(tree_ind.dirty){
        fs.open("catalog_ind.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_ind.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_ind.info.rel), sizeof(Syst_Index));
        fs.close();
    }else if(tree_rel.dirty){
        fs.open("catalog_rel.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(tree_rel.info.rel.page_id*4096);
        fs.write(reinterpret_cast<char*>(&tree_rel.info.rel),sizeof(Syst_Rel));
        fs.close();
    }
}