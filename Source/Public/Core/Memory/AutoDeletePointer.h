// Created by Przemys³aw Wiewióra 2020

#pragma once
#include "CoreMinimal.h"

/**
 * class managing other class pointer lifecycle
 */
template<typename TTypeToStore>
class FAutoDeletePointer
{
public:
	/** Normal constructor - Create object to store */
	template<typename ...TInParams>
	explicit FAutoDeletePointer(TInParams... Params)
		: StoredObject(new TTypeToStore(Params...))
		, bHasClass(true)
	{
	}

	/** Copy constructor - Makes previous FAutoDeletePointer not usable anymore. */
	FAutoDeletePointer(FAutoDeletePointer& OtherAutoDeletePointer) noexcept 
		: StoredObject(OtherAutoDeletePointer.StoredObject)
		, bHasClass(true)
	{
		OtherAutoDeletePointer.MarkAsMoved();
	}

	/** Move constructor - Makes previous FAutoDeletePointer not usable anymore. */
	FAutoDeletePointer(FAutoDeletePointer&& OtherAutoDeletePointer) noexcept 
		: StoredObject(OtherAutoDeletePointer.StoredObject)
		, bHasClass(true)
	{
		OtherAutoDeletePointer.MarkAsMoved();
	}

	/** Destructor - Destroy stored class. */
	virtual ~FAutoDeletePointer()
	{
		if (bHasClass)
		{
			delete StoredObject;
		}
	}

	/** Move assignment operator - Currently we do not have a constructor supporting it. */
	FAutoDeletePointer& operator=(FAutoDeletePointer&& OtherAutoDeletePointer) noexcept
	{
		// We can not move class if there is already a class.
		ENSURE_VALID(this->StoredObject == nullptr);

		this->StoredObject = OtherAutoDeletePointer.StoredObject;

		OtherAutoDeletePointer.MarkAsMoved();

        return *this;
    }

	/** Copy assignment operator. */
	FAutoDeletePointer& operator=(FAutoDeletePointer OtherAutoDeletePointer) = delete;

	TTypeToStore* Get() const
	{
#if _DEBUG
		// This pointer was moved to other and should not be used!
		if (ENSURE_VALID(bHasClass))
		{
			if (ENSURE_VALID(StoredObject != nullptr))
			{
				return StoredObject;
			}
			else
			{
				return nullptr;
			}
		}
#endif

		return StoredObject;
	}

	/**
	 * Get stored element.
	 */
	virtual TTypeToStore* operator->() const
	{
		return Get();
	}

private:
	/** Used by 'Move constructor' */
	void MarkAsMoved()
	{
		// Moving already moved pointer or moving pointer without class.
		ENSURE_VALID(bHasClass);

		bHasClass = false;
		StoredObject = nullptr;
	}
protected:
	/** Our managed class. */
	TTypeToStore* StoredObject;
private:
	/** This property indicates if this @Store pointer was moved and should not be destroyed. */
	bool bHasClass;
};
