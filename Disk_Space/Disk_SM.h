#pragma once
#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
/*
#include "FSM.h"
#include "../Nodes/Node.h"

class Disk_SM
{
    private:
    std::string file;
    uint16_t num_pages{};
    uint16_t offset_free{};
    FSM fsm;
public:


    Disk_SM(std::string);
    
    ~Disk_SM(){std::cout<<"calling"<<std::endl;};

    
    bool free_page(uint16_t page_num);
    uint16_t write_new_page();
    bool write_page(Node* page,uint16_t page_num);
    bool read_page(uint16_t page_num,Node* maybe);
    bool get_catalog(); //we use to get the info we need for the file from the catalog. probably create some special struct to save the info it gets so we can access it in our other methods.
    uint16_t page(){return fsm.page();};
    void overwrite(uint16_t page_num);
};


*/