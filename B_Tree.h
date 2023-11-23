#pragma once

#include "./Disk_Space/FSM.h"
#include "./Disk_Space/Disk_SM.h"

#include "./Catalog/Syst_Root.h"
#include "./Catalog/Syst_Index.h"
#include "./Catalog/Syst_Attr.h"
#include "./Catalog/Syst_Rel.h"

#include <cstring>
#include <fstream>
#include <vector>
#include <stdint.h>

template<typename T>
struct Info_Pack{
    uint16_t index{};
    uint16_t index_root{};
    Syst_Root root{};
    T rel{};
    // std::fstream* fs;
    std::vector<uint32_t> offsets;
    

};


// template<typename T>
// struct Frame_t{
//   T page;
//   bool dirty{};
//   uint16_t pin_count{};
// };
//T is the leaf page type and S is the row type

//CATALOG ONLY B+TREE IMPLEMENTATION

template<typename T,typename S>
class B_Tree
{
  std::string file;
  FSM fsm;  
  public:
    
    B_Tree<T,S>(std::string file_name):file{file_name}{};
    B_Tree<T,S>(std::string file_name, bool has_height):file{file_name},height{has_height}{};
    // ~B_Tree<T,S>(){};
    Info_Pack<T> info{};
    bool height{};
    bool dirty{};
    // std::fstream fs;
    
    std::vector<S>rows{};
    System_Rel_Row rel{};
    Syst_Index_Row ind;
    
    std::vector<Syst_Attr_Row*>attrs{};
    uint16_t out{};
    
    void search_catalog(uint16_t key,uint16_t num_rows,std::string database = "");
    void remove_catalog(uint16_t key, uint16_t num_rows);
    void insert_catalog(uint16_t key, S row,uint16_t num_rows);
    void search_range_catalog(uint16_t key_first,uint16_t key_last,uint16_t num_rows);
    
    
    uint16_t calc_name(const char* arr);

};



#include "B_Tree.hh"

