#pragma once
#include <stdint.h>
#include <string>

/*
ind_name(string)
ind_height(int)
key_type(char)
ind_size(int)
ind_min(ind_type)
ind_max(ind_type)
num_keys(int)
*/
class Syst_Index
{
    typedef struct{
    std::string ind_name{};
    uint8_t ind_height{};
    char key_type;
    uint16_t ind_size{};
    uint32_t ind_min{};
    uint32_t ind_max{};
    uint32_t num_keys{};
    }Syst_Index_Row;
    public:
};