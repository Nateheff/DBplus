/*
    WELCOME TO DB+
   SQL RDBMS By Nathan Heffington

    I am proud to present this system and codebase to you and hope it serves you in whatever capacity you desire it to. If you want mroe general information about the project or me, the readme.txt file has all of that so I'd recommend starting there.

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


#define SIZE_NAME_COLUMN 10
#define NUM_MEASUREMENTS 1
#define SIZE_PAGE 



/*
Meta_Results do_meta(std::string cmd){
    if(cmd == std::string{".exit"})
        exit(EXIT_SUCCESS);
    else{
        return META_FOREIGN;
    }
}
*/

//    FSM test_fsm;
   

//    int check{1};
//    test_fsm.create_fsm(std::string{"file"});
//    std::fstream fs;
//    fs.write(reinterpret_cast<char*>(&test_fsm),sizeof(test_fsm));
//    Disk_SM test{std::string{"file"}};
//    Node new_node;
//    Buffer_Pool pool{&test};
   
//    for(size_t i = 1;i<8;i++){
//    new_node = *pool.get_page(i);
//    new_node.print_data();
//    std::cout<<"\n";
//    };

/*
    main()
    THIS IS A MESS
    I know...it's not pretty, but it works and serves it's purpose. The function itself pretty much only controls the initial prompting and then lets the rest of the system do the rest. This function is kind of like a beat up squeaky door with at the entrance of heaven (a little dramatic but you get the point).



*/

int main()
{
    
    std::string db{};
    std::fstream fs;
    fs.open("databases.txt",std::ios_base::out|std::ios_base::in|std::ios_base::binary|std::ios_base::ate);
    //Initial prompting which gets the database which the user is working in this session
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
    
    Run obj(db);
    
    obj.run();
    obj.tree_rel.search_catalog(1141,28);
    obj.tree_ind.rel = obj.tree_rel.info.rel.rows[obj.tree_rel.info.index];
    obj.tree_rel.search_catalog(1149,28);
    obj.tree_rel.rel = obj.tree_rel.info.rel.rows[obj.tree_rel.info.index];
    obj.tree_rel.search_catalog(1269,28);
    obj.tree_attr.rel = obj.tree_rel.info.rel.rows[obj.tree_rel.info.index];

    //These are all of the supported keywords and their token values
    Keyword_List res_list = {{{"bool",0},{"char",1},{"create",2},{"database",3},{"float",4},{"from",5},{"insert",6},{"int",7},{"and",8},{"set",9},{"select",10},{"table",11},{"varchar",12},{"where",13},{"between",14},{"drop",15},{"delete",16},{"update",17},{"short",18},{"into",19}},20,9};

    //All of the supported operators and their token values
    std::unordered_map<std::string,uint16_t>operators{{"*",20},{">",21},{"<",22},{"/",23},{"(",24},{")",25},{"=",26},{"+",27},{"-",28},{"<=",29},{">=",30},{"<>",31},{",",32}};
    std::string query={"create table faces ( int a, float b, float c, short d )"};
    while(true){
    std::cout<<"Enter Command to begin: ";
    std::getline(std::cin,query);

    //Parses the query into tokens (see Lexer/Scanner.h)
    Scanner test(query,&res_list,operators);
    test.scanner_run();
    

    //Recieves parsed query in form of tokens and makes necessary function calls (see Parser/Construct.h)
    receiver_main(test.full_tok,test.identifiers,&res_list,&obj);
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




   
}

