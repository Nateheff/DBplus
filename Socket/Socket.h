#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdint.h>
#include <iostream>

#include "../Lexer/list.h"
#include "../run.h"

#define DEFAULT_SERVER "127.0.0.1"
#define DEFAULT_PORT "3490"
#define MAX_QUERY 0xFFFFF


struct socket_query{
    SOCKET current_socket;
    std::string query;
};

class Server{
    private:
    WSADATA wsaData;
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    struct addrinfo hints, *res;
    int sockfd, new_fd;
    SOCKET sock;

    public:

    Server();
    ~Server();
    std::string get_query(SOCKET* fd);
    SOCKET get_connection();
    void execute_query(SOCKET* fd, Keyword_List &res, std::unordered_map<std::string,uint16_t>operators, std::string query, Run* obj);
};

