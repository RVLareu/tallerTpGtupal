
#include "client.h"
#include "yaml-cpp/yaml.h"

// Carga archivo de config
YAML::Node config = YAML::LoadFile("/etc/quantum-chess/config.yaml");
std::string ASSETS_PATH = config["ASSETS_PATH"].as<std::string>();

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