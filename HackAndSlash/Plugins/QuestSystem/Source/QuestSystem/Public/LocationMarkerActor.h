// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LocationMarker.h"
#include "GameFramework/Actor.h"
#include "LocationMarkerActor.generated.h"

UCLASS()
class QUESTSYSTEM_API ALocationMarkerActor : public AActor, public ILocationMarker
{
	GENERATED_BODY()

public:
	ALocationMarkerActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void OnOverlapByActor(AActor* OverlappingActor);
};