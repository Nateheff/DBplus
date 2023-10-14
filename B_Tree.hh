#pragma once

// void B_Tree::create_catalog(){
//     std::string name = {"catalog_rel"};
//     std::ofstream fs;
//     fs.open(name+".db",std::ios_base::binary);
//     S empty;

    
//     for(size_t i =0; i<26;i++){
//         info.rel.rows[i] = empty;
//     }
    
//     fs.write(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
    
//     fs.close();
//     // std::cout<<"catalog: "<<name<<std::endl;
//     fsm.create_fsm(name);
    
// };
template<typename T,typename S>
uint16_t B_Tree<T,S>::calc_name(char* arr){
    uint16_t name{};
    for(size_t i = 0;i<64;i++)
    name += arr[i];
    
    return name;
}

template<typename T,typename S>
void B_Tree<T,S>::search(uint16_t key,uint16_t num_rows,bool has_height){
    
    // std::cout<<"started"<<std::endl;
    info.fs->close();
    // std::cout<<"started"<<std::endl;
    if(!info.fs->is_open()){
    info.fs->open(file+".db",std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    // std::cout<<"open"<<std::endl;
    //search through root
    };
    
    T leaf;
    
    //get pointer
    
    uint32_t offset{};
    
    if(has_height){
        
        
        info.fs->seekg(0);
        info.fs->read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
        
        uint16_t index = info.root.next_index;
        info.offsets.push_back(0);
        // std::cout<<"Root: "<<info.root.page_id<<" "<<info.root.arr[0].key<<" "<<(int)info.root.next_index<<std::endl;
        // std::cout<<"Bottom: "<<info.root.bottom_p<<std::endl;
    for(size_t i = 0;i<15;i++)
    std::cout<<i<<": "<<"Key: "<<info.root.arr[i].key<<" Pointer: "<<info.root.arr[i].pointer<<std::endl;
    
    while(index == 1){
       
        // std::cout<<"HERE "<<index<<std::endl;
    for(size_t i = 0; i < 511;i++){
        if(info.root.arr[0].key > key){
            // std::cout<<"3"<<std::endl;
            offset = info.root.bottom_p;
            info.offsets.push_back(offset);
            info.fs->seekg(offset);
            info.fs->read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            
            index = info.root.next_index;
            
            break;
        } else if(info.root.arr[i].key > key && info.root.arr[i-1].key < key){
            // std::cout<<"2"<<std::endl;
            offset = info.root.arr[i].pointer;
            info.offsets.push_back(offset);
            info.fs->seekg(offset);
            info.fs->read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            
            index = info.root.next_index;
            
            break;
        } else if(info.root.arr[i].key == key){
            // std::cout<<"1: "<<i<<std::endl;
            
            info.offsets.push_back(info.root.arr[i].pointer);
            offset = info.root.arr[i].pointer;
            info.fs->seekg(offset);
            info.fs->read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            
            index = info.root.next_index;
                     
            break;

        } else if(info.root.arr[i].key < key && info.root.arr[i+1].pointer == 0){
            // std::cout<<"4"<<std::endl;
            info.offsets.push_back(info.root.arr[i].pointer);

            offset = info.root.arr[i].pointer;
            // std::cout<<"offseT: "<<offset<<" "<<info.root.arr[i].key<<std::endl;
            info.fs->seekg(offset);
            info.fs->read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            
            // std::cout<<"RooT: "<<info.root.page_id<<" "<<(int)info.root.next_index<<" "<<info.fs->gcount()<<std::endl;
            index = info.root.next_index;
            
            break;
        }
       
    }
    // std::cout<<"next_index: "<<index<<" root: "<<info.root.page_id<<std::endl;
    };
    // std::cout<<"step 1: "<<info.offsets.size()<<std::endl;
    // std::cout<<"Index ID: "<<info.root.page_id<<std::endl;
    for(size_t i = 0; i < 511;i++){
        if(info.root.arr[i].key == key){
            std::cout<<"equals: "<<i<<std::endl;
            info.index_root = i;
            offset = info.root.arr[i].pointer;
            
            info.fs->seekg(offset);
            // std::cout<<"offset: "<<offset<<std::endl;
            info.fs->read(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
            
            break;
            

        } else if(i ==0 && key < info.root.arr[i].key){
            // std::cout<<info.root.page_id<<" "<<info.root.arr[0].key<<" "<<info.root.arr[0].pointer<<std::endl;
            std::cout<<"lower"<<std::endl;
            info.index_root = i;
            offset = info.root.bottom_p;
            
            info.fs->seekg(offset);
            // std::cout<<"offset: "<<offset<<std::endl;
            info.fs->read(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
            
            break;

        } else if(info.root.arr[i].key > key && info.root.arr[i-1].key < key){
            std::cout<<key<<" between: "<<info.root.arr[i-1].key<<" and "<<info.root.arr[i].key<<" at "<<i<<std::endl;
            info.index_root = i;
            offset = info.root.arr[i-1].pointer;
            // std::cout<<"offset: "<<offset<<std::endl;
            
            
            info.fs->seekg(offset);
            info.fs->read(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
            
            // std::cout<<info.rel.page_id<<std::endl;
            // std::cout<<info.root.arr[i].key<<std::endl;
            break;
        }else if(info.root.arr[i].key < key && info.root.arr[i+1].pointer == 0){
            info.index_root = i+1;
            std::cout<<i<<"larger than: "<<info.root.arr[i].key<<std::endl;
            offset = info.root.arr[i].pointer;
            
            
            info.fs->seekg(offset);
            
            info.fs->read(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
            
            
            break;
        }
        
    }
    // std::cout<<"step 2: "<<info.offsets.size()<<std::endl;
    // std::cout<<"Rel: "<<info.rel.page_id<<" "<<info.rel.is_index<<std::endl;
    
    }else{
        // std::cout<<"No height"<<std::endl;
        info.fs->seekg(0);
        info.fs->read(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
        
        info.rel.page_id = 0;

    };
    // std::cout<<"got the rel"<<info.rel.page_id<<std::endl;
    for(size_t i =0;i<num_rows;i++){
        uint16_t name{};
        
        for(size_t j = 0; j<64;j++){
        name += info.rel.rows[i].index[j];
        }
        std::cout<<"name: "<<name<<" key: "<<key<<std::endl;
        
        if(key <= name || (i == num_rows-1 && key > name)||info.rel.rows[i].check == 0){
            std::cout<<"searching "<<i<<" "<<key<<" vs "<<name<<std::endl;
            info.index = i;
            
            return;
        }
     
    }
    
    
    };

template<typename T,typename S>
void B_Tree<T,S>::remove(uint16_t key, uint16_t num_rows, bool has_height){
    //search like you did in search
    std::cout<<"here"<<std::endl;
    search(key,num_rows,1);
    std::cout<<"Searched"<<std::endl;
    if(!fsm.has_root()){
    fsm.get_fsm(file);
    std::cout<<"got the fsm"<<std::endl;
    }
    std::cout<<"Info: "<<info.rel.page_id<<" "<<info.rel.rows[info.index].index<<std::endl;
    for(size_t i = 0;i<num_rows:i++)
    std::cout<<i<<": "<<info.rel.rows[i].index<<std::endl;
    //once you have the correct page and relation row, delete the row from the array of relation rows. Update the fsm and any other things you need to telling them that space is open. maybe try to move all the rows "above" the one you delete down to have the free space at the end which will make free space easier to track
    S empty;
    info.rel.rows[row.index] = empty;
    for(size_t i = row.index; i < num_rows;i++){
        info.rel.rows[i] = info.rel.rows[i+1];
    }
    for(size_t i = 0;i<num_rows:i++)
    std::cout<<i<<": "<<info.rel.rows[i].index<<std::endl;
    if(info.rel.rows[0].check == 0){
        fsm.set_space(info.rel.page_id,0);
        std::cout<<"huh"<<std::endl;
    }else
    fsm.set_space(info.rel.page_id,1);

    fsm.flush_fsm(info.rel.page_id);
    

};

template<typename T,typename S>
void B_Tree<T,S>::insert(uint16_t key, S row,uint16_t num_rows,size_t test){
//search normally
    
    // std::cout<<"Key: "<<key<<std::endl;
    if(test > num_rows)
    search(key,num_rows,1);
    else
    search(key,num_rows,0);
    
    // std::cout<<"Offsets: "<<info.offsets.size()<<std::endl;
    // std::cout<<"Page: "<<info.rel.page_id<<std::endl;
    // std::cout<<"Root: "<<info.root.page_id<<std::endl;

// std::cout<<"Searched"<<info.rel.page_id<<std::endl;
    // std::cout<<info.root.arr[0].key<<std::endl;
    
    //std::cout<<"still";
    
//once you have the page of where the row with the key would fit, see if there's space via the fsm and if there is, move all rows "greater" than it up 1 row space and put the new row in the space created at the correct place. If there's not room, split, and do the b+ tree thing. this will take some effort to figure out how to do.
    
    // std::cout<<"beginning insert: "<<info.rel.page_id<<std::endl;
   
    if(!fsm.has_root()){
    fsm.get_fsm(file);
    std::cout<<"got fsm"<<std::endl;
    }
    
    // std::cout<<"Checking: "<<real<<std::endl;
    //std::cout<<"Got the FSM"<<std::endl;
    //THIS IS BASICALLY JUST THE B+ TREE INSERT IMPLEMENTATION, SO JUST REPLACE THIS WITH B+ TREE INSERT WHEN ITS DONE
    uint16_t key_of_interest{};
    uint32_t new_page_offset{};
    uint32_t new_low_p{};
    
    // std::cout<<"Checking: "<<info.rel.page_id<<std::endl;
    if(fsm.has_space(info.rel.page_id,test)==1){
        // std::cout<<"Has space"<<std::endl;
        
        //std::cout<<"INDEX: "<<info.index<<row.index<<std::endl;
        S empty;
        // for(size_t i=0;i<26;i++)
        //     std::cout<<i<<": "<<info.rel.rows[i].check<<std::endl;
        for(size_t i = num_rows-2;i >= info.index;i--){
            
            
            info.rel.rows[i+1] = info.rel.rows[i];
            info.rel.rows[i] = empty;
            if(i == 0)
            break;
        }
        
        // for(size_t i=0;i<26;i++)
        //     std::cout<<i<<": "<<info.rel.rows[i].check<<std::endl;
        // std::cout<<"ROW: "<<row.check<<std::endl;
        // 
        info.rel.rows[info.index] = row;
        // for(size_t i=0;i<26;i++)
        //     std::cout<<i<<": "<<info.rel.rows[i].index<<std::endl;
        fsm.set_space(info.rel.page_id,1);
        //  std::cout<<"ATTENTION: "<<info.rel.rows[0].check<<info.rel.rows[1].check<<std::endl;
        if(info.rel.rows[num_rows-1].check != 0){
        // std::cout<<"1!"<<std::endl;
        fsm.set_space(info.rel.page_id,2);
        }
        
         //write back
        //  std::cout<<"THIS: "<<info.offsets.size()<<std::endl;
        // 
        
        
       
        info.fs->seekp(info.rel.page_id*4096);
        
        info.fs->write(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
        
       fsm.flush_fsm(0);
       
    //    
        info.offsets.clear();
   
    
        return;
    }else{
         //step 1: split leaf, get positon of new leaf.
        // std::cout<<"words: "<<info.offsets.size()<<std::endl;
        if(info.offsets.size()>=1){
        T half;
        half.page_id = fsm.page();
        
        // if(half.page_id >=469)
        // std::cout<<"still "<<std::endl;
        // std::cout<<"PAGE: "<<half.page_id;
        new_page_offset = (half.page_id) * 4096;
        // std::cout<<"OFF: "<<new_page_offset<<std::endl;
    
        S empty;
        for(size_t i = num_rows/2; i<num_rows;i++){
            half.rows[i-(num_rows/2)]=info.rel.rows[i];
            info.rel.rows[i] = empty;
            
        }
        // for(size_t i=0;i<26;i++)
        //     std::cout<<i<<": "<<info.rel.rows[i].check<<std::endl;
        // for(size_t i=0;i<26;i++)
        //     std::cout<<i<<": "<<info.rel.rows[i].check<<std::endl;
        // for(size_t i=0;i<26;i++)
        //     std::cout<<i<<": "<<half.rows[i].check<<std::endl;
        //make room and insert new row into proper leaf and get upper median key to send to parent node.
       
        if(info.index < num_rows/2){
            // std::cout<<"1"<<std::endl;
            key_of_interest = calc_name(info.rel.rows[(num_rows/2)-1].index);
            for(size_t i = num_rows/2; i > info.index;i--){
                info.rel.rows[i] = info.rel.rows[i-1];
            };
            info.rel.rows[info.index] = row;
            
        }else if(info.index > num_rows/2){
            
            key_of_interest = calc_name(half.rows[0].index);
            // std::cout<<"Bruh: "<<key_of_interest<<std::endl;
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                half.rows[i] = half.rows[i-1];
            }
            half.rows[info.index -(num_rows/2) ] = row;
        }else{
            key_of_interest = key;
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                half.rows[i] = half.rows[i-1];
            }
            half.rows[info.index -(num_rows/2)] = row;
        };
        fsm.set_space(half.page_id,1);
        fsm.set_space(info.rel.page_id,1);
        info.fs->seekp(info.rel.page_id * 4096);
        info.fs->write(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
        
        info.fs->seekp(new_page_offset);
        info.fs->write(reinterpret_cast<char*>(&half),sizeof(half));
        
        
        }
        
    };
    // step 2: send new KOI/position of new to parent node.
    Key_Pointer k_p{key_of_interest,new_page_offset};
    // if(test > 8384)
//   std::cout<<"made it here: "<<info.offsets.size()<<info.root.page_id<<std::endl;
  if(info.offsets.size() >= 1){
    for(size_t i = info.offsets.size()-1; i >= 0; i--){
        // std::cout<<"here"<<std::endl;
        //get parent node into memory
        // Syst_Root root;
        // info.fs->seekg(info.offsets.at(i));
        // info.fs->read(reinterpret_cast<char*>(&root),4096);
        // std::cout<<info.root.page_id<<" "<<fsm.has_space(info.root.page_id)<<std::endl;
        if(fsm.has_space(info.root.page_id,2)==1){
            // std::cout<<"space: "<<k_p.key<<" "<<k_p.pointer<<std::endl;
            // step 3: if parent has room, insert at appropriate location. 
            
            // std::cout<<"ROOT: "<<info.root.page_id<<std::endl;
            // std::cout<<info.root.arr[i].key<<": "<<info.root.arr[i].pointer<<std::endl;
            if(info.index_root >= 4096){
                std::cout<<"space: "<<k_p.key<<" "<<k_p.pointer<<std::endl;
            // step 3: if parent has room, insert at appropriate location. 
            
            std::cout<<"ROOT: "<<info.root.page_id<<std::endl;
            for(size_t i = 0; i < 511;i++){
                if(info.root.arr[i].key == key){
            // std::cout<<"equals: "<<i<<std::endl;
                info.index_root = i;
                break;
                } else if(i ==0 && key < info.root.arr[i].key){
            // std::cout<<info.root.page_id<<" "<<info.root.arr[0].key<<" "<<info.root.arr[0].pointer<<std::endl;
            // std::cout<<"lower"<<std::endl;
                info.index_root = i;
                break;

                } else if(info.root.arr[i].key > key && info.root.arr[i-1].key < key){
            // std::cout<<key<<" between: "<<info.root.arr[i-1].key<<" and "<<info.root.arr[i].key<<" at "<<i<<std::endl;
                info.index_root = i;
                break;
                }else if(info.root.arr[i].key < key && info.root.arr[i+1].pointer == 0){
                info.index_root = i+1;
            
                break;
                }
            }
            };
            for(size_t i = 510;i > info.index_root;i--)
            info.root.arr[i] = info.root.arr[i-1];
            // std::cout<<"word "<<info.root.page_id<<" "<<info.index_root<<std::endl;
            info.root.arr[info.index_root] = k_p;
            if(info.root.arr[510].key != 0){
                std::cout<<"2!"<<info.root.arr[510].key<<" "<<info.root.page_id<<std::endl;
            fsm.set_space(info.root.page_id,2);
            }
            info.fs->seekp(info.root.page_id*4096);
            info.fs->write(reinterpret_cast<char*>(&info.root),4096);
            
            fsm.flush_fsm(0);
            // std::cout<<"flush"<<std::endl;
            info.offsets.clear();
            // std::cout<<"going: "<<info.index_root<<std::endl;
            info.index_root = 0;
            return;
        }else if(fsm.has_space(info.root.page_id,3)!=1 && i != 0){
            //If parent does not have room, split parent and get location of new parent.
            std::cout<<"splitting index: "<<info.root.page_id<<" "<<info.index_root<<" "<<info.offsets.size()<<std::endl;

            Syst_Root half_root;
            half_root.page_id = fsm.page();
            // std::cout<<"New page: "<<half_root.page_id<<std::endl;
            uint32_t offset_new_index = half_root.page_id*4096;
            uint16_t temp_koi{};
            

            //split
            Key_Pointer empty;
            if(info.index_root > 256){
            std::cout<<"more1"<<std::endl;
            temp_koi = info.root.arr[256].key;
            half_root.bottom_p = info.root.arr[256].pointer;
            info.root.arr[256]=empty;
            for(size_t i = 257;i < 511;i++){
            half_root.arr[i-257] = info.root.arr[i];
            
            
            info.root.arr[i]=empty;
        }
            
             
            for(size_t i= 256; i > info.index_root - 256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[info.index_root] = k_p;
        }else if(info.index_root< 256){
            std::cout<<"less1"<<std::endl;
            temp_koi = info.root.arr[255].key;
            half_root.bottom_p = info.root.arr[255].pointer;
            info.root.arr[255]=empty;
            for(size_t i = 256;i < 511;i++){
            half_root.arr[i-256] = info.root.arr[i];
            
            
            info.root.arr[i]=empty;
            }

            for(size_t i =256; i > info.index;i--){
                info.root.arr[i]=info.root.arr[i-1];
                // info.root.arr[i-1]=empty;
            }
            info.root.arr[info.index_root] = k_p;
        }else{
            std::cout<<"special1"<<std::endl;
            temp_koi = key;
            
            half_root.bottom_p = k_p.pointer;
            // info.root.arr[256]=empty;
            for(size_t i = 257;i < 511;i++){
            half_root.arr[i-257] = info.root.arr[i];
            
            
            info.root.arr[i]=empty;
        }
            for(size_t i= 256; i > info.index_root - 256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[info.index_root] = k_p;
            };
            // step 4: send new KOI/position of new index node to the parent node and if room, insert at appropriate location.
            // std::cout<<"New Stuff: "<<temp_koi<<" "<<offset_new_index<<" "<<half_root.page_id<<" "<<half_root.bottom_p<<std::endl;
            k_p.key = temp_koi;
            k_p.pointer = offset_new_index;
            half_root.next_index = info.root.next_index;
            // for(size_t i = 0; i<256;i++)
            // std::cout<<i<<": "<<half_root.arr[i].key<<std::endl;
            // for(size_t i = 0; i < 256;i++)
            // std::cout<<i<<": "<<info.root.arr[i].key<<std::endl;
            // std::cout<<i<<" ATTENTION: "<<info.offsets.at(i)<<" "<<info.offsets.at(i-1)<<std::endl;
            fsm.set_space(info.root.page_id,1);
            fsm.set_space(half_root.page_id,1);
            info.fs->seekp(info.root.page_id*4096);
            info.fs->write(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            info.fs->seekp(half_root.page_id*4096);
            info.fs->write(reinterpret_cast<char*>(&half_root),sizeof(half_root));
            info.fs->seekg(info.offsets.at(i-1));
            info.fs->read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            info.index_root = 4097;
            info.offsets.clear();
            // std::cout<<"DONEE"<<std::endl;
        }else if(fsm.has_space(info.root.page_id,4)!=1 && i == 0){
            std::cout<<"SPLTTING ROOT: "<<i<<" "<<info.offsets.size()<<std::endl;
            Key_Pointer empty;
            Syst_Root half_root;
            
            half_root.page_id = fsm.page();
            // std::cout<<"Half: "<<half_root.page_id<<std::endl;
        //split current info.root
        //if i > 255, the koi goes to i=256 else, i = 255
        

        
        
        fsm.set_space(half_root.page_id,1);

        // std::cout<<"still"<<half_root.page_id<<std::endl;
        info.root.page_id = fsm.page();
        // std::cout<<"Old root: "<<info.root.page_id<<std::endl;
        fsm.set_space(info.root.page_id,1);
        //get new info.root page and send koi and location of new "children" to new info.root for l & r pointers
        Syst_Root new_root;
        uint16_t temp_koi{};
        uint32_t temp_p{};



        // std::cout<<"INDeX: "<<info.index_root<<std::endl;
        if(info.index_root > 256){
            std::cout<<"more"<<std::endl;
            temp_koi = info.root.arr[256].key;
            half_root.bottom_p = info.root.arr[256].pointer;
            info.root.arr[256]=empty;
            for(size_t i = 257;i < 511;i++){
            half_root.arr[i-257] = info.root.arr[i];
            
            
            info.root.arr[i]=empty;
        }
            
             
            for(size_t i= 256; i > info.index_root - 256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[info.index_root] = k_p;
        }else if(info.index_root< 256){
            std::cout<<"less"<<std::endl;
            temp_koi = info.root.arr[255].key;
            half_root.bottom_p = info.root.arr[255].pointer;
            info.root.arr[255]=empty;
            for(size_t i = 256;i < 511;i++){
            half_root.arr[i-256] = info.root.arr[i];
            
            
            info.root.arr[i]=empty;
            }
            // temp_koi = info.root.arr[255].key;
            for(size_t i =256; i > info.index;i--){
                info.root.arr[i]=info.root.arr[i-1];
            }
            info.root.arr[info.index_root] = k_p;
        }else{
            std::cout<<"special"<<std::endl;
            temp_koi = key;
            
            half_root.bottom_p = k_p.pointer;
            // info.root.arr[256]=empty;
            for(size_t i = 257;i < 511;i++){
            half_root.arr[i-257] = info.root.arr[i];
            
            
            info.root.arr[i]=empty;
        }
            for(size_t i= 256; i > info.index_root - 256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[info.index_root] = k_p;
            };
        //     for(size_t i = 0;i<257;i++){
        //     std::cout<<i<<": "<<info.root.arr[i].key<<std::endl;
        // }
        // for(size_t i = 0;i<257;i++){
        //     std::cout<<i<<": "<<half_root.arr[i].key<<std::endl;
        // }
            k_p.key = temp_koi;
            //switch the current 0 index page and the info.root page  so the info.root is always at index 0
            k_p.pointer = half_root.page_id * 4096;
            // std::cout<<"Pointer OI: "<<k_p.pointer<<std::endl;
            new_root.page_id = 0;
            new_root.bottom_p = info.root.page_id * 4096;
            // std::cout<<"Bottom P: "<<new_root.bottom_p<<std::endl;
            // info.root.next_index = 0;
            half_root.next_index = info.root.next_index;
            new_root.next_index = 1;
            new_root.arr[0]=k_p;
            fsm.set_space(0,1);
            info.fs->seekp(0);
            info.fs->write(reinterpret_cast<char*>(&new_root),4096);
            info.fs->seekp((half_root.page_id)*4096);
            info.fs->write(reinterpret_cast<char*>(&half_root),4096);
            info.fs->seekg((info.root.page_id)*4096);
            info.fs->write(reinterpret_cast<char*>(&info.root),4096);
            fsm.flush_fsm(0);
            std::cout<<"it worked? "<<new_root.bottom_p<<" "<<test<<" "<<new_root.arr[0].pointer<<" "<<half_root.bottom_p<<" "<<info.root.bottom_p<<std::endl;
            info.offsets.clear();
            return;
        }; 
        // step 5: repeat until opening in index or at top level (root)
        std::cout<<"nowhere"<<std::endl;
    };
  }else{
    Key_Pointer empty;
            Syst_Root new_root;
            T half;
            
            new_root.page_id = 0;
            new_root.bottom_p = 4096;
            S empty_row;

            for(size_t i = num_rows/2;i < num_rows;i++){
                half.rows[i-(num_rows/2)] = info.rel.rows[i];
                info.rel.rows[i] = empty_row;
            
            }
            
            if(info.index < num_rows/2){
                key_of_interest = calc_name(info.rel.rows[(num_rows/2)-1].index);
            for(size_t i = num_rows/2; i > info.index;i--){
                info.rel.rows[i] = info.rel.rows[i-1];
            };
            info.rel.rows[info.index] = row;
            }else if(info.index > num_rows/2){
            key_of_interest = calc_name(half.rows[0].index);
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                half.rows[i] = half.rows[i-1];
            }
            half.rows[info.index -(num_rows/2) ] = row;
        }else
            key_of_interest = key;
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                half.rows[i] = half.rows[i-1];
        }
        // std::cout<<"KOI: "<<key_of_interest<<std::endl;
        //get new root page and send koi and location of new "children" to new root for l & r pointers
        
        

        
        new_root.arr[0] = {key_of_interest,8192};
        new_root.next_index=0;
        info.rel.page_id = 1;
        half.page_id = 2;

        
            //switch the current 0 index page and the root page  so the root is always at index 0
            
            fsm.set_space(0,1);
            fsm.set_space(1,1);
            fsm.set_space(2,1);
            
            info.fs->seekp(0);
            info.fs->write(reinterpret_cast<char*>(&new_root),sizeof(new_root));
            info.fs->seekp((info.rel.page_id)*4096);
            info.fs->write(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
            info.fs->seekp((half.page_id)*4096);
            info.fs->write(reinterpret_cast<char*>(&half),sizeof(half));
        info.fs->close();
        info.index = 0;
        info.offsets.clear();
        
        fsm.flush_fsm(0);
        
        std::cout<<"split"<<std::endl;
  };
  
// step 6: if need to split root, get new root page, send koi and locations of children to new root. save location of new root in specialized file with root locations of each index.
    // fsm.flush_fsm(std::string{"catalog_rel"});
};