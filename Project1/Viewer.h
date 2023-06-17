#ifndef VIEWER_H
#define VIEWER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <deque>
#include <list>
#include <tuple>

#include "blocks.h"

class Viewer : public sf::Sprite {
private:
	sf::RenderTexture texture;
	std::vector<sf::RectangleShape> rects;

	std::vector<sf::Color> cols;

	int width, height;
	float r_dx;

	std::vector< std::pair<volatile int*, uint32_t>> tracklist;
	std::vector< std::deque<volatile int*>> trackvalues;

	Blocks& blk;

	void colorizer(int i);
	void updatetrackvalues();

public:
	void checkvalues();

	Viewer(int, int, Blocks&);

	void render();

	void mark(int index, uint32_t color);
	void mark(int start, int end, uint32_t color);
	void unmark(int index);
	void unmark(int start, int end);
	void unmark_all();
};

#endif // VIEWER_H