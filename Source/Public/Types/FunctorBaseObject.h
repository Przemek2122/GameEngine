// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

/**
 * C++ Delegate 
 * https://stackoverflow.com/questions/9568150/what-is-a-c-delegate
 */
template<typename TReturnType = void, typename TInParams = void()>
class FFunctorBase
{
public:
	/** For static functions */
	FFunctorBase(TReturnType& InFunctionPointer)
		: FunctionPointer(InFunctionPointer)
		, ClassObject(nullptr)
	{
	}
	/** For calling function on an object */
	FFunctorBase(TReturnType& InFunctionPointer, void* ClassObject)
		: FunctionPointer(InFunctionPointer)
		, ClassObject(ClassObject)
	{
	}

	/** This function calls stored function */
	TReturnType operator()(TInParams Params)
    {
		return (*FunctionPointer)();;
    }
	/** Assign function to this. */
	FFunctorBase& operator=(FFunctorBase const& InFunctor)
    {
		FunctionPointer = InFunctor.FunctionPointer;
		ClassObject = InFunctor.ClassObject;
		
		return this;
    }

	_NODISCARD bool IsBound() const
	{
		return FunctionPointer != nullptr;
	}
	_NODISCARD bool IsBoundClassObject() const
	{
		return ClassObject != nullptr;
	}

protected:
	TReturnType (*FunctionPointer)(TInParams);
	void* ClassObject;
};
