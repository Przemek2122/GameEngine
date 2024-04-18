// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ECS/Component.h"
#include "Interfaces/TransformInterface2D.h"

/**
 * Component for handling transform of the entity
 * Every component which should have transform should inherit from this class
 */
class UBaseTransformComponent : public UComponent, public ITransformParentInterface2D<int>
{
public:
	UBaseTransformComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UBaseTransformComponent() override = default;

	/** Begin UComponent */
	void BeginPlay() override;
	void EndPlay() override;

	void OnComponentCreated(const std::string& ComponentName, UComponent* NewComponent) override;
	void OnComponentDestroy(const std::string& ComponentName, UComponent* OldComponent) override;
	/** End UComponent */

	/** Final location - returns location in center of object */
	FVector2D<int> GetLocationCenter() const;

	FVector2D<int> GetSize() const;

	/** Called from map using delegate each time map location (camera position) is changed */
	void OnMapLocationChanged(FVector2D<int> NewLocation);

protected:
	FVector2D<int> Size;

};