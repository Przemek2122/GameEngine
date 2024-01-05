// See https://github.com/Przemek2122/GameEngine

#include "CoreEngine.h"
#include "Assets/Parser.h"

FParser::FParser(const CArray<char>& InSeparatorCharArray, const CArray<char>& InIgnoredCharArray, const CArray<char>& InCommentCharArray)
	: SeparatorCharArray(InSeparatorCharArray)
	, IgnoredCharArray(InIgnoredCharArray)
	, CommentCharArray(InCommentCharArray)
{
}

CArray<std::string> FParser::ParseLineIntoStrings(const std::string& Line)
{
	CArray<std::string> ParsedStrings;

	std::string CurrentWord;

	for (const char& Char : Line)
	{
		if (IsComment(Char))
		{
			// Comment means we stop interpreting as comment goes to the end of the line
			break;
		}
		
		if (IsSeparator(Char))
		{
			ParsedStrings.Push(CurrentWord);

			CurrentWord.clear();
		}
		else if (!IsIgnored(Char))
		{
			CurrentWord += Char;
		}
	}

	if (CurrentWord.length() > 0)
	{
		ParsedStrings.Push(CurrentWord);
	}

	return ParsedStrings;
}

bool FParser::AreCharsEqual(const char A, const char B)
{
	return (A == B);
}

bool FParser::IsComment(const char Any)
{
	bool bIsMatchFound = false;

	for (const char CommentChar : CommentCharArray)
	{
		if (AreCharsEqual(CommentChar, Any))
		{
			bIsMatchFound = true;

			break;
		}
	}

	return bIsMatchFound;
}

bool FParser::IsSeparator(const char Any)
{
	bool bIsMatchFound = false;

	for (const char& SeparatorChar : SeparatorCharArray)
	{
		if (AreCharsEqual(SeparatorChar, Any))
		{
			bIsMatchFound = true;

			break;
		}
	}

	return bIsMatchFound;
}

bool FParser::IsIgnored(char Any)
{
	bool bIsMatchFound = false;

	for (const char& IgnoredChar : IgnoredCharArray)
	{
		if (AreCharsEqual(IgnoredChar, Any))
		{
			bIsMatchFound = true;

			break;
		}
	}

	return bIsMatchFound;
}
