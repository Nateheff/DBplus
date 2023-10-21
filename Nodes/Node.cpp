#include "Node.h"
/*
void Node::set_checksum(uint16_t huh= 0){
    page_header.checksum = huh;
};//we'll make our way around to this...

void Node::set_p(uint16_t lp = 0,uint16_t up = 0,uint16_t spec = 0){
    page_header.free_lp = lp;
    page_header.free_up = up;
    page_header.spec_lp = spec;
};

void Node::set_pg_size(uint16_t size){
    page_header.pg_size = size;
};

void Node::set_data(char arr[MAX_PAGE-12]){
    
    uint16_t free_space = MAX_PAGE-page_header.pg_size;
    for(size_t i = 0;i < free_space;i++){
    data[i]=arr[i];
    }
    std::cout<<data[0]<<std::endl;
};

void Node::set_next(uint16_t next_p){
    next_node = next_p;
};

void Node::print_data(){  
    std::cout<<data[0]<<std::endl;
    for(size_t i= 0;i<4084;i++){
        if(data[i]!='\0')
    std::cout<<data[i];
    else
    return;
    }
    std::cout<<"\n"<<std::endl;
}

*/