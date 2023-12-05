#pragma once
#include "../include/HeapSort.h" 

HeapSort::HeapSort() : Algorithm() {
	t1 = new Thread(std::thread(&HeapSort::sort, this));
	std::cout << "HeapSort Thread" << std::endl;
}

HeapSort::~HeapSort() {
	delete t1;
}

void HeapSort::heapify(int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && heights[left] > heights[largest])
		largest = left;
	if (right < n && heights[right] > heights[largest])
		largest = right;
	
	if (largest != i) {
		std::swap(heights[i], heights[largest]);
		CURSOR_PLACEMENT(largest);
		heapify(n, largest);
	}
	else {
		CURSOR_PLACEMENT(largest);
	}
}

void HeapSort::sort() {
	// This keeps running on one thread
	while (!Variables::finished) {
		while (Variables::start) {
			std::cout << "Sorting" << std::endl;
			for (int i = Variables::arrSize / 2 - 1; i >= 0; i--) {
				CHECK_EXIT;
				std::lock_guard<std::mutex> lock(mtx);
				CURSOR_PLACEMENT(i);
				heapify(Variables::arrSize, i);
				std::this_thread::sleep_for(std::chrono::milliseconds(Variables::delayMs));
			}
			CHECK_EXIT;
			for (int i = Variables::arrSize - 1; i >= 0; i--) {
				CHECK_EXIT;
				std::lock_guard<std::mutex> lock(mtx);
				std::swap(heights[0], heights[i]);
				CURSOR_PLACEMENT(i);
				heapify(i, 0);
				std::this_thread::sleep_for(std::chrono::milliseconds(Variables::delayMs));
			}
			Variables::finished = Variables::start ? true : false;
			Variables::start = false;
		}
	}

}