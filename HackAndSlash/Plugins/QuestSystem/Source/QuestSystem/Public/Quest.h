// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest.generated.h"

class UObjective;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestAction, AQuest*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStatusChanged, AQuest*);

UCLASS()
class QUESTSYSTEM_API AQuest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		FText Name;

	UPROPERTY(EditAnywhere)
		FText Description;

	UPROPERTY(EditAnywhere)
		TArray<UObjective*> Objectives;

	UPROPERTY(EditAnywhere)
		bool bIsStoryQuest = true;

	UPROPERTY(EditAnywhere)
		bool bKeepObjectivesOrder = true;

	UPROPERTY(EditAnywhere)
		AQuest* PreviousQuest;

	UPROPERTY(EditAnywhere)
		bool bIsTaken = false;

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "NewObjectives")
		void UpdateLocation();

	UFUNCTION()
		void TakeQuest(AActor* Character);

	UFUNCTION(BlueprintPure)
		const TArray<UObjective*>& GetObjectives() const;

	void OnObjectiveCompleted(UObjective* Objective);

	bool IsCompleted() const;

	FOnQuestAction OnQuestStatusChanged;
	FOnStatusChanged OnStatusChanged;

#if WITH_EDITOR

	UFUNCTION(CallInEditor, Category = "NewObjectives")
		void AddInteractObjective();

	UFUNCTION(CallInEditor, Category = "NewObjectives")
		void AddLocationObjective();

	UFUNCTION(CallInEditor, Category = "NewObjectives")
		void AddCollectionObjective();

#endif
};
