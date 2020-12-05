//

#pragma once

#include "ContainerBase.h"

/**
 * Dynamic array template for any type.
 */
template<typename TType>
class CArray : public CContainerBase<TType>
{
	/** Begin CContainerBase interface */
	inline int Size() const override
	{
		return Vector.size();
	};
	inline bool IsEmpty() const override
	{
		return Vector.empty();
	}
	/** End CContainerBase interface */



	std::vector Vector;
};
