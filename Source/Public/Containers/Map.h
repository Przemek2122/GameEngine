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
	inline size_t Size() const override
	{
		return Map.size();
	};
	inline bool IsEmpty() const override
	{
		return Map.empty();
	}
	/** End CContainerBase interface */


public:
	// C++ Map
	std::map<TKey, TValue> Map;
};
