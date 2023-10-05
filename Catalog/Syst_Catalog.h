#pragma once

#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <stdint.h>
#include <iostream>


class Syst_Catalog{

    public:
    uint16_t calc_name(char* arr);
    void create_catalog(std::string type);
};