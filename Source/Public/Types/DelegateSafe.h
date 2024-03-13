// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "DelegateBase.h"
#include "FunctorLambda.h"
#include "FunctorObject.h"

/**
 * Delegate extending base with bind and unbind and UnBindAll.
 *
 * @Note: When passing by parameter use reference or pointer, otherwise it will not compile.
 * @Note: All functions passed in are deleted at end of this object life.
 */
template<typename TReturnType = void, typename... TInParams>
class FDelegateSafe : public FDelegateBase<TReturnType, std::shared_ptr<FFunctorBase<TReturnType, TInParams ...>>, TInParams...>
{
public:
	using FunctorType = FFunctorBase<TReturnType, TInParams ...>;
	using DelegateBase = FDelegateBase<TReturnType, std::shared_ptr<FunctorType>, TInParams...>;

	using FunctorLambdaType = FFunctorLambda<TReturnType, TInParams...>;
	using FunctorObjectType = FFunctorObject<TReturnType, TInParams...>;

	// Default constructor
	FDelegateSafe() = default;

	// Copy constructor - Forbidden, not efficient + causes double deletion of Functors
	// Could be fixed by creating flag telling destructor if Functors are moved or not
	FDelegateSafe(const FDelegateSafe& InDelegate) = delete;

	// Move constructor
	FDelegateSafe(FDelegateSafe&& InDelegate) noexcept
	{
		DelegateBase::Functors = std::move(InDelegate.DelegateBase::Functors);
	}

	// Copy operator - Forbidden, not efficient + causes double deletion of Functors
	// Could be fixed by creating flag telling destructor if Functors are moved or not
	FDelegateSafe& operator=(const FDelegateSafe& InDelegate) = delete;

	// Copy assignment operator
	FDelegateSafe& operator=(FDelegateSafe&& InDelegate) noexcept
	{
		DelegateBase::Functors = std::move(InDelegate.DelegateBase::Functors);

		return *this;
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

	/** You can make new FFunctorLambda<TReturnType, TInParams...> */
	void BindLambda(FunctorLambdaType& Lambda)
	{
		DelegateBase::Functors.Push(std::make_shared<FunctorLambdaType>(Lambda));
	}

	/** Bind C++ Lambda - Fast but not recommended - Cannot be unbind */
	template <typename TTypeAuto>
	void BindLambdaRaw(TTypeAuto Lambda)
	{
		DelegateBase::Functors.Push(std::make_shared<FunctorLambdaType>(Lambda));
	}

	void UnBindLambda(FunctorLambdaType& Lambda)
	{
		auto Index = INDEX_NONE;

		for (int i = 0; i < DelegateBase::Functors.Size(); i++)
		{
			if (Lambda.IsEqual(DelegateBase::Functors[i].get()))
			{
				Index = i;

				break;
			}
		}

		//if (Index != INDEX_NONE)
		//{
		//	DelegateBase::Functors.RemoveAt(Index);
		//}
	}

	/*
	template <typename TTypeAuto>
	void UnBindLambda(TTypeAuto& Lambda)
	{
		int Index = INDEX_NONE;

		for (int i = 0; i < DelegateBase::Functors.Size(); i++)
		{
			if (DelegateBase::Functors[i] == Lambda)
			{
				Index = i;

				break;
			}
		}

		if (Index != INDEX_NONE)
		{
			DelegateBase::Functors.RemoveAt(Index);
		}
	}
	*/

	int FindIndexOfLambda(FunctorLambdaType& Lambda)
	{
		int Index = INDEX_NONE;

		for (int i = 0; i < DelegateBase::Functors.Size(); i++)
		{
			if (Lambda == DelegateBase::Functors[i].get())
			{
				Index = i;

				break;
			}
		}

		return Index;
	}

	/** Remove function by functor reference. Use with caution. */
	void UnBindAll()
	{
		DelegateBase::Functors.Clear();
	}
	
};
