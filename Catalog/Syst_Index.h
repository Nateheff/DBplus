#pragma once
#include <stdint.h>
#include <string>
#include <fstream>
#include "Syst_Root.h"

#include <cstring>
#include "../B_Tree.h"

/*
ind_name(string)
ind_height(int)
key_type(char)
ind_size(int)
ind_min(ind_type)
ind_max(ind_type)
num_keys(int)
*/

struct Syst_Index_Row
{
    char index[64]={}; //ind_name
    uint8_t ind_height{};
    char key_type;
    uint16_t check{}; //index_size (pages)
    uint32_t ind_min{};
    uint32_t ind_max{};
    uint32_t num_keys{};
    uint32_t ind_start{};
};

struct Syst_Index
{
    
    uint32_t page_id{};
    uint8_t is_index{};
    uint32_t bottom_p{};
    Syst_Index_Row rows[4087/(sizeof(Syst_Index_Row))];//array of them
    char padding[4]{};
    
};

class Catalog_Index{
    
public:
bool height{};
void create_catalog(B_Tree<Syst_Index,Syst_Index_Row>* tree_ind);
void has_height();

};


