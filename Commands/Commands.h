#pragma once
#include <vector>
#include <string>
#include <stdint.h>
#include <fstream>

#include "../run.h"

struct type_size{
    uint16_t size{};
    char type;
};

type_size attr_info(uint16_t token);
void create_db(std::string name);
void create_table(std::string table_name, std::vector<uint16_t>full_tok, std::vector<std::string>identifiers,size_t ft_size,size_t id_size,Keyword_List*list,Run* obj);
