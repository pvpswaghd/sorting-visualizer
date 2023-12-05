#pragma once
#include <atomic>
#include <vector>
#include <mutex>

struct Variables {
	inline static unsigned int arrSize = 20; // default size of the vector
	inline static int cursorPos = 1;
	inline static int cursorSize[1] = { 1 };
	inline static int delayMs = 50;
	inline static int option = 0;
	inline static std::atomic<bool> start = false, reset = false, finished = false;
	inline static const char* algoNames[] = { "BubbleSort", "HeapSort" };
	inline static std::condition_variable cv;
	inline static std::mutex cv_m;
};

inline extern std::vector<int> heights(Variables::arrSize);