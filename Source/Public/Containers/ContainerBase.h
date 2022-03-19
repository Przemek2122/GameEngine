// Created by Przemys³aw Wiewióra 2020 

#pragma once

/**
 * Base class for containers.
 */
template<typename TType, typename TSizeType = int>
class CContainerBase
{
public:
	virtual ~CContainerBase() = default;

	virtual TSizeType Size() const = 0;
	virtual bool IsEmpty() const = 0;

};
