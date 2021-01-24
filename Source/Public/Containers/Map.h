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
	_NODISCARD inline size_t Size() const override
	{
		return Map.size();
	};
	_NODISCARD inline bool IsEmpty() const override
	{
		return Map.empty();
	}
	/** End CContainerBase interface */

	_NODISCARD inline void Clear()
	{
		Map.clear();
	}
	
	_NODISCARD inline bool HasKey(TKey& Key)
	{
		return Map.find(Key) != Map.end();
	}

	INLINE_DEBUGABLE TValue& operator[](TKey& Index)
	{
		return Map[Index];
	}
	INLINE_DEBUGABLE TValue& operator[](TKey Index)
	{
		return Map[Index];
	}

	_NODISCARD inline void Emplace(TKey& Key, TValue& Value)
	{
		Map.emplace(Key, Value);
	}
	_NODISCARD inline void Emplace(TKey& Key, TValue& Value) const
	{
		Map.emplace(Key, Value);
	}

	_NODISCARD inline void InsertOrAssign(TKey& Key, TValue& Value)
	{
		Map.insert_or_assign(Key, Value);
	}
	_NODISCARD inline void InsertOrAssign(TKey& Key, TValue& Value) const
	{
		Map.insert_or_assign(Key, Value);
	}
	
	_NODISCARD inline bool Remove(TKey Key)
	{
		return Map.erase(Key);
	}

	_NODISCARD inline bool ContainsKey(TKey Key)
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
	_NODISCARD inline bool ContainsKey(TKey Key) const
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
	_NODISCARD inline bool ContainsValue(TValue Value)
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
	_NODISCARD inline bool ContainsValue(TValue Value) const
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
	
	_NODISCARD inline TValue FindByKey(TKey Key)
	{
		return Map.find(Key)->second;
	}
	_NODISCARD inline TValue FindByValue(TValue Value)
	{
		return Map.find(Value);
	}

	_NODISCARD inline void SetAll(TValue& Value)
	{
		typename std::map<TKey, TValue>::iterator Iterator;
		
		for (Iterator = Map.begin(); Iterator != Map.end(); Iterator++)
		{
			Iterator->second = Value;
		}
	}
	_NODISCARD inline void SetAll(TValue Value)
	{
		typename std::map<TKey, TValue>::iterator Iterator;
		
		for (Iterator = Map.begin(); Iterator != Map.end(); Iterator++)
		{
			Iterator->second = Value;
		}
	}

public:
	// C++ Map
	std::map<TKey, TValue> Map;
};
