#pragma once
#include "Serializable.hpp"
#include "Internal_Leaf_Node.h"

#include <any>
#include <iostream>
#include <tuple>
#include <memory>
/*
 * We Need:
 * #rows per block (512 (block size)/row size), #blocks(db size/ 512(block size))
 * 
 **/
 



using namespace Serialize;

class Leaf_Node: public Serializable<Leaf_Node>
{    Internal_Leaf_Node* parent_ptr;
    const uint16_t max_size = 4096;
   
    
    struct Record{
};
    std::vector<Record>table;
    Leaf_Node* next_ptr;
    
public:

    void Get_Types(){
        
    }
    
    template<typename ...Args>
    void Add_Table(const Args...params){
        Record rec{params...};
        
        int test;
        auto tup = std::make_tuple(test);
        table.emplace_back(rec);
    }
    
    Leaf_Node()=default;
    ~Leaf_Node()=default;
};
























































































/*
class Type_Base{
   virtual ~Type_Base(){};
template<typename T>const T& get() const;
template<typename T, typename U> void set_value(const U& rhs); 
};

template<typename T>
class Type: public Type_Base{
public:
    Type(const T& rhs):value(rhs){};
    const &T get() const {return value;};
    void set_value(const &T rhs){value=rhs};
private:
    T value;
}

template<typename T> const &T Type_Base::get()const
{ return dynamic_cast<const Type<T>&>(*this).get();}
template<typename T,typename U> void Type_Base::set_value(const &U rhs)
{ return dynamic_cast<Type<U>&>(*this).set_value(rhs); }


class Leaf_Node: public Serializable<Leaf_Node>
{
    template<typename T,typename ...S>
    struct Record{
        T key;
    };
    template<typename T,typename ...S>
    std::shared_ptr<Record<T,S...>> Create_Row(T key, S...s){
            std::shared_ptr<Record<T,S...>>rec;
            return rec;
};
    
    template<typename T>
    struct Table{
        std::tuple<std::vector<int>>columns;
        std::map<T,std::tuple<int>>rows;
        
        
    };
    
    Internal_Leaf_Node* parent_node;
    
    Leaf_Node* next_node;
    
public:




std::vector<int> Get_Types(){
    uint16_t num_columns{};
    std::cout<<"Data types:\n 1: INT\n 2: FLOAT\n 3: BOOL\n 4: STRING\n";
    
    std::cout<<"# columns in table: ";
    std::cin>>num_columns;
    std::vector<int>types;

    int i{0};
    int type{1};
    
    do
    {
        
            if(i==0){
            std::cout<<"Enter key type: ";
            std::cin>>type;
            if(type <=0 || type >= 5){
            std::cout<<"Invalid type selection: "<<type<<std::endl;
            }
            else{
            types.push_back(type);
            
            i++;
            }
            }
            else{
            std::cout<<"Enter column "<<i<<" type: ";
            std::cin>>type;
            if(type <=0 || type >= 5)
            std::cout<<"Invalid type selection: "<<type<<std::endl;
            else{
            
            
            
            i++;
            
            }
        
        }
        
        
        
        
    }while(i < num_columns);
    auto rec = Create_Row(1,2,34,5,6.6,7.7,std::string{"grace"});
    return types;
    
    };
    
    
    Leaf_Node()=default;
    ~Leaf_Node()=default;


template<typename T>
void Set_All_Types(std::vector<int>types,Table<T>& table){
    
    for(size_t i=2;i<types.size();i++){
    if(types.at(i) == 1){
        
        auto test = std::tuple_cat(table.columns,std::make_tuple(1));
       table.columns.
    }else if(types.at(i)==2){
            std::tuple temp = std::make_tuple<float>;
        table.columns = std::tuple_cat(table.columns,temp);
    }else if(types.at(i)==3){
            std::tuple temp = std::make_tuple<bool>;
        table.columns = std::tuple_cat(temp,table.columns);
    }else if(types.at(i)==4){
            std::tuple temp = std::make_tuple<std::string>;
        table.columns = std::tuple_cat(temp,table.columns);
    };

    }
};


 
 
 void Set_First_Types(std::vector<int>types){
    
    
    for(size_t i = 0; i < types.size();i++){
        if(i==0){
            switch(types.at(0)){
                case 1:
                switch(types.at(1)){
                    case 1:
                    auto* tuple = Make_Tuple(types);
                }
            }
            
        }
        
       
    }
};

   void* Make_Tuple(std::vector<int>types){
       std::vector<std::tuple<int>>tups;
       auto ret = tups.at(0);
       if(tups.size() == 1)
           return &ret;
        
        tups.clear();
       for(size_t i = 1;i<types.size();i++){
           if(types.at(i) == 1){
        std::tuple<int>tup;
        tups.push_back(tup);
       
    }else if(types.at(i)==2){
            std::tuple<float>tup;
        tups.push_back(tup);
    }else if(types.at(i)==3){
            std::tuple<bool>tup;
    tups.push_back(tup);};
//    }else if(types.at(i)==4){
//            std::tuple<std::string::c_str()>tup;
//        
//    };
       }
       
       for(size_t i = 0; i<tups.size();i++){
           auto tup = std::tuple_cat(tups.at(i),tups.at(i+1));
           tups.at(0)=tup;
           
       }
   }

    

};


    for(size_t i = 0; i <= num_columns;i++){
        if(i==0){
            uint8_t type{0};
            while(type <1 && type>4){
            std::cout<<" Key type: ";
            std::cin>>type;
            switch(type){
                case(type==1):{
                    std::string id_name{};
                    std::cout<<"Key name: ";
                    std::getline(std::cin,id_name);
                columns.insert(id_name,std::any_cast<int>());
                
                }
            }
            }
        }
    }
   

};

*/