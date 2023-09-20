#include "Syst_Attr.h"
#include "Syst_Index.h"
#include "Syst_Rel.h"
#include "Syst_Root.h"
#include "../Disk_Space/FSM.h"

#include <fstream>
#include <vector>

typedef struct {
    uint16_t index{};
    System_Rel_Row data;
    Syst_Rel* rel;
    std::fstream* fs;
    std::vector<uint32_t> offsets;

}Info_Pack;

void create_catalog(std::string type){
    std::string name = {"catalog_"+type};
    std::fstream fs;
    fs.open(name+".db",std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    FSM fsm;
    fsm.create_fsm(name+"_fsm.db");

}


Info_Pack* search_rel(uint16_t key,bool has_height=1){
    //get root
    std::fstream fs;
    fs.open("catalog.db",std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    //search through root
    
    Syst_Rel rel;
    
    //get pointer
    Info_Pack pack;
    uint32_t offset{};
    
    if(has_height){

        Syst_Root root;
        fs.read(reinterpret_cast<char*>(&root),4096);
        uint16_t index = root.next_index;

    while(index == 1){
    for(size_t i = 0; i < 511;i++){
        if(root.arr[i].key == key){

            pack.offsets.push_back(root.arr[i].pointer);
            offset = root.arr[i].pointer;
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&root),4096);
            index = root.next_index;

        } else if(root.arr[i].key > key && root.arr[i-1].key < key){
            offset = root.arr[i].pointer;
            pack.offsets.push_back(offset);
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&root),4096);
            index = root.next_index;
        }
    }
    };

    for(size_t i = 0; i < 511;i++){
        if(root.arr[i].key == key){

            offset = root.arr[i].pointer;
            pack.offsets.push_back(offset);
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&rel),4096);
            

        } else if(root.arr[i].key > key && root.arr[i-1].key < key){
            offset = root.arr[i].pointer;
            pack.offsets.push_back(offset);
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&rel),4096);
            
        }
    }
    }else{
        fs.read(reinterpret_cast<char*>(&rel),sizeof(rel));
        rel.page_id = 1;
    };

    for(size_t i =0;i<27;i++){
        uint16_t name{};
        for(size_t j = 0; j<65;j++)
        name += rel.rows[i].rel_name[j];

        if(key == name){
            
            pack.index = i;
            pack.data = rel.rows[i];
            pack.rel = &rel;
            pack.fs = &fs;
            
            return &pack;
        };

                
    }

    
    pack.index = 0;
    pack.rel = &rel;
    pack.fs = &fs;
    
   

    };
void remove_rel(uint16_t key){
    //search like you did in search
    Info_Pack* pack = search_rel(key);
    //once you have the correct page and relation row, delete the row from the array of relation rows. Update the fsm and any other things you need to telling them that space is open. maybe try to move all the rows "above" the one you delete down to have the free space at the end which will make free space easier to track
    System_Rel_Row empty;
    pack->rel->rows[pack->index] = empty;
    for(size_t i = pack->index;i<=25;i++){
        pack->rel->rows[i] = pack->rel->rows[i+1];
    };
    pack->fs->seekp(pack->offsets.at(pack->offsets.size()-1));
    pack->fs->write(reinterpret_cast<char*>(pack->rel),4096);
    pack->fs->close();
    FSM fsm;
    std::string name{"catalog_rel"};
    fsm.get_fsm(name,fsm.access_data());
    fsm.set_space(pack->rel->page_id,1);
    fsm.flush_fsm(name);

};

uint16_t calc_name(char* arr){
    uint16_t name{};
    for(size_t i = 0;i<65;i++)
    name += arr[i];

    return name;
}

