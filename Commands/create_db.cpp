#include "Commands.h"

void create_db(std::string name){
    FSM fsm;
    fsm.create_fsm(name);
    std::fstream fs;
    fs.open(name+".db",std::ios_base::binary|std::ios_base::out);
    fs.close();
}