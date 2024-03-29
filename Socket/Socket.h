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

// struct sockaddr {
//     unsigned short    sa_family;    // address family, AF_xxx
//     char              sa_data[14];  // 14 bytes of protocol address
// }; 

// struct addrinfo {
//     int              ai_flags;     // AI_PASSIVE, AI_CANONNAME, etc.
//     int              ai_family;    // AF_INET, AF_INET6, AF_UNSPEC
//     int              ai_socktype;  // SOCK_STREAM, SOCK_DGRAM
//     int              ai_protocol;  // use 0 for "any"
//     size_t           ai_addrlen;   // size of ai_addr in bytes
//     struct sockaddr *ai_addr;      // struct sockaddr_in or _in6
//     char            *ai_canonname; // full canonical hostname

//     struct addrinfo *ai_next;      // linked list, next node
// };

// Internet address (a structure for historical reasons)
// struct in_addr {
//     uint32_t saddr; // that's a 32-bit int (4 bytes)
// };

// struct sockaddr_in {
//     short int          sin_family;  // Address family, AF_INET
//     unsigned short int sin_port;    // Port number
//     struct in_addr     sin_addr;    // Internet address
//     unsigned char      sin_zero[8]; // Same size as struct sockaddr
// };

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
    socket_query get_query();
    void execute_query(SOCKET* fd, Keyword_List &res, std::unordered_map<std::string,uint16_t>operators, std::string query, Run* obj);
};

