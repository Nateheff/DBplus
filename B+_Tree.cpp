#include "B+_Tree.h"



void Bp_Tree::search(uint32_t key,uint16_t num_rows, uint16_t row_size){


    std::fstream fs;

   
    fs.open(info.relation.rel_file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);

    uint32_t offset{};
    
    if(info.ind->ind_height > 0){
        
        fs.seekg(info.ind->ind_start);
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
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
            
            break;
            

        } else if(i ==0 && key < info.root.arr[i].key){
            info.index_root = i;
            offset = info.root.bottom_p;
            
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
            
            break;

        } else if(info.root.arr[i].key > key && info.root.arr[i-1].key < key){
            info.index_root = i;
            offset = info.root.arr[i-1].pointer;
            
            
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
     
            break;
        }else if(info.root.arr[i].key < key && info.root.arr[i+1].pointer == 0){
            info.index_root = i+1;
            offset = info.root.arr[i].pointer;
            
            
            fs.seekg(offset);
            
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
            
            
            break;
        }
        
    }
   
    
    }else{
        
        fs.seekg(info.ind->ind_start);
        fs.read(reinterpret_cast<char*>(&info.leaf),4096);
        info.leaf.page_id = 0;

    };
   
    for(size_t i =0;i<num_rows;i++){
            uint32_t index{};
            memcpy(&index,&info.leaf.data[i*row_size],4);
            
            if(key <= index || (i == num_rows-1 && key > index)||index == 0){
               
                info.index = i;
                
                return;
        
        }
    }
    
};

void Bp_Tree::search(float key,uint16_t num_rows, uint16_t row_size){
 
 
    std::fstream fs;

    fs.open(info.relation.rel_file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    
    
    uint32_t offset{};
    
    if(info.ind->ind_height > 0){
        
        fs.seekg(info.ind->ind_start);
        fs.read(reinterpret_cast<char*>(&root_f),sizeof(root_f));
        
        uint16_t index = root_f.next_index;
        info.offsets.push_back(0);

    
    while(index == 1){
       
    for(size_t i = 0; i < 511;i++){
        if(info.root.arr[0].key > key){
            offset = root_f.bottom_p;
            info.offsets.push_back(offset);
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&root_f),sizeof(root_f));
            
            index = root_f.next_index;
            
            break;
        } else if(root_f.arr[i].key > key && root_f.arr[i-1].key < key){
            offset = root_f.arr[i].pointer;
            info.offsets.push_back(offset);
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&root_f),sizeof(root_f));
            
            index = root_f.next_index;
            
            break;
        } else if(root_f.arr[i].key == key){
            
            info.offsets.push_back(root_f.arr[i].pointer);
            offset = root_f.arr[i].pointer;
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&root_f),sizeof(root_f));
            
            index = root_f.next_index;
                     
            break;

        } else if(root_f.arr[i].key < key && root_f.arr[i+1].pointer == 0){
            info.offsets.push_back(root_f.arr[i].pointer);

            offset = root_f.arr[i].pointer;
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&root_f),sizeof(root_f));
            
            index = root_f.next_index;
            
            break;
        }
       
    }
    };

    for(size_t i = 0; i < 511;i++){
        if(root_f.arr[i].key == key){
            info.index_root = i;
            offset = root_f.arr[i].pointer;
            
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
            
            break;
            

        } else if(i ==0 && key < root_f.arr[i].key){
            info.index_root = i;
            offset = root_f.bottom_p;
            
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
            
            break;

        } else if(root_f.arr[i].key > key && root_f.arr[i-1].key < key){
            info.index_root = i;
            offset = root_f.arr[i-1].pointer;
            
            
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
        
            break;
        }else if(root_f.arr[i].key < key && root_f.arr[i+1].pointer == 0){
            info.index_root = i+1;
            offset = root_f.arr[i].pointer;
            
            
            fs.seekg(offset);
            
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
            
            
            break;
        }
        
    }

    
    }else{
        
        fs.seekg(info.ind->ind_start);
        fs.read(reinterpret_cast<char*>(&info.leaf),4096);
        info.leaf.page_id = 0;

    };
    
    for(size_t i =0;i<num_rows;i++){
            float index{};
            memcpy(&index,&info.leaf.data[i*row_size],4);
            if(key <= index || (i == num_rows-1 && key > index)||index == 0){
                info.index = i;
                
                return;
        
        }
    }
    
};


