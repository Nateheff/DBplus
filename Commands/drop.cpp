#include "Commands.h"

void drop_db(std::string file, Run* obj){
    remove(file.c_str());
}

void drop_table(std::string table_name, Run* obj){
    uint16_t key = obj->tree_rel.calc_name(table_name.c_str());
    obj->tree_rel.remove_catalog(key,28);
    obj->tree_ind.remove_catalog(key,48);
    std::string fsm{table_name+"_fsm.db"};
    obj->tree_attr.remove_catalog(key,30);
    remove(fsm.c_str());
}