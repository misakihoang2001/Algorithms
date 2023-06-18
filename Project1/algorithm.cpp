#include "algorithm.h"

Algorithm::Algorithm(Blocks& b, Viewer& v) :data(b), view(v) {
	setalg(0);
	working = false;
	sorted = true;
	algcount = alglist.size();
}

void Algorithm::start() {
	if (working) return;
	working = true;
	if (sortingThread.joinable())
		sortingThread.join();
	sortingThread = std::thread(&Algorithm::algo, this);
}

void Algorithm::stop() {
	working = false;
	sortingThread.detach();
}

void Algorithm::setalg(int s) {

}