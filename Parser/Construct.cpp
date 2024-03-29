#include "Construct.h"
#include "../Commands/Commands.h"
#include "../Disk_Space/FSM.h"
#include "../B+_Tree.h"


std::string process_rows(std::vector<Row>rows){
    std::string final_s;
    for(Row row: rows){
        std::string data(row.data.data());
        final_s.append(data+"\n");
    }
    return final_s;
}

std::string receiver_main(std::vector<uint16_t> full_tok,std::vector<std::string> identifiers,Keyword_List* list,Run* obj){
    std::vector<Row> selected;
    // for(size_t i = 0; i < full_tok.size();i++){
        switch(full_tok.at(0)){
            case(2): //create 
            {
                uint8_t mode {};
                if(full_tok.at(1)==3){//database
                    create_db(identifiers.at(0),obj);
                    std::cout<<"Creating database!"<<std::endl;
                    return "success";
                }
                else if(full_tok.at(1)==11){//table
                std::string table_name = identifiers.at(0);
                if(full_tok.at(full_tok.size()-1)!=25)//(
                    return NULL;
                std::cout<<"creating table!"<<std::endl;
                
                create_table(table_name,full_tok,identifiers,full_tok.size()-3,identifiers.size()-1,list,obj);
                return "success";
                }else
                return NULL;
                

            }
            case(6): //insert
            {
                std::string table_name = identifiers.at(0);
                if(full_tok.at(1)!= 19 || full_tok.at(2)!=24)
                return "success";
                std::cout<<"inserting "<<table_name<<std::endl;
                insert(table_name,identifiers,obj);
                return NULL;
                
            }
            case(10)://select
            {
                

                std::string table_name{};
                
                // bool get_all = false;

                if(full_tok.at(1)==20 && full_tok.at(2)==5){
                    table_name = identifiers.at(0);
                    if(full_tok.size()==3){
                    selected = select(table_name,obj,identifiers);
                    break;
                    }
                    else if(full_tok.at(3)==13){
                        if(full_tok.at(full_tok.size()-1)!=8)
                        selected = select_all(table_name,obj,identifiers.at(1),full_tok.at(4),identifiers.at(2));
                        else
                        selected = select_all(table_name,obj,identifiers.at(1),full_tok.at(4),identifiers.at(2),identifiers.at(3));
                        break;
                    }
                }
                
                if(full_tok.at(1)!=20){
                std::vector<std::string>ids;
                    if(full_tok.size()>2 && full_tok.at(3)==26){
                        table_name = identifiers.at(identifiers.size()-3);
                        
                        if(full_tok.at(full_tok.size()-1)!=8)
                        selected = select_all(table_name,obj,identifiers.at(1),full_tok.at(4),identifiers.at(2));
                        else
                        selected = select_all(table_name,obj,identifiers.at(1),full_tok.at(4),identifiers.at(2),identifiers.at(3));
                        break;
                    }
                    else if(full_tok.size()==2){
                        table_name = identifiers.at(identifiers.size()-1);
                        selected = select(table_name,obj,identifiers);
                        break;
                    }

                }
                if(selected.size() > 0)
                    return process_rows(selected);
                return NULL;
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
                return "success";
                }else if(full_tok.at(1)==11){
                drop_table(identifiers.at(0),obj); //FOR TABLE
                std::cout<<"success"<<std::endl;
                return " ";
                }else
                return NULL;
            }
            case(16):
            {
                

                std::string table_name = identifiers.at(0);
                if(full_tok.size()==2){
                delete_all(table_name,obj); //DELETE ALL )true/false) for db/table
                std::cout<<"clearing table"<<std::endl;
                break;
                };
                if(full_tok.at(1)!=5 || full_tok.at(2)!=13)
                return NULL;
                

                
                std::cout<<"deleting what you said where you said"<<std::endl;
                delete_row(table_name,identifiers,obj,full_tok.at(3),identifiers.at(identifiers.size()-1));

                break;

            }
            case(17):
            {
                if(full_tok.at(1)!=9)
                return NULL;
                
                if((std::find(full_tok.cbegin(),full_tok.cend(),13))==full_tok.cend()){
                update_all(identifiers.at(0),obj,identifiers);
                std::cout<<"updating all rows"<<std::endl;
                return "success";
                }
                if(full_tok.at(full_tok.size()-1)!=8){
                identifiers.erase(identifiers.cbegin()+identifiers.size()-2,identifiers.cend()-1);
                update(identifiers.at(0),obj,identifiers,full_tok.at(full_tok.size()-1),identifiers.at(identifiers.size()-1));
                return "success";
                }else{
                    identifiers.erase(identifiers.cbegin()+identifiers.size()-3,identifiers.cend()-2);
                update(identifiers.at(0),obj,identifiers,full_tok.at(full_tok.size()-2),identifiers.at(identifiers.size()-2),identifiers.at(identifiers.size()-1));
                return "success";
                }
                // if(identifiers.size() <=5){
                //     std::string key_column = identifiers.at(3);
                //     std::string key_val = identifiers.at(4);
                //     std::cout<<"updating key value said where you said!"<<std::endl;
                //     //update(table_name,column_name,new_val,key_column,key_val);
                // }else{
                //     std::string column_check = identifiers.at(3);
                //     std::string column_val = identifiers.at(4);
                //     std::string key_column = identifiers.at(5);
                //     std::string key_val = identifiers.at(6);
                //     std::cout<<"updating what you said where you said!"<<std::endl;
                //     //update(table_name,column_name,new_val,key_column,key_val,column_check,column_val);
                // };
                break;
                
            }
            
        // }
    }
    return "success";
};