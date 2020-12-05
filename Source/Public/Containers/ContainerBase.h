// 

#pragma once

/**
 * Base class for containers.
 */
template<typename TType>
class CContainerBase
{
public:
	inline virtual size_t Size() const = 0;
	inline virtual bool IsEmpty() const = 0;

};
