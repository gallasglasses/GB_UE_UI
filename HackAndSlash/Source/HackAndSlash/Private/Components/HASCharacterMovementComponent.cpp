// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HASCharacterMovementComponent.h"
#include "Player/HASBaseCharacter.h"

float UHASCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const AHASBaseCharacter* Player = Cast<AHASBaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}