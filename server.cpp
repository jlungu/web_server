#include "server.hpp"
#include "response.hpp"
#define PORT 8080
#define MAX_BUF_LENGTH 8192

/*
 Main function concerning our server code. Starts server, listens on port, handles requests.
 */
int server(std::string hostAddress, int port, std::string hostName){
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
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(hostAddress.c_str());
    
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
    std::cout << std::endl <<  "~~~~~WEB Server Started~~~~~" << std::endl;
    std::cout << "WEB ADDRESS: http://" << hostAddress << ":" << port << std::endl;
    std::cout << "MACHINE: "<< hostName << std::endl;
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
/*
 Grabs host info for the web server.
 */
struct hostInfo getHostNetworkAddresses(){
    char ac[80];
    struct hostInfo h;
    if (gethostname(ac, sizeof(ac)) < 0){
        std::cerr << "Error when loading local host name. Exiting..." << std::endl;
        exit(1);
    }
    h.hostName = std::string(ac);//Adding the host name to the struct we'll return.
    struct hostent *phe = gethostbyname(ac);//Grabbing struct depicting host info from hostname.
    if (phe == 0){
        std::cerr << "BAD HOST LOOKUP" << std::endl;
        exit(1);
    }
    for (int i = 0; phe->h_addr_list[i] != 0; i++){
        struct in_addr addr;
        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
        h.networkAddresses.push_back(inet_ntoa(addr));//Pushing the address to our VECTOR of addresses.
    }
    return h;
}
