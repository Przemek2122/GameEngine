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
template<typename TReturnType = void, typename... TInParams>
class FDelegate : public FDelegateBase<TReturnType, TInParams...>
{
using DelegateBase = FDelegateBase<TReturnType, TInParams...>;
	
public:
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
	/** Executes all bound functions using Lambda to define how it executes. */
	using ExecuteByLambdaDefinitionFunctor = FFunctorBase<TReturnType, TInParams...>;
	using ExecuteByLambdaDefinition = FFunctorLambda<void, ExecuteByLambdaDefinitionFunctor*, TInParams...>;
	virtual void ExecuteByLambda(ExecuteByLambdaDefinition Lambda, TInParams... InParams)
	{
		const auto FunctorsNum = DelegateBase::Functors.Size();

		for (int i = 0; i < FunctorsNum; i++)
		{
			Lambda(DelegateBase::Functors[i], InParams ...);
		}
	}
	/** End FDelegateBase interface */

	/** You can make new FFunctorLambda<TReturnType, TInParams...>, Lambdas will be auto destroyed with this delegate. */
	void BindLambda(FFunctorLambda<TReturnType, TInParams...>* Lambda)
	{
		DelegateBase::Functors.Push(Lambda);
	}
	template <typename TTypeAuto>
	void BindLambda(TTypeAuto Lambda)
	{
		// @TODO Could be memory leak
		DelegateBase::Functors.Push(new FFunctorLambda<TReturnType, TInParams...>(Lambda));
	}
	
	void UnBindLambda(FFunctorLambda<TReturnType, TInParams...>& Lambda)
	{
		DelegateBase::Functors.Remove(Lambda);
	}
	void UnBindLambda(FFunctorLambda<TReturnType, TInParams...>&& Lambda)
	{
		DelegateBase::Functors.Remove(Lambda);
	}

	/*
	 * Example on how to bind your object
	 * OnYourDelegateChanged.BindObject(this, &FYourClass::YourFunctionName);
	 * Real example from code:
	 * OnWidgetOrderChanged.BindObject(this, &FWidgetInputManager::ChangeOrder);
	*/
	template<typename TClass>
	void BindObject(TClass* InClassObject, TReturnType(TClass::* InFunctionPointer)(TInParams...))
	{
		DelegateBase::Functors.Push(new FFunctorObject<TClass, TReturnType, TInParams...>(InClassObject, InFunctionPointer));
	}

	template<typename TClass>
	void UnBindObject(TClass* InClassObject, TReturnType(TClass::* InFunctionPointer)(TInParams...))
	{
		int Index;
		const bool bIsFound = DelegateBase::Functors.FindByLambda([&](FFunctorBase<TReturnType, TInParams...>* Object)
		{
			if (FFunctorObject<TClass, TReturnType, TInParams...>* FunctorObject = dynamic_cast<FFunctorObject<TClass, TReturnType, TInParams...>*>(Object))
			{
				if (FunctorObject->GetClassObject() == InClassObject && FunctorObject->IsFunctionPointerSame(InFunctionPointer))
				{
					return true;
				}
			}

			return false;
		}, Index);

		if (bIsFound)
		{
			delete DelegateBase::Functors[Index];

			DelegateBase::Functors.RemoveAt(Index);
		}
	}
	
	/** Remove function by functor reference. Use with caution. */
	void UnBindAll()
	{
		// Clean DelegateBase::Functors
		for (int i = 0; i < DelegateBase::Functors.Size(); i++)
		{
			delete DelegateBase::Functors[i];
		}

		DelegateBase::Functors.Clear();
	}
	
};
