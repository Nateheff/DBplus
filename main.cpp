/*
  Simple SQL DBMS By Nathan Heffington
   * Serialization method largely inspired by Chris Ryan's method of binary object serialization
 
*/

#include <iostream>
#include <string> 
#include <sstream>
#include <fstream>
#include <cstring>
#include "Lexer/scanner.h"
#include "Lexer/list.h"
#include "Parser/Construct.cpp"
#include "Disk_Space/Disk_SM.h"
#include "Disk_Space/FSM.h"


#define SIZE_NAME_COLUMN 10
#define NUM_MEASUREMENTS 1
#define SIZE_PAGE 


#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute);

enum Meta_Results {META_SUCCESS,META_FOREIGN};
enum Result {SUCCESS, FAILURE};



Meta_Results do_meta(std::string cmd){
    if(cmd == std::string{".exit"})
        exit(EXIT_SUCCESS);
    else{
        return META_FOREIGN;
    }
}



int main()
{
    /*
    Keyword_List res_list = {{{"bool",0},{"char",1},{"create",2},{"database",3},{"float",4},{"from",5},{"insert",6},{"int",7},{"key",8},{"primary",9},{"select",10},{"table",11},{"varchar",12},{"where",13},{"between",14},{"drop",15},{"delete",16},{"update",17}},18,9};
    std::unordered_map<std::string,uint16_t>operators{{"*",19},{">",20},{"<",21},{"/",22},{"(",23},{")",24},{"=",25},{"+",26},{"-",27},{"<=",28},{">=",29},{"<>",30}};
    std::string query;
    
    std::getline(std::cin,query);
    
    Scanner test(query,&res_list,operators);
    test.scanner_run();
    test.print_query();
    receiver(test.full_tok,test.identifiers);
    */
    
   FSM test_fsm;
   

   int check{1};
   test_fsm.create_fsm(std::string{"file"});
   std::fstream fs;
   fs.write(reinterpret_cast<char*>(&test_fsm),sizeof(test_fsm));
   Disk_SM test{std::string{"file"}};
   Node new_node;
   for(size_t i = 1;i<8;i++){
   test.read_page(i,&new_node);
    new_node.print_data();
    std::cout<<"\n";
   };
//    test.read_page(1,&new_node);
//    new_node.print_data();
//    Node new_node2;
//    test.read_page(2,&new_node2);
//    new_node2.print_data();
   
//    do{
//     std::cout<<"Go? ";
//     std::cin >>check;
   
//    uint16_t page_num = test.write_new_page();
//    uint8_t hole{};
//    if(page_num == 2){
//     std::cout<<"freeing"<<std::endl;
//     test.free_page(1);
//     hole=1;
//    }
//    if(page_num==5){
//     std::cout<<"freeing"<<std::endl;
//     test.free_page(3);
//     hole=1;
//    }
   
//    Node node;
//    char str[MAX_PAGE-12];
//    std::cout<<"enter data for page "<<page_num<<": ";
//    std::cin >>str;
//    node.set_data(str);
//    node.set_checksum(32);
//    node.set_p(10,11,12);

   
//    test.write_page(&node,page_num);

   
//    Node new_node;
//    test.read_page(page_num,&new_node);
//    std::cout<<"wrote"<<std::endl;
//    new_node.print_data();
//    }while(check!=0);
   
}
