// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

/**
 * Function storage class. Supports:
 * Function on objects
 */
template<typename TClass, typename TReturnType, typename... TInParams>
class FFunctorObject : public FFunctorBase<TReturnType, TInParams...>
{
public:
	FFunctorObject(TClass* InClassObject, TReturnType (TClass::*InFunctionPointer)(TInParams...))
		: FunctionPointer(InFunctionPointer)
		, ClassObject(InClassObject)
	{
	}
	
	/** Begin FFunctorBase interface */
	TReturnType operator()(TInParams... Params) override
    {
		if (FunctionPointer != nullptr && ClassObject != nullptr)
		{
			return (ClassObject->*FunctionPointer)(Params...);
		}

		return TReturnType();
    }

	_NODISCARD bool IsValid() const override
	{
		return (FunctionPointer != nullptr && ClassObject != nullptr);
	}

	_NODISCARD EFunctorType GetFunctorType() const override { return EFunctorType::FT_OBJECT; }
	/** End FFunctorBase interface */

	FFunctorObject& operator=(FFunctorObject const& InFunctor)
    {
		FunctionPointer = InFunctor.FunctionPointer;
		ClassObject = InFunctor.ClassObject;
		
		return this;
    }

	bool operator==(FFunctorObject const& OtherFunctor)
	{
		return (ClassObject == OtherFunctor.ClassObject && FunctionPointer == OtherFunctor.FunctionPointer);
	}

	bool IsFunctionPointerSame(TReturnType(TClass::* InFunctionPointer)(TInParams...)) const
	{
		return (FunctionPointer == InFunctionPointer);
	}

	/** Stored object which has above function. */
	TClass* GetClassObject() const
	{
		return ClassObject;
	}

protected:
	/** Stored function. */
	TReturnType (TClass::*FunctionPointer)(TInParams ...);
	
	/** Stored object which has above function. */
	TClass* ClassObject;
};
