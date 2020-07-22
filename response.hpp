//
//  response.hpp
//  web_server
//
//  Created by James Lungu on 7/17/20.
//  Copyright © 2020 James Lungu. All rights reserved.
//

#ifndef response_hpp
#define response_hpp
#endif /* response_hpp */

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#define DELIM " "

//Wraps client request & file descriptor in a struct, for simplicity.
struct client {
    int socket_fd;
    std::string request;
};

void *generate_response(struct client *client);//Generates HTTP response for given client.
std::string find_content_type(std::string request);//Gives what content type we need for this



