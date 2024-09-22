// Created by Przemys³aw Wiewióra 2024

#include "CoreEngine.h"
#include "ECS/AI/AITree.h"

#include "ECS/AI/AIActionBase.h"

FAITree::FAITree(EEntity* InOwnerEntity)
	: ChooseActionMethod(EChooseActionMethod::Random)
	, OwnerEntity(InOwnerEntity)
	, CurrentAction(nullptr)
	, bIsTreeEnabled(true)
{
}

void FAITree::RemoveAction(const FAIActionBase* AiAction)
{
	ContainerInt Index;

	const bool bIsIndexFound = AiActionsArray.FindByLambda([&](const std::shared_ptr<FAIActionBase>& Item)
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
			FinishAction();
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

void FAITree::OnActionChosen(FAIActionBase* AiAction)
{
	StartAction(AiAction);
}

void FAITree::StartAction(FAIActionBase* AiAction)
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
			FAIActionBase* ChosenAction = nullptr;
			CArray<std::shared_ptr<FAIActionBase>> AllActionsCopy = AiActionsArray;

			while(ChosenAction == nullptr && AllActionsCopy.Size() > 0)
			{
				int32_t RandomIndex = FMath::RandRange(0, AllActionsCopy.Size() - 1);
				const std::shared_ptr<FAIActionBase>& AiAction = AllActionsCopy[RandomIndex];

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
			FAIActionBase* HighestPriorityAction = nullptr;

			for (std::shared_ptr<FAIActionBase>& AiAction : AiActionsArray)
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

void FAITree::FinishAction()
{
	CurrentAction->End();

	CurrentAction = nullptr;
}
