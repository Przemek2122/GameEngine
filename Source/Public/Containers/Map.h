// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ContainerBase.h"

#include <map>

/*
 * Class for safe queue.
 * Not thread safe
 */
template<typename TKey, typename TValue>
class CMap : public CContainerBase<TValue>
{
public:
	/** Begin CContainerBase interface */
	_NODISCARD SDL_FORCE_INLINE size_t Size() const override
	{
		return Map.size();
	}
	_NODISCARD SDL_FORCE_INLINE bool IsEmpty() const override
	{
		return Map.empty();
	}
	/** End CContainerBase interface */

	/** Removes all elements from the container (which are destroyed), leaving the container with a size of 0. */
	_NODISCARD SDL_FORCE_INLINE void Clear()
	{
		Map.clear();
	}
	
	template<typename TAutoType>
	_NODISCARD SDL_FORCE_INLINE void IsValidKey(const TAutoType Key) const
	{
		return HasKey(Key);
	}
	
	template<typename TAutoType>
	_NODISCARD bool HasKey(TAutoType Key)
	{
		return Map.find(Key) != Map.end();
	}

	template<typename TAutoType>
	SDL_FORCE_INLINE TValue& operator[](TAutoType Index)
	{
		return Map[Index];
	}
	template<typename TAutoType>
	SDL_FORCE_INLINE TValue& operator[](TAutoType Index) const
	{
		return Map[Index];
	}
	
	template<typename TAutoType>
	SDL_FORCE_INLINE TValue At(TAutoType Index)
	{
		return Map.at(Index);
	}
	template<typename TAutoType>
	SDL_FORCE_INLINE TValue At(TAutoType Index) const
	{
		return Map.at(Index);
	}
	
	template<typename TKeyAuto, typename TValueAuto>
	_NODISCARD SDL_FORCE_INLINE void Emplace(TKeyAuto Key, TValueAuto Value)
	{
		Map.emplace(Key, Value);
	}
	template<typename TKeyAuto, typename TValueAuto>
	_NODISCARD SDL_FORCE_INLINE void Emplace(TKeyAuto Key, TValueAuto Value) const
	{
		Map.emplace(Key, Value);
	}

	template<typename TKeyAuto, typename TValueAuto>
	_NODISCARD SDL_FORCE_INLINE void InsertOrAssign(TKeyAuto Key, TValueAuto Value)
	{
		Map.insert_or_assign(Key, Value);
	}
	
	template<typename TAutoType>
	SDL_FORCE_INLINE bool Remove(TAutoType Key)
	{
		return Map.erase(Key);
	}
	
	template<typename TAutoType>
	_NODISCARD SDL_FORCE_INLINE bool ContainsKey(TAutoType Key)
	{
		for (auto& Pair : Map)
		{
			if (Pair.first == Key)
			{
				return true;
			}
		}

		return false;
	}
	template<typename TAutoType>
	_NODISCARD SDL_FORCE_INLINE bool ContainsKey(TAutoType Key) const
	{
		for (auto& Pair : Map)
		{
			if (Pair.first == Key)
			{
				return true;
			}
		}

		return false;
	}
	template<typename TAutoType>
	_NODISCARD SDL_FORCE_INLINE bool ContainsValue(TAutoType Value)
	{
		for (auto& Pair : Map)
		{
			if (Pair.second == Value)
			{
				return true;
			}
		}

		return false;
	}
	template<typename TAutoType>
	_NODISCARD SDL_FORCE_INLINE bool ContainsValue(TAutoType Value) const
	{
		for (auto& Pair : Map)
		{
			if (Pair.second == Value)
			{
				return true;
			}
		}

		return false;
	}
	
	template<typename TAutoType>
	_NODISCARD SDL_FORCE_INLINE TValue FindValueByKey(TAutoType Key)
	{
		return Map.find(Key)->second;
	}
	template<typename TAutoType>
	_NODISCARD SDL_FORCE_INLINE TValue FindKeyByValue(TAutoType Value)
	{
		return Map.find(Value);
	}
	
	template<typename TAutoType>
	_NODISCARD SDL_FORCE_INLINE void SetAll(TAutoType Value)
	{
		typename std::map<TKey, TValue>::iterator Iterator;
		
		for (Iterator = Map.begin(); Iterator != Map.end(); ++Iterator)
		{
			Iterator->second = Value;
		}
	}

	void MapIterator(FFunctorLambda<void, TKey, TValue> Delegate)
	{
		for (auto it = Map.begin(); it != Map.end(); ++it)
		{
			Delegate(it->first, it->second);
		}
	}

	void MapIteratorByIndexOnly(FFunctorLambda<void, TKey> Delegate)
	{
		for (auto it = Map.begin(); it != Map.end(); ++it)
		{
			Delegate(it->first);
		}
	}

	void MapIteratorByValueOnly(FFunctorLambda<void, TValue> Delegate)
	{
		for (auto it = Map.begin(); it != Map.end(); ++it)
		{
			Delegate(it->second);
		}
	}

public:
	// C++ Map
	std::map<TKey, TValue> Map;
};
