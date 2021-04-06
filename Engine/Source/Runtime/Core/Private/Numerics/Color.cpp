// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Numerics/Color.h"

#include "Core/String.h"
#include "HashHelper.h"
#include "Exception/IndexOutOfRangeException.h"

using namespace std;

map<size_t, Color> Color::convertTable =
{
	{ "AliceBlue"_s->GetHashCode(), Color::FromHtml("#F0F8FF"_s) },
	{ "AntiqueWhite"_s->GetHashCode(), Color::FromHtml("#FAEBD7"_s) },
	{ "Aqua"_s->GetHashCode(), Color::FromHtml("#00FFFF"_s) },
	{ "Aquamarine"_s->GetHashCode(), Color::FromHtml("#7FFFD4"_s) },
	{ "Azure"_s->GetHashCode(), Color::FromHtml("#F0FFFF"_s) },
	{ "Beige"_s->GetHashCode(), Color::FromHtml("#F5F5DC"_s) },
	{ "Bisque"_s->GetHashCode(), Color::FromHtml("#FFE4C4"_s) },
	{ "Black"_s->GetHashCode(), Color::FromHtml("#000000"_s) },
	{ "BlanchedAlmond"_s->GetHashCode(), Color::FromHtml("#FFEBCD"_s) },
	{ "Blue"_s->GetHashCode(), Color::FromHtml("#0000FF"_s) },
	{ "BlueViolet"_s->GetHashCode(), Color::FromHtml("#8A2BE2"_s) },
	{ "Brown"_s->GetHashCode(), Color::FromHtml("#A52A2A"_s) },
	{ "BurlyWood"_s->GetHashCode(), Color::FromHtml("#DEB887"_s) },
	{ "CadetBlue"_s->GetHashCode(), Color::FromHtml("#5F9EA0"_s) },
	{ "Chartreuse"_s->GetHashCode(), Color::FromHtml("#7FFF00"_s) },
	{ "Chocolate"_s->GetHashCode(), Color::FromHtml("#D2691E"_s) },
	{ "Coral"_s->GetHashCode(), Color::FromHtml("#FF7F50"_s) },
	{ "CornflowerBlue"_s->GetHashCode(), Color::FromHtml("#6495ED"_s) },
	{ "Cornsilk"_s->GetHashCode(), Color::FromHtml("#FFF8DC"_s) },
	{ "Crimson"_s->GetHashCode(), Color::FromHtml("#DC143C"_s) },
	{ "Cyan"_s->GetHashCode(), Color::FromHtml("#00FFFF"_s) },
	{ "DarkBlue"_s->GetHashCode(), Color::FromHtml("#00008B"_s) },
	{ "DarkCyan"_s->GetHashCode(), Color::FromHtml("#008B8B"_s) },
	{ "DarkGoldenrod"_s->GetHashCode(), Color::FromHtml("#B8860B"_s) },
	{ "DarkGray"_s->GetHashCode(), Color::FromHtml("#A9A9A9"_s) },
	{ "DarkGreen"_s->GetHashCode(), Color::FromHtml("#006400"_s) },
	{ "DarkKhaki"_s->GetHashCode(), Color::FromHtml("#BDB76B"_s) },
	{ "DarkMagenta"_s->GetHashCode(), Color::FromHtml("#8B008B"_s) },
	{ "DarkOliveGreen"_s->GetHashCode(), Color::FromHtml("#556B2F"_s) },
	{ "DarkOrange"_s->GetHashCode(), Color::FromHtml("#FF8C00"_s) },
	{ "DarkOrchid"_s->GetHashCode(), Color::FromHtml("#9932CC"_s) },
	{ "DarkRed"_s->GetHashCode(), Color::FromHtml("#8B0000"_s) },
	{ "DarkSalmon"_s->GetHashCode(), Color::FromHtml("#E9967A"_s) },
	{ "DarkSeaGreen"_s->GetHashCode(), Color::FromHtml("#8FBC8B"_s) },
	{ "DarkSlateBlue"_s->GetHashCode(), Color::FromHtml("#483D8B"_s) },
	{ "DarkSlateGray"_s->GetHashCode(), Color::FromHtml("#2F4F4F"_s) },
	{ "DarkTurquoise"_s->GetHashCode(), Color::FromHtml("#00CED1"_s) },
	{ "DarkViolet"_s->GetHashCode(), Color::FromHtml("#9400D3"_s) },
	{ "DeepPink"_s->GetHashCode(), Color::FromHtml("#FF1493"_s) },
	{ "DeepSkyBlue"_s->GetHashCode(), Color::FromHtml("#00BFFF"_s) },
	{ "DimGray"_s->GetHashCode(), Color::FromHtml("#696969"_s) },
	{ "DodgerBlue"_s->GetHashCode(), Color::FromHtml("#1E90FF"_s) },
	{ "Firebrick"_s->GetHashCode(), Color::FromHtml("#B22222"_s) },
	{ "FloralWhite"_s->GetHashCode(), Color::FromHtml("#FFFAF0"_s) },
	{ "ForestGreen"_s->GetHashCode(), Color::FromHtml("#228B22"_s) },
	{ "Fuchsia"_s->GetHashCode(), Color::FromHtml("#FF00FF"_s) },
	{ "Gainsboro"_s->GetHashCode(), Color::FromHtml("#DCDCDC"_s) },
	{ "GhostWhite"_s->GetHashCode(), Color::FromHtml("#F8F8FF"_s) },
	{ "Gold"_s->GetHashCode(), Color::FromHtml("#FFD700"_s) },
	{ "Goldenrod"_s->GetHashCode(), Color::FromHtml("#DAA520"_s) },
	{ "Gray"_s->GetHashCode(), Color::FromHtml("#808080"_s) },
	{ "Green"_s->GetHashCode(), Color::FromHtml("#008000"_s) },
	{ "GreenYellow"_s->GetHashCode(), Color::FromHtml("#ADFF2F"_s) },
	{ "Honeydew"_s->GetHashCode(), Color::FromHtml("#F0FFF0"_s) },
	{ "HotPink"_s->GetHashCode(), Color::FromHtml("#FF69B4"_s) },
	{ "IndianRed"_s->GetHashCode(), Color::FromHtml("#CD5C5C"_s) },
	{ "Indigo"_s->GetHashCode(), Color::FromHtml("#4B0082"_s) },
	{ "Ivory"_s->GetHashCode(), Color::FromHtml("#FFFFF0"_s) },
	{ "Khaki"_s->GetHashCode(), Color::FromHtml("#F0E68C"_s) },
	{ "Lavender"_s->GetHashCode(), Color::FromHtml("#E6E6FA"_s) },
	{ "LavenderBlush"_s->GetHashCode(), Color::FromHtml("#FFF0F5"_s) },
	{ "LawnGreen"_s->GetHashCode(), Color::FromHtml("#7CFC00"_s) },
	{ "LemonChiffon"_s->GetHashCode(), Color::FromHtml("#FFFACD"_s) },
	{ "LightBlue"_s->GetHashCode(), Color::FromHtml("#ADD8E6"_s) },
	{ "LightCoral"_s->GetHashCode(), Color::FromHtml("#F08080"_s) },
	{ "LightCyan"_s->GetHashCode(), Color::FromHtml("#E0FFFF"_s) },
	{ "LightGoldenrodYellow"_s->GetHashCode(), Color::FromHtml("#FAFAD2"_s) },
	{ "LightGray"_s->GetHashCode(), Color::FromHtml("#D3D3D3"_s) },
	{ "LightGreen"_s->GetHashCode(), Color::FromHtml("#90EE90"_s) },
	{ "LightPink"_s->GetHashCode(), Color::FromHtml("#FFB6C1"_s) },
	{ "LightSalmon"_s->GetHashCode(), Color::FromHtml("#FFA07A"_s) },
	{ "LightSeaGreen"_s->GetHashCode(), Color::FromHtml("#20B2AA"_s) },
	{ "LightSkyBlue"_s->GetHashCode(), Color::FromHtml("#87CEFA"_s) },
	{ "LightSlateGray"_s->GetHashCode(), Color::FromHtml("#778899"_s) },
	{ "LightSteelBlue"_s->GetHashCode(), Color::FromHtml("#B0C4DE"_s) },
	{ "LightYellow"_s->GetHashCode(), Color::FromHtml("#FFFFE0"_s) },
	{ "Lime"_s->GetHashCode(), Color::FromHtml("#00FF00"_s) },
	{ "LimeGreen"_s->GetHashCode(), Color::FromHtml("#32CD32"_s) },
	{ "Linen"_s->GetHashCode(), Color::FromHtml("#FAF0E6"_s) },
	{ "Magenta"_s->GetHashCode(), Color::FromHtml("#FF00FF"_s) },
	{ "Maroon"_s->GetHashCode(), Color::FromHtml("#800000"_s) },
	{ "MediumAquamarine"_s->GetHashCode(), Color::FromHtml("#66CDAA"_s) },
	{ "MediumBlue"_s->GetHashCode(), Color::FromHtml("#0000CD"_s) },
	{ "MediumOrchid"_s->GetHashCode(), Color::FromHtml("#BA55D3"_s) },
	{ "MediumPurple"_s->GetHashCode(), Color::FromHtml("#9370DB"_s) },
	{ "MediumSeaGreen"_s->GetHashCode(), Color::FromHtml("#3CB371"_s) },
	{ "MediumSlateBlue"_s->GetHashCode(), Color::FromHtml("#7B68EE"_s) },
	{ "MediumSpringGreen"_s->GetHashCode(), Color::FromHtml("#00FA9A"_s) },
	{ "MediumTurquoise"_s->GetHashCode(), Color::FromHtml("#48D1CC"_s) },
	{ "MediumVioletRed"_s->GetHashCode(), Color::FromHtml("#C71585"_s) },
	{ "MidnightBlue"_s->GetHashCode(), Color::FromHtml("#191970"_s) },
	{ "MintCream"_s->GetHashCode(), Color::FromHtml("#F5FFFA"_s) },
	{ "MistyRose"_s->GetHashCode(), Color::FromHtml("#FFE4E1"_s) },
	{ "Moccasin"_s->GetHashCode(), Color::FromHtml("#FFE4B5"_s) },
	{ "NavajoWhite"_s->GetHashCode(), Color::FromHtml("#FFDEAD"_s) },
	{ "Navy"_s->GetHashCode(), Color::FromHtml("#000080"_s) },
	{ "OldLace"_s->GetHashCode(), Color::FromHtml("#FDF5E6"_s) },
	{ "Olive"_s->GetHashCode(), Color::FromHtml("#808000"_s) },
	{ "OliveDrab"_s->GetHashCode(), Color::FromHtml("#6B8E23"_s) },
	{ "Orange"_s->GetHashCode(), Color::FromHtml("#FFA500"_s) },
	{ "OrangeRed"_s->GetHashCode(), Color::FromHtml("#FF4500"_s) },
	{ "Orchid"_s->GetHashCode(), Color::FromHtml("#DA70D6"_s) },
	{ "PaleGoldenrod"_s->GetHashCode(), Color::FromHtml("#EEE8AA"_s) },
	{ "PaleGreen"_s->GetHashCode(), Color::FromHtml("#98FB98"_s) },
	{ "PaleTurquoise"_s->GetHashCode(), Color::FromHtml("#AFEEEE"_s) },
	{ "PaleVioletRed"_s->GetHashCode(), Color::FromHtml("#DB7093"_s) },
	{ "PapayaWhip"_s->GetHashCode(), Color::FromHtml("#FFEFD5"_s) },
	{ "PeachPuff"_s->GetHashCode(), Color::FromHtml("#FFDAB9"_s) },
	{ "Peru"_s->GetHashCode(), Color::FromHtml("#CD853F"_s) },
	{ "Pink"_s->GetHashCode(), Color::FromHtml("#FFC0CB"_s) },
	{ "Plum"_s->GetHashCode(), Color::FromHtml("#DDA0DD"_s) },
	{ "PowderBlue"_s->GetHashCode(), Color::FromHtml("#B0E0E6"_s) },
	{ "Purple"_s->GetHashCode(), Color::FromHtml("#800080"_s) },
	{ "Red"_s->GetHashCode(), Color::FromHtml("#FF0000"_s) },
	{ "RosyBrown"_s->GetHashCode(), Color::FromHtml("#BC8F8F"_s) },
	{ "RoyalBlue"_s->GetHashCode(), Color::FromHtml("#4169E1"_s) },
	{ "SaddleBrown"_s->GetHashCode(), Color::FromHtml("#8B4513"_s) },
	{ "Salmon"_s->GetHashCode(), Color::FromHtml("#FA8072"_s) },
	{ "SandyBrown"_s->GetHashCode(), Color::FromHtml("#F4A460"_s) },
	{ "SeaGreen"_s->GetHashCode(), Color::FromHtml("#2E8B57"_s) },
	{ "SeaShell"_s->GetHashCode(), Color::FromHtml("#FFF5EE"_s) },
	{ "Sienna"_s->GetHashCode(), Color::FromHtml("#A0522D"_s) },
	{ "Silver"_s->GetHashCode(), Color::FromHtml("#C0C0C0"_s) },
	{ "SkyBlue"_s->GetHashCode(), Color::FromHtml("#87CEEB"_s) },
	{ "SlateBlue"_s->GetHashCode(), Color::FromHtml("#6A5ACD"_s) },
	{ "SlateGray"_s->GetHashCode(), Color::FromHtml("#708090"_s) },
	{ "Snow"_s->GetHashCode(), Color::FromHtml("#FFFAFA"_s) },
	{ "SpringGreen"_s->GetHashCode(), Color::FromHtml("#00FF7F"_s) },
	{ "SteelBlue"_s->GetHashCode(), Color::FromHtml("#4682B4"_s) },
	{ "Tan"_s->GetHashCode(), Color::FromHtml("#D2B48C"_s) },
	{ "Teal"_s->GetHashCode(), Color::FromHtml("#008080"_s) },
	{ "Thistle"_s->GetHashCode(), Color::FromHtml("#D8BFD8"_s) },
	{ "Tomato"_s->GetHashCode(), Color::FromHtml("#FF6347"_s) },
	{ "Transparent"_s->GetHashCode(), Color::FromHtml("#00000000"_s) },
	{ "Turquoise"_s->GetHashCode(), Color::FromHtml("#40E0D0"_s) },
	{ "Violet"_s->GetHashCode(), Color::FromHtml("#EE82EE"_s) },
	{ "Wheat"_s->GetHashCode(), Color::FromHtml("#F5DEB3"_s) },
	{ "White"_s->GetHashCode(), Color::FromHtml("#FFFFFF"_s) },
	{ "WhiteSmoke"_s->GetHashCode(), Color::FromHtml("#F5F5F5"_s) },
	{ "Yellow"_s->GetHashCode(), Color::FromHtml("#FFFF00"_s) },
	{ "YellowGreen"_s->GetHashCode(), Color::FromHtml("#9ACD32"_s) },
};

