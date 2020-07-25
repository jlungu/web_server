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
    std::cout << "~~~~~JSERVER v1.0.0~~~~~" << std::endl;
    
    struct hostInfo host = getHostNetworkAddresses();//Grabbing host info.
    
    std::cout << "Select ENTER for default option." << std::endl << std::endl;
    std::string input;
    int selection;
    bool valid;
    int port = 0;
    while (1){//Loops until we get a valid input.
        std::cout << "Select an IP Address to host server on: " << std::endl;
        for (int i = 0; i < host.networkAddresses.size(); i++){
            if (host.networkAddresses[i] == "127.0.0.1"){
                std::cout << (i+1) << ") " << host.networkAddresses[i] << " (default)" << std::endl;
            }
            else{
                std::cout << (i+1) << ") " << host.networkAddresses[i] << std::endl;
            }
            
        }
        std::cout << "Enter SELECTION: ";
        std::getline(std::cin, input);
        //std::cin >> input;//Inputting users selection.
        if (input.length() == 0){
            //Choosing default option
            selection = 0;
            break;
        }
        valid = (input.find_first_not_of( "0123456789" ) == std::string::npos);//Checks if input is an int.
        if (!valid){
            std::cout << "Invalid selection." << std::endl;
            continue;
        }
        selection = std::stoi(input);
        if (selection < 1 || selection > host.networkAddresses.size()){
            std::cout << "Invalid selection." << std::endl;
            continue;
        }
        break;//Valid selection
    }
    std::string address;
    if (selection == 0){
        //Choost default.
        address = "127.0.0.1";
    }
    else{
         address = host.networkAddresses[selection-1];
    }
    while(1){
        std::cout << "Select PORT (default 8080): ";
        input = "";
        std::getline(std::cin, input);
        if (input ==  ""){
            port = 8080;
            break;
        }
        valid = (input.find_first_not_of( "0123456789" ) == std::string::npos);//Checks if input is an int.
        if (!valid){
            std::cout << "Invalid PORT." << std::endl;
            continue;
        }
        break;
    }
    if (input != ""){
        port = std::stoi(input);
    }
  
    server(address, port, host.hostName);//Starts our main server.
    return 0;
}
