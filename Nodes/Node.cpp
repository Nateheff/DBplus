#include "Node.h"
#include "../Catalog/Syst_Attr.h"
#include "../Catalog/Syst_Index.h"
#include "../Catalog/Syst_Rel.h"

void create_tuple(std::string table_name,Run* obj,Row* row,std::vector<std::string>identifiers){
    
   uint16_t key =obj->tree_attr.calc_name(table_name.c_str());
    obj->tree_rel.search_range_catalog(key,key,28);
    obj->tree_ind.search_range_catalog(key,key,48);
    for(size_t i = 0;i<obj->tree_rel.rows.size();i++){
        if(strcmp(obj->database.c_str(),obj->tree_rel.rows.at(i).rel_file)){
            obj->tree_ind.info.index+=i;
            obj->tree_rel.info.index+=i;
        }
    }
    
    obj->tree_attr.search_range_catalog(key,key,30);
    System_Rel_Row rel = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    Syst_Index_Row ind = obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
    row->data.resize(rel.row_size);
    
    switch(obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1).type){
        case 's':
        case 'i':
        case 'b':
        {
        row->index = atoi(identifiers.at(1).c_str());
        break;
        }
       
        case('c'):
        {
        row->index = identifiers.at(1).at(0);
        break;
        }
        case('v'):
        {
        row->index = obj->tree_attr.calc_name(identifiers.at(1).c_str());
        break;
        }
    }
    char* test;
    memcpy(row->data.data(),&row->index,4);
    uint16_t pos{sizeof(row->index)};
    
    
    for(size_t i = 0; i<obj->tree_attr.rows.size();i++){

       

    if(identifiers.at(i+1).length()==0){

        switch(obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1-i).type){
            case('b'):
            {
                bool d{};
                memcpy(&row->data.data()[pos],&d,1);
                break;
            }
            case('c'):
            {
                char d{};
                memcpy(&row->data.data()[pos],&d,1);
                break;
            }
            case('f'):
            {
                float d{};
                memcpy(&row->data.data()[pos],&d,4);
                break;
            }
            case('i'):
            {
                uint32_t d{};
                memcpy(&row->data.data()[pos],&d,4);
                break;
            }
            case('v'):
            {
                char d[64]={};
                memcpy(&row->data.data()[pos],&d,64);
                break;
            }
            case('s'):
            {
                uint16_t d{};
                memcpy(&row->data.data()[pos],&d,2);
                break;
            }
        }
        
    }else{
        switch(obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1-i).type){
            case('b'):
            {
                bool d{atoi(identifiers.at(i+1).c_str())};
                memcpy(&row->data.data()[pos],&d,1);
                break;
                
            }
            case('c'):
            {
                char d{identifiers.at(i+1).at(0)};
                memcpy(&row->data.data()[pos],&d,1);
                break;
            }
            case('f'):
            {
                float d{atof(identifiers.at(i+1).c_str())};
                memcpy(&row->data.data()[pos],&d,4);
                break;
            }
            case('i'):
            {
                uint32_t d{atoi(identifiers.at(i+1).c_str())};
                memcpy(&row->data.data()[pos],&d,4);
                break;
            }
            case('v'):
            {
                char d[64] = {};
                strcpy(d,identifiers.at(i+1).c_str());
                memcpy(&row->data.data()[pos],&d,64);
                break;
            }
            case('s'):
            {
                uint16_t d{atoi(identifiers.at(i+1).c_str())};
                memcpy(&row->data.data()[pos],&d,2);
                break;
            }
        }
        pos += obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1-i).check;
    }
    
    } 
    return;
};

float create_tuple_f(std::string table_name,Run* obj,Row* row,std::vector<std::string>identifiers){
    
   uint16_t key =obj->tree_attr.calc_name(table_name.c_str());
    obj->tree_rel.search_range_catalog(key,key,28);
    obj->tree_ind.search_range_catalog(key,key,48);
    for(size_t i = 0;i<obj->tree_rel.rows.size();i++){
        if(strcmp(obj->database.c_str(),obj->tree_rel.rows.at(i).rel_file)){
            obj->tree_ind.info.index+=i;
            obj->tree_rel.info.index+=i;
        }
    }
   
    obj->tree_attr.search_range_catalog(key,key,30);
    System_Rel_Row rel = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    Syst_Index_Row ind = obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
    row->data.resize(rel.row_size);
    
    float index{};
    index = (float)atof(identifiers.at(1).c_str());
    // char* test;
    memcpy(row->data.data(),&index,4);
    uint16_t pos{4};
    
    
    for(size_t i = 0; i<obj->tree_attr.rows.size();i++){

       

    if(identifiers.at(i+1).length()==0){

       // std::cout<<"empty"<<std::endl;
        switch(obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1-i).type){
            case('b'):
            {
                bool d{};
                memcpy(&row->data.data()[pos],&d,1);
                break;
            }
            case('c'):
            {
                char d{};
                memcpy(&row->data.data()[pos],&d,1);
                break;
            }
            case('f'):
            {
                float d{};
                memcpy(&row->data.data()[pos],&d,4);
                break;
            }
            case('i'):
            {
                uint32_t d{};
                memcpy(&row->data.data()[pos],&d,4);
                break;
            }
            case('v'):
            {
                char d[64]={};
                memcpy(&row->data.data()[pos],&d,64);
                break;
            }
            case('s'):
            {
                uint16_t d{};
                memcpy(&row->data.data()[pos],&d,2);
                break;
            }
        }
        
    }else{
        switch(obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1-i).type){
            case('b'):
            {
                bool d{atoi(identifiers.at(i+1).c_str())};
                memcpy(&row->data.data()[pos],&d,1);
                break;
                
            }
            case('c'):
            {
                char d{identifiers.at(i+1).at(0)};
                memcpy(&row->data.data()[pos],&d,1);
                break;
            }
            case('f'):
            {
                float d{atof(identifiers.at(i+1).c_str())};
                memcpy(&row->data.data()[pos],&d,4);
                break;
            }
            case('i'):
            {
                uint32_t d{atoi(identifiers.at(i+1).c_str())};
                memcpy(&row->data.data()[pos],&d,4);
                break;
            }
            case('v'):
            {
                char d[64]={};
                strcpy(d,identifiers.at(i+1).c_str());
                memcpy(&row->data.data()[pos],&d,64);
                break;
            }
            case('s'):
            {
                uint16_t d{atoi(identifiers.at(i+1).c_str())};
                memcpy(&row->data.data()[pos],&d,2);
                break;
            }
        }
        pos += obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1-i).check;
    }
    
    } 
    return index;
};

