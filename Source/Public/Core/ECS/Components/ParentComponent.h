// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ECS/BaseComponent.h"
#include "Interfaces/TransformInterface2D.h"

/**
 * Component for handling transform of the entity
 * Every component which should have transform should inherit from this class
 */
class UParentComponent : public UBaseComponent, public ITransformParentInterface2D<int>
{
public:
	UParentComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UParentComponent() override = default;

	/** Begin UBaseComponent */
	void BeginPlay() override;
	void OnComponentCreated(const std::string& ComponentName, UBaseComponent* NewComponent) override;
	void OnComponentDestroy(const std::string& ComponentName, UBaseComponent* OldComponent) override;
	/** End UBaseComponent */

	FVector2D<float> GetForwardVector() const;
	FVector2D<float> GetRightVector() const;

	/** Final location - returns location in center of object */
	FVector2D<int> GetLocationCenter() const;

	void SetSize(const FVector2D<int> NewSize);
	FVector2D<int> GetSize() const;

protected:
	FVector2D<int> Size;

};