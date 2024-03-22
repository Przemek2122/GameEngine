// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ECS/Component.h"
#include "Interfaces/TransformInterface2D.h"

/**
 * Component for handling transform of the entity
 */
class UTransformComponent : public UComponent, public ITransformInterface2D<int>
{
public:
	UTransformComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UTransformComponent() override = default;

	/** Begin UComponent */
	void BeginPlay() override;
	void EndPlay() override;
	/** End UComponent */

	FVector2D<int> GetSize() const;

	void OnTransformLocationChanged(const ELocationChangeType LocationChangeType) override;

	/** Called from map using delegate each time map location (camera position) is changed */
	void OnMapLocationChanged(FVector2D<int> NewLocation);

	/** Called when location is changed - Either by unit or map movement */
	FDelegate<void, FVector2D<int>> OnLocationChanged;

protected:
	FVector2D<int> Size;

};