#include "B+_Tree.h"

// void Bp_Tree::write_page(Curr_Node* node,std::string file,uint32_t offset){

    // std::fstream fs;
    // fs.open(file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
    // fs.seekp(offset);
    // std::ostream_iterator<uint32_t> output_iterator(fs, "\n");
    // std::copy(std::begin(node->indexes), std::end(node->indexes), output_iterator);
    // fs.close();
// };

void Bp_Tree::search(uint32_t key,uint16_t num_rows, uint16_t row_size){
    std::cout<<"started "<<num_rows<<" "<<row_size<<std::endl;
    // fs.clear();
    // std::cout<<"started"<<std::endl;
    

    

    // Syst_Root root{};
    
    // Curr_Node leaf;
    
    // std::vector<uint32_t>offsets;
    // uint16_t index_root{};
    // uint16_t index{};

    
    
    
    
    
    std::fstream fs;
    
    // std::cout<<"null "<<fs.is_open()<<std::endl;
    
   
    fs.open(info.relation.rel_file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    // std::cout<<"open "<<info.relation.rel_file<<fs.is_open()<<std::endl;
    //search through root
    
    
    
    // std::cout<<fs.is_open()<<std::endl;
    //get pointer
    
    uint32_t offset{};
    
    if(info.ind->ind_height > 0){
        
        // std::cout<<"height"<<std::endl;
        fs.seekg(info.ind->ind_start);
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
        
        fs.seekg(info.ind->ind_start);
        // std::cout<<"pre "<<fs.fail()<<std::endl;
        fs.read(reinterpret_cast<char*>(&info.leaf),4096);
        // std::cout<<"post "<<fs.gcount()<<" "<<4096<<std::endl;
        info.leaf.page_id = 0;

    };
    
    // std::cout<<"got the rel"<<info.leaf.page_id<<" "<<info.leaf.bottom_p<<" "<<info.leaf.is_index<<std::endl;
    for(size_t i =0;i<num_rows;i++){
            uint32_t index{};
            memcpy(&index,&info.leaf.data[i*row_size],4);
            // std::cout<<"name: "<<index<<" key: "<<key<<std::endl;
            if(key <= index || (i == num_rows-1 && key > index)||index == 0){
            // std::cout<<"found "<<i<<std::endl;
                info.index = i;
                
                return;
        
        }
    }
    
};

void Bp_Tree::search(float key,uint16_t num_rows, uint16_t row_size){
    std::cout<<"started float "<<num_rows<<" "<<row_size<<std::endl;
    // fs.clear();
    // std::cout<<"started"<<std::endl;
    

    

    // Syst_Root root{};
    
    // Curr_Node leaf;
    
    // std::vector<uint32_t>offsets;
    // uint16_t index_root{};
    // uint16_t index{};

    
    
    
    
    
    std::fstream fs;
    
    // std::cout<<"null "<<fs.is_open()<<std::endl;
    
   
    fs.open(info.relation.rel_file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    // std::cout<<"open "<<info.relation.rel_file<<fs.is_open()<<std::endl;
    //search through root
    
    
    
    // std::cout<<fs.is_open()<<std::endl;
    //get pointer
    
    uint32_t offset{};
    
    if(info.ind->ind_height > 0){
        
        // std::cout<<"height"<<std::endl;
        fs.seekg(info.ind->ind_start);
        fs.read(reinterpret_cast<char*>(&root_f),sizeof(root_f));
        
        uint16_t index = root_f.next_index;
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
            offset = root_f.bottom_p;
            info.offsets.push_back(offset);
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&root_f),sizeof(root_f));
            
            index = root_f.next_index;
            
            break;
        } else if(root_f.arr[i].key > key && root_f.arr[i-1].key < key){
            // std::cout<<"2"<<std::endl;
            offset = root_f.arr[i].pointer;
            info.offsets.push_back(offset);
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&root_f),sizeof(root_f));
            
            index = root_f.next_index;
            
            break;
        } else if(root_f.arr[i].key == key){
            // std::cout<<"1: "<<i<<std::endl;
            
            info.offsets.push_back(root_f.arr[i].pointer);
            offset = root_f.arr[i].pointer;
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&root_f),sizeof(root_f));
            
            index = root_f.next_index;
                     
            break;

        } else if(root_f.arr[i].key < key && root_f.arr[i+1].pointer == 0){
            // std::cout<<"4"<<std::endl;
            info.offsets.push_back(root_f.arr[i].pointer);

            offset = root_f.arr[i].pointer;
            // std::cout<<"offseT: "<<offset<<" "<<root.arr[i].key<<std::endl;
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&root_f),sizeof(root_f));
            
            // std::cout<<"RooT: "<<root.page_id<<" "<<(int)root.next_index<<" "<<fs.gcount()<<std::endl;
            index = root_f.next_index;
            
            break;
        }
       
    }
    // std::cout<<"next_index: "<<index<<" root: "<<root.page_id<<std::endl;
    };
    // std::cout<<"step 1: "<<offsets.size()<<std::endl;
    // std::cout<<"Index ID: "<<root.page_id<<std::endl;
    for(size_t i = 0; i < 511;i++){
        if(root_f.arr[i].key == key){
            // std::cout<<"equals: "<<i<<std::endl;
            info.index_root = i;
            offset = root_f.arr[i].pointer;
            
            fs.seekg(offset);
            // std::cout<<"offset: "<<offset<<std::endl;
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
            
            break;
            

        } else if(i ==0 && key < root_f.arr[i].key){
            // std::cout<<root.page_id<<" "<<root.arr[0].key<<" "<<root.arr[0].pointer<<std::endl;
            // std::cout<<"lower"<<std::endl;
            info.index_root = i;
            offset = root_f.bottom_p;
            
            fs.seekg(offset);
            // std::cout<<"offset: "<<offset<<std::endl;
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
            
            break;

        } else if(root_f.arr[i].key > key && root_f.arr[i-1].key < key){
            // std::cout<<key<<" between: "<<root.arr[i-1].key<<" and "<<root.arr[i].key<<" at "<<i<<std::endl;
            info.index_root = i;
            offset = root_f.arr[i-1].pointer;
            // std::cout<<"offset: "<<offset<<std::endl;
            
            
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
            
            // std::cout<<leaf.page_id<<std::endl;
            // std::cout<<root.arr[i].key<<std::endl;
            break;
        }else if(root_f.arr[i].key < key && root_f.arr[i+1].pointer == 0){
            info.index_root = i+1;
            // std::cout<<i<<"larger than: "<<root.arr[i].key<<std::endl;
            offset = root_f.arr[i].pointer;
            
            
            fs.seekg(offset);
            
            fs.read(reinterpret_cast<char*>(&info.leaf),4096);
            
            
            break;
        }
        
    }
    // std::cout<<"step 2: "<<offsets.size()<<std::endl;
    // std::cout<<"Rel: "<<leaf.page_id<<" "<<leaf.is_index<<std::endl;
    
    }else{
        std::cout<<"No height "<<" "<<fs.tellg()<<std::endl;
        
        fs.seekg(info.ind->ind_start);
        std::cout<<"pre "<<fs.fail()<<std::endl;
        fs.read(reinterpret_cast<char*>(&info.leaf),4096);
        std::cout<<"post "<<fs.gcount()<<" "<<4096<<std::endl;
        info.leaf.page_id = 0;

    };
    
    // std::cout<<"got the rel"<<info.leaf.page_id<<" "<<info.leaf.bottom_p<<" "<<info.leaf.is_index<<std::endl;
    for(size_t i =0;i<num_rows;i++){
            float index{};
            memcpy(&index,&info.leaf.data[i*row_size],4);
            std::cout<<"name: "<<index<<" key: "<<key<<std::endl;
            if(key <= index || (i == num_rows-1 && key > index)||index == 0){
            std::cout<<"found "<<i<<std::endl;
                info.index = i;
                
                return;
        
        }
    }
    
};

