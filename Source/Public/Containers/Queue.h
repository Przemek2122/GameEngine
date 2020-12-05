//

#pragma once

#include "ContainerBase.h"

/*
 * Class for safe queue.
 * Not thread safe
 */
template<typename TType>
class CQueue : public CContainerBase<TType>
{
public:
	/** Begin CContainerBase interface */
	inline size_t Size() const override
	{
		return Queue.size();
	};
	inline bool IsEmpty() const override
	{
		return Queue.empty();
	}
	/** End CContainerBase interface */

	inline void Push(const TType& Value)
	{
		Queue.push(Value);
	}

	/** @Returns first element without removing. */
	inline TType& PeekFirst()
	{
		return Queue.front();
	}
	/** @Returns first element without removing. */
	inline TType PeekFirst() const
	{
		return Queue.front();
	}

	/** @Returns last element without removing. */
	inline TType& PeekLast()
	{
		return Queue.back();
	}
	/** @Returns last element without removing. */
	inline TType PeekLast() const
	{
		return Queue.back();
	}

	/** Construct element at end and insert */
	template<class... TArgs>
	inline decltype(auto) Emplace(TArgs&&... Args)
	{
		return Queue.emplace(Args);
	}

	/** Removes the first element. */
	inline void Pop()
	{
		Queue.pop();
	}

	/** C++ queue. */
	std::queue<TType> Queue;
};
