// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "ECS/Entity.h"

enum class EInputState;

class ECameraManager : public EEntity
{
public:
	ECameraManager(FEntityManager* InEntityManager);

	/** Begin EEntity */
	void BeginPlay() override;
	void EndPlay() override;
	void Tick(float DeltaTime) override;
	/** End EEntity */

	void RegisterInput();
	void UnregisterInput();

	void OnMouseMove(FVector2D<int> Location, EInputState);
	void OnMouseRightClick(FVector2D<int> Location, EInputState);

protected:
	FMapManager* WindowMapManager;

	FVector2D<int> CameraLocation;

}; 
