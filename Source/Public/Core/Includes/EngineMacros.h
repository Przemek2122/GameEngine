// Created by Przemys³aw Wiewióra 2020

#pragma once

// Public macros

#ifdef _DEBUG
// Not inline in debug to be able to see callstack.
#define INLINE_DEBUGABLE
// Throw in debug
#define ENSURE(Message) throw Message
#else
// Inline in release
#define INLINE_DEBUGABLE inline
// No throw in release
#define ENSURE(Message)
#endif

#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

#define GAMEENGINE_API DLLIMPORT