Color::Color(float splat) : This(splat, splat, splat, splat)
{

}

Color::Color()
{

}

Color::Color(float r, float g, float b, float a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

Color::Color(const Color& copy)
{
	R = copy.R;
	G = copy.G;
	B = copy.B;
	A = copy.A;
}

bool Color::Equals(const Color& rh) const
{
	return (*this) == rh;
}

bool Color::NearlyEquals(const Color& rh, float epsilon) const
{
	return abs(R - rh.R) <= epsilon
		&& abs(G - rh.G) <= epsilon
		&& abs(B - rh.B) <= epsilon
		&& abs(A - rh.A) <= epsilon;
}

size_t Color::GetHashCode() const
{
	return HashHelper::GetHashCode(R)
		 ^ HashHelper::GetHashCode(G)
		 ^ HashHelper::GetHashCode(B)
		 ^ HashHelper::GetHashCode(A);
}

SString* Color::ToString() const
{
	return SString::Format("{{R: {0}, G: {1}, B: {2}, A: {3}}}"_s, R, G, B, A);
}

float Color::GetComponentOrDefault(size_t index) const
{
	if (!Contains(index))
	{
		return 0;
	}

	const float* ptr = &R;
	return ptr[index];
}

bool Color::Contains(size_t index) const
{
	return index < GetCount();
}

const float& Color::operator [](size_t index) const
{
	if (!Contains(index))
	{
		throw new SIndexOutOfRangeException();
	}

	const float* ptr = &R;
	return ptr[index];
}

float& Color::operator [](size_t index)
{
	if (!Contains(index))
	{
		throw new SIndexOutOfRangeException();
	}

	float* ptr = &R;
	return ptr[index];
}

Color Color::operator -() const
{
	return Color(-R, -G, -B, -A);
}

Color Color::operator +(const Color& value) const
{
	return Color(R + value.R, G + value.G, B + value.B, A + value.A);
}

Color Color::operator -(const Color& value) const
{
	return Color(R - value.R, G - value.G, B - value.B, A + value.A);
}

Color Color::operator *(const Color& value) const
{
	return Color(R * value.R, G * value.G, B * value.B, A + value.A);
}

Color Color::operator /(const Color& value) const
{
	return Color(R / value.R, G / value.G, B / value.B, A + value.A);
}

Color Color::operator ^(const Color& value) const
{
	return AlphaBlend(*this, value);
}

Color& Color::operator +=(const Color& right)
{
	R += right.R;
	G += right.G;
	B += right.B;
	A += right.A;
	return *this;
}

Color& Color::operator -=(const Color& right)
{
	R -= right.R;
	G -= right.G;
	B -= right.B;
	A -= right.A;
	return *this;
}

Color& Color::operator *=(const Color& right)
{
	R *= right.R;
	G *= right.G;
	B *= right.B;
	A *= right.A;
	return *this;
}

Color& Color::operator /=(const Color& right)
{
	R /= right.R;
	G /= right.G;
	B /= right.B;
	A /= right.A;
	return *this;
}

Color& Color::operator ^=(const Color& right)
{
	return (*this) = (*this) ^ right;
}

Color Color::AlphaBlend(const Color& left, const Color& right)
{
	return AlphaBlend(left, right, right.A);
}

Color Color::AlphaBlend(const Color& left, const Color& right, float alpha)
{
	Color r = left * (1.0f - alpha) + right * alpha;
	r.A = 1.0f;
	return r;
}

Color Color::FromUInt(uint32 argb)
{
	uint8 b = (uint8)argb;
	uint8 g = (uint8)(argb >> 8);
	uint8 r = (uint8)(argb >> 16);
	uint8 a = (uint8)(argb >> 24);
	return FromBytes(r, g, b, a);
}

Color Color::FromHtml(SString* html)
{
	if (html == nullptr || html->GetLength() == 0)
	{
		return Color::Transparent;
	}

	// #AARRGGBB
	if (html->GetLength() == 9)
	{
		wistringstream wiss;
		wiss.str(html->Substring(1, 8)->C_Str());
		uint32 hexCode;
		wiss >> hex >> hexCode;
		return Color::FromUInt(hexCode);
	}

	// #RRGGBB
	if (html->GetLength() == 7)
	{
		wistringstream wiss;
		wiss.str(html->Substring(1, 6)->C_Str());
		uint32 hexCode;
		wiss >> hex >> hexCode;
		hexCode |= 0xFF000000;
		return Color::FromUInt(hexCode);
	}

	// In table color.
	auto it = convertTable.find(html->GetHashCode());
	if (it != convertTable.end())
	{
		return it->second;
	}

	return Color::Transparent;
}

Color Color::FromBytes(uint8 r, uint8 g, uint8 b, uint8 a)
{
	constexpr float Inv255 = 1.0f / 255.0f;
	return Color((float)r * Inv255, (float)g * Inv255, (float)b * Inv255, (float)a * Inv255);
}

Color operator +(float left, const Color& right)
{
	return Color(left, left, left, left) + right;
}

Color operator -(float left, const Color& right)
{
	return Color(left, left, left, left) - right;
}

Color operator *(float left, const Color& right)
{
	return Color(left, left, left, left) * right;
}

Color operator /(float left, const Color& right)
{
	return Color(left, left, left, left) / right;
}

Color Color::AliceBlue = FromHtml("#F0F8FF"_s);
Color Color::AntiqueWhite = FromHtml("#FAEBD7"_s);
Color Color::Aqua = FromHtml("#00FFFF"_s);
Color Color::Aquamarine = FromHtml("#7FFFD4"_s);
Color Color::Azure = FromHtml("#F0FFFF"_s);
Color Color::Beige = FromHtml("#F5F5DC"_s);
Color Color::Bisque = FromHtml("#FFE4C4"_s);
Color Color::Black = FromHtml("#000000"_s);
Color Color::BlanchedAlmond = FromHtml("#FFEBCD"_s);
Color Color::Blue = FromHtml("#0000FF"_s);
Color Color::BlueViolet = FromHtml("#8A2BE2"_s);
Color Color::Brown = FromHtml("#A52A2A"_s);
Color Color::BurlyWood = FromHtml("#DEB887"_s);
Color Color::CadetBlue = FromHtml("#5F9EA0"_s);
Color Color::Chartreuse = FromHtml("#7FFF00"_s);
Color Color::Chocolate = FromHtml("#D2691E"_s);
Color Color::Coral = FromHtml("#FF7F50"_s);
Color Color::CornflowerBlue = FromHtml("#6495ED"_s);
Color Color::Cornsilk = FromHtml("#FFF8DC"_s);
Color Color::Crimson = FromHtml("#DC143C"_s);
Color Color::Cyan = FromHtml("#00FFFF"_s);
Color Color::DarkBlue = FromHtml("#00008B"_s);
Color Color::DarkCyan = FromHtml("#008B8B"_s);
Color Color::DarkGoldenrod = FromHtml("#B8860B"_s);
Color Color::DarkGray = FromHtml("#A9A9A9"_s);
Color Color::DarkGreen = FromHtml("#006400"_s);
Color Color::DarkKhaki = FromHtml("#BDB76B"_s);
Color Color::DarkMagenta = FromHtml("#8B008B"_s);
Color Color::DarkOliveGreen = FromHtml("#556B2F"_s);
Color Color::DarkOrange = FromHtml("#FF8C00"_s);
Color Color::DarkOrchid = FromHtml("#9932CC"_s);
Color Color::DarkRed = FromHtml("#8B0000"_s);
Color Color::DarkSalmon = FromHtml("#E9967A"_s);
Color Color::DarkSeaGreen = FromHtml("#8FBC8B"_s);
Color Color::DarkSlateBlue = FromHtml("#483D8B"_s);
Color Color::DarkSlateGray = FromHtml("#2F4F4F"_s);
Color Color::DarkTurquoise = FromHtml("#00CED1"_s);
Color Color::DarkViolet = FromHtml("#9400D3"_s);
Color Color::DeepPink = FromHtml("#FF1493"_s);
Color Color::DeepSkyBlue = FromHtml("#00BFFF"_s);
Color Color::DimGray = FromHtml("#696969"_s);
Color Color::DodgerBlue = FromHtml("#1E90FF"_s);
Color Color::Firebrick = FromHtml("#B22222"_s);
Color Color::FloralWhite = FromHtml("#FFFAF0"_s);
Color Color::ForestGreen = FromHtml("#228B22"_s);
Color Color::Fuchsia = FromHtml("#FF00FF"_s);
Color Color::Gainsboro = FromHtml("#DCDCDC"_s);
Color Color::GhostWhite = FromHtml("#F8F8FF"_s);
Color Color::Gold = FromHtml("#FFD700"_s);
Color Color::Goldenrod = FromHtml("#DAA520"_s);
Color Color::Gray = FromHtml("#808080"_s);
Color Color::Green = FromHtml("#008000"_s);
Color Color::GreenYellow = FromHtml("#ADFF2F"_s);
Color Color::Honeydew = FromHtml("#F0FFF0"_s);
Color Color::HotPink = FromHtml("#FF69B4"_s);
Color Color::IndianRed = FromHtml("#CD5C5C"_s);
Color Color::Indigo = FromHtml("#4B0082"_s);
Color Color::Ivory = FromHtml("#FFFFF0"_s);
Color Color::Khaki = FromHtml("#F0E68C"_s);
Color Color::Lavender = FromHtml("#E6E6FA"_s);
Color Color::LavenderBlush = FromHtml("#FFF0F5"_s);
Color Color::LawnGreen = FromHtml("#7CFC00"_s);
Color Color::LemonChiffon = FromHtml("#FFFACD"_s);
Color Color::LightBlue = FromHtml("#ADD8E6"_s);
Color Color::LightCoral = FromHtml("#F08080"_s);
Color Color::LightCyan = FromHtml("#E0FFFF"_s);
Color Color::LightGoldenrodYellow = FromHtml("#FAFAD2"_s);
Color Color::LightGray = FromHtml("#D3D3D3"_s);
Color Color::LightGreen = FromHtml("#90EE90"_s);
Color Color::LightPink = FromHtml("#FFB6C1"_s);
Color Color::LightSalmon = FromHtml("#FFA07A"_s);
Color Color::LightSeaGreen = FromHtml("#20B2AA"_s);
Color Color::LightSkyBlue = FromHtml("#87CEFA"_s);
Color Color::LightSlateGray = FromHtml("#778899"_s);
Color Color::LightSteelBlue = FromHtml("#B0C4DE"_s);
Color Color::LightYellow = FromHtml("#FFFFE0"_s);
Color Color::Lime = FromHtml("#00FF00"_s);
Color Color::LimeGreen = FromHtml("#32CD32"_s);
Color Color::Linen = FromHtml("#FAF0E6"_s);
Color Color::Magenta = FromHtml("#FF00FF"_s);
Color Color::Maroon = FromHtml("#800000"_s);
Color Color::MediumAquamarine = FromHtml("#66CDAA"_s);
Color Color::MediumBlue = FromHtml("#0000CD"_s);
Color Color::MediumOrchid = FromHtml("#BA55D3"_s);
Color Color::MediumPurple = FromHtml("#9370DB"_s);
Color Color::MediumSeaGreen = FromHtml("#3CB371"_s);
Color Color::MediumSlateBlue = FromHtml("#7B68EE"_s);
Color Color::MediumSpringGreen = FromHtml("#00FA9A"_s);
Color Color::MediumTurquoise = FromHtml("#48D1CC"_s);
Color Color::MediumVioletRed = FromHtml("#C71585"_s);
Color Color::MidnightBlue = FromHtml("#191970"_s);
Color Color::MintCream = FromHtml("#F5FFFA"_s);
Color Color::MistyRose = FromHtml("#FFE4E1"_s);
Color Color::Moccasin = FromHtml("#FFE4B5"_s);
Color Color::NavajoWhite = FromHtml("#FFDEAD"_s);
Color Color::Navy = FromHtml("#000080"_s);
Color Color::OldLace = FromHtml("#FDF5E6"_s);
Color Color::Olive = FromHtml("#808000"_s);
Color Color::OliveDrab = FromHtml("#6B8E23"_s);
Color Color::Orange = FromHtml("#FFA500"_s);
Color Color::OrangeRed = FromHtml("#FF4500"_s);
Color Color::Orchid = FromHtml("#DA70D6"_s);
Color Color::PaleGoldenrod = FromHtml("#EEE8AA"_s);
Color Color::PaleGreen = FromHtml("#98FB98"_s);
Color Color::PaleTurquoise = FromHtml("#AFEEEE"_s);
Color Color::PaleVioletRed = FromHtml("#DB7093"_s);
Color Color::PapayaWhip = FromHtml("#FFEFD5"_s);
Color Color::PeachPuff = FromHtml("#FFDAB9"_s);
Color Color::Peru = FromHtml("#CD853F"_s);
Color Color::Pink = FromHtml("#FFC0CB"_s);
Color Color::Plum = FromHtml("#DDA0DD"_s);
Color Color::PowderBlue = FromHtml("#B0E0E6"_s);
Color Color::Purple = FromHtml("#800080"_s);
Color Color::Red = FromHtml("#FF0000"_s);
Color Color::RosyBrown = FromHtml("#BC8F8F"_s);
Color Color::RoyalBlue = FromHtml("#4169E1"_s);
Color Color::SaddleBrown = FromHtml("#8B4513"_s);
Color Color::Salmon = FromHtml("#FA8072"_s);
Color Color::SandyBrown = FromHtml("#F4A460"_s);
Color Color::SeaGreen = FromHtml("#2E8B57"_s);
Color Color::SeaShell = FromHtml("#FFF5EE"_s);
Color Color::Sienna = FromHtml("#A0522D"_s);
Color Color::Silver = FromHtml("#C0C0C0"_s);
Color Color::SkyBlue = FromHtml("#87CEEB"_s);
Color Color::SlateBlue = FromHtml("#6A5ACD"_s);
Color Color::SlateGray = FromHtml("#708090"_s);
Color Color::Snow = FromHtml("#FFFAFA"_s);
Color Color::SpringGreen = FromHtml("#00FF7F"_s);
Color Color::SteelBlue = FromHtml("#4682B4"_s);
Color Color::Tan = FromHtml("#D2B48C"_s);
Color Color::Teal = FromHtml("#008080"_s);
Color Color::Thistle = FromHtml("#D8BFD8"_s);
Color Color::Tomato = FromHtml("#FF6347"_s);
Color Color::Transparent = FromHtml("#00000000"_s);
Color Color::Turquoise = FromHtml("#40E0D0"_s);
Color Color::Violet = FromHtml("#EE82EE"_s);
Color Color::Wheat = FromHtml("#F5DEB3"_s);
Color Color::White = FromHtml("#FFFFFF"_s);
Color Color::WhiteSmoke = FromHtml("#F5F5F5"_s);
Color Color::Yellow = FromHtml("#FFFF00"_s);
Color Color::YellowGreen = FromHtml("#9ACD32"_s);