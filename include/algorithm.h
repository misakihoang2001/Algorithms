#ifndef ALGRITHM_H
#define ALGOITHM_H

#include <algorithm>
#include <vector>

#include <iostream>
#include <string>

class Algorithms {
private:
	Block& data;
	Viewer& view;

	std::thread sotringThread;

	int algcount;

	void algo();

	void check();
	void shuffle();
	void bubblesort();
	void mergesort();	void m_ms(int left, int right);
	void quicksort();	void q_qs(int low, int high);
	void radixsort();	void r_cs(int place);
	void insertionsort();
	void selectionsort();

	const std::vector<std::string> alglist = { "Check", "Shuffle", "Bubblesort", "Mergesort", "Quicksort", "Radixsort", "InsertionSort", "SelectionSort" };
	void setdesc();

public:

	Algorithms(Block& data_array, Viewer& view);

	void start();
	void stop();

	bool working;
	bool sorted;
	int selectedAlg;
	std::string algdesc;

	void setalg(int algnumber);

	std::string getalg();
};

#endif
