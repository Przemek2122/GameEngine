// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/SubSystems/SubSystemParentInterface.h"
#include "ECS/SubSystems/SubSystemInstanceInterface.h"

ISubSystemParentInterface::ISubSystemParentInterface() = default;

ISubSystemParentInterface::~ISubSystemParentInterface()
{
	for (const ISubSystemInstanceInterface* SubSystemInstanceInterface : SubSystemsArray)
	{
		delete SubSystemInstanceInterface;
	}
}

void ISubSystemParentInterface::TickSubSystems()
{
	for (ISubSystemInstanceInterface* SubSystemInstanceInterface : SubSystemsArray)
	{
		SubSystemInstanceInterface->TickSubSystem();
	}
}

ISubSystemInstanceInterface* ISubSystemParentInterface::CreateSubSystem(FClassStorage<ISubSystemInstanceInterface> Class)
{
	ISubSystemInstanceInterface* NewObject = Class.Allocate();

	SubSystemsArray.Push(NewObject);

	return NewObject;
}

void ISubSystemParentInterface::RegisterSubSystem(ISubSystemInstanceInterface* InSubSystemInstanceInterface)
{
	SubSystemsArray.Push(InSubSystemInstanceInterface);
}

void ISubSystemParentInterface::UnRegisterSubSystem(ISubSystemInstanceInterface* InSubSystemInstanceInterface)
{
	SubSystemsArray.Remove(InSubSystemInstanceInterface);
}
