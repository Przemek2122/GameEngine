//

#pragma once

#include "ContainerBase.h"
#include <vector>

/**
 * Dynamic array template for any type.
 */
template<typename TType>
class CArray : public CContainerBase<TType>
{
public:
	/** Begin CContainerBase interface */
	inline size_t Size() const override
	{
		return Vector.size();
	}
	inline bool IsEmpty() const override
	{
		return Vector.empty();
	}
	/** End CContainerBase interface */

	inline void Push(TType& Value)
	{
		Vector.push_back(Value);
	}
	inline void Push(const TType& Value)
	{
		Vector.push_back(Value);
	}

	inline bool RemoveAt(const size_t Index)
	{
		Vector.erase(Vector.begin() + Index);
	}
	/** Remove first match. */
	inline bool Remove(TType& Value)
	{
		return Vector.erase(std::remove(Vector.begin(), Vector.end(), Value), Vector.end()) != Vector.end();
	}
	/** Remove all matches. */
	inline bool RemoveAll(TType& Value)
	{
		std::vector<int>::iterator Iter = Vector.begin();

		size_t RemovedElements = 0;

		while (Iter != Vector.end())
		{
			if (*Iter == Value)
			{
				Iter = Vector.erase(Iter);
				RemovedElements++;
			}
			else 
			{
				Iter++;
			}
		}

		return RemovedElements > 0;
	}

	INLINE_DEBUGABLE TType& operator[](size_t Index)
	{
		return Vector[Index];
	}

	INLINE_DEBUGABLE constexpr TType& At(size_t Index)
	{
		return Vector.at(Index);
	}

	/** @TODO Add suport for auto. */

	inline void Fill(const TType& Value)
	{
		Vector._Ufill(Value);
	}

	inline constexpr void Swap(std::vector<TType>& Other)
	{
		Vector.swap(Other);
	}

	TType& begin()
	{
		return Vector.begin();
	}

	TType& end()
	{
		return Vector.end();
	}

	TType& begin() const
	{
		return Vector.begin();
	}

	TType& end() const
	{
		return Vector.end();
	}

	TType* begin()
	{
		return Vector.begin();
	}

	TType* end()
	{
		return Vector.end();
	}

	TType* begin() const
	{
		return Vector.begin();
	}

	TType* end() const
	{
		return Vector.end();
	}

public:
	/** C++ Vector */
	std::vector<TType> Vector;
};
