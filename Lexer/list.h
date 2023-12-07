#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include <unordered_map>




typedef struct Keyword_List{
    std::unordered_map<std::string,uint16_t>kws;
    int num_kw;
    int max_leng;

}Keyword_List;


