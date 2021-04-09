// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Numerics/Color.h"

#include "Core/String.h"
#include "HashHelper.h"
#include "Exception/IndexOutOfRangeException.h"

using namespace std;

map<size_t, Color> Color::convertTable =
{
	{ HashHelper::GetHashCode("AliceBlue"), Color::FromHtml("#F0F8FF") },
	{ HashHelper::GetHashCode("AntiqueWhite"), Color::FromHtml("#FAEBD7") },
	{ HashHelper::GetHashCode("Aqua"), Color::FromHtml("#00FFFF") },
	{ HashHelper::GetHashCode("Aquamarine"), Color::FromHtml("#7FFFD4") },
	{ HashHelper::GetHashCode("Azure"), Color::FromHtml("#F0FFFF") },
	{ HashHelper::GetHashCode("Beige"), Color::FromHtml("#F5F5DC") },
	{ HashHelper::GetHashCode("Bisque"), Color::FromHtml("#FFE4C4") },
	{ HashHelper::GetHashCode("Black"), Color::FromHtml("#000000") },
	{ HashHelper::GetHashCode("BlanchedAlmond"), Color::FromHtml("#FFEBCD") },
	{ HashHelper::GetHashCode("Blue"), Color::FromHtml("#0000FF") },
	{ HashHelper::GetHashCode("BlueViolet"), Color::FromHtml("#8A2BE2") },
	{ HashHelper::GetHashCode("Brown"), Color::FromHtml("#A52A2A") },
	{ HashHelper::GetHashCode("BurlyWood"), Color::FromHtml("#DEB887") },
	{ HashHelper::GetHashCode("CadetBlue"), Color::FromHtml("#5F9EA0") },
	{ HashHelper::GetHashCode("Chartreuse"), Color::FromHtml("#7FFF00") },
	{ HashHelper::GetHashCode("Chocolate"), Color::FromHtml("#D2691E") },
	{ HashHelper::GetHashCode("Coral"), Color::FromHtml("#FF7F50") },
	{ HashHelper::GetHashCode("CornflowerBlue"), Color::FromHtml("#6495ED") },
	{ HashHelper::GetHashCode("Cornsilk"), Color::FromHtml("#FFF8DC") },
	{ HashHelper::GetHashCode("Crimson"), Color::FromHtml("#DC143C") },
	{ HashHelper::GetHashCode("Cyan"), Color::FromHtml("#00FFFF") },
	{ HashHelper::GetHashCode("DarkBlue"), Color::FromHtml("#00008B") },
	{ HashHelper::GetHashCode("DarkCyan"), Color::FromHtml("#008B8B") },
	{ HashHelper::GetHashCode("DarkGoldenrod"), Color::FromHtml("#B8860B") },
	{ HashHelper::GetHashCode("DarkGray"), Color::FromHtml("#A9A9A9") },
	{ HashHelper::GetHashCode("DarkGreen"), Color::FromHtml("#006400") },
	{ HashHelper::GetHashCode("DarkKhaki"), Color::FromHtml("#BDB76B") },
	{ HashHelper::GetHashCode("DarkMagenta"), Color::FromHtml("#8B008B") },
	{ HashHelper::GetHashCode("DarkOliveGreen"), Color::FromHtml("#556B2F") },
	{ HashHelper::GetHashCode("DarkOrange"), Color::FromHtml("#FF8C00") },
	{ HashHelper::GetHashCode("DarkOrchid"), Color::FromHtml("#9932CC") },
	{ HashHelper::GetHashCode("DarkRed"), Color::FromHtml("#8B0000") },
	{ HashHelper::GetHashCode("DarkSalmon"), Color::FromHtml("#E9967A") },
	{ HashHelper::GetHashCode("DarkSeaGreen"), Color::FromHtml("#8FBC8B") },
	{ HashHelper::GetHashCode("DarkSlateBlue"), Color::FromHtml("#483D8B") },
	{ HashHelper::GetHashCode("DarkSlateGray"), Color::FromHtml("#2F4F4F") },
	{ HashHelper::GetHashCode("DarkTurquoise"), Color::FromHtml("#00CED1") },
	{ HashHelper::GetHashCode("DarkViolet"), Color::FromHtml("#9400D3") },
	{ HashHelper::GetHashCode("DeepPink"), Color::FromHtml("#FF1493") },
	{ HashHelper::GetHashCode("DeepSkyBlue"), Color::FromHtml("#00BFFF") },
	{ HashHelper::GetHashCode("DimGray"), Color::FromHtml("#696969") },
	{ HashHelper::GetHashCode("DodgerBlue"), Color::FromHtml("#1E90FF") },
	{ HashHelper::GetHashCode("Firebrick"), Color::FromHtml("#B22222") },
	{ HashHelper::GetHashCode("FloralWhite"), Color::FromHtml("#FFFAF0") },
	{ HashHelper::GetHashCode("ForestGreen"), Color::FromHtml("#228B22") },
	{ HashHelper::GetHashCode("Fuchsia"), Color::FromHtml("#FF00FF") },
	{ HashHelper::GetHashCode("Gainsboro"), Color::FromHtml("#DCDCDC") },
	{ HashHelper::GetHashCode("GhostWhite"), Color::FromHtml("#F8F8FF") },
	{ HashHelper::GetHashCode("Gold"), Color::FromHtml("#FFD700") },
	{ HashHelper::GetHashCode("Goldenrod"), Color::FromHtml("#DAA520") },
	{ HashHelper::GetHashCode("Gray"), Color::FromHtml("#808080") },
	{ HashHelper::GetHashCode("Green"), Color::FromHtml("#008000") },
	{ HashHelper::GetHashCode("GreenYellow"), Color::FromHtml("#ADFF2F") },
	{ HashHelper::GetHashCode("Honeydew"), Color::FromHtml("#F0FFF0") },
	{ HashHelper::GetHashCode("HotPink"), Color::FromHtml("#FF69B4") },
	{ HashHelper::GetHashCode("IndianRed"), Color::FromHtml("#CD5C5C") },
	{ HashHelper::GetHashCode("Indigo"), Color::FromHtml("#4B0082") },
	{ HashHelper::GetHashCode("Ivory"), Color::FromHtml("#FFFFF0") },
	{ HashHelper::GetHashCode("Khaki"), Color::FromHtml("#F0E68C") },
	{ HashHelper::GetHashCode("Lavender"), Color::FromHtml("#E6E6FA") },
	{ HashHelper::GetHashCode("LavenderBlush"), Color::FromHtml("#FFF0F5") },
	{ HashHelper::GetHashCode("LawnGreen"), Color::FromHtml("#7CFC00") },
	{ HashHelper::GetHashCode("LemonChiffon"), Color::FromHtml("#FFFACD") },
	{ HashHelper::GetHashCode("LightBlue"), Color::FromHtml("#ADD8E6") },
	{ HashHelper::GetHashCode("LightCoral"), Color::FromHtml("#F08080") },
	{ HashHelper::GetHashCode("LightCyan"), Color::FromHtml("#E0FFFF") },
	{ HashHelper::GetHashCode("LightGoldenrodYellow"), Color::FromHtml("#FAFAD2") },
	{ HashHelper::GetHashCode("LightGray"), Color::FromHtml("#D3D3D3") },
	{ HashHelper::GetHashCode("LightGreen"), Color::FromHtml("#90EE90") },
	{ HashHelper::GetHashCode("LightPink"), Color::FromHtml("#FFB6C1") },
	{ HashHelper::GetHashCode("LightSalmon"), Color::FromHtml("#FFA07A") },
	{ HashHelper::GetHashCode("LightSeaGreen"), Color::FromHtml("#20B2AA") },
	{ HashHelper::GetHashCode("LightSkyBlue"), Color::FromHtml("#87CEFA") },
	{ HashHelper::GetHashCode("LightSlateGray"), Color::FromHtml("#778899") },
	{ HashHelper::GetHashCode("LightSteelBlue"), Color::FromHtml("#B0C4DE") },
	{ HashHelper::GetHashCode("LightYellow"), Color::FromHtml("#FFFFE0") },
	{ HashHelper::GetHashCode("Lime"), Color::FromHtml("#00FF00") },
	{ HashHelper::GetHashCode("LimeGreen"), Color::FromHtml("#32CD32") },
	{ HashHelper::GetHashCode("Linen"), Color::FromHtml("#FAF0E6") },
	{ HashHelper::GetHashCode("Magenta"), Color::FromHtml("#FF00FF") },
	{ HashHelper::GetHashCode("Maroon"), Color::FromHtml("#800000") },
	{ HashHelper::GetHashCode("MediumAquamarine"), Color::FromHtml("#66CDAA") },
	{ HashHelper::GetHashCode("MediumBlue"), Color::FromHtml("#0000CD") },
	{ HashHelper::GetHashCode("MediumOrchid"), Color::FromHtml("#BA55D3") },
	{ HashHelper::GetHashCode("MediumPurple"), Color::FromHtml("#9370DB") },
	{ HashHelper::GetHashCode("MediumSeaGreen"), Color::FromHtml("#3CB371") },
	{ HashHelper::GetHashCode("MediumSlateBlue"), Color::FromHtml("#7B68EE") },
	{ HashHelper::GetHashCode("MediumSpringGreen"), Color::FromHtml("#00FA9A") },
	{ HashHelper::GetHashCode("MediumTurquoise"), Color::FromHtml("#48D1CC") },
	{ HashHelper::GetHashCode("MediumVioletRed"), Color::FromHtml("#C71585") },
	{ HashHelper::GetHashCode("MidnightBlue"), Color::FromHtml("#191970") },
	{ HashHelper::GetHashCode("MintCream"), Color::FromHtml("#F5FFFA") },
	{ HashHelper::GetHashCode("MistyRose"), Color::FromHtml("#FFE4E1") },
	{ HashHelper::GetHashCode("Moccasin"), Color::FromHtml("#FFE4B5") },
	{ HashHelper::GetHashCode("NavajoWhite"), Color::FromHtml("#FFDEAD") },
	{ HashHelper::GetHashCode("Navy"), Color::FromHtml("#000080") },
	{ HashHelper::GetHashCode("OldLace"), Color::FromHtml("#FDF5E6") },
	{ HashHelper::GetHashCode("Olive"), Color::FromHtml("#808000") },
	{ HashHelper::GetHashCode("OliveDrab"), Color::FromHtml("#6B8E23") },
	{ HashHelper::GetHashCode("Orange"), Color::FromHtml("#FFA500") },
	{ HashHelper::GetHashCode("OrangeRed"), Color::FromHtml("#FF4500") },
	{ HashHelper::GetHashCode("Orchid"), Color::FromHtml("#DA70D6") },
	{ HashHelper::GetHashCode("PaleGoldenrod"), Color::FromHtml("#EEE8AA") },
	{ HashHelper::GetHashCode("PaleGreen"), Color::FromHtml("#98FB98") },
	{ HashHelper::GetHashCode("PaleTurquoise"), Color::FromHtml("#AFEEEE") },
	{ HashHelper::GetHashCode("PaleVioletRed"), Color::FromHtml("#DB7093") },
	{ HashHelper::GetHashCode("PapayaWhip"), Color::FromHtml("#FFEFD5") },
	{ HashHelper::GetHashCode("PeachPuff"), Color::FromHtml("#FFDAB9") },
	{ HashHelper::GetHashCode("Peru"), Color::FromHtml("#CD853F") },
	{ HashHelper::GetHashCode("Pink"), Color::FromHtml("#FFC0CB") },
	{ HashHelper::GetHashCode("Plum"), Color::FromHtml("#DDA0DD") },
	{ HashHelper::GetHashCode("PowderBlue"), Color::FromHtml("#B0E0E6") },
	{ HashHelper::GetHashCode("Purple"), Color::FromHtml("#800080") },
	{ HashHelper::GetHashCode("Red"), Color::FromHtml("#FF0000") },
	{ HashHelper::GetHashCode("RosyBrown"), Color::FromHtml("#BC8F8F") },
	{ HashHelper::GetHashCode("RoyalBlue"), Color::FromHtml("#4169E1") },
	{ HashHelper::GetHashCode("SaddleBrown"), Color::FromHtml("#8B4513") },
	{ HashHelper::GetHashCode("Salmon"), Color::FromHtml("#FA8072") },
	{ HashHelper::GetHashCode("SandyBrown"), Color::FromHtml("#F4A460") },
	{ HashHelper::GetHashCode("SeaGreen"), Color::FromHtml("#2E8B57") },
	{ HashHelper::GetHashCode("SeaShell"), Color::FromHtml("#FFF5EE") },
	{ HashHelper::GetHashCode("Sienna"), Color::FromHtml("#A0522D") },
	{ HashHelper::GetHashCode("Silver"), Color::FromHtml("#C0C0C0") },
	{ HashHelper::GetHashCode("SkyBlue"), Color::FromHtml("#87CEEB") },
	{ HashHelper::GetHashCode("SlateBlue"), Color::FromHtml("#6A5ACD") },
	{ HashHelper::GetHashCode("SlateGray"), Color::FromHtml("#708090") },
	{ HashHelper::GetHashCode("Snow"), Color::FromHtml("#FFFAFA") },
	{ HashHelper::GetHashCode("SpringGreen"), Color::FromHtml("#00FF7F") },
	{ HashHelper::GetHashCode("SteelBlue"), Color::FromHtml("#4682B4") },
	{ HashHelper::GetHashCode("Tan"), Color::FromHtml("#D2B48C") },
	{ HashHelper::GetHashCode("Teal"), Color::FromHtml("#008080") },
	{ HashHelper::GetHashCode("Thistle"), Color::FromHtml("#D8BFD8") },
	{ HashHelper::GetHashCode("Tomato"), Color::FromHtml("#FF6347") },
	{ HashHelper::GetHashCode("Transparent"), Color::FromHtml("#00000000") },
	{ HashHelper::GetHashCode("Turquoise"), Color::FromHtml("#40E0D0") },
	{ HashHelper::GetHashCode("Violet"), Color::FromHtml("#EE82EE") },
	{ HashHelper::GetHashCode("Wheat"), Color::FromHtml("#F5DEB3") },
	{ HashHelper::GetHashCode("White"), Color::FromHtml("#FFFFFF") },
	{ HashHelper::GetHashCode("WhiteSmoke"), Color::FromHtml("#F5F5F5") },
	{ HashHelper::GetHashCode("Yellow"), Color::FromHtml("#FFFF00") },
	{ HashHelper::GetHashCode("YellowGreen"), Color::FromHtml("#9ACD32") },
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
	auto it = convertTable.find(HashHelper::GetHashCode(html->AsMultiByte().c_str()));
	if (it != convertTable.end())
	{
		return it->second;
	}

	return Color::Transparent;
}