// void Bp_Tree::delete_row(Run* obj, uint16_t index_first, uint16_t index_last){
//     Row row{};
//     row.data.resize(info.relation.row_size);
//     uint16_t num_rows = 4087/info.relation.row_size;
//     std::cout<<"resized"<<std::endl;
//     std::fstream fs;
//     fs.open(info.relation.rel_file, std::ios_base::binary|std::ios_base::in|std::ios_base::out);

//     if(info.pages.size()==1){

//     for(size_t j = info.index;j<index_last;j++){

//             memcpy(&info.pages.at(0).data[j*info.relation.row_size],row.data.data(),info.relation.row_size);
//             fs.seekp(info.pages.at(0).page_id*4096+info.ind->ind_start);
//             fs.write(reinterpret_cast<char*>(&info.pages.at(0)),sizeof(info.pages.at(0)));

//     }
//     fsm.set_space(info.pages.at(0).page_id,1);
//     std::cout<<"fsm 1"<<std::endl;
//     }

//     if(info.pages.size()>1){

//     for(size_t j = info.index;j<num_rows;j++){

//             memcpy(&info.pages.at(0).data[j*info.relation.row_size],row.data.data(),info.relation.row_size);
//             fs.seekp(info.pages.at(0).page_id*4096+info.ind->ind_start);
//             fs.write(reinterpret_cast<char*>(&info.pages.at(0)),sizeof(info.pages.at(0)));
//             fsm.set_space(info.pages.at(0).page_id,1);
//     }

//     for(size_t i = 0; i<info.pages.size()-1;i++){

//         for(size_t j = 0;j<num_rows;j++){

//             memcpy(&info.pages.at(i).data[j*info.relation.row_size],row.data.data(),info.relation.row_size);
//         }
//         fs.seekp(info.pages.at(i).page_id*4096+info.ind->ind_start);
//         fs.write(reinterpret_cast<char*>(&info.pages.at(i)),sizeof(info.pages.at(i)));
//         fsm.set_space(info.pages.at(i).page_id,0);
        
//     }

//     for(size_t i = 0;i<index_last;i++){
//          memcpy(&info.pages.at(info.pages.size()-1).data[i*info.relation.row_size],row.data.data(),info.relation.row_size);
//     }
//     if(index_last == num_rows)
//     fsm.set_space(info.pages.at(info.pages.size()-1).page_id,0);
//     else
//     fsm.set_space(info.pages.at(info.pages.size()-1).page_id,1);
    
//     std::cout<<"multi page"<<std::endl;

//     }
    
    
    
//     //dirty tree
    
//     info.relation.num_rows -= index_last-index_first;

//     obj->tree_rel.dirty = true;
    
//     // info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
//     // info.ind = &obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
//     // search(key,num_rows,row_size);
//     // // std::cout<<"searched"<<std::endl;
//     // std::fstream fs;
//     // fs.open(info.relation.rel_file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
//     // for(size_t i = info.index;i<num_rows;i++){
//     //     memcpy(&info.leaf.data[i*row_size],&info.leaf.data[(i+1)*row_size],row_size);
//     // }
//     // uint32_t index{};
//     // memcpy(&index,&info.leaf.data[0],4);
//     // if(info.index = 0 && index==0){
//     //     fsm.set_space(info.leaf.page_id,0);      
//     // }
//     // fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
//     // fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
//     // std::cout<<"deleted row!"<<std::endl;
// }

// void Bp_Tree::delete_row(float key, uint16_t num_rows,uint16_t row_size,Run* obj){
//     info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
//     info.ind = &obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
//     search(key,num_rows,row_size);
//     // std::cout<<"searched"<<std::endl;
//     std::fstream fs;
//     fs.open(info.relation.rel_file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
//     for(size_t i = info.index;i<num_rows;i++){
//         memcpy(&info.leaf.data[i*row_size],&info.leaf.data[(i+1)*row_size],row_size);
//     }
//     float index{};
//     memcpy(&index,&info.leaf.data[0],4);
//     if(info.index = 0 && index==0){
//         fsm.set_space(info.leaf.page_id,0);      
//     }
//     fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
//     fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
//     std::cout<<"deleted row!"<<std::endl;
// }