void edit_row(Curr_Node* node,std::vector<uint16_t>positions,std::vector<char>types, std::vector<std::string>values, uint16_t num_rows, uint16_t row_size, Run* obj,uint16_t index_first){
    std::vector<uint16_t>offsets{};
    uint16_t off{4};
    offsets.push_back(off);
    for(int i = obj->tree_attr.rows.size()-1;i>=0;i--){
        off+=obj->tree_attr.rows.at(i).check;
        offsets.push_back(off);
    }
    for(size_t i = 0;i<num_rows;i++){
        for(size_t j = 0; j<positions.size();j++){
            switch(types.at(j)){
            case('b'):
            {
                bool d{atoi(values.at(j).c_str())};
                memcpy(&node->data[((i+index_first)*row_size)+offsets.at(positions.at(j))],&d,1);
                break;
                
            }
            case('c'):
            {
                char d{values.at(j).at(0)};
                memcpy(&node->data[((i+index_first)*row_size)+offsets.at(positions.at(j))],&d,1);
                break;
            }
            case('f'):
            {
                float d{atof(values.at(j).c_str())};
                memcpy(&node->data[((i+index_first)*row_size)+offsets.at(positions.at(j))],&d,4);
                break;
            }
            case('i'):
            {
                uint32_t d{atoi(values.at(j).c_str())};
                memcpy(&node->data[((i+index_first)*row_size)+offsets.at(positions.at(j))],&d,4);
                break;
            }
            case('v'):
            {
                char d[64]={};
                strcpy(d,values.at(j).c_str());
                memcpy(&node->data[((i+index_first)*row_size)+offsets.at(positions.at(j))],&d,64);
                break;
            }
            case('s'):
            {
                uint16_t d{atoi(values.at(j).c_str())};
                memcpy(&node->data[((i+index_first)*row_size)+offsets.at(positions.at(j))],&d,2);
                break;
            }
        }
        }}
}

std::vector<Row> edit_rows(Curr_Node* node,std::vector<uint16_t>positions,std::vector<char>types, std::vector<std::string>values, uint16_t num_rows, uint16_t row_size, Run* obj,uint16_t index_first){
    std::vector<uint16_t>offsets{};
    std::vector<Row>rows{};
    uint16_t off{4};
    offsets.push_back(off);
    for(int i = obj->tree_attr.rows.size()-1;i>=0;i--){
        off+=obj->tree_attr.rows.at(i).check;
        offsets.push_back(off);
    }

    Row row{};
    row.data.resize(row_size);
    for(size_t i = 0;i<num_rows;i++){
        memcpy(row.data.data(),&node->data[((i+index_first)*num_rows)],row_size);
        if(types.at(0)=='f'){
            float d{atof(values.at(0).c_str())};
            memcpy(row.data.data(),&d,4);
        }else{
            uint32_t d{atoi(values.at(0).c_str())};
            memcpy(row.data.data(),&d,4);
        }
        for(size_t j = 0; j<positions.size();j++){
            switch(types.at(j)){
            case('b'):
            {
                bool d{atoi(values.at(j).c_str())};
                memcpy(&row.data.data()[offsets.at(positions.at(j))],&d,1);
                break;
                
            }
            case('c'):
            {
                char d{values.at(j).at(0)};
                memcpy(&row.data.data()[offsets.at(positions.at(j))],&d,1);
                break;
            }
            case('f'):
            {
                float d{atof(values.at(j).c_str())};
                memcpy(&row.data.data()[offsets.at(positions.at(j))],&d,4);
                break;
            }
            case('i'):
            {
                uint32_t d{atoi(values.at(j).c_str())};
                memcpy(&row.data.data()[offsets.at(positions.at(j))],&d,4);
                break;
            }
            case('v'):
            {
                char d[64]={};
                strcpy(d,values.at(j).c_str());
                memcpy(&row.data.data()[offsets.at(positions.at(j))],&d,64);
                break;
            }
            case('s'):
            {
                uint16_t d{atoi(values.at(j).c_str())};
                memcpy(&row.data.data()[offsets.at(positions.at(j))],&d,2);
                break;
            }
        }
        }
        rows.push_back(row);
       
    }
    return rows;
}

