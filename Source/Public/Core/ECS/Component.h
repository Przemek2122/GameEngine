// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ComponentManagerInterface.h"

class EEntity;

class UComponent : public UObject, public IComponentManagerInterface
{
public:
	UComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UComponent() override = default;

	virtual void BeginPlay();
	virtual void EndPlay();

	virtual void Tick();
	virtual void Render();

	virtual void ActivateComponent();
	virtual void DeactivateComponent();

	bool IsComponentActive() const;

	template<typename TComponentClass>
	TComponentClass* RequireComponent() const
	{
		if (HasOwner())
		{
			TComponentClass* Component = GetOwner()->GetComponentByClass<TComponentClass>();

			if (Component != nullptr)
			{
				return Component;
			}
			else
			{
				LOG_ERROR("Missing component of type: " << typeid(TComponentClass).name());
			}
		}

		return nullptr;
	}

protected:
	bool bIsComponentActive;


};
