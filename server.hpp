//
//  server.hpp
//  web_server
//
//  Created by James Lungu on 7/17/20.
//  Copyright © 2020 James Lungu. All rights reserved.
//

#ifndef server_hpp
#define server_hpp

#endif /* server_hpp */

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <fstream>
#include <thread>
#include <vector>
#include <arpa/inet.h>
#include <netdb.h>

struct hostInfo {
    std::string hostName;
    std::vector<std::string> networkAddresses;//Vector for addresses
};

//FUNCTION PROTOTYPES
int server(std::string hostAddress, int port, std::string hostName);//Main server function; waiting and accepting for connections
struct hostInfo getHostNetworkAddresses();
