// Created by Przemys�aw Wiewi�ra 2020

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
		return (ClassObject->*FunctionPointer)(Params...);
    }
	_NODISCARD virtual bool IsValid() const override
	{
		return (FunctionPointer != nullptr && ClassObject != nullptr);
	}
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

protected:
	/** Stored function. */
	TReturnType (TClass::*FunctionPointer)(TInParams ...);
	
	/** Stored object which has above function. */
	TClass* ClassObject;
};
