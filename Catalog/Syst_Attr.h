#pragma once
#include "Syst_Catalog.h"
#include "Syst_Root.h"
#include "../Disk_Space/FSM.h"

/*
attr_name(string)
rel_name(string)
position(int)
type(char)
attr_len(int)
attr_align(char)
*/

typedef struct{
    char index[64]={}; //attr_name
    char attr_name[64]={};
    uint16_t position{};
    char type;
    uint8_t attr_len{};
    char attr_align;
    }Syst_Attr_Row;

typedef struct 
{
    uint32_t page_id{};
    uint8_t is_index{};
    uint32_t next_p{};
    Syst_Attr_Row rows[4089/sizeof(Syst_Attr_Row)];
    
    char padding[4096-(sizeof(rows)+10)];
}Syst_Attr;

typedef struct{
    uint16_t index;
    uint16_t index_first{};
    uint16_t index_last{};
    std::vector<Syst_Attr_Row>data;
    Syst_Attr* attr;
    std::fstream* fs;
    std::vector<uint32_t> offsets;
    std::vector<uint16_t>pg_ids;
    FSM* fsm;
    
}Attr_Info_Pack;

class Catalog_Attr: public Syst_Catalog{
Attr_Info_Pack pack;
public:
Attr_Info_Pack* search_range_attr(uint16_t key,Attr_Info_Pack *pack,uint16_t num,bool has_height = 1);
void remove_range_atrr(uint16_t key, uint16_t num,Attr_Info_Pack* pack);
void insert_range_attr(uint16_t key,std::vector<Syst_Attr_Row>rows,Attr_Info_Pack* pack);
};



