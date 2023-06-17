#ifndef BLOCKS_H
#define BLOCKS_H

#include <thread>
#include <chrono>
#include <vector>
#include <iostream>

#include "sound_effect.h"

class Blocks {
public:
	int amount;
	int max_val;
	int r_delay;
	int w_delay;

	struct COUNTERS
	{
		int c;
		int r;
		int w;
		int s;
	}counter;

	std::vector<int> items;

	sound_effect& sound;

	Blocks(int amount, int max_val, sound_effect& sound_obj);

	int cmp(int left, int right);
	void b_swap(int a, int b);
	void stopsound();

	void reset_counters();
	void setdelay(int delay_time);

	float operator[](int);
	void operator()(int, int);
};

#endif // !BLOCKS_H
