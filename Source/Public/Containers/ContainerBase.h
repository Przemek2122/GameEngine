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

	SDL_FORCE_INLINE virtual TSizeType Size() const = 0;
	SDL_FORCE_INLINE virtual bool IsEmpty() const = 0;

};
