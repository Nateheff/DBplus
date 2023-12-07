#pragma once


template<typename T,typename S>
uint16_t B_Tree<T,S>::calc_name(const char* arr){
    uint16_t name{};
    for(size_t i = 0;i<strlen(arr);i++)
    name += arr[i]=='\0' ? 0:arr[i];
    
    return name;
}




template<typename T,typename S>
void B_Tree<T,S>::search_catalog(uint16_t key,uint16_t num_rows,std::string database){
    
    
    
        
    std::fstream fs;
    
    
    
   
    fs.open(file+".db",std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    //search through root
    
    
    
    //get pointer
    
    uint32_t offset{};
    
    if(height){
        
        fs.seekg(0);
        fs.read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
        
        uint16_t index = info.root.next_index;
        info.offsets.push_back(0);
        
    
    while(index == 1){
       
    for(size_t i = 0; i < 511;i++){
        if(info.root.arr[0].key > key){
            offset = info.root.bottom_p;
            info.offsets.push_back(offset);
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            
            index = info.root.next_index;
            
            break;
        } else if(info.root.arr[i].key > key && info.root.arr[i-1].key < key){
            offset = info.root.arr[i].pointer;
            info.offsets.push_back(offset);
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            
            index = info.root.next_index;
            
            break;
        } else if(info.root.arr[i].key == key){
            
            info.offsets.push_back(info.root.arr[i].pointer);
            offset = info.root.arr[i].pointer;
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            
            index = info.root.next_index;
                     
            break;

        } else if(info.root.arr[i].key < key && info.root.arr[i+1].pointer == 0){
            info.offsets.push_back(info.root.arr[i].pointer);

            offset = info.root.arr[i].pointer;
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            
            index = info.root.next_index;
            
            break;
        }
       
    }
    };
    for(size_t i = 0; i < 511;i++){
        if(info.root.arr[i].key == key){
            info.index_root = i;
            offset = info.root.arr[i].pointer;
            
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
            
            break;
            

        } else if(i ==0 && key < info.root.arr[i].key){
            info.index_root = i;
            offset = info.root.bottom_p;
            
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
            
            break;

        } else if(info.root.arr[i].key > key && info.root.arr[i-1].key < key){
            info.index_root = i;
            offset = info.root.arr[i-1].pointer;
            
            
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
       
            break;
        }else if(info.root.arr[i].key < key && info.root.arr[i+1].pointer == 0){
            info.index_root = i+1;
            offset = info.root.arr[i].pointer;
            
            
            fs.seekg(offset);
            
            fs.read(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
            
            
            break;
        }
        
    }
    
    }else{
        
        fs.seekg(0);
        fs.read(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
        info.rel.page_id = 0;

    };
    
    for(size_t i =0;i<num_rows;i++){
        uint16_t name{};
            for(size_t j = 0; j<63;j++){
            name += info.rel.rows[i].index[j];
            
            }
            if(key <= name || (i == num_rows-1 && key > name)||info.rel.rows[i].check == 0){
                
                info.index = i;
                
                return;
                
        }
        
    }
    
    
    };

template<typename T,typename S>
void B_Tree<T,S>::remove_catalog(uint16_t key, uint16_t num_rows){
    //search like you did in search
    
    search_catalog(key,num_rows);
    std::fstream fs;
    if(!fsm.has_root())
    fsm.get_fsm(file);
    
    
    
    //once you have the correct page and relation row, delete the row from the array of relation rows. Update the fsm and any other things you need to telling them that space is open. maybe try to move all the rows "above" the one you delete down to have the free space at the end which will make free space easier to track
    S empty;
    info.rel.rows[info.index] = empty;
    for(size_t i = info.index; i < num_rows;i++){
        info.rel.rows[i] = info.rel.rows[i+1];
    }
    
    
    if(info.rel.rows[0].check == 0)
        fsm.set_space(info.rel.page_id,0);
        
    else
    fsm.set_space(info.rel.page_id,1);

    fsm.flush_fsm(info.rel.page_id);
    fs.open(file+".db",std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    fs.seekp(info.rel.page_id*4096);
    fs.write(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
    fs.close();

};

template<typename T,typename S>
void B_Tree<T,S>::insert_catalog(uint16_t key, S row,uint16_t num_rows){
//search normally
    
    
    
    search_catalog(key,num_rows);
    std::fstream fs;
    fs.open(file+".db",std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    


    
//once you have the page of where the row with the key would fit, see if there's space via the fsm and if there is, move all rows "greater" than it up 1 row space and put the new row in the space created at the correct place. If there's not room, split, and do the b+ tree thing. this will take some effort to figure out how to do.
    
   
   
    if(!fsm.has_root()){
    fsm.get_fsm(file);
    
    }
    
    
    //THIS IS BASICALLY JUST THE B+ TREE INSERT IMPLEMENTATION, SO JUST REPLACE THIS WITH B+ TREE INSERT WHEN ITS DONE
    uint16_t key_of_interest{};
    uint32_t new_page_offset{};
    uint32_t new_low_p{};
    
    if(fsm.has_space(info.rel.page_id)==1){
        
        S empty;
        
        for(size_t i = num_rows-2;i >= info.index;i--){
            
            
            info.rel.rows[i+1] = info.rel.rows[i];
            info.rel.rows[i] = empty;
            if(i == 0)
            break;
        }
        
        
        info.rel.rows[info.index] = row;
        
        fsm.set_space(info.rel.page_id,1);
        if(info.rel.rows[num_rows-1].check != 0){
        fsm.set_space(info.rel.page_id,2);
        }
        
         //write back
        
        
        
       
        fs.seekp(info.rel.page_id*4096);
        
        fs.write(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
        
       fsm.flush_fsm(0);
       
    //    
        info.offsets.clear();
   
    
        return;
    }else if(fsm.has_space(info.rel.page_id) != 1 && info.rel.page_id != 0){
         //step 1: split leaf, get positon of new leaf.
        if(info.offsets.size()>=1){
        T half;
        half.page_id = fsm.page();
        
       
        new_page_offset = (half.page_id) * 4096;
    
        S empty;
        for(size_t i = num_rows/2; i<num_rows;i++){
            half.rows[i-(num_rows/2)]=info.rel.rows[i];
            info.rel.rows[i] = empty;
            
        }
        
        //make room and insert new row into proper leaf and get upper median key to send to parent node.
       
        if(info.index < num_rows/2){
            
            key_of_interest = calc_name(info.rel.rows[(num_rows/2)-1].index);
            
            for(size_t i = num_rows/2; i > info.index;i--){
                info.rel.rows[i] = info.rel.rows[i-1];
            };
            info.rel.rows[info.index] = row;
            
        }else if(info.index > num_rows/2){
            
            key_of_interest = calc_name(info.rel.rows[0].index);
            
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
        half.bottom_p = info.rel.bottom_p;
        info.rel.bottom_p = half.page_id*4096;
        fsm.set_space(half.page_id,1);
        fsm.set_space(info.rel.page_id,1);
        fs.seekp(info.rel.page_id * 4096);
        fs.write(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
        
        fs.seekp(new_page_offset);
        fs.write(reinterpret_cast<char*>(&half),sizeof(half));
        rel.num_pages++;
        rel.num_rows = (half.page_id * num_rows)*.66;
        
        }
        
    };
    // step 2: send new KOI/position of new to parent node.
    Key_Pointer k_p{key_of_interest,new_page_offset};
  if(info.offsets.size() >= 1){
    for(size_t i = info.offsets.size()-1; i >= 0; i--){
        //get parent node into memory
        
        if(fsm.has_space(info.root.page_id)==1){
            
            // step 3: if parent has room, insert at appropriate location. 
            
           
            if(info.index_root >= 4096){
            // step 3: if parent has room, insert at appropriate location. 
            
            for(size_t i = 0; i < 511;i++){
                if(info.root.arr[i].key == key){
                info.index_root = i;
                break;
                } else if(i ==0 && key < info.root.arr[i].key){
                info.index_root = i;
                break;

                } else if(info.root.arr[i].key > key && info.root.arr[i-1].key < key){
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
            info.root.arr[info.index_root] = k_p;
            if(info.root.arr[510].key != 0){
            fsm.set_space(info.root.page_id,2);
            }
            fs.seekp(info.root.page_id*4096);
            fs.write(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            
            fsm.flush_fsm(0);
            info.offsets.clear();
            info.index_root = 0;
            return;
        }else if(fsm.has_space(info.root.page_id)!=1 && i != 0){
            //If parent does not have room, split parent and get location of new parent.

            Syst_Root half_root;
            half_root.page_id = fsm.page();
            uint32_t offset_new_index = half_root.page_id*4096;
            uint16_t temp_koi{};
            

            //split
            Key_Pointer empty;
            if(info.index_root > 256){
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
            temp_koi = info.root.arr[255].key;
            half_root.bottom_p = info.root.arr[255].pointer;
            info.root.arr[255]=empty;
            for(size_t i = 256;i < 511;i++){
            half_root.arr[i-256] = info.root.arr[i];
            
            
            info.root.arr[i]=empty;
            }

            for(size_t i =256; i > info.index;i--){
                info.root.arr[i]=info.root.arr[i-1];
            }
            info.root.arr[info.index_root] = k_p;
        }else{
            temp_koi = key;
            
            half_root.bottom_p = k_p.pointer;
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
            k_p.key = temp_koi;
            k_p.pointer = offset_new_index;
            half_root.next_index = info.root.next_index;
            
            fsm.set_space(info.root.page_id,1);
            fsm.set_space(half_root.page_id,1);
            fs.seekp(info.root.page_id*4096);
            fs.write(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            fs.seekp(half_root.page_id*4096);
            fs.write(reinterpret_cast<char*>(&half_root),sizeof(half_root));
            fs.seekg(info.offsets.at(i-1));
            fs.read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            info.index_root = 4097;
            info.offsets.clear();
            
        }else if(fsm.has_space(info.root.page_id)!=1 && i == 0){
            Key_Pointer empty;
            Syst_Root half_root;
            
            half_root.page_id = fsm.page();
        //split current info.root
        //if i > 255, the koi goes to i=256 else, i = 255
        

        
        
        fsm.set_space(half_root.page_id,1);

        info.root.page_id = fsm.page();
        fsm.set_space(info.root.page_id,1);
        //get new info.root page and send koi and location of new "children" to new info.root for l & r pointers
        Syst_Root new_root;
        uint16_t temp_koi{};
        uint32_t temp_p{};



        if(info.index_root > 256){
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
            temp_koi = info.root.arr[255].key;
            half_root.bottom_p = info.root.arr[255].pointer;
            info.root.arr[255]=empty;
            for(size_t i = 256;i < 511;i++){
            half_root.arr[i-256] = info.root.arr[i];
            
            
            info.root.arr[i]=empty;
            }
            for(size_t i =256; i > info.index;i--){
                info.root.arr[i]=info.root.arr[i-1];
            }
            info.root.arr[info.index_root] = k_p;
        }else{
            temp_koi = key;
            
            half_root.bottom_p = k_p.pointer;
            for(size_t i = 257;i < 511;i++){
            half_root.arr[i-257] = info.root.arr[i];
            
            
            info.root.arr[i]=empty;
        }
            for(size_t i= 256; i > info.index_root - 256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[info.index_root] = k_p;
            };
            
            k_p.key = temp_koi;
            //switch the current 0 index page and the info.root page  so the info.root is always at index 0
            k_p.pointer = half_root.page_id * 4096;
            new_root.page_id = 0;
            new_root.bottom_p = info.root.page_id * 4096;
            // info.root.next_index = 0;
            half_root.next_index = info.root.next_index;
            new_root.next_index = 1;
            new_root.arr[0]=k_p;
            fsm.set_space(0,1);
            fs.seekp(0);
            fs.write(reinterpret_cast<char*>(&new_root),sizeof(new_root));
            fs.seekp((half_root.page_id)*4096);
            fs.write(reinterpret_cast<char*>(&half_root),sizeof(half_root));
            fs.seekg((info.root.page_id)*4096);
            fs.write(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            fsm.flush_fsm(0);
        
            info.offsets.clear();
            return;
        }; 
        // step 5: repeat until opening in index or at top level (root)
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
            half.rows[0]=row;
        }
        //get new root page and send koi and location of new "children" to new root for l & r pointers
        
        
        
        
        new_root.arr[0] = {key_of_interest,8192};
        new_root.next_index=0;
        info.rel.page_id = 1;
        half.page_id = 2;
        info.rel.bottom_p = half.page_id*4096;
        
            fsm.set_space(0,1);
            fsm.set_space(1,1);
            fsm.set_space(2,1);
            fs.seekp(0);
            fs.write(reinterpret_cast<char*>(&new_root),sizeof(new_root));
            fs.seekp((info.rel.page_id)*4096);
            fs.write(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
            fs.seekp((half.page_id)*4096);
            fs.write(reinterpret_cast<char*>(&half),sizeof(half));
        fs.close();
        info.index = 0;
        info.offsets.clear();
        height = 1;
        rel.num_pages++;
        fsm.flush_fsm(0);
        
  };
  
// step 6: if need to split root, get new root page, send koi and locations of children to new root. save location of new root in specialized file with root locations of each index.
    rel.num_rows++;
    
};

template<typename T,typename S>
void B_Tree<T,S>::search_range_catalog(uint16_t key,uint16_t key_last,uint16_t num_rows){
    rows.clear();
    uint16_t index_last{num_rows};
    search_catalog(key,num_rows);
    if(height){
    //if height 
    std::fstream fs;
    //get first index
    
    
    if(key > key_last)
    return;
    bool found = false;
    while(!found){
    for(size_t i = info.index; i<num_rows;i++){
        
        if(calc_name(info.rel.rows[i+1].index) > key_last){
            index_last = i;
            break;
        }
    };
    if(index_last < num_rows){
        for(size_t i = info.index; i <= index_last;i++){
            rows.push_back(info.rel.rows[i]);
        }
        found = true;
    }else{
        for(size_t i = info.index;i<num_rows;i++){
        rows.push_back(info.rel.rows[i]);
        if(info.rel.rows[i+1].check == 0)
        break;
        }
        
        fs.seekg(info.rel.bottom_p);
        fs.read(reinterpret_cast<char*>(&info.rel),sizeof(info.rel));
        info.index = 0;
    };
    }
    //if the insert will not fit on that page 
    //get the next leaf page
    //see if it will fit on that page and keep all pages in memory
    //return index of first, page of first, index of last, page of last, everything you need
    }else{
        //if no height:
        for(size_t i = info.index;i<num_rows;i++){
            if(calc_name(info.rel.rows[i+1].index) > key_last){
            rows.push_back(info.rel.rows[i]);
            index_last = i;
            return;
            }else if(calc_name(info.rel.rows[i].index)!=0)
            rows.push_back(info.rel.rows[i]);
        }
        

    }
    
    return;
}

