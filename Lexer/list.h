#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <string>

typedef struct Keyword_List{
    std::unordered_map<std::string,uint16_t>kws;
    int num_kw;
    int max_leng;

}Keyword_List;

struct KW_OP{
    static struct Keyword_List res_list;
    static std::unordered_map<std::string,uint16_t>operators;
};
//These are all of the supported keywords and their token values
// extern Keyword_List res_list;

    //All of the supported operators and their token values
// extern std::unordered_map<std::string,uint16_t>operators;



