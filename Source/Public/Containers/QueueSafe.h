//

#pragma once

#include "Queue.h"
#include "ThirdParty/SDL/SDL.h"

/*
 * Class for safe queue.
 * Thread safe
 */
template<typename TType>
class CQueueSafe : public CQueue<TType>
{
public:
	/* Add element at end. */
	inline void PushSafe(const TType& Value)
	{
		while (!Mutex.try_lock())
		{
			SDL_Delay(1);
		}

		CQueue<TType>::Push(Value);

		Mutex.unlock();
	}

	/* Delete first element. */
	inline void PopSafe()
	{
		while (!Mutex.try_lock())
		{
			SDL_Delay(1);
		}

		CQueue<TType>::Pop();

		Mutex.unlock();
	}

protected:
	mutable std::mutex Mutex;

};
