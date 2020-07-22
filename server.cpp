#include "server.hpp"
#include "response.hpp"
#define PORT 8080
#define MAX_BUF_LENGTH 8192

/*
 Main function concerning our server code. Starts server, listens on port, handles requests.
 */
int server(int argc, const char * argv[]){
    int server_fd, new_socket;
    long valread;
    struct sockaddr_in address;
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //Creating, binding, and accepting connections on a socket.
    int addrlen = sizeof(address);
    //SOCKET CREATION
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        std::cerr << "ERROR occured in socket creation." << std::endl;
        return EXIT_FAILURE;
    }
    
    const int trueFlag = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &trueFlag, sizeof(int)) < 0)
        std::cerr << "Error! " << std::endl;
    
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
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::cout << "WEB Server Started." << std::endl;
    //CONNECTION LOOP; WAITING FOR CLIENTS
    
    std::vector<char> buffer(MAX_BUF_LENGTH);
    struct client c;//Struct holding client items.
    while (1){
        //ACCEPTING CONENCTIONS FROM PORT
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0){
            std::cerr << "ERROR accepting connection at specified port." << std::endl;
            return EXIT_FAILURE;
        }
        std::cout << "INCOMING connection from port " << address.sin_port << std::endl;
        
        //Reading from client the HTTP request.
        if ((valread = read(new_socket, &buffer[0], buffer.size())) < 0){
            std::cerr << "ERROR reading from client socket!" << std::endl;
            return -1;
        }
        //MOVING TO THE RESPONSE FUNCTION.CREATE THREAD, PASS REQUEST TO RESPONSE FUNCTION!
        std::string request(buffer.begin(), buffer.end());
        std::string response_string;
        //We have the request. We now need to pass this request to a thread.
        struct client *c = new client();
        c->socket_fd = new_socket;
        c->request = request;
        std::thread t(generate_response, c);//Creating a new thread to handle this clients request.
        t.detach();//Detaching thread, so it may handle its own termination
    }
    return 0;
}
