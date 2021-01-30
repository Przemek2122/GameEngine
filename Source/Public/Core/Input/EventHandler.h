// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "CoreMinimal.h"

class FEventHandler
{
public:
	FEventHandler(SDL_Event InEvent);
	virtual ~FEventHandler();

	virtual void HandleEvents();

	void ResetAllButtons();

	_NODISCARD bool HasInput(std::string InputName);
	bool GetInput(std::string InputName);

	_NODISCARD bool HasMouseMoved() const;
	_NODISCARD FVector2D<int> GetMouseLocationCurrent() const;
	_NODISCARD FVector2D<int> GetMouseLocationLast() const;

protected:
	void AddInput(std::string InputName);
	void RemoveInput(const std::string& InputName);

protected:
	SDL_Event Event;

	CMap<std::string, bool> InputMap;

	FVector2D<int> MouseLocationCurrent;
	FVector2D<int> MouseLocationLast;
	
	bool QuitInputDetected;
	
};