void Bp_Tree::insert(uint32_t key, uint16_t num_rows,uint16_t row_size, Run* obj, Row row){
    
//search normally
    
    
    info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    info.ind = &obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
    search(key,num_rows,row_size);
    std::fstream fs;
    fs.open(info.relation.rel_file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);

    
//once you have the page of where the row with the key would fit, see if there's space via the fsm and if there is, move all rows "greater" than it up 1 row space and put the new row in the space created at the correct place. If there's not room, split, and do the b+ tree thing. this will take some effort to figure out how to do.
    
   
    if(!fsm.has_root()){
    fsm.get_fsm(obj->database.substr(0,obj->database.size()-3));
    }
    
    //THIS IS BASICALLY JUST THE B+ TREE INSERT IMPLEMENTATION, SO JUST REPLACE THIS WITH B+ TREE INSERT WHEN ITS DONE
    uint32_t key_of_interest{};
    uint32_t new_page_offset{};
    uint32_t new_low_p{};
    
    if(fsm.has_space(info.leaf.page_id)==1){
        
        std::vector<char>empty{};
        empty.resize(row_size);

        uint32_t index{};
        memcpy(&index,&info.leaf.data[info.index*row_size],4);
        if(index != key){
        for(size_t i = num_rows-2;i >= info.index;i--){
            memcpy(&info.leaf.data[(i+1)*row_size],&info.leaf.data[i*row_size],row_size);
            memcpy(&info.leaf.data[i*row_size],empty.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
            
            if(i == 0)
            break;
        }
        }

        memcpy(&info.leaf.data[info.index*row_size],row.data.data(),row_size);
        fsm.set_space(info.leaf.page_id,1);
        uint32_t index_last{};
        memcpy(&index_last,&info.leaf.data[(num_rows-1)*row_size],4);
        if(index_last != 0){
        fsm.set_space(info.leaf.page_id,2);
        }
      
        
        
       
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        
        fs.write(reinterpret_cast<char*>(&info.leaf),4096);
       fsm.flush_fsm(0);
       fs.close();
    //    
        info.offsets.clear();
   
        return;
    }else if(fsm.has_space(info.leaf.page_id) != 1 && info.leaf.page_id != 0){
         //step 1: split info.leaf, get positon of new info.leaf.
        if(info.offsets.size()>=1){
        Curr_Node half;
        half.page_id = fsm.page();
        
       
        new_page_offset = (half.page_id) * 4096+info.ind->ind_start;
        uint32_t index{};
        std::vector<char>empty{};
        empty.resize(row_size);

        for(size_t i = num_rows/2; i<num_rows;i++){
            memcpy(&half.data[(i-(num_rows/2))*row_size],&info.leaf.data[i*row_size],row_size);
            memcpy(&info.leaf.data[i*row_size],empty.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
            
        }
       
        //make room and insert new row into proper info.leaf and get upper median key to send to parent node.
       
        if(info.index < num_rows/2){
            
            memcpy(&key_of_interest,&info.leaf.data[((num_rows/2)-1)*row_size],4);
            
            
        memcpy(&index,&info.leaf.data[info.index*row_size],4);
        if(index != key){
            for(size_t i = num_rows/2; i > info.index;i--){
                memcpy(&info.leaf.data[i*row_size],&info.leaf.data[(i-1)*row_size],row_size);
            };
        }
            memcpy(&info.leaf.data[info.index*row_size],row.data.data(),row_size);
            
        }else if(info.index > num_rows/2){
            
            memcpy(&key_of_interest,half.data,4);
            
            memcpy(&index,&half.data[(info.index-(num_rows/2))*row_size],4);
        if(index != key){
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                memcpy(&half.data[i*row_size],&half.data[(i-1)*row_size],row_size);
            }
        }
            memcpy(&half.data[(info.index -(num_rows/2))*row_size],row.data.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
        }else{
            key_of_interest = key;
            memcpy(&index,&half.data[(info.index-(num_rows/2))*row_size],4);
        if(index != key){
            for(size_t i = num_rows/2;i > 0;i--){
                memcpy(&half.data[i*row_size],&half.data[(i-1)*row_size],row_size);
            }
        }
            memcpy(&half.data[0],row.data.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
        };
        half.bottom_p = info.leaf.bottom_p;
        info.leaf.bottom_p = half.page_id*4096+info.ind->ind_start;
        fsm.set_space(half.page_id,1);
        fsm.set_space(info.leaf.page_id,1);
        fs.seekp(info.leaf.page_id * 4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),4096);
        
        fs.seekp(new_page_offset);
        fs.write(reinterpret_cast<char*>(&half),sizeof(half));
        info.relation.num_pages++;
        info.relation.num_rows = (half.page_id * num_rows)*.66;
        
        }
        
    };
    // step 2: send new KOI/position of new to parent node.
    Key_Pointer k_p{key_of_interest,new_page_offset};

  if(info.offsets.size() >= 1){
    for(size_t i = info.offsets.size()-1; i >= 0; i--){
        //get parent node into memory
       
        if(fsm.has_space(info.root.page_id)==1){
           
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
            fs.seekp(info.root.page_id*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&info.root),sizeof(info.root));
          
            fsm.flush_fsm(0);
            info.offsets.clear();
            info.index_root = 0;
            return;
        }else if(fsm.has_space(info.root.page_id)!=1 && i != 0){
            //If parent does not have room, split parent and get location of new parent.

            Syst_Root half_root;
            half_root.page_id = fsm.page();
            uint32_t offset_new_index = half_root.page_id*4096+info.ind->ind_start;
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
            fs.seekp(info.root.page_id*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            fs.seekp(half_root.page_id*4096+info.ind->ind_start);
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
            k_p.pointer = half_root.page_id * 4096+info.ind->ind_start;
            new_root.page_id = 0;
            new_root.bottom_p = info.root.page_id * 4096+info.ind->ind_start;

            half_root.next_index = info.root.next_index;
            new_root.next_index = 1;
            new_root.arr[0]=k_p;
            fsm.set_space(0,1);
            fs.seekp(info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&new_root),sizeof(new_root));
            fs.seekp((half_root.page_id)*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&half_root),sizeof(half_root));
            fs.seekg((info.root.page_id)*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            fsm.flush_fsm(0);
        
            info.offsets.clear();
            return;
        }; 
        // step 5: repeat until opening in index or at top level (root)
        std::cout<<"nowhere"<<std::endl;
    };
  }else{
    Key_Pointer empty;
            Syst_Root new_root;
            Curr_Node half;
            
            new_root.page_id = 0;
            new_root.bottom_p = 4096+info.ind->ind_start;
            Row empty_row;
            std::vector<char>em{};
            em.resize(row_size);
            for(size_t i = num_rows/2;i < num_rows;i++){
                memcpy(&half.data[(i-(num_rows/2))*row_size],&info.leaf.data[i*row_size],row_size);
                memcpy(&info.leaf.data[i*row_size],em.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
            
            }
            
            if(info.index < num_rows/2){
                
                memcpy(&key_of_interest,&info.leaf.data[((num_rows/2)-1)*row_size],4);
               
            for(size_t i = num_rows/2; i > info.index;i--){
                memcpy(&info.leaf.data[i*row_size],&info.leaf.data[(i-1)*row_size],row_size);
            };
            memcpy(&info.leaf.data[info.index*row_size],row.data.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
            }else if(info.index > num_rows/2){
               
            memcpy(&key_of_interest, &half.data[0],4);//CHECK////////////////////////////////////////////////////////////////////////////
            
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                memcpy(&half.data[i*row_size],&half.data[(i-1)*row_size],row_size);
            }
            memcpy(&half.data[(info.index -(num_rows/2))*row_size],row.data.data(),row_size);//FIXX/////////////////////////////////////////////////////////////////////
        }else
            key_of_interest = key;
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                memcpy(&half.data[i*row_size],&half.data[(i-1)*row_size],row_size);

            memcpy(half.data,row.data.data(),row_size);
        }
        //get new root page and send koi and location of new "children" to new root for l & r pointers
        
        
        
        
        new_root.arr[0] = {key_of_interest,8192+info.ind->ind_start};
        new_root.next_index=0;
        info.leaf.page_id = 1;
        half.page_id = 2;
        info.leaf.bottom_p = half.page_id*4096+info.ind->ind_start;
        half.bottom_p = 0;
        
            fsm.set_space(0,1);
            fsm.set_space(1,1);
            fsm.set_space(2,1);
            fs.seekp(info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&new_root),sizeof(new_root));
            fs.seekp((info.leaf.page_id)*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&info.leaf),4096);
            fs.seekp((half.page_id)*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&half),4096);
        fs.close();
        info.index = 0;
        info.offsets.clear();
        info.ind->ind_height = 1;
        obj->tree_ind.dirty = true;
        obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].num_pages++;
        obj->tree_rel.dirty = true;
        fsm.flush_fsm(0);
        obj->flush();
  };
  
