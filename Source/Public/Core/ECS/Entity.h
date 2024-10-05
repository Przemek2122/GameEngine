// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "AI/AITree.h"
#include "ECS/BaseComponent.h"

class FGameModeBase;
class FWindowAdvanced;
class FMap;
class FGameModeManager;
class FEntityManager;

/**
 * Generic entity class
 */
class EEntity : public FObject, public IComponentManagerInterface
{
public:
	EEntity(FEntityManager* InEntityManager);
	~EEntity() override = default;

	/** Called when starting or creating Entity */
	virtual void BeginPlay();

	/** Called right before destruction */
	virtual void EndPlay();

	/** Called every frame */
	virtual void Tick(float DeltaTime);

	/** Called every frame from engine code. */
	void ReceiveTick(float DeltaTime);

	/** Called every frame for rendering purposes */
	virtual void Render();

	/** Called every frame from engine code. */
	void ReceiveRender();

	virtual void SetRootComponent(UBaseComponent* NewComponent);
	virtual UBaseComponent* GetRootComponent() const;
	virtual UParentComponent* GetParentComponent() const;

	/** @Returns value of parent component (if present) */
	FVector2D<int32> GetLocation() const;

	/** @Returns value of parent component (if present) */
	int32 GetRotation() const;

	FEntityManager* GetEntityManagerOwner() const;
	FWindow* GetWindow() const;
	FWindowAdvanced* GetWindowAdvanced() const;
	FGameModeManager* GetGameModeManager() const;
	FGameModeBase* GetGameMode() const;
	FMap* GetCurrentMap() const;

	const CArray<std::shared_ptr<FAIMemorySet>>& GetAIMemorySetArray() const { return AIMemorySetArray; }

	/** Get AIMemorySet by class, it will iterate all existing MemorySets to find correct one */
	template<typename TAIMemorySetClass>
	std::shared_ptr<TAIMemorySetClass> GetAIMemorySetByClass()
	{
		for (std::shared_ptr<FAIMemorySet>& AIMemorySetPtr : AIMemorySetArray)
		{
			if (dynamic_cast<TAIMemorySetClass*>(AIMemorySetPtr.get()) != nullptr)
			{
				return std::dynamic_pointer_cast<TAIMemorySetClass>(AIMemorySetPtr);
			}
		}

		return std::make_shared<TAIMemorySetClass>(nullptr);
	}

protected:
	/** Register input to FEventHandler. Remember to unregister input in UnRegisterInput! */
	virtual void RegisterInput(FEventHandler* InputHandler);
	virtual void UnRegisterInput(FEventHandler* InputHandler);

	void RegisterInputInternal();
	void UnRegisterInputInternal();

	virtual void SetupAIActions();

	template<typename TAiTreeClass>
	TAiTreeClass* CreateAiTree()
	{
		std::shared_ptr<TAiTreeClass> AiTreePtr = std::make_shared<TAiTreeClass>(this);

		AiTreeArray.Push(AiTreePtr);

		return AiTreePtr.get();
	}

	/** Create new AIMemorySet */
	template<class TAIMemorySetClass>
	TAIMemorySetClass* CreateAIMemorySetByClass()
	{
		TAIMemorySetClass* NewAIMemorySet = std::make_shared<TAIMemorySetClass>();

		return NewAIMemorySet;
	}

	/** Begin IComponentManagerInterface */
	void OnComponentCreated(const std::string& ComponentName, UBaseComponent* NewComponent) override;
	/** End IComponentManagerInterface */

private:
	/** Array of AI memory sets. */
	CArray<std::shared_ptr<FAIMemorySet>> AIMemorySetArray;

	/** Entity manager */
	FEntityManager* EntityManagerOwner;

	/** Root component. First component added or set by user */
	UBaseComponent* DefaultRootComponent;

	/** Ai tree array */
	CArray<std::shared_ptr<FAITree>> AiTreeArray;

	bool bWasBeginPlayCalled;

};
