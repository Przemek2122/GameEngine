// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"

#if ENGINE_NETWORK_LIB_ENABLED
#include "NetworkClassBase.h"

class FNetworkServerBase : public FNetworkClassBase
{
public:
	FNetworkServerBase(FNetworkManager* InNetworkManager);

};

#endif