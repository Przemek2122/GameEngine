#pragma once

#include "CoreMinimal.h"

/**
 * Enum for render phases (defines order of rendering, first render first)
 */
enum class ERenderPhase : Uint8
{
	// Special case for background rendering (map)
	Background = 1,
	Pre,
	Main,
	Post
};

/**
 * Class for objects that need to be ticked
 * Self registers and unregisters
 */
class FRenderInterface
{
public:
	FRenderInterface();
	virtual ~FRenderInterface();

	/** @returns Phase registered in constructor. */
	ERenderPhase GetRegisteredPhase() const { return RegisteredPhase; }

	/** Called only once, so changing return value does not change state */
	virtual ERenderPhase GetRenderPhase() const = 0;

	/** Called every frame in given phase */
	virtual void Draw(float DeltaTime) = 0;

private:
	ERenderPhase RegisteredPhase;
};
