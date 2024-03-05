#include "CoreEngine.h"
#include "Core/Interfaces/CoreLoop/TickInterface.h"

#include "Engine/EngineTickingManager.h"

FTickInterface::FTickInterface()
	: bIsRegistered(false)
	, RegisteredPhase(ETickPhase::None)
	, TickFunctor(FFunctorObject(this, &FTickInterface::Tick))
{
}

FTickInterface::~FTickInterface()
{
	if (bIsRegistered)
	{
		GEngine->GetEngineTickingManager()->UnRegisterInterface(TickFunctor, RegisteredPhase);
	}
}

void FTickInterface::Register()
{
	if (!bIsRegistered)
	{
		bIsRegistered = true;

		RegisteredPhase = GetTickPhase();

		GEngine->GetEngineTickingManager()->RegisterInterface(TickFunctor, RegisteredPhase);
	}
}
