#include "CoreEngine.h"

#include "Renderer/Widgets/UIMenu.h"

FUIMenu::FUIMenu(FWindow* InOwnerWindow)
	: OwnerWindow(InOwnerWindow)
{
#if _DEBUG
	if (OwnerWindow == nullptr)
	{
		LOG_ERROR("OwnerWindow is nullptr!");
	}
#endif
}

FWindow* FUIMenu::GetOwnerWindow() const
{
	return OwnerWindow;
}
