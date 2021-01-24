// Created by Przemys³aw Wiewióra 2020

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
	_NODISCARD inline size_t Size() const override
	{
		return Vector.size();
	}
	_NODISCARD inline bool IsEmpty() const override
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
		return Vector.erase(Vector.begin() + Index);
	}
	/** Remove first match. */
	inline bool Remove(TType& Value)
	{
		return Vector.erase(std::remove(Vector.begin(), Vector.end(), Value), Vector.end()) != Vector.end();
	}
	/** Remove all matches. */
	inline bool RemoveAll(TType& Value)
	{
		std::vector<int>::iterator Iterator = Vector.begin();

		size_t RemovedElements = 0;

		while (Iterator != Vector.end())
		{
			if (*Iterator == Value)
			{
				Iterator = Vector.erase(Iterator);
				RemovedElements++;
			}
			else 
			{
				++Iterator;
			}
		}

		return RemovedElements > 0;
	}

	INLINE_DEBUGABLE TType& operator[](size_t Index)
	{
		return Vector[Index];
	}

	INLINE_DEBUGABLE const TType& operator[](size_t Index) const
	{
		return Vector[Index];
	}

	INLINE_DEBUGABLE constexpr TType& At(size_t Index)
	{
		return Vector.at(Index);
	}

	inline void Fill(const TType& Value)
	{
		Vector._Ufill(Value);
	}

	inline constexpr void Swap(std::vector<TType>& Other)
	{
		Vector.swap(Other);
	}

	inline void SetNum(size_t NewSize)
	{
		Vector.resize(NewSize);
	}
	
	inline void Clear()
	{
		Vector.clear();		
	}
	inline void Empty()
	{
		Vector.empty();
	}

public:
	/** C++ Vector */
	std::vector<TType> Vector;
};
