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
#include <sstream>
#include <fstream>
#include <string.h>
#define DELIM " "

std::string generate_response(char *request);
std::string find_content_type(std::string request);//Gives what content type we need for this