void Bp_Tree::insert(uint32_t key, uint16_t num_rows,uint16_t row_size, Run* obj, Row row){
    std::cout<<"Inserting! "<<std::endl;
    
//search normally
    
    // std::cout<<"Key: "<<key<<std::endl;
    // if(test > num_rows)
    // search(key,num_rows,ind_type);
    // else
    info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    info.ind = &obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
    search(key,num_rows,row_size);
    std::cout<<"searched"<<std::endl;
    std::fstream fs;
    fs.open(info.relation.rel_file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    // std::cout<<"Offsets: "<<info.offsets.size()<<std::endl;
    // std::cout<<"Page: "<<info.leaf.page_id<<std::endl;
    // std::cout<<"Root: "<<root_f.page_id<<std::endl;

// std::cout<<"Searched"<<leaf.page_id<<std::endl;
    // std::cout<<info.root.arr[0].key<<std::endl;
    
    //std::cout<<"still";
    
//once you have the page of where the row with the key would fit, see if there's space via the fsm and if there is, move all rows "greater" than it up 1 row space and put the new row in the space created at the correct place. If there's not room, split, and do the b+ tree thing. this will take some effort to figure out how to do.
    
    // std::cout<<"beginning insert: "<<info.relation.index<<std::endl;
   
    if(!fsm.has_root()){
    fsm.get_fsm(info.relation.index);
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
        std::cout<<"Has space"<<std::endl;
        
        std::cout<<"INDEX: "<<info.index<<std::endl;
        std::vector<char>empty{};
        empty.resize(row_size);
        uint32_t index_t{};
        for(size_t i=0;i<5;i++){
            memcpy(&index_t,&info.leaf.data[i*row_size],4);
            std::cout<<i<<": "<<index_t<<" "<<i*row_size<<std::endl;
        }
        
         std::cout<<"pre-loop"<<std::endl;
        for(size_t i = num_rows-2;i >= info.index;i--){
            // std::cout<<i<<std::endl;
            memcpy(&info.leaf.data[(i+1)*row_size],&info.leaf.data[i*row_size],row_size);
            memcpy(&info.leaf.data[i*row_size],empty.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
            
            if(i == 0)
            break;
        }
        std::cout<<"post loop"<<std::endl;
        for(size_t i=0;i<4;i++){
            memcpy(&index_t,&info.leaf.data[i*row_size],4);
            std::cout<<i<<": "<<index_t<<" "<<i*row_size<<std::endl;
        }
        // for(size_t i=0;i<26;i++)
        //     std::cout<<i<<"b: "<<leaf.data[i].index<<std::endl;
        // std::cout<<"ROW: "<<row.check<<std::endl;
        // 
        memcpy(&info.leaf.data[info.index*row_size],row.data.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
        // std::cout<<"post insert"<<std::endl;
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
        // std::cout<<"post index"<<std::endl;
         //write back
        //  std::cout<<"THIS: "<<info.offsets.size()<<std::endl;
        // 
        
        
       
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        
        fs.write(reinterpret_cast<char*>(&info.leaf),4096);
        std::cout<<"pre flush"<<std::endl;
       fsm.flush_fsm(0);
       fs.close();
    //    
        info.offsets.clear();
   
        std::cout<<"done"<<std::endl;
        return;
    }else if(fsm.has_space(info.leaf.page_id) != 1 && info.leaf.page_id != 0){
         //step 1: split info.leaf, get positon of new info.leaf.
        // std::cout<<"words: "<<info.offsets.size()<<std::endl;
        if(info.offsets.size()>=1){
        Curr_Node half;
        half.page_id = fsm.page();
        
        // if(half.page_id >=469)
        // std::cout<<"still "<<std::endl;
        // std::cout<<"PAGE: "<<half.page_id;
        new_page_offset = (half.page_id) * 4096+info.ind->ind_start;
        // std::cout<<"OFF: "<<new_page_offset<<std::endl;
    
        std::vector<char>empty{};
        empty.resize(row_size);

        for(size_t i = num_rows/2; i<num_rows;i++){
            memcpy(&half.data[(i-(num_rows/2))*row_size],&info.leaf.data[i*row_size],row_size);
            memcpy(&info.leaf.data[i*row_size],empty.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
            
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
            
            memcpy(&key_of_interest,&info.leaf.data[((num_rows/2)-1)*row_size],4);
            
            for(size_t i = num_rows/2; i > info.index;i--){
                memcpy(&info.leaf.data[i*row_size],&info.leaf.data[(i-1)*row_size],row_size);
            };
            memcpy(&info.leaf.data[info.index*row_size],row.data.data(),row_size);
            
        }else if(info.index > num_rows/2){
            
            memcpy(&key_of_interest,&info.leaf.data[info.index*row_size],4);
            
            // std::cout<<"Bruh: "<<key_of_interest<<std::endl;
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                memcpy(&half.data[i*row_size],&half.data[(i-1)*row_size],row_size);
            }
            memcpy(&half.data[(info.index -(num_rows/2))*row_size],row.data.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
        }else{
            key_of_interest = key;
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                memcpy(&info.leaf.data[i*row_size],&info.leaf.data[(i-1)*row_size],row_size);
            }
            memcpy(&half.data[(info.index -(num_rows/2))*row_size],row.data.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
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
    // if(test > 8384)
//   std::cout<<"made it here: "<<info.offsets.size()<<info.root.page_id<<std::endl;
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
                // std::cout<<"space: "<<k_p.key<<" "<<k_p.pointer<<std::endl;
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
            fs.seekp(info.root.page_id*4096+info.ind->ind_start);
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
            uint32_t offset_new_index = half_root.page_id*4096+info.ind->ind_start;
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
            fs.seekp(info.root.page_id*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&info.root),sizeof(info.root));
            fs.seekp(half_root.page_id*4096+info.ind->ind_start);
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
            k_p.pointer = half_root.page_id * 4096+info.ind->ind_start;
            std::cout<<"Pointer OI: "<<k_p.pointer<<std::endl;
            new_root.page_id = 0;
            new_root.bottom_p = info.root.page_id * 4096+info.ind->ind_start;
            std::cout<<"Bottom P: "<<new_root.bottom_p<<std::endl;
            // info.root.next_index = 0;
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
        std::cout<<"KOI: "<<key_of_interest<<std::endl;
        //get new root page and send koi and location of new "children" to new root for l & r pointers
        
        
        
        
        new_root.arr[0] = {key_of_interest,8192+info.ind->ind_start};
        new_root.next_index=0;
        info.leaf.page_id = 1;
        half.page_id = 2;
        info.leaf.bottom_p = half.page_id*4096+info.ind->ind_start;
        std::cout<<"Info: "<<half.page_id<<" "<<info.leaf.page_id<<std::endl;
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
            fs.seekp(info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&new_root),sizeof(new_root));
            fs.seekp((info.leaf.page_id)*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&info.leaf),4096);
            fs.seekp((half.page_id)*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&half),4096);
        fs.close();
        // std::cout<<"even still"<<std::endl;
        info.index = 0;
        info.offsets.clear();
        // std::cout<<"clear?"<<std::endl;
        info.ind->ind_height = 1;
        obj->tree_ind.dirty = true;
        // std::cout<<"height?"<<std::endl;
        obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].num_pages++;
        obj->tree_rel.dirty = true;
        // std::cout<<"pre flush"<<std::endl;
        fsm.flush_fsm(0);
        obj->flush();
        std::cout<<"split"<<std::endl;
  };
  
// step 6: if need to split root, get new root page, send koi and locations of children to new root. save location of new root in specialized file with root locations of each index.
    // fsm.flush_fsm(std::string{"catalog_rel"});
    obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].num_rows++;
    

};

