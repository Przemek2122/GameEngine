// Created by Przemys³aw Wiewióra 2020

#pragma once

#include "AI/AiTree.h"
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

	FEntityManager* GetEntityManagerOwner() const;
	FWindow* GetWindow() const;
	FWindowAdvanced* GetWindowAdvanced() const;
	FGameModeManager* GetGameModeManager() const;
	FGameModeBase* GetGameMode() const;
	FMap* GetCurrentMap() const;

protected:
	/** Register input to FEventHandler. Remember to unregister input in UnRegisterInput! */
	virtual void RegisterInput(FEventHandler* InputHandler);
	virtual void UnRegisterInput(FEventHandler* InputHandler);

	void RegisterInputInternal();
	void UnRegisterInputInternal();

	virtual void SetupAiActions();

	template<typename TAiTreeClass>
	TAiTreeClass* CreateAiTree()
	{
		std::shared_ptr<TAiTreeClass> AiTreePtr = std::make_shared<TAiTreeClass>(this);

		AiTreeArray.Push(AiTreePtr);

		return AiTreePtr.get();
	}

	/** Begin IComponentManagerInterface */
	void OnComponentCreated(const std::string& ComponentName, UBaseComponent* NewComponent) override;
	/** End IComponentManagerInterface */

private:
	/** Entity manager */
	FEntityManager* EntityManagerOwner;

	/** Root component. First component added or set by user */
	UBaseComponent* DefaultRootComponent;

	/** Ai tree array */
	CArray<std::shared_ptr<FAiTree>> AiTreeArray;

	bool bWasBeginPlayCalled;

};
