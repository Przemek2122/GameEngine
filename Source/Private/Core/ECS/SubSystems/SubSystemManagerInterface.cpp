// Created by Przemys�aw Wiewi�ra 2024

#include "CoreEngine.h"
#include "ECS/SubSystems/SubSystemManagerInterface.h"
#include "ECS/SubSystems/SubSystemInstanceInterface.h"

ISubSystemManagerInterface::~ISubSystemManagerInterface()
{
	for (ContainerInt i = 0; i < SubSystemsArray.Size(); i++)
	{
		delete SubSystemsArray[i];
	}
}

void ISubSystemManagerInterface::TickSubSystems()
{
	for (ISubSystemInstanceInterface* SubSystemInstanceInterface : SubSystemsArray)
	{
		SubSystemInstanceInterface->TickSubSystem();
	}
}

void ISubSystemManagerInterface::RegisterSubSystem(ISubSystemInstanceInterface* InSubSystemInstanceInterface)
{
	SubSystemsArray.Push(InSubSystemInstanceInterface);
}

void ISubSystemManagerInterface::UnRegisterSubSystem(ISubSystemInstanceInterface* InSubSystemInstanceInterface)
{
	SubSystemsArray.Remove(InSubSystemInstanceInterface);
}
