
#include "FSM.h"

bool FSM::create_fsm(std::string name){
    data.free_page = 0;
    data.hole = 0;
    data.free_space[0] = 1;
    data.free_space[1]=1;
    std::fstream fs;
    fs.open(name+"_fsm.db",std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    fs.write(reinterpret_cast<char*>(&data),sizeof(data));
    fs.close();
};

void FSM::get_fsm(std::string name, FSM_Data* fsm){
    std::fstream fs;
    fs.open(name+"_fsm.db",std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    fs.read(reinterpret_cast<char*>(fsm),sizeof(*fsm));
    fs.close();
}

void FSM::flush_fsm(std::string name){
    std::fstream fs;
    fs.open(name+"_fsm.db",std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    fs.write(reinterpret_cast<char*>(&data),sizeof(data));
}