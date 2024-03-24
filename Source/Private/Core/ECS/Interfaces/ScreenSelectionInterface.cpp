#include "CoreEngine.h"
#include "ECS/Interfaces/ScreenSelectionInterface.h"
#include "ECS/Entities/ScreenSelectionEntity.h"

/** Static for performance */
static EScreenSelectionEntity* ScreenSelectionEntityStatic;

IScreenSelectionInterface::IScreenSelectionInterface()
	: bIsRegistered(false)
	, bIsSelected(false)
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
			if (ScreenSelectionEntityStatic != nullptr)
			{
				ScreenSelectionEntityStatic->RegisterScreenSelectable(this);
			}
			else
			{
				ScreenSelectionEntityStatic = InEntityManager->CreateEntity<EScreenSelectionEntity>();

				ScreenSelectionEntityStatic->RegisterScreenSelectable(this);

				InEntityManager->OnEntityManagerDestroyed.BindStatic(&IScreenSelectionInterface::ResetScreenSelection);
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

void IScreenSelectionInterface::NativeSelect()
{
	if (!bIsSelected)
	{
		OnSelect();
	}
}

void IScreenSelectionInterface::NativeDeselect()
{
	if (bIsSelected)
	{
		OnDeSelect();
	}
}

EScreenSelectionEntity* IScreenSelectionInterface::GetScreenSelectionEntityStatic()
{
	return ScreenSelectionEntityStatic;
}

void IScreenSelectionInterface::ResetScreenSelection()
{
	ScreenSelectionEntityStatic = nullptr;
}
