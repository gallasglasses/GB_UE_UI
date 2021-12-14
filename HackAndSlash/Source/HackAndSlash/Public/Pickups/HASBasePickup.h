// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HASBasePickup.generated.h"

class USphereComponent;

UCLASS()
class HACKANDSLASH_API AHASBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	AHASBasePickup();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
		USphereComponent* CollisionComponent;

	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn);
	void PickupWasTaken();
};
