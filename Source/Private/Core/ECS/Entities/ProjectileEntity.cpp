#include "CoreEngine.h"
#include "ECS/Entities/ProjectileEntity.h"

#include "ECS/Components/MoveComponent.h"
#include "ECS/Components/RenderComponent.h"

EProjectileEntity::EProjectileEntity(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
{
	UParentComponent* NewRootComponent = CreateComponent<UParentComponent>("RootComponent");

	RenderComponent = NewRootComponent->CreateComponent<URenderComponent>("RenderComponent");
	MovementComponent = NewRootComponent->CreateComponent<UMoveComponent>("MovementComponent");
}

void EProjectileEntity::SetProjectileParams(const EInitialProjectileParams& InitialProjectileParams) const
{
	// Set movement settings
	MovementComponent->SetMovementMethod(EMovementMethod::Linear);
	MovementComponent->SetLinearSpeedPerSecond(InitialProjectileParams.LinearSpeedPerSecond);

	// Set rotation
	GetParentComponent()->SetRotation(InitialProjectileParams.Angle);
}

URenderComponent* EProjectileEntity::GetRenderComponent() const
{
	return RenderComponent;
}

UMoveComponent* EProjectileEntity::GetMovementComponent() const
{
	return MovementComponent;
}
