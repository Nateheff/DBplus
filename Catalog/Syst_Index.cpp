#include "Syst_Index.h"

void Catalog_Index::create_catalog(B_Tree<Syst_Index,Syst_Index_Row>* tree_ind){
    std::string name = {"catalog_ind"};
    
    
    // std::cout<<"t: "<<tree.calc_name(name.c_str())<<std::endl;
    
    Syst_Index root;
    Syst_Index_Row ind{};
    Syst_Index_Row attr{};
    Syst_Index_Row rel{};
    uint16_t ind_ind = tree_ind->calc_name(name.c_str());
    uint16_t ind_rel = tree_ind->calc_name("catalog_rel");
    uint16_t ind_attr = tree_ind->calc_name("catalog_attr");
    std::cout<<"1 "<<std::endl;
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
    attr.key_type = 's';

std::cout<<ind_ind<<" "<<ind_rel<<" "<<ind_attr<<std::endl;
    root.rows[0] = ind;
    root.rows[1] = rel;
    root.rows[2] = attr;
    std::ofstream fs;
    std::cout<<"2"<<std::endl;
    fs.open(name+".db",std::ios_base::binary|std::ios_base::out);
    fs.write(reinterpret_cast<char*>(&root),sizeof(root));
    std::cout<<"3 "<<fs.tellp()<<std::endl;
    fs.close();
    FSM fsm;
    fsm.create_fsm(name);
    std::cout<<"4"<<std::endl;
    return;    
}

void Catalog_Index::has_height(){
std::fstream fs;
fs.open("catalog_ind.db",std::ios_base::binary|std::ios_base::in|std::ios_base::out|std::ios_base::ate);


height = (fs.tellp() > 4096);
}