#pragma once

#include "./Disk_Space/FSM.h"
#include "./Disk_Space/Disk_SM.h"
#include "./Buffer_Manager/Frame.h"
#include "./Buffer_Manager/Buffer_PM.h"
#include "./Catalog/Syst_Root.h"


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
    std::fstream* fs;
    std::vector<uint32_t> offsets;
    

};

template<typename T,typename S>
class B_Tree
{
  std::string file;

  public:
    B_Tree<T,S>(std::string file_name):file{file_name}{};
    ~B_Tree<T,S>(){info.fs->close();std::cout<<"closed"<<std::endl;}
    Info_Pack<T> info{};
    
    std::vector<S>rows;
    FSM fsm;  
    void search(uint16_t key,uint16_t num_rows,bool has_height);
    void remove(uint16_t key, uint16_t num_rows, bool has_height);
    void insert(uint16_t key, S row,uint16_t num_rows,size_t test);
    
    void search_range(uint16_t key_first,uint16_t key_last,uint16_t num_rows,bool has_height);
    uint16_t calc_name(char* arr);

};
#include "B_Tree.hh"

