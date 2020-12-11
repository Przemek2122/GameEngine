// Created by Przemys³aw Wiewióra 2020

#pragma once

// Public macros

#ifdef _DEBUG
// Not inline in debug to be able to see callstack.
#define INLINE_DEBUGABLE
#else
// Inline in release
#define INLINE_DEBUGABLE inline
#endif
