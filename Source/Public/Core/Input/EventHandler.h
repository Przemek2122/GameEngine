// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

/** This class is used to tell type of input, if it is pressed or released. */
enum class EInputState
{
	NOT_PRESSED = 0,
	PRESS = 1,
	RELEASE = 2,
	ENUM_MAX
};

/** This class is used to handle mouse events. */
class FMouseInputDelegateWrapper
{
public:
	FMouseInputDelegateWrapper(FEventHandler* InEventHandler)
		: bWasSentAlready(false)
		, EventHandler(InEventHandler)
		, CurrentInputState(EInputState::NOT_PRESSED)
	{
	}

	void Execute(const FVector2D<int>& Location, const EInputState InputState);

	void Reset();

	FDelegate<void, FVector2D<int>, EInputState> Delegate;

private:
	void AddToResetQueue();

private:
	/** True if input was sent already. */
	bool bWasSentAlready;

	FEventHandler* EventHandler;

	/** Current state of input. It is incremented in execute and then reset in reset */
	EInputState CurrentInputState;
};

/** This class is used to handle keyboard events. It exists to allow rebinding. */
class FInputDelegateWrapper
{
public:
	FInputDelegateWrapper(FEventHandler* InEventHandler)
		: bWasSentAlready(false)
		, EventHandler(InEventHandler)
		, CurrentInputState(EInputState::NOT_PRESSED)
	{
	}

	void Execute(EInputState InputState);

	void Reset();

	/** Called when input is detected. */
	FDelegate<void, EInputState> Delegate;

private:
	void AddToResetQueue();

private:
	/** True if input was sent already. */
	bool bWasSentAlready;

	FEventHandler* EventHandler;

	/** Current state of input. It is incremented in execute and then reset in reset */
	EInputState CurrentInputState;
};

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

protected:
	SDL_Event Event;

public:
	void HandleEvents();

	void ResetAll();

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

public:
	_NODISCARD bool QuitInputDetected() const;

protected:
	/** This map is used to reset mouse delegates. */
	CArray<FMouseInputDelegateWrapper*> MouseInputDelegateResetQueue;
	/** This map is used to reset keyboard delegates. */
	CArray<FInputDelegateWrapper*> KeyboardInputDelegateResetQueue;

	FVector2D<int> MouseLocationCurrent;
	FVector2D<int> MouseLocationLast;
	
	bool bQuitInputDetected;
	
};
