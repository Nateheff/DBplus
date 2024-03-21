#include "run.h"

/*
    run()

    This function does all the prep and setup when the program is initially ran. It open databases.txt which is our system's very groteque method of keeping track of user databases. 
    If the user has a database, the function will print out all their databases and they can choose to work in a preexisting database or create a new one.
    If the user has no previous databases (most likely this is their first time running the program), the function will create all of the necessary catalog files.
*/
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

/*
    begin()

    This function uses the information in catalog_ing to get the heights of each of the catalogs so that they can be searched. 
*/
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
    flush()

    If the user has made any changes to any of the catalogs, the catalog will be labeled "dirty" and will be rewritten to the file overriding the old data. Otherwise, the catalog pages just go out of memory and the disk information is unchanged.
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

/*
    Basically the same as flush() above
*/
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