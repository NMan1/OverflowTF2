#pragma once
#include "..\math\vector.hpp"
#include "..\color.hpp"
#include "..\..\interfaces\interfaces.hpp"

namespace draw {
	extern unsigned long font;

	extern int default_font_size;

	extern int default_font_weight;

	void init();

	int get_text_size_width(std::string text, int font_size=default_font_size);

	int get_text_size_height(std::string text, int font_size=default_font_size);

	bool w2s(const vector& origin, vector_2d& screen);

	void line(int x1, int y1, int x2, int y2, color color);

	void line(vector_2d point1, vector_2d point2, color color);

	void box(vector_2d top_left, vector_2d bottom_right, color color);

	void box(int x, int y, int w, int h, color color);

	void filled_box(int x, int y, int w, int h, color color);

	void filled_box(vector_2d top_left, vector_2d bottom_right, color color);

	void circle(vector_2d point, float radius, color color);

	void text(std::string text, vector_2d position, color color, int font_size=default_font_size, bool center=false);
}