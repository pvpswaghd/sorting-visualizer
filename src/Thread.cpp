#include "../include/Thread.h"
#include <stdexcept>

Thread::Thread(std::thread t) : t_(std::move(t)) {
    if (!t_.joinable()) {
        throw std::logic_error("No thread");
    }
}

Thread::~Thread() {
    if (t_.joinable()) {
        t_.join();
    }
}

Thread::Thread(Thread&& t) : t_(std::move(t.t_)) { }

Thread& Thread::operator=(Thread&& t) {
    if (t_.joinable()) {
        t_.join();
    }
    t_ = std::move(t.t_);
    return *this;
}


