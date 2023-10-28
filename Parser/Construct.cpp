#include "Construct.h"

bool receiver_main(std::vector<uint16_t> full_tok,std::vector<std::string> identifiers,Keyword_List*list){
    std::cout<<full_tok.size()<<" "<<identifiers.size()<<std::endl;
    for(size_t i = 0; i < full_tok.size();i++){
        switch(full_tok.at(i)){
            case(2): //create
            {
                uint8_t mode {};
                if(full_tok.at(i+1)==3){//database
                    create_db(identifiers.at(0));
                    std::cout<<"Creating database!"<<std::endl;
                }
                else if(full_tok.at(i+1)==11){//table
                std::string table_name = identifiers.at(0);
                if(full_tok.at(full_tok.size()-1)!=24)//(
                return false;
                std::cout<<"creating table!"<<std::endl;
                create_table(table_name,full_tok,identifiers,full_tok.size()-3,identifiers.size()-1,list);
                }else
                return false;
                break;

            }
            case(6): //insert
            {
                std::string table_name = identifiers.at(0);
                if(full_tok.at(i+1)!= 23)
                return false;
                std::cout<<"inserting"<<std::endl;
                //if(!insert(table_name,identifiers))
                //return false;
                break;
            }
            case(10)://select
            {
                bool get_all = false;
                if(full_tok.at(i+1)!=19)
                std::string column_name = identifiers.at(0);
                else
                get_all = true;

                if((get_all && full_tok.at(i+2)!=5)||(!get_all && full_tok.at(i+1)!=5))
                return false;

                if(get_all)
                std::string table_name = identifiers.at(0);
                else
                std::string table_name = identifiers.at(1);

                if(full_tok.size() <= 3){
                //select(get_all,table_name,column_name);
                std::cout<<"selecting all!"<<std::endl;
                break;
                }
                if((get_all && full_tok.at(i+3)!=13)||(!get_all && full_tok.at(i+2)!=13))
                return false;

                if(get_all){
                std::string where_column = identifiers.at(1);
                uint16_t where_op = full_tok.at(i+4);
                std::cout<<"selecting all from where you said!"<<std::endl;
                //select(get_all,table_name,column_name,where_column,where_op,identifiers);
                }else{
                std::string where_column = identifiers.at(2);
                uint16_t where_op = full_tok.at(i+3);
                std::cout<<"Selecting what you said from where you said!"<<std::endl;
                //select(get_all,table_name,column_name,where_column,where_op,identifiers);
                };
                break;
                
            }
            case(15):
            {
                if(full_tok.at(i+1)==3)
                //drop(true,indentifiers.at(0)) FOR DATABSE
                std::cout<<"dropping db"<<std::endl;
                else if(full_tok.at(i+1)==11)
                //drop(false,identifiers.at(0)) FOR TABLE
                std::cout<<"dropping table"<<std::endl;
                else
                return false;
            }
            case(16):
            {
                if(full_tok.at(i+1)!=5)
                return false;

                std::string table_name = identifiers.at(0);
                if(full_tok.size()==2){
                //delete(true,table_name) DELETE ALL )true/false) for db/table
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
        }
    }
    return true;
};