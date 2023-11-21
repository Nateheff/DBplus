#pragma once
#include <vector>
#include <string>
#include <stdint.h>
#include <fstream>
#include <iostream>

#include "../Lexer/list.h"
#include "../Nodes/Node.h"
// #include "../Disk_Space/FSM.h"
// #include "../Catalog/Syst_Attr.h"
// #include "../Catalog/Syst_Index.h"
// #include "../Catalog/Syst_Root.h"
// #include "../Catalog/Syst_Rel.h"

// #include "../B_Tree.h"
// #include "../B_Tree.hh"
// #include "../B+_Tree.h"
#include "../run.h"


struct type_size{
    uint16_t size{};
    char type;
};

type_size attr_info(uint16_t token);
void create_db(std::string name);
void create_table(std::string table_name, std::vector<uint16_t>full_tok, std::vector<std::string>identifiers,size_t ft_size,size_t id_size,Keyword_List*list,Run* obj);
std::vector<Row> select(std::string table_name, Run* obj, std::vector<std::string>identifiers);
std::vector<Row> select_all(std::string table_name,Run*obj,std::string attr,uint16_t op,std::string value,std::string v_2 = "");
void insert(std::string table_name,std::vector<std::string>identifiers,Run* obj);
void delete_row(std::string table_name,std::vector<std::string>identifiers,Run* obj, uint16_t op, std::string value);
void delete_row_f(std::string table_name,std::vector<std::string>identifiers,Run* obj, uint16_t op, std::string value);
void delete_all(std::string table_name, Run* obj);
void delete_all_f(std::string table_name, Run* obj);
void drop_db(std::string file, Run* obj);
void drop_table(std::string table_name, Run* obj);
void update_all(std::string table_name, Run* obj, std::vector<std::string>identifiers);
void update(std::string table_name,Run*obj,std::vector<std::string>identifiers,uint16_t op, std::string value,std::string v_2 = "");