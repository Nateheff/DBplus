
#include "scanner.h"
#include <iostream>
#include <algorithm>

bool Scanner::scanner_run(){
    // std::cout<<scan_buf.length()<<std::endl;
    for(size_t i = 0; i < scan_buf.length();i++){ 
        
        if(scan_buf.at(i) != ' '&& scan_buf.at(i)!=scan_buf.back()){
            if(op_set.find(std::string{scan_buf.at(i)}) != op_set.end()){
                std::cout<<"Op: "<<scan_buf.at(i)<<" ";
                full_tok.push_back(op_set[std::string{scan_buf.at(i)}]);
                
            }else
            term += scan_buf.at(i);
            
            
        }else{
            if(get_kw_tok(term) > kw_list->num_kw  && op_set.find(term)==op_set.end() && term.length()>0){
                
                std::cout<<"ID: "<<term<<" ";
                identifiers.push_back(term);
                
                term.clear();
            }else if(get_kw_tok(term) < kw_list->num_kw){
                
                std::cout<<"Command: "<<term<<" ";
                full_tok.push_back(get_kw_tok(term));
                term.clear();
            // }else if(op_set.find(term) != op_set.end()){
            //     std::cout<<"Op: "<<term<<" ";
            //     full_tok.push_back(op_set[term]);
            //     term.clear();
            }else if(scan_buf.at(i)==' ')
            continue;
            else
            return false;
        };

    };
    std::cout<<std::endl;
    return true;
};

uint16_t Scanner::get_kw_tok(std::string command){
    if(command.length() > kw_list->max_leng)
    return kw_list->num_kw+1;
 
    std::transform(command.begin(),command.end(),command.begin(),[](unsigned char c){return tolower(c);});
    
    auto check = kw_list->kws.find(command);
    if(check == kw_list->kws.end())
        return kw_list->num_kw+1;

    return check->second;
};

void Scanner::print_query(){
    for(uint16_t tok: full_tok)
    std::cout<<tok<<" "<<std::endl;
};

