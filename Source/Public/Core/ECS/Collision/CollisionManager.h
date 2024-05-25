// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "ECS/SubSystems/SubSystemInstanceInterface.h"

class FSquareCollision;
class FCircleCollision;

class FCollisionManager : public ISubSystemInstanceInterface
{
public:
	FCollisionManager();

	/** Begin ISubSystemInstanceInterface */
	void InitializeSubSystem() override;
	void TickSubSystem() override;
	/** End ISubSystemInstanceInterface */

	void RegisterCircleCollision(FCircleCollision* InCircleCollision);
	void UnRegisterCircleCollision(FCircleCollision* InCircleCollision);

	void RegisterSquareCollision(FSquareCollision* SquareCollision);
	void UnRegisterSquareCollision(FSquareCollision* SquareCollision);

	void CheckCircleCollision();
	void CheckSquareCollision();

protected:
	/** Circle collision array */
	CArray<FCircleCollision*> CircleCollisionArray;

	/** Square collision array */
	CArray<FSquareCollision*> SquareCollisionArray;
	
};
