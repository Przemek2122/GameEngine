// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "AIActionBase.h"
#include "CoreMinimal.h"

class FAIMemorySet;
class FAIActionBase;

/**
 * AI Trees are used for decision making on which action should AI Choose
 * You might use multiple trees to create behaviour for example
 * One tree for movement. One action for direct approach. One for approach from left etc...
 * Another example would be AI with multiple weapons.
 */
class FAITree
{
public:
	FAITree(EEntity* InOwnerEntity);
	virtual ~FAITree();

	/** Create AI Action. */
	template<typename TActionClass>
	TActionClass* CreateAction()
	{
		std::shared_ptr<TActionClass> ActionPtr = std::make_shared<TActionClass>(this);

		ActionPtr->Initialize();

		AllAIActionsArray.Push(ActionPtr);

		return ActionPtr.get();
	}

	/** Delete AI Action. */
	void RemoveAction(const FAIActionBase* AiAction);

	template<class TActionClass>
	TActionClass* GetActionByClass()
	{
		TActionClass* CastedAction = nullptr;

		for (std::shared_ptr<FAIActionBase>& AIAction : AllAIActionsArray)
		{
			CastedAction = dynamic_cast<TActionClass*>(AIAction.get());
			if (CastedAction != nullptr)
			{
				break;
			}
		}

		return CastedAction;
	}

	void TickInternal();

	/** Start, stop actions and tick them. */
	virtual void Tick();

	EEntity* GetOwnerEntity() const;

	void SetIsTreeEnabled(const bool bInEnable);

	/** Will activate action if not running and ready */
	bool ActivateAction(FAIActionBase* InAction);

	/** Will stop action, use force to stop for sure */
	bool StopAction(FAIActionBase* InAction, const bool bForceStopAction = false);

	bool IsAnyActionRunning() const;

	const CArray<std::shared_ptr<FAIMemorySet>>& GetAIMemorySetArray() const { return AIMemorySetArray; }

	/** Create new AIMemorySet */
	template<class TAIMemorySetClass>
	TAIMemorySetClass* CreateAIMemorySetByClass()
	{
		TAIMemorySetClass* NewAIMemorySet = std::make_shared<TAIMemorySetClass>();

		return NewAIMemorySet;
	}

	/** Get AIMemorySet by class, it will iterate all existing MemorySets to find correct one */
	template<class TAIMemorySetClass>
	TAIMemorySetClass* GetAIMemorySetByClass()
	{
		TAIMemorySetClass* AIMemorySetCasted = nullptr;

		for (std::shared_ptr<FAIMemorySet>& AIMemorySetPtr : AIMemorySetArray)
		{
			AIMemorySetCasted = dynamic_cast<TAIMemorySetClass*>(AIMemorySetPtr.get());
			if (AIMemorySetCasted != nullptr)
			{
				break;
			}
		}

		return AIMemorySetCasted;
	}

protected:
	/** Choosing action method, override to change default behaviour */
	virtual void ChooseAction();

	virtual void OnActionActivated(FAIActionBase* InAction);
	virtual void OnActionDeactivated(FAIActionBase* InAction);

	void StartAction(FAIActionBase* InAction);
	void EndAction(FAIActionBase* InAction);
	void EndAllActiveActions();

protected:
	/** FAIActionBase array, see CreateAction and RemoveAction */
	CArray<std::shared_ptr<FAIActionBase>> AllAIActionsArray;

private:
	/** Array of AI memory sets. */
	CArray<std::shared_ptr<FAIMemorySet>> AIMemorySetArray;

	/** Owner entity */
	EEntity* OwnerEntity;

	/** If true Tick will choose action when previous finished. */
	bool bIsTreeEnabled;

};
