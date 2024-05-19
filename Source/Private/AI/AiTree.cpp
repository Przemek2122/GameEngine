// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/AI/AiTree.h"

#include "ECS/AI/AiActionBase.h"

FAiTree::FAiTree(EEntity* InOwnerEntity)
	: ChooseActionMethod(EChooseActionMethod::Random)
	, OwnerEntity(InOwnerEntity)
	, CurrentAction(nullptr)
	, bIsTreeEnabled(true)
{
}

void FAiTree::RemoveAction(const FAiActionBase* AiAction)
{
	int Index;

	const bool bIsIndexFound = AiActionsArray.FindByLambda([&](const std::shared_ptr<FAiActionBase>& Item)
	{
		bool bIsItemEqual = false;

		if (Item.get() == AiAction)
		{
			bIsItemEqual = true;
		}

		return bIsItemEqual;
	}, Index);

	if (bIsIndexFound)
	{
		AiActionsArray.RemoveAt(Index);
	}
}

void FAiTree::TickInternal()
{
	if (bIsTreeEnabled)
	{
		Tick();
	}
}

void FAiTree::Tick()
{
	if (CurrentAction == nullptr)
	{
		ChooseActionInternal();
	}
	else
	{
		CurrentAction->Tick();
	}
}

EEntity* FAiTree::GetOwnerEntity() const
{
	return OwnerEntity;
}

void FAiTree::SetChooseActionMethod(const EChooseActionMethod InChooseActionMethod)
{
	ChooseActionMethod = InChooseActionMethod;
}

void FAiTree::SetIsTreeEnabled(const bool bInEnable)
{
	bIsTreeEnabled = bInEnable;
}

void FAiTree::ChooseActionCustom()
{
}

void FAiTree::OnActionChosen(FAiActionBase* AiAction)
{
	CurrentAction = AiAction;
	CurrentAction->StartAction();
}

void FAiTree::ChooseActionInternal()
{
	switch (ChooseActionMethod)
	{
		case EChooseActionMethod::Random:
		{
			FAiActionBase* ChosenAction = nullptr;
			CArray<std::shared_ptr<FAiActionBase>> AllActionsCopy = AiActionsArray;

			while(ChosenAction == nullptr && AllActionsCopy.Size() > 0)
			{
				int32_t RandomIndex = FMath::RandRange(0, AllActionsCopy.Size() - 1);
				const std::shared_ptr<FAiActionBase>& AiAction = AllActionsCopy[RandomIndex];

				if (AiAction->IsActionReady())
				{
					ChosenAction = AiAction.get();
				}
				else
				{
					AllActionsCopy.RemoveAt(RandomIndex);
				}
			}

			if (ChosenAction != nullptr)
			{
				OnActionChosen(ChosenAction);
			}

			break;
		}
		case EChooseActionMethod::ByPriority:
		{
			int32_t HighestPriority = -1;
			FAiActionBase* HighestPriorityAction = nullptr;

			for (std::shared_ptr<FAiActionBase>& AiAction : AiActionsArray)
			{
				if (AiAction->IsActionReady())
				{
					int32_t CurrentPriority = AiAction->GetActionPriority();

					if (CurrentPriority > HighestPriority)
					{
						HighestPriority = CurrentPriority;

						HighestPriorityAction = AiAction.get();
					}
				}
			}

			if (HighestPriorityAction != nullptr)
			{
				OnActionChosen(HighestPriorityAction);
			}

			break;
		}
		case EChooseActionMethod::Custom:
		{
			ChooseActionCustom();

			break;
		}
		default:
		{
			LOG_WARN("Default case!");
		}
	}
}
