#ifndef __COMMON_SOCKET_H__
#define __COMMON_SOCKET_H__

#include <sys/types.h>
// Wrapper RAII de un socket de c
// No copiable pero sí movible.
class Socket{
    private:
        int file_descriptor;
        void _getaddrinfo(struct addrinfo **address, 
                    const char *host, 
                    const char * service, 
                    bool server);
        explicit Socket(int file_descriptor);

    public:
        Socket();
        ~Socket();
        
        //No se permite la construcción o asignación por copia.
        Socket(const Socket& other) = delete;
        Socket& operator=(const Socket& other) = delete;
        //Pero sí por Movimiento
        Socket(Socket&& other);
        Socket& operator=(Socket&& other);
        
        //Fuerza el cierre del socket.
        void force_stop();

        //Abre una conexión al host y servicio indicados.
        void connect(const char *host, const char *service);
        //Realiza un bind y listen en en host y servicio indicados.
        void listen(const char *host, const char *service, 
                    int max_conn_pool);
        //Acepta una conexión del pool de conexiones 
        //y se la asigna a un nuevo Socket.
        Socket accept();
        
        //Envia longitud bytes del buffer al socket.
        ssize_t send(const char *buffer, size_t length);
        //Recibe length bytes del socket y los guarda en buffer. 
        ssize_t recv(char *buffer, size_t length);
};

#endif
