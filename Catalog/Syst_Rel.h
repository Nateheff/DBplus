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
typedef struct{
    char rel_name [64]{};
    char rel_file [64]{};
    char* row_type;
    uint16_t num_pages{};
    uint32_t num_rows{};
    uint16_t num_attrs{};
    char kind;
    uint16_t row_size{};
    }System_Rel_Row;

struct Syst_Rel{
    uint16_t page_id{};
    uint8_t is_index{0};
    uint32_t bottom_p{};
    System_Rel_Row rows[4089/sizeof(System_Rel_Row)]; //array of them
    char padding [4096 - (sizeof(rows)+14)];
};