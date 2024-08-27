#include "CoreEngine.h"
#include "ECS/Components/TeamComponent.h"

UTeamComponent::UTeamComponent(IComponentManagerInterface* InComponentManagerInterface)
	: UBaseComponent(InComponentManagerInterface)
	, CurrentTeam(0)
{
}

UTeamComponent::UTeamComponent(IComponentManagerInterface* InComponentManagerInterface, const FUserId& InOwnerUserId, const int InTeam)
	: UBaseComponent(InComponentManagerInterface)
	, OwnerUserId(InOwnerUserId)
	, CurrentTeam(InTeam)
{
}
