#pragma once
#include <vector>
#include <string>
#include <stdint.h>
#include <fstream>
#include <iostream>

#include "../Lexer/list.h"
// #include "../Disk_Space/FSM.h"
// #include "../Catalog/Syst_Attr.h"
// #include "../Catalog/Syst_Index.h"
// #include "../Catalog/Syst_Root.h"
// #include "../Catalog/Syst_Rel.h"

// #include "../B_Tree.h"
// #include "../B_Tree.hh"
#include "../run.h"


struct type_size{
    uint16_t size{};
    char type;
};

type_size attr_info(uint16_t token);
void create_db(std::string name);
void create_table(std::string table_name, std::vector<uint16_t>full_tok, std::vector<std::string>identifiers,size_t ft_size,size_t id_size,Keyword_List*list,Run* obj);
void select(std::string table_name, Run* obj, std::vector<std::string>identifiers);
void select(std::string table_name, Run* obj, std::vector<std::string>identifiers,std::string attr, uint16_t op,std::string value);
void select_all(std::string table_name, Run* obj);
void select_all(std::string table_name,Run*obj,std::string attr,uint16_t op,std::string value);
