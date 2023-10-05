#include "Syst_Catalog.h"
#include "Syst_Attr.h"
#include "Syst_Index.h"
#include "Syst_Rel.h"
#include "Syst_Root.h"
#include "../Disk_Space/FSM.h"

#include <fstream>
#include <vector>
#include <set>






void Syst_Catalog::create_catalog(std::string type){
    std::string name = {"catalog_"+type};
    std::ofstream fs;
    fs.open(name+".db",std::ios_base::binary);
    fs.close();
    FSM fsm;
    fsm.create_fsm(name);
    

}
uint16_t Syst_Catalog::calc_name(char* arr){
    uint16_t name{};
    for(size_t i = 0;i<64;i++)
    name += arr[i];
    
    return name;
}





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