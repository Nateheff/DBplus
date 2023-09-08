#pragma once
#include <stdint.h>
#include <string>
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

class Syst_Rel{
    typedef struct{
    std::string rel_name;
    std::string rel_file;
    char row_type[0];
    uint16_t num_pages{};
    uint32_t num_rows{};
    uint16_t num_attrs{};
    char kind;
    uint16_t row_size{};
    }System_Rel_Row;
    public:
    
};