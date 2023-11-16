#pragma once
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>

#include "run.h"
#include "Nodes/Node.h"
#include "Catalog/Syst_Root.h"

struct Info{
    uint16_t index{};
    uint16_t index_root{};
    Syst_Root root{};
    Curr_Node leaf{};
    // std::fstream* fs;
    std::vector<uint32_t> offsets;
    std::vector<Row>rows{};
    System_Rel_Row relation{};
    Syst_Index_Row* ind{};
    

};

class Bp_Tree{
    private:
    FSM fsm;
    public:
    Info info{};
    Syst_Root_f root_f{};
    void search(uint32_t key,uint16_t num_rows,uint16_t row_size);
    void search(float key, uint16_t num_rows, uint16_t row_size);
    void insert(uint32_t key, uint16_t num_rows,uint16_t row_size, Run* obj, Row row);
    void insert(float key, uint16_t num_rows,uint16_t row_size, Run* obj, Row row);
    void delete_row(uint32_t key, uint16_t num_rows,uint16_t row_size,Run* obj);
    void delete_row(float key,uint16_t num_rows, uint16_t row_size, Run* obj);
    void search_range(uint32_t key_first,uint32_t key_last,uint16_t num_rows);
    void search_range(float key_first,float key_last,uint16_t num_rows);
    float update(float key, uint16_t num_rows,uint16_t row_size, Run* obj, Row row);
    void update(uint32_t key, uint16_t num_rows,uint16_t row_size, Run* obj, Row row);
    // void write_page(Curr_Node* node,std::string file,uint32_t offset = 0);
 
};