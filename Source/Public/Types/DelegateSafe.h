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
	FDelegateSafe(const FDelegateSafe& InDelegate) = delete;

	// Move constructor
	FDelegateSafe(FDelegateSafe&& InDelegate) noexcept
	{
		DelegateBase::Functors = std::move(InDelegate.DelegateBase::Functors);
	}

	// Copy operator - Forbidden, not efficient + causes double deletion of Functors
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

	/** Bind C++ raw Lambda - Fast but not recommended */
	template <typename TTypeAuto>
	void BindLambda(TTypeAuto Lambda)
	{
		DelegateBase::Functors.Push(std::make_shared<FunctorLambdaType>(Lambda));
	}

	/** You can make new FFunctorLambda<TReturnType, TInParams...> */
	void BindLambda(FunctorLambdaType& Lambda)
	{
		DelegateBase::Functors.Push(std::make_shared<FunctorLambdaType>(Lambda));
	}

	/** Remove lambda, only by previously added type (function pointer must be equal) */
	void UnBindLambda(FunctorLambdaType& Lambda)
	{
		int Index = FindIndexOfLambda(Lambda);

		if (Index != INDEX_NONE)
		{
			DelegateBase::Functors.RemoveAt(Index);
		}
	}

	/** Remove C++ raw Lambda - Fast but not recommended */
	template <typename TTypeAuto>
	void UnBindLambda(TTypeAuto& Lambda)
	{
		std::shared_ptr<FunctorLambdaType> TemporarySharedLambdaPointer = std::make_shared<FunctorLambdaType>(Lambda);

		int Index = FindIndexOfLambda(*TemporarySharedLambdaPointer);

		if (Index != INDEX_NONE)
		{
			DelegateBase::Functors.RemoveAt(Index);
		}
	}

	/** Remove all bound functions. */
	void UnBindAll()
	{
		DelegateBase::Functors.Clear();
	}

protected:
	int FindIndexOfLambda(FunctorLambdaType& Lambda)
	{
		int Index = INDEX_NONE;

		for (int i = 0; i < DelegateBase::Functors.Size(); i++)
		{
			std::shared_ptr<FunctorType>& Functor = DelegateBase::Functors[i];

			// Quick check if it is lambda - Fast
			if (Functor->GetFunctorType() == EFunctorType::FT_LAMBDA)
			{
				FunctorLambdaType* FunctorLambda = dynamic_cast<FunctorLambdaType*>(Functor.get());

				if (FunctorLambda->IsEqual(Lambda))
				{
					Index = i;

					break;
				}
			}
		}

		return Index;
	}
	
};
