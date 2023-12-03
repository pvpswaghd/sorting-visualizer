#pragma once

#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>

#include <thread>

class Thread {
public:
    explicit Thread(std::thread t);
    ~Thread();
    Thread(Thread&& t);
    Thread& operator=(Thread&& t);

    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

private:
    std::thread t_;
};