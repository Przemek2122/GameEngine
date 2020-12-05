//

#pragma once

#include "ContainerBase.h"

/*
 * Class for safe queue.
 * Not thread safe
 */
template<typename TType>
class CQueue : public CContainerBase<TType>
{
public:
	/** Begin CContainerBase interface */
	inline size_t Size() const override
	{
		return Queue.size();
	};
	inline bool IsEmpty() const override
	{
		return Queue.empty();
	}
	/** End CContainerBase interface */



	// C++ Map
	std::map;
};
