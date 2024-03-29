
#include "run.h"
#include "Socket/Socket.h"
#include "Lexer/list.h"

KW_OP kw_ops;
int main()
{
    try{
        Run obj;
        obj.run();
        obj.tree_rel.search_catalog(1141,28);
        obj.tree_ind.rel = obj.tree_rel.info.rel.rows[obj.tree_rel.info.index];
        obj.tree_rel.search_catalog(1149,28);
        obj.tree_rel.rel = obj.tree_rel.info.rel.rows[obj.tree_rel.info.index];
        obj.tree_rel.search_catalog(1269,28);
        obj.tree_attr.rel = obj.tree_rel.info.rel.rows[obj.tree_rel.info.index];
        
        Server server;
        while(true){
            socket_query info = server.get_query();
            server.execute_query(&info.current_socket, kw_ops.res_list, kw_ops.operators, info.query, &obj);
        }

    }catch(std::string val){
        std::cerr<<val<<std::endl;
    }
};