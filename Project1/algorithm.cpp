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
	if (s == -1)
		selectedAlg = (selectedAlg + 1) % algcount;
	else if (s == -2)
		selectedAlg = (selectedAlg + algcount - 1) % algcount;
	else
		selectedAlg = s;
	if (!working) {
		data.reset_counters();
		view.unmark_all();
	}
	setdesc();
}

void Algorithm::setdesc() {
	switch (selectedAlg)
	{
	case 0:
		algdesc = "Checks if the array is sorted or not. Colors green for sorted blocks and red for unsorted block.";
		break;
	case 1:
		algdesc = "Shuffles the blocks using std::random_shuffle.";
		break;
	case 2:
		algdesc = "Bubblesort O(n^2):: Reading: red";
		break;
	case 3:
		algdesc = "Mergesort O(nlogn):: Reading: red | Writting: Blue | Left: cyan | Right: Yellow";
		break;
	case 4:
		algdesc = "Quicksort O(nlogn): Reading: Red | Swaping elements: Light red | Pivot: Green";
		break;
	case 5:
		algdesc = "Radixsort O(d*(n+b)): Reading: Red | Writting: Blue | Finding Max: Yellow";
		break;
	case 6: 
		algdesc = "InsertionSort O(n^2): Reading: Red | Writting: Blur";
		break;
	case 7:
		algdesc = "Selection Sort O(n^2): Writting: Blue | Finding Min: Purple";
	default:
		break;
	}
}

std::string Algorithm::getalg() {
	return alglist[selectedAlg];
}

void Algorithm::algo() {
	data.reset_counters();
	view.unmark_all();
	switch (selectedAlg)
	{
	case 0:
		Algorithm::check();
		break;
	case 1:
		Algorithm::shuffle();
		break;
	case 2:
		Algorithm::bubblesort();
		data.stopsound();
		Algorithm::check();
		break;
	case 3:
		Algorithm::mergesort();
		data.stopsound();
		Algorithm::check();
		break;
	case 4:
		Algorithm::quicksort();
		data.stopsound();
		Algorithm::check();
		break;
	case 5:
		Algorithm::radixsort();
		data.stopsound();
		Algorithm::check();
		break;
	case 6:
		Algorithm::insertionsort();
		data.stopsound();
		Algorithm::check();
		break;
	case 7:
		Algorithm::selectionsort();
		data.stopsound();
		Algorithm::check();
		break;
	}
	working = false;
}

void Algorithm::check() {
	selectedAlg = 0;
	setdesc();
	int n = data.amount - 1, c = -1;

	view.mark(0, 0x00ff00ff);

	for (c = 0; c < n; c++) {
		float val = data.items[c];
		if (val > data.items[c + 1]) {
			view.mark(c + 1, 0x00ff00ff);
			break;
		}
		data.sound.play(2, 0.5 + (0.5 * val) / data.max_val);
		view.mark(c + 1, 0x00ff00ff);
		std::this_thread::sleep_for(std::chrono::milliseconds(2000 / n));
	}
	sorted = (n == c) ? true : false;
	if (sorted) {
		view.mark(n, 0x00ff00ff);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		data.sound.play(3, 1);
	}
	else
		data.sound.play(4, 1);
}

void Algorithm::shuffle() {
	std::random_shuffle(data.items.begin(), data.items.end());
	sorted = false;
}

void Algorithm::bubblesort() {
	for (int i = 0, n = data.amount; i != n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			view.mark(j, 0x00ff00ff);
			if (data.cmp(j, j + 1) == 1)
				data.b_swap(j, j + 1);
			view.unmark(j);
		}
	}
}

void Algorithm::mergesort() {
	m_ms(0, data.amount - 1);
}

void Algorithm::m_ms(int left, int right) {
	if (left >= right) return;
	int mid = (left + right) / 2;

	m_ms(left, mid);
	m_ms(mid + 1, right);

	m_merge(left, mid, right);
}

void Algorithm::m_merge(int left, int mid, int right) {
	view.mark(left, 0x00ffffff);
	view.mark(right, 0xffff00ff);
	int left_n = mid - left + 1;
	int right_n = right - mid;

	int left_arr[left_n];
	int right_arr[right_n];
	
	for (int i = 0; i < left_n; i++) {
		view.mark(left + i + 1, 0xff0000ff);
		left_arr[i] = data[left + i];
		view.unmark(left+i+1);
	}

	for (int i = 0; i < right_n; i++) {
		view.mark(mid + i + 1, 0xff000ff);
		right_arr[i] = data[mid + i + 1];
		view.unmark(mid + i + 1);
	}

	int i = 0;
	int j = 0;
	int k = left;

	while (i < left_n && j < right_n)
	{
		view.mark(k - 1, 0x0000ffff);
		if (left_arr[i] <= right_arr[j]) {
			data(k, left_arr[i]);
			i++;
		}
		else {
			data(k, right_arr[j]);
			j++;
		}
		view.unmark(k - 1);
		k++;
	}
	while (i < left_n) {
		view.mark(k - 1, 0x0000ffff);
		data(k, left_arr[i]);
		i++;
		view.unmark(k - 1);
		k++;
	}

}