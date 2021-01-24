// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

/**
 * Function storage class. Supports:
 * NOTHING! It's abstract class used as base.
 *
 * Can be used to call stored function on child, @see operator()
 *
 * As this is base, some link will be provided
 * https://isocpp.org/wiki/faq/pointers-to-members
 */
template<typename TReturnType, typename TInParams>
class FFunctorBase
{
public:
	/** This function calls stored function */
	virtual TReturnType operator()(TInParams Params = nullptr) = 0; // TInParams InParams = nullptr

	/** True if any function was bound. */                                                                                                                                                
	_NODISCARD virtual bool IsValid() const = 0;
};
