// Created by Przemys�aw Wiewi�ra 2020

#pragma once

// Public macros

#include "CoreMinimal.h"

SDL_FORCE_INLINE bool Inline_ENSURE_VALID_Lambda(auto Condition)
{
	if (Condition)
	{
		return true;
	}
	else
	{
		__debugbreak();

		return false;
	}
};

#if _DEBUG
// Not inline in debug to be able to see callstack.
#define INLINE_DEBUGABLE
// Just a stop, can be continued
#define ENSURE_VALID(Condition) Inline_ENSURE_VALID_Lambda(Condition)
//#define ENSURE_VALID_MESSAGE(Condition, Message) Inline_ENSURE_VALID_MESSAGE_Lambda(Condition, Message)
#else
// Inline in release
#define INLINE_DEBUGABLE SDL_FORCE_INLINE
// No throw in release
#define ENSURE_VALID(Condition)
//#define ENSURE_VALID_MESSAGE(Condition, Message)
#endif

#define TEXT(Text) const_cast<char*>(Text)
#define STRING(Text) std::string(Text)

#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

// Unused for now as we make static .lib
#if GAMEENGINELIB // Inside DLL
#	define GAMEENGINE_API   __declspec(dllexport)
#else // Outside DLL
#	define GAMEENGINE_API   __declspec(dllimport)
#endif // GAMEENGINELIB

#define Super __super
