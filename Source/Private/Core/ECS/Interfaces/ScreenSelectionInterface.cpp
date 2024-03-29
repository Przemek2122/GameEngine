#include "CoreEngine.h"
#include "ECS/Interfaces/ScreenSelectionInterface.h"
#include "ECS/Entities/ScreenSelectionEntity.h"

IScreenSelectionInterface::IScreenSelectionInterface()
	: ScreenSelectionEntity(nullptr)
	, bIsRegistered(false)
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
				RegisterToScreenSelectionInternal();
			}
			else
			{
				// Try to find ScreenSelectionEntity
				ScreenSelectionEntity = InEntityManager->GetEntityByType<EScreenSelectionEntity>();
				if (ScreenSelectionEntity != nullptr)
				{
					RegisterToScreenSelectionInternal();
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

		bIsRegistered = false;
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

void IScreenSelectionInterface::RegisterToScreenSelectionInternal()
{
	ScreenSelectionEntity->RegisterScreenSelectable(this);

	ScreenSelectionEntity->OnEndPlay.BindObject(this, &IScreenSelectionInterface::UnregisterFromScreenSelection);
}
