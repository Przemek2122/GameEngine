// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"

enum class EChooseActionMethod
{
	Random,
	ByPriority,
	Custom
};

class FAiActionBase;

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

	/** Create AI Action. */
	template<typename TActionClass>
	TActionClass* CreateAction()
	{
		std::shared_ptr<TActionClass> ActionPtr = std::make_shared<TActionClass>(this);

		AiActionsArray.Push(ActionPtr);

		return ActionPtr.get();
	}

	/** Delete AI Action. */
	void RemoveAction(const FAiActionBase* AiAction);

	void TickInternal();

	virtual void Tick();

	EEntity* GetOwnerEntity() const;

	void SetChooseActionMethod(const EChooseActionMethod InChooseActionMethod);

	void SetIsTreeEnabled(const bool bInEnable);

protected:
	/** If you want to have custom behaviour of choosing action set ChooseActionMethod and override this method */
	virtual void ChooseActionCustom();

	virtual void OnActionChosen(FAiActionBase* AiAction);

private:
	void ChooseActionInternal();
		
	/** Current method of choosing action to play, see ChooseActionInternal */
	EChooseActionMethod ChooseActionMethod;

	/** Owner entity */
	EEntity* OwnerEntity;

	/** FAiActionBase array, see CreateAction and RemoveAction */
	CArray<std::shared_ptr<FAiActionBase>> AiActionsArray;

	/** Current AiAction running */
	FAiActionBase* CurrentAction;

	/** If true Tick will choose action when previous finished. */
	bool bIsTreeEnabled;

};
