#include "Syst_Index.h"
#include "../Disk_Space/FSM.h"

uint16_t Catalog_Index::calc_name(const char* arr){
    uint16_t name{};
    for(size_t i = 0;i<strlen(arr);i++)
    name += arr[i];
    
    return name;
}

void Catalog_Index::create_catalog(){
    std::string name = {"catalog_ind"};
    
    Syst_Index root;
    Syst_Index_Row ind{};
    Syst_Index_Row attr{};
    Syst_Index_Row rel{};
    uint16_t ind_ind = calc_name(name.c_str());
    uint16_t ind_rel = calc_name("catalog_rel");
    uint16_t ind_attr = calc_name("catalog_attr");
    
    ind.check = 1;
    strcpy(ind.index,"catalog_ind");
    ind.key_type = 's';
    ind.num_keys = 3;
    ind.ind_min = ind_attr;
    ind.ind_max = ind_rel;
    
    attr.check = 1;
    strcpy(attr.index,"catalog_attr");
    attr.key_type = 's';
    
    rel.check = 1;
    strcpy(rel.index,"catalog_rel");
    rel.key_type = 's';


    root.rows[0] = ind;
    root.rows[1] = rel;
    root.rows[2] = attr;
    std::ofstream fs;
    
    fs.open(name+".db",std::ios_base::binary|std::ios_base::out);
    fs.write(reinterpret_cast<char*>(&root),sizeof(root));
    
    fs.close();
    FSM fsm;
    fsm.create_fsm(name);
    
    return;    
}

void Catalog_Index::has_height(){
std::fstream fs;
fs.open("catalog_ind.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out|std::ios_base::ate);


height = (fs.tellp() > 4096);
}