#pragma once

class ISurface
{
public:
	void unlock_cursor()
	{
		typedef void(__thiscall* original_fn)(void*);
		utils::get_vfunc< original_fn >(this, 61)(this);
	}
	void set_color(int r, int g, int b, int a)
	{
		typedef void(__thiscall* original_fn)(PVOID, int, int, int, int);
		utils::get_vfunc< original_fn >(this, 11)(this, r, g, b, a);
	}
	void filled_rect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* original_fn)(PVOID, int, int, int, int);
		utils::get_vfunc< original_fn >(this, 12)(this, x0, y0, x1, y1);
	}
	void outlined_rect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* original_fn)(PVOID, int, int, int, int);
		utils::get_vfunc< original_fn >(this, 14)(this, x0, y0, x1, y1);
	}
	void line(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* original_fn)(void*, int, int, int, int);
		utils::get_vfunc<original_fn>(this, 15)(this, x0, y0, x1, y1);
	}
	void set_text_font(unsigned long font)
	{
		typedef void(__thiscall* original_fn)(PVOID, unsigned long);
		utils::get_vfunc< original_fn >(this, 17)(this, font);
	}
	void set_text_color(int r, int g, int b, int a)
	{
		typedef void(__thiscall* original_fn)(PVOID, int, int, int, int);
		utils::get_vfunc< original_fn >(this, 19)(this, r, g, b, a);
	}
	void set_text_pos(int x, int y)
	{
		typedef void(__thiscall* original_fn)(PVOID, int, int);
		utils::get_vfunc< original_fn >(this, 20)(this, x, y);
	}
	void print_text(const wchar_t* text, int textLen)
	{
		typedef void(__thiscall* original_fn)(PVOID, const wchar_t*, int, int);
		return utils::get_vfunc< original_fn >(this, 22)(this, text, textLen, 0);
	}
	unsigned long create_font()
	{
		typedef unsigned int(__thiscall* original_fn)(PVOID);
		return utils::get_vfunc< original_fn >(this, 66)(this);
	}
	void set_font_glyph(unsigned long& font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		typedef void(__thiscall* original_fn)(PVOID, unsigned long, const char*, int, int, int, int, int, int, int);
		utils::get_vfunc< original_fn >(this, 67)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}
	void get_text_size(unsigned long font, const wchar_t* text, int& wide, int& tall)
	{
		typedef void(__thiscall* original_fn)(PVOID, unsigned long, const wchar_t*, int&, int&);
		utils::get_vfunc< original_fn >(this, 75)(this, font, text, wide, tall);
	}
	int CreateNewTextureID(bool procedural = true) {
		typedef int(__thiscall* FN)(PVOID, bool);
		return utils::get_vfunc<FN>(this, 37)(this, procedural);
	}

	bool DrawGetTextureFile(int id, char* filename, int maxlen) {
		typedef bool(__thiscall* FN)(PVOID, int, char*, int);
		return utils::get_vfunc<FN>(this, 29)(this, id, filename, maxlen);
	};

	void DrawSetTextureFile(int id, const char* filename, int hardwareFilter, bool forceReload) {
		typedef void(__thiscall* FN)(PVOID, int, const char*, int, bool);
		return utils::get_vfunc<FN>(this, 30)(this, id, filename, hardwareFilter, forceReload);
	};

	void DrawSetTextureRGBA(int id, unsigned char const* rgba, int wide, int tall, int hardwareFilter = 0, bool forceReload = false) {
		typedef void(__thiscall* FN)(PVOID, int, unsigned char const*, int, int, int, bool);
		return utils::get_vfunc<FN>(this, 31)(this, id, rgba, wide, tall, hardwareFilter, forceReload);
	}

	void DrawSetTexture(int id) {
		typedef void(__thiscall* FN)(PVOID, int);
		return utils::get_vfunc<FN>(this, 32)(this, id);
	}

	void DrawGetTextureSize(int id, int& wide, int& tall) {
		typedef void(__thiscall* FN)(PVOID, int, int&, int&);
		return utils::get_vfunc<FN>(this, 33)(this, id, wide, tall);
	};

	bool IsTextureIDValid(int id) {
		typedef bool(__thiscall* FN)(PVOID, int);
		return utils::get_vfunc<FN>(this, 35)(this, id);
	}

	void DrawTexturedRect(int x, int y, int w, int h) {
		typedef void(__thiscall* FN)(PVOID, int, int, int, int);
		return utils::get_vfunc<FN>(this, 34)(this, x, y, x + w, y + h);
	}
};