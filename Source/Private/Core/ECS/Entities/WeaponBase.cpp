#include "CoreEngine.h"
#include "Core/ECS/Entities/WeaponBase.h"

#include "Timer/TimerManager.h"

EWeaponBase::EWeaponBase(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
	, bCanAttack(true)
	, bIsDelayed(false)
{
}

void EWeaponBase::Attack()
{
	if (CanAttack())
	{
		PerformAttack();

		if (ShouldDelayAttacks())
		{
			FDelegateSafe<void, FOptionalTimerParams*> OnAttackDelayFinished;
			OnAttackDelayFinished.BindObject(this, &EWeaponBase::AttackDelayFinished);

			AttackDelayTimer = FTimerManager::CreateTimerSync(OnAttackDelayFinished, 0.1f);

			bIsDelayed = true;
		}

		OnAttackPerformed();
	}
}

void EWeaponBase::SetCanAttack(const bool bInCanAttack)
{
	bCanAttack = bInCanAttack;

	OnCanAttackChanged();
}

void EWeaponBase::PerformAttack()
{
}

void EWeaponBase::AttackDelayFinished(FOptionalTimerParams* OptionalTimerParams)
{
	OnAttackDelayFinished();

	bIsDelayed = false;
}

void EWeaponBase::OnCanAttackChanged()
{
}

void EWeaponBase::OnAttackPerformed()
{
}

void EWeaponBase::OnAttackDelayFinished()
{
}
