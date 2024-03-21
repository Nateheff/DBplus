#pragma once

/*
    run.h

    Run class is what (shockingly) is responsible for preparing the system and running the inital setup. This largely involves accessing and preparing the system catalogs which hold the information of all the data in each database. 

    The three trees which are attributes of the run class are of the class called "B_Tree", but they are really B+ Trees, these are just specialized for the catalogs and I wanted the B+ Trees used for user data to have the class name B+ Tree. These trees are implemented in B_Tree.h and B_Tree.hh
*/

#include "Catalog/Syst_Attr.h"
#include "Catalog/Syst_Index.h"
#include "Catalog/Syst_Root.h"
#include "Catalog/Syst_Rel.h"
#include "B_Tree.h"
#include <iterator>



class Run{
    public:
        //The B+ Tree for the index catalog
        B_Tree<Syst_Index,Syst_Index_Row>tree_ind{std::string{"catalog_ind"}};
        //The B+ Tree for the attributes catalog
        B_Tree<Syst_Attr,Syst_Attr_Row>tree_attr{std::string{"catalog_attr"}};
        //The B+ Tree for the relation catalog
        B_Tree<Syst_Rel,System_Rel_Row>tree_rel{std::string{"catalog_rel"}};
    
    std::string database{};
    bool run();
    void begin();
    void flush();
    Run(){};
    Run(std::string db):database{db}{};
    ~Run();
};