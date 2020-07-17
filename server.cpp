//
//  server.cpp
//  web_server
//
//  Created by James Lungu on 7/17/20.
//  Copyright © 2020 James Lungu. All rights reserved.
//

#include "server.hpp"
#define PORT 8080

/**
 Main function concerning our server code. Starts server, listens on port, handles requests.
 */
int server(int argc, const char * argv[]){
    int server_fd, new_socket;
    long valread;
    struct sockaddr_in address;
    
    int addrlen = sizeof(address);
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    
    
    //SOCKET CREATION
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        std::cerr << "ERROR occured in socket creation." << std::endl;
        return EXIT_FAILURE;
    }
    
    //BINDING ADDRESS TO SOCKET 
    memset((char *)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
        std::cerr << "ERROR occured in binding socket to address." << std::endl;
        return EXIT_FAILURE;
    }
    
    //LISTENING ON SPECIFIC PORT
    if (listen(server_fd, 3) < 0){
        std::cerr << "ERROR listening at specified port." << std::endl;
        return EXIT_FAILURE;
    }
    
    std::cout << "WEB Server Started" << std::endl;
    //CONNECTION LOOP; WAITING FOR CLIENTS
    while (1){
        std::cout << "AWAITING connection..." << std::endl;
        //ACCEPTING CONENCTIONS FROM PORT
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0){
            std::cerr << "ERROR accepting connection at specified port." << std::endl;
            return EXIT_FAILURE;
        }
        std::cout << "INCOMING connection from port " << address.sin_port << std::endl;
        std::cout << "Client port#" << address.sin_port << " connected" << std::endl;
        char buffer[30000];
        valread = read(new_socket, buffer, 30000);
        std::cout << buffer;
        write(new_socket, hello, strlen(hello));
        std::cout << hello << strlen(hello) << std::endl;
        std::cout << "SENT RESPONSE" << std::endl;
        close(new_socket);
    }
    
    return 0;
}
