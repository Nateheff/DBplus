#include "B+_Tree.h"

// void Bp_Tree::write_page(Curr_Node* node,std::string file,uint32_t offset){

    // std::fstream fs;
    // fs.open(file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
    // fs.seekp(offset);
    // std::ostream_iterator<uint32_t> output_iterator(fs, "\n");
    // std::copy(std::begin(node->indexes), std::end(node->indexes), output_iterator);
    // fs.close();
// };

void Bp_Tree::search(uint16_t key,uint16_t num_rows, uint16_t row_size, Run* obj){
    std::cout<<"started "<<num_rows<<" "<<row_size<<std::endl;
    // fs.clear();
    // std::cout<<"started"<<std::endl;
    

    

    // Syst_Root root{};
    
    // Curr_Node leaf;
    
    // std::vector<uint32_t>offsets;
    // uint16_t index_root{};
    // uint16_t index{};

    
    
    
    
    
    std::fstream fs;
    
    std::cout<<"null "<<fs.is_open()<<std::endl;
    
   
    fs.open(info.relation.rel_file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    std::cout<<"open "<<info.relation.rel_file<<fs.is_open()<<std::endl;
    //search through root
    
    
    
    // std::cout<<fs.is_open()<<std::endl;
    //get pointer
    
    uint32_t offset{};
    
    if(info.ind.ind_height > 0){
        
        std::cout<<"height"<<std::endl;
        fs.seekg(0);
        fs.read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
        
        uint16_t index = info.root.next_index;
        info.offsets.push_back(0);
        // std::cout<<"Root: "<<root.page_id<<" "<<root.arr[0].key<<" "<<(int)root.next_index<<std::endl;
        // std::cout<<"Bottom: "<<root.bottom_p<<std::endl;
    // for(size_t i = 0;i<15;i++)
    // std::cout<<i<<": "<<"Key: "<<root.arr[i].key<<" Pointer: "<<root.arr[i].pointer<<std::endl;
    
    while(index == 1){
       
        // std::cout<<"HERE "<<index<<std::endl;
    for(size_t i = 0; i < 511;i++){
        if(info.root.arr[0].key > key){
            std::cout<<"3"<<std::endl;
            offset = info.root.bottom_p;
            info.offsets.push_back(offset);
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            
            index = info.root.next_index;
            
            break;
        } else if(info.root.arr[i].key > key && info.root.arr[i-1].key < key){
            // std::cout<<"2"<<std::endl;
            offset = info.root.arr[i].pointer;
            info.offsets.push_back(offset);
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            
            index = info.root.next_index;
            
            break;
        } else if(info.root.arr[i].key == key){
            // std::cout<<"1: "<<i<<std::endl;
            
            info.offsets.push_back(info.root.arr[i].pointer);
            offset = info.root.arr[i].pointer;
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            
            index = info.root.next_index;
                     
            break;

        } else if(info.root.arr[i].key < key && info.root.arr[i+1].pointer == 0){
            // std::cout<<"4"<<std::endl;
            info.offsets.push_back(info.root.arr[i].pointer);

            offset = info.root.arr[i].pointer;
            // std::cout<<"offseT: "<<offset<<" "<<root.arr[i].key<<std::endl;
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            
            // std::cout<<"RooT: "<<root.page_id<<" "<<(int)root.next_index<<" "<<fs.gcount()<<std::endl;
            index = info.root.next_index;
            
            break;
        }
       
    }
    // std::cout<<"next_index: "<<index<<" root: "<<root.page_id<<std::endl;
    };
    // std::cout<<"step 1: "<<offsets.size()<<std::endl;
    // std::cout<<"Index ID: "<<root.page_id<<std::endl;
    for(size_t i = 0; i < 511;i++){
        if(info.root.arr[i].key == key){
            // std::cout<<"equals: "<<i<<std::endl;
            info.index_root = i;
            offset = info.root.arr[i].pointer;
            
            fs.seekg(offset);
            // std::cout<<"offset: "<<offset<<std::endl;
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
            
            break;
            

        } else if(i ==0 && key < info.root.arr[i].key){
            // std::cout<<root.page_id<<" "<<root.arr[0].key<<" "<<root.arr[0].pointer<<std::endl;
            // std::cout<<"lower"<<std::endl;
            info.index_root = i;
            offset = info.root.bottom_p;
            
            fs.seekg(offset);
            // std::cout<<"offset: "<<offset<<std::endl;
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
            
            break;

        } else if(info.root.arr[i].key > key && info.root.arr[i-1].key < key){
            // std::cout<<key<<" between: "<<root.arr[i-1].key<<" and "<<root.arr[i].key<<" at "<<i<<std::endl;
            info.index_root = i;
            offset = info.root.arr[i-1].pointer;
            // std::cout<<"offset: "<<offset<<std::endl;
            
            
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
            
            // std::cout<<leaf.page_id<<std::endl;
            // std::cout<<root.arr[i].key<<std::endl;
            break;
        }else if(info.root.arr[i].key < key && info.root.arr[i+1].pointer == 0){
            info.index_root = i+1;
            // std::cout<<i<<"larger than: "<<root.arr[i].key<<std::endl;
            offset = info.root.arr[i].pointer;
            
            
            fs.seekg(offset);
            
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
            
            
            break;
        }
        
    }
    // std::cout<<"step 2: "<<offsets.size()<<std::endl;
    // std::cout<<"Rel: "<<leaf.page_id<<" "<<leaf.is_index<<std::endl;
    
    }else{
        std::cout<<"No height "<<" "<<fs.tellg()<<std::endl;
        
        fs.seekg(0);
        std::cout<<"pre "<<fs.fail()<<std::endl;
        fs.read(reinterpret_cast<char*>(&info.leaf),4096);
        std::cout<<"post "<<fs.gcount()<<" "<<4096<<std::endl;
        info.leaf.page_id = 0;

    };
    
    std::cout<<"got the rel"<<info.leaf.page_id<<" "<<info.leaf.bottom_p<<" "<<info.leaf.is_index<<std::endl;
    for(size_t i =0;i<num_rows;i++){
            uint32_t index{};
            memcpy(&index,&info.leaf.data[i*row_size],4);
            // std::cout<<"name: "<<info.leaf.data[i].index<<" key: "<<key<<std::endl;
            if(key <= index || (i == num_rows-1 && key > index)||index == 0){
            std::cout<<"found "<<i<<std::endl;
                info.index = i;
                
                return;
        
        }
    }
    
};


void Bp_Tree::insert(uint32_t key, uint16_t num_rows,uint16_t row_size, Run* obj, Row row){
    std::cout<<"Inserting! "<<std::endl;
    
//search normally
    
    // std::cout<<"Key: "<<key<<std::endl;
    // if(test > num_rows)
    // search(key,num_rows,ind_type);
    // else
    info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    info.ind = obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
    search(key,num_rows,row_size,obj);
    std::fstream fs;
    fs.open(info.relation.rel_file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    // std::cout<<"Offsets: "<<info.offsets.size()<<std::endl;
    // std::cout<<"Page: "<<leaf.page_id<<std::endl;
    // std::cout<<"Root: "<<info.root.page_id<<std::endl;

// std::cout<<"Searched"<<leaf.page_id<<std::endl;
    // std::cout<<info.root.arr[0].key<<std::endl;
    
    //std::cout<<"still";
    
//once you have the page of where the row with the key would fit, see if there's space via the fsm and if there is, move all rows "greater" than it up 1 row space and put the new row in the space created at the correct place. If there's not room, split, and do the b+ tree thing. this will take some effort to figure out how to do.
    
    // std::cout<<"beginning insert: "<<leaf.page_id<<std::endl;
   
    if(!fsm.has_root()){
    fsm.get_fsm(info.relation.rel_file);
    std::cout<<"got fsm"<<std::endl;
    }
    
    // std::cout<<"Checking: "<<real<<std::endl;
    //std::cout<<"Got the FSM"<<std::endl;
    //THIS IS BASICALLY JUST THE B+ TREE INSERT IMPLEMENTATION, SO JUST REPLACE THIS WITH B+ TREE INSERT WHEN ITS DONE
    uint32_t key_of_interest{};
    uint32_t new_page_offset{};
    uint32_t new_low_p{};
    
    // std::cout<<"Checking: "<<leaf.page_id<<std::endl;
    if(fsm.has_space(info.leaf.page_id)==1){
        // std::cout<<"Has space"<<std::endl;
        
        std::cout<<"INDEX: "<<info.index<<std::endl;
        std::vector<char>empty{};
        empty.resize(row_size);
        // for(size_t i=0;i<24;i++)
        //     std::cout<<i<<": "<<leaf.data[i].index<<std::endl;
        for(size_t i = num_rows-2;i >= info.index;i--){
            
            
            memcpy(&info.leaf.data[(i+1)*row_size],&info.leaf.data[i*row_size],row_size);
            memcpy(&info.leaf.data[i],empty.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
            if(i == 0)
            break;
        }
        
        // for(size_t i=0;i<26;i++)
        //     std::cout<<i<<"b: "<<leaf.data[i].index<<std::endl;
        // std::cout<<"ROW: "<<row.check<<std::endl;
        // 
        memcpy(&info.leaf.data[info.index*row_size],row.data.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
        // for(size_t i=0;i<26;i++)
        //     std::cout<<i<<": "<<leaf.data[i].index<<std::endl;
        fsm.set_space(info.leaf.page_id,1);
        //  std::cout<<"ATTENTION: "<<leaf.data[0].check<<leaf.data[1].check<<std::endl;
        uint32_t index{};
        memcpy(&index,&info.leaf.data[(num_rows-1)*row_size],4);
        if(index != 0){
        std::cout<<"1!"<<std::endl;
        fsm.set_space(info.leaf.page_id,2);
        }
        
         //write back
        //  std::cout<<"THIS: "<<info.offsets.size()<<std::endl;
        // 
        
        
       
        fs.seekp(info.leaf.page_id*4096);
        
        fs.write(reinterpret_cast<char*>(&info.leaf),4096);
        
       fsm.flush_fsm(0);
       
    //    
        info.offsets.clear();
   
    
        return;
    }else if(fsm.has_space(info.leaf.page_id) != 1 && info.leaf.page_id != 0){
         //step 1: split info.leaf, get positon of new info.leaf.
        std::cout<<"words: "<<info.offsets.size()<<std::endl;
        if(info.offsets.size()>=1){
        Curr_Node half;
        half.page_id = fsm.page();
        
        // if(half.page_id >=469)
        // std::cout<<"still "<<std::endl;
        // std::cout<<"PAGE: "<<half.page_id;
        new_page_offset = (half.page_id) * 4096;
        // std::cout<<"OFF: "<<new_page_offset<<std::endl;
    
        Row empty;
        for(size_t i = num_rows/2; i<num_rows;i++){
            half.data[i-(num_rows/2)]=info.leaf.data[i];
            info.leaf.data[i] = '\0';//FIXX////////////////////////////////////////////////////////////////////////////
            
        }
        // for(size_t i=0;i<26;i++)
        //     std::cout<<i<<": "<<info.leaf.data[i].check<<std::endl;
        // for(size_t i=0;i<26;i++)
        //     std::cout<<i<<": "<<info.leaf.data[i].check<<std::endl;
        // for(size_t i=0;i<26;i++)
        //     std::cout<<i<<": "<<half.rows[i].check<<std::endl;
        //make room and insert new row into proper info.leaf and get upper median key to send to parent node.
       
        if(info.index < num_rows/2){
            // std::cout<<"1"<<std::endl;
            
            key_of_interest = info.leaf.indexes.at((num_rows/2)-1);
            
            for(size_t i = num_rows/2; i > info.index;i--){
                info.leaf.data[i] = info.leaf.data[i-1];
            };
            info.leaf.data[info.index] = '\0';
            
        }else if(info.index > num_rows/2){
            
            key_of_interest = info.leaf.indexes.at(info.index);
            
            // std::cout<<"Bruh: "<<key_of_interest<<std::endl;
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                half.data[i] = half.data[i-1];
            }
            half.data[info.index -(num_rows/2) ] = '\0';//FIXX////////////////////////////////////////////////////////////////////////////
        }else{
            key_of_interest = key;
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                half.data[i] = half.data[i-1];
            }
            half.data[info.index -(num_rows/2)] = '\0';//FIXX////////////////////////////////////////////////////////////////////////////
        };
        half.bottom_p = info.leaf.bottom_p;
        info.leaf.bottom_p = half.page_id*4096;
        fsm.set_space(half.page_id,1);
        fsm.set_space(info.leaf.page_id,1);
        fs.seekp(info.leaf.page_id * 4096);
        fs.write(reinterpret_cast<char*>(&info.leaf),4096);
        
        fs.seekp(new_page_offset);
        fs.write(reinterpret_cast<char*>(&half),sizeof(half));
        info.relation.num_pages++;
        info.relation.num_rows = (half.page_id * num_rows)*.66;
        
        }
        
    };
    // step 2: send new KOI/position of new to parent node.
    Key_Pointer k_p{key_of_interest,new_page_offset};
    // if(test > 8384)
  std::cout<<"made it here: "<<info.offsets.size()<<info.root.page_id<<std::endl;
  if(info.offsets.size() >= 1){
    for(size_t i = info.offsets.size()-1; i >= 0; i--){
        std::cout<<"beginning deep"<<std::endl;
        //get parent node into memory
        // Syst_Root root;
        // fs.seekg(info.offsets.at(i));
        // fs.read(reinterpret_cast<char*>(&root),4096);
        // std::cout<<info.root.page_id<<" "<<fsm.has_space(info.root.page_id)<<std::endl;
        if(fsm.has_space(info.root.page_id)==1){
            // std::cout<<"space: "<<k_p.key<<" "<<k_p.pointer<<std::endl;
            // step 3: if parent has room, insert at appropriate location. 
            
            // std::cout<<"ROOT: "<<info.root.page_id<<std::endl;
            // std::cout<<info.root.arr[i].key<<": "<<info.root.arr[i].pointer<<std::endl;
            if(info.index_root >= 4096){
                std::cout<<"space: "<<k_p.key<<" "<<k_p.pointer<<std::endl;
            // step 3: if parent has room, insert at appropriate location. 
            
            // std::cout<<"ROOT: "<<info.root.page_id<<std::endl;
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
            fs.seekp(info.root.page_id*4096);
            fs.write(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            // for(size_t i = 0; i<10;i++){
                // std::cout<<i<<": "<<info.root.arr[i].key<<std::endl;
            // }
            fsm.flush_fsm(0);
            // std::cout<<"flush"<<std::endl;
            info.offsets.clear();
            // std::cout<<"going: "<<info.index_root<<std::endl;
            info.index_root = 0;
            return;
        }else if(fsm.has_space(info.root.page_id)!=1 && i != 0){
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
            fs.seekp(info.root.page_id*4096);
            fs.write(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            fs.seekp(half_root.page_id*4096);
            fs.write(reinterpret_cast<char*>(&half_root),sizeof(half_root));
            fs.seekg(info.offsets.at(i-1));
            fs.read(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            info.index_root = 4097;
            info.offsets.clear();
            
            // std::cout<<"DONEE"<<std::endl;
        }else if(fsm.has_space(info.root.page_id)!=1 && i == 0){
            std::cout<<"SPLTTING ROOT: "<<i<<" "<<info.offsets.size()<<std::endl;
            Key_Pointer empty;
            Syst_Root half_root;
            
            half_root.page_id = fsm.page();
            // std::cout<<"Half: "<<half_root.page_id<<std::endl;
        //split current info.root
        //if i > 255, the koi goes to i=256 else, i = 255
        

        
        
        fsm.set_space(half_root.page_id,1);

        std::cout<<"still"<<half_root.page_id<<std::endl;
        info.root.page_id = fsm.page();
        std::cout<<"Old root: "<<info.root.page_id<<std::endl;
        fsm.set_space(info.root.page_id,1);
        //get new info.root page and send koi and location of new "children" to new info.root for l & r pointers
        Syst_Root new_root;
        uint16_t temp_koi{};
        uint32_t temp_p{};



        std::cout<<"INDeX: "<<info.index_root<<std::endl;
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
            for(size_t i = 0;i<257;i++){
            std::cout<<i<<": "<<info.root.arr[i].key<<std::endl;
        }
        for(size_t i = 0;i<257;i++){
            std::cout<<i<<": "<<half_root.arr[i].key<<std::endl;
        }
            k_p.key = temp_koi;
            //switch the current 0 index page and the info.root page  so the info.root is always at index 0
            k_p.pointer = half_root.page_id * 4096;
            std::cout<<"Pointer OI: "<<k_p.pointer<<std::endl;
            new_root.page_id = 0;
            new_root.bottom_p = info.root.page_id * 4096;
            std::cout<<"Bottom P: "<<new_root.bottom_p<<std::endl;
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
        
            std::cout<<"it worked? "<<new_root.bottom_p<<" "<<new_root.arr[0].pointer<<" "<<half_root.bottom_p<<" "<<info.root.bottom_p<<std::endl;
            info.offsets.clear();
            return;
        }; 
        // step 5: repeat until opening in index or at top level (root)
        std::cout<<"nowhere"<<std::endl;
    };
  }else{
    // std::cout<<"started split"<<std::endl;
    Key_Pointer empty;
            Syst_Root new_root;
            Curr_Node half;
            
            new_root.page_id = 0;
            new_root.bottom_p = 4096;
            Row empty_row;

            for(size_t i = num_rows/2;i < num_rows;i++){
                half.data[i-(num_rows/2)] = info.leaf.data[i];
                info.leaf.data[i] = '\0';//FIXX////////////////////////////////////////////////////////////////////////////
            
            }
            
            if(info.index < num_rows/2){
                
                key_of_interest = info.leaf.indexes.at((num_rows/2)-1);
               
            for(size_t i = num_rows/2; i > info.index;i--){
                info.leaf.data[i] = info.leaf.data[i-1];
            };
            info.leaf.data[info.index] = '\0';//FIXX////////////////////////////////////////////////////////////////////////////
            }else if(info.index > num_rows/2){
               
            key_of_interest = info.leaf.indexes.at(0);//CHECK////////////////////////////////////////////////////////////////////////////
            
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                half.data[i] = half.data[i-1];
            }
            half.data[info.index -(num_rows/2) ] = '\0';//FIXX/////////////////////////////////////////////////////////////////////
        }else
            key_of_interest = key;
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                half.data[i] = half.data[i-1];
        }
        // std::cout<<"KOI: "<<key_of_interest<<std::endl;
        //get new root page and send koi and location of new "children" to new root for l & r pointers
        
        
        
        
        new_root.arr[0] = {key_of_interest,8192};
        new_root.next_index=0;
        info.leaf.page_id = 1;
        half.page_id = 2;
        info.leaf.bottom_p = half.page_id*4096;
        // std::cout<<"Info: "<<half.page_id<<" "<<leaf.page_id<<std::endl;
            //switch the current 0 index page and the root page  so the root is always at index 0
            // for(size_t i = 0; i<10;i++){
                // std::cout<<i<<": "<<new_root.arr[i].key<<std::endl;
            // }
            // for(size_t i = 0; i<num_rows;i++)
            // std::cout<<i<<": "<<leaf.data[i].index<<std::endl;
            // for(size_t i = 0; i<num_rows;i++)
            // std::cout<<i<<": "<<half.rows[i].index<<std::endl;
            fsm.set_space(0,1);
            fsm.set_space(1,1);
            fsm.set_space(2,1);
            // std::cout<<"still"<<std::endl;
            fs.seekp(0);
            fs.write(reinterpret_cast<char*>(&new_root),sizeof(new_root));
            fs.seekp((info.leaf.page_id)*4096);
            fs.write(reinterpret_cast<char*>(&info.leaf),4096);
            fs.seekp((half.page_id)*4096);
            fs.write(reinterpret_cast<char*>(&half),4096);
        fs.close();
        // std::cout<<"even still"<<std::endl;
        info.index = 0;
        info.offsets.clear();
        // std::cout<<"clear?"<<std::endl;
        info.ind.ind_height = 1;
        // std::cout<<"height?"<<std::endl;
        info.relation.num_pages++;
        // std::cout<<"pre flush"<<std::endl;
        fsm.flush_fsm(0);
        
        std::cout<<"split"<<std::endl;
  };
  
// step 6: if need to split root, get new root page, send koi and locations of children to new root. save location of new root in specialized file with root locations of each index.
    // fsm.flush_fsm(std::string{"catalog_rel"});
    info.relation.num_rows++;
    

};
