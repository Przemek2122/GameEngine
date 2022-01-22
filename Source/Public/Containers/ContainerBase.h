// Created by Przemys�aw Wiewi�ra 2020 

#pragma once

/**
 * Base class for containers.
 */
template<typename TType>
class CContainerBase
{
public:
	virtual ~CContainerBase() = default;
	SDL_FORCE_INLINE virtual size_t Size() const = 0;
	SDL_FORCE_INLINE virtual bool IsEmpty() const = 0;

};
