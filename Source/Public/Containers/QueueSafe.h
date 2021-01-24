// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "Deque.h"
#include "ThirdParty/SDL/SDL.h"

/*
 * Class for safe queue.
 * Thread safe
 */
template<typename TType>
class CQueueSafe : public CDeque<TType>
{
public:
	/* Add element at end. */
	inline void PushFrontSafe(const TType& Value)
	{
		while (!Mutex.try_lock())
		{
			SDL_Delay(1);
		}

		CDeque<TType>::PushFront(Value);

		Mutex.unlock();
	}
	inline void PushBackSafe(const TType& Value)
	{
		while (!Mutex.try_lock())
		{
			SDL_Delay(1);
		}

		CDeque<TType>::PushBack(Value);

		Mutex.unlock();
	}

	/* Delete first element. */
	inline void DequeFrontSafe()
	{
		while (!Mutex.try_lock())
		{
			SDL_Delay(1);
		}

		CDeque<TType>::DequeFront();

		Mutex.unlock();
	}
	/* Delete last element. */
	inline void DequeBackSafe()
	{
		while (!Mutex.try_lock())
		{
			SDL_Delay(1);
		}

		CDeque<TType>::DequeBack();

		Mutex.unlock();
	}

protected:
	mutable std::mutex Mutex;

};
