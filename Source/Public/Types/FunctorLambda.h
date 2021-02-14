// Created by Przemys³aw Wiewióra 2020

#pragma once

#include <functional>

#include "CoreMinimal.h"

/**
 * Function storage class. Supports:
 * Lambda
 */
template<typename TReturnType, typename... TInParams> 
class FFunctorLambda : public FFunctorBase<TReturnType, TInParams...>
{
public:
	template<typename TTypeAuto>
	FFunctorLambda(TTypeAuto InFunction)
		: Function(std::move(InFunction))
	{
    }
	FFunctorLambda(std::function<TReturnType(TInParams ...)>& InFunction)
		: Function(std::move(InFunction))
	{
    }
	FFunctorLambda(std::function<TReturnType(TInParams ...)>&& InFunction)
		: Function(std::move(InFunction))
	{
    }
	
	/** Begin FFunctorBase interface */
	virtual TReturnType operator()(TInParams... Params) override
	{
		return Function(Params ...);
	}                                                                                                                                               
	_NODISCARD virtual bool IsValid() const override
	{
		return false;
	}
	/** End FFunctorBase interface */

protected:
	/** Stored lambda */
	std::function<TReturnType(TInParams ...)> Function;
};
