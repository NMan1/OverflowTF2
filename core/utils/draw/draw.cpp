#include "draw.hpp"
#include "..\..\source-sdk\structs\enums.hpp"

typedef float matrix3x4[3][4];

int utils::screen_x = 0, utils::screen_y = 0;
v_matrix utils::world_to_projection = {};

namespace draw {
	unsigned long font = NULL;

	int default_font_size = 17;

	int default_font_weight = 750;

	void init() {
		if (!interfaces::surface) {
			return;
		}

		font = interfaces::surface->create_font();
		interfaces::surface->set_font_glyph(font, "Tahoma", default_font_size, default_font_weight, 0, 0, font_flags::ANTIALIAS);
		interfaces::engine->get_screen_size(utils::screen_x, utils::screen_y);
	}

	int get_text_size_width(std::string text, int font_size) {
		auto w_text = std::wstring(text.begin(), text.end());
		int wide, tall;
		interfaces::surface->set_font_glyph(font, "Tahoma", font_size, default_font_weight, 0, 0, font_flags::ANTIALIAS);
		interfaces::surface->get_text_size(font, w_text.c_str(), wide, tall);
		return wide;
	}
	
	int get_text_size_height(std::string text, int font_size) {
		auto w_text = std::wstring(text.begin(), text.end());
		int wide, tall;
		interfaces::surface->set_font_glyph(font, "Tahoma", font_size, default_font_weight, 0, 0, font_flags::ANTIALIAS);
		interfaces::surface->get_text_size(font, w_text.c_str(), wide, tall);
		return tall;
	}

	bool w2s(const vector& origin, vector_2d& screen) {
		//const matrix3x4& worldToScreen = interfaces::engine->world_to_screen_matrix(); //Grab the world to screen matrix from CEngineClient::WorldToScreenMatrix
		const matrix3x4& worldToScreen = utils::world_to_projection.As3x4(); //Grab the world to screen matrix from CEngineClient::WorldToScreenMatrix

		float w = worldToScreen[3][0] * origin[0] + worldToScreen[3][1] * origin[1] + worldToScreen[3][2] * origin[2] + worldToScreen[3][3]; //Calculate the angle in compareson to the player's camera.

		if (w > 0.001)
		{
			float fl1DBw = 1 / w; 
			screen.x = (utils::screen_x / 2) + (0.5 * ((worldToScreen[0][0] * origin[0] + worldToScreen[0][1] * origin[1] + worldToScreen[0][2] * origin[2] + worldToScreen[0][3]) * fl1DBw) * utils::screen_x + 0.5); //Get the X dimension and push it in to the Vector.
			screen.y = (utils::screen_y / 2) - (0.5 * ((worldToScreen[1][0] * origin[0] + worldToScreen[1][1] * origin[1] + worldToScreen[1][2] * origin[2] + worldToScreen[1][3]) * fl1DBw) * utils::screen_y + 0.5); //Get the Y dimension and push it in to the Vector.
			return true;
		}

		return false;
	}

	void line(int x1, int y1, int x2, int y2, color color) {
		interfaces::surface->set_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->line(x1, y1, x2, y2);
	}

	void line(vector_2d point1, vector_2d point2, color color) {
		interfaces::surface->set_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->line(point1.x, point1.y, point2.x, point2.y);
	}

	void box(vector_2d top_left, vector_2d bottom_right, color color, float width) {
		interfaces::surface->set_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->outlined_rect(top_left.x, top_left.y, bottom_right.x, bottom_right.y);
	}
	
	void box(int x, int y, int w, int h, color color, float width) {
		interfaces::surface->set_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->outlined_rect(x, y, x + w, y + h);
	}

	void circle(vector_2d point, float radius, color color) {
		float step = (float)M_PI * 2.0f / 30;

		for (float a = 0; a < (M_PI * 2.0f); a += step) {
			vector_2d start(radius * cosf(a) + point.x, radius * sinf(a) + point.y);
			vector_2d end(radius * cosf(a + step) + point.x, radius * sinf(a + step) + point.y);
			line(start, end, color);
		}
	}

	void text(std::string text, vector_2d position, color color, int font_size, bool center) {
		auto w_text = std::wstring(text.begin(), text.end());

		interfaces::surface->set_font_glyph(font, "Tahoma", font_size, default_font_weight, 0, 0, font_flags::ANTIALIAS);

		if (!center) {
			interfaces::surface->set_text_pos(position.x, position.y);
		}
		else {
			int wide, tall;
			interfaces::surface->get_text_size(font, w_text.c_str(), wide, tall);
			interfaces::surface->set_text_pos(position.x - (wide / 2), position.y - (tall / 2));
		}

		interfaces::surface->set_text_font(font);
		interfaces::surface->set_text_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->print_text(w_text.c_str(), text.length());
	}
}