//

#pragma once

#include "Queue.h"

/*
 * Class for safe queue.
 * Thread safe
 */
template<typename Type>
class CQueueSafe : public CQueue<Type>
{
public:
	/* Add element at end. */
	void SafePush(const Type& value)
	{
		while (!Mutex.try_lock())
		{
			SDL_Delay(1);
		}

		CQueue<Type>::Queue.push(value);
		Mutex.unlock();
	}

	/* Delete first element. */
	void SafePop()
	{
		while (!Mutex.try_lock())
		{
			SDL_Delay(1);
		}

		CQueue<Type>::Queue.pop();
		Mutex.unlock();
	}

protected:
	mutable std::mutex Mutex;

};