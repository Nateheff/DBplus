#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP
#include <map>
#include <memory>

namespace Serialize{
    class Serializable_Base;
    class Type_Info{
        static auto& Map(){static std::map<uint8_t, Type_Info*>map; return map;}
        
        using PFNCreate = Serializable_Base * (*)();
    public:
        Type_Info(const size_t h, PFNCreate pfn): hash{uint8_t(h)}, pfncreate{pfn}
        {
            Map()[hash] = this;
        }
        Serializable_Base* Create() const {return pfncreate();}
        const uint8_t Hash() const {return hash;};
        static Type_Info* Find(uint8_t h) {return Map()[h];}
    private:
    uint8_t hash;
    PFNCreate pfncreate;
    };
    
    class Archive;
    class Serializable_Base{
        friend class Archive;
    protected:
        virtual ~Serializable_Base(){};
        virtual void Serialize(Archive &arc){}
        virtual const Type_Info* Get_Type_Info() const {return nullptr;}
        virtual bool Is_Of_Type(uint8_t hash) const {return false;}
    
        
    };
    
    template<typename T, class Base = Serializable_Base>
class Serializable: public Base
{
    friend class Archive;
    static const Type_Info s_type_info;
    static Serializable_Base* Create() {return new T;}
    virtual const Type_Info* Get_Type_Info() const {return &s_type_info;}
    protected:
    virtual bool Is_Of_Type(uint8_t hash) const {
        if(s_type_info.Hash() != hash)
            return Base::Is_Of_Type(hash);
        return true;
    }
public:
    

};
template<typename T, class Base>
const Type_Info Serializable<T,Base>::s_type_info(typeid(T).hash_code(),Create);
}
#endif // SERIALIZABLE_HPP
