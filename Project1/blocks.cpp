#include "blocks.h"

Blocks::Blocks(int a, int m, sound_effect& s) :sound(s) {
	amount = a;
	max_val = m;

	setdelay(100);
	reset_counters();

	items.clear();

	for (int i = 1; i <= amount; i++) {
		items.push_back(i * m / a);
	}
}

int Blocks::cmp(int i, int j) {

	counter.c++;

	int a = this->operator[](i);
	int b = this->operator[](j);

	if (a == b)
		return 0;
	else if (a < 0)
		return -1;
	else
		return 1;
}

void Blocks::stopsound() {
	sound.stop();
}

void Blocks::b_swap(int i, int j) {

	counter.c++;

	int t = this->operator[](i);
	this->operator()(i, this->operator[](j));
	this->operator()(j, t);
}

void Blocks::reset_counters() {
	counter.c = 0;
	counter.r = 0;
	counter.w = 0;
	counter.s = 0;
}

void Blocks::setdelay(int d) {
	if (d >= 0) {
		r_delay = d;
		w_delay = d;
	}
	else if (d == -1) {
		r_delay += 100;
	}
	else if (d == -2 && r_delay >= 100) {
		r_delay -= 100;
	}
	else if (d == -3)
		w_delay += 100;
	else if (d == -4 && w_delay >= 100)
		w_delay -= 100;
	else if (d == -5)
		r_delay += 1000;
	else if (d == -6 && r_delay >= 1000)
		r_delay -= 1000;
	else if (d == -7)
		w_delay += 1000;
	else if (d == -8 && w_delay >= 1000)
		w_delay -= 1000;
}

float Blocks::operator[](int i) {
	if (i >= amount) {
		std::cout << "Out of bond value " << i << "Selected!";
		return 0;
	}
	counter.s++;
	float val = items[i];
	sound.play(0, 0.5 + 1 * val / max_val);

}