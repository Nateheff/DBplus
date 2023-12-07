#include "Syst_Attr.h"


void Catalog_Attr::create_catalog(){
    
    std::string name = {"catalog_attr"};
    std::vector<Syst_Attr_Row>vec{};
    for(size_t i = 0;i<20;i++){
        Syst_Attr_Row empty{};
        vec.push_back(empty);
    }
    for(size_t i = 0; i<8;i++){
        strcpy(vec.at(i).index,"catalog_ind");
        vec.at(i).position = i+1;
    }
    //ind attributes
   
    strcpy(vec.at(0).attr_name,"index");
    vec.at(0).check = 64;
    vec.at(0).type = 's';
    
    strcpy(vec.at(1).attr_name,"ind_height");
    vec.at(1).check = 1;
    vec.at(1).type = 'i';

    strcpy(vec.at(2).attr_name,"key_type");
    vec.at(2).check = 1;
    vec.at(2).type = 'c';

    strcpy(vec.at(3).attr_name,"check");
    vec.at(3).check = 2;
    vec.at(3).type = 's';

    strcpy(vec.at(4).attr_name,"ind_min");
    vec.at(4).check = 4;
    vec.at(4).type = 'i';

    strcpy(vec.at(5).attr_name, "ind_max");
    vec.at(5).check = 4;
    vec.at(5).type = 'i';

    strcpy(vec.at(6).attr_name, "num_keys");
    vec.at(6).check = 4;
    vec.at(6).type = 'i';

    strcpy(vec.at(7).attr_name,"ind_start");
    vec.at(7).check = 4;
    vec.at(7).type = 'i';
    

    //rel attributes
    for(size_t i = 8; i<15;i++){
        strcpy(vec.at(i).index,"catalog_rel");
        vec.at(i).position = i-7;
    }

    strcpy(vec.at(8).attr_name,"index");
    vec.at(8).check = 64;
    vec.at(8).type = 's';

    strcpy(vec.at(9).attr_name,"rel_file");
    vec.at(9).check = 64;
    vec.at(9).type = 's';

    strcpy(vec.at(10).attr_name,"num_pages");
    vec.at(10).check = 2;
    vec.at(10).type = 's';

    strcpy(vec.at(11).attr_name,"num_rows");
    vec.at(11).check = 4;
    vec.at(11).type = 'i';

    strcpy(vec.at(12).attr_name,"check");
    vec.at(12).check = 2;
    vec.at(12).type = 's';

    strcpy(vec.at(13).attr_name,"kind");
    vec.at(13).check = 1;
    vec.at(13).type = 'c';

    strcpy(vec.at(14).attr_name,"row_size");
    vec.at(14).check = 2;
    vec.at(14).type = 's';
    //attr attributes
    for(size_t i = 15; i< 20;i++){
        strcpy(vec.at(i).index,"catalog_attr");
        vec.at(i).position = i-14;
    }
    strcpy(vec.at(15).attr_name,"index");
    vec.at(15).check = 64;
    vec.at(15).type = 's';

    strcpy(vec.at(16).attr_name,"attr_name");
    vec.at(16).check = 64;
    vec.at(16).type = 's';

    strcpy(vec.at(17).attr_name,"position");
    vec.at(17).check = 2;
    vec.at(17).type = 's';

    strcpy(vec.at(18).attr_name, "type");
    vec.at(18).check = 1;
    vec.at(18).type = 'c';

    strcpy(vec.at(19).attr_name,"check");
    vec.at(19).check = 1;
    vec.at(19).type = 'i';

    Syst_Attr root{};
    for(size_t i = 0;i<20;i++){
        
        root.rows[i] = vec.at(i);
        
    }
    std::fstream fs;
    fs.open(name+".db",std::ios_base::binary|std::ios_base::out);
    fs.write(reinterpret_cast<char*>(&root),sizeof(root));
    FSM fsm;
    fsm.create_fsm(name);
    return;
}
// typedef struct{
//     char index[63]={}; //rel_name
//     char attr_name[63]={};
//     uint16_t position{};
//     char type;
//     uint8_t check{}; //attr_length(bytes)
//     }Syst_Attr_Row;

/*
Attr_Info_Pack* Catalog_Attr::search_range_attr(uint16_t key,Attr_Info_Pack *pack,uint16_t num,bool has_height = 1){
    //get first index of key
    //get root
    
    pack->fsm->get_fsm(std::string{"catalog_attr"});
    
    pack->fs->open("catalog_attr.db",std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    //search through root
    
    Syst_Attr attr;
    
    //get pointer
   
    uint32_t offset{};
    
    if(has_height){

        Syst_Root root;
        pack->fs->read(reinterpret_cast<char*>(&root),4096);
        uint16_t index = root.next_index;

    while(index == 1){
    for(size_t i = 0; i < 511;i++){
        if(root.arr[i].key == key){

            pack->offsets.push_back(root.arr[i].pointer);
            offset = root.arr[i].pointer;
            pack->fs->seekg(offset);
            pack->fs->read(reinterpret_cast<char*>(&root),4096);
            index = root.next_index;
            
        } else if(root.arr[i].key > key && root.arr[i-1].key < key){
            offset = root.arr[i].pointer;
            pack->offsets.push_back(offset);
            pack->fs->seekg(offset);
            pack->fs->read(reinterpret_cast<char*>(&root),4096);
            index = root.next_index;
            
        }
    }
    };

    for(size_t i = 0; i < 511;i++){
        if(root.arr[i].key == key){

            offset = root.arr[i].pointer;
            pack->offsets.push_back(offset);
            pack->offsets.push_back(root.arr[i+1].pointer);
            pack->fs->seekg(offset);
            pack->fs->read(reinterpret_cast<char*>(pack->attr),4096);
            break;

        } else if(root.arr[i].key >= key && root.arr[i-1].key < key){
            offset = root.arr[i].pointer;
            pack->offsets.push_back(offset);
            pack->fs->seekg(offset);
            pack->fs->read(reinterpret_cast<char*>(pack->attr),4096);
            break;
            
        }
    }
    }else{
        pack->fs->read(reinterpret_cast<char*>(pack->attr),sizeof(attr));
        pack->attr->page_id = 0;
        
    };

    for(size_t i =0;i<31;i++){
        uint16_t name{};
        for(size_t j = 0; j<65;j++)
        name += pack->attr->rows[i].rel_name[j];

        if(key == name){
            
            pack->index = i;
            pack->pg_ids.push_back(pack->attr->page_id);
            pack->index_first = i;
            
            break;
            // return &pack;
        }else if(key < name || (i == 30 && key > name)||pack->attr->rows[i].attr_len == 0){
            
            pack->index = i;
            pack->index_first = i;
            pack->pg_ids.push_back(pack->attr->page_id);
            
            break;
        }    
    }
    if((pack->index + num) > 30){

        for(size_t i = pack->index;i < 31;i++)
        pack->data.push_back(pack->attr->rows[i]);

        uint8_t num_pages = (num-pack->index)/30;
        uint8_t num_last = num % 30; 

        for(size_t i = 0; i >= num_pages;i++){
        pack->fs->seekp(pack->attr->next_p);
        pack->fs->read(reinterpret_cast<char*>(pack->attr),4096);
        pack->pg_ids.push_back(pack->attr->page_id);
        if(i != num_pages){
            for(size_t i = 0; i< 31;i++)
            pack->data.push_back(pack->attr->rows[i]);
            
        }else{
            for(size_t i = 0; i<num_last;i++){
                pack->data.push_back(pack->attr->rows[i]);
            }
            pack->index_last = num_last;
            
        }

        }

    }else{
        for(size_t i = pack->index;i <= pack->index+num;i++)
        pack->data.push_back(pack->attr->rows[i]);
    }
    
    return pack;
    
};
void Catalog_Attr::remove_range_atrr(uint16_t key, uint16_t num,Attr_Info_Pack* pack){
    //search to get pages and indexes
    pack = search_range_attr(key,pack,num);
    FSM fsm;
    std::string name{"catalog_attr"};
    fsm.get_fsm(name);
    //set page(s) space(s) (fsm)
    Syst_Attr_Row empty;
    pack->fs->seekp((pack->pg_ids.at(0)-1)*4096);
    pack->fs->read(reinterpret_cast<char*>(pack->attr),4096);
    

    for(size_t i = pack->index;((i<pack->index + num)&&(i < 31));i++){
        pack->attr->rows[i] = empty;
    }
    fsm.set_space(pack->attr->page_id,1);
    for(size_t i = 1;i<pack->pg_ids.size() -1;i++){
        pack->fs->seekg(pack->pg_ids.at(i));
        pack->fs->read(reinterpret_cast<char*>(pack->attr),4096);
        if(i == pack->pg_ids.size()-1){
            for(size_t i =0;i<pack->index_last -1;i++){
                pack->attr->rows[i] = empty;
            }
            fsm.set_space(pack->attr->page_id,1);
        }else{
            for(size_t i = 0;i<31;i++){
                pack->attr->rows[i] = empty;
            }
            fsm.set_space(pack->attr->page_id,2);
        }
    }
    //set space(s) to empty
};
void Catalog_Attr::insert_range_attr(uint16_t key,std::vector<Syst_Attr_Row>rows,Attr_Info_Pack* pack){
    pack = search_range_attr(key,pack,rows.size());
    while(rows.size() > 0){
    for(size_t i = 0;i<rows.size();i++){
            uint16_t final_i{};
        while(pack->fsm->has_space(pack->attr->page_id,0)){

            for(size_t i = 31;i>pack->index_first;i--){
                pack->attr->rows[i] = pack->attr->rows[i-1]; 
            }
            if(pack->attr->rows[30].attr_len != 0){
                pack->fsm->set_space(pack->attr->page_id,0);
            }
         pack->attr->rows[pack->index_first] = rows.at(i);
                final_i = i;
        };
        rows.erase(rows.begin(),rows.begin() + final_i);
        if(rows.size()==0)
        return;

        break;
    };
    Key_Pointer k_p{};
    //find index of key
    for(size_t i =0;i<31;i++){
            uint16_t name{};
            for(size_t j = 0; j<65;j++)
                name += pack->attr->rows[i].rel_name[j];

            if(key == name){
                pack->index = i;
                break;
            } 
            if(key < name){
            pack->index = i;
            break;  
            }
            if(key > name && i == 30)
            pack->index = 30;
            
        };
    //split
    Syst_Attr new_attr;
    
    new_attr.page_id = pack->fsm->page();
    Syst_Attr_Row empty;
    for(size_t i = 15;i<31;i++){
        new_attr.rows[i-15] = pack->attr->rows[i];
        pack->attr->rows[i]=empty;//set rows 16-30 to empty as they are now in the new leaf
    }
    pack->fsm->set_space(new_attr.page_id,1);
    pack->fsm->set_space(pack->attr->page_id,1);
    new_attr.next_p = pack->attr->next_p;
    pack->attr->next_p = (new_attr.page_id -1)*4096;
    if(pack->index < 15){
        for(size_t i = 16;i > (pack->index);i--){
            pack->attr->rows[i]=pack->attr->rows[i-1]; 
        }
        pack->attr->rows[pack->index] = rows.at(0);
        rows.erase(rows.begin());
        k_p.key = calc_name(new_attr.rows[0].rel_name);
        k_p.pointer = (new_attr.page_id -1)*4096;
    }else if(pack->index >= 15){
        for(size_t i = 16;i > (pack->index-15);i--){
            new_attr.rows[i]=new_attr.rows[i-1]; 
        }
        new_attr.rows[pack->index-15] = rows.at(0);
        rows.erase(rows.begin());
        k_p.key = calc_name(new_attr.rows[0].rel_name);
        k_p.pointer = (new_attr.page_id -1)*4096;
    };
    uint32_t new_low_p{};

    for(size_t i = pack->offsets.size()-2; i >= 0; i--){
        //get parent node into memory
        Syst_Root root;
        pack->fs->seekg(pack->offsets.at(i));
        pack->fs->read(reinterpret_cast<char*>(&root),4096);

        if(pack->fsm->has_space(root.page_id,0)){
            // step 3: if parent has room, insert at appropriate location. 

            for(size_t i =0; i<511;i++){
                if(k_p.key < root.arr[i].key){
                    pack->index = i;
                    break;
                }
                if(root.arr[i].key == 0){
                    pack->index = i;
                    break;
                }
            };

            for(size_t i = 510;i > pack->index;i--)
            root.arr[i] = root.arr[i-1];

            root.arr[pack->index] = k_p;
            if(root.arr[510].key != 0)
            pack->fsm->set_space(root.page_id,0);
            pack->fs->seekp(pack->offsets.at(i));
            pack->fs->write(reinterpret_cast<char*>(&root),4096);
            return;
        }else if(!pack->fsm->has_space(root.page_id,0) && i != 0){
            //If parent does not have room, split parent and get location of new parent.
            
            Syst_Root half_root;
            half_root.page_id = pack->fsm->page();
            uint32_t offset_new_index = (half_root.page_id -1 )*4096;
            uint16_t temp_koi{};
            

            for(size_t i = 0; i< 511;i++){
                if(root.arr[i].key > k_p.key){
                pack->index = i;
                break;
                };

                if(i == 510 && root.arr[i].key < k_p.key){
                pack->index = 510;
                break;
                };
            }

            //split
            Key_Pointer empty;
            if(pack->index > 256){
            for(size_t i = 257; i< 511;i++){
                half_root.arr[i-257]=root.arr[i];
                root.arr[i]=empty;
            }
            temp_koi = root.arr[256].key;
            new_low_p = root.arr[256].pointer;
            half_root.bottom_p = new_low_p;
            root.arr[256] = {0,0};
            for(size_t i= 257; i > pack->index-257;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[pack->index] = k_p;
            }else if(pack->index< 256){

            for(size_t i = 256; i< 511;i++){
                half_root.arr[i-256]=root.arr[i];
                root.arr[i]=empty;
            }

            temp_koi = root.arr[255].key;
            new_low_p = root.arr[255].pointer;
            half_root.bottom_p = new_low_p;
            root.arr[255]={0,0};
            for(size_t i =255; i > pack->index-255;i--){
                root.arr[i]=root.arr[i-1];
            }
            root.arr[pack->index] = k_p;
            }else{
            for(size_t i = 256; i < 511;i++){
                half_root.arr[i-256] = root.arr[i];
                root.arr[i]=empty;
            }
            temp_koi = key;
            new_low_p = k_p.pointer;
            half_root.bottom_p = new_low_p;
            for(size_t i= 256; i > pack->index-256;i--){
                half_root.arr[i] = half_root.arr[i-1];
            }
            half_root.arr[pack->index] = k_p;
            };
            // step 4: send new KOI/position of new index node to the parent node and if room, insert at appropriate location.

            k_p.key = temp_koi;
            k_p.pointer = offset_new_index;

        }
    };
    };
};
*/