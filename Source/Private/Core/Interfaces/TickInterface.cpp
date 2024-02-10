#include "CoreEngine.h"
#include "Core/Interfaces/TickInterface.h"

FTickInterface::FTickInterface()
{
	GEngine->RegisterTickingObject(this);
}

FTickInterface::~FTickInterface()
{
	GEngine->UnRegisterTickingObject(this);
}
