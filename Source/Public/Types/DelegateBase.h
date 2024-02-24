// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"

/**
 * Base Delegate storing functors.
 * Call ExecuteByLambda to execute all bound functions.
 */
template<typename TReturnType, typename... TInParams>
class FDelegateBase
{
using Functor = FFunctorBase<TReturnType, TInParams...>;
	
public:
	FDelegateBase() = default;
	virtual ~FDelegateBase()
	{
		for (const Functor* FunctorObject : Functors)
		{
			delete FunctorObject;
		}

		Functors.Clear();
	}

	/** @returns true if there is at least one function bound. */
	_NODISCARD virtual bool IsBound() const
	{
		return (Functors.Size() > 0);
	}
	
	/** Executes all bound functions. */
	virtual void Execute(TInParams... InParams) = 0;

protected:
	CArray<Functor*> Functors;
	
};
