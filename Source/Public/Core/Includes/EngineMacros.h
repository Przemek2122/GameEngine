// Created by Przemys³aw Wiewióra 2020

#pragma once

// Public macros

#if _DEBUG
// Not inline in debug to be able to see callstack.
#define INLINE_DEBUGABLE
// Just a stop, can be continued
#define ENSURE_VALID(Condition) if (!(Condition)) { __debugbreak(); }
#define ENSURE_VALID_MESSAGE(Condition, Message) if (!(Condition)) { __debugbreak(); LOG_WARN(Message); }
#else
// Inline in release
#define INLINE_DEBUGABLE SDL_FORCE_INLINE
// No throw in release
#define ENSURE_VALID(Condition)
#define ENSURE_VALID_MESSAGE(Condition, Message)
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
