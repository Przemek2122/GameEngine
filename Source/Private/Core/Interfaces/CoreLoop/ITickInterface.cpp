#include "CoreEngine.h"
#include "Core/Interfaces/CoreLoop/ITickInterface.h"

#include "Engine/EngineTickingManager.h"

ITickInterface::ITickInterface()
	: bIsRegistered(false)
	, RegisteredPhase(ETickPhase::None)
	, TickFunctor(FFunctorObject(this, &ITickInterface::Tick))
{
}

ITickInterface::~ITickInterface()
{
	if (bIsRegistered)
	{
		GEngine->GetEngineTickingManager()->UnRegisterInterface(TickFunctor, RegisteredPhase);
	}
}

void ITickInterface::Register()
{
	if (!bIsRegistered)
	{
		bIsRegistered = true;

		RegisteredPhase = GetTickPhase();

		GEngine->GetEngineTickingManager()->RegisterInterface(TickFunctor, RegisteredPhase);
	}
}
