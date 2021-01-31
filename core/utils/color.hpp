#pragma once

class color
{
public:
	color()
	{
		*((int *)this) = 0;
	}
	color(int color32)
	{
		*((int *)this) = color32;
	}

	color(int _r, int _g, int _b)
	{
		set_color(_r, _g, _b, 255);
	}

	color(int _r, int _g, int _b, int _a)
	{
		set_color(_r, _g, _b, _a);
	}

	void set_color(int _r, int _g, int _b, int _a = 255)
	{
		_color[0] = (unsigned char)_r;
		_color[1] = (unsigned char)_g;
		_color[2] = (unsigned char)_b;
		_color[3] = (unsigned char)_a;
	}

	void get_color(int& _r, int& _g, int& _b, int& _a) const
	{
		_r = _color[0];
		_g = _color[1];
		_b = _color[2];
		_a = _color[3];
	}

	void set_raw_color(int color32)
	{
		*((int*)this) = color32;
	}

	int get_raw_color() const
	{
		return *((int*)this);
	}

	int get_d3d_color() const
	{
		return ((int)((((_color[3]) & 0xff) << 24) | (((_color[0]) & 0xff) << 16) | (((_color[1]) & 0xff) << 8) | ((_color[2]) & 0xff)));
	}

	inline int r() const
	{
		return _color[0];
	}

	inline int g() const
	{
		return _color[1];
	}

	inline int b() const
	{
		return _color[2];
	}

	inline int a() const
	{
		return _color[3];
	}

	inline float r_base() const
	{
		return _color[0] / 255.0f;
	}

	inline float g_base() const
	{
		return _color[1] / 255.0f;
	}

	inline float b_base() const
	{
		return _color[2] / 255.0f;
	}

	inline float a_base() const
	{
		return _color[3] / 255.0f;
	}

	unsigned char& operator[](int index)
	{
		return _color[index];
	}

	const unsigned char& operator[](int index) const
	{
		return _color[index];
	}

	bool operator ==(const color& rhs) const
	{
		return (*((int *)this) == *((int *)&rhs));
	}

	bool operator !=(const color& rhs) const
	{
		return !(operator==(rhs));
	}

	color& operator=(const color& rhs)
	{
		set_raw_color(rhs.get_raw_color());
		return *this;
	}

	float* base()
	{
		float clr[3];

		clr[0] = _color[0] / 255.0f;
		clr[1] = _color[1] / 255.0f;
		clr[2] = _color[2] / 255.0f;

		return &clr[0];
	}

	float* base_alpha()
	{
		float clr[4];

		clr[0] = _color[0] / 255.0f;
		clr[1] = _color[1] / 255.0f;
		clr[2] = _color[2] / 255.0f;
		clr[3] = _color[3] / 255.0f;

		return &clr[0];
	}

	float hue() const
	{
		if (_color[0] == _color[1] && _color[1] == _color[2])
		{
			return 0.0f;
		}

		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float delta = max - min;
		float hue = 0.0f;

		if (r == max)
		{
			hue = (g - b) / delta;
		}
		else if (g == max)
		{
			hue = 2 + (b - r) / delta;
		}
		else if (b == max)
		{
			hue = 4 + (r - g) / delta;
		}
		hue *= 60;

		if (hue < 0.0f)
		{
			hue += 360.0f;
		}
		return hue;
	}

	float saturation() const
	{
		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float l, s = 0;

		if (max != min)
		{
			l = (max + min) / 2;
			if (l <= 0.5f)
				s = (max - min) / (max + min);
			else
				s = (max - min) / (2 - max - min);
		}
		return s;
	}

	float brightness() const
	{
		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		return (max + min) / 2;
	}

	static color from_hsb(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return color(
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 2)
		{
			return color(
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 3)
		{
			return color(
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255)
			);
		}
		else if (h < 4)
		{
			return color(
				(unsigned char)(p * 255),
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else if (h < 5)
		{
			return color(
				(unsigned char)(t * 255),
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else
		{
			return color(
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255),
				(unsigned char)(q * 255)
			);
		}
	}

	static color red()
	{
		return color(255, 0, 0);
	}

	static color green()
	{
		return color(0, 255, 0);
	}

	static color blue()
	{
		return color(0, 0, 255);
	}

	static color light_blue()
	{
		return color(100, 100, 255);
	}

	static color grey()
	{
		return color(128, 128, 128);
	}

	static color dark_grey()
	{
		return color(45, 45, 45);
	}

	static color black()
	{
		return color(0, 0, 0);
	}

	static color white()
	{
		return color(255, 255, 255);
	}

	static color purple()
	{
		return color(220, 0, 220);
	}

	//Menu
	static color background()
	{
		return color(55, 55, 55);
	}

	static color frame_border()
	{
		return color(80, 80, 80);
	}

	static color main_text()
	{
		return color(230, 230, 230);
	}

	static color header_text()
	{
		return color(49, 124, 230);
	}

	static color current_tab()
	{
		return color(55, 55, 55);
	}

	static color tabs()
	{
		return color(23, 23, 23);
	}

	static color highlight()
	{
		return color(49, 124, 230);
	}

	static color element_border()
	{
		return color(0, 0, 0);
	}

	static color slider_scroll()
	{
		return color(78, 143, 230);
	}

private:
	unsigned char _color[4];
};