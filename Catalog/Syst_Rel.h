#pragma once
#include "Syst_Catalog.h"
#include "Syst_Root.h"
#include "../Disk_Space/FSM.h"
#include <cstring>
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
typedef struct{
    char rel_name[64]={};
    char rel_file[64]={};
    char* row_type;
    uint16_t num_pages{};
    uint32_t num_rows{};
    uint16_t num_attrs{};
    char kind;
    uint16_t row_size{};
    }System_Rel_Row;

struct Syst_Rel{
    uint32_t page_id{};
    uint8_t is_index{};
    uint32_t bottom_p{};
    System_Rel_Row rows[4089/sizeof(System_Rel_Row)]; //array of them
    char padding [4096 - (sizeof(rows)+20)]{};
};
typedef struct {
    uint16_t index{};
    uint16_t index_root{};
    Syst_Root root;
    Syst_Rel rel;
    std::fstream* fs;
    std::vector<uint32_t> offsets;
    

}Info_Pack;

class Catalog_Rel:public Syst_Catalog{
    public:
Info_Pack info;
FSM fsm;

void search_rel(uint16_t key,bool has_height);
void remove_rel(uint16_t key,Info_Pack* pack);
void insert_rel(uint16_t key, System_Rel_Row row,size_t test);
void create_catalog();
~Catalog_Rel(){info.fs->close(); std::cout<<"closing"<<std::endl;};
};