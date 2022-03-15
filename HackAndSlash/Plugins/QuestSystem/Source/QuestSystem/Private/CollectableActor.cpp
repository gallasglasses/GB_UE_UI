// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectableActor.h"

void ACollectableActor::OnCollectionFinished(AActor* ActorCollectedObject)
{
	NotifyCollectionFinished(this, ActorCollectedObject);
}