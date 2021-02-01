#pragma once
#include <wtypes.h>
#include "..\..\utils\math\vector.hpp"

class iv_debug_overlay
{
public:
	virtual void add_entity_text_overlay(int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char* format, ...) = 0;
	virtual void add_box_overlay(const vector& origin, const vector& mins, const vector& max, QAngle const& orientation, int r, int g, int b, int a, float duration) = 0;
	virtual void add_triangle_overlay(const vector& p1, const vector& p2, const vector& p3, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
	virtual void add_line_overlay(const vector& origin, const vector& dest, int r, int g, int b,bool noDepthTest, float duration) = 0;
	virtual void add_text_overlay(const vector& origin, float duration, const char* format, ...) = 0;
	virtual void add_text_overlay(const vector& origin, int line_offset, float duration, const char* format, ...) = 0;
	virtual void add_screen_text_overlay(float flXPos, float flYPos,float flDuration, int r, int g, int b, int a, const char* text) = 0;
	virtual void add_swept_box_overlay(const vector& start, const vector& end, const vector& mins, const vector& max, const QAngle& angles, int r, int g, int b, int a, float flDuration) = 0;
	virtual void add_grid_overlay(const vector& origin) = 0;
	virtual int screen_position(const vector& point, vector& screen) = 0;
	virtual int screen_position(float flXPos, float flYPos, vector& screen) = 0;

	virtual DWORD* get_first(void) = 0;
	virtual DWORD* get_next(DWORD* current) = 0;
	virtual void clear_dead_overlays(void) = 0;
	virtual void clear_all_overlays() = 0;
};