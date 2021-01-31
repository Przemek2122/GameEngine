// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "DelegateBase.h"

/**
 * Delegate extending base with bind and unbind and UnBindAll.
 */
template<typename TReturnType = void, typename... TInParams>
class FDelegate : public FDelegateBase<TReturnType, TInParams...>
{
using DelegateBase = FDelegateBase<TReturnType, TInParams...>;
	
public:
	FDelegate() = default;
	virtual ~FDelegate() = default;
	
	/** Begin FDelegateBase interface */
	/** Executes all bound functions. */
	virtual void Execute(TInParams... InParams) override
	{
		const auto FunctorsNum = DelegateBase::Functors.Size();
	
		for (int i = 0; i < FunctorsNum; i++)
		{
			DelegateBase::Functors[i](InParams ...);
		}
	}
	/** End FDelegateBase interface */

	/** Add function by functor reference. */
	template<typename TTypeAuto>
	void BindFunctionRef(TTypeAuto Functor)
	{
		DelegateBase::Functors.Push(Functor);
	}

	/** Remove function by functor reference. */
	template<typename TTypeAuto>
	void UnBindFunctionRef(TTypeAuto Functor)
	{
		DelegateBase::Functors.Remove(Functor);
	}
	
	/** Remove function by functor reference. Use with caution. */
	void UnBindAll()
	{
		DelegateBase::Functors.Clear();
	}
	
};
