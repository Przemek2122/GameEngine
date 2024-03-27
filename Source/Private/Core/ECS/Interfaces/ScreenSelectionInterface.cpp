#include "CoreEngine.h"
#include "ECS/Interfaces/ScreenSelectionInterface.h"
#include "ECS/Entities/ScreenSelectionEntity.h"

IScreenSelectionInterface::IScreenSelectionInterface()
	: bIsRegistered(false)
	, bIsSelected(false)
{
}

IScreenSelectionInterface::~IScreenSelectionInterface()
{
	UnregisterFromScreenSelection();
}

void IScreenSelectionInterface::RegisterToScreenSelection(const FEntityManager* InEntityManager)
{
	if (!bIsRegistered)
	{
		if (InEntityManager != nullptr)
		{
			if (ScreenSelectionEntity != nullptr)
			{
				ScreenSelectionEntity->RegisterScreenSelectable(this);
			}
			else
			{
				// Try to find ScreenSelectionEntity
				ScreenSelectionEntity = InEntityManager->GetEntityByType<EScreenSelectionEntity>();
				if (ScreenSelectionEntity != nullptr)
				{
					ScreenSelectionEntity->RegisterScreenSelectable(this);
				}
			}
		}

		bIsRegistered = true;
	}
}

void IScreenSelectionInterface::UnregisterFromScreenSelection()
{
	if (bIsRegistered && ScreenSelectionEntity != nullptr)
	{
		ScreenSelectionEntity->UnRegisterScreenSelectable(this);
	}
}

void IScreenSelectionInterface::NativeSelect()
{
	if (!bIsSelected)
	{
		OnSelect();

		bIsSelected = true;
	}
}

void IScreenSelectionInterface::NativeDeselect()
{
	if (bIsSelected)
	{
		OnDeSelect();

		bIsSelected = false;
	}
}