// step 6: if need to split root, get new root page, send koi and locations of children to new root. save location of new root in specialized file with root locations of each index.
    obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].num_rows++;
    

};

void Bp_Tree::insert(float key, uint16_t num_rows,uint16_t row_size, Run* obj, Row row){
    
//search normally
    
    
    info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    info.ind = &obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
    search(key,num_rows,row_size);
    std::fstream fs;
    fs.open(info.relation.rel_file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
   
    if(!fsm.has_root()){
    fsm.get_fsm(obj->database.substr(0,obj->database.size()-3));
    }

    //THIS IS BASICALLY JUST THE B+ TREE INSERT IMPLEMENTATION, SO JUST REPLACE THIS WITH B+ TREE INSERT WHEN ITS DONE
    float key_of_interest{};
    uint32_t new_page_offset{};
    uint32_t new_low_p{};
    
    if(fsm.has_space(info.leaf.page_id)==1){
        
        std::vector<char>empty{};
        empty.resize(row_size);
        float index_t{};

        float index{};
        memcpy(&index,&info.leaf.data[info.index*row_size],4);
        if(index != key){
        for(size_t i = num_rows-2;i >= info.index;i--){
            memcpy(&info.leaf.data[(i+1)*row_size],&info.leaf.data[i*row_size],row_size);
            memcpy(&info.leaf.data[i*row_size],empty.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
            
            if(i == 0)
            break;
        }
        };
     
        memcpy(&info.leaf.data[info.index*row_size],row.data.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
      
        fsm.set_space(info.leaf.page_id,1);
        float index_last{};
        memcpy(&index_last,&info.leaf.data[(num_rows-1)*row_size],4);
        if(index_last != 0){
        fsm.set_space(info.leaf.page_id,2);
        }
       
        
        
       
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        
        fs.write(reinterpret_cast<char*>(&info.leaf),4096);
       fsm.flush_fsm(0);
       fs.close();
    //    
        info.offsets.clear();
   
        return;
    }else if(fsm.has_space(info.leaf.page_id) != 1 && info.leaf.page_id != 0){
         //step 1: split info.leaf, get positon of new info.leaf.
        if(info.offsets.size()>=1){
        Curr_Node half;
        half.page_id = fsm.page();

        new_page_offset = (half.page_id) * 4096+info.ind->ind_start;
    
        std::vector<char>empty{};
        empty.resize(row_size);
        float index{};

        for(size_t i = num_rows/2; i<num_rows;i++){
            memcpy(&half.data[(i-(num_rows/2))*row_size],&info.leaf.data[i*row_size],row_size);
            memcpy(&info.leaf.data[i*row_size],empty.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
            
        }

        //make room and insert new row into proper info.leaf and get upper median key to send to parent node.
       
        if(info.index < num_rows/2){
            
            memcpy(&key_of_interest,&info.leaf.data[((num_rows/2)-1)*row_size],4);
            
            
        memcpy(&index,&info.leaf.data[info.index*row_size],4);
        if(index != key){
            for(size_t i = num_rows/2; i > info.index;i--){
                memcpy(&info.leaf.data[i*row_size],&info.leaf.data[(i-1)*row_size],row_size);
            };
        }
            memcpy(&info.leaf.data[info.index*row_size],row.data.data(),row_size);
            
        }else if(info.index > num_rows/2){
            
            memcpy(&key_of_interest,half.data,4);
            
            memcpy(&index,&half.data[(info.index-(num_rows/2))*row_size],4);
        if(index != key){
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                memcpy(&half.data[i*row_size],&half.data[(i-1)*row_size],row_size);
            }
        }
            memcpy(&half.data[(info.index -(num_rows/2))*row_size],row.data.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
        }else{
            key_of_interest = key;
            memcpy(&index,&half.data[(info.index-(num_rows/2))*row_size],4);
        if(index != key){
            for(size_t i = num_rows/2;i > 0;i--){
                memcpy(&half.data[i*row_size],&half.data[(i-1)*row_size],row_size);
            }
        }
            memcpy(&half.data[0],row.data.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
        };
        half.bottom_p = info.leaf.bottom_p;
        info.leaf.bottom_p = half.page_id*4096+info.ind->ind_start;
        fsm.set_space(half.page_id,1);
        fsm.set_space(info.leaf.page_id,1);
        fs.seekp(info.leaf.page_id * 4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),4096);
        
        fs.seekp(new_page_offset);
        fs.write(reinterpret_cast<char*>(&half),sizeof(half));
        info.relation.num_pages++;
        info.relation.num_rows = (half.page_id * num_rows)*.66;
        
        }
        
    };
    // step 2: send new KOI/position of new to parent node.
    Key_Pointer_f k_p{key_of_interest,new_page_offset};
    // if(test > 8384)
  if(info.offsets.size() >= 1){
    for(size_t i = info.offsets.size()-1; i >= 0; i--){
        //get parent node into memory

        if(fsm.has_space(root_f.page_id)==1){
            // step 3: if parent has room, insert at appropriate location. 

            if(info.index_root >= 4096){
            // step 3: if parent has room, insert at appropriate location. 
            
            for(size_t i = 0; i < 511;i++){
                if(root_f.arr[i].key == key){
                info.index_root = i;
                break;
                } else if(i ==0 && key < root_f.arr[i].key){

                info.index_root = i;
                break;

                } else if(root_f.arr[i].key > key && root_f.arr[i-1].key < key){
                info.index_root = i;
                break;
                }else if(root_f.arr[i].key < key && root_f.arr[i+1].pointer == 0){
                info.index_root = i+1;
            
                break;
                }
            }
            };
            for(size_t i = 510;i > info.index_root;i--)
            root_f.arr[i] = root_f.arr[i-1];
            root_f.arr[info.index_root] = k_p;
            if(root_f.arr[510].key != 0){
            fsm.set_space(root_f.page_id,2);
            }
            fs.seekp(root_f.page_id*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&root_f),sizeof(root_f));
         
            fsm.flush_fsm(0);
            info.offsets.clear();
            info.index_root = 0;
            return;
        }else if(fsm.has_space(root_f.page_id)!=1 && i != 0){
            //If parent does not have room, split parent and get location of new parent.

            Syst_Root_f half_root;
            half_root.page_id = fsm.page();
            uint32_t offset_new_index = half_root.page_id*4096+info.ind->ind_start;
            float temp_koi{};
            

            //split
            Key_Pointer_f empty;
            if(info.index_root > 256){
            temp_koi = root_f.arr[256].key;
            half_root.bottom_p = root_f.arr[256].pointer;
            root_f.arr[256]=empty;
            for(size_t i = 257;i < 511;i++){
            half_root.arr[i-257] = root_f.arr[i];
            
            
            root_f.arr[i]=empty;
        }
            
             
            for(size_t i= 256; i > info.index_root - 256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[info.index_root] = k_p;
        }else if(info.index_root< 256){
            temp_koi = root_f.arr[255].key;
            half_root.bottom_p = root_f.arr[255].pointer;
            root_f.arr[255]=empty;
            for(size_t i = 256;i < 511;i++){
            half_root.arr[i-256] = root_f.arr[i];
            
            
            root_f.arr[i]=empty;
            }

            for(size_t i =256; i > info.index;i--){
                root_f.arr[i]=root_f.arr[i-1];
            }
            root_f.arr[info.index_root] = k_p;
        }else{
            temp_koi = key;
            
            half_root.bottom_p = k_p.pointer;
            for(size_t i = 257;i < 511;i++){
            half_root.arr[i-257] = root_f.arr[i];
            
            
            root_f.arr[i]=empty;
        }
            for(size_t i= 256; i > info.index_root - 256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[info.index_root] = k_p;
            };
            // step 4: send new KOI/position of new index node to the parent node and if room, insert at appropriate location.
            k_p.key = temp_koi;
            k_p.pointer = offset_new_index;
            half_root.next_index = root_f.next_index;

            fsm.set_space(root_f.page_id,1);
            fsm.set_space(half_root.page_id,1);
            fs.seekp(root_f.page_id*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&root_f),sizeof(root_f));
            fs.seekp(half_root.page_id*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&half_root),sizeof(half_root));
            fs.seekg(info.offsets.at(i-1));
            fs.read(reinterpret_cast<char*>(&root_f),sizeof(root_f));
            info.index_root = 4097;
            info.offsets.clear();
            
        }else if(fsm.has_space(root_f.page_id)!=1 && i == 0){
            Key_Pointer_f empty;
            Syst_Root_f half_root;
            
            half_root.page_id = fsm.page();

        //split current root_f
        //if i > 255, the koi goes to i=256 else, i = 255
        

        
        
        fsm.set_space(half_root.page_id,1);

        root_f.page_id = fsm.page();
        fsm.set_space(root_f.page_id,1);
        //get new root_f page and send koi and location of new "children" to new root_f for l & r pointers
        Syst_Root_f new_root;
        float temp_koi{};
        uint32_t temp_p{};



        if(info.index_root > 256){
            temp_koi = root_f.arr[256].key;
            half_root.bottom_p = root_f.arr[256].pointer;
            root_f.arr[256]=empty;
            for(size_t i = 257;i < 511;i++){
            half_root.arr[i-257] = root_f.arr[i];
            
            
            root_f.arr[i]=empty;
        }
            
             
            for(size_t i= 256; i > info.index_root - 256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[info.index_root] = k_p;
        }else if(info.index_root< 256){
            temp_koi = root_f.arr[255].key;
            half_root.bottom_p = root_f.arr[255].pointer;
            root_f.arr[255]=empty;
            for(size_t i = 256;i < 511;i++){
            half_root.arr[i-256] = root_f.arr[i];
            
            
            root_f.arr[i]=empty;
            }
            for(size_t i =256; i > info.index;i--){
                root_f.arr[i]=root_f.arr[i-1];
            }
            root_f.arr[info.index_root] = k_p;
        }else{
            temp_koi = key;
            
            half_root.bottom_p = k_p.pointer;
            for(size_t i = 257;i < 511;i++){
            half_root.arr[i-257] = root_f.arr[i];
            
            
            root_f.arr[i]=empty;
        }
            for(size_t i= 256; i > info.index_root - 256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[info.index_root] = k_p;
            };
            
            k_p.key = temp_koi;
            //switch the current 0 index page and the root_f page  so the root_f is always at index 0
            k_p.pointer = half_root.page_id * 4096+info.ind->ind_start;
            new_root.page_id = 0;
            new_root.bottom_p = root_f.page_id * 4096+info.ind->ind_start;
            half_root.next_index = root_f.next_index;
            new_root.next_index = 1;
            new_root.arr[0]=k_p;
            fsm.set_space(0,1);
            fs.seekp(info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&new_root),sizeof(new_root));
            fs.seekp((half_root.page_id)*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&half_root),sizeof(half_root));
            fs.seekg((root_f.page_id)*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&root_f),sizeof(root_f));
            fsm.flush_fsm(0);
        
            info.offsets.clear();
            return;
        }; 
        // step 5: repeat until opening in index or at top level (root)
        std::cout<<"nowhere"<<std::endl;
    };
  }else{
    Key_Pointer_f empty;
            Syst_Root_f new_root;
            Curr_Node half;
            
            new_root.page_id = 0;
            new_root.bottom_p = 4096+info.ind->ind_start;
            Row empty_row;
            std::vector<char>em{};
            em.resize(row_size);
            for(size_t i = num_rows/2;i < num_rows;i++){
                memcpy(&half.data[(i-(num_rows/2))*row_size],&info.leaf.data[i*row_size],row_size);
                memcpy(&info.leaf.data[i*row_size],em.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
            
            }
            
            if(info.index < num_rows/2){
                
                memcpy(&key_of_interest,&info.leaf.data[((num_rows/2)-1)*row_size],4);
               
            for(size_t i = num_rows/2; i > info.index;i--){
                memcpy(&info.leaf.data[i*row_size],&info.leaf.data[(i-1)*row_size],row_size);
            };
            memcpy(&info.leaf.data[info.index*row_size],row.data.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
            }else if(info.index > num_rows/2){
               
            memcpy(&key_of_interest, &half.data[0],4);//CHECK////////////////////////////////////////////////////////////////////////////
            
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                memcpy(&half.data[i*row_size],&half.data[(i-1)*row_size],row_size);
            }
            memcpy(&half.data[(info.index -(num_rows/2))*row_size],row.data.data(),row_size);//FIXX/////////////////////////////////////////////////////////////////////
        }else
            key_of_interest = key;
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                memcpy(&half.data[i*row_size],&half.data[(i-1)*row_size],row_size);

            memcpy(half.data,row.data.data(),row_size);
        }
        //get new root page and send koi and location of new "children" to new root for l & r pointers
        
        
        
        
        new_root.arr[0] = {key_of_interest,8192+info.ind->ind_start};
        new_root.next_index=0;
        info.leaf.page_id = 1;
        half.page_id = 2;
        half.bottom_p = 0;
        info.leaf.bottom_p = half.page_id*4096+info.ind->ind_start;
            //switch the current 0 index page and the root page  so the root is always at index 0

            fsm.set_space(0,1);
            fsm.set_space(1,1);
            fsm.set_space(2,1);
            fs.seekp(info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&new_root),sizeof(new_root));
            fs.seekp((info.leaf.page_id)*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&info.leaf),4096);
            fs.seekp((half.page_id)*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&half),4096);
        fs.close();
        info.index = 0;
        info.offsets.clear();
        info.ind->ind_height = 1;
        obj->tree_ind.dirty = true;
        obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].num_pages++;
        obj->tree_rel.dirty = true;
        fsm.flush_fsm(0);
        obj->flush();
  };
  
