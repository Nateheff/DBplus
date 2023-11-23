#include "Commands.h"

void drop_db(std::string file, Run* obj){
    std::string db{file+".db"};
    remove(db.c_str());
    std::string fsm{file+"_fsm.db"};
    remove(fsm.c_str());
    std::fstream fs;
    fs.open("databases.txt",std::ios_base::in|std::ios_base::out|std::ios_base::binary);
    std::string data{};
    while(std::getline(fs,data)){}
    std::cout<<"db: "<<data<<std::endl;
    auto first = data.find(file);
    if(first != data.npos){
        std::cout<<"erasing "<<first<<std::endl;
    data.erase(first,file.length()+1);
    std::cout<<data<<std::endl;
    }
    fs.close();
    fs.open("databases.txt",std::ios_base::out|std::ios_base::binary);
    fs.write(data.c_str(),data.length());
    fs.close();
}

void drop_table(std::string table_name, Run* obj){
    std::cout<<"TABLE DROP"<<std::endl;
    uint16_t key = obj->tree_rel.calc_name(table_name.c_str());
    obj->tree_rel.search_range_catalog(key,key,28);
    for(size_t i = 0;i<obj->tree_rel.rows.size();i++){
        if(strcmp(obj->database.c_str(),obj->tree_rel.rows.at(i).rel_file)){
            obj->tree_ind.info.index+=i;
        }
    }
    uint16_t num_attrs = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].check;
    obj->tree_rel.remove_catalog(key,28);
    obj->tree_ind.remove_catalog(key,48);
    std::string fsm{table_name+"_fsm.db"};

    std::cout<<num_attrs<<std::endl;

    for(size_t i = 0;i<num_attrs;i++)
    obj->tree_attr.remove_catalog(key,30);
   
    remove(fsm.c_str());
}