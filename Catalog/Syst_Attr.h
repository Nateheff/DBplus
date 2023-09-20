#pragma once
#include <stdint.h>
#include <string>


/*
attr_name(string)
rel_name(string)
position(int)
type(char)
attr_len(int)
attr_align(char)
*/
typedef struct{
    std::string attr_name;
    std::string rel_name;
    uint16_t position{};
    char type;
    uint8_t attr_len{};
    char attr_align;
    }Syst_Attr_Row;

typedef struct 
{
    uint8_t is_index{0};
    uint16_t last_p{};
    Syst_Attr_Row row;//array of them
    uint16_t next_p{};
};
    




