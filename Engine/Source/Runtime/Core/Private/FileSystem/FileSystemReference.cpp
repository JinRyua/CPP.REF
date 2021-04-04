// Copyright 2020-2021 Aumoa.lib. All right reserved.

#include "FileSystem/FileSystemReference.h"

#include "Core/String.h"

using namespace std;
using namespace std::filesystem;

SFileSystemReference::SFileSystemReference(SString* inPath) : Super()
{
	myPath = inPath;
}

SFileSystemReference::~SFileSystemReference()
{

}

SString* SFileSystemReference::GetRelativePath(SFileSystemReference* inReference) const
{
	// TODO:
	return nullptr;
}

SString* SFileSystemReference::GetFullPath(SString* path)
{
	// TODO:
	SString* currentDirectory = GetCurrentDirectory();
	return nullptr;
}

SString* SFileSystemReference::GetCurrentDirectory()
{
	return new SString(current_path().c_str());
}

bool SFileSystemReference::IsValidPath(SString* path)
{
	// TODO:
	return true;
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