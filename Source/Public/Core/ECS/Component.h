// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "ComponentManagerInterface.h"

class EEntity;

class UComponent : public UObject, public IComponentManagerInterface
{
public:
	UComponent(IComponentManagerInterface* InComponentManagerInterface);
	virtual ~UComponent() override;
	
};
