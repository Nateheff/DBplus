#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "list.h"

/*
Takes in the string as scan buf, then pushes the characters to term.
*/
class Scanner{ 
    
    std::string scan_buf;
    std::string term; //current term in scanner
    uint16_t scan_loc; //location of scanner (offset from beginning of query)
    const Keyword_List *kw_list;
    
    // std::vector<uint16_t>tokens;
    // std::vector<std::string>ops;
    std::unordered_map<std::string,uint16_t>op_set;
    

    public:
    std::vector<std::string>identifiers;
    std::vector<uint16_t>full_tok;
    Scanner(std::string query,Keyword_List *kws,std::unordered_map<std::string,uint16_t>op):scan_buf{query+" "},term{},kw_list{kws},op_set{op}{};

    bool scanner_run();
    uint16_t get_kw_tok(std::string);
    void print_query();
        

};


