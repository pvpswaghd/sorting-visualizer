#pragma once

#include "Variables.h"
#include "Algorithm.h"
#include "BubbleSort.h"
#include "HeapSort.h"
#include <random>
#include <numeric>
#include <iostream>

class Setup {
public:
	inline static std::unique_ptr<Algorithm> sorter;
	static void initialize();
	static void switchAlgo();
	static void shuffle();
	static void showVectorContent();
};
