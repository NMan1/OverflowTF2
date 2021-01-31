#pragma once


class IVDebugOverlay
{
public:
	virtual void AddEntityTextOverlay(int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char* format, ...) = 0;
	virtual void AddBoxOverlay(const vector& origin, const vector& mins, const vector& max, QAngle const& orientation, int r, int g, int b, int a, float duration) = 0;
	virtual void AddTriangleOverlay(const vector& p1, const vector& p2, const vector& p3, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
	virtual void AddLineOverlay(const vector& origin, const vector& dest, int r, int g, int b,bool noDepthTest, float duration) = 0;
	virtual void AddTextOverlay(const vector& origin, float duration, const char* format, ...) = 0;
	virtual void AddTextOverlay(const vector& origin, int line_offset, float duration, const char* format, ...) = 0;
	virtual void AddScreenTextOverlay(float flXPos, float flYPos,float flDuration, int r, int g, int b, int a, const char* text) = 0;
	virtual void AddSweptBoxOverlay(const vector& start, const vector& end, const vector& mins, const vector& max, const QAngle& angles, int r, int g, int b, int a, float flDuration) = 0;
	virtual void AddGridOverlay(const vector& origin) = 0;
	virtual int screen_position(const vector& point, vector& screen) = 0;
	virtual int screen_position(float flXPos, float flYPos, vector& screen) = 0;

	virtual DWORD* GetFirst(void) = 0;
	virtual DWORD* GetNext(DWORD* current) = 0;
	virtual void ClearDeadOverlays(void) = 0;
	virtual void ClearAllOverlays() = 0;
};