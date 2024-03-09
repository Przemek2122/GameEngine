// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "Core/Input/EventHandlerMouse.h"
#include "Core/Input/EventHandlerKeyboard.h"

class FMouseDelegates
{
public:
	/* Mouse move delegate. Called when mouse moves. */
	FAutoDeletePointer<FMouseInputDelegateWrapper> MouseMoveDelegate;

	/** Called when mouse left click is detected */
	FAutoDeletePointer<FMouseInputDelegateWrapper> MouseLeftButtonDelegate;

	/** Called when mouse middle click is detected */
	FAutoDeletePointer<FMouseInputDelegateWrapper> MouseMiddleButtonDelegate;

	/** Called when mouse right click is detected */
	FAutoDeletePointer<FMouseInputDelegateWrapper> MouseRightButtonDelegate;
};

class FKeyBoardDelegates
{
public:
	/** Called when escape is used */
	FAutoDeletePointer<FInputDelegateWrapper> EscapeDelegate;

};

class FEventHandler
{
public:
	FEventHandler(const SDL_Event& InEvent);
	virtual ~FEventHandler();

public:
	void HandleEvents();

	void ResetAll();

	_NODISCARD bool QuitInputDetected() const;

	_NODISCARD bool HasMouseMoved() const;
	_NODISCARD FVector2D<int> GetMouseLocationCurrent() const;
	_NODISCARD FVector2D<int> GetMouseLocationLast() const;

	void AddMouseInputDelegateToReset(FMouseInputDelegateWrapper* MouseInputDelegateWrapper);
	void AddKeyboardInputDelegateToReset(FInputDelegateWrapper* KeyboardInputDelegateWrapper);

	FMouseDelegates MouseDelegates;
	FKeyBoardDelegates KeyBoardDelegates;

protected:
	/** Initializer, helper for constructor - Set mouse delegates. */
	void SetMouseDelegates();
	/** Initializer, helper for constructor - Set keyboard delegates. */
	void SetKeyBoardDelegates();

	virtual void SwitchOnInput(Uint32 EventType);

	virtual void InputKeyUp();
	virtual void MouseMotion();
	virtual void InputWindowEvent();
	virtual void InputKeyDown();
	virtual void InputMouseDown();
	virtual void InputMouseUp();

protected:
	/** This map is used to reset mouse delegates. */
	CArray<FMouseInputDelegateWrapper*> MouseInputDelegateResetQueue;
	/** This map is used to reset keyboard delegates. */
	CArray<FInputDelegateWrapper*> KeyboardInputDelegateResetQueue;

	FVector2D<int> MouseLocationCurrent;
	FVector2D<int> MouseLocationLast;

	SDL_Event Event;
	
	bool bQuitInputDetected;
	
};
