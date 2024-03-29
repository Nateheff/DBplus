#include "list.h"

struct Keyword_List KW_OP::res_list = {{{"bool",0},{"char",1},{"create",2},{"database",3},{"float",4},{"from",5},{"insert",6},{"int",7},{"and",8},{"set",9},{"select",10},{"table",11},{"varchar",12},{"where",13},{"between",14},{"drop",15},{"delete",16},{"update",17},{"short",18},{"into",19}},20,9};

std::unordered_map<std::string,uint16_t> KW_OP::operators = {{"*",20},{">",21},{"<",22},{"/",23},{"(",24},{")",25},{"=",26},{"+",27},{"-",28},{"<=",29},{">=",30},{"<>",31},{",",32}};