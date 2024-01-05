// See https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"

class FParser
{
public:
	/**
	 * Constructor for Parser, it's required to call before anything else in this class as it sets basic properties.
	 * @param InSeparatorCharArray Defines which chars are meant to be words breaker
	 * @param InIgnoredCharArray Defines which chars are ignored like they were not present
	 * @param InCommentCharArray Defines which chars means comment and rest of the line after them are ignored.
	 */
	FParser(
		const CArray<char>& InSeparatorCharArray,
		const CArray<char>& InIgnoredCharArray = { ' ' },
		const CArray<char>& InCommentCharArray = { '#' }
	);

	/** Takes given string and splits it into words by Separators set in constructor */
	CArray<std::string> ParseLineIntoStrings(const std::string& Line);

	inline static bool AreCharsEqual(char A, char B);

	bool IsComment(char Any);
	bool IsSeparator(char Any);
	bool IsIgnored(char Any);

protected:
	CArray<char> SeparatorCharArray;
	CArray<char> CommentCharArray;
	CArray<char> IgnoredCharArray;

};
