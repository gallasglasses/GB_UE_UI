// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/HASDealDamageAnimNotifyState.h"
#include "Engine.h"

void UHASDealDamageAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::White, __FUNCTION__);
	OnNotifiedStateSignature.Broadcast();
}

//void UHASDealDamageAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Silver, __FUNCTION__);
//	
//	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
//}

void UHASDealDamageAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Black, __FUNCTION__);
}