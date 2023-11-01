#pragma once
#include <stdint.h>
#include <fstream>
#include <iostream>

const int MAX_PAGES = 130814951;
// const int MAX_PAGES = 2100000;
// typedef struct{
// uint32_t key{};
// uint32_t pointer{};
// }Key_Pointer;

// typedef struct{
// bool is_root{};
// uint32_t free_page{};
// uint16_t bottom_p{};
// Key_Pointer data[4092/8];

// }FSM_Root;

typedef struct{
    uint32_t num_pages{};
    uint32_t hole{};
    uint8_t free_space[4088] = {0};
}FSM_Data_Root;

typedef struct{
    uint8_t free_space[4096] = {};
}FSM_Data;
class FSM 
{
    std::string name;
    FSM_Data_Root root{};
    FSM_Data* data;
    public: 
    bool create_fsm(std::string name);
    void new_page();
    bool get_fsm(std::string name);
    uint32_t page();
    void set_space(uint32_t page_num,uint8_t space);
    void flush_fsm(uint32_t page_num);
    uint8_t has_space(uint32_t page_num);
    bool has_root(){ return root.num_pages!=0;}
    // uint8_t is_hole(){return data.hole;};
    // void set_hole(uint8_t num){data.hole=num;};
    // uint16_t page(){return data.free_page;};
    // void set_page(uint16_t page_num){data.free_page = page_num;};
    // bool has_space(uint16_t page_num){return (data.free_space[page_num]==1);};
    // void set_space(uint16_t page_num,uint8_t space){data.free_space[page_num] = space;};
    // void delete_space(){delete[] data.free_space;};
    // void get_fsm(std::string name, FSM_Data* fsm);
    // FSM_Data* access_data(){return &data;}
    // 
    // void calc_free(){for(size_t i= 0;i<MAX_PAGES - (sizeof(data.hole)+sizeof(data.free_page));i++){if(data.free_space[i]>1) {data.free_page = i+1;return;}}}
    
};

