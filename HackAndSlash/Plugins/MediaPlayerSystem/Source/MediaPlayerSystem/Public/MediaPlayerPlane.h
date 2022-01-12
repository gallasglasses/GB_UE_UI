// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MediaPlayerPlane.generated.h"

class UMediaPlayer;

UCLASS()
class MEDIAPLAYERSYSTEM_API AMediaPlayerPlane : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMediaPlayerPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMediaPlayer* MediaPlayer;
};