Color Color::FromHtml(string_view html)
{
	if (html.length() == 0)
	{
		return Color::Transparent;
	}

	// #AARRGGBB
	if (html.length() == 9)
	{
		istringstream wiss;
		wiss.str(html.substr(1, 8).data());
		uint32 hexCode;
		wiss >> hex >> hexCode;
		return Color::FromUInt(hexCode);
	}

	// #RRGGBB
	if (html.length() == 7)
	{
		istringstream wiss;
		wiss.str(html.substr(1, 6).data());
		uint32 hexCode;
		wiss >> hex >> hexCode;
		hexCode |= 0xFF000000;
		return Color::FromUInt(hexCode);
	}

	// In table color.
	auto it = convertTable.find(HashHelper::GetHashCode(html.data()));
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

Color Color::AliceBlue = FromHtml("#F0F8FF");
Color Color::AntiqueWhite = FromHtml("#FAEBD7");
Color Color::Aqua = FromHtml("#00FFFF");
Color Color::Aquamarine = FromHtml("#7FFFD4");
Color Color::Azure = FromHtml("#F0FFFF");
Color Color::Beige = FromHtml("#F5F5DC");
Color Color::Bisque = FromHtml("#FFE4C4");
Color Color::Black = FromHtml("#000000");
Color Color::BlanchedAlmond = FromHtml("#FFEBCD");
Color Color::Blue = FromHtml("#0000FF");
Color Color::BlueViolet = FromHtml("#8A2BE2");
Color Color::Brown = FromHtml("#A52A2A");
Color Color::BurlyWood = FromHtml("#DEB887");
Color Color::CadetBlue = FromHtml("#5F9EA0");
Color Color::Chartreuse = FromHtml("#7FFF00");
Color Color::Chocolate = FromHtml("#D2691E");
Color Color::Coral = FromHtml("#FF7F50");
Color Color::CornflowerBlue = FromHtml("#6495ED");
Color Color::Cornsilk = FromHtml("#FFF8DC");
Color Color::Crimson = FromHtml("#DC143C");
Color Color::Cyan = FromHtml("#00FFFF");
Color Color::DarkBlue = FromHtml("#00008B");
Color Color::DarkCyan = FromHtml("#008B8B");
Color Color::DarkGoldenrod = FromHtml("#B8860B");
Color Color::DarkGray = FromHtml("#A9A9A9");
Color Color::DarkGreen = FromHtml("#006400");
Color Color::DarkKhaki = FromHtml("#BDB76B");
Color Color::DarkMagenta = FromHtml("#8B008B");
Color Color::DarkOliveGreen = FromHtml("#556B2F");
Color Color::DarkOrange = FromHtml("#FF8C00");
Color Color::DarkOrchid = FromHtml("#9932CC");
Color Color::DarkRed = FromHtml("#8B0000");
Color Color::DarkSalmon = FromHtml("#E9967A");
Color Color::DarkSeaGreen = FromHtml("#8FBC8B");
Color Color::DarkSlateBlue = FromHtml("#483D8B");
Color Color::DarkSlateGray = FromHtml("#2F4F4F");
Color Color::DarkTurquoise = FromHtml("#00CED1");
Color Color::DarkViolet = FromHtml("#9400D3");
Color Color::DeepPink = FromHtml("#FF1493");
Color Color::DeepSkyBlue = FromHtml("#00BFFF");
Color Color::DimGray = FromHtml("#696969");
Color Color::DodgerBlue = FromHtml("#1E90FF");
Color Color::Firebrick = FromHtml("#B22222");
Color Color::FloralWhite = FromHtml("#FFFAF0");
Color Color::ForestGreen = FromHtml("#228B22");
Color Color::Fuchsia = FromHtml("#FF00FF");
Color Color::Gainsboro = FromHtml("#DCDCDC");
Color Color::GhostWhite = FromHtml("#F8F8FF");
Color Color::Gold = FromHtml("#FFD700");
Color Color::Goldenrod = FromHtml("#DAA520");
Color Color::Gray = FromHtml("#808080");
Color Color::Green = FromHtml("#008000");
Color Color::GreenYellow = FromHtml("#ADFF2F");
Color Color::Honeydew = FromHtml("#F0FFF0");
Color Color::HotPink = FromHtml("#FF69B4");
Color Color::IndianRed = FromHtml("#CD5C5C");
Color Color::Indigo = FromHtml("#4B0082");
Color Color::Ivory = FromHtml("#FFFFF0");
Color Color::Khaki = FromHtml("#F0E68C");
Color Color::Lavender = FromHtml("#E6E6FA");
Color Color::LavenderBlush = FromHtml("#FFF0F5");
Color Color::LawnGreen = FromHtml("#7CFC00");
Color Color::LemonChiffon = FromHtml("#FFFACD");
Color Color::LightBlue = FromHtml("#ADD8E6");
Color Color::LightCoral = FromHtml("#F08080");
Color Color::LightCyan = FromHtml("#E0FFFF");
Color Color::LightGoldenrodYellow = FromHtml("#FAFAD2");
Color Color::LightGray = FromHtml("#D3D3D3");
Color Color::LightGreen = FromHtml("#90EE90");
Color Color::LightPink = FromHtml("#FFB6C1");
Color Color::LightSalmon = FromHtml("#FFA07A");
Color Color::LightSeaGreen = FromHtml("#20B2AA");
Color Color::LightSkyBlue = FromHtml("#87CEFA");
Color Color::LightSlateGray = FromHtml("#778899");
Color Color::LightSteelBlue = FromHtml("#B0C4DE");
Color Color::LightYellow = FromHtml("#FFFFE0");
Color Color::Lime = FromHtml("#00FF00");
Color Color::LimeGreen = FromHtml("#32CD32");
Color Color::Linen = FromHtml("#FAF0E6");
Color Color::Magenta = FromHtml("#FF00FF");
Color Color::Maroon = FromHtml("#800000");
Color Color::MediumAquamarine = FromHtml("#66CDAA");
Color Color::MediumBlue = FromHtml("#0000CD");
Color Color::MediumOrchid = FromHtml("#BA55D3");
Color Color::MediumPurple = FromHtml("#9370DB");
Color Color::MediumSeaGreen = FromHtml("#3CB371");
Color Color::MediumSlateBlue = FromHtml("#7B68EE");
Color Color::MediumSpringGreen = FromHtml("#00FA9A");
Color Color::MediumTurquoise = FromHtml("#48D1CC");
Color Color::MediumVioletRed = FromHtml("#C71585");
Color Color::MidnightBlue = FromHtml("#191970");
Color Color::MintCream = FromHtml("#F5FFFA");
Color Color::MistyRose = FromHtml("#FFE4E1");
Color Color::Moccasin = FromHtml("#FFE4B5");
Color Color::NavajoWhite = FromHtml("#FFDEAD");
Color Color::Navy = FromHtml("#000080");
Color Color::OldLace = FromHtml("#FDF5E6");
Color Color::Olive = FromHtml("#808000");
Color Color::OliveDrab = FromHtml("#6B8E23");
Color Color::Orange = FromHtml("#FFA500");
Color Color::OrangeRed = FromHtml("#FF4500");
Color Color::Orchid = FromHtml("#DA70D6");
Color Color::PaleGoldenrod = FromHtml("#EEE8AA");
Color Color::PaleGreen = FromHtml("#98FB98");
Color Color::PaleTurquoise = FromHtml("#AFEEEE");
Color Color::PaleVioletRed = FromHtml("#DB7093");
Color Color::PapayaWhip = FromHtml("#FFEFD5");
Color Color::PeachPuff = FromHtml("#FFDAB9");
Color Color::Peru = FromHtml("#CD853F");
Color Color::Pink = FromHtml("#FFC0CB");
Color Color::Plum = FromHtml("#DDA0DD");
Color Color::PowderBlue = FromHtml("#B0E0E6");
Color Color::Purple = FromHtml("#800080");
Color Color::Red = FromHtml("#FF0000");
Color Color::RosyBrown = FromHtml("#BC8F8F");
Color Color::RoyalBlue = FromHtml("#4169E1");
Color Color::SaddleBrown = FromHtml("#8B4513");
Color Color::Salmon = FromHtml("#FA8072");
Color Color::SandyBrown = FromHtml("#F4A460");
Color Color::SeaGreen = FromHtml("#2E8B57");
Color Color::SeaShell = FromHtml("#FFF5EE");
Color Color::Sienna = FromHtml("#A0522D");
Color Color::Silver = FromHtml("#C0C0C0");
Color Color::SkyBlue = FromHtml("#87CEEB");
Color Color::SlateBlue = FromHtml("#6A5ACD");
Color Color::SlateGray = FromHtml("#708090");
Color Color::Snow = FromHtml("#FFFAFA");
Color Color::SpringGreen = FromHtml("#00FF7F");
Color Color::SteelBlue = FromHtml("#4682B4");
Color Color::Tan = FromHtml("#D2B48C");
Color Color::Teal = FromHtml("#008080");
Color Color::Thistle = FromHtml("#D8BFD8");
Color Color::Tomato = FromHtml("#FF6347");
Color Color::Transparent = FromHtml("#00000000");
Color Color::Turquoise = FromHtml("#40E0D0");
Color Color::Violet = FromHtml("#EE82EE");
Color Color::Wheat = FromHtml("#F5DEB3");
Color Color::White = FromHtml("#FFFFFF");
Color Color::WhiteSmoke = FromHtml("#F5F5F5");
Color Color::Yellow = FromHtml("#FFFF00");
Color Color::YellowGreen = FromHtml("#9ACD32");