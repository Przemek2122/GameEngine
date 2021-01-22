//

#pragma once

#include "ContainerBase.h"

/*
 * Class for safe queue.
 * Not thread safe
 */
template<typename TType>
class CDeque : public CContainerBase<TType>
{
public:
	/** Begin CContainerBase interface */
	inline size_t Size() const override
	{
		return Deque.size();
	};
	inline bool IsEmpty() const override
	{
		return Deque.empty();
	}
	/** End CContainerBase interface */

	/** @Returns first element without removing. */
	inline TType& PeekFirst()
	{
		return Deque.front();
	}
	/** @Returns first element without removing. */
	inline TType PeekFirst() const
	{
		return Deque.front();
	}

	/** @Returns last element without removing. */
	inline TType& PeekLast()
	{
		return Deque.back();
	}
	/** @Returns last element without removing. */
	inline TType PeekLast() const
	{
		return Deque.back();
	}

	inline TType GetPositionOf(const TType& Value) const
	{
		auto Iterator = std::find(Deque->c.begin(), Deque->c.end(), Value);
		return std::distance(Deque->c.begin(), Iterator);
	}

	inline TType& operator[](size_t Index)
	{
		return Deque[Index];
	}

	inline const TType& operator[](size_t Index) const
	{
		return Deque[Index];
	}
	
	inline void PushBack(TType& Value)
	{
		Deque.push_back(Value);
	}
	inline void PushBack(TType& Value) const
	{
		Deque.push_back(Value);
	}
	inline void PushBack(TType Value)
	{
		Deque.push_back(Value);
	}
	inline void PushBack(TType Value) const
	{
		Deque.push_back(Value);
	}
	inline void PushFront(TType& Value)
	{
		Deque.push_front(Value);
	}
	inline void PushFront(TType& Value) const
	{
		Deque.push_front(Value);
	}
	inline void PushFront(TType Value)
	{
		Deque.push_front(Value);
	}
	inline void PushFront(TType Value) const
	{
		Deque.push_front(Value);
	}

	inline void DequeFront()
	{
		Deque.pop_front();
	}
	inline void DequeFront() const
	{
		Deque.pop_front();
	}
	inline void DequeBack()
	{
		Deque.pop_back();
	}
	inline void DequeBack() const
	{
		Deque.pop_back();
	}
	
	/** C++ deque. */
	std::deque<TType> Deque;
};
