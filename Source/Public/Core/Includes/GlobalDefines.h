// Created by Przemys³aw Wiewióra 2020

#pragma once

/** Should any type of tests be compiled? */
#define ENGINE_TESTS_ALLOW_ANY					1

/** Should default tests be performed? */
#define ENGINE_TESTS_RUN						1 && ENGINE_TESTS_ALLOW_ANY


/** Should show memory allocation debug? */
#define ENGINE_MEMORY_ALLOCATION_DEBUG			0

/** Should show widgets allocation debug? */
#define ENGINE_MEMORY_ALLOCATION_DEBUG_WIDGETS	1 && ENGINE_MEMORY_ALLOCATION_DEBUG
/** Should show assets allocation debug? */
#define ENGINE_MEMORY_ALLOCATION_DEBUG_ASSETS	1 && ENGINE_MEMORY_ALLOCATION_DEBUG
/** Should show fonts allocation debug? */
#define ENGINE_MEMORY_ALLOCATION_DEBUG_FONTS	1 && ENGINE_MEMORY_ALLOCATION_DEBUG


