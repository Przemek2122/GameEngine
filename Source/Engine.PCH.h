// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers


// Add headers that you want to pre-compile here

// C/C++ includes
#include <iostream>
#include <stdio.h>
#include <string>

// ThirdParty includes
#include "ThirdParty/SDL/SDL.h"
#undef main // Required as SDL defines it's own main.

// Game engine includes
#include "Misc/Util.h"
#include "Core/Engine.h"



