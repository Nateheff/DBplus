#pragma once
#include <stdint.h>
#include <vector>
#include <iostream>
#include <algorithm>
// class Run;
#include "../run.h"


const uint16_t MAX_PAGE = 4096;

struct Row{
    uint32_t index{};
    std::vector<char> data{};
};

struct Curr_Node{
    uint32_t page_id{};
    uint32_t bottom_p{};
    bool is_index{};
    char data[4087]={};
    // std::vector<uint32_t>indexes;
    // std::string data{};
};


struct Tuple_Attr{
    Syst_Attr_Row meta;
    char* data;
};

void edit_row(Curr_Node* node,std::vector<uint16_t>positions,std::vector<char>types, std::vector<std::string>values, uint16_t num_rows, uint16_t row_size, Run* obj);
std::vector<Row> edit_rows(Curr_Node* node,std::vector<uint16_t>positions,std::vector<char>types, std::vector<std::string>values, uint16_t num_rows, uint16_t row_size, Run* obj);

void create_tuple(std::string table_name, Run* obj, Row* row,std::vector<std::string>identifiers);
float create_tuple_f(std::string table_name,Run* obj,Row* row,std::vector<std::string>identifiers);
// void fill_tuple(std::vector<Syst_Attr_Row>*tuple_info,char*data,uint16_t size)
template<typename T>
T get_type(char*data, char type, int size){
    switch(type){
        case('i'):
        T integer = atoi(data);
        return integer;
        case('d'||'f'):{
            T doub = atof(data);
            return doub;
            
        }
        case('b'):
        T bl = atoi(data);
        return bl;

    };
}



class Node
{
uint16_t a = sizeof(Curr_Node);
//     typedef struct Page_Header{
//         uint16_t checksum{};
//         uint16_t free_lp{};
//         uint16_t free_up{};
//         uint16_t spec_lp{};
//         uint16_t pg_size{};
//         uint16_t pg_id{};
//     }Page_Header; //12 bytes
//     Page_Header page_header;
//     char data[MAX_PAGE-sizeof(page_header)];
//     uint16_t next_node;
    
// public:
//     void set_checksum(uint16_t);//we'll make our way around to this...
//     void set_p(uint16_t,uint16_t,uint16_t);
//     void set_id(uint16_t id){page_header.pg_id = id;};
//     void set_pg_size(uint16_t);
//     void set_data(char*);
//     void set_next(uint16_t);
//     void print_data();
//     uint16_t page_id(){return page_header.pg_id;};
   

};


