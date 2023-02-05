#pragma once

class Color
{
public:

	unsigned int mColorValue;

public:

	Color() = default;
	Color(const Color& color);
	Color(unsigned int colorVal);
	Color(unsigned char a, unsigned char r, unsigned char g, unsigned char b);
	Color(unsigned char r, unsigned char g, unsigned char b);
	Color(Color color, unsigned char a);
	Color& operator = (Color color);

	unsigned char GetA() const;
	unsigned char GetR() const;
	unsigned char GetG() const;
	unsigned char GetB() const;
	void SetA(unsigned char a);
	void SetR(unsigned char r);
	void SetG(unsigned char g);
	void SetB(unsigned char b);
};

namespace Colors
{
	static Color MakeRGB(unsigned char r, unsigned char g, unsigned char b) { return Color(r, g, b); }
	static Color White(255u, 255u, 255u);
	static Color Black(0u, 0u, 0u);
	static Color Gray(0x80u, 0x80u, 0x80u);
	static Color LightGray(0xD3u, 0xD3u, 0xD3u);
	static Color Red(255u, 0u, 0u);
	static Color Green(0u, 255u, 0u);
	static Color Blue(0u, 0u, 255u);
	static Color Yellow(255u, 255u, 0u);
	static Color Cyan(0u, 255u, 255u);
	static Color Magenta(255u, 0u, 255u);
}
