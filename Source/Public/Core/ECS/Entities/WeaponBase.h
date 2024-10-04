#pragma once

#include "CoreMinimal.h"

struct FOptionalTimerParams;

/**
 * Base class for weapons with some basic functionality
 */
class EWeaponBase : public EEntity
{
public:
	EWeaponBase(FEntityManager* InEntityManager);

	/** Try to attack if possible */
	virtual void Attack();

	/** Defines if attack can be performed - Check for delay between attacks etc */
	virtual bool CanAttack() const { return (bCanAttack && !bIsDelayed); }

	virtual bool ShouldDelayAttacks() const { return true; }

	/** Sets bool which disables or enables attacks */
	void SetCanAttack(const bool bInCanAttack);

protected:
	virtual void PerformAttack();
	void AttackDelayFinished(FOptionalTimerParams* OptionalTimerParams);

	virtual void OnCanAttackChanged();
	virtual void OnAttackPerformed();
	virtual void OnAttackDelayFinished();

private:
	bool bCanAttack;
	bool bIsDelayed;

	/** Timer for delayed attacks */
	std::shared_ptr<FTimer> AttackDelayTimer;

};
