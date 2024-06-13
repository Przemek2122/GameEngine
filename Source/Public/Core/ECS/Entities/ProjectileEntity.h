#pragma once

#include "CoreMinimal.h"
#include "ECS/Entity.h"

class UMoveComponent;
class URenderComponent;

struct EInitialProjectileParams
{
	EInitialProjectileParams(const float InLinearSpeedPerSecond = 40.f)
		: LinearSpeedPerSecond(InLinearSpeedPerSecond)
	{
	}

	float LinearSpeedPerSecond;
};

/**
 * Simple projectile component
 */
class EProjectileEntity : public EEntity
{
public:
	EProjectileEntity(FEntityManager* InEntityManager);

	void SetProjectileParams(const EInitialProjectileParams& InitialProjectileParams) const;

	URenderComponent* GetRenderComponent() const;
	UMoveComponent* GetMovementComponent() const;

protected:
	URenderComponent* RenderComponent;
	UMoveComponent* MovementComponent;

};
