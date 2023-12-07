
#include "FSM.h"

bool FSM::create_fsm(std::string name_val){
    
    name = name_val+"_fsm.db";
    
    std::fstream fs;
    fs.open(name,std::ios_base::binary|std::ios_base::out);
    
    root.num_pages = 1;
    set_space(0,1);
    fs.write(reinterpret_cast<char*>(&root),sizeof(root));
    
    fs.close();
    return true;

};

void FSM::new_page(){
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

bool FSM::get_fsm(std::string name_val){
    
    std::fstream fs;
    name = name_val + "_fsm.db";
    // FSM_Data_Root empty;
    // root= &empty;
    int x = -1;
    try{
    fs.open(name,std::ios_base::binary | std::ios_base::in|std::ios_base::out);
    fs.read(reinterpret_cast<char*>(&root),sizeof(root));
    throw x;
    }catch(int x){
        return false;
    }
    if(fs.gcount()==0 && !fs.fail()){
        std::cout<<"EMPTY"<<std::endl;
        
    }else if(fs.fail() || !fs.is_open()){
        std::cout<<"BAD: "<<fs.gcount()<<std::endl;
        
    }else{
        std::cout<<"Read: "<<fs.tellg()<<std::endl;
    }
    fs.close();
  return true;
    
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
        uint32_t offset = ((((page_num)-4088)/4096)+1)*4096;
        fs.seekp(offset);
        fs.read(reinterpret_cast<char*>(data),sizeof(*data));
        data->free_space[page_num - (offset)] = space;
        if(space == 0){
            if(page_num==root.num_pages -1)
                root.num_pages--;
            else if(page_num < root.num_pages && page_num > root.hole)
                return;
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
        this->new_page();
        
        }
    }
    
    
};
void FSM::flush_fsm(uint32_t page_num){
    std::fstream fs;
    fs.open(name,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    
    fs.write(reinterpret_cast<char*>(&root),sizeof(root));
    if(page_num > 4088){
        std::cout<<"wrong"<<std::endl;
    uint32_t offset = ((((page_num)-4088)/4096)+1)*4096;
    fs.seekg(offset);
    fs.write(reinterpret_cast<char*>(data),sizeof(*data));
    };
    fs.close();
}

uint8_t FSM::has_space(uint32_t page_num){
    if(page_num > 4088){
        std::cout<<"wrong2: "<<page_num<<std::endl;
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
    
    if(!root.hole || root.hole >= root.num_pages)
    return root.num_pages; 
    else { 
        std::cout<<"HOLE!"<<std::endl;
        if((root.hole - 1)==root.num_pages){
            uint32_t hole = root.hole;
            root.hole= 0;
            return hole;
        }
        
        if(root.hole > 4088){
            std::fstream fs;
            uint32_t offset = ((((root.hole)-4088)/4096)+1)*4096;
        fs.seekp(offset);
        fs.read(reinterpret_cast<char*>(data),sizeof(*data));
        fs.close();
        root.hole-=4088;
        if(data->free_space[(root.hole-((root.hole/4096)*4096))+1] == 0){
            uint32_t hole = root.hole;
            root.hole++;
            return hole;
        }
        }else{
            if(root.free_space[root.hole+1]==0){
                uint32_t hole = root.hole;
            root.hole++;
            return hole;
            }
        }
    };
    
    };