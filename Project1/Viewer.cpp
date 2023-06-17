#include "Viewer.h"

Viewer::Viewer(int w, int h, Blocks& b) :blk(b) {
	width = w;
	height = h;
	r_dx = (float)width / blk.amount;

	rects = std::vector<sf::RectangleShape>(blk.amount);

	cols = std::vector<sf::Color>(blk.amount, sf::Color::White);

	texture.create(width, height);
	this->setTexture(texture.getTexture());
}


void Viewer::render() {
	texture.clear();
	for (int i = 0, j = rects.size(); i < j; i++) {
		float h = blk.items[i];

		rects[i].setSize(sf::Vector2f(r_dx, h));
		rects[i].setPosition(i * r_dx, height - h);
		rects[i].setFillColor(cols[i]);
		texture.draw(rects[i]);
	}
	texture.display();
}

void Viewer::mark(int i, uint32_t c) {
	if (i >= rects.size()) return;
	cols[i] = sf::Color(c);
}

void Viewer::mark(int s, int e, uint32_t c) {
	std::fill(cols.begin() + s, cols.begin() + e, sf::Color(c));
}

void Viewer::unmark(int i) {
	if (i >= rects.size()) return;
	cols[i] = sf::Color::White;
}

void Viewer::unmark(int s, int e) {
	std::fill(cols.begin() + s, cols.begin() + e, sf::Color::White);
}

void Viewer::unmark_all() {
	std::fill(cols.begin(), cols.end(), sf::Color::White);
}

void Viewer::colorizer(int index) {
	rects[index].setFillColor(sf::Color::White);
}