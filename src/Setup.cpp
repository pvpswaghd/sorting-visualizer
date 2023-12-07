#include "Setup.h"
#include "Sound.h"


void Setup::initialize() {
	//Sound::initialize(Variables::arrSize);
	Setup::shuffle();
	sorter = std::make_unique<BubbleSort>();
}


void Setup::shuffle(){
	std::cout << heights.size() << std::endl;
	std::iota(heights.begin(), heights.end(), 1);
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(heights.begin(), heights.end(), g);
}

void Setup::showVectorContent(){
	for (auto i : heights) {
		std::cout << i << std::endl;
	}
}

void Setup::switchAlgo() {
	Variables::start = false;
	Variables::finished = true;
	sorter.reset();
	Setup::shuffle();
	Variables::finished = false;
	switch (Variables::option) {
	case 0:
		sorter = std::make_unique<BubbleSort>();
		break;
	case 1:
		sorter = std::make_unique<HeapSort>();
		break;
	}
}
