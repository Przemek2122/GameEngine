//

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
	
	_NODISCARD inline bool Remove(TKey& Key)
	{
		return Map.erase(Key);
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
