// Created by Przemys³aw Wiewióra 2020

#pragma once

#include <functional>

template<typename T, typename... U>
size_t getAddress(std::function<T(U...)> Func)
{
	typedef T(fnType)(U...);
	fnType** fnPointer = Func.template target<fnType*>();
	return (size_t)*fnPointer;
}

/**
 * Function storage class. Supports:
 * Lambda
 */
template<typename TReturnType, typename... TInParams> 
class FFunctorLambda : public FFunctorBase<TReturnType, TInParams...>
{
public:
	typedef FFunctorLambda<TReturnType, TInParams...> TSelfType;

	/** Constructor for lamdas */
	template<typename TTypeAuto>
	FFunctorLambda(TTypeAuto InFunction)
		: Function(std::move(InFunction))
	{
	}

	/** Copy function constructor */
	FFunctorLambda(std::function<TReturnType(TInParams ...)>& InFunction)
		: Function(std::move(InFunction))
	{
	}
	/** Move function constructor */
	FFunctorLambda(std::function<TReturnType(TInParams ...)>&& InFunction)
		: Function(std::move(InFunction))
	{
	}

	/*
	friend bool operator==(TSelfType& A, TSelfType& B)
	{
		return (A.Function.target_type() == B.Function.target_type() && getAddress(A.Function) == getAddress(B.Function));
	}
	*/

	bool IsEqual(TSelfType& Other)
	{
		return (Function.target_type() == Other.Function.target_type() && getAddress(Function) == getAddress(Other.Function));
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
