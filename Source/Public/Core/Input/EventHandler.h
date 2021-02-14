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

	_NODISCARD bool HasMouseMoved() const;
	_NODISCARD FVector2D<int> GetMouseLocationCurrent() const;
	_NODISCARD FVector2D<int> GetMouseLocationLast() const;
	
	/** Use to check if primary input exists. */
	_NODISCARD bool HasPrimaryInput(std::string InputName);
	/** Use to check primary input. */
	_NODISCARD bool GetPrimaryInput(std::string InputName);

protected:
	/** Add primary input (Engine uses) Name from  */
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
	SDL_Event Event;

	/** Direct input map. */
	CMap<std::string, bool> PrimaryInputMap;
	/** Use this map to make aliases for primary map. */
	CMap<std::string, std::string> SecondaryInputMap;

	FVector2D<int> MouseLocationCurrent;
	FVector2D<int> MouseLocationLast;
	
	bool bQuitInputDetected;
	
};
