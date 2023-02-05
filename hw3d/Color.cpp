#include "Color.h"

Color::Color(const Color& color) :
	mColorValue(color.mColorValue)
{}

Color::Color(unsigned int colorValue) :
	mColorValue(colorValue)
{}

Color::Color(unsigned char a, unsigned char r, unsigned char g, unsigned char b) :
	mColorValue((a << 24u) | (r << 16u) | (g << 8u) | b)
{}

Color::Color(unsigned char r, unsigned char g, unsigned char b) :
	mColorValue((r << 16u) | (g << 8u) | b)
{}

Color::Color(Color color, unsigned char a) :
	Color((a << 24u) | color.mColorValue)
{}

Color& Color::operator = (Color color)
{
	mColorValue = color.mColorValue;
	return *this;
}

unsigned char Color::GetA() const
{
	return mColorValue >> 24u;
}

unsigned char Color::GetR() const
{
	return (mColorValue >> 16u) & 0xFFu;
}

unsigned char Color::GetG() const
{
	return (mColorValue >> 8u) & 0xFFu;
}

unsigned char Color::GetB() const
{
	return mColorValue & 0xFFu;
}

void Color::SetA(unsigned char a)
{
	mColorValue = (mColorValue & 0xFFFFFFu) | (a << 24u);
}

void Color::SetR(unsigned char r)
{
	mColorValue = (mColorValue & 0xFF00FFFFu) | (r << 16u);
}

void Color::SetG(unsigned char g)
{
	mColorValue = (mColorValue & 0xFFFF00FFu) | (g << 8u);
}

void Color::SetB(unsigned char b)
{
	mColorValue = (mColorValue & 0xFFFFFF00u) | b;
}
