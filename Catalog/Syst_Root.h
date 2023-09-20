#pragma once
#include <stdint.h>



typedef struct{
        uint16_t key{};
        uint32_t pointer{};
}Key_Pointer;

typedef struct {
        
        uint16_t page_id{};
        uint8_t next_index{1};
        uint32_t bottom_p{};
        Key_Pointer arr[4089/sizeof(Key_Pointer)];
        
}Syst_Root;


