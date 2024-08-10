#pragma once

#include "ECS/BaseComponent.h"
#include "Engine/Logic/BaseController.h"

/**
 * Team Component
 * defines team and user which is owning a unit
 */
class UTeamComponent : public UBaseComponent
{
public:
	UTeamComponent(IComponentManagerInterface* InComponentManagerInterface, const FUserId& InOwnerUserId, const int InTeam);

	int GetCurrentTeam() const { return CurrentTeam; }

	FUserId GetOwnerUserId() const { return OwnerUserId; }

protected:
	/** Team of owning entity */
	int CurrentTeam;

	/** Owner id */
	FUserId OwnerUserId;

};
