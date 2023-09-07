#ifndef FILE_PREP_HPP
#define FILE_PREP_HPP
#include <fstream>
#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>

class File_Prep
{
    
    using Mode = std::ios_base::openmode;
    
public:
std::fstream file;
static const Mode Load = std::ios_base::binary | std::ios_base::in; //Mode for Loading from db
static const Mode Save = std::ios_base::binary | std::ios_base::out | std::ios_base::app;//Mode for saving to db

uint32_t save(void* pData, uint32_t size){file.write((char*)pData, size); file.close(); return size;};
uint32_t load(void* pData, uint32_t size){file.read((char*)pData,size); file.close();std::cout<<"11 file-read: "<<pData<<" "<<file.gcount()<<" "<<file.is_open()<<std::endl; return size;};

    File_Prep(const std::string path, const Mode mode = Save):file(path,mode){};
    

};

#endif // FILE_PREP_HPP
