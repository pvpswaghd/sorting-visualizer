#include "BubbleSort.h"

BubbleSort::BubbleSort() : Algorithm() {
	t1 = new Thread(std::thread(&BubbleSort::sort, this));
}

BubbleSort::~BubbleSort() {
	delete t1;
}

void BubbleSort::sort() {
	// This keeps running on one thread
	while (!Variables::finished) {
		while (Variables::start) {
			std::cout << "Sorting" << std::endl;
			for (int i = 0; i < Variables::arrSize-1; i++) {
				for (int j = 0; j < Variables::arrSize-i-1; j++) {
					CURSOR_PLACEMENT(j + 1);
					if (heights[j] > heights[j + 1]) {
						std::lock_guard<std::mutex> lock(mtx);
						std::swap(heights[j], heights[j + 1]);
					}
					CHECK_EXIT;
					std::this_thread::sleep_for(std::chrono::milliseconds(Variables::delayMs));
				}
				CHECK_EXIT;
			}
			Variables::finished = Variables::start ? true : false;
			Variables::start = false;
		}
		
	}
	
}