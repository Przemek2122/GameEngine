// See https://github.com/Przemek2122/GameEngine

#pragma once

#include "CoreMinimal.h"
#include "Assets/Assets/MapAsset.h"

/**
 * Class for map management
 */
class FMap
{
public:
	FMap(FMapAsset* InMapAsset);

protected:
	/** Map asset */
	FAutoDeletePointer<FMapAsset> MapAsset;

};
