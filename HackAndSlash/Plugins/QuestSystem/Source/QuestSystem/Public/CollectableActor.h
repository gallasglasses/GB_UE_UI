// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectableObject.h"
#include "CollectableActor.generated.h"

UCLASS()
class QUESTSYSTEM_API ACollectableActor : public AActor, public ICollectableObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void OnCollectionFinished(AActor* ActorCollectedObject);
};