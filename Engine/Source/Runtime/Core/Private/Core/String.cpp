// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "Core/String.h"

#undef interface
#include <Windows.h>
#include "Exception/ArgumentNullException.h"
#include "Exception/IndexOutOfRangeException.h"
#include "Exception/FormatException.h"
#include "Exception/ArgumentException.h"
#include "Core/IStringFormattable.h"

using namespace std;

wchar_t SString::EmptyBuffer[1] = { 0 };

#define ThrowIfNull(exp) if ((exp) == nullptr) { throw new SArgumentNullException("("_s #exp ## _s ") == nullptr"_s); }
#define ThrowArg(exp) if (exp) { throw new SArgumentException(#exp ## _s); }

namespace
{
    inline bool IsLatin1(wchar_t ch)
    {
        return ch <= '\x00ff';
    }

    inline bool IsWhiteSpaceLatin1(wchar_t ch)
    {
        return (ch == ' ') || (ch >= '\x0009' && ch <= '\x000d') || ch == '\x00a0' || ch == '\x0085';
    }

    inline bool IsWhiteSpace(wchar_t ch)
    {
        if (IsLatin1(ch))
        {
            return IsWhiteSpaceLatin1(ch);
        }
        return false;
    }
}

SString::SString() : Super()
	, text_buffer(nullptr)
	, len(0)
	, bDynamicBuffer(false)
{
	text_buffer = EmptyBuffer;
}

SString::~SString()
{
	if (text_buffer != nullptr && bDynamicBuffer)
	{
		delete[] text_buffer;
		text_buffer = nullptr;
	}
}

SString* SString::ToString() const
{
	return const_cast<SString*>(this);
}

bool SString::Equals(SObject* right) const
{
	if (SString* ptr = Cast<SString>(right); ptr != nullptr)
	{
		return (*this).operator ==(ptr);
	}
	else
	{
		return Super::Equals(right);
	}
}

size_t SString::GetHashCode() const
{
    if (!hash_cache.has_value())
    {
        size_t hash1 = 5381;
        size_t hash2 = hash1;

        size_t	        c;
        const wchar_t* s = text_buffer;

        while ((c = s[0]) != 0) {
            hash1 = ((hash1 << 5) + hash1) ^ c;
            c = s[1];
            if (c == 0)
                break;
            hash2 = ((hash2 << 5) + hash2) ^ c;
            s += 2;
        }

        hash_cache = hash1 + (hash2 * 1566083941);
    }

    return hash_cache.value();
}

SString::SString(const char* text) : This(text, Strlen(text))
{

}

SString::SString(const wchar_t* text) : This(text, Strlen(text))
{

}

SString::SString(const char* text, size_t len) : This()
{
    Assign(text, len);
}

SString::SString(const wchar_t* text, size_t len) : This()
{
    if (text == EmptyBuffer)
    {
        text_buffer = text;
    }
    else
    {
        Assign(text, len);
    }
}

SString::SString(const string& text) : This(text.c_str(), text.length())
{

}

SString::SString(const wstring& text) : This(text.c_str(), text.length())
{

}

SString::SString(string_view text) : This(text.data(), text.length())
{

}

SString::SString(wstring_view text) : This(text.data(), text.length())
{

}

SString* SString::Substring(size_t startIndex, optional<size_t> length) const
{
    if (!length.has_value())
    {
        length = len - startIndex;
    }

    return new SString(text_buffer + startIndex, length.value());
}

optional<size_t> SString::IndexOf(SString* value, size_t startIndex, bool bIgnoreCase) const
{
    SString* r = ""_s ""_s ""_s;
    ThrowIfNull(value);
    ThrowArg(value->GetLength() == 0);

    for (size_t i = startIndex; i < len; ++i)
    {
        optional<size_t> find = IndexOf(value->text_buffer[0], i, bIgnoreCase);
        // Could'n find any chars.
        if (!find.has_value())
        {
            return {};
        }

        // Find chars but lack of length.
        size_t rem = len - i;
        if (rem < value->GetLength())
        {
            return {};
        }
        rem = value->GetLength();

        const size_t seekpos = find.value();
        if (bIgnoreCase)
        {
            bool bSucceeded = true;
            for (size_t j = 0; j < rem; ++j)
            {
                if (tolower(text_buffer[seekpos + j]) != tolower(value->text_buffer[j]))
                {
                    bSucceeded = false;
                    break;
                }
            }

            if (bSucceeded)
            {
                return seekpos;
            }
        }
        else
        {
            if (memcmp(text_buffer + seekpos, value->C_Str(), sizeof(wchar_t) * rem) == 0)
            {
                return seekpos;
            }
        }

        i = seekpos + 1;
    }

    return {};
}

optional<size_t> SString::IndexOf(wchar_t value, size_t startIndex, bool bIgnoreCase) const
{
    ThrowArg(startIndex >= len);

    for (size_t i = startIndex; i < len; ++i)
    {
        bool bCompare = false;

        if (bIgnoreCase)
        {
            bCompare = tolower(text_buffer[i]) == tolower(value);
        }
        else
        {
            bCompare = text_buffer[i] == value;
        }

        if (bCompare)
        {
            return i;
        }
    }

    return {};
}

optional<size_t> SString::IndexOfAny(const wchar_t* value_sequence, size_t length, size_t startIndex, bool bIgnoreCase) const
{
    ThrowArg(startIndex >= len);
    ThrowIfNull(value_sequence);
    ThrowArg(length == 0);

    auto Compare = [&](size_t index, wchar_t value)
    {
        if (bIgnoreCase)
        {
            return tolower(text_buffer[index]) == tolower(value);
        }
        else
        {
            return text_buffer[index] == value;
        }
    };

    for (size_t i = startIndex; i < len; ++i)
    {
        for (size_t j = 0; j < length; ++j)
        {
            if (Compare(i, value_sequence[j]))
            {
                return i;
            }
        }
    }

    return {};
}

string SString::AsMultiByte() const
{
    string buf;

    int length = ::WideCharToMultiByte(CP_ACP, 0, text_buffer, (int)len, nullptr, 0, nullptr, FALSE);
    buf.resize(length, ' ');
    ::WideCharToMultiByte(CP_ACP, 0, text_buffer, (int)len, buf.data(), length, nullptr, FALSE);

    return buf;
}

const wchar_t* SString::C_Str() const
{
	return text_buffer;
}

size_t SString::GetLength() const
{
	return len;
}

vector<SString*> SString::Split(wchar_t separator, bool bRemoveEmptyEntries, bool bTrimEntries)
{
    vector<SString*> entries;

    auto AddEntry = [&](size_t seekpos, size_t curr)
    {
        size_t begin = seekpos;
        size_t end = curr;

        if (bTrimEntries)
        {
            // 문자열의 양쪽 끝 공백을 제거합니다.
            for (size_t i = begin; i < end; ++i)
            {
                const wchar_t wch = text_buffer[i];
                if (isspace(wch) != 0)
                {
                    ++begin;
                }
                else
                {
                    break;
                }
            }

            for (size_t i = end - 1; i >= begin; --i)
            {
                const wchar_t wch = text_buffer[i];
                if (isspace(wch) != 0)
                {
                    --end;
                }
                else
                {
                    break;
                }
            }
        }

        // 길이가 0이면 빈 개체입니다.
        size_t length = end - begin;
        if (length == 0)
        {
            return;
        }

        entries.emplace_back(new SString(text_buffer + begin, length));
    };

    size_t seekpos = 0;
    for (; seekpos < len;)
    {
        optional<size_t> curr = IndexOf(separator, seekpos);
        if (!curr.has_value())
        {
            break;
        }

        AddEntry(seekpos, curr.value());
        seekpos = curr.value() + 1;
    }

    // 마지막 남은 부분도 넣습니다.
    if (seekpos != len)
    {
        AddEntry(seekpos, len);
    }

    return entries;
}

SString* SString::Format(SString* format)
{
    std::vector<int> r;
    std::span<int> g = r;
    return format;
}

SString* SString::Join(SString* separator, const span<SString*>& values)
{
    if (values.empty())
    {
        return new SString(EmptyBuffer);
    }

    if (values.size() <= 1)
    {
        return values[0];
    }

    size_t total_length = 0;
    for (size_t i = 0; i < values.size(); ++i)
    {
        total_length += values[i]->GetLength();
    }

    size_t sep_length = separator->GetLength();
    total_length += sep_length * (values.size() - 1);

    wchar_t* buffer = new wchar_t[SizeAsBoundary(total_length + 1)];
    size_t   seekpos = 0;

    struct __Finally
    {
        wchar_t* buf;

        __Finally(wchar_t* buf) : buf(buf)
        {

        }

        ~__Finally()
        {
            if (buf != nullptr)
            {
                delete[] buf;
                buf = nullptr;
            }
        }

        void Detach()
        {
            buf = nullptr;
        }
    }
    finally(buffer);

    for (size_t i = 0; i < values.size(); ++i)
    {
        size_t length = values[i]->GetLength();
        memcpy(buffer + seekpos, values[i]->C_Str(), sizeof(wchar_t) * length);
        seekpos += length;

        if (seekpos < total_length)
        {
            memcpy(buffer + seekpos, separator->C_Str(), sizeof(wchar_t*) * sep_length);
            seekpos += sep_length;
        }
    }

    buffer[total_length] = 0;

    auto result = new SString();
    result->text_buffer = buffer;
    result->len = total_length;
    result->bDynamicBuffer = true;
    finally.Detach();

    return move(result);
}

SString* SString::Concat(const span<SString*>& values)
{
    if (values.empty())
    {
        return new SString(EmptyBuffer);
    }

    if (values.size() <= 1)
    {
        return values[0];
    }

    size_t total_length = 0;
    for (size_t i = 0; i < values.size(); ++i)
    {
        total_length += values[i]->GetLength();
    }

    wchar_t* buffer = new wchar_t[SizeAsBoundary(total_length + 1)];
    size_t   seekpos = 0;

    struct __Finally
    {
        wchar_t* buf;

        __Finally(wchar_t* buf) : buf(buf)
        {

        }

        ~__Finally()
        {
            if (buf != nullptr)
            {
                delete[] buf;
                buf = nullptr;
            }
        }

        void Detach()
        {
            buf = nullptr;
        }
    }
    finally(buffer);

    for (size_t i = 0; i < values.size(); ++i)
    {
        size_t length = values[i]->GetLength();
        memcpy(buffer + seekpos, values[i]->C_Str(), sizeof(wchar_t) * length);
        seekpos += length;
    }

    buffer[total_length] = 0;

    auto result = new SString();
    result->text_buffer = buffer;
    result->len = total_length;
    result->bDynamicBuffer = true;
    finally.Detach();

    return move(result);
}

bool SString::IsNullOrEmpty(SString* value)
{
    return value == nullptr || value->GetLength() == 0;
}

bool SString::IsNullOrWhiteSpace(SString* value)
{
    if (value == nullptr)
    {
        return true;
    }

    for (size_t i = 0; i < value->GetLength(); i++)
    {
        if (!IsWhiteSpace(value->text_buffer[i]))
        {
            return false;
        }
    }

    return true;
}

SString* SString::FormatHelper(SString* format, const span<SObject*>& unpackedArgs)
{
    ThrowIfNull(format);
 
    size_t pos = 0;
    size_t len = format->GetLength();
    wchar_t ch = L'\x0';

    std::wstringstream wss;
 
    while (true)
    {
        size_t p = pos;
        size_t i = pos;

        while (pos < len)
        {
            ch = format->text_buffer[pos];
 
            pos++;
            if (ch == L'}')
            {
                if (pos < len && format->text_buffer[pos] == L'}')
                {
                    pos++;
                }
                else
                {
                    throw SFormatException();
                }
            }
 
            if (ch == L'{')
            {
                if (pos < len && format->text_buffer[pos] == L'{')
                {
                    pos++;
                }
                else
                {
                    pos--;
                    break;
                }
            }
 
            wss << ch;
        }
 
        if (pos == len)
        {
            break;
        }

        pos++;
        if (pos == len || (ch = format->text_buffer[pos]) < L'0' || ch > L'9')
        {
            throw SFormatException();
        }

        size_t index = 0;
        do
        {
            index = index * 10 + ch - L'0';
            pos++;
            if (pos == len)
            {
                throw SFormatException();
            }

            ch = format->text_buffer[pos];
        } while (ch >= L'0' && ch <= L'9' && index < 1000000);

        if (index >= unpackedArgs.size())
        {
            throw new SFormatException("Format index is out of range."_s);
        }

        while (pos < len && (ch = format->text_buffer[pos]) == L' ')
        {
            pos++;
        }

        bool leftJustify = false;
        int width = 0;
        if (ch == L',')
        {
            pos++;
            while (pos < len && format->text_buffer[pos] == L' ')
            {
                pos++;
            }
 
            if (pos == len)
            {
                throw SFormatException();
            }

            ch = format->text_buffer[pos];
            if (ch == L'-')
            {
                leftJustify = true;
                pos++;
                if (pos == len)
                {
                    throw SFormatException();
                }
                ch = format->text_buffer[pos];
            }

            if (ch < L'0' || ch > L'9')
            {
                throw SFormatException();
            }

            do
            {
                width = width * 10 + ch - L'0';
                pos++;
                if (pos == len)
                {
                    throw SFormatException();
                }
                ch = format->text_buffer[pos];
            } while (ch >= L'0' && ch <= L'9' && width < 1000000);
        }
 
        while (pos < len && (ch = format->text_buffer[pos]) == L' ')
        {
            pos++;
        }

        SObject* arg = unpackedArgs[index];
        std::wostringstream fmt;
        if (ch == L':')
        {
            pos++;
            p = pos;
            i = pos;
            while (true)
            {
                if (pos == len)
                {
                    throw SFormatException();
                }

                ch = format->text_buffer[pos];
                pos++;
                if (ch == L'{')
                {
                    if (pos < len && format->text_buffer[pos] == L'{')
                    {
                        pos++;
                    }
                    else
                    {
                        throw SFormatException();
                    }
                }
                else if (ch == L'}')
                {
                    if (pos < len && format->text_buffer[pos] == L'}')
                    {
                        pos++;
                    }
                    else
                    {
                        pos--;
                        break;
                    }
                }
 
                fmt << ch;
            }
        }

        if (ch != L'}')
        {
            throw SFormatException();
        }

        pos++;
        wstring s;
        wstring fmtstr = fmt.str();

        if (arg != nullptr)
        {
            if (IStringFormattable* formattable = nullptr; fmtstr.length() != 0 && (formattable = dynamic_cast<IStringFormattable*>(arg)) != nullptr)
            {
                s = formattable->ToString(new SString(fmtstr.c_str()))->C_Str();
            }
            else
            {
                s = arg->ToString()->C_Str();
            }
        }

        ssize_t pad = width - s.length();
        if (!leftJustify && pad > 0)
        {
            size_t repeat = (size_t)pad;
            while (repeat-- != 0)
            {
                wss.put(L' ');
            }
        }

        wss << s;

        if (leftJustify && pad > 0)
        {
            size_t repeat = pad;
            while (repeat-- != 0)
            {
                wss.put(L' ');
            }
        }
    }

    return new SString(wss.str().c_str());
}

wchar_t* SString::MultiByteToWideChar(const char* multibyte, size_t* len)
{
	int length = ::MultiByteToWideChar(CP_UTF8, 0, multibyte, (int)*len, nullptr, 0);
    auto* buffer = AllocCharBuffer<wchar_t>(*len + 1);
	::MultiByteToWideChar(CP_UTF8, 0, multibyte, (int)*len, buffer, length);
	*len = length;
	return buffer;
}

wchar_t* SString::CopyAllocate(const wchar_t* text, size_t len)
{
    auto* buffer = AllocCharBuffer<wchar_t>(len + 1);
	memcpy(buffer, text, sizeof(wchar_t) * len);
	return buffer;
}

void* SString::AllocInternal(size_t sizeInBytes)
{
    return new int8[sizeInBytes]{ };
}

void SString::FreeInternal(void* internalPointer)
{
    delete[] reinterpret_cast<int8*&>(internalPointer);
}

void SString::Assign(const char* text, size_t len)
{
    text_buffer = MultiByteToWideChar(text, &len);
    this->len = len;
    bDynamicBuffer = true;
}

void SString::Assign(const wchar_t* text, size_t len)
{
    text_buffer = CopyAllocate(text, len);
    this->len = len;
    bDynamicBuffer = true;
}

size_t SString::SizeAsBoundary(size_t len)
{
	size_t rem = len % 4;
	if (rem != 0)
	{
		len += 4 - rem;
	}
	return len;
}