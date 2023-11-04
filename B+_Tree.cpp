#include "B+_Tree.h"
void search(uint16_t key,uint16_t num_rows, uint16_t row_size, char ind_type, Run* obj){
    std::cout<<"started "<<num_rows<<" "<<row_size<<" "<<ind_type<<std::endl;
    // fs.clear();
    // std::cout<<"started"<<std::endl;
    char arr[row_size] = {};

    System_Rel_Row relation = obj->tree_rel.info.rel.rows[obj->tree_rel.info.index];
    Syst_Index_Row ind = obj->tree_ind.info.rel.rows[obj->tree_ind.info.index];

    Syst_Root root{};
    Row row{};
    Curr_Node leaf;
    Row data[4087/sizeof(row)];
    std::vector<uint32_t>offsets;
    uint16_t index_root{};
    uint16_t index{};

    std::cout<<sizeof(row)<<std::endl;
    row.data=arr;
    std::cout<<sizeof(row)<<std::endl;
    
    
    
    std::cout<<sizeof(data)<<std::endl;
    std::fstream fs;
    
    std::cout<<"null "<<fs.is_open()<<std::endl;
    
   
    fs.open(relation.rel_file,std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    std::cout<<"open "<<relation.rel_file<<fs.is_open()<<std::endl;
    //search through root
    
    
    
    // std::cout<<fs.is_open()<<std::endl;
    //get pointer
    
    uint32_t offset{};
    
    if(ind.ind_height > 0){
        
        std::cout<<"height"<<std::endl;
        fs.seekg(0);
        fs.read(reinterpret_cast<char*>(&root),sizeof(root));
        
        uint16_t index = root.next_index;
        offsets.push_back(0);
        // std::cout<<"Root: "<<root.page_id<<" "<<root.arr[0].key<<" "<<(int)root.next_index<<std::endl;
        // std::cout<<"Bottom: "<<root.bottom_p<<std::endl;
    // for(size_t i = 0;i<15;i++)
    // std::cout<<i<<": "<<"Key: "<<root.arr[i].key<<" Pointer: "<<root.arr[i].pointer<<std::endl;
    
    while(index == 1){
       
        // std::cout<<"HERE "<<index<<std::endl;
    for(size_t i = 0; i < 511;i++){
        if(root.arr[0].key > key){
            std::cout<<"3"<<std::endl;
            offset = root.bottom_p;
            offsets.push_back(offset);
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&root),sizeof(root));
            
            index = root.next_index;
            
            break;
        } else if(root.arr[i].key > key && root.arr[i-1].key < key){
            // std::cout<<"2"<<std::endl;
            offset = root.arr[i].pointer;
            offsets.push_back(offset);
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&root),sizeof(root));
            
            index = root.next_index;
            
            break;
        } else if(root.arr[i].key == key){
            // std::cout<<"1: "<<i<<std::endl;
            
            offsets.push_back(root.arr[i].pointer);
            offset = root.arr[i].pointer;
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&root),sizeof(root));
            
            index = root.next_index;
                     
            break;

        } else if(root.arr[i].key < key && root.arr[i+1].pointer == 0){
            // std::cout<<"4"<<std::endl;
            offsets.push_back(root.arr[i].pointer);

            offset = root.arr[i].pointer;
            // std::cout<<"offseT: "<<offset<<" "<<root.arr[i].key<<std::endl;
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&root),sizeof(root));
            
            // std::cout<<"RooT: "<<root.page_id<<" "<<(int)root.next_index<<" "<<fs.gcount()<<std::endl;
            index = root.next_index;
            
            break;
        }
       
    }
    // std::cout<<"next_index: "<<index<<" root: "<<root.page_id<<std::endl;
    };
    // std::cout<<"step 1: "<<offsets.size()<<std::endl;
    // std::cout<<"Index ID: "<<root.page_id<<std::endl;
    for(size_t i = 0; i < 511;i++){
        if(root.arr[i].key == key){
            // std::cout<<"equals: "<<i<<std::endl;
            index_root = i;
            offset = root.arr[i].pointer;
            
            fs.seekg(offset);
            // std::cout<<"offset: "<<offset<<std::endl;
            fs.read(reinterpret_cast<char*>(&leaf),sizeof(leaf));
            
            break;
            

        } else if(i ==0 && key < root.arr[i].key){
            // std::cout<<root.page_id<<" "<<root.arr[0].key<<" "<<root.arr[0].pointer<<std::endl;
            // std::cout<<"lower"<<std::endl;
            index_root = i;
            offset = root.bottom_p;
            
            fs.seekg(offset);
            // std::cout<<"offset: "<<offset<<std::endl;
            fs.read(reinterpret_cast<char*>(&leaf),sizeof(leaf));
            
            break;

        } else if(root.arr[i].key > key && root.arr[i-1].key < key){
            // std::cout<<key<<" between: "<<root.arr[i-1].key<<" and "<<root.arr[i].key<<" at "<<i<<std::endl;
            index_root = i;
            offset = root.arr[i-1].pointer;
            // std::cout<<"offset: "<<offset<<std::endl;
            
            
            fs.seekg(offset);
            fs.read(reinterpret_cast<char*>(&leaf),sizeof(leaf));
            
            // std::cout<<info.rel.page_id<<std::endl;
            // std::cout<<root.arr[i].key<<std::endl;
            break;
        }else if(root.arr[i].key < key && root.arr[i+1].pointer == 0){
            index_root = i+1;
            // std::cout<<i<<"larger than: "<<root.arr[i].key<<std::endl;
            offset = root.arr[i].pointer;
            
            
            fs.seekg(offset);
            
            fs.read(reinterpret_cast<char*>(&leaf),sizeof(leaf));
            
            
            break;
        }
        
    }
    // std::cout<<"step 2: "<<offsets.size()<<std::endl;
    // std::cout<<"Rel: "<<info.rel.page_id<<" "<<info.rel.is_index<<std::endl;
    
    }else{
        std::cout<<"No height "<<" "<<fs.tellg()<<std::endl;
        
        fs.seekg(0);
        std::cout<<"pre "<<fs.fail()<<std::endl;
        fs.read(reinterpret_cast<char*>(&leaf),sizeof(leaf));
        std::cout<<"post "<<fs.gcount()<<" "<<sizeof(leaf)<<std::endl;
        leaf.page_id = 0;

    };
    
    std::cout<<"got the rel"<<leaf.page_id<<" "<<leaf.bottom_p<<" "<<leaf.is_index<<std::endl;
    for(size_t i =0;i<num_rows;i++){
        
            std::cout<<"name: "<<leaf.data[i].index<<" key: "<<key<<std::endl;
            if(key <= leaf.data[i].index || (i == num_rows-1 && key > leaf.data[i].index)||leaf.data[i].index == 0){
            std::cout<<"found "<<i<<std::endl;
                index = i;
                
                return;
        
        }
    }
    
};

void insert(uint16_t key, uint16_t num_rows,uint16_t row_size, Run* obj, Curr_Node leaf){
    std::cout<<"Inserting! "<<std::endl;
};