// step 6: if need to split root, get new root page, send koi and locations of children to new root. save location of new root in specialized file with root locations of each index.
    obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].num_rows++;
    

};

void Bp_Tree::search_range(uint32_t key_first,uint32_t key_last,uint16_t num_rows){
    info.rows.clear();
    uint16_t index_last{num_rows};
    search(key_first,num_rows,info.relation.row_size);

    if(info.ind->ind_height > 0){

    //if height 
    std::fstream fs;
    //get first index
    
    if(key_first > key_last)
    return;

    uint32_t index{};
    Row row{};
    bool found = false;
    row.data.resize(info.relation.row_size);
    
    for(size_t i = info.index; i<num_rows;i++){
        memcpy(&index,&info.leaf.data[i*info.relation.row_size],4);
        memcpy(row.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
        
        if(index >= key_last){
            if(index == key_last)
            info.rows.push_back(row);
            index_last = i;
            found = true;
            break;
        }
        if(index == 0){

            if(info.leaf.bottom_p == 0)
            found = true;

            index_last = i;
            break;
        }
        info.rows.push_back(row);
    }
    
    while(!found){
        
    fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
    fs.seekg(info.leaf.bottom_p);
    fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
    fs.close();
     for(size_t i = 0; i<num_rows;i++){
        memcpy(&index,&info.leaf.data[i*info.relation.row_size],4);
        memcpy(row.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
        if(index >= key_last){
            if(index == key_last)
            info.rows.push_back(row);
            info.index_last = i;
            found = true;
            break;
        }
        if(index == 0){

            if(info.leaf.bottom_p == 0)
            found = true;

            index_last = i;
            break;
        }
        info.rows.push_back(row);
     }

    }
    
    //if the insert will not fit on that page 
    //get the next leaf page
    //see if it will fit on that page and keep all pages in memory
    //return index of first, page of first, index of last, page of last, everything you need
    }else{
        //if no height:
        Row row{};
        row.data.resize(info.relation.row_size);
        for(size_t i = info.index;i<num_rows;i++){
            
            memcpy(row.data.data(),&info.leaf.data[(i)*info.relation.row_size],info.relation.row_size);
            memcpy(&row.index,row.data.data(),4);
            if(row.index >= key_last || row.index == 0){
            info.rows.push_back(row);
            index_last = i;
            return;
            }else if(row.index!=0)
            info.rows.push_back(row);
        }
        

    }
    
    return;
}

void Bp_Tree::search_range(float key_first,float key_last,uint16_t num_rows){
    info.rows.clear();
    uint16_t index_last{num_rows};
    search(key_first,num_rows,info.relation.row_size);
    if(info.ind->ind_height > 0){
    //if height 
    std::fstream fs;
    //get first index
    
    if(key_first > key_last)
    return;
    float index{};
    Row row{};
    row.data.resize(info.relation.row_size);
    bool found = false;
    for(size_t i = info.index; i<num_rows;i++){
        memcpy(&index,&info.leaf.data[i*info.relation.row_size],4);
        memcpy(row.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
        
        if(index >= key_last){
            if(index == key_last)
            info.rows.push_back(row);
            index_last = i;
            found = true;
            break;
        }
        if(index == 0.0){

            if(info.leaf.bottom_p == 0)
            found = true;

            index_last = i;
            break;
        }
        info.rows.push_back(row);
    }
    
    while(!found){
        
    fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
    fs.seekg(info.leaf.bottom_p);
    fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
    fs.close();
     for(size_t i = 0; i<num_rows;i++){
        memcpy(&index,&info.leaf.data[i*info.relation.row_size],4);
        memcpy(row.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
        if(index >= key_last){
            if(index==key_last)
            info.rows.push_back(row);
            info.index_last = i;
            found = true;
            break;
            
        }
        if(index == 0){

            if(info.leaf.bottom_p == 0)
            found = true;

            index_last = i;
            break;
        }
        info.rows.push_back(row);
     }

    }
    //if the insert will not fit on that page 
    //get the next leaf page
    //see if it will fit on that page and keep all pages in memory
    //return index of first, page of first, index of last, page of last, everything you need
    }else{
        //if no height:
        Row row{};
        float index{};
        row.data.resize(info.relation.row_size);
        for(size_t i = info.index;i<num_rows;i++){
            
            memcpy(row.data.data(),&info.leaf.data[(i)*info.relation.row_size],info.relation.row_size);
            memcpy(&index,row.data.data(),4);
            if(index >= key_last || index == 0){
            info.rows.push_back(row);
            index_last = i;
            return;
            }else if(row.index!=0)
            info.rows.push_back(row);
        }

    }
    
    return;
}

void Bp_Tree::delete_range(uint32_t key_first,uint32_t key_last,uint16_t num_rows,Row row)
{
    search(key_first,num_rows,info.relation.row_size);
    std::fstream fs;
    bool found{};
    uint32_t index{};
    uint32_t index_i{};
    Row row_empty{};

    

    row_empty.data.resize(info.relation.row_size);
    row.data.resize(info.relation.row_size);
    
    if(info.ind->ind_height > 0){

        for(size_t i = info.index; i < num_rows;i++){
            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);
            if(index_i != 0){
            memcpy(&info.leaf.data[i*info.relation.row_size],row.data.data(),info.relation.row_size);
            }
            if(index > key_last || index == 0.0){
                info.index_last = i;
                
                for(size_t j = info.index; j<num_rows-info.index_last-1;j++){
                memcpy(&index,&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],4);
                
                if(index == 0)
                break;

                memcpy(&info.leaf.data[j*info.relation.row_size],&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],info.relation.row_size);
                memcpy(&info.leaf.data[(j+i+1)*info.relation.row_size],row.data.data(),info.relation.row_size);

                }
                break;
            }
        }
        
        fsm.set_space(info.leaf.page_id,1);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        fs.close();
        while(!found){
        
        
            fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
            fs.seekg(info.leaf.bottom_p);
            fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
            fs.close();
            for(size_t i = 0; i< num_rows;i++){
                memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
                memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
                memcpy(&index_i,row_empty.data.data(),4);

                if(index_i != 0){
                memcpy(&info.leaf.data[i*info.relation.row_size],row.data.data(),info.relation.row_size);
                
                }

                if(index > key_last || (info.leaf.bottom_p == 0 && index==0)){
                    info.index_last = i;
                    found = true;
                    for(size_t j = info.index; j<num_rows-info.index_last-1;j++){
                        memcpy(&index,&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],4);
                
                        if(index == 0)
                        break;

                        memcpy(&info.leaf.data[j*info.relation.row_size],&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],info.relation.row_size);
                        memcpy(&info.leaf.data[(j+i+1)*info.relation.row_size],row.data.data(),info.relation.row_size);

                    }
                    break;
                } 
                if(index == 0){
                    info.index_last = i;
                    for(size_t j = info.index; j<num_rows-info.index_last-1;j++){
                        memcpy(&index,&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],4);

                        memcpy(&info.leaf.data[j*info.relation.row_size],&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],info.relation.row_size);
                        memcpy(&info.leaf.data[(j+i+1)*info.relation.row_size],row.data.data(),info.relation.row_size);

                    }
                    break;
                }
                

            }
            
            fsm.set_space(info.leaf.page_id,1);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        fs.close();
        }


        
       
    
    }else{
        
        for(size_t i = info.index; i < num_rows-1;i++){

            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);

            if(index_i != 0.0){
            memcpy(&info.leaf.data[i*info.relation.row_size],row.data.data(),info.relation.row_size);
            
            }
            if(index > key_last || index == 0.0){

                info.index_last = i;
                
                for(size_t j = info.index; j<num_rows-info.index_last-1;j++){
                memcpy(&index,&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],4);
                
                if(index == 0)
                break;

                memcpy(&info.leaf.data[j*info.relation.row_size],&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],info.relation.row_size);
                memcpy(&info.leaf.data[(j+i+1)*info.relation.row_size],row.data.data(),info.relation.row_size);

                }
                break;
            }
        }
        
        fsm.set_space(info.leaf.page_id,1);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        fs.close();
    }
    
    
};
void Bp_Tree::delete_range(float key_first,float key_last,uint16_t num_rows,Row row){
    search(key_first,num_rows,info.relation.row_size);
    std::fstream fs;
    bool found{};
    float index{};
    float index_i{};
    Row row_empty{};

    
    
    

    row_empty.data.resize(info.relation.row_size);
    row.data.resize(info.relation.row_size);
    
    if(info.ind->ind_height > 0){

        for(size_t i = info.index; i < num_rows;i++){
            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);
            if(index_i != 0){
            memcpy(&info.leaf.data[i*info.relation.row_size],row.data.data(),info.relation.row_size);
            }
            if(index > key_last || index == 0.0){
                info.index_last = i;
                
                for(size_t j = info.index; j<num_rows-info.index_last-1;j++){
                memcpy(&index,&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],4);
                
                if(index == 0)
                break;

                memcpy(&info.leaf.data[j*info.relation.row_size],&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],info.relation.row_size);
                memcpy(&info.leaf.data[(j+i+1)*info.relation.row_size],row.data.data(),info.relation.row_size);

                }
                break;
            }
        }
        
        fsm.set_space(info.leaf.page_id,1);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        fs.close();
        while(!found){
        
        

            fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
            fs.seekg(info.leaf.bottom_p);
            fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
            fs.close();
            for(size_t i = 0; i< num_rows;i++){
                memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
                memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
                memcpy(&index_i,row_empty.data.data(),4);
                if(index_i != 0){
                memcpy(&info.leaf.data[i*info.relation.row_size],row.data.data(),info.relation.row_size);
                
                }
                if(index > key_last || (info.leaf.bottom_p == 0 && index==0.0)){
                    info.index_last = i;
                    found = true;
                    for(size_t j = info.index; j<num_rows-info.index_last-1;j++){
                        memcpy(&index,&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],4);
                
                        

                        memcpy(&info.leaf.data[j*info.relation.row_size],&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],info.relation.row_size);
                        memcpy(&info.leaf.data[(j+i+1)*info.relation.row_size],row.data.data(),info.relation.row_size);

                    }
                    break;
                } 
                if(index == 0.0){
                    info.index_last = i;
                    for(size_t j = info.index; j<num_rows-info.index_last-1;j++){
                        memcpy(&index,&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],4);
                
                        

                        memcpy(&info.leaf.data[j*info.relation.row_size],&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],info.relation.row_size);
                        memcpy(&info.leaf.data[(j+i+1)*info.relation.row_size],row.data.data(),info.relation.row_size);

                    }
                    break;
                }
                

            }
           
        fsm.set_space(info.leaf.page_id,1); 
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        }


        
       
    
    }else{
        
        for(size_t i = info.index; i < num_rows-1;i++){

            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);

            if(index_i != 0.0){
            memcpy(&info.leaf.data[i*info.relation.row_size],row.data.data(),info.relation.row_size);
            
            }
            if(index > key_last || index == 0.0){

                info.index_last = i;
                
                for(size_t j = info.index; j<num_rows-info.index_last-1;j++){
                memcpy(&index,&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],4);
                
                if(index == 0)
                break;

                memcpy(&info.leaf.data[j*info.relation.row_size],&info.leaf.data[(j+info.index_last+1)*info.relation.row_size],info.relation.row_size);
                memcpy(&info.leaf.data[(j+i+1)*info.relation.row_size],row.data.data(),info.relation.row_size);

                }
                break;
            }
        }
        
        fsm.set_space(info.leaf.page_id,1);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
    }
    
};

