#include "Archive.h"


#include <ostream>
#include <istream>
#include <iostream>


//////////////////////////////////////
//////////////////////////////////////
//TEST ALL
///TEST ALL
//TEST ALL
//TEST ALL
//TEST ALL
//TEST ALL
//TEST ALL
//TEST ALL
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////

using namespace Serialize;
    //##-## NON templatized implementations 

    void Archive::Reset(){
        map_type_id.clear();
        map_obj_shared.clear();
        map_id_type.clear();
        map_id_obj.clear();
        map_obj_id.clear();
        map_id_obj[Id_Null] = nullptr;
        map_obj_id[nullptr] = Id_Start;
        next_obj_id = Id_Start;
        hash = BIG_PRIME;
        error = 0;
    }
    
    bool Archive::Checkpoint(){
        if(Is_Error()) return false;
        switch(mode){
            case Save_Archive:
            Save(hash);
            return true;
            case Load_Archive:
            {
                uint32_t h = hash;
                uint32_t file_hash = {};
                Load(file_hash);
                if(file_hash == h)
                    return true;
            }
            default:
                break;
        }
        Error();
        return false;
    }

    void Archive::Save(std::string &str){
        if(Is_Error()) return;
        uint32_t size = uint32_t(str.length());
        if(size && (save((uint8_t*)str.data(),size) != int32_t(size)))
            return Error();
    }
    
    void Archive::Load(std::string &str){
        if(Is_Error()) return;
        uint32_t size = uint32_t(str.length());
        str.clear();
        if(size){
            std::string str2(size+1,'\0');
            if(load((uint8_t*)str2.data(),size) != int32_t(size))
                return Error();
            str.swap(str2);
        }
    }
    void Archive::Save(void* pVoid, uint32_t size){
        if(Is_Error()) return;
        
        if(size && (save(pVoid,size) != int32_t(size)))
            return Error();
    }
    
    void Archive::Load(void* pVoid, uint32_t size){
        if(Is_Error()) return;
        
        if(size && (load(pVoid,size) != int32_t(size)))
            return Error();
    }
    
    void Archive::Save_Type(Serializable_Base* pObj){
        const Type_Info* pTypeInfo = pObj->Get_Type_Info();
        Type_Id& type_id = map_type_id[pTypeInfo];
        if(!type_id){
            type_id = next_type_id++;
            uint32_t hash = pTypeInfo->Hash();
            Save(hash);
        }
    } 
    
    const Type_Info* Archive::Load_Type(){
        uint8_t h = 0;
        Load(h);
        const Type_Info* pType_Info = Type_Info::Find(h);
        return pType_Info;
    }
    
    int32_t Archive::save(void* pData, uint32_t size){
        std::cout<<"5 Archive save: "<<(uint8_t*)pData<<std::endl;
        Hash((uint8_t*)&pData,size);
        
        return file.save(pData,size);
    }
    
    int32_t Archive::load(void* pData, uint32_t size){
        std::cout<<"10 Archive load: "<<pData<<std::endl;
        int32_t TEST = file.load(pData,size);
        std::cout<<"12 check load: "<<TEST<<std::endl;
        
        
        Hash((uint8_t*)&pData,size);
        
        return TEST;
    }
    




