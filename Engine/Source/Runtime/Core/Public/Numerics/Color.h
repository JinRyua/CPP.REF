// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "TNumericsBasicOperator.h"

#include <map>
#include <string_view>
#include "Core/CoreConcepts.h"

class SString;

#pragma warning(disable: 4251)
#pragma pack(push, 4)
/// <summary>
/// 색을 표현합니다.
/// </summary>
struct CORE_API Color : public TNumericsBasicOperator<Color, float, float, float, float>
{
	using This = Color;

private:
	Color(float splat);

	static std::map<size_t, Color> convertTable;

public:
	/// <summary>
	/// R 값을 나타냅니다.
	/// </summary>
	float R;

	/// <summary>
	/// G 값을 나타냅니다.
	/// </summary>
	float G;

	/// <summary>
	/// B 값을 나타냅니다.
	/// </summary>
	float B;

	/// <summary>
	/// A 값을 나타냅니다.
	/// </summary>
	float A;

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	Color();

	/// <summary>
	/// 개체를 초기화합니다. 
	/// </summary>
	/// <param name="r"> R 값을 전달합니다. </param>
	/// <param name="g"> G 값을 전달합니다. </param>
	/// <param name="b"> B 값을 전달합니다. </param>
	/// <param name="a"> A 값을 전달합니다. </param>
	Color(float r, float g, float b, float a = 1);

	/// <summary>
	/// 개체를 초기화합니다.
	/// </summary>
	/// <param name="copy"> 초기화 값을 전달합니다. </param>
	Color(const Color& copy);

	/// <summary>
	/// 대상 색과 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool Equals(const Color& rh) const;

	/// <summary>
	/// 대상 색과 같은지 비교합니다.
	/// </summary>
	/// <param name="rh"> 대상 개체를 전달합니다. </param>
	/// <param name="epsilon"> 비교 오차를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool NearlyEquals(const Color& rh, float epsilon) const;

	/// <summary>
	/// 해시 코드 값을 가져옵니다.
	/// </summary>
	/// <returns> 값이 반환됩니다. </returns>
	size_t GetHashCode() const;

	/// <summary>
	/// 개체의 간단한 설명을 텍스트 형식으로 가져옵니다.
	/// </summary>
	/// <returns> 텍스트 개체가 반환됩니다. </returns>
	SString* ToString() const;

	/// <summary>
	/// 컴포넌트 값을 가져옵니다.
	/// </summary>
	/// <param name="index"> 컴포넌트 위치를 전달합니다. </param>
	/// <returns> 값이 반환됩니다. </returns>
	float GetComponentOrDefault(size_t index) const;

	/// <summary>
	/// 벡터 형식에서 값을 생성합니다.
	/// </summary>
	/// <param name="vector"> 벡터 형식의 값을 전달합니다. </param>
	template<TIsVectorType T>
	inline void Construct(const T& vector);

	/// <summary>
	/// 벡터 형식으로 변환합니다.
	/// </summary>
	/// <returns> 변환된 벡터 형식 값이 반환됩니다. </returns>
	template<TIsVectorType T>
	inline T Cast() const;

	/// <summary>
	/// 해당 인덱스가 포함되어 있는지 검사합니다.
	/// </summary>
	/// <param name="index"> 인덱스를 전달합니다. </param>
	/// <returns> 검사 결과가 반환됩니다. </returns>
	bool Contains(size_t index) const;

	/// <summary>
	/// 컴포넌트 개수를 가져옵니다.
	/// </summary>
	/// <returns> 개수가 반환됩니다. </returns>
	size_t GetCount() const { return 4; }

	const float& operator [](size_t index) const;
	float& operator [](size_t index);

	Color operator -() const;
	Color operator +(const Color& right) const;
	Color operator -(const Color& right) const;
	Color operator *(const Color& right) const;
	Color operator /(const Color& right) const;
	Color operator ^(const Color& right) const;

	Color& operator +=(const Color& right);
	Color& operator -=(const Color& right);
	Color& operator *=(const Color& right);
	Color& operator /=(const Color& right);
	Color& operator ^=(const Color& right);

	/// <summary>
	/// 알파 블렌딩을 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 값을 전달합니다. </param>
	/// <param name="right"> 두 번째 값을 전달합니다. </param>
	/// <returns> 블렌딩 결과가 반환됩니다. </returns>
	static Color AlphaBlend(const Color& left, const Color& right);

	/// <summary>
	/// 알파 블렌딩을 계산합니다.
	/// </summary>
	/// <param name="left"> 첫 번째 값을 전달합니다. </param>
	/// <param name="right"> 두 번째 값을 전달합니다. </param>
	/// <param name="alpha"> 덮어쓸 알파 값을 전달합니다. </param>
	/// <returns> 블렌딩 결과가 반환됩니다. </returns>
	static Color AlphaBlend(const Color& left, const Color& right, float alpha);

	/// <summary>
	/// 부호 없는 32비트 정수형에서 색상 값을 생성합니다.
	/// </summary>
	/// <param name="argb"> 값을 전달합니다. </param>
	/// <returns> 색상 값이 반환됩니다. </returns>
	static Color FromUInt(uint32 argb);

	/// <summary>
	/// HTML 텍스트에서 색상 값을 생성합니다.
	/// </summary>
	/// <param name="html"> 텍스트 값을 전달합니다. </param>
	/// <returns> 색상 값이 반환됩니다. </returns>
	static Color FromHtml(SString* html);

	/// <summary>
	/// HTML 텍스트에서 색상 값을 생성합니다.
	/// </summary>
	/// <param name="html"> 텍스트 값을 전달합니다. </param>
	/// <returns> 색상 값이 반환됩니다. </returns>
	static Color FromHtml(std::string_view html);

	/// <summary>
	/// 바이트 값에서 색상 값을 생성합니다.
	/// </summary>
	/// <param name="r"> R 값을 전달합니다. </param>
	/// <param name="g"> G 값을 전달합니다. </param>
	/// <param name="b"> B 값을 전달합니다. </param>
	/// <param name="a"> A 값을 전달합니다. </param>
	/// <returns> 색상 값이 반환됩니다. </returns>
	static Color FromBytes(uint8 r, uint8 g, uint8 b, uint8 a);
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color AliceBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color AntiqueWhite;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Aqua;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Aquamarine;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Azure;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Beige;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Bisque;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Black;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color BlanchedAlmond;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Blue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color BlueViolet;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Brown;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color BurlyWood;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color CadetBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Chartreuse;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Chocolate;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Coral;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color CornflowerBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Cornsilk;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Crimson;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Cyan;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkCyan;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkGoldenrod;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkGray;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkGreen;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkKhaki;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkMagenta;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkOliveGreen;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkOrange;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkOrchid;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkRed;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkSalmon;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkSeaGreen;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkSlateBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkSlateGray;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkTurquoise;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DarkViolet;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DeepPink;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DeepSkyBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DimGray;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color DodgerBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Firebrick;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color FloralWhite;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color ForestGreen;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Fuchsia;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Gainsboro;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color GhostWhite;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Gold;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Goldenrod;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Gray;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Green;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color GreenYellow;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Honeydew;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color HotPink;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color IndianRed;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Indigo;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Ivory;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Khaki;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Lavender;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LavenderBlush;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LawnGreen;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LemonChiffon;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LightBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LightCoral;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LightCyan;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LightGoldenrodYellow;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LightGray;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LightGreen;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LightPink;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LightSalmon;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LightSeaGreen;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LightSkyBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LightSlateGray;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LightSteelBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LightYellow;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Lime;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color LimeGreen;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Linen;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Magenta;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Maroon;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color MediumAquamarine;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color MediumBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color MediumOrchid;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color MediumPurple;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color MediumSeaGreen;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color MediumSlateBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color MediumSpringGreen;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color MediumTurquoise;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color MediumVioletRed;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color MidnightBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color MintCream;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color MistyRose;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Moccasin;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color NavajoWhite;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Navy;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color OldLace;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Olive;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color OliveDrab;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Orange;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color OrangeRed;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Orchid;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color PaleGoldenrod;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color PaleGreen;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color PaleTurquoise;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color PaleVioletRed;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color PapayaWhip;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color PeachPuff;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Peru;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Pink;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Plum;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color PowderBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Purple;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Red;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color RosyBrown;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color RoyalBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color SaddleBrown;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Salmon;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color SandyBrown;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color SeaGreen;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color SeaShell;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Sienna;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Silver;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color SkyBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color SlateBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color SlateGray;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Snow;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color SpringGreen;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color SteelBlue;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Tan;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Teal;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Thistle;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Tomato;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Transparent;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Turquoise;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Violet;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Wheat;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color White;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color WhiteSmoke;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color Yellow;
	
	/// <summary>
	/// 미리 정의된 색상 값을 가져옵니다.
	/// </summary>	
	static Color YellowGreen;
};
#pragma pack(pop)

CORE_API Color operator +(float left, const Color& right);
CORE_API Color operator -(float left, const Color& right);
CORE_API Color operator *(float left, const Color& right);
CORE_API Color operator /(float left, const Color& right);

#include "Color.inl"