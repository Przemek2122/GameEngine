// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ECS/Component.h"

class FEntityManager;

class EEntity : public UObject, public IComponentManagerInterface
{
public:
	EEntity(FEntityManager* InEntityManager);
	virtual ~EEntity() override;

	/** Called when starting or creating Entity */
	virtual void BeginPlay();
	/** Called right before destruction */
	virtual void EndPlay();

	/** Called every frame */
	virtual void Tick(float DeltaTime);

	/** Called every frame from engine code. */
	void ReceiveTick(float DeltaTime);

	FEntityManager* GetEntityManagerOwner() const;
	FWindow* GetWindow() const;

protected:
	FEntityManager* EntityManagerOwner;
};
