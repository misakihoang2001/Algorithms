#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "blocks.h"
#include "Viewer.h"

#include <algorithm>
#include <vector>

#include <iostream>
#include <string>

class Algorithm {
private:
	Blocks& data;
	Viewer& view;

	std::thread sortingThread;

	int algcount;

	void algo();

	void check();
	void shuffle();
	void bubblesort();
	void mergesort();
	void quicksort();
	void radixsort();
	void insertionsort();
	void selectionsort();

	void m_ms(int left, int right);
	void q_qs(int low, int high);
	void r_cs(int place);

	void m_merge(int left, int mid, int right);
	int q_fix(int left, int mid, int right);
	int r_max();

	const std::vector<std::string> alglist = { "Check", "Shuffle", "Bubblesort", "Mergesort", "Quicksort", "Radixsort", "Insertionsort", "Selectionsort" };

	void setdesc();
public:
	Algorithm(Blocks& data_array, Viewer& view);

	void start();
	void stop();

	bool working;
	bool sorted;

	int selectedAlg;
	std::string algdesc;

	void setalg(int algnumber);

	std::string getalg();


};

#endif // !ALGORITHM_H
