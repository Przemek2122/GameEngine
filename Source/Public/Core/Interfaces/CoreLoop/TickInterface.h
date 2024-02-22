#pragma once

#include "CoreMinimal.h"

/**
 * Enum for tick phases (defines order of ticking, first tick first)
 */
enum class ETickPhase : Uint8
{
	Pre = 1,
	Main,
	Post
};

/**
 * Class for objects that need to be ticked
 * Self registers and unregisters
 */
class FTickInterface
{
public:
	FTickInterface();
	virtual ~FTickInterface();

	/** @returns Phase registered in constructor. */
	ETickPhase GetRegisteredPhase() const { return RegisteredPhase; }

	/** Called only once, so changing return value does not change state */
	virtual ETickPhase GetTickPhase() const = 0;

	/** Called every frame in given phase */
	virtual void Tick(float DeltaTime) = 0;

private:
	ETickPhase RegisteredPhase;
};
