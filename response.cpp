#include "response.hpp"

/*
 Function determines the appripriate response to send to the client.
 */
std::string generate_response(char *request){
    //Need to parse the header, and see what we were given.
    std::cout << request << std::endl;
    std::istringstream http_request(request);
    std::string line;//LINE
    std::getline(http_request, line);//Grabbing first line, the REQUEST
    std::string line_args[3];
    std::string temp;
    int i = 0;
    for ( std::istringstream stream(line); stream >> temp;){
        line_args[i] = temp;
        i++;
    }
    //We now have an array of args.
    //GET Request. Only going to support GET now.
    if (line_args[0].compare("GET") != 0){
        return NULL;//NULL implies error.
    }
    //Proceeding further. Need to grab the file the GET is for.
    std::string file = "web" + line_args[1];
    std::ifstream req_file;
    req_file.open(file);//Making file input from the given file.
    if (!req_file.is_open()){
        std::cerr << "~ File " << file << " not found." << std::endl;
        return "";
    }
    std::string file_content = "";
    //Will PRIMARILY be writing this to html file...
    while (std::getline(req_file, temp)){
        file_content += temp;
    }
    req_file.close();
    return file_content;
}
