#ifndef NODE_HPP
#define NODE_HPP
#include <stdint.h>
#include <vector>
#include <iostream>
#include <algorithm>

const uint16_t MAX_PAGE = 4096;

class Node
{
    
    typedef struct Page_Header{
        uint16_t checksum;
        uint16_t free_lp;
        uint16_t free_up;
        uint16_t spec_lp;
        uint16_t pg_size;
    }Page_Header; //10 bytes
    Page_Header page_header;
    char data[MAX_PAGE-12];
    uint16_t next_node;
    
public:
    void set_checksum(uint16_t);//we'll make our way around to this...
    void set_p(uint16_t,uint16_t,uint16_t);
    void set_pg_size(uint16_t);
    void set_data(char*);
    void set_next(uint16_t);
    void print_data();
   

};

#endif // NODE_HPP
