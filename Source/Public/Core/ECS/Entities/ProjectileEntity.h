#pragma once

#include "CoreMinimal.h"
#include "ECS/Entity.h"

class UMoveComponent;
class URenderComponent;

struct EInitialProjectileParams
{
	EInitialProjectileParams(const float InLinearSpeedPerSecond = 40.f, const int InAngle = 0)
		: LinearSpeedPerSecond(InLinearSpeedPerSecond)
		, Angle(InAngle)
	{
	}

	/** Speed of projectile */
	float LinearSpeedPerSecond;

	/** Sets default angle of RootComponent */
	int Angle;
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
