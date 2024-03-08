#pragma once

#include "CoreMinimal.h"

class FMap;

/**
 * Class for editing the map
 * It should have references to the map
 * Map should not have references to it
 */
class FMapEditor
{
public:
	FMapEditor(FMap* InMap);

	void Initialize();
	void DeInitialize();

protected:
	FMap* Map;

};
