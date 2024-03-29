#include "Commands.h"
#include "../Disk_Space/FSM.h"

void create_db(std::string name, Run* obj){
    obj->database = name+".db";
    FSM fsm;
    fsm.create_fsm(name);
    std::fstream fs;
    fs.open(name+".db",std::ios_base::binary|std::ios_base::out);
    fs.close();
    fs.open("databases.txt",std::ios_base::in|std::ios_base::out|std::ios_base::app);
    fs << name+" ";
    fs.close(); 
}