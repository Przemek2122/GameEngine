// Created by Przemys³aw Wiewióra 2020-2024

#pragma once

#include "ECS/BaseComponent.h"

class FCollisionManager;
class FCollisionBase;

/**
 * Component for collision management
 */
class UCollisionComponent : public UBaseTransformComponent
{
public:
	UCollisionComponent(IComponentManagerInterface* InComponentManagerInterface);

	void Init() override;

	void AddCollision(FCollisionBase* CollisionObject);
	void RemoveCollision(FCollisionBase* CollisionObject);

	/** Notify manager about changed collision */
	void OnTransformLocationChanged(const ELocationChangeType LocationChangeType) override;

protected:
	/** @returns collision subsystem. Might be expensive. Try avoid use */
	FCollisionManager* GetCollisionManager() const;

private:
	/** Array with collision objects */
	CArray<FCollisionBase*> CollisionObjectsArray;

	/** Collision manager cached reference */
	FCollisionManager* CollisionManagerCached;

};
