#include "response.hpp"
#include "content_type.hpp"

/*
 Function determines the appripriate response to send to the client.
 */
void *generate_response(struct client *client){
    //Need to parse the header, and see what we were given.
    std::string response_header = "";//Holds response header.
    std::istringstream http_request(client->request);
    std::string line;//LINE
    std::getline(http_request, line);//Grabbing first line, the REQUEST
    std::string line_args[3];
    std::string temp;
    int i = 0;
    //Splicing line into 3 parts; http type, requested file, status.
    for ( std::istringstream stream(line); stream >> temp;){
        line_args[i] = temp;
        i++;
    }
    for (int i = 0; i < 13; i++){
         std::getline(http_request, line);
    }
    
    //We now have an array of args.
    //GET Request. Only going to support GET now.
    if (line_args[0].compare("GET") != 0){
        return NULL;
    }
    if (line_args[1] == "/"){//Return index.html if nothing is particularly requested.
        line_args[1] = "/index.html";
    }
    //Proceeding further. Need to grab the file the GET is for.
    std::string file;
    if (line_args[1] == "/err_style.css")//If error page, it isnt in web directory.
        file = "err_style.css";
    else
        file = "web" + line_args[1];
    std::ifstream req_file;
    req_file.open(file);//Making file input from the given file.
    if (!req_file.is_open()){
        std::cerr << "~ File " << file << " not found." << std::endl;
        response_header = "HTTP/1.1 404 Not Found";//Couldnt find file. Will return the error_page.html
        line_args[1] = "/error_page.html";//Returning the NEW file.
        req_file.open("error_page.html");
        if (!req_file.is_open()){
            //Missing files.
           return NULL;
        }
    }
    else{
        response_header = "HTTP/1.1 200 OK";//OK, valid response header
    }
    
    std::string file_content = "";
    //Will PRIMARILY be writing this to html file...
    while (std::getline(req_file, temp)){
        file_content += temp;
    }
    req_file.close();
    
    std::string content_type = find_content_type(line_args[1]);//Finding content type to return.
    std::string str = response_header + "\nContent-Type: " + content_type + "\nContent-Length: " + std::to_string(file_content.length()) + "\n\n" + file_content;
    const char* resp = str.c_str();
    send(client->socket_fd, resp , strlen(resp), 0);//SENDING response to the client!
    close(client->socket_fd);
    delete(client);//Freeing/deleting the client struct used.
    return NULL;
}

/*
 Function finds the proper content type to send as part of HTTP response
 */
std::string find_content_type(std::string req){
    //req is file requested. Extension hints at what content type we need.
    //Finding last index of '.', then finding the extension of the file.
    int index = -1;
    for (int i = (int) req.length()-1; i >= 0; i--){
        if (req.at(i) == '.'){
            index = i;
            break;
        }
    }
    if (index == -1){
        return "text/plain";//Errorl not a valid file.
    }
    std::string type = req.substr(index+1, req.length()-1);
    //Parsed the file type. Seeing which content-type this corresponds to...
    if (type == "js"){
        type = "javascript";//js == javascript.
    }
    else if (type == "ico"){//ico is weird. ico == vnd.microsoft.ico
        type = "vnd.microsoft.icon";
    }
    else if (type == "svg"){//ico is weird. ico == vnd.microsoft.ico
        type = "svg+xml";
    }
    if (std::find(std::begin(text), std::end(text), type) != std::end(text)){
        //We found the file in this content-type.
        return "text/" + type;
    }
    else if (std::find(std::begin(image), std::end(image), type) != std::end(image)){
        return "image/" + type;
    }
    else if (std::find(std::begin(application), std::end(application), type) != std::end(application)){
        return "application/" + type;
    }
    else if (std::find(std::begin(font), std::end(font), type) != std::end(font)){
        return "font/" + type;
    }
    else if (std::find(std::begin(video), std::end(video), type) != std::end(video)){
        return "video/"+ type;
    }
    else if (std::find(std::begin(multipart), std::end(multipart), type) != std::end(multipart)){
        return "multipart/"+ type;
    }
    else if (std::find(std::begin(message), std::end(message), type) != std::end(message)){
        return "message/" + type;
    }
    else if (std::find(std::begin(audio), std::end(audio), type) != std::end(audio)){
        return "audio/" + type;
    }
    else if (std::find(std::begin(model), std::end(model), type) != std::end(model)){
        return "model/" + type;
    }
    else{
        return "text/plain";
    }
}
