#pragma once

#include "Algorithm.h"


class HeapSort : public Algorithm {
public:
	HeapSort();
	~HeapSort();
	void heapify(int n, int i);
	void sort();
};