void Bp_Tree::insert(float key, uint16_t num_rows,uint16_t row_size, Run* obj, Row row){
    std::cout<<"Inserting float! "<<std::endl;
    
//search normally
    
    std::cout<<"Key: "<<key<<std::endl;
    // if(test > num_rows)
    // search(key,num_rows,ind_type);
    // else
    info.relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    info.ind = &obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];
    search(key,num_rows,row_size);
    std::cout<<"searched"<<std::endl;
    std::fstream fs;
    fs.open(info.relation.rel_file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    // std::cout<<"Offsets: "<<info.offsets.size()<<std::endl;
    // std::cout<<"Page: "<<info.leaf.page_id<<std::endl;
    // std::cout<<"Root: "<<info.root.page_id<<std::endl;

// std::cout<<"Searched"<<leaf.page_id<<std::endl;
    // std::cout<<info.root.arr[0].key<<std::endl;
    
    //std::cout<<"still";
    

    
    // std::cout<<"beginning insert: "<<info.relation.index<<std::endl;
   
    if(!fsm.has_root()){
    fsm.get_fsm(info.relation.index);
    std::cout<<"got fsm"<<std::endl;
    }
    
    // std::cout<<"Checking: "<<real<<std::endl;
    //std::cout<<"Got the FSM"<<std::endl;
    //THIS IS BASICALLY JUST THE B+ TREE INSERT IMPLEMENTATION, SO JUST REPLACE THIS WITH B+ TREE INSERT WHEN ITS DONE
    float key_of_interest{};
    uint32_t new_page_offset{};
    uint32_t new_low_p{};
    
    // std::cout<<"Checking: "<<leaf.page_id<<std::endl;
    if(fsm.has_space(info.leaf.page_id)==1){
        std::cout<<"Has space"<<std::endl;
        
        std::cout<<"INDEX: "<<info.index<<std::endl;
        std::vector<char>empty{};
        empty.resize(row_size);
        float index_t{};
        for(size_t i=0;i<5;i++){
            memcpy(&index_t,&info.leaf.data[i*row_size],4);
            std::cout<<i<<": "<<index_t<<" "<<i*row_size<<std::endl;
        }
        
         std::cout<<"pre-loop"<<std::endl;
        for(size_t i = num_rows-2;i >= info.index;i--){
            // std::cout<<i<<std::endl;
            memcpy(&info.leaf.data[(i+1)*row_size],&info.leaf.data[i*row_size],row_size);
            memcpy(&info.leaf.data[i*row_size],empty.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
            
            if(i == 0)
            break;
        }
        std::cout<<"post loop"<<std::endl;
        for(size_t i=0;i<4;i++){
            memcpy(&index_t,&info.leaf.data[i*row_size],4);
            std::cout<<i<<": "<<index_t<<" "<<i*row_size<<std::endl;
        }
        // for(size_t i=0;i<26;i++)
        //     std::cout<<i<<"b: "<<leaf.data[i].index<<std::endl;
        // std::cout<<"ROW: "<<row.check<<std::endl;
        // 
        memcpy(&info.leaf.data[info.index*row_size],row.data.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
        // std::cout<<"post insert"<<std::endl;
        // for(size_t i=0;i<26;i++)
        //     std::cout<<i<<": "<<leaf.data[i].index<<std::endl;
        fsm.set_space(info.leaf.page_id,1);
        //  std::cout<<"ATTENTION: "<<leaf.data[0].check<<leaf.data[1].check<<std::endl;
        float index{};
        memcpy(&index,&info.leaf.data[(num_rows-1)*row_size],4);
        if(index != 0){
        std::cout<<"1!"<<std::endl;
        fsm.set_space(info.leaf.page_id,2);
        }
        // std::cout<<"post index"<<std::endl;
         //write back
        //  std::cout<<"THIS: "<<info.offsets.size()<<std::endl;
        // 
        
        
       
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        
        fs.write(reinterpret_cast<char*>(&info.leaf),4096);
        std::cout<<"pre flush"<<std::endl;
       fsm.flush_fsm(0);
       fs.close();
    //    
        info.offsets.clear();
   
        std::cout<<"done"<<std::endl;
        return;
    }else if(fsm.has_space(info.leaf.page_id) != 1 && info.leaf.page_id != 0){
         //step 1: split info.leaf, get positon of new info.leaf.
        // std::cout<<"words: "<<info.offsets.size()<<std::endl;
        if(info.offsets.size()>=1){
        Curr_Node half;
        half.page_id = fsm.page();
        
        // if(half.page_id >=469)
        // std::cout<<"still "<<std::endl;
        // std::cout<<"PAGE: "<<half.page_id;
        new_page_offset = (half.page_id) * 4096+info.ind->ind_start;
        // std::cout<<"OFF: "<<new_page_offset<<std::endl;
    
        std::vector<char>empty{};
        empty.resize(row_size);

        for(size_t i = num_rows/2; i<num_rows;i++){
            memcpy(&half.data[(i-(num_rows/2))*row_size],&info.leaf.data[i*row_size],row_size);
            memcpy(&info.leaf.data[i*row_size],empty.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
            
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
            
            memcpy(&key_of_interest,&info.leaf.data[((num_rows/2)-1)*row_size],4);
            
            for(size_t i = num_rows/2; i > info.index;i--){
                memcpy(&info.leaf.data[i*row_size],&info.leaf.data[(i-1)*row_size],row_size);
            };
            memcpy(&info.leaf.data[info.index*row_size],row.data.data(),row_size);
            
        }else if(info.index > num_rows/2){
            
            memcpy(&key_of_interest,&info.leaf.data[info.index*row_size],4);
            
            // std::cout<<"Bruh: "<<key_of_interest<<std::endl;
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                memcpy(&half.data[i*row_size],&half.data[(i-1)*row_size],row_size);
            }
            memcpy(&half.data[(info.index -(num_rows/2))*row_size],row.data.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
        }else{
            key_of_interest = key;
            for(size_t i = num_rows/2;i > info.index - (num_rows/2);i--){
                memcpy(&info.leaf.data[i*row_size],&info.leaf.data[(i-1)*row_size],row_size);
            }
            memcpy(&half.data[(info.index -(num_rows/2))*row_size],row.data.data(),row_size);//FIXX////////////////////////////////////////////////////////////////////////////
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
//   std::cout<<"made it here: "<<info.offsets.size()<<info.root.page_id<<std::endl;
  if(info.offsets.size() >= 1){
    for(size_t i = info.offsets.size()-1; i >= 0; i--){
        std::cout<<"beginning deep"<<std::endl;
        //get parent node into memory
        // Syst_Root root;
        // fs.seekg(info.offsets.at(i));
        // fs.read(reinterpret_cast<char*>(&root),4096);
        // std::cout<<info.root.page_id<<" "<<fsm.has_space(info.root.page_id)<<std::endl;
        if(fsm.has_space(root_f.page_id)==1){
            // std::cout<<"space: "<<k_p.key<<" "<<k_p.pointer<<std::endl;
            // step 3: if parent has room, insert at appropriate location. 
            
            // std::cout<<"ROOT: "<<root_f.page_id<<std::endl;
            // std::cout<<root_f.arr[i].key<<": "<<root_f.arr[i].pointer<<std::endl;
            if(info.index_root >= 4096){
                // std::cout<<"space: "<<k_p.key<<" "<<k_p.pointer<<std::endl;
            // step 3: if parent has room, insert at appropriate location. 
            
            // std::cout<<"ROOT: "<<root_f.page_id<<std::endl;
            for(size_t i = 0; i < 511;i++){
                if(root_f.arr[i].key == key){
            // std::cout<<"equals: "<<i<<std::endl;
                info.index_root = i;
                break;
                } else if(i ==0 && key < root_f.arr[i].key){
            // std::cout<<root_f.page_id<<" "<<root_f.arr[0].key<<" "<<root_f.arr[0].pointer<<std::endl;
            // std::cout<<"lower"<<std::endl;
                info.index_root = i;
                break;

                } else if(root_f.arr[i].key > key && root_f.arr[i-1].key < key){
            // std::cout<<key<<" between: "<<root_f.arr[i-1].key<<" and "<<root_f.arr[i].key<<" at "<<i<<std::endl;
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
            // std::cout<<"word "<<root_f.page_id<<" "<<info.index_root<<std::endl;
            root_f.arr[info.index_root] = k_p;
            if(root_f.arr[510].key != 0){
                std::cout<<"2!"<<root_f.arr[510].key<<" "<<root_f.page_id<<std::endl;
            fsm.set_space(root_f.page_id,2);
            }
            fs.seekp(root_f.page_id*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&root_f),sizeof(root_f));
            // for(size_t i = 0; i<10;i++){
                // std::cout<<i<<": "<<root_f.arr[i].key<<std::endl;
            // }
            fsm.flush_fsm(0);
            // std::cout<<"flush"<<std::endl;
            info.offsets.clear();
            // std::cout<<"going: "<<info.index_root<<std::endl;
            info.index_root = 0;
            return;
        }else if(fsm.has_space(root_f.page_id)!=1 && i != 0){
            //If parent does not have room, split parent and get location of new parent.
            std::cout<<"splitting index: "<<root_f.page_id<<" "<<info.index_root<<" "<<info.offsets.size()<<std::endl;

            Syst_Root_f half_root;
            half_root.page_id = fsm.page();
            // std::cout<<"New page: "<<half_root.page_id<<std::endl;
            uint32_t offset_new_index = half_root.page_id*4096+info.ind->ind_start;
            float temp_koi{};
            

            //split
            Key_Pointer_f empty;
            if(info.index_root > 256){
            std::cout<<"more1"<<std::endl;
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
            std::cout<<"less1"<<std::endl;
            temp_koi = root_f.arr[255].key;
            half_root.bottom_p = root_f.arr[255].pointer;
            root_f.arr[255]=empty;
            for(size_t i = 256;i < 511;i++){
            half_root.arr[i-256] = root_f.arr[i];
            
            
            root_f.arr[i]=empty;
            }

            for(size_t i =256; i > info.index;i--){
                root_f.arr[i]=root_f.arr[i-1];
                // root_f.arr[i-1]=empty;
            }
            root_f.arr[info.index_root] = k_p;
        }else{
            std::cout<<"special1"<<std::endl;
            temp_koi = key;
            
            half_root.bottom_p = k_p.pointer;
            // root_f.arr[256]=empty;
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
            // std::cout<<"New Stuff: "<<temp_koi<<" "<<offset_new_index<<" "<<half_root.page_id<<" "<<half_root.bottom_p<<std::endl;
            k_p.key = temp_koi;
            k_p.pointer = offset_new_index;
            half_root.next_index = root_f.next_index;
            // for(size_t i = 0; i<256;i++)
            // std::cout<<i<<": "<<half_root.arr[i].key<<std::endl;
            // for(size_t i = 0; i < 256;i++)
            // std::cout<<i<<": "<<root_f.arr[i].key<<std::endl;
            // std::cout<<i<<" ATTENTION: "<<info.offsets.at(i)<<" "<<info.offsets.at(i-1)<<std::endl;
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
            
            // std::cout<<"DONEE"<<std::endl;
        }else if(fsm.has_space(root_f.page_id)!=1 && i == 0){
            std::cout<<"SPLTTING ROOT: "<<i<<" "<<info.offsets.size()<<std::endl;
            Key_Pointer_f empty;
            Syst_Root_f half_root;
            
            half_root.page_id = fsm.page();
            // std::cout<<"Half: "<<half_root.page_id<<std::endl;
        //split current root_f
        //if i > 255, the koi goes to i=256 else, i = 255
        

        
        
        fsm.set_space(half_root.page_id,1);

        std::cout<<"still"<<half_root.page_id<<std::endl;
        root_f.page_id = fsm.page();
        std::cout<<"Old root: "<<root_f.page_id<<std::endl;
        fsm.set_space(root_f.page_id,1);
        //get new root_f page and send koi and location of new "children" to new root_f for l & r pointers
        Syst_Root_f new_root;
        float temp_koi{};
        uint32_t temp_p{};



        std::cout<<"INDeX: "<<info.index_root<<std::endl;
        if(info.index_root > 256){
            std::cout<<"more"<<std::endl;
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
            std::cout<<"less"<<std::endl;
            temp_koi = root_f.arr[255].key;
            half_root.bottom_p = root_f.arr[255].pointer;
            root_f.arr[255]=empty;
            for(size_t i = 256;i < 511;i++){
            half_root.arr[i-256] = root_f.arr[i];
            
            
            root_f.arr[i]=empty;
            }
            // temp_koi = root_f.arr[255].key;
            for(size_t i =256; i > info.index;i--){
                root_f.arr[i]=root_f.arr[i-1];
            }
            root_f.arr[info.index_root] = k_p;
        }else{
            std::cout<<"special"<<std::endl;
            temp_koi = key;
            
            half_root.bottom_p = k_p.pointer;
            // root_f.arr[256]=empty;
            for(size_t i = 257;i < 511;i++){
            half_root.arr[i-257] = root_f.arr[i];
            
            
            root_f.arr[i]=empty;
        }
            for(size_t i= 256; i > info.index_root - 256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[info.index_root] = k_p;
            };
            for(size_t i = 0;i<257;i++){
            std::cout<<i<<": "<<root_f.arr[i].key<<std::endl;
        }
        for(size_t i = 0;i<257;i++){
            std::cout<<i<<": "<<half_root.arr[i].key<<std::endl;
        }
            k_p.key = temp_koi;
            //switch the current 0 index page and the root_f page  so the root_f is always at index 0
            k_p.pointer = half_root.page_id * 4096+info.ind->ind_start;
            std::cout<<"Pointer OI: "<<k_p.pointer<<std::endl;
            new_root.page_id = 0;
            new_root.bottom_p = root_f.page_id * 4096+info.ind->ind_start;
            std::cout<<"Bottom P: "<<new_root.bottom_p<<std::endl;
            // root_f.next_index = 0;
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
        
            std::cout<<"it worked? "<<new_root.bottom_p<<" "<<new_root.arr[0].pointer<<" "<<half_root.bottom_p<<" "<<root_f.bottom_p<<std::endl;
            info.offsets.clear();
            return;
        }; 
        // step 5: repeat until opening in index or at top level (root)
        std::cout<<"nowhere"<<std::endl;
    };
  }else{
    // std::cout<<"started split"<<std::endl;
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
        std::cout<<"KOI: "<<key_of_interest<<std::endl;
        //get new root page and send koi and location of new "children" to new root for l & r pointers
        
        
        
        
        new_root.arr[0] = {key_of_interest,8192+info.ind->ind_start};
        new_root.next_index=0;
        info.leaf.page_id = 1;
        half.page_id = 2;
        info.leaf.bottom_p = half.page_id*4096+info.ind->ind_start;
        std::cout<<"Info: "<<half.page_id<<" "<<info.leaf.page_id<<std::endl;
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
            fs.seekp(info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&new_root),sizeof(new_root));
            fs.seekp((info.leaf.page_id)*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&info.leaf),4096);
            fs.seekp((half.page_id)*4096+info.ind->ind_start);
            fs.write(reinterpret_cast<char*>(&half),4096);
        fs.close();
        // std::cout<<"even still"<<std::endl;
        info.index = 0;
        info.offsets.clear();
        // std::cout<<"clear?"<<std::endl;
        info.ind->ind_height = 1;
        obj->tree_ind.dirty = true;
        // std::cout<<"height?"<<std::endl;
        obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].num_pages++;
        obj->tree_rel.dirty = true;
        // std::cout<<"pre flush"<<std::endl;
        fsm.flush_fsm(0);
        obj->flush();
        std::cout<<"split"<<std::endl;
  };
  
// step 6: if need to split root, get new root page, send koi and locations of children to new root. save location of new root in specialized file with root locations of each index.
    // fsm.flush_fsm(std::string{"catalog_rel"});
    obj->tree_rel.info.rel.rows[obj->tree_rel.info.index].num_rows++;
    

};

void Bp_Tree::search_range(uint32_t key_first,uint32_t key_last,uint16_t num_rows){
    info.rows.clear();
    uint16_t index_last{num_rows};
    // std::cout<<"range "<<key<<std::endl;
    search(key_first,num_rows,info.relation.row_size);
    // std::cout<<"past search"<<std::endl;
    if(info.ind->ind_height > 0){
    //if height 
    std::fstream fs;
    //get first index
    
    // for(size_t i =0;i<num_rows;i++)
    // std::cout<<i<<": "<<calc_name(info.rel.rows[i].index)<<std::endl;
    if(key_first > key_last)
    return;
    uint32_t index{};
    Row row{};
    bool found = false;
    while(!found){
        // std::cout<<info.rel.page_id<<" "<<info.index<<std::endl;
    for(size_t i = info.index; i<num_rows;i++){
        // std::cout<<"a"<<calc_name(info.rel.rows[i+1].index)<<std::endl;
        memcpy(&index,&info.leaf.data[i*info.relation.row_size],4);
        if(index > key_last){
            index_last = i;
            // std::cout<<"here"<<std::endl;
            break;
        }
    };
    if(index_last < num_rows){
        // std::cout<<"found: "<<index_last<<std::endl;
        
        for(size_t i = info.index; i <= index_last;i++){
            memcpy(row.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&row.index,row.data.data(),4);
            info.rows.push_back(row);//FIX///////////////////////////////////
        }
        found = true;
    }else{
        for(size_t i = info.index;i<num_rows;i++){
            memcpy(row.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
        info.rows.push_back(row);
        
        if(row.index == 0)//FIX////////////////////////////////
        break;
        }
        if(info.leaf.bottom_p == 0)
        return;
        fs.seekg(info.leaf.bottom_p);
        fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        info.index = 0;
    };
    }
    //if the insert will not fit on that page 
    //get the next leaf page
    //see if it will fit on that page and keep all pages in memory
    //return index of first, page of first, index of last, page of last, everything you need
    }else{
        //if no height:
        // std::cout<<"no height"<<std::endl;
        Row row{};
        uint32_t index{};
        for(size_t i = info.index;i<num_rows;i++){
            // std::cout<<i<<": "<<calc_name(info.rel.rows[i].index)<<info.rel.rows[i].index<<calc_name(info.rel.rows[i+1].index)<<std::endl;
            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row.data.data(),&info.leaf.data[(i)*info.relation.row_size],info.relation.row_size);
            memcpy(&row.index,row.data.data(),4);
            if(index > key_last){
                // std::cout<<i<<": out"<<std::endl;
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
    // std::cout<<"range "<<key<<std::endl;
    search(key_first,num_rows,info.relation.row_size);
    // std::cout<<"past search"<<std::endl;
    if(info.ind->ind_height > 0){
    //if height 
    std::fstream fs;
    //get first index
    
    // for(size_t i =0;i<num_rows;i++)
    // std::cout<<i<<": "<<calc_name(info.rel.rows[i].index)<<std::endl;
    if(key_first > key_last)
    return;
    float index{};
    Row row{};
    row.data.resize(info.relation.row_size);
    bool found = false;
    while(!found){
        // std::cout<<info.rel.page_id<<" "<<info.index<<std::endl;
    for(size_t i = info.index; i<num_rows;i++){
        // std::cout<<"a"<<calc_name(info.rel.rows[i+1].index)<<std::endl;
        memcpy(&index,&info.leaf.data[i*info.relation.row_size],4);
        if(index > key_last){
            index_last = i;
            // std::cout<<"here"<<std::endl;
            break;
        }
    };
    if(index_last < num_rows){
        // std::cout<<"found: "<<index_last<<std::endl;
        
        for(size_t i = info.index; i <= index_last;i++){
            memcpy(row.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            // memcpy(&row.index,row.data.data(),4);
            info.rows.push_back(row);//FIX///////////////////////////////////
        }
        found = true;
    }else{
        for(size_t i = info.index;i<num_rows;i++){
            memcpy(row.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
        info.rows.push_back(row);
        
        if(row.index == 0)//FIX////////////////////////////////
        break;
        }
        if(info.leaf.bottom_p == 0)
        return;
        fs.seekg(info.leaf.bottom_p);
        fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        info.index = 0;
    };
    }
    //if the insert will not fit on that page 
    //get the next leaf page
    //see if it will fit on that page and keep all pages in memory
    //return index of first, page of first, index of last, page of last, everything you need
    }else{
        //if no height:
        // std::cout<<"no height"<<std::endl;
        Row row{};
        float index{};
        row.data.resize(info.relation.row_size);
        for(size_t i = info.index;i<num_rows;i++){
            // std::cout<<i<<": "<<calc_name(info.rel.rows[i].index)<<info.rel.rows[i].index<<calc_name(info.rel.rows[i+1].index)<<std::endl;
            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row.data.data(),&info.leaf.data[(i)*info.relation.row_size],info.relation.row_size);
            // memcpy(&row.index,row.data.data(),4);
            if(index > key_last){
                // std::cout<<i<<": out"<<std::endl;
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
    std::cout<<"searched"<<std::endl;
    std::fstream fs;
    bool found{};
    uint32_t index{};
    uint32_t index_i{};
    Row row_empty{};

    

    row_empty.data.resize(info.relation.row_size);
    // row_dump.data.resize(info.relation.row_size);
    std::cout<<"resized "<<row.data.size()<<std::endl;
    
    if(info.ind->ind_height > 0){

        for(size_t i = info.index; i < num_rows;i++){
            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);
            if(index_i != 0){
            std::cout<<"row pushed "<<index_i<<std::endl;
            // info.rows.push_back(row);
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
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        while(!found){
        
        

            // fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
            fs.seekg(info.leaf.bottom_p);
            fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));

            for(size_t i = 0; i< num_rows;i++){
                memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
                memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
                memcpy(&index_i,row_empty.data.data(),4);
                if(index_i != 0){
                std::cout<<"row pushed"<<std::endl;
                memcpy(&info.leaf.data[i*info.relation.row_size],row.data.data(),info.relation.row_size);
                
                }
                if(index > key_last || index == 0){
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
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        }


        
       
    
    }else{
        std::cout<<"no height"<<std::endl;
        
        // std::cout<<"assigned "<<info.index<<std::endl;
        for(size_t i = info.index; i < num_rows-1;i++){

            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            // std::cout<<"index copied "<<i*info.relation.row_size<<std::endl;
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);

            if(index_i != 0.0){
            // std::cout<<"row pushed "<<index_i<<" "<<i<<std::endl;
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
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        std::cout<<"should return"<<std::endl;
    }
    
    
};
void Bp_Tree::delete_range(float key_first,float key_last,uint16_t num_rows,Row row){
    search(key_first,num_rows,info.relation.row_size);
    std::cout<<"searched float"<<std::endl;
    std::fstream fs;
    bool found{};
    float index{};
    float index_i{};
    Row row_empty{};

    // Row row_dump{};
    
    
    

    row_empty.data.resize(info.relation.row_size);
    row.data.resize(info.relation.row_size);
    // row_dump.data.resize(info.relation.row_size);
    std::cout<<"resized "<<row_empty.data.size()<<std::endl;
    
    if(info.ind->ind_height > 0){

        for(size_t i = info.index; i < num_rows;i++){
            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);
            if(index_i != 0){
            std::cout<<"row pushed "<<index_i<<std::endl;
            // info.rows.push_back(row);
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
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        while(!found){
        
        

            // fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
            fs.seekg(info.leaf.bottom_p);
            fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));

            for(size_t i = 0; i< num_rows;i++){
                memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
                memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
                memcpy(&index_i,row_empty.data.data(),4);
                if(index_i != 0){
                std::cout<<"row pushed"<<std::endl;
                memcpy(&info.leaf.data[i*info.relation.row_size],row.data.data(),info.relation.row_size);
                
                }
                if(index > key_last || index == 0){
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
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        }


        
       
    
    }else{
        std::cout<<"no height"<<std::endl;
        
        std::cout<<"assigned "<<info.index<<std::endl;
        for(size_t i = info.index; i < num_rows-1;i++){

            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            std::cout<<"index copied "<<i*info.relation.row_size<<std::endl;
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);

            if(index_i != 0.0){
            std::cout<<"row pushed "<<index_i<<" "<<i<<std::endl;
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
        std::cout<<"out of loop"<<std::endl;
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        std::cout<<"should return"<<std::endl;
    }
    
};

void Bp_Tree::update_range(uint32_t key_first,uint32_t key_last,uint16_t num_rows,std::vector<uint16_t>positions,std::vector<char>types, Run* obj, std::vector<std::string>values){
    Row row{};
    search(key_first,num_rows,info.relation.row_size);
    std::cout<<"searched"<<std::endl;
    std::fstream fs;
    bool found{};
    uint32_t index{};
    uint32_t index_i{};
    Row row_empty{};

    

    row_empty.data.resize(info.relation.row_size);
    // row_dump.data.resize(info.relation.row_size);
    std::cout<<"resized "<<row.data.size()<<std::endl;
    
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
        edit_row(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        while(!found){
        
        

            // fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
            fs.seekg(info.leaf.bottom_p);
            fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));

            for(size_t i = 0; i< num_rows;i++){
                memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
                memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
                memcpy(&index_i,row_empty.data.data(),4);
                
                if(index > key_last || index == 0){
                    info.index_last = i;
                    break;
                } 
                

            }
        edit_row(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        }


        
       
    
    }else{
        std::cout<<"no height"<<std::endl;
        
        // std::cout<<"assigned "<<info.index<<std::endl;
        for(size_t i = info.index; i < num_rows-1;i++){

            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            // std::cout<<"index copied "<<i*info.relation.row_size<<std::endl;
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);

            
            if(index > key_last || index == 0){

                info.index_last = i;
                
                
                break;
            }
        }
        edit_row(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        std::cout<<"should return"<<std::endl;
    }
};

void Bp_Tree::update_range(float key_first,float key_last,uint16_t num_rows,std::vector<uint16_t>positions,std::vector<char>types, Run* obj, std::vector<std::string>values){
    Row row{};
    search(key_first,num_rows,info.relation.row_size);
    std::cout<<"searched"<<std::endl;
    std::fstream fs;
    bool found{};
    float index{};
    float index_i{};
    Row row_empty{};

    

    row_empty.data.resize(info.relation.row_size);
    // row_dump.data.resize(info.relation.row_size);
    std::cout<<"resized "<<row.data.size()<<std::endl;
    
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
        edit_row(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        while(!found){
        
        

            // fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
            fs.seekg(info.leaf.bottom_p);
            fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));

            for(size_t i = 0; i< num_rows;i++){
                memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
                memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
                memcpy(&index_i,row_empty.data.data(),4);
                
                if(index > key_last || index == 0.0){
                    info.index_last = i;
                    break;
                } 
                

            }
        edit_row(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        }


        
       
    
    }else{
        std::cout<<"no height"<<std::endl;
        
        // std::cout<<"assigned "<<info.index<<std::endl;
        for(size_t i = info.index; i < num_rows-1;i++){

            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            // std::cout<<"index copied "<<i*info.relation.row_size<<std::endl;
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);

            
            if(index > key_last || index == 0.0){

                info.index_last = i;
                
                
                break;
            }
        }
        edit_row(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj);
        fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        std::cout<<"should return "<<info.leaf.page_id<<info.ind->ind_start<<fs.tellp()<<std::endl;
        fs.close();
    }
}

void Bp_Tree::update_index_range(uint32_t key_first,uint32_t key_last,uint16_t num_rows,std::vector<uint16_t>positions,std::vector<char>types, Run* obj, std::vector<std::string>values){
    search(key_first,num_rows,info.relation.row_size);

    Row row{};
    search(key_first,num_rows,info.relation.row_size);
    std::cout<<"searched"<<std::endl;
    std::fstream fs;
    bool found{};
    uint32_t index{};
    uint32_t index_i{};
    Row row_empty{};
    Row row_dump{};
    

    row_empty.data.resize(info.relation.row_size);
    // row_dump.data.resize(info.relation.row_size);
    std::cout<<"resized "<<row.data.size()<<std::endl;
    
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
        info.rows = edit_rows(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj);
        delete_range(info.index,index_i,num_rows,row_dump);
        for(size_t i = 0; i< info.rows.size();i++){
            uint32_t ind{};
            memcpy(&ind,info.rows.at(i).data.data(),4);
            insert(ind,num_rows,info.relation.row_size,obj,info.rows.at(i));
        }
        // fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        // fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        // fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        while(!found){
        
        

            fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
            fs.seekg(info.leaf.bottom_p);
            fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));

            for(size_t i = 0; i< num_rows;i++){
                memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
                memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
                memcpy(&index_i,row_empty.data.data(),4);
                if(index > key_last || index == 0.0){
                    info.index_last = i;
                    break;
                } 
                

            }
        info.rows = edit_rows(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj);
        delete_range(info.index,index_i,num_rows,row_dump);
        for(size_t i = 0; i< info.rows.size();i++){
            uint32_t ind{};
            memcpy(&ind,info.rows.at(i).data.data(),4);
            insert(ind,num_rows,info.relation.row_size,obj,info.rows.at(i));
        }
        // fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        // fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        // fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        }


        
       
    
    }else{
        std::cout<<"no height"<<std::endl;
        
        // std::cout<<"assigned "<<info.index<<std::endl;
        for(size_t i = info.index; i < num_rows-1;i++){

            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            // std::cout<<"index copied "<<i*info.relation.row_size<<std::endl;
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);
            
            if(index > key_last || index == 0.0){

                info.index_last = i;
                
                
                break;
            }
        }
        info.rows = edit_rows(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj);
        delete_range(info.index,index_i,num_rows,row_dump);
        for(size_t i = 0; i< info.rows.size();i++){
            uint32_t ind{};
            memcpy(&ind,info.rows.at(i).data.data(),4);
            insert(ind,num_rows,info.relation.row_size,obj,info.rows.at(i));
        }
        // fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        // fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        // fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        // std::cout<<"should return "<<info.leaf.page_id<<info.ind->ind_start<<fs.tellp()<<std::endl;
        // fs.close();
    }
};

void Bp_Tree::update_index_range(float key_first,float key_last,uint16_t num_rows,std::vector<uint16_t>positions,std::vector<char>types, Run* obj, std::vector<std::string>values){
    // search(key_first,num_rows,info.relation.row_size);

    Row row{};
    std::cout<<info.relation.row_size<<std::endl;
    search(key_first,num_rows,info.relation.row_size);
    std::cout<<"searched "<<info.relation.row_size<<std::endl;
    std::fstream fs;
    bool found{};
    float index{};
    float index_i{};
    Row row_empty{};
    Row row_dump{};
    

    row_empty.data.resize(info.relation.row_size);
    // row_dump.data.resize(info.relation.row_size);
    std::cout<<"resized "<<row_empty.data.size()<<std::endl;
    
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
        info.rows = edit_rows(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj);
        delete_range(info.index,index_i,num_rows,row_dump);
        for(size_t i = 0; i< info.rows.size();i++){
            float ind{};
            memcpy(&ind,info.rows.at(i).data.data(),4);
            insert(ind,num_rows,info.relation.row_size,obj,info.rows.at(i));
        }
        // fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        // fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        // fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        while(!found){
        
        

            fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
            fs.seekg(info.leaf.bottom_p);
            fs.read(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));

            for(size_t i = 0; i< num_rows;i++){
                memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
                memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
                memcpy(&index_i,row_empty.data.data(),4);
                if(index > key_last || index == 0.0){
                    info.index_last = i;
                    break;
                } 
                

            }
        info.rows = edit_rows(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj);
        delete_range(key_first,key_last,num_rows,row_dump);
        for(size_t i = 0; i< info.rows.size();i++){
            float ind{};
            memcpy(&ind,info.rows.at(i).data.data(),4);
            insert(ind,num_rows,info.relation.row_size,obj,info.rows.at(i));
        }
        // fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        // fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        // fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        }


        
       
    
    }else{
        std::cout<<"no height"<<std::endl;
        
        std::cout<<"assigned "<<info.index<<std::endl;
        for(size_t i = info.index; i < num_rows-1;i++){

            memcpy(&index,&info.leaf.data[(i+1)*info.relation.row_size],4);
            // std::cout<<"index copied "<<i*info.relation.row_size<<std::endl;
            memcpy(row_empty.data.data(),&info.leaf.data[i*info.relation.row_size],info.relation.row_size);
            memcpy(&index_i,row_empty.data.data(),4);
            
            
            if(index > key_last || index == 0.0){

                info.index_last = i;
                
                
                break;
            }
        }
        info.rows = edit_rows(&info.leaf,positions,types,values,(info.index_last-info.index)+1,info.relation.row_size,obj);
        std::cout<<info.index_last<<" "<<info.index<<" "<<index_i<<std::endl;
        delete_range(info.index,index_i,num_rows,row_dump);
        for(size_t i = 0; i< info.rows.size();i++){
            
            float ind{};
            memcpy(&ind,info.rows.at(i).data.data(),4);
            insert(ind,num_rows,info.relation.row_size,obj,info.rows.at(i));
        }
        // fs.open(info.relation.rel_file,std::ios_base::binary|std::ios_base::in|std::ios_base::out);
        // fs.seekp(info.leaf.page_id*4096+info.ind->ind_start);
        // fs.write(reinterpret_cast<char*>(&info.leaf),sizeof(info.leaf));
        // std::cout<<"should return "<<info.leaf.page_id<<info.ind->ind_start<<fs.tellp()<<std::endl;
        // fs.close();
    }
}