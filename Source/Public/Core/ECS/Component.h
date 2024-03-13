// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ComponentManagerInterface.h"

class EEntity;

class UComponent : public UObject, public IComponentManagerInterface
{
public:
	UComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UComponent() override;

	virtual void BeginPlay();
	virtual void EndPlay();

	virtual void Tick();
	virtual void Render();

	template<typename TComponentClass>
	void RequireComponent() const
	{
		if (HasOwner())
		{
			TComponentClass* Component = GetOwner()->GetComponentByClass<TComponentClass>();

			if (Component == nullptr)
			{
				LOG_ERROR("Missing component of type: " << typeid(TComponentClass).name());
			}
		}
	}

};
