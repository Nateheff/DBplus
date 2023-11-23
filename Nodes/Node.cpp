#include "Node.h"
#include "../Catalog/Syst_Attr.h"
#include "../Catalog/Syst_Index.h"
#include "../Catalog/Syst_Rel.h"

void create_tuple(std::string table_name,Run* obj,Row* row,std::vector<std::string>identifiers){
    //// std::cout<<"CREATING TUPLE"<<std::endl;
    
   uint16_t key =obj->tree_attr.calc_name(table_name.c_str());
    obj->tree_rel.search_range_catalog(key,key,28);
    //// std::cout<<"searched rel "<<key<<std::endl;
    obj->tree_ind.search_range_catalog(key,key,48);
    for(size_t i = 0;i<obj->tree_rel.rows.size();i++){
        if(strcmp(obj->database.c_str(),obj->tree_rel.rows.at(i).rel_file)){
            obj->tree_ind.info.index+=i;
            obj->tree_rel.info.index+=i;
        }
    }
    
    //// std::cout<<"searched ind"<<std::endl;
    obj->tree_attr.search_range_catalog(key,key,30);
    //// std::cout<<"searched attr"<<std::endl;
    System_Rel_Row rel = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    Syst_Index_Row ind = obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
    std::cout<<"CHECK: "<<rel.rel_file<<" "<<rel.row_size<<std::endl;
    row->data.resize(rel.row_size);
    // for(auto& d:row->data){
    //// std::cout<<identifiers.at(1)<<std::endl;
    //// std::cout<<obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1).type<<std::endl;
    // }
    switch(obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1).type){
        case 's':
        case 'i':
        case 'b':
        {
        //// std::cout<<"int/short/bool"<<std::endl;
        row->index = atoi(identifiers.at(1).c_str());
        break;
        }
        // case('f'):
        // {
        // row->index = atof(identifiers.at(1).c_str());
        // break;
        // }
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
    std::cout<<row->index<<std::endl;
    memcpy(row->data.data(),&row->index,4);
    std::cout<<row->index<<std::endl;
    uint16_t pos{sizeof(row->index)};
    
    
    for(size_t i = 0; i<obj->tree_attr.rows.size();i++){

        //// std::cout<<"in loop "<<(int)obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1-i).check<<" "<<obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1-i).type<<std::endl;
        
        //// std::cout<<"at "<<obj->tree_attr.rows.size()-1-i<<std::endl;
        // pos += obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1-i).check;
    //   // std::cout<<pos<<" "<<row->data.data()<<" "<<row->data.size()<<" "<<identifiers.at(i+1)<<std::endl;

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
                char d[64];
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
        std::cout<<"length"<<std::endl;
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
                //// std::cout<<"float"<<std::endl;
                float d{atof(identifiers.at(i+1).c_str())};
                memcpy(&row->data.data()[pos],&d,4);
                break;
            }
            case('i'):
            {
                //// std::cout<<"int"<<std::endl;
                uint32_t d{atoi(identifiers.at(i+1).c_str())};
                memcpy(&row->data.data()[pos],&d,4);
                //// std::cout<<"success"<<std::endl;
                break;
            }
            case('v'):
            {
                char d[64];
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
    std::cout<<row->index<<std::endl;
    return;
};

float create_tuple_f(std::string table_name,Run* obj,Row* row,std::vector<std::string>identifiers){
   // std::cout<<"CREATING FLOAT TUPLE"<<std::endl;
    
   uint16_t key =obj->tree_attr.calc_name(table_name.c_str());
    obj->tree_rel.search_range_catalog(key,key,28);
    //// std::cout<<"searched rel "<<key<<std::endl;
    obj->tree_ind.search_range_catalog(key,key,48);
    for(size_t i = 0;i<obj->tree_rel.rows.size();i++){
        if(strcmp(obj->database.c_str(),obj->tree_rel.rows.at(i).rel_file)){
            obj->tree_ind.info.index+=i;
            obj->tree_rel.info.index+=i;
        }
    }
    //// std::cout<<"searched ind"<<std::endl;
    obj->tree_attr.search_range_catalog(key,key,30);
    //// std::cout<<"searched attr"<<std::endl;
    System_Rel_Row rel = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    Syst_Index_Row ind = obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
    row->data.resize(rel.row_size);
    // for(auto& d:row->data){
   // std::cout<<"A "<<identifiers.at(1)<<std::endl;
    //// std::cout<<obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1).type<<std::endl;
    // }
    float index{};
    index = (float)atof(identifiers.at(1).c_str());
    // float test{32432.5436445};
    // char* test;
   // std::cout<<index<<std::endl;
    memcpy(row->data.data(),&index,4);
    //// std::cout<<row->index<<std::endl;
    uint16_t pos{4};
    
    
    for(size_t i = 0; i<obj->tree_attr.rows.size();i++){

       // std::cout<<"in loop "<<(int)obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1-i).check<<" "<<obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1-i).type<<std::endl;
        
        //// std::cout<<"at "<<obj->tree_attr.rows.size()-1-i<<std::endl;
        // pos += obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1-i).check;
    //   // std::cout<<pos<<" "<<row->data.data()<<" "<<row->data.size()<<" "<<identifiers.at(i+1)<<std::endl;

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
                char d[64];
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
        //// std::cout<<"length"<<std::endl;
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
                //// std::cout<<"float"<<std::endl;
                float d{atof(identifiers.at(i+1).c_str())};
                memcpy(&row->data.data()[pos],&d,4);
                break;
            }
            case('i'):
            {
                //// std::cout<<"int"<<std::endl;
                uint32_t d{atoi(identifiers.at(i+1).c_str())};
                memcpy(&row->data.data()[pos],&d,4);
                //// std::cout<<"success"<<std::endl;
                break;
            }
            case('v'):
            {
                char d[64];
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
    //// std::cout<<row->index<<std::endl;
    return index;
};

void edit_row(Curr_Node* node,std::vector<uint16_t>positions,std::vector<char>types, std::vector<std::string>values, uint16_t num_rows, uint16_t row_size, Run* obj,uint16_t index_first){
    std::vector<uint16_t>offsets{};
    std::cout<<"editting row"<<std::endl;
    uint16_t off{4};
    offsets.push_back(off);
    for(int i = obj->tree_attr.rows.size()-1;i>=0;i--){
    //    std::cout<<i<<std::endl;
        off+=obj->tree_attr.rows.at(i).check;
    //    std::cout<<off<<" v "<<i<<std::endl;
        offsets.push_back(off);
    //    std::cout<<i<<std::endl;
    }
//    std::cout<<"offsets covered "<<num_rows<<" "<<positions.size()<<" "<<values.size()<<std::endl;
    for(size_t i = 0;i<num_rows;i++){
        for(size_t j = 0; j<positions.size();j++){
        //    std::cout<<values.at(j)<<" k "<<offsets.at(j)<<std::endl;
        //    std::cout<<(i*row_size)+offsets.at(positions.at(j))<<std::endl;
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
               // std::cout<<"float"<<std::endl;
                float d{atof(values.at(j).c_str())};
                memcpy(&node->data[((i+index_first)*row_size)+offsets.at(positions.at(j))],&d,4);
                break;
            }
            case('i'):
            {
               // std::cout<<"int"<<std::endl;
                uint32_t d{atoi(values.at(j).c_str())};
                memcpy(&node->data[((i+index_first)*row_size)+offsets.at(positions.at(j))],&d,4);
                //// std::cout<<"success"<<std::endl;
                break;
            }
            case('v'):
            {
                char d[64];
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
//    std::cout<<"edited"<<std::endl;
}

std::vector<Row> edit_rows(Curr_Node* node,std::vector<uint16_t>positions,std::vector<char>types, std::vector<std::string>values, uint16_t num_rows, uint16_t row_size, Run* obj,uint16_t index_first){
    std::vector<uint16_t>offsets{};
    std::vector<Row>rows{};
    uint16_t off{4};
    offsets.push_back(off);
    for(int i = obj->tree_attr.rows.size()-1;i>=0;i--){
    //    std::cout<<(int)obj->tree_attr.rows.at(i).check<<std::endl;
        off+=obj->tree_attr.rows.at(i).check;
    //    std::cout<<off<<" v "<<i<<std::endl;
        offsets.push_back(off);
    //    std::cout<<i<<std::endl;
    }

//    std::cout<<"offsets covered rows"<<num_rows<<" "<<positions.size()<<" "<<values.size()<<std::endl;
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
        //    std::cout<<values.at(j)<<" "<<j<<" "<<offsets.at(positions.at(j))<<std::endl;
        //    std::cout<<(i*row_size)+offsets.at(positions.at(j))<<std::endl;
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
            //    std::cout<<"float"<<std::endl;
                float d{atof(values.at(j).c_str())};
                memcpy(&row.data.data()[offsets.at(positions.at(j))],&d,4);
                break;
            }
            case('i'):
            {
               std::cout<<"int"<<std::endl;
                uint32_t d{atoi(values.at(j).c_str())};
                memcpy(&row.data.data()[offsets.at(positions.at(j))],&d,4);
                std::cout<<"success"<<std::endl;
                break;
            }
            case('v'):
            {
                char d[64];
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
        // for(auto i: row.data)
    //    std::cout<<i;
    //    std::cout<<std::endl;
    }
    return rows;
}

/*void fill_tuple(std::vector<Syst_Attr_Row>*tuple_info,char*data,uint16_t size)
{//
std::cout<<"allocated"<<std::endl;
    std::vector<Tuple_Attr>vec;
    
    uint16_t pos{};
    for(auto info:*tuple_info){
        
        char value[(int)info.check];
        for(size_t i =pos;i<=pos+info.check;i++){
            value[i]=data[i];
        }
        pos+=info.check;
        Tuple_Attr tup{info,value};
        vec.push_back(tup);
    }

    return vec;
};
*/

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
   // std::cout<<data[0]<<std::endl;
};

void Node::set_next(uint16_t next_p){
    next_node = next_p;
};

void Node::print_data(){  
   // std::cout<<data[0]<<std::endl;
    for(size_t i= 0;i<4084;i++){
        if(data[i]!='\0')
   // std::cout<<data[i];
    else
    return;
    }
   // std::cout<<"\n"<<std::endl;
}

*/