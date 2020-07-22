//
//  main.cpp
//  web_server
//
//  Created by James Lungu on 7/17/20.
//  Copyright © 2020 James Lungu. All rights reserved.
//

#include <iostream>
#include "server.hpp"

int main(int argc, const char * argv[]) {
    std::cout << "~~~~~JSERVER v0.0.0~~~~~" << std::endl;
    server(argc, argv);//Starts our main server.
    return 0;
}
