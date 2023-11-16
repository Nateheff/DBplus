#pragma once
#include <stdint.h>



typedef struct{
        uint32_t key{};
        uint32_t pointer{};
}Key_Pointer;

typedef struct{
        float key{};
        uint32_t pointer{};
}Key_Pointer_f;

typedef struct {
        
        uint16_t page_id{};
        uint8_t next_index{1};
        uint32_t bottom_p{};
        Key_Pointer arr[4089/sizeof(Key_Pointer)];
        
}Syst_Root;

typedef struct {
        
        uint16_t page_id{};
        uint8_t next_index{1};
        uint32_t bottom_p{};
        Key_Pointer_f arr[4089/sizeof(Key_Pointer)];
        
}Syst_Root_f;


