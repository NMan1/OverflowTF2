#include "draw.hpp"
#include "..\..\source-sdk\structs\enums.hpp"

typedef float matrix3x4[3][4];

int utils::screen_x = 0, utils::screen_y = 0;
vmatrix utils::world_to_projection = {};

namespace draw {
	int default_font_weight = 200;

	unsigned long health_font;

	unsigned long pickup_font;

	unsigned long object_font;

	unsigned long class_name_font;

	unsigned long watermark_font;

	void init() {
		if (!interfaces::surface) {
			return;
		}

		health_font = interfaces::surface->create_font();
		interfaces::surface->set_font_glyph(health_font, "Tahoma", 12, default_font_weight, 0, 0, font_flags::DROPSHADOW | font_flags::ANTIALIAS);
			
		pickup_font = interfaces::surface->create_font();
		interfaces::surface->set_font_glyph(pickup_font, "Tahoma", 14, default_font_weight, 0, 0, font_flags::DROPSHADOW | font_flags::ANTIALIAS);
		
		object_font = interfaces::surface->create_font();
		interfaces::surface->set_font_glyph(object_font, "Tahoma", 14, default_font_weight, 0, 0, font_flags::DROPSHADOW | font_flags::ANTIALIAS);
			
		class_name_font = interfaces::surface->create_font();
		interfaces::surface->set_font_glyph(class_name_font, "Tahoma", 15, default_font_weight, 0, 0, font_flags::DROPSHADOW | font_flags::ANTIALIAS);
			
		watermark_font = interfaces::surface->create_font();
		interfaces::surface->set_font_glyph(watermark_font, "Tahoma", 22, default_font_weight, 0, 0, font_flags::DROPSHADOW | font_flags::ANTIALIAS);

		interfaces::engine->get_screen_size(utils::screen_x, utils::screen_y);

		utils::log("[-] Draw Objects Initialized");
	}

	int get_text_size_width(unsigned long font, std::string text) {
		if (text.find(".") != std::string::npos) {
			text = text.substr(0, text.find("."));
		}

		wchar_t temp[128];
		int wide = 0, tall = 0;

		if (MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, temp, 128) > 0) {
			interfaces::surface->get_text_size(font, temp, wide, tall);
		}
		return wide;
	}
	
	int get_text_size_height(unsigned long font, std::string text) {
		wchar_t temp[128];
		int wide = 0, tall = 0;

		if (MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, temp, 128) > 0) {
			interfaces::surface->get_text_size(font, temp, wide, tall);
		}
		return tall;
	}

	bool w2s(const vector& origin, vector& screen) {
		return interfaces::debug_overlay->screen_position(origin, screen) != -1;
	}

	void line(int x1, int y1, int x2, int y2, color color) {
		interfaces::surface->set_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->line(x1, y1, x2, y2);
	}

	void line(vector point1, vector point2, color color) {
		interfaces::surface->set_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->line(point1.x, point1.y, point2.x, point2.y);
	}

	void rect(vector top_left, vector bottom_right, color color) {
		interfaces::surface->set_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->outlined_rect(top_left.x, top_left.y, bottom_right.x, bottom_right.y);
	}
	
	void rect(int x, int y, int w, int h, color color) {
		interfaces::surface->set_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->outlined_rect(x, y, x + w, y + h);
	}
	
	void filled_rect(int x, int y, int w, int h, color color) {
		interfaces::surface->set_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->filled_rect(x, y, x + w, y + h);
	}

	void filled_rect(vector top_left, vector bottom_right, color color) {
		interfaces::surface->set_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->filled_rect(top_left.x, top_left.y, bottom_right.x, bottom_right.y);
	}

	void circle(vector point, float radius, color color) {
		float step = (float)M_PI * 2.0f / 40;

		for (float a = 0; a < (M_PI * 2.0f); a += step) {
			vector start(radius * cosf(a) + point.x, radius * sinf(a) + point.y);
			vector end(radius * cosf(a + step) + point.x, radius * sinf(a + step) + point.y);
			line(start, end, color);
		}
	}

	void text(unsigned long font, std::string text, vector position, color color, bool center) {
		wchar_t temp[128];
		int text_width, text_height;
		if (MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, temp, 128) > 0) {
			interfaces::surface->set_text_font(font);
			if (center) {
				interfaces::surface->get_text_size(font, temp, text_width, text_height);
				interfaces::surface->set_text_pos(position.x - text_width / 2, position.y);
			}
			else
				interfaces::surface->set_text_pos(position.x, position.y);
			interfaces::surface->set_text_color(color.r(), color.g(), color.b(), color.a());
			interfaces::surface->print_text(temp, wcslen(temp));
		}
	}	
	
	void text(unsigned long font, std::string text, int x, int y, color color, bool center) {
		wchar_t temp[128];
		int text_width, text_height;
		if (MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, temp, 128) > 0) {
			interfaces::surface->set_text_font(font);
			if (center) {
				interfaces::surface->get_text_size(font, temp, text_width, text_height);
				interfaces::surface->set_text_pos(x - text_width / 2, y);
			}
			else
				interfaces::surface->set_text_pos(x, y);
			interfaces::surface->set_text_color(color.r(), color.g(), color.b(), color.a());
			interfaces::surface->print_text(temp, wcslen(temp));
		}
	}
	
	void text(unsigned long font, const wchar_t* text, int x, int y, color color, bool center) {
		int text_width, text_height;
		interfaces::surface->set_text_font(font);
		if (center) {
			interfaces::surface->get_text_size(font, text, text_width, text_height);
			interfaces::surface->set_text_pos(x - text_width / 2, y);
		}
		else
			interfaces::surface->set_text_pos(x, y);
		interfaces::surface->set_text_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->print_text(text, wcslen(text));
	}
	
	void text(unsigned long font, const wchar_t* text, vector position, color color, bool center) {
		int text_width, text_height;
		interfaces::surface->set_text_font(font);
		if (center) {
			interfaces::surface->get_text_size(font, text, text_width, text_height);
			interfaces::surface->set_text_pos(position.x - text_width / 2, position.y);
		}
		else
			interfaces::surface->set_text_pos(position.x, position.y);
		interfaces::surface->set_text_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->print_text(text, wcslen(text));
	}
}