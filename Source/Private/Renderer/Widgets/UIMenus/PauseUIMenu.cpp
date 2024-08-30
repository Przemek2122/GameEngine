#include "CoreEngine.h"
#include "Renderer/Widgets/UIMenus/PauseUIMenu.h"

#include "Input/EventHandler.h"
#include "Renderer/WindowAdvanced.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"

FPauseUIMenu::FPauseUIMenu(FWindow* InGameWindow)
	: FUIMenu(InGameWindow)
	, VerticalBoxWidget(nullptr)
	, bIsVisible(false)
{
}

void FPauseUIMenu::Initialize()
{
	OnBindDelegateRequested();

	// Create VerticalBoxWidget
	VerticalBoxWidget = GetOwnerWindow()->CreateWidget<FVerticalBoxWidget>();
	VerticalBoxWidget->SetAnchor(EAnchor::Center);

	// Create content
	CreateMenuInVerticalBox(VerticalBoxWidget);

	// Hide by default
	Hide();
}

void FPauseUIMenu::DeInitialize()
{
	OnUnbindDelegateRequested();

	VerticalBoxWidget->DestroyWidget();
}

bool FPauseUIMenu::OnExitButtonPressed(EInputState InputState)
{
	if (InputState == EInputState::RELEASE)
	{
		if (bIsVisible)
		{
			DisablePauseMenu();
		}
		else
		{
			EnablePauseMenu();
		}
	}

	return true;
}

void FPauseUIMenu::OnExitToMenuRequested()
{
	FWindowAdvanced* WindowAdvanced = GetOwnerWindow<FWindowAdvanced>();
	if (WindowAdvanced != nullptr)
	{
		OnExitToMenu(WindowAdvanced);
	}
	else
	{
		LOG_ERROR("WindowAdvanced is nullptr!");
	}
}

void FPauseUIMenu::OnExitToMenu(FWindowAdvanced* WindowAdvanced)
{
	LOG_DEBUG("Exit to menu requested");
}

FVerticalBoxWidget* FPauseUIMenu::GetVerticalBoxWidget() const
{
	return VerticalBoxWidget;
}

void FPauseUIMenu::DisablePauseMenu()
{
	bIsVisible = false;

	Hide();
}

void FPauseUIMenu::EnablePauseMenu()
{
	bIsVisible = true;

	Show();
}

void FPauseUIMenu::Show()
{
	if (IsInitialized())
	{
		VerticalBoxWidget->SetWidgetVisibility(EWidgetVisibility::Visible);

		OnMenuShown();
	}
	else
	{
		// Initialize if not initialized
		InitializePublic();
	}
}

void FPauseUIMenu::Hide()
{
	VerticalBoxWidget->SetWidgetVisibility(EWidgetVisibility::Collapsed);

	OnMenuHidden();
}

void FPauseUIMenu::OnMenuShown()
{
}

void FPauseUIMenu::OnMenuHidden()
{
}

void FPauseUIMenu::CreateMenuInVerticalBox(FVerticalBoxWidget* InVerticalBoxWidget)
{
	FButtonWidget* BackButton = VerticalBoxWidget->CreateWidget<FButtonWidget>();
	FTextWidget* TextWidget = BackButton->CreateWidget<FTextWidget>();
	TextWidget->SetText("Back to menu");
	BackButton->OnClickRelease.BindObject(this, &FPauseUIMenu::OnExitToMenuRequested);
}

void FPauseUIMenu::OnBindDelegateRequested()
{
	FInputDelegateWrapper* EscapeDelegate = GEngine->GetEventHandler()->KeyBoardDelegates.ButtonEscape.Get();

	EscapeDelegate->Delegate.BindObject(this, &FPauseUIMenu::OnExitButtonPressed);
}

void FPauseUIMenu::OnUnbindDelegateRequested()
{
	FInputDelegateWrapper* EscapeDelegate = GEngine->GetEventHandler()->KeyBoardDelegates.ButtonEscape.Get();

	EscapeDelegate->Delegate.UnBindObject(this, &FPauseUIMenu::OnExitButtonPressed);
}