void insert_rel(uint16_t key, System_Rel_Row row){
//search normally
    Info_Pack* pack = search_rel(key);
//once you have the page of where the row with the key would fit, see if there's space via the fsm and if there is, move all rows "greater" than it up 1 row space and put the new row in the space created at the correct place. If there's not room, split, and do the b+ tree thing. this will take some effort to figure out how to do.
    FSM fsm;
    std::string name{"catalog_rel"};
    fsm.get_fsm(name,fsm.access_data());

    //THIS IS BASICALLY JUST THE B+ TREE INSERT IMPLEMENTATION, SO JUST REPLACE THIS WITH B+ TREE INSERT WHEN ITS DONE
    uint16_t key_of_interest{};
    uint32_t new_page_offset{};
    if(fsm.has_space(pack->rel->page_id)){

        for(size_t i =0;i<27;i++){
            uint16_t name = calc_name(pack->rel->rows[i].rel_name);
            // for(size_t j = 0; j<65;j++)
            //     name += pack->rel->rows[i].rel_name[j];

            
            if(key < name || pack->rel->page_id == 0){
            pack->index = i;
            break;  
            }

        };
        

        for(size_t i = 25;i>=26-pack->index;i--){
            pack->rel->rows[i+1] = pack->rel->rows[i];
        }

        pack->rel->rows[pack->index] = row;
         
        if(pack->rel->rows[25].num_attrs != 0)
        fsm.set_space(pack->rel->page_id,0);
         //write back
         
        pack->fs->seekp(pack->offsets.at(pack->offsets.size()-1));
        pack->fs->write(reinterpret_cast<char*>(pack->rel),4096);
        return;
    }else{
         //step 1: split leaf, get positon of new leaf.
        fsm.calc_free();
        Syst_Rel half;
        half.page_id = fsm.page();
        new_page_offset = (half.page_id - 1) * 4096;

        for(size_t i =0;i<27;i++){
            uint16_t name{};
            for(size_t j = 0; j<65;j++)
                name += pack->rel->rows[i].rel_name[j];
            
            

            if(key == name){
                pack->index = i;
                break;
            } 
            if(key < name){
            pack->index = i;
            break;  
            }
            if(key > name && i == 26)
            pack->index = 26;
            
        };

        

        for(size_t i = 13; i<27;i++){
            half.rows[i-13]=pack->rel->rows[i];
        }

        //make room and insert new row into proper leaf and get upper median key to send to parent node.

        if(pack->index < 13){
            key_of_interest = calc_name(pack->rel->rows[12].rel_name);
            for(size_t i = 13; i > pack->index;i--){
                pack->rel->rows[i] = pack->rel->rows[i-1];
            };
            pack->rel->rows[pack->index] = row;

        }else if(pack->index > 13){
            key_of_interest = calc_name(pack->rel->rows[13].rel_name);
            for(size_t i = 13;i > pack->index - 13;i--){
                half.rows[i] = half.rows[i-1];
            }
            half.rows[pack->index -13 ] = row;
        }else
            key_of_interest = key;
            for(size_t i = 13;i > pack->index - 13;i--){
                half.rows[i] = half.rows[i-1];
            }
            half.rows[pack->index -13] = row;
        fsm.set_space(half.page_id,1);
        fsm.set_space(pack->rel->page_id,1);
    };
    // step 2: send new KOI/position of new to parent node.
    Key_Pointer k_p{key_of_interest,new_page_offset};
  
    for(size_t i = pack->offsets.size()-2; i >= 0; i--){
        //get parent node into memory
        Syst_Root root;
        pack->fs->seekg(pack->offsets.at(i));
        pack->fs->read(reinterpret_cast<char*>(&root),4096);

        if(fsm.has_space(root.page_id)){
            // step 3: if parent has room, insert at appropriate location. 

            for(size_t i =0; i<510;i++){
                if(key_of_interest < root.arr[i].key){
                    pack->index = i;
                    break;
                }
                if(root.arr[i].key == 0){
                    pack->index = i;
                    break;
                }
            };

            for(size_t i = 511;i > pack->index;i--)
            root.arr[i] = root.arr[i-1];

            root.arr[pack->index] = k_p;
            if(root.arr[511].key != 0)
            fsm.set_space(root.page_id,0);
            pack->fs->seekp(pack->offsets.at(i));
            pack->fs->write(reinterpret_cast<char*>(&root),4096);
            return;
        }else if(!fsm.has_space(root.page_id) && i != 0){
            //If parent does not have room, split parent and get location of new parent.
            fsm.calc_free();
            Syst_Root half_root;
            half_root.page_id = fsm.page();
            uint32_t offset_new_index = (half_root.page_id -1 )*4096;
            uint16_t temp_koi{};

            for(size_t i = 0; i< 512;i++){
                if(root.arr[i].key > key_of_interest){
                pack->index = i;
                break;
                };

                if(i == 511 && root.arr[i].key < key_of_interest){
                pack->index = 511;
                break;
                };
            }
            //split
            for(size_t i = 256; i< 512;i++){
                half_root.arr[i-256]=root.arr[i];
            }

            if(pack->index > 256){
            temp_koi = half_root.arr[0].key;
            for(size_t i= 256; i > pack->index - 256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[pack->index] = k_p;
            }else if(pack->index< 256){
            temp_koi = root.arr[255].key;
            for(size_t i =256; i > pack->index;i--){
                root.arr[i]=root.arr[i-1];
            }
            root.arr[pack->index] = k_p;
            }else{
            temp_koi = key;
            for(size_t i= 256; i > pack->index - 256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[pack->index] = k_p;
            };
            // step 4: send new KOI/position of new index node to the parent node and if room, insert at appropriate location.

            k_p.key = temp_koi;
            k_p.pointer = offset_new_index;

        }else if(!fsm.has_space(root.page_id) && i == 0){
            Syst_Root half_root;
            fsm.calc_free();
            half_root.page_id = fsm.page();
        //split current root
        for(size_t i = 256;i <= 511;i++){
            half_root.arr[i-256] = root.arr[i];
        }
        fsm.set_space(half_root.page_id,1);

        fsm.calc_free();
        root.page_id = fsm.page();
        fsm.set_space(root.page_id,1);
        //get new root page and send koi and location of new "children" to new root for l & r pointers
        Syst_Root new_root;
        uint16_t temp_koi{};
        uint32_t temp_p{};

        for(size_t i = 0;i<512;i++){
            if(root.arr[i].key > key){
            pack->index = i;
            break;
            };

            if(i==511&&root.arr[i].key < key){
                pack->index = 511;
                break;
            }

        }

        if(pack->index > 256){
            temp_koi = half_root.arr[0].key;
            for(size_t i= 256; i > pack->index - 256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[pack->index] = k_p;
            }else if(pack->index< 256){
            temp_koi = root.arr[255].key;
            for(size_t i =256; i > pack->index;i--){
                root.arr[i]=root.arr[i-1];
            }
            root.arr[pack->index] = k_p;
            }else{
            temp_koi = key;
            for(size_t i= 256; i > pack->index - 256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[pack->index] = k_p;
            };
            //switch the current 0 index page and the root page  so the root is always at index 0
            k_p.pointer = half_root.page_id;
            new_root.page_id = 0;
            new_root.bottom_p = (root.page_id-1) * 4096;
            new_root.next_index = 1;
            new_root.arr[0]=k_p;
            fsm.set_space(0,1);
            pack->fs->seekp(0);
            pack->fs->write(reinterpret_cast<char*>(&new_root),4096);
            pack->fs->seekp((half_root.page_id-1)*4096);
            pack->fs->write(reinterpret_cast<char*>(&half_root),4096);
            pack->fs->seekg((root.page_id-1)*4096);
            pack->fs->write(reinterpret_cast<char*>(&root),4096);
            
        }; 
        // step 5: repeat until opening in index or at top level (root)
    };
// step 6: if need to split root, get new root page, send koi and locations of children to new root. save location of new root in specialized file with root locations of each index.

};
void search_range_attr(uint16_t key,uint16_t num){

};
void remove_range_atrr(uint16_t key, uint16_t num){};
void insert_range_attr(uint16_t key, uint16_t num){};

/*
    if(fsm.has_space(pack->rel->page_id)){

        for(size_t i =0;i<27;i++){
            uint16_t name{};
            for(size_t j = 0; j<65;j++)
                name += pack->rel->rows[i].rel_name[j];

            
            if(key < name || pack->rel->page_id == 0){
            pack->index = i;
            break;  
            }

        };
        

        for(size_t i = 25;i>=26-pack->index;i--){
            pack->rel->rows[i+1] = pack->rel->rows[i];
        }

        pack->rel->rows[pack->index] = row;
         
        if(pack->rel->page_id != 0)
        fsm.set_space(pack->rel->page_id,0);
         //write back
         
        pack->fs->seekp(pack->offsets.at(pack->offsets.size()-1));
        pack->fs->write(reinterpret_cast<char*>(pack->rel),4096);
    }else{
        //split current node pushing half to new node and keeping half
        Syst_Rel half;
        for(size_t i =0;i<27;i++){
            uint16_t name{};
            for(size_t j = 0; j<65;j++)
                name += pack->rel->rows[i].rel_name[j];
            if(i == 13)
                key_of_interest = name;
            if(key == name){
                pack->index = i;
                break;
            } 
            if(key < name){
            pack->index = i;
            break;  
            }
        };
         
        for(size_t i = 13; i<27;i++)
        half.rows[i-13]=pack->rel->rows[i];

        //insert 
        if(pack->index < 13){
        for(size_t i = 25;i>=26-pack->index;i--)
            pack->rel->rows[i+1] = pack->rel->rows[i];
            pack->rel->rows[pack->index] = row;
        }else{
            for(size_t i = 25;i>=26-pack->index;i--)
            half.rows[i+1] = half.rows[i];
            half.rows[(pack->index)] = row;
        }


        //save to fsm new page info and change old page info
        fsm.calc_free();
        half.page_id = fsm.page();
        fsm.set_space(half.page_id,1);
        fsm.set_space(pack->rel->page_id,1);
        
        //go to parent node
        for(size_t i= pack->offsets.size()-2; i>=0;i--){
            pack->fs->seekg(pack->offsets.at(i));
            Syst_Root root;
            pack->fs->read(reinterpret_cast<char*>(&root),sizeof(root));

            //see if the parent has room
            if(fsm.has_space(root.page_id)){
                for(size_t i = 0; i<511;i++){
                    if(root.arr[i].key > key_of_interest){
                        pack->index = i;
                        break;
                    }
                }
                for(size_t i = 510;i >= pack->index;i--){
                    root.arr[i].pointer += 4096;
                    root.arr[i+1]=root.arr[i];
                }
                Key_Pointer k_p;
                k_p.key = key_of_interest;
                k_p.pointer=half.page_id * 4096;
                if(root.arr[510].key != 0)
                fsm.set_space(root.page_id,0);
                break;
            } else{
                for(size_t i = 0; i < 511;i++){
                    if(root.arr[i].key > key_of_interest)
                    pack->index = i;
                    break;
                }
                for(size_t i = pack->index;i<511;i++){
                    root.arr[i].pointer += 4096;
                }
            Syst_Root half_root;
            for(size_t i = 256; i<511;i++){
                half_root.arr[i-256] = root.arr[i];
                half_root.arr[i-256].pointer += 4096;
            }
            if(pack->index < 256){
                for(size_t i = 256;i>=511-pack->index;i--)
                    root.arr[i+1] = root.arr[i];
                root.arr[pack->index] = {key_of_interest,1};
            }else{
                for(size_t i = 256;i>=256-pack->index;i--)
                    half_root.arr[i+1] = half_root.arr[i];
                half_root.arr[(pack->index)] = {key_of_interest,1};
            }

            }
            
            //if not, split again, but you have to change the key pointer values

            */