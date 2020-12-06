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
	};
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

	inline bool RemoveAt(const size_t Value)
	{
		Vector.erase(Value);
	}

	inline TType& operator[](size_t Index)
	{
		return Vector[Index];
	}

	inline constexpr TType& At(size_t Index)
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

public:
	/** C++ Vector */
	std::vector<TType> Vector;
};
