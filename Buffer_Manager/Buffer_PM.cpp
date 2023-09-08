#include "Buffer_PM.h"

Node* Buffer_Pool::get_page(uint16_t page_num){
    
    while(true){
    if(pool.size()>0 && pool.size()<=pool.capacity()){//if it find the page in the pool it returns and it ends here
        for(auto frame:pool){
            if(frame.id()==page_num){
            frame.add_pin();
            std::cout<<"YES"<<std::endl;
            return frame.get_page();
            }else
            std::cout<<"downing"<<std::endl;
            frame.down_pin();
        };
     };
    if(pool.size()< pool.capacity()){//if the page isn't found in the pool and there's still room in the pool, just add a new page.
    Frame* space = new Frame; 
    std::cout<<"Here 4: "<<space->get_page()<<std::endl;
    dsm->read_page(page_num,space->get_page());
    space->add_pin();
    pool.push_back(*space);
    return space->get_page();
    };
    std::cout<<"almost"<<std::endl;
    for(auto frame: pool){//if the page isn't in the pool, and there isn't any more room in the pool, we use our replacement policy.
    frame.down_pin();
        if(frame.pin()==0){
            if(frame.is_dirty())
            dsm->write_page(frame.get_page(),frame.id());
            std::cout<<"using replacement"<<std::endl;
            dsm->read_page(page_num,frame.get_page());
            return frame.get_page();
        }
    }
    };
};
    /*
    while(!in){
        
    for(size_t i = 0;i<pool.capacity();i++){
        if(pool.capacity()!=pool.size())
        {
            
            Frame* space = new Frame;
            std::cout<<"Here 4: "<<space->get_page()<<std::endl;
            dsm->read_page(page_num,space->get_page());
            space->add_pin();
            pool.push_back(*space);
            std::cout<<pool.at(i).get_page()<<std::endl;
            return space->get_page();
        }
        else if(pool.at(i).id()==page_num)
        {
            std::cout<<"1"<<std::endl;
        pool.at(i).add_pin();
        in = true;
        return pool.at(i).get_page();
        }
        else if(pool.at(i).pin()==0 && pool.at(i).id()!=page_num)
        {
        in = true;
        std::cout<<"here 2"<<std::endl;
        if(pool.at(i).is_dirty());
            dsm->write_page(pool.at(i).get_page(),pool.at(i).id());

        dsm->read_page(page_num,pool.at(i).get_page());
        pool.at(i).add_pin();
        return pool.at(i).get_page();
        }
        else if(pool.at(i).pin()>0 && pool.at(i).id()!=page_num)
        {
        pool.at(i).down_pin();
        std::cout<<"Here 3"<<std::endl;
        }
        
        
        
    };
    };
*/


bool Buffer_Pool::release_page(uint16_t page_num){

};