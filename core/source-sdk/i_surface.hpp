#pragma once
#include "..\utils\utils.hpp"

class i_surface
{
public:
	void unlock_cursor()
	{
		typedef void(__thiscall* fn)(void*);
		utils::get_vfunc< fn >(this, 61)(this);
	}

	void set_color(int r, int g, int b, int a)
	{
		typedef void(__thiscall* fn)(void*, int, int, int, int);
		utils::get_vfunc< fn >(this, 11)(this, r, g, b, a);
	}

	void filled_rect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* fn)(void*, int, int, int, int);
		utils::get_vfunc< fn >(this, 12)(this, x0, y0, x1, y1);
	}

	void outlined_rect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* fn)(void*, int, int, int, int);
		utils::get_vfunc< fn >(this, 14)(this, x0, y0, x1, y1);
	}

	void line(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* fn)(void*, int, int, int, int);
		utils::get_vfunc<fn>(this, 15)(this, x0, y0, x1, y1);
	}

	void set_text_font(unsigned long font)
	{
		typedef void(__thiscall* fn)(void*, unsigned long);
		utils::get_vfunc< fn >(this, 17)(this, font);
	}

	void set_text_color(int r, int g, int b, int a)
	{
		typedef void(__thiscall* fn)(void*, int, int, int, int);
		utils::get_vfunc< fn >(this, 19)(this, r, g, b, a);
	}

	void set_text_pos(int x, int y)
	{
		typedef void(__thiscall* fn)(void*, int, int);
		utils::get_vfunc< fn >(this, 20)(this, x, y);
	}

	void print_text(const wchar_t* text, int textLen)
	{
		typedef void(__thiscall* fn)(void*, const wchar_t*, int, int);
		return utils::get_vfunc< fn >(this, 22)(this, text, textLen, 0);
	}

	unsigned long create_font()
	{
		typedef unsigned int(__thiscall* fn)(void*);
		return utils::get_vfunc< fn >(this, 66)(this);
	}

	void set_font_glyph(unsigned long& font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		typedef void(__thiscall* fn)(void*, unsigned long, const char*, int, int, int, int, int, int, int);
		utils::get_vfunc< fn >(this, 67)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}

	void get_text_size(unsigned long font, const wchar_t* text, int& wide, int& tall)
	{
		typedef void(__thiscall* fn)(void*, unsigned long, const wchar_t*, int&, int&);
		utils::get_vfunc< fn >(this, 75)(this, font, text, wide, tall);
	}

	int create_new_texture_i_d(bool procedural = true) {
		typedef int(__thiscall* fn)(void*, bool);
		return utils::get_vfunc<fn>(this, 37)(this, procedural);
	}

	bool draw_get_texture_file(int id, char* filename, int maxlen) {
		typedef bool(__thiscall* fn)(void*, int, char*, int);
		return utils::get_vfunc<fn>(this, 29)(this, id, filename, maxlen);
	};

	void draw_set_texture_file(int id, const char* filename, int hardwareFilter, bool forceReload) {
		typedef void(__thiscall* fn)(void*, int, const char*, int, bool);
		return utils::get_vfunc<fn>(this, 30)(this, id, filename, hardwareFilter, forceReload);
	};

	void draw_set_texture_rgba(int id, unsigned char const* rgba, int wide, int tall, int hardwareFilter = 0, bool forceReload = false) {
		typedef void(__thiscall* fn)(void*, int, unsigned char const*, int, int, int, bool);
		return utils::get_vfunc<fn>(this, 31)(this, id, rgba, wide, tall, hardwareFilter, forceReload);
	}

	void draw_set_texture(int id) {
		typedef void(__thiscall* fn)(void*, int);
		return utils::get_vfunc<fn>(this, 32)(this, id);
	}

	void draw_get_texture_size(int id, int& wide, int& tall) {
		typedef void(__thiscall* fn)(void*, int, int&, int&);
		return utils::get_vfunc<fn>(this, 33)(this, id, wide, tall);
	};

	bool is_texture_id_valid(int id) {
		typedef bool(__thiscall* fn)(void*, int);
		return utils::get_vfunc<fn>(this, 35)(this, id);
	}

	void draw_textured_rect(int x, int y, int w, int h) {
		typedef void(__thiscall* fn)(void*, int, int, int, int);
		return utils::get_vfunc<fn>(this, 34)(this, x, y, x + w, y + h);
	}
};