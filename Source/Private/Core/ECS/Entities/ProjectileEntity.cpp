#include "CoreEngine.h"
#include "ECS/Entities/ProjectileEntity.h"

#include "ECS/Components/MoveComponent.h"

EProjectileEntity::EProjectileEntity(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
{
	RenderComponent = CreateComponent<URenderComponent>("RenderComponent");
	MovementComponent = CreateComponent<UMoveComponent>("MovementComponent");
	MovementComponent->SetMovementMethod(EMovementMethod::Linear);
}

void EProjectileEntity::SetProjectileParams(const EInitialProjectileParams& InitialProjectileParams)
{

}

URenderComponent* EProjectileEntity::GetRenderComponent() const
{
	return RenderComponent;
}

UMoveComponent* EProjectileEntity::GetMovementComponent() const
{
	return MovementComponent;
}
