// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Object.h"

#include <vector>
#include <span>
#include <string>
#include <optional>
#include "IStringFormattable.h"

template<class T>
concept TIsStringConvertible = requires(const T& arg)
{
	{ arg.ToString() };
};

template<class T>
constexpr bool VIsStringConvertible = false;
template<TIsStringConvertible T>
constexpr bool VIsStringConvertible<T> = true;

template<class T>
constexpr bool VIsFormattableStringConvertible = false;
template<TIsFormattableStringConvertible T>
constexpr bool VIsFormattableStringConvertible<T> = true;

template<class T>
concept TIsOnlyStringConvertible = VIsStringConvertible<T> && !VIsFormattableStringConvertible<T>;

template<class TItem>
using StringIterator = TItem*;

/// <summary>
/// 수정 불가능한 문자열 개체를 표현합니다.
/// </summary>
SCLASS(SString) class CORE_API SString final : virtual public SObject
{
	SCLASS_BODY(SString)

public:
	/// <summary>
	/// 문자열의 각 문자를 반복하는 반복 개체입니다.
	/// </summary>
	using Iterator = StringIterator<wchar_t>;

	/// <summary>
	/// 문자열의 각 문자를 반복하는 반복 개체입니다.
	/// </summary>
	using ConstIterator = StringIterator<const wchar_t>;

private:
	static wchar_t EmptyBuffer[1];

	const wchar_t* text_buffer;
	size_t len;
	bool bDynamicBuffer : 1;
	mutable std::optional<size_t> hash_cache;

public:
	/// <summary>
	/// 빈 문자열 개체를 초기화합니다.
	/// </summary>
	SString();
	~SString() override;

	/// <summary>
	/// 개체를 가져옵니다.
	/// </summary>
	SString* ToString() const override;

	/// <summary>
	/// 대상 개체가 문자열 개체일 경우 대상 문자열 개체와 같은지 비교합니다.
	/// </summary>
	/// <param name="right"> 대상 개체를 전달합니다. </param>
	/// <returns> 비교 결과가 반환됩니다. </returns>
	bool Equals(SObject* right) const override;

	/// <summary>
	/// 문자열 전체의 해시 코드를 가져옵니다.
	/// </summary>
	/// <returns> 해시 코드가 반환됩니다. </returns>
	size_t GetHashCode() const override;

	/// <summary>
	/// 표준 문자열로 개체를 초기화합니다.
	/// </summary>
	/// <param name="text"> 표준 문자열을 전달합니다. </param>
	SString(const char* text);

	/// <summary>
	/// 표준 문자열로 개체를 초기화합니다.
	/// </summary>
	/// <param name="text"> 표준 문자열을 전달합니다. </param>
	SString(const wchar_t* text);

	/// <summary>
	/// 표준 문자열로 개체를 초기화합니다.
	/// </summary>
	/// <param name="text"> 표준 문자열을 전달합니다. </param>
	/// <param name="len"> 표준 문자열의 길이를 전달합니다. </param>
	SString(const char* text, size_t len);

	/// <summary>
	/// 표준 문자열로 개체를 초기화합니다.
	/// </summary>
	/// <param name="text"> 표준 문자열을 전달합니다. </param>
	/// <param name="len"> 표준 문자열의 길이를 전달합니다. </param>
	SString(const wchar_t* text, size_t len);

	/// <summary>
	/// 표준 문자열로 개체를 초기화합니다.
	/// </summary>
	/// <param name="text"> 표준 문자열을 전달합니다. </param>
	SString(const std::string& text);

	/// <summary>
	/// 표준 문자열로 개체를 초기화합니다.
	/// </summary>
	/// <param name="text"> 표준 문자열을 전달합니다. </param>
	SString(const std::wstring& text);

	/// <summary>
	/// 표준 문자열로 개체를 초기화합니다.
	/// </summary>
	/// <param name="text"> 표준 문자열을 전달합니다. </param>
	SString(std::string_view text);

	/// <summary>
	/// 표준 문자열로 개체를 초기화합니다.
	/// </summary>
	/// <param name="text"> 표준 문자열을 전달합니다. </param>
	SString(std::wstring_view text);

	/// <summary>
	/// 표준 문자열로 개체를 초기화합니다.
	/// </summary>
	/// <param name="begin"> 표준 문자열의 반복기 시작 위치를 전달합니다. </param>
	/// <param name="end"> 표준 문자열의 반복기 종료 위치를 전달합니다. </param>
	template<TIsIterator<char> TIterator>
	SString(TIterator begin, TIterator end);

	/// <summary>
	/// 표준 문자열로 개체를 초기화합니다.
	/// </summary>
	/// <param name="begin"> 표준 문자열의 반복기 시작 위치를 전달합니다. </param>
	/// <param name="end"> 표준 문자열의 반복기 종료 위치를 전달합니다. </param>
	template<TIsIterator<wchar_t> TIterator>
	SString(TIterator begin, TIterator end);

	/// <summary>
	/// 부분 문자열을 가져옵니다.
	/// </summary>
	/// <param name="startIndex"> 부분 문자열의 시작 위치를 전달합니다. </param>
	/// <param name="length"> 부분 문자열의 길이를 가져옵니다. </param>
	/// <returns> 부분 문자열 개체가 반환됩니다. </returns>
	SString* Substring(size_t startIndex, std::optional<size_t> length = {}) const;

	/// <summary>
	/// 문자열에서 특정 값을 찾습니다.
	/// </summary>
	/// <param name="value"> 찾을 값을 전달합니다. </param>
	/// <param name="startIndex"> 찾기 시작할 위치를 전달합니다. </param>
	/// <param name="bIgnoreCase"> 대소문자 구분을 무시합니다. </param>
	/// <returns> 찾았을 경우 위치의 인덱스가, 그렇지 않을 경우 <see cref="std::nullopt"/>가 반환됩니다. </returns>
	std::optional<size_t> IndexOf(SString* value, size_t startIndex = 0, bool bIgnoreCase = false) const;

	/// <summary>
	/// 문자열에서 특정 값을 찾습니다.
	/// </summary>
	/// <param name="value"> 찾을 값을 전달합니다. </param>
	/// <param name="startIndex"> 찾기 시작할 위치를 전달합니다. </param>
	/// <param name="bIgnoreCase"> 대소문자 구분을 무시합니다. </param>
	/// <returns> 찾았을 경우 위치의 인덱스가, 그렇지 않을 경우 <see cref="std::nullopt"/>가 반환됩니다. </returns>
	std::optional<size_t> IndexOf(wchar_t value, size_t startIndex = 0, bool bIgnoreCase = false) const;

	/// <summary>
	/// 문자열에서 특정 값 목록 중 일치하는 아무 것을 찾습니다.
	/// </summary>
	/// <param name="value_sequence"> 찾을 값 목록을 전달합니다. </param>
	/// <param name="length"> 찾을 값 목록의 길이를 전달합니다. </param>
	/// <param name="startIndex"> 찾기 시작할 위치를 전달합니다. </param>
	/// <param name="bIgnoreCase"> 대소문자 구분을 무시합니다. </param>
	/// <returns> 찾았을 경우 위치의 인덱스가, 그렇지 않을 경우 <see cref="std::nullopt"/>가 반환됩니다. </returns>
	std::optional<size_t> IndexOfAny(const wchar_t* value_sequence, size_t length, size_t startIndex = 0, bool bIgnoreCase = false) const;

	/// <summary>
	/// 멀티바이트 형식 문자열로 변경합니다.
	/// </summary>
	/// <returns> 표준 문자열 개체가 반환됩니다. </returns>
	std::string AsMultiByte() const;

	/// <summary>
	/// 네이티브 문자열 포인터를 가져옵니다.
	/// </summary>
	/// <returns> 문자열 포인터가 반환됩니다. </returns>
	const wchar_t* C_Str() const;

	/// <summary>
	/// 문자열 길이를 가져옵니다.
	/// </summary>
	/// <returns> 길이가 반환됩니다. </returns>
	size_t GetLength() const;

	/// <summary>
	/// 문자열을 지정자 단위로 분할합니다.
	/// </summary>
	/// <param name="separator"> 분할 지정자를 전달합니다. </param>
	/// <param name="bRemoveEmptyEntries"> 빈 아이템을 제거합니다. </param>
	/// <param name="bTrimEntries"> 아이템의 주변 공백을 제거합니다. </param>
	/// <returns> 문자열 목록이 반환됩니다. </returns>
	std::vector<SString*> Split(wchar_t separator, bool bRemoveEmptyEntries = false, bool bTrimEntries = false);

	/// <summary>
	/// 지정 서식을 사용하여 텍스트를 만듭니다.
	/// </summary>
	/// <typeparam name="...TArgs"> 매개변수 형식 목록입니다. </typeparam>
	/// <param name="format"> 서식 텍스트를 전달합니다. </param>
	/// <param name="...args"> 서식 매개변수를 전달합니다. </param>
	/// <returns> 생성된 텍스트가 반환됩니다. </returns>
	template<class... TArgs>
	static SString* Format(SString* format, TArgs&&... args);

	/// <summary>
	/// 지정 서식을 사용하여 텍스트를 만듭니다.
	/// </summary>
	/// <typeparam name="...TArgs"> 매개변수 형식 목록입니다. </typeparam>
	/// <param name="format"> 서식 텍스트를 전달합니다. </param>
	/// <returns> 생성된 텍스트가 반환됩니다. </returns>
	static SString* Format(SString* format);

	/// <summary>
	/// 문자열 사이를 지정자로 연결합니다.
	/// </summary>
	/// <typeparam name="...TArgs"> 매개변수 형식 목록입니다. </typeparam>
	/// <param name="separator"> 지정자를 전달합니다. </param>
	/// <param name="arg1"> 매개변수 목록을 전달합니다. </param>
	/// <param name="arg2"> 매개변수 목록을 전달합니다. </param>
	/// <param name="...values"> 매개변수 목록을 전달합니다. </param>
	/// <returns> 생성된 텍스트가 반환됩니다. </returns>
	template<class... TArgs>
	static SString* Join(SString* separator, SString* arg1, SString* arg2, TArgs&&... values);

	/// <summary>
	/// 문자열 사이를 지정자로 연결합니다.
	/// </summary>
	/// <typeparam name="...TArgs"> 매개변수 형식 목록입니다. </typeparam>
	/// <param name="separator"> 지정자를 전달합니다. </param>
	/// <param name="values"> 매개변수 목록을 전달합니다. </param>
	/// <returns> 생성된 텍스트가 반환됩니다. </returns>
	template<class T, size_t N> requires TIsStringConvertible<T> || TIsStringConstructible<T>
	static SString* Join(SString* separator, const T(&values)[N]);

	/// <summary>
	/// 문자열 사이를 지정자로 연결합니다.
	/// </summary>
	/// <param name="separator"> 지정자를 전달합니다. </param>
	/// <param name="values"> 매개변수 목록을 전달합니다. </param>
	/// <returns> 생성된 텍스트가 반환됩니다. </returns>
	static SString* Join(SString* separator, const std::span<SString*>& values);

	/// <summary>
	/// 문자열을 연결합니다.
	/// </summary>
	/// <typeparam name="...TArgs"> 매개변수 형식 목록입니다. </typeparam>
	/// <param name="arg1"> 매개변수 목록을 전달합니다. </param>
	/// <param name="arg2"> 매개변수 목록을 전달합니다. </param>
	/// <param name="...values"> 매개변수 목록을 전달합니다. </param>
	/// <returns> 생성된 텍스트가 반환됩니다. </returns>
	template<class... TArgs>
	static SString* Concat(SString* arg1, SString* arg2, TArgs&&... values);

	/// <summary>
	/// 문자열을 연결합니다.
	/// </summary>
	/// <typeparam name="...TArgs"> 매개변수 형식 목록입니다. </typeparam>
	/// <param name="separator"> 지정자를 전달합니다. </param>
	/// <param name="values"> 매개변수 목록을 전달합니다. </param>
	/// <returns> 생성된 텍스트가 반환됩니다. </returns>
	template<class T, size_t N> requires TIsStringConvertible<T> || TIsStringConstructible<T>
	static SString* Concat(const T(&values)[N]);

	/// <summary>
	/// 문자열을 연결합니다.
	/// </summary>
	/// <param name="separator"> 지정자를 전달합니다. </param>
	/// <param name="values"> 매개변수 목록을 전달합니다. </param>
	/// <returns> 생성된 텍스트가 반환됩니다. </returns>
	static SString* Concat(const std::span<SString*>& values);

	/// <summary>
	/// 문자열 개체가 널이거나 비어있는지 검사합니다.
	/// </summary>
	/// <param name="value"> 문자열 개체를 전달합니다. </param>
	/// <returns> 검사 결과를 반환합니다. </returns>
	static bool IsNullOrEmpty(SString* value);

	/// <summary>
	/// 문자열 개체가 널이거나 공백으로 이루어져있는지 검사합니다.
	/// </summary>
	/// <param name="value"> 문자열 개체를 전달합니다. </param>
	/// <returns> 검사 결과를 반환합니다. </returns>
	static bool IsNullOrWhiteSpace(SString* value);

private:
	static SString* FormatHelper(SString* format, const std::span<SObject*>& unpackedArgs);
	wchar_t* MultiByteToWideChar(const char* multibyte, size_t* len);
	wchar_t* CopyAllocate(const wchar_t* text, size_t len);

	template<TIsChar TChar>
	static TChar* AllocCharBuffer(size_t len);
	template<TIsChar TChar>
	static void Free(TChar* charBuffer);
	static void* AllocInternal(size_t sizeInBytes);
	static void FreeInternal(void* internalPointer);

	void Assign(const char* text, size_t len);
	void Assign(const wchar_t* text, size_t len);

	template<TIsChar TChar>
	inline static size_t Strlen(const TChar* text);
	template<TIsChar TChar>
	inline static bool Strcmp(const TChar* left, const TChar* right);
	static size_t SizeAsBoundary(size_t len);

	template<TIsRefCore T>
	static SObject* GetString(T* packedArg);
	template<TIsPrimitive T>
	static SObject* GetString(T packedArg);
	template<TIsChar T>
	static SObject* GetString(const T* packedArg);
	template<TIsOnlyStringConvertible T>
	static SObject* GetString(const T& packedArg);
	template<TIsFormattableStringConvertible T>
	static SObject* GetString(const T& packedArg);
	template<TIsBaseOf<SObject> T>
	static SObject* GetString(const T* packedArg);

	template<class T, class... TArgs>
	static void FormatUnpack(std::vector<SObject*>& container, size_t index, T&& arg, TArgs&&... args);
};

inline SString* operator "" _s(const char* text, size_t length)
{
	return new SString(text, length);
}

#include "String.inl"