void Bp_Tree::update_range(uint32_t key_first,uint32_t key_last,uint16_t num_rows,std::vector<uint16_t>positions,std::vector<char>types, Run* obj, std::vector<std::string>values){
    Row row{};
    search(key_first,num_rows,info.relation.row_size);
    std::fstream fs;
    bool found{};
    uint32_t index{};
    uint32_t index_i{};
    Row row_empty{};

    

    row_empty.data.resize(info.relation.row_size);
    
    if(info.ind->ind_height > 0){
        for(size_t i = info.index; i < num_rows;i++){
            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);
            if(index > key_last || (info.leaf.bottom_p ==0 && index==0)){
                info.index_last = i;
                found = true;
                break;
            }
            if(index == 0){
                info.index_last = i;
                break;
            }
        }
        edit_row(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj,info.index);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        fs.close();
        while(!found){
        
            
            fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
            fs.seekg(info.leaf.bottom_p);
            fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
            fs.close();
            for(size_t i = 0; i< num_rows;i++){
                memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
                memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
                memcpy(&index_i,row_empty.data.data(),4);
                if(index > key_last || (info.leaf.bottom_p == 0 && index==0)){
                    info.index_last = i;
                    found = true;
                    break;
                }
                if(index == 0){
                    info.index_last = i;
                    break;
                } 
                

            }
        edit_row(&info.leaf,positions,types,values,info.index_last+1,info.relation.row_size,obj);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        fs.close();
        }


        
       
    
    }else{
        
        for(size_t i = info.index; i < num_rows-1;i++){

            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);

            
            if(index > key_last || index == 0){

                info.index_last = i;
                
                
                break;
            }
        }
        edit_row(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj,info.index);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
    }
};

