#pragma once
#include "..\vector.hpp"
#include "../../interfaces/interfaces.hpp"

namespace draw {
	extern unsigned long font;

	extern int default_font_size;

	extern int default_font_weight;

	void init();

	bool w2s(const vector& origin, vector2D& screen);

	void line(int x1, int y1, int x2, int y2, color color);

	void line(vector2D point1, vector2D point2, color color);

	void box(vector2D top_left, vector2D bottom_right, color color, float width);

	void text(std::string text, vector2D position, color color, int font_size=default_font_size, bool center=false);
}