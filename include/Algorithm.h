#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>

class Algorithm {
protected:
	std::atomic<bool> start, isFinished;
	std::atomic<bool> paused;
public:
	void start();
	void stop();
	void pause_and_resume();
	
	bool returnStart();
	bool isFinished();
		
};