// Created by Przemys³aw Wiewióra 2020 

#pragma once

/** 32 bit integer - Default integer type for containers. */
typedef Uint32 ContainerInt;
/** 64 bit integer type for containers. */
typedef Uint64 ContainerBigInt;
/** 63 + 1 bit integer type for containers. */
typedef int64_t PotentiallyNegativeContainerInt;

/**
 * Base class for containers.
 */
template<typename TType, typename TSizeType = ContainerInt>
class CContainerBase
{
public:
	virtual ~CContainerBase() = default;

	virtual TSizeType Size() const = 0;
	virtual bool IsEmpty() const = 0;

};
