#include "Socket.h"
#include "../Lexer/scanner.h"


Server::Server(){
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    getaddrinfo(DEFAULT_SERVER, DEFAULT_PORT, &hints, &res);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
}

socket_query Server::get_query(){

    if(bind(sockfd, res->ai_addr, res->ai_addrlen)==-1){
        closesocket(sockfd);
        perror("server: bind");
    }

    if(listen(sockfd, 10)==-1){
        perror("listen");
        exit(1);
    }

    
    addr_size = sizeof(their_addr);

    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    if(new_fd == -1){
        perror("accept");
    }

    char buff[4096];
    int buff_len = recv(new_fd, buff, 4096, 0);
    if(buff_len == -1){
        perror("receive");
    }

    std::string query(buff);
    socket_query output;
    output.query = query;
    output.current_socket = new_fd;
    return output;

}

void Server::execute_query(SOCKET* fd, Keyword_List &res_list, std::unordered_map<std::string,uint16_t>operators, std::string query, Run* obj){
    Scanner scanner(query, &res_list, operators);
    scanner.scanner_run();

    std::string response = receiver_main(scanner.full_tok, scanner.identifiers, &res_list, obj);


}