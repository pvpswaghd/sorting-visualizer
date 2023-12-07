#include "Algorithm.h"

Algorithm::Algorithm(){

}

Algorithm::~Algorithm() {

}

void Algorithm::CURSOR_PLACEMENT(int i) {
	Variables::cursorPos = i;
	Variables::cursorSize[0] = heights[i];
}