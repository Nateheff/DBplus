/*
    WELCOME TO DB+
   SQL RDBMS By Nathan Heffington

    I am proud to present this system and codebase to you and hope it serves you in whatever
     capacity you desire it to. If you want mroe general information about the project or me, 
     the readme.txt file has all of that so I'd recommend starting there.

    Thank you!
   
 
*/

#include <iostream>
#include <string> 
#include <sstream>
#include <fstream>
#include <cstring>
#include <set>

#include "Commands/Commands.h"
#include "Parser/Construct.h"
#include "run.h"
#include "B_Tree.h"
#include "B_Tree.hh"
#include "Lexer/scanner.h"
#include "Socket/Socket.h"
#include "Lexer/list.h"

#define SIZE_NAME_COLUMN 10
#define NUM_MEASUREMENTS 1
#define SIZE_PAGE 

/*
    main()
    I know...it's not pretty, but it works and serves it's purpose. The function itself pretty much
    only controls the initial prompting and then lets the rest of the system do the rest. 
     
*/

KW_OP kw_ops;
int main()
{
    
    std::string db{};
    std::fstream fs;

    //databases.txt contains the names of all the databases for this user.
    fs.open("databases.txt",std::ios_base::out|std::ios_base::in|std::ios_base::binary|std::ios_base::ate);

    //Checking if the user has any saved databases
    if(fs.tellp()>0){
        fs.close();
        fs.open("databases.txt",std::ios_base::out|std::ios_base::in|std::ios_base::binary);
        std::cout<<"Welcome back to DB+! Your databases are: "<<std::endl;
        while(fs>>db){
            std::cout<<db<<std::endl;
        }
        std::cout<<"Enter the database you'd like to work in this session: ";
        std::cin >> db;
        std::cin.ignore();
        
        db+=".db";
    }
    
    //Run objects are defined in run.h and contain the catalogs for the database
    Run obj(db);
    
    //obj.run() creates/retreives all of the database catalog info
    obj.run();
    obj.tree_rel.search_catalog(1141,28);
    obj.tree_ind.rel = obj.tree_rel.info.rel.rows[obj.tree_rel.info.index];
    obj.tree_rel.search_catalog(1149,28);
    obj.tree_rel.rel = obj.tree_rel.info.rel.rows[obj.tree_rel.info.index];
    obj.tree_rel.search_catalog(1269,28);
    obj.tree_attr.rel = obj.tree_rel.info.rel.rows[obj.tree_rel.info.index];

    //A test querys
    std::string query={"create table faces ( int a, float b, float c, short d )"};

    //The command loop whcih takes queries from the user for the session
    while(true){
        std::cout<<"Enter Command to begin: ";
        std::getline(std::cin,query);

        //Parses the query into tokens (see Lexer/Scanner.h)
        Scanner test(query,&kw_ops.res_list,kw_ops.operators);
        test.scanner_run();
        

        //Recieves parsed query in form of tokens and makes necessary function calls (see Parser/Construct.h)
        receiver_main(test.full_tok,test.identifiers,&kw_ops.res_list,&obj);
    };
    
    //Fun little test function
    // for(size_t i = 0; i< 49990; i+= 6){
    //     std::vector<std::string>ids;
    //     ids.push_back("faces");
    //     ids.push_back(vec.at(i));
    //     ids.push_back(vec.at(i+1)+"."+vec.at(i+2));
    //     ids.push_back(vec.at(i+3)+"."+vec.at(i+4));
    //     ids.push_back(vec.at(i+5));
    //     insert("faces",ids,&obj);
    // }

   
};


