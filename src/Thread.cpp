#include "../include/Thread.h"
#include <stdexcept>
#include <iostream>

Thread::Thread(std::thread t) : t_(std::move(t)) {
    if (!t_.joinable()) {
        throw std::logic_error("No thread");
    }
    std::cout << "Thread started" << std::endl;

}

Thread::~Thread() {
    if (t_.joinable()) {
        t_.join();
    }
    std::cout << "Thread destroyed" << std::endl;
}

Thread::Thread(Thread&& t) : t_(std::move(t.t_)) { }

Thread& Thread::operator=(Thread&& t) {
    if (t_.joinable()) {
        t_.join();
    }
    t_ = std::move(t.t_);
    return *this;
}


