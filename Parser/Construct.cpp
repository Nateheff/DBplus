#include "Construct.h"
#include "../Commands/Commands.h"
#include "../Disk_Space/FSM.h"
#include "../B+_Tree.h"

bool receiver_main(std::vector<uint16_t> full_tok,std::vector<std::string> identifiers,Keyword_List* list,Run* obj){
    
    std::cout<<full_tok.size()<<" "<<identifiers.size()<<std::endl;
    // for(size_t i = 0; i < full_tok.size();i++){
        switch(full_tok.at(0)){
            case(2): //create 
            {
                uint8_t mode {};
                if(full_tok.at(1)==3){//database
                    create_db(identifiers.at(0));
                    std::cout<<"Creating database!"<<std::endl;
                }
                else if(full_tok.at(1)==11){//table
                std::string table_name = identifiers.at(0);
                if(full_tok.at(full_tok.size()-1)!=25)//(
                return false;
                std::cout<<"creating table!"<<std::endl;
                
                create_table(table_name,full_tok,identifiers,full_tok.size()-3,identifiers.size()-1,list,obj);
                }else
                return false;
                break;

            }
            case(6): //insert
            {
                std::string table_name = identifiers.at(0);
                if(full_tok.at(1)!= 19 || full_tok.at(2)!=24)
                return false;
                std::cout<<"inserting "<<table_name<<std::endl;
                insert(table_name,identifiers,obj);
                return true;
                
            }
            case(10)://select
            {
                for(auto id:identifiers)
                std::cout<<id<<std::endl;

                std::string table_name{};
                
                // bool get_all = false;

                if(full_tok.at(1)==20 && full_tok.at(2)==5){
                    std::cout<<"ok "<<full_tok.at(3)<<std::endl;
                    table_name = identifiers.at(0);
                    if(full_tok.size()==3){
                        std::cout<<"all simple"<<std::endl;
                    select(table_name,obj,identifiers);
                    return true;
                    }
                    else if(full_tok.at(3)==13){
                        std::cout<<"all where"<<std::endl;
                        select_all(table_name,obj,identifiers.at(1),full_tok.at(4),identifiers.at(2));
                        return true;
                    }
                }
                
                if(full_tok.at(1)!=20){
                std::vector<std::string>ids;
                    if(full_tok.size()>2 && full_tok.at(3)==26){
                        table_name = identifiers.at(identifiers.size()-3);
                        
                        select_all(table_name,obj,identifiers.at(identifiers.size()-2),full_tok.at(3),identifiers.at(identifiers.size()-1));
                        return true;
                    }
                    else if(full_tok.size()==2){
                        table_name = identifiers.at(identifiers.size()-1);
                        select(table_name,obj,identifiers);
                        return true;
                    }

                }
                return false;
                // std::cout<<"change"<<std::endl;
                // select(false,identifiers.at(0),identifiers.at(1),obj);
                /*
                if(full_tok.at(1)!=20)
                std::string column_name = identifiers.at(0);
                else
                get_all = true;

                if(full_tok.at(2)!=5)
                return false;
                
                if(get_all)
                table_name = identifiers.at(0);
                else
                table_name = identifiers.at(1);

                // if(full_tok.size() <= 3){
                // select_all(table_name, obj);
                // std::cout<<"selecting all!"<<std::endl;
                // break;
                // }
                // if((get_all && full_tok.at(i+3)!=13)||(!get_all && full_tok.at(i+2)!=13))
                // return false;

                if(get_all){
                // std::string where_column = identifiers.at(1);
                // uint16_t where_op = full_tok.at(i+4);
                std::cout<<"selecting all from where you said!"<<std::endl;
                select_all(table_name,obj);
                }else{
                // std::string where_column = identifiers.at(2);
                // uint16_t where_op = full_tok.at(i+3);
                std::cout<<"Selecting what you said from where you said!"<<std::endl;
                select(table_name,obj,identifiers);
                };
                break;
                */
            }
            case(15):
            {
                if(full_tok.at(1)==3){
                drop_db(identifiers.at(0),obj); //FOR DATABSE
                std::cout<<"dropping db"<<std::endl;
                }else if(full_tok.at(1)==11){
                drop_table(identifiers.at(0),obj); //FOR TABLE
                std::cout<<"dropping table"<<std::endl;
                }else
                return false;
            }
            case(16):
            {
                if(full_tok.at(1)!=5)
                return false;

                std::string table_name = identifiers.at(0);
                if(full_tok.size()==2){
                //delete_all(true,table_name) DELETE ALL )true/false) for db/table
                std::cout<<"clearing table"<<std::endl;
                break;
                };

                if(full_tok.at(2)!=13)
                return false;

                std::string column_name = identifiers.at(1);
                uint16_t delete_op = full_tok.at(3);
                std::cout<<"deleting what you said where you said"<<std::endl;
                //delete(table_name,column_name,delete_op,indentifiers);

                break;

            }
            case(17):
            {
                std::string table_name = identifiers.at(0);
                std::string column_name = identifiers.at(1);
                std::string new_val = identifiers.at(2);
                if(full_tok.size()==2)
                //update(table_name,column_name,new_val);
                std::cout<<"updating all rows"<<std::endl;

                if(full_tok.at(2)!=13)
                return false;

                if(identifiers.size() <=5){
                    std::string key_column = identifiers.at(3);
                    std::string key_val = identifiers.at(4);
                    std::cout<<"updating key value said where you said!"<<std::endl;
                    //update(table_name,column_name,new_val,key_column,key_val);
                }else{
                    std::string column_check = identifiers.at(3);
                    std::string column_val = identifiers.at(4);
                    std::string key_column = identifiers.at(5);
                    std::string key_val = identifiers.at(6);
                    std::cout<<"updating what you said where you said!"<<std::endl;
                    //update(table_name,column_name,new_val,key_column,key_val,column_check,column_val);
                };
                break;
                
            }
            
        // }
    }
    return true;
};