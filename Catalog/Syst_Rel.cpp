#include "Syst_Rel.h"


void Catalog_Rel::create_catalog(){
    std::string name = {"catalog_rel"};
   
    std::fstream fs;
    fs.open(name+".db",std::ios_base::binary|std::ios_base::out);
    Syst_Rel root{};

    System_Rel_Row rel{};
    System_Rel_Row attr{};
    System_Rel_Row ind{};

    rel.check = 7;
    strcpy(rel.index,"catalog_rel");
    rel.num_pages = 1;
    rel.num_rows = 3;
    strcpy(rel.rel_file,"catalog_rel.db");
    rel.row_size = sizeof(System_Rel_Row);
    
    ind.check = 7;
    strcpy(ind.index,"catalog_ind");
    ind.num_pages = 1;
    ind.num_rows = 3;
    strcpy(ind.rel_file,"catalog_ind.db");
    ind.row_size = 84;

    attr.check = 5;
    strcpy(attr.index,"catalog_attr");
    attr.num_pages = 1;
    attr.num_rows = 20;
    strcpy(attr.rel_file,"catalog_attr.db");
    attr.row_size= 132;

    root.rows[0] = ind;
    root.rows[1] = rel;
    root.rows[2] = attr;
    fs.write(reinterpret_cast<char*>(&root),sizeof(root));
    
    fs.close();
    
    fsm.create_fsm(name);
    return;
};

