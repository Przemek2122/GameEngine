// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "DelegateBase.h"
#include "FunctorLambda.h"
#include "FunctorObject.h"

/**
 * Delegate extending base with bind and unbind and UnBindAll.
 *
 * Note:
 * All functions passed in are deleted at end of this object life.
 */
template<typename... TInParams>
class FDelegate : public FDelegateBase<void, TInParams...>
{
using DelegateBase = FDelegateBase<void, TInParams...>;
	
public:
	FDelegate() = default;
	virtual ~FDelegate() override
	{
		const auto FunctorsNum = DelegateBase::Functors.Size();

		// Delete Lambdas
		for (int i = 0; i < FunctorsNum; i++)
		{
			delete DelegateBase::Functors[i];
		}
	}
	
	/** Begin FDelegateBase interface */
	/** Executes all bound functions. */
	virtual void Execute(TInParams... InParams) override
	{
		const auto FunctorsNum = DelegateBase::Functors.Size();
	
		for (int i = 0; i < FunctorsNum; i++)
		{
			DelegateBase::Functors[i]->operator()(InParams ...);
		}
	}
	/** End FDelegateBase interface */

	/** You can make new FFunctorLambda<TReturnType, TInParams...>, Lambdas will be auto destroyed with this delegate. */
	void BindLambda(FFunctorLambda<void, TInParams...>* Lambda)
	{
		DelegateBase::Functors.Push(Lambda);
	}
	template <typename TTypeAuto>
	void BindLambda(TTypeAuto Lambda)
	{
		DelegateBase::Functors.Push(new FFunctorLambda<void, TInParams...>(Lambda));
	}
	
	void UnBindLambda(FFunctorLambda<void, TInParams...>& Lambda)
	{
		DelegateBase::Functors.Remove(Lambda);
	}
	void UnBindLambda(FFunctorLambda<void, TInParams...>&& Lambda)
	{
		DelegateBase::Functors.Remove(Lambda);
	}

	/*
	void BindObject(FFunctorObject<void, TInParams...>&& FunctorObject)
	{
		DelegateBase::Functors.Push(FunctorObject);
	}
	*/
	template<typename TClass>
	void BindObject(TClass* InClassObject, void(TClass::* InFunctionPointer)(TInParams...))
	{
		DelegateBase::Functors.Push(new FFunctorObject<TClass, void, TInParams...>(InClassObject, InFunctionPointer));
	}
	/*
	void UnBindObject(FFunctorObject<void, TInParams...>&& FunctorObject)
	{
		DelegateBase::Functors.Remove(FunctorObject);
	}
	*/
	
	/** Remove function by functor reference. Use with caution. */
	void UnBindAll()
	{
		DelegateBase::Functors.Clear();
	}
	
};
