//

#pragma once

/*
 * Class for safe queue.
 * Not thread safe
 */
template<typename Type>
class CQueue
{
public:
	/** @Returns first element without removing. */
	Type& PeekFirst()
	{
		return Queue.front();
	}
	/** @Returns first element without removing. */
	Type PeekFirst() const
	{
		return Queue.front();
	}

	/** @Returns last element without removing. */
	Type& PeekLast()
	{
		return Queue.back();
	}
	/** @Returns last element without removing. */
	Type PeekLast() const
	{
		return Queue.back();
	}

	/** @Returns true  */
	bool IsEmpty() const
	{
		return Queue.empty();
	}

protected:
	std::queue<Type> Queue;

};
