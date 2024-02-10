#include "CoreEngine.h"
#include "Core/Interfaces/CoreLoop/TickInterface.h"

FTickInterface::FTickInterface()
{
	GEngine->RegisterTickingObject(this);
}

FTickInterface::~FTickInterface()
{
	GEngine->UnRegisterTickingObject(this);
}
