// Fill out your copyright notice in the Description page of Project Settings.

#include "LocationMarkerActor.h"

ALocationMarkerActor::ALocationMarkerActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALocationMarkerActor::BeginPlay()
{
	Super::BeginPlay();

}

void ALocationMarkerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALocationMarkerActor::OnOverlapByActor(AActor* OverlappingActor)
{
	NotifyOverlapWithActor(this, OverlappingActor);
}
