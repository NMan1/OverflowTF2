#pragma once
#include "..\math\vector.hpp"
#include "..\color.hpp"
#include "..\..\interfaces\interfaces.hpp"

namespace draw {
	extern unsigned long health_font;

	extern unsigned long pickup_font;

	extern unsigned long object_font;

	extern unsigned long class_name_font;

	extern unsigned long watermark_font;

	extern int default_font_size;

	extern int default_font_weight;

	void init();

	int get_text_size_width(unsigned long font, std::string text);

	int get_text_size_height(unsigned long font, std::string text);

	bool w2s(const vector& origin, vector& screen);

	void line(int x1, int y1, int x2, int y2, color color);

	void line(vector point1, vector point2, color color);

	void rect(vector top_left, vector bottom_right, color color);

	void rect(int x, int y, int w, int h, color color);

	void filled_rect(int x, int y, int w, int h, color color);

	void filled_rect(vector top_left, vector bottom_right, color color);

	void circle(vector point, float radius, color color);

	void text(unsigned long font, std::string text, vector position, color color, bool center=false);

	void text(unsigned long font, std::string text, int x, int y, color color, bool center=false);

	void text(unsigned long font, const  wchar_t* text, int x, int y, color color, bool center=false);

	void text(unsigned long font, const wchar_t* text, vector position, color color, bool center=false);
}