void Bp_Tree::update_range(float key_first,float key_last,uint16_t num_rows,std::vector<uint16_t>positions,std::vector<char>types, Run* obj, std::vector<std::string>values){
    Row row{};
    search(key_first,num_rows,info.relation.row_size);
    std::fstream fs;
    bool found{};
    float index{};
    float index_i{};
    Row row_empty{};

    

    row_empty.data.resize(info.relation.row_size);
    
    if(info.ind->ind_height > 0){

        for(size_t i = info.index; i < num_rows;i++){
            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);
            
            if(index > key_last || index == 0.0){
                info.index_last = i;
                break;
            }
        }
        edit_row(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj,info.index);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        fs.close();
        while(!found){
        
        

            fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
            fs.seekg(info.leaf.bottom_p);
            fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
            fs.close();
            for(size_t i = 0; i< num_rows;i++){
                memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
                memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
                memcpy(&index_i,row_empty.data.data(),4);
                
                if(index > key_last || (info.leaf.bottom_p == 0 && index==0.0)){
                    info.index_last = i;
                    found = true;
                    break;
                } 
                if(index == 0.0){
                    info.index_last = i;
                    break;
                }
                

            }
        edit_row(&info.leaf,positions,types,values,info.index_last+1,info.relation.row_size,obj);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        fs.close();
        }


        
       
    
    }else{
        
        for(size_t i = info.index; i < num_rows-1;i++){

            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);

            
            if(index > key_last || index == 0.0){

                info.index_last = i;
                
                
                break;
            }
        }
        edit_row(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj,info.index);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        fs.close();
    }
}

void Bp_Tree::update_index_range(uint32_t key_first,uint32_t key_last,uint16_t num_rows,std::vector<uint16_t>positions,std::vector<char>types, Run* obj, std::vector<std::string>values){
    search(key_first,num_rows,info.relation.row_size);

    Row row{};
    search(key_first,num_rows,info.relation.row_size);
    std::fstream fs;
    bool found{};
    uint32_t index{};
    uint32_t index_i{};
    Row row_empty{};
    Row row_dump{};
    

    row_empty.data.resize(info.relation.row_size);
    
    if(info.ind->ind_height > 0){

        for(size_t i = info.index; i < num_rows;i++){
            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);
            if(index > key_last){
                info.index_last = i;
                found = true;
                break;
            }
            if(index == 0){
                info.index_last = i;
                break;
            }

        }
        info.rows = edit_rows(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj,info.index);
        delete_range(key_first,index_i,num_rows,row_dump);
        for(size_t i = 0; i< info.rows.size();i++){
            uint32_t ind{};
            memcpy(&ind,info.rows.at(i).data.data(),4);
            insert(ind,num_rows,info.relation.row_size,obj,info.rows.at(i));
        }

        while(!found){
            fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
            fs.seekg(info.leaf.bottom_p);
            fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
            for(size_t i = 0; i< num_rows;i++){
                memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
                memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
                memcpy(&index_i,row_empty.data.data(),4);
                if(index > key_last || (info.leaf.bottom_p == 0 && index==0)){
                    found = true;
                    info.index_last = i;
                    break;
                }
                if(index == 0){
                    info.index_last = 1;
                    break;
                }
                

            }
        info.rows = edit_rows(&info.leaf,positions,types,values,info.index_last+1,info.relation.row_size,obj);
        delete_range(key_first,index_i,num_rows,row_dump);
        for(size_t i = 0; i< info.rows.size();i++){
            uint32_t ind{};
            memcpy(&ind,info.rows.at(i).data.data(),4);
            insert(ind,num_rows,info.relation.row_size,obj,info.rows.at(i));
        }

        }


        
       
    
    }else{
        
        for(size_t i = info.index; i < num_rows-1;i++){

            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);

            
            if(index > key_last || index == 0){

                info.index_last = i;
                
                
                break;
            }
        }
        info.rows = edit_rows(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj,info.index);
        delete_range(key_first,index_i,num_rows,row_dump);
        for(size_t i = 0; i< info.rows.size();i++){
            uint32_t ind{};
            memcpy(&ind,info.rows.at(i).data.data(),4);
            insert(ind,num_rows,info.relation.row_size,obj,info.rows.at(i));
        }
       
    }
};

void Bp_Tree::update_index_range(float key_first,float key_last,uint16_t num_rows,std::vector<uint16_t>positions,std::vector<char>types, Run* obj, std::vector<std::string>values){

    Row row{};
    search(key_first,num_rows,info.relation.row_size);
    std::fstream fs;
    bool found{};
    float index{};
    float index_i{};
    Row row_empty{};
    Row row_dump{};
    

    row_empty.data.resize(info.relation.row_size);
    
    if(info.ind->ind_height > 0){

        for(size_t i = info.index; i < num_rows;i++){
            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);
            if(index > key_last){
                info.index_last = i;
                found = true;
                break;
            }
            if(index == 0.0){
                info.index_last = i;
                break;
            }
        }
        info.rows = edit_rows(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj,info.index);
        delete_range(info.index,index_i,num_rows,row_dump);
        for(size_t i = 0; i< info.rows.size();i++){
            float ind{};
            memcpy(&ind,info.rows.at(i).data.data(),4);
            insert(ind,num_rows,info.relation.row_size,obj,info.rows.at(i));
        }
        
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        while(!found){
        
        

            
            fs.seekg(info.leaf.bottom_p);
            fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
            
            for(size_t i = 0; i< num_rows;i++){
                memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
                memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
                memcpy(&index_i,row_empty.data.data(),4);
                if(index > key_last || (info.leaf.bottom_p == 0 && index==0)){
                    info.index_last = i;
                    found = true;
                    break;
                } 
                if(index == 0.0){
                    info.index_last = i;
                    break;
                }
            }
        info.rows = edit_rows(&info.leaf,positions,types,values,info.index_last+1,info.relation.row_size,obj);
        delete_range(key_first,key_last,num_rows,row_dump);
        for(size_t i = 0; i< info.rows.size();i++){
            float ind{};
            memcpy(&ind,info.rows.at(i).data.data(),4);
            insert(ind,num_rows,info.relation.row_size,obj,info.rows.at(i));
        }

        }


        fs.close();
       
    
    }else{
        
        for(size_t i = info.index; i < num_rows-1;i++){

            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);
            
            
            if(index > key_last || index == 0.0){

                info.index_last = i;
                
                
                break;
            }
        }
        info.rows = edit_rows(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj,info.index);
        delete_range(key_first,key_last,num_rows,row_dump);
        for(size_t i = 0; i< info.rows.size();i++){
            
            float ind{};
            memcpy(&ind,info.rows.at(i).data.data(),4);
            insert(ind,num_rows,info.relation.row_size,obj,info.rows.at(i));
        }
   
    }
}

