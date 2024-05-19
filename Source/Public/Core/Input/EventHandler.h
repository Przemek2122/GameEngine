// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"
#include "Assets/IniReader/IniObject.h"
#include "Core/Input/EventHandlerMouse.h"
#include "Core/Input/EventHandlerKeyboard.h"

/**
 * Mouse delegates.
 * @Note Remember to initialize all delegates.
 */
class FMouseDelegates
{
public:
	FMouseDelegates(FEventHandler* EventHandler);

	/** Add input. RawInputName is for SDL codes while InputName is for our code use. */
	void AddInput(FEventHandler* EventHandler, FIniObject* InIniObject, const std::string& RawInputName);

	/** Raw engine internal use name */
	FMouseInputDelegateWrapper* GetMouseDelegateByNameRaw(const std::string& InputName);

	FMouseInputDelegateWrapper* GetMouseDelegateByName(const std::string& InputName);

protected:
	CMap<std::string, std::shared_ptr<FMouseInputDelegateWrapper>> RawInputNameToDelegateMap;
	CMap<std::string, std::shared_ptr<FMouseInputDelegateWrapper>> InputNameToDelegateMap;

};

/**
 * Keyboard delegates.
 * @Note Remember to initialize all delegates.
 */
class FKeyBoardDelegates
{
	typedef FAutoDeletePointer<FInputDelegateWrapper> FKeyBoardButtonDelegate;

public:
	FKeyBoardDelegates(FEventHandler* EventHandler);

	void AddInput(FEventHandler* EventHandler, const std::string& RawInputName, const std::string& InputName);

	FInputDelegateWrapper* GetMouseDelegateByName(const std::string& InputName);

	/** Called when escape is used */
	FKeyBoardButtonDelegate ButtonEscape;

	/** Called when '0' key is used */
	FKeyBoardButtonDelegate Button0;
	/** Called when '1' key is used */
	FKeyBoardButtonDelegate Button1;
	/** Called when '2' key is used */
	FKeyBoardButtonDelegate Button2;
	/** Called when '3' key is used */
	FKeyBoardButtonDelegate Button3;
	/** Called when '4' key is used */
	FKeyBoardButtonDelegate Button4;
	/** Called when '5' key is used */
	FKeyBoardButtonDelegate Button5;
	/** Called when '6' key is used */
	FKeyBoardButtonDelegate Button6;
	/** Called when '7' key is used */
	FKeyBoardButtonDelegate Button7;
	/** Called when '8' key is used */
	FKeyBoardButtonDelegate Button8;
	/** Called when '9' key is used */
	FKeyBoardButtonDelegate Button9;

	/** Called when 'A' key is used */
	FKeyBoardButtonDelegate ButtonA;
	/** Called when 'B' key is used */
	FKeyBoardButtonDelegate ButtonB;
	/** Called when 'C' key is used */
	FKeyBoardButtonDelegate ButtonC;
	/** Called when 'D' key is used */
	FKeyBoardButtonDelegate ButtonD;
	/** Called when 'E' key is used */
	FKeyBoardButtonDelegate ButtonE;

	/** Called when 'W' key is used */
	FKeyBoardButtonDelegate ButtonW;
	/** Called when 'S' key is used */
	FKeyBoardButtonDelegate ButtonS;

	/** Called when up arrow key is used */
	FKeyBoardButtonDelegate ButtonArrowUP;
	/** Called when down arrow key is used */
	FKeyBoardButtonDelegate ButtonArrowDOWN;
	/** Called when right arrow key is used */
	FKeyBoardButtonDelegate ButtonArrowRIGHT;
	/** Called when left arrow key is used */
	FKeyBoardButtonDelegate ButtonArrowLEFT;

	/** Called when 'Delete' key is used */
	FKeyBoardButtonDelegate ButtonDELETE;

protected:
	CMap<std::string, std::shared_ptr<FInputDelegateWrapper>> RawInputNameToDelegateMap;
	CMap<std::string, std::shared_ptr<FInputDelegateWrapper>> InputNameToDelegateMap;

};

class FEventHandler
{
public:
	FEventHandler(const SDL_Event& InEvent);
	virtual ~FEventHandler();

	void HandleEvents();

	void ResetAll();

	void InitializeInputFromConfig();

	_NODISCARD bool QuitInputDetected() const;

	_NODISCARD bool HasMouseMoved() const;
	_NODISCARD FVector2D<int> GetMouseLocationCurrent() const;
	_NODISCARD FVector2D<int> GetMouseLocationLast() const;

	void AddMouseInputDelegateToReset(FMouseInputDelegateWrapper* MouseInputDelegateWrapper);
	void AddKeyboardInputDelegateToReset(FInputDelegateWrapper* KeyboardInputDelegateWrapper);

	FMouseDelegates MouseDelegates;
	FKeyBoardDelegates KeyBoardDelegates;

	/**
	 * Perhaps create an array with SDL KeyCodes? and binding them like
	 * BindEvent(SDL_MOUSEMOTION, this, &ECameraManager::OnMouseMove);
	 */

protected:
	void InitializeMouseDelegates();
	void InitializeKeyBoardDelegates();

	virtual void SwitchOnInput(Uint32 EventType);

	virtual void InputKeyDown();
	virtual void InputKeyUp();
	virtual void MouseMotion();
	virtual void InputMouseDown();
	virtual void InputMouseUp();
	virtual void InputWindowEvent();

protected:
	/** This map is used to reset mouse delegates. */
	CArray<FMouseInputDelegateWrapper*> MouseInputDelegateResetQueue;
	/** This map is used to reset keyboard delegates. */
	CArray<FInputDelegateWrapper*> KeyboardInputDelegateResetQueue;

	FVector2D<int> MouseLocationCurrent;
	FVector2D<int> MouseLocationLast;

	SDL_Event Event;
	
	bool bQuitInputDetected;

	std::shared_ptr<FIniObject> EngineInputIniObject;
	
};
