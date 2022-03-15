// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"
#include "InteractableObject.h"
#include "CollectableObject.h"
#include "LocationMarker.h"
#include "Kismet/GameplayStatics.h"

UInteractionObjective::UInteractionObjective()
{
	Type = EObjectiveType::Ot_Interact;
	WorldTargetName = GET_MEMBER_NAME_CHECKED(UInteractionObjective, Target);
}

void UInteractionObjective::ActivateObjective(AActor* Instigator)
{
	//Super::ActivateObjective(Instigator);

	if (auto* InteractTarget = Cast<IInteractableObject>(Target))
	{
		InteractTarget->OnInteractionFinished.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
		{
				if (bCanBeCompleted && Instigator == InteractInstigator)
				{
					bIsCompleted = true;
					OnObjectiveCompleted.Broadcast(this);
				}
		});
	}
}

ULocationObjective::ULocationObjective()
{
	Type = EObjectiveType::Ot_Location;
	WorldTargetName = GET_MEMBER_NAME_CHECKED(ULocationObjective, Marker);
}

void ULocationObjective::ActivateObjective(AActor* Instigator)
{
	//Super::ActivateObjective(Instigator);

	if (auto* InteractTarget = Cast<ILocationMarker>(Marker))
	{
		InteractTarget->OnLocationReached.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
			{
				if (bCanBeCompleted && Instigator == InteractInstigator)
				{
					bIsCompleted = true;
					OnObjectiveCompleted.Broadcast(this);
				}
			}
		);
	}
}

UCollectionObjective::UCollectionObjective()
{
	Type = EObjectiveType::Ot_Collect;
	WorldTargetName = GET_MEMBER_NAME_CHECKED(UCollectionObjective, TargetTag);
}

void UCollectionObjective::ActivateObjective(AActor* Instigator)
{
	//Super::ActivateObjective(Instigator);

// 	FHitResult InteractHit;
// 	auto IntendedTarget = InteractHit.GetActor();
// 	auto InteractTarget = Cast<ICollectableObject>(IntendedTarget);

 	TArray<AActor*> IntendedTarget;
 	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TargetTag, IntendedTarget);
 
 	for (int32 i = 0; i < IntendedTarget.Num(); i++)
 	{
 		if (ICollectableObject* InteractTarget = Cast<ICollectableObject>(IntendedTarget[i]))
 		{
 			InteractTarget->OnCollectionFinished.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
 			{
 				if (bCanBeCompleted && Instigator == InteractInstigator)
 				{
 					if (++CollectedCount >= TargetCount)
 					{
 						bIsCompleted = true;
 						OnObjectiveCompleted.Broadcast(this);
 						UE_LOG(LogTemp, Display, TEXT("CollectedCount %d, ProgressPercent 100%%"), CollectedCount);
 						CollectedCount = 0;
 					}
 					else
 					{
 						int32 ProgressPercent = CollectedCount * 100 / TargetCount;
 						OnObjectiveInProgress.Broadcast(this, ProgressPercent);
 						UE_LOG(LogTemp, Display, TEXT("CollectedCount %d, ProgressPercent %d%%"), CollectedCount, ProgressPercent);
 					}
 				}
 			});
 		}
 	}

	/*if (auto* InteractTarget = Cast<ICollectableObject>(CollectObject))
	{
		InteractTarget->OnCollectionFinished.AddLambda([this, Instigator](AActor* Object, AActor* InteractInstigator)
			{
				if (bCanBeCompleted && Instigator == InteractInstigator)
				{
					bIsCompleted = true;
					OnObjectiveCompleted.Broadcast(this);
				}
			});
	}*/
}