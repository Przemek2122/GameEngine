#pragma once

#include "CoreMinimal.h"
#include "ECS/Entity.h"

enum class EInputState;
class IScreenSelectionInterface;

class EScreenSelectionEntity : public EEntity
{
public:
	EScreenSelectionEntity(FEntityManager* InEntityManager);
	~EScreenSelectionEntity() override = default;

	/** Begin EEntity */
	void BeginPlay() override;
	void EndPlay() override;
	/** End EEntity */

	void RegisterScreenSelectable(IScreenSelectionInterface* InScreenSelectable);
	void UnRegisterScreenSelectable(IScreenSelectionInterface* InScreenSelectable);

	void OnMouseMove(FVector2D<int> InMousePosition, EInputState);
	void OnMouseLeftClick(FVector2D<int> InMousePosition, EInputState InputState);

protected:
	void RegisterInput();
	void UnRegisterInput();

protected:
	/** Array with screen selectable items */
	CArray<IScreenSelectionInterface*> ScreenSelectableObjects;

	/** Selecting when left mouse button is pressed */
	bool bIsSelecting;

	/** Start of the selection */
	FVector2D<int> SelectionStart;

};
