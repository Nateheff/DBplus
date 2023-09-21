#pragma once
#include <stdint.h>
#include <fstream>
#include <iostream>

const int MAX_PAGES = 130814951;
// const int MAX_PAGES = 2100000;
typedef struct{
    uint8_t hole{};
    uint16_t free_page{1};
    uint8_t* free_space = new uint8_t[MAX_PAGES - (sizeof(hole)+sizeof(free_page))];
    }FSM_Data;
class FSM 
{
    
    FSM_Data data;
    public: 
    bool create_fsm(std::string name);
    uint8_t is_hole(){return data.hole;};
    void set_hole(uint8_t num){data.hole=num;};
    uint16_t page(){return data.free_page;};
    void set_page(uint16_t page_num){data.free_page = page_num;};
    uint8_t has_space(uint16_t page_num){return (data.free_space[page_num]==1);};
    void set_space(uint16_t page_num,uint8_t space){data.free_space[page_num] = space;};
    void delete_space(){delete[] data.free_space;};
    void get_fsm(std::string name, FSM_Data* fsm);
    FSM_Data* access_data(){return &data;}
    void flush_fsm(std::string name);
    void calc_free(){for(size_t i= 0;i<MAX_PAGES - (sizeof(data.hole)+sizeof(data.free_page));i++){if(data.free_space[i]>1) {data.free_page = i+1;return;}}}
};

