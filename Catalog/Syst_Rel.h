#pragma once

#include "Syst_Root.h"
#include "../Disk_Space/FSM.h"
#include <cstring>
#include <vector>
/*
rel_name(string)
rel_file(string)
row_type(special(probably char array))
num_pages(int)
num_rows(int)
num_attrs(int)
kind(char(index,normal,etc.))
row_size(int)
*/

 struct System_Rel_Row{
    char index[63]={};
    char rel_file[63]={};
    uint16_t num_pages{};
    uint32_t num_rows{};
    uint16_t check{};//num_attrs
    char kind;
    uint16_t row_size{};
    };

struct Syst_Rel{
    uint32_t page_id{};
    uint8_t is_index{};
    uint32_t bottom_p{};
    System_Rel_Row rows[4089/sizeof(System_Rel_Row)]; //array of them
    char padding [24]{};
};
typedef struct {
    uint16_t index{};
    uint16_t index_root{};
    Syst_Root root;
    Syst_Rel rel;
    std::fstream* fs;
    std::vector<uint32_t> offsets;
    

}Info_Pack_Rel;

class Catalog_Rel{
    public:
Info_Pack_Rel info;
FSM fsm;
void create_catalog();
};