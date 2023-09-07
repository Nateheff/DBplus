#pragma once
//#include <istream>
//#include <ostream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include <memory>
#include <string>
#include <iostream>

#include "File_Prep.hpp"
#include "Serializable.hpp"


//THE NUMBERS IN COMMENT ARE THE LINE WHERE YOU CAN IMPLEMENTATION IN .CPP FILE

namespace Serialize{
template <typename T> constexpr bool is_integral_type = std::is_integral<T>::value;
template <typename T> constexpr bool is_plain_old_data = (std::is_pod<T>::value && !std::is_integral<T>::value);
template <typename T> constexpr bool is_serializable = std::is_base_of<Serializable_Base, T>::value;

template <typename T, typename W = void> using if_integral_type = std::enable_if_t<is_integral_type<T>,W>;
template <typename T, typename W = void> using if_plain_type = std::enable_if_t<is_plain_old_data<T>,W>;
template <typename T, typename W = void> using if_serializable = std::enable_if_t<is_serializable<T>,W>;

template<typename T> if_integral_type<T,T>Byte_Order(T data);
 //Find data type to call correct specialized save/load

class Archive
{
    public:


enum Mode {Unknown, Save_Archive, Load_Archive}; 

    Archive(File_Prep &file, Mode mode = Unknown):file(file),mode(mode){Reset();};
    ~Archive()=default;
    template <typename T>
    Archive& operator<<(T& obj); //25 Insertion for stream out to db
    template<typename T>
    Archive& operator>>(T& obj); //31 Extraction for stream out of db
    template <typename T>
    Archive& Serialize(T& obj);
    
   private:
File_Prep &file;
    Mode mode = Unknown;
    uint32_t error = 0;
    
    enum {BIG_PRIME = 2038074743};
    void Hash(uint8_t* pData, uint32_t size) 
    {
        
        std::cout<<"6 Hash: "<<*pData<<std::endl;
        while(size--){
        hash = (hash+*pData++) * 0x0101;
        hash ^= (hash >> 3);
        std::cout<<"7 hash: "<<hash<<std::endl;
    }
    }
    uint32_t hash = BIG_PRIME;
    using Obj_Id = uint32_t;
    using Type_Id = uint32_t;
    
    enum {Id_Null = 1, Id_Start = 2};
    Type_Id next_type_id = Id_Start; //reset type and obj ids
    Obj_Id next_obj_id = Id_Start;
    
    std::map<const Type_Info*, Type_Id> map_type_id;
    std::map<void*, Obj_Id> map_obj_id;
    //WHAT'S THE DIFFERENCE BETWEEN THESE AND WHAT THE DIFFERENT USE CASE? (I DON'T KNOW)
    std::map<Type_Id, const Type_Info*> map_id_type;
    std::map<Obj_Id,void*> map_id_obj;
    
    std::map<void*, std::shared_ptr<Serializable_Base>> map_obj_shared;
    
    public:
    
   void Reset(); //37 clear/initialize attributes to defaults/null
   bool Checkpoint(); //
   void Set_Save() {if(mode != Save_Archive){Reset(); mode = Save_Archive;}}; //Ensure saving
   void Set_Load() {if(mode != Load_Archive){Reset(); mode=Load_Archive;}}; //Ensure Loading
   bool Is_Saving() {return mode == Save_Archive;}; //used to check archive mode;
   bool Is_Load() {return mode == Load_Archive;};
   bool Is_Error() {return error > 0;}; //basic error checking
   
        //11 Serializing objects passed in via Archive::serialize function not stream;
   
protected:

void Error() {error++;}; //sets Is_Error to true 

//WOW that is a lot of boiler plate... I'm sorry :) (Just wait til the .cpp file)

//User defined serializable objects:
template<typename T> if_serializable<T> Save(T& data);  //Object derived from Serializable (LOCATION)
template<typename T> if_serializable<T> Load(T& data); //Object derived from Serializable (LOACTION)

template<typename T> if_serializable<T> Save(T*& data);  //pointer to Object derived from Serializable (LOCATION)
template<typename T> if_serializable<T> Load(T*& data);  //pointer to Object derived from Serializable (LOCATION)

template<typename T, size_t count> if_serializable<T> Save(T (&data)[count]);  //array of Object derived from Serializable (LOCATION)
template<typename T, size_t count> if_serializable<T> Load(T (&data)[count]);  //array of Object derived from Serializable (LOACTION)

//Integral Types:
template <typename T> if_integral_type<T> Save(T &data); 
template <typename T> if_integral_type<T> Load(T &data);

template <typename T, size_t count> if_integral_type<T> Save(T (&array)[count]);
template <typename T, size_t count> if_integral_type<T> Load(T (&array)[count]);

//Plain Old Data
template<typename T> if_plain_type<T> Save(T& data);
template<typename T> if_plain_type<T> Load(T& data);

template<typename T> if_plain_type<T> Save(T*& data);
template<typename T> if_plain_type<T> Load(T*& data);

template<typename T, size_t count> if_plain_type<T> Save(T (&array)[count]);
template<typename T, size_t count> if_plain_type<T> Load(T (&array)[count]);

//Pointers
template <typename T> void Save(std::shared_ptr<T>& ptr);
template <typename T> void Load(std::shared_ptr<T>& ptr);

template <typename T> void Save(std::unique_ptr<T>& ptr);
template <typename T> void Load(std::unique_ptr<T>& ptr);

//Data Structures
template <typename T> void Save(std::vector<T>& vec);
template <typename T> void Load(std::vector<T>& vec);

template <typename T> void Save(std::list<T>& list);
template <typename T> void Load(std::list<T>& list);

template <typename Key, typename Value> void Save(std::map<Key,Value>&map);
template <typename Key, typename Value> void Load(std::map<Key,Value>&map);

void Save(std::string& str); //71 Specialization for std::strings since I'm choosing not to use char*[] in data;
void Load(std::string& str); //78

void Save(void* pVoid, uint32_t size); //89
void Load(void* pVoid, uint32_t size); //96 BLOB

void Save_Type(Serializable_Base* pObj); //103 pass in base pointer to get type of data for pseudo reflection later
const Type_Info* Load_Type();//113 Get the type of data being streamed in for reflection

int32_t save(void* pData, uint32_t size); //120
int32_t load(void* pData, uint32_t size); //125

   
};//Archive
}//Serialize
#include "Archive.hh"
