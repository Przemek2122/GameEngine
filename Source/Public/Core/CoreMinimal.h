// include for headers

#pragma once

// Stuff forward declared here must be included in CoreEngine.h

// Third Party forward declarations
struct SDL_Renderer;
struct SDL_Window; 
union SDL_Event;
struct SDL_Thread;

// Engine base classes forward declarations
class FEngineMain;
class FEngine;
class FFilesystem;
class FRenderer;
class FWindow;

template<typename TType>
class CContainerBase;
template<typename TType>
class CArray;
template<typename TKey, typename TValue>
class CMap;
template<typename TType>
class CQueue;
template<typename TType>
class CQueueSafe;


// Public macros

#ifdef _DEBUG
// It is an inline function but only in release.
#define INLINE_DEBUGABLE
#elif
#define INLINE_DEBUGABLE inline
#endif

