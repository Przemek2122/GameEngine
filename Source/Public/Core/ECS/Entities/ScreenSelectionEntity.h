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
	void EndPlay() override;
	/** End EEntity */

	virtual void RegisterScreenSelectable(IScreenSelectionInterface* InScreenSelectable);
	virtual void UnRegisterScreenSelectable(IScreenSelectionInterface* InScreenSelectable);

	virtual void OnMouseMove(FVector2D<int> InMousePosition, EInputState);
	virtual void OnMouseLeftClick(FVector2D<int> InMousePosition, EInputState InputState);

	/** Called when selection is started */
	virtual void OnStartSelecting();

	/** Called when selection is finished */
	virtual void OnEndSelecting();

	const CArray<IScreenSelectionInterface*>& GetCurrentlySelectedObjects() const;

	/** Delegate called on EndPlay (destroy this entity) */
	FDelegate<> OnEndPlay;

protected:
	/** Begin EEntity */
	void RegisterInput(const FEventHandler* InputHandler) override;
	void UnRegisterInput(const FEventHandler* InputHandler) override;
	/** End EEntity */

	virtual void AddToCurrentlySelectedObjects(IScreenSelectionInterface* InScreenSelectable);
	virtual void RemoveFromCurrentlySelectedObjects(IScreenSelectionInterface* InScreenSelectable);

protected:
	/** Array with screen selectable items */
	CArray<IScreenSelectionInterface*> ScreenSelectableObjects;

	/** Currently selected objects list */
	CArray<IScreenSelectionInterface*> CurrentlySelectedObjects;

	/** Selecting when left mouse button is pressed */
	bool bIsSelecting;

	/** Start of the selection */
	FVector2D<int> SelectionStart;

};
