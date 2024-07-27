#pragma once

#include "ECS/BaseComponent.h"

class UTeamComponent : public UBaseComponent
{
public:
	UTeamComponent(IComponentManagerInterface* InComponentManagerInterface, const int InTeam);

	int GetCurrentTeam() const { return CurrentTeam; }

protected:
	int CurrentTeam;

};
