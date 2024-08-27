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
	UTeamComponent(IComponentManagerInterface* InComponentManagerInterface);
	UTeamComponent(IComponentManagerInterface* InComponentManagerInterface, const FUserId& InOwnerUserId, const int InTeam);

	void SetOwnerUserId(const FUserId& NewOwnerUserId) { OwnerUserId = NewOwnerUserId; }
	FUserId GetOwnerUserId() const { return OwnerUserId; }

	int GetCurrentTeam() const { return CurrentTeam; }

protected:
	/** Owner id */
	FUserId OwnerUserId;

	/** Team of owning entity */
	int CurrentTeam;



};
