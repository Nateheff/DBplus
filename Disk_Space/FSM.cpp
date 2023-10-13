
#include "FSM.h"

bool FSM::create_fsm(std::string name_val){
    // data.free_page = 0;
    // data.hole = 0;
    // data.free_space[0] = 1;
    // data.free_space[1]=1;
    // std::ofstream fs;
    // fs.open(name+"_fsm.db",std::ios_base::binary);
    // fs.write(reinterpret_cast<char*>(&data),51250);
    // std::cout<<"wrote: "<<fs.tellp()<<std::endl;
    // fs.close();
    // delete [] data.free_space;
    name = name_val+"_fsm.db";
    std::fstream fs;
    //std::cout<<name<<std::endl;
    fs.open(name,std::ios_base::binary|std::ios_base::out);
    // FSM_Data_Root root_empty;
    // root = &root_empty;
    set_space(0,1);
    fs.write(reinterpret_cast<char*>(&root),sizeof(root));
    std::cout<<"wrote"<<std::endl;
    std::cout<<"made"<<std::endl;
    fs.close();

};

void FSM::new_page(){
    std::cout<<"CALLED"<<std::endl;
    // std::fstream fs;
    // fs.open(name,std::ios_base::binary);

    // fs.read(reinterpret_cast<char*>(root),sizeof(*root));
    std::fstream fs;
    uint32_t offset = ((((root.num_pages)-4088)/4096)+1)*4096;
    if(offset == 0){
    std::cout<<"wrong call"<<std::endl;
    return;
    };
    FSM_Data new_data;
    fs.seekp(offset);
    fs.write(reinterpret_cast<char*>(&new_data),sizeof(new_data));
    root.num_pages++;
    fs.close();
    
}

void FSM::get_fsm(std::string name_val){
    
    std::fstream fs;
    //std::cout<<name<<std::endl;
    name = name_val + "_fsm.db";
    // std::cout<<name<<std::endl;
    // FSM_Data_Root empty;
    // root= &empty;
    fs.open(name,std::ios_base::binary | std::ios_base::in);
    // if(fs.is_open() && fs.good())
    // std::cout<<"early"<<std::endl;
    fs.read(reinterpret_cast<char*>(&root),sizeof(root));
std::cout<<"read"<<std::endl;
    if(fs.gcount()==0 && !fs.fail()){
        std::cout<<"EMPTY"<<std::endl;
        
    }else if(fs.fail() || !fs.is_open()){
        std::cout<<"BAD: "<<fs.gcount()<<std::endl;
        
    }else{
        // std::cout<<"Read: "<<fs.tellg()<<std::endl;
    }
    fs.close();
  
    
}

void FSM::set_space(uint32_t page_num,uint8_t space){
    if(page_num > root.num_pages){
        std::cout<<"INVALID PAGE NUM: "<<page_num<<" "<<(int)space<<std::endl;
        return;
    }

    //std::cout<<"Here"<<page_num<<std::endl;
    if(page_num > 4088){
        std::fstream fs;
    
        fs.open(name,std::ios_base::binary | std::ios_base::in);
        std::cout<<"WOAH"<<std::endl;
        uint32_t offset = ((((page_num)-4088)/4096)+1)*4096;
        fs.seekp(offset);
        fs.read(reinterpret_cast<char*>(data),sizeof(*data));
        data->free_space[page_num - (offset)] = space;
        if(space == 0){
            if(page_num==root.num_pages -1)
                root.num_pages--;
            else
                root.hole = page_num;
        }else if(space == 1){
            if(page_num == root.num_pages)
            root.num_pages++;
            else if(page_num == root.hole)
            root.hole = 0;
        }
        if(data->free_space[4095] != 0 && root.hole > offset && root.hole < offset+4096){
            this->new_page();
            std::cout<<"hole: "<<root.hole<<" page: "<<page_num<<std::endl;
        }
        fs.close();
    }else{
        root.free_space[page_num] = space;
        if(space == 0){
            if(page_num==root.num_pages -1)
                root.num_pages--;
            else
                root.hole = page_num;
        }else if(space == 1){
            if(page_num == root.num_pages)
            root.num_pages++;
            else if(page_num == root.hole)
            root.hole = 0;
        }
        if(root.free_space[4087]!= 0 && (root.hole > 4088 || root.hole == 0)){
        std::cout<<"hole2: "<<root.hole<<" page2: "<<page_num<<(int)root.free_space[4087]<<std::endl;
        this->new_page();
        
        }
    }
    if(root.num_pages >= 4000)
    std::cout<<"NUM Pages: "<<root.num_pages<<std::endl;
    
};
void FSM::flush_fsm(uint32_t page_num){
    std::fstream fs;
    fs.open(name,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    // std::cout<<name<<std::endl;
    // fs.seekp(0);
    // std::cout<<root.num_pages<<" "<<root.hole<<" "<<(int)root.free_space[3]<<std::endl;
    fs.write(reinterpret_cast<char*>(&root),sizeof(root));
    // std::cout<<fs.tellp()<<std::endl;
    if(page_num != 0){
        std::cout<<"wrong"<<std::endl;
    uint32_t offset = ((((page_num)-4088)/4096)+1)*4096;
    fs.seekg(offset);
    fs.write(reinterpret_cast<char*>(data),sizeof(*data));
    };
    fs.close();
}

uint8_t FSM::has_space(uint32_t page_num,uint16_t check){
    //std::cout<<"Here: "<<page_num<<std::endl;
    if(page_num > 4088){
        std::cout<<"wrong2: "<<page_num<<" b "<<check<<std::endl;
        return 0;
    uint32_t offset = ((((page_num)-4088)/4096)+1)*4096;
    std::fstream fs;
    fs.seekp(offset);
    fs.read(reinterpret_cast<char*>(data),sizeof(*data));
    uint16_t index = page_num - offset - 1;
    return data->free_space[index];
    }else{
        return root.free_space[page_num];
    }
}

uint32_t FSM::page() {
    // if(root.num_pages > 600)
    // std::cout<<root.num_pages<<std::endl;
    if(!root.hole)
    return root.num_pages; 
    else { 
        std::cout<<"HOLE!"<<std::endl;
        return root.hole;
    };
    
    };