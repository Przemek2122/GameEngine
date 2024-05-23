// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"

class ISubSystemInstanceInterface;

/**
 * Interface for SubSystem manager
 */
class ISubSystemParentInterface
{
public:
	ISubSystemParentInterface();
	virtual ~ISubSystemParentInterface();

	void TickSubSystems();

	/**
	 * Get SubSystem by given class.
	 * @tparam TClass Class to search for.
	 * @return Class if found. nullptr otherwise.
	 */
	template<typename TClass>
	TClass* GetSubSystemByClass() const
	{
		static_assert(std::is_base_of_v<TClass, ISubSystemInstanceInterface>, "SubSystem must inherit from ISubSystemInstanceInterface.");

		TClass* Object = nullptr;
			
		for (ISubSystemInstanceInterface* SubSystemInstanceInterface : SubSystemsArray)
		{
			if (TClass* CastedObject = dynamic_cast<TClass>(SubSystemInstanceInterface))
			{
				Object = CastedObject;
			}
		}

		return Object;
	}

	/** Create subsystem by given class with optional parameters */
	/*
	template<typename TClass, typename... TInParams>
	TClass* CreateSubSystem(TInParams... InParams) const
	{
		TClass* NewEntity = new TClass(InParams ...);

		return NewEntity;
	}
	*/

	ISubSystemInstanceInterface* CreateSubSystem(FClassStorage<ISubSystemInstanceInterface> Class);

	void RegisterSubSystem(ISubSystemInstanceInterface* InSubSystemInstanceInterface);
	void UnRegisterSubSystem(ISubSystemInstanceInterface* InSubSystemInstanceInterface);

protected:
	CArray<ISubSystemInstanceInterface*> SubSystemsArray;

};
