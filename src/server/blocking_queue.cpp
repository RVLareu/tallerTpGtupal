#include <mutex>
#include <vector>
#include <iostream>
#include "./blocking_queue.h"

BlockingQueue::BlockingQueue(): 
                            queue(),
                            open(true){}
void BlockingQueue::close(){
    std::unique_lock<std::mutex> unique_lock(this->mutex);
    this->open = false;
    this->condition_variable.notify_all();
} 
void BlockingQueue::push(const std::vector<char> &item){
    std::unique_lock<std::mutex> unique_lock(this->mutex);
    this->queue.push(item);
    this->condition_variable.notify_all();
} 
std::vector<char> BlockingQueue::pop(){
    std::unique_lock<std::mutex> unique_lock(this->mutex);
    while (this->queue.empty()){        
        if (!this->open){
            throw "BlockingQueue Closed";
        }
        this->condition_variable.wait(unique_lock);
    }
    std::vector<char> item = this->queue.front();
    this->queue.pop();
        
    return item;
} 
