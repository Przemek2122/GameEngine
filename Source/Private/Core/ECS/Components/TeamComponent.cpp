#include "CoreEngine.h"
#include "ECS/Components/TeamComponent.h"

UTeamComponent::UTeamComponent(IComponentManagerInterface* InComponentManagerInterface, const int InTeam)
	: UBaseComponent(InComponentManagerInterface)
{
}
