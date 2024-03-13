// Created by Przemys�aw Wiewi�ra 2020

#pragma once

#include "ComponentManagerInterface.h"

class EEntity;

class UComponent : public UObject, public IComponentManagerInterface
{
public:
	UComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UComponent() override;

	virtual void BeginPlay();
	virtual void EndPlay();

	virtual void Tick();
	virtual void Render();

};
