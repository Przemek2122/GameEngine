#include "CoreEngine.h"
#include "ECS/Interfaces/ScreenSelectionInterface.h"
#include "ECS/Entities/ScreenSelectionEntity.h"

/** Static for performance */
static EScreenSelectionEntity* ScreenSelectionEntityStatic;

IScreenSelectionInterface::IScreenSelectionInterface()
	: bIsRegistered(false)
	, EntityManager(nullptr)
{
}

IScreenSelectionInterface::~IScreenSelectionInterface()
{
	UnregisterFromScreenSelection();
}

void IScreenSelectionInterface::RegisterToScreenSelection(FEntityManager* InEntityManager)
{
	if (!bIsRegistered)
	{
		if (InEntityManager != nullptr)
		{
			EntityManager = InEntityManager;

			if (ScreenSelectionEntityStatic != nullptr)
			{
				ScreenSelectionEntityStatic->RegisterScreenSelectable(this);
			}
			else
			{
				ScreenSelectionEntityStatic = InEntityManager->CreateEntity<EScreenSelectionEntity>();

				ScreenSelectionEntityStatic->RegisterScreenSelectable(this);
			}
		}

		bIsRegistered = true;
	}
}

void IScreenSelectionInterface::UnregisterFromScreenSelection()
{
	if (bIsRegistered && ScreenSelectionEntityStatic != nullptr)
	{
		ScreenSelectionEntityStatic->UnRegisterScreenSelectable(this);
	}
}

EScreenSelectionEntity* IScreenSelectionInterface::GetScreenSelectionEntityStatic()
{
	return ScreenSelectionEntityStatic;
}
