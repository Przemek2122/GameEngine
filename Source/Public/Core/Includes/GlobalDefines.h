// Created by Przemys³aw Wiewióra 2020

#pragma once

#define INDEX_NONE								-1

/** Defines default order for widget display */
#define WIDGET_DEFINES_DEFAULT_ORDER			0

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

#define THREAD_WAIT_MS(TimeInMS)	std::this_thread::sleep_for(std::chrono::milliseconds(TimeInMS))
#define THREAD_WAIT_NS(TimeInNS)	std::this_thread::sleep_for(std::chrono::nanoseconds(TimeInNS))
/** Wait for 0.00001 second (or 0.01 ms) */
#define THREAD_WAIT_SHORT_TIME		THREAD_WAIT_NS(10000) 

#define COUNTER_START(PropertyNameStart) const auto PropertyNameStart{ std::chrono::high_resolution_clock::now() }
#define COUNTER_END(PropertyNameStart, PropertyNameEnd) std::chrono::duration<double, std::nano> PropertyNameEnd{ std::chrono::high_resolution_clock::now() - PropertyNameStart }
#define COUNTER_GET(PropertyNameEnd) PropertyNameEnd.count()
