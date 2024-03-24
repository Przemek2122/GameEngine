#pragma once

#include "CoreMinimal.h"

class EScreenSelectionEntity;

/**
 * Objects using this interface can be selected by screen selection
 */
class IScreenSelectionInterface
{
public:
	IScreenSelectionInterface();
	virtual ~IScreenSelectionInterface();

	/** You need to call register */
	void RegisterToScreenSelection(FEntityManager* InEntityManager);

	/** Unregister does not have to be called */
	void UnregisterFromScreenSelection();

	void NativeSelect();

	void NativeDeselect();

	/** Override to return location of selection */
	virtual FVector2D<int> GetLocation() = 0;

	/** Override to return size of selection */
	virtual FVector2D<int> GetSize() = 0;

	/** Called when object is selected (once) */
	virtual void OnSelect() = 0;

	/** Called when object is de-selected (once) */
	virtual void OnDeSelect() = 0;

	static EScreenSelectionEntity* GetScreenSelectionEntityStatic();

	static void ResetScreenSelection();

protected:
	bool bIsRegistered;
	bool bIsSelected;

};
