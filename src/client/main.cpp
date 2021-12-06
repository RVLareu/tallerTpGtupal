
#include "client.h"


int main(int argc, char** argv){

    if (argc != 3) {
        std::cout << "Invalid arguments, must be host port";
        return 0;
    }
    
    char* host = argv[1];
    char* port = argv[2];

    Client client(host, port);
    client.run();
    return 0;
}