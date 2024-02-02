// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "../Widget.h"
#include "Renderer/Widgets/WidgetInputInterface.h"

enum class EHoverState : Uint8
{
	None,
	Entered,
	Exited
};

enum class EClickState : Uint8
{
	NotClicked,
	Pressed,
	Released
};

class FInteractionBaseWidget : public FWidget
{
public:
	FInteractionBaseWidget(IWidgetManagementInterface* InWidgetManagementInterface, const std::string& InWidgetName, const int InWidgetOrder = 0);
	virtual ~FInteractionBaseWidget() override;

	/** Begin FWidget */
	void Init() override;
	void PreDeInit() override;
	/** End FWidget */

	void SetupInput(FWidgetInputManager* WidgetInputManager);
	void ClearInput(FWidgetInputManager* WidgetInputManager);

	bool OnMouseLeftButtonPress(FVector2D<int> Location);
	bool OnMouseLeftButtonRelease(FVector2D<int> Location);
	void OnMouseMove(FVector2D<int> Location);

	static _NODISCARD FVector2D<int> GetMouseLocation();

	/** Called once when pressed in widget area. */
	virtual void NativePress();
	/** Called once when released. */
	virtual void NativeRelease();
	/** Called when should be released because mouse is outside of widget */
	virtual void NativeReleaseOutsideWidget();
	/** Called every frame when hovered. */
	virtual void NativeHover();

	/** Called when mouse enters this widget */
	virtual void NativeMouseEnterWidget();
	/** Called when mouse exits this widget */
	virtual void NativeMouseExitWidget();

	void SetHoverState(EHoverState NewHoverState);
	_NODISCARD EHoverState GetHoverState() const;
	virtual void OnHoverStateChanged();

	void OnLeftMouseButtonReleased(FVector2D<int> Location);
	void OnRightMouseButtonReleased(FVector2D<int> Location);

protected:
	EClickState ClickState;
	EHoverState HoverState;

	bool bIsInWidget;
	bool bMouseEnteredWidget;
	FWidgetInputManager* WidgetInputManager;
	
};
