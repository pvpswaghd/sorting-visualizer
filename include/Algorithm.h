#pragma once

#include "Thread.h"
#include "Variables.h"
#include <iostream>
#include <atomic>
#include <thread> 
#include <mutex>
#include <algorithm>

#define CHECK_EXIT if(!Variables::start && Variables::finished) return;

class Algorithm {
protected:
	std::mutex mtx;
	Thread* t1;
public:
	Algorithm();
	virtual ~Algorithm();
	virtual void sort() = 0; //pure virtual function
	
	void CURSOR_PLACEMENT(int i);
	bool returnStart();
	bool isFinished();
		
};