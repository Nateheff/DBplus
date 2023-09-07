#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include <unordered_map>
#define NUM_KEYWORDS 13

// #define KEYWORD(keyname, key_token_val)

typedef struct Keyword_List{
    std::unordered_map<std::string,uint16_t>kws;
    int num_kw;
    int max_leng;

}Keyword_List;

// kw_tok add_arr[NUM_KEYWORDS]{BOOL,CHAR,CREATE,DB,FLOAT,FROM,INSERT,INT,KEY,PRIMARY,SELECT,TABLE,VARCHAR};



