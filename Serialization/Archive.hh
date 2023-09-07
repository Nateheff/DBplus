#pragma once
namespace Serialize{
    
template<typename T>
    Archive& Archive::Serialize(T& obj){
        switch(mode){
            case Save_Archive:
                Save(obj);
                break;
            case Load_Archive:
                Load(obj);
                break; 
            default: Error();
            break;
        }
        return *this;
    }
    
   template<typename T>
    Archive& Archive::operator<<(T& obj){
    Set_Save();
    Save(obj);
    return *this;
    }
    
    template<typename T>
    Archive& Archive::operator>>(T& obj){
        Set_Load();
        Load(obj);
        return *this;
    }
   
    template<typename T>
    if_serializable<T> Archive::Save(T &obj){
        if(Is_Error()) return;
        Save_Type(&obj);
        obj.Serialize(*this);
    }

    template<typename T>
    if_serializable<T> Archive::Load(T& obj){
        if(Is_Error()) return;
        const Type_Info *pTypeInfo = Load_Type();
        if(!pTypeInfo || (pTypeInfo != obj.Get_Type_Info()))
            return Error();
        obj.Serialize(*this);
    }


    template<typename T>
    if_serializable<T> Archive::Save(T *&pObj){
        if(Is_Error()) return;
        Obj_Id& obj_id = map_obj_id[pObj];
        obj_id = next_obj_id++;
        Save_Type(pObj);
        pObj->Serialize(*this);
    }
    
    template<typename T>
    if_serializable<T> Archive::Load(T *&pObj){
        if(Is_Error()) return;
        const Type_Info* pTypeInfo = Load_Type();
        if(!pTypeInfo)
            return Error();
        uint32_t hash = T::s_type_info.Hash();
        T*& pNew = (T*)pTypeInfo->Create();
        if(!pNew->Is_Of_Type(hash)){
            delete pNew;
            return Error();
        }
        pNew->Serialize(*this);
        if(pObj)
            delete pObj;
        pObj = pNew;
    }
    
    template<typename T, size_t count>
    if_serializable<T> Archive::Save(T(&array)[count]){
        if(Is_Error()) return;
        Save_Type(array);
        for(auto &item:array)
            item.Serialize(*this);
    }
    
    template<typename T, size_t count>
    if_serializable<T> Archive::Load(T(&array)[count]){
        if(Is_Error()) return;
        const Type_Info* pTypeInfo = Load_Type();
        if(!pTypeInfo || (pTypeInfo != array->Get_Type_Info()))
            return Error();
        for(auto &item:array)
            item.Serialize(*this);
    }
    
    template<typename T>
    if_plain_type<T> Archive::Save(T  &data){
        if(Is_Error()) return;
        save(&data,sizeof(data));
    }
    
    template<typename T>
    if_plain_type<T> Archive::Load(T &data){
        if(Is_Error()) return;
        load(&data, sizeof(data));
    }
    
    template<typename T>
    if_plain_type<T>Archive::Save(T *&pObj){
        if(Is_Error()) return;
        Obj_Id &obj_id = map_obj_id[pObj];
        obj_id = next_obj_id++;
        Save(*pObj);
    }
    
    template<typename T>
    if_plain_type<T> Archive::Load(T *&pObj){
        if(Is_Error()) return;
        T*& pNew = (T*&)map_id_obj[pObj];
        if(!pNew){
        
        pNew = new T;
        Load(*pNew);
        if(pObj != pNew)
        {
            if(pObj)
                delete pObj;
            pObj = pNew;
        }
        
        }
    }
    
    template<typename T,size_t count>
    if_plain_type<T> Archive::Save(T(&array)[count]){
        if(Is_Error()) return;
        save(&array,sizeof(array));
    }
    
    template<typename T, size_t count>
    if_plain_type<T> Archive::Load(T(&array)[count]){
        if(Is_Error()) return;
        load(&array,sizeof(array));
    }
    
    template<typename T>
    if_integral_type<T> Archive::Save(T &data){
        if(Is_Error()) return;
        std::cout<<"1: start"<<std::endl;
        using unType = typename std::make_unsigned<T>::type;
        
        unType un_data = *(unType*)&data;
        std::cout<<"2: un_data: "<<un_data<<std::endl;
        unType un_nbo = Byte_Order(un_data);
        std::cout<<"4 un-nbo: "<<un_nbo<<std::endl;
        save((void*)&un_nbo, sizeof(T));
        
    }
    
    template<typename T>
    if_integral_type<T> Archive::Load(T &data){
        
        if(Is_Error()) return;
        std::cout<<"9 start load"<<std::endl;
        using unType = typename std::make_unsigned<T>::type;
        unType un_data = {};
        
        load(&un_data, sizeof(T));
        
        std::cout<<"Byte_Order load: "<<un_data<<std::endl;
        unType un_BO = Byte_Order(un_data);
       
        data = *(T*)&un_BO;
       
    }
    
    template<typename T, size_t count>
    if_integral_type<T> Archive::Save(T(&array)[count]){
        if(Is_Error()) return;
        for(auto &item:array)
            Save(item);
    }
    
    template<typename T, size_t count>
    if_integral_type<T> Archive::Load(T(&array)[count]){
        if(Is_Error()) return;
        for(auto &item:array)
            Load(item);
    }
    
    
    template<typename T>
void Archive::Save(std::shared_ptr<T>& ptr){
    if(Is_Error()) return;
    T* pType = ptr.get();
    Save(pType);
}
    
    template<typename T>
        void Archive::Load(std::shared_ptr<T>& ptr){
        if(Is_Error()) return;
        T* pType = nullptr;
        Load(pType);
        if(pType){
            std::shared_ptr<T>& type = (std::shared_ptr<T>&)map_obj_shared[pType];
            if(!type)
                type = std::shared_ptr<T>(pType);
            ptr = type;
        }
    }
    
    template<typename T>
    void Archive::Save(std::unique_ptr<T>& ptr){
        if(Is_Error()) return;
        T* type = ptr.get();
        Save(type);
    }
    
    template<typename T>
    void Archive::Load(std::unique_ptr<T>& ptr){
        if(Is_Error()) return;
        T* ptype = nullptr;
        Load(ptype);
        ptr=std::unique_ptr<T>(ptype);
    }
    
    template<typename T>
    void Archive::Save(std::vector<T>& vec){
        for(T& item: vec){
            Save(item);
        }
    }
    
    template<typename T>
    void Archive::Load(std::vector<T>& vec){
        if(Is_Error()) return;
        vec.clear();
        bool done = false;
        do{
            
            T type = {};
            Load(type);
            if(!type)
                done = true;
            else
            vec.push_back(type);
        }while(!done);
    }
    
    template<typename T>
    void Archive::Save(std::list<T>& list){
        if(Is_Error()) return;
       
        for(T& item: list){
            Save(item);
        }
    }
    
    template<typename T>
    void Archive::Load(std::list<T>& list){
        if(Is_Error()) return;
        list.clear();
        bool done = false;
        do{
            
            T type = {};
            Load(type);
            if(!type)
                done = true;
            else
            list.push_back(type);
        }while(!done); 
    }
    template<typename K, typename V>
    void Archive::Save(std::map<K,V>&map){
        if(Is_Error()) return;
        
        for(auto& pair: map){
            Save(pair.first);
            Save(pair.second);
        }
    }
    
    template<typename K, typename V>
    void Archive::Load(std::map<K,V>& map){
        if(Is_Error()) return;
        map.clear();
        bool done = false;
        while(!done){
            K key = {};
            V value = {};
            Load(key);
            if(!key)
                done = true;
            else{
            Load(value);
            map[key] = value;
            
            }
        }
    }

    template<typename T>
    if_integral_type<T,T> Byte_Order(T data){
        
        static const uint32_t i = 1;
        if((*(uint8_t*)&i) == 1){
            
            if constexpr(sizeof(data)==sizeof(uint16_t)){
                std::cout<<"3 Byte--order data: "<<data<<std::endl;
                return T(((uint16_t(data) << 8) & 0xff00U) |
                ((uint16_t(data) >> 8) & 0x00ffU));
            }else if constexpr(sizeof(data)==sizeof(uint32_t)){
                std::cout<<"3 Byte--order data: "<<data<<std::endl;
                return T(((uint32_t(data) << 24) & 0xff000000U) |
                ((uint32_t(data) << 8) & 0x00ff0000U) | 
                ((uint32_t(data) >> 8) & 0x0000ff00U) |
                ((uint32_t(data) >> 24) & 0x000000ffU));
            }else if constexpr(sizeof(data) == sizeof(uint64_t)){
                std::cout<<"3 Byte--order data: "<<data<<std::endl;
            return T(((uint64_t(data) << 56) & 0xff00000000000000ULL) |
                        ((uint64_t(data) << 40) & 0x00ff000000000000ULL) |
                        ((uint64_t(data) << 24) & 0x0000ff0000000000ULL) |
                        ((uint64_t(data) <<  8) & 0x000000ff00000000ULL) |
                        ((uint64_t(data) >>  8) & 0x00000000ff000000ULL) |
                        ((uint64_t(data) >> 24) & 0x0000000000ff0000ULL) |
                        ((uint64_t(data) >> 40) & 0x000000000000ff00ULL) |
                        ((uint64_t(data) >> 56) & 0x00000000000000ffULL));
        }
        std::cout<<"3 Byte-order data: "<<data<<std::endl;
        return data;
        
        }
        std::cout<<"3 Byte_order data: "<<data<<std::endl;
    return data;
    
    }

}