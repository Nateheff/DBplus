#include "Commands.h"
#include "../Disk_Space/FSM.h"
#include "../B+_Tree.h"

type_size attr_info(uint16_t token){
    switch(token){
        case(0):{
        type_size bl{1,'b'};
        return bl;
        }
        case(1):{
        type_size cr{1,'c'};
        return cr;
        }
        case(4):{
        type_size fl{4,'f'};
        return fl;
        }
        case(7):{
        type_size in{4,'i'};
        return in;
        }
        case(12):{
        type_size vc{64,'v'};
        return vc;
        }
        case(18):{
        type_size s{2,'s'};
        return s;
        }default:{
        type_size nu{0,' '};
        return nu;
        }
    }
    
}

void create_table(std::string table_name, std::vector<uint16_t>full_tok, std::vector<std::string>identifiers,size_t ft_size,size_t id_size,Keyword_List*list,Run*obj){
    for(size_t i = 0;i<full_tok.size();i++){
        std::cout<<i<<": "<<full_tok.at(i)<<std::endl;
    }
    for(size_t i = 0;i<identifiers.size();i++){
        std::cout<<i<<": "<<identifiers.at(i)<<std::endl;
    }
    // std::cout<<ft_size<<std::endl;
    // std::cout<<id_size<<std::endl;
    

    FSM fsm;
    /*
    if(!fsm.get_fsm(table_name)){
        std::cout<<"No fsm, db never created!"<<std::endl;
        return;
    };
   */ 

    

std::string file = table_name+".db";
uint16_t key = obj->tree_attr.calc_name(table_name.c_str());
std::vector<Syst_Attr_Row>attrs{id_size};
Syst_Index_Row ind{};
System_Rel_Row rel{};
std::vector<type_size>infos;
for(size_t i = 3;i<full_tok.size();i++){
    type_size b = attr_info(full_tok.at(i));
    if(b.size != 0){
    infos.push_back(b);
    };
}
uint16_t r_s{4};
for(size_t i =0;i<id_size;i++){
    strcpy(attrs.at(i).index,table_name.c_str());
    strcpy(attrs.at(i).attr_name,identifiers.at(i).c_str());
    attrs.at(i).position = i;
    type_size info = infos.at(i);
    attrs.at(i).check = info.size;
    attrs.at(i).type = info.type;
    r_s+=info.size;
    obj->tree_attr.insert_catalog(obj->tree_attr.calc_name(table_name.c_str()),attrs.at(i),30);
}

if(fsm.page()>1){
    ind.ind_start = fsm.page()*4096;
}
strcpy(ind.index,table_name.c_str());
ind.check = 1;
ind.ind_height = 0;
ind.ind_max = 0;
ind.ind_min = 0;
ind.num_keys = 0;
ind.key_type = infos.at(0).type;

obj->tree_ind.insert_catalog(key,ind,48);

rel.check = id_size;
strcpy(rel.index,table_name.c_str());
table_name+=".db";
strcpy(rel.rel_file,table_name.c_str());
rel.num_pages = 1;
rel.num_rows = 0;
rel.row_size = r_s;
obj->tree_rel.insert_catalog(key,rel,28);
Bp_Tree tree{};
Curr_Node empty{};
// empty.indexes.resize(r_s);
// empty.data.resize(4083-(empty.indexes.size()*4));
std::fstream fs;
fs.write(reinterpret_cast<char*>(&empty),sizeof(empty));
fs.close();

};