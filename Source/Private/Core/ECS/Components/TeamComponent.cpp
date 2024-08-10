#include "CoreEngine.h"
#include "ECS/Components/TeamComponent.h"

UTeamComponent::UTeamComponent(IComponentManagerInterface* InComponentManagerInterface, const FUserId& InOwnerUserId, const int InTeam)
	: UBaseComponent(InComponentManagerInterface)
	, CurrentTeam(InTeam)
	, OwnerUserId(InOwnerUserId)
{
}
