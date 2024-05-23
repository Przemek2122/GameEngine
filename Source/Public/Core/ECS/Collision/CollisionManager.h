// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"

class FSquareCollision;
class FCircleCollision;

class FCollisionManager
{
public:
	FCollisionManager();

	void RegisterCircleCollision(FCircleCollision* InCircleCollision);
	void UnRegisterCircleCollision(FCircleCollision* InCircleCollision);

	void RegisterSquareCollision(FSquareCollision* SquareCollision);
	void UnRegisterSquareCollision(FSquareCollision* SquareCollision);

	void CheckCircleCollision();
	void CheckSquareCollision();

protected:
	CArray<FCircleCollision*> CircleCollisionArray;
	CArray<FCircleCollision*> SquareCollisionArray;
	
};
