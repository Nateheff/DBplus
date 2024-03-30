#include "Commands.h"
#include "../B_Tree.h"
#include "../B+_Tree.h"
#include <iomanip>

std::vector<Row> select(std::string table_name, Run* obj, std::vector<std::string>identifiers){
    Bp_Tree tree{};
    
    uint32_t key = obj->tree_attr.calc_name(table_name.c_str());
    
    obj->tree_rel.search_range_catalog(key,key,28); 
    obj->tree_ind.search_range_catalog(key,key,48);
    for(size_t i = 0;i<obj->tree_rel.rows.size();i++){
        if(strcmp(obj->database.c_str(),obj->tree_rel.rows.at(i).rel_file)){
            obj->tree_ind.info.index+=i;
            obj->tree_rel.info.index+=i;
        }
    }
    obj->tree_attr.search_range_catalog(key,key,30);
    uint16_t row_size = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].row_size;
    if(obj->tree_ind.info.rel.rows[obj->tree_ind.info.index].key_type=='f'){
        float k{};
        tree.search_range(k,__FLT32_MAX__,(4087/obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].row_size));
    }
    else{
    key = 0;
    tree.search_range(key,UINT32_MAX,(4087/obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].row_size));
    }
    
    std::vector<uint16_t>offsets{};
    uint16_t off{4};
    for(int i = obj->tree_attr.rows.size()-1;i>=0;i--){
        Syst_Attr_Row attr = obj->tree_attr.rows.at(i);
    std::cout<<std::setw(10)<<std::left<<attr.attr_name;
    
    offsets.push_back(off);
    off+=attr.check;
    }
    std::cout<<"\n"<<std::endl;
    char y_n{};
    if(tree.info.rows.size()>100){
        std::cout<<"Do you want to print out "<<tree.info.rows.size()<<" rows? (Y/N): ";
        std::cin >> y_n;
        std::cin.ignore();
    }
    if(y_n == 'y' || y_n == 'Y'||y_n == '\0'){
    for(size_t i = 0; i<tree.info.rows.size();i++){
        std::cout<<std::endl;
        for(size_t j = 0; j<obj->tree_attr.rows.size();j++){
        switch(obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1-j).type){
            case('b'):
            {
                bool d{};
                memcpy(&d,&tree.info.rows.at(i).data[offsets.at(j)],1);
                std::cout<<"  "<<d;
                break;
                
            }
            case('c'):
            {
                char d{};
                memcpy(&d,&tree.info.rows.at(i).data[offsets.at(j)],1);
                std::cout<<"  "<<d;
                break;
            }
            case('f'):
            {
                //// std::cout<<"float"<<std::endl;
                float d{};
                memcpy(&d,&tree.info.rows.at(i).data[offsets.at(j)],4);
                std::cout<<"  "<<d;
                break;
            }
            case('i'):
            {
                //// std::cout<<"int"<<std::endl;
                uint32_t d{};
                memcpy(&d,&tree.info.rows.at(i).data[offsets.at(j)],4);
                //// std::cout<<"success"<<std::endl;
                std::cout<<"  "<<d;
                break;
            }
            case('v'):
            {
                char d[64] = {};
                
                memcpy(&d,&tree.info.rows.at(i).data[offsets.at(j)],64);
                std::cout<<"  "<<d;
                break;
            }
            case('s'):
            {
                uint16_t d{};
                memcpy(&d,&tree.info.rows.at(i).data[offsets.at(j)],2);
                std::cout<<"  "<<d;
                break;
            }
        }
        }
    }

    }
    return tree.info.rows;
    
}

std::vector<Row> select_all(std::string table_name,Run*obj,std::string attr,uint16_t op,std::string value,std::string v_2)
{
    
    Bp_Tree tree{};
    uint32_t index{};
    float ind{};
    
    
    uint16_t key = obj->tree_attr.calc_name(table_name.c_str());
    
    obj->tree_rel.search_range_catalog(key,key,28); 
    obj->tree_ind.search_range_catalog(key,key,48);
    for(size_t i = 0;i<obj->tree_rel.rows.size();i++){
        if(strcmp(obj->database.c_str(),obj->tree_rel.rows.at(i).rel_file)){
            obj->tree_ind.info.index+=i;
            obj->tree_rel.info.index+=i;
        }
    }
    obj->tree_attr.search_range_catalog(key,key,30);
    
    tree.info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    tree.info.ind = &obj->tree_ind.info.rel.rows[obj->tree_rel.info.index];
    if(tree.info.ind->key_type != 'f'){

        switch(obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1).type){
        case 's':
        case 'i':
        case 'b':
        {
        index = atoi(value.c_str());
        break;
        }
        
        case('c'):
        {
        index = value.at(0);
        break;
        }
        case('v'):
        {
        index = obj->tree_attr.calc_name(value.c_str());
        break;
        }
    }
    uint16_t row_size = tree.info.relation.row_size;
    uint16_t num_rows = (4087/row_size);
    switch(op){
        case(21)://>
        {
           tree.search_range(index+1,UINT32_MAX,num_rows); 
           break;
        }
        case(22)://<
        {
            tree.search_range(0,index-1,num_rows);
            break;
        }
        case(26)://=
        {
            tree.search_range(index,index,num_rows);
            break;
        }
        case(29)://<=
        {
            tree.search_range(0,index,num_rows);
            break;
        }
        case(30)://>=
        {
            tree.search_range(index,UINT32_MAX,num_rows); 
           break;
        }
        case(14):
        {
            tree.search_range(index,atoi(v_2.c_str()),num_rows);
            break;
        }
    }
    }else{
        ind = atof(value.c_str());
        uint16_t row_size = tree.info.relation.row_size;
    uint16_t num_rows = (4087/row_size);
    
    switch(op){
        case(21)://>
        {
           tree.search_range(ind+__FLT32_MIN__,__FLT32_MAX__,num_rows); 
           break;
        }
        case(22)://<
        {
            tree.search_range(0.0,ind-__FLT32_MIN__,num_rows);
            break;
        }
        case(26)://=
        {
            tree.search_range(ind,ind,num_rows);
            break;
        }
        case(29)://<=
        {
            tree.search_range(0.0,ind,num_rows);
            break;
        }
        case(30)://>=
        {
            tree.search_range(ind,__FLT32_MAX__,num_rows); 
           break;
        }
        case(14):
        {
            tree.search_range(ind,atof(v_2.c_str()),num_rows);
           break;

        }
    }
    }
    std::vector<uint16_t>offsets{};
    uint16_t off{4};
    for(int i = obj->tree_attr.rows.size()-1;i>=0;i--){
        Syst_Attr_Row attr = obj->tree_attr.rows.at(i);
    std::cout<<std::setw(10)<<std::left<<attr.attr_name;
    
    offsets.push_back(off);
    off+=attr.check;
    }
    std::cout<<"\n"<<std::endl;
    // char y_n{};
    // if(tree.info.rows.size()>100){
    //     std::cout<<"Do you want to print out "<<tree.info.rows.size()<<" rows? (Y/N): ";
    //     std::cin >> y_n;
    //     std::cin.ignore();
    // }
    // if(y_n == 'y' || y_n == 'Y'||y_n == '\0'){
    for(size_t i = 0; i<tree.info.rows.size();i++){
        for(size_t j = 0; j<obj->tree_attr.rows.size();j++){
            
        switch(obj->tree_attr.rows.at(obj->tree_attr.rows.size()-1-j).type){
            case('b'):
            {
                bool d{};
                memcpy(&d,&tree.info.rows.at(i).data[offsets.at(j)],1);
                std::cout<<"  "<<d;
                break;
                
            }
            case('c'):
            {
                char d{};
                memcpy(&d,&tree.info.rows.at(i).data[offsets.at(j)],1);
                std::cout<<"  "<<d;
                break;
            }
            case('f'):
            {
                //// std::cout<<"float"<<std::endl;
                float d{};
                memcpy(&d,&tree.info.rows.at(i).data[offsets.at(j)],4);
                std::cout<<"  "<<d;
                break;
            }
            case('i'):
            {
                //// std::cout<<"int"<<std::endl;
                uint32_t d{};
                memcpy(&d,&tree.info.rows.at(i).data[offsets.at(j)],4);
                std::cout<<"  "<<d;
                //// std::cout<<"success"<<std::endl;
                break;
            }
            case('v'):
            {
                char d[64] = {};
                
                memcpy(&d,&tree.info.rows.at(i).data[offsets.at(j)],64);
                std::cout<<"  "<<d;
                break;
            }
            case('s'):
            {
                uint16_t d{};
                memcpy(&d,&tree.info.rows.at(i).data[offsets.at(j)],2);
                std::cout<<"  "<<d;
                break;
            }
        }
        }
        std::cout<<std::endl;
    // }
    std::cout<<std::endl;
    }
    return tree.info.rows;
};