#include "CoreEngine.h"
#include "Core/Interfaces/CoreLoop/RenderInterface.h"

#include "Engine/EngineRenderingManager.h"

FRenderInterface::FRenderInterface()
	: bIsRegistered(false)
	, RegisteredPhase(ERenderPhase::None)
	, RenderFunctor(FFunctorObject(this, &FRenderInterface::Render))
{
	Register();
}

FRenderInterface::~FRenderInterface()
{
	if (bIsRegistered)
	{
		GEngine->GetEngineRenderingManager()->UnRegisterInterface(RenderFunctor, RegisteredPhase);
	}
}

void FRenderInterface::Register()
{
	if (!bIsRegistered)
	{
		bIsRegistered = true;

		RegisteredPhase = GetRenderPhase();

		GEngine->GetEngineRenderingManager()->RegisterInterface(RenderFunctor, RegisteredPhase);
	}
}
