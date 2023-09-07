#pragma once
#include <stdint.h>
#include <fstream>
#include <iostream>

const int MAX_PAGES = 130814951;
// const int MAX_PAGES = 2100000;
class FSM 
{
    
    uint8_t hole{};
    uint16_t free_page{1};
    uint8_t* free_space = new uint8_t[MAX_PAGES - (sizeof(hole)+sizeof(free_page))];

    public: 
    bool create_fsm(std::string name);
    uint8_t is_hole(){return hole;};
    void set_hole(uint8_t num){hole=num;};
    uint16_t page(){return free_page;};
    void set_page(uint16_t page_num){free_page = page_num;};
    uint8_t has_space(uint16_t page_num){return free_space[page_num];};
    void set_space(uint16_t page_num,uint8_t space){free_space[page_num] = space;};
    void delete_space(){delete[] free_space;};
};