#pragma once

#include "CoreMinimal.h"
#include "ECS/Entity.h"

class IScreenSelectionInterface;

class EScreenSelectionEntity : public EEntity
{
public:
	EScreenSelectionEntity(FEntityManager* InEntityManager);

	void RegisterScreenSelectable(IScreenSelectionInterface* InScreenSelectable);

	void UnRegisterScreenSelectable(IScreenSelectionInterface* InScreenSelectable);

protected:
	CArray<IScreenSelectionInterface*> ScreenSelectableObjects;

};
