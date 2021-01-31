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
		SetColor(_r, _g, _b, 255);
	}

	color(int _r, int _g, int _b, int _a)
	{
		SetColor(_r, _g, _b, _a);
	}

	void SetColor(int _r, int _g, int _b, int _a = 255)
	{
		_color[0] = (unsigned char)_r;
		_color[1] = (unsigned char)_g;
		_color[2] = (unsigned char)_b;
		_color[3] = (unsigned char)_a;
	}

	void GetColor(int& _r, int& _g, int& _b, int& _a) const
	{
		_r = _color[0];
		_g = _color[1];
		_b = _color[2];
		_a = _color[3];
	}

	void SetRawColor(int color32)
	{
		*((int*)this) = color32;
	}

	int GetRawColor() const
	{
		return *((int*)this);
	}

	int GetD3DColor() const
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

	inline float rBase() const
	{
		return _color[0] / 255.0f;
	}

	inline float gBase() const
	{
		return _color[1] / 255.0f;
	}

	inline float bBase() const
	{
		return _color[2] / 255.0f;
	}

	inline float aBase() const
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
		SetRawColor(rhs.GetRawColor());
		return *this;
	}

	float* Base()
	{
		float clr[3];

		clr[0] = _color[0] / 255.0f;
		clr[1] = _color[1] / 255.0f;
		clr[2] = _color[2] / 255.0f;

		return &clr[0];
	}

	float* BaseAlpha()
	{
		float clr[4];

		clr[0] = _color[0] / 255.0f;
		clr[1] = _color[1] / 255.0f;
		clr[2] = _color[2] / 255.0f;
		clr[3] = _color[3] / 255.0f;

		return &clr[0];
	}

	float Hue() const
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

	float Saturation() const
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

	float Brightness() const
	{
		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		return (max + min) / 2;
	}

	static color FromHSB(float hue, float saturation, float brightness)
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

	static color Red()
	{
		return color(255, 0, 0);
	}

	static color Green()
	{
		return color(0, 255, 0);
	}

	static color Blue()
	{
		return color(0, 0, 255);
	}

	static color LightBlue()
	{
		return color(100, 100, 255);
	}

	static color Grey()
	{
		return color(128, 128, 128);
	}

	static color DarkGrey()
	{
		return color(45, 45, 45);
	}

	static color Black()
	{
		return color(0, 0, 0);
	}

	static color White()
	{
		return color(255, 255, 255);
	}

	static color Purple()
	{
		return color(220, 0, 220);
	}

	//Menu
	static color Background()
	{
		return color(55, 55, 55);
	}

	static color FrameBorder()
	{
		return color(80, 80, 80);
	}

	static color MainText()
	{
		return color(230, 230, 230);
	}

	static color HeaderText()
	{
		return color(49, 124, 230);
	}

	static color CurrentTab()
	{
		return color(55, 55, 55);
	}

	static color Tabs()
	{
		return color(23, 23, 23);
	}

	static color Highlight()
	{
		return color(49, 124, 230);
	}

	static color ElementBorder()
	{
		return color(0, 0, 0);
	}

	static color SliderScroll()
	{
		return color(78, 143, 230);
	}

private:
	unsigned char _color[4];
};