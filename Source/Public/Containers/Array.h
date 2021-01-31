// Created by Przemys�aw Wiewi�ra 2020

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
	_NODISCARD SDL_FORCE_INLINE size_t Size() const override
	{
		return Vector.size();
	}
	_NODISCARD SDL_FORCE_INLINE bool IsEmpty() const override
	{
		return Vector.empty();
	}
	/** End CContainerBase interface */
	
	template<typename TTypeAuto>
	SDL_FORCE_INLINE void Push(TTypeAuto Value)
	{
		Vector.push_back(Value);
	}
	template<typename TTypeAuto>
	SDL_FORCE_INLINE void Push(TTypeAuto Value)const
	{
		Vector.push_back(Value);
	}
	
	SDL_FORCE_INLINE bool RemoveAt(const size_t Index)
	{
		if (Index >= 0 && Index < Size())
		{
			Vector.erase(Vector.begin() + Index);
			
			return true;
		}
#ifdef _DEBUG
		else
		{
			ENSURE_VALID_MESSAGE(false, "CArray::RemoveAt(" << Index << "): Given index is out of range.");
		}
#endif

		return false;
	}
	
	/** Remove first match. */
	template<typename TTypeAuto>
	SDL_FORCE_INLINE bool Remove(TTypeAuto Value)
	{
		auto DeleteIndex = FindIndexOf(Value);

		if (DeleteIndex != -1)
		{
			return RemoveAt(DeleteIndex);
		}
		
		return false;
	}
	
	/** Remove all matches. */
	template<typename TTypeAuto>
	SDL_FORCE_INLINE bool RemoveAll(TTypeAuto Value)
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

	SDL_FORCE_INLINE TType& operator[](size_t Index)
	{
		return Vector[Index];
	}

	SDL_FORCE_INLINE const TType& operator[](size_t Index) const
	{
		return Vector[Index];
	}
	
	template<typename TTypeAuto>
	SDL_FORCE_INLINE constexpr TType& At(TTypeAuto Index)
	{
		return Vector.at(Index);
	}

	/** @return Index or -1 if not found */
	template<typename TTypeAuto>
	_NODISCARD SDL_FORCE_INLINE int FindIndexOf(TTypeAuto Value)
	{
		const int VectorSize = Vector.size();
		
		for (int i = 0; i < VectorSize; i++)
		{
			if (Vector[i] == Value)
			{
				return i;
			}
		}
		
		return -1;
	}
	
	template<typename TTypeAuto>
	SDL_FORCE_INLINE void Fill(TTypeAuto Value)
	{
		Vector._Ufill(Value);
	}
	
	SDL_FORCE_INLINE constexpr void Swap(std::vector<TType>& Other)
	{
		Vector.swap(Other);
	}
	
	template<typename TTypeAuto>
	SDL_FORCE_INLINE void SetNum(TTypeAuto NewSize)
	{
		Vector.resize(NewSize);
	}
	
	SDL_FORCE_INLINE void Clear()
	{
		Vector.clear();		
	}
	SDL_FORCE_INLINE void Empty()
	{
		Vector.empty();
	}

public:
	/** C++ Vector */
	std::vector<TType> Vector;
};
