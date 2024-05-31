// Created by Przemys�aw Wiewi�ra 2020-2024

#pragma once

#include "ECS/BaseComponent.h"
#include "ECS/Component.h"

class FCollisionManager;
class FCollisionBase;

/**
 * Component for collision management
 */
class UCollisionComponent : public UComponent
{
public:
	UCollisionComponent(IComponentManagerInterface* InComponentManagerInterface);

	void BeginPlay() override;

	void AddCollision(FCollisionBase* CollisionObject);
	void RemoveCollision(FCollisionBase* CollisionObject);

	/** Notify manager about changed collision */
	void OnTransformLocationChanged() override;

	const CArray<FCollisionBase*>& GetCollisionObjectsArray() const;

	//void OnCollision();
	
protected:
	/** @returns collision subsystem. Might be expensive. Try avoid use */
	FCollisionManager* GetCollisionManager() const;

	virtual FVector2D<int> GetLocationForCollision() const;

#if _DEBUG
	static FColorRGBA GetCollisionDebugColor();
#endif

	/** Collision manager cached reference */
	FCollisionManager* CollisionManagerCached;

private:
	/** Array with collision objects */
	CArray<FCollisionBase*> CollisionObjectsArray;

	/** Last location cache */
	FVector2D<int> LastLocationCache;

};
