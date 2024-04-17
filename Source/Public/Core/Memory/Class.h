// Created by Przemys³aw Wiewióra 2020-2024

#pragma once

#include "CoreMinimal.h"

/** Do not use directly - Use FClassStorage instead */
class FClass
{
public:
    virtual ~FClass() = default;

	virtual void* Allocate() const = 0;
	virtual std::string GetClassName() const = 0;
};

/** Do not use directly - Use FClassStorage instead */
template<typename TType>
class TClass : public FClass
{
public:
	/** Create instance */
	void* Allocate() const override
	{
        return new TType;
    }

	std::string GetClassName() const override
	{
		return typeid(TType).name();
	}
};

/** Storage class for storing TClass */
template<typename TBaseClass>
class FClassStorage
{
public:
	FClassStorage()
		: StoredClass(nullptr)
	{
	}

	FClassStorage(FClassStorage& ClassStorage) = delete;
	FClassStorage(FClassStorage&& ClassStorage) = delete;

	~FClassStorage()
	{
		delete StoredClass;
	}

	/** Set stored class. */
	template<typename TType>
	void Set()
	{
		// Perform check for base class, it has to be child of TType
		static_assert(std::is_base_of_v<TBaseClass, TType>, "FClassStorage::Set given class does not inherit from TBaseClass");

		delete StoredClass;

		StoredClass = new TClass<TType>;
	}

	/**
	 * Function for actually creating class instance.
	 *
	 * @Note: Might return null if class is not set.
	 * @Note: Will not be garbage collected any way so make sure to delete it after use!
	 */
	_NODISCARD TBaseClass* Allocate()
	{
		if (StoredClass == nullptr)
		{
			Set<TBaseClass>();
		}

		return static_cast<TBaseClass*>(StoredClass->Allocate());
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
		delete StoredClass;

		StoredClass = nullptr;
	}

protected:
	FClass* StoredClass;

};
