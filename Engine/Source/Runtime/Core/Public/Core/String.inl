// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include <sstream>
#include <iomanip>

template<TIsIterator<char> TIterator>
inline SString::SString(TIterator begin, TIterator end)
{
	size_t length = end - begin;
	auto buffer = HeapStorage(AllocCharBuffer<char>(length + 1));
	auto seek = buffer.ptr;
	for (auto it = begin; it != end; ++it)
	{
		*seek++ = *it;
	}

	Assign(buffer.ptr, length);
}

template<TIsIterator<wchar_t> TIterator>
inline SString::SString(TIterator begin, TIterator end)
{
	size_t length = end - begin;
	auto buffer = HeapStorage(AllocCharBuffer<wchar_t>(length + 1));
	auto seek = buffer.ptr;
	for (auto it = begin; it != end; ++it)
	{
		*seek++ = *it;
	}

	text_buffer = buffer.ptr;
	buffer.ptr = nullptr;
	len = length;
	bDynamicBuffer = true;
}

template<class... TArgs>
inline SString* SString::Format(SString* format, TArgs&&... args)
{
	std::vector<SObject*> unpacked(sizeof...(TArgs));
	if constexpr (sizeof...(TArgs) != 0)
	{
		FormatUnpack(unpacked, 0, std::forward<TArgs>(args)...);
	}
	return FormatHelper(format, unpacked);
}

template<class T, size_t N> requires TIsStringConvertible<T> || TIsStringConstructible<T>
inline SString* SString::Join(SString* separator, const T(&values)[N])
{
	std::vector<T> values_vec(values, values + N);
	return Join(separator, values_vec);
}

template<class... TArgs>
inline SString* SString::Join(SString* separator, SString* arg1, SString* arg2, TArgs&&... values)
{
	std::vector<SString*> values_vec({ arg1, arg2, values... });
	return Join(separator, values_vec);
}

template<class T, size_t N> requires TIsStringConvertible<T> || TIsStringConstructible<T>
inline SString* SString::Concat(const T(&values)[N])
{
	std::vector<T> values_vec(values, values + N);
	return Concat(values_vec);
}

template<class... TArgs>
inline SString* SString::Concat(SString* arg1, SString* arg2, TArgs&&... values)
{
	std::vector<SString*> values_vec({ arg1, arg2, values... });
	return Concat(values_vec);
}

template<TIsChar TChar>
inline TChar* SString::AllocCharBuffer(size_t len)
{
	len = SizeAsBoundary(len + 1);
	TChar* buffer = (TChar*)AllocInternal(sizeof(TChar) * len);
	memset(buffer, 0, (len) * sizeof(TChar));
	return buffer;
}

template<TIsChar TChar>
inline void SString::Free(TChar* charBuffer)
{
	FreeInternal(charBuffer);
}

template<TIsChar TChar>
inline size_t SString::Strlen(const TChar* text)
{
	size_t length = 0;
	for (auto item = text; *item != 0; ++item)
	{
		length += 1;
	}
	return length;
}

template<TIsChar TChar>
inline bool SString::Strcmp(const TChar* left, const TChar* right)
{
	while (true)
	{
		if (*left == 0 || *right == 0)
		{
			return *left == *right;
		}

		else if (*left != *right)
		{
			return false;
		}

		++left;
		++right;
	}

	return false;
}

template<TIsRefCore T>
SObject* SString::GetString(T* packedArg)
{
	return packedArg;
}

template<TIsPrimitive T>
SObject* SString::GetString(T packedArg)
{
	class SPrimitiveString : virtual public SObject, virtual public IStringFormattable
	{
		T value;

	public:
		SPrimitiveString(T value) : value(value)
		{

		}

		~SPrimitiveString() override
		{

		}

		SString* ToString() const override
		{
			std::wstringstream woss;
			woss << value;
			return new SString(woss.str());
		}

		virtual SString* ToString(SString* formatText) const
		{
			std::wstringstream woss;
			const wchar_t* c_str = formatText->C_Str();
			if (c_str[0] == L'x')
			{
				woss << std::hex;
			}
			else if (c_str[0] == L'X')
			{
				woss << std::uppercase << std::hex;
			}

			if (formatText->GetLength() >= 2)
			{
				size_t pad = 0;
				std::wistringstream wiss;
				wiss.str(c_str + 1);
				wiss >> pad;

				if (pad != 0)
				{
					woss << std::setfill(L'0') << std::setw(pad);
				}
			}

			woss << value;
			return new SString(woss.str());
		}
	};

	return new SPrimitiveString(packedArg);
}

template<TIsChar T>
SObject* SString::GetString(const T* packedArg)
{
	return new SString(packedArg);
}

template<TIsOnlyStringConvertible T>
SObject* SString::GetString(const T& packedArg)
{
	return packedArg.ToString();
}

template<TIsFormattableStringConvertible T>
SObject* SString::GetString(const T& packedArg)
{
	class SFormattableString : virtual public SObject, virtual public IStringFormattable
	{
		const T& value;

	public:
		SFormattableString(const T& value) : value(value)
		{

		}

		~SFormattableString() override
		{

		}

		SString* ToString() const override
		{
			return value.ToString();
		}

		virtual SString* ToString(SString* formatText) const
		{
			return value.ToString(formatText);
		}
	};

	return new SFormattableString(packedArg);
}

template<TIsBaseOf<SObject> T>
SObject* SString::GetString(const T* packedArg)
{
	return packedArg;
}

template<class T, class... TArgs>
static void SString::FormatUnpack(std::vector<SObject*>& container, size_t index, T&& arg, TArgs&&... args)
{
	container[index++] = GetString(std::forward<T>(arg));

	if constexpr (sizeof...(TArgs) != 0)
	{
		FormatUnpack(container, index, std::forward<TArgs>(args)...);
	}
}