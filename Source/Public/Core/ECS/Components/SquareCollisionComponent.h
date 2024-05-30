// Created by Przemys³aw Wiewióra 2020-2024

#pragma once

#include "CollisionComponent.h"
#include "ECS/BaseComponent.h"

class FSquareCollision;
class FCollisionManager;
class FCollisionBase;

/**
 * Component for collision management
 */
class USquareCollisionComponent : public UCollisionComponent
{
public:
	USquareCollisionComponent(IComponentManagerInterface* InComponentManagerInterface);
	~USquareCollisionComponent() override;

	void Tick(const float DeltaTime) override;

	void Init() override;

protected:
	FSquareCollision* SquareCollision;

};
