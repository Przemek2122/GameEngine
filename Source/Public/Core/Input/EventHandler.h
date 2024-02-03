// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

/** This class is used to handle mouse events. */
class FMouseInputDelegateWrapper
{
public:
	FMouseInputDelegateWrapper(FEventHandler* InEventHandler)
		: bWasSentAlready(false)
		, EventHandler(InEventHandler)
	{
	}

	void Execute(const FVector2D<int>& Location);
	void AddToResetQueue();
	void Reset();

	FDelegate<void, FVector2D<int>> Delegate;

private:
	bool bWasSentAlready;
	FEventHandler* EventHandler;
};

/** This class is used to handle keyboard events. It exists to allow rebinding. */
class FInputDelegateWrapper
{
public:

	/** Called when input is detected. */
	FDelegate<> Delegate;
};

class FEventHandler
{
public:
	FEventHandler(const SDL_Event& InEvent);
	virtual ~FEventHandler();

protected:
	SDL_Event Event;

public:
	virtual void HandleEvents();

	void ResetAll();

	_NODISCARD bool HasMouseMoved() const;
	_NODISCARD FVector2D<int> GetMouseLocationCurrent() const;
	_NODISCARD FVector2D<int> GetMouseLocationLast() const;
	
	/** Use to check if primary input exists. */
	_NODISCARD bool HasPrimaryInput(const std::string& InputName);
	/** Use to check primary input. */
	_NODISCARD bool GetPrimaryInput(const std::string& InputName);

	void AddMouseInputDelegateToReset(FMouseInputDelegateWrapper* MouseInputDelegateWrapper);

	/* Mouse move delegate. Called when mouse moves. */
	FAutoDeletePointer<FMouseInputDelegateWrapper> MouseMoveDelegate;

	/** Called when mouse left click is detected */
	FAutoDeletePointer<FMouseInputDelegateWrapper> MouseLeftButtonPressDelegate;
	/** Called when mouse left click is released */
	FAutoDeletePointer<FMouseInputDelegateWrapper> MouseLeftButtonReleaseDelegate;

	/** Called when mouse right click is detected */
	FAutoDeletePointer<FMouseInputDelegateWrapper> MouseRightButtonPressDelegate;
	/** Called when mouse right click is released */
	FAutoDeletePointer<FMouseInputDelegateWrapper> MouseRightButtonReleaseDelegate;

	/** Called when escape is used */
	FAutoDeletePointer<FInputDelegateWrapper> EscapeDelegate;

protected:
	/** Add primary input (GEngine uses) Name from  */
	void AddPrimaryInput(const std::string& InPrimaryName);
	/** Remove primary input */
	void RemovePrimaryInput(const std::string& InPrimaryName);

public:
	/** Remove primary input */
	void RemoveSecondaryInput(const std::string& InSecondaryName);
	/** Create or replace secondary input. */
	void SetSecondaryInput(const std::string& InSecondaryName, const std::string& InPrimaryName);
	
	/** Use to check if primary input exists. Check if secondary and bound primary input exists. */
	_NODISCARD bool HasSecondaryInput(const std::string& InputName);
	/** Use to check primary input. Will use map to get primary input. */
	_NODISCARD bool GetSecondaryInput(const std::string& InputName);

	_NODISCARD bool QuitInputDetected() const;

protected:
	/** Direct input map. */
	CMap<std::string, bool> PrimaryInputMap;
	/** Use this map to make aliases for primary map. */
	CMap<std::string, std::string> SecondaryInputMap;

	/** This map is used to reset mouse delegates. */
	CArray<FMouseInputDelegateWrapper*> MouseInputDelegateResetQueue;

	FVector2D<int> MouseLocationCurrent;
	FVector2D<int> MouseLocationLast;
	
	bool bQuitInputDetected;
	
};
