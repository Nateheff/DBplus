#pragma once
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>

#include "run.h"
#include "Nodes/Node.h"
#include "Catalog/Syst_Root.h"

/*
B+_Tree.h

This is the definition of the B+ trees which we use to store users' data. This implementation
is similar to the trees in B_Tree.h, but since user data can be of any type, size, or length,
we have to account for this in our B+ Tree operations.

Info

A helper strcuture that holds the key information for the database.
*/

struct Info{
    uint16_t index{};
    uint16_t index_root{};
    uint16_t index_last{};
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
    void delete_row(Run* obj, uint16_t index_first,uint16_t index_last);
    // void delete_row(float key,uint16_t num_rows, uint16_t row_size, Run* obj);
    void search_range(uint32_t key_first,uint32_t key_last,uint16_t num_rows);
    void search_range(float key_first,float key_last,uint16_t num_rows);
    void delete_range(uint32_t key_first,uint32_t key_last,uint16_t num_rows,Row row);
    void delete_range(float key_first,float key_last,uint16_t num_rows,Row row);
    void update_range(uint32_t key_first,uint32_t key_last,uint16_t num_rows,std::vector<uint16_t>positions,std::vector<char>types, Run* obj, std::vector<std::string>values);
    void update_range(float key_first,float key_last,uint16_t num_rows,std::vector<uint16_t>positions,std::vector<char>types, Run* obj, std::vector<std::string>values);
    void update_index_range(uint32_t key_first,uint32_t key_last,uint16_t num_rows,std::vector<uint16_t>positions,std::vector<char>types, Run* obj, std::vector<std::string>values);
    void update_index_range(float key_first,float key_last,uint16_t num_rows,std::vector<uint16_t>positions,std::vector<char>types, Run* obj, std::vector<std::string>values);
    // void write_page(Curr_Node* node,std::string file,uint32_t offset = 0);
 
};