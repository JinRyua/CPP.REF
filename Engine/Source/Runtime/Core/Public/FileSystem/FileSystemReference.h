// Copyright 2020-2021 Aumoa.lib. All right reserved.

#pragma once

#include "Core/Object.h"

class SString;

/// <summary>
/// 파일 시스템에서 특정 경로에 대한 레퍼런스를 탐색합니다.
/// </summary>
SCLASS(SFileSystemReference) class SFileSystemReference : virtual public SObject
{
	SCLASS_BODY(SFileSystemReference)

private:
	static constexpr const wchar_t NotAllowedPathChars[] = L"\\/:*?\"<>|";
	static constexpr const wchar_t DirectorySeparatorChar = L'\\';

	SPROPERTY(SString*, myPath);

public:
	/// <summary>
	/// 상대적 경로 또는 전체 경로를 지정하여 새 레퍼런스를 생성합니다.
	/// </summary>
	/// <param name="inPath"> 지원하는 경로 유형을 전달합니다. </param>
	SFileSystemReference(SString* inPath);
	~SFileSystemReference() override;

	/// <summary>
	/// 대상 레퍼런스와 상대적 경로를 가져옵니다.
	/// </summary>
	/// <param name="inReference"> 대상 레퍼런스를 전달합니다. </param>
	/// <returns> 상대적 경로가 반환됩니다. </returns>
	SString* GetRelativePath(SFileSystemReference* inReference) const;

protected:
	/// <summary>
	/// 상대 경로의 절대 경로를 가져옵니다.
	/// </summary>
	/// <param name="path"> 상대 경로를 전달합니다. </param>
	/// <returns> 절대 경로가 반환됩니다. </returns>
	static SString* GetFullPath(SString* path);

	/// <summary>
	/// 시스템의 현재 디렉토리를 가져옵니다.
	/// </summary>
	/// <returns> 현재 디렉토리 경로가 반환됩니다. </returns>
	static SString* GetCurrentDirectory();

private:
	static bool IsValidPath(SString* path);
	static bool IsRootBased(SString* path);
	static void NormalizePathDirectorySeparator(SString* path);

	static bool IsDriveLetter(wchar_t letter);
	static bool IsDirectorySeparator(wchar_t letter);
	static bool IsValidPathChar(wchar_t letter, wchar_t additionalAllow);
};