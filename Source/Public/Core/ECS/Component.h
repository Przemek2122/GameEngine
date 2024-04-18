// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ComponentManagerInterface.h"

class EEntity;

/**
 * Base component class.
 * Children should have one of transform interfaces included.
 * Most common would be 'public ITransformChildInterface2D<int>'
 */
class UComponent : public UObject, public IComponentManagerInterface
{
public:
	UComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UComponent() override = default;

	virtual void BeginPlay();
	virtual void EndPlay();

	virtual void Tick(const float DeltaTime);
	virtual void Render();

	virtual void ActivateComponent();
	virtual void DeactivateComponent();

	bool IsComponentActive() const;

	/** Component is owned by entity and this function returns parent */
	EEntity* GetEntity() const;

	UComponent* GetRootComponentOfEntity() const;

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
