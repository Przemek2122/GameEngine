// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/SubSystems/SubSystemInstanceInterface.h"

ISubSystemInstanceInterface::ISubSystemInstanceInterface(ISubSystemParentInterface* InSubSystemParentInterface)
	: SubSystemParentInterface(InSubSystemParentInterface)
{
	SubSystemParentInterface->RegisterSubSystem(this);
}

ISubSystemInstanceInterface::~ISubSystemInstanceInterface()
{
	SubSystemParentInterface->UnRegisterSubSystem(this);
}

void ISubSystemInstanceInterface::TickSubSystem()
{
}
