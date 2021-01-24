// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

/**
 * Function storage class. Supports:
 * - Static function
 */
template<typename TReturnType = void, typename TInParams = void()>
class FFunctorStatic : public FFunctorBase<TReturnType, TInParams>
{
public:	
	/** For static functions */
	FFunctorStatic(TReturnType (*InFunctionPointer)(TInParams))
		: FunctionPointer(InFunctionPointer)
	{
	}

	/** Begin FFunctorBase interface */
	virtual TReturnType operator()(TInParams Params = nullptr)
    {
		return FunctionPointer(Params);
    }
	
	_NODISCARD virtual bool IsValid() const override
	{
		return FunctionPointer != nullptr;
	}
	/** End FFunctorBase interface */

	/** Assign other instance to this. */
	FFunctorStatic& operator=(FFunctorStatic const& InFunctor)
    {
		FunctionPointer = InFunctor.FunctionPointer;
		
		return this;
    }

protected:
	/** Stored function */
	TReturnType (*FunctionPointer)(TInParams);
};
