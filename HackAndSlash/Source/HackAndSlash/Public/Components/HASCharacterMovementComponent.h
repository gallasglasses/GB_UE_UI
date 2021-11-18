// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HASCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.1", ClampMax = "3.0"))
	float RunModifier = 1.5f;
	virtual float GetMaxSpeed() const override;
};
