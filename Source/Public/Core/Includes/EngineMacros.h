// Created by Przemys³aw Wiewióra 2020

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

/**
 * Advanced text, returns std::string, can be used anywhere
 * Can be used like:
 * TEXT_O("Test button " << "1" << 1)
 */
#define TEXT_ADV(Text) (dynamic_cast<std::ostringstream&>(TEXT_OST(Text)).str())
/**
 * more advanced text, returns ostringstream
 * Can be used like:
 * TEXT_O("Test button " << "1" << 1)
 */
#define TEXT_OST(Text) (std::ostringstream().flush() << (Text))
/** Most basic text implementation, just changes to char* */
#define TEXT_CHAR(Text) (const_cast<char*>(Text))
#define STRING(Text) std::string(Text)

#define Super __super
