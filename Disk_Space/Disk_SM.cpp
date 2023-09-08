#include "Disk_SM.h"
#include <memory>
#include <fstream>
#include <bitset>

Disk_SM::Disk_SM(std::string file_name){
    
    std::fstream fs;
    fs.open(std::string{file_name+"_fsm.db"},std::ios_base::binary|std::ios_base::out|std::ios_base::in);
    fs.write(reinterpret_cast<char*>(&fsm),sizeof(fsm));
    file = {file_name+".db"};
}

bool Disk_SM::free_page(uint16_t page_num){
   //find page in used_pages
//    overwrite(page_num);
    fsm.set_page(page_num);
   //add page to holes
    if(page_num < num_pages)
    fsm.set_hole(1);

    num_pages--;
}

// void Disk_SM::overwrite(uint16_t page_num){
//     std::fstream fs;
//     fs.open(file,std::ios_base::binary|std::ios_base::out|std::ios_base::in);
//     fs.seekp((page_num-1) * 4096,std::ios_base::beg);
//     Node empty;
//     fs.write(reinterpret_cast<char*>(&empty),sizeof(empty));

// }

uint16_t Disk_SM::write_new_page(){
    fsm.set_space(0,0);
    std::cout<<"num_pages: "<<num_pages<<std::endl;
    std::fstream fs;
    fs.open(file,std::ios_base::binary|std::ios_base::out|std::ios_base::in);
    Node empty;
    uint16_t pg_num{};
    offset_free = (num_pages) * 4096;
    
    std::cout<<"Page: "<<fsm.page()<<std::endl;

    if(fsm.is_hole()){
    offset_free = (fsm.page()-1) * 4096;
        std::cout<<"HOLE"<<offset_free<<std::endl;
    fsm.set_hole(0);
    num_pages++;
    fs.seekp(offset_free,std::ios_base::beg);
    fs.write(reinterpret_cast<char*>(&empty),4096);
    fs.close();
    
    return fsm.page();
    };

    
    fsm.set_space(num_pages,1);
    std::cout<<"this right? "<<offset_free<<std::endl;
   
    fs.seekp(offset_free,std::ios_base::beg);
    pg_num = num_pages + 1;
    fs.write(reinterpret_cast<char*>(&empty),4096);
    offset_free = pg_num*4096;
    
    fs.clear();
    fs.seekp(0);
    fs.close();
    std::cout<<"page num: "<<pg_num<<std::endl;
    num_pages++;
    fsm.set_page(num_pages+1);
    return pg_num;
}

bool Disk_SM::write_page(Node* page,uint16_t page_num){
    page->set_id(page_num);
    std::cout<<"writing: "<<page_num<<std::endl;
    std::fstream fs;
    fs.open(file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    
    fs.seekp((page_num-1) * 4096,std::ios_base::beg);
    
    fs.write(reinterpret_cast<char*>(page),4096);
    fs.clear();
    fs.seekp(0);
    fs.close();

    
    
    
}

bool Disk_SM::read_page(uint16_t page_num,Node* maybe){
    
    std::fstream fs;
    fs.open(file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    fs.seekg((page_num-1)*4096);
    
    
    fs.read(reinterpret_cast<char*>(maybe),sizeof(*maybe));
    
    
    fs.clear();
    fs.seekg(0);
    fs.close();
    
    return true;

}

