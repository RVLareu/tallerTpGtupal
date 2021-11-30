#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__
#include <queue>
#include <mutex>
#include <string>
#include <condition_variable>

class BlockingQueue{
    private:
        std::mutex mutex;
        std::condition_variable condition_variable;
        std::queue<std::vector<char>> queue;
        bool open;
    public:
        BlockingQueue();
        void close();
        //Inserta un elemento en la última posicion de la cola.
        void push(const std::vector<char>& item);
        //Quita el primer elemento de la cola y lo devuelve.
        std::vector<char> pop();
};

#endif
