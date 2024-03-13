#include "CoreEngine.h"
#include "Renderer/Widgets/UIMenu.h"

FUIMenu::FUIMenu(FWindow* InOwnerWindow)
	: bIsInitialized(false)
	, OwnerWindow(InOwnerWindow)
{
#if _DEBUG
	if (OwnerWindow == nullptr)
	{
		LOG_ERROR("OwnerWindow is nullptr!");
	}
#endif
}

FUIMenu::~FUIMenu()
{
	DeInitializePublic();
}

FWindow* FUIMenu::GetOwnerWindow() const
{
	return OwnerWindow;
}

void FUIMenu::InitializePublic()
{
	if (!bIsInitialized)
	{
		bIsInitialized = true;

		Initialize();
	}
}

void FUIMenu::DeInitializePublic()
{
	if (bIsInitialized)
	{
		bIsInitialized = false;

		DeInitialize();
	}
}

bool FUIMenu::IsInitialized() const
{
	return bIsInitialized;
}

void FUIMenu::Initialize()
{
}

void FUIMenu::DeInitialize()
{
}
