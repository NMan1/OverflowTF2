#include "draw.hpp"

namespace draw {
	unsigned long font = NULL;

	int default_font_size = 17;

	int default_font_weight = 750;

	void init() {
		if (!interfaces::surface) {
			return;
		}

		font = interfaces::surface->create_font();
		interfaces::surface->set_font_glyph(font, "Tahoma", default_font_size, default_font_weight, 0, 0, FONTFLAG_ANTIALIAS);
	}

	bool w2s(const vector& origin, vector2D& screen) {
		const matrix3x4& worldToScreen = interfaces::engine->WorldToScreenMatrix(); //Grab the world to screen matrix from CEngineClient::WorldToScreenMatrix

		float w = worldToScreen[3][0] * origin[0] + worldToScreen[3][1] * origin[1] + worldToScreen[3][2] * origin[2] + worldToScreen[3][3]; //Calculate the angle in compareson to the player's camera.

		if (w > 0.001) //If the object is within view.
		{
			float fl1DBw = 1 / w; //Divide 1 by the angle.
			int screen_x, screen_y;
			interfaces::engine->get_screen_size(screen_x, screen_y);
			screen.x = (screen_x / 2) + (0.5 * ((worldToScreen[0][0] * origin[0] + worldToScreen[0][1] * origin[1] + worldToScreen[0][2] * origin[2] + worldToScreen[0][3]) * fl1DBw) * screen_x + 0.5); //Get the X dimension and push it in to the Vector.
			screen.y = (screen_y / 2) - (0.5 * ((worldToScreen[1][0] * origin[0] + worldToScreen[1][1] * origin[1] + worldToScreen[1][2] * origin[2] + worldToScreen[1][3]) * fl1DBw) * screen_y + 0.5); //Get the Y dimension and push it in to the Vector.
			return true;
		}

		return false;
	}

	void line(int x1, int y1, int x2, int y2, color color) {
		interfaces::surface->set_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->line(x1, y1, x2, y2);
	}

	void line(vector2D point1, vector2D point2, color color) {
		interfaces::surface->set_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->line(point1.x, point1.y, point2.x, point2.y);
	}

	void box(vector2D top_left, vector2D bottom_right, color color, float width) {
		interfaces::surface->set_color(color.r(), color.g(), color.b(), color.a());
		interfaces::surface->outlined_rect(top_left.x, top_left.y, bottom_right.x, bottom_right.y);
	}

	void text(std::string text, vector2D position, color color, int font_size, bool center) {
		auto w_text = std::wstring(text.begin(), text.end());

		if (font_size != default_font_size) {
			interfaces::surface->set_font_glyph(font, "Tahoma", font_size, default_font_weight, 0, 0, FONTFLAG_ANTIALIAS);
		}

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