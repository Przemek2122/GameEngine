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

	virtual FVector2D<int> GetLocation() = 0;
	virtual FVector2D<int> GetSize() = 0;
	virtual void OnSelection() = 0;

	static EScreenSelectionEntity* GetScreenSelectionEntityStatic();

protected:
	bool bIsRegistered;

};
