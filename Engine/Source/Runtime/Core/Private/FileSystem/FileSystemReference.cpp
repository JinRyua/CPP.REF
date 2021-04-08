// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "FileSystem/FileSystemReference.h"
SCLASS_BODY_IMPL(SFileSystemReference);

#include <sstream>
#include "Core/String.h"
#include "Exception/ArgumentException.h"
#include "Exception/InvalidOperationException.h"

using namespace std;
using namespace std::filesystem;

SFileSystemReference::SFileSystemReference() : Super()
{
	throw new SInvalidOperationException("표준 생성자는 지원하지 않습니다."_s);
}

SFileSystemReference::SFileSystemReference(SString* inPath) : Super()
{
	myPath = GetFullPath(inPath);
}

SFileSystemReference::~SFileSystemReference()
{

}

SString* SFileSystemReference::GetFullPath() const
{
	return myPath;
}

SString* SFileSystemReference::GetFullPath(SString* path)
{
	SString* currentDirectory = GetCurrentDirectory();
	return Combine(currentDirectory, path);
}

SString* SFileSystemReference::GetCurrentDirectory()
{
	return new SString(current_path().c_str());
}

SString* SFileSystemReference::Combine(SString* path1, SString* path2)
{
	path1 = TrimDirectorySeparator(path1);
	path2 = TrimDirectorySeparator(path2);

	return SString::Join("\\"_s, path1, path2);
}

bool SFileSystemReference::IsRootBased(SString* path)
{
	// C:\\ 등, 드라이브 문자가 포함된 경로의 최소 길이는 3글자입니다.
	if (path->GetLength() < 3)
	{
		return false;
	}

	const wchar_t* c_str = path->C_Str();

	if (!IsDriveLetter(c_str[0]))
	{
		return false;
	}

	if (c_str[1] != L':')
	{
		return false;
	}

	return !IsDirectorySeparator(c_str[2]);
}

SString* SFileSystemReference::NormalizePath(SString* path)
{
	path = NormalizePathDirectorySeparator(path);
	path = NormalizeRelativePath(path);
	return path;
}

SString* SFileSystemReference::NormalizePathDirectorySeparator(SString* path)
{
	// \를 /로 바꿉니다.
	wstringstream wss;

	size_t seekpos = 0;
	for (; seekpos < path->GetLength();)
	{
		optional<size_t> indexOf = path->IndexOf(L'/', seekpos);
		if (indexOf.has_value())
		{
			wss << wstring_view(path->C_Str() + seekpos, indexOf.value() - seekpos) << L'\\';
			seekpos = indexOf.value() + 1;
		}

		else
		{
			// 이 경우 이 문자열에는 \가 존재하지 않습니다.
			if (seekpos == 0)
			{
				return path;
			}
			else
			{
				break;
			}
		}
	}

	size_t remain = path->GetLength() - seekpos;
	if (remain != 0)
	{
		wss << wstring_view(path->C_Str() + seekpos, remain);
	}

	return new SString(wss.str());
}

SString* SFileSystemReference::NormalizeRelativePath(SString* path)
{
	// 이 경로에는 상위 디렉토리로 이동이 포함되어 있지 않습니다.
	if (!path->IndexOf(".."_s).has_value())
	{
		return path;
	}

	// 이 경로는 깊이가 1입니다.
	if (!path->IndexOf(DirectorySeparatorChar).has_value())
	{
		return path;
	}

	vector<SString*> splits = path->Split(DirectorySeparatorChar, true, true);

	// 경로에 \..\ 형식만 포함되어 있습니다.
	if (splits.size() == 1)
	{
		return splits[0];
	}

	vector<SString*> actuals;
	actuals.reserve(splits.size());
	for (size_t i = 0; i < splits.size(); ++i)
	{
		const wchar_t* c_str = splits[i]->C_Str();
		size_t len = splits[i]->GetLength();

		// .으로 시작할 경우 무조건 ".."이어야 합니다.
		if (c_str[0] == L'.')
		{
			if (len != 2 || c_str[1] != L'.')
			{
				throw new SArgumentException("경로에 올바르지 않은 형식이 있습니다."_s);
			}

			// 이전 경로가 있을 경우 이전 경로를 제거합니다.
			if (actuals.size() >= 1)
			{
				SString* last = actuals.back();
				const wchar_t* last_c_str = last->C_Str();
				size_t len = last->GetLength();

				// 드라이브 루트의 경우 상위로 갈 수 없습니다.
				if (len == 2 && IsDriveLetter(last_c_str[0]) && last_c_str[1] == L':')
				{
					throw new SArgumentException("경로에 올바르지 않은 형식이 있습니다."_s);
				}

				actuals.erase(--actuals.end());
			}
		}

		// 일반적인 경우 경로를 추가합니다.
		else
		{
			actuals.emplace_back(splits[i]);
		}
	}

	// 경로 문자열을 다시 조립합니다.
	return SString::Join("\\"_s, actuals);
}

SString* SFileSystemReference::TrimDirectorySeparator(SString* path)
{
	const wchar_t* c_str = path->C_Str();
	size_t len = path->GetLength();

	size_t begin = 0;
	size_t end = len;

	for (size_t i = begin; i < end; ++i)
	{
		if (IsDirectorySeparator(c_str[i]))
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
		if (IsDirectorySeparator(c_str[i]))
		{
			--end;
		}
		else
		{
			break;
		}
	}

	if (begin == 0 && end == len)
	{
		return path;
	}

	return new SString(c_str + begin, end - begin);
}

bool SFileSystemReference::IsDriveLetter(wchar_t letter)
{
	return isalpha((int)letter) != 0;
}

bool SFileSystemReference::IsDirectorySeparator(wchar_t letter)
{
	return letter == DirectorySeparatorChar;
}

bool SFileSystemReference::IsValidPathChar(wchar_t letter, wchar_t additionalAllow)
{
	for (size_t i = 0; i < _countof(NotAllowedPathChars); ++i)
	{
		if (NotAllowedPathChars[i] == additionalAllow)
		{
			continue;
		}

		if (letter == NotAllowedPathChars[i])
		{
			return false;
		}
	}

	return true;
}