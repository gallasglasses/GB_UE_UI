// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActorSpawnerWidget.generated.h"

class UTextBlock;

UCLASS()
class HACKANDSLASH_API UActorSpawnerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SpawnerClass;
	
	UPROPERTY()
	AActor* SpawnedActor = nullptr;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TextDraggedItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NameDraggedItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText PickupDescription;

	void OnMouseButtonUp();
};
