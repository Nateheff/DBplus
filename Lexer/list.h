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

//These are all of the supported keywords and their token values
Keyword_List res_list = {{{"bool",0},{"char",1},{"create",2},{"database",3},{"float",4},{"from",5},{"insert",6},{"int",7},{"and",8},{"set",9},{"select",10},{"table",11},{"varchar",12},{"where",13},{"between",14},{"drop",15},{"delete",16},{"update",17},{"short",18},{"into",19}},20,9};

    //All of the supported operators and their token values
std::unordered_map<std::string,uint16_t>operators{{"*",20},{">",21},{"<",22},{"/",23},{"(",24},{")",25},{"=",26},{"+",27},{"-",28},{"<=",29},{">=",30},{"<>",31},{",",32}};
