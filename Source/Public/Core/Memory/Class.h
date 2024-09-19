// Created by Przemys³aw Wiewióra 2020-2024

#pragma once

#include "CoreMinimal.h"

/** Do not use directly - Use FClassStorage instead */
class FClass
{
public:
    virtual ~FClass() = default;

	virtual std::string GetClassName() const = 0;
};

/** Do not use directly - Use FClassStorage instead */
template<typename TType, typename... TArgs>
class TClass : public FClass
{
public:
	/** Create instance */
	virtual void* Allocate(TArgs... Args) const
	{
        return new TType(Args...);
    }

	std::string GetClassName() const override
	{
		return "please fix xD";
		//return typeid(TType).name();
	}
};

/** Storage class for storing TClass */
template<typename TBaseClass, typename... TArgs>
class FClassStorage
{
public:
	FClassStorage()
		: StoredClass(nullptr)
	{
	}

	FClassStorage(const FClassStorage& ClassStorage)
		: StoredClass(ClassStorage.StoredClass)
	{
		
	}
	FClassStorage(const FClassStorage&& ClassStorage) noexcept
		: StoredClass(ClassStorage.StoredClass)
	{
		
	}

	virtual ~FClassStorage()
	{
	}

	FClassStorage& operator=(const FClassStorage& Other)
	{
		StoredClass = Other.StoredClass;

		return *this;
	}

	/** Set stored class. */
	template<typename TType>
	void Set()
	{
		// Perform check for base class, it has to be child of TType
		static_assert(std::is_base_of_v<TBaseClass, TType>, "FClassStorage::Set given class does not inherit from TBaseClass");

		StoredClass = std::make_shared<TClass<TType, TArgs...>>();
	}

	/**
	 * Function for actually creating class instance.
	 *
	 * @Note: Might return null if class is not set.
	 * @Note: Will not be garbage collected any way so make sure to delete it after use!
	 */
	_NODISCARD TBaseClass* Allocate(TArgs... Args)
	{
		if (StoredClass == nullptr)
		{
			Set<TBaseClass>();
		}

		return static_cast<TBaseClass*>(StoredClass->Allocate(Args...));
	}

	/** @returns true if any type is in storage */
	_NODISCARD bool IsSet() const
	{
		return StoredClass != nullptr;
	}

	template<typename TType>
	_NODISCARD bool IsSame()
	{
		if (StoredClass == nullptr)
		{
			return false;
		}

		return dynamic_cast<TClass<TType>*>(StoredClass) != nullptr;
	}

	std::string GetClassName() const
	{
		if (StoredClass == nullptr)
		{
			return "nullptr";
		}

		return StoredClass->GetClassName();
	}

	void Reset()
	{
		StoredClass = nullptr;
	}

protected:
	std::shared_ptr<TClass<TBaseClass, TArgs...>> StoredClass;

};
