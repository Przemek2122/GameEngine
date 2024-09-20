// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/AI/AITree.h"

#include "ECS/AI/AiActionBase.h"

FAITree::FAITree(EEntity* InOwnerEntity)
	: ChooseActionMethod(EChooseActionMethod::Random)
	, OwnerEntity(InOwnerEntity)
	, CurrentAction(nullptr)
	, bIsTreeEnabled(true)
{
}

void FAITree::RemoveAction(const FAiActionBase* AiAction)
{
	ContainerInt Index;

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

void FAITree::TickInternal()
{
	if (bIsTreeEnabled)
	{
		Tick();
	}
}

void FAITree::Tick()
{
	if (CurrentAction == nullptr)
	{
		ChooseActionInternal();
	}
	else
	{
		if (CurrentAction->ShouldFinishAction())
		{
			CurrentAction->End();

			CurrentAction = nullptr;
		}
		else
		{
			CurrentAction->Tick();
		}
	}
}

EEntity* FAITree::GetOwnerEntity() const
{
	return OwnerEntity;
}

void FAITree::SetChooseActionMethod(const EChooseActionMethod InChooseActionMethod)
{
	ChooseActionMethod = InChooseActionMethod;
}

void FAITree::SetIsTreeEnabled(const bool bInEnable)
{
	bIsTreeEnabled = bInEnable;
}

void FAITree::ChooseActionCustom()
{
}

void FAITree::OnActionChosen(FAiActionBase* AiAction)
{
	CurrentAction = AiAction;
	CurrentAction->Start();
}

void FAITree::ChooseActionInternal()
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
