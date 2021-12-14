// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/HASBasePickup.h"
#include "HASHealthPickup.generated.h"

class UStaticMeshComponent;

UCLASS()
class HACKANDSLASH_API AHASHealthPickup : public AHASBasePickup
{
	GENERATED_BODY()
public:
	AHASHealthPickup();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
		float HealthAmount = 50.f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;
	
private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
