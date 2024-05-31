// Created by Przemys�aw Wiewi�ra 2020-2024

#pragma once

#include "CollisionComponent.h"
#include "ECS/BaseComponent.h"

class FCircleCollision;
class FCollisionManager;
class FCollisionBase;

/**
 * Component for collision management
 */
class UCircleCollisionComponent : public UCollisionComponent
{
public:
	UCircleCollisionComponent(IComponentManagerInterface* InComponentManagerInterface);
	~UCircleCollisionComponent() override;

	void BeginPlay() override;
	void Render() override;

	void OnTransformLocationChanged() override;

protected:
	virtual int GetCircleRadius() const;

private:
	FCircleCollision* CircleCollision;

};
