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
    char rel_name[64];
    char attr_name[64];
    uint16_t position{};
    char type;
    uint8_t attr_len{};
    char attr_align;
    }Syst_Attr_Row;

typedef struct 
{
    uint16_t page_id{};
    uint8_t is_index{0};
    
    Syst_Attr_Row rows[4089/sizeof(Syst_Attr_Row)];
    uint32_t next_p{};
    char padding[4096-(sizeof(rows)+10)];
}Syst_Attr;
    




