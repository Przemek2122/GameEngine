#pragma once

#include "CoreMinimal.h"

/**
 * Class for UI widgets
 * Like MainMenu, PauseMenu, etc.
 */
class FUIMenu
{
public:
	/**
	 * Window is very important for widgets as it stores widget that we can later add more widgets to.
	 */
	FUIMenu(FWindow* InOwnerWindow);
	virtual ~FUIMenu() = default;

	//virtual void Initialize();
	//virtual void DeInitialize();

	FWindow* GetOwnerWindow() const;

private:
	FWindow* OwnerWindow